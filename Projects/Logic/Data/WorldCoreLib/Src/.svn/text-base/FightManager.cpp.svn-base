/******************************************************************************/
#include "stdafx.h"
#include "FightManager.h"
#include "GameObject.h"
/******************************************************************************/

namespace MG
{
	//-----------------------------------------------------------------------------
	FightManager::FightManager( GameObject* owner )
		: mOwner(owner)
		, mFightBeginTime(0)
	{

	}

	//-----------------------------------------------------------------------------
	FightManager::~FightManager()
	{

	}

	void FightManager::addAndUpdateFightInfo( GameObject* fightObject, IdType addHateGameObjID, UInt hateVal )
	{
		UInt addHateVal = 0;
		Bool isFightInfo = true;

		GAMEOBJ_TYPE ownerType = mOwner->getType();
		IdType ownerID = mOwner->getID(); 

		if(mFightList.size() == 0)
		{
			isFightInfo = false;
		}

		if(ownerID == addHateGameObjID)
		{
			addHateVal = hateVal;
		}

		IdType fightId = ownerType * ownerID + fightObject->getType() * fightObject->getID();
		FightInfo* fightInfo = getFightInfo(fightId);
		if(!fightInfo)
		{
			fightInfo = addFightInfo(fightId, fightObject, addHateVal);
			if(addHateGameObjID == ownerID)
			{
				fightInfo->isInitiative= true;
			}
		}
		else
		{
			fightInfo->updateInfo(fightObject, addHateVal);
		}

		if(!isFightInfo)
		{
			mFightBeginTime = fightInfo->beginTime;
		}

		//通知监听FightInfo有改变
		notifyChanged(fightObject);
	}


	////-----------------------------------------------------------------------
	//void FightManager::addAndUpdateFightOnAppoint( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID )
	//{
	//	//addAndUpdateFightInfo(fightInitiativeType, fightInitiativeID, fightPassivityType, fightPassivityID, fightInitiativeID, 10);
	//	//addAndUpdateFightInfo(fightInitiativeType, fightInitiativeID, fightPassivityType, fightPassivityID, fightPassivityID, 10);
	//}

	////-----------------------------------------------------------------------
	//void FightManager::addAndUpdateFightOnUseAttackSkill( GAMEOBJ_TYPE fightObjecteType, IdType fightObjectID, IdType skillId, IdType addHateGameObjID, UInt hateVal )
	//{
	//	addAndUpdateFightInfo(fightObjecteType, fightObjectID, addHateGameObjID, hateVal);
	//}

	////-----------------------------------------------------------------------
	//void FightManager::addAndUpdateFightOnGuard( GAMEOBJ_TYPE fightObjecteType, IdType fightObjecteID )
	//{
	//	addAndUpdateFightInfo(fightObjecteType, fightObjecteID, mOwnerID, 10);
	//}

	////-----------------------------------------------------------------------
	//void FightManager::addAndUpdateFightOnUseAuxiliarySkill( GAMEOBJ_TYPE fightObjecteType, IdType fightObjecteID, IdType addHateGameObjID, UInt hateVal )
	//{
	//	addAndUpdateFightInfo(fightObjecteType, fightObjecteID, addHateGameObjID, hateVal);
	//}

	////-----------------------------------------------------------------------
	//void FightManager::delFightOnScope(  GAMEOBJ_TYPE fightObjecteType, IdType fightObjecteID )
	//{
	//	delFightInfo(fightObjecteType, fightObjecteID);
	//}

	////-----------------------------------------------------------------------
	//void FightManager::delFightOnEndTime(  GAMEOBJ_TYPE fightObjecteType, IdType fightObjecteID )
	//{
	//	delFightInfo(fightObjecteType, fightObjecteID);
	//}

	////-----------------------------------------------------------------------
	//void FightManager::delFightOnPursue(  GAMEOBJ_TYPE fightObjecteType, IdType fightObjecteID )
	//{
	//	delFightInfo(fightObjecteType, fightObjecteID);
	//}


	//-----------------------------------------------------------------------
	void FightManager::delFightInfo( GameObject* fightObject )
	{
		IdType fightId = mOwner->getType() * mOwner->getID() + fightObject->getType() * fightObject->getID();
		delFightInfo(fightId);
	}

	//-----------------------------------------------------------------------
	void FightManager::delAllFightInfo()
	{
		mFightList.clear();
		mFightBeginTime = 0;

		//notifyChanged();
	}

	//-----------------------------------------------------------------------
	void FightManager::update()
	{

	}

	//------------------------------------------------------------------------------------
	void FightManager::delFightInfo( IdType fightInfoID )
	{
		if(mFightList.size() == 0)
		{
			return;
		}

		std::map<IdType, FightInfo>::iterator it = mFightList.find(fightInfoID);
		if(mFightList.end() != it)
		{
			//通知监听FightInfo有改变
			notifyChanged(it->second.fightObject);
			mFightList.erase(it);
		}

		if(mFightList.size() == 0)
		{
			notifyEndFight(mOwner);
		}
	}
	
	//------------------------------------------------------------------------------------
	FightInfo* FightManager::getFightInfo( IdType fightInfoID )
	{
		std::map<IdType, FightInfo>::iterator it = mFightList.find(fightInfoID);
		if(mFightList.end() != it)
		{
			return &(it->second);
		}

		return NULL;
	}

	//------------------------------------------------------------------------------------
	FightInfo* FightManager::getFightInfoForIndex( UInt index )
	{
		UInt tempIndex = 0;
		for(std::map<IdType, FightInfo>::iterator it = mFightList.begin(); it != mFightList.end(); ++it)
		{
			if(tempIndex == index)
			{
				return &(it->second);	
			}

			tempIndex++;
		}

		return NULL;
	}

	//------------------------------------------------------------------------------------
	FightInfo* FightManager::getFightInfo( GameObject* fightObject )
	{
		IdType fightId =  mOwner->getType() * mOwner->getID() + fightObject->getType() * fightObject->getID();
		return getFightInfo(fightId);
	}

	//------------------------------------------------------------------------------------
	FightInfo* FightManager::addFightInfo( IdType fightInfoID, GameObject* fightObject, UInt hateVal )
	{		
		Bool isNotifyEnterFight = false;
		if(mFightList.size() == 0)
		{
			isNotifyEnterFight = true;
		}

		FightInfo fightInfo;
		fightInfo.fightID = fightInfoID;
		fightInfo.fightObject = fightObject;
		fightInfo.updateInfo(fightObject, hateVal);

		mFightList[fightInfoID] = fightInfo;
		
		if(isNotifyEnterFight)
		{
			notifyEnterFight(mOwner);
		}

		return &(mFightList[fightInfoID]);
	}

	//------------------------------------------------------------------------------------
	std::map<IdType, FightInfo>* FightManager::getFightInfoList()
	{
		return &mFightList;
	}

	//------------------------------------------------------------------------------------
	UInt FightManager::getFightInfoNum()
	{
		return mFightList.size();
	}

	//------------------------------------------------------------------------------------
	void FightManager::addListener( FightManagerListener* listener )
	{
		mListenerList.push_back(listener);
	}

	//------------------------------------------------------------------------------------
	void FightManager::removeListener( FightManagerListener* listener )
	{
		FightManagerListener* fightManagerListener = NULL;
		for(std::list<FightManagerListener*>::iterator it = mListenerList.begin(); it != mListenerList.end(); ++it)
		{
			fightManagerListener = (*it);
			if(!fightManagerListener || fightManagerListener == listener)
			{
				continue;
			}

			mListenerList.erase(it);
			return;
		}
	}

	//------------------------------------------------------------------------------------
	void FightManager::clearAllListener()
	{
		mListenerList.clear();
	}

	//------------------------------------------------------------------------------------
	void FightManager::notifyChanged( GameObject* fightObject )
	{
		FightManagerListener* fightManagerListener = NULL;
		for(std::list<FightManagerListener*>::iterator it = mListenerList.begin(); it != mListenerList.end(); ++it)
		{
			fightManagerListener = (*it);
			if(!fightManagerListener)
			{
				continue;
			}

			fightManagerListener->onFightInfoChanged(fightObject);
		}
	}

	//------------------------------------------------------------------------------------
	void FightManager::notifyEnterFight( GameObject* fightObject )
	{
		for(std::list<FightManagerListener*>::iterator it = mListenerList.begin(); it != mListenerList.end(); ++it)
		{
			(*it)->onEnterFight(fightObject);
		}
	}

	//------------------------------------------------------------------------------------
	void FightManager::notifyEndFight( GameObject* fightObject )
	{
		for(std::list<FightManagerListener*>::iterator it = mListenerList.begin(); it != mListenerList.end(); ++it)
		{
			(*it)->onEndFight(fightObject);
		}
	}

	//------------------------------------------------------------------------------------
	FightInfo* FightManager::getFightInfoByHate( HateType hateType )
	{
		UInt maxHateVal = 0;
		UInt secHateVal = 0;
		FightInfo* maxHateFightInfo = NULL;
		FightInfo* secHateFightInfo = NULL;

		for(std::map<IdType, FightInfo>::iterator it = mFightList.begin(); it != mFightList.end(); ++it)
		{
			if(it->second.hateVal > maxHateVal)
			{
				secHateVal = maxHateVal;
				secHateFightInfo = maxHateFightInfo;

				maxHateVal = it->second.hateVal;
				maxHateFightInfo = &it->second;
			}
		}

		switch(hateType)
		{
		case HT_MAX:
			return maxHateFightInfo;

		case HT_SEC:
			return secHateFightInfo;
		}

		return NULL;
	}

	//------------------------------------------------------------------------------------
	U64 FightManager::getFightBeginTime()
	{
		return mFightBeginTime;
	}

	//------------------------------------------------------------------------------------
	Bool FightManager::isEnterFight()
	{
		Bool isEnterFightState = false;
		if(mFightList.size())
		{
			isEnterFightState = true;
		}

		return isEnterFightState;
	}

	//------------------------------------------------------------------------------------
	Vec3 FightManager::getEnterFightPos()
	{
		return mEnterFightPos;
	}

}