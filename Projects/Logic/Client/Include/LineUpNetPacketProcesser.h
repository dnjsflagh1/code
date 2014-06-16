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
		Bool	processLoginServerPacket(I32 id,NetEventRecv* packet);
		Bool	processFrontServerPacket(I32 id,NetEventRecv* packet);
		// 当收到排队信息
		void	onRecvLineUpInfoFromLoginServer(I32 netId,PT_LINE_UP_L2C_DATA* data);
		void	onRecvLineUpInfoFromFrontServer(I32 netId,PT_LINE_UP_F2C_DATA* data);

		// 当收到取消排队结果
		void	onRecvClientCancleLineUpCmdResultFromLoginServer(I32 netId,PT_LINE_UP_L2C_CANCLE_CMD_RELULT_DATA* data);
		void	onRecvClientCancleLineUpCmdResultFromFrontServer(I32 netId,PT_LINE_UP_F2C_CANCLE_CMD_RELULT_DATA* data);
		// 发送取消排队命令
		void	sendCancleLineUpCmdToLoginServer(I32 netId,Byte type);
		void	sendCancleLineUpCmdToFrontServer(I32 netId,Byte type);

	};
}
#endif