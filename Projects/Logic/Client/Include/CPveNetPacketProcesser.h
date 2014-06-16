/******************************************************************************/
#ifndef _C_PVE_NET_PACKET_PROCESSER_H_
#define _C_PVE_NET_PACKET_PROCESSER_H_
/******************************************************************************/
#include "ClientPreqs.h"
#include "PveNetPacket.h"
#include "GameNetEvent.h"

/******************************************************************************/
namespace MG
{
	class CPveNetPacketProcesser
	{
	public:
		CPveNetPacketProcesser(){};
		~CPveNetPacketProcesser(){}
		SINGLETON_INSTANCE(CPveNetPacketProcesser)

		Bool	processFrontServerPacket(I32 id,NetEventRecv* packet);

	public:
		void	sendPveRoomList();
		void	sendPveCreate(AccountIdType creatorAccountId, RegionIdType targetRegionId, const Char16* pveName);
		void	sendPveEnterRoom(int roomId);
		void	sendPveLeaveRoom(AccountIdType accountId);
		void	sendPveStart(AccountIdType accountId);
		void	sendPveKickMember(AccountIdType leaderAccountId, AccountIdType kickAccountId);

	public:
		void	onRecvPveError(I32 id, PT_PVE_T2C_ERROR_DATA* data);
		void	onRecvPveCreate(I32 id, PT_PVE_T2C_CREATE_DATA* data);
		void	onRecvPveRoomListBegin(I32 id, PT_PVE_T2C_ROOM_LIST_BEGIN_DATA* data);
		void	onRecvPveRoomList(I32 id, PT_PVE_T2C_ROOM_LIST_DATA* data);
		void	onRecvPveRoomListEnd(I32 id, PT_PVE_T2C_ROOM_LIST_END_DATA* data);

		void	onRecvEnterRoom(I32 id, PT_PVE_T2C_ENTER_ROOM_DATA* data);
		void	onRecvLeaveRoom(I32 id, PT_PVE_T2C_LEAVE_ROOM_DATA* data);
		void	onRecvDestroyRoom(I32 id, PT_PVE_T2C_DESTROY_ROOM_DATA* data);

		void	onRecvPveStart(I32 id, PT_PVE_F2C_START_DATA* data);

		void	onRecvMemberListBegin(I32 id, PT_PVE_T2C_MEMBER_LIST_BEGIN_DATA* data);
		void	onRecvMemberList(I32 id, PT_PVE_T2C_MEMBER_LIST_DATA* data);
		void	onRecvMemberListEnd(I32 id, PT_PVE_T2C_MEMBER_LIST_END_DATA* data);
	};
}

#endif	//_C_PVE_NET_PACKET_PROCESSER_H_
