/******************************************************************************/
#ifndef _CFIGHTMAINMANAGER_H_
#define _CFIGHTMAINMANAGER_H_
/******************************************************************************/
#include "FightMainManager.h"
#include "ClientPreqs.h"

/******************************************************************************/

/******************************************************************************/
//ս��������
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
	//	//�������ս����Ϣ
	//	virtual void						addAndUpdateFightOnAppoint( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID, GAMEOBJ_TYPE fightOtherObjectType, IdType fightOtherObjectID );
	//	//�����������ս����Ϣ
	//	virtual void						addAndUpdateFightOnUseAttackSkill( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID, GAMEOBJ_TYPE fightOtherObjectType, IdType fightOtherObjectID, IdType skillId, IdType addHateGameObjID, UInt hateVal );
	//	//�������ս����Ϣ
	//	virtual void						addAndUpdateFightOnGuard( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID, GAMEOBJ_TYPE fightOtherObjectType, IdType fightOtherObjectID );
	//	//�����������ս����Ϣ
	//	virtual void						addAndUpdateFightOnUseAuxiliarySkill( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID, GAMEOBJ_TYPE fightOtherObjectType, IdType fightOtherObjectID, UInt hateVal );

	//	//////////////////////////////////////////////////////////////////////////////////////////////////////
	//	//�뿪��Χɾ��ս����Ϣ
	//	virtual void						delFightOnScope( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID, GAMEOBJ_TYPE fightOtherObjectType, IdType fightOtherObjectID );
	//	//��������ʱ��ɾ��ս����Ϣ
	//	virtual void						delFightOnEndTime( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID, GAMEOBJ_TYPE fightOtherObjectType, IdType fightOtherObjectID );
	//	//����׷������ɾ��ս����Ϣ
	//	virtual void						delFightOnPursue( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID, GAMEOBJ_TYPE fightOtherObjectType, IdType fightOtherObjectID );

	//	//ɾ������ս����Ϣ
	//	virtual void						delAllFightInfo( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID );

	//	//////////////////////////////////////////////////////////////////////////////////////////////////////

	//	FightManager*						getFightManager( GAMEOBJ_TYPE gameObjType, IdType gameObjID );

	//protected:
	//	virtual void						addAndUpdateAllFight( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID, GAMEOBJ_TYPE fightOtherObjectType, IdType fightOtherObjectID , UInt hateVal, Bool isOwnerAdd );

	//};

}

#endif