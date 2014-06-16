/******************************************************************************/
#ifndef _REGIONNETPACKETPROCESSER_H_
#define _REGIONNETPACKETPROCESSER_H_
/******************************************************************************/
#include "ClientPreqs.h"
#include "CommonGameDefine.h"
#include "RegionNetPacket.h"
#include "GameNetEvent.h"
/******************************************************************************/
namespace MG
{
	class RegionNetPacketProcesser
	{
	public:
		SINGLETON_INSTANCE(RegionNetPacketProcesser)

		Bool	processFrontServerPacket(I32 id,NetEventRecv* packet);
	public:
		
		void onRecvPlayerCharacterEnter( I32 id, PT_REGION_M2C_ADD_PLAYER_CHARACTER_DATA* data );
		void onRecvPlayerCharacterLeave( I32 id, PT_REGION_M2C_REMOVE_PLAYER_CHARACTER_DATA* data );

		void onRecvPlayerCharacterCreateAndAppear( I32 id, PT_REGION_M2C_CREATE_APPEAR_PLAYER_CHARACTER_DATA* data );
		void onRecvPlayerCharacterDestroyAndDisappear( I32 id, PT_REGION_M2C_DESTROY_DISAPPEAR_PLAYER_CHARACTER_DATA* data );

		void onRecvPlayerCharacterAppear( I32 id, PT_REGION_M2C_APPEAR_PLAYER_CHARACTER_DATA* data );
		void onRecvPlayerCharacterDisappear( I32 id, PT_REGION_M2C_DISAPPEAR_PLAYER_CHARACTER_DATA* data );

		void onRecvBuildingEnter( I32 id, PT_REGION_M2C_ADD_BUILDING_DATA* data );
		void onRecvBuildingLeave( I32 id, PT_REGION_M2C_REMOVE_BUILDING_DATA* data );

		////第三方角色进入
		//void onRecvThirdPartCharacterEnter( I32 id, PT_REGION_M2C_ADD_TRITH_PART_CHARACTER_DATA* data );

		//怪物进入
		void onRecvMonsterEnter( I32 id, PT_REGION_M2C_ADD_MONSTER_DATA* data );

		//怪物复活
		void onRecvMonsterAlive( I32 id, PT_REGION_M2C_MONSTER_ALIVE_DATA* data );

		void onRecvMonsterCreateAndAppear( I32 id, PT_REGION_M2C_CREATE_APPEAR_MONSTER_DATA* data );

		void onRecvMonsterDestroyAndDisappear( I32 id, PT_REGION_M2C_DESTROY_DISAPPEAR_MONSTER_DATA* data );

		//需要调整士兵的位子
		void onRecvTroopCreate( I32 id, PT_REGION_M2C_CREATE_TROOP_DATA* data );
		
		//军队
		void onRecvTroopEnter( I32 id, PT_REGION_M2C_ADD_TROOP_DATA* data );

		//怪物AI 控制
		void onRecvMonsterAIControl( I32 id, PT_REGION_M2C_MONSTER_AI_CONTROL_DATA* data );
		
		//加载场景完成
		void onRecvEndLoadScene( I32 id, PT_REGION_M2C_END_LOAD_SCENE_DATA* data );

		//玩家角色复活
		void onRecvPlayerCharacterAliveFromMapServer( I32 id, PT_REGION_M2C_PLAYER_CHARACTER_ALIVE_DATA* data );

		void onRecvPlayerCharacterAliveFromFrontServer( I32 id, PT_REGION_F2C_PLAYER_CHARACTER_ALIVE_DATA* data );


	public:
		//计算军队和士兵的位置 并通知服务器
		void	sendCreateTroopReturn(PT_REGION_M2C_CREATE_TROOP_DATA* data);
		
		void	sendAddBuildingByPlayer(U64 characterId, U64 regionId, Byte regionType, Int addBuildingNum, NetAddBuildingInfo* addBuildingInfo);
		void	sendRemoveBuildingByPlayer(U64  buildingId);


		void	sendAddTroopTest();

		void	sendTest();
		void	sendTest1();

		void	sendPlayerCharacterSetAlive(PlayerCharacterIdType playerCharacterId,  AliveType aliveType);		//玩家角色复活

	};
}

#endif	//_REGIONNETPACKETPROCESSER_H_
