/******************************************************************************/
#ifndef _BATTLE_SCORE_NET_PACKET_PROCESSER_H_
#define _BATTLE_SCORE_NET_PACKET_PROCESSER_H_
/******************************************************************************/

#include "MapServerPreqs.h"
#include "GameNetPacket.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************/
	//据点地图网络消息处理
	/******************************************************************************/
	class SBattleScoreNetPacketProcesser
	{
	public:
		SBattleScoreNetPacketProcesser();
		~SBattleScoreNetPacketProcesser();
		SINGLETON_INSTANCE(SBattleScoreNetPacketProcesser);

		void	sendBattleScoreNotify(const Int rankId, SRegionObjectBase* region);

	};

}


#endif	//_BATTLE_SCORE_NET_PACKET_PROCESSER_H_