/******************************************************************************/
#ifndef _FIGHTMAINMANAGER_H_
#define _FIGHTMAINMANAGER_H_
/******************************************************************************/
#include "WorldCoreDefine.h"
#include "CommonGameDefine.h"

/******************************************************************************/

/******************************************************************************/
//战斗管理
/******************************************************************************/

namespace MG
{
	class FightMainManager
	{
	public:
		FightMainManager();
		~FightMainManager();

	public:
		//邀请添加战斗信息
		virtual void						addAndUpdateFightOnAppoint( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID, GAMEOBJ_TYPE fightOtherObjectType, IdType fightOtherObjectID ) = 0;
		//攻击技能添加战斗信息
		virtual void						addAndUpdateFightOnUseAttackSkill( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID, GAMEOBJ_TYPE fightOtherObjectType, IdType fightOtherObjectID, IdType skillId, IdType addHateGameObjID, UInt hateVal ) = 0;
		//索敌添加战斗信息
		virtual void						addAndUpdateFightOnGuard( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID, GAMEOBJ_TYPE fightOtherObjectType, IdType fightOtherObjectID ) = 0;
		//辅助技能添加战斗信息
		virtual void						addAndUpdateFightOnUseAuxiliarySkill( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID, GAMEOBJ_TYPE fightOtherObjectType, IdType fightOtherObjectID, UInt hateVal ) = 0;

		//////////////////////////////////////////////////////////////////////////////////////////////////////
		//离开范围删除战斗信息
		virtual void						delFightOnScope( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID, GAMEOBJ_TYPE fightOtherObjectType, IdType fightOtherObjectID ) = 0;
		//超过结束时间删除战斗信息
		virtual void						delFightOnEndTime( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID, GAMEOBJ_TYPE fightOtherObjectType, IdType fightOtherObjectID ) = 0;
		//超过追击距离删除战斗信息
		virtual void						delFightOnPursue( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID, GAMEOBJ_TYPE fightOtherObjectType, IdType fightOtherObjectID ) = 0;

		//删除所有战斗信息
		virtual void						delAllFightInfo( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID ) = 0;

	protected:
		virtual void						addAndUpdateAllFight( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID, GAMEOBJ_TYPE fightOtherObjectType, IdType fightOtherObjectID , UInt hateVal, Bool isOwnerAdd ) = 0;
	

	};

}

#endif