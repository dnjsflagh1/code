/******************************************************************************/
#include "stdafx.h"
#include "SAIFightTrigger.h"
#include "SCharacter.h"
#include "SWorldManager.h"
#include "STroop.h"
#include "FightAiGroupTemplate.h"
#include "SFightMainManager.h"
#include "SAIController.h"
#include "SFightManager.h"
/******************************************************************************/

namespace MG
{

	//--------------------------------------------------------------------------

	Str SAIFightTrigger::STATE_NAME = "SAIFightTrigger";

	//--------------------------------------------------------------------------
	SAIFightTrigger::SAIFightTrigger( SCharacter* owner )
		:LinedStateObject(STATE_NAME)
		,mOwner(owner)
		,mFightAIGroup(NULL)
		,mPauseThinkTime(0)
		,mCurrTargetType(GOT_UNKNOWN)
		,mCurrTargetId(0)
	{
	}

	//--------------------------------------------------------------------------
	SAIFightTrigger::~SAIFightTrigger()
	{
	}

	//-----------------------------------------------------------------------
	void SAIFightTrigger::update( Flt delta )
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
		
		addFightAITriggerCount(fightAIInfo->aiFightId);

		setFightEvent(fightAIInfo);

		mPauseThinkTime = 2;
	}

	//-----------------------------------------------------------------------
	Bool SAIFightTrigger::isFinished()
	{
		return false;
	}

	//-----------------------------------------------------------------------
	void SAIFightTrigger::onEnter()
	{
		if(mOwner->getType() != GOT_SOLDIER)
		{
			mFightAIGroup = mOwner->getFightAIGroup();
		}
		else
		{	
			//mFightAIGroup = ((STroopSoldier*)mOwner)->getOwnerTroop()->getFightAIGroup();
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
	void SAIFightTrigger::onLeave()
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
	void SAIFightTrigger::notifyFightTrigger( FightTriggerEvent& fightTriggerEvent )
	{
		if(mAIListener)
		{
			mAIListener->onFightTrigger(fightTriggerEvent);
		}
		//FightTriggerListener* fightTriggerListener = NULL;
		//for(std::list<FightTriggerListener*>::iterator it = mListenerList.begin(); it != mListenerList.end(); ++it)
		//{
		//	fightTriggerListener = (*it);
		//	if(!fightTriggerListener)
		//	{
		//		continue;
		//	}

		//	fightTriggerListener->onFightTrigger(fightTriggerEvent);
		//}
	}

	//------------------------------------------------------------------------------------
	FightAIInfo* SAIFightTrigger::checkFightTrigger( const FightAIGroup* fightAIInfoGroup )
	{
		FightAIInfo* fightAIInfo = NULL;
		for(UInt  i = 0; i < fightAIInfoGroup->aiFightAIInfoList.size(); ++i)
		{
			FightAIInfo* tempFightAIInfo = fightAIInfoGroup->aiFightAIInfoList[i];
			if(!tempFightAIInfo)
			{
				continue;
			}

			if(getFightAITriggerCount(tempFightAIInfo->aiFightId) < tempFightAIInfo->contactNum 
				&&( i == 0 || tempFightAIInfo->priority >= fightAIInfo->priority))
			{
				fightAIInfo = tempFightAIInfo;
			}
		}

		if(!fightAIInfo)
		{
			return false;
		}

		Bool isTrigger = false;

		U32 randomNum = MGRandom::getInstance().rand_ab_One(0, 1000);
		if(randomNum <= fightAIInfo->randomNum)
		{
			switch(fightAIInfo->contactType)
			{
			case CT_ContactType1:
				isTrigger = checkContactType1(fightAIInfo);
				break;

			case CT_ContactType2:
				isTrigger = checkContactType2(fightAIInfo);
				break;

			case CT_ContactType3:
				isTrigger = checkContactType3(fightAIInfo);
				break;

			case CT_ContactType4:
				isTrigger = checkContactType4(fightAIInfo);
				break;

			case CT_ContactType5:
				isTrigger = checkContactType5(fightAIInfo);
				break;

			case CT_ContactType6:
				isTrigger = checkContactType6(fightAIInfo);
				break;

			case CT_ContactType7:
				isTrigger = checkContactType7(fightAIInfo);
				break;

			case CT_ContactType8:
				isTrigger = checkContactType8(fightAIInfo);
				break;
			}
		}

	
		if(!isTrigger)
		{
			fightAIInfo = NULL;
		}

		return fightAIInfo;
	}

	//------------------------------------------------------------------------------------
	Bool SAIFightTrigger::checkContactType1( FightAIInfo* fightAIInfo )
	{
		FightManager* fightManager = NULL;

		GAMEOBJ_TYPE gameObjType = GOT_UNKNOWN;
		IdType gameObjId = 0;

		getCharacterForContactCharType(fightAIInfo, gameObjType, gameObjId);
		if(gameObjType == GOT_UNKNOWN || gameObjId == 0)
		{
			return false;
		}

		U32 currTime = MGTimeOp::getCurrTick();

		DYNAMIC_ASSERT(0);
		SCharacter* character = NULL;//SWorldManager::getInstance().getCharacterFromSceneObject(mOwner->getRegionType(), mOwner->getRegionID(), mOwner->getCurrentRealRegionObject()->getInstanceUId(), gameObjType, gameObjId);
		if(!character)
		{
			return false;
		}

		fightManager = character->getFightManager();
		Flt fightIntervalTime = (currTime - fightManager->getFightBeginTime()) / 1000;

		if(!fightManager || fightIntervalTime <= fightAIInfo->contactParam2)
		{
			return false;
		}

		return true;
	}

	//------------------------------------------------------------------------------------
	Bool SAIFightTrigger::checkContactType2( FightAIInfo* fightAIInfo )
	{
		FightManager* fightManager = NULL;

		GAMEOBJ_TYPE gameObjType = GOT_UNKNOWN;
		IdType gameObjId = 0;

		getCharacterForContactCharType(fightAIInfo, gameObjType, gameObjId);
		if(gameObjType == GOT_UNKNOWN || gameObjId == 0)
		{
			return false;
		}

		DYNAMIC_ASSERT(0);
		SCharacter* character = NULL; //SWorldManager::getInstance().getCharacterFromSceneObject(mOwner->getRegionType(), mOwner->getRegionID(), mOwner->getCurrentRealRegionObject()->getInstanceUId(), gameObjType, gameObjId);
		if(!character)
		{
			return false;
		}

		fightManager = character->getFightManager();

		if(fightManager->getFightInfoNum() <= fightAIInfo->contactParam2)
		{
			destroy();
			return false;
		}

		return true;
	}

	//------------------------------------------------------------------------------------
	Bool SAIFightTrigger::checkContactType3( FightAIInfo* fightAIInfo )
	{
		GAMEOBJ_TYPE gameObjType = GOT_UNKNOWN;
		IdType gameObjId = 0;

		getCharacterForContactCharType(fightAIInfo, gameObjType, gameObjId);
		if(gameObjType == GOT_UNKNOWN || gameObjId == 0)
		{
			return false;
		}

		DYNAMIC_ASSERT(0);
		SCharacter* character = NULL;//SWorldManager::getInstance().getCharacterFromSceneObject(mOwner->getRegionType(), mOwner->getRegionID(), mOwner->getCurrentRealRegionObject()->getInstanceUId(), gameObjType, gameObjId);
		if(!character)
		{
			return false;
		}

		AttributeSet* attributeSet = character->getAttributeSet();
		Flt val1 = attributeSet->getFanalValue(fightAIInfo->contactParam2);
		Flt val2 = attributeSet->getFanalValue(fightAIInfo->contactParam3);

		if( (val1 / val2 * 0.1) >= fightAIInfo->contactParam4)
		{
			return false;
		}

		return true;
	}

	//------------------------------------------------------------------------------------
	Bool SAIFightTrigger::checkContactType4( FightAIInfo* fightAIInfo )
	{
		GAMEOBJ_TYPE gameObjType = GOT_UNKNOWN;
		IdType gameObjId = 0;

		getCharacterForContactCharType(fightAIInfo, gameObjType, gameObjId);
		if(gameObjType == GOT_UNKNOWN || gameObjId == 0)
		{
			return false;
		}

		DYNAMIC_ASSERT(0);
		SCharacter* character = NULL;//SWorldManager::getInstance().getCharacterFromSceneObject(mOwner->getRegionType(), mOwner->getRegionID(), mOwner->getCurrentRealRegionObject()->getInstanceUId(), gameObjType, gameObjId);
		if(!character)
		{
			return false;
		}

		AttributeSet* attributeSet = character->getAttributeSet();
		Flt val1 = attributeSet->getFanalValue(fightAIInfo->contactParam2);
		Flt val2 = attributeSet->getFanalValue(fightAIInfo->contactParam3);

		if((val1 / val2 * 0.1) <= fightAIInfo->contactParam4)
		{
			return false;
		}

		return true;
	}

	//------------------------------------------------------------------------------------

	Bool SAIFightTrigger::checkContactType5( FightAIInfo* fightAIInfo )
	{
		GAMEOBJ_TYPE gameObjType = GOT_UNKNOWN;
		IdType gameObjId = 0;

		getCharacterForContactCharType(fightAIInfo, gameObjType, gameObjId);
		if(gameObjType == GOT_UNKNOWN || gameObjId == 0)
		{
			return false;
		}

		DYNAMIC_ASSERT(0);
		SCharacter* character = NULL;//SWorldManager::getInstance().getCharacterFromSceneObject(mOwner->getRegionType(), mOwner->getRegionID(), mOwner->getCurrentRealRegionObject()->getInstanceUId(), gameObjType, gameObjId);
		if(!character)
		{
			return false;
		}

		AttributeSet* attributeSet = character->getAttributeSet();
		Flt val = attributeSet->getFanalValue(fightAIInfo->contactParam2);

		if(val >= fightAIInfo->contactParam4)
		{
			return false;
		}

		return true;
	}

	//------------------------------------------------------------------------------------

	Bool SAIFightTrigger::checkContactType6( FightAIInfo* fightAIInfo )
	{
		GAMEOBJ_TYPE gameObjType = GOT_UNKNOWN;
		IdType gameObjId = 0;

		getCharacterForContactCharType(fightAIInfo, gameObjType, gameObjId);
		if(gameObjType == GOT_UNKNOWN || gameObjId == 0)
		{
			return false;
		}

		DYNAMIC_ASSERT(0);
		SCharacter* character = NULL;//SWorldManager::getInstance().getCharacterFromSceneObject(mOwner->getRegionType(), mOwner->getRegionID(), mOwner->getCurrentRealRegionObject()->getInstanceUId(), gameObjType, gameObjId);
		if(!character)
		{
			return false;
		}

		AttributeSet* attributeSet = character->getAttributeSet();
		Flt val = attributeSet->getFanalValue(fightAIInfo->contactParam2);

		if(val <= fightAIInfo->contactParam4)
		{
			return false;
		}

		return true;
	}

	//------------------------------------------------------------------------------------

	Bool SAIFightTrigger::checkContactType7( FightAIInfo* fightAIInfo )
	{
		GAMEOBJ_TYPE ownerType = GOT_UNKNOWN;
		IdType ownerId = 0;

		if(mOwner->getType() != GOT_SOLDIER)
		{
			ownerType = mOwner->getType();
			ownerId = mOwner->getID();
		}
		else
		{
			STroop* troopObject = 0;//((STroopSoldier*)mOwner)->getOwnerTroop();
			ownerType = GOT_TROOP;
			ownerId = troopObject->getID();
		}

		GAMEOBJ_TYPE gameObjType = GOT_UNKNOWN;
		IdType gameObjId = 0;

		getCharacterForContactCharType(fightAIInfo, gameObjType, gameObjId);

		if(gameObjType == GOT_UNKNOWN || gameObjId == 0 ||(gameObjType == ownerType && gameObjId == ownerId))
		{
			return false; 
		}

		Vec3 ownerPos = mOwner->getPos();
		Vec3 targetPos;

		DYNAMIC_ASSERT(0);
		SCharacter* character = NULL;//SWorldManager::getInstance().getCharacterFromSceneObject(mOwner->getRegionType(), mOwner->getRegionID(), mOwner->getCurrentRealRegionObject()->getInstanceUId(), gameObjType, gameObjId);
		if(!character)
		{
			return false;
		}

		if(gameObjType != GOT_TROOP)
		{
			targetPos = character->getPos();
		}
		else
		{
			//STroopSoldier* troopSoldier = ((STroop*)character)->getSoldierEntitysForMinDis(ownerPos);
			//targetPos = troopSoldier->getPos();
		}

		if((ownerPos - targetPos).length() <= fightAIInfo->contactParam2)
		{
			return false;
		}

		return true;
	}

	//------------------------------------------------------------------------------------

	Bool SAIFightTrigger::checkContactType8( FightAIInfo* fightAIInfo )
	{
		GAMEOBJ_TYPE ownerType = GOT_UNKNOWN;
		IdType ownerId = 0;

		if(mOwner->getType() != GOT_SOLDIER)
		{
			ownerType = mOwner->getType();
			ownerId = mOwner->getID();
		}
		else
		{
			STroop* troopObject;// = ((STroopSoldier*)mOwner)->getOwnerTroop();
			ownerType = GOT_TROOP;
			ownerId = troopObject->getID();
		}

		GAMEOBJ_TYPE gameObjType = GOT_UNKNOWN;
		IdType gameObjId = 0;

		getCharacterForContactCharType(fightAIInfo, gameObjType, gameObjId);

		if(gameObjType == GOT_UNKNOWN || gameObjId == 0 || (gameObjType == ownerType && gameObjId == ownerId))
		{
			return false; 
		}

		Vec3 ownerPos = mOwner->getPos();
		Vec3 targetPos;

		DYNAMIC_ASSERT(0);
		SCharacter* character = NULL;//SWorldManager::getInstance().getCharacterFromSceneObject(mOwner->getRegionType(), mOwner->getRegionID(), mOwner->getCurrentRealRegionObject()->getInstanceUId(), gameObjType, gameObjId);
		if(!character)
		{
			return false;
		}

		if(gameObjType != GOT_TROOP)
		{
			targetPos = character->getPos();
		}
		else
		{
			//STroopSoldier* troopSoldier = ((STroop*)character)->getSoldierEntitysForMinDis(ownerPos);
			//targetPos = troopSoldier->getPos();
		}

		if((ownerPos - targetPos).length() >= fightAIInfo->contactParam2)
		{
			return false;
		}

		return true;
	}

	//------------------------------------------------------------------------------------
	void SAIFightTrigger::getCharacterForContactCharType( FightAIInfo* fightAIInfo, GAMEOBJ_TYPE& gameObjType, IdType& gameObjId )
	{
		gameObjType = GOT_UNKNOWN;
		gameObjId = 0;

		switch(fightAIInfo->contactParam1)
		{
		case CCT_CCT1:
			gameObjType = mOwner->getType();
			if(gameObjType != GOT_SOLDIER)
			{
				gameObjId = mOwner->getID();
			}
			else
			{
				//gameObjId = ((STroopSoldier*)mOwner)->getOwnerTroop()->getID();
			}
			break;

		case CCT_CCT2:
			gameObjType = mCurrTargetType;
			gameObjId = mCurrTargetId;
			break;

		case CCT_CCT3:
		case CCT_CCT4:
			{
				FightManager* fightManager = NULL;
				UInt tempHateVal = 0;
				GAMEOBJ_TYPE tempType = GOT_UNKNOWN;
				IdType tempId = 0;

				if(mOwner->getType() != GOT_SOLDIER)
				{
					fightManager = mOwner->getFightManager();
				}
				else
				{
					//fightManager = ((STroopSoldier*)mOwner)->getOwnerTroop()->getFightManager();
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
				gameObjId = fightInfo->fightObject->getID();	
			}
			break;
		}
	}

	//------------------------------------------------------------------------------------
	void SAIFightTrigger::getCharacterForEventCharType( FightAIInfo* fightAIInfo, std::vector<FightEventGameObj>& fightEventGameObjList )
	{
		fightEventGameObjList.clear();

		FightEventGameObj fightEventGameObj;

		switch(fightAIInfo->eventParam1)
		{
		case ETT_EET1:
			fightEventGameObj.gameObjType = mOwner->getType();
			if(fightEventGameObj.gameObjType != GOT_SOLDIER)
			{
				fightEventGameObj.gameObjId = mOwner->getID();
			}
			else
			{
				fightEventGameObj.gameObjId;// = ((STroopSoldier*)mOwner)->getOwnerTroop()->getID();
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
				FightManager* fightManager = NULL;
				UInt tempHateVal = 0;
				GAMEOBJ_TYPE tempType = GOT_UNKNOWN;
				IdType tempId = 0;

				if(mOwner->getType() != GOT_SOLDIER)
				{
					fightManager = mOwner->getFightManager();
				}
				else
				{
					fightManager;// = ((STroopSoldier*)mOwner)->getOwnerTroop()->getFightManager();
				}

				if(!fightManager)
				{
					return;
				}

				FightInfo* fightInfo = NULL;
				if(ETT_EET3)
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

				fightEventGameObj.gameObjType = fightInfo->fightObject->getType();
				fightEventGameObj.gameObjId = fightInfo->fightObject->getID();

				fightEventGameObjList.push_back(fightEventGameObj);
			}
			break;

		case ETT_EET5:
			{
				FightManager* fightManager = NULL;

				if(mOwner->getType() != GOT_SOLDIER)
				{
					fightManager = mOwner->getFightManager();
				}
				else
				{
					//fightManager = ((STroopSoldier*)mOwner)->getOwnerTroop()->getFightManager();
				}

				if(!fightManager)
				{
					return;
				}

				UInt fightInfoNum = fightManager->getFightInfoNum();
				if(fightInfoNum == 0)
				{
					return;
				}

				UInt randomIndex = MGRandom::getInstance().rand_ab_One(0, fightInfoNum);
				FightInfo* fightInfo = fightManager->getFightInfoForIndex(randomIndex);

				fightEventGameObj.gameObjType = fightInfo->fightObject->getType();
				fightEventGameObj.gameObjId = fightInfo->fightObject->getID();

				fightEventGameObjList.push_back(fightEventGameObj);
			}

			break;

		case ETT_EET6:
			{
				FightManager* fightManager = NULL;
				UInt tempHateVal = 0;
				GAMEOBJ_TYPE tempType = GOT_UNKNOWN;
				IdType tempId = 0;

				if(mOwner->getType() != GOT_SOLDIER)
				{
					fightManager = mOwner->getFightManager();
				}
				else
				{
					fightManager;// = ((STroopSoldier*)mOwner)->getOwnerTroop()->getFightManager();
				}

				if(!fightManager)
				{
					return;
				}

				std::map<IdType, FightInfo>* fightInfoList = fightManager->getFightInfoList();
				for(std::map<IdType, FightInfo>::iterator it = fightInfoList->begin(); it != fightInfoList->end(); ++it)
				{
					fightEventGameObj.gameObjType = it->second.fightObject->getType();
					fightEventGameObj.gameObjId = it->second.fightObject->getID();

					fightEventGameObjList.push_back(fightEventGameObj);
				}
			}

			break;
		}
	}

	//------------------------------------------------------------------------------------
	void SAIFightTrigger::setFightEvent( FightAIInfo* fightAIInfo )
	{
		std::vector<FightEventGameObj> fightEventGameObjList;
		getCharacterForEventCharType(fightAIInfo, fightEventGameObjList);

		FightTriggerEvent fightTriggerEvent;

		switch(fightAIInfo->eventType)
		{
		case ET_EventType1:
			fightTriggerEvent.fightTriggerEventType = FTET_BUFF;
			break;

		case ET_EventType2:
			fightTriggerEvent.fightTriggerEventType = FTET_SKILL;
			break;
		}
		
		fightTriggerEvent.eventParam1 = fightAIInfo->eventParam2;
		fightTriggerEvent.fightEventGameObjList = fightEventGameObjList;

		notifyFightTrigger(fightTriggerEvent);
	}

	//------------------------------------------------------------------------------------
	void SAIFightTrigger::addFightAITriggerCount( UInt fightAIId )
	{
		if(mOwner->getType() != GOT_SOLDIER)
		{
			mOwner->addFightAITriggerCount(fightAIId);
		}
		else
		{
			//((STroopSoldier*)mOwner)->getOwnerTroop()->addFightAITriggerCount(fightAIId);
		}
	}

	//------------------------------------------------------------------------------------
	UInt SAIFightTrigger::getFightAITriggerCount( UInt fightAIId )
	{
		UInt count = 0;
		if(mOwner->getType() != GOT_SOLDIER)
		{
			count = mOwner->getFightAITriggerCount(fightAIId);
		}
		else
		{
			//count = ((STroopSoldier*)mOwner)->getOwnerTroop()->getFightAITriggerCount(fightAIId);
		}

		return count;
	}

	//------------------------------------------------------------------------------------
	void SAIFightTrigger::setCurrTarget( GAMEOBJ_TYPE gameObjType, IdType gameObjId )
	{
		mCurrTargetType = gameObjType;
		mCurrTargetId = gameObjId;
	}

}