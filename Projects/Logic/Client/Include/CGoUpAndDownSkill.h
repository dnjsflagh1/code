/******************************************************************************/
#ifndef _CGOUPANDDOWNSKILL_H_
#define _CGOUPANDDOWNSKILL_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "CSkillObject.h"
#include "CSkillEffectSystem.h"
/******************************************************************************/
namespace MG
{

	/******************************************************************************
	升降云梯技能

	******************************************************************************/
	class CGoUpAndDownSkill : public CSkillObject
	{
	public:
		CGoUpAndDownSkill( CCharacterSceneEntity* owner );
		virtual ~CGoUpAndDownSkill();

	protected:

		//执行技能发射逻辑
		virtual void						execClientSkillStartInjectLogic();
	};
}

#endif