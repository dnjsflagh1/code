/******************************************************************************/
#ifndef _SCAMPAIGNNETPACKETPROCESSER_H_
#define _SCAMPAIGNNETPACKETPROCESSER_H_
/******************************************************************************/

#include "MapServerPreqs.h"
#include "GameNetPacket.h"
#include "CampaignNetPacket.h"
#include "NetTranspondPacketProcesser.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************/
	//�ֿ��ͼ������Ϣ����
	/******************************************************************************/
	class SCampaignNetPacketProcesser
	{
	public:
		SINGLETON_INSTANCE(SCampaignNetPacketProcesser);
		SCampaignNetPacketProcesser();
		~SCampaignNetPacketProcesser();

		Bool	processFrontServerPacket(I32 id, NetEventRecv* packet);
		Bool	processCenterServerPacket(I32 id, NetEventRecv* packet);

	public:

		//@{ FrontServer
		//void onRecvCampaignCreate(I32 id, PT_CAMPAIGN_F2M_CREATE_DATA* data);		//���� ����
		//void onRecvCampaignEnter(I32 id, PT_CAMPAIGN_F2M_ENTER_DATA* data);			// ���뵽�������б�
		//void onRecvCampaignReadyConfirm(I32 id, PT_CAMPAIGN_F2M_READY_DATA* data);
		//void onRecvCampaignList(I32 id, PT_CAMPAIGN_F2M_LIST_DATA* data);			// ��� �����б�

		//void onRecvCampaignLeave(I32 id, PT_CAMPAIGN_F2M_LEAVE_DATA* data);			// ����뿪
		//void onRecvCampaignKickClan(I32 id, PT_CAMPAIGN_F2M_KICK_CLAN_DATA* data);	//���� �����

		void onRecvCampaignStartFromFrontServer(I32 id, PT_CAMPAIGN_F2M_START_DATA* data);
		void onRecvCampaignInviteDefenseFromCenterServer(I32 id, PT_CAMPAIGN_T2M_INVITE_DEFENSE_REGION_DATA* data);
		//void onRecvCampaignEndFromCenterServer(I32 id, PT_CAMPAIGN_T2M_END_DATA* data);


		void sendCampaignStartNewRegionToCenterServer(CampaignIdType campaignId, SInstanceRegion *newRegion);
		void sendMainCampDestroyToCenterServer(const CampaignIdType campaignId, const FORCE myCampForce);

		/******************************************************************************/

		//void broadCampaignCreateToFrontServer(PT_CAMPAIGN_F2M_CREATE_DATA* data);

		//void sendCampaignCreateToCenterServer(PT_CAMPAIGN_F2M_CREATE_DATA* data);

	/******************************************************************************/
		
		
		//void onRecvCampaignJoinStandBy(I32 id, PT_CAMPAIGN_F2M_JOIN_STANDBY_DATA* data);
		//void onRecvCampaignJoinStandByMySelf(I32 id, PT_CAMPAIGN_F2M_JOIN_STANDBY_MYSELF_DATA* data);
		//void onRecvCampaignJoinWaiting(I32 id, PT_CAMPAIGN_F2M_JOIN_WATING_DATA* data);
		
		
		
		//void onRecvCampaignReadyMySelf(I32 id, PT_CAMPAIGN_F2M_READY_MYSELF_DATA* data);	//׼��

		
		


		//void onRecvCampaignArmyList(I32 id, PT_CAMPAIGN_CS_ARMYLIST_DATA* data);
		void onRecvCampaignChangeCampControl(I32 id, PT_CAMPAIGN_F2M_CHANGE_CAMP_CONTROL_DATA* data);
		void onRecvCampaignChangeCampOwner(I32 id, PT_CAMPAIGN_F2M_CHANGE_CAMP_OWNER_DATA* data);
		void onRecvCampaignTroopControllerList(I32 id, PT_CAMPAIGN_F2M_TROOP_CONTROLLER_LIST_DATA* data);
		void onRecvCampaignEnd(I32 id, PT_CAMPAIGN_F2M_END_DATA* data);

		void onRecvCampaignCreateCampByControler(I32 id, PT_CAMPAIGN_F2M_CREATE_CAMP_BY_CONTROLER_DATA* data);

		void broadcastChangeCampControlToRegion(SCamp* myCamp, SRegionObjectBase* region);
		void broadcastChangeTroopControlToRegion(SCamp* myCamp, SRegionObjectBase* region);
		void sendChangeTroopControlToPlayer( SPlayer* player, SCamp* myCamp);
		void sendTroopControllerListToPlayer(PT_CAMPAIGN_F2M_TROOP_CONTROLLER_LIST_DATA* data, SPlayer* myPlayer);


		void onCampaignLeave(const U64 accountId, const U64 regionId, const U64 campaignId, const U64 clanId);


		void broadcastCampaignEnd(std::map<PlayerCharacterIdType, SCharacter*>* playerCharacterList, SRegionObjectBase* regionObject, CampaignIdType campaignId, FORCE winnerForce, RegionIdType fromRegionId, SAtkInstance* atkInstanceInfo);
	
	public:
		void	sendCampaignError(U64 accountId, CAMPAIGN_ERROR error);

		//ս����ʼ���佫�;�������Ŀ���ͼ
		void	playerCharacterAndTroopJumpRegionWithPlayer(std::map<ClanIdType, ClanArmy*>* armyList,Byte regionType, Int regionID, JUMP_TYPE jumpType);
		void	playerCharacterAndTroopJumpRegionWithPlayer(std::map<ClanIdType, ClanArmy*>* armyList, SRegionObjectBase* region, JUMP_TYPE jumpType);


		void	playerCharacterAndTroopJumpRegionBackWithPlayer(std::map<ClanIdType, ClanArmy*>* armyList);
		//@ }

		//�������� ���ڴ�����
	//private:
	//	SMapObject_OldVersion*		_getMapObject(U64 regionId);
	//	SPlaceObject_OldVersion*	_getPlaceObject(U64 regionId);

	public:

		//void	broadToCampaignMember(NetTranspondSendDataBufferPtr& dataPtr, Int dataSize, Campaign* campaign);
		//void	broadToCampaignMember(Campaign* campaign, Byte channel,Byte type,CChar* data,I32 dataSize,U64 code);
		void	broadToCampaignMemberExclusive(Campaign* campaign, const U64 exceptAccountId, Byte channel,Byte type,CChar* data,I32 dataSize,U64 code);
		
		//�㲥��Ϣ��player���ڵ�MapObject����
		void	sendToPlayerInMapObject(NetTranspondSendDataBufferPtr& dataPtr, Int dataSize, SPlayer* player);
		void	sendToPlayerInMapObject(NetTranspondSendDataBufferPtr& dataPtr, Int dataSize, AccountIdType accountId);

		//�㲥��MapObject��������е���
		void	broadToMapObject(NetTranspondSendDataBufferPtr& dataPtr, Int dataSize, SMapObject* mapObject);

	};

}


#endif	//_SCAMPAIGNNETPACKETPROCESSER_H_