/******************************************************************************/
#ifndef _TIMENETPACKETPROCESSER_H_
#define _TIMENETPACKETPROCESSER_H_
/******************************************************************************/
#include "GameNetPacket.h"
#include "CenterServerPreqs.h"
#include "TimeNetPacket.h"
/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//服务器状态相关网络消息处理
	/******************************************************************************/
	class TimeNetPacketProcesser
	{
	public:
		SINGLETON_INSTANCE(TimeNetPacketProcesser);
		TimeNetPacketProcesser();
		~TimeNetPacketProcesser();

		Bool	processMapServerPacket(I32 id,NetEventRecv* packet);
		Bool	processFrontServerPacket(I32 id,NetEventRecv* packet);

		void	onRecvGetTime(I32 id);
	};
}
#endif //_TIMENETPACKETPROCESSER_H_