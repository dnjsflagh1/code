/******************************************************************************/
#include "stdafx.h"
#include "SAIAttack.h"
#include "SWorldManager.h"
#include "SCharacter.h"
#include "SkillBaseInfo.h"
#include "SSkillUseManager.h"
#include "SkillInfoList.h"
#include "ShortRangeGeneralAttackSkillTemplate.h"
#include "LongRangeGeneralAttackSkillTemplate.h"
#include "SingleTargetSkillTemplate.h"
#include "CharacterSkillTempLate.h"
#include "SkillBaseInfo.h"
#include "SSkillOwnManager.h"
#include "CharacterList.h"
#include "SAIController.h"
#include "SSkillNetPacketProcesser.h"
/******************************************************************************/

namespace MG
{

	//--------------------------------------------------------------------------

	Str SAIAttack::STATE_NAME = "SAIAttack";

	//--------------------------------------------------------------------------
	SAIAttack::SAIAttack( SCharacter* owner )
		:LinedStateObject(STATE_NAME)
		,SAI(owner)
		,mTargetId(0)
		,mTargetIndex(0)
		,mTargetType(GOT_UNKNOWN)
		,mSkillId(0)
		,mIsFinished(false)
		,mSkillObject(NULL)
		,mPauseThinkTime(0)
		,mAIAttackState(AIAS_NULL)
		,mMinIntervalAttackTime(1000)
		,mMaxIntervalAttackTime(2000)
	{
		mAIType = AIT_ATTACK;
	}

	//--------------------------------------------------------------------------
	SAIAttack::~SAIAttack()
	{

	}

	//-----------------------------------------------------------------------
	void SAIAttack::update( Flt delta )
	{
		if(mPauseThinkTime > 0)
		{
			mPauseThinkTime -= delta;
			return;
		}

		updateAttack(delta);
	}				 

	//-----------------------------------------------------------------------
	Bool SAIAttack::isFinished()
	{
		return mIsFinished;
	}

	//-----------------------------------------------------------------------
	void SAIAttack::onEnter()
	{
		if(mOwner->isDead())
		{ 
			destroy();
			return;
		}

		if(mTargetId == 0)
		{
			aiEnd();
			destroy();
			return;
		}

		mSkillObject = (SSkillObject*)mOwner->getSkillUseManager()->prepareUseSkill(mSkillId);
		if(!mSkillObject)
		{	
			aiEnd();
			destroy();
			return;
		}

		SkillInfo* skillInfo = mSkillObject->getSkillInfo();
		if(isTargetCharSkill(skillInfo) || skillInfo->skillType == SKT_SINGLEEMITTER)
		{
			SCharacter* targetCharacter = 0;//SWorldManager::getInstance().getCharacterFromSceneObject(mOwner->getRegionType(), mOwner->getRegionID(), mOwner->getCurrentRealRegionObject()->getInstanceUId(), mTargetType, mTargetId, mTargetIndex);
			if(!targetCharacter)
			{
				notifyTargetDied();
				destroy();
				return;
			}

			if(!isAttack(mOwner, targetCharacter))
			{
				notifyTargetDied();
				destroy();
				return;
			}

			mTargetPos = targetCharacter->getPos();
			mTargetPos.y = 0;
		}
		else if(skillInfo->skillType == SKT_SELFAREA
			|| skillInfo->skillType == SKT_TARGETPOSAREA)
		{
			mTargetPos = mOwner->getPos();	
		}

		InitiativeSkillBasicInfo* initiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)skillInfo->skillInfo;
		
		Flt range = initiativeSkillBasicInfo->range;
		Flt dis = (mOwner->getPos() - mTargetPos).length();

		if( dis > range )
		{
			aiEnd();
			destroy();
			return;
		}

		if(isTargetCharSkill(skillInfo))
		{
			mSkillObject->setTargetObject(mTargetType, mTargetId, mTargetIndex);
		}
		else if(isTargetPosSkill(skillInfo))
		{
			mSkillObject->setTargetPosition(mTargetPos);
		}

		mPauseThinkTime = initiativeSkillBasicInfo->actionTime + initiativeSkillBasicInfo->attackFrontTime;

		mAIAttackState = AIAS_START;
	}

	//-----------------------------------------------------------------------
	void SAIAttack::onLeave()
	{
		
	}

	//-----------------------------------------------------------------------
	void SAIAttack::setTarget(GAMEOBJ_TYPE gameType, GameObjectIdType id, UInt index)
	{
		mTargetType = gameType;
		mTargetId = id;
		mTargetIndex = index;
	}

	//-----------------------------------------------------------------------
	void SAIAttack::setTarget(Vec3 pos)
	{
		mTargetPos = pos;
	}

	//-----------------------------------------------------------------------
	void SAIAttack::setUseSkillId(IdType skillId)
	{
		mSkillId = skillId;
	}

	//-----------------------------------------------------------------------
	void SAIAttack::updateAttack( Flt delta )
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
	void SAIAttack::useSkill( SSkillObject* skillObject )
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
				//SkillNetPacketProcesser::getInstance().sendPlayCharacterClantSkillRequestPacketToPackBuffer(skillObject);
			}
			else if(mOwner->getType() == GOT_SOLDIER)
			{
				//CAITroopObjectSendSkillPacket* aiTroopObjectSendSkillPacket = (CAITroopObjectSendSkillPacket*)((CTroopSoldierEntity*)mCharacterSceneEntity)->getTroopEntity()->getAIStateManager().getState("CAITroopObjectSendSkillPacket", false);
				//if(!aiTroopObjectSendSkillPacket)
				//{
				//	return;
				//}

				//SkillNetPacketProcesser::getInstance().sendTroopClantSkillRequestPacketToPackBuffer(skillObject);
			}
			else if(mOwner->getType() == GOT_MONSTER)
			{
				//SSkillNetPacketProcesser::getInstance().sendMonsterClantSkillRequestPacketToPackBuffer(skillObject);
			}
		}
		else
		{
			if(mOwner->getType() == GOT_PLAYERCHARACTER)
			{
				//SkillNetPacketProcesser::getInstance().sendPlayCharacterInjectSkillRequestPacketToPackBuffer(skillObject);
			}
			else if(mOwner->getType() == GOT_SOLDIER)
			{
				//CAITroopObjectSendSkillPacket* aiTroopObjectSendSkillPacket = (CAITroopObjectSendSkillPacket*)((CTroopSoldierEntity*)mCharacterSceneEntity)->getTroopEntity()->getAIStateManager().getState("CAITroopObjectSendSkillPacket", false);
				//if(!aiTroopObjectSendSkillPacket)
				//{
				//	return;
				//}

				//SkillNetPacketProcesser::getInstance().sendTroopInjectSkillRequestPacketToPackBuffer(skillObject);
			}
			else if(mOwner->getType() == GOT_MONSTER)
			{
				SSkillNetPacketProcesser::getInstance().sendMonsterInjectSkillToClient((SMonster*)mOwner, skillObject);
				//SkillNetPacketProcesser::getInstance().sendMonsterInjectSkillRequestPacketToPackBuffer(skillObject);
			}
		}
	}

	//-----------------------------------------------------------------------
	Bool SAIAttack::isAttack( SCharacter* owner, SCharacter* target )
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
	void SAIAttack::notifyAttackEnd()
	{
		if(mAIListener)
		{
			mAIListener->onAttackEnd();
		}
	}

	//-----------------------------------------------------------------------
	void SAIAttack::notifyTargetDied()
	{
		if(mAIListener)
		{
			mAIListener->onTargetDied();
		}
	}

	//-----------------------------------------------------------------------
	void SAIAttack::aiEnd()
	{
		notifyEnd();
		destroy();
	}

	//-----------------------------------------------------------------------
	Bool SAIAttack::isTargetCharSkill( SkillInfo* skillInfo )
	{
		if (skillInfo->skillType == SKT_SHORTRANGEGENERAL
			|| skillInfo->skillType == SKT_LONGRANGEGENERAL
			|| skillInfo->skillType == SKT_SINGLETARGET)
		{
			return true;
		}

		return false;
	}

	//-----------------------------------------------------------------------
	Bool SAIAttack::isTargetPosSkill( SkillInfo* skillInfo )
	{
		if (skillInfo->skillType == SKT_SINGLEEMITTER
			|| skillInfo->skillType == SKT_SELFAREA
			|| skillInfo->skillType == SKT_TARGETPOSAREA)
		{
			return true;
		}

		return false;
	}
}