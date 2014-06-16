/******************************************************************************/
#ifndef _S_PVE_NET_PACKET_PROCESSER_H_
#define _S_PVE_NET_PACKET_PROCESSER_H_
/******************************************************************************/


#include "FrontServerPreqs.h"
#include "PveNetPacket.h"
#include "SPlayer.h"

/******************************************************************************/
namespace MG
{

	class SPveNetPacketProcessor
	{
	public:
		SINGLETON_INSTANCE(SPveNetPacketProcessor);
		SPveNetPacketProcessor();
		~SPveNetPacketProcessor();

		Bool	processMapServerPacket(I32 id, NetEventRecv* packet);
		Bool	processCenterServerPacket(I32 id, NetEventRecv* packet);
		Bool	processClientPacket(I32 id, NetEventRecv* packet);

	public:
		void	sendPveDisconnectToCenterServer(SPlayerPtr player);

		void	sendPveStartToClient(SPlayerPtr& player);

	public:
		void    onRecvPveCreateFromClient(I32 id, PT_PVE_C2F_CREATE_DATA* data);
		void    onRecvPveRoomListFromClient(I32 id, PT_PVE_C2F_ROOM_LIST_DATA* data);
		void    onRecvPveEnterRoomFromClient(I32 id, PT_PVE_C2F_ENTER_ROOM_DATA* data);
		void    onRecvPveLeaveRoomFromClient(I32 id, PT_PVE_C2F_LEAVE_ROOM_DATA* data);
		void    onRecvPveStartFromClient(I32 id, PT_PVE_C2F_START_DATA* data);
		void    onRecvPveKickFromClient(I32 id, PT_PVE_C2F_KICK_DATA* data);


		void    onRecvCreateRoomFromCenterServer(I32 id, PT_PVE_T2C_CREATE_DATA* data);
		void    onRecvLeaveRoomFromCenterServer(I32 id, PT_PVE_T2C_LEAVE_ROOM_DATA* data);
		void    onRecvDestroyRoomFromCenterServer(I32 id, PT_PVE_T2C_DESTROY_ROOM_DATA* data);
		void    onRecvStartRoomFromCenterServer(I32 id, PT_PVE_T2F_START_DATA* data);
		void    onRecvStartJumpRegionFromCenterServer(I32 id, PT_PVE_T2F_START_JUMP_REGION_DATA* data);

	};
}

#endif	//_CAMPAIGNNETPACKETPROCESSER_H_