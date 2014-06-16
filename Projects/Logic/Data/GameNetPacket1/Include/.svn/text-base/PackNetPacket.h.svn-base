/******************************************************************************/
#ifndef _PACKNETPACKET_H_
#define _PACKNETPACKET_H_
/******************************************************************************/
#include "CommonGameDefine.h"
#include "NetDefine.h"
#include "PlayerCharacterNetPacket.h"
#include "TroopNetPacket.h"
#include "SkillNetPacket.h"
#include "MonsterNetPacket.h"
/******************************************************************************/


namespace MG
{
	/******************************************************************************/
	//玩家包类型
	/******************************************************************************/
	enum PackNetPacketObjectType
	{
		PT_OBJECT_UNKNOWN = 0,
		PT_CHARACTER_C2S_PACK,
		PT_CHARACTER_S2C_PACK,
	};

	enum PackNetPacketType
	{
		PT_PACKET_UNKNOWN = 0,
		PT_PLAYERCHARACTER_MOVE,
		PT_PLAYERCHARACTER_STOP_MOVE,
		PT_PLAYERCHARACTER_CLANT,
		PT_PLAYERCHARACTER_INJECT_EMITTER,
		PT_PLAYERCHARACTER_INJECT_POINT,
		PT_PLAYERCHARACTER_INJECT_OBJECT,
		PT_PLAYERCHARACTER_INJECT_END,
		PT_TROOP_MOVE,
		PT_TROOP_STOP_MOVE,
		PT_TROOP_USE_SKILL,
		PT_TROOP_SOLDIER_MOVE,
		PT_TROOP_SOLDIER_STOP_MOVE,
		PT_TROOP_SOLDIER_CLANT,
		PT_TROOP_SOLDIER_INJECT_EMITTER,
		PT_TROOP_SOLDIER_INJECT_POINT,
		PT_TROOP_SOLDIER_INJECT_OBJECT,
		PT_TROOP_SOLDIER_INJECT_END,
		PT_MONSTER_MOVE,
		PT_MONSTER_INSTANT_MOVE,
		PT_MONSTER_STOP_MOVE,
		PT_MONSTER_CLANT,
		PT_MONSTER_INJECT_EMITTER,
		PT_MONSTER_INJECT_POINT,
		PT_MONSTER_INJECT_OBJECT,
		PT_MONSTER_INJECT_END,

		PT_PLAYERCHARACTER_AFFECT_COLLISION_PLAYERCHARACTER,	
		PT_PLAYERCHARACTER_AFFECT_COLLISION_TROOP,			
		PT_PLAYERCHARACTER_AFFECT_COLLISION_BUILDING,			
		PT_PLAYERCHARACTER_AFFECT_COLLISION_MONSTER,
		PT_MONSTER_AFFECT_COLLISION_PLAYERCHARACTER,			
		PT_MONSTER_AFFECT_COLLISION_TROOP,					
		PT_MONSTER_AFFECT_COLLISION_BUILDING,					
		PT_MONSTER_AFFECT_COLLISION_MONSTER,					
		PT_TROOP_AFFECT_COLLISION_TROOP,						
		PT_TROOP_AFFECT_COLLISION_PLAYERCHARACTER,			
		PT_TROOP_AFFECT_COLLISION_BUILDING,					
		PT_TROOP_AFFECT_COLLISION_MONSTER,					
		PT_BUILDING_AFFECT_COLLISION_PLAYERCHARACTER,			
		PT_BUILDING_AFFECT_COLLISION_BUILDING,				
		PT_BUILDING_AFFECT_COLLISION_TROOP,					
		PT_BUILDING_AFFECT_COLLISION_MONSTER,														

	};

	/******************************************************************************/


#pragma pack (push)
#pragma pack (1)

	//////////////////////////////////////////////////////////////////////////////

	///数据包声明
	//重新整理

	//////////////////////////////////////////////////////////////////////////////
	struct PT_PACK_C2S_CHARACTER_DATA
	{
		U64		playerId;
		I32		instanceId;
		U64		regionId;
		Byte	regionType;
		Int		packetNum;
		Char8	data[1];
	};

	//**********************************************************************

	struct PT_PACK_C2S_CHARACTER_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_PACK_C2S_CHARACTER_DATA);
		static const Int elmsSize = sizeof(Char8);
		static const Int headSize = dataSize - elmsSize;
	};

	//**********************************************************************

	struct PT_PACK_C2S_PLAYERCHARACTER_MOVE_DATA
	{
		PackNetPacketType									type;
		PT_PLAYERCHARACTER_C2S_MOVE_POS_DATA				packet;
	};

	struct PT_PACK_C2S_PLAYERCHARACTER_STOP_MOVE_DATA
	{
		PackNetPacketType									type;
		PT_PLAYERCHARACTER_C2S_STOP_MOVE_DATA				packet;
	};


	//**********************************************************************

	struct PT_PACK_C2M_PLAYERCHARACTER_CLANT_DATA
	{
		PackNetPacketType									type;
		PT_SKILL_C2M_PLAYERCHARACTER_CLANT_DATA				packet;
	};

	//**********************************************************************

	/*struct PT_PACK_F2M_PLAYERCHARACTER_CLANT_DATA
	{
		PackNetPacketType									type;
		PT_SKILL_F2M_PLAYERCHARACTER_CLANT_DATA				packet;
	};*/

	//**********************************************************************

	struct PT_PACK_M2C_PLAYERCHARACTER_CLANT_DATA
	{
		PackNetPacketType									type;
		PT_SKILL_M2C_PLAYERCHARACTER_CLANT_DATA				packet;
	};

	//**********************************************************************

	struct PT_PACK_C2M_PLAYERCHARACTER_INJECT_EMITTER_DATA
	{
		PackNetPacketType									type;
		PT_SKILL_C2M_PLAYERCHARACTER_INJECT_EMITTER_DATA	packet;
	};


	//struct PT_PACK_F2M_PLAYERCHARACTER_INJECT_EMITTER_DATA
	//{
	//	PackNetPacketType									type;
	//	PT_SKILL_F2M_PLAYERCHARACTER_INJECT_EMITTER_DATA	packet;
	//};

	//**********************************************************************

	struct PT_PACK_M2C_PLAYERCHARACTER_INJECT_EMITTER_DATA
	{
		PackNetPacketType									type;
		PT_SKILL_M2C_PLAYERCHARACTER_INJECT_EMITTER_DATA	packet;
	};

	//**********************************************************************

	struct PT_PACK_C2M_PLAYERCHARACTER_INJECT_POINT_DATA
	{
		PackNetPacketType									type;
		PT_SKILL_C2M_PLAYERCHARACTER_INJECT_POINT_DATA		packet;
	};

	//**********************************************************************

	/*struct PT_PACK_F2M_PLAYERCHARACTER_INJECT_POINT_DATA
	{
		PackNetPacketType									type;
		PT_SKILL_F2M_PLAYERCHARACTER_INJECT_POINT_DATA		packet;
	};*/

	//**********************************************************************

	struct PT_PACK_M2C_PLAYERCHARACTER_INJECT_POINT_DATA
	{
		PackNetPacketType									type;
		PT_SKILL_M2C_PLAYERCHARACTER_INJECT_POINT_DATA		packet;
	};

	//**********************************************************************

	struct PT_PACK_C2M_PLAYERCHARACTER_INJECT_OBJECT_DATA
	{
		PackNetPacketType									type;
		PT_SKILL_C2M_PLAYERCHARACTER_INJECT_OBJECT_DATA		packet;
	};

	//**********************************************************************

	//struct PT_PACK_F2M_PLAYERCHARACTER_INJECT_OBJECT_DATA
	//{
	//	PackNetPacketType									type;
	//	PT_SKILL_F2M_PLAYERCHARACTER_INJECT_OBJECT_DATA		packet;
	//};

	//**********************************************************************

	struct PT_PACK_M2C_PLAYERCHARACTER_INJECT_OBJECT_DATA
	{
		PackNetPacketType									type;
		PT_SKILL_M2C_PLAYERCHARACTER_INJECT_OBJECT_DATA		packet;
	};

	//**********************************************************************

	struct PT_PACK_C2M_PLAYERCHARACTER_END_INJECT_DATA
	{
		PackNetPacketType									type;
		PT_SKILL_C2M_PLAYERCHARACTER_END_INJECT_DATA		packet;
	};

	//struct PT_PACK_F2M_PLAYERCHARACTER_END_INJECT_DATA
	//{
	//	PackNetPacketType									type;
	//	PT_SKILL_F2M_PLAYERCHARACTER_END_INJECT_DATA		packet;
	//};

	struct PT_PACK_M2C_PLAYERCHARACTER_END_INJECT_DATA
	{
		PackNetPacketType									type;
		PT_SKILL_M2C_PLAYERCHARACTER_END_INJECT_DATA		packet;
	};

	//**********************************************************************

	struct PT_PACK_C2M_MONSTER_CLANT_DATA
	{
		PackNetPacketType									type;
		PT_SKILL_C2M_MONSTER_CLANT_DATA						packet;
	};

	//**********************************************************************

	//struct PT_PACK_F2M_MONSTER_CLANT_DATA
	//{
	//	PackNetPacketType									type;
	//	PT_SKILL_F2M_MONSTER_CLANT_DATA						packet;
	//};

	//**********************************************************************

	struct PT_PACK_M2C_MONSTER_CLANT_DATA
	{
		PackNetPacketType									type;
		PT_SKILL_M2C_MONSTER_CLANT_DATA						packet;
	};

	//**********************************************************************

	struct PT_PACK_C2M_MONSTER_INJECT_EMITTER_DATA
	{
		PackNetPacketType									type;
		PT_SKILL_C2M_MONSTER_INJECT_EMITTER_DATA			packet;
	};


	//struct PT_PACK_F2M_MONSTER_INJECT_EMITTER_DATA
	//{
	//	PackNetPacketType									type;
	//	PT_SKILL_F2M_MONSTER_INJECT_EMITTER_DATA            packet;
	//};

	//**********************************************************************

	struct PT_PACK_M2C_MONSTER_INJECT_EMITTER_DATA
	{
		PackNetPacketType									type;
		PT_SKILL_M2C_MONSTER_INJECT_EMITTER_DATA			packet;
	};

	//**********************************************************************

	struct PT_PACK_C2M_MONSTER_INJECT_POINT_DATA
	{
		PackNetPacketType									type;
		PT_SKILL_C2M_MONSTER_INJECT_POINT_DATA				packet;
	};

	//**********************************************************************

	//struct PT_PACK_F2M_MONSTER_INJECT_POINT_DATA
	//{
	//	PackNetPacketType									type;
	//	PT_SKILL_F2M_MONSTER_INJECT_POINT_DATA				packet;
	//};

	//**********************************************************************

	struct PT_PACK_M2C_MONSTER_INJECT_POINT_DATA
	{
		PackNetPacketType									type;
		PT_SKILL_M2C_MONSTER_INJECT_POINT_DATA				packet;
	};

	//**********************************************************************

	struct PT_PACK_C2M_MONSTER_INJECT_OBJECT_DATA
	{
		PackNetPacketType									type;
		PT_SKILL_C2M_MONSTER_INJECT_OBJECT_DATA				packet;
	};

	//**********************************************************************

	//struct PT_PACK_F2M_MONSTER_INJECT_OBJECT_DATA
	//{
	//	PackNetPacketType									type;
	//	PT_SKILL_F2M_MONSTER_INJECT_OBJECT_DATA				packet;
	//};

	//**********************************************************************

	struct PT_PACK_M2C_MONSTER_INJECT_OBJECT_DATA
	{
		PackNetPacketType									type;
		PT_SKILL_M2C_MONSTER_INJECT_OBJECT_DATA				packet;
	};

	//**********************************************************************

	struct PT_PACK_C2M_MONSTER_END_INJECT_DATA
	{
		PackNetPacketType									type;
		PT_SKILL_C2M_MONSTER_END_INJECT_DATA				packet;
	};

	//struct PT_PACK_F2M_MONSTER_END_INJECT_DATA
	//{
	//	PackNetPacketType									type;
	//	PT_SKILL_F2M_MONSTER_END_INJECT_DATA				packet;
	//};

	struct PT_PACK_M2C_MONSTER_END_INJECT_DATA
	{
		PackNetPacketType									type;
		PT_SKILL_M2C_MONSTER_END_INJECT_DATA				packet;
	};

	//**********************************************************************

	struct PT_PACK_C2S_TROOP_MOVE_DATA
	{
		PackNetPacketType									type;
		PT_TROOP_C2S_MOVE_POS_DATA							packet;
	};

	struct PT_PACK_C2S_TROOP_STOP_MOVE_DATA
	{
		PackNetPacketType									type;
		PT_TROOP_C2S_STOP_MOVE_DATA							packet;
	};

	struct PT_PACK_C2S_TROOP_USE_SKILL_DATA
	{
		PackNetPacketType									type;
		PT_SKILL_C2S_TROOP_USE_SKILL_DATA					packet;
	};

	struct PT_PACK_C2S_TROOP_SOLDIER_MOVE_DATA
	{
		PackNetPacketType									type;
		PT_TROOP_SOLDIER_C2S_MOVE_POS_DATA					packet;
	};

	struct PT_PACK_S2C_TROOP_SOLDIER_MOVE_DATA
	{
		PackNetPacketType									type;
		PT_TROOP_SOLDIER_S2C_MOVE_POS_DATA					packet;
	};

	struct PT_PACK_C2S_TROOP_SOLDIER_STOP_MOVE_DATA
	{
		PackNetPacketType									type;
		PT_TROOP_SOLDIER_C2S_STOP_MOVE_DATA					packet;
	};

	struct PT_PACK_S2C_TROOP_SOLDIER_STOP_MOVE_DATA
	{
		PackNetPacketType									type;
		PT_TROOP_SOLDIER_S2C_STOP_MOVE_DATA					packet;
	};

	struct PT_PACK_C2M_TROOP_SOLDIER_CLANT_DATA
	{
		PackNetPacketType									type;
		PT_SKILL_C2M_TROOP_CLANT_DATA						packet;
	};

	//struct PT_PACK_F2M_TROOP_SOLDIER_CLANT_DATA
	//{
	//	PackNetPacketType									type;
	//	PT_SKILL_F2M_TROOP_CLANT_DATA						packet;
	//};


	struct PT_PACK_M2C_TROOP_SOLDIER_CLANT_DATA
	{
		PackNetPacketType									type;
		PT_SKILL_M2C_TROOP_CLANT_DATA						packet;
	};

	struct PT_PACK_C2M_TROOP_SOLDIER_END_INJECT_DATA
	{
		PackNetPacketType									type;
		PT_SKILL_C2M_TROOP_END_INJECT_DATA					packet;
	};

	//struct PT_PACK_F2M_TROOP_SOLDIER_END_INJECT_DATA
	//{
	//	PackNetPacketType									type;
	//	PT_SKILL_F2M_TROOP_END_INJECT_DATA					packet;
	//};


	struct PT_PACK_M2C_TROOP_SOLDIER_END_INJECT_DATA
	{
		PackNetPacketType									type;
		PT_SKILL_M2C_TROOP_END_INJECT_DATA					packet;
	};

	struct PT_PACK_C2M_TROOP_SOLDIER_INJECT_OBJECT_DATA
	{
		PackNetPacketType									type;
		PT_SKILL_C2M_TROOP_INJECT_OBJECT_DATA				packet;
	};

	//struct PT_PACK_F2M_TROOP_SOLDIER_INJECT_OBJECT_DATA
	//{
	//	PackNetPacketType									type;
	//	PT_SKILL_F2M_TROOP_INJECT_OBJECT_DATA				packet;
	//};


	struct PT_PACK_M2C_TROOP_SOLDIER_INJECT_OBJECT_DATA
	{
		PackNetPacketType									type;
		PT_SKILL_M2C_TROOP_INJECT_OBJECT_DATA				packet;
	};

	struct PT_PACK_C2M_TROOP_SOLDIER_INJECT_EMITTER_DATA
	{
		PackNetPacketType									type;
		PT_SKILL_C2M_TROOP_INJECT_EMITTER_DATA				packet;
	};


	//struct PT_PACK_F2M_TROOP_SOLDIER_INJECT_EMITTER_DATA
	//{
	//	PackNetPacketType									type;
	//	PT_SKILL_F2M_TROOP_INJECT_EMITTER_DATA				packet;
	//};


	struct PT_PACK_M2C_TROOP_SOLDIER_INJECT_EMITTER_DATA
	{
		PackNetPacketType									type;
		PT_SKILL_M2C_TROOP_INJECT_EMITTER_DATA				packet;
	};

	struct PT_PACK_C2M_TROOP_SOLDIER_INJECT_POINT_DATA
	{
		PackNetPacketType									type;
		PT_SKILL_C2M_TROOP_INJECT_POINT_DATA				packet;
	};

	struct PT_PACK_M2C_TROOP_SOLDIER_INJECT_POINT_DATA
	{
		PackNetPacketType									type;
		PT_SKILL_M2C_TROOP_INJECT_POINT_DATA				packet;
	};

	struct PT_PLAYERCHARACTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA
	{
		PackNetPacketType														type;
		PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA		packet;
	};

	struct PT_PLAYERCHARACTER_AFFECT_COLLISION_TROOP_DATA
	{
		PackNetPacketType														type;
		PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_TROOP_DATA				packet;
	};

	struct PT_PLAYERCHARACTER_AFFECT_COLLISION_BUILDING_DATA
	{
		PackNetPacketType														type;
		PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_BUILDING_DATA				packet;
	};

	struct PT_PLAYERCHARACTER_AFFECT_COLLISION_MONSTER_DATA
	{
		PackNetPacketType														type;
		PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_MONSTER_DATA				packet;
	};

	struct PT_MONSTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA
	{
		PackNetPacketType														type;
		PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA				packet;
	};

	struct PT_MONSTER_AFFECT_COLLISION_TROOP_DATA
	{
		PackNetPacketType														type;
		PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_TROOP_DATA						packet;
	};

	struct PT_MONSTER_AFFECT_COLLISION_BUILDING_DATA
	{
		PackNetPacketType														type;
		PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_BUILDING_DATA						packet;
	};

	struct PT_MONSTER_AFFECT_COLLISION_MONSTER_DATA
	{
		PackNetPacketType														type;
		PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_MONSTER_DATA						packet;
	};

	struct PT_TROOP_AFFECT_COLLISION_TROOP_DATA
	{
		PackNetPacketType														type;
		PT_SKILL_C2M_TROOP_AFFECT_COLLISION_TROOP_DATA							packet;
	};

	struct PT_TROOP_AFFECT_COLLISION_PLAYERCHARACTER_DATA
	{
		PackNetPacketType														type;
		PT_SKILL_C2M_TROOP_AFFECT_COLLISION_PLAYERCHARACTER_DATA				packet;
	};

	struct PT_TROOP_AFFECT_COLLISION_BUILDING_DATA
	{
		PackNetPacketType														type;
		PT_SKILL_C2M_TROOP_AFFECT_COLLISION_BUILDING_DATA						packet;
	};

	struct PT_TROOP_AFFECT_COLLISION_MONSTER_DATA
	{
		PackNetPacketType														type;
		PT_SKILL_C2M_TROOP_AFFECT_COLLISION_MONSTER_DATA						packet;
	};

	struct PT_BUILDING_AFFECT_COLLISION_PLAYERCHARACTER_DATA
	{
		PackNetPacketType														type;
		PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_PLAYERCHARACTER_DATA				packet;
	};

	struct PT_BUILDING_AFFECT_COLLISION_BUILDING_DATA
	{
		PackNetPacketType														type;
		PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_BUILDING_DATA					packet;
	};

	struct PT_BUILDING_AFFECT_COLLISION_TROOP_DATA
	{
		PackNetPacketType														type;
		PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_TROOP_DATA						packet;
	};

	struct PT_BUILDING_AFFECT_COLLISION_MONSTER_DATA
	{
		PackNetPacketType														type;
		PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_MONSTER_DATA						packet;
	};

	//**********************************************************************


	//**********************************************************************


	//**********************************************************************


	//**********************************************************************

	//struct PT_PACK_C2S_PLAYERCHARACTER_CLANT_DATA
	//{
	//	PackNetPacketType						type;
	//	PT_PLAYERCHARACTER_C2S_MOVE_POS_DATA	moveData[1];
	//};

	//**********************************************************************

	struct PT_PACK_S2C_CHARACTER_DATA
	{
		I32		clientId;
		U64		regionId;
		Byte	regionType;
		Int		packetNum;
		Char8	data[1];
	};

	//**********************************************************************

	struct PT_PACK_S2C_CHARACTER_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_PACK_S2C_CHARACTER_DATA);
		static const Int elmsSize = sizeof(Char8);
		static const Int headSize = dataSize - elmsSize;
	};

	//**********************************************************************

	struct PT_PACK_S2C_PLAYERCHARACTER_MOVE_DATA
	{
		PackNetPacketType						type;
		PT_PLAYERCHARACTER_S2C_MOVE_POS_DATA	packet;
	};

	//**********************************************************************

	struct PT_PACK_S2C_PLAYERCHARACTER_STOP_MOVE_DATA
	{
		PackNetPacketType						type;
		PT_PLAYERCHARACTER_S2C_STOP_MOVE_DATA	packet;
	};

	//**********************************************************************

	struct PT_PACK_S2C_MONSTER_MOVE_DATA
	{
		PackNetPacketType						type;
		PT_MONSTER_S2C_MOVE_POS_DATA			packet;
	};

	//**********************************************************************
	struct PT_PACK_S2C_INSTANT_MONSTER_MOVE_DATA
	{
		PackNetPacketType						type;
		PT_MONSTER_S2C_INSTANT_MOVE_POS_DATA	packet;
	};

	//**********************************************************************

	struct PT_PACK_S2C_MONSTER_STOP_MOVE_DATA
	{
		PackNetPacketType						type;
		PT_MONSTER_S2C_STOP_MOVE_DATA			packet;
	};

	//**********************************************************************

	struct PT_PACK_S2C_TROOP_MOVE_DATA
	{
		PackNetPacketType						type;
		PT_TROOP_S2C_MOVE_POS_DATA				packet;
	};

	//**********************************************************************

	struct PT_PACK_S2C_TROOP_STOP_MOVE_DATA
	{
		PackNetPacketType						type;
		PT_TROOP_S2C_STOP_MOVE_DATA				packet;
	};

	//**********************************************************************

	struct PT_PACK_S2C_TROOP_USE_SKILL_DATA
	{
		PackNetPacketType						 type;
		PT_SKILL_S2C_TROOP_USE_SKILL_DATA		 packet;
	};




	   

#pragma pack (pop)
}

/******************************************************************************/

#endif