/******************************************************************************/
#include "MapServerPreqs.h"
#include "ServerStateNetPacket.h"
/******************************************************************************/

namespace MG
{

	/******************************************************************************/
	//服务器状态相关网络消息处理
	//主要是用来同步 MapServer 和 FrontServer之间的状态
	/******************************************************************************/
	class ServerStateNetPacketProcesser
	{
	public:
		SINGLETON_INSTANCE(ServerStateNetPacketProcesser);
		Bool	processCenterServerPacket(I32 id,NetEventRecv* packet);
		
		//当收到同步服务器状态
		//void	onRecvSyncServerState( I32 id , PT_SERVER_STATE_S2S_SYNC_MAPSERVER_STATE_DATA* data);
		void	onRecvSyncServerStateNew( I32 id , PT_SERVER_STATE_S2S_SYNC_MAPSERVER_STATE_NEW_DATA* data);
		
	};
}