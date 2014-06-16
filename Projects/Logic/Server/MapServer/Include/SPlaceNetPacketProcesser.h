/******************************************************************************/
#ifndef _SPLACENETPACKETPROCESSER_H_
#define _SPLACENETPACKETPROCESSER_H_
/******************************************************************************/

#include "MapServerPreqs.h"
#include "GameNetPacket.h"
#include "PlaceNetPacket.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************/
	//据点地图网络消息处理
	/******************************************************************************/
	class SPlaceNetPacketProcesser
	{
	public:
		SINGLETON_INSTANCE(SPlaceNetPacketProcesser);
		SPlaceNetPacketProcesser();
		~SPlaceNetPacketProcesser();

		Bool	processFrontServerPacket(I32 id, NetEventRecv* packet);

	public:
		//发送据点基础数据到客户端
		void	sendPlaceBaseInfoToPlayer( Player* player, SMapObject* placeObject );
	public:

		void	onRecvPlaceClickFromFrontServer(I32 id, PT_PLACE_F2M_CLICED_INFO_DATA* data);

	protected:

	};

}


#endif