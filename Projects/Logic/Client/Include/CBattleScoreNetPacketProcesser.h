/******************************************************************************/
#ifndef _C_BATTLE_SCORE_NET_PACKET_PROCESSER_H_
#define _C_BATTLE_SCORE_NET_PACKET_PROCESSER_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "GameNetEvent.h"
#include "BattleScoreNetPacket.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************/
	//据点地图网络消息处理
	/******************************************************************************/
	class CBattleScoreNetPacketProcesser
	{
	public:
		CBattleScoreNetPacketProcesser();
		~CBattleScoreNetPacketProcesser();
		SINGLETON_INSTANCE(CBattleScoreNetPacketProcesser);

		Bool	processFrontServerPacket(I32 id,NetEventRecv* packet);


		void	onRecvBattleScoreNotifyFromFrontServer(I32 id, PT_BATTLESCORE_M2C_NOTIFY_DATA* data);
	};

}


#endif	//_C_BATTLE_SCORE_NET_PACKET_PROCESSER_H_