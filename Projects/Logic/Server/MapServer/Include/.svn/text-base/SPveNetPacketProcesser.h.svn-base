/******************************************************************************/
#ifndef _S_PVE_NET_PACKET_PROCESSER_H_
#define _S_PVE_NET_PACKET_PROCESSER_H_
/******************************************************************************/

#include "MapServerPreqs.h"
#include "PveNetPacket.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************/
	//PVE网络消息处理
	/******************************************************************************/
	class SPveNetPacketProcesser
	{
	public:
		SINGLETON_INSTANCE(SPveNetPacketProcesser);
		SPveNetPacketProcesser();
		~SPveNetPacketProcesser();

		Bool	processFrontServerPacket(I32 id, NetEventRecv* packet);

	
		void	onRecvPveStartFromFrontServer(NetIdType frontServerNetId, PT_PVE_F2M_START_DATA* data);
	};

}


#endif	//_S_PVE_NET_PACKET_PROCESSER_H_