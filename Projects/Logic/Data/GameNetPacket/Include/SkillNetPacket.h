/******************************************************************************/
#ifndef _SKILLNETPACKET_H_
#define _SKILLNETPACKET_H_
/******************************************************************************/

#include "CommonGameDefine.h"
#include "NetDefine.h"
#include "GameNetPacket.h"

/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //技能数据包消息枚举
    /******************************************************************************/
	enum SkillNetPacket
	{
		PT_SKILL_UNKNOW = 0,

		PT_SKILL_C2F_LEARN,                             //客户端学习技能请求
		PT_SKILL_F2M_LEARN,                             //客户端学习技能请求
        PT_SKILL_F2C_LEARN_RESULT,                      //服务端学习技能结果

		PT_SKILL_C2M_PLAYERCHARACTER_CLANT,             //客户端玩家角色吟唱技能请求
        PT_SKILL_M2C_PLAYERCHARACTER_CLANT,             //地图服务器广播玩家角色吟唱技能到客户端

		PT_SKILL_C2M_PLAYERCHARACTER_INJECT_EMITTER,	//客户端玩家角色释放瞬发技能请求 
        PT_SKILL_M2C_PLAYERCHARACTER_INJECT_EMITTER,	//地图服务器广播玩家角色释放瞬发技能到客户端  
        
		PT_SKILL_C2M_PLAYERCHARACTER_INJECT_POINT,		//客户端玩家角色释放点技能请求 
		PT_SKILL_M2C_PLAYERCHARACTER_INJECT_POINT,		//地图服务器广播玩家角色释放点技能到客户端  

		PT_SKILL_C2M_PLAYERCHARACTER_INJECT_OBJECT,		//客户端玩家角色释放目标对象技能请求 
		PT_SKILL_M2C_PLAYERCHARACTER_INJECT_OBJECT,		//地图服务器广播玩家角色释放目标对象技能到客户端  

		PT_SKILL_C2M_PLAYERCHARACTER_END_INJECT,		//客户端玩家角色中断释放
		PT_SKILL_M2C_PLAYERCHARACTER_END_INJECT,

		PT_SKILL_C2M_MONSTER_CLANT,						//客户端怪物角色吟唱技能请求
		PT_SKILL_M2C_MONSTER_CLANT,						//地图服务器广播怪物吟唱技能到客户端
														
		PT_SKILL_C2M_MONSTER_INJECT_EMITTER,			//客户端怪物释放瞬发技能请求 
		PT_SKILL_M2C_MONSTER_INJECT_EMITTER,			//地图服务器广播怪物释放瞬发技能到客户端  
														
		PT_SKILL_C2M_MONSTER_INJECT_POINT,				//客户端怪物释放点技能请求 
		PT_SKILL_M2C_MONSTER_INJECT_POINT,				//地图服务器广播怪物释放点技能到客户端  
														
		PT_SKILL_C2M_MONSTER_INJECT_OBJECT,				//客户端怪物释放目标对象技能请求  
		PT_SKILL_M2C_MONSTER_INJECT_OBJECT,				//地图服务器广播怪物释放目标对象技能到客户端  
														
		PT_SKILL_C2M_MONSTER_END_INJECT,				//客户端怪物中断释放
		PT_SKILL_M2C_MONSTER_END_INJECT,

		PT_SKILL_C2S_TROOP_USE_SKILL,
		PT_SKILL_S2C_TROOP_USE_SKILL,

		PT_SKILL_C2M_TROOP_CLANT,             			//客户端玩家军队吟唱技能请求
		PT_SKILL_M2C_TROOP_CLANT,             			//地图服务器广播玩家军队吟唱技能到客户端

		PT_SKILL_C2M_TROOP_INJECT_EMITTER,				//客户端玩家军队释放瞬发技能请求 
		PT_SKILL_M2C_TROOP_INJECT_EMITTER,				//地图服务器广播玩家军队释放瞬发技能到客户端  

		PT_SKILL_C2M_TROOP_INJECT_POINT,				//客户端玩家军队释放点技能请求 
		PT_SKILL_M2C_TROOP_INJECT_POINT,				//地图服务器广播玩家军队释放点技能到客户端  

		PT_SKILL_C2M_TROOP_INJECT_OBJECT,				//客户端玩家军队释放目标对象技能请求 
		PT_SKILL_M2C_TROOP_INJECT_OBJECT,				//地图服务器广播玩家军队释放目标对象技能到客户端  

		PT_SKILL_C2M_TROOP_END_INJECT,					//客户端玩家军队中断释放
		PT_SKILL_M2C_TROOP_END_INJECT,


		PT_SKILL_C2M_BUILDING_CLANT,             		//客户端玩家建筑吟唱技能请求
		PT_SKILL_M2C_BUILDING_CLANT,             		//地图服务器广播玩家建筑吟唱技能到客户端

		PT_SKILL_C2M_BUILDING_INJECT_EMITTER,			//客户端玩家建筑释放瞬发技能请求  
		PT_SKILL_M2C_BUILDING_INJECT_EMITTER,			//地图服务器广播玩家建筑释放瞬发技能到客户端  

		PT_SKILL_C2M_BUILDING_INJECT_POINT,				//客户端玩家建筑释放点技能请求 
		PT_SKILL_M2C_BUILDING_INJECT_POINT,				//地图服务器广播玩家建筑释放点技能到客户端  

		PT_SKILL_C2M_BUILDING_INJECT_OBJECT,			//客户端玩家建筑释放目标对象技能请求 
		PT_SKILL_M2C_BUILDING_INJECT_OBJECT,			//地图服务器广播玩家建筑释放目标对象技能到客户端  

		PT_SKILL_C2F_BUILDING_END_INJECT,				//客户端玩家建筑中断释放

        PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_PLAYERCHARACTER,	//客户端武将技能碰撞玩家角色请求

		PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_TROOP,			//客户端武将技能碰撞军队请求

		PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_BUILDING,			//客户端武将技能碰撞建筑请求

		PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_MONSTER,			//客户端武将技能碰撞怪物请求

		PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_PLAYERCHARACTER,			//客户端怪物技能碰撞玩家角色请求

		PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_TROOP,					//客户端怪物技能碰撞军队请求

		PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_BUILDING,					//客户端怪物技能碰撞建筑请求

		PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_MONSTER,					//客户端怪物技能碰撞怪物请求

		PT_SKILL_C2M_TROOP_AFFECT_COLLISION_TROOP,						//客户端军队技能碰撞军队请求

		PT_SKILL_C2M_TROOP_AFFECT_COLLISION_PLAYERCHARACTER,			//客户端军队技能碰撞武将请求

		PT_SKILL_C2M_TROOP_AFFECT_COLLISION_BUILDING,					//客户端军队技能碰撞建筑请求

		PT_SKILL_C2M_TROOP_AFFECT_COLLISION_MONSTER,					//客户端军队技能碰撞怪物请求

		PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_PLAYERCHARACTER,			//客户端建筑技能碰撞武将请求

		PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_BUILDING,				//客户端建筑技能碰撞建筑请求

		PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_TROOP,					//客户端建筑技能碰撞军队请求

		PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_MONSTER,					//客户端建筑技能碰撞怪物请求

		PT_SKILL_C2M_SUMMON_BUILDING,									//召唤怪物。
	};

    /******************************************************************************/
    //技能数据包声明
    /******************************************************************************/
#pragma pack (push)
#pragma pack (1)


    /******************************************************************************/
    //学习技能相关
    /******************************************************************************/
	struct PT_SKILL_C2F_LEARN_DATA
	{
        IdType  characterId; 
        IdType  skillId; 
		UInt    skillLevel;
	};
    struct PT_SKILL_C2F_LEARN_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SKILL_C2F_LEARN_DATA);
    };
	//--------------------------------------------------------------------------------------
	struct PT_SKILL_F2M_LEARN_DATA
	{
		IdType  characterId; 
		IdType  skillId; 
		UInt    skillLevel;
	};
	struct PT_SKILL_F2M_LEARN_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_SKILL_F2M_LEARN_DATA);
	};

    //////////////////////////////////////////////////////////////////////////////

    enum PT_SKILL_F2C_LEARN_RESULT_TYPE
    {
        PSFL_NONE = 0,
        PSFL_SUCCESS ,
        PSFL_FAIL,
    };

	struct PT_SKILL_F2C_LEARN_RESULT_DATA
	{
        IdType  characterId; 
        IdType  skillId; 
        Byte    learnResult;
	};
    struct PT_SKILL_F2C_LEARN_RESULT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SKILL_F2C_LEARN_RESULT_DATA);
    };

    /******************************************************************************/
    //吟唱技能相关
    /******************************************************************************/
	struct PT_SKILL_C2M_PLAYERCHARACTER_CLANT_DATA
	{
        GameObjectIndexIdInSceneType			characterIndex;
        IdType			skillId; 
		NetVec2Data 	characterPos;	//玩家角色位置
		NetVec2Data 	characterDir;	//玩家角色方向
		Byte			targetType;
		GameObjectIndexIdInSceneType			targetId;
		UInt			targetIndex;
		NetVec2Data		targetPos;
	};
    struct PT_SKILL_C2M_PLAYERCHARACTER_CLANT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SKILL_C2M_PLAYERCHARACTER_CLANT_DATA);
    };

 //   //////////////////////////////////////////////////////////////////////

	//struct PT_SKILL_F2M_PLAYERCHARACTER_CLANT_DATA
	//{
 //       IdType			playerId;
 //       IdType			characterId; 
 //       IdType			skillId;		
	//	NetVec2Data characterPos;	//玩家角色位置
	//	NetVec2Data characterDir;	//玩家角色方向
	//};
 //   struct PT_SKILL_F2M_PLAYERCHARACTER_CLANT_DATA_INFO
 //   {
 //       static const Int dataSize = sizeof (PT_SKILL_F2M_PLAYERCHARACTER_CLANT_DATA);
 //   };

    //////////////////////////////////////////////////////////////////////

    struct PT_SKILL_M2C_PLAYERCHARACTER_CLANT_DATA
    {
        GameObjectIndexIdInSceneType			characterIndex; 
        IdType			skillId; 
		NetVec2Data 		characterPos;	//玩家角色位置
		NetVec2Data 		characterDir;	//玩家角色方向
    };
    struct PT_SKILL_M2C_PLAYERCHARACTER_CLANT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SKILL_M2C_PLAYERCHARACTER_CLANT_DATA);
    };

	//////////////////////////////////////////////////////////////////////

	struct PT_SKILL_C2M_MONSTER_CLANT_DATA
	{
		IdType			playerId;
		IdType			monsterId;
		IdType			skillId; 
		NetVec2Data 		characterPos;	//玩家角色位置
		NetVec2Data 		characterDir;	//玩家角色方向
		Byte			targetType;
		IdType			targetId;
		IdType			targetIndex;
		NetVec2Data 		targetPos;
		RegionIdType	regionID; 
		Byte			regionType;
		InstanceUIdType instanceUid;
	};
	struct PT_SKILL_C2M_MONSTER_CLANT_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_SKILL_C2M_MONSTER_CLANT_DATA);
	};

	////////////////////////////////////////////////////////////////////////

	//struct PT_SKILL_F2M_MONSTER_CLANT_DATA
	//{
	//	IdType			playerId;
	//	IdType			monsterId; 
	//	IdType			skillId;		
	//	NetVec2Data characterPos;	//玩家角色位置
	//	NetVec2Data characterDir;	//玩家角色方向
	//};
	//struct PT_SKILL_F2M_MONSTER_CLANT_DATA_INFO
	//{
	//	static const Int dataSize = sizeof (PT_SKILL_F2M_MONSTER_CLANT_DATA);
	//};

	//////////////////////////////////////////////////////////////////////

	struct PT_SKILL_M2C_MONSTER_CLANT_DATA
	{
		GameObjectIndexIdInSceneType			monsterIndex; 
		IdType			skillId; 
		NetVec2Data 		characterPos;	//玩家角色位置
		NetVec2Data 		characterDir;	//玩家角色方向
	};
	struct PT_SKILL_M2C_MONSTER_CLANT_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_SKILL_M2C_MONSTER_CLANT_DATA);
	};

	//////////////////////////////////////////////////////////////////////

	struct PT_SKILL_C2M_TROOP_CLANT_DATA
	{
		GameObjectIndexIdInSceneType			troopIndex;
		UInt			soldierIndex;
		IdType			skillId; 
		NetVec2Data 	troopPos;	//玩家角色位置
		NetVec2Data 	troopDir;	//玩家角色方向
		Byte			targetType;
		GameObjectIndexIdInSceneType			targetId;
		IdType			targetIndex;
		NetVec2Data		targetPos;
	};

    struct PT_SKILL_C2M_TROOP_CLANT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SKILL_C2M_TROOP_CLANT_DATA);
    };

 //   //////////////////////////////////////////////////////////////////////


	//struct PT_SKILL_F2M_TROOP_CLANT_DATA
	//{
	//	Byte			regionType;
	//	RegionIdType	regionID; 
	//	InstanceUIdType instanceUid;
	//	IdType			playerId;
	//	IdType			troopId; 
	//	UInt			soldierIndex;
	//	IdType			skillId;		
	//	NetVec2Data troopPos;	//玩家角色位置
	//	NetVec2Data troopDir;	//玩家角色方向
	//};
 //   struct PT_SKILL_F2M_TROOP_CLANT_DATA_INFO
 //   {
 //       static const Int dataSize = sizeof (PT_SKILL_F2M_TROOP_CLANT_DATA);
 //   };

    //////////////////////////////////////////////////////////////////////

	struct PT_SKILL_M2C_TROOP_CLANT_DATA
	{
		GameObjectIndexIdInSceneType			troopIndex;
		UInt			soldierIndex;
		IdType			skillId; 
		NetVec2Data 		troopPos;	//玩家角色位置
		NetVec2Data 		troopDir;	//玩家角色方向
	};
    struct PT_SKILL_M2C_TROOP_CLANT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SKILL_M2C_TROOP_CLANT_DATA);
    };

	//////////////////////////////////////////////////////////////////////

	struct PT_SKILL_C2M_BUILDING_CLANT_DATA
	{
		GameObjectIndexIdInSceneType			buildingIndex;
		IdType			skillId; 
		//NetVec2Data buildingPos;	//玩家角色位置
		//NetVec2Data buildingDir;	//玩家角色方向
	};
    struct PT_SKILL_C2M_BUILDING_CLANT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SKILL_C2M_BUILDING_CLANT_DATA);
    };
    
 //   //////////////////////////////////////////////////////////////////////

	//struct PT_SKILL_F2M_BUILDING_CLANT_DATA
	//{
	//	IdType			playerId;
	//	IdType			buildingId; 
	//	IdType			skillId;	
	//	//IdType			mapId;
	//	//NetVec2Data buildingPos;	//玩家角色位置
	//	//NetVec2Data buildingDir;	//玩家角色方向
	//};
 //   struct PT_SKILL_F2M_BUILDING_CLANT_DATA_INFO
 //   {
 //       static const Int dataSize = sizeof (PT_SKILL_F2M_BUILDING_CLANT_DATA);
 //   };
 //   
 //   //////////////////////////////////////////////////////////////////////

	struct PT_SKILL_M2C_BUILDING_CLANT_DATA
	{
		GameObjectIndexIdInSceneType			buildingIndex; 
		IdType			skillId; 
		//IdType			mapId;
		//NetVec2Data buildingPos;	//玩家角色位置
		//NetVec2Data buildingDir;	//玩家角色方向
	};
    struct PT_SKILL_M2C_BUILDING_CLANT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SKILL_M2C_BUILDING_CLANT_DATA);
    };
	
    /******************************************************************************/
    //释放飞行碰撞技能相关
    /******************************************************************************/
    struct PT_SKILL_C2M_PLAYERCHARACTER_INJECT_EMITTER_DATA
    {
        GameObjectIndexIdInSceneType characterIndex; 
        IdType			skillId; 
		NetVec2Data 	injectDir;
    };
    struct PT_SKILL_C2M_PLAYERCHARACTER_INJECT_EMITTER_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SKILL_C2M_PLAYERCHARACTER_INJECT_EMITTER_DATA);
    };

    //////////////////////////////////////////////////////////////////////

  //  struct PT_SKILL_F2M_PLAYERCHARACTER_INJECT_EMITTER_DATA
  //  {
  //      IdType			playerId;
  //      IdType			characterId; 
  //      IdType			skillId; 
		//NetVec2Data injectDir;
  //  };
  //  struct PT_SKILL_F2M_PLAYERCHARACTER_INJECT_EMITTER_DATA_INFO
  //  {
  //      static const Int dataSize = sizeof (PT_SKILL_F2M_PLAYERCHARACTER_INJECT_EMITTER_DATA);
  //  };

    //////////////////////////////////////////////////////////////////////

    struct PT_SKILL_M2C_PLAYERCHARACTER_INJECT_EMITTER_DATA
    {
        GameObjectIndexIdInSceneType			characterIndex; 
        IdType			skillId; 
		NetVec2Data 		injectDir;
    };
    struct PT_SKILL_M2C_PLAYERCHARACTER_INJECT_EMITTER_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SKILL_M2C_PLAYERCHARACTER_INJECT_EMITTER_DATA);
    };

	//////////////////////////////////////////////////////////////////////

	struct PT_SKILL_C2M_MONSTER_INJECT_EMITTER_DATA
	{
		IdType			playerId;
		IdType			monsterId; 
		IdType			skillId; 
		NetVec2Data 		injectDir;
		RegionIdType	regionId; 
		Byte			regionType;		//yuanlinhu
		InstanceUIdType instanceUid;
	};
	struct PT_SKILL_C2M_MONSTER_INJECT_EMITTER_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_SKILL_C2M_MONSTER_INJECT_EMITTER_DATA);
	};

	//////////////////////////////////////////////////////////////////////

	//struct PT_SKILL_F2M_MONSTER_INJECT_EMITTER_DATA
	//{
	//	IdType			playerId;
	//	IdType			monsterId; 
	//	IdType			skillId; 
	//	NetVec2Data injectDir;
	//};
	//struct PT_SKILL_F2M_MONSTER_INJECT_EMITTER_DATA_INFO
	//{
	//	static const Int dataSize = sizeof (PT_SKILL_F2M_MONSTER_INJECT_EMITTER_DATA);
	//};

	//////////////////////////////////////////////////////////////////////

	struct PT_SKILL_M2C_MONSTER_INJECT_EMITTER_DATA
	{
		GameObjectIndexIdInSceneType			monsterIndex; 
		IdType			skillId; 
		NetVec2Data 		injectDir;
	};
	struct PT_SKILL_M2C_MONSTER_INJECT_EMITTER_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_SKILL_M2C_MONSTER_INJECT_EMITTER_DATA);
	};

	//////////////////////////////////////////////////////////////////////		


	struct PT_SKILL_C2M_TROOP_INJECT_EMITTER_DATA
	{
		GameObjectIndexIdInSceneType			troopIndex; 
		UInt			soldierIndex; 
		IdType			skillId; 
		NetVec2Data 		injectDir;
	};
    struct PT_SKILL_C2M_TROOP_INJECT_EMITTER_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SKILL_C2M_TROOP_INJECT_EMITTER_DATA);
    };

    //////////////////////////////////////////////////////////////////////

	/*struct PT_SKILL_F2M_TROOP_INJECT_EMITTER_DATA
	{
		Byte			regionType;
		RegionIdType	regionID; 
		InstanceUIdType instanceUid;
		IdType			playerId;
		IdType			troopId; 
		UInt			soldierIndex; 
		IdType			skillId;
		NetVec2Data injectDir;
	};
    struct PT_SKILL_F2M_TROOP_INJECT_EMITTER_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SKILL_F2M_TROOP_INJECT_EMITTER_DATA);
    };*/

    //////////////////////////////////////////////////////////////////////

	struct PT_SKILL_M2C_TROOP_INJECT_EMITTER_DATA
	{
		GameObjectIndexIdInSceneType			troopIndex; 
		UInt			soldierIndex;
		IdType			skillId; 
		NetVec2Data 		injectDir;
	};
    struct PT_SKILL_M2C_TROOP_INJECT_EMITTER_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SKILL_M2C_TROOP_INJECT_EMITTER_DATA);
    };

	//////////////////////////////////////////////////////////////////////

	struct PT_SKILL_C2M_BUILDING_INJECT_EMITTER_DATA
	{
		GameObjectIndexIdInSceneType			buildingIndex; 
		IdType			skillId; 
	};
    struct PT_SKILL_C2M_BUILDING_INJECT_EMITTER_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SKILL_C2M_BUILDING_INJECT_EMITTER_DATA);
    };

    //////////////////////////////////////////////////////////////////////

	//struct PT_SKILL_F2M_BUILDING_INJECT_EMITTER_DATA
	//{
	//	IdType			playerId;
	//	IdType			buildingId; 
	//	IdType			skillId; 
	//	//IdType			mapId;
	//};
 //   struct PT_SKILL_F2M_BUILDING_INJECT_EMITTER_DATA_INFO
 //   {
 //       static const Int dataSize = sizeof (PT_SKILL_F2M_BUILDING_INJECT_EMITTER_DATA);
 //   };

    //////////////////////////////////////////////////////////////////////

	struct PT_SKILL_M2C_BUILDING_INJECT_EMITTER_DATA
	{
		IdType			buildingId; 
		IdType			skillId; 
	};
    struct PT_SKILL_M2C_BUILDING_INJECT_EMITTER_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SKILL_M2C_BUILDING_INJECT_EMITTER_DATA);
    };

	/******************************************************************************/
	//释放点技能相关
	/******************************************************************************/
	struct PT_SKILL_C2M_PLAYERCHARACTER_INJECT_POINT_DATA
	{
		GameObjectIndexIdInSceneType			characterIndex; 
		IdType			skillId; 
		NetVec2Data 		targetPos;		//目标点位置
		NetVec2Data 		dir;
	};
    struct PT_SKILL_C2M_PLAYERCHARACTER_INJECT_POINT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SKILL_C2M_PLAYERCHARACTER_INJECT_POINT_DATA);
    };

    //////////////////////////////////////////////////////////////////////

	//struct PT_SKILL_F2M_PLAYERCHARACTER_INJECT_POINT_DATA
	//{
	//	IdType			playerId;
	//	IdType			characterId; 
	//	IdType			skillId; 
	//	NetVec2Data targetPos;		//目标点位置
	//};
 //   struct PT_SKILL_F2M_PLAYERCHARACTER_INJECT_POINT_DATA_INFO
 //   {
 //       static const Int dataSize = sizeof (PT_SKILL_F2M_PLAYERCHARACTER_INJECT_POINT_DATA);
 //   };

    //////////////////////////////////////////////////////////////////////

	struct PT_SKILL_M2C_PLAYERCHARACTER_INJECT_POINT_DATA
	{
		GameObjectIndexIdInSceneType			characterIndex; 
		IdType			skillId; 
		NetVec2Data 		targetPos;		//目标点位置
		NetVec2Data 		dir;
	};
    struct PT_SKILL_M2C_PLAYERCHARACTER_INJECT_POINT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SKILL_M2C_PLAYERCHARACTER_INJECT_POINT_DATA);
    };

	//////////////////////////////////////////////////////////////////////



	struct PT_SKILL_C2M_MONSTER_INJECT_POINT_DATA
	{
		IdType			playerId;
		IdType			monsterId; 
		IdType			skillId; 
		NetVec2Data 		targetPos;		//目标点位置
		RegionIdType	regionId; 
		Byte			regionType;		//yuanlinhu
		InstanceUIdType instanceUid;
	};
	struct PT_SKILL_C2M_MONSTER_INJECT_POINT_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_SKILL_C2M_MONSTER_INJECT_POINT_DATA);
	};

	//////////////////////////////////////////////////////////////////////

	//struct PT_SKILL_F2M_MONSTER_INJECT_POINT_DATA
	//{
	//	IdType			playerId;
	//	IdType			monsterId; 
	//	IdType			skillId; 
	//	NetVec2Data targetPos;		//目标点位置
	//};
	//struct PT_SKILL_F2M_MONSTER_INJECT_POINT_DATA_INFO
	//{
	//	static const Int dataSize = sizeof (PT_SKILL_F2M_MONSTER_INJECT_POINT_DATA);
	//};

	//////////////////////////////////////////////////////////////////////

	struct PT_SKILL_M2C_MONSTER_INJECT_POINT_DATA
	{
		GameObjectIndexIdInSceneType			monsterIndex; 
		IdType			skillId; 
		NetVec2Data 		targetPos;		//目标点位置
	};
	struct PT_SKILL_M2C_MONSTER_INJECT_POINT_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_SKILL_M2C_MONSTER_INJECT_POINT_DATA);
	};

	//////////////////////////////////////////////////////////////////////



	struct PT_SKILL_C2M_TROOP_INJECT_POINT_DATA
	{
		GameObjectIndexIdInSceneType			troopIndex; 
		UInt			soldierIndex; 
		IdType			skillId; 
		NetVec2Data 		dir;
		NetVec2Data 		targetPos;		//目标点位置
	};
    struct PT_SKILL_C2M_TROOP_INJECT_POINT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SKILL_C2M_TROOP_INJECT_POINT_DATA);
    };

    //////////////////////////////////////////////////////////////////////

	//struct PT_SKILL_F2M_TROOP_INJECT_POINT_DATA
	//{
	//	IdType			playerId;
	//	IdType			troopGroupId; 
	//	UInt			troopId;  
	//	IdType			skillId; 
	//	NetVec2Data targetPos;		//目标点位置
	//};
 //   struct PT_SKILL_F2M_TROOP_INJECT_POINT_DATA_INFO
 //   {
 //       static const Int dataSize = sizeof (PT_SKILL_F2M_TROOP_INJECT_POINT_DATA);
 //   };

    //////////////////////////////////////////////////////////////////////

	struct PT_SKILL_M2C_TROOP_INJECT_POINT_DATA
	{
		GameObjectIndexIdInSceneType			troopIndex; 
		UInt			soldierIndex;
		IdType			skillId;
		NetVec2Data 		dir;
		NetVec2Data			targetPos;		//目标点位置
	};
    struct PT_SKILL_M2C_TROOP_INJECT_POINT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SKILL_M2C_TROOP_INJECT_POINT_DATA);
    };

	//////////////////////////////////////////////////////////////////////

	struct PT_SKILL_C2M_BUILDING_INJECT_POINT_DATA
	{
		GameObjectIndexIdInSceneType			buildingIndex; 
		IdType			skillId; 
		IdType          mapId;
		NetVec2Data 		targetPos;		//目标点位置
	};
    struct PT_SKILL_C2M_BUILDING_INJECT_POINT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SKILL_C2M_BUILDING_INJECT_POINT_DATA);
    };

    //////////////////////////////////////////////////////////////////////

	//struct PT_SKILL_F2M_BUILDING_INJECT_POINT_DATA
	//{
	//	IdType			playerId;
	//	IdType			buildingId; 
	//	IdType			skillId; 
	//	//IdType			mapId;
	//	NetVec2Data targetPos;		//目标点位置
	//};
 //   struct PT_SKILL_F2M_BUILDING_INJECT_POINT_DATA_INFO
 //   {
 //       static const Int dataSize = sizeof (PT_SKILL_F2M_BUILDING_INJECT_POINT_DATA);
 //   };

    //////////////////////////////////////////////////////////////////////

	struct PT_SKILL_M2C_BUILDING_INJECT_POINT_DATA
	{
		GameObjectIndexIdInSceneType			buildingIndex; 
		IdType			skillId; 
		NetVec2Data 	targetPos;		//目标点位置
	};
    struct PT_SKILL_M2C_BUILDING_INJECT_POINT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SKILL_M2C_BUILDING_INJECT_POINT_DATA);
    };

	/******************************************************************************/
	//释放目标位置技能相关
	/******************************************************************************/
	struct PT_SKILL_C2M_PLAYERCHARACTER_INJECT_OBJECT_DATA
	{
		GameObjectIndexIdInSceneType			characterIndex; 
		IdType			skillId; 
		Byte			objectType;		//目标对象类型
		GameObjectIndexIdInSceneType			objectId;		//目标对象编号
		UInt			objectIndex;
	};
    struct PT_SKILL_C2M_PLAYERCHARACTER_INJECT_OBJECT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SKILL_C2M_PLAYERCHARACTER_INJECT_OBJECT_DATA);
    };

    //////////////////////////////////////////////////////////////////////

	//struct PT_SKILL_F2M_PLAYERCHARACTER_INJECT_OBJECT_DATA
	//{
	//	IdType			playerId;
	//	IdType			characterId; 
	//	IdType			skillId; 
	//	Byte			objectType;		//目标对象类型
	//	IdType			objectId;		//目标对象编号
	//	UInt			objectIndex;
	//	InstanceUIdType instanceUid;
	//};
 //   struct PT_SKILL_F2M_PLAYERCHARACTER_INJECT_OBJECT_DATA_INFO
 //   {
 //       static const Int dataSize = sizeof (PT_SKILL_F2M_PLAYERCHARACTER_INJECT_OBJECT_DATA);
 //   };

    //////////////////////////////////////////////////////////////////////

	struct PT_SKILL_M2C_PLAYERCHARACTER_INJECT_OBJECT_DATA
	{
		GameObjectIndexIdInSceneType			characterIndex; 
		IdType			skillId; 
		Byte			objectType;		//目标对象类型
		GameObjectIndexIdInSceneType			objectId;		//目标对象编号
		UInt			objectIndex;
	};
    struct PT_SKILL_M2C_PLAYERCHARACTER_INJECT_OBJECT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SKILL_M2C_PLAYERCHARACTER_INJECT_OBJECT_DATA);
    };

	//////////////////////////////////////////////////////////////////////




	struct PT_SKILL_C2M_MONSTER_INJECT_OBJECT_DATA
	{
		IdType			playerId;
		IdType			monsterId; 
		IdType			skillId; 
		Byte			objectType;		//目标对象类型
		IdType			objectId;		//目标对象编号
		UInt			objectIndex;
		RegionIdType	regionId;
		Byte			regionType;		//yuanlinhu
		InstanceUIdType instanceUid;
	};
	struct PT_SKILL_C2M_MONSTER_INJECT_OBJECT_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_SKILL_C2M_MONSTER_INJECT_OBJECT_DATA);
	};

	//////////////////////////////////////////////////////////////////////

	//struct PT_SKILL_F2M_MONSTER_INJECT_OBJECT_DATA
	//{
	//	IdType			playerId;
	//	IdType			monsterId; 
	//	IdType			skillId; 
	//	Byte			objectType;		//目标对象类型
	//	IdType			objectId;		//目标对象编号
	//	UInt			objectIndex;
	//	InstanceUIdType instanceUid;
	//};
	//struct PT_SKILL_F2M_MONSTER_INJECT_OBJECT_DATA_INFO
	//{
	//	static const Int dataSize = sizeof (PT_SKILL_F2M_MONSTER_INJECT_OBJECT_DATA);
	//};

	//////////////////////////////////////////////////////////////////////

	struct PT_SKILL_M2C_MONSTER_INJECT_OBJECT_DATA
	{
		GameObjectIndexIdInSceneType			monsterIndex; 
		IdType			skillId; 
		Byte			objectType;		//目标对象类型
		GameObjectIndexIdInSceneType			objectId;		//目标对象编号
		UInt			objectIndex;
	};
	struct PT_SKILL_M2C_MONSTER_INJECT_OBJECT_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_SKILL_M2C_MONSTER_INJECT_OBJECT_DATA);
	};

	//////////////////////////////////////////////////////////////////////

	struct PT_SKILL_C2M_TROOP_INJECT_OBJECT_DATA
	{
		GameObjectIndexIdInSceneType			troopIndex; 
		UInt			soldierId; 
		IdType			skillId; 
		Byte			objectType;		//目标对象类型
		GameObjectIndexIdInSceneType			objectId;		//目标对象编号
		UInt			objectIndex;
	};
    struct PT_SKILL_C2M_TROOP_INJECT_OBJECT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SKILL_C2M_TROOP_INJECT_OBJECT_DATA);
    };

    //////////////////////////////////////////////////////////////////////

	//struct PT_SKILL_F2M_TROOP_INJECT_OBJECT_DATA
	//{
	//	Byte			regionType;
	//	RegionIdType	regionID; 
	//	InstanceUIdType instanceUid;
	//	IdType			playerId;
	//	IdType			troopId; 
	//	UInt			soldierIndex; 
	//	IdType			skillId; 
	//	Byte			objectType;		//目标对象类型
	//	IdType			objectId;		//目标对象编号
	//	UInt			objectIndex;
	//};
 //   struct PT_SKILL_F2M_TROOP_INJECT_OBJECT_DATA_INFO
 //   {
 //       static const Int dataSize = sizeof (PT_SKILL_F2M_TROOP_INJECT_OBJECT_DATA);
 //   };

    //////////////////////////////////////////////////////////////////////

	struct PT_SKILL_M2C_TROOP_INJECT_OBJECT_DATA
	{
		GameObjectIndexIdInSceneType			troopIndex; 
		UInt			soldierIndex;
		IdType			skillId; 
		Byte			objectType;		//目标对象类型
		GameObjectIndexIdInSceneType			objectId;		//目标对象编号
		UInt			objectIndex;
	};
    struct PT_SKILL_M2C_TROOP_INJECT_OBJECT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SKILL_M2C_TROOP_INJECT_OBJECT_DATA);
    };

	//////////////////////////////////////////////////////////////////////

	struct PT_SKILL_C2S_TROOP_USE_SKILL_DATA
	{
		GameObjectIndexIdInSceneType			troopIndex; 
		IdType			skillId; 
		Byte			targetType;		//目标对象类型
		GameObjectIndexIdInSceneType			targetIndex;		//目标对象编号
		NetVec2Data 	targetPos;		//目标点位置
	};
	struct PT_SKILL_C2S_TROOP_USE_SKILL_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_SKILL_C2S_TROOP_USE_SKILL_DATA);
	};

	//////////////////////////////////////////////////////////////////////

	struct PT_SKILL_S2C_TROOP_USE_SKILL_DATA
	{
		GameObjectIndexIdInSceneType			troopIndex; 
		IdType			skillId; 
		Byte			targetType;		//目标对象类型
		GameObjectIndexIdInSceneType			targetId;		//目标对象编号
		NetVec2Data 	targetPos;		//目标点位置
	};
	struct PT_SKILL_S2C_TROOP_USE_SKILL_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_SKILL_S2C_TROOP_USE_SKILL_DATA);
	};

	//////////////////////////////////////////////////////////////////////

	struct PT_SKILL_C2M_BUILDING_INJECT_OBJECT_DATA
	{
		IdType			buildingId; 
		IdType			skillId; 
		Byte			objectType;		//目标对象类型
		IdType			objectId;		//目标对象编号
		UInt			objectIndex;
		Byte			regionType;
		RegionIdType	regionID; 
		InstanceUIdType instanceUid;
	};
    struct PT_SKILL_C2M_BUILDING_INJECT_OBJECT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SKILL_C2M_BUILDING_INJECT_OBJECT_DATA);
    };

    //////////////////////////////////////////////////////////////////////

	//struct PT_SKILL_F2M_BUILDING_INJECT_OBJECT_DATA
	//{
	//	IdType			playerId;
	//	IdType			buildingId; 
	//	IdType			skillId; 
	//	//IdType			mapId;
	//	Byte			objectType;		//目标对象类型
	//	IdType			objectId;		//目标对象编号
	//	UInt			objectIndex;
	//};
 //   struct PT_SKILL_F2M_BUILDING_INJECT_OBJECT_DATA_INFO
 //   {
 //       static const Int dataSize = sizeof (PT_SKILL_F2M_BUILDING_INJECT_OBJECT_DATA);
 //   };

    //////////////////////////////////////////////////////////////////////

	struct PT_SKILL_M2C_BUILDING_INJECT_OBJECT_DATA
	{
		GameObjectIndexIdInSceneType			buildingIndex; 
		IdType			skillId; 
		Byte			objectType;		//目标对象类型
		GameObjectIndexIdInSceneType			objectId;		//目标对象编号
		UInt			objectIndex;
	};
    struct PT_SKILL_M2C_BUILDING_INJECT_OBJECT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SKILL_M2C_BUILDING_INJECT_OBJECT_DATA);
    };


	/******************************************************************************/
	//中断释放技能相关
	/******************************************************************************/
	struct PT_SKILL_C2M_PLAYERCHARACTER_END_INJECT_DATA
	{
		GameObjectIndexIdInSceneType			characterIndex; 
		IdType			skillId; 
	};
    struct PT_SKILL_C2M_PLAYERCHARACTER_END_INJECT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SKILL_C2M_PLAYERCHARACTER_END_INJECT_DATA);
    };

	/*struct PT_SKILL_F2M_PLAYERCHARACTER_END_INJECT_DATA
	{
		IdType			playerId;
		IdType			characterId; 
		IdType			skillId; 
	};
	struct PT_SKILL_F2M_PLAYERCHARACTER_END_INJECT_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_SKILL_F2M_PLAYERCHARACTER_END_INJECT_DATA);
	};*/
	//-----------------------------------------------------------------------------------------------
	struct PT_SKILL_M2C_PLAYERCHARACTER_END_INJECT_DATA
	{
		GameObjectIndexIdInSceneType			characterIndex; 
		IdType			skillId; 
	};
	struct PT_SKILL_M2C_PLAYERCHARACTER_END_INJECT_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_SKILL_M2C_PLAYERCHARACTER_END_INJECT_DATA);
	};
	//-----------------------------------------------------------------------------------------------
	struct PT_SKILL_C2M_MONSTER_END_INJECT_DATA
	{
		IdType			playerId;
		IdType			monsterId; 
		IdType			skillId; 
		RegionIdType	regionID; 
		Byte			regionType;		//yuanlinhu
		InstanceUIdType instanceUid;
	};
	struct PT_SKILL_C2M_MONSTER_END_INJECT_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_SKILL_C2M_MONSTER_END_INJECT_DATA);
	};
	//-----------------------------------------------------------------------------------------------
	//struct PT_SKILL_F2M_MONSTER_END_INJECT_DATA
	//{
	//	IdType			playerId;
	//	IdType			monsterId; 
	//	IdType			skillId; 
	//};
	//struct PT_SKILL_F2M_MONSTER_END_INJECT_DATA_INFO
	//{
	//	static const Int dataSize = sizeof (PT_SKILL_F2M_MONSTER_END_INJECT_DATA);
	//};
	//-----------------------------------------------------------------------------------------------
	struct PT_SKILL_M2C_MONSTER_END_INJECT_DATA
	{
		GameObjectIndexIdInSceneType			monsterIndex; 
		IdType			skillId; 
	};
	struct PT_SKILL_M2C_MONSTER_END_INJECT_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_SKILL_M2C_MONSTER_END_INJECT_DATA);
	};

	//////////////////////////////////////////////////////////////////////
	struct PT_SKILL_C2M_TROOP_END_INJECT_DATA
	{
		GameObjectIndexIdInSceneType			troopIndex;
		UInt			soldierIndex; 
		IdType			skillId;
	};
    struct PT_SKILL_C2M_TROOP_END_INJECT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SKILL_C2M_TROOP_END_INJECT_DATA);
    };

	//////////////////////////////////////////////////////////////////////

	//struct PT_SKILL_F2M_TROOP_END_INJECT_DATA
	//{
	//	Byte			regionType;
	//	RegionIdType	regionID; 
	//	InstanceUIdType instanceUid;
	//	IdType			troopId;
	//	UInt			soldierIndex; 
	//	IdType			skillId; 
	//};
	//struct PT_SKILL_F2M_TROOP_END_INJECT_DATA_INFO
	//{
	//	static const Int dataSize = sizeof (PT_SKILL_F2M_TROOP_END_INJECT_DATA);
	//};

	//////////////////////////////////////////////////////////////////////

	struct PT_SKILL_M2C_TROOP_END_INJECT_DATA
	{
		IdType			troopId;
		UInt			soldierIndex; 
		IdType			skillId; 
	};
	struct PT_SKILL_M2C_TROOP_END_INJECT_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_SKILL_M2C_TROOP_END_INJECT_DATA);
	};

	//////////////////////////////////////////////////////////////////////

	struct PT_SKILL_C2F_BUILDING_END_INJECT_DATA
	{
		IdType			buildingId; 
		IdType			skillId; 
		//IdType			mapId;
	};
    struct PT_SKILL_C2F_BUILDING_END_INJECT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SKILL_C2F_BUILDING_END_INJECT_DATA);
    };
    /******************************************************************************/
    //技能碰撞相关
    /******************************************************************************/

    struct PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA
    {
        GameObjectIndexIdInSceneType  injectCharacterIndex;  //施法的玩家角色
        GameObjectIndexIdInSceneType  affectCharacterIndex;  //影响的玩家角色
        UInt    affectTotal;        //影响的总人数
        IdType  skillId; 
    };
    struct PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA);
    };

    //////////////////////////////////////////////////////////////////////

	//struct PT_SKILL_F2M_PLAYERCHARACTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA
	//{
	//	IdType  injectCharacterId;  //施法的玩家角色
	//	IdType  affectCharacterId;  //影响的玩家角色
	//	UInt    affectTotal;        //影响的总人数
	//	IdType  skillId; 
	//};
 //   struct PT_SKILL_F2M_PLAYERCHARACTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA_INFO
 //   {
 //       static const Int dataSize = sizeof (PT_SKILL_F2M_PLAYERCHARACTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA);
 //   };

    //////////////////////////////////////////////////////////////////////

	struct PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_TROOP_DATA
	{
		GameObjectIndexIdInSceneType  injectCharacterIndex;  //施法的玩家角色
		GameObjectIndexIdInSceneType	affectTroopIndex;
		UInt	affectSoldierIndex; 
		UInt    affectTotal;        //影响的总人数
		IdType  skillId; 
	};
    struct PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_TROOP_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_TROOP_DATA);
    };

    //////////////////////////////////////////////////////////////////////

	//struct PT_SKILL_F2M_PLAYERCHARACTER_AFFECT_COLLISION_TROOP_DATA
	//{
	//	IdType  		injectCharacterId;  //施法的玩家角色
	//	IdType			affectTroopId;
	//	UInt			affectSoldierIndex; 
	//	UInt    		affectTotal;        //影响的总人数
	//	IdType  		skillId;
	//	Byte			regionType;
	//	RegionIdType	regionID; 
	//	InstanceUIdType instanceUid;
	//};
 //   struct PT_SKILL_F2M_PLAYERCHARACTER_AFFECT_COLLISION_TROOP_DATA_INFO
 //   {
 //       static const Int dataSize = sizeof (PT_SKILL_F2M_PLAYERCHARACTER_AFFECT_COLLISION_TROOP_DATA);
 //   };

    //////////////////////////////////////////////////////////////////////

	struct PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_BUILDING_DATA
	{
		GameObjectIndexIdInSceneType  injectCharacterIndex;  //施法的玩家角色
		GameObjectIndexIdInSceneType  affectBuildingIndex;  //影响的玩家角色
		UInt    affectTotal;        //影响的总人数
		IdType  skillId; 
	};
    struct PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_BUILDING_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_BUILDING_DATA);
    };

    //////////////////////////////////////////////////////////////////////

	//struct PT_SKILL_F2M_PLAYERCHARACTER_AFFECT_COLLISION_BUILDING_DATA
	//{
	//	IdType  		injectCharacterId;  //施法的玩家角色
	//	IdType  		affectBuildingId;  //影响的玩家角色
	//	UInt    		affectTotal;        //影响的总人数
	//	IdType  		skillId;
	//};
 //   struct PT_SKILL_F2M_PLAYERCHARACTER_AFFECT_COLLISION_BUILDING_DATA_INFO
 //   {
 //       static const Int dataSize = sizeof (PT_SKILL_F2M_PLAYERCHARACTER_AFFECT_COLLISION_BUILDING_DATA);
 //   };

	//////////////////////////////////////////////////////////////////////

	struct PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_MONSTER_DATA
	{
		GameObjectIndexIdInSceneType  injectCharacterIndex;  //施法的玩家角色
		GameObjectIndexIdInSceneType  affectMonsterIndex;  //影响的玩家角色
		UInt    affectTotal;        //影响的总人数
		IdType  skillId; 
		NetVec2Data 	affectPos;		//目标点位置
	};
	struct PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_MONSTER_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_MONSTER_DATA);
	};

	//////////////////////////////////////////////////////////////////////

	//struct PT_SKILL_F2M_PLAYERCHARACTER_AFFECT_COLLISION_MONSTER_DATA
	//{
	//	IdType  		injectCharacterId;  //施法的玩家角色
	//	IdType  		affectMonsterId;  //影响的玩家角色
	//	UInt    		affectTotal;        //影响的总人数
	//	IdType  		skillId;
	//};
	//struct PT_SKILL_F2M_PLAYERCHARACTER_AFFECT_COLLISION_MONSTER_DATA_INFO
	//{
	//	static const Int dataSize = sizeof (PT_SKILL_F2M_PLAYERCHARACTER_AFFECT_COLLISION_MONSTER_DATA);
	//};

	//////////////////////////////////////////////////////////////////////

	struct PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_MONSTER_DATA
	{
		GameObjectIndexIdInSceneType  injectMonsterIndex;  //施法的玩家角色
		GameObjectIndexIdInSceneType  affectMonsterIndex;  //影响的玩家角色
		UInt    affectTotal;        //影响的总人数
		IdType  skillId; 
	};
	struct PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_MONSTER_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_MONSTER_DATA);
	};

	//////////////////////////////////////////////////////////////////////

	//struct PT_SKILL_F2M_MONSTER_AFFECT_COLLISION_MONSTER_DATA
	//{
	//	IdType  injectMonsterId;  //施法的玩家角色
	//	IdType  affectMonsterId;  //影响的玩家角色
	//	UInt    affectTotal;        //影响的总人数
	//	IdType  skillId; 
	//};
	//struct PT_SKILL_F2M_MONSTER_AFFECT_COLLISION_MONSTER_DATA_INFO
	//{
	//	static const Int dataSize = sizeof (PT_SKILL_F2M_MONSTER_AFFECT_COLLISION_MONSTER_DATA);
	//};

	//////////////////////////////////////////////////////////////////////

	struct PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_TROOP_DATA
	{
		GameObjectIndexIdInSceneType  injectMonsterIndex;  //施法的玩家角色
		GameObjectIndexIdInSceneType	affectTroopIndex;
		UInt    affectTotal;        //影响的总人数
		IdType  skillId; 
	};
	struct PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_TROOP_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_TROOP_DATA);
	};

	//////////////////////////////////////////////////////////////////////

	//struct PT_SKILL_F2M_MONSTER_AFFECT_COLLISION_TROOP_DATA
	//{
	//	IdType  		injectMonsterId;  //施法的玩家角色
	//	IdType			affectTroopId;
	//	UInt			affectSoldierIndex; 
	//	UInt    		affectTotal;        //影响的总人数
	//	IdType  		skillId;
	//	Byte			regionType;
	//	RegionIdType	regionID; 
	//	InstanceUIdType instanceUid;
	//};
	//struct PT_SKILL_F2M_MONSTER_AFFECT_COLLISION_TROOP_DATA_INFO
	//{
	//	static const Int dataSize = sizeof (PT_SKILL_F2M_MONSTER_AFFECT_COLLISION_TROOP_DATA);
	//};

	//////////////////////////////////////////////////////////////////////

	struct PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_BUILDING_DATA
	{
		GameObjectIndexIdInSceneType  injectMonsterIndex;  //施法的玩家角色
		GameObjectIndexIdInSceneType  affectBuildingIndex;  //影响的玩家角色
		UInt    affectTotal;        //影响的总人数
		IdType  skillId; 
	};
	struct PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_BUILDING_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_BUILDING_DATA);
	};

	//////////////////////////////////////////////////////////////////////

	//struct PT_SKILL_F2M_MONSTER_AFFECT_COLLISION_BUILDING_DATA
	//{
	//	IdType  		injectMonsterId;  //施法的玩家角色
	//	IdType  		affectBuildingId;  //影响的玩家角色
	//	UInt    		affectTotal;        //影响的总人数
	//	IdType  		skillId;
	//};
	//struct PT_SKILL_F2M_MONSTER_AFFECT_COLLISION_BUILDING_DATA_INFO
	//{
	//	static const Int dataSize = sizeof (PT_SKILL_F2M_MONSTER_AFFECT_COLLISION_BUILDING_DATA);
	//};

	//////////////////////////////////////////////////////////////////////


	struct PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA
	{
		GameObjectIndexIdInSceneType  injectMonsterIndex;  //施法的玩家角色
		GameObjectIndexIdInSceneType  affectCharacterIndex;  //影响的玩家角色
		UInt    affectTotal;        //影响的总人数
		IdType  skillId; 
	};
	struct PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA);
	};

	//////////////////////////////////////////////////////////////////////

	//struct PT_SKILL_F2M_MONSTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA
	//{
	//	IdType  		injectMonsterId;  //施法的玩家角色
	//	IdType  		affectCharacterId;  //影响的玩家角色
	//	UInt    		affectTotal;        //影响的总人数
	//	IdType  		skillId;
	//};
	//struct PT_SKILL_F2M_MONSTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA_INFO
	//{
	//	static const Int dataSize = sizeof (PT_SKILL_F2M_MONSTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA);
	//};

	//////////////////////////////////////////////////////////////////////








	struct PT_SKILL_C2M_TROOP_AFFECT_COLLISION_TROOP_DATA
	{
		GameObjectIndexIdInSceneType  injectTroopIndex;  //施法的玩家角色
		GameObjectIndexIdInSceneType  affectTroopIndex;  //影响的玩家角色
		UInt    affectTotal;        //影响的总人数
		IdType  skillId;
	};
    struct PT_SKILL_C2M_TROOP_AFFECT_COLLISION_TROOP_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SKILL_C2M_TROOP_AFFECT_COLLISION_TROOP_DATA);
    };

    //////////////////////////////////////////////////////////////////////

	//struct PT_SKILL_F2M_TROOP_AFFECT_COLLISION_TROOP_DATA
	//{
	//	IdType  		injectTroopId;  //施法的玩家角色
	//	UInt			injectSoldierIndex;
	//	IdType  		affectTroopId;  //影响的玩家角色
	//	UInt			affectSoldierIndex;
	//	UInt    		affectTotal;        //影响的总人数
	//	IdType  		skillId; 
	//	Byte			regionType;
	//	RegionIdType	regionID; 
	//	InstanceUIdType instanceUid;
	//};
 //   struct PT_SKILL_F2M_TROOP_AFFECT_COLLISION_TROOP_DATA_INFO
 //   {
 //       static const Int dataSize = sizeof (PT_SKILL_F2M_TROOP_AFFECT_COLLISION_TROOP_DATA);
 //   };

    //////////////////////////////////////////////////////////////////////

	struct PT_SKILL_C2M_TROOP_AFFECT_COLLISION_PLAYERCHARACTER_DATA
	{
		GameObjectIndexIdInSceneType  		injectTroopIndex;  //施法的玩家角色
		GameObjectIndexIdInSceneType  		affectCharacterIndex;  //影响的玩家角色
		UInt    		affectTotal;        //影响的总人数
		IdType  		skillId;
	};
    struct PT_SKILL_C2M_TROOP_AFFECT_COLLISION_PLAYERCHARACTER_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SKILL_C2M_TROOP_AFFECT_COLLISION_PLAYERCHARACTER_DATA);
    };

    //////////////////////////////////////////////////////////////////////

	//struct PT_SKILL_F2M_TROOP_AFFECT_COLLISION_PLAYERCHARACTER_DATA
	//{
	//	IdType  		injectTroopId;  //施法的玩家角色
	//	UInt			injectSoldierIndex;
	//	IdType  		affectCharacterId;  //影响的玩家角色
	//	UInt    		affectTotal;        //影响的总人数
	//	IdType  		skillId; 
	//	Byte			regionType;
	//	RegionIdType	regionID; 
	//	InstanceUIdType instanceUid;
	//};
 //   struct PT_SKILL_F2M_TROOP_AFFECT_COLLISION_PLAYERCHARACTER_DATA_INFO
 //   {
 //       static const Int dataSize = sizeof (PT_SKILL_F2M_TROOP_AFFECT_COLLISION_PLAYERCHARACTER_DATA);
 //   };

    //////////////////////////////////////////////////////////////////////

	struct PT_SKILL_C2M_TROOP_AFFECT_COLLISION_BUILDING_DATA
	{
		GameObjectIndexIdInSceneType  injectTroopIndex;  //施法的玩家角色
		GameObjectIndexIdInSceneType  affectBuildingIndex;  //影响的玩家角色
		UInt    affectTotal;        //影响的总人数
		IdType  skillId; 
	};
    struct PT_SKILL_C2M_TROOP_AFFECT_COLLISION_BUILDING_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SKILL_C2M_TROOP_AFFECT_COLLISION_BUILDING_DATA);
    };
    
    //////////////////////////////////////////////////////////////////////

	//struct PT_SKILL_F2M_TROOP_AFFECT_COLLISION_BUILDING_DATA
	//{
	//	IdType  injectTroopGroupId;  //施法的玩家角色
	//	UInt	injectTroopId;
	//	IdType  affectBuildingId;  //影响的玩家角色
	//	UInt    affectTotal;        //影响的总人数
	//	IdType  skillId; 
	//};
 //   struct PT_SKILL_F2M_TROOP_AFFECT_COLLISION_BUILDING_DATA_INFO
 //   {
 //       static const Int dataSize = sizeof (PT_SKILL_F2M_TROOP_AFFECT_COLLISION_BUILDING_DATA);
 //   };

	//////////////////////////////////////////////////////////////////////

	struct PT_SKILL_C2M_TROOP_AFFECT_COLLISION_MONSTER_DATA
	{
		GameObjectIndexIdInSceneType  injectTroopIndex;  //施法的玩家角色
		GameObjectIndexIdInSceneType  affectMonsterIndex;  //影响的玩家角色
		UInt    affectTotal;        //影响的总人数
		IdType  skillId; 
	};
	struct PT_SKILL_C2M_TROOP_AFFECT_COLLISION_MONSTER_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_SKILL_C2M_TROOP_AFFECT_COLLISION_MONSTER_DATA);
	};

	//////////////////////////////////////////////////////////////////////

	//struct PT_SKILL_F2M_TROOP_AFFECT_COLLISION_MONSTER_DATA
	//{
	//	IdType  injectTroopGroupId;  //施法的玩家角色
	//	UInt	injectTroopId;
	//	IdType  affectMonsterId;  //影响的玩家角色
	//	UInt    affectTotal;        //影响的总人数
	//	IdType  skillId; 
	//};
	//struct PT_SKILL_F2M_TROOP_AFFECT_COLLISION_MONSTER_DATA_INFO
	//{
	//	static const Int dataSize = sizeof (PT_SKILL_F2M_TROOP_AFFECT_COLLISION_MONSTER_DATA);
	//};

	////////////////////////////////////////////////////////////////////////////////////

	struct PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_BUILDING_DATA
	{
		GameObjectIndexIdInSceneType  injectBuildingIndex;  //施法的玩家角色
		GameObjectIndexIdInSceneType  affectBuildingIndex;  //影响的玩家角色
		UInt    affectTotal;        //影响的总人数
		IdType  skillId;
	};
    struct PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_BUILDING_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_BUILDING_DATA);
    };

    ////////////////////////////////////////////////////////////////////////////////////

	//struct PT_SKILL_F2M_BUILDING_AFFECT_COLLISION_BUILDING_DATA
	//{
	//	IdType  injectBuildingId;  //施法的玩家角色
	//	IdType  affectBuildingId;  //影响的玩家角色
	//	UInt    affectTotal;        //影响的总人数
	//	IdType  skillId; 
	//};
 //   struct PT_SKILL_F2M_BUILDING_AFFECT_COLLISION_BUILDING_DATA_INFO
 //   {
 //       static const Int dataSize = sizeof (PT_SKILL_F2M_BUILDING_AFFECT_COLLISION_BUILDING_DATA);
 //   };

    ////////////////////////////////////////////////////////////////////////////////////

	struct PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_PLAYERCHARACTER_DATA
	{
		GameObjectIndexIdInSceneType  injectBuildingIndex;  //施法的玩家角色
		GameObjectIndexIdInSceneType  affectCharacterIndex;  //影响的玩家角色
		UInt    affectTotal;        //影响的总人数
		IdType  skillId;
	};
    struct PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_PLAYERCHARACTER_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_PLAYERCHARACTER_DATA);
    };

    ////////////////////////////////////////////////////////////////////////////////////

	//struct PT_SKILL_F2M_BUILDING_AFFECT_COLLISION_PLAYERCHARACTER_DATA
	//{
	//	IdType  injectBuildingId;  //施法的玩家角色
	//	IdType  affectCharacterId;  //影响的玩家角色
	//	UInt    affectTotal;        //影响的总人数
	//	IdType  skillId; 
	//};
 //   struct PT_SKILL_F2M_BUILDING_AFFECT_COLLISION_PLAYERCHARACTER_DATA_INFO
 //   {
 //       static const Int dataSize = sizeof (PT_SKILL_F2M_BUILDING_AFFECT_COLLISION_PLAYERCHARACTER_DATA);
 //   };

    ////////////////////////////////////////////////////////////////////////////////////

	struct PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_TROOP_DATA
	{
		GameObjectIndexIdInSceneType  injectBuildingIndex;  //施法的玩家角色
		GameObjectIndexIdInSceneType  affectTroopIndex;  //影响的玩家角色
		UInt    affectTotal;        //影响的总人数
		IdType  skillId; 
	};
    struct PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_TROOP_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_TROOP_DATA);
    };

    ////////////////////////////////////////////////////////////////////////////////////

	//struct PT_SKILL_F2M_BUILDING_AFFECT_COLLISION_TROOP_DATA
	//{
	//	IdType  injectBuildingId;  //施法的玩家角色
	//	IdType  affectTroopGroupId;  //影响的玩家角色
	//	UInt	affectTroopId;
	//	UInt    affectTotal;        //影响的总人数
	//	IdType  skillId; 
	//};
 //   struct PT_SKILL_F2M_BUILDING_AFFECT_COLLISION_TROOP_DATA_INFO
 //   {
 //       static const Int dataSize = sizeof (PT_SKILL_F2M_BUILDING_AFFECT_COLLISION_TROOP_DATA);
 //   };

	////////////////////////////////////////////////////////////////////////////////////

	struct PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_MONSTER_DATA
	{
		GameObjectIndexIdInSceneType  injectBuildingIndex;  //施法的玩家角色
		GameObjectIndexIdInSceneType  affectMonsterIndex;  //影响的玩家角色
		UInt    affectTotal;        //影响的总人数
		IdType  skillId; 
	};
	struct PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_MONSTER_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_MONSTER_DATA);
	};

	////////////////////////////////////////////////////////////////////////////////////

	//struct PT_SKILL_F2M_BUILDING_AFFECT_COLLISION_MONSTER_DATA
	//{
	//	IdType  injectBuildingId;  //施法的玩家角色
	//	IdType  affectMonsterId;  //影响的玩家角色
	//	UInt    affectTotal;        //影响的总人数
	//	IdType  skillId; 
	//};
	//struct PT_SKILL_F2M_BUILDING_AFFECT_COLLISION_MONSTER_DATA_INFO
	//{
	//	static const Int dataSize = sizeof (PT_SKILL_F2M_BUILDING_AFFECT_COLLISION_MONSTER_DATA);
	//};


	/******************************************************************************/
	//释放点技能相关
	/******************************************************************************/
	struct PT_SKILL_C2M_SUMMON_BUILDING_DATA 
	{
		IdType			characterId;
		IdType			skillId;
		IdType			mapId;
		IdType			tamplateId;
		NetVec2Data 		pos;
	};
    struct PT_SKILL_C2M_SUMMON_BUILDING_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_SKILL_C2M_SUMMON_BUILDING_DATA);
    };

    ////////////////////////////////////////////////////////////////////////////////////

	//struct PT_SKILL_F2M_SUMMON_BUILDING_DATA 
	//{
	//	IdType			characterId;
	//	IdType			skillId;
	//	IdType			mapId;
	//	IdType			tamplateId;
	//	NetVec2Data pos;
	//};
 //   struct PT_SKILL_F2M_SUMMON_BUILDING_DATA_INFO
 //   {
 //       static const Int dataSize = sizeof (PT_SKILL_F2M_SUMMON_BUILDING_DATA);
 //   };

#pragma pack (pop)
}

#endif