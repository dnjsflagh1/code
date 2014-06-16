/******************************************************************************/
#include "stdafx.h"
#include "Pathfinder.h"
#include <memory.h>
#include "MGSceneNode.h"
#include "MGEngineUtility.h"
//#include "BlockManager.h"
/******************************************************************************/

namespace MG
{
	//-----------------------------------------------------------------------
	PathFinder::PathFinder(): mPathFindNum(1), mOnOpenList(1), mOnCloseList(2)
	{

	}

	//-----------------------------------------------------------------------
	PathFinder::~PathFinder()
	{
		unLoadPathFinderMap();
	}

	//-----------------------------------------------------------------------
	void PathFinder::loadPathFinderMap( GridPool<Byte>* mapBlock )
	{
		mMapBlock = mapBlock;

		unLoadPathFinderMap();

		UInt mapWidth = mapBlock->getWorldGridWidth();
		UInt mapHeight = mapBlock->getWorldGridHeight();
		Flt tileSize = mapBlock->getGridSize();
		Vec2 leftBottomPos = mapBlock->getLeftBottomPos();

		mOpenAndCloseList.createGrids(mapWidth, mapHeight, tileSize, leftBottomPos);

		mOpenPosList.createGrids(mapWidth, mapHeight, tileSize, leftBottomPos);

		mCellCostList.createGrids(mapWidth, mapHeight, tileSize, leftBottomPos);

		mOpenList.createGrids(mapWidth, mapHeight, tileSize, leftBottomPos);
	}

	//-----------------------------------------------------------------------
	bool PathFinder::findPath( Int startX, Int startZ, Int targetX, Int targetZ, std::vector<UInt>& ignorePosList, std::vector<PathCell>& pathList, Int findPathObjectCellDiameter, Int findCellRadius )
	{
		pathList.clear();

		if(mPathFindNum > 200)
		{
			mPathFindNum = 1;
			mOpenAndCloseList.clearWorldGrid();
		}

		mPathFindNum += 2;
		mOnOpenList = mPathFindNum - 1;
		mOnCloseList = mPathFindNum;

		UInt* open1 = mOpenList.getGridDataByIndex(1);
		(*open1) = 1;

		Byte/*UInt*/* openAndClose = NULL;
		Byte/*UInt*/* openAndCloseParent = NULL;
		Byte/*UInt*/* openAndCloseTarget = NULL;

		UInt* open2 = NULL;
		UInt* openU = NULL;
		UInt* openV = NULL;
		UInt* open2U = NULL;
		UInt* open2U1 = NULL;
		UInt* openTemp = NULL;
		UInt* openM = NULL;
		UInt* openM2 = NULL;

		Int parentX = 0;
		Int parentZ = 0;
		Int parentOffsetX = 0;
		Int parentOffsetZ = 0;
		Int parentPos = 0;
		Int offSetX = 0;
		Int offSetZ = 0;
		Int currPos = 0;
		Int currX = 0;
		Int currZ = 0;
		Int gCost = 0;
		Int tempGCost = 0;
		Int openListItemNum = 1;
		Int u = 0;
		Int v = 0;
		Int m = 0;
		UInt temp = 0;
		Int tempOpenListIndex = 0;

		Int findRadiusOffSetX = 0;
		Int findRadiusOffSetZ = 0;

		UInt mapWidth = mMapBlock->getWorldGridWidth();
		UInt mapHeight = mMapBlock->getWorldGridHeight();
		//Int findScopeWidth = mMapWidth;

		//if(findCellRadius > 0)
		//{
		//	findRadiusOffSetX = startX - findCellRadius - 1;
		//	findRadiusOffSetZ = startZ - findCellRadius - 1;
		//	findScopeWidth = findCellRadius * 2;
		//}

        if(targetX == startX && targetZ == startZ)
        {
            return false;
        }
		else if(findCellRadius > 0 && ( targetX < startX - findCellRadius || targetZ < startZ - findCellRadius || targetX > startX + findCellRadius || targetZ > startZ + findCellRadius ) )
		{
			return false;
		}
		else if(isInDiameter(targetX, targetZ, ignorePosList, findPathObjectCellDiameter))
		{
			return false;
		}
		

		OpenPos* openPos = mOpenPosList.getGridDataByIndex(1);
		openPos->x = startX;
		openPos->z = startZ;

		OpenPos* openPosTemp = NULL;
		OpenPos* openPosV = NULL;
		OpenPos* openPosM2 = NULL;

		CellCost* cellCost = mCellCostList.getGridDataByPoint(startX ,startZ);
		memset(cellCost, 0, sizeof(CellCost));

		CellCost* cellCostU = NULL;
		CellCost* cellCostV = NULL;
		CellCost* cellCost2U = NULL;
		CellCost* cellCost2U1 = NULL;
		CellCost* cellCostTemp = NULL;
		CellCost* cellCostParent = NULL;
		CellCost* cellCostM = NULL;
		CellCost* cellCostM2 = NULL;

		Byte* block1 = NULL;
		Byte* block2 = NULL;
		Byte* block3 = NULL;

		Bool isblock1 = false;
		Bool isblock2 = false;
		Bool isblock3 = false;

		//memset(&mCellCostList[ startX + (startZ- 1) * mMapWidth ], 0, sizeof(CellCost));

		do 
		{
			if(openListItemNum == 0)
			{
				return false;
			}
			
			open1 = mOpenList.getGridDataByIndex(1);
			openPos = mOpenPosList.getGridDataByIndex((*open1));
			openListItemNum -= 1;
			parentX = openPos->x;
			parentZ = openPos->z;
			parentPos = mMapBlock->convertGridPointToGridIndex(parentX, parentZ);

			openAndCloseParent = mOpenAndCloseList.getGridDataByIndex(parentPos);
			(*openAndCloseParent) = mOnCloseList;

			open1 = mOpenList.getGridDataByIndex(1);
			open2 = mOpenList.getGridDataByIndex(openListItemNum + 1);
			(*open1) = (*open2);

			v = 1;
			m = 1;

			do
			{
				u = v;

				openU = mOpenList.getGridDataByIndex(u);
				open2U = mOpenList.getGridDataByIndex(2*u);
				cellCostU = mCellCostList.getGridDataByIndex((*openU));
				cellCost2U = mCellCostList.getGridDataByIndex((*open2U));

				if(2*u+1 <= openListItemNum)
				{
					if((cellCostU->gCost + cellCostU->hCost) >= (cellCost2U->gCost + cellCost2U->hCost))
					{		
						v = 2*u;
					}

					openV = mOpenList.getGridDataByIndex(v);
					open2U1 = mOpenList.getGridDataByIndex(2*u+1);
					cellCostV = mCellCostList.getGridDataByIndex((*openV));
					cellCost2U1 = mCellCostList.getGridDataByIndex((*open2U1));

					if((cellCostV->gCost + cellCostV->hCost)>= (cellCost2U1->gCost + cellCost2U1->hCost))
					{
						v = 2*u+1;
					}
				}
				else if(2*u <= openListItemNum)
				{
					if((cellCostU->gCost + cellCostU->hCost) >= (cellCost2U->gCost + cellCost2U->hCost))
					{		
						v = 2*u;
					}
				}

				if(u != v)
				{
					temp = (*(mOpenList.getGridDataByIndex(u)));
					openPosTemp = mOpenPosList.getGridDataByIndex(temp);
					tempOpenListIndex = openPosTemp->inOpenListIndex;

					openV = mOpenList.getGridDataByIndex(v);
					openPosV = mOpenPosList.getGridDataByIndex((*openV));
					openPosTemp->inOpenListIndex = openPosV->inOpenListIndex;

					openU = mOpenList.getGridDataByIndex(u);
					openV = mOpenList.getGridDataByIndex(v);
					(*openU) = (*openV);

					openPosV->inOpenListIndex = tempOpenListIndex;
					(*openV) = temp;
				}
				else
				{
					break;
				}

			}while (1);

			for(int i = 0; i < 9; ++i)
			{	
				offSetX = i % 3 - 1;
				offSetZ = i / 3 - 1;

				currX = parentX + offSetX;
				currZ = parentZ + offSetZ;

				if((offSetX == 0 && offSetZ == 0) 
					|| (findCellRadius > 0 
					&& (currX < startX - findCellRadius 
					|| currZ < startZ - findCellRadius 
					|| currX > startX + findCellRadius 
					|| currZ > startZ + findCellRadius )) 
					|| currX <= 0 || currZ <= 0
					||  currX > mapWidth 
					|| currZ > mapHeight)
				{
					continue;
				}

				//currPos = currX + (currZ - 1) * findScopeWidth;

				//if(currX < startX - findPathObjectCellRadius || currX > startX + findPathObjectCellRadius || currZ < startZ - findPathObjectCellRadius || currZ > startZ + findPathObjectCellRadius)
				//{
				//	continue;
				//}

				currPos = mMapBlock->convertGridPointToGridIndex(currX, currZ);
				isblock1 = isBlock(currX, currZ, ignorePosList, findPathObjectCellDiameter);


                if(offSetX != 0 && offSetZ != 0)
                {
                    if(offSetX < 0)
                    {
                        isblock2 = isBlock(currX - offSetX, currZ, ignorePosList, findPathObjectCellDiameter, BlockManager::VERTEX_RIGHTDOWN);
                    }
                    else if(offSetX > 0)
                    {
                        isblock2 = isBlock(currX - offSetX, currZ, ignorePosList, findPathObjectCellDiameter, BlockManager::VERTEX_LEFTDOWN);
                    }
                    else
                    {
                        isblock2 = false;
                    }

                    if(offSetZ < 0)
                    {
                        isblock3 = isBlock(currX, currZ - offSetZ, ignorePosList, findPathObjectCellDiameter, BlockManager::VERTEX_LEFTUP);
                    }
                    else if(offSetZ > 0)
                    {
                        isblock3 = isBlock(currX, currZ - offSetZ, ignorePosList, findPathObjectCellDiameter, BlockManager::VERTEX_RIGHTUP);
                    }
                    else
                    {
                        isblock3 = false;
                    }
                }
                else 
                {
                    isblock2 = false;
                    isblock3 = false;
                }


                if( isblock1 == true || isblock2 == true || isblock3 == true)
				{
					continue;
				}

				openAndClose = mOpenAndCloseList.getGridDataByIndex(currPos);
				if((*openAndClose) == mOnCloseList/*|| (!isIgnoreDynamicBlock && mDynamicBlockMap[currPos] == mUnwalkable)*/)
				{
					continue;
				}

				if(abs(currX - parentX) == 1 && abs(currZ - parentZ) == 1)
				{
					gCost = 14;
				}
				else
				{
					gCost = 10;
				}

				if((*openAndClose) != mOnOpenList)
				{
					openListItemNum += 1;
					//openListItemID +=1;
					m = openListItemNum;

					openM = mOpenList.getGridDataByIndex(m);
					(*openM) = currPos;

					cellCost = mCellCostList.getGridDataByIndex(currPos);
					cellCostParent = mCellCostList.getGridDataByIndex(parentPos);

					cellCost->gCost = cellCostParent->gCost + gCost;
					cellCost->hCost = 10*(abs(currX - targetX) + abs(currZ - targetZ));
					//cellCost->fCost = cellCost->gCost + cellCost->hCost; 

					openPos = mOpenPosList.getGridDataByIndex(currPos);

					(*openAndClose) = mOnOpenList;
					openPos->x = currX;
					openPos->z = currZ;
					openPos->parentOffsetX = offSetX;
					openPos->parentOffsetZ = offSetZ;
					openPos->inOpenListIndex = m;

				}
				else
				{
					cellCostParent = mCellCostList.getGridDataByIndex(parentPos);
					cellCost = mCellCostList.getGridDataByIndex(currPos);

					openPos = mOpenPosList.getGridDataByIndex(currPos);

					tempGCost = cellCostParent->gCost + gCost;
					m = 1;
					if(tempGCost < cellCost->gCost)
					{

						cellCost->gCost = tempGCost;
						//cellCost->fCost = tempGCost + cellCost->hCost;
						openPos->parentOffsetX = offSetX;
						openPos->parentOffsetZ = offSetZ;

						m = openPos->inOpenListIndex;
					}
				}

				while (m!=1)
				{
					openM = mOpenList.getGridDataByIndex(m);
					openM2 = mOpenList.getGridDataByIndex(m/2);
					cellCostM = mCellCostList.getGridDataByIndex((*openM));
					cellCostM2 = mCellCostList.getGridDataByIndex((*openM2));

					if((cellCostM->gCost + cellCostM->hCost) <= (cellCostM2->gCost + cellCostM2->hCost))
					{
						temp = (*openM);
						openPosTemp = mOpenPosList.getGridDataByIndex(temp);
						tempOpenListIndex = openPosTemp->inOpenListIndex;

						openPosM2 = mOpenPosList.getGridDataByIndex((*openM2));
						(*openM) = (*openM2);
						openPosTemp->inOpenListIndex = openPosM2->inOpenListIndex;

						openPosM2->inOpenListIndex = tempOpenListIndex;
						(*openM2) = temp;

						m = m / 2;
					}
					else
					{
						break;
					}
				}

			}

			openAndCloseTarget = mOpenAndCloseList.getGridDataByPoint(targetX, targetZ);
			if((*openAndCloseTarget) == mOnOpenList)
			{
				break;
			}

		} while (1);

		PathCell cell ;
		cell.x = targetX;
		cell.z = targetZ;

		OpenPos* openPosPath = NULL;

		pathList.push_back(cell);

		while (cell.z != startZ || cell.x != startX)
		{
			openPosPath = mOpenPosList.getGridDataByPoint(cell.x, cell.z);
			cell.x = openPosPath->x - openPosPath->parentOffsetX;
			cell.z = openPosPath->z - openPosPath->parentOffsetZ;

			//if(cell.y== startY && cell.x == startX)
			//{
			//	break;
			//}

			pathList.push_back(cell);
		}

		return true;
	}

	//-----------------------------------------------------------------------
	Bool PathFinder::findPath( PathCell startCell, PathCell targetCell, std::vector<UInt>& ignorePosList, std::vector<PathCell>& pathList, Int findPathObjectCellRadius, Int findCellRadius)
	{
		return findPath(startCell.x, startCell.z, targetCell.x, targetCell.z, ignorePosList, pathList, findPathObjectCellRadius, findCellRadius);
	}

	//-----------------------------------------------------------------------
	Bool PathFinder::findPath(Vector3 startPos, Vector3 targetPos, std::vector<UInt>& ignorePosList, std::vector<PathCell>& pathList, Int findPathObjectCellRadius, Int findCellRadius)
	{
		PathCell startCell = getPathPointByWorldPos(startPos);
		PathCell endCell = getPathPointByWorldPos(targetPos);

		return findPath(startCell, endCell, ignorePosList, pathList, findPathObjectCellRadius, findCellRadius);
	}


    //-----------------------------------------------------------------------
	PathFinder::movedir PathFinder::getMoveDir( PathCell& src , PathCell& des )
    {
        if(des.x > src.x)
        {
            if(des.z == src.z)
            {
                return md_right;
            }
            else 
            if(des.z > src.z)
            {
                return md_downright;
            }
            else 
            if(des.z < src.z)
            {
                return md_upright;
            }
        }
        else
        if(des.x < src.x)
        {
            if(des.z == src.z)
            {
                return md_left;
            }
            else 
            if(des.z > src.z)
            {
                return md_downleft;
            }
            else 
            if(des.z < src.z)
            {
                return md_upleft;
            }
        }
        else 
        if(des.x == src.x)
        {
            if(des.z == src.z)
            {
                DYNAMIC_ASSERT( false );
            }
            else 
            if(des.z > src.z)
            {
                return md_down;
            }
            else 
            if(des.z < src.z)
            {
                return md_up;
            }
        }
    }

	//-----------------------------------------------------------------------
	void PathFinder::getWorldPosListByPathList( Vector3 startPos, Vector3 targetPos, std::vector<PathCell>& pathList, std::vector<Vector3>& movePosList, Bool isOffset )
	{
		movePosList.clear();

		if(pathList.size() <= 1)
		{
			return;
		}

        UInt pathListMaxIndex = pathList.size() - 1;

        // 当前和上一个网格
		PathCell currCell = pathList[pathListMaxIndex-1];
		PathCell lastCell = pathList[pathListMaxIndex];

        // 当前和上一个网格方向
		PathFinder::movedir	currMoveDir = md_null;
		PathFinder::movedir lastMoveDir = getMoveDir( lastCell, currCell );;
        Vector3 posNode(0,0,0);

        // 是否偏移
        Vector3 setOff ;
        if ( isOffset )
        {
            // 得到网格坐标点
            Vector3 startCellPos = getWorldPosByPathPoint(lastCell.x, lastCell.z);
            // 计算偏移量
            setOff = startPos - startCellPos;
            setOff.y = 0;
        }
        
        ///////////////////////////////////////////////////////////////////////////////////////////////////

        // 增加移动点
        movePosList.push_back(startPos);

        // 遍历寻路网格列表，合并同方向网格
        // 从倒数第二个开始遍历
        UInt loopSize = pathListMaxIndex - 1;
        
		for(Int i = loopSize; i > 0; --i)
		{
			currCell = pathList[i];

            currMoveDir = getMoveDir( lastCell, currCell );

			if( lastMoveDir != currMoveDir )
			{
                posNode = getWorldPosByPathPoint(lastCell.x, lastCell.z);

                if ( isOffset )
                {
                    if ( i != 0 )
                    {
                        posNode += setOff;
                    }
                }
        
                movePosList.push_back(posNode);
                lastMoveDir = currMoveDir;
			}

			lastCell = currCell;
		}

		movePosList.push_back(targetPos);
	}

	//-----------------------------------------------------------------------
	Vector3	PathFinder::getWorldPosByPathPoint(Int x,  Int z)
	{
		Vec2 worldPos;
		VecU2 gridPoint = VecU2(x,z);
		mMapBlock->convertGridPointToWorldPosition(gridPoint, worldPos);

		return Vector3(worldPos.x, 0, worldPos.y);
	}

	//-----------------------------------------------------------------------
	PathCell PathFinder::getPathPointByWorldPos(Vector3 pos)
	{
		VecU2 gridPoint;
		PathCell tempPathCell;

		mMapBlock->convertWorldPositionToGridPoint(Vec2(pos.x, pos.z), gridPoint);
		tempPathCell.x = gridPoint.x;
		tempPathCell.z = gridPoint.y;
		
		return tempPathCell;
	}

	//-----------------------------------------------------------------------
	Int	PathFinder::getPathIndexByPathPoint(Int cellX, Int cellZ)
	{
		return mMapBlock->convertGridPointToGridIndex(cellX,cellZ);
	}

	//-----------------------------------------------------------------------
	Bool PathFinder::isBlockBetweenTwoPos(Vector3 startPos, Vector3 endPos, std::vector<UInt>& ignorePosList, Int findPathObjectCellDiameter)
	{
		//Int cellIndex = 0;
		Flt dis = (endPos - startPos).length();
		Flt currDis = 0;
		Vector3 currPos = startPos;
		Vector3 dir = (endPos - startPos).normalisedCopy();
		PathCell startCell = getPathPointByWorldPos(startPos);
		PathCell currCell = getPathPointByWorldPos(startPos);
		PathCell endCell = getPathPointByWorldPos(endPos);

		Byte* block = NULL;
		Bool isblock = false;

		while(1/*currCell.x != endCell.x || currCell.y != endCell.y*/)
		{
			currPos += dir;
			currDis = (currPos - startPos).length();
			if(currDis >= dis)
			{
				return false;
			}

			currCell = getPathPointByWorldPos(currPos);
			
			
			isblock = isBlock(currCell.x, currCell.z, ignorePosList, findPathObjectCellDiameter);
			if(isblock)
			{
				return true;
			}

		}

		return false;
	}

	//-----------------------------------------------------------------------
	void PathFinder::pathSmooth(std::vector<Vector3>& movePosList, std::vector<UInt>& ignorePosList, Int findPathObjectCellDiameter)
	{
		if(movePosList.size() == 0)
		{
			return;
		}

		Bool isAdd = true;

		Int index = 0;
		Vector3 startPos = movePosList[0];
		Vector3 targetPos = movePosList[movePosList.size() - 1];
		std::vector<Vector3>::iterator tempIt;

		std::vector<Vector3>::iterator it = movePosList.begin();
		for(; it != movePosList.end();)
		{
			if(isAdd && (index == 0 || index % 2 != 0))
			{
				//++it;
				++index;

				if(index != 0)
				{
					tempIt = it;
				}

			}
			else if(!isBlockBetweenTwoPos(startPos, (*it), ignorePosList, findPathObjectCellDiameter))
			{
				it = movePosList.erase(tempIt);
				tempIt = it;
				isAdd = false;
			}
			else
			{
				startPos = (*it);
				isAdd = true;
				//++it;
				++index;
			}

			++it;

			if(it == movePosList.end() /*|| targetPos == (*it)*/)
			{
				return;
			}

			

		}
	}

	//-----------------------------------------------------------------------
	void PathFinder::unLoadPathFinderMap()
	{
		mOpenAndCloseList.destroyGrids();
		mOpenPosList.destroyGrids();
		mCellCostList.destroyGrids();
		mOpenList.destroyGrids();
	}

	//-----------------------------------------------------------------------
	Flt PathFinder::getTileSize()
	{
		return mMapBlock->getGridSize();
	}


	//-----------------------------------------------------------------------
	Bool PathFinder::senceNode2DIsIntersect( ISceneNode* sceneNode1, ISceneNode* sceneNode2, Vector3  detectionCollidePos)
	{
		MovableObject* object = ((MGSceneNode*)sceneNode1)->getOgreSceneNode()->getAttachedObject(0);
		Flt sceneNode1Width = object->getBoundingBox().getHalfSize().length();

		object = ((MGSceneNode*)sceneNode2)->getOgreSceneNode()->getAttachedObject(0);
		Flt sceneNode2Width = object->getBoundingBox().getHalfSize().length();

		Vector3 pos1;
		if(detectionCollidePos == Vector3(0,0,0))
		{
			pos1 = MGEngineUtility::getPosition(sceneNode1);
		}
		else
		{
			pos1 = detectionCollidePos;
		}
		
		Vector3 pos2 = MGEngineUtility::getPosition(sceneNode2);

		Flt dis = (pos2 - pos1).length();

		if(dis <= sceneNode1Width + sceneNode2Width)
		{
			return true;
		}

		return false;
	}


	//-----------------------------------------------------------------------
	bool PathFinder::isBlock( Int currX, Int currZ, std::vector<UInt>& ignorePosList, Int findPathObjectCellDiameter, BlockManager::VertexPos vertexPos )
	{
		UInt minXOffSet = 0;
		UInt maxXOffSet = 0;
		UInt minZOffSet = 0;
		UInt maxZOffSet = 0;

		if(findPathObjectCellDiameter % 2 == 0)
		{
			if(vertexPos == BlockManager::VERTEX_LEFTUP)
			{
				minXOffSet = findPathObjectCellDiameter - 1;
				minZOffSet = 0;
				maxXOffSet = 0;
				maxZOffSet = findPathObjectCellDiameter - 1;
			}
			else if(vertexPos == BlockManager::VERTEX_LEFTDOWN)
			{
				minXOffSet = findPathObjectCellDiameter - 1;
				minZOffSet = findPathObjectCellDiameter - 1;
				maxXOffSet = 0;
				maxZOffSet = 0;
			}
			else if(vertexPos == BlockManager::VERTEX_RIGHTUP)
			{
				minXOffSet = 0;
				minZOffSet = 0;
				maxXOffSet = findPathObjectCellDiameter - 1;
				maxZOffSet = findPathObjectCellDiameter - 1;
			}
			else if(vertexPos == BlockManager::VERTEX_RIGHTDOWN)
			{
				minXOffSet = 0;
				minZOffSet = findPathObjectCellDiameter - 1;
				maxXOffSet = findPathObjectCellDiameter - 1;
				maxZOffSet = 0;
			}

		}
		else 
		{
			minXOffSet = findPathObjectCellDiameter * 0.5;
			minZOffSet = findPathObjectCellDiameter * 0.5;
			maxXOffSet = findPathObjectCellDiameter * 0.5;
			maxZOffSet = findPathObjectCellDiameter * 0.5;
		}

		Byte* gridBlock = NULL;
		for(UInt z = currZ - minZOffSet; z <= currZ + maxZOffSet; ++z)
		{
			for(UInt x = currX - minXOffSet; x <= currX + maxXOffSet; ++x)
			{
				if(isInDiameter(x, z, ignorePosList, findPathObjectCellDiameter))
				{
					continue;
				}

				gridBlock = mMapBlock->getGridDataByPoint(x,z);
				if(!gridBlock)
				{	
					continue;
				}


				if ( BlockManager::isBlockFlag(gridBlock, BlockManager::LLF_STRUCTURE_OUTSIDE) )
                {
                    return true;
                }
			}
		}

		return false;
	}


	//-----------------------------------------------------------------------
	Bool PathFinder::isInDiameter(Int currX, Int currZ, std::vector<UInt>& ignorePosList, Int findPathObjectCellDiameter, BlockManager::VertexPos vertexPos )
	{

		if(ignorePosList.size() == 0)
		{
			return false;
		}

		UInt index = mMapBlock->convertGridPointToGridIndex(currX, currZ);
		for(UInt i = 0; i < ignorePosList.size(); ++i)
		{
			if(index == ignorePosList[i])
			{
				return true;
			}
		}

		return false;
		//UInt worldGridWidth =  mMapBlock->getWorldGridWidth();
		//UInt worldGridHeight =  mMapBlock->getWorldGridHeight();
		//UInt worldGridSize = worldGridWidth * worldGridHeight;

		//UInt minXOffSet = 0;
		//UInt maxXOffSet = 0;
		//UInt minZOffSet = 0;
		//UInt maxZOffSet = 0;

		//if(findPathObjectCellDiameter % 2 == 0)
		//{
		//	if(vertexPos == BlockManager::VERTEX_LEFTUP)
		//	{
		//		minXOffSet = findPathObjectCellDiameter - 1;
		//		minZOffSet = 0;
		//		maxXOffSet = 0;
		//		maxZOffSet = findPathObjectCellDiameter - 1;
		//	}
		//	else if(vertexPos == BlockManager::VERTEX_LEFTDOWN)
		//	{
		//		minXOffSet = findPathObjectCellDiameter - 1;
		//		minZOffSet = findPathObjectCellDiameter - 1;
		//		maxXOffSet = 0;
		//		maxZOffSet = 0;
		//	}
		//	else if(vertexPos == BlockManager::VERTEX_RIGHTUP)
		//	{
		//		minXOffSet = 0;
		//		minZOffSet = 0;
		//		maxXOffSet = findPathObjectCellDiameter - 1;
		//		maxZOffSet = findPathObjectCellDiameter - 1;
		//	}
		//	else if(vertexPos == BlockManager::VERTEX_RIGHTDOWN)
		//	{
		//		minXOffSet = 0;
		//		minZOffSet = findPathObjectCellDiameter - 1;
		//		maxXOffSet = findPathObjectCellDiameter - 1;
		//		maxZOffSet = 0;
		//	}

		//}
		//else 
		//{
		//	minXOffSet = findPathObjectCellDiameter * 0.5;
		//	minZOffSet = findPathObjectCellDiameter * 0.5;
		//	maxXOffSet = findPathObjectCellDiameter * 0.5;
		//	maxZOffSet = findPathObjectCellDiameter * 0.5;
		//}


		//if(currX < centerX - minXOffSet 
		//	||currX > centerX + maxXOffSet 
		//	||currZ < centerZ - minZOffSet 
		//	||currZ > centerZ + maxZOffSet)
		//{
		//	return false;
		//}

		//return true;
	}

	//-----------------------------------------------------------------------
	void PathFinder::getCenterPosByMovePos( std::vector<Vector3>& movePosList, Int findPathObjectCellDiameter, BlockManager::VertexPos vertexPos )
	{		
		if(findPathObjectCellDiameter % 2 != 0)
		{
			return;
		}

		UInt dynamicBlockMapWidth = mMapBlock->getWorldGridWidth();
		UInt dynamicBlockMapHeight = mMapBlock->getWorldGridHeight();

		Vector3 pos;

		for(UInt i = 0; i < movePosList.size(); ++i)
		{
			pos = movePosList[i];
			VecU2 gridPoint;
			mMapBlock->convertWorldPositionToGridPoint(Vec2(pos.x, pos.z), gridPoint);
			Vec2 gridPos;
			mMapBlock->convertGridPointToWorldPosition(gridPoint, gridPos);

			{
				Vec2 vertexPosList[BlockManager::VERTEX_MAX];
				vertexPosList[BlockManager::VERTEX_LEFTUP] = Vec2(gridPos.x - BlockManager::DYNAMIC_BLOCK_GRID_SIZE * 0.5, gridPos.y - BlockManager::DYNAMIC_BLOCK_GRID_SIZE * 0.5);
				vertexPosList[BlockManager::VERTEX_RIGHTUP] = Vec2(gridPos.x + BlockManager::DYNAMIC_BLOCK_GRID_SIZE * 0.5, gridPos.y - BlockManager::DYNAMIC_BLOCK_GRID_SIZE * 0.5);
				vertexPosList[BlockManager::VERTEX_RIGHTDOWN] = Vec2(gridPos.x + BlockManager::DYNAMIC_BLOCK_GRID_SIZE * 0.5, gridPos.y + BlockManager::DYNAMIC_BLOCK_GRID_SIZE * 0.5);
				vertexPosList[BlockManager::VERTEX_LEFTDOWN] = Vec2(gridPos.x - BlockManager::DYNAMIC_BLOCK_GRID_SIZE * 0.5, gridPos.y + BlockManager::DYNAMIC_BLOCK_GRID_SIZE * 0.5);

				Vec2 currPos(pos.x, pos.z);

				if(vertexPos == BlockManager::VERTEX_MAX)
				{
					Flt minDis = 0;
					Flt tempDis = 0;
					for(Int i = 0; i < BlockManager::VERTEX_MAX; ++i)
					{
						tempDis = (currPos - vertexPosList[i]).length();
						if(i == 0 || minDis > tempDis)
						{
							vertexPos = (BlockManager::VertexPos)i;
							minDis = tempDis;
						}
					}
				}

				Vec2 gridPoint1;
				if(vertexPos == BlockManager::VERTEX_LEFTUP)
				{
					pos.x = gridPos.x - BlockManager::DYNAMIC_BLOCK_GRID_SIZE * 0.5;
					pos.z = gridPos.y - BlockManager::DYNAMIC_BLOCK_GRID_SIZE * 0.5;
				}
				else if(vertexPos == BlockManager::VERTEX_RIGHTUP)
				{
					pos.x = gridPos.x + BlockManager::DYNAMIC_BLOCK_GRID_SIZE * 0.5;
					pos.z = gridPos.y - BlockManager::DYNAMIC_BLOCK_GRID_SIZE * 0.5;
				}
				else if(vertexPos == BlockManager::VERTEX_RIGHTDOWN)
				{
					pos.x = gridPos.x + BlockManager::DYNAMIC_BLOCK_GRID_SIZE * 0.5;
					pos.z = gridPos.y + BlockManager::DYNAMIC_BLOCK_GRID_SIZE * 0.5;
				}
				else 
                if(vertexPos == BlockManager::VERTEX_LEFTDOWN)
				{
					pos.x = gridPos.x - BlockManager::DYNAMIC_BLOCK_GRID_SIZE * 0.5;
					pos.z = gridPos.y + BlockManager::DYNAMIC_BLOCK_GRID_SIZE * 0.5;
				}
			}

			movePosList[i] = pos;
		}

	}

}
