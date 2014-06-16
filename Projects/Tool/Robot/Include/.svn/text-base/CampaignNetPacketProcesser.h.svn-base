/******************************************************************************/
#ifndef _CAMPAIGNNETPACKETPROCESSER_H_
#define _CAMPAIGNNETPACKETPROCESSER_H_
/******************************************************************************/
#include "ClientPreqs.h"
#include "CommonGameDefine.h"
#include "GameNetEvent.h"
#include "CampaignNetPacket.h"
#include "CCampaign.h"
/******************************************************************************/
namespace MG
{
	class CampaignNetPacketProcesser
	{
	public:
		CampaignNetPacketProcesser(){isEnd = true;isEndHandle = true;}
		~CampaignNetPacketProcesser(){}
		SINGLETON_INSTANCE(CampaignNetPacketProcesser)

		Bool	processFrontServerPacket(CClient* client,NetEventRecv* packet);
		
		Bool	isEnd;
		Bool    isEndHandle;
	public:
		//--------------------------------- 接收 ---------------------------------
		void onRecvCampaignListBegin( CClient* client, PT_CAMPAIGN_T2C_CAMPAIGN_LIST_BEGIN_DATA* data );
		void onRecvCampaignList( CClient* client, PT_CAMPAIGN_T2C_CAMPAIGN_LIST_DATA* data );
		void onRecvCampaignListEnd( CClient* client, PT_CAMPAIGN_T2C_CAMPAIGN_LIST_END_DATA* data );
		
		void onRecvCampaignCreate( CClient* client, PT_CAMPAIGN_T2C_CREATE_DATA* data );				//ok
		void onRecvCampaignEnter( CClient* client, PT_CAMPAIGN_F2C_ENTER_ATTACK_DATA* data );				//ok
		void onRecvCampaignMemberList( CClient* client, PT_CAMPAIGN_F2C_MEMBER_LIST_DATA* data );
		void onRecvCampaignInviteDefense( CClient* client, PT_CAMPAIGN_M2C_INVITE_DEFENSE_REGION_DATA* data );
		void onRecvCampaignEnd( CClient* client, PT_CAMPAIGN_M2C_END_DATA* data );
		

		//void onRecvCampaignWaitingList( CClient* client, PT_CAMPAIGN_SC_WAITING_LIST_DATA* data );	//ok
		//void onRecvCampaignStandByList( CClient* client, PT_CAMPAIGN_SC_STANDBY_LIST_DATA* data );	//ok
		//void onRecvCampaignJoin( CClient* client, PT_CAMPAIGN_SC_JOIN_STANDBY_DATA* data );
		//void onRecvCampaignJoinMySelf( CClient* client, PT_CAMPAIGN_SC_JOIN_STANDBY_MYSELF_DATA* data );
		void onRecvCampaignReadyMySelf( CClient* client, PT_CAMPAIGN_T2C_READY_MYSELF_DATA* data );
		void onRecvCampaignLeave( CClient* client, PT_CAMPAIGN_T2C_LEAVE_DATA* data );
		void onRecvCampaignDestroy( CClient* client, PT_CAMPAIGN_T2C_DESTROY_DATA* data );
		void onRecvCampaignStartNewCampaign( CClient* client, PT_CAMPAIGN_T2C_START_NEW_CAMPAIGN_DATA* data );












		//void onRecvCampaignJoinWaiting( CClient* client, PT_CAMPAIGN_SC_JOIN_WATING_DATA* data );
		//void onRecvCampaignReady( CClient* client, PT_CAMPAIGN_SC_READY_DATA* data );
		
		//void onRecvCampaignStart( CClient* client, PT_CAMPAIGN_SC_START_DATA* data );
		void onRecvCampaignError( CClient* client, PT_CAMPAIGN_T2C_ERROR_DATA* data );
		
		//void onRecvCampaignArmyList( CClient* client, PT_CAMPAIGN_SC_ARMYLIST_DATA* data );
		//void onRecvCampaignEndBattle( CClient* client, PT_CAMPAIGN_SC_END_BATTLE_DATA* data );
		//void onRecvCampaignKick( CClient* client, PT_CAMPAIGN_SC_KICK_CLAN_DATA* data );

		//--------------------------------- 发送 ---------------------------------
		// ----------------------------------------- 重新整理 Begin -----------------------------------------

		//请求战斗房间列表
		void	sendCampaignList(I32 frontServerId);

		//发起战斗 【开房间】
		void	sendCampaignCreate(I32 frontServerId,const U64 creatorClanId, const U64 targetRegionId, const Char16* campaignName);

		//进入选中的战役房间大厅
		void	sendCampaignEnter(I32 frontServerId,const ClanIdType myClanId, const CampaignIdType campaignId);

		void	sendCampaignJoinDefense(I32 frontServerId,const RegionIdType targetRegionId, const CampaignIdType campaignId, const ClanIdType myClanId);

		//玩家准备
		void	sendCampaignReadyMySelf(I32 frontServerId,CampaignIdType campaignId, ClanIdType myClanId, PlayerCharacterIdType playerCharacterId);
		
		//离开房间
		void	sendCampaignLeave(I32 frontServerId,CampaignIdType campaignId, ClanIdType clanId);
	

		// ----------------------------------------- 重新整理 End -----------------------------------------
		
		
		//玩家自己进入某个位置
		/*void	sendCampaignJoinMySelf(U64 regionId, U64 campaignId, U64 joinClanId, Byte force, Byte position);*/

		




		//房主将玩家加入到战斗列表
		void	sendCampaignJoin(U64 regionId, U64 campaignId, U64 myClanId, U64 targetClanId);

		

		//房主将玩家加入从战斗列表 放到 等待大厅
		//void	sendWaitingJoin(U64 regionId, U64 campaignId, U64 myClanId, U64 targetClanId);
			
		

		

		


		//调整部队信息
		//void	sendCampaignArmyList(I32 frontServerId,U64 regionId, U64 campaignId, U64 clanId, U64 playerCharacterId, U64 troopId);

		//将玩家从房间踢出
		//void	sendCampaignKickClan( const U64 regionId, const U64 campaignId, const U64 myClanId, const U64 kickClanId, const Byte force, const Byte position);

		//所有的人都准备好，开始战斗
		void	sendCampaignStart(I32 frontServerId,const CampaignIdType campaignId, const ClanIdType starterClanId);
		void	sendCampaignEndManual(I32 frontServerId,CampaignIdType campaignId);

	};
}

#endif	//_CAMPAIGNNETPACKETPROCESSER_H_
