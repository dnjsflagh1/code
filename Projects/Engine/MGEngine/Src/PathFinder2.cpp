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
		//@ �������
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
        //@ ���ݳ�ʼ��
        //------------------------------------------------------------------------------------

		// �[�������
		mCellPool->clear();

		// �[�տ��������
		mOpenList->makeEmpty();
		
        // �������
        mIgnoreBlockIndexList   = ignoreBlockIndexList;
        // �ϰ����ƫ�Ʒ�Χ


        // �ϰ������С
        UInt fCellSize = (moveCellDiameter) * 0.5;
        mBlockCheckCellRadius = fCellSize;
        
		//if(mBlockCheckCellRadius != 0)
		//{
		//	mBlockCheckCellRadius += 2;
		//}

        // ��ս��
		mFindPathCellFullResult.clear();
		mFindPathNodeFullResult.clear();
		mFindPathCellCombineResult.clear();
        mFindPathNodeCombineResult.clear();
		mFindPathNodeSmoothResult.clear();

		//------------------------------------------------------------------------------------
		//@ ��������
		//------------------------------------------------------------------------------------

		// �ڹر��б��е���Ŀ���������������
		FindPathCell* nearestCellInCloseList = NULL;

		// ��ǰ�����������������
		VecU2 currCheckCellPoint;
		FindPathCell* currCheckCell = NULL;

		// ��ǰ������Χ������
		VecU2 currCheckAroundCellPoint;
		FindPathCell* currCheckAroundCell = NULL;


		// ��ʼ���Ŀ�������
		FindPathCell* startCell = NULL;
		FindPathCell* destCell = NULL;

		//------------------------------------------------------------------------------------
		//@ ���Ӻ����б��е�����
        //------------------------------------------------------------------------------------
		for ( std::map<UInt, UInt>::iterator it = ignoreBlockIndexList.begin(); it != ignoreBlockIndexList.end(); ++it )
		{
			UInt index = it->first;
			mCellGrids.convertGridIndexToGridPoint( index, currCheckCellPoint );
			activeFindPathCell( currCheckCellPoint, currCheckCell );		

			if ( currCheckCell )
			{
				// �����Ƿ����ϰ��ļ��
				currCheckCell->findPathState = FindPathCell::FS_IDLE;
                currCheckCell->blockState = FindPathCell::BS_OUT_BLOCK;
			}
		}

		//------------------------------------------------------------------------------------
		//@ ����Ŀ������ʼ��
		//------------------------------------------------------------------------------------

		// Ŀ���
		activeFindPathCell( targetCellPoint, destCell );	
        destCell->findPathState = FindPathCell::FS_IDLE ;
        destCell->blockState = FindPathCell::BS_OUT_BLOCK ;

		// ��ʼ��
		activeFindPathCell( startCellPoint, startCell );	
		startCell->findPathState = FindPathCell::FS_IDLE;

		// ������ʼ�㵽�����б�
		startCell->gCost = 0;
		startCell->binaryHeapCost = getMoveHCost( startCell, destCell ) + 0;
		mOpenList->insert( startCell );
		startCell->findPathState = FindPathCell::FS_IN_OPEN_LIST;

		//------------------------------------------------------------------------------------
		//@ Ѱ·����
		//------------------------------------------------------------------------------------

		// ѭ������
		Int loopCount = 0;
		// ������̬�ϰ�����
		Int checkDynamicBlockCount = 0;

		//8����ѭ������
		UInt eightCellLoopIndex = 0;
		//8����ѭ������
		UInt eightCellLoopCount = 8;
		//8����ƫ��
		VecI82	eightCellOffset;

		// ���ڱ��� gCost hCost �����м�ֵ
		UInt gCost = 0;
		UInt hCost = 0;

		// ��ײ���ѭ������
		VecU2 blockCheckIndex;
		VecU2 blockCheckMaxIndex;

		FindPathCell* currBlockCheckCell = NULL;
		Bool isBlock = false;

        // ��̬��ײ��־λ
        Bool dynamicBlockDirty = false;

        // �Ƿ���
        Bool isCheckBlock = true;

		while( true )
		{

			//------------------------------------------------------------------------------------
			//@ Ѱ�ҿ����б���Fֵ��͵ĸ��ӡ����ǳ���Ϊ��ǰ��
			//------------------------------------------------------------------------------------

			mOpenList->deleteMin( currCheckCell );


			//------------------------------------------------------------------------------------
			//@ ����ر��б�
			//------------------------------------------------------------------------------------

			currCheckCell->findPathState = FindPathCell::FS_IN_CLOSE_LIST;

            // �����Ŀ������˳�
            if ( currCheckCell == destCell )
            {
                nearestCellInCloseList = currCheckCell;
                break; //�˳�ѭ��
            }

            // ���û����ֱ������
            if ( nearestCellInCloseList == NULL )
            {
                nearestCellInCloseList = currCheckCell;
            }else
            {
                // ��ɢʽѰ·
                if ( mPathFinderType == PT_SPREAD_SEARCH )
                {
                    // ����ر��б���gCost�ƶ���������һ��
                    if ( currCheckCell->gCost >= nearestCellInCloseList->gCost )
                    {
                        nearestCellInCloseList = currCheckCell;
                    }
                }else
                // �����Ѱ·
                {
                    // ����ر��б���binaryHeapCost�ƶ�������С��һ��
					// ����"<="��Ϊ�˷�ֹ�����ƶ�
                    if ( currCheckCell->binaryHeapCost < nearestCellInCloseList->binaryHeapCost )
                    {
                        nearestCellInCloseList = currCheckCell;
                    }
                }
            }


            //------------------------------------------------------------------------------------
            //@ ��⵱ǰ���ϰ�
            //------------------------------------------------------------------------------------

            // ����������ϰ����������ٴμ���ϰ���Ϊ�˷�ֹ���ϰ��ڿ���
            //if ( checkBlock( currCheckCell, currBlockCheckCell, blockCheckIndex, blockCheckMaxIndex ) )
            //{
            //    isCheckBlock = false;
            //}else
            //{
            //    isCheckBlock = true;
            //}


			//------------------------------------------------------------------------------------
			//@ ��⵱ǰ����Χ8������
			//------------------------------------------------------------------------------------
			
			for(eightCellLoopIndex = 0; eightCellLoopIndex < eightCellLoopCount; ++eightCellLoopIndex)
			{	
				eightCellOffset = mFindPathEightCellOffset[ eightCellLoopIndex ];

				// ����ƫ������ȡ����Χ�������
				currCheckAroundCellPoint.x = currCheckCell->x + eightCellOffset.x;
				currCheckAroundCellPoint.y = currCheckCell->z + eightCellOffset.y;

				activeFindPathCell( currCheckAroundCellPoint, currCheckAroundCell );

				if ( currCheckAroundCell )
				{
					//------------------------------------------------------------------------------------
					//@ ����ϰ�
					// �Լ������Ϊ���� mBlockCheckCellRadiusΪ�뾶��Χ�����Χ�������Ƿ�Ϊ�ϰ�
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
                            // ����Ǿ�̬�ϰ����Թ�
                            if ( currBlockCheckCell->blockState == FindPathCell::BS_IN_STATIC_BLOCK )
                                continue;

                            // ����Ƕ�̬�ϰ����Թ�,����¼
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
					//@ ���ر��б�
					//------------------------------------------------------------------------------------
					// ����ǹر��б����Թ�
					if ( currCheckAroundCell->findPathState == FindPathCell::FS_IN_CLOSE_LIST )
						continue;

					//------------------------------------------------------------------------------------
					//@ ��⿪���б�
					//------------------------------------------------------------------------------------
					// ������ڿ�ʼ�б��У�������ӽ�ȥ���ѵ�ǰ����Ϊ��һ��ĸ��ڵ㡣��¼��һ���F,G,��Hֵ��
					if ( currCheckAroundCell->findPathState != FindPathCell::FS_IN_OPEN_LIST )
					{
						// ���ø��ڵ�
						currCheckAroundCell->parent = currCheckCell;

						// ��¼F,G,��Hֵ��
						currCheckAroundCell->gCost = getMoveGCost( currCheckAroundCell, currCheckCell );
						currCheckAroundCell->binaryHeapCost = currCheckAroundCell->gCost + getMoveHCost( currCheckAroundCell, destCell );

						// ���뵽�����б���
						mOpenList->insert( currCheckAroundCell );
						currCheckAroundCell->findPathState = FindPathCell::FS_IN_OPEN_LIST;
					}else
					//������Ѿ��ڿ����б��У���GֵΪ�ο�����µ�·���Ƿ���á����͵�Gֵ��ζ�Ÿ��õ�·����
					//������������Ͱ���һ��ĸ��ڵ�ĳɵ�ǰ�񣬲������¼�����һ���G��Fֵ. �����¶Կ����б�����
					{
						gCost = getMoveGCost( currCheckAroundCell, currCheckCell );
						if ( gCost < currCheckAroundCell->gCost )
						{
							// �������ø��ڵ�
							currCheckAroundCell->parent = currCheckCell;

							// ��¼F,G,��Hֵ��
							hCost = currCheckAroundCell->binaryHeapCost - currCheckAroundCell->gCost;
							currCheckAroundCell->gCost = gCost;
							currCheckAroundCell->binaryHeapCost = currCheckAroundCell->gCost + hCost;

							// ��������
							mOpenList->filterUp( currCheckAroundCell->binaryHeapIndex );
						}
					}

				}
			}

			//------------------------------------------------------------------------------------
			//@ û���ҵ�Ŀ��������ѭ���ж�
			//------------------------------------------------------------------------------------

			// ��������б�Ϊ�գ����˳�
			if ( mOpenList->isEmpty() )
			{
				break;	//�˳�ѭ��
			}

			// ��������������޶�ֵ���˳�
			if ( loopCount++ > checkMaxPath )
			{
				result = PFR_OVER_LENGTH;
				break; //�˳�ѭ��
			}

			// ���������̬�ϰ����������޶�ֵ���˳�
            if ( dynamicBlockDirty )
            {
                if ( ++checkDynamicBlockCount > checkMaxDynamicBlock )
                {
				    result = PFR_OVER_DYNAMIC_BLOCK;
                    break; //�˳�ѭ��
                }
                dynamicBlockDirty = false;
            }
		}

		//------------------------------------------------------------------------------------
		//@ �ӹر��б��� �����������·��
		//------------------------------------------------------------------------------------
	
        // ����������Ŀ������ʾ����ҪѰ·
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
				// ����ڵ㵽����б���
				mFindPathCellFullResult.push_back( VecU2(currCheckCell->x, currCheckCell->z) );
			
				// ����ǿ�ʼ�ڵ����˳�
				if ( currCheckCell == startCell )
				{
					result = PFR_SUCCESS;
					break;
				}

				// ���û�и��ڵ����˳�
				if ( currCheckCell->parent == NULL )
				{
					DYNAMIC_ASSERT( false );
					break;
				}

				// ����ѭ���������˳�
				if ( loopCount++ > loopLimit )
				{
					DYNAMIC_ASSERT( false );
					break;
				}

				// ��ø��ڵ�
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

                // ��ǰ����һ������
                VecU2 currCell = mFindPathCellFullResult[cellListMaxIndex-1];
                VecU2 lastCell = mFindPathCellFullResult[cellListMaxIndex];

                VecU2 newAddCell = lastCell;
                VecU2 finalCell = mFindPathCellFullResult[0];

                // ��ǰ����һ��������
                PathFinder2::Movedir currMoveDir = md_null;
                PathFinder2::Movedir lastMoveDir = getMoveDir( lastCell, currCell );

                // ������ʼ��������
                mFindPathCellCombineResult.push_back( lastCell );
                newAddCell = lastCell;

				UInt listNum = 0;

                // ����Ѱ·�����б��ϲ�ͬ��������
                // �ӵ����ڶ�����ʼ����
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

                // ������һ�����������������꣬���֮
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
        // ������ݳ�ʼ��
        Flt dis             = (endPos - startPos).length();
        Flt currDis         = 0;
        Vec3 lastPos        = startPos;
        Vec3 currPos        = startPos;
        Vec3 dir            = (endPos - startPos);
        dir.normalise();
        // ʹ�����񳤶ȵ������
        dir = dir * mMapBlock->getGridSize();

        // ��ײ�������
        FindPathCell* currBlockCheckCell = NULL;
        FindPathCell* currBlockCheckCellResult = NULL;
        // ��ײ���ѭ������
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
        // ��Ҫ��dir�ֽ��2��������
       

        // ���������������
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
                //TODO:JJJ  ��Ҫ��dir�ֽ��2��������
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
