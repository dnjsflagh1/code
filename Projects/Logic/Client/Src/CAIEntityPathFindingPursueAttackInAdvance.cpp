/******************************************************************************/
#include "stdafx.h"
#include "CAIEntityPathFindingPursueAttackInAdvance.h"
#include "CSceneManager.h"
#include "CCharacterSceneEntity.h"
#include "SkillBaseInfo.h"
#include "CSkillUseManager.h"
#include "SkillNetPacketProcesser.h"
#include "SkillInfoList.h"
#include "ShortRangeGeneralAttackSkillTemplate.h"
#include "LongRangeGeneralAttackSkillTemplate.h"
#include "SingleTargetSkillTemplate.h"
#include "CAIManager.h"
#include "IBlockManager.h"
#include "ClientMain.h"
#include "CAITroopObjectSendSkillPacket.h"
#include "CTroopSoldierEntity.h"
#include "CTroopEntity.h"
#include "CharacterSkillTempLate.h"
#include "SkillBaseInfo.h"
#include "CPlayer.h"
#include "CSkillOwnManager.h"
#include "CharacterList.h"
#include "PlayCharacterNetPacketProcesser.h"
#include "CActionManager.h"
#include "TroopNetPacketProcesser.h"
/******************************************************************************/

namespace MG
{

    //--------------------------------------------------------------------------

    Str CAIEntityPathFindingPursueAttackInAdvance::STATE_NAME = "CAIEntityPathFindingPursueAttackInAdvance";

    //--------------------------------------------------------------------------
    CAIEntityPathFindingPursueAttackInAdvance::CAIEntityPathFindingPursueAttackInAdvance( CCharacterSceneEntity* characterSceneEntity )
        :LinedStateObject(STATE_NAME)
		,mCharacterSceneEntity(characterSceneEntity)
		,mTargetId(0)
		,mTargetIndex(0)
		,mTargetType(GOT_UNKNOWN)
		,mSkillId(0)
		,mPathFindingMoveAI(0)
		,mIsFinished(false)
		,mSkillInfo(NULL)
		,mSkillObject(NULL)
		,mAIEntityGroup(NULL)
		,mIsLoopAttack(false)
		,mIsSelectTargetObject(false)
		,mPauseThinkTime(0)
		,mPausePursueThinkTime(0)
		,mState(PAS_ATTACK)
		,mAttackRange(0)
    {

    }

    //--------------------------------------------------------------------------
    CAIEntityPathFindingPursueAttackInAdvance::~CAIEntityPathFindingPursueAttackInAdvance()
    {

    }

    //-----------------------------------------------------------------------
    void CAIEntityPathFindingPursueAttackInAdvance::update( Flt delta )
    {
		if(mPauseThinkTime > 0)
		{
			mPauseThinkTime -= delta;
			return;
		}

		switch(mState)
		{
		case PAS_PURSUE:
			updatePursue(delta);
			break;

		case PAS_ATTACK:
			updateAttack(delta);
			break;
		}

    }				 

    //-----------------------------------------------------------------------
    Bool CAIEntityPathFindingPursueAttackInAdvance::isFinished()
    {
        return mIsFinished;
    }

    //-----------------------------------------------------------------------
    void CAIEntityPathFindingPursueAttackInAdvance::onEnter()
    {
		//mCharacterSceneEntity->getDynamicData()->isFightState = true;

		if(mCharacterSceneEntity->getDynamicData()->isDied)
		{
			destroy();
			return;
		}

		//如果mSkillId == 0使用默认技能
		if(mSkillId == 0)
		{
			mSkillId = getDefaultSkill();
		}

		mSkillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(mSkillId);
		if(!mSkillInfo)
		{
			destroy();
			return;
		}
		
		////重新选择目标
		//if(mIsSelectTargetObject)
		//{
		//	selectTargetObject();
		//}
		
		//如果目标是object
		if(mTargetId != 0)
		{
			CCharacterSceneEntity* targetEntity = CSceneManager::getInstance().getCharacterSceneEntity(mTargetType, mTargetId, mTargetIndex);
			if(!targetEntity)
			{
				destroy();
				return;
			}

			if(!isAttack(mCharacterSceneEntity, targetEntity))
			{
				destroy();
				return;
			}

			targetEntity->getEntity()->getSceneNode()->getPosition(mTargetPos);
		}

		//设置技能的skillobject
		mSkillObject = (CSkillObject*)mCharacterSceneEntity->getSkillUseManager()->prepareUseSkill(mSkillId);
		if(!mSkillObject)
		{	
			destroy();
			return;
		}

		if(mTargetId != 0)
		{
			mSkillObject->setTargetObject(mTargetType, mTargetId, mTargetIndex);
		}
		else
		{
			mSkillObject->setTargetPosition(mTargetPos);
		}

		//设置技能的间隔时间
		if(mSkillInfo->skillType == SKT_SHORTRANGEGENERAL || mSkillInfo->skillType == SKT_LONGRANGEGENERAL)
		{
			mAttackIntervalTime = ((Flt)(((InitiativeSkillBasicInfo*)mSkillInfo->skillInfo)->attackFrontTime + ((InitiativeSkillBasicInfo*)mSkillInfo->skillInfo)->attackBehindTime)) /*/ 1000*/;
			mIsLoopAttack = true;
		}
		else if(mIsLoopAttack)
		{
			mAttackIntervalTime = ((Flt)(((InitiativeSkillBasicInfo*)mSkillInfo->skillInfo)->publicTimepieceDelay)) / 1000 + 0.5;
		}

		mMoveToPos = mTargetPos;
		mMoveToPos.y = 0;

		Flt patherRadius = mCharacterSceneEntity->getEntity()->getModelObject()->getPatherRadius();
		// 通过半径计算出所占用网格大小
		mBlockDiameter = patherRadius * 2 / ClientMain::getInstance().getScene()->getBlockManager()->getDynamicBlockGridSize();

		mAttackRange = getAttackRange();
    }

    //-----------------------------------------------------------------------
    void CAIEntityPathFindingPursueAttackInAdvance::onLeave()
    {
        //mCharacterSceneEntity->getDynamicData()->isFightState = false;
		if(mCharacterSceneEntity->getType() == GOT_TROOP)
		{
			((CTroopEntity*)mCharacterSceneEntity)->stopAttack();
		}
    }

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingPursueAttackInAdvance::setTarget(GAMEOBJ_TYPE gameType, GameObjectIdType id, UInt index)
	{
		mTargetType = gameType;
		mTargetId = id;
		mTargetIndex = index;

		if(mCharacterSceneEntity->getType() == GOT_SOLDIER && mTargetType == GOT_SOLDIER)
		{
			((CTroopSoldierEntity*)mCharacterSceneEntity)->setTarget(mTargetType, mTargetId, mTargetIndex);
		}
	}

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingPursueAttackInAdvance::setTarget(Vec3 pos)
	{
		mTargetPos = pos;
	}

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingPursueAttackInAdvance::setUseSkillId(IdType skillId)
	{
		mSkillId = skillId;
	}

	//-----------------------------------------------------------------------
	IdType CAIEntityPathFindingPursueAttackInAdvance::getDefaultSkill()
	{
		if(mCharacterSceneEntity->getType() == GOT_PLAYERCHARACTER)
		{
			CPlayerCharacter* playerCharacter = CPlayer::getInstance().getPlayerCharacter(mCharacterSceneEntity->getID());
			if(!playerCharacter)
			{
				return 0;
			}
			
			CSkillOwnManager* skillOwnManager = playerCharacter->getSkillOwnManager();
			if(!skillOwnManager)
			{
				return 0;
			}

			return skillOwnManager->getDefaultSkill();
		}
		else
		{
			UInt characterTemplateId = 0;

			if(mCharacterSceneEntity->getType() == GOT_TROOP)
			{
				characterTemplateId = mCharacterSceneEntity->getDynamicData()->mCharacterTemplateID;
			}
			else if(mCharacterSceneEntity->getType() == GOT_SOLDIER)
			{
				characterTemplateId = ((CTroopSoldierEntity*)mCharacterSceneEntity)->getTroopEntity()->getDynamicData()->mCharacterTemplateID;
			}
			else if(mCharacterSceneEntity->getType() == GOT_MONSTER)
			{
				characterTemplateId = mCharacterSceneEntity->getDynamicData()->mCharacterTemplateID;
			}

			const CharacterTempInfo* characterTempInfo = CharacterTemplate::getInstance().getCharacterTempInfo(characterTemplateId);
			if(!characterTempInfo)
			{
				return 0;
			}

			CharSkillInfo* charSkillInfo = (CharSkillInfo*)CharacterSkillTemplate::getInstance().getCharSkillInfo(characterTempInfo->getCharacterCharacterSkillId(0));
			if(!charSkillInfo)
			{
				return 0;
			}

			SkillInfo* skillInfo = NULL;
			for(UInt i = 0; i < CHAR_SKILL_NUM; ++i)
			{
				skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(charSkillInfo->CharSkillList[i]);
				if(!skillInfo)
				{
					continue;
				}

				if(skillInfo->skillType == SKT_SHORTRANGEGENERAL || skillInfo->skillType == SKT_LONGRANGEGENERAL)
				{
					return skillInfo->skillId;
				}
			}
		}

		return 0;
	}

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingPursueAttackInAdvance::selectTargetObject()
	{
		if(mCharacterSceneEntity->getType() == GOT_TROOP)
		{
			return;
		}

		CCharacterSceneEntity* targetEntity = CSceneManager::getInstance().getCharacterSceneEntity(mTargetType, mTargetId, mTargetIndex);
		if(!targetEntity || targetEntity->getType() != GOT_TROOP)
		{
			return;
		}

		CTroopEntity* troopEntity = (CTroopEntity*)targetEntity/*((CTroopSoldierEntity*)targetEntity)->getTroopEntity()*/;
		if(!troopEntity)
		{
			destroy();
			return;
		}

		Int targetSoldierId = -1;
		Flt tempDis = 0;
		Flt minDis = 0;
		Vec3 targetPos;
		Vec3 ownerPos = mCharacterSceneEntity->getPos();
		CTroopSoldierEntity* troopSoldierEntity = NULL;

		for(UInt i = 0; i < troopEntity->getSoldierEntitysNum(); ++i)
		{
			troopSoldierEntity = troopEntity->getSoldierEntitysByIndex(i);
			if(!troopSoldierEntity)
			{
				continue;
			}


			if(isTroopCompanionTarget(troopSoldierEntity->getType(), troopEntity->getID(), troopSoldierEntity->getID()))
			{
				continue;
			}

			targetPos = troopSoldierEntity->getPos();
			tempDis = (targetPos - ownerPos).length();
			if(minDis == 0 || /*i == 0 || */tempDis < minDis)
			{
				minDis = tempDis;
				targetSoldierId = troopSoldierEntity->getID();
			}
		}

		if(targetSoldierId == -1)
		{
			return;
		}

		GAMEOBJ_TYPE targetType;
		GameObjectIdType targetId;
		UInt targetIndex;

		((CTroopSoldierEntity*)mCharacterSceneEntity)->getTarget(targetType, targetId, targetIndex);
		if((targetType == GOT_UNKNOWN || targetType == GOT_TROOP || targetType == GOT_SOLDIER) && targetId != troopEntity->getID())
		{
			setTarget(GOT_SOLDIER, troopEntity->getID(), targetSoldierId);
		}
		else
		{
			mTargetType = targetType;
			mTargetId = targetId;
			mTargetIndex = targetIndex;
		}
		
	}

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingPursueAttackInAdvance::setAIEntityGroup( CAIEntityGroup* aiEntityGroup )
	{
		mAIEntityGroup = aiEntityGroup;
	}

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingPursueAttackInAdvance::updatePursue( Flt delta )
	{
		if(mTargetId != 0)
		{
			CCharacterSceneEntity* targetEntity = CSceneManager::getInstance().getCharacterSceneEntity(mTargetType, mTargetId, mTargetIndex);
			if(!targetEntity || targetEntity->getDynamicData()->isDied)
			{
				destroy();
				return;
			}

			CCSEntityLineMoveAcion* lineMoveAcion = (CCSEntityLineMoveAcion*)targetEntity->getActionStateManager().getState("CCSEntityLineMoveAcion", false);
			if(lineMoveAcion)
			{
				mTargetTargetPos = lineMoveAcion->getDestination();
				mTargetTargetPos.y = 0;

				if(mTargetTargetPos != mLastTargetTargetPos)
				{	
					Vec3 targetPos;
					clacPursueTime(mCharacterSceneEntity, targetEntity, targetPos);
					mTargetPos = targetPos;
					mLastTargetTargetPos = mTargetTargetPos;
				}

				Vec3 dis = mCharacterSceneEntity->getPos() - mTargetPos;
				Flt disLength  = dis.length();
				if(disLength < 2)
				{
					mTargetPos = targetEntity->getPos();
				}
			}
			else
			{
				mTargetPos = targetEntity->getPos();
			}


			// 这是有用的。还会回来的。
			//if(mCharacterSceneEntity->getEntity()->getSceneNode()->getScene()->getBlockManager()->isDynamicBlockByRadius(mMoveToPos, mBlockDiameter/*, IBlockManager::VERTEX_LEFTDOWN*/))
			//{
			//	Vec3 dir = mCharacterSceneEntity->getPos() - mMoveToPos /*mTargetPos*/;
			//	dir.normalise();
			//	mCharacterSceneEntity->getEntity()->getSceneNode()->getScene()->getBlockManager()->getPosNearestAccessiblePos(mTargetPos, dir, mBlockDiameter, mMoveToPos);
			//}		//if(mCharacterSceneEntity->getEntity()->getSceneNode()->getScene()->getBlockManager()->isDynamicBlockByRadius(mMoveToPos, mBlockDiameter/*, IBlockManager::VERTEX_LEFTDOWN*/))
			//{
			//	Vec3 dir = mCharacterSceneEntity->getPos() - mMoveToPos /*mTargetPos*/;
			//	dir.normalise();
			//	mCharacterSceneEntity->getEntity()->getSceneNode()->getScene()->getBlockManager()->getPosNearestAccessiblePos(mTargetPos, dir, mBlockDiameter, mMoveToPos);
			//}
		}

		//判断是否进入技能发射范围
		Flt dis = (mTargetPos - mCharacterSceneEntity->getPos()).length();
		if(mAttackRange == 0 || dis <= mAttackRange)
		{
			if(mPathFindingMoveAI)
			{
				mPathFindingMoveAI->destroy();
			}

			if(mCharacterSceneEntity->getType() == GOT_PLAYERCHARACTER)
			{
				PlayCharacterNetPacketProcesser::getInstance().sendPlayerCharacterStopMoveToPackBuffer(mCharacterSceneEntity->getID());
			}
			else if(mCharacterSceneEntity->getType() == GOT_SOLDIER)
			{
				mCharacterSceneEntity->stopMoveToAction();
			}
			else if(mCharacterSceneEntity->getType() == GOT_TROOP)
			{
				//TroopNetPacketProcesser::getInstance().sendTroopEntityStopMoveToPackBuffer(CPlayer::getInstance().getActiveClan()->getData()->regionType, CPlayer::getInstance().getActiveClan()->getData()->regionID, CPlayer::getInstance().getInstanceUid(), mCharacterSceneEntity->getID());
			}

			mState = PAS_ATTACK;
			return;
		}

		if(mPausePursueThinkTime > 0)
		{
			mPausePursueThinkTime -= delta;
			return;
		}

		if(mTargetPos == mLastTargetPos)
		{
			return;
		}

		if(mCharacterSceneEntity->getType() != GOT_SOLDIER)
		{
			mPathFindingMoveAI = CAIManager::getInstance().createCAIEntityPathFindingMoveInAdvance(mCharacterSceneEntity);
			mPathFindingMoveAI->setDestination(mTargetPos);
			mPathFindingMoveAI->setAIEntityGroup(mAIEntityGroup);
			mCharacterSceneEntity->getAIStateManager().push(mPathFindingMoveAI, false);
		}
		else
		{
			mCharacterSceneEntity->doMoveToAction(mTargetPos, 0, false);
		}

		mLastTargetPos = mTargetPos;

		//mPausePursueThinkTime = 1;
	}

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingPursueAttackInAdvance::updateAttack( Flt delta )
	{
		if(mTargetId != 0)
		{
			// 死亡后退出
			CCharacterSceneEntity* targetEntity = CSceneManager::getInstance().getCharacterSceneEntity(mTargetType, mTargetId, mTargetIndex);
			if(!targetEntity || targetEntity->getDynamicData()->isDied)
			{
				destroy();
				return;
			}

			mTargetPos = targetEntity->getPos();
		}

		// 判断目标是否超出技能发射范围

		Vec3 dir = mTargetPos - mCharacterSceneEntity->getPos();
		Flt dis = dir.length();
		
		//dir.normalise();
		//mCharacterSceneEntity->setDir(dir);

		if(mAttackRange != 0 && dis > mAttackRange)
		{
			mState = PAS_PURSUE;
			return;
		}

		useSkill(mSkillObject, mSkillInfo);
		stopThink(mAttackIntervalTime);
		
		if(!mIsLoopAttack)
		{
			mIsFinished = true;
		}
	}

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingPursueAttackInAdvance::useSkill( CSkillObject* skillObject, SkillInfo*	skillInfo )
	{
		if( skillInfo->skillType != SKT_PARABOLAAREA 
			&& skillInfo->skillType != SKT_GOUPANDDOWN 
			&& skillInfo->skillType != SKT_SHORTRANGEGENERAL 
			&& skillInfo->skillType != SKT_LONGRANGEGENERAL 
			&& skillInfo->skillType != SKT_SELFAREA 
			&& skillInfo->skillType != SKT_TARGETPOSAREA 
			&& skillInfo->skillType != SKT_SINGLEEMITTER )
		{
			if(mCharacterSceneEntity->getType() == GOT_PLAYERCHARACTER)
			{
				SkillNetPacketProcesser::getInstance().sendPlayCharacterClantSkillRequestPacketToPackBuffer(skillObject);
			}
			else if(mCharacterSceneEntity->getType() == GOT_SOLDIER)
			{
				//CAITroopObjectSendSkillPacket* aiTroopObjectSendSkillPacket = (CAITroopObjectSendSkillPacket*)((CTroopSoldierEntity*)mCharacterSceneEntity)->getTroopEntity()->getAIStateManager().getState("CAITroopObjectSendSkillPacket", false);
				//if(!aiTroopObjectSendSkillPacket)
				//{
				//	return;
				//}

				//SkillNetPacketProcesser::getInstance().sendTroopClantSkillRequestPacketToPackBuffer(skillObject);

				destroy();
				return;
			}
			else if(mCharacterSceneEntity->getType() == GOT_MONSTER)
			{
				//SkillNetPacketProcesser::getInstance().sendMonsterClantSkillRequestPacketToPackBuffer(skillObject);
			}
			else if(mCharacterSceneEntity->getType() == GOT_TROOP)
			{
				SkillNetPacketProcesser::getInstance().sendTroopClantSkillRequestPacketToPackBuffer(skillObject);
			}
		}
		else
		{
			if(mCharacterSceneEntity->getType() == GOT_PLAYERCHARACTER)
			{
				SkillNetPacketProcesser::getInstance().sendPlayCharacterInjectSkillRequestPacketToPackBuffer(skillObject);
			}
			else if(mCharacterSceneEntity->getType() == GOT_SOLDIER)
			{
				CSkillObject* useSkillObject = (CSkillObject*)mCharacterSceneEntity->getSkillUseManager()->prepareUseSkill(skillInfo->skillId);
				if(!useSkillObject)
				{
					return;
				}

				useSkillObject->setTargetObject(skillObject->getTargetObjectType(), skillObject->getTargetObjectID(), skillObject->getTargetObjectIndex());

				CCSEntityInjectSkillAcion* injectSkillAcion = CActionManager::getInstance().createCCSEntityInjectSkillAcion(useSkillObject);
				mCharacterSceneEntity->getActionStateManager().push(injectSkillAcion);
				//CAITroopObjectSendSkillPacket* aiTroopObjectSendSkillPacket = (CAITroopObjectSendSkillPacket*)((CTroopSoldierEntity*)mCharacterSceneEntity)->getTroopEntity()->getAIStateManager().getState("CAITroopObjectSendSkillPacket", false);
				//if(!aiTroopObjectSendSkillPacket)
				//{
				//	return;
				//}

				//SkillNetPacketProcesser::getInstance().sendTroopInjectSkillRequestPacketToPackBuffer(skillObject);

				destroy();
				return;
			}
			else if(mCharacterSceneEntity->getType() == GOT_MONSTER)
			{
	//			SkillNetPacketProcesser::getInstance().sendMonsterInjectSkillRequestPacketToPackBuffer(skillObject);
			}
			else if(mCharacterSceneEntity->getType() == GOT_TROOP)
			{
				SkillNetPacketProcesser::getInstance().sendTroopUseSkillRequestPacketToPackBuffer(skillObject);
			}
		}
	}

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingPursueAttackInAdvance::setIsLoopAttack( Bool isLoopAttack )
	{
		mIsLoopAttack = isLoopAttack;
	}

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingPursueAttackInAdvance::setIsSelectTargetObject( Bool isSelectTargetObject )
	{
		mIsSelectTargetObject = isSelectTargetObject;
	}

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingPursueAttackInAdvance::getTarget( GAMEOBJ_TYPE& gameType, GameObjectIdType& id, UInt& index )
	{
		gameType = mTargetType;
		id = mTargetId;
		index =mTargetIndex;
	}

	//-----------------------------------------------------------------------
	Bool CAIEntityPathFindingPursueAttackInAdvance::isAttack( CCharacterSceneEntity* owner, CCharacterSceneEntity* target )
	{
		if(!mSkillInfo)
		{
			return false;
		}

		//owner->getSkillUseManager()->isCanUseSkill(mSkillInfo, target);

		GAMEOBJ_TYPE gameObjectType = owner->getType();

		if(target->getType() != GOT_BUILDING)
		{
			return true;
		}

		if(gameObjectType != GOT_PLAYERCHARACTER && gameObjectType != GOT_SOLDIER)
		{
			return true;
		}

		if(gameObjectType == GOT_SOLDIER)
		{
			TROOPTEMPLATE_TYPE troopType =owner->getCharacterTempInfo()->getArmyArmyType();
			if(troopType == TROOPTEMPLATE_TYPE_BROADSWORD 
				|| troopType == TROOPTEMPLATE_TYPE_SPEAR 
				|| troopType == TROOPTEMPLATE_TYPE_HORSE 
				|| troopType == TROOPTEMPLATE_TYPE_BOW)
			{
				return false;
			}        
		}
		else
		{
			return false;
		}

		return true;
	}

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingPursueAttackInAdvance::stopThink( Flt time )
	{
		mPauseThinkTime = time;
	}

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingPursueAttackInAdvance::resumeThink()
	{
		mPauseThinkTime = 0;
	}

	//-----------------------------------------------------------------------
	Flt CAIEntityPathFindingPursueAttackInAdvance::getAttackRange()
	{
		Flt skillRange = ((InitiativeSkillBasicInfo*)mSkillInfo->skillInfo)->range;
		Flt characterRange = 0;

		if(mTargetId != 0)
		{
			CCharacterSceneEntity* targetEntity = CSceneManager::getInstance().getCharacterSceneEntity(mTargetType, mTargetId, mTargetIndex);
			if(!targetEntity)
			{
				return 0;
			}

			if(mCharacterSceneEntity->getType() == GOT_TROOP)
			{
				characterRange = mCharacterSceneEntity->getEntity()->getModelObject()->getPatherRadius() + targetEntity->getEntity()->getModelObject()->getPatherRadius() + 1.5;
				if(skillRange < characterRange)
				{
					return characterRange;
				}
			}
			else if(targetEntity->getType() == GOT_TROOP)
			{
				characterRange = mCharacterSceneEntity->getEntity()->getModelObject()->getWidth() / 2 + targetEntity->getEntity()->getModelObject()->getPatherRadius() + skillRange;
				return characterRange;
			}
			else
			{
				characterRange = mCharacterSceneEntity->getEntity()->getModelObject()->getWidth() / 2 + targetEntity->getEntity()->getModelObject()->getWidth() / 2 + skillRange;
				return characterRange;
			}
		}

		return skillRange;
	}

	//-----------------------------------------------------------------------
	Bool CAIEntityPathFindingPursueAttackInAdvance::isTroopCompanionTarget( GAMEOBJ_TYPE gameType, GameObjectIdType id, UInt index )
	{
		if(mCharacterSceneEntity->getType() != GOT_SOLDIER)
		{
			return false;
		}
		
		CTroopEntity* troopEntity = ((CTroopSoldierEntity*)mCharacterSceneEntity)->getTroopEntity();
		if(!troopEntity)
		{
			return false;
		}

		GAMEOBJ_TYPE targetType;
		GameObjectIdType targetId;
		UInt targetIndex;

		CTroopSoldierEntity* troopSoldierEntity = NULL;
		for(UInt i = 0; i < troopEntity->getSoldierEntitysNum(); ++i)
		{
			troopSoldierEntity = troopEntity->getSoldierEntitysByIndex(i);
			if(troopSoldierEntity == mCharacterSceneEntity)
			{
				continue;
			}

			if(!troopSoldierEntity || troopSoldierEntity->getDynamicData()->isDied)
			{
				continue;
			}

			troopSoldierEntity->getTarget(targetType, targetId, targetIndex);
			if(/*targetType == gameType && */targetId == id && targetIndex == index)
			{
				return true;
			}
		}

		return false;
	}

	//-----------------------------------------------------------------------
	Flt CAIEntityPathFindingPursueAttackInAdvance::clacPursueTime( CCharacterSceneEntity* owner, CCharacterSceneEntity* target, Vec3& pursuePos )
	{
		pursuePos = Vec3(0,0,0);

		Vec3 ownerPos = owner->getPos();
		Vec3 targetPos = target->getPos();
		Vec3 targetTargetPos;
		CCSEntityLineMoveAcion* lineMoveAcion = (CCSEntityLineMoveAcion*)target->getActionStateManager().getState("CCSEntityLineMoveAcion", false);
		if(lineMoveAcion)
		{
			targetTargetPos = lineMoveAcion->getDestination();
			targetTargetPos.y = 0;
		}
		else
		{
			pursuePos = targetTargetPos;
			return 0;
		}

		Vec3 targetDir = targetTargetPos - targetPos;
		targetDir.normalise();
		targetDir.y = 0;

		Vec3 ownerTargetDis = targetPos - ownerPos;
		
		Flt ownerSpeed = owner->getDynamicData()->moveSpeed;
		Flt targetSpeed = target->getDynamicData()->moveSpeed;

		Int a = (ownerTargetDis.x * targetSpeed * ownerTargetDis.x * targetSpeed) + (ownerTargetDis.z * targetSpeed * ownerTargetDis.z * targetSpeed) - ownerSpeed * ownerSpeed;
		Int b = 2 * targetDir.x * ownerTargetDis.x * targetSpeed + 2 * targetDir.z * ownerTargetDis.z * targetSpeed;
		Int c = targetDir.x * targetDir.x + targetDir.z * targetDir.z;

		if((b*b - 4*a*c) < 0)
		{
			pursuePos = targetTargetPos;
			return 0;
		}

		Flt t1 = (-b + sqrt((Flt)(b*b - 4*a*c))) / (2 * a);
		Flt t2 = (-b - sqrt((Flt)(b*b - 4*a*c))) / (2 * a);

		if(t1 <= t2)
		{
			pursuePos = targetPos + targetDir * t1 * targetSpeed;
			return t1;
		}
		else
		{
			pursuePos = targetPos + targetDir * t2 * targetSpeed;
			return t2;
		}
		
		pursuePos = targetTargetPos;
		return 0;
	}
}