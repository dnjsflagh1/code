/******************************************************************************/
#include "stdafx.h"
#include "SSceneGridManager.h"
#include "SSceneGrid.h"
#include "SCharacter.h"
#include "DropItemManager.h"
#include "SRegionNetPacketProcesser.h"
#include "ArtMapResCsv.h"
#include "GameRadarConfig.h"
#include "SSceneObject.h"
#include "RegionObjectData.h"
/******************************************************************************/
namespace MG
{

	//--------------------------------------------------------------------------
	SSceneGridManager::SSceneGridManager()
		:mGridWidthNum(0)
		,mGridHeightNum(0)
		,mGridWidth(0)
		,mGridHeight(0)
		,mInteractionGridWidth(0)
		,mInteractionGridHalfWidth(0)
		,mNeedAddGridWidth(0)
		,mNeedAddGridHalfWidth(0)
		,mSceneGridList(NULL)
		,mTemplateId(0)
		,mRegionObjectBase(NULL)
	{

	}

	//--------------------------------------------------------------------------
	SSceneGridManager::~SSceneGridManager()
	{
		unInitialize();
	}

	//--------------------------------------------------------------------------
	Bool SSceneGridManager::initialize( SSceneObject* sceneObj )
	{
		if(mSceneGridList)
		{
			return false;
		}

		loadGridMap(sceneObj);

		UInt count = mGridWidthNum * mGridHeightNum;
		for(UInt i = 0; i < count; ++i)
		{
			mSceneGridList[i].setSceneGridManager(this);
		}
		return true;
	}

	//--------------------------------------------------------------------------
	Bool SSceneGridManager::unInitialize()
	{
		destroyAllGrid();
		return true;
	}

	//--------------------------------------------------------------------------
	void SSceneGridManager::clear()
	{
		removeAllObjectInSceneGrid();
	}

	//--------------------------------------------------------------------------
	void SSceneGridManager::loadGridMap( SSceneObject* sceneObj )
	{
		if(!sceneObj)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		UInt id = sceneObj->getData()->getMapId();

		MapListCsvInfo* mapListCsvInfo = MapListCsv::getInstance().getInfoByMapId(id);
		if(!mapListCsvInfo)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		ArtMapResCsvInfo* artMapResCsvInfo = ArtMapResCsv::getInstance().getArtMapResInfoById(mapListCsvInfo->artMapResId);
		if(!artMapResCsvInfo)
		{
			DYNAMIC_ASSERT(0);
			return;
		}
 
		U32 radarID = (sceneObj->getGameType() == GameType_Rpg) ? artMapResCsvInfo->rpgRadarId : artMapResCsvInfo->slgRadarId;
		const GameRadarConfigInfo* radarInfo = GameRadarConfig::getInstance().getGameRadarConfigInfo(radarID);
		if(!radarInfo)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		//Vec3 centerPos = Vec3(512,0,-512);
		mLeftBottomPos.x = radarInfo->worldCenter.x - radarInfo->worldSize.x / 2;
		mLeftBottomPos.z = radarInfo->worldCenter.y + radarInfo->worldSize.y / 2;

		mTemplateId = id;
		//mGridWidthNum = gridWidthNum;
		//mGridHeightNum = gridHeightNum;
		//mGridWidth = gridWidth;
		//mGridHeight = gridHeight;
		mGridWidth  = 20;
		mGridHeight = 20;
		mGridWidthNum =  radarInfo->worldSize.x / mGridWidth;
		mGridHeightNum = radarInfo->worldSize.y / mGridHeight;
		if(mGridWidthNum * mGridWidth < radarInfo->worldSize.x)
		{
			mGridWidthNum++;
		}

		if(mGridHeightNum * mGridHeight <  radarInfo->worldSize.y)
		{
			mGridHeightNum++;
		}

		mInteractionGridWidth = 5;
		mInteractionGridHalfWidth = mInteractionGridWidth / 2;
		mNeedAddGridWidth = 3;
		mNeedAddGridHalfWidth = mNeedAddGridWidth / 2;

		UInt a = sizeof(SSceneGrid);

		mSceneGridList = MG_NEW SSceneGrid[mGridWidthNum * mGridHeightNum];
	}

	//--------------------------------------------------------------------------
	void SSceneGridManager::destroyAllGrid()
	{
		MG_SAFE_DELETE_ARRAY(mSceneGridList);
	}

	//--------------------------------------------------------------------------
	UInt SSceneGridManager::getSceneGridIndex( Vec3 pos )
	{
		VecU2 gridPos = getSceneGridPos(pos);

		UInt index = getSceneGridIndexForGridPos(gridPos);

		return index;
	}

	//--------------------------------------------------------------------------
	VecU2 SSceneGridManager::getSceneGridPos( Vec3 pos )
	{
		pos = pos - mLeftBottomPos;

		DYNAMIC_ASSERT(pos.z <= 0);

		VecU2 gridPos;
		gridPos.x = pos.x / mGridWidth;
		gridPos.y = (-pos.z) / mGridHeight;


		return gridPos;
	}

	//--------------------------------------------------------------------------
	SSceneGrid* SSceneGridManager::getSceneGrid( Vec3 pos )
	{
		UInt index = getSceneGridIndex(pos);
		if(index < 0 || index > mGridWidthNum * mGridHeightNum)
		{
			return NULL;
		}

		return &mSceneGridList[index];
	}

	//--------------------------------------------------------------------------
	void SSceneGridManager::addOrUpdateObjectInSceneGrid( SCharacter* character, Bool isFilterSelf )
	{
		Vec3 currPos = character->getPos();
		SSceneGrid* currSceneGrid = getSceneGrid(currPos);
		if(!currSceneGrid)
		{
			return;
		}

		SSceneObjectInSceneGridsManager* sceneObjectInSceneGridsManager = 0;//character->getSceneObjectInSceneGridsManager();
		if(!sceneObjectInSceneGridsManager || currSceneGrid == sceneObjectInSceneGridsManager->mLastSceneGrid)
		{
			return;
		}

		std::map<UInt, SSceneGrid*> currInteractionGridList;
		std::map<UInt, SSceneGrid*> currNeedAddGridList;

		getSceneGridsList( currPos, mInteractionGridWidth, currInteractionGridList );
		getSceneGridsList( currPos, mNeedAddGridWidth, currNeedAddGridList );

		std::map<UInt, SSceneGrid*> delGridList;
		subSceneGridsList( sceneObjectInSceneGridsManager->mInteractionGridList, currInteractionGridList, delGridList);

		std::map<UInt, SSceneGrid*> addGridList;
		subSceneGridsList( currNeedAddGridList, sceneObjectInSceneGridsManager->mInteractionGridList, addGridList);

		//////////////////////////////////////////////////////////////////////////////////

		onLeaveSceneGrid(character, delGridList, isFilterSelf);
		onEnterSceneGrid(character, currSceneGrid, addGridList, isFilterSelf);

	}

	//--------------------------------------------------------------------------
	void SSceneGridManager::removeObjectInSceneGrid( SCharacter* character, Bool isFilterSelf )
	{
		SSceneObjectInSceneGridsManager* sceneObjectInSceneGridsManager = 0;//character->getSceneObjectInSceneGridsManager();
		if(!sceneObjectInSceneGridsManager)
		{
			return;
		}

		if(sceneObjectInSceneGridsManager->mCurrSceneGrid)
		{
			//sceneObjectInSceneGridsManager->mCurrSceneGrid->removeCharacter(character);
		}

		//for(std::map<UInt, SSceneGrid*>::iterator it = sceneObjectInSceneGridsManager->interactionGridList.begin(); it != sceneObjectInSceneGridsManager->interactionGridList.end(); ++it)
		//{
		//	it->second->removeCharacterInteraction(character);
		//}

		std::map<UInt, SSceneGrid*> leaveGridList;
		for(std::map<UInt, SSceneGrid*>::iterator interactionIt = sceneObjectInSceneGridsManager->mInteractionGridList.begin(); interactionIt != sceneObjectInSceneGridsManager->mInteractionGridList.end(); ++interactionIt)
		{
			leaveGridList[interactionIt->first] = interactionIt->second;
		}

		onLeaveSceneGrid(character, leaveGridList, isFilterSelf);

		sceneObjectInSceneGridsManager->mCurrSceneGrid = NULL;
		sceneObjectInSceneGridsManager->mLastSceneGrid = NULL;
		sceneObjectInSceneGridsManager->mInteractionGridList.clear();
	}

	//--------------------------------------------------------------------------
	void SSceneGridManager::onEnterSceneGrid( SCharacter* character, SSceneGrid* currGrid, std::map<UInt, SSceneGrid*>& enterGridList, Bool isFilterSelf )
	{
		if(!mRegionObjectBase)
		{
			return;
		}

		SSceneObjectInSceneGridsManager* sceneObjectInSceneGridsManager = 0;//character->getSceneObjectInSceneGridsManager();

		if(!sceneObjectInSceneGridsManager->mCurrSceneGrid)
		{
			sceneObjectInSceneGridsManager->mLastSceneGrid = currGrid;

		}

		sceneObjectInSceneGridsManager->mCurrSceneGrid = currGrid;
		//currGrid->addCharacter(character);

		if(enterGridList.size() == 0)
		{
			return;
		}

		//sceneObjectInSceneGridsManager->currSceneGrid = currGrid;
		//currGrid->addCharacter(character);

		SPlayer* player = NULL;//character->getOwnerPlayer();
		for(std::map<UInt, SSceneGrid*>::iterator enterIt = enterGridList.begin(); enterIt != enterGridList.end(); ++enterIt)
		{
			if(player)
			{
				//enterIt->second->addPlayerInteraction(player);
			}
			
			sceneObjectInSceneGridsManager->mInteractionGridList[enterIt->first] = enterIt->second;
		}

		if(character->getType() == GOT_PLAYERCHARACTER)
		{
			SRegionNetPacketProcesser::getInstance().broadcastAppearPlayerCharacterToRegionToOther((SPlayerCharacter*)character, mRegionObjectBase, isFilterSelf);
			SRegionNetPacketProcesser::getInstance().broadcastAppearPlayerCharacterToRegionToSelf((SPlayerCharacter*)character, enterGridList, isFilterSelf);
			SRegionNetPacketProcesser::getInstance().broadcastMonsterAppearToRegion((SPlayerCharacter*)character, enterGridList);
		}
	}

	//--------------------------------------------------------------------------
	void SSceneGridManager::onLeaveSceneGrid( SCharacter* character, std::map<UInt, SSceneGrid*>& leaveGridList, Bool isFilterSelf )
	{
		SSceneObjectInSceneGridsManager* sceneObjectInSceneGridsManager = 0;//character->getSceneObjectInSceneGridsManager();

		if(sceneObjectInSceneGridsManager->mCurrSceneGrid)
		{
			//sceneObjectInSceneGridsManager->mCurrSceneGrid->removeCharacter(character);
		}

		/*SSceneGrid* currtSceneGrid = sceneObjectInSceneGridsManager->currSceneGrid;*/
		sceneObjectInSceneGridsManager->mLastSceneGrid = sceneObjectInSceneGridsManager->mCurrSceneGrid;
		sceneObjectInSceneGridsManager->mCurrSceneGrid = NULL;

		if(leaveGridList.size() == 0)
		{
			return;
		}

		SPlayer* player = NULL;//character->getOwnerPlayer();

		//sceneObjectInSceneGridsManager->lastSceneGrid = sceneObjectInSceneGridsManager->currSceneGrid;
		//sceneObjectInSceneGridsManager->currSceneGrid = NULL;

		for(std::map<UInt, SSceneGrid*>::iterator leaveIt = leaveGridList.begin(); leaveIt != leaveGridList.end(); ++leaveIt)
		{
			if(player)
			{
				//leaveIt->second->removePlayerInteraction(player);
			}
			
			std::map<UInt, SSceneGrid*>::iterator interactionIt = sceneObjectInSceneGridsManager->mInteractionGridList.find(leaveIt->first);
			if(interactionIt != sceneObjectInSceneGridsManager->mInteractionGridList.end())
			{
				sceneObjectInSceneGridsManager->mInteractionGridList.erase(interactionIt);
			}
		}
		
		if(character->getType() == GOT_PLAYERCHARACTER)
		{
			SRegionNetPacketProcesser::getInstance().broadcastDisappearPlayerCharacterToRegionToOther(character, mRegionObjectBase, isFilterSelf);
			SRegionNetPacketProcesser::getInstance().broadcastDisappearPlayerCharacterToRegionToSelf(character, leaveGridList, isFilterSelf);
			SRegionNetPacketProcesser::getInstance().broadcastMonsterDisappearToRegion((SPlayerCharacter*)character, leaveGridList);
		}
		
	}

	//--------------------------------------------------------------------------
	UInt SSceneGridManager::getSceneGridIndexForGridPos( VecU2 gridPos )
	{
		UInt index = gridPos.y * mGridWidthNum + gridPos.x;

		return index;
	}

	//--------------------------------------------------------------------------
	void SSceneGridManager::addOrUpdateObjectInSceneGrid( dropItemData* dropItem )
	{
		Vec3 currPos = Vec3(dropItem->pos.x, 0, dropItem->pos.y);

		SSceneGrid* currSceneGrid = getSceneGrid(currPos);
		//currSceneGrid->addDropItem(dropItem);

		std::map<UInt, SSceneGrid*> interactionList;
		getSceneGridsList(currPos, mNeedAddGridWidth, interactionList);

		//for(std::map<UInt, SSceneGrid*>::iterator it = interactionList.begin(); it != interactionList.end(); ++it)
		//{
		//	it->second->addDropItemInteraction(dropItem);
		//}
	}

	//--------------------------------------------------------------------------
	void SSceneGridManager::removeAllObjectInSceneGrid()
	{
		UInt count = mGridWidthNum * mGridHeightNum;

		for(UInt i = 0; i < count; ++i)
		{
			mSceneGridList[i].removeAll();
			//mSceneGridList[i].removeAllInteraction();
		}
	}

	//--------------------------------------------------------------------------
	void SSceneGridManager::getSceneGridsList( Vec3 pos, UInt width, std::map<UInt, SSceneGrid*>& gridsList )
	{
		gridsList.clear();

		VecU2 gridPos = getSceneGridPos(pos);

		Int minX = gridPos.x - width / 2;
		Int minY = gridPos.y - width / 2;
		Int maxX = gridPos.x + width / 2;
		Int maxY = gridPos.y + width / 2;

		UInt index = 0;

		for(Int x = minX; x <= maxX; ++x)
		{
			for(Int y = minY; y <= maxY; ++y)
			{
				if(x >= 0 && x < mGridWidthNum && y >= 0 && y < mGridHeightNum)
				{
					index = getSceneGridIndexForGridPos(VecU2(x,y));

					gridsList[index] = &mSceneGridList[index];
				}
			}
		}
	}

	//--------------------------------------------------------------------------
	void SSceneGridManager::subSceneGridsList( std::map<UInt, SSceneGrid*>& gridsList1, std::map<UInt, SSceneGrid*>& gridsList2, std::map<UInt, SSceneGrid*>& resultGridsList )
	{
		resultGridsList.clear();

		for(std::map<UInt, SSceneGrid*>::iterator it1 = gridsList1.begin(); it1 != gridsList1.end(); ++it1)
		{
			std::map<UInt, SSceneGrid*>::iterator it2 = gridsList2.find(it1->first);
			if(it2 == gridsList2.end())
			{
				resultGridsList[it1->first] = it1->second;
			}
		}
	}

	//--------------------------------------------------------------------------
	UInt SSceneGridManager::getTemplateId()
	{
		return mTemplateId;
	}


}