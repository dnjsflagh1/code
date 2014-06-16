/******************************************************************************/
#ifndef _MONSTERNETPACKET_H_
#define _MONSTERNETPACKET_H_
/******************************************************************************/
#include "CommonGameDefine.h"
#include "NetDefine.h"
/******************************************************************************/

namespace MG
{
	/******************************************************************************/
	//玩家角色包类型
	/******************************************************************************/
	enum MonsterNetPacketType
	{
		PT_MONSTER_UNKNOWN = 0,

		PT_MONSTER_S2C_MOVE_POS,		// [Server -> Client] 位置移动
		PT_MONSTER_S2C_INSTANT_MOVE_POS,
		PT_MONSTER_S2C_STOP_MOVE,

		PT_MONSTER_S2C_ENTER_FIGHT,
		PT_MONSTER_S2C_END_FIGHT,

		PT_MONSTER_MTF_BEKILLED
	};

#pragma pack (push)
#pragma pack (1)
	//**********************************************************************

	//-----------------------------------------------------
	struct PT_MONSTER_S2C_MOVE_POS_DATA
	{
		GameObjectIndexIdInSceneType				monsterIndex;
		NetVec2Data 		startMovePos;
		NetVec2Data 		endMovePos;
		U64				startMoveTime;
	};
	struct PT_MONSTER_S2C_MOVE_POS_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_MONSTER_S2C_MOVE_POS_DATA);
	};

	//**********************************************************************

	struct PT_MONSTER_S2C_INSTANT_MOVE_POS_DATA
	{
		GameObjectIndexIdInSceneType				monsterIndex;
		NetVec2Data 	moveToPos;
	};
	struct PT_MONSTER_S2C_INSTANT_MOVE_POS_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_MONSTER_S2C_INSTANT_MOVE_POS_DATA);
	};

	//**********************************************************************

	//-----------------------------------------------------
	struct PT_MONSTER_S2C_STOP_MOVE_DATA
	{
		GameObjectIndexIdInSceneType				monsterIndex;
		NetVec2Data		pos;
	};

	struct PT_MONSTER_S2C_STOP_MOVE_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_MONSTER_S2C_STOP_MOVE_DATA);
	};

	//**********************************************************************
	struct PT_MONSTER_S2C_ENTER_FIGHT_DATA
	{
		GameObjectIndexIdInSceneType			monsterIndex;
		Flt				moveSpeed;
	};
	struct PT_MONSTER_S2C_ENTER_FIGHT_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_MONSTER_S2C_ENTER_FIGHT_DATA);
	};

	//-------------------------------------------------------------------------------
	struct PT_MONSTER_S2C_END_FIGHT_DATA
	{
		GameObjectIndexIdInSceneType			monsterIndex;
		Flt				moveSpeed;
	};
	struct PT_MONSTER_S2C_END_FIGHT_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_MONSTER_S2C_END_FIGHT_DATA);
	};

	//**********************************************************************

    //-----------------------------------------------------
	struct PT_MONSTER_M2F_BEKILLED
	{
         GameObjectIndexIdInSceneType           monsterIndex;
		 PlayerCharacterIdType   playerCharacterId;
		 PlayerIdType            playerID;
         NetIdType               clientIdInFrontServer;
	};
	struct PT_MONSTER_M2F_BEKILLED_DATA_INFO
	{
		static const Int dataSize = sizeof(PT_MONSTER_M2F_BEKILLED);
	};
#pragma pack (pop)
}

/******************************************************************************/

#endif