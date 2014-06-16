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
	//角色相关网络消息处理
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

		//当接受到怪物被玩家杀死
		void onRecvMonsterBeKilledByPlayerCharacterFromMapServer(I32 id,PT_MONSTER_M2F_BEKILLED* data);

		//@{ MapServer
	public:
		//发送角色移动消息
		//void sendMonsterMoveToMapServer(I32 id, PT_MONSTER_C2F_MOVE_POS_DATA* data );
	protected:


		//@ }
	};

}


#endif