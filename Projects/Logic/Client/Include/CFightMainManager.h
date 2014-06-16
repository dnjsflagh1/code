/******************************************************************************/
#ifndef _CFIGHTMAINMANAGER_H_
#define _CFIGHTMAINMANAGER_H_
/******************************************************************************/
#include "FightMainManager.h"
#include "ClientPreqs.h"

/******************************************************************************/

/******************************************************************************/
//战斗主管理
/******************************************************************************/

namespace MG
{
	//class CFightMainManager : public FightMainManager
	//{
	//public:
	//	CFightMainManager();
	//	~CFightMainManager();
	//	SINGLETON_INSTANCE(CFightMainManager)

	//public:
	//	//邀请添加战斗信息
	//	virtual void						addAndUpdateFightOnAppoint( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID, GAMEOBJ_TYPE fightOtherObjectType, IdType fightOtherObjectID );
	//	//攻击技能添加战斗信息
	//	virtual void						addAndUpdateFightOnUseAttackSkill( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID, GAMEOBJ_TYPE fightOtherObjectType, IdType fightOtherObjectID, IdType skillId, IdType addHateGameObjID, UInt hateVal );
	//	//索敌添加战斗信息
	//	virtual void						addAndUpdateFightOnGuard( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID, GAMEOBJ_TYPE fightOtherObjectType, IdType fightOtherObjectID );
	//	//辅助技能添加战斗信息
	//	virtual void						addAndUpdateFightOnUseAuxiliarySkill( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID, GAMEOBJ_TYPE fightOtherObjectType, IdType fightOtherObjectID, UInt hateVal );

	//	//////////////////////////////////////////////////////////////////////////////////////////////////////
	//	//离开范围删除战斗信息
	//	virtual void						delFightOnScope( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID, GAMEOBJ_TYPE fightOtherObjectType, IdType fightOtherObjectID );
	//	//超过结束时间删除战斗信息
	//	virtual void						delFightOnEndTime( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID, GAMEOBJ_TYPE fightOtherObjectType, IdType fightOtherObjectID );
	//	//超过追击距离删除战斗信息
	//	virtual void						delFightOnPursue( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID, GAMEOBJ_TYPE fightOtherObjectType, IdType fightOtherObjectID );

	//	//删除所有战斗信息
	//	virtual void						delAllFightInfo( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID );

	//	//////////////////////////////////////////////////////////////////////////////////////////////////////

	//	FightManager*						getFightManager( GAMEOBJ_TYPE gameObjType, IdType gameObjID );

	//protected:
	//	virtual void						addAndUpdateAllFight( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID, GAMEOBJ_TYPE fightOtherObjectType, IdType fightOtherObjectID , UInt hateVal, Bool isOwnerAdd );

	//};

}

#endif