#ifndef _SERVERSTATENETPACKETPROCESSER_H_
#define _SERVERSTATENETPACKETPROCESSER_H_

/******************************************************************************/
#include "FrontServerPreqs.h"
#include "ServerStateNetPacket.h"
/******************************************************************************/

namespace MG
{

	/******************************************************************************/
	//服务器状态相关网络消息处理
	/******************************************************************************/
	class ServerStateNetPacketProcesser
	{
	public:
		SINGLETON_INSTANCE(ServerStateNetPacketProcesser);

		Bool	processMapServerPacket(I32 id,NetEventRecv* packet);
		Bool	processCenterServerPacket(I32 id,NetEventRecv* packet);
		
		void	onRecvSyncServerStateNewStart( I32 id , PT_SERVER_STATE_S2S_SYNC_MAPSERVER_STATE_NEW_START_DATA* data);
		void	onRecvSyncServerStateNew( I32 id , PT_SERVER_STATE_S2S_SYNC_MAPSERVER_STATE_NEW_DATA* data);
	};
}
#endif //_SERVERSTATENETPACKETPROCESSER_H_