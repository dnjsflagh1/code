/******************************************************************************/
#ifndef _TIMENETPACKETPROCESSER_H_
#define _TIMENETPACKETPROCESSER_H_
/******************************************************************************/
#include "TimeNetPacket.h"
/******************************************************************************/

namespace MG
{

	class TimeNetPacketProcesser
	{
	public:
		SINGLETON_INSTANCE(TimeNetPacketProcesser);

	public:
		Bool	processCenterServerPacket(I32 id,NetEventRecv* packet);
		void	onRecvSyncTime( I32 id , PT_TIME_E2S_SYNC_DATA* data);
		void	getTimeFromCenterServer();
	};
}
#endif

