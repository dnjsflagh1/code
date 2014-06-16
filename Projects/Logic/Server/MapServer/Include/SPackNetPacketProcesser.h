/******************************************************************************/
#ifndef _SPACKNETPACKETPROCESSER_H_
#define _SPACKNETPACKETPROCESSER_H_
/******************************************************************************/

#include "MapServerPreqs.h"
#include "LoginNetPacket.h"
#include "PackNetPacket.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************/
	//角色相关网络消息处理
	/******************************************************************************/
	class SPackNetPacketProcesser
	{
	public:
		SINGLETON_INSTANCE(SPackNetPacketProcesser);
		SPackNetPacketProcesser();
		~SPackNetPacketProcesser();

		Bool	processFrontServerPacket(I32 id, NetEventRecv* packet);
		Bool	processMapServerPacket(I32 id, NetEventRecv* packet);

	public:
		////一些具体发送包方法

		//void sendPlayerCharacterJumpregionResult(SPlayerCharacter* playerCharacter);

		////广播角色移动消息
		//void	broadcastPlayerCharacterMove(SPlayerCharacter* playerCharacter, NetVec2 startMovePos);


	protected:
		//一些具体处理包方法

		void	onRecvCharacterPackFromFrontServer( I32 id , PT_PACK_C2S_CHARACTER_DATA* data);

	protected:
  

	};

}


#endif