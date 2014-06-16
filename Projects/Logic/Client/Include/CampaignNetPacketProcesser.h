/******************************************************************************/
#ifndef _CAMPAIGNNETPACKETPROCESSER_H_
#define _CAMPAIGNNETPACKETPROCESSER_H_
/******************************************************************************/
#include "ClientPreqs.h"
#include "CommonGameDefine.h"
#include "GameNetEvent.h"
#include "CampaignNetPacket.h"
#include "SCampaign.h"
/******************************************************************************/
namespace MG
{
	class CampaignNetPacketProcesser
	{
	public:
		CampaignNetPacketProcesser(){};
		~CampaignNetPacketProcesser(){}
		SINGLETON_INSTANCE(CampaignNetPacketProcesser)

		Bool	processFrontServerPacket(I32 id,NetEventRecv* packet);

	public:
		//--------------------------------- 接收 ---------------------------------

		void onRecvCampaignListBegin( I32 id, PT_CAMPAIGN_T2C_CAMPAIGN_LIST_BEGIN_DATA* data );
		void onRecvCampaignList( I32 id, PT_CAMPAIGN_T2C_CAMPAIGN_LIST_DATA* data );
		void onRecvCampaignListEnd( I32 id, PT_CAMPAIGN_T2C_CAMPAIGN_LIST_END_DATA* data );
		
		void onRecvCampaignCreate( I32 id, PT_CAMPAIGN_T2C_CREATE_DATA* data );				//ok
		void onRecvCampaignEnterAttack( I32 id, PT_CAMPAIGN_F2C_ENTER_ATTACK_DATA* data );				//ok
		void onRecvCampaignEnterDefense( I32 id, PT_CAMPAIGN_F2C_ENTER_DEFENSE_DATA* data );				//ok
		void onRecvCampaignInfo( I32 id, PT_CAMPAIGN_T2C_CAMPAIGN_INFO_DATA* data );

		void onRecvCampaignMemberList( I32 id, PT_CAMPAIGN_F2C_MEMBER_LIST_DATA* data );
		void onRecvCampaignInviteDefense( I32 id, PT_CAMPAIGN_M2C_INVITE_DEFENSE_REGION_DATA* data );
		void onRecvCampaignEnd( I32 id, PT_CAMPAIGN_M2C_END_DATA* data );
		

		//void onRecvCampaignWaitingList( I32 id, PT_CAMPAIGN_SC_WAITING_LIST_DATA* data );	//ok
		//void onRecvCampaignStandByList( I32 id, PT_CAMPAIGN_SC_STANDBY_LIST_DATA* data );	//ok
		//void onRecvCampaignJoin( I32 id, PT_CAMPAIGN_SC_JOIN_STANDBY_DATA* data );
		//void onRecvCampaignJoinMySelf( I32 id, PT_CAMPAIGN_SC_JOIN_STANDBY_MYSELF_DATA* data );
		void onRecvCampaignReadyMySelf( I32 id, PT_CAMPAIGN_T2C_READY_MYSELF_DATA* data );
		void onRecvCampaignLeave( I32 id, PT_CAMPAIGN_T2C_LEAVE_DATA* data );
		void onRecvCampaignDestroy( I32 id, PT_CAMPAIGN_T2C_DESTROY_DATA* data );
		void onRecvCampaignStartNewCampaign( I32 id, PT_CAMPAIGN_T2C_START_NEW_CAMPAIGN_DATA* data );
		void onRecvCampaignChangeCampControl( I32 id, PT_CAMPAIGN_M2C_CHANGE_CAMP_CONTROL_DATA* data );
		void onRecvCampaignChangeTroopControl( I32 id, PT_CAMPAIGN_M2C_CHANGE_TROOP_CONTROL_DATA* data );
		void onRecvCampaignTroopControllerList( I32 id, PT_CAMPAIGN_M2C_TROOP_CONTROLLER_LIST_DATA* data );

		void onRecvCampaignLeaveInCampaign( I32 id, PT_CAMPAIGN_F2C_LEAVE_IN_CAMPAIGN_DATA* data );











		//void onRecvCampaignJoinWaiting( I32 id, PT_CAMPAIGN_SC_JOIN_WATING_DATA* data );
		//void onRecvCampaignReady( I32 id, PT_CAMPAIGN_SC_READY_DATA* data );
		
		//void onRecvCampaignStart( I32 id, PT_CAMPAIGN_SC_START_DATA* data );
		void onRecvCampaignError( I32 id, PT_CAMPAIGN_T2C_ERROR_DATA* data );
		
		//void onRecvCampaignArmyList( I32 id, PT_CAMPAIGN_SC_ARMYLIST_DATA* data );
		//void onRecvCampaignEndBattle( I32 id, PT_CAMPAIGN_SC_END_BATTLE_DATA* data );
		//void onRecvCampaignKick( I32 id, PT_CAMPAIGN_SC_KICK_CLAN_DATA* data );

		//--------------------------------- 发送 ---------------------------------
		// ----------------------------------------- 重新整理 Begin -----------------------------------------

		//请求战斗房间列表
		void	sendCampaignList();

		//发起战斗 【开房间】
		void	sendCampaignCreate(ClanIdType creatorClanId, RegionIdType targetRegionId, const Char16* campaignName, REGION_OBJ_TYPE targetRegionType);

		//进入选中的战役房间大厅
		void	sendCampaignEnter(const ClanIdType myClanId, const CampaignIdType campaignId);

		void	sendCampaignJoinDefense(const RegionIdType targetRegionId, const CampaignIdType campaignId, const ClanIdType myClanId);

		//玩家准备
		void	sendCampaignReadyMySelf(CampaignIdType campaignId, ClanIdType myClanId, PlayerCharacterIdType playerCharacterId);
		
		//离开房间
		void	sendCampaignLeave(CampaignIdType campaignId, ClanIdType clanId);
	
		//战斗中离开
		void	sendCampaignLeaveInCampaign(CampaignIdType campaignId, ClanIdType clanId);

		//改变军营的控制权
		void	sendCampaignChangeCampControl(const CampaignIdType	campaignId, const AccountIdType	ownerAccountId, const CampIdType campId, const AccountIdType targetControlerAccountId);

		void	sendCampaignTroopControllerList(const AccountIdType	myAccountId, const CampaignIdType myCampainId, const CampIdType campId);

		//手动结束 战斗， ChinaJoy 版本
		void	sendCampaignEndManual(CampaignIdType campaignId);

		//离开结算界面
		void	sendCampaignLeaveScore(PlayerCharacterIdType playerCharacterId, U32 itemGroupId);
		// ----------------------------------------- 重新整理 End -----------------------------------------
		
		
		//玩家自己进入某个位置
		//void	sendCampaignJoinMySelf(U64 regionId, U64 campaignId, U64 joinClanId, Byte force, Byte position);

		




		//房主将玩家加入到战斗列表
		void	sendCampaignJoin(U64 regionId, U64 campaignId, U64 myClanId, U64 targetClanId);

		

		//房主将玩家加入从战斗列表 放到 等待大厅
		//void	sendWaitingJoin(U64 regionId, U64 campaignId, U64 myClanId, U64 targetClanId);
			
		

		

		


		//调整部队信息
		//void	sendCampaignArmyList(U64 regionId, U64 campaignId, U64 clanId, U64 playerCharacterId, U64 troopId);

		//将玩家从房间踢出
		//void	sendCampaignKickClan( const U64 regionId, const U64 campaignId, const U64 myClanId, const U64 kickClanId, const Byte force, const Byte position);

		//所有的人都准备好，开始战斗
		void	sendCampaignStart(const CampaignIdType campaignId, const ClanIdType starterClanId);


	};
}

#endif	//_CAMPAIGNNETPACKETPROCESSER_H_
