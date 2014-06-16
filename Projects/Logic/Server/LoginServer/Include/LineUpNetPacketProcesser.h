/******************************************************************************/
#ifndef _LINEUPNETPACKETPROCESSER_H_
#define _LINEUPNETPACKETPROCESSER_H_
/******************************************************************************/

#include "NetAddress.h"
#include "GameNetPacket.h"
#include "LineUpNetPacket.h"

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//排队消息处理
	/******************************************************************************/
	class LineUpNetPacketProcesser
	{
	public:
		SINGLETON_INSTANCE(LineUpNetPacketProcesser);

	public:
		Bool	processClientPacket(I32 id,NetEventRecv* packet);

		void	sendLineUpInfoToClient(I32 netId,Byte type,I32 waitCount = 0);
		void	onRecvCancleLineUpCmd(I32 netId,PT_LINE_UP_C2L_CANCLE_CMD_DATA* data);
		void	sendCancleLineCmdRelustToClient(I32 netId,Byte type,Byte result);

	};
}
#endif