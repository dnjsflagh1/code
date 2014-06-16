/******************************************************************************/
#ifndef _PVE_NET_PACKET_H_
#define _PVE_NET_PACKET_H_
/******************************************************************************/
#include "CommonGameDefine.h"
#include "NetDefine.h"
/******************************************************************************/

namespace MG
{
	/******************************************************************************/
	//Pve数据包想关类型
	/******************************************************************************/
	enum PveNetPacket
	{
		PT_PVE_UNKNOWN = 0,

		PT_PVE_T2C_ERROR,			//错误

		PT_PVE_C2F_ROOM_LIST,			//所有PVE房间的列表
		PT_PVE_F2T_ROOM_LIST,
		PT_PVE_T2C_ROOM_LIST_BEGIN,
		PT_PVE_T2C_ROOM_LIST,
		PT_PVE_T2C_ROOM_LIST_END,


		PT_PVE_C2F_CREATE,				//创建pve 队伍
		PT_PVE_F2T_CREATE,
		PT_PVE_T2C_CREATE,

		PT_PVE_C2F_ENTER_ROOM,
		PT_PVE_F2T_ENTER_ROOM,
		PT_PVE_T2C_ENTER_ROOM,

		PT_PVE_T2C_MEMBER_LIST_BEGIN,
		PT_PVE_T2C_MEMBER_LIST,			//房间里的玩家列表
		PT_PVE_T2C_MEMBER_LIST_END,

		PT_PVE_C2F_LEAVE_ROOM,
		PT_PVE_F2T_LEAVE_ROOM,
		PT_PVE_T2C_LEAVE_ROOM,

		PT_PVE_T2C_DESTROY_ROOM,

		PT_PVE_C2F_START,
		PT_PVE_F2T_START,
		PT_PVE_T2F_START,
		PT_PVE_F2M_START,
		PT_PVE_M2T_START_NEW_INSTANCE,
		PT_PVE_T2F_START_JUMP_REGION,
		PT_PVE_F2C_START,

		PT_PVE_F2T_DISCONNECT,

		PT_PVE_C2F_KICK,
		PT_PVE_F2T_KICK,
	};


#pragma pack (push)
#pragma pack (1)

	enum Pve_Error
	{
		Pve_Error_Null,

		Pve_Error_Has_Member,			//已经加入
		Pve_Error_Empty_Room,
		Pve_Error_Full_Member,
		Pve_Error_Start_No_Right,			//没有权限开启
		Pve_Error_Kick,

		Pve_Error_Max
	};
	
	struct PT_PVE_T2C_ERROR_DATA
	{
		Byte		error;
	};

	struct PT_PVE_T2C_ERROR_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_PVE_T2C_ERROR_DATA);
	};


	//////////////////////////////////////////////////////////////////////////////////
	struct NetPveRoomInfo
	{
		AccountIdType		creatorAccountId;							//房间创建者的id
		Int					pveRoomId;
		RegionIdType		targetRegionId;
		Int					memberNum;									//房间里的人数
		Char16				pveRoomName[MAX_PVE_NAME];
	};

	struct NetPveMemberInfo
	{
		AccountIdType		accountId;
		Byte				position;
		U32					charArtIcon;
		Int					charLevel;
		Char16				characterName[MAX_CHARACTER_NAME_LEN];
	};
	//////////////////////////////////////////////////////////////////////////////////
	struct PT_PVE_C2F_ROOM_LIST_DATA
	{

	};

	struct PT_PVE_C2F_ROOM_LIST_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_PVE_C2F_ROOM_LIST_DATA);
	};

	//////////////////////////////////////////////////////////////////////////////////


	struct PT_PVE_F2T_ROOM_LIST_DATA
	{
		NetIdType		clientNetId;
		AccountIdType	accountId;
	};

	struct PT_PVE_F2T_ROOM_LIST_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_PVE_F2T_ROOM_LIST_DATA);
	};

	//////////////////////////////////////////////////////////////////////////////////
	struct PT_PVE_T2C_ROOM_LIST_BEGIN_DATA
	{

	};

	struct PT_PVE_T2C_ROOM_LIST_BEGIN_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_PVE_T2C_ROOM_LIST_BEGIN_DATA);
	};

	//////////////////////////////////////////////////////////////////////////////////


	struct PT_PVE_T2C_ROOM_LIST_DATA
	{
		NetIdType		clientNetId;
		Int				addPveRoomNum;
		NetPveRoomInfo	addPveRoomInfo[1];
	};

	struct PT_PVE_T2C_ROOM_LIST_DATA_INFO
	{
		static Int const 	netAddPveRoomInfoSize = sizeof (NetPveRoomInfo);
		static Int const 	headSize = sizeof (PT_PVE_T2C_ROOM_LIST_DATA) - sizeof( NetPveRoomInfo );
		static Int       	dataSize(PT_PVE_T2C_ROOM_LIST_DATA* data)
		{ 
			return PT_PVE_T2C_ROOM_LIST_DATA_INFO::headSize + PT_PVE_T2C_ROOM_LIST_DATA_INFO::netAddPveRoomInfoSize * data->addPveRoomNum;
		};
	};

	//////////////////////////////////////////////////////////////////////////////////
	struct PT_PVE_T2C_ROOM_LIST_END_DATA
	{

	};

	struct PT_PVE_T2C_ROOM_LIST_END_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_PVE_T2C_ROOM_LIST_END_DATA);
	};

	//////////////////////////////////////////////////////////////////////////////////
	struct PT_PVE_C2F_CREATE_DATA
	{
		AccountIdType	creatorAccountId;					//PVE创建者
		RegionIdType	targetRegionId;						//攻击目标
		Char16			pveName[MAX_PVE_NAME];				//PVE的名字
	};

	struct PT_PVE_C2F_CREATE_DATA_INFO
	{
		static Int const  dataSize = sizeof(PT_PVE_C2F_CREATE_DATA);
	};

	//////////////////////////////////////////////////////////////////////////////////
	struct PT_PVE_F2T_CREATE_DATA
	{
		AccountIdType	accountId;
		NetIdType		clientNetId;
		Int				charArtIcon;						//玩家头像
		Int				level;								//等级
		Char16			charName[MAX_CHARACTER_NAME_LEN];	//武将名字
		RegionIdType	targetRegionId;						//攻击目标
		Char16			pveRoomName[MAX_PVE_NAME];			//pve房间的名字
	};

	struct PT_PVE_F2T_CREATE_DATA_INFO
	{
		static Int const  dataSize = sizeof(PT_PVE_F2T_CREATE_DATA);
	};

	//////////////////////////////////////////////////////////////////////////////////
	struct PT_PVE_T2C_CREATE_DATA
	{
		NetPveRoomInfo		newPveRoomInfo;				//房间信息
		NetPveMemberInfo	creatorInfo;				//创建者的信息
	};

	struct PT_PVE_T2C_CREATE_DATA_INFO
	{
		static Int const  dataSize = sizeof(PT_PVE_T2C_CREATE_DATA);
	};

	//////////////////////////////////////////////////////////////////////////////////
	struct PT_PVE_C2F_ENTER_ROOM_DATA
	{
		Int					roomId;
	};
	struct PT_PVE_C2F_ENTER_ROOM_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_PVE_C2F_ENTER_ROOM_DATA);
	};

	//////////////////////////////////////////////////////////////////////////////////
	struct PT_PVE_F2T_ENTER_ROOM_DATA
	{
		AccountIdType		accountId;
		NetIdType			clientNetId;
		Int					charArtIcon;						//玩家头像
		Int					charLevel;
		Char16				charName[MAX_CHARACTER_NAME_LEN];	//武将名字
		Int					roomId;
	};

	struct PT_PVE_F2T_ENTER_ROOM_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_PVE_F2T_ENTER_ROOM_DATA);
	};

	//////////////////////////////////////////////////////////////////////////////////
	struct PT_PVE_T2C_ENTER_ROOM_DATA
	{
		Int						roomId;
		NetPveMemberInfo		memberInfo;
	};
	struct PT_PVE_T2C_ENTER_ROOM_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_PVE_T2C_ENTER_ROOM_DATA);
	};


	//////////////////////////////////////////////////////////////////////////////////
	struct PT_PVE_T2C_MEMBER_LIST_BEGIN_DATA
	{

	};

	struct PT_PVE_T2C_MEMBER_LIST_BEGIN_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_PVE_T2C_MEMBER_LIST_BEGIN_DATA);
	};
	
	//////////////////////////////////////////////////////////////////////////////////
	struct PT_PVE_T2C_MEMBER_LIST_DATA
	{
		//Int						roomId;
		Int						addMemberNum;
		NetPveMemberInfo		addMemberInfo[1];
	};
	struct PT_PVE_T2C_MEMBER_LIST_DATA_INFO
	{
		static Int const 	netAddPveMemberInfoSize = sizeof (NetPveMemberInfo);
		static Int const 	headSize = sizeof (PT_PVE_T2C_MEMBER_LIST_DATA) - sizeof( NetPveMemberInfo );
		static Int       	dataSize(PT_PVE_T2C_MEMBER_LIST_DATA* data)
		{ 
			return PT_PVE_T2C_MEMBER_LIST_DATA_INFO::headSize + PT_PVE_T2C_MEMBER_LIST_DATA_INFO::netAddPveMemberInfoSize * data->addMemberNum;
		};
	};

	//////////////////////////////////////////////////////////////////////////////////
	struct PT_PVE_T2C_MEMBER_LIST_END_DATA
	{

	};

	struct PT_PVE_T2C_MEMBER_LIST_END_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_PVE_T2C_MEMBER_LIST_END_DATA);
	};


	//////////////////////////////////////////////////////////////////////////////////
	struct PT_PVE_C2F_LEAVE_ROOM_DATA
	{
		AccountIdType	accountId;
	};
	struct PT_PVE_C2F_LEAVE_ROOM_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_PVE_C2F_LEAVE_ROOM_DATA);
	};

	//////////////////////////////////////////////////////////////////////////////////
	struct PT_PVE_F2T_LEAVE_ROOM_DATA
	{
		AccountIdType			accountId;
		NetIdType				clientNetId;
		Int						roomId;
	};
	struct PT_PVE_F2T_LEAVE_ROOM_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_PVE_F2T_LEAVE_ROOM_DATA);
	};

	//////////////////////////////////////////////////////////////////////////////////
	struct PT_PVE_T2C_LEAVE_ROOM_DATA
	{
		NetIdType				clientNetId;
		AccountIdType			accountId;
		Int						roomId;
		//NetPveMemberInfo		memberInfo;
	};
	struct PT_PVE_T2C_LEAVE_ROOM_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_PVE_T2C_LEAVE_ROOM_DATA);
	};


	//////////////////////////////////////////////////////////////////////////////////
	struct PT_PVE_T2C_DESTROY_ROOM_DATA
	{
		NetIdType				clientNetId;
		AccountIdType			accountId;
		Int						roomId;
		NetPveMemberInfo		memberInfo;
	};

	struct PT_PVE_T2C_DESTROY_ROOM_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_PVE_T2C_DESTROY_ROOM_DATA);
	};

	//////////////////////////////////////////////////////////////////////////////////

	struct PT_PVE_C2F_START_DATA
	{
		AccountIdType			accountId;
	};

	struct PT_PVE_C2F_START_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_PVE_C2F_START_DATA);
	};
	
	//////////////////////////////////////////////////////////////////////////////////
	struct PT_PVE_F2T_START_DATA
	{
		AccountIdType		accountId;
		NetIdType			clientNetId;
		Int					roomId;
	};

	struct PT_PVE_F2T_START_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_PVE_F2T_START_DATA);
	};

	//////////////////////////////////////////////////////////////////////////////////
	struct PT_PVE_T2F_START_DATA
	{
		AccountIdType		accountId;
		RegionIdType		targetRegionId;
		Int					roomId;
	};

	struct PT_PVE_T2F_START_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_PVE_T2F_START_DATA);
	};

	//////////////////////////////////////////////////////////////////////////////////
	struct PT_PVE_F2M_START_DATA
	{
		AccountIdType		accountId;
		RegionIdType		targetRegionId;
		Int					roomId;
	};

	struct PT_PVE_F2M_START_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_PVE_F2M_START_DATA);
	};
	
	//////////////////////////////////////////////////////////////////////////////////
	struct PT_PVE_M2T_START_NEW_INSTANCE_DATA
	{
		AccountIdType		accountId;
		RegionIdType		targetRegionId;
		InstanceUIdType		targetInstanceUId;
		Int					roomId;
	};

	struct PT_PVE_M2T_START_NEW_INSTANCE_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_PVE_M2T_START_NEW_INSTANCE_DATA);
	};


	//////////////////////////////////////////////////////////////////////////////////
	struct PT_PVE_T2F_START_JUMP_REGION_DATA
	{
		AccountIdType		accountId;
		RegionIdType		targetRegionId;
		InstanceUIdType		targetInstanceUId;
	};

	struct PT_PVE_T2F_START_JUMP_REGION_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_PVE_T2F_START_JUMP_REGION_DATA);
	};


	//////////////////////////////////////////////////////////////////////////////////
	struct PT_PVE_F2C_START_DATA
	{

	};

	struct PT_PVE_F2C_START_INFO
	{
		static const Int dataSize = sizeof(PT_PVE_F2C_START_DATA);
	};
	
	//////////////////////////////////////////////////////////////////////////////////
	struct PT_PVE_F2T_DISCONNECT_DATA
	{
		Int				roomId;
		AccountIdType	accountId;
	};

	struct PT_PVE_F2T_DISCONNECT_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_PVE_F2T_DISCONNECT_DATA);
	};

	//////////////////////////////////////////////////////////////////////////////////
	struct PT_PVE_C2F_KICK_DATA
	{
		AccountIdType		leaderAccountId;
		AccountIdType		kickAccountId;
	};

	struct PT_PVE_C2F_KICK_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_PVE_C2F_KICK_DATA);
	};

	//////////////////////////////////////////////////////////////////////////////////
	struct PT_PVE_F2T_KICK_DATA
	{
		Int					roomId;
		AccountIdType		leaderAccountId;
		NetIdType			leaderClientNetId;
		AccountIdType		kickAccountId;
		
	};

	struct PT_PVE_F2T_KICK_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_PVE_F2T_KICK_DATA);
	};
	
	
	//////////////////////////////////////////////////////////////////////////////////
#pragma pack (pop)
}

/******************************************************************************/

#endif	//_CAMPAIGNNETPACKET_H_