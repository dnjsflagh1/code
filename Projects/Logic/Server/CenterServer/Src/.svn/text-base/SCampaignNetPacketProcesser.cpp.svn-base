
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
		//开始创建战斗对象
		if( NULL == newCampaign)
		{
			//不能发起战斗
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
			// 设置标签
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_T2C_CREATE;


			// 转换逻辑包
			PT_CAMPAIGN_T2C_CREATE_DATA* sendData = (PT_CAMPAIGN_T2C_CREATE_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
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

				// 发送数据.
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

		//开始创建战斗对象
		if( NULL == campaign)
		{
			//不能发起战斗
			sendCampaignErrorToFrontServer(frontserverNetId, CAMPAIGN_START_FAIL, data->clientNetId, data->accountId);
			return ;
		}
		
		//能否满足开始条件
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

		//开始创建战斗对象
		if( NULL == campaign)
		{
			//不能发起战斗
			sendCampaignErrorToFrontServer(frontServerNetId, CAMPAIGN_START_FAIL, data->clientNetId, campaign->getAttackHostInfoByClanId()->accountId);
			return ;
		}

		ClanArmy* myClanArmy = campaign->getAttackMemberInfoByClanId(data->myClanId);
		DYNAMIC_ASSERT(NULL != myClanArmy && false == myClanArmy->empty());
		//能否满足开始条件
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
			//进入失败
			sendCampaignErrorToFrontServer(frontServerNetId, CAMPAIGN_LEAVE_FAIL, data->clientNetId, accountId);
			return ;
		}

		ClanArmy*	hostInfo = leaveCampaign->getAttackHostInfoByClanId();
		if (NULL != hostInfo && hostInfo->clanID == myClanId)
		{
			//房主 离开， 则 摧毁整个房间
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

		//广播给客户端
		ClientNetTranspondSendDataBufferPtr dataPtr;
        ClientNetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr );
		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_T2C_LEAVE;

			// 转换逻辑包
			PT_CAMPAIGN_T2C_LEAVE_DATA* sendData = (PT_CAMPAIGN_T2C_LEAVE_DATA*)(packet->data);
			if ( sendData )
			{
				sendData->accountId		= accountId;
				sendData->campaignId	= campaignId;
				sendData->clanId		= myClanId;
				sendData->myPosition	= (Byte)leaveMemberPosition;

				Int sendDataSize = GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2C_LEAVE_INFO::dataSize;


				//发给房主
				{
					std::map<POSITION, ClanArmy*>* memberList =  leaveCampaign->getAttackHostList();
					_broadCampaignMsgToMemberListViaClient(dataPtr, 
						GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2C_LEAVE_INFO::dataSize,
												memberList);
				}

				// 发给普通玩家
				{
					std::map<POSITION, ClanArmy*>* memberList =  leaveCampaign->getAttackMemberList();
					_broadCampaignMsgToMemberListViaClient(dataPtr, 
						GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2C_LEAVE_INFO::dataSize,
												memberList);
				}
			}
		}

		//清空该玩家信息
		leaveMember->clear();
		DYNAMIC_ASSERT(true == leaveMember->empty());

		//数量减掉
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
			//离开失败
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

		//检查是否是军营控制者
		if (FORCE_ATTACK == leaveClanInfo->force)
		{
			if (leaveCampaign->getAttackCampOwnerAccountId() == leaveClanInfo->accountId)
			{
				//我是【进攻方】的军营控制者
				const AccountIdType targetCampOwnerAccountId = leaveCampaign->getRandomCampOwnerAccountId(FORCE_ATTACK, leaveClanInfo->accountId);
				if (targetCampOwnerAccountId > 0 && targetCampOwnerAccountId != leaveClanInfo->accountId)
				{
					//找到满足条件的
					leaveCampaign->setAttackCampOwnerAccountId(targetCampOwnerAccountId);
					sendCampaignChangeCampOwnerToFrontServer(frontServerNetId, leaveCampaign, targetCampOwnerAccountId);
				}

			}
		}
		else if (FORCE_DEFENSE == leaveClanInfo->force)
		{
			if (leaveCampaign->getDefenseCampOwnerAccountId() == leaveClanInfo->accountId)
			{
				//我是【防守方】的军营控制者.
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
		//清空该玩家信息
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
		
		//战斗还没开始
		myCampaign = SCampaignManager::getInstance().getPrepareCampaign(campaignId);
		if (NULL != myCampaign)
		{
			//根据 ClanID 遍历所有的战场信息
			PT_CAMPAIGN_F2T_LEAVE_DATA leaveData;
			memset(&leaveData, 0, sizeof(leaveData));
			leaveData.clanId = data->clanId;
			leaveData.campaignId = myCampaign->getCampaignId();
			//该玩家在房间里
			onRecvCampaignLeave(frontServerNetId, &leaveData );
			return; 
		}

		//战斗中离开的情况
		myCampaign = SCampaignManager::getInstance().getBattleCampaign(campaignId);
		if (NULL != myCampaign)
		{
			Int memberNum = myCampaign->getAttackRealMemberNum();
			if (1 == memberNum)
			{
				//我是最后一个人， 战斗结束
				SCampaignManager::getInstance().sendCampaignEndPacket(myCampaign, FORCE_DEFENSE);

				SCampaignManager::getInstance().destroyCampaign(campaignId);
				broadCampaignDestroyToAllFrontServer(campaignId);

				return;
			}

			//检查是否是军营控制者
			if (FORCE_ATTACK == myClanInfo->force)
			{
				if (myCampaign->getAttackCampOwnerAccountId() == myClanInfo->accountId)
				{
					//我是【进攻方】的军营控制者
					const AccountIdType targetCampOwnerAccountId = myCampaign->getRandomCampOwnerAccountId(FORCE_ATTACK, myClanInfo->accountId);
					if (targetCampOwnerAccountId > 0 && targetCampOwnerAccountId != myClanInfo->accountId)
					{
						//找到满足条件的
						myCampaign->setAttackCampOwnerAccountId(targetCampOwnerAccountId);
						sendCampaignChangeCampOwnerToFrontServer(frontServerNetId, myCampaign, targetCampOwnerAccountId);
					}

				}
			}
			else if (FORCE_DEFENSE == myClanInfo->force)
			{
				if (myCampaign->getDefenseCampOwnerAccountId() == myClanInfo->accountId)
				{
					//我是【防守方】的军营控制者.
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

			//清空我自己的信息
			myClanInfo->clear();

			//查看还剩余多少攻击方玩家， 暂时只检查攻击方的数量
			myCampaign->setAttackRealMemberNum(--memberNum);
			return;
		}

		//结算时掉线
		myCampaign = SCampaignManager::getInstance().getEndCampaign(campaignId);
		if (NULL != myCampaign)
		{
			myClanInfo->isLeave = true;
			if (true == myCampaign->isAllClanLeave())
			{
				//所有的玩家都离开， 立即结束结算界面
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
				//找到 时间到的战斗，从列表删除战斗
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

		//暂时不检测
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
			//没找到我的信息
			return ;
		}
		
		//开始填充玩家的ID
		std::vector<NetTroopControllerInfo> memberList;
		AccountIdType campOwnerAccountId = 0;

		if (FORCE_ATTACK == myClanArmy->force)
		{
			campOwnerAccountId = myCampaign->getAttackCampOwnerAccountId();
			//房主信息 
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
			
			// 普通玩家
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

			//防守方
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
			//非法
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
			//进入失败
			sendCampaignErrorToFrontServer(frontServerNetId, CAMPAIGN_ENTER_FAIL, data->clientNetId, accountId);
			return ;
		}

		if (newCampaign->getAttackRealMemberNum() > POSITION_MAX)
		{
			//进入失败， 满人
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
		
		//我的信息广播给房间里的人, 但不发给我
		broadEnterMemberMsgToOtherMemberList(newCampaign, newMember);

		//房间里玩家信息发送给我
		sendMemberListToNewMember(newCampaign->getAttackHostList(), newMember, newCampaign->getCampaignId(), FORCE_ATTACK, true);
		sendMemberListToNewMember(newCampaign->getAttackMemberList(), newMember, newCampaign->getCampaignId(), FORCE_ATTACK);
	}

	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::onRecvCampaignEnterDefenseFromFrontServer(NetIdType frontServerNetId, PT_CAMPAIGN_F2T_ENTER_DEFENSE_DATA* data )
	{
		SCampaign* curCampaign = SCampaignManager::getInstance().getBattleCampaign(data->campaignId);
		if (NULL ==curCampaign)
		{
			//进入失败
			sendCampaignErrorToFrontServer(frontServerNetId, CAMPAIGN_ENTER_FAIL, data->clientNetId, data->accountId);
			return ;
		}

		if (curCampaign->getDefenseRealMemberNum() > POSITION_MAX)
		{
			//进入失败， 满人
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
		
		//send CampaignInfo房间信息， 以便客户端创建
		sendCampaignInfoToClient(curCampaign, newMember);

		sendMemberListToNewMember(curCampaign->getAttackHostList(), newMember, curCampaign->getCampaignId(), FORCE_ATTACK, true);
		sendMemberListToNewMember(curCampaign->getAttackMemberList(), newMember, curCampaign->getCampaignId(), FORCE_ATTACK);
		sendMemberListToNewMember(curCampaign->getDefenseMemberList(), newMember, curCampaign->getCampaignId(), FORCE_DEFENSE);


		//修改玩家的战斗内存信息
		sendCampaignEnterDefenseToFrontServer(curCampaign, newMember);

		Bool isBattleLeader = false;
		Int memberNum = curCampaign->getDefenseRealMemberNum();
		if (0 == memberNum)
		{
			isBattleLeader = true;
		}
		//跳转地图
		sendCampaignSingleMemberJumpRegionToFrontServer(newMember, curCampaign->getCampaignTargetRegionId(), curCampaign->getCampaignTargetInstance(), curCampaign->getDefenseRealMemberNum(), JUMP_DEFENSE, isBattleLeader, curCampaign->getPrepareTimeSecond());

		//开始创建军营
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
		//绑定战斗的地图副本
		SCampaign* myCampaign = SCampaignManager::getInstance().popPrepareCampaign(campaignId);
		DYNAMIC_ASSERT(NULL != myCampaign);
		myCampaign->setCampaignTargetInstanceId(instanceUid);
		
		std::map<POSITION, ClanArmy*>* hostList = myCampaign->getAttackHostList();
		std::map<POSITION, ClanArmy*>* memberList = myCampaign->getAttackMemberList();
		DYNAMIC_ASSERT(hostList->size() == 1);		//必须是一个主人

		//通知服务器内所以的客户端， 此战斗开始
		myCampaign->setPrepareTimeSecond(myCampaign->getTimeListInfo()->time3);
		sendStartNewCampaignToClient(myCampaign);

		//攻击方的玩家 跳入到 战斗副本
		sendCampaignMemberJumpRegionToFrontServer(hostList, targetRegionId, instanceUid, JUMP_ATTACK, myCampaign->getPrepareTimeSecond());
		sendCampaignMemberJumpRegionToFrontServer(memberList, targetRegionId, instanceUid, JUMP_ATTACK, myCampaign->getPrepareTimeSecond(), 1);
		
		//从准备战斗列表中放入已战斗列表中
		SCampaignManager::getInstance().addCampaignStart(myCampaign, myCampaign->getTimeListInfo()->time2);	//秒数

		//邀请防守方参加战斗
		sendInviteDefenseCampaignMemberToMapServer(myCampaign->getCampaignTargetRegionId(), instanceUid, myCampaign->getCampaignId());

		//开始创建 军营【攻击方】
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
			// 设置标签
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_T2C_ERROR;

			// 转换逻辑包
			PT_CAMPAIGN_T2C_ERROR_DATA* sendData = (PT_CAMPAIGN_T2C_ERROR_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->error = error;

				// 发送数据.
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
			// 设置标签
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_T2C_DESTROY;

			// 转换逻辑包
			PT_CAMPAIGN_T2C_DESTROY_DATA* sendData = (PT_CAMPAIGN_T2C_DESTROY_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->campaignId = campaignId;

				// 发送数据.
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

		// 设置标签
		packet->channel = GNPC_CAMPAIGN;
		packet->type    = PT_CAMPAIGN_T2C_CAMPAIGN_LIST_BEGIN;

		// 转换逻辑包
		PT_CAMPAIGN_T2C_CAMPAIGN_LIST_BEGIN_DATA* sendData = (PT_CAMPAIGN_T2C_CAMPAIGN_LIST_BEGIN_DATA*)(packet->data);
		if ( sendData )
		{
			// 填充逻辑包

			// 发送数据.
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

		// 设置标签
		packet->channel = GNPC_CAMPAIGN;
		packet->type    = PT_CAMPAIGN_T2C_CAMPAIGN_LIST_END;

		// 转换逻辑包
		PT_CAMPAIGN_T2C_CAMPAIGN_LIST_END_DATA* sendData = (PT_CAMPAIGN_T2C_CAMPAIGN_LIST_END_DATA*)(packet->data);
		if ( sendData )
		{
			// 填充逻辑包

			// 发送数据.
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

		// 当前发送数据头大小
		I32 sendDataHeadSize    = 0;
		// 当前发送数据大小
		I32 sendDataSize        = 0;
		// 准备发送数据大小
		I32 prepareSendDataSize = 0;

		// 遍历角色队列
		std::map<ClanIdType, SCampaign*>::iterator iter = campaignList->begin();
		while( campaignList->end() != iter )
		{
			//--------------------------------------------------------------------------

			if ( dataPtr.mDataPtr.isNull() == false )
			{
				// 递增一个角色数据大小到发送数据缓存大小
				prepareSendDataSize = sendDataSize + PT_CAMPAIGN_T2C_CAMPAIGN_LIST_DATA_INFO::netAddCampainInfoSize;

				// 如果大于缓存最大大小则发送
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
			// 设置标签
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_T2C_CAMPAIGN_INFO;

			// 转换逻辑包
			PT_CAMPAIGN_T2C_CAMPAIGN_INFO_DATA* sendData = (PT_CAMPAIGN_T2C_CAMPAIGN_INFO_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
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
				// 发送数据.
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
        
		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();

		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_T2F_ENTER_ATTACK;

			// 转换逻辑包
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

				//FrontServer 填充
				sendData->newMember.level				= 0;
				sendData->newMember.hp					= 0;
				sendData->newMember.mp					= 0;

				Int sendDataSize = GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2F_ENTER_ATTACK_INFO::dataSize;

				//发给房主
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

				// 发给普通玩家
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
				//发给普通玩家 End
			}
		}
	}

	void SCampaignNetPacketProcesser::sendLeaveInCampaignToFrontServer(SCampaign* campaign, ClanArmy* newClanInfo)
	{
		GameNetSendDataBufferPtr dataPtr ;
		CenterServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();

		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_T2F_LEAVE_IN_CAMPAIGN;

			// 转换逻辑包
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
			// 设置标签
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_T2C_READY_MYSELF;

			// 转换逻辑包
			PT_CAMPAIGN_T2C_READY_MYSELF_DATA* sendData = (PT_CAMPAIGN_T2C_READY_MYSELF_DATA*)(packet->data);
			if ( sendData )
			{
				//1. 确认   2.取消

				sendData->campaignId		= campaign->getCampaignId();
				sendData->myClanId			= myClanInfo->clanID;
				sendData->myPosition		= myClanInfo->position;
				sendData->playerCharacterId	= myClanInfo->playerCharacterInfo.playerCharacterId;
				sendData->readyState		= myClanInfo->readyState;

				Int sendDataSize = GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2C_READY_MYSELF_INFO::dataSize;


				//发给房主
				{
					std::map<POSITION, ClanArmy*>* memberList =  campaign->getAttackHostList();
					_broadCampaignMsgToMemberListViaClient(dataPtr, 
						GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2C_READY_MYSELF_INFO::dataSize,
													memberList);
				}

				// 发给普通玩家
				{
					std::map<POSITION, ClanArmy*>* memberList =  campaign->getAttackMemberList();
					_broadCampaignMsgToMemberListViaClient(dataPtr, 
						GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2C_READY_MYSELF_INFO::dataSize,
						memberList);
				}
				//发给普通玩家 End
			}
		}
	}

	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::sendMemberListToNewMember(std::map<POSITION, ClanArmy*>* memberList, ClanArmy* newClanInfo, CampaignIdType campaignId, FORCE force, Bool isHost/* = false*/)
	{
		GameNetSendDataBufferPtr dataPtr ;

		// 转换成标准包格式
		GameNetPacketData* packet = NULL;
		PT_CAMPAIGN_T2F_MEMBER_LIST_DATA* sendData = NULL;
		// 当前发送数据头大小
		I32 sendDataHeadSize    = 0;
		// 当前发送数据大小
		I32 sendDataSize        = 0;
		// 准备发送数据大小
		I32 prepareSendDataSize = 0;

		// 遍历角色队列
		std::map<POSITION, ClanArmy*>::iterator iter = memberList->begin();
		while( memberList->end() != iter && false == iter->second->empty() )
		{
			//--------------------------------------------------------------------------
			
			if ( dataPtr.isNull() == false )
			{
				// 递增一个角色数据大小到发送数据缓存大小
				prepareSendDataSize = sendDataSize + PT_CAMPAIGN_T2F_MEMBER_LIST_DATA_INFO::netAddMemberInfoSize;

				// 如果大于缓存最大大小则发送
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

				// 转换成标准包格式
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

			//填充
			tempSend->accountId			= tempClan->accountId;
			tempSend->clanId			= tempClan->clanID;
			tempSend->playerCharacterId	= tempClan->playerCharacterInfo.playerCharacterId;
			tempSend->charArtIcon		= tempClan->playerCharacterInfo.charArtIcon;
			tempSend->position			= tempClan->position;
			tempSend->readyState		= tempClan->readyState;
			tempSend->isHost			= isHost;

			//FrontServer 填充
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
		// 获得一个发送【客户端】缓存
		GameNetSendDataBufferPtr dataPtr;
        CenterServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_T2F_START;

			// 转换逻辑包
			PT_CAMPAIGN_T2F_START_DATA* sendData = (PT_CAMPAIGN_T2F_START_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->accountId			= hostArmy->accountId;
				sendData->targetRegionId	= campaign->getCampaignTargetRegionId();
				sendData->campaignId		= campaign->getCampaignId();


				// 发送数据
				CenterServerMain::getInstance().getServerLauncher()->sendServer(dataPtr, 
					GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2F_START_INFO::dataSize, 
					frontserverNetId);
			}
		}
	}

	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::sendStartNewCampaignToClient(SCampaign* campaign)
	{
		//广播给所有的客户端
		ClientNetTranspondSendDataBufferPtr dataPtr;
        ClientNetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr );
		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_T2C_START_NEW_CAMPAIGN;

			// 转换逻辑包
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
		// 获得一个发送【客户端】缓存
		GameNetSendDataBufferPtr dataPtr;
        CenterServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_T2F_CHANGE_CAMP_CONTROL;

			// 转换逻辑包
			PT_CAMPAIGN_T2F_CHANGE_CAMP_CONTROL_DATA* sendData = (PT_CAMPAIGN_T2F_CHANGE_CAMP_CONTROL_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->targetRegionId			= campaign->getCampaignTargetRegionId();
				sendData->targetInstanceUId			= campaign->getCampaignTargetInstance();
				sendData->ownerAccountId			= campaign->getAttackHostClanArmyInfo()->accountId;
				sendData->campId					= campId;
				sendData->targetControlerAccountId	= targetControler;


				// 发送数据
				CenterServerMain::getInstance().getServerLauncher()->sendServer(dataPtr, 
					GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2F_CHANGE_CAMP_CONTROL_INFO::dataSize, 
					frontserverNetId);
			}
		}
	}

	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::sendCampaignChangeCampOwnerToFrontServer(NetIdType frontserverNetId,SCampaign* campaign, AccountIdType targetAccountId)
	{
		// 获得一个发送【客户端】缓存
		GameNetSendDataBufferPtr dataPtr ;
        CenterServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if (NULL == packet )
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// 设置标签
		packet->channel = GNPC_CAMPAIGN;
		packet->type    = PT_CAMPAIGN_T2F_CHANGE_CAMP_OWNER;

		// 转换逻辑包
		PT_CAMPAIGN_T2F_CHANGE_CAMP_OWNER_DATA* sendData = (PT_CAMPAIGN_T2F_CHANGE_CAMP_OWNER_DATA*)(packet->data);
		if ( sendData )
		{
			// 填充逻辑包
			sendData->targetRegionId		= campaign->getCampaignTargetRegionId();
			sendData->targetInstanceUId		= campaign->getCampaignTargetInstance();
			sendData->accountId				= targetAccountId;

			// 发送数据
			CenterServerMain::getInstance().getServerLauncher()->sendServer(dataPtr, 
				GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2F_CHANGE_CAMP_OWNER_INFO::dataSize, 
				frontserverNetId);
		}
		
	}

	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::sendCampaignEnterDefenseToFrontServer(SCampaign* campaign, const ClanArmy* myArmy)
	{
		// 获得一个发送【客户端】缓存
		GameNetSendDataBufferPtr dataPtr;
        CenterServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_T2F_ENTER_DEFENSE;

			// 转换逻辑包
			PT_CAMPAIGN_T2F_ENTER_DEFENSE_DATA* sendData = (PT_CAMPAIGN_T2F_ENTER_DEFENSE_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
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
				//广播给所有房间里的人
				{
					//房主
					std::map<POSITION, ClanArmy*>* host = campaign->getAttackHostList();
					for (std::map<POSITION, ClanArmy*>::iterator iter = host->begin(); iter != host->end(); ++iter)
					{
						if (iter->second->empty() == true)
						{
							continue;
						}

						// 发送数据
						sendData->toAccountId	= iter->second->accountId;
						CenterServerMain::getInstance().getServerLauncher()->sendServer(dataPtr, dataSize, 
							iter->second->frontServerNetId);

						 CenterServerMain::getInstance().getServerLauncher()->cloneSendDataBuffer( dataPtr, dataPtr, UInt(dataPtr->getLogicDataSendSize()) );
						packet = (GameNetPacketData*) dataPtr->getLogicData();
						sendData = (PT_CAMPAIGN_T2F_ENTER_DEFENSE_DATA*)(packet->data);
					}
				}

				{
					//攻击方队员
					std::map<POSITION, ClanArmy*>* host = campaign->getAttackMemberList();
					for (std::map<POSITION, ClanArmy*>::iterator iter = host->begin(); iter != host->end(); ++iter)
					{
						if (iter->second->empty() == true)
						{
							continue;
						}
						// 发送数据
						sendData->toAccountId	= iter->second->accountId;
						CenterServerMain::getInstance().getServerLauncher()->sendServer(dataPtr,
							dataSize, iter->second->frontServerNetId);

						CenterServerMain::getInstance().getServerLauncher()->cloneSendDataBuffer( dataPtr, dataPtr, UInt(dataPtr->getLogicDataSendSize()) );
						packet = (GameNetPacketData*) dataPtr->getLogicData();
						sendData = (PT_CAMPAIGN_T2F_ENTER_DEFENSE_DATA*)(packet->data);
					}
				}

				{
					//防守方队员
					std::map<POSITION, ClanArmy*>* host = campaign->getDefenseMemberList();
					for (std::map<POSITION, ClanArmy*>::iterator iter = host->begin(); iter != host->end(); ++iter)
					{
						if (iter->second->empty() == true)
						{
							continue;
						}

						//if (myArmy->accountId == iter->second->accountId)
						//{
						//	//不给我自己发
						//	continue;
						//}

						// 发送数据
						sendData->toAccountId	= iter->second->accountId;
						// 发送数据
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
		// 获得一个发送【客户端】缓存
		GameNetSendDataBufferPtr dataPtr;
        CenterServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( NULL == packet )
		{
			DYNAMIC_ASSERT(0);
			return;
		}
		// 设置标签
		packet->channel = GNPC_CAMPAIGN;
		packet->type    = PT_CAMPAIGN_T2F_CREATE_CAMP_BY_CONTROLER;

		// 转换逻辑包
		PT_CAMPAIGN_T2F_CREATE_CAMP_BY_CONTROLER_DATA* sendData = (PT_CAMPAIGN_T2F_CREATE_CAMP_BY_CONTROLER_DATA*)(packet->data);
		if ( NULL == sendData )
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// 填充逻辑包
		sendData->campaignId				= campaign->getCampaignId();
		sendData->targetRegionId			= campaign->getCampaignTargetRegionId();
		sendData->targetInstanceUId			= campaign->getCampaignTargetInstance();
		sendData->targetControlerAccountId	= campControlerId;
		sendData->campForce					= campForce;
		sendData->campNum					= campSize;
		sendData->campIndexStart			= indexStart;

		// 发送数据
		CenterServerMain::getInstance().getServerLauncher()->sendServer(dataPtr, 
			GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2F_CREATE_CAMP_BY_CONTROLER_INFO::dataSize, 
			frontserverNetId);
	}

	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::sendCampaignTroopControllerList(const SCampaign* myCampaign, const AccountIdType campOwnerAccountId, const CampIdType campId, std::vector<NetTroopControllerInfo>* memberList, ClanArmy* myClanArmy)
	{
		DYNAMIC_ASSERT(NULL != myCampaign && campOwnerAccountId > 0 && campId > 0);

		GameNetSendDataBufferPtr dataPtr ;

		// 转换成标准包格式
		GameNetPacketData* packet = NULL;
		//packet->channel = GNPC_CAMPAIGN;
		//packet->type    = PT_CAMPAIGN_T2F_TROOP_CONTROLLER_LIST;

		PT_CAMPAIGN_T2F_TROOP_CONTROLLER_LIST_DATA* sendData = NULL;

		// 当前发送数据头大小
		I32 sendDataHeadSize    = 0;
		// 当前发送数据大小
		I32 sendDataSize        = 0;
		// 准备发送数据大小
		I32 prepareSendDataSize = 0;

		// 遍历角色队列
		std::vector<NetTroopControllerInfo>::iterator iter = memberList->begin();
		while( memberList->end() != iter)
		{
			//--------------------------------------------------------------------------
			
			if ( dataPtr.isNull() == false )
			{
				// 递增一个角色数据大小到发送数据缓存大小
				prepareSendDataSize = sendDataSize + PT_CAMPAIGN_T2F_TROOP_CONTROLLER_LIST_DATA_INFO::netAddMemberInfoSize;

				// 如果大于缓存最大大小则发送
				if ( prepareSendDataSize >= dataPtr->getLogicDataMaxSize() )
				{
					// 发送数据
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

				// 转换成标准包格式
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

				// 当前发送数据头大小
				sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2F_TROOP_CONTROLLER_LIST_DATA_INFO::headSize;
				// 当前发送数据大小
				sendDataSize        = sendDataHeadSize;
				// 准备发送数据大小
				prepareSendDataSize = sendDataHeadSize;
			}

			//--------------------------------------------------------------------------

			//开始 填充
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
		// 获得一个发送【客户端】缓存
		GameNetSendDataBufferPtr dataPtr;
        CenterServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( NULL == packet )
		{
			DYNAMIC_ASSERT(0);
			return;
		}
		// 设置标签
		packet->channel = GNPC_CAMPAIGN;
		packet->type    = PT_CAMPAIGN_T2F_END;

		// 转换逻辑包
		PT_CAMPAIGN_T2F_END_DATA* sendData = (PT_CAMPAIGN_T2F_END_DATA*)(packet->data);
		if ( NULL == sendData )
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// 填充逻辑包
		sendData->targetRegionId	= campaign->getCampaignTargetRegionId();
		sendData->targetInstanceUId = campaign->getCampaignTargetInstance();
		sendData->campaignId		= campaign->getCampaignId();
		sendData->fromRegionId		= campaign->getCampaignTargetRegionId();		//暂时发这个
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
		// 获得一个发送【客户端】缓存
		GameNetSendDataBufferPtr dataPtr;
        CenterServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_T2F_START_JUMP_REGION;

			// 转换逻辑包
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
				// 发送数据
				CenterServerMain::getInstance().getServerLauncher()->sendServer(dataPtr, 
					GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2F_START_JUMP_REGION_INFO::dataSize, 
					myClan->frontServerNetId);
			}
		}
	}

	//--------------------------------------------------------------------------
	void SCampaignNetPacketProcesser::sendInviteDefenseCampaignMemberToMapServer(RegionIdType regionId, InstanceUIdType instanceUid, CampaignIdType campaignId)
	{
		// 获得一个发送【客户端】缓存
		GameNetSendDataBufferPtr dataPtr;
        CenterServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_T2M_INVITE_DEFENSE_REGION;

			// 转换逻辑包
			PT_CAMPAIGN_T2M_INVITE_DEFENSE_REGION_DATA* sendData = (PT_CAMPAIGN_T2M_INVITE_DEFENSE_REGION_DATA*)(packet->data);
			if ( sendData )
			{
				sendData->toRegionId		= regionId;
				sendData->toInstanceId		= instanceUid;
				sendData->campaignId		= campaignId;

				// 发送数据
				ServerManager::getInstance().boardcastNetPacketToMapServers(dataPtr, 
					GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2M_INVITE_DEFENSE_REGION_INFO::dataSize);
			}
		}
	}

	//--------------------------------------------------------------------------


}