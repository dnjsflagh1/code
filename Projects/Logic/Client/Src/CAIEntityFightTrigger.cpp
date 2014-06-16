/******************************************************************************/
#include "stdafx.h"
#include "CAIEntityFightTrigger.h"
#include "ICollisionSystem.h"
#include "CCharacterSceneEntity.h"
#include "ClientMain.h"
#include "CSceneManager.h"
#include "CTroopSoldierEntity.h"
#include "CTroopEntity.h"
#include "CPlayer.h"
#include "FightAiGroupTemplate.h"
#include "CFightMainManager.h"
#include "CAIController.h"
/******************************************************************************/

namespace MG
{

	//--------------------------------------------------------------------------

	Str CAIEntityFightTrigger::STATE_NAME = "CAIEntityFightTrigger";

	//--------------------------------------------------------------------------
	CAIEntityFightTrigger::CAIEntityFightTrigger( CCharacterSceneEntity* characterSceneEntity )
		:LinedStateObject(STATE_NAME)
		,mCharacterSceneEntity(characterSceneEntity)
		,mFightAIGroup(NULL)
		,mPauseThinkTime(0)
	{

	}

	//--------------------------------------------------------------------------
	CAIEntityFightTrigger::~CAIEntityFightTrigger()
	{

	}

	//-----------------------------------------------------------------------
	void CAIEntityFightTrigger::update( Flt delta )
	{
		if(mPauseThinkTime > 0)
		{
			mPauseThinkTime -= delta;
			return;
		}

		FightAIInfo* fightAIInfo = checkFightTrigger(mFightAIGroup);
		if(!fightAIInfo)
		{
			return;
		}

		setFightEvent(fightAIInfo);

		mPauseThinkTime = 2;
	}

	//-----------------------------------------------------------------------
	Bool CAIEntityFightTrigger::isFinished()
	{
		return false;
	}

	//-----------------------------------------------------------------------
	void CAIEntityFightTrigger::onEnter()
	{
		if(mCharacterSceneEntity->getType() != GOT_SOLDIER)
		{
			mFightAIGroup = mCharacterSceneEntity->getFightAIGroup();
		}
		else
		{	
			mFightAIGroup = ((CTroopSoldierEntity*)mCharacterSceneEntity)->getTroopEntity()->getFightAIGroup();
		}

		if(!mFightAIGroup)
		{
			destroy();
			return;
		}

		//FightAIInfo* fightAIInfo = checkFightTrigger(fightAIGroup);
		//if(!fightAIInfo)
		//{
		//	destroy();
		//	return;
		//}

		//setFightEvent(fightAIInfo);
	}	

	//-----------------------------------------------------------------------
	void CAIEntityFightTrigger::onLeave()
	{

	}

	//------------------------------------------------------------------------------------
	//void CAIEntityFightTrigger::addFightTriggerListener( FightTriggerListener* listener )
	//{
	//	mListenerList.push_back(listener);
	//}

	////------------------------------------------------------------------------------------
	//void CAIEntityFightTrigger::removeFightTriggerListener( FightTriggerListener* listener )
	//{
	//	FightTriggerListener* fightTriggerListener = NULL;
	//	for(std::list<FightTriggerListener*>::iterator it = mListenerList.begin(); it != mListenerList.end(); ++it)
	//	{
	//		fightTriggerListener = (*it);
	//		if(!fightTriggerListener || fightTriggerListener == listener)
	//		{
	//			continue;
	//		}

	//		mListenerList.erase(it);
	//		return;
	//	}
	//}

	////------------------------------------------------------------------------------------
	//void CAIEntityFightTrigger::clearAllFightTriggerListener()
	//{
	//	mListenerList.clear();
	//}

	//------------------------------------------------------------------------------------
	Bool CAIEntityFightTrigger::checkContactType1( FightAIInfo* fightAIInfo )
	{
		//FightManager* fightManager = NULL;

		//GAMEOBJ_TYPE gameObjType = GOT_UNKNOWN;
		//IdType gameObjId = 0;

		//getCharacterForContactCharType(fightAIInfo, gameObjType, gameObjId);
		//if(gameObjType == GOT_UNKNOWN || gameObjId == 0)
		//{
		//	return false;
		//}

		//U32 currTime = MGTimeOp::getCurrTick();

		//fightManager = CFightMainManager::getInstance().getFightManager(gameObjType, gameObjId);

		//if(!fightManager || currTime - fightManager->getFightBeginTime() <= fightAIInfo->contactParam2)
		//{
		//	return false;
		//}

		return true;
	}

	//------------------------------------------------------------------------------------
	Bool CAIEntityFightTrigger::checkContactType2( FightAIInfo* fightAIInfo )
	{
		//FightManager* fightManager = NULL;

		//GAMEOBJ_TYPE gameObjType = GOT_UNKNOWN;
		//IdType gameObjId = 0;

		//getCharacterForContactCharType(fightAIInfo, gameObjType, gameObjId);

		//fightManager = CFightMainManager::getInstance().getFightManager(gameObjType, gameObjId);
		//if(!fightManager)
		//{	
		//	return false;
		//}

		//if(fightManager->getFightInfoNum() <= fightAIInfo->contactParam2)
		//{
		//	destroy();
		//	return false;
		//}

		return true;
	}

	//------------------------------------------------------------------------------------
	Bool CAIEntityFightTrigger::checkContactType3( FightAIInfo* fightAIInfo )
	{
		GAMEOBJ_TYPE ownerType = GOT_UNKNOWN;
		IdType ownerId = 0;

		if(mCharacterSceneEntity->getType() != GOT_SOLDIER)
		{
			ownerType = mCharacterSceneEntity->getType();
			ownerId = mCharacterSceneEntity->getID();
		}
		else
		{
			CTroopEntity* troopObject = ((CTroopSoldierEntity*)mCharacterSceneEntity)->getTroopEntity();
			ownerType = GOT_TROOP;
			ownerId = troopObject->getID();
		}

		GAMEOBJ_TYPE gameObjType = GOT_UNKNOWN;
		IdType gameObjId = 0;

		getCharacterForContactCharType(fightAIInfo, gameObjType, gameObjId);

		if(gameObjType != ownerType || gameObjId != ownerId)
		{
			
		}

		return true;
	}

	//------------------------------------------------------------------------------------
	Bool CAIEntityFightTrigger::checkContactType4( FightAIInfo* fightAIInfo )
	{
		GAMEOBJ_TYPE ownerType = GOT_UNKNOWN;
		IdType ownerId = 0;

		if(mCharacterSceneEntity->getType() != GOT_SOLDIER)
		{
			ownerType = mCharacterSceneEntity->getType();
			ownerId = mCharacterSceneEntity->getID();
		}
		else
		{
			CTroopEntity* troopObject = ((CTroopSoldierEntity*)mCharacterSceneEntity)->getTroopEntity();
			ownerType = GOT_TROOP;
			ownerId = troopObject->getID();
		}

		GAMEOBJ_TYPE gameObjType = GOT_UNKNOWN;
		IdType gameObjId = 0;

		getCharacterForContactCharType(fightAIInfo, gameObjType, gameObjId);

		if(gameObjType != ownerType || gameObjId != ownerId)
		{

		}

		return true;
	}

	//------------------------------------------------------------------------------------

	Bool CAIEntityFightTrigger::checkContactType5( FightAIInfo* fightAIInfo )
	{
		GAMEOBJ_TYPE ownerType = GOT_UNKNOWN;
		IdType ownerId = 0;

		if(mCharacterSceneEntity->getType() != GOT_SOLDIER)
		{
			ownerType = mCharacterSceneEntity->getType();
			ownerId = mCharacterSceneEntity->getID();
		}
		else
		{
			CTroopEntity* troopObject = ((CTroopSoldierEntity*)mCharacterSceneEntity)->getTroopEntity();
			ownerType = GOT_TROOP;
			ownerId = troopObject->getID();
		}

		GAMEOBJ_TYPE gameObjType = GOT_UNKNOWN;
		IdType gameObjId = 0;

		getCharacterForContactCharType(fightAIInfo, gameObjType, gameObjId);

		if(gameObjType != ownerType || gameObjId != ownerId)
		{

		}

		return true;
	}

	//------------------------------------------------------------------------------------

	Bool CAIEntityFightTrigger::checkContactType6( FightAIInfo* fightAIInfo )
	{
		GAMEOBJ_TYPE ownerType = GOT_UNKNOWN;
		IdType ownerId = 0;

		if(mCharacterSceneEntity->getType() != GOT_SOLDIER)
		{
			ownerType = mCharacterSceneEntity->getType();
			ownerId = mCharacterSceneEntity->getID();
		}
		else
		{
			CTroopEntity* troopObject = ((CTroopSoldierEntity*)mCharacterSceneEntity)->getTroopEntity();
			ownerType = GOT_TROOP;
			ownerId = troopObject->getID();
		}

		GAMEOBJ_TYPE gameObjType = GOT_UNKNOWN;
		IdType gameObjId = 0;

		getCharacterForContactCharType(fightAIInfo, gameObjType, gameObjId);

		if(gameObjType != ownerType || gameObjId != ownerId)
		{

		}

		return true;
	}

	//------------------------------------------------------------------------------------

	Bool CAIEntityFightTrigger::checkContactType7( FightAIInfo* fightAIInfo )
	{
		GAMEOBJ_TYPE ownerType = GOT_UNKNOWN;
		IdType ownerId = 0;

		if(mCharacterSceneEntity->getType() != GOT_SOLDIER)
		{
			ownerType = mCharacterSceneEntity->getType();
			ownerId = mCharacterSceneEntity->getID();
		}
		else
		{
			CTroopEntity* troopObject = ((CTroopSoldierEntity*)mCharacterSceneEntity)->getTroopEntity();
			ownerType = GOT_TROOP;
			ownerId = troopObject->getID();
		}

		GAMEOBJ_TYPE gameObjType = GOT_UNKNOWN;
		IdType gameObjId = 0;

		getCharacterForContactCharType(fightAIInfo, gameObjType, gameObjId);

		if(gameObjType == ownerType && gameObjId == ownerId)
		{
			return false; 
		}

		Vec3 ownerPos = mCharacterSceneEntity->getPos();
		Vec3 targetPos;

		if(gameObjType != GOT_TROOP)
		{
			CTroopEntity* troopObject = CSceneManager::getInstance().getTroopEntity(gameObjId);
			if(!troopObject)
			{
				return false;
			}

			CTroopSoldierEntity* troopSoldierEntity = troopObject->getSoldierEntitysForMinDis(ownerPos);
			targetPos = troopSoldierEntity->getPos();
		}
		else
		{
			CCharacterSceneEntity* characterSceneEntity = CSceneManager::getInstance().getCharacterSceneEntity(gameObjType, gameObjId);
			if(!characterSceneEntity)
			{
				return false;
			}

			targetPos = characterSceneEntity->getPos();

		}

		if((ownerPos - targetPos).length() <= fightAIInfo->contactParam2)
		{
			return false;
		}

		return true;
	}

	//------------------------------------------------------------------------------------

	Bool CAIEntityFightTrigger::checkContactType8( FightAIInfo* fightAIInfo )
	{
		GAMEOBJ_TYPE ownerType = GOT_UNKNOWN;
		IdType ownerId = 0;

		if(mCharacterSceneEntity->getType() != GOT_SOLDIER)
		{
			ownerType = mCharacterSceneEntity->getType();
			ownerId = mCharacterSceneEntity->getID();
		}
		else
		{
			CTroopEntity* troopObject = ((CTroopSoldierEntity*)mCharacterSceneEntity)->getTroopEntity();
			ownerType = GOT_TROOP;
			ownerId = troopObject->getID();
		}

		GAMEOBJ_TYPE gameObjType = GOT_UNKNOWN;
		IdType gameObjId = 0;

		getCharacterForContactCharType(fightAIInfo, gameObjType, gameObjId);

		if(gameObjType == ownerType && gameObjId == ownerId)
		{
			return false; 
		}

		Vec3 ownerPos = mCharacterSceneEntity->getPos();
		Vec3 targetPos;

		if(gameObjType != GOT_TROOP)
		{
			CTroopEntity* troopObject = CSceneManager::getInstance().getTroopEntity(gameObjId);
			if(!troopObject)
			{
				return false;
			}

			CTroopSoldierEntity* troopSoldierEntity = troopObject->getSoldierEntitysForMinDis(ownerPos);
			targetPos = troopSoldierEntity->getPos();
		}
		else
		{
			CCharacterSceneEntity* characterSceneEntity = CSceneManager::getInstance().getCharacterSceneEntity(gameObjType, gameObjId);
			if(!characterSceneEntity)
			{
				return false;
			}

			targetPos = characterSceneEntity->getPos();

		}

		if((ownerPos - targetPos).length() >= fightAIInfo->contactParam2)
		{
			return false;
		}

		return true;
	}

	//------------------------------------------------------------------------------------
	void CAIEntityFightTrigger::getCharacterForContactCharType( FightAIInfo* fightAIInfo, GAMEOBJ_TYPE& gameObjType, IdType& gameObjId )
	{
		gameObjType = GOT_UNKNOWN;
		gameObjId = 0;

		switch(fightAIInfo->contactParam1)
		{
		case CCT_CCT1:
			gameObjType = mCharacterSceneEntity->getType();
			if(gameObjType != GOT_SOLDIER)
			{
				gameObjId = mCharacterSceneEntity->getID();
			}
			else
			{
				gameObjId = ((CTroopSoldierEntity*)mCharacterSceneEntity)->getTroopEntity()->getID();
			}
			break;

		case CCT_CCT2:
			gameObjType = mCurrTargetType;
			gameObjId = mCurrTargetId;
			break;

		case CCT_CCT3:
		case CCT_CCT4:
			{
				/*FightManager* fightManager = NULL;
				UInt tempHateVal = 0;
				GAMEOBJ_TYPE tempType = GOT_UNKNOWN;
				IdType tempId = 0;

				if(mCharacterSceneEntity->getType() != GOT_SOLDIER)
				{
					fightManager = mCharacterSceneEntity->getFightManager();
				}
				else
				{
					fightManager = ((CTroopSoldierEntity*)mCharacterSceneEntity)->getTroopEntity()->getFightManager();
				}

				if(!fightManager)
				{
					return;
				}

				FightInfo* fightInfo = NULL;
				if(CCT_CCT3)
				{
					fightInfo = fightManager->getFightInfoByHate(FightManager::HT_MAX);
				}
				else
				{
					fightInfo = fightManager->getFightInfoByHate(FightManager::HT_SEC);
				}
				
				if(!fightInfo)
				{
					return;
				}

				gameObjType = fightInfo->fightObject->getType();
				gameObjId = fightInfo->fightObject->getID();	*/
			}
			break;
		}
	}

	//------------------------------------------------------------------------------------
	void CAIEntityFightTrigger::getCharacterForEventCharType( FightAIInfo* fightAIInfo, std::vector<FightEventGameObj>& fightEventGameObjList )
	{
		fightEventGameObjList.clear();

		FightEventGameObj fightEventGameObj;

		switch(fightAIInfo->eventParam1)
		{
		case ETT_EET1:
			fightEventGameObj.gameObjType = mCharacterSceneEntity->getType();
			if(fightEventGameObj.gameObjType != GOT_SOLDIER)
			{
				fightEventGameObj.gameObjId = mCharacterSceneEntity->getID();
			}
			else
			{
				fightEventGameObj.gameObjId = ((CTroopSoldierEntity*)mCharacterSceneEntity)->getTroopEntity()->getID();
			}

			fightEventGameObjList.push_back(fightEventGameObj);
			break;

		case ETT_EET2:
			fightEventGameObj.gameObjType = mCurrTargetType;
			fightEventGameObj.gameObjId = mCurrTargetId;

			fightEventGameObjList.push_back(fightEventGameObj);
			break;

		case ETT_EET3:
		case ETT_EET4:
			{
				//FightManager* fightManager = NULL;
				//UInt tempHateVal = 0;
				//GAMEOBJ_TYPE tempType = GOT_UNKNOWN;
				//IdType tempId = 0;

				//if(mCharacterSceneEntity->getType() != GOT_SOLDIER)
				//{
				//	fightManager = mCharacterSceneEntity->getFightManager();
				//}
				//else
				//{
				//	fightManager = ((CTroopSoldierEntity*)mCharacterSceneEntity)->getTroopEntity()->getFightManager();
				//}

				//if(!fightManager)
				//{
				//	return;
				//}

				//FightInfo* fightInfo = NULL;
				//if(ETT_EET3)
				//{
				//	fightInfo = fightManager->getFightInfoByHate(FightManager::HT_MAX);
				//}
				//else
				//{
				//	fightInfo = fightManager->getFightInfoByHate(FightManager::HT_SEC);
				//}

				//if(!fightInfo)
				//{
				//	return;
				//}

				//fightEventGameObj.gameObjType = fightInfo->fightObject->getType();
				//fightEventGameObj.gameObjId = fightInfo->fightObject->getID();

				//fightEventGameObjList.push_back(fightEventGameObj);
			}
			break;

		case ETT_EET5:
			{
				//FightManager* fightManager = NULL;

				//if(mCharacterSceneEntity->getType() != GOT_SOLDIER)
				//{
				//	fightManager = mCharacterSceneEntity->getFightManager();
				//}
				//else
				//{
				//	fightManager = ((CTroopSoldierEntity*)mCharacterSceneEntity)->getTroopEntity()->getFightManager();
				//}

				//if(!fightManager)
				//{
				//	return;
				//}

				//UInt fightInfoNum = fightManager->getFightInfoNum();
				//if(fightInfoNum == 0)
				//{
				//	return;
				//}

				//UInt randomIndex = MGRandom::getInstance().rand_ab_One(0, fightInfoNum);
				//FightInfo* fightInfo = fightManager->getFightInfoForIndex(randomIndex);

				//fightEventGameObj.gameObjType = fightInfo->fightObject->getType();
				//fightEventGameObj.gameObjId = fightInfo->fightObjectID;

				//fightEventGameObjList.push_back(fightEventGameObj);
			}

			break;

		case ETT_EET6:
			{
				//FightManager* fightManager = NULL;
				//UInt tempHateVal = 0;
				//GAMEOBJ_TYPE tempType = GOT_UNKNOWN;
				//IdType tempId = 0;

				//if(mCharacterSceneEntity->getType() != GOT_SOLDIER)
				//{
				//	fightManager = mCharacterSceneEntity->getFightManager();
				//}
				//else
				//{
				//	fightManager = ((CTroopSoldierEntity*)mCharacterSceneEntity)->getTroopEntity()->getFightManager();
				//}

				//if(!fightManager)
				//{
				//	return;
				//}

				//std::map<IdType, FightInfo>* fightInfoList = fightManager->getFightInfoList();
				//for(std::map<IdType, FightInfo>::iterator it = fightInfoList->begin(); it != fightInfoList->end(); ++it)
				//{
				//	fightEventGameObj.gameObjType = it->second.fightObject->getType();
				//	fightEventGameObj.gameObjId = it->second.fightObjectID;

				//	fightEventGameObjList.push_back(fightEventGameObj);
				//}
			}

			break;
		}
	}


	//------------------------------------------------------------------------------------
	UInt CAIEntityFightTrigger::getFightAITriggerCount( UInt fightAIId )
	{
		UInt count = 0;
		if(mCharacterSceneEntity->getType() != GOT_SOLDIER)
		{
			count = mCharacterSceneEntity->getFightAITriggerCount(fightAIId);
		}
		else
		{
			count = ((CTroopSoldierEntity*)mCharacterSceneEntity)->getTroopEntity()->getFightAITriggerCount(fightAIId);
		}

		return count;
	}

}