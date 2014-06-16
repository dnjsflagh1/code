/******************************************************************************/
#ifndef _SPLACENETPACKETPROCESSER_H_
#define _SPLACENETPACKETPROCESSER_H_
/******************************************************************************/
#include "PlaceNetPacket.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************/
	//据点消息处理
	/******************************************************************************/
	class SPlaceNetPacketProcesser
	{
	public:
		SINGLETON_INSTANCE(SPlaceNetPacketProcesser);
		SPlaceNetPacketProcesser();
		~SPlaceNetPacketProcesser();

		Bool	processClientPacket(I32 id, NetEventRecv* packet);

	public:

		//当收到据点请求点击消息是发送据点信息到MapServer
		void	onRecvPlaceClickFromClient( I32 netId, PT_PLACE_C2F_CLICED_INFO_DATA* data);

	protected:


	};

}


#endif