
/******************************************************************************/

#include "stdafx.h"
#include "SCampaignNetPacketProcesser.h"
#include "GameNetEvent.h"
#include "CenterServerMain.h"
#include "SCampaignManager.h"
#include "ServerManager.h"
#include "BattleConfig.h"
#include "ClientNetTranspondPacketProcesser.h"
#include "CenterServerMain.h"

/******************************************************************************/
namespace MG
{
	//--------------------------------------------------------------------------
	SCampaignNetPacketProcesser::SCampaignNetPacketProcesser()
	{
	}

	//--------------------------------------------------------------------------
	SCampaignNetPacketProcesser::~SCampaignNetPacketProcesser()
	{
	}

	//--------------------------------------------------------------------------
	Bool SCampaignNetPacketProcesser::processFrontServerPacket(I32 id, NetEventRecv* packet)
	{
		if ( packet->getChannel() == GNPC_CAMPAIGN )
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_CAMPAIGN_F2T_CAMPAIGN_LIST:
				onRecvCampaignListFromFrontServer( id , (PT_CAMPAIGN_F2T_CAMPAIGN_LIST_DATA*)data->data);
				break;
			case PT_CAMPAIGN_F2T_CREATE:
				onRecvCampaignCreateFromFrontServer( id , (PT_CAMPAIGN_F2T_CREATE_DATA*)data->data);
				break;
			case PT_CAMPAIGN_F2T_ENTER_ATTACK:
				onRecvCampaignEnterAttackFromFrontServer( id , (PT_CAMPAIGN_F2T_ENTER_ATTACK_DATA*)data->data);
				break;
			case PT_CAMPAIGN_F2T_ENTER_DEFENSE:
				onRecvCampaignEnterDefenseFromFrontServer( id , (PT_CAMPAIGN_F2T_ENTER_DEFENSE_DATA*)data->data);
				break;
			case PT_CAMPAIGN_F2T_START:
				onRecvCampaignStartFromFrontServer( id , (PT_CAMPAIGN_F2T_START_DATA*)data->data);
				break;
			case PT_CAMPAIGN_M2T_START_NEW_INSTANCE:
				onRecvCampaignJumpInstanceRegionFromMapServer( id , (PT_CAMPAIGN_M2T_START_NEW_INSTANCE_DATA*)data->data);
				break;
			case PT_CAMPAIGN_F2T_READY_MYSELF:
				onRecvCampaignReady( id , (PT_CAMPAIGN_F2T_READY_MYSELF_DATA*)data->data);
				break;
			case PT_CAMPAIGN_F2T_LEAVE:
				onRecvCampaignLeave( id , (PT_CAMPAIGN_F2T_LEAVE_DATA*)data->data);
				break;
			case PT_CAMPAIGN_F2T_LEAVE_IN_CAMPAIGN:
				onRecvCampaignLeaveInCampaign( id , (PT_CAMPAIGN_F2T_LEAVE_IN_CAMPAIGN_DATA*)data->data);
				break;
			case PT_CAMPAIGN_F2T_CHANGE_CAMP_CONTROL:
				onRecvCampaignChangeCampControl( id , (PT_CAMPAIGN_F2T_CHANGE_CAMP_CONTROL_DATA*)data->data);
				break;
			case PT_CAMPAIGN_F2T_TROOP_CONTROLLER_LIST:
				onRecvCampaignTroopControllerList( id , (PT_CAMPAIGN_F2T_TROOP_CONTROLLER_LIST_DATA*)data->data);
				break;
			case PT_CAMPAIGN_F2T_DISCONNECT:
				onRecvCampaignDisconnect( id , (PT_CAMPAIGN_F2T_DISCONNECT_DATA*)data->data);
				break;
			case PT_CAMPAIGN_M2T_MAIN_CAMP_DESTROY:
				onRecvCampaignMainCampDestroy( id , (PT_CAMPAIGN_M2T_MAIN_CAMP_DESTROY_DATA*)data->data);
				break;
			case PT_CAMPAIGN_F2T_END_MANUAL:
				onRecvCampaignEndManual( id , (PT_CAMPAIGN_F2T_END_MANUAL_DATA*)data->data);
				break;
			default:
				DYNAMIC_ASSERT(0);
				break;
			}

			return true;
		}
		return false;
	}

	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::onRecvCampaignCreateFromFrontServer(NetIdType frontServerNetId, PT_CAMPAIGN_F2T_CREATE_DATA* data )
	{
		AccountIdType	accountId		= data->accountId;
		ClanIdType		creatorClanId	= data->creatorClanId;
		RegionIdType	targetRegionId  = data->targetRegionId;

		SCampaign* newCampaign = SCampaignManager::getInstance().createCampaign(frontServerNetId, accountId, creatorClanId, data->creatorClanName, data->campaignName,
			targetRegionId, (REGION_OBJ_TYPE)data->targetRegionType);

#if 0	//for test
		for (Int i=1; i<3; ++i)
		{
			newCampaign->joinAttackList(frontServerNetId, accountId + i, creatorClanId + i, L"test1");

			ClanArmy*	newTemp = newCampaign->getAttackMemberInfoByClanId(data->creatorClanId + i);
			DYNAMIC_ASSERT(NULL != newTemp);
			newTemp->frontServerNetId							= frontServerNetId;
			newTemp->clientNetId								= data->clientNetId;
			newTemp->playerCharacterInfo.playerCharacterId		= data->creatorPlayerCharacterId + i;
			newTemp->playerCharacterInfo.charArtIcon			= data->charArtIcon;
			newTemp->playerCharacterInfo.playerCharacterName	= data->creatorPlayerCharacterName;
		}
#endif

#if 0	//for test
		for (Int i=1; i<100; ++i)
		{
			SCampaign* tempCampaign = SCampaignManager::getInstance().createCampaign(frontserverNetId, accountId+i, creatorClanId+i, data->creatorClanName, data->campaignName,
				targetRegionId);
			DYNAMIC_ASSERT(NULL != tempCampaign);
		}
#endif
		//��ʼ����ս������
		if( NULL == newCampaign)
		{
			//���ܷ���ս��
			sendCampaignErrorToFrontServer(frontServerNetId, CREATE_FAIL, data->clientNetId, accountId);
			return ;
		}

		ClanArmy*	newMember = newCampaign->getAttackHostMemberInfoByClanId(data->creatorClanId);
		DYNAMIC_ASSERT(NULL != newMember);
		newMember->frontServerNetId							= frontServerNetId;
		newMember->clientNetId								= data->clientNetId;
		newMember->playerCharacterInfo.playerCharacterId	= data->creatorPlayerCharacterId;
		newMember->playerCharacterInfo.charArtIcon			= data->charArtIcon;
		newMember->playerCharacterInfo.playerCharacterName	= data->creatorPlayerCharacterName;

		//sendCampaignCreateToClient(frontserverNetId, data);

		ClientNetTranspondSendDataBufferPtr dataPtr;
        ClientNetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr );
		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if(packet)
		{
			// ���ñ�ǩ
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_T2C_CREATE;


			// ת���߼���
			PT_CAMPAIGN_T2C_CREATE_DATA* sendData = (PT_CAMPAIGN_T2C_CREATE_DATA*)(packet->data);
			if ( sendData )
			{
				// ����߼���
				sendData->campaignInfo.accountId	  = data->accountId;
				//sendData->clientNetId				  = data->clientNetId;
				sendData->campaignInfo.campaignId	  = data->creatorClanId;
				sendData->campaignInfo.creatorClanId  = data->creatorClanId;
				sendData->campaignInfo.charArtIcon	  = data->charArtIcon;
				sendData->campaignInfo.targetRegionId = data->targetRegionId;
				WStrnCpyS(sendData->campaignInfo.creatorPlayerCharacterName, data->creatorPlayerCharacterName, MAX_CHARACTER_NAME_LEN);
				WStrnCpyS(sendData->campaignInfo.creatorClanName, data->creatorPlayerCharacterName, MAX_CLAN_NAME);
				WStrnCpyS(sendData->campaignInfo.campaignName, data->campaignName, MAX_CAMPAIGN_NAME);
				sendData->campaignInfo.memberNum = 0;

				// ��������.
				ClientNetTranspondPacketProcesser::getInstance().broadClientTranspondSendDataToFrontServer(dataPtr, 
					GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2C_CREATE_INFO::dataSize);
			}
		}
	}

	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::onRecvCampaignListFromFrontServer(NetIdType frontserverNetId, PT_CAMPAIGN_F2T_CAMPAIGN_LIST_DATA* data )
	{
		std::map<ClanIdType, SCampaign*>* campaignList = SCampaignManager::getInstance().getPrepareCampaignList();
		
		sendCampaignListToClient(frontserverNetId, campaignList, data->clientNetId, data->accountId);
	}

	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::onRecvCampaignStartFromFrontServer(NetIdType frontserverNetId, PT_CAMPAIGN_F2T_START_DATA* data )
	{
		SCampaign* campaign = SCampaignManager::getInstance().getPrepareCampaign(data->campaignId);

		//��ʼ����ս������
		if( NULL == campaign)
		{
			//���ܷ���ս��
			sendCampaignErrorToFrontServer(frontserverNetId, CAMPAIGN_START_FAIL, data->clientNetId, data->accountId);
			return ;
		}
		
		//�ܷ����㿪ʼ����
		if (false == campaign->canStartBattle(data->starterClanId))
		{
			sendCampaignErrorToFrontServer(frontserverNetId, CAMPAIGN_START_FAIL, data->clientNetId, data->accountId);
			return ;
		}

		sendCampaignStartToFrontServer(frontserverNetId,campaign, campaign->getAttackHostList()->begin()->second);
	}

	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::onRecvCampaignReady(NetIdType frontServerNetId, PT_CAMPAIGN_F2T_READY_MYSELF_DATA* data )
	{
		SCampaign* campaign = SCampaignManager::getInstance().getPrepareCampaign(data->campaignId);

		//��ʼ����ս������
		if( NULL == campaign)
		{
			//���ܷ���ս��
			sendCampaignErrorToFrontServer(frontServerNetId, CAMPAIGN_START_FAIL, data->clientNetId, campaign->getAttackHostInfoByClanId()->accountId);
			return ;
		}

		ClanArmy* myClanArmy = campaign->getAttackMemberInfoByClanId(data->myClanId);
		DYNAMIC_ASSERT(NULL != myClanArmy && false == myClanArmy->empty());
		//�ܷ����㿪ʼ����
		if (false == campaign->setReady(data->myClanId))
		{
			sendCampaignErrorToFrontServer(frontServerNetId, CAMPAIGN_READY_CONFIRM_FAIL, data->clientNetId, campaign->getAttackHostInfoByClanId()->accountId);
			return ;
		}

		broadMemberReadyToOtherMemberList(campaign, myClanArmy);
	}

	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::onRecvCampaignLeave(NetIdType frontServerNetId, PT_CAMPAIGN_F2T_LEAVE_DATA* data )
	{
		AccountIdType	accountId	= data->accountId;
		ClanIdType		myClanId	= data->clanId;
		CampaignIdType	campaignId  = data->campaignId;

		SCampaign* leaveCampaign = SCampaignManager::getInstance().getPrepareCampaign(campaignId);
		if (NULL == leaveCampaign)
		{
			//����ʧ��
			sendCampaignErrorToFrontServer(frontServerNetId, CAMPAIGN_LEAVE_FAIL, data->clientNetId, accountId);
			return ;
		}

		ClanArmy*	hostInfo = leaveCampaign->getAttackHostInfoByClanId();
		if (NULL != hostInfo && hostInfo->clanID == myClanId)
		{
			//���� �뿪�� �� �ݻ���������
			SCampaignManager::getInstance().destroyCampaign(campaignId);
			broadCampaignDestroyToAllFrontServer(campaignId);
			return;
		}

		ClanArmy* leaveMember = leaveCampaign->getAttackMemberInfoByClanId(myClanId);
		DYNAMIC_ASSERT(NULL != leaveMember);

		if (true == leaveMember->empty())
		{
			sendCampaignErrorToFrontServer(frontServerNetId, CAMPAIGN_LEAVE_FAIL, data->clientNetId, accountId);
			return ;
		}

		POSITION		leaveMemberPosition		= leaveMember->position;

		//�㲥���ͻ���
		ClientNetTranspondSendDataBufferPtr dataPtr;
        ClientNetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr );
		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_T2C_LEAVE;

			// ת���߼���
			PT_CAMPAIGN_T2C_LEAVE_DATA* sendData = (PT_CAMPAIGN_T2C_LEAVE_DATA*)(packet->data);
			if ( sendData )
			{
				sendData->accountId		= accountId;
				sendData->campaignId	= campaignId;
				sendData->clanId		= myClanId;
				sendData->myPosition	= (Byte)leaveMemberPosition;

				Int sendDataSize = GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2C_LEAVE_INFO::dataSize;


				//��������
				{
					std::map<POSITION, ClanArmy*>* memberList =  leaveCampaign->getAttackHostList();
					_broadCampaignMsgToMemberListViaClient(dataPtr, 
						GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2C_LEAVE_INFO::dataSize,
												memberList);
				}

				// ������ͨ���
				{
					std::map<POSITION, ClanArmy*>* memberList =  leaveCampaign->getAttackMemberList();
					_broadCampaignMsgToMemberListViaClient(dataPtr, 
						GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2C_LEAVE_INFO::dataSize,
												memberList);
				}
			}
		}

		//��ո������Ϣ
		leaveMember->clear();
		DYNAMIC_ASSERT(true == leaveMember->empty());

		//��������
		Int memberNum = leaveCampaign->getAttackRealMemberNum();
		leaveCampaign->setAttackRealMemberNum(--memberNum);
	}

	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::onRecvCampaignLeaveInCampaign(NetIdType frontServerNetId, PT_CAMPAIGN_F2T_LEAVE_IN_CAMPAIGN_DATA* data )
	{
		AccountIdType	accountId	= data->accountId;
		ClanIdType		myClanId	= data->clanId;
		CampaignIdType	campaignId  = data->campaignId;

		SCampaign* leaveCampaign = SCampaignManager::getInstance().getBattleCampaign(campaignId);
		if (NULL == leaveCampaign)
		{
			//�뿪ʧ��
			sendCampaignErrorToFrontServer(frontServerNetId, CAMPAIGN_LEAVE_FAIL, data->clientNetId, accountId);
			return ;
		}

		ClanArmy*	leaveClanInfo = leaveCampaign->getAttackHostInfoByClanId();
		if (NULL == leaveClanInfo)
		{
			sendCampaignErrorToFrontServer(frontServerNetId, CAMPAIGN_LEAVE_FAIL, data->clientNetId, accountId);
			return ;
		}

		if (leaveClanInfo->clanID != myClanId)
		{
			leaveClanInfo = NULL;
		}

		if (NULL == leaveClanInfo)
		{
			leaveClanInfo = leaveCampaign->getAttackMemberInfoByClanId(myClanId);
		}

		if (NULL == leaveClanInfo)
		{
			leaveClanInfo = leaveCampaign->getDefenseMemberInfoByClanId(myClanId);
		}
		

		DYNAMIC_ASSERT(leaveClanInfo->empty() == false);

		if (true == leaveClanInfo->empty())
		{
			sendCampaignErrorToFrontServer(frontServerNetId, CAMPAIGN_LEAVE_FAIL, data->clientNetId, accountId);
			return ;
		}

		//����Ƿ��Ǿ�Ӫ������
		if (FORCE_ATTACK == leaveClanInfo->force)
		{
			if (leaveCampaign->getAttackCampOwnerAccountId() == leaveClanInfo->accountId)
			{
				//���ǡ����������ľ�Ӫ������
				const AccountIdType targetCampOwnerAccountId = leaveCampaign->getRandomCampOwnerAccountId(FORCE_ATTACK, leaveClanInfo->accountId);
				if (targetCampOwnerAccountId > 0 && targetCampOwnerAccountId != leaveClanInfo->accountId)
				{
					//�ҵ�����������
					leaveCampaign->setAttackCampOwnerAccountId(targetCampOwnerAccountId);
					sendCampaignChangeCampOwnerToFrontServer(frontServerNetId, leaveCampaign, targetCampOwnerAccountId);
				}

			}
		}
		else if (FORCE_DEFENSE == leaveClanInfo->force)
		{
			if (leaveCampaign->getDefenseCampOwnerAccountId() == leaveClanInfo->accountId)
			{
				//���ǡ����ط����ľ�Ӫ������.
				const AccountIdType targetCampOwnerAccountId = leaveCampaign->getRandomCampOwnerAccountId(FORCE_DEFENSE, leaveClanInfo->accountId);
				if (targetCampOwnerAccountId > 0 && targetCampOwnerAccountId != leaveClanInfo->accountId)
				{
					leaveCampaign->setDefenseCampOwnerAccountId(targetCampOwnerAccountId);
					sendCampaignChangeCampOwnerToFrontServer(frontServerNetId, leaveCampaign, targetCampOwnerAccountId);
				}
			}
		}
		else
		{
			DYNAMIC_ASSERT(0);
		}

		sendLeaveInCampaignToFrontServer(leaveCampaign, leaveClanInfo);

		if (leaveClanInfo->force == FORCE_ATTACK)
		{
			Int attackRealMemberNum = leaveCampaign->getAttackRealMemberNum();
			leaveCampaign->setAttackRealMemberNum( --attackRealMemberNum );
		}
		else if(leaveClanInfo->force == FORCE_DEFENSE)
		{
			Int defenseRealMemberNum = leaveCampaign->getDefenseRealMemberNum();
			leaveCampaign->setDefenseRealMemberNum( --defenseRealMemberNum );
		}
		else
		{
			DYNAMIC_ASSERT(0);
		}
		//��ո������Ϣ
		leaveClanInfo->clear();
		DYNAMIC_ASSERT(true == leaveClanInfo->empty());

		Int attackMemberNum = leaveCampaign->getAttackRealMemberNum();
		Int DefenseMemberNum = leaveCampaign->getDefenseRealMemberNum();
		if ( (attackMemberNum <= 0) && (DefenseMemberNum <= 0) )
		{
			SCampaignManager::getInstance().destroyCampaign(campaignId);
			return;
		}
	}


	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::onRecvCampaignDisconnect(NetIdType frontServerNetId, PT_CAMPAIGN_F2T_DISCONNECT_DATA* data )
	{
		const ClanIdType	myClanId	= data->clanId;
		
		SCampaign* myCampaign = SCampaignManager::getInstance().getCampaignByClanId(myClanId);
		if (NULL == myCampaign)
		{
			return;
		}

		ClanArmy* myClanInfo = myCampaign->getClanArmyByClanId(myClanId);
		if (NULL == myClanInfo || true == myClanInfo->empty())
		{
			return;
		}

		const CampIdType campaignId = myCampaign->getCampaignId();
		
		//ս����û��ʼ
		myCampaign = SCampaignManager::getInstance().getPrepareCampaign(campaignId);
		if (NULL != myCampaign)
		{
			//���� ClanID �������е�ս����Ϣ
			PT_CAMPAIGN_F2T_LEAVE_DATA leaveData;
			memset(&leaveData, 0, sizeof(leaveData));
			leaveData.clanId = data->clanId;
			leaveData.campaignId = myCampaign->getCampaignId();
			//������ڷ�����
			onRecvCampaignLeave(frontServerNetId, &leaveData );
			return; 
		}

		//ս�����뿪�����
		myCampaign = SCampaignManager::getInstance().getBattleCampaign(campaignId);
		if (NULL != myCampaign)
		{
			Int memberNum = myCampaign->getAttackRealMemberNum();
			if (1 == memberNum)
			{
				//�������һ���ˣ� ս������
				SCampaignManager::getInstance().sendCampaignEndPacket(myCampaign, FORCE_DEFENSE);

				SCampaignManager::getInstance().destroyCampaign(campaignId);
				broadCampaignDestroyToAllFrontServer(campaignId);

				return;
			}

			//����Ƿ��Ǿ�Ӫ������
			if (FORCE_ATTACK == myClanInfo->force)
			{
				if (myCampaign->getAttackCampOwnerAccountId() == myClanInfo->accountId)
				{
					//���ǡ����������ľ�Ӫ������
					const AccountIdType targetCampOwnerAccountId = myCampaign->getRandomCampOwnerAccountId(FORCE_ATTACK, myClanInfo->accountId);
					if (targetCampOwnerAccountId > 0 && targetCampOwnerAccountId != myClanInfo->accountId)
					{
						//�ҵ�����������
						myCampaign->setAttackCampOwnerAccountId(targetCampOwnerAccountId);
						sendCampaignChangeCampOwnerToFrontServer(frontServerNetId, myCampaign, targetCampOwnerAccountId);
					}

				}
			}
			else if (FORCE_DEFENSE == myClanInfo->force)
			{
				if (myCampaign->getDefenseCampOwnerAccountId() == myClanInfo->accountId)
				{
					//���ǡ����ط����ľ�Ӫ������.
					const AccountIdType targetCampOwnerAccountId = myCampaign->getRandomCampOwnerAccountId(FORCE_DEFENSE, myClanInfo->accountId);
					if (targetCampOwnerAccountId > 0 && targetCampOwnerAccountId != myClanInfo->accountId)
					{
						myCampaign->setDefenseCampOwnerAccountId(targetCampOwnerAccountId);
						sendCampaignChangeCampOwnerToFrontServer(frontServerNetId, myCampaign, targetCampOwnerAccountId);
					}
				}
			}
			else
			{
				DYNAMIC_ASSERT(0);
			}

			//������Լ�����Ϣ
			myClanInfo->clear();

			//�鿴��ʣ����ٹ�������ң� ��ʱֻ��鹥����������
			myCampaign->setAttackRealMemberNum(--memberNum);
			return;
		}

		//����ʱ����
		myCampaign = SCampaignManager::getInstance().getEndCampaign(campaignId);
		if (NULL != myCampaign)
		{
			myClanInfo->isLeave = true;
			if (true == myCampaign->isAllClanLeave())
			{
				//���е���Ҷ��뿪�� ���������������
				SCampaignManager::getInstance().delEndCampaign(myCampaign->getCampaignId());
			}
			return;
		}
		else
		{
			DYNAMIC_ASSERT(0);
		}

	}

	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::onRecvCampaignMainCampDestroy(NetIdType frontServerNetId, PT_CAMPAIGN_M2T_MAIN_CAMP_DESTROY_DATA* data )
	{
		FORCE winnerForce = FORCE_INIT;
		if (FORCE_ATTACK == data->campForce)
		{
			winnerForce  =FORCE_DEFENSE;
		}
		else if (FORCE_DEFENSE == data->campForce)
		{
			winnerForce  =FORCE_ATTACK;
		}
		else
		{
			DYNAMIC_ASSERT(0);
		}
		DYNAMIC_ASSERT(winnerForce == FORCE_ATTACK || winnerForce == FORCE_DEFENSE);


		SCampaignManager::getInstance().mainCampDestroy(data->campaignId, winnerForce);
#if 0
		const CampaignIdType endBattleCampaignId = data->campaignId;
		std::map<CampaignIdType, SCampaign*>* battleList = SCampaignManager::getInstance().getOnBattleCampaignList();

		for ( std::map<CampaignIdType, SCampaign*>::iterator iter = battleList->begin(); 
			iter != battleList->end(); )
		{
			SCampaign* tempCampaign = iter->second;
			if (endBattleCampaignId == tempCampaign->getCampaignId())
			{
				//�ҵ� ʱ�䵽��ս�������б�ɾ��ս��
				CampaignIdType campaignId = tempCampaign->getCampaignId();
				SCampaignManager::getInstance().sendCampaignEndPacket(tempCampaign, winnerForce);
				battleList->erase(iter++);
			}
			else
			{
				++iter;
			}
		}
#endif
#if 0
		SCampaign* endCampaign = mOnBattleList.getSecondData(data->campaignId);

		sendCampaignEndPacket(endCampaign, endCampaign->getWinnerForce());
		endCampaign->setDestroyBattleTime(7);
		mDestroyBattleList.addData(endBattleCampaignId, endCampaign);

		mOnBattleList.eraseData(endBattleCampaignId);

		SCampaign* myCampaign = SCampaignManager::getInstance().getBattleCampaign(data->campaignId);
		if (NULL == myCampaign)
		{
			return; 
		}

		myCampaign->setWinnerForce(winnerForce);
		myCampaign->setEndBattleTime(0);
#endif
	}

	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::onRecvCampaignEndManual(NetIdType frontServerNetId, PT_CAMPAIGN_F2T_END_MANUAL_DATA* data )
	{
		SCampaign* myCampaign = SCampaignManager::getInstance().getBattleCampaign(data->campaignId);
		if (NULL == myCampaign)
		{
			return; 
		}

		myCampaign->setEndBattleTime(0);
	}

	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::onRecvCampaignChangeCampControl(NetIdType frontServerNetId, PT_CAMPAIGN_F2T_CHANGE_CAMP_CONTROL_DATA* data )
	{
		SCampaign* myCampaign = SCampaignManager::getInstance().getBattleCampaign(data->campaignId);
		if (NULL == myCampaign)
		{
			DYNAMIC_ASSERT(0);
			//send error
			return; 
		}

		//��ʱ�����
		//if (myCampaign->getAttackHostClanArmyInfo()->accountId == data->ownerAccountId)
		//{
		//	//send error
		//	return;
		//}

		sendCampaignChangeCampControlToFrontServer(frontServerNetId, myCampaign, data->targetControlerAccountId, data->campId);
	}

	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::onRecvCampaignTroopControllerList(NetIdType frontServerNetId, PT_CAMPAIGN_F2T_TROOP_CONTROLLER_LIST_DATA* data )
	{
		SCampaign* myCampaign = SCampaignManager::getInstance().getBattleCampaign(data->campaignId);
		if (NULL == myCampaign)
		{
			DYNAMIC_ASSERT(0);
			//send error
			return; 
		}

		ClanArmy* myClanArmy = myCampaign->getClanArmyByClanId(data->myClanId);
		if (NULL == myClanArmy || true == myClanArmy->empty())
		{
			//û�ҵ��ҵ���Ϣ
			return ;
		}
		
		//��ʼ�����ҵ�ID
		std::vector<NetTroopControllerInfo> memberList;
		AccountIdType campOwnerAccountId = 0;

		if (FORCE_ATTACK == myClanArmy->force)
		{
			campOwnerAccountId = myCampaign->getAttackCampOwnerAccountId();
			//������Ϣ 
			{
				std::map<POSITION, ClanArmy*>* attackHostList = myCampaign->getAttackHostList();
				for (std::map<POSITION, ClanArmy*>::iterator iter = attackHostList->begin(); iter != attackHostList->end(); ++iter)
				{
					ClanArmy* tempArmy = iter->second;
					if (false == tempArmy->empty())
					{
						NetTroopControllerInfo memInfo = { 0 };
						memInfo.accountId			= tempArmy->accountId;
						memInfo.playerCharacterId	= tempArmy->playerCharacterInfo.playerCharacterId;
						memInfo.charArtIcon			= tempArmy->playerCharacterInfo.charArtIcon;
						WStrnCpyS(memInfo.playerCharacterName, tempArmy->playerCharacterInfo.playerCharacterName.c_str(), MAX_CHARACTER_NAME_LEN);
						memberList.push_back(memInfo);
					}
				}
			}
			
			// ��ͨ���
			{
				std::map<POSITION, ClanArmy*>* attackMemberList = myCampaign->getAttackMemberList();
				for (std::map<POSITION, ClanArmy*>::iterator iter = attackMemberList->begin(); iter != attackMemberList->end(); ++iter)
				{
					ClanArmy* tempArmy = iter->second;
					if (false == tempArmy->empty())
					{
						NetTroopControllerInfo memInfo = { 0 };
						memInfo.accountId			= tempArmy->accountId;
						memInfo.playerCharacterId	= tempArmy->playerCharacterInfo.playerCharacterId;
						memInfo.charArtIcon			= tempArmy->playerCharacterInfo.charArtIcon;
						WStrnCpyS(memInfo.playerCharacterName, tempArmy->playerCharacterInfo.playerCharacterName.c_str(), MAX_CHARACTER_NAME_LEN);

						memberList.push_back(memInfo);
					}
				}
			}

		}
		else if(FORCE_DEFENSE == myClanArmy->force)
		{

			campOwnerAccountId = myCampaign->getDefenseCampOwnerAccountId();

			//���ط�
			std::map<POSITION, ClanArmy*>* defenseMemberList = myCampaign->getDefenseMemberList();
			for (std::map<POSITION, ClanArmy*>::iterator iter = defenseMemberList->begin(); iter != defenseMemberList->end(); ++iter)
			{
				ClanArmy* tempArmy = iter->second;
				if (false == tempArmy->empty())
				{
					NetTroopControllerInfo memInfo = { 0 };
					memInfo.accountId			= tempArmy->accountId;
					memInfo.playerCharacterId	= tempArmy->playerCharacterInfo.playerCharacterId;
					memInfo.charArtIcon			= tempArmy->playerCharacterInfo.charArtIcon;
					WStrnCpyS(memInfo.playerCharacterName, tempArmy->playerCharacterInfo.playerCharacterName.c_str(), MAX_CHARACTER_NAME_LEN);

					memberList.push_back(memInfo);
				}
			}
		}
		else
		{
			//�Ƿ�
			DYNAMIC_ASSERT(0);
			//send error
			return;
		}

		sendCampaignTroopControllerList(myCampaign, campOwnerAccountId, data->campId, &memberList, myClanArmy);

	}

	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::onRecvCampaignEnterAttackFromFrontServer(NetIdType frontServerNetId, PT_CAMPAIGN_F2T_ENTER_ATTACK_DATA* data )
	{
		AccountIdType	accountId	= data->accountId;
		ClanIdType		myClanId	= data->myClanId;
		CampaignIdType	campaignId  = data->campaignId;

		SCampaign* newCampaign = SCampaignManager::getInstance().enterCampaignJoinAttackList(frontServerNetId, accountId, campaignId, myClanId, data->myClanName);
		if (NULL ==newCampaign)
		{
			//����ʧ��
			sendCampaignErrorToFrontServer(frontServerNetId, CAMPAIGN_ENTER_FAIL, data->clientNetId, accountId);
			return ;
		}

		if (newCampaign->getAttackRealMemberNum() > POSITION_MAX)
		{
			//����ʧ�ܣ� ����
			sendCampaignErrorToFrontServer(frontServerNetId, CAMPAIGN_ENTER_FULL, data->clientNetId, accountId);
			return ;
		}


		ClanArmy*	newMember = newCampaign->getAttackMemberInfoByClanId(myClanId);
		DYNAMIC_ASSERT(NULL != newMember);
		newMember->frontServerNetId							= frontServerNetId;
		newMember->clientNetId								= data->clientNetId;
		newMember->playerCharacterInfo.playerCharacterId	= data->myPlayerCharacterId;
		newMember->playerCharacterInfo.charArtIcon			= data->charArtIcon;
		newMember->playerCharacterInfo.playerCharacterName	= data->myPlayerCharacterName;
		
		//�ҵ���Ϣ�㲥�����������, ����������
		broadEnterMemberMsgToOtherMemberList(newCampaign, newMember);

		//�����������Ϣ���͸���
		sendMemberListToNewMember(newCampaign->getAttackHostList(), newMember, newCampaign->getCampaignId(), FORCE_ATTACK, true);
		sendMemberListToNewMember(newCampaign->getAttackMemberList(), newMember, newCampaign->getCampaignId(), FORCE_ATTACK);
	}

	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::onRecvCampaignEnterDefenseFromFrontServer(NetIdType frontServerNetId, PT_CAMPAIGN_F2T_ENTER_DEFENSE_DATA* data )
	{
		SCampaign* curCampaign = SCampaignManager::getInstance().getBattleCampaign(data->campaignId);
		if (NULL ==curCampaign)
		{
			//����ʧ��
			sendCampaignErrorToFrontServer(frontServerNetId, CAMPAIGN_ENTER_FAIL, data->clientNetId, data->accountId);
			return ;
		}

		if (curCampaign->getDefenseRealMemberNum() > POSITION_MAX)
		{
			//����ʧ�ܣ� ����
			sendCampaignErrorToFrontServer(frontServerNetId, CAMPAIGN_ENTER_FULL, data->clientNetId, data->accountId);
			return ;
		}

		curCampaign->joinDefenseList(frontServerNetId, data->accountId, data->myClanId, data->myClanName);

		ClanArmy* newMember	= curCampaign->getDefenseMemberInfoByClanId(data->myClanId);

		DYNAMIC_ASSERT(NULL != newMember);
		newMember->accountId								= data->accountId;
		newMember->frontServerNetId							= frontServerNetId;
		newMember->clientNetId								= data->clientNetId;
		newMember->playerCharacterInfo.playerCharacterId	= data->myPlayerCharacterId;
		newMember->playerCharacterInfo.charArtIcon			= data->charArtIcon;
		newMember->playerCharacterInfo.playerCharacterName = data->myPlayerCharacterName;
		
		//send CampaignInfo������Ϣ�� �Ա�ͻ��˴���
		sendCampaignInfoToClient(curCampaign, newMember);

		sendMemberListToNewMember(curCampaign->getAttackHostList(), newMember, curCampaign->getCampaignId(), FORCE_ATTACK, true);
		sendMemberListToNewMember(curCampaign->getAttackMemberList(), newMember, curCampaign->getCampaignId(), FORCE_ATTACK);
		sendMemberListToNewMember(curCampaign->getDefenseMemberList(), newMember, curCampaign->getCampaignId(), FORCE_DEFENSE);


		//�޸���ҵ�ս���ڴ���Ϣ
		sendCampaignEnterDefenseToFrontServer(curCampaign, newMember);

		Bool isBattleLeader = false;
		Int memberNum = curCampaign->getDefenseRealMemberNum();
		if (0 == memberNum)
		{
			isBattleLeader = true;
		}
		//��ת��ͼ
		sendCampaignSingleMemberJumpRegionToFrontServer(newMember, curCampaign->getCampaignTargetRegionId(), curCampaign->getCampaignTargetInstance(), curCampaign->getDefenseRealMemberNum(), JUMP_DEFENSE, isBattleLeader, curCampaign->getPrepareTimeSecond());

		//��ʼ������Ӫ
		if (curCampaign->getDefenseCampOwnerAccountId() == 0)
		{
			curCampaign->setDefenseCampOwnerAccountId(data->accountId);
			sendCampaignCreateCampListByContorlerToFrontServer(frontServerNetId, curCampaign, data->accountId, FORCE_DEFENSE, POSITION_MAX, 0);
		}

		curCampaign->setDefenseRealMemberNum(++memberNum);
	}

	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::onRecvCampaignJumpInstanceRegionFromMapServer(NetIdType frontserverNetId, PT_CAMPAIGN_M2T_START_NEW_INSTANCE_DATA* data )
	{
		RegionIdType	targetRegionId	= data->targetRegionId;
		InstanceUIdType instanceUid		= data->instanceUid;
		CampaignIdType	campaignId		= data->campaignId;

		SCampaignManager* temp = &(SCampaignManager::getInstance());
		//��ս���ĵ�ͼ����
		SCampaign* myCampaign = SCampaignManager::getInstance().popPrepareCampaign(campaignId);
		DYNAMIC_ASSERT(NULL != myCampaign);
		myCampaign->setCampaignTargetInstanceId(instanceUid);
		
		std::map<POSITION, ClanArmy*>* hostList = myCampaign->getAttackHostList();
		std::map<POSITION, ClanArmy*>* memberList = myCampaign->getAttackMemberList();
		DYNAMIC_ASSERT(hostList->size() == 1);		//������һ������

		//֪ͨ�����������ԵĿͻ��ˣ� ��ս����ʼ
		myCampaign->setPrepareTimeSecond(myCampaign->getTimeListInfo()->time3);
		sendStartNewCampaignToClient(myCampaign);

		//����������� ���뵽 ս������
		sendCampaignMemberJumpRegionToFrontServer(hostList, targetRegionId, instanceUid, JUMP_ATTACK, myCampaign->getPrepareTimeSecond());
		sendCampaignMemberJumpRegionToFrontServer(memberList, targetRegionId, instanceUid, JUMP_ATTACK, myCampaign->getPrepareTimeSecond(), 1);
		
		//��׼��ս���б��з�����ս���б���
		SCampaignManager::getInstance().addCampaignStart(myCampaign, myCampaign->getTimeListInfo()->time2);	//����

		//������ط��μ�ս��
		sendInviteDefenseCampaignMemberToMapServer(myCampaign->getCampaignTargetRegionId(), instanceUid, myCampaign->getCampaignId());

		//��ʼ���� ��Ӫ����������
		ClanArmy* clanArmy = myCampaign->getAttackHostClanArmyInfo();
		DYNAMIC_ASSERT(NULL != clanArmy);
		sendCampaignCreateCampListByContorlerToFrontServer(clanArmy->frontServerNetId, myCampaign, clanArmy->accountId,FORCE_ATTACK, POSITION_MAX, 0);
	}

	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::sendCampaignErrorToFrontServer(NetIdType frontserverNetId, CAMPAIGN_ERROR error, NetIdType clientNetId, AccountIdType accountId)
	{
		ClientNetTranspondSendDataBufferPtr dataPtr;
        ClientNetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr );
		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_T2C_ERROR;

			// ת���߼���
			PT_CAMPAIGN_T2C_ERROR_DATA* sendData = (PT_CAMPAIGN_T2C_ERROR_DATA*)(packet->data);
			if ( sendData )
			{
				// ����߼���
				sendData->error = error;

				// ��������.
				ClientNetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(dataPtr, 
					GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2C_ERROR_INFO::dataSize,frontserverNetId,
									clientNetId, accountId);
			}
		}
	}

	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::broadCampaignDestroyToAllFrontServer(CampaignIdType campaignId)
	{
		ClientNetTranspondSendDataBufferPtr dataPtr ;
        ClientNetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr );
		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();

		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_T2C_DESTROY;

			// ת���߼���
			PT_CAMPAIGN_T2C_DESTROY_DATA* sendData = (PT_CAMPAIGN_T2C_DESTROY_DATA*)(packet->data);
			if ( sendData )
			{
				// ����߼���
				sendData->campaignId = campaignId;

				// ��������.
				ClientNetTranspondPacketProcesser::getInstance().broadClientTranspondSendDataToFrontServer(dataPtr,
							GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2C_DESTROY_INFO::dataSize);
			}
		}
	}

	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::sendCampaignCampaignListBeginToClient(NetIdType frontserverNetId, const NetIdType clientNetId,const AccountIdType accountId)
	{
		ClientNetTranspondSendDataBufferPtr dataPtr;
        ClientNetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr );
		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if(NULL == packet)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// ���ñ�ǩ
		packet->channel = GNPC_CAMPAIGN;
		packet->type    = PT_CAMPAIGN_T2C_CAMPAIGN_LIST_BEGIN;

		// ת���߼���
		PT_CAMPAIGN_T2C_CAMPAIGN_LIST_BEGIN_DATA* sendData = (PT_CAMPAIGN_T2C_CAMPAIGN_LIST_BEGIN_DATA*)(packet->data);
		if ( sendData )
		{
			// ����߼���

			// ��������.
			ClientNetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(dataPtr,
				GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2C_CAMPAIGN_LIST_BEGIN_INFO::dataSize,
				frontserverNetId, clientNetId, accountId);
		}
	}

	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::sendCampaignCampaignListEndToClient(NetIdType frontserverNetId, const NetIdType clientNetId,const AccountIdType accountId)
	{
		ClientNetTranspondSendDataBufferPtr dataPtr;
        ClientNetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr );
		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if(NULL == packet)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// ���ñ�ǩ
		packet->channel = GNPC_CAMPAIGN;
		packet->type    = PT_CAMPAIGN_T2C_CAMPAIGN_LIST_END;

		// ת���߼���
		PT_CAMPAIGN_T2C_CAMPAIGN_LIST_END_DATA* sendData = (PT_CAMPAIGN_T2C_CAMPAIGN_LIST_END_DATA*)(packet->data);
		if ( sendData )
		{
			// ����߼���

			// ��������.
			ClientNetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(dataPtr,
				GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2C_CAMPAIGN_LIST_END_INFO::dataSize,
				frontserverNetId, clientNetId, accountId);
		}
	}

	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::sendCampaignListToClient(NetIdType frontserverNetId, std::map<ClanIdType, SCampaign*>* campaignList, NetIdType clientNetId, AccountIdType accountId)
	{

		//--------------------------------------------------------------------------

		sendCampaignCampaignListBeginToClient(frontserverNetId, clientNetId, accountId);

		//--------------------------------------------------------------------------

		ClientNetTranspondSendDataBufferPtr dataPtr    ;
		GameNetPacketData* packet       = NULL;
		PT_CAMPAIGN_T2C_CAMPAIGN_LIST_DATA* sendData = NULL;

		// ��ǰ��������ͷ��С
		I32 sendDataHeadSize    = 0;
		// ��ǰ�������ݴ�С
		I32 sendDataSize        = 0;
		// ׼���������ݴ�С
		I32 prepareSendDataSize = 0;

		// ������ɫ����
		std::map<ClanIdType, SCampaign*>::iterator iter = campaignList->begin();
		while( campaignList->end() != iter )
		{
			//--------------------------------------------------------------------------

			if ( dataPtr.mDataPtr.isNull() == false )
			{
				// ����һ����ɫ���ݴ�С���������ݻ����С
				prepareSendDataSize = sendDataSize + PT_CAMPAIGN_T2C_CAMPAIGN_LIST_DATA_INFO::netAddCampainInfoSize;

				// ������ڻ�������С����
				if ( prepareSendDataSize >= dataPtr.getTranspondDataMaxSize(10) )
				{
					ClientNetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(
						dataPtr,
						GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2C_CAMPAIGN_LIST_DATA_INFO::dataSize(sendData),
						frontserverNetId, clientNetId, accountId);
					dataPtr.mDataPtr.setNull();
				}
			}

			//--------------------------------------------------------------------------

			if ( dataPtr.mDataPtr.isNull() )
			{
				ClientNetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer(dataPtr,MG_GAME_NET_PACKET_BIG_MAX_SIZE);
				packet       = (GameNetPacketData*) dataPtr.getTranspondData();

				if (NULL == packet)
				{
					DYNAMIC_ASSERT(0);
					return;
				}

				packet->channel = GNPC_CAMPAIGN;
				packet->type    = PT_CAMPAIGN_T2C_CAMPAIGN_LIST;

				sendData = (PT_CAMPAIGN_T2C_CAMPAIGN_LIST_DATA*)(packet->data);
				sendData->addCampainNum = 0;
				sendData->clientNetId = clientNetId;

				sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2C_CAMPAIGN_LIST_DATA_INFO::headSize;
				sendDataSize        = sendDataHeadSize;
				prepareSendDataSize = sendDataHeadSize;
			}

			//--------------------------------------------------------------------------

			NetCampainInfo* tempSend = &(sendData->addCampainInfo[sendData->addCampainNum]);
			SCampaign* tempCampaign = iter->second;

			tempSend->accountId			= tempCampaign->getCampaignCreatorAccountId();
			tempSend->campaignId		= tempCampaign->getCampaignId();
			tempSend->targetRegionId	= tempCampaign->getCampaignTargetRegionId();
			tempSend->targetRegionType	= tempCampaign->getCampaignTargetRegionType();
			tempSend->creatorClanId		= tempCampaign->getCampaignCreatorClanId();
			tempSend->charArtIcon		= tempCampaign->getAttackHostClanArmyInfo()->playerCharacterInfo.charArtIcon;
			WStrnCpyS(tempSend->creatorClanName, tempCampaign->getAttackHostClanArmyInfo()->playerCharacterInfo.playerCharacterName.c_str(), MAX_CHARACTER_NAME_LEN);
			WStrnCpyS(tempSend->creatorClanName, tempCampaign->getCampaignCreatorClanName().c_str(), MAX_CLAN_NAME);
			WStrnCpyS(tempSend->campaignName, tempCampaign->getCampaignName().c_str(), MAX_CAMPAIGN_NAME);
			tempSend->memberNum			= tempCampaign->getAttackRealMemberNum();

			sendDataSize += PT_CAMPAIGN_T2C_CAMPAIGN_LIST_DATA_INFO::netAddCampainInfoSize;

			++sendData->addCampainNum;
			++iter;
		}

		if ( dataPtr.mDataPtr.isNull() == false )
		{
			ClientNetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(
				dataPtr,
				GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2C_CAMPAIGN_LIST_DATA_INFO::dataSize(sendData),
				frontserverNetId, clientNetId, accountId);

			dataPtr.mDataPtr.setNull();
		}
		
		//--------------------------------------------------------------------------

		sendCampaignCampaignListEndToClient(frontserverNetId, clientNetId, accountId);
	}

	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::sendCampaignCreateToClient(NetIdType frontserverNetId, PT_CAMPAIGN_F2T_CREATE_DATA* data)
	{
		
	}

	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::sendCampaignInfoToClient(const SCampaign* campaignInfo, const ClanArmy* myClan)
	{
		ClientNetTranspondSendDataBufferPtr dataPtr;
        ClientNetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr );
		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if(packet)
		{
			// ���ñ�ǩ
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_T2C_CAMPAIGN_INFO;

			// ת���߼���
			PT_CAMPAIGN_T2C_CAMPAIGN_INFO_DATA* sendData = (PT_CAMPAIGN_T2C_CAMPAIGN_INFO_DATA*)(packet->data);
			if ( sendData )
			{
				// ����߼���
				sendData->campaignInfo.accountId	  = campaignInfo->getCampaignCreatorAccountId();
				sendData->campaignInfo.campaignId	  = campaignInfo->getCampaignId();
				sendData->campaignInfo.creatorClanId  = campaignInfo->getCampaignCreatorClanId();
				sendData->campaignInfo.charArtIcon	  = 0;
				sendData->campaignInfo.targetRegionId = campaignInfo->getCampaignTargetRegionId();
				WStrnCpyS(sendData->campaignInfo.creatorPlayerCharacterName, L"", MAX_CHARACTER_NAME_LEN);
				WStrnCpyS(sendData->campaignInfo.creatorClanName, L"", MAX_CLAN_NAME);
				WStrnCpyS(sendData->campaignInfo.campaignName, L"", MAX_CAMPAIGN_NAME);
				sendData->campaignInfo.memberNum = 0;

				const Int dataSize = GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2C_CAMPAIGN_INFO_INFO::dataSize;
				// ��������.
				ClientNetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(
					dataPtr, dataSize, 
					myClan->frontServerNetId, myClan->clientNetId, myClan->accountId);
			}
		}
	}

	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::broadEnterMemberMsgToOtherMemberList(SCampaign* campaign, ClanArmy* newClanInfo)
	{
		GameNetSendDataBufferPtr dataPtr;
        CenterServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );
        
		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();

		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_T2F_ENTER_ATTACK;

			// ת���߼���
			PT_CAMPAIGN_T2F_ENTER_ATTACK_DATA* sendData = (PT_CAMPAIGN_T2F_ENTER_ATTACK_DATA*)(packet->data);
			if ( sendData )
			{
				sendData->campaignId					= campaign->getCampaignId();
				sendData->targetRegionId				= campaign->getCampaignTargetRegionId();
				sendData->newMember.accountId			= newClanInfo->accountId;
				sendData->newMember.clanId				= newClanInfo->clanID;
				sendData->newMember.playerCharacterId	= newClanInfo->playerCharacterInfo.playerCharacterId;
				sendData->newMember.charArtIcon			= newClanInfo->playerCharacterInfo.charArtIcon;
				sendData->newMember.position			= newClanInfo->position;
				sendData->newMember.readyState			= newClanInfo->readyState;
				sendData->newMember.isHost				= false;

				//FrontServer ���
				sendData->newMember.level				= 0;
				sendData->newMember.hp					= 0;
				sendData->newMember.mp					= 0;

				Int sendDataSize = GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2F_ENTER_ATTACK_INFO::dataSize;

				//��������
				{
					std::map<POSITION, ClanArmy*>* memberList =  campaign->getAttackHostList();
					for (std::map<POSITION, ClanArmy*>::iterator iter = memberList->begin(); iter != memberList->end(); ++iter)
					{
						if (iter->second->empty() == true)
						{
							continue;
						}

						sendData->toPlayerAccount = iter->second->accountId;

						CenterServerMain::getInstance().getServerLauncher()->sendServer(dataPtr, 
							GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2F_ENTER_ATTACK_INFO::dataSize, 
							iter->second->frontServerNetId);

						CenterServerMain::getInstance().getServerLauncher()->cloneSendDataBuffer( dataPtr, dataPtr, UInt(dataPtr->getLogicDataSendSize()) );
						packet = (GameNetPacketData*) dataPtr->getLogicData();
						sendData = (PT_CAMPAIGN_T2F_ENTER_ATTACK_DATA*)(packet->data);
					}
				}

				// ������ͨ���
				{
					std::map<POSITION, ClanArmy*>* memberList =  campaign->getAttackMemberList();
					for (std::map<POSITION, ClanArmy*>::iterator iter = memberList->begin(); iter != memberList->end(); ++iter)
					{
						if (iter->second->empty() == true)
						{
							continue;
						}
						sendData->toPlayerAccount = iter->second->accountId;

						CenterServerMain::getInstance().getServerLauncher()->sendServer(dataPtr,
							GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2F_ENTER_ATTACK_INFO::dataSize, 
							iter->second->frontServerNetId);

						CenterServerMain::getInstance().getServerLauncher()->cloneSendDataBuffer( dataPtr, dataPtr, UInt(dataPtr->getLogicDataSendSize()) );
						packet = (GameNetPacketData*) dataPtr->getLogicData();
						sendData = (PT_CAMPAIGN_T2F_ENTER_ATTACK_DATA*)(packet->data);
					}
				}
				//������ͨ��� End
			}
		}
	}

	void SCampaignNetPacketProcesser::sendLeaveInCampaignToFrontServer(SCampaign* campaign, ClanArmy* newClanInfo)
	{
		GameNetSendDataBufferPtr dataPtr ;
		CenterServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();

		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_T2F_LEAVE_IN_CAMPAIGN;

			// ת���߼���
			PT_CAMPAIGN_T2F_LEAVE_IN_CAMPAIGN_DATA* sendData = (PT_CAMPAIGN_T2F_LEAVE_IN_CAMPAIGN_DATA*)(packet->data);
			if ( sendData )
			{
				sendData->accountId		= newClanInfo->accountId;
				sendData->campaignId	= campaign->getCampaignId();

				Int sendDataSize = GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2F_LEAVE_IN_CAMPAIGN_INFO::dataSize;

				CenterServerMain::getInstance().getServerLauncher()->sendServer(dataPtr, 
					GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2F_LEAVE_IN_CAMPAIGN_INFO::dataSize, 
					newClanInfo->frontServerNetId);

			}
		}
	}

	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::broadMemberReadyToOtherMemberList(SCampaign* campaign, ClanArmy* myClanInfo)
	{
		ClientNetTranspondSendDataBufferPtr dataPtr;
        ClientNetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr );
		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_T2C_READY_MYSELF;

			// ת���߼���
			PT_CAMPAIGN_T2C_READY_MYSELF_DATA* sendData = (PT_CAMPAIGN_T2C_READY_MYSELF_DATA*)(packet->data);
			if ( sendData )
			{
				//1. ȷ��   2.ȡ��

				sendData->campaignId		= campaign->getCampaignId();
				sendData->myClanId			= myClanInfo->clanID;
				sendData->myPosition		= myClanInfo->position;
				sendData->playerCharacterId	= myClanInfo->playerCharacterInfo.playerCharacterId;
				sendData->readyState		= myClanInfo->readyState;

				Int sendDataSize = GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2C_READY_MYSELF_INFO::dataSize;


				//��������
				{
					std::map<POSITION, ClanArmy*>* memberList =  campaign->getAttackHostList();
					_broadCampaignMsgToMemberListViaClient(dataPtr, 
						GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2C_READY_MYSELF_INFO::dataSize,
													memberList);
				}

				// ������ͨ���
				{
					std::map<POSITION, ClanArmy*>* memberList =  campaign->getAttackMemberList();
					_broadCampaignMsgToMemberListViaClient(dataPtr, 
						GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2C_READY_MYSELF_INFO::dataSize,
						memberList);
				}
				//������ͨ��� End
			}
		}
	}

	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::sendMemberListToNewMember(std::map<POSITION, ClanArmy*>* memberList, ClanArmy* newClanInfo, CampaignIdType campaignId, FORCE force, Bool isHost/* = false*/)
	{
		GameNetSendDataBufferPtr dataPtr ;

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = NULL;
		PT_CAMPAIGN_T2F_MEMBER_LIST_DATA* sendData = NULL;
		// ��ǰ��������ͷ��С
		I32 sendDataHeadSize    = 0;
		// ��ǰ�������ݴ�С
		I32 sendDataSize        = 0;
		// ׼���������ݴ�С
		I32 prepareSendDataSize = 0;

		// ������ɫ����
		std::map<POSITION, ClanArmy*>::iterator iter = memberList->begin();
		while( memberList->end() != iter && false == iter->second->empty() )
		{
			//--------------------------------------------------------------------------
			
			if ( dataPtr.isNull() == false )
			{
				// ����һ����ɫ���ݴ�С���������ݻ����С
				prepareSendDataSize = sendDataSize + PT_CAMPAIGN_T2F_MEMBER_LIST_DATA_INFO::netAddMemberInfoSize;

				// ������ڻ�������С����
				if ( prepareSendDataSize >= dataPtr->getLogicDataMaxSize() )
				{
					CenterServerMain::getInstance().getServerLauncher()->sendServer(
						dataPtr, 
						GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2F_MEMBER_LIST_DATA_INFO::dataSize(sendData), 
						newClanInfo->frontServerNetId);

					dataPtr.setNull();
				}
			}
	
			//--------------------------------------------------------------------------

			if ( dataPtr.isNull() )
			{
				CenterServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

				// ת���ɱ�׼����ʽ
				packet = (GameNetPacketData*) dataPtr->getLogicData();

				if ( !packet )
					return ;

				packet->channel = GNPC_CAMPAIGN;
				packet->type    = PT_CAMPAIGN_T2F_MEMBER_LIST;

				sendData = (PT_CAMPAIGN_T2F_MEMBER_LIST_DATA*)(packet->data);
				sendData->addMemberNum		= 0;
				sendData->frontServerNetId	= newClanInfo->frontServerNetId;
				sendData->campaignId		= campaignId;
				sendData->force				= force;
				sendData->accountId			= newClanInfo->accountId;

				sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2F_MEMBER_LIST_DATA_INFO::headSize;
				sendDataSize        = sendDataHeadSize;
				prepareSendDataSize = sendDataHeadSize;
			}

			//--------------------------------------------------------------------------
			
			NetCampaignMemberInfo* tempSend = &(sendData->addMemberInfo[sendData->addMemberNum]);
			ClanArmy* tempClan = iter->second;

			//���
			tempSend->accountId			= tempClan->accountId;
			tempSend->clanId			= tempClan->clanID;
			tempSend->playerCharacterId	= tempClan->playerCharacterInfo.playerCharacterId;
			tempSend->charArtIcon		= tempClan->playerCharacterInfo.charArtIcon;
			tempSend->position			= tempClan->position;
			tempSend->readyState		= tempClan->readyState;
			tempSend->isHost			= isHost;

			//FrontServer ���
			tempSend->level				= 0;
			tempSend->hp				= 0;
			tempSend->mp				= 0;

			sendDataSize += PT_CAMPAIGN_T2F_MEMBER_LIST_DATA_INFO::netAddMemberInfoSize;

			++sendData->addMemberNum;
			++iter;
		}

		//--------------------------------------------------------------------------

		if ( dataPtr.isNull() == false )
		{
			CenterServerMain::getInstance().getServerLauncher()->sendServer(
				dataPtr, 
				GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2F_MEMBER_LIST_DATA_INFO::dataSize(sendData), 
				newClanInfo->frontServerNetId);

			dataPtr.setNull();
		}
	}

	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::sendCampaignStartToFrontServer(NetIdType frontserverNetId, SCampaign* campaign, ClanArmy* hostArmy)
	{
		// ���һ�����͡��ͻ��ˡ�����
		GameNetSendDataBufferPtr dataPtr;
        CenterServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_T2F_START;

			// ת���߼���
			PT_CAMPAIGN_T2F_START_DATA* sendData = (PT_CAMPAIGN_T2F_START_DATA*)(packet->data);
			if ( sendData )
			{
				// ����߼���
				sendData->accountId			= hostArmy->accountId;
				sendData->targetRegionId	= campaign->getCampaignTargetRegionId();
				sendData->campaignId		= campaign->getCampaignId();


				// ��������
				CenterServerMain::getInstance().getServerLauncher()->sendServer(dataPtr, 
					GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2F_START_INFO::dataSize, 
					frontserverNetId);
			}
		}
	}

	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::sendStartNewCampaignToClient(SCampaign* campaign)
	{
		//�㲥�����еĿͻ���
		ClientNetTranspondSendDataBufferPtr dataPtr;
        ClientNetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr );
		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_T2C_START_NEW_CAMPAIGN;

			// ת���߼���
			PT_CAMPAIGN_T2C_START_NEW_CAMPAIGN_DATA* sendData = (PT_CAMPAIGN_T2C_START_NEW_CAMPAIGN_DATA*)(packet->data);
			if ( sendData )
			{
				sendData->campaignId 			= campaign->getCampaignId();
				sendData->regionId	 			= campaign->getCampaignTargetRegionId();
				sendData->regionType 			= campaign->getCampaignTargetRegionType();
				sendData->prepareTimeSecond		= campaign->getPrepareTimeSecond();

				ClientNetTranspondPacketProcesser::getInstance().broadClientTranspondSendDataToFrontServer(dataPtr,
					GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2C_START_NEW_CAMPAIGN_INFO::dataSize);
			}
		}
	}

	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::sendCampaignChangeCampControlToFrontServer(NetIdType frontserverNetId, SCampaign* campaign, AccountIdType targetControler, const CampIdType campId)
	{
		// ���һ�����͡��ͻ��ˡ�����
		GameNetSendDataBufferPtr dataPtr;
        CenterServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_T2F_CHANGE_CAMP_CONTROL;

			// ת���߼���
			PT_CAMPAIGN_T2F_CHANGE_CAMP_CONTROL_DATA* sendData = (PT_CAMPAIGN_T2F_CHANGE_CAMP_CONTROL_DATA*)(packet->data);
			if ( sendData )
			{
				// ����߼���
				sendData->targetRegionId			= campaign->getCampaignTargetRegionId();
				sendData->targetInstanceUId			= campaign->getCampaignTargetInstance();
				sendData->ownerAccountId			= campaign->getAttackHostClanArmyInfo()->accountId;
				sendData->campId					= campId;
				sendData->targetControlerAccountId	= targetControler;


				// ��������
				CenterServerMain::getInstance().getServerLauncher()->sendServer(dataPtr, 
					GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2F_CHANGE_CAMP_CONTROL_INFO::dataSize, 
					frontserverNetId);
			}
		}
	}

	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::sendCampaignChangeCampOwnerToFrontServer(NetIdType frontserverNetId,SCampaign* campaign, AccountIdType targetAccountId)
	{
		// ���һ�����͡��ͻ��ˡ�����
		GameNetSendDataBufferPtr dataPtr ;
        CenterServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if (NULL == packet )
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// ���ñ�ǩ
		packet->channel = GNPC_CAMPAIGN;
		packet->type    = PT_CAMPAIGN_T2F_CHANGE_CAMP_OWNER;

		// ת���߼���
		PT_CAMPAIGN_T2F_CHANGE_CAMP_OWNER_DATA* sendData = (PT_CAMPAIGN_T2F_CHANGE_CAMP_OWNER_DATA*)(packet->data);
		if ( sendData )
		{
			// ����߼���
			sendData->targetRegionId		= campaign->getCampaignTargetRegionId();
			sendData->targetInstanceUId		= campaign->getCampaignTargetInstance();
			sendData->accountId				= targetAccountId;

			// ��������
			CenterServerMain::getInstance().getServerLauncher()->sendServer(dataPtr, 
				GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2F_CHANGE_CAMP_OWNER_INFO::dataSize, 
				frontserverNetId);
		}
		
	}

	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::sendCampaignEnterDefenseToFrontServer(SCampaign* campaign, const ClanArmy* myArmy)
	{
		// ���һ�����͡��ͻ��ˡ�����
		GameNetSendDataBufferPtr dataPtr;
        CenterServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_T2F_ENTER_DEFENSE;

			// ת���߼���
			PT_CAMPAIGN_T2F_ENTER_DEFENSE_DATA* sendData = (PT_CAMPAIGN_T2F_ENTER_DEFENSE_DATA*)(packet->data);
			if ( sendData )
			{
				// ����߼���
				sendData->campaignId		= campaign->getCampaignId();
				sendData->regionId			= campaign->getCampaignTargetRegionId();
				sendData->regionType		= campaign->getCampaignTargetRegionType();
				sendData->prepareTimeSecond	= campaign->getPrepareTimeSecond();

				sendData->newMember.accountId			= myArmy->accountId;
				sendData->newMember.clanId				= myArmy->clanID;
				sendData->newMember.playerCharacterId	= myArmy->playerCharacterInfo.playerCharacterId;
				WStrnCpyS(sendData->newMember.playerCharacterName, myArmy->playerCharacterInfo.playerCharacterName.c_str(), MAX_CHARACTER_NAME_LEN);
				sendData->newMember.position			= myArmy->position;
				sendData->newMember.readyState			= myArmy->readyState;
				sendData->newMember.isHost				= false;

				sendData->newMember.level			= 0;
				sendData->newMember.charArtIcon		= myArmy->playerCharacterInfo.charArtIcon;
				sendData->newMember.hp				= 0;
				sendData->newMember.mp				= 0;


				const Int dataSize = GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2F_ENTER_DEFENSE_INFO::dataSize;
				//�㲥�����з��������
				{
					//����
					std::map<POSITION, ClanArmy*>* host = campaign->getAttackHostList();
					for (std::map<POSITION, ClanArmy*>::iterator iter = host->begin(); iter != host->end(); ++iter)
					{
						if (iter->second->empty() == true)
						{
							continue;
						}

						// ��������
						sendData->toAccountId	= iter->second->accountId;
						CenterServerMain::getInstance().getServerLauncher()->sendServer(dataPtr, dataSize, 
							iter->second->frontServerNetId);

						 CenterServerMain::getInstance().getServerLauncher()->cloneSendDataBuffer( dataPtr, dataPtr, UInt(dataPtr->getLogicDataSendSize()) );
						packet = (GameNetPacketData*) dataPtr->getLogicData();
						sendData = (PT_CAMPAIGN_T2F_ENTER_DEFENSE_DATA*)(packet->data);
					}
				}

				{
					//��������Ա
					std::map<POSITION, ClanArmy*>* host = campaign->getAttackMemberList();
					for (std::map<POSITION, ClanArmy*>::iterator iter = host->begin(); iter != host->end(); ++iter)
					{
						if (iter->second->empty() == true)
						{
							continue;
						}
						// ��������
						sendData->toAccountId	= iter->second->accountId;
						CenterServerMain::getInstance().getServerLauncher()->sendServer(dataPtr,
							dataSize, iter->second->frontServerNetId);

						CenterServerMain::getInstance().getServerLauncher()->cloneSendDataBuffer( dataPtr, dataPtr, UInt(dataPtr->getLogicDataSendSize()) );
						packet = (GameNetPacketData*) dataPtr->getLogicData();
						sendData = (PT_CAMPAIGN_T2F_ENTER_DEFENSE_DATA*)(packet->data);
					}
				}

				{
					//���ط���Ա
					std::map<POSITION, ClanArmy*>* host = campaign->getDefenseMemberList();
					for (std::map<POSITION, ClanArmy*>::iterator iter = host->begin(); iter != host->end(); ++iter)
					{
						if (iter->second->empty() == true)
						{
							continue;
						}

						//if (myArmy->accountId == iter->second->accountId)
						//{
						//	//�������Լ���
						//	continue;
						//}

						// ��������
						sendData->toAccountId	= iter->second->accountId;
						// ��������
						CenterServerMain::getInstance().getServerLauncher()->sendServer(dataPtr, 
							dataSize, iter->second->frontServerNetId);

						CenterServerMain::getInstance().getServerLauncher()->cloneSendDataBuffer( dataPtr, dataPtr, UInt(dataPtr->getLogicDataSendSize()) );
						packet = (GameNetPacketData*) dataPtr->getLogicData();
						sendData = (PT_CAMPAIGN_T2F_ENTER_DEFENSE_DATA*)(packet->data);
					}
				}
			}
		}
	}

	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::sendCampaignCreateCampListByContorlerToFrontServer(
		NetIdType frontserverNetId, SCampaign* campaign, AccountIdType campControlerId, FORCE campForce, Int campSize, Int indexStart)
	{
		// ���һ�����͡��ͻ��ˡ�����
		GameNetSendDataBufferPtr dataPtr;
        CenterServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( NULL == packet )
		{
			DYNAMIC_ASSERT(0);
			return;
		}
		// ���ñ�ǩ
		packet->channel = GNPC_CAMPAIGN;
		packet->type    = PT_CAMPAIGN_T2F_CREATE_CAMP_BY_CONTROLER;

		// ת���߼���
		PT_CAMPAIGN_T2F_CREATE_CAMP_BY_CONTROLER_DATA* sendData = (PT_CAMPAIGN_T2F_CREATE_CAMP_BY_CONTROLER_DATA*)(packet->data);
		if ( NULL == sendData )
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// ����߼���
		sendData->campaignId				= campaign->getCampaignId();
		sendData->targetRegionId			= campaign->getCampaignTargetRegionId();
		sendData->targetInstanceUId			= campaign->getCampaignTargetInstance();
		sendData->targetControlerAccountId	= campControlerId;
		sendData->campForce					= campForce;
		sendData->campNum					= campSize;
		sendData->campIndexStart			= indexStart;

		// ��������
		CenterServerMain::getInstance().getServerLauncher()->sendServer(dataPtr, 
			GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2F_CREATE_CAMP_BY_CONTROLER_INFO::dataSize, 
			frontserverNetId);
	}

	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::sendCampaignTroopControllerList(const SCampaign* myCampaign, const AccountIdType campOwnerAccountId, const CampIdType campId, std::vector<NetTroopControllerInfo>* memberList, ClanArmy* myClanArmy)
	{
		DYNAMIC_ASSERT(NULL != myCampaign && campOwnerAccountId > 0 && campId > 0);

		GameNetSendDataBufferPtr dataPtr ;

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = NULL;
		//packet->channel = GNPC_CAMPAIGN;
		//packet->type    = PT_CAMPAIGN_T2F_TROOP_CONTROLLER_LIST;

		PT_CAMPAIGN_T2F_TROOP_CONTROLLER_LIST_DATA* sendData = NULL;

		// ��ǰ��������ͷ��С
		I32 sendDataHeadSize    = 0;
		// ��ǰ�������ݴ�С
		I32 sendDataSize        = 0;
		// ׼���������ݴ�С
		I32 prepareSendDataSize = 0;

		// ������ɫ����
		std::vector<NetTroopControllerInfo>::iterator iter = memberList->begin();
		while( memberList->end() != iter)
		{
			//--------------------------------------------------------------------------
			
			if ( dataPtr.isNull() == false )
			{
				// ����һ����ɫ���ݴ�С���������ݻ����С
				prepareSendDataSize = sendDataSize + PT_CAMPAIGN_T2F_TROOP_CONTROLLER_LIST_DATA_INFO::netAddMemberInfoSize;

				// ������ڻ�������С����
				if ( prepareSendDataSize >= dataPtr->getLogicDataMaxSize() )
				{
					// ��������
					CenterServerMain::getInstance().getServerLauncher()->sendServer(
						dataPtr, 
						GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2F_TROOP_CONTROLLER_LIST_DATA_INFO::dataSize(sendData), 
						myClanArmy->frontServerNetId);
					dataPtr.setNull();
				}
			}

			//--------------------------------------------------------------------------

			if ( dataPtr.isNull() )
			{
				CenterServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

				// ת���ɱ�׼����ʽ
				packet = (GameNetPacketData*) dataPtr->getLogicData();

				if (NULL == packet)
				{
					DYNAMIC_ASSERT(0);
					return ;
				}

				packet->channel = GNPC_CAMPAIGN;
				packet->type    = PT_CAMPAIGN_T2F_TROOP_CONTROLLER_LIST;

				sendData = (PT_CAMPAIGN_T2F_TROOP_CONTROLLER_LIST_DATA*)(packet->data);
				sendData->myAccountId			= myClanArmy->accountId;
				sendData->targetRegionId		= myCampaign->getCampaignTargetRegionId();
				sendData->targetInstanceUId		= myCampaign->getCampaignTargetInstance();
				sendData->campId				= campId;
				sendData->campOwnerAccountId	= campOwnerAccountId;
				sendData->troopCurControllerAccountId	= 0;
				sendData->addMemberNum					= 0;

				// ��ǰ��������ͷ��С
				sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2F_TROOP_CONTROLLER_LIST_DATA_INFO::headSize;
				// ��ǰ�������ݴ�С
				sendDataSize        = sendDataHeadSize;
				// ׼���������ݴ�С
				prepareSendDataSize = sendDataHeadSize;
			}

			//--------------------------------------------------------------------------

			//��ʼ ���
			NetTroopControllerInfo* tempSend = &(sendData->addMemberInfo[sendData->addMemberNum]);
			tempSend->accountId	 = iter->accountId;
			tempSend->templateId = 0;
			tempSend->playerCharacterId	 = iter->playerCharacterId;
			WStrnCpyS(tempSend->playerCharacterName, iter->playerCharacterName, MAX_CHARACTER_NAME_LEN);

			sendDataSize += PT_CAMPAIGN_T2F_TROOP_CONTROLLER_LIST_DATA_INFO::netAddMemberInfoSize;

			++sendData->addMemberNum;
			++iter;
		}

		//--------------------------------------------------------------------------

		if ( dataPtr.isNull() == false )
		{
			CenterServerMain::getInstance().getServerLauncher()->sendServer(dataPtr, 
				GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2F_TROOP_CONTROLLER_LIST_DATA_INFO::dataSize(sendData), 
				myClanArmy->frontServerNetId);
			dataPtr.setNull();
		}
	}

	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::sendCampaignEndToFrontServer(SCampaign* campaign)
	{
		// ���һ�����͡��ͻ��ˡ�����
		GameNetSendDataBufferPtr dataPtr;
        CenterServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( NULL == packet )
		{
			DYNAMIC_ASSERT(0);
			return;
		}
		// ���ñ�ǩ
		packet->channel = GNPC_CAMPAIGN;
		packet->type    = PT_CAMPAIGN_T2F_END;

		// ת���߼���
		PT_CAMPAIGN_T2F_END_DATA* sendData = (PT_CAMPAIGN_T2F_END_DATA*)(packet->data);
		if ( NULL == sendData )
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// ����߼���
		sendData->targetRegionId	= campaign->getCampaignTargetRegionId();
		sendData->targetInstanceUId = campaign->getCampaignTargetInstance();
		sendData->campaignId		= campaign->getCampaignId();
		sendData->fromRegionId		= campaign->getCampaignTargetRegionId();		//��ʱ�����
		sendData->winnerForce		= campaign->getWinnerForce();


		ServerManager::getInstance().boardcastToFrontServers(dataPtr, 
			GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2F_END_INFO::dataSize);
	}

	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::_broadCampaignMsgToMemberListViaClient(
        ClientNetTranspondSendDataBufferPtr& dataPtr,
        Int sendDataSize,  
        std::map<POSITION, ClanArmy*>* memberList)
	{
		for (std::map<POSITION, ClanArmy*>::iterator iter = memberList->begin(); iter != memberList->end(); ++iter)
		{
			ClanArmy* clanArmy = iter->second;
			if (clanArmy->empty() == true)
			{
				continue;
			}

			ClientNetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(
                dataPtr, 
				sendDataSize, 
                clanArmy->frontServerNetId, 
                clanArmy->clientNetId, 
                clanArmy->accountId);
            
            CenterServerMain::getInstance().getServerLauncher()->cloneSendDataBuffer( dataPtr.mDataPtr, dataPtr.mDataPtr, UInt(dataPtr.mUsedHeadSize + dataPtr.mEstimateTailSize + sendDataSize ) );
		}
	}

	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::sendCampaignMemberJumpRegionToFrontServer(std::map<POSITION, ClanArmy*>* memberList, RegionIdType regionId, InstanceUIdType instanceUid, JUMP_TYPE jumpType, U32 prepareTimeSecond, Int startIndex)
	{
		Bool isBattleLeader = false;
		if (0 == startIndex && 
			(JUMP_ATTACK == jumpType || JUMP_DEFENSE == jumpType))
		{
			isBattleLeader = true;
		}

		Int index = startIndex;
		for (std::map<POSITION, ClanArmy*>::iterator iter = memberList->begin(); iter != memberList->end(); ++iter)
		{
			if (true == iter->second->empty())
			{
				continue;
			}

			sendCampaignSingleMemberJumpRegionToFrontServer(iter->second, regionId, instanceUid, index, jumpType, isBattleLeader, prepareTimeSecond);
			index++;
		}
	}

	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::sendCampaignSingleMemberJumpRegionToFrontServer(ClanArmy* myClan, RegionIdType regionId, InstanceUIdType instanceUid, Int index, JUMP_TYPE jumpType, Bool isBattleLeader, U32 prepareTimeSecond)
	{
		// ���һ�����͡��ͻ��ˡ�����
		GameNetSendDataBufferPtr dataPtr;
        CenterServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_T2F_START_JUMP_REGION;

			// ת���߼���
			PT_CAMPAIGN_T2F_START_JUMP_REGION_DATA* sendData = (PT_CAMPAIGN_T2F_START_JUMP_REGION_DATA*)(packet->data);
			if ( sendData )
			{
				sendData->accountId					= myClan->accountId;
				sendData->clanId					= myClan->clanID;
				sendData->toRegionId				= regionId;
				sendData->toRegionType				= ROT_PLACE;
				sendData->toInstanceId				= instanceUid;
				sendData->jumpType					= jumpType;
				sendData->jumpIndex					= index;
				sendData->isBattleLeader			= isBattleLeader;
				sendData->prepareTimeSecond			= prepareTimeSecond;
				// ��������
				CenterServerMain::getInstance().getServerLauncher()->sendServer(dataPtr, 
					GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2F_START_JUMP_REGION_INFO::dataSize, 
					myClan->frontServerNetId);
			}
		}
	}

	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::sendInviteDefenseCampaignMemberToMapServer(RegionIdType regionId, InstanceUIdType instanceUid, CampaignIdType campaignId)
	{
		// ���һ�����͡��ͻ��ˡ�����
		GameNetSendDataBufferPtr dataPtr;
        CenterServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_T2M_INVITE_DEFENSE_REGION;

			// ת���߼���
			PT_CAMPAIGN_T2M_INVITE_DEFENSE_REGION_DATA* sendData = (PT_CAMPAIGN_T2M_INVITE_DEFENSE_REGION_DATA*)(packet->data);
			if ( sendData )
			{
				sendData->toRegionId		= regionId;
				sendData->toInstanceId		= instanceUid;
				sendData->campaignId		= campaignId;

				// ��������
				ServerManager::getInstance().boardcastNetPacketToMapServers(dataPtr, 
					GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2M_INVITE_DEFENSE_REGION_INFO::dataSize);
			}
		}
	}

	//--------------------------------------------------------------------------


}