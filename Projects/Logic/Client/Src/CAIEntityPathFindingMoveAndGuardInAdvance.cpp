/******************************************************************************/
#include "stdafx.h"
#include "CAIEntityPathFindingMoveAndGuardInAdvance.h"
#include "ICollisionSystem.h"
#include "CCharacterSceneEntity.h"
#include "ClientMain.h"
#include "CSceneManager.h"
#include "CTroopSoldierEntity.h"
#include "CTroopEntity.h"
#include "CPlayer.h"
/******************************************************************************/

namespace MG
{

    //--------------------------------------------------------------------------

    Str CAIEntityPathFindingMoveAndGuardInAdvance::STATE_NAME = "CAIEntityPathFindingMoveAndGuardInAdvance";

    //--------------------------------------------------------------------------
    CAIEntityPathFindingMoveAndGuardInAdvance::CAIEntityPathFindingMoveAndGuardInAdvance( CCharacterSceneEntity* characterSceneEntity )
        :LinedStateObject(STATE_NAME)
		,mCharacterSceneEntity(characterSceneEntity)
		,mTargetType(GOT_UNKNOWN)
		,mTargetId(0)
		,mTargetIndex(0)
		,mGuardRadius(0)
		,mPursueRadius(0)
		,mViewRadius(0)
		,mState(MAGAS_NULL)
		,mPauseThinkTime(0)
    {

    }

    //--------------------------------------------------------------------------
    CAIEntityPathFindingMoveAndGuardInAdvance::~CAIEntityPathFindingMoveAndGuardInAdvance()
    {

    }

    //-----------------------------------------------------------------------
    void CAIEntityPathFindingMoveAndGuardInAdvance::update( Flt delta )
    {

		if(mCharacterSceneEntity->getDynamicData()->isDied)
		{
			return;
		}

		switch(mState)
		{
		case MAGAS_MOVE:
			updateMoveTo(delta);
			break;

		case MAGAS_SEARCH:
			updateSearch(delta);
			break;

		case MAGAS_PURSUEATTACK:
			updatePursueAttack(delta);
			break;
		}

		stopThink(5);

    }

    //-----------------------------------------------------------------------
    Bool CAIEntityPathFindingMoveAndGuardInAdvance::isFinished()
    {
		Vec3 currPos = mCharacterSceneEntity->getPos();
		if((currPos - mDestination).length() <= 1)
		{
			return true;	
		}

        return false;
    }

    //-----------------------------------------------------------------------
    void CAIEntityPathFindingMoveAndGuardInAdvance::onEnter()
    {
		if(mCharacterSceneEntity->getDynamicData()->isDied)
		{
			destroy();
			return;
		}

		CAIEntityPathFindingMoveInAdvance* pathFindingMoveInAdvanceAI = CAIManager::getInstance().createCAIEntityPathFindingMoveInAdvance(mCharacterSceneEntity); 
		pathFindingMoveInAdvanceAI->setDestination(mDestination);

		mCharacterSceneEntity->getAIStateManager().push(pathFindingMoveInAdvanceAI);

		if(mCharacterSceneEntity->getType() == GOT_SOLDIER)
		{
			CTroopEntity* troopObject = ((CTroopSoldierEntity*)mCharacterSceneEntity)->getTroopEntity();
			if(!troopObject)
			{
				return;
			}

			mViewRadius = troopObject->getCAttributeSystem()->getViewRange();
			troopObject->getFightManager()->addListener(this);
		}
		else if(mCharacterSceneEntity->getType() == GOT_PLAYERCHARACTER)
		{
			CPlayerCharacter* playerCharacter = CPlayer::getInstance().getPlayerCharacter(mCharacterSceneEntity->getID());
			if(!playerCharacter)
			{
				return;
			}

			mViewRadius = playerCharacter->getAttributeSystem()->getViewRange();
			//mCharacterSceneEntity->getFightManager()->addListener(this);
		}
		else
		{
			mViewRadius = mGuardRadius;
			//mCharacterSceneEntity->getFightManager()->addListener(this);
		}

		mState = MAGAS_MOVE;
    }

    //-----------------------------------------------------------------------
    void CAIEntityPathFindingMoveAndGuardInAdvance::onLeave()
    {
		mCharacterSceneEntity->getAIStateManager().removeState(CAIEntityPathFindingPursueAttackInAdvance::STATE_NAME, false);
		mCharacterSceneEntity->getAIStateManager().removeState(CAIEntityPathFindingMoveInAdvance::STATE_NAME, false);

		//if(mCharacterSceneEntity->getType() == GOT_SOLDIER)
		//{
		//	CTroopObject* troopObject = ((CTroopSoldierEntity*)mCharacterSceneEntity)->getTroopEntity();
		//	if(!troopObject)
		//	{
		//		return;
		//	}
		//	//troopObject->getFightManager()->removeListener(this);
		//}
		//else
		//{
		//	//mCharacterSceneEntity->getFightManager()->removeListener(this);
		//}
    }

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingMoveAndGuardInAdvance::setDestination( Vec3 pos )
	{
		mDestination = pos;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//-----------------------------------------------------------------------
	void CAIEntityPathFindingMoveAndGuardInAdvance::startPursueAndAttack( GAMEOBJ_TYPE targetType, IdType targetId, UInt targetIndex )
	{
		notifyTroopPursueAndAttack(targetType, targetId, targetIndex);
		pursueAndAttack(targetType, targetId, targetIndex);

		mState = MAGAS_PURSUEATTACK;
	}

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingMoveAndGuardInAdvance::notifyTroopPursueAndAttack( GAMEOBJ_TYPE targetType, IdType targetId, UInt targetIndex )
	{
		if(mCharacterSceneEntity->getType() == GOT_SOLDIER)
		{
			CTroopEntity* troopObject = ((CTroopSoldierEntity*)mCharacterSceneEntity)->getTroopEntity();
			CTroopSoldierEntity* troopSoldierEntity = NULL;
			for(UInt i = 0; i < troopObject->getSoldierEntitysNum(); ++i)
			{
				troopSoldierEntity = troopObject->getSoldierEntitysByIndex(i);
				if(!troopSoldierEntity)
				{
					continue;
				}

				if( mCharacterSceneEntity != troopSoldierEntity )
				{
					CAIEntityPathFindingMoveAndGuardInAdvance* moveAndGuardInAdvance = (CAIEntityPathFindingMoveAndGuardInAdvance*)troopSoldierEntity->getAIStateManager().getState(CAIEntityPathFindingMoveAndGuardInAdvance::mName, false);
					if(moveAndGuardInAdvance)
					{
						moveAndGuardInAdvance->setTarget(targetType, targetId, targetIndex);
						moveAndGuardInAdvance->pursueAndAttack(targetType, targetId, targetIndex);
						moveAndGuardInAdvance->setState(MAGAS_PURSUEATTACK);
					}
				}
			}
		}
	}

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingMoveAndGuardInAdvance::pursueAndAttack( GAMEOBJ_TYPE targetType, IdType targetId, UInt targetIndex )
	{
		mCharacterSceneEntity->getAIStateManager().removeState(CAIEntityPathFindingMoveInAdvance::STATE_NAME, false);

		CAIEntityPathFindingPursueAttackInAdvance* pursueAttackInAdvanceAI = CAIManager::getInstance().createCAIEntityPathFindingPursueAttackInAdvance(mCharacterSceneEntity); 
		pursueAttackInAdvanceAI->setTarget(targetType, targetId, targetIndex);
		pursueAttackInAdvanceAI->setUseSkillId(0);

		mCharacterSceneEntity->getAIStateManager().push(pursueAttackInAdvanceAI, false);
	}

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingMoveAndGuardInAdvance::endPursueAndAttack()
	{
		mTargetType = GOT_UNKNOWN;
		mTargetId = 0;
		mTargetIndex = 0;

		mCharacterSceneEntity->getAIStateManager().removeState(CAIEntityPathFindingPursueAttackInAdvance::STATE_NAME, false);
		mState = MAGAS_MOVE;
	}

	//-----------------------------------------------------------------------
	Bool CAIEntityPathFindingMoveAndGuardInAdvance::getTargetBySearch( GAMEOBJ_TYPE& targetType, IdType& targetId, UInt& targetIndex )
	{
		targetType = GOT_UNKNOWN;
		targetId = 0;
		targetIndex = 0;

		ISceneObjectCollisionCallback callback;
		callback.isCheckQueryFlagsMask = true;
		callback.isCheckSingle = false;
		callback.queryFlagsMask = GQT_TROOP | GQT_SOLDIER | GQT_PLAYERCHARACTER | GQT_MONSTER;
		Vec3 ownerPos = mCharacterSceneEntity->getPos();
		RectF rect(ownerPos.x - mGuardRadius, ownerPos.x + mGuardRadius, ownerPos.z + mGuardRadius, ownerPos.z - mGuardRadius);
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

			if(mCharacterSceneEntity->getDynamicData()->force == characterSceneEntity->getDynamicData()->force)
			{
				continue;
			}

			if(characterSceneEntity == mCharacterSceneEntity)//²âÊÔÓÃ
			{
				continue;
			}

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

			if(mTargetType != GOT_SOLDIER)
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
	Bool CAIEntityPathFindingMoveAndGuardInAdvance::getTargetByHate( GAMEOBJ_TYPE& targetType, IdType& targetId, UInt& targetIndex )
	{
		targetType = GOT_UNKNOWN;
		targetId = 0;
		targetIndex = 0;

		//FightManager* fightManager = NULL;
		//if(mCharacterSceneEntity->getType() == GOT_SOLDIER)
		//{
		//	fightManager = ((CTroopSoldierEntity*)mCharacterSceneEntity)->getTroopEntity()->getFightManager();
		//}
		//else
		//{
		//	fightManager = mCharacterSceneEntity->getFightManager();
		//}

		//if(!fightManager)
		//{
		//	return false;
		//}

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
		//	if(it->second.hateVal > tempHateVal)
		//	{
		//		tempHateVal = it->second.hateVal;
		//		tempType = it->second.fightObject->getType();
		//		tempId = it->second.fightObject->getID();
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
		//		tempDis = (troopSoldier->getPos() - mCharacterSceneEntity->getPos()).length();

		//		if(tempDis > mPursueRadius)
		//		{
		//			continue;
		//		}

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

		//	Flt dis = (targetCharacter->getPos() - mCharacterSceneEntity->getPos()).length();
		//	if(dis > mPursueRadius)
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
	void CAIEntityPathFindingMoveAndGuardInAdvance::updateSearch(Flt delta)
	{
		GAMEOBJ_TYPE tempType = GOT_UNKNOWN;
		IdType tempId = 0;
		UInt tempIndex = 0;

		if(getTargetByHate(tempType, tempId, tempIndex))
		{
			mTargetType = tempType;
			mTargetId = tempId;
			mTargetIndex = tempIndex;
		}
		else if(getTargetBySearch(tempType, tempId, tempIndex))
		{
			mTargetType = tempType;
			mTargetId = tempId;
			mTargetIndex = tempIndex;
		}
		else
		{
			return;
		}



		startPursueAndAttack(mTargetType, mTargetId, mTargetIndex);
	}

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingMoveAndGuardInAdvance::updatePursueAttack( Flt delta )
	{
		if(!mCharacterSceneEntity->getAIStateManager().getState(CAIEntityPathFindingPursueAttackInAdvance::STATE_NAME, false))
		{
			endPursueAndAttack();
		}

		CCharacterSceneEntity* targetCharacterSceneEntity = CSceneManager::getInstance().getCharacterSceneEntity(mTargetType, mTargetId, mTargetIndex);
		if(!targetCharacterSceneEntity || targetCharacterSceneEntity->getDynamicData()->isDied)
		{
			endPursueAndAttack();
			return;
		}

		Vec3 ownerPos = mCharacterSceneEntity->getPos();
		Vec3 targetPos = targetCharacterSceneEntity->getPos();
		if((targetPos - ownerPos).length() > mPursueRadius || (targetPos - ownerPos).length() > mViewRadius)
		{
			endPursueAndAttack();
			return;
		}

	}

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingMoveAndGuardInAdvance::updateMoveTo( Flt delta )
	{
		CAIEntityPathFindingMoveInAdvance* pathFindingMoveInAdvanceAI = CAIManager::getInstance().createCAIEntityPathFindingMoveInAdvance(mCharacterSceneEntity); 
		pathFindingMoveInAdvanceAI->setDestination(mDestination);

		mCharacterSceneEntity->getAIStateManager().push(pathFindingMoveInAdvanceAI);

		mState = MAGAS_SEARCH;
	}

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingMoveAndGuardInAdvance::setTarget( GAMEOBJ_TYPE targetType, IdType targetId, UInt targetIndex )
	{
		mTargetType = targetType;
		mTargetId = targetId;
		mTargetIndex = targetIndex;
	}

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingMoveAndGuardInAdvance::onFightInfoChanged( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID )
	{
		if(fightObjectType == mTargetType && fightObjectID == mTargetId)
		{
			return;
		}

		mState = MAGAS_SEARCH;
	}

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingMoveAndGuardInAdvance::setState( MoveAndGuardAIState state )
	{
		mState = state;
	}

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingMoveAndGuardInAdvance::stopThink( Flt time )
	{
		mPauseThinkTime = time;
	}

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingMoveAndGuardInAdvance::resumeThink()
	{
		mPauseThinkTime = 0;
	}

}