/******************************************************************************/
#ifndef _SKILLOWNMANAGER_H_
#define _SKILLOWNMANAGER_H_
/******************************************************************************/

#include "WorldCorePreqs.h"

/******************************************************************************/
namespace MG
{

	/******************************************************************************/
	//角色所属的技能管理器
	/******************************************************************************/

	class SkillOwnManager
	{
	public:
		SkillOwnManager( GameObject* owner );
		virtual ~SkillOwnManager();

	public:

		virtual void											addOwnerSkill( IdType skillId );

		virtual Bool											isLearnSkill( IdType skillId );

		virtual Bool											learnSkill( IdType skillId );

		virtual Bool											isOwnSkill(IdType skillId );

		virtual UInt											getOwnSkillNum();

		virtual IdType											getOwnerSkillByIndex( UInt index );

	protected:


	protected:
		std::vector<IdType>										mSkillList;
		GameObject*												mOwner;											
	};
}


#endif