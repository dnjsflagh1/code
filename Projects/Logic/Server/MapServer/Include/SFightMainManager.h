/******************************************************************************/
#ifndef _SFIGHTMAINMANAGER_H_
#define _SFIGHTMAINMANAGER_H_
/******************************************************************************/
#include "MapServerPreqs.h"

/******************************************************************************/

/******************************************************************************/
//战斗主管理
/******************************************************************************/

namespace MG
{
	class SFightMainManager
	{
	public:
		SFightMainManager();
		~SFightMainManager();
		SINGLETON_INSTANCE(SFightMainManager)

	public:
		//邀请添加战斗信息
		virtual void						addAndUpdateFightOnAppoint( SCharacter* fightCharacter, SCharacter* fightOtherCharacter );
		//攻击技能添加战斗信息
		virtual void						addAndUpdateFightOnUseAttackSkill( SCharacter* fightCharacter, SCharacter* fightOtherCharacter, UInt hateVal );
		//索敌添加战斗信息
		virtual void						addAndUpdateFightOnGuard( SCharacter* fightCharacter, SCharacter* fightOtherCharacter );
		//辅助技能添加战斗信息
		virtual void						addAndUpdateFightOnUseAuxiliarySkill( SCharacter* fightCharacter, SCharacter* fightOtherCharacter, UInt hateVal );

		//////////////////////////////////////////////////////////////////////////////////////////////////////
		//离开范围删除战斗信息
		virtual void						delFightOnScope( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID, GAMEOBJ_TYPE fightOtherObjectType, IdType fightOtherObjectID );
		//超过结束时间删除战斗信息
		virtual void						delFightOnEndTime( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID, GAMEOBJ_TYPE fightOtherObjectType, IdType fightOtherObjectID );
		//超过追击距离删除战斗信息
		virtual void						delFightOnPursue( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID, GAMEOBJ_TYPE fightOtherObjectType, IdType fightOtherObjectID );

		//删除所有战斗信息
		virtual void						delAllFightInfo( SCharacter* character );

	protected:
		virtual void						addAndUpdateAllFight( SCharacter* fightCharacter, SCharacter* fightOtherCharacter, UInt hateVal, Bool isOwnerAdd );

	};

}

#endif