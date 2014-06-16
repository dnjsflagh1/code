/******************************************************************************/
#include "stdafx.h"
#include "CGoUpAndDownSkill.h"
#include "CCharacterSceneEntity.h"
#include "SkillBaseInfo.h"
#include "CSceneManager.h"
#include "CGoUpAndDownSkillEffect.h"
/******************************************************************************/

namespace MG
{

	//-----------------------------------------------------------------------
	CGoUpAndDownSkill::CGoUpAndDownSkill( CCharacterSceneEntity* owner )
		: CSkillObject(owner)
	{

	}

	//-----------------------------------------------------------------------
	CGoUpAndDownSkill::~CGoUpAndDownSkill()
	{

	}

	//-----------------------------------------------------------------------
	void CGoUpAndDownSkill::execClientSkillStartInjectLogic()
	{
		CCharacterSceneEntity* owner = CSceneManager::getInstance().getCharacterSceneEntity(mOwnerType, mOwnerId, mOwnerIndex);
		if(!owner)
		{
			stopUse();
			return;
		}

		CSkillEffectSystem* system = CSceneManager::getInstance().getSkillEffectSystem();
		CGoUpAndDownSkillEffect* effect = system->addGoUpAndDownSkillEffect( this );
		effect->setDir(owner->getDir());
		effect->setTargetPos(mTargetPosition);
		effect->start();
	}

}