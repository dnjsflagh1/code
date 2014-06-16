/******************************************************************************/
#include "stdafx.h"
#include "Pathfinder2.h"
#include "MGSceneNode.h"
#include "MGEngineUtility.h"


#include <memory.h>

/******************************************************************************/

namespace MG
{
	#define FINDPATHCELL_BINARYHEAP_ADD_UP_COUNT 10000
	#define FINDPATHCELL_FASTSTRUCTPOOL_ADD_UP_COUNT 2000
	#define FINDPATHPARTLENGHT	20


    //-----------------------------------------------------------------------
    PathFinder2::PathFinder2()
    {
        mPathFinderType = PT_ALWAYS_NEAREST;

        mBlockCheckCellRadius = 0;

		mMapBlock = NULL;
		mOpenList = NULL;
		mCellPool = NULL;

		mFindPathEightCellOffset.push_back( VecI82( 1  ,0) );
		mFindPathEightCellOffset.push_back( VecI82( 1  ,1) );
		mFindPathEightCellOffset.push_back( VecI82( 0  ,1) );
		mFindPathEightCellOffset.push_back( VecI82( -1 ,1) );
		mFindPathEightCellOffset.push_back( VecI82( -1 ,0) );
		mFindPathEightCellOffset.push_back( VecI82( -1 ,-1) );
		mFindPathEightCellOffset.push_back( VecI82( 0  ,-1) );
		mFindPathEightCellOffset.push_back( VecI82( 1  ,-1) );
    }

    //-----------------------------------------------------------------------
    PathFinder2::~PathFinder2()
    {
        unLoad();
    }

    //-----------------------------------------------------------------------
    void PathFinder2::load( GridPool<Byte>* mapBlock )
    {
        mMapBlock = mapBlock;

        unLoad();

		mMapGridWidth	= mapBlock->getWorldGridWidth();
		mMapGridHeight	= mapBlock->getWorldGridHeight();
		mMapOneGridSize = mapBlock->getGridSize();
		Vec2 leftBottomPos = mapBlock->getLeftBottomPos(); 

        mCellGrids.createGrids(mMapGridWidth, mMapGridHeight, mMapOneGridSize, leftBottomPos);

		mOpenList = MG_NEW BinaryHeap<FindPathCell*>(FINDPATHCELL_BINARYHEAP_ADD_UP_COUNT);
		mCellPool = MG_NEW FastStructPool<FindPathCell>(FINDPATHCELL_FASTSTRUCTPOOL_ADD_UP_COUNT);
    }

	//-----------------------------------------------------------------------
	void PathFinder2::unLoad()
	{
		mCellGrids.destroyGrids();
		
		MG_SAFE_DELETE( mOpenList );
		MG_SAFE_DELETE( mCellPool );
	}

	//-----------------------------------------------------------------------
	Bool PathFinder2::isLoaded()
	{
		return mMapBlock != NULL;
	}

    //-----------------------------------------------------------------------
    void PathFinder2::setType ( PathFinder2::PathFinderType type )
    {
        mPathFinderType = type;
    }

	//-----------------------------------------------------------------------
	void PathFinder2::convertWorldPositionToGridPoint( Vec3 startPos, VecU2& gridPoint )
	{
		if( isLoaded() == false)
		{
			return;
		}

		mMapBlock->convertWorldPositionToGridPoint(Vec2(startPos.x, startPos.z), gridPoint);
	}

    //-----------------------------------------------------------------------
    PathFindingResult PathFinder2::findPath( VecU2 startCellPoint, VecU2 targetCellPoint, 
								std::map<UInt, UInt>& ignoreBlockIndexList, 
								UInt moveCellDiameter, 
								Int checkMaxPath, 
								Int checkMaxDynamicBlock )
    {

		PathFindingResult result = PFR_ERROR;

		//------------------------------------------------------------------------------------
		//@ 参数检查
		//------------------------------------------------------------------------------------

		if( isLoaded() == false)
		{
			return PFR_ERROR;
		}
		
		if(startCellPoint == targetCellPoint)
		{
			return PFR_ALREADY_ARRIVE;
		}

		if( abs( (Int)startCellPoint.x - (Int)targetCellPoint.x ) < (Int)1 )
		{
            if( abs( (Int)startCellPoint.y - (Int)targetCellPoint.y ) < (Int)1 )
            {
                return PFR_ALREADY_ARRIVE;
            }
		}

		if ( checkMaxPath < 0 )
		{
			checkMaxPath = mMapGridWidth * mMapGridHeight;
		}

		if ( checkMaxDynamicBlock < 0 )
		{
			checkMaxDynamicBlock = mMapGridWidth * mMapGridHeight;
		}

        //------------------------------------------------------------------------------------
        //@ 数据初始化
        //------------------------------------------------------------------------------------

		// 淸空网格池
		mCellPool->clear();

		// 淸空开启二叉堆
		mOpenList->makeEmpty();
		
        // 保存参数
        mIgnoreBlockIndexList   = ignoreBlockIndexList;
        // 障碍检测偏移范围


        // 障碍网格大小
        UInt fCellSize = (moveCellDiameter) * 0.5;
        mBlockCheckCellRadius = fCellSize;
        
		//if(mBlockCheckCellRadius != 0)
		//{
		//	mBlockCheckCellRadius += 2;
		//}

        // 清空结果
		mFindPathCellFullResult.clear();
		mFindPathNodeFullResult.clear();
		mFindPathCellCombineResult.clear();
        mFindPathNodeCombineResult.clear();
		mFindPathNodeSmoothResult.clear();

		//------------------------------------------------------------------------------------
		//@ 参数声明
		//------------------------------------------------------------------------------------

		// 在关闭列表中的离目标点最近的网格对象
		FindPathCell* nearestCellInCloseList = NULL;

		// 当前检测的网格坐标和网格
		VecU2 currCheckCellPoint;
		FindPathCell* currCheckCell = NULL;

		// 当前检测点周围的网格
		VecU2 currCheckAroundCellPoint;
		FindPathCell* currCheckAroundCell = NULL;


		// 起始点和目标点网格
		FindPathCell* startCell = NULL;
		FindPathCell* destCell = NULL;

		//------------------------------------------------------------------------------------
		//@ 增加忽略列表中的网格
        //------------------------------------------------------------------------------------
		for ( std::map<UInt, UInt>::iterator it = ignoreBlockIndexList.begin(); it != ignoreBlockIndexList.end(); ++it )
		{
			UInt index = it->first;
			mCellGrids.convertGridIndexToGridPoint( index, currCheckCellPoint );
			activeFindPathCell( currCheckCellPoint, currCheckCell );		

			if ( currCheckCell )
			{
				// 忽略是否是障碍的检测
				currCheckCell->findPathState = FindPathCell::FS_IDLE;
                currCheckCell->blockState = FindPathCell::BS_OUT_BLOCK;
			}
		}

		//------------------------------------------------------------------------------------
		//@ 增加目标点和起始点
		//------------------------------------------------------------------------------------

		// 目标点
		activeFindPathCell( targetCellPoint, destCell );	
        destCell->findPathState = FindPathCell::FS_IDLE ;
        destCell->blockState = FindPathCell::BS_OUT_BLOCK ;

		// 起始点
		activeFindPathCell( startCellPoint, startCell );	
		startCell->findPathState = FindPathCell::FS_IDLE;

		// 增加起始点到开启列表
		startCell->gCost = 0;
		startCell->binaryHeapCost = getMoveHCost( startCell, destCell ) + 0;
		mOpenList->insert( startCell );
		startCell->findPathState = FindPathCell::FS_IN_OPEN_LIST;

		//------------------------------------------------------------------------------------
		//@ 寻路计算
		//------------------------------------------------------------------------------------

		// 循环次数
		Int loopCount = 0;
		// 遇到动态障碍次数
		Int checkDynamicBlockCount = 0;

		//8网格循环索引
		UInt eightCellLoopIndex = 0;
		//8网格循环次数
		UInt eightCellLoopCount = 8;
		//8网格偏移
		VecI82	eightCellOffset;

		// 用于保存 gCost hCost 计算中间值
		UInt gCost = 0;
		UInt hCost = 0;

		// 碰撞检测循环索引
		VecU2 blockCheckIndex;
		VecU2 blockCheckMaxIndex;

		FindPathCell* currBlockCheckCell = NULL;
		Bool isBlock = false;

        // 动态碰撞标志位
        Bool dynamicBlockDirty = false;

        // 是否检测
        Bool isCheckBlock = true;

		while( true )
		{

			//------------------------------------------------------------------------------------
			//@ 寻找开启列表中F值最低的格子。我们称它为当前格
			//------------------------------------------------------------------------------------

			mOpenList->deleteMin( currCheckCell );


			//------------------------------------------------------------------------------------
			//@ 加入关闭列表
			//------------------------------------------------------------------------------------

			currCheckCell->findPathState = FindPathCell::FS_IN_CLOSE_LIST;

            // 如果是目标点则退出
            if ( currCheckCell == destCell )
            {
                nearestCellInCloseList = currCheckCell;
                break; //退出循环
            }

            // 如果没有则直接设置
            if ( nearestCellInCloseList == NULL )
            {
                nearestCellInCloseList = currCheckCell;
            }else
            {
                // 扩散式寻路
                if ( mPathFinderType == PT_SPREAD_SEARCH )
                {
                    // 保存关闭列表中gCost移动耗损最大的一个
                    if ( currCheckCell->gCost >= nearestCellInCloseList->gCost )
                    {
                        nearestCellInCloseList = currCheckCell;
                    }
                }else
                // 最近点寻路
                {
                    // 保存关闭列表中binaryHeapCost移动耗损最小的一个
					// 不用"<="是为了防止来回移动
                    if ( currCheckCell->binaryHeapCost < nearestCellInCloseList->binaryHeapCost )
                    {
                        nearestCellInCloseList = currCheckCell;
                    }
                }
            }


            //------------------------------------------------------------------------------------
            //@ 检测当前点障碍
            //------------------------------------------------------------------------------------

            // 如果检测出有障碍，则无需再次检测障碍，为了防止在障碍内卡死
            //if ( checkBlock( currCheckCell, currBlockCheckCell, blockCheckIndex, blockCheckMaxIndex ) )
            //{
            //    isCheckBlock = false;
            //}else
            //{
            //    isCheckBlock = true;
            //}


			//------------------------------------------------------------------------------------
			//@ 检测当前点周围8个网格
			//------------------------------------------------------------------------------------
			
			for(eightCellLoopIndex = 0; eightCellLoopIndex < eightCellLoopCount; ++eightCellLoopIndex)
			{	
				eightCellOffset = mFindPathEightCellOffset[ eightCellLoopIndex ];

				// 根据偏移量获取到周围网格对象
				currCheckAroundCellPoint.x = currCheckCell->x + eightCellOffset.x;
				currCheckAroundCellPoint.y = currCheckCell->z + eightCellOffset.y;

				activeFindPathCell( currCheckAroundCellPoint, currCheckAroundCell );

				if ( currCheckAroundCell )
				{
					//------------------------------------------------------------------------------------
					//@ 检测障碍
					// 以检测网格为中心 mBlockCheckCellRadius为半径范围检测周围的网格是否为障碍
					//------------------------------------------------------------------------------------

                    if ( isCheckBlock )
                    {
					    isBlock = checkBlock( currCheckAroundCell, currBlockCheckCell, blockCheckIndex, blockCheckMaxIndex, eightCellOffset  );
                    }else
                    {
                        isBlock = false;
                    }

				    if ( isBlock )
                    {
                        if ( currBlockCheckCell )
                        {
                            // 如果是静态障碍则略过
                            if ( currBlockCheckCell->blockState == FindPathCell::BS_IN_STATIC_BLOCK )
                                continue;

                            // 如果是动态障碍则略过,并记录
                            if ( currBlockCheckCell->blockState == FindPathCell::BS_IN_DYNAMIC_BLOCK )
                            {
                                dynamicBlockDirty = true;
                                continue;
                            }
                        }else
                        {
                            continue;
                        }
                    }
                    
					//------------------------------------------------------------------------------------
					//@ 检测关闭列表
					//------------------------------------------------------------------------------------
					// 如果是关闭列表则略过
					if ( currCheckAroundCell->findPathState == FindPathCell::FS_IN_CLOSE_LIST )
						continue;

					//------------------------------------------------------------------------------------
					//@ 检测开启列表
					//------------------------------------------------------------------------------------
					// 如果不在开始列表中，把它添加进去。把当前格作为这一格的父节点。记录这一格的F,G,和H值。
					if ( currCheckAroundCell->findPathState != FindPathCell::FS_IN_OPEN_LIST )
					{
						// 设置父节点
						currCheckAroundCell->parent = currCheckCell;

						// 记录F,G,和H值。
						currCheckAroundCell->gCost = getMoveGCost( currCheckAroundCell, currCheckCell );
						currCheckAroundCell->binaryHeapCost = currCheckAroundCell->gCost + getMoveHCost( currCheckAroundCell, destCell );

						// 放入到开启列表中
						mOpenList->insert( currCheckAroundCell );
						currCheckAroundCell->findPathState = FindPathCell::FS_IN_OPEN_LIST;
					}else
					//如果它已经在开启列表中，用G值为参考检查新的路径是否更好。更低的G值意味着更好的路径。
					//如果是这样，就把这一格的父节点改成当前格，并且重新计算这一格的G和F值. 并重新对开启列表排序
					{
						gCost = getMoveGCost( currCheckAroundCell, currCheckCell );
						if ( gCost < currCheckAroundCell->gCost )
						{
							// 重新设置父节点
							currCheckAroundCell->parent = currCheckCell;

							// 记录F,G,和H值。
							hCost = currCheckAroundCell->binaryHeapCost - currCheckAroundCell->gCost;
							currCheckAroundCell->gCost = gCost;
							currCheckAroundCell->binaryHeapCost = currCheckAroundCell->gCost + hCost;

							// 重新排序
							mOpenList->filterUp( currCheckAroundCell->binaryHeapIndex );
						}
					}

				}
			}

			//------------------------------------------------------------------------------------
			//@ 没有找到目标点的跳出循环判断
			//------------------------------------------------------------------------------------

			// 如果开启列表为空，则退出
			if ( mOpenList->isEmpty() )
			{
				break;	//退出循环
			}

			// 如果检测次数超过限定值则退出
			if ( loopCount++ > checkMaxPath )
			{
				result = PFR_OVER_LENGTH;
				break; //退出循环
			}

			// 如果遇到动态障碍次数超过限定值则退出
            if ( dynamicBlockDirty )
            {
                if ( ++checkDynamicBlockCount > checkMaxDynamicBlock )
                {
				    result = PFR_OVER_DYNAMIC_BLOCK;
                    break; //退出循环
                }
                dynamicBlockDirty = false;
            }
		}

		//------------------------------------------------------------------------------------
		//@ 从关闭列表中 获得完整网格路径
		//------------------------------------------------------------------------------------
	
        // 如果最近点是目标点则表示不需要寻路
        if(startCell == nearestCellInCloseList)
        {
            return PFR_LOSE_WAY;
        }

		if ( nearestCellInCloseList )
		{
			currCheckCell = nearestCellInCloseList;
	
			UInt loopLimit = mMapGridWidth * mMapGridHeight;
			UInt loopCount = 0;
			while( true )
			{
				// 保存节点到结果列表中
				mFindPathCellFullResult.push_back( VecU2(currCheckCell->x, currCheckCell->z) );
			
				// 如果是开始节点则退出
				if ( currCheckCell == startCell )
				{
					result = PFR_SUCCESS;
					break;
				}

				// 如果没有父节点则退出
				if ( currCheckCell->parent == NULL )
				{
					DYNAMIC_ASSERT( false );
					break;
				}

				// 超过循环次数则退出
				if ( loopCount++ > loopLimit )
				{
					DYNAMIC_ASSERT( false );
					break;
				}

				// 获得父节点
				currCheckCell = currCheckCell->parent;
			}
		}
		
		return	result ;
    }

	//-----------------------------------------------------------------------
	std::vector<VecU2>& PathFinder2::getFullFindCellPathResult()
	{
		return mFindPathCellFullResult;
	}

	//-----------------------------------------------------------------------
	std::vector<Vec3>& PathFinder2::getFullFindPathNodeResult()
	{
		if ( mFindPathNodeFullResult.size() != mFindPathCellFullResult.size() )
		{

		}

		return mFindPathNodeFullResult;
	}

    //-----------------------------------------------------------------------
    std::vector<VecU2>& PathFinder2::getCombineFindCellPathResult()
    {
        if ( mFindPathCellCombineResult.size() == 0 )
        {
            mFindPathCellCombineResult.size();

            if ( mFindPathCellFullResult.size() <= 0 )
            {
                
            }else
            if ( mFindPathCellFullResult.size() == 1 )
            {
                mFindPathCellCombineResult.push_back( mFindPathCellFullResult[0] );
            }else
            {

                UInt cellListMaxIndex = mFindPathCellFullResult.size() - 1;

                // 当前和上一个网格
                VecU2 currCell = mFindPathCellFullResult[cellListMaxIndex-1];
                VecU2 lastCell = mFindPathCellFullResult[cellListMaxIndex];

                VecU2 newAddCell = lastCell;
                VecU2 finalCell = mFindPathCellFullResult[0];

                // 当前和上一个网格方向
                PathFinder2::Movedir currMoveDir = md_null;
                PathFinder2::Movedir lastMoveDir = getMoveDir( lastCell, currCell );

                // 增加起始网格坐标
                mFindPathCellCombineResult.push_back( lastCell );
                newAddCell = lastCell;

				UInt listNum = 0;

                // 遍历寻路网格列表，合并同方向网格
                // 从倒数第二个开始遍历
                Int loopSize = cellListMaxIndex - 1;
                for(Int i = loopSize; i > 0; --i)
                {
                    currCell = mFindPathCellFullResult[i];

                    currMoveDir = getMoveDir( lastCell, currCell );

                    if( lastMoveDir != currMoveDir )
                    {
						listNum = mFindPathCellCombineResult.size();
						if(!(lastCell == mFindPathCellCombineResult[0]) && !(lastCell == mFindPathCellCombineResult[listNum - 1]))
						{
							mFindPathCellCombineResult.push_back(lastCell);
						}
		
                        mFindPathCellCombineResult.push_back(currCell);
                        newAddCell = currCell;
                        lastMoveDir = currMoveDir;
                    }

                    lastCell = currCell;
                }

                // 如果最后一个不是最终网格坐标，则加之
                if ( !(newAddCell==finalCell) )
                {
                    mFindPathCellCombineResult.push_back( finalCell );
                }
            }
        }

        return mFindPathCellCombineResult;
    }

	//-----------------------------------------------------------------------
	std::vector<Vec3>&	PathFinder2::getFindPathNodePartResult()
	{
		mFindPathNodePartResult.clear();
		Int loopSize = mFindPathNodeCombineResult.size();
		Vec3 lastPos;
		Vec3 currPos;

		Vec3 dir;
		Flt disLen = 0;

		for(Int i = 0; i < loopSize; i++)
		{
			if(i == 0)
			{
				lastPos = mFindPathNodeCombineResult[i];
				mFindPathNodePartResult.push_back(lastPos);
				continue;
			}
			else
			{
				currPos = mFindPathNodeCombineResult[i];
			}

			dir = currPos - lastPos;
			disLen = dir.length();
			if(disLen > FINDPATHPARTLENGHT)
			{
				UInt partNum = disLen / FINDPATHPARTLENGHT;
				dir.normalise();
				for(UInt partIndex = 0; partIndex < partNum; ++partIndex)
				{
					Vec3 pos = lastPos + dir * (partIndex + 1) * FINDPATHPARTLENGHT;
					mFindPathNodePartResult.push_back(pos);
				}
			}
	
			mFindPathNodePartResult.push_back(currPos);

			lastPos = currPos;
		}

		return mFindPathNodePartResult;
	}

    //-----------------------------------------------------------------------
    std::vector<Vec3>& PathFinder2::getCombineFindPathNodeResult() 
    {
        getCombineFindCellPathResult();

		if ( mFindPathNodeCombineResult.size() != mFindPathCellCombineResult.size() )
        {
            mFindPathNodeCombineResult.clear();

            Int loopSize = mFindPathCellCombineResult.size();
            Vec3 worldPos;
            Vec2 worldPos2D;
            for(Int i = 0; i < loopSize; i++)
            {
                mCellGrids.convertGridPointToWorldPosition(mFindPathCellCombineResult[i], worldPos2D);

                worldPos.x = worldPos2D.x;
                worldPos.y = 0;
                worldPos.z = worldPos2D.y;
                mFindPathNodeCombineResult.push_back( worldPos );
            }
        }

        return mFindPathNodeCombineResult;
    }

	//-----------------------------------------------------------------------
	std::vector<Vec3>& PathFinder2::getSmoothFindPathNodeResult()
	{
		getCombineFindPathNodeResult();
		std::vector<Vec3> mFindPathNodeResult = getFindPathNodePartResult();

        if ( mFindPathNodeSmoothResult.size() == 0 )
        {
            if(mFindPathNodeResult.size() == 0)
            {
                return mFindPathNodeSmoothResult;
            }
            mFindPathNodeSmoothResult = mFindPathNodeResult;

            ///////////////////////////////////////////////////////////////////////

            Bool isAdd      = true;
            Int index       = 0;
            Vec3 startPos   = mFindPathNodeSmoothResult[0];
            Vec3 targetPos  = mFindPathNodeSmoothResult[mFindPathNodeSmoothResult.size() - 1];
            std::vector<Vec3>::iterator tempIt;

            std::vector<Vec3>::iterator it = mFindPathNodeSmoothResult.begin();
            for(; it != mFindPathNodeSmoothResult.end();)
            {
                if(isAdd && (index == 0 || index % 2 != 0))
                {
                    ++index;

                    if(index != 0)
                    {
                        tempIt = it;
                    }

                }
                else 
                if( isBlockBetweenTwoPos(startPos, (*it)) == false )
                {
                    it = mFindPathNodeSmoothResult.erase(tempIt);
                    tempIt = it;
                    isAdd = false;
                }
                else
                {
                    startPos = (*it);
                    isAdd = true;
                    ++index;
                }

                ++it;

                if(it == mFindPathNodeSmoothResult.end())
                {
                    return mFindPathNodeSmoothResult;
                }
            }
        }
        
		return mFindPathNodeSmoothResult;
	}

    //-----------------------------------------------------------------------
    Bool PathFinder2::isBlockBetweenTwoPos( Vec3 startPos, Vec3 endPos )
    {
        // 检测数据初始化
        Flt dis             = (endPos - startPos).length();
        Flt currDis         = 0;
        Vec3 lastPos        = startPos;
        Vec3 currPos        = startPos;
        Vec3 dir            = (endPos - startPos);
        dir.normalise();
        // 使用网格长度递增检测
        dir = dir * mMapBlock->getGridSize();

        // 碰撞网格对象
        FindPathCell* currBlockCheckCell = NULL;
        FindPathCell* currBlockCheckCellResult = NULL;
        // 碰撞检测循环索引
        VecU2 blockCheckIndex;
        VecU2 blockCheckMaxIndex;
        VecU2 gridPoint;
		VecI82 gridDir;
        Bool isBlock = false;

		VecU2 startGridPoint;
		VecU2 endGridPoint;

		VecU2 lastGridPoint;

		Int offSetX = 0;
		Int offSetY = 0;

        //TODO:JJJ
        // 需要吧dir分解成2个网格方向
       

        // 递增检测网格数据
        while(1)
        {
			lastGridPoint = gridPoint;
            lastPos = currPos;
            currPos += dir;
            currDis = (currPos - startPos).length();
            if(currDis >= dis)
            {
                return false;
            }

			convertWorldPositionToGridPoint( currPos, gridPoint );
			if(gridPoint == lastGridPoint && !(gridPoint == VecU2(0,0)))
			{
				continue;
			}

			mMapBlock->convertWorldPositionToGridPoint(Vec2(lastPos.x, lastPos.z), startGridPoint);
			mMapBlock->convertWorldPositionToGridPoint(Vec2(currPos.x,currPos.z), endGridPoint);

			offSetX = endGridPoint.x - startGridPoint.x;
			offSetY = endGridPoint.y - startGridPoint.y;

			if(offSetX > 0)
			{
				gridDir.x = 1;
			}
			else if(offSetX < 0)
			{
				gridDir.x = -1;
			}
			else
			{
				gridDir.x = 0;
			}

			if(offSetY > 0)
			{
				gridDir.y = 1;
			}
			else if(offSetY < 0)
			{
				gridDir.y = -1;
			}
			else
			{
				gridDir.y = 0;
			}

            activeFindPathCell( gridPoint, currBlockCheckCell );

            if ( currBlockCheckCell )
            {
                //TODO:JJJ  需要吧dir分解成2个网格方向
				isBlock = checkBlock( currBlockCheckCell, currBlockCheckCellResult, blockCheckIndex, blockCheckMaxIndex, gridDir );
                //isBlock = checkBlock( currBlockCheckCell, currBlockCheckCellResult, blockCheckIndex, blockCheckMaxIndex, gridDir1 );
                //isBlock = checkBlock( currBlockCheckCell, currBlockCheckCellResult, blockCheckIndex, blockCheckMaxIndex, gridDir2 );

                if( isBlock )
                {
                    return true;
                }
            }
        }

        return false;
    }
}
