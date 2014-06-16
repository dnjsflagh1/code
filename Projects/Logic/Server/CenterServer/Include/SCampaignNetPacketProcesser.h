/******************************************************************************/
#ifndef _S_CAMPAIGN_NET_PACKET_PROCESSER_H_
#define _S_CAMPAIGN_NET_PACKET_PROCESSER_H_
/******************************************************************************/

#include "CenterServerPreqs.h"
#include "CampaignNetPacket.h"
#include "GameNetPacket.h"
#include "SCampaign.h"
#include "ClientNetTranspondPacketProcesser.h"

/******************************************************************************/
namespace MG
{

	class SCampaignNetPacketProcesser
	{
	public:
		SINGLETON_INSTANCE(SCampaignNetPacketProcesser);
		SCampaignNetPacketProcesser();
		~SCampaignNetPacketProcesser();

		Bool	processFrontServerPacket(I32 id, NetEventRecv* packet);


		/******************************************************************************/
		//MapServer 收到的消息
		void    onRecvCampaignCreateFromFrontServer(NetIdType frontServerNetId, PT_CAMPAIGN_F2T_CREATE_DATA* data );
		void    onRecvCampaignListFromFrontServer(NetIdType frontServerNetId, PT_CAMPAIGN_F2T_CAMPAIGN_LIST_DATA* data );
		void    onRecvCampaignStartFromFrontServer(NetIdType frontServerNetId, PT_CAMPAIGN_F2T_START_DATA* data );
		void    onRecvCampaignEnterAttackFromFrontServer(NetIdType frontServerNetId, PT_CAMPAIGN_F2T_ENTER_ATTACK_DATA* data );
		void    onRecvCampaignEnterDefenseFromFrontServer(NetIdType frontServerNetId, PT_CAMPAIGN_F2T_ENTER_DEFENSE_DATA* data );
		void    onRecvCampaignReady(NetIdType frontServerNetId, PT_CAMPAIGN_F2T_READY_MYSELF_DATA* data );
		void    onRecvCampaignLeave(NetIdType frontServerNetId, PT_CAMPAIGN_F2T_LEAVE_DATA* data );
		void    onRecvCampaignChangeCampControl(NetIdType frontServerNetId, PT_CAMPAIGN_F2T_CHANGE_CAMP_CONTROL_DATA* data );
		void    onRecvCampaignTroopControllerList(NetIdType frontServerNetId, PT_CAMPAIGN_F2T_TROOP_CONTROLLER_LIST_DATA* data );
		void    onRecvCampaignDisconnect(NetIdType frontServerNetId, PT_CAMPAIGN_F2T_DISCONNECT_DATA* data );
		void    onRecvCampaignMainCampDestroy(NetIdType frontServerNetId, PT_CAMPAIGN_M2T_MAIN_CAMP_DESTROY_DATA* data );
		void    onRecvCampaignEndManual(NetIdType frontServerNetId, PT_CAMPAIGN_F2T_END_MANUAL_DATA* data );


		void    onRecvCampaignLeaveInCampaign(NetIdType frontServerNetId, PT_CAMPAIGN_F2T_LEAVE_IN_CAMPAIGN_DATA* data );


		void	sendCampaignCreateToClient(NetIdType frontServerNetId, PT_CAMPAIGN_F2T_CREATE_DATA* data);
		void	sendCampaignErrorToFrontServer(NetIdType frontServerNetId, CAMPAIGN_ERROR error, NetIdType clientNetId, AccountIdType accountId);
		
		void	sendCampaignInfoToClient(const SCampaign* campaignInfo, const ClanArmy* myClan);

		void	sendCampaignCampaignListBeginToClient(NetIdType frontserverNetId, const NetIdType clientNetId,const AccountIdType accountId);
		void	sendCampaignListToClient(NetIdType frontServerNetId, std::map<ClanIdType, SCampaign*>* campaignList, NetIdType clientNetId, AccountIdType accountId);
		void	sendCampaignCampaignListEndToClient(NetIdType frontserverNetId, const NetIdType clientNetId,const AccountIdType accountId);

		void	sendCampaignStartToFrontServer(NetIdType frontServerNetId, SCampaign* campaign, ClanArmy* hostArmy);
		void	sendStartNewCampaignToClient(SCampaign* campaign);
		//void	sendCampaignEndToClient(SCampaign* campaign);
		void	sendCampaignEndToFrontServer(SCampaign* campaign);
		void	broadEnterMemberMsgToOtherMemberList(SCampaign* campaign, ClanArmy* newClanInfo);
		void	sendMemberListToNewMember(std::map<POSITION, ClanArmy*>* memberList, ClanArmy* newClanInfo, CampaignIdType campaignId,  FORCE force, Bool isHost = false);

		void	broadMemberReadyToOtherMemberList(SCampaign* campaign, ClanArmy* myClanInfo);

		void	broadCampaignDestroyToAllFrontServer(CampaignIdType campaignId);
		//战斗开始后要把角色放入到相应的副本区
		void	sendCampaignMemberJumpRegionToFrontServer(std::map<POSITION, ClanArmy*>* memberList, RegionIdType regionId, InstanceUIdType instanceUid, JUMP_TYPE jumpType, U32 prepareTimeSecond, Int startIndex = 0);
		void	sendCampaignSingleMemberJumpRegionToFrontServer(ClanArmy* myClan, RegionIdType regionId, InstanceUIdType instanceUid, Int index, JUMP_TYPE jumpType, Bool isBattleLeader, U32 prepareTimeSecond);
		
		void	sendInviteDefenseCampaignMemberToMapServer(RegionIdType regionId, InstanceUIdType instanceUid, CampaignIdType campaignId);
		//void	sendCampaignEndToMapServer(RegionIdType regionId, InstanceUIdType instanceUid, CampaignIdType campaignId);


		void	sendCampaignChangeCampControlToFrontServer(NetIdType frontserverNetId, SCampaign* campaign, AccountIdType targetControler, const CampIdType campId);
		void	sendCampaignChangeCampOwnerToFrontServer(NetIdType frontserverNetId, SCampaign* campaign, AccountIdType targetControler);


		void	sendCampaignEnterDefenseToFrontServer(SCampaign* curCampaign, const ClanArmy* myArmy);
		
		void	sendCampaignCreateCampListByContorlerToFrontServer(NetIdType frontserverNetId, SCampaign* campaign, AccountIdType campControlerId, FORCE campForce, Int campSize, Int indexStart);

		void	sendCampaignTroopControllerList(const SCampaign* myCampaign, const AccountIdType campOwnerAccountId, const CampIdType campId, std::vector<NetTroopControllerInfo>* memberList, ClanArmy* myClanArmy);
		

		void	sendLeaveInCampaignToFrontServer(SCampaign* campaign, ClanArmy* newClanInfo);
		
	private:
		//void	_sendCampaignEndToFrontServer(SCampaign* campaign, std::map<POSITION, ClanArmy*>* memberList);

		//把消息广播给memberList
		void	_broadCampaignMsgToMemberListViaClient(ClientNetTranspondSendDataBufferPtr& dataPtr, Int sendDataSize, std::map<POSITION, ClanArmy*>* memberList);


		
		/******************************************************************************/

	public:
		void    onRecvCampaignJumpInstanceRegionFromMapServer(NetIdType frontserverNetId, PT_CAMPAIGN_M2T_START_NEW_INSTANCE_DATA* data );

	};
}

#endif	//_S_CAMPAIGN_NET_PACKET_PROCESSER_H_