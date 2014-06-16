/******************************************************************************/
#include "stdafx.h"
#include "CAIController.h"
#include "CAIEntityGuard.h"
#include "ICollisionSystem.h"
#include "CCharacterSceneEntity.h"
#include "ClientMain.h"
#include "CSceneManager.h"
#include "CTroopSoldierEntity.h"
#include "CTroopEntity.h"
#include "CPlayer.h"
#include "WorldCoreDefine.h"
#include "FightInfo.h"

//#include "FightManager.h"
/******************************************************************************/

namespace MG
{

    //--------------------------------------------------------------------------

    Str CAIEntityGuard::STATE_NAME = "CAIEntityGuardInAdvance";

    //--------------------------------------------------------------------------
    CAIEntityGuard::CAIEntityGuard( CCharacterSceneEntity* characterSceneEntity )
        :LinedStateObject(STATE_NAME)
		,CAI(characterSceneEntity)
		,mGuardRadius(5)
		,mGuardIntervalTime(0)
		,mAssaultableClant(0)
		,mAssaultableChar(0)
		,mPauseThinkTime(0)
    {
		mAIType = AIT_GUARD;
    }

    //--------------------------------------------------------------------------
    CAIEntityGuard::~CAIEntityGuard()
    {

    }

	//-----------------------------------------------------------------------
	void CAIEntityGuard::onEnter()
	{
		if(mOwner->getDynamicData()->isDied)
		{
			destroy();
			return;
		}

		mGuardRadius = mOwner->getEntity()->getModelObject()->getPatherRadius() * 2 + mGuardRadius;
	}

	//-----------------------------------------------------------------------
	void CAIEntityGuard::update( Flt delta )
	{
		if(mPauseThinkTime > 0)
		{
			mPauseThinkTime -= delta;
			return;
		}

		if(mOwner->getDynamicData()->isDied)
		{
			return;
		}

		GAMEOBJ_TYPE tempType = GOT_UNKNOWN;
		IdType tempId = 0;
		UInt tempIndex = 0;

		if(getTargetBySearch(tempType, tempId, tempIndex))
		{
			notifySearchTarget(tempType, tempId, tempIndex);
			destroy();
			return;
		}

		mPauseThinkTime = mGuardIntervalTime;
	}

	//-----------------------------------------------------------------------
	void CAIEntityGuard::onLeave()
	{
		notifyEnd();
	}

    //-----------------------------------------------------------------------
    Bool CAIEntityGuard::isFinished()
    {
        return false;
    }

	//-----------------------------------------------------------------------
	Bool CAIEntityGuard::getTargetBySearch( GAMEOBJ_TYPE& targetType, IdType& targetId, UInt& targetIndex )
	{
		targetType = GOT_UNKNOWN;
		targetId = 0;
		targetIndex = 0;

		ISceneObjectCollisionCallback callback;
		callback.isCheckQueryFlagsMask = true;
		callback.isCheckSingle = false;
		callback.queryFlagsMask = GQT_TROOP | GQT_SOLDIER | GQT_PLAYERCHARACTER | GQT_MONSTER;
		Vec3 ownerPos = mOwner->getPos();
		RectF rect(ownerPos.x - mGuardRadius, ownerPos.x + mGuardRadius, ownerPos.z - mGuardRadius, ownerPos.z + mGuardRadius);
		ClientMain::getInstance().getScene()->getCollisionSystem()->checkRectCollision(rect, &callback);

		ILogicBinder* logicBinder = NULL;
		ISceneObject* sceneObject = NULL;
		CCharacterSceneEntity* characterSceneEntity = NULL;
		CCharacterSceneEntity* targetCharacterSceneEntity = NULL;
		Flt minDis = 0;
		Flt tempDis = 0;
		Vec3 targetPos;

		for(UInt i = 0; i < callback.collisionList.size(); ++i)
		{
			sceneObject = callback.collisionList[i].second;
			if(!sceneObject)
			{
				continue;
			}

			logicBinder = sceneObject->getLogicBinder();

			if(!logicBinder || !logicBinder->manager)
			{
				continue;
			}

			characterSceneEntity = (CCharacterSceneEntity*)logicBinder->manager;

			if(mOwner->getDynamicData()->force == characterSceneEntity->getDynamicData()->force)
			{
				continue;
			}

			//if(characterSceneEntity->getType() == GOT_SOLDIER && ((CTroopSoldierEntity*)characterSceneEntity)->getTroopEntity()->getID() == mOwner->getID())
			//{
			//	continue;
			//}

			//if(characterSceneEntity == mOwner)//²âÊÔÓÃ
			//{
			//	continue;
			//}

			targetPos = characterSceneEntity->getPos();

			tempDis = (targetPos - ownerPos).length();
			if(minDis == 0 || minDis >  tempDis)
			{
				minDis = tempDis;
				targetCharacterSceneEntity = characterSceneEntity;
			}
		}

		if(targetCharacterSceneEntity)
		{
			targetType = targetCharacterSceneEntity->getType();

			if(targetType != GOT_SOLDIER)
			{
				targetId = targetCharacterSceneEntity->getID();
				targetIndex = 0;
			}
			else
			{
				targetId = ((CTroopSoldierEntity*)targetCharacterSceneEntity)->getTroopEntity()->getID();
				targetIndex = targetCharacterSceneEntity->getID();
			}

			return true;
		}

		return false;
	}

	//-----------------------------------------------------------------------
	void CAIEntityGuard::notifySearchTarget(  GAMEOBJ_TYPE targetType, IdType targetId, UInt targetIndex )
	{
		if(mAIListener)
		{
			mAIListener->onSearchTarget(targetType, targetId, targetIndex);
		}
	}

	//-----------------------------------------------------------------------

	void CAIEntityGuard::setAIParam( Flt guardIntervalTime, Flt guardRadius, UInt assaultableClant, UInt assaultableChar )
	{
		mGuardIntervalTime = guardIntervalTime / 1000;
		mGuardRadius = guardRadius;
		mAssaultableClant = assaultableClant;
		mAssaultableChar = assaultableChar;
	}
	
}