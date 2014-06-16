/******************************************************************************/
#ifndef _CSKILLOWNMANAGER_H_
#define _CSKILLOWNMANAGER_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "SkillOwnManager.h"

/******************************************************************************/
namespace MG
{

	/******************************************************************************/
	//角色所属的技能管理器
	/******************************************************************************/
	class CCharacter;
	class CSkillOwnManager : public SkillOwnManager
	{
	public:
		CSkillOwnManager( CCharacter* character );
		virtual ~CSkillOwnManager();

	public:
		virtual void	addOwnerSkill( IdType skillId );
		UInt			getDefaultSkill();

	protected:
		UInt			mDefaultSkill;

	};
}


#endif