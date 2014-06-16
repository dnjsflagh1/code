/******************************************************************************/
#ifndef _PACKNETPACKETPROCESSER_H_
#define _PACKNETPACKETPROCESSER_H_
/******************************************************************************/
#include "PackNetPacket.h"
#include "FrontServerPreqs.h"
/******************************************************************************/

namespace MG
{

	/******************************************************************************/
	//角色相关网络消息处理
	/******************************************************************************/

	/******************************************************************************/
	class PackNetPacketProcesser
	{
	public:
		SINGLETON_INSTANCE(PackNetPacketProcesser);
		PackNetPacketProcesser();
		~PackNetPacketProcesser();

		Bool	processClientPacket(I32 id, NetEventRecv* packet);
		Bool	processLoginServerPacket(I32 id, NetEventRecv* packet);
		Bool	processMapServerPacket(I32 id, NetEventRecv* packet);

	public:

		//************************************************************

		//@{ Client

	protected:

		void	onRecvCharacterPack( I32 id, NetEventRecv* packet );

	protected:

		//@ }
	};

}


#endif