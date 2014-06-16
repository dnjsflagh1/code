/******************************************************************************/
#ifndef _SREGIONNETPACKETPROCESSER_H_
#define _SREGIONNETPACKETPROCESSER_H_
/******************************************************************************/

#include "MapServerPreqs.h"
#include "GameNetPacket.h"
#include "RegionNetPacket.h"
#include "SceneFileLoader.h"
#include "SSceneGridManager.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************/
	//区域网络消息处理
	/******************************************************************************/
	class SRegionNetPacketProcesser
	{
	public:
		SRegionNetPacketProcesser();
		~SRegionNetPacketProcesser();
		SINGLETON_INSTANCE(SRegionNetPacketProcesser);

		Bool	processFrontServerPacket(I32 id, NetEventRecv* packet);

	public:
		//发送消息处理
		void	sendPlayerCharacterListToPlayer_New( SPlayer* player, std::map<PlayerCharacterIdType, SCharacter*>* playerCharacterList, GameType gameType );
		void	broadcastPlayerCharacterEnterToRegion_New(SPlayerCharacter* playerCharacter, SRegionObjectBase* region);

		void	broadcastPlayerCharacterLeaveToRegion_New(SCharacter* playerCharacter, SRegionObjectBase* region);

		void	broadcastAppearPlayerCharacterToRegionToSelf( SPlayerCharacter* playerCharacter, std::map<UInt, SSceneGrid*>& regionGridList, Bool isFilterSelf = true);
		void	broadcastAppearPlayerCharacterToRegionToOther( SPlayerCharacter* playerCharacter, SRegionObjectBase* region, Bool isFilterSelf = true );

		void	broadcastDisappearPlayerCharacterToRegionToSelf( SCharacter* playerCharacter, std::map<UInt, SSceneGrid*>& regionGridList, Bool isFilterSelf = true );
		void	broadcastDisappearPlayerCharacterToRegionToOther( SCharacter* playerCharacter, SRegionObjectBase* region, Bool isFilterSelf = true );

		//玩家角色复活
		void	broadcastPlayerCharacterAliveToRegion(SPlayerCharacter* playerCharacter, SRegionObjectBase* region);
		void	sendPlayerCharacterAliveToFrontServer(SPlayerCharacter* playerCharacter);

		//发送军队列表到【客户端】
		void	broadcastTroopEnterToRegion(SCharacter* troop, SRegionObjectBase* region);
		void	broadcastTroopLeaveToRegion(SCharacter* troop, SRegionObjectBase* region);

		
		//广播建筑物信息
		void	sendBattleBuildingListToPlayer_NEW( SPlayer* player, std::map<BuildingIdType, GameObject*>* buildingList );
		void	broadcastBattleBuildingEnterToRegion_NEW(SCharacter* building, SRegionObjectBase* region);
		void	broadcastBattleBuildingLeaveToRegion_NEW(SCharacter* building, SRegionObjectBase* region);

		void	broadcastBuildingCreateAndAppearToRegion(SCharacter* building, SRegionObjectBase* region);
		void	broadcastBuildingDestroyAndDisappearToRegion(SCharacter* building, SRegionObjectBase* region);

		void	broadcastBuildingAppearToRegion(SCharacter* building, SRegionObjectBase* region);
		void	broadcastBuildingDisappearToRegion(SCharacter* building, SRegionObjectBase* region);

		//第三方角色
		//void	sendThirthPartListToPlayer( SPlayer* toPlayer, std::map<GameObjectIdType, SThirdPartCharacter*>* thirthPartCharacterList);
		
		//怪物列表
		void	sendMonsterListToPlayer( SPlayer* toPlayer, std::map<MonsterIdType, SMonster*>* monsterList );

		void	broadcastMonsterAppearToRegion( SPlayerCharacter* playerCharacter, std::map<UInt, SSceneGrid*>& regionGridList );
		void	broadcastMonsterDisappearToRegion( SPlayerCharacter* playerCharacter, std::map<UInt, SSceneGrid*>& regionGridList );
		
		//怪物复活
		void	broadcastMonsterAliveToRegion(SMonster* monster, SRegionObjectBase* region);
		
		//军营
		void	sendCampListToPlayer( SPlayer* toPlayer, std::map<CampIdType, SCamp*>* campList);
		void	broadcastCampEnterToRegion(SCamp* camp, SRegionObjectBase* region);

		//建筑
		void	sendBuildingListToPlayer( SPlayer* toPlayer, std::map<BuildingIdType, SBuilding*>* buildingList);
		void	broadcastBuildingEnterToRegion(SBuilding* building, SRegionObjectBase* region);

		//军队
		void	sendTroopListToPlayer( SPlayer* toPlayer, std::map<TroopIdType, SCharacter*>* troopList);
		//void	sendTroopListToFrontServer( SPlayer* player, std::map<TroopIdType, SCharacter*>* troopList);
		
		//军队 创建
		void	sendCreateTroopGroupListToOwnerPlayer(std::map<TroopGroupIdType, STroopGroup*>* troopGroupList, SRegionObjectBase* regionObj);

		void	sendCreateTroopGroupToOwnerPlayer(STroopGroup* newTroop, SRegionObjectBase* regionObj, Int index);
	
		//Monster AI 控制权
		void	sendMonsterAIControlToPlayerList(std::map<AccountIdType, Player*>* playerList);
		void	sendMonsterAIControlToPlayer(SPlayer* player);

		//通知客户端 场景加载完成
		void	sendEndLoadScene(SPlayer* player);

	public:
		//接收消息处理
		void	onRecvAddBatleFromFrontServer( I32 id , PT_REGION_F2M_ADD_BUILDING_DATA* data);
		void	onRecvRemoveBatleFromFrontServer( I32 id , PT_REGION_F2M_REMOVE_BUILDING_DATA* data);

		void	onRecvCreateTroopRetFromFrontServer( I32 id , PT_REGION_F2M_CREATE_TROOP_RET_DATA* data);

		void	onRecvAddTroopTestFromFrontServer( I32 id , PT_REGION_C2M_ADD_TROOP_TEST_DATA* data);

		void	onRecvPlayerCharacterSetAliveFromFrontServer( I32 id , PT_REGION_F2M_PLAYER_CHARACTER_ALIVE_DATA* data);

		void	onRecvTestFromFrontServer( I32 id , PT_REGION_C2M_TEST_DATA* data);
		
		void	onRecvTest1FromFrontServer( I32 id , PT_REGION_C2M_TEST_DATA* data);

	protected:

		void	broadcastCreateAndAppearPlayerCharacterToRegionToSelf( SPlayerCharacter* playerCharacter, SPlayer* myPlayer );
		void	broadcastBuffListToRegionToSelf( SPlayerCharacter* playerCharacter, SPlayer* myPlayer );
		void	broadcastCreateAndAppearPlayerCharacterToRegionToOther( SPlayerCharacter* playerCharacter, SRegionObjectBase* region, Bool isFilterSelf = true );
		void    broadcastCreateAndAppearPlayerCharacterEquipListToRegionToSelf(SPlayerCharacter* playerCharacter, SPlayer* myPlayer);  //广播装备列表

		void	broadcastDestroyAndDisappearPlayerCharacterToRegionToSelf( SCharacter* playerCharacter, SPlayer* myPlayer );
		void	broadcastDestroyAndDisappearPlayerCharacterToRegionToOther( SCharacter* playerCharacter, SRegionObjectBase* region, Bool isFilterSelf = true );

		void	broadcastAppearPlayerCharacterToRegionToSelf(SPlayerCharacter* playerCharacter, SRegionObjectBase* region);
		void	broadcastAppearPlayerCharacterToRegionToOther(SPlayerCharacter* playerCharacter, SRegionObjectBase* region);

		void	broadcastDisappearPlayerCharacterToRegionToSelf(SCharacter* playerCharacter, SRegionObjectBase* region);
		void	broadcastDisappearPlayerCharacterToRegionToOther(SCharacter* playerCharacter, SRegionObjectBase* region);

		void	broadcastMonsterCreateAndAppearToRegion( SPlayerCharacter* playerCharacter, std::map<UInt, SSceneGrid*>& regionGridList );
		void	broadcastMonsterDestroyAndDisappearToRegion( SPlayerCharacter* playerCharacter, std::map<UInt, SSceneGrid*>& regionGridList );

		void	broadcastMonsterAppearToRegion(SMonster* monster, SRegionObjectBase* region);
		void	broadcastMonsterDisappearToRegion(SMonster* monster, SRegionObjectBase* region);

	};

}


#endif	//SRegionNetPacketProcesser