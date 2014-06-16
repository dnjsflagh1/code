/******************************************************************************/
#ifndef _SERVERSTATENETPACKETPROCESSER_H_
#define _SERVERSTATENETPACKETPROCESSER_H_
/******************************************************************************/
#include "ServerStateNetPacket.h"
#include "CenterServerPreqs.h"
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
		Bool	processFrontServerPacket(I32 id,NetEventRecv* packet);
	};
}
#endif //_SERVERSTATENETPACKETPROCESSER_H_
