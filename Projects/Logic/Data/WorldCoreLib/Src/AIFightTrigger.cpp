/******************************************************************************/
#include "stdafx.h"
#include "AIFightTrigger.h"
#include "FightAiGroupTemplate.h"
#include "FightMainManager.h"
#include "AIController.h"
/******************************************************************************/

namespace MG
{

	//--------------------------------------------------------------------------
	AIFightTrigger::AIFightTrigger()
		:mFightAIGroup(NULL)
		,mPauseThinkTime(0)
	{

	}

	//--------------------------------------------------------------------------
	AIFightTrigger::~AIFightTrigger()
	{

	}

	//-----------------------------------------------------------------------
	void AIFightTrigger::update( Flt delta )
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
	void AIFightTrigger::notifyFightTrigger( FightTriggerEvent& fightTriggerEvent )
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
	FightAIInfo* AIFightTrigger::checkFightTrigger( const FightAIGroup* fightAIInfoGroup )
	{
		FightAIInfo* fightAIInfo = NULL;
		for(UInt  i = 0; i < fightAIInfoGroup->aiFightAIInfoList.size(); ++i)
		{
			FightAIInfo* tempFightAIInfo = fightAIInfoGroup->aiFightAIInfoList[i];
			if(!tempFightAIInfo)
			{
				continue;
			}

			if(i == 0 
				|| tempFightAIInfo->priority >= fightAIInfo->priority
				|| getFightAITriggerCount(tempFightAIInfo->aiFightId) < tempFightAIInfo->contactNum)
			{
				fightAIInfo = tempFightAIInfo;
			}
		}

		if(!fightAIInfo)
		{
			return NULL;
		}

		Bool isTrigger = false;

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

		if(!isTrigger)
		{
			fightAIInfo = NULL;
		}

		return fightAIInfo;
	}

	//------------------------------------------------------------------------------------
	Bool AIFightTrigger::checkContactType1( FightAIInfo* fightAIInfo )
	{
		return false;
	}

	//------------------------------------------------------------------------------------
	Bool AIFightTrigger::checkContactType2( FightAIInfo* fightAIInfo )
	{
		return false;
	}

	//------------------------------------------------------------------------------------
	Bool AIFightTrigger::checkContactType3( FightAIInfo* fightAIInfo )
	{
		return false;
	}

	//------------------------------------------------------------------------------------
	Bool AIFightTrigger::checkContactType4( FightAIInfo* fightAIInfo )
	{
		return false;
	}

	//------------------------------------------------------------------------------------

	Bool AIFightTrigger::checkContactType5( FightAIInfo* fightAIInfo )
	{
		return false;
	}

	//------------------------------------------------------------------------------------

	Bool AIFightTrigger::checkContactType6( FightAIInfo* fightAIInfo )
	{
		return false;
	}

	//------------------------------------------------------------------------------------

	Bool AIFightTrigger::checkContactType7( FightAIInfo* fightAIInfo )
	{
		return false;
	}

	//------------------------------------------------------------------------------------

	Bool AIFightTrigger::checkContactType8( FightAIInfo* fightAIInfo )
	{
		return false;
	}

	//------------------------------------------------------------------------------------
	void AIFightTrigger::getCharacterForContactCharType( FightAIInfo* fightAIInfo, GAMEOBJ_TYPE& gameObjType, IdType& gameObjId )
	{

	}

	//------------------------------------------------------------------------------------
	void AIFightTrigger::getCharacterForEventCharType( FightAIInfo* fightAIInfo, std::vector<FightEventGameObj>& fightEventGameObjList )
	{

	}

	//------------------------------------------------------------------------------------
	void AIFightTrigger::setFightEvent( FightAIInfo* fightAIInfo )
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
	void AIFightTrigger::setCurrTarget( GAMEOBJ_TYPE gameObjType, IdType gameObjId )
	{
		mCurrTargetType = gameObjType;
		mCurrTargetId = gameObjId;
	}

	//------------------------------------------------------------------------------------
	UInt AIFightTrigger::getFightAITriggerCount( UInt aiFightId )
	{
		return 0;
	}

}