/******************************************************************************/
#include "stdafx.h"
#include "ClientMain.h"
#include "CMonsterEntity.h"
#include "CSceneManager.h"
#include "ISceneNode.h"
#include "CPlayer.h"
#include "MonsterData.h"
#include "CharacterList.h"
/******************************************************************************/

namespace MG
{
	//-----------------------------------------------------------------------
	CMonsterEntity::CMonsterEntity( IEntity* entity )
		:CCharacterSceneEntity( entity, GOT_MONSTER, GQT_MONSTER, (MG_NEW MonsterEntityData) )
		,mPauseThinkTime(0)
	{
	}

	//-----------------------------------------------------------------------
	CMonsterEntity::~CMonsterEntity()
	{
		unInitialize();
	}

	//-----------------------------------------------------------------------
	void CMonsterEntity::initialize()
	{
		initializeEntity();
		CCharacterSceneEntity::initialize();
	}

	//-----------------------------------------------------------------------
	void CMonsterEntity::unInitialize()
	{
		CCharacterSceneEntity::unInitialize();
	}

	//-----------------------------------------------------------------------
	void CMonsterEntity::update( Flt delta )
	{
		checkAndPlayIdleAnim(delta);
		CCharacterSceneEntity::update(delta);
	}
	//-----------------------------------------------------------------------
	void CMonsterEntity::initializeEntity()
	{
		//mEntity->getModelObject()->setEmissive(color);
	}

	//-----------------------------------------------------------------------
	Bool CMonsterEntity::isBattleState()
	{
		MonsterEntityData* data = getDynamicData();
		if ( data )
			return data->isFightState;

		return false;
	}

	//-----------------------------------------------------------------------
	MonsterEntityData* CMonsterEntity::getDynamicData()
	{
		return dynamic_cast<MonsterEntityData*>(getGameObjectData());
	}

	//-----------------------------------------------------------------------
	void CMonsterEntity::checkAndPlayIdleAnim( Flt delta )
	{
		if(getDynamicData()->isDied)
		{
			return;
		}

		if(mPauseThinkTime > 0)
		{
			mPauseThinkTime -= delta;
			return;
		}

		Flt animLength = 0;
		if(getActionStateManager().isEmpty())
		{
			animLength = getAnimationLength("idle");
			playAnimation("idle", false);
		}

		mPauseThinkTime = MGRandom::getInstance().rand_ab_One(1, 6) + animLength;
	}

}