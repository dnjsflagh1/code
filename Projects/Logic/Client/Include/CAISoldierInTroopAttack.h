/******************************************************************************/
#ifndef _SOLDIERINTROOPATTACK_H_
#define _SOLDIERINTROOPATTACK_H_
/******************************************************************************/

#include "CAIEntityAttack.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************

	******************************************************************************/
	class CAISoldierInTroopAttack
	{
	public:
		CAISoldierInTroopAttack( CTroopEntity* troopEntity );
		virtual ~CAISoldierInTroopAttack();

		//×´Ì¬Ãû×Ö
		static Str STATE_NAME;

		////////////////////////////////////////////////////////////////////////

		void											setUseSkill( IdType skillId );

		void											setTarget( GAMEOBJ_TYPE targetType, IdType targetId, Vec3 taegetPos );

		void											onUseSkill();

	protected:

		CSkillObject*									setSkillObject( CTroopSoldierEntity* troopSoldierEntity );

	protected:
		CTroopEntity*									mTroopEntity;
		IdType											mSkillId;
		GAMEOBJ_TYPE									mTargetType;
		IdType											mTargetId;
		Vec3											mTaegetPos;
	};
}

#endif