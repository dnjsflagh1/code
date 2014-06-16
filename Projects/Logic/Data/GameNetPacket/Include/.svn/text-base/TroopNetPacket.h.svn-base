/******************************************************************************/
#ifndef _TROOP_NET_PACKET_H_
#define _TROOP_NET_PACKET_H_
/******************************************************************************/
#include "CommonGameDefine.h"
#include "NetDefine.h"
#include "GameNetPacket.h"
/******************************************************************************/

namespace MG
{
	/******************************************************************************/
	//玩家角色包类型
	/******************************************************************************/
	enum TroopNetPacketType
	{
		PT_TROOP_UNKNOWN = 0,

		// [Client -> Server] 军队跳转区域
		PT_TROOP_GROUP_C2F_JUMP_REGION,
		PT_TROOP_GROUP_F2C_JUMP_REGION,			
		PT_TROOP_GROUP_F2M_JUMP_REGION,

		PT_TROOP_C2S_MOVE_POS,		// [Client -> Server] 位置移动
		PT_TROOP_S2C_MOVE_POS,		// [Server -> Client] 位置移动

		PT_TROOP_C2S_STOP_MOVE,
		PT_TROOP_S2C_STOP_MOVE,

		PT_TROOP_GROUP_C2S_YAW_DIR,
		PT_TROOP_GROUP_S2C_YAW_DIR,

		PT_TROOP_GROUP_C2S_MOVE_OBJECT,
		PT_TROOP_GROUP_S2C_MOVE_OBJECT,

		PT_TROOP_C2S_MOVE_OBJECT,
		PT_TROOP_S2C_MOVE_OBJECT,

		PT_TROOP_SOLDIER_C2S_MOVE_POS,		// [Client -> Server] 位置移动
		PT_TROOP_SOLDIER_S2C_MOVE_POS,		// [Server -> Client] 位置移动

		PT_TROOP_SOLDIER_C2S_STOP_MOVE,		// [Client -> Server] 位置移动
		PT_TROOP_SOLDIER_S2C_STOP_MOVE,		// [Server -> Client] 位置移动

        PT_TROOP_GROUP_M2F_ADD_TROOP,        //   frontsever修正军队的地图和地图类型
        PT_TROOP_GROUP_M2F_REMOVE_TROOP,     //   frontsever修正军队的地图和地图类型

		PT_TROOP_GROUP_F2C_SKILL_INFO,

		PT_TROOP_S2C_ENTER_FIGHT,
		PT_TROOP_S2C_END_FIGHT,

	};

#pragma pack (push)
#pragma pack (1)


	//**********************************************************************
	// 角色区域跳转:
	//-----------------------------------------------------
	struct PT_TROOP_GROUP_C2F_JUMP_REGION_DATA
	{
		U64					troopId;
		U64					toRegionId;
		Byte				toRegionType;
		//跳转点：
	};
    struct PT_TROOP_GROUP_C2F_JUMP_REGION_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_TROOP_GROUP_C2F_JUMP_REGION_DATA);
    };
	//-----------------------------------------------------
	enum TroopGroupJumpRegionResult
	{
		TroopJumpRegionResult_Succeed,
		TroopJumpRegionResult_Fail,

	};
	struct PT_TROOP_GROUP_F2C_JUMP_REGION_DATA
	{
		TroopGroupJumpRegionResult jumpResult;
	};
    struct PT_TROOP_GROUP_F2C_JUMP_REGION_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_TROOP_GROUP_F2C_JUMP_REGION_DATA);
    };
	//-----------------------------------------------------
	struct PT_TROOP_GROUP_F2M_JUMP_REGION_DATA
	{
		U64		troopId;
		Byte	toRegionType;
		UInt	toRegionID;
	};
    struct PT_TROOP_GROUP_F2M_JUMP_REGION_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_TROOP_GROUP_F2M_JUMP_REGION_DATA);
    };
	//**********************************************************************
	struct PT_TROOP_C2S_MOVE_POS_DATA
	{
		GameObjectIndexIdInSceneType					troopIndex;
		NetVec2Data 		startMovePos;
		NetVec2Data 		endMovePos;
		Bool				isBlockCheck;
	};
    struct PT_TROOP_C2S_MOVE_POS_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_TROOP_C2S_MOVE_POS_DATA);
    };
	//-----------------------------------------------------

	struct PT_TROOP_GROUP_C2S_MOVE_OBJECT_DATA
	{
		U64				troopGroupId;
		U64				objectId;
		UInt			objectType;
		Flt				radius;
		Bool			isCommand;
	};
    struct PT_TROOP_GROUP_C2S_MOVE_OBJECT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_TROOP_GROUP_C2S_MOVE_OBJECT_DATA);
    };
	//-----------------------------------------------------

	struct PT_TROOP_C2S_MOVE_OBJECT_DATA
	{
		U64				troopGroupId;
		Int				troopIndex;
		U64				objectId;
		Int				objectIndex;
		UInt			objectType;
		Flt				radius;
		Bool			isCommand;
	};
    struct PT_TROOP_C2S_MOVE_OBJECT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_TROOP_C2S_MOVE_OBJECT_DATA);
    };

	//-----------------------------------------------------

	struct PT_TROOP_GROUP_C2S_YAW_DIR_DATA
	{
		U64				troopGroupId;
		NetVec2Data 		dir;
	};
    struct PT_TROOP_GROUP_C2S_YAW_DIR_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_TROOP_GROUP_C2S_YAW_DIR_DATA);
    };

	//-----------------------------------------------------

	struct PT_TROOP_C2S_STOP_MOVE_DATA
	{
		GameObjectIndexIdInSceneType				troopIndex;
	};
    struct PT_TROOP_C2S_STOP_MOVE_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_TROOP_C2S_STOP_MOVE_DATA);
    };

	//-----------------------------------------------------

	struct PT_TROOP_S2C_MOVE_POS_DATA
	{
		GameObjectIndexIdInSceneType				troopIndex;
		NetVec2Data 	startMovePos;
		NetVec2Data 	endMovePos;
		U64				startMoveTime;
		Bool			isBlockCheck;
	};
    struct PT_TROOP_S2C_MOVE_POS_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_TROOP_S2C_MOVE_POS_DATA);
    };

	//-----------------------------------------------------

	struct PT_TROOP_GROUP_S2C_MOVE_OBJECT_DATA
	{
		U64				troopGroupId;
		U64				objectId;
		UInt			objectType;
		Flt				radius;
		Bool			isCommand;
	};
    struct PT_TROOP_GROUP_S2C_MOVE_OBJECT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_TROOP_GROUP_S2C_MOVE_OBJECT_DATA);
    };

	//-----------------------------------------------------

	struct PT_TROOP_GROUP_S2C_YAW_DIR_DATA
	{
		U64				troopGroupId;
		NetVec2Data		dir;
	};
    struct PT_TROOP_GROUP_S2C_YAW_DIR_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_TROOP_GROUP_S2C_YAW_DIR_DATA);
    };


	//-----------------------------------------------------

	struct PT_TROOP_S2C_STOP_MOVE_DATA
	{
		GameObjectIndexIdInSceneType				troopIndex;
	};
    struct PT_TROOP_S2C_STOP_MOVE_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_TROOP_S2C_STOP_MOVE_DATA);
    };

	//**********************************************************************
	struct PT_TROOP_S2C_ENTER_FIGHT_DATA
	{
		GameObjectIndexIdInSceneType			troopIndex;
	};
	struct PT_TROOP_S2C_ENTER_FIGHT_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_TROOP_S2C_ENTER_FIGHT_DATA);
	};

	//-------------------------------------------------------------------------------
	struct PT_TROOP_S2C_END_FIGHT_DATA
	{
		GameObjectIndexIdInSceneType			troopIndex;
	};
	struct PT_TROOP_S2C_END_FIGHT_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_TROOP_S2C_END_FIGHT_DATA);
	};

	//-----------------------------------------------------
	struct PT_TROOP_S2C_MOVE_OBJECT_DATA
	{
		U64				troopGroupId;
		Int				troopIndex;
		U64				objectId;
		Int				objectIndex;
		UInt			objectType;
		Flt				radius;
		Bool			isCommand;
	};
    struct PT_TROOP_S2C_MOVE_OBJECT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_TROOP_S2C_MOVE_OBJECT_DATA);
    };

	//-----------------------------------------------------

	//**********************************************************************
	struct PT_TROOP_SOLDIER_C2S_MOVE_POS_DATA
	{
		Byte			regionType;
		RegionIdType	regionID; 
		InstanceUIdType instanceUid;
		GameObjectIndexIdInSceneType				troopIndex;
		Byte			soldierIndex;
		NetVec2Data 		startMovePos;
		NetVec2Data 		endMovePos;
	};

    struct PT_TROOP_SOLDIER_C2S_MOVE_POS_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_TROOP_SOLDIER_C2S_MOVE_POS_DATA);
    };

	//-----------------------------------------------------
	struct PT_TROOP_SOLDIER_S2C_MOVE_POS_DATA
	{
		GameObjectIndexIdInSceneType				troopIndex;
		Byte			soldierIndex;
		NetVec2Data 		startMovePos;
		NetVec2Data 		endMovePos;
		U64				startMoveTime;
	};
    struct PT_TROOP_SOLDIER_S2C_MOVE_POS_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_TROOP_SOLDIER_S2C_MOVE_POS_DATA);
    };
    //-----------------------------------------------------

	struct PT_TROOP_SOLDIER_C2S_STOP_MOVE_DATA
	{
		GameObjectIndexIdInSceneType				troopIndex;
		Byte			soldierIndex;
	};

	struct PT_TROOP_SOLDIER_C2S_STOP_MOVE_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_TROOP_SOLDIER_C2S_STOP_MOVE_DATA);
	};

	//-----------------------------------------------------
	struct PT_TROOP_SOLDIER_S2C_STOP_MOVE_DATA
	{
		GameObjectIndexIdInSceneType				troopIndex;
		Byte			soldierIndex;
	};

	struct PT_TROOP_SOLDIER_S2C_STOP_MOVE_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_TROOP_SOLDIER_S2C_STOP_MOVE_DATA);
	};
	//-----------------------------------------------------
    struct NetTroopGroupRegionChange
    {
        IdType troopID;

        IdType regionID;
        Byte regionType;
    };
    struct PT_TROOP_GROUP_M2F_ADD_TROOP_DATA
    {
        IdType netID;
        U32 troopNum;
        NetTroopGroupRegionChange info;
    };
    struct PT_TROOP_GROUP_M2F_ADD_TROOP_DATA_INFO
    {
        static Int  dataSize(PT_TROOP_GROUP_M2F_ADD_TROOP_DATA* data)
        { 
            static Int  headSize        = sizeof (PT_TROOP_GROUP_M2F_ADD_TROOP_DATA) - sizeof( NetTroopGroupRegionChange );
            static Int  netTroopGroupRegionChangeSize    = sizeof (NetTroopGroupRegionChange);

            return headSize + netTroopGroupRegionChangeSize * data->troopNum;
        };
    };
	//-----------------------------------------------------
	struct PT_TROOP_GROUP_F2C_SKILL_INFO_DATA
	{
		IdType			troopGroupId;
		UInt			skillNum;
		SkillNetData	skillList[1];
	};
    struct PT_TROOP_GROUP_F2C_SKILL_INFO_DATA_INFO
    {
        static const Int headSize       = sizeof (PT_TROOP_GROUP_F2C_SKILL_INFO_DATA) - sizeof (SkillNetData);
        static const Int elementSize    = sizeof (SkillNetData);
    };
    //-----------------------------------------------------
#pragma pack (pop)
}

/******************************************************************************/

#endif	//_TROOP_NET_PACKET_H_