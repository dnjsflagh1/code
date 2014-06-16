#include "stdafx.h"
#include "BlockObject.h"
#include "DynamicBlockObject.h"
#include "MGEngineUtility.h"
#include "Scene.h"

namespace MG
{

	/**********************************************************************************************/

	BlockObjectSceneManager::BlockObjectSceneManager(Scene* scene)
		:mScene(mScene)
	{

	}

	//------------------------------------------------------------------------------------------
	BlockObjectSceneManager::~BlockObjectSceneManager()
	{

	}

	//------------------------------------------------------------------------------------------
	void BlockObjectSceneManager::Init( Vec2 leftBottomPos, Vec2 rightUpPos, Flt regineGridSize )
	{
		Flt regineGridWidth			= abs(rightUpPos.x - leftBottomPos.x);
		Flt regineGridHeight		= abs(rightUpPos.y - leftBottomPos.y);
		UInt regionGridWidthNum		= regineGridWidth / regineGridSize;
		UInt regionGridHeightNum	= regineGridHeight / regineGridSize;

		if(regionGridWidthNum * regineGridSize < regineGridWidth)
		{
			regionGridWidthNum++;
		}

		if(regionGridHeightNum * regineGridSize < regineGridHeight)
		{
			regionGridHeightNum++;
		}

		mRegionGridList.createGrids(regionGridWidthNum, regionGridHeightNum, regineGridSize, leftBottomPos);
	}

	//------------------------------------------------------------------------------------------
	void BlockObjectSceneManager::getBlockObjectList( MG::RectF rect, std::map<BlockObject*, BlockObject*> &blockObjectList )
	{
		blockObjectList.clear();
		
		std::map<UInt, RegionGrid*> regionGridList;
		getRegionRectList(rect, regionGridList);

		RegionGrid* regionGrid = NULL;
		std::map<BlockObject*, BlockObject*>::iterator it;

		for(std::map<UInt, RegionGrid*>::iterator regionGridIt = regionGridList.begin(); regionGridIt != regionGridList.end(); ++regionGridIt)
		{
			regionGrid = regionGridIt->second;
			if(!regionGrid)
			{
				continue;
			}

			for(it = regionGrid->mBlockObjectList.begin(); it != regionGrid->mBlockObjectList.end(); ++it)
			{
				blockObjectList[it->first] = it->second;	
			}
		}

	}

	//------------------------------------------------------------------------------------------
	void BlockObjectSceneManager::getBlockObjectList( Vec3 pos, std::map<BlockObject*, BlockObject*>& blockObjectList )
	{
		blockObjectList.clear();

		RegionGrid* regionGrid = getRegionRect(pos);
		if(!regionGrid)
		{
			return;
		}

		for(std::map<BlockObject*, BlockObject*>::iterator it = regionGrid->mBlockObjectList.begin(); it != regionGrid->mBlockObjectList.end(); ++it)
		{
			blockObjectList[it->first] = it->second;	
		}
	}

	//------------------------------------------------------------------------------------------
	Bool BlockObjectSceneManager::isHasBlockObject( MG::RectF rect )
	{
		std::map<BlockObject*, BlockObject*> blockObjectList;
		getBlockObjectList(rect, blockObjectList);
		if(blockObjectList.size() != 0)
		{
			return true;
		}

		return false;
	}

	//------------------------------------------------------------------------------------------
	Bool BlockObjectSceneManager::isHasBlockObject( Vec3 pos )
	{
		std::map<BlockObject*, BlockObject*> blockObjectList;
		getBlockObjectList(pos, blockObjectList);
		if(blockObjectList.size() != 0)
		{
			return true;
		}

		return false;
	}

	//------------------------------------------------------------------------------------------
	void BlockObjectSceneManager::addBlockObject( BlockObject* blockObject )
	{
		RectF rect = blockObject->getBlockPosRect();

		std::map<UInt, RegionGrid*> regionGridList;
		getRegionRectList(rect, regionGridList);

		RegionGrid* regionGrid = NULL;

		for(std::map<UInt, RegionGrid*>::iterator regionGridIt = regionGridList.begin(); regionGridIt != regionGridList.end(); ++regionGridIt)
		{
			regionGrid = regionGridIt->second;
			if(!regionGrid)
			{
				continue;
			}

			regionGrid->mBlockObjectList[blockObject] = blockObject;
		}

		blockObject->addCurrRegionGrid(regionGridList);
	}


	//------------------------------------------------------------------------------------------
	void BlockObjectSceneManager::removeBlockObject( BlockObject* blockObject )
	{
		RectF rect = blockObject->getBlockPosRect();

		std::map<UInt, RegionGrid*> regionGridList;
		getRegionRectList(rect, regionGridList);

		RegionGrid* regionGrid = NULL;
		std::map<BlockObject*, BlockObject*>::iterator blockObjectIt;

		for(std::map<UInt, RegionGrid*>::iterator regionGridIt = regionGridList.begin(); regionGridIt != regionGridList.end(); ++regionGridIt)
		{
			regionGrid = regionGridIt->second;
			if(!regionGrid)
			{
				continue;
			}

			blockObjectIt = regionGrid->mBlockObjectList.find(blockObject);
			if(blockObjectIt == regionGrid->mBlockObjectList.end())
			{
				continue;
			}

			regionGrid->mBlockObjectList.erase(blockObjectIt);
		}

		blockObject->removeCurrRegionGrid();
	}

	//------------------------------------------------------------------------------------------
	void BlockObjectSceneManager::getRegionRectList( MG::RectF rect, std::map<UInt, RegionGrid*>& regionGridList )
	{
		regionGridList.clear();

		VecU2 leftTopPoint;
		mRegionGridList.convertWorldPositionToGridPoint(Vec2(rect.left, rect.top), leftTopPoint);

		VecU2 rightBottomPoint;
		mRegionGridList.convertWorldPositionToGridPoint(Vec2(rect.right, rect.bottom), rightBottomPoint);

		UInt regionGridIndex = 0;
		RegionGrid* regionGrid = NULL;
		std::map<BlockObject*, BlockObject*>::iterator it;

		for(UInt x = leftTopPoint.x; x <= rightBottomPoint.x; ++x)
		{
			for(UInt y = rightBottomPoint.y; y <= leftTopPoint.y; ++y)
			{
				regionGrid = mRegionGridList.getGridDataByPoint(x, y);
				if(!regionGrid)
				{
					continue;
				}
				
				regionGridIndex = mRegionGridList.convertGridPointToGridIndex(VecU2(x, y));
				regionGridList[regionGridIndex] = regionGrid;
			}
		}
	}

	//------------------------------------------------------------------------------------------
	BlockObjectSceneManager::RegionGrid* BlockObjectSceneManager::getRegionRect( Vec3 pos )
	{
		RegionGrid* regionGrid = mRegionGridList.getGridByWorldPosition(pos.x, pos.z);
		if(!regionGrid)
		{
			return NULL;
		}

		return regionGrid;
	}

	//------------------------------------------------------------------------------------------
	void BlockObjectSceneManager::refreshBlock( BlockObject* blockObject )
	{
		removeBlockObject(blockObject);
		addBlockObject(blockObject);
	}

	//-----------------------------------------------------------------------
	Bool BlockObjectSceneManager::isBlockBetweenTwoPos( IDynamicBlockObject* ignoreObj, Vec3 startPos, 
														Vec3 endPos, 
														Flt blockCheckRadius, 
														IDynamicBlockObject*& collideBlockObject, 
														ISceneNodeGridLineMoveToAction::MoveToPathFindType moveToPathFindType, 
														Flt checkBlcokLenght )
	{
		Flt adjustRange = 1;

		Vec3 dir = endPos - startPos;
		dir.y = 0;
		dir.normalise();

		RectF checkRect;

		switch(moveToPathFindType)
		{	
		case ISceneNodeGridLineMoveToAction::PFT_STATIC:
			{
				//Flt addCheckLenght = 0;
				//if(checkBlcokLenght > blockCheckRadius)
				//{
				//	addCheckLenght = checkBlcokLenght;
				//}
				//else
				//{
				//	addCheckLenght = blockCheckRadius;
				//}

				//endPos += dir * addCheckLenght;
				blockCheckRadius *= adjustRange;
			}

			break;
		case ISceneNodeGridLineMoveToAction::PFT_DYNAMIC:
			blockCheckRadius *= adjustRange;
			break;
		case ISceneNodeGridLineMoveToAction::PFT_NOPATHFIND:
			blockCheckRadius *= adjustRange;
			break;
		default:
			DYNAMIC_ASSERT(0);
		}

		if(startPos.z > endPos.z)
		{
			checkRect.top = endPos.z - blockCheckRadius;
			checkRect.bottom = startPos.z + blockCheckRadius;
		}
		else
		{
			checkRect.top = startPos.z - blockCheckRadius;
			checkRect.bottom = endPos.z + blockCheckRadius;
		}

		if(startPos.x > endPos.x)
		{
			checkRect.right = startPos.x + blockCheckRadius;
			checkRect.left = endPos.x - blockCheckRadius;
		}
		else
		{
			checkRect.right = endPos.x + blockCheckRadius;
			checkRect.left = startPos.x - blockCheckRadius;
		}

		Vec3 startPosList[4];

		startPosList[0] = startPos + Vec3(1,0,1) * blockCheckRadius;
		startPosList[1] = startPos + Vec3(-1,0,1) * blockCheckRadius;
		startPosList[2] = startPos + Vec3(1,0,-1) * blockCheckRadius;
		startPosList[3] = startPos + Vec3(-1,0,-1) * blockCheckRadius;

		Vec3 endPosList[4];

		endPosList[0] = endPos + Vec3(1,0,1) * blockCheckRadius;
		endPosList[1] = endPos + Vec3(-1,0,1) * blockCheckRadius;
		endPosList[2] = endPos + Vec3(1,0,-1) * blockCheckRadius;
		endPosList[3] =	endPos + Vec3(-1,0,-1) * blockCheckRadius;

		//Vec3 startPosList[3];
		///*Vec3*/ dir = endPos - startPos;
		//dir.y = 0;
		//dir.normalise();

		//Vec3 tempDir = MGMath::rotateVector(dir, 90 * (MG_PI / 180));
		//startPosList[0] = startPos + tempDir * blockCheckCellRadius;
		//startPosList[1] = startPos;
		//tempDir = MGMath::rotateVector(dir, 270 * (MG_PI / 180));
		//startPosList[2] = startPos + tempDir * blockCheckCellRadius;

		//Vec3 endPosList[3];
		//dir = startPos - endPos;
		//dir.y = 0;
		//dir.normalise();

		//tempDir = MGMath::rotateVector(dir, 270 * (MG_PI / 180));
		//endPosList[0] = endPos + tempDir * blockCheckCellRadius;
		//endPosList[1] = endPos - dir * (blockCheckCellRadius * 1.41421);
		//tempDir = MGMath::rotateVector(dir, 90 * (MG_PI / 180));
		//endPosList[2] = endPos + tempDir * blockCheckCellRadius;

		Vector2 checkStartPos;
		Vector2 checkEndPos;

		std::map<BlockObject*, BlockObject*> blockObjectList;
		getBlockObjectList(checkRect, blockObjectList);

		DynamicBlockObject* ignoreDynamicBlockObj = (DynamicBlockObject*)ignoreObj;
		BlockObject* ignoreBlockObject = ignoreDynamicBlockObj;

		BlockObject* blockObject = NULL;
		RectF blockRect;
		FloatRect tempRect;
		RectF reRect;
		for(std::map<BlockObject*, BlockObject*>::iterator it = blockObjectList.begin(); it != blockObjectList.end(); ++it)
		{
			blockObject = it->second;
			if(!blockObject)
			{
				continue;
			}

			if(ignoreBlockObject == blockObject)
			{
				continue;
			}

			blockRect = blockObject->getBlockPosRect();

			reRect = blockRect.intersect(checkRect);
			if(reRect.isNull())
			{
				continue;
			}

			tempRect = FloatRect(blockRect.left, blockRect.top, blockRect.right, blockRect.bottom);

			for(UInt i = 0; i < 4; ++i)
			{
				checkStartPos.x = startPosList[i].x;
				checkStartPos.y = startPosList[i].z;
				checkEndPos.x = endPosList[i].x;
				checkEndPos.y = endPosList[i].z;

				//if(MGEngineUtility::clampLineInRect(Vector2(startPos.x,startPos.z)/*Vector2(startPosList[i].x, startPosList[i].z)*/, Vector2(endPos.x,endPos.z)/*Vector2(endPosList[i].x, endPosList[i].z)*/, tempRect))
				if(MGEngineUtility::clampLineInRect(checkStartPos, checkEndPos, tempRect))
				{
					DynamicBlockObject* dynamicBlockObject = (DynamicBlockObject*)blockObject;
					collideBlockObject = dynamicBlockObject;
					return true;
				}
			}

		}

		return false;



		//// 检测数据初始化
		//Flt dis             = (endPos - startPos).length();
		//Flt currDis         = 0;
		//Vec3 lastPos        = startPos;
		//Vec3 currPos        = startPos;
		//Vec3 dir            = (endPos - startPos);
		//dir.normalise();
		//// 使用网格长度递增检测
		//dir = dir * mMapBlock.getGridSize();

		//// 碰撞网格对象
		//FindPathCell21* currBlockCheckCell = NULL;
		//FindPathCell21* currBlockCheckCellResult = NULL;
		//// 碰撞检测循环索引
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
		//// 需要吧dir分解成2个网格方向


		//// 递增检测网格数据
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
		//		//TODO:JJJ  需要吧dir分解成2个网格方向
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