/******************************************************************************/
#ifndef _SMAPNETPACKETPROCESSER_H_
#define _SMAPNETPACKETPROCESSER_H_
/******************************************************************************/

#include "MapServerPreqs.h"
#include "GameNetPacket.h"
//#include "MapNetPacket.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************/
	//分块地图网络消息处理
	/******************************************************************************/
	class SMapNetPacketProcesser
	{
	public:
		SINGLETON_INSTANCE(SMapNetPacketProcesser);
		SMapNetPacketProcesser();
		~SMapNetPacketProcesser();

		Bool	processFrontServerPacket(I32 id, NetEventRecv* packet);

	public:

	//@{ FrontServer
	public:

		//发送地图基础数据到客户端
		void	sendMapBaseInfoToPlayer( SPlayer* player, SMapObject* mapObject );

	protected:


	//@ }

	};

}


#endif