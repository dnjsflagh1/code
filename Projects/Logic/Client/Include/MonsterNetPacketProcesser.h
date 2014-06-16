/******************************************************************************/
#ifndef _MONSTERNETPACKETPROCESSER_H_
#define _MONSTERNETPACKETPROCESSER_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "NetAddress.h"
#include "GameNetEvent.h"
#include "MonsterNetPacket.h"

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//��ɫ��Ϣ���ɶ���
	/******************************************************************************/
	class MonsterNetPacketProcesser
	{
	public:
		SINGLETON_INSTANCE(MonsterNetPacketProcesser)

		Bool	processFrontServerPacket(I32 id,NetEventRecv* packet);

		// ���͵�NetPacketPackManager�������д������
		void	onRecvMonsterMove( I32 id, PT_MONSTER_S2C_MOVE_POS_DATA* data );
		void	onRecvInstantMonsterMove( I32 id, PT_MONSTER_S2C_INSTANT_MOVE_POS_DATA* data );
		void	onRecvMonsterStopMove( I32 id, PT_MONSTER_S2C_STOP_MOVE_DATA* data );

		void    onRecvMonsterEnterFight(I32 id, PT_MONSTER_S2C_ENTER_FIGHT_DATA* data);
		void    onRecvMonsterEndFight(I32 id, PT_MONSTER_S2C_END_FIGHT_DATA* data);


	private:
		/*void	sendPlayerCharacterPackBuffer(IdType id);*/

	};
}

#endif