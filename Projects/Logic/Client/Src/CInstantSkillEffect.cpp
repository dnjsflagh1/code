/******************************************************************************/
#include "stdafx.h"
#include "CInstantSkillEffect.h"
#include "CSceneManager.h"
#include "CLuaSkillSystem.h"
#include "CPlayer.h"
#include "SkillNetPacketProcesser.h"
#include "CBuildingEntity.h"
#include "SkillBaseInfo.h"
/******************************************************************************/

namespace MG
{

	//--------------------------------------------------------------------------
	CInstantSkillEffect::CInstantSkillEffect( CSkillObject* object )
		:CSkillEffect( object )
		, mEffectEntity(NULL)
		,mTargetIndex(0)
		,mTargetId(0)
		,mTargetType(GOT_PLAYERCHARACTER)
		,mState(ISES_NULL)
		,mPauseThinkTime(0)
	{

	}

	//--------------------------------------------------------------------------
	CInstantSkillEffect::~CInstantSkillEffect()
	{
		end();
	}

	//--------------------------------------------------------------------------
	void CInstantSkillEffect::start()
	{
		CSkillEffect::start();
		
		CCharacterSceneEntity* ownerCCharacterSceneEntity = CSceneManager::getInstance().getCharacterSceneEntity(mSkillObject->getOwnerType(), mSkillObject->getOwnerID(), mSkillObject->getOwnerIndex());
		if(!ownerCCharacterSceneEntity || ownerCCharacterSceneEntity->getDynamicData()->isDied)
		{
			end();
			return;
		}

		CCharacterSceneEntity* targetCharacterSceneEntity = CSceneManager::getInstance().getCharacterSceneEntity(mTargetType, mTargetId, mTargetIndex);
		if(!targetCharacterSceneEntity || targetCharacterSceneEntity->getDynamicData()->isDied)
		{
			end();
			return;
		}

		Vec3 dir = targetCharacterSceneEntity->getPos() - ownerCCharacterSceneEntity->getPos();
		dir.normalise();
		ownerCCharacterSceneEntity->setDir(dir);

		mState = ISES_COLLISION;
	}

	//--------------------------------------------------------------------------
	void CInstantSkillEffect::end()
	{
		CSkillEffect::end();
	}

	//--------------------------------------------------------------------------
	void CInstantSkillEffect::update( Flt delta )
	{
		if(mPauseThinkTime > 0)
		{
			mPauseThinkTime -= delta;
			return;
		}

		CCharacterSceneEntity* owner = CSceneManager::getInstance().getCharacterSceneEntity(mSkillObject->getOwnerType(), mSkillObject->getOwnerID(), mSkillObject->getOwnerIndex());
		if(!owner || owner->getDynamicData()->isDied)
		{
			end();
			return;
		}

		CCharacterSceneEntity* target = CSceneManager::getInstance().getCharacterSceneEntity(mTargetType, mTargetId, mTargetIndex);
		if(!target || target->getDynamicData()->isDied)
		{
			end();
			return;
		}

		switch(mState)
		{
		case ISES_COLLISION:
			effectCollision(owner, target);
			break;
		}

	}

	//-----------------------------------------------------------------------
	void CInstantSkillEffect::setPos( Vec3 pos )
	{
		mPos = pos;
	}

	//-----------------------------------------------------------------------

	void CInstantSkillEffect::setTargetIndex( UInt index )
	{
		mTargetIndex = index;
	}
	//-----------------------------------------------------------------------
	void CInstantSkillEffect::setTargetID( IdType id )
	{
		mTargetId = id;
	}

	//-----------------------------------------------------------------------
	void CInstantSkillEffect::setTargetType( GAMEOBJ_TYPE type )
	{
		mTargetType = type;
	}

	//-----------------------------------------------------------------------
	void CInstantSkillEffect::effectCollision( CCharacterSceneEntity* owner, CCharacterSceneEntity* target )
	{
		CLuaSkillSystem::getInstance().execClientCollisionAffectScript(target, 1, mSkillObject, this );

		if(target->getType() == GOT_MONSTER && owner->getDynamicData()->belongPlayerID == CPlayer::getInstance().getAccountID())
		{
			SkillNetPacketProcesser::getInstance().sendSkillCharacterCollisionAffectCharacter(mSkillObject->getOwnerType(), owner, mTargetType, target, 1, mSkillObject->getSkillInfo()->skillId, CPlayer::getInstance().getActiveClan()->getFocusRegionID());
		}
		else if(target->getDynamicData()->belongPlayerID == CPlayer::getInstance().getAccountID())
		{
			SkillNetPacketProcesser::getInstance().sendSkillCharacterCollisionAffectCharacter(mSkillObject->getOwnerType(), owner, mTargetType, target, 1, mSkillObject->getSkillInfo()->skillId, CPlayer::getInstance().getActiveClan()->getFocusRegionID());
		}

		end();
	}

	//-----------------------------------------------------------------------
	void CInstantSkillEffect::stopUpdate( Flt time )
	{
		mPauseThinkTime = time;
	}

	//-----------------------------------------------------------------------
	void CInstantSkillEffect::resumeUpdate()
	{
		mPauseThinkTime = 0;
	}

}