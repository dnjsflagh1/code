/******************************************************************************/
#ifndef _TIMENETPACKETPROCESSER_H_
#define _TIMENETPACKETPROCESSER_H_
/******************************************************************************/
#include "TimeNetPacket.h"
#include "GameNetEvent.h"
/******************************************************************************/

namespace MG
{

	class TimeNetPacketProcesser
	{
	public:
		SINGLETON_INSTANCE(TimeNetPacketProcesser);
		Bool	processFrontServerPacket(I32 id,NetEventRecv* packet);
		void	onRecvSyncTime( I32 id , PT_TIME_E2S_SYNC_DATA* data);
	};
}
#endif

