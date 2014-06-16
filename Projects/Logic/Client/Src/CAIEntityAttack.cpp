/******************************************************************************/
#include "stdafx.h"
#include "CAIEntityAttack.h"
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
#include "CAIController.h"
/******************************************************************************/

namespace MG
{

	//--------------------------------------------------------------------------

	Str CAIEntityAttack::STATE_NAME = "CAIEntityAttack";

	//--------------------------------------------------------------------------
	CAIEntityAttack::CAIEntityAttack( CCharacterSceneEntity* characterSceneEntity )
		:LinedStateObject(STATE_NAME)
		,CAI(characterSceneEntity)
		,mTargetId(0)
		,mTargetIndex(0)
		,mTargetType(GOT_UNKNOWN)
		,mSkillId(0)
		,mIsFinished(false)
		,mSkillObject(NULL)
		,mPauseThinkTime(0)
		,mAIAttackState(AIAS_NULL)
		,mMinIntervalAttackTime(1000)
		,mMaxIntervalAttackTime(1500)
	{
		mAIType = AIT_ATTACK;
	}

	//--------------------------------------------------------------------------
	CAIEntityAttack::~CAIEntityAttack()
	{

	}

	//-----------------------------------------------------------------------
	void CAIEntityAttack::update( Flt delta )
	{
		if(mPauseThinkTime > 0)
		{
			mPauseThinkTime -= delta;
			return;
		}

		updateAttack(delta);
	}				 

	//-----------------------------------------------------------------------
	Bool CAIEntityAttack::isFinished()
	{
		return mIsFinished;
	}

	//-----------------------------------------------------------------------
	void CAIEntityAttack::onEnter()
	{
		if(mOwner->getDynamicData()->isDied)
		{ 
			destroy();
			return;
		}


		//如果目标是object
		Flt targetPatherRadius = 0;
		if(mTargetId != 0)
		{
			CCharacterSceneEntity* targetEntity = CSceneManager::getInstance().getCharacterSceneEntity(mTargetType, mTargetId, mTargetIndex);
			if(!targetEntity)
			{
				notifyTargetDied();
				destroy();
				return;
			}

			if(!isAttack(mOwner, targetEntity))
			{
				notifyTargetDied();
				destroy();
				return;
			}

			mTargetPos = targetEntity->getPos();
			targetPatherRadius = targetEntity->getEntity()->getModelObject()->getPatherRadius();
		}

		//设置技能的skillobject
		mSkillObject = (CSkillObject*)mOwner->getSkillUseManager()->prepareUseSkill(mSkillId);
		if(!mSkillObject)
		{	
			aiEnd();
			return;
		}

		UInt range = 0;
		InitiativeSkillBasicInfo* initiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)(mSkillObject->getSkillInfo()->skillInfo);

		SkillType skillType = mSkillObject->getSkillInfo()->skillType;
		Flt skillRange = initiativeSkillBasicInfo->range;

		if(mOwner->getType() == GOT_TROOP)
		{
			range = mOwner->getEntity()->getModelObject()->getPatherRadius() + targetPatherRadius + 1.5;
			if(skillRange > range)
			{
				range = skillRange;
			}
		}
		else
		{
			range = mOwner->getEntity()->getModelObject()->getWidth() / 2 + targetPatherRadius + skillRange;
		}

		Flt dis = (mOwner->getPos() - mTargetPos).length();

		if( dis > range )
		{
			aiEnd();
			return;
		}

		if(mTargetId != 0 && (skillType != SKT_TARGETPOSAREA && skillType != SKT_PARABOLAAREA))
		{
			mSkillObject->setTargetObject(mTargetType, mTargetId, mTargetIndex);
		}
		else
		{
			mSkillObject->setTargetPosition(mTargetPos);
		}


		mPauseThinkTime = initiativeSkillBasicInfo->actionTime + initiativeSkillBasicInfo->attackFrontTime;

		mAIAttackState = AIAS_START;

	}

	//-----------------------------------------------------------------------
	void CAIEntityAttack::onLeave()
	{
		
	}

	//-----------------------------------------------------------------------
	void CAIEntityAttack::setTarget(GAMEOBJ_TYPE gameType, GameObjectIdType id, UInt index)
	{
		mTargetType = gameType;
		mTargetId = id;
		mTargetIndex = index;
	}

	//-----------------------------------------------------------------------
	void CAIEntityAttack::setTarget(Vec3 pos)
	{
		mTargetPos = pos;
	}

	//-----------------------------------------------------------------------
	void CAIEntityAttack::setUseSkillId(IdType skillId)
	{
		mSkillId = skillId;
	}

	//-----------------------------------------------------------------------
	void CAIEntityAttack::updateAttack( Flt delta )
	{
		switch(mAIAttackState)
		{
		case AIAS_START:
			{
				useSkill(mSkillObject);
				mAIAttackState = AIAS_END;

				SkillInfo* skillInfo = mSkillObject->getSkillInfo();
				InitiativeSkillBasicInfo* initiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)skillInfo->skillInfo;
				Flt intervalTime = MGRandom::getInstance().rand_ab_One(mMinIntervalAttackTime, mMaxIntervalAttackTime);
				intervalTime /= 1000;
				mPauseThinkTime = initiativeSkillBasicInfo->attackBehindTime + intervalTime;
			}
			return;

		case AIAS_END:
			mIsFinished = true;
			notifyAttackEnd();

			mAIAttackState =  AIAS_NULL;
			break;
		}
	}

	//-----------------------------------------------------------------------
	void CAIEntityAttack::useSkill( CSkillObject* skillObject )
	{
		SkillInfo* skillInfo = skillObject->getSkillInfo();

		if( skillInfo->skillType != SKT_PARABOLAAREA 
			&& skillInfo->skillType != SKT_GOUPANDDOWN 
			&& skillInfo->skillType != SKT_SHORTRANGEGENERAL 
			&& skillInfo->skillType != SKT_LONGRANGEGENERAL 
			&& skillInfo->skillType != SKT_SELFAREA 
			&& skillInfo->skillType != SKT_TARGETPOSAREA 
			&& skillInfo->skillType != SKT_SINGLEEMITTER )
		{
			if(mOwner->getType() == GOT_PLAYERCHARACTER)
			{
				SkillNetPacketProcesser::getInstance().sendPlayCharacterClantSkillRequestPacketToPackBuffer(skillObject);
			}
			else if(mOwner->getType() == GOT_SOLDIER)
			{
				CAITroopObjectSendSkillPacket* aiTroopObjectSendSkillPacket = (CAITroopObjectSendSkillPacket*)((CTroopSoldierEntity*)mOwner)->getTroopEntity()->getAIStateManager().getState("CAITroopObjectSendSkillPacket", false);
				if(!aiTroopObjectSendSkillPacket)
				{
					return;
				}

				SkillNetPacketProcesser::getInstance().sendTroopClantSkillRequestPacketToPackBuffer(skillObject);
			}
			else if(mOwner->getType() == GOT_MONSTER)
			{
				//SkillNetPacketProcesser::getInstance().sendMonsterClantSkillRequestPacketToPackBuffer(skillObject);
			}
		}
		else
		{
			if(mOwner->getType() == GOT_PLAYERCHARACTER)
			{
				SkillNetPacketProcesser::getInstance().sendPlayCharacterInjectSkillRequestPacketToPackBuffer(skillObject);
			}
			else if(mOwner->getType() == GOT_SOLDIER)
			{
				CAITroopObjectSendSkillPacket* aiTroopObjectSendSkillPacket = (CAITroopObjectSendSkillPacket*)((CTroopSoldierEntity*)mOwner)->getTroopEntity()->getAIStateManager().getState("CAITroopObjectSendSkillPacket", false);
				if(!aiTroopObjectSendSkillPacket)
				{
					return;
				}

				SkillNetPacketProcesser::getInstance().sendTroopInjectSkillRequestPacketToPackBuffer(skillObject);
			}
			else if(mOwner->getType() == GOT_MONSTER)
			{
		//		SkillNetPacketProcesser::getInstance().sendMonsterInjectSkillRequestPacketToPackBuffer(skillObject);
			}
			else if(mOwner->getType() == GOT_TROOP)
			{
				SkillNetPacketProcesser::getInstance().sendTroopUseSkillRequestPacketToPackBuffer(skillObject);
			}
		}

		notifyAttackEnd();
	}

	//-----------------------------------------------------------------------
	Bool CAIEntityAttack::isAttack( CCharacterSceneEntity* owner, CCharacterSceneEntity* target )
	{
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
	void CAIEntityAttack::notifyAttackEnd()
	{
		if(mAIListener)
		{
			mAIListener->onAttackEnd();
		}
	}

	//-----------------------------------------------------------------------
	void CAIEntityAttack::notifyTargetDied()
	{
		if(mAIListener)
		{
			mAIListener->onTargetDied();
		}
	}

	//-----------------------------------------------------------------------
	void CAIEntityAttack::aiEnd()
	{
		notifyEnd();
		destroy();
	}
}