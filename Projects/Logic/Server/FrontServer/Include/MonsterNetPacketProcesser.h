/******************************************************************************/
#ifndef _MONSTERNETPACKETPROCESSER_H_
#define _MONSTERNETPACKETPROCESSER_H_
/******************************************************************************/

#include "MonsterNetPacket.h"
#include "FrontServerPreqs.h"
/******************************************************************************/

namespace MG
{

	/******************************************************************************/
	//��ɫ���������Ϣ����
	/******************************************************************************/
	class SPlayer;
	/******************************************************************************/
	class MonsterNetPacketProcesser
	{
	public:
		SINGLETON_INSTANCE(MonsterNetPacketProcesser);
		MonsterNetPacketProcesser();
		~MonsterNetPacketProcesser();

		Bool	processClientPacket(I32 id, NetEventRecv* packet);
		Bool	processLoginServerPacket(I32 id, NetEventRecv* packet);
		Bool	processMapServerPacket(I32 id, NetEventRecv* packet);

	public:

		//************************************************************

		//@{ Client

	protected:

		//�����ܵ����ﱻ���ɱ��
		void onRecvMonsterBeKilledByPlayerCharacterFromMapServer(I32 id,PT_MONSTER_M2F_BEKILLED* data);

		//@{ MapServer
	public:
		//���ͽ�ɫ�ƶ���Ϣ
		//void sendMonsterMoveToMapServer(I32 id, PT_MONSTER_C2F_MOVE_POS_DATA* data );
	protected:


		//@ }
	};

}


#endif