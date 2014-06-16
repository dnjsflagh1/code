/******************************************************************************/
#ifndef _S_PVE_NET_PACKET_PROCESSER_H_
#define _S_PVE_NET_PACKET_PROCESSER_H_
/******************************************************************************/

#include "CenterServerPreqs.h"
#include "PveNetPacket.h"



/******************************************************************************/
namespace MG
{
	class SPveNetPacketProcesser
	{
	public:
		SPveNetPacketProcesser();
		~SPveNetPacketProcesser();
		SINGLETON_INSTANCE(SPveNetPacketProcesser);

		Bool	processFrontServerPacket(I32 id, NetEventRecv* packet);

		//FrontServer 异常断开的情况
		void	processFrontServerDisconnect(NetIdType frontServerNetId);

		//接收消息
		void    onRecvDisconnectFromFrontServer(NetIdType frontServerNetId, PT_PVE_F2T_DISCONNECT_DATA* data );
		void    onRecvRoomListFromFrontServer(NetIdType frontServerNetId, PT_PVE_F2T_ROOM_LIST_DATA* data );
		void    onRecvCreateFromFrontServer(NetIdType frontServerNetId, PT_PVE_F2T_CREATE_DATA* data );
		void    onRecvEnterRoomFromFrontServer(NetIdType frontServerNetId, PT_PVE_F2T_ENTER_ROOM_DATA* data );
		void    onRecvLeaveRoomFromFrontServer(NetIdType frontServerNetId, PT_PVE_F2T_LEAVE_ROOM_DATA* data );
		void    onRecvStartRoomFromFrontServer(NetIdType frontServerNetId, PT_PVE_F2T_START_DATA* data );
		void    onRecvStartNewInstanceFromMapServer(NetIdType mapServerNetId, PT_PVE_M2T_START_NEW_INSTANCE_DATA* data );
		void    onRecvKickFromFrontServer(NetIdType frontServerNetId, PT_PVE_F2T_KICK_DATA* data );

		//发送消息
		void	sendPveErrorToFrontServer(NetIdType frontserverNetId, Pve_Error error, NetIdType clientNetId, AccountIdType accountId);
		void	sendPveRoomListBeginToClient(NetIdType frontserverNetId, const NetIdType clientNetId,const AccountIdType accountId);
		void	sendPveRoomListEndToClient(NetIdType frontserverNetId, const NetIdType clientNetId,const AccountIdType accountId);


	private:
		void	_sendMemberListToClientBegin(NetIdType frontserverNetId, const NetIdType clientNetId,const AccountIdType accountId);
		void	_sendMemberListToClient(std::map<Pve_Position, SPveMember*>* memberList, const SPveMember* newMember);
		void	_sendMemberListToClientEnd(NetIdType frontserverNetId, const NetIdType clientNetId,const AccountIdType accountId);

		void	_sendPveMemberJumpRegion(const SPveMember* pveMember, RegionIdType targetRegionId, InstanceUIdType targetInstanceUId);

		void	_destroyRoom(PT_PVE_F2T_LEAVE_ROOM_DATA* data, SPveRoom* pveRoom, NetIdType frontServerNetId);
		void	_leaveRoom(PT_PVE_F2T_LEAVE_ROOM_DATA* data, SPveRoom* pveRoom, NetIdType frontServerNetId);
	};
}

#endif	//_S_PVE_NET_PACKET_PROCESSER_H_