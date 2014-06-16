/******************************************************************************/
#include "stdafx.h"
#include "CAIController.h"
#include "CAIEntityHateDetect.h"
#include "ICollisionSystem.h"
#include "CCharacterSceneEntity.h"
#include "ClientMain.h"
#include "CSceneManager.h"
#include "CTroopSoldierEntity.h"
#include "CTroopEntity.h"
#include "WorldCoreDefine.h"

//#include "FightManager.h"
/******************************************************************************/

namespace MG
{

	//--------------------------------------------------------------------------

	Str CAIEntityHateDetect::STATE_NAME = "CAIEntityHateDetect";

	//--------------------------------------------------------------------------
	CAIEntityHateDetect::CAIEntityHateDetect( CCharacterSceneEntity* characterSceneEntity )
		:LinedStateObject(STATE_NAME)
		,CAI(characterSceneEntity)
		,mIsMoveTo(true)
		,mPauseThinkTime(0)
		,mHateRatio(0)
		,mCurrTargetType(GOT_UNKNOWN)
		,mCurrTargetId(0)
		,mCurrTargetIndex(0)
	{
		mAIType = AIT_HATEDETECT;
	}

	//--------------------------------------------------------------------------
	CAIEntityHateDetect::~CAIEntityHateDetect()
	{

	}

	//-----------------------------------------------------------------------
	void CAIEntityHateDetect::onEnter()
	{
		if(mOwner->getDynamicData()->isDied)
		{
			destroy();
			return;
		}
	}

	//-----------------------------------------------------------------------
	void CAIEntityHateDetect::update( Flt delta )
	{
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
			return;
		}

		mPauseThinkTime = 1;
	}

	//-----------------------------------------------------------------------
	void CAIEntityHateDetect::onLeave()
	{
		notifyEnd();
	}

	//-----------------------------------------------------------------------
	Bool CAIEntityHateDetect::isFinished()
	{
		return false;
	}

	//-----------------------------------------------------------------------
	void CAIEntityHateDetect::notifyReturnFinish()
	{
		if(mAIListener)
		{
			mAIListener->onReturnFinish();
		}
	}

	//-----------------------------------------------------------------------

	void CAIEntityHateDetect::setIsMoveTo( Bool isMoveTo )
	{
		mIsMoveTo = isMoveTo;
	}

	//-----------------------------------------------------------------------
	void CAIEntityHateDetect::setReturnToPos( Vec3 pos )
	{
		mReturnPos = pos;
	}

	//-----------------------------------------------------------------------
	Bool CAIEntityHateDetect::getTargetByHate( GAMEOBJ_TYPE& targetType, IdType& targetId, UInt& targetIndex )
	{
		//targetType = GOT_UNKNOWN;
		//targetId = 0;
		//targetIndex = 0;

		//FightManager* fightManager = NULL;
		//if(mOwner->getType() == GOT_SOLDIER)
		//{
		//	fightManager = ((CTroopSoldierEntity*)mOwner)->getTroopEntity()->getFightManager();
		//}
		//else
		//{
		//	fightManager = mOwner->getFightManager();
		//}

		//if(!fightManager)
		//{
		//	return false;
		//}

		//IdType fightID = 

		//FightInfo*  fightInfo = fightManager->getFightInfo(mCurrTargetType, mCurrTargetId);
		//if(!fightInfo)
		//{
		//	return false;
		//}

		//Flt currTargetHateVal =  fightInfo->hateVal * (mHateRatio / 100);

		//UInt tempHateVal = 0;
		//GAMEOBJ_TYPE tempType = GOT_UNKNOWN;
		//IdType tempId = 0;

		//std::map<IdType, FightInfo>* fightInfoList = fightManager->getFightInfoList();
		//if(!fightInfoList)
		//{
		//	return false;
		//}

		//for(std::map<IdType, FightInfo>::iterator it = fightInfoList->begin(); it != fightInfoList->end(); ++it)
		//{
		//	if(it->second.hateVal > currTargetHateVal)
		//	{
		//		tempHateVal = it->second.hateVal;
		//		tempType = it->second.fightObject->getType();
		//		tempId = it->second.fightObjectID;
		//	}
		//}

		//if(tempType == GOT_UNKNOWN || tempHateVal == 0)
		//{
		//	return false;
		//}

		//if(tempType == GOT_SOLDIER)
		//{
		//	Flt tempDis = 0;
		//	Flt minDis = 0;
		//	Int tempIndex = -1;

		//	CTroopObject* troopObject = CSceneManager::getInstance().getTroopObject(tempId);
		//	if(!troopObject)
		//	{
		//		return false;
		//	}

		//	CTroopSoldierEntity*  troopSoldier = NULL;
		//	for(UInt i = 0; i < troopObject->getSoldierEntitysNum(); ++i)
		//	{
		//		troopSoldier = troopObject->getSoldierEntitys(i);
		//		tempDis = (troopSoldier->getPos() - mOwner->getPos()).length();

		//		if(minDis > tempDis || i == 0)
		//		{
		//			minDis = tempDis;
		//			tempIndex = i;
		//		}
		//	}

		//	if(tempIndex == -1)
		//	{
		//		return false;
		//	}

		//	targetType = tempType;
		//	targetId = tempId;
		//	targetIndex = tempIndex;
		//}
		//else
		//{
		//	CCharacterSceneEntity* targetCharacter = CSceneManager::getInstance().getCharacterSceneEntity(tempType, tempId);
		//	if(!targetCharacter)
		//	{
		//		return false;
		//	}

		//	targetType = tempType;
		//	targetId = tempId;
		//	targetIndex = 0;
		//}

		return false;
	}

	//-----------------------------------------------------------------------
	void CAIEntityHateDetect::setHateRatio( Bool hateRatio )
	{
		mHateRatio = hateRatio;
	}

	//-----------------------------------------------------------------------
	void CAIEntityHateDetect::setCurrTarget( GAMEOBJ_TYPE currTargetType, IdType currTargetId, UInt currTargetIndex )
	{
		mCurrTargetType = currTargetType;
		mCurrTargetId = currTargetId;
		mCurrTargetIndex = currTargetIndex;
	}



}