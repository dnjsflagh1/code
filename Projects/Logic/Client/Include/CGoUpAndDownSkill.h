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
	�������ݼ���

	******************************************************************************/
	class CGoUpAndDownSkill : public CSkillObject
	{
	public:
		CGoUpAndDownSkill( CCharacterSceneEntity* owner );
		virtual ~CGoUpAndDownSkill();

	protected:

		//ִ�м��ܷ����߼�
		virtual void						execClientSkillStartInjectLogic();
	};
}

#endif