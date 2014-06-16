/******************************************************************************/
#ifndef _SFIGHTMAINMANAGER_H_
#define _SFIGHTMAINMANAGER_H_
/******************************************************************************/
#include "MapServerPreqs.h"

/******************************************************************************/

/******************************************************************************/
//ս��������
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
		//�������ս����Ϣ
		virtual void						addAndUpdateFightOnAppoint( SCharacter* fightCharacter, SCharacter* fightOtherCharacter );
		//�����������ս����Ϣ
		virtual void						addAndUpdateFightOnUseAttackSkill( SCharacter* fightCharacter, SCharacter* fightOtherCharacter, UInt hateVal );
		//�������ս����Ϣ
		virtual void						addAndUpdateFightOnGuard( SCharacter* fightCharacter, SCharacter* fightOtherCharacter );
		//�����������ս����Ϣ
		virtual void						addAndUpdateFightOnUseAuxiliarySkill( SCharacter* fightCharacter, SCharacter* fightOtherCharacter, UInt hateVal );

		//////////////////////////////////////////////////////////////////////////////////////////////////////
		//�뿪��Χɾ��ս����Ϣ
		virtual void						delFightOnScope( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID, GAMEOBJ_TYPE fightOtherObjectType, IdType fightOtherObjectID );
		//��������ʱ��ɾ��ս����Ϣ
		virtual void						delFightOnEndTime( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID, GAMEOBJ_TYPE fightOtherObjectType, IdType fightOtherObjectID );
		//����׷������ɾ��ս����Ϣ
		virtual void						delFightOnPursue( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID, GAMEOBJ_TYPE fightOtherObjectType, IdType fightOtherObjectID );

		//ɾ������ս����Ϣ
		virtual void						delAllFightInfo( SCharacter* character );

	protected:
		virtual void						addAndUpdateAllFight( SCharacter* fightCharacter, SCharacter* fightOtherCharacter, UInt hateVal, Bool isOwnerAdd );

	};

}

#endif