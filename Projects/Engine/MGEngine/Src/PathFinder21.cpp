/******************************************************************************/
#include "stdafx.h"
#include "Pathfinder21.h"
#include "MGSceneNode.h"
#include "MGEngineUtility.h"


#include <memory.h>
#include "Scene.h"
#include "BlockObject.h"

/******************************************************************************/

namespace MG
{
#define FINDPATHCELL_BINARYHEAP_ADD_UP_COUNT 10000
#define FINDPATHCELL_FASTSTRUCTPOOL_ADD_UP_COUNT 2000


	//-----------------------------------------------------------------------
	PathFinder21::PathFinder21()
	{
		mPathFinderType = PT_ALWAYS_NEAREST;

		mBlockObjRadius = 0;

		mMapGridWidth = 0;
		mMapGridHeight = 0;

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
	PathFinder21::~PathFinder21()
	{
		unLoad();
	}

	//-----------------------------------------------------------------------
	void PathFinder21::load( Scene* scene, UInt pathFinderGridWidth, UInt pathFinderGridHeight )
	{
		unLoad();

		mScene = scene;

		mMapGridMaxWidth = pathFinderGridWidth;
		mMapGridMaxHeight = pathFinderGridHeight;

		mMapBlock.createGrids(pathFinderGridWidth, pathFinderGridHeight, 0.5, Vec2(0,0));
		mCellGrids.createGrids(pathFinderGridWidth, pathFinderGridHeight, 0.5, Vec2(0,0));

		mOpenList = MG_NEW BinaryHeap<FindPathCell21*>(FINDPATHCELL_BINARYHEAP_ADD_UP_COUNT);
		mCellPool = MG_NEW FastStructPool<FindPathCell21>(FINDPATHCELL_FASTSTRUCTPOOL_ADD_UP_COUNT);
	}

	//-----------------------------------------------------------------------
	void PathFinder21::unLoad()
	{
		mCellGrids.destroyGrids();
		mMapBlock.destroyGrids();

		MG_SAFE_DELETE( mOpenList );
		MG_SAFE_DELETE( mCellPool );
	}

	//-----------------------------------------------------------------------
	Bool PathFinder21::isLoaded()
	{
		return mMapBlock.getIsGridCreated();
	}

	//-----------------------------------------------------------------------
	void PathFinder21::setBlockGrid( RectF setBlockRect, FindPathCell21::BlockState blockState )
	{
		VecU2 leftTopPoint;
		mMapBlock.convertWorldPositionToGridPoint(Vec2(setBlockRect.left, setBlockRect.top), leftTopPoint);

		VecU2 rightBottomPoint;
		mMapBlock.convertWorldPositionToGridPoint(Vec2(setBlockRect.right, setBlockRect.bottom), rightBottomPoint);

		UInt regionGridIndex = 0;
		Byte* blockData = NULL;

		for(UInt x = leftTopPoint.x; x <= rightBottomPoint.x; ++x)
		{
			for(UInt y = rightBottomPoint.y; y <= leftTopPoint.y; ++y)
			{
				blockData = mMapBlock.getGridDataByPoint(x, y);
				if(!blockData)
				{
					continue;
				}

				(*blockData) |= blockState;
			}
		}
	}

	//-----------------------------------------------------------------------
	void PathFinder21::setBlockGrid( RectF setBlockRect, BlockObject* ignoreBlockObject )
	{
		RectF ignoreBlockRect = ignoreBlockObject->getBlockPosRect();

		Flt width = setBlockRect.width();
		Flt height = setBlockRect.height();

		Flt length = 0;
		if(width > height)
		{
			length = width;
		}
		else
		{	
			length = height;
		}

		Flt gridSize = 0.5;

		if( length / gridSize > (mMapGridMaxWidth-1) )
		{
			gridSize = length / (mMapGridMaxWidth-1);
		}

		mMapOneGridSize = gridSize;

		mMapGridWidth = width / gridSize;
		mMapGridHeight = height / gridSize;

		mMapBlock.clearWorldGrid();

		mMapBlock.changeGridSize(gridSize);
		mMapBlock.changeLeftBottomPos(Vec2(setBlockRect.left, setBlockRect.bottom));
		mCellGrids.changeGridSize(gridSize);
		mCellGrids.changeLeftBottomPos(Vec2(setBlockRect.left, setBlockRect.bottom));

		std::map<BlockObject*, BlockObject*> blockObjectList;
		mScene->getDynamicBlockObjectSceneManager()->getBlockObjectList(setBlockRect, blockObjectList);

		Flt selfHalfWidth = ignoreBlockRect.width() * 0.5;
		Flt selfHalfHeight = ignoreBlockRect.height() * 0.5;

		
		RectF blockRect;

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//setSelfBlock
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//blockRect = ignoreBlockObject->getBlockPosRect();
		//setBlockGrid(blockRect, FindPathCell21::BS_IN_SELF_BLOCK);

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//setDynamicBlock
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BlockObject* blockObject = NULL;
		for(std::map<BlockObject*, BlockObject*>::iterator it = blockObjectList.begin(); it != blockObjectList.end(); ++it)
		{
			blockObject = it->second;
			if(!blockObject)
			{
				continue;
			}

			if(blockObject == ignoreBlockObject)
			{
				continue;
			}

			blockRect = blockObject->getBlockPosRect();
			if(blockRect.intersect(setBlockRect).isNull())
			{
				continue;
			}

			if(blockRect == ignoreBlockRect)
			{
				continue;
			}

			blockRect.left -= selfHalfWidth;
			blockRect.right += selfHalfWidth;
			blockRect.top -= selfHalfHeight;
			blockRect.bottom += selfHalfHeight;

			setBlockGrid(blockRect, FindPathCell21::BS_IN_DYNAMIC_BLOCK);
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//setStaticicBlock
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		GridPool<Byte>* staticBlockMap = mScene->getBlockManager()->getStaticBlockList();
		VecU2 leftTopPoint;
		staticBlockMap->convertWorldPositionToGridPoint(Vec2(blockRect.left, blockRect.top), leftTopPoint);

		VecU2 rightBottomPoint;
		staticBlockMap->convertWorldPositionToGridPoint(Vec2(blockRect.right, blockRect.bottom), rightBottomPoint);
		Byte* blockData = NULL;
		RectF staticBlockRect;
		Vec2 staticBlockPos;
		Flt staticGridHalfSize = staticBlockMap->getGridSize() * 0.5;

		for(UInt x = leftTopPoint.x; x < rightBottomPoint.x; ++x)
		{
			for(UInt y = rightBottomPoint.y; y < leftTopPoint.y; ++y)
			{
				blockData = staticBlockMap->getGridDataByPoint(x, y);
				if(!blockData)
				{
					continue;
				}

				if ( !(*blockData & BlockManager::BLF_TERRAIN_BLOCK) )
				{
					continue;
				}

				staticBlockMap->convertGridPointToWorldPosition(VecU2(x,y), staticBlockPos);

				staticBlockRect.left = staticBlockPos.x - staticGridHalfSize;
				staticBlockRect.right = staticBlockPos.x + staticGridHalfSize;
				staticBlockRect.top = staticBlockPos.y - staticGridHalfSize;
				staticBlockRect.bottom = staticBlockPos.y + staticGridHalfSize;

				setBlockGrid(staticBlockRect, FindPathCell21::BS_IN_STATIC_BLOCK);
			}
		}
	}

	//-----------------------------------------------------------------------
	void PathFinder21::clearBlockGrid()
	{
		mMapBlock.clearWorldGrid(0);
	}


	//-----------------------------------------------------------------------
	void PathFinder21::setType ( PathFinder21::PathFinderType type )
	{
		mPathFinderType = type;
	}

	//-----------------------------------------------------------------------
	void PathFinder21::convertWorldPositionToGridPoint( Vec3 startPos, VecU2& gridPoint )
	{
		if( isLoaded() == false)
		{
			return;
		}

		mMapBlock.convertWorldPositionToGridPoint(Vec2(startPos.x, startPos.z), gridPoint);
	}

	//-----------------------------------------------------------------------
	PathFindingResult PathFinder21::findPath( BlockObject* pathFinder,
		Vec3 startPos,
		Vec3 targetPos, 
		RectF findPathRect,
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

		RectF pathFinderBlockRect = pathFinder->getBlockPosRect();

		//clearBlockGrid();
		setBlockGrid(findPathRect, pathFinder);

		VecU2 startCellPoint;
		mMapBlock.convertWorldPositionToGridPoint(Vec2(startPos.x, startPos.z), startCellPoint);
		VecU2 targetCellPoint;
		mMapBlock.convertWorldPositionToGridPoint(Vec2(targetPos.x, targetPos.z), targetCellPoint);

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

		// �ϰ����ƫ�Ʒ�Χ


		// �ϰ������С

		mBlockObjRadius = pathFinderBlockRect.width();

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
		FindPathCell21* nearestCellInCloseList = NULL;

		// ��ǰ�����������������
		VecU2 currCheckCellPoint;
		FindPathCell21* currCheckCell = NULL;

		// ��ǰ������Χ������
		VecU2 currCheckAroundCellPoint;
		FindPathCell21* currCheckAroundCell = NULL;


		// ��ʼ���Ŀ�������
		FindPathCell21* startCell = NULL;
		FindPathCell21* destCell = NULL;

		//------------------------------------------------------------------------------------
		//@ ����Ŀ������ʼ��
		//------------------------------------------------------------------------------------

		// Ŀ���
		activeFindPathCell( targetCellPoint, destCell );	
		destCell->findPathState = FindPathCell21::FS_IDLE ;
		destCell->blockState = FindPathCell21::BS_OUT_BLOCK ;

		// ��ʼ��
		activeFindPathCell( startCellPoint, startCell );	
		startCell->findPathState = FindPathCell21::FS_IDLE;

		// ������ʼ�㵽�����б�
		startCell->gCost = 0;
		startCell->binaryHeapCost = getMoveHCost( startCell, destCell ) + 0;
		mOpenList->insert( startCell );
		startCell->findPathState = FindPathCell21::FS_IN_OPEN_LIST;

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

		FindPathCell21* currBlockCheckCell = NULL;
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

			currCheckCell->findPathState = FindPathCell21::FS_IN_CLOSE_LIST;

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
					if ( (currCheckCell->binaryHeapCost - currCheckCell->gCost) < (nearestCellInCloseList->binaryHeapCost - nearestCellInCloseList->gCost))
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
						isBlock = checkBlock( currCheckAroundCell );

						if(!isBlock)
						{
							if(eightCellOffset.x == 0 || eightCellOffset.y == 0)
							{
								isBlock = false;
							}
							else
							{
								activeFindPathCell( VecU2(currCheckAroundCellPoint.x - eightCellOffset.x, currCheckAroundCellPoint.y) , currBlockCheckCell );
								if(currBlockCheckCell)
								{
									if(eightCellOffset.x != 0)
									{
										isBlock = checkBlock(currBlockCheckCell);
									}
									else
									{
										isBlock = false;
									}
								}
								else
								{
									isBlock = true;
								}

								if(!isBlock)
								{
									activeFindPathCell( VecU2(currCheckAroundCellPoint.x, currCheckAroundCellPoint.y - eightCellOffset.y) , currBlockCheckCell );
									if(currBlockCheckCell)
									{
										if(eightCellOffset.y != 0)
										{
											isBlock = checkBlock(currBlockCheckCell);
										}
										else
										{
											isBlock = false;
										}
									}
									else
									{
										isBlock = true;
									}
								}
							}
						}
					}
					else
					{
						isBlock = false;
					}

					if ( isBlock )
					{
						if ( currCheckAroundCell )
						{
							// ����Ǿ�̬�ϰ����Թ�
							if ( currCheckAroundCell->blockState == FindPathCell21::BS_IN_STATIC_BLOCK )
								continue;

							// ����Ƕ�̬�ϰ����Թ�,����¼
							if ( currCheckAroundCell->blockState == FindPathCell21::BS_IN_DYNAMIC_BLOCK )
							{
								dynamicBlockDirty = true;
								continue;
							}

							continue;
						}else
						{
							continue;
						}
					}

					//------------------------------------------------------------------------------------
					//@ ���ر��б�
					//------------------------------------------------------------------------------------
					// ����ǹر��б����Թ�
					if ( currCheckAroundCell->findPathState == FindPathCell21::FS_IN_CLOSE_LIST )
						continue;

					//------------------------------------------------------------------------------------
					//@ ��⿪���б�
					//------------------------------------------------------------------------------------
					// ������ڿ�ʼ�б��У�������ӽ�ȥ���ѵ�ǰ����Ϊ��һ��ĸ��ڵ㡣��¼��һ���F,G,��Hֵ��
					if ( currCheckAroundCell->findPathState != FindPathCell21::FS_IN_OPEN_LIST )
					{
						// ���ø��ڵ�
						currCheckAroundCell->parent = currCheckCell;

						// ��¼F,G,��Hֵ��
						currCheckAroundCell->gCost = getMoveGCost( currCheckAroundCell, currCheckCell );
						currCheckAroundCell->binaryHeapCost = currCheckAroundCell->gCost + getMoveHCost( currCheckAroundCell, destCell );

						// ���뵽�����б���
						mOpenList->insert( currCheckAroundCell );
						currCheckAroundCell->findPathState = FindPathCell21::FS_IN_OPEN_LIST;
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
	std::vector<VecU2>& PathFinder21::getFullFindCellPathResult()
	{
		return mFindPathCellFullResult;
	}

	//-----------------------------------------------------------------------
	std::vector<Vec3>& PathFinder21::getFullFindPathNodeResult()
	{
		if ( mFindPathNodeFullResult.size() != mFindPathCellFullResult.size() )
		{

		}

		return mFindPathNodeFullResult;
	}

	//-----------------------------------------------------------------------
	std::vector<VecU2>& PathFinder21::getCombineFindCellPathResult()
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
					PathFinder21::Movedir currMoveDir = md_null;
					PathFinder21::Movedir lastMoveDir = getMoveDir( lastCell, currCell );

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
	std::vector<Vec3>& PathFinder21::getCombineFindPathNodeResult() 
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
	std::vector<Vec3>& PathFinder21::getSmoothFindPathNodeResult()
	{
		getCombineFindPathNodeResult();

		if ( mFindPathNodeSmoothResult.size() == 0 )
		{
			if(mFindPathNodeCombineResult.size() == 0)
			{
				return mFindPathNodeSmoothResult;
			}
			mFindPathNodeSmoothResult = mFindPathNodeCombineResult;

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
	Bool PathFinder21::isBlockBetweenTwoPos( Vec3 startPos, Vec3 endPos, Flt ignoreRange )
	{
		RectF checkRect;

		Vec3 dir = endPos - startPos;
		dir.y = 0;
		Flt disLen = dir.length();
		dir.normalise();

		endPos += dir * (mBlockObjRadius * 1.41421);
		//endPos += (dir * mBlockObjRadius /** 2*/ + dir * disLen);

		if(startPos.z > endPos.z)
		{
			checkRect.top = endPos.z - mBlockObjRadius;
			checkRect.bottom = startPos.z + mBlockObjRadius;
		}
		else
		{
			checkRect.top = startPos.z - mBlockObjRadius;
			checkRect.bottom = endPos.z + mBlockObjRadius;
		}

		if(startPos.x > endPos.x)
		{
			checkRect.right = startPos.x + mBlockObjRadius;
			checkRect.left = endPos.x - mBlockObjRadius;
		}
		else
		{
			checkRect.right = endPos.x + mBlockObjRadius;
			checkRect.left = startPos.x - mBlockObjRadius;
		}

		Vec3 startPosList[3];
		/*Vec3*/ dir = endPos - startPos;
		dir.y = 0;
		dir.normalise();

		Vec3 tempDir = MGMath::rotateVector(dir, 90 * (MG_PI / 180));
		startPosList[0] = startPos + tempDir * mBlockObjRadius;
		startPosList[1] = startPos;
		tempDir = MGMath::rotateVector(dir, 270 * (MG_PI / 180));
		startPosList[0] = startPos + tempDir * mBlockObjRadius;

		Vec3 endPosList[3];
		dir = startPos - endPos;
		dir.y = 0;
		dir.normalise();

		tempDir = MGMath::rotateVector(dir, 270 * (MG_PI / 180));
		endPosList[0] = endPos + tempDir * mBlockObjRadius;
		endPosList[1] = endPos;
		tempDir = MGMath::rotateVector(dir, 90 * (MG_PI / 180));
		endPosList[0] = endPos + tempDir * mBlockObjRadius;


		std::map<BlockObject*, BlockObject*> blockObjectList;
		mScene->getDynamicBlockObjectSceneManager()->getBlockObjectList(checkRect, blockObjectList);

		BlockObject* blockObject = NULL;
		RectF blockRect;
		FloatRect tempRect;
		for(std::map<BlockObject*, BlockObject*>::iterator it = blockObjectList.begin(); it != blockObjectList.end(); ++it)
		{
			blockObject = it->second;
			if(!blockObject)
			{
				continue;
			}
	
			blockRect = blockObject->getBlockPosRect();

			if(blockRect.intersect(checkRect).isNull())
			{
				continue;
			}

			tempRect = FloatRect(blockRect.left, blockRect.top, blockRect.right, blockRect.bottom);

			for(UInt i = 0; i < 3; ++i)
			{
				//if(MGEngineUtility::clampLineInRect(Vector2(startPos.x,startPos.z)/*Vector2(startPosList[i].x, startPosList[i].z)*/, Vector2(endPos.x,endPos.z)/*Vector2(endPosList[i].x, endPosList[i].z)*/, tempRect))
				if(MGEngineUtility::clampLineInRect(Vector2(startPosList[i].x, startPosList[i].z), Vector2(endPosList[i].x, endPosList[i].z), tempRect))
				{
					return true;
				}
			}
		}

		return false;

		

		//// ������ݳ�ʼ��
		//Flt dis             = (endPos - startPos).length();
		//Flt currDis         = 0;
		//Vec3 lastPos        = startPos;
		//Vec3 currPos        = startPos;
		//Vec3 dir            = (endPos - startPos);
		//dir.normalise();
		//// ʹ�����񳤶ȵ������
		//dir = dir * mMapBlock.getGridSize();

		//// ��ײ�������
		//FindPathCell21* currBlockCheckCell = NULL;
		//FindPathCell21* currBlockCheckCellResult = NULL;
		//// ��ײ���ѭ������
		//VecU2 blockCheckIndex;
		//VecU2 blockCheckMaxIndex;
		//VecU2 gridPoint;
		//VecI82 gridDir;
		//Bool isBlock = false;

		//VecU2 startGridPoint;
		//VecU2 endGridPoint;

		//VecU2 lastGridPoint;

		//Int offSetX = 0;
		//Int offSetY = 0;

		////TODO:JJJ
		//// ��Ҫ��dir�ֽ��2��������


		//// ���������������
		//while(1)
		//{
		//	lastGridPoint = gridPoint;
		//	lastPos = currPos;
		//	currPos += dir;
		//	currDis = (currPos - startPos).length();
		//	if(currDis >= dis)
		//	{
		//		return false;
		//	}

		//	convertWorldPositionToGridPoint( currPos, gridPoint );
		//	if(gridPoint == lastGridPoint && !(gridPoint == VecU2(0,0)))
		//	{
		//		continue;
		//	}

		//	mMapBlock.convertWorldPositionToGridPoint(Vec2(lastPos.x, lastPos.z), startGridPoint);
		//	mMapBlock.convertWorldPositionToGridPoint(Vec2(currPos.x,currPos.z), endGridPoint);

		//	offSetX = endGridPoint.x - startGridPoint.x;
		//	offSetY = endGridPoint.y - startGridPoint.y;

		//	if(offSetX > 0)
		//	{
		//		gridDir.x = 1;
		//	}
		//	else if(offSetX < 0)
		//	{
		//		gridDir.x = -1;
		//	}
		//	else
		//	{
		//		gridDir.x = 0;
		//	}

		//	if(offSetY > 0)
		//	{
		//		gridDir.y = 1;
		//	}
		//	else if(offSetY < 0)
		//	{
		//		gridDir.y = -1;
		//	}
		//	else
		//	{
		//		gridDir.y = 0;
		//	}

		//	activeFindPathCell( gridPoint, currBlockCheckCell );

		//	if ( currBlockCheckCell )
		//	{
		//		//TODO:JJJ  ��Ҫ��dir�ֽ��2��������
		//		isBlock = checkBlock( currBlockCheckCell, currBlockCheckCellResult, blockCheckIndex, blockCheckMaxIndex, gridDir );
		//		//isBlock = checkBlock( currBlockCheckCell, currBlockCheckCellResult, blockCheckIndex, blockCheckMaxIndex, gridDir1 );
		//		//isBlock = checkBlock( currBlockCheckCell, currBlockCheckCellResult, blockCheckIndex, blockCheckMaxIndex, gridDir2 );

		//		if( isBlock )
		//		{
		//			return true;
		//		}
		//	}
		//}

		return false;
	}
}
