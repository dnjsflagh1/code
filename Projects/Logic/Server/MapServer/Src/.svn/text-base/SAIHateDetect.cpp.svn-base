/******************************************************************************/
#include "stdafx.h"
#include "SAIController.h"
#include "SAIHateDetect.h"
#include "SCharacter.h"
#include "SWorldManager.h"
#include "STroop.h"
#include "WorldCoreDefine.h"

#include "SFightManager.h"
/******************************************************************************/

namespace MG
{

	//--------------------------------------------------------------------------

	Str SAIHateDetect::STATE_NAME = "SAIHateDetect";

	//--------------------------------------------------------------------------
	SAIHateDetect::SAIHateDetect( SCharacter* owner )
		:LinedStateObject(STATE_NAME)
		,SAI(owner)
		,mPauseThinkTime(0)
		,mHateRatio(0)
		,mCurrTargetType(GOT_UNKNOWN)
		,mCurrTargetId(0)
		,mCurrTargetIndex(0)
	{
		mAIType = AIT_HATEDETECT;
	}

	//--------------------------------------------------------------------------
	SAIHateDetect::~SAIHateDetect()
	{
	}

	//-----------------------------------------------------------------------
	void SAIHateDetect::onEnter()
	{
		if(mOwner->isDead())
		{
			destroy();
			return;
		}

		GAMEOBJ_TYPE targetType = GOT_UNKNOWN; 
		IdType targetId = 0; 
		UInt targetIndex = 0;

		if(getTargetByHate(targetType, targetId, targetIndex))
		{
			notifySearchTarget(targetType, targetId, targetIndex);
		}

		mPauseThinkTime = 1;
	}

	//-----------------------------------------------------------------------
	void SAIHateDetect::update( Flt delta )
	{
		if(mOwner->isDead())
		{
			destroy();
			return;
		}

		if(mPauseThinkTime > 0)
		{
			mPauseThinkTime -= delta;
			return;
		}

		GAMEOBJ_TYPE targetType = GOT_UNKNOWN; 
		IdType targetId = 0; 
		UInt targetIndex = 0;

		if(getTargetByHate(targetType, targetId, targetIndex))
		{
			notifySearchTarget(targetType, targetId, targetIndex);
			return;
		}

		mPauseThinkTime = 1;
	}

	//-----------------------------------------------------------------------
	void SAIHateDetect::onLeave()
	{
		notifyEnd();
	}

	//-----------------------------------------------------------------------
	Bool SAIHateDetect::isFinished()
	{
		return false;
	}

	//-----------------------------------------------------------------------
	void SAIHateDetect::notifySearchTarget(  GAMEOBJ_TYPE targetType, IdType targetId, UInt targetIndex )
	{
		if(mAIListener)
		{
			mAIListener->onSearchTarget(targetType, targetId, targetIndex);
		}
	}

	//-----------------------------------------------------------------------
	Bool SAIHateDetect::getTargetByHate( GAMEOBJ_TYPE& targetType, IdType& targetId, UInt& targetIndex )
	{
		targetType = GOT_UNKNOWN;
		targetId = 0;
		targetIndex = 0;

		FightManager* fightManager = NULL;
		if(mOwner->getType() == GOT_SOLDIER)
		{
			//fightManager = ((STroopSoldier*)mOwner)->getOwnerTroop()->getFightManager();
		}
		else
		{
			fightManager = mOwner->getFightManager();
		}

		if(!fightManager)
		{
			return false;
		}

		Flt currTargetHateVal = 0;
		IdType fightId = 0;

		if(mCurrTargetType != GOT_UNKNOWN && mCurrTargetId != 0)
		{
			fightId = mOwner->getType() * mOwner->getID() + mCurrTargetType * mCurrTargetId;
			FightInfo*  fightInfo = fightManager->getFightInfo(fightId);
			if(!fightInfo)
			{
				return false;
			}

			currTargetHateVal =  fightInfo->hateVal + fightInfo->hateVal * (mHateRatio / 1000);
		}

		UInt tempHateVal = 0;
		GAMEOBJ_TYPE tempType = GOT_UNKNOWN;
		IdType tempId = 0;

		std::map<IdType, FightInfo>* fightInfoList = fightManager->getFightInfoList();
		if(!fightInfoList)
		{
			return false;
		}

		for(std::map<IdType, FightInfo>::iterator it = fightInfoList->begin(); it != fightInfoList->end(); ++it)
		{
			if(it->first != fightId && it->second.hateVal > currTargetHateVal)
			{
				tempHateVal = it->second.hateVal;
				tempType = it->second.fightObject->getType();
				tempId = it->second.fightObject->getID();
			}
		}

		if(tempType == GOT_UNKNOWN || tempHateVal == 0)
		{
			return false;
		}

		if(tempType == GOT_SOLDIER)
		{
			Flt tempDis = 0;
			Flt minDis = 0;

			STroop* troopObject = 0;//SWorldManager::getInstance().getTroopFromMemory(mOwner->getRegionType(), mOwner->getRegionID(), mOwner->getCurrentRealRegionObject()->getInstanceUId(), tempId);
			if(!troopObject)
			{
				return false;
			}

			//STroopSoldier* troopSoldier = 0;//troopObject->getSoldierEntitysForMinDis(mOwner->getPos());
			//if(!troopSoldier)
			//{
			//	return false;
			//}

			//targetType = tempType;
			//targetId = tempId;
			//targetIndex = troopSoldier->getID();
		}
		else
		{
			DYNAMIC_ASSERT(0);
			SCharacter* targetCharacter = NULL;//SWorldManager::getInstance().getCharacterFromSceneObject(mOwner->getRegionType(), mOwner->getRegionID(), mOwner->getCurrentRealRegionObject()->getInstanceUId(), tempType, tempId);
			if(!targetCharacter)
			{
				return false;
			}

			targetType = tempType;
			targetId = tempId;
			targetIndex = 0;
		}

		return true;
	}

	//-----------------------------------------------------------------------
	void SAIHateDetect::setHateRatio( U16 hateRatio )
	{
		mHateRatio = hateRatio;
	}

	//-----------------------------------------------------------------------
	void SAIHateDetect::setCurrTarget( GAMEOBJ_TYPE currTargetType, IdType currTargetId, UInt currTargetIndex )
	{
		mCurrTargetType = currTargetType;
		mCurrTargetId = currTargetId;
		mCurrTargetIndex = currTargetIndex;
	}



}