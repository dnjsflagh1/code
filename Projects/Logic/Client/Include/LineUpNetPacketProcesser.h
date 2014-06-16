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
	//�Ŷ���Ϣ����
	/******************************************************************************/
	class LineUpNetPacketProcesser
	{
	public:
		SINGLETON_INSTANCE(LineUpNetPacketProcesser);

	public:
		Bool	processLoginServerPacket(I32 id,NetEventRecv* packet);
		Bool	processFrontServerPacket(I32 id,NetEventRecv* packet);
		// ���յ��Ŷ���Ϣ
		void	onRecvLineUpInfoFromLoginServer(I32 netId,PT_LINE_UP_L2C_DATA* data);
		void	onRecvLineUpInfoFromFrontServer(I32 netId,PT_LINE_UP_F2C_DATA* data);

		// ���յ�ȡ���Ŷӽ��
		void	onRecvClientCancleLineUpCmdResultFromLoginServer(I32 netId,PT_LINE_UP_L2C_CANCLE_CMD_RELULT_DATA* data);
		void	onRecvClientCancleLineUpCmdResultFromFrontServer(I32 netId,PT_LINE_UP_F2C_CANCLE_CMD_RELULT_DATA* data);
		// ����ȡ���Ŷ�����
		void	sendCancleLineUpCmdToLoginServer(I32 netId,Byte type);
		void	sendCancleLineUpCmdToFrontServer(I32 netId,Byte type);

	};
}
#endif