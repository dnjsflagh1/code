/******************************************************************************/
#include "stdafx.h"
#include "SAIController.h"
#include "SAIGuard.h"
#include "SCharacter.h"
#include "SWorldManager.h"
#include "STroop.h"
#include "WorldCoreDefine.h"
#include "FightInfo.h"
#include "SFightMainManager.h"

//#include "FightManager.h"
/******************************************************************************/

namespace MG
{

    //--------------------------------------------------------------------------

    Str SAIGuard::STATE_NAME = "SAIGuard";

    //--------------------------------------------------------------------------
    SAIGuard::SAIGuard( SCharacter* owner )
        :LinedStateObject(STATE_NAME)
		,SAI(owner)
		,mGuardRadius(5)
		,mGuardIntervalTime(0)
		,mAssaultableClant(0)
		,mAssaultableChar(0)
		,mPauseThinkTime(0)
    {
		mAIType = AIT_GUARD;
    }

    //--------------------------------------------------------------------------
    SAIGuard::~SAIGuard()
    {
    }

	//-----------------------------------------------------------------------
	void SAIGuard::onEnter()
	{
		if(mOwner->isDead())
		{
			destroy();
			return;
		}
	}

	//-----------------------------------------------------------------------
	void SAIGuard::update( Flt delta )
	{
		if(mPauseThinkTime > 0)
		{
			mPauseThinkTime -= delta;
			return;
		}

		if(mOwner->isDead())
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
	void SAIGuard::onLeave()
	{
		notifyEnd();
	}

    //-----------------------------------------------------------------------
    Bool SAIGuard::isFinished()
    {
        return false;
    }

	//-----------------------------------------------------------------------
	Bool SAIGuard::getTargetBySearch( GAMEOBJ_TYPE& targetType, IdType& targetId, UInt& targetIndex )
	{
		targetType = GOT_UNKNOWN;
		targetId = 0;
		targetIndex = 0;

		//SRegionObjectBase* regionObject = mOwner->getCurrentRegionObject();
		//if(!regionObject)
		//{
		//	destroy();
		//	return false;
		//}

		Vec3 ownerPos = mOwner->getPos();

		Flt minDis = 0;
		Flt tempDis = 0;

		SCharacter* tempCharacter = NULL;
		SCharacter* minDisCharacter = NULL;

		std::map<PlayerCharacterIdType, SCharacter*>* playercharacterList = 0;//regionObject->getPlayerCharacterList();
		if(playercharacterList)
		{
			for(std::map<PlayerCharacterIdType, SCharacter*>::iterator it = playercharacterList->begin(); it != playercharacterList->end(); ++it)
			{
				tempCharacter = it->second;
				if(!tempCharacter || tempCharacter->isDead())
				{
					continue;
				}

				tempDis = (tempCharacter->getPos() - ownerPos).length();
				if(tempDis <= mGuardRadius && (minDis == 0 || tempDis < minDis))
				{
					minDis = tempDis;
					minDisCharacter = tempCharacter;
				}
			}
		}

		if(minDisCharacter)
		{
			targetType = minDisCharacter->getType();
			targetId = minDisCharacter->getID();
			targetIndex = 0;

			SFightMainManager::getInstance().addAndUpdateFightOnGuard(mOwner, minDisCharacter);

			return true;
		}

		//ISceneObjectCollisionCallback callback;
		//callback.isCheckQueryFlagsMask = true;
		//callback.isCheckSingle = false;
		//callback.queryFlagsMask = GOT_TROOP | GOT_SOLDIER | GOT_PLAYERCHARACTER | GOT_MONSTER;
		//Vec3 ownerPos = mCharacterSceneEntity->getPos();
		//RectF rect(ownerPos.x - mGuardRadius, ownerPos.x + mGuardRadius, ownerPos.z + mGuardRadius, ownerPos.z - mGuardRadius);
		//ClientMain::getInstance().getScene()->getCollisionSystem()->checkRectCollision(rect, &callback);

		//ILogicBinder* logicBinder = NULL;
		//ISceneObject* sceneObject = NULL;
		//CCharacterSceneEntity* characterSceneEntity = NULL;
		//CCharacterSceneEntity* targetCharacterSceneEntity = NULL;
		//Flt minDis = 0;
		//Flt tempDis = 0;
		//Vec3 targetPos;

		//for(UInt i = 0; i < callback.collisionList.size(); ++i)
		//{
		//	sceneObject = callback.collisionList[i].second;
		//	if(!sceneObject)
		//	{
		//		continue;
		//	}

		//	logicBinder = sceneObject->getLogicBinder();

		//	if(!logicBinder || !logicBinder->manager)
		//	{
		//		continue;
		//	}

		//	characterSceneEntity = (CCharacterSceneEntity*)logicBinder->manager;

		//	if(mCharacterSceneEntity->getDynamicData()->force == characterSceneEntity->getDynamicData()->force)
		//	{
		//		continue;
		//	}

		//	if(characterSceneEntity == mCharacterSceneEntity)//²âÊÔÓÃ
		//	{
		//		continue;
		//	}

		//	targetPos = characterSceneEntity->getPos();

		//	tempDis = (targetPos - ownerPos).length();
		//	if(minDis == 0 || minDis >  tempDis)
		//	{
		//		minDis = tempDis;
		//		targetCharacterSceneEntity = characterSceneEntity;
		//	}
		//}

		//if(targetCharacterSceneEntity)
		//{
		//	targetType = targetCharacterSceneEntity->getType();

		//	if(targetType != GOT_SOLDIER)
		//	{
		//		targetId = targetCharacterSceneEntity->getID();
		//		targetIndex = 0;
		//	}
		//	else
		//	{
		//		targetId = ((CTroopSoldierEntity*)targetCharacterSceneEntity)->getTroopEntity()->getID();
		//		targetIndex = targetCharacterSceneEntity->getID();
		//	}

		//	return true;
		//}

		return false;
	}

	//-----------------------------------------------------------------------
	void SAIGuard::notifySearchTarget(  GAMEOBJ_TYPE targetType, IdType targetId, UInt targetIndex )
	{
		if(mAIListener)
		{
			mAIListener->onSearchTarget(targetType, targetId, targetIndex);
		}
	}

	//-----------------------------------------------------------------------

	void SAIGuard::setAIParam( Flt guardIntervalTime, Flt guardRadius, UInt assaultableClant, UInt assaultableChar )
	{
		mGuardIntervalTime = guardIntervalTime / 1000;
		mGuardRadius = guardRadius;
		mAssaultableClant = assaultableClant;
		mAssaultableChar = assaultableChar;
	}
	
}