
/******************************************************************************/
#include "stdafx.h"
#include "CampaignNetPacketProcesser.h"
#include "ClientNetApplyManager.h"
#include "CPlayer.h"
#include "CCampaignManagerNew.h"
#include "CClientNew.h"
#include "MainFrm.h"
#include "MGRobot.h"
#include "CampaignPage.h"
/******************************************************************************/

namespace MG
{										   
	//--------------------------------------------------------------------------
	Bool CampaignNetPacketProcesser::processFrontServerPacket(CClient* client,NetEventRecv* packet)
	{
		if ( packet->getChannel() == GNPC_CAMPAIGN )
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_CAMPAIGN_T2C_ERROR:
				onRecvCampaignError( client, (PT_CAMPAIGN_T2C_ERROR_DATA*)data->data );
				break;
			case PT_CAMPAIGN_T2C_CREATE:
				onRecvCampaignCreate( client, (PT_CAMPAIGN_T2C_CREATE_DATA*)data->data );
				break;
			case PT_CAMPAIGN_F2C_ENTER_ATTACK:
				onRecvCampaignEnter( client, (PT_CAMPAIGN_F2C_ENTER_ATTACK_DATA*)data->data );
				break;
			case PT_CAMPAIGN_F2C_MEMBER_LIST:
				onRecvCampaignMemberList( client, (PT_CAMPAIGN_F2C_MEMBER_LIST_DATA*)data->data );
				break;
			case PT_CAMPAIGN_M2C_INVITE_DEFENSE_REGION:
				onRecvCampaignInviteDefense( client, (PT_CAMPAIGN_M2C_INVITE_DEFENSE_REGION_DATA*)data->data );
				break;
			case PT_CAMPAIGN_M2C_END:
				onRecvCampaignEnd( client, (PT_CAMPAIGN_M2C_END_DATA*)data->data );
				break;
			case PT_CAMPAIGN_T2C_READY_MYSELF:
				onRecvCampaignReadyMySelf( client, (PT_CAMPAIGN_T2C_READY_MYSELF_DATA*)data->data );
				break;
			case PT_CAMPAIGN_T2C_LEAVE:
				onRecvCampaignLeave( client, (PT_CAMPAIGN_T2C_LEAVE_DATA*)data->data );
				break;
			case PT_CAMPAIGN_T2C_DESTROY:
				onRecvCampaignDestroy( client, (PT_CAMPAIGN_T2C_DESTROY_DATA*)data->data );
				break;
			case PT_CAMPAIGN_T2C_START_NEW_CAMPAIGN:
				onRecvCampaignStartNewCampaign( client, (PT_CAMPAIGN_T2C_START_NEW_CAMPAIGN_DATA*)data->data );
				break;
			case PT_CAMPAIGN_F2C_ENTER_DEFENSE:
				break;
			case PT_CAMPAIGN_T2C_CAMPAIGN_LIST_BEGIN:
				onRecvCampaignListBegin( client, (PT_CAMPAIGN_T2C_CAMPAIGN_LIST_BEGIN_DATA*)data->data );
				break;
			case PT_CAMPAIGN_T2C_CAMPAIGN_LIST:
				onRecvCampaignList( client, (PT_CAMPAIGN_T2C_CAMPAIGN_LIST_DATA*)data->data );
				break;
			case PT_CAMPAIGN_T2C_CAMPAIGN_LIST_END:
				onRecvCampaignListEnd( client, (PT_CAMPAIGN_T2C_CAMPAIGN_LIST_END_DATA*)data->data );
				(CButton*)((CMainFrame*)theApp.m_pMainWnd)->GetCampaignPage()->GetDlgItem(IDC_BTN_CREATE_CAMPAGIN)->EnableWindow(TRUE);
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
	void CampaignNetPacketProcesser::onRecvCampaignListBegin( CClient* client, PT_CAMPAIGN_T2C_CAMPAIGN_LIST_BEGIN_DATA* data )
	{
		
		/*CCampaignManager*  campaignMgr = client->getCampaignManger();
		if (campaignMgr)
		{
			campaignMgr->clearCampaignsInServer();
		}
		else
		{
			DYNAMIC_ASSERT(false);
		}*/
	}
	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignList( CClient* client, PT_CAMPAIGN_T2C_CAMPAIGN_LIST_DATA* data )
	{
		// 当收到战场列表 更新战场列表信息
		// 将开始的战场加入战场管理器

		/*CCampaignManager*  campaignMgr = client->getCampaignManger();
		if (campaignMgr)
		{
			campaignMgr->clearCCCRegions();
			campaignMgr->clearNCCRegions();
			std::map<RegionIdType,CampaignIdType>*  campaigns = campaignMgr->getCampaignsInServer();

			if (campaigns)
			{	
				if (!campaigns->empty())
				{
					DYNAMIC_ASSERT(false);
				}
				else
				{
					for (Int i = 0; i < data->addCampainNum; ++i)
					{
						campaigns[campInfo->targetRegionId] = data->
					}
				}
			}
			else
			{
				DYNAMIC_ASSERT(false);
			}
		}
		else
		{
			DYNAMIC_ASSERT(false);
		}*/
	}
	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignListEnd(CClient* client, PT_CAMPAIGN_T2C_CAMPAIGN_LIST_END_DATA* data )
	{
		/////////////////////////////////////////////////////////
		/*CCampaignManager*  campaignMgr = client->getCampaignManger();
		if (!campaignMgr)
		{
			DYNAMIC_ASSERT(false);
			return;
		}
		else
		{
			campaignMgr->resetRegions();
			campaignMgr->assignmentCampaign();
			campaignMgr->createCampaignRoomListToServer();
		}*/

	}
	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignCreate( CClient* client, PT_CAMPAIGN_T2C_CREATE_DATA* data )
	{
		CCampaignManager* campaignMgr = client->getCampaignManger();
		if (!campaignMgr)
		{
			return;
		}
		CCampaign* campaign = client->getCampaign();
		if (!campaign)
		{
			return;
		}
		if (client->getPlayerObj()->getActiveClan()->getClanID() == data->campaignInfo.creatorClanId)
			// 如果战场受管理 并且当前用户是房主 需要设置战场状态
		{
			campaign->setState(CCAMPAIGN_STATE_APPLIED);
			campaign->setCampaignName(data->campaignInfo.campaignName);
			campaign->setOwned(true);
			campaign->setCampaignId(data->campaignInfo.campaignId);
			campaignMgr->addOwnedCampaignById(data->campaignInfo.campaignId,campaign);
			campaign->getArmyInfo(client)->state = CCAMPAIGN_ARMY_STATE_ENTER;
			campaign->enterCampaign();
		}
		
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignEnter( CClient* client, PT_CAMPAIGN_F2C_ENTER_ATTACK_DATA* data )
	{

		// 当接收玩家进入房间 
		// 由房主来处理信息
		CCampaignManager* campaignMgr = client->getCampaignManger();
		if (!campaignMgr)
		{
			return;
		}
		CCampaign* campaign = campaignMgr->getOwnedCampaignById(data->campaignId);
		if (!campaign)
		{
			return;
		}
		if (campaign->getHost() != client)
		{
			return;
		}
		campaign->getArmyInfo(data->newMember.playerCharacterId)->state = CCAMPAIGN_ARMY_STATE_ENTER;
		if (campaign->checkCompleteEnter())
		{
			campaign->ready();
		}
		
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignMemberList( CClient* client, PT_CAMPAIGN_F2C_MEMBER_LIST_DATA* data )
	{
		
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignInviteDefense( CClient* client, PT_CAMPAIGN_M2C_INVITE_DEFENSE_REGION_DATA* data )
	{
		
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignEnd( CClient* client, PT_CAMPAIGN_M2C_END_DATA* data )
	{
		//// 当战场结束 由房主来处理信息
		//CCampaign* campaign = CCampaignManager::getInstance().getCampaign(data->campaignId);
		//if (!campaign )
		//{
		//	return;
		//}
		//
		//if (campaign->getHost() != client)
		//{
		//	return;
		//}
		//if (!campaign->isOwned())
		//{
		//	CCampaignManager::getInstance().removeCampaign(data->campaignId);	
		//}
		//else
		//{
		//	campaign->setState(CCAMPAIGN_STATE_END);
		//}
		//// 更新攻城副本信息
		//CCampaignManager::getInstance().removeCreateRegion(campaign->getCampaignTargetRegionId(),false);
		// 当接收玩家进入房间 
		// 由房主来处理信息

		CCampaignManager* campaignMgr = client->getCampaignManger();
		if (!campaignMgr)
		{
			return;
		}
		CCampaign* campaign = campaignMgr->removeOwnedCampaignById(data->campaignId);
		if (!campaign)
		{
			return;
		}
		if (campaign->getHost() != client)
		{
			return;
		}
		
		campaign->setState(CCAMPAIGN_STATE_PREASSIGNMENT);
		if (!campaignMgr->isTimeOut() 
			&& campaignMgr->getCtrlState() == CampaignCtrlState_CanStart)
		{
			campaign->netCreateCampaign();
		}
			
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignReadyMySelf( CClient* client, PT_CAMPAIGN_T2C_READY_MYSELF_DATA* data )
	{
		//// 当接收玩家准备 只需要一个人处理信息
		CCampaignManager* campaignMgr = client->getCampaignManger();
		if (!campaignMgr)
		{
			return;
		}
		CCampaign* campaign = campaignMgr->getOwnedCampaignById(data->campaignId);
		if (!campaign)
		{
			return;
		}
		if (campaign->getHost() != client)
		{
			return;
		}
		campaign->getArmyInfo(data->playerCharacterId)->state = data->readyState ? CCAMPAIGN_ARMY_STATE_CONFIRM : CCAMPAIGN_ARMY_STATE_CANCEL;
		
		if (campaign->checkCompleteConfirm())
		{
			campaign->startBattle();
		}
		

	}

#if 0
	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignStandByList( CClient* client, PT_CAMPAIGN_SC_STANDBY_LIST_DATA* data )
	{
		
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignWaitingList( CClient* client, PT_CAMPAIGN_SC_WAITING_LIST_DATA* data )
	{
		//FUNDETECTION(__MG_FUNC__);
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignJoin( CClient* client, PT_CAMPAIGN_SC_JOIN_STANDBY_DATA* data )
	{
		//FUNDETECTION(__MG_FUNC__);
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignJoinMySelf( CClient* client, PT_CAMPAIGN_SC_JOIN_STANDBY_MYSELF_DATA* data )
	{

	}
#endif
#if 0
	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignEndBattle( CClient* client, PT_CAMPAIGN_SC_END_BATTLE_DATA* data )
	{

	}
#endif
	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignLeave( CClient* client, PT_CAMPAIGN_T2C_LEAVE_DATA* data )
	{
		DYNAMIC_ASSERT(false);
		/*CCampaign* campaign = CCampaignManager::getInstance().getCampaign(data->campaignId);
		if (!campaign)
		{
			return;
		}
		CCampaignManager::getInstance().removeCreateRegion(campaign->getCampaignTargetRegionId(),false);
		CCampaignManager::getInstance().removeCampaign(data->campaignId);*/
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignDestroy( CClient* client, PT_CAMPAIGN_T2C_DESTROY_DATA* data )
	{

		CCampaignManager* campaignMgr = client->getCampaignManger();
		if (!campaignMgr)
		{
			return;
		}
		CCampaign* campaign = campaignMgr->removeOwnedCampaignById(data->campaignId);
		if (!campaign)
		{
			return;
		}
		if (campaign->getHost() != client)
		{
			return;
		}
		campaign->setState(CCAMPAIGN_STATE_PREASSIGNMENT);


	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignStartNewCampaign( CClient* client, PT_CAMPAIGN_T2C_START_NEW_CAMPAIGN_DATA* data )
	{
		CCampaignManager* campaignMgr = client->getCampaignManger();
		if (!campaignMgr)
		{
			return;
		}
		CCampaign* campaign = campaignMgr->getOwnedCampaignById(data->campaignId);
		if (!campaign)
		{
			return;
		}
		if (campaign->getHost() != client)
		{
			return;
		}
		campaign->setState(CCAMPAIGN_STATE_START);
		campaign->denfenseEnter();

	}

#if 0
	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignKick( CClient* client, PT_CAMPAIGN_SC_KICK_CLAN_DATA* data )
	{

	}
#endif

#if 0
	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignJoinWaiting( CClient* client, PT_CAMPAIGN_SC_JOIN_WATING_DATA* data )
	{
		//FUNDETECTION(__MG_FUNC__);
	}
#endif

#if 0
	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignArmyList( CClient* client, PT_CAMPAIGN_SC_ARMYLIST_DATA* data )
	{
		//FUNDETECTION(__MG_FUNC__);
	}
#endif
#if 0
	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignReady( CClient* client, PT_CAMPAIGN_SC_READY_DATA* data )
	{
		//FUNDETECTION(__MG_FUNC__);
	}
#endif
	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::onRecvCampaignError( CClient* client, PT_CAMPAIGN_T2C_ERROR_DATA* data )
	{
		// 创建战场失败需要重新 设置战场数据
		/*if (data->error == CREATE_FAIL)
		{
			CCampaign* camp = client->getCampaign();
			if (camp && camp->getHost() == client)
			{
				camp->setState(CCAMPAIGN_STATE_APPLIEDERR);
				CCampaignManager::getInstance().init();
			}
		}*/
		
		/*CCampaignManager* campaignMgr = client->getCampaignManger();
		if (!campaignMgr)
		{
			return;
		}
		CCampaign* campaign = campaignMgr->getOwnedCampaignById();
		if (!campaign)
		{
			return;
		}
		if (campaign->getHost() != client)
		{
			return;
		}
		switch (data->error)
		{
		case CAMPAIGN_START_FAIL:
			campaignMgr->getCampaignListFromServer();
			break;
		case CREATE_FAIL:
			campaignMgr->getCampaignListFromServer();
			break;
		}*/
		DYNAMIC_ASSERT_LOG(false,"战场错误");
	}


	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::sendCampaignCreate(I32 frontServerId,const U64 creatorClanId, const U64 targetRegionId, const Char16* campaignName)
	{

        ///////////////////////////////////////////////////////////////////////////

        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );


        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_CAMPAIGN;
            packet->type    = PT_CAMPAIGN_C2F_CREATE;

            // 转换逻辑包
            PT_CAMPAIGN_C2F_CREATE_DATA* sendData = (PT_CAMPAIGN_C2F_CREATE_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                sendData->creatorClanId	=creatorClanId;
                sendData->targetRegionId = targetRegionId;
                WStrnCpyS(sendData->campaignName, campaignName, MAX_CAMPAIGN_NAME);

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket(frontServerId, dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_CAMPAIGN_C2F_CREATE_INFO::dataSize );
            }
        }

        ///////////////////////////////////////////////////////////////////////////
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::sendCampaignEnter(I32 frontServerId,const ClanIdType myClanId, const CampaignIdType campaignId)
	{
        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_CAMPAIGN;
            packet->type    = PT_CAMPAIGN_C2F_ENTER_ATTACK;

            // 转换逻辑包
            PT_CAMPAIGN_C2F_ENTER_ATTACK_DATA* sendData = (PT_CAMPAIGN_C2F_ENTER_ATTACK_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                sendData->myClanId	 = myClanId;
                sendData->campaignId = campaignId;

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket(frontServerId, dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_CAMPAIGN_C2F_ENTER_ATTACK_INFO::dataSize );
            }
        }
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::sendCampaignJoinDefense(I32 frontServerId,const RegionIdType targetRegionId, const CampaignIdType campaignId, const ClanIdType myClanId)
	{
		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_C2F_ENTER_DEFENSE;

			// 转换逻辑包
			PT_CAMPAIGN_C2F_ENTER_DEFENSE_DATA* sendData = (PT_CAMPAIGN_C2F_ENTER_DEFENSE_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->myClanId	 = myClanId;
				sendData->campaignId = campaignId;

				// 发送数据
				ClientNetApplyManager::getInstance().sendFrontServerPacket(frontServerId, dataPtr , 
					GameNetPacketData_INFO::headSize + PT_CAMPAIGN_C2F_ENTER_DEFENSE_INFO::dataSize );
			}
		}
	}

	//--------------------------------------------------------------------------
	/*void CampaignNetPacketProcesser::sendCampaignJoinMySelf(U64 regionId, U64 campaignId, U64 joinClanId, Byte force, Byte position)
	{
        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_CAMPAIGN;
            packet->type    = PT_CAMPAIGN_C2F_JOIN_STANDBY_MYSELF;

            // 转换逻辑包
            PT_CAMPAIGN_C2F_JOIN_STANDBY_MYSELF_DATA* sendData = (PT_CAMPAIGN_C2F_JOIN_STANDBY_MYSELF_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                sendData->regionId	= regionId;
                sendData->campaignId = campaignId;
                sendData->joinClanId = joinClanId;
                sendData->force		= force;
                sendData->position	= position;

                // 发送数据
				//ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
				//	GameNetPacketData_INFO::headSize + PT_CAMPAIGN_C2F_JOIN_STANDBY_MYSELF_DATA_INFO::dataSize );
            }
        }
		
	}*/



	//--------------------------------------------------------------------------
	/*void CampaignNetPacketProcesser::sendWaitingJoin(U64 regionId, U64 campaignId, U64 myClanId, U64 targetClanId)
	{
        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_CAMPAIGN;
            packet->type    = PT_CAMPAIGN_C2F_JOIN_WATING;

            // 转换逻辑包
            PT_CAMPAIGN_C2F_JOIN_WATING_DATA* sendData = (PT_CAMPAIGN_C2F_JOIN_WATING_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                sendData->regionId	= regionId;
                sendData->campaignId = campaignId;
                sendData->creatorId	= myClanId;
                sendData->joinClanId = targetClanId;

                // 发送数据
                //ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                //    GameNetPacketData_INFO::headSize + PT_CAMPAIGN_C2F_JOIN_WATING_DATA_INFO::dataSize );
            }
        }
		
	}*/


	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::sendCampaignReadyMySelf(I32 frontServerId,CampaignIdType campaignId, ClanIdType myClanId, PlayerCharacterIdType playerCharacterId)
	{
        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_CAMPAIGN;
            packet->type    = PT_CAMPAIGN_C2F_READY_MYSELF;

            // 转换逻辑包
            PT_CAMPAIGN_C2F_READY_MYSELF_DATA* sendData = (PT_CAMPAIGN_C2F_READY_MYSELF_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                sendData->campaignId		= campaignId;
                sendData->myClanId			= myClanId;
                sendData->playerCharacterId	= playerCharacterId;

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket( frontServerId,dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_CAMPAIGN_C2F_READY_MYSELF_INFO::dataSize );
            }
        }
			
    }

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::sendCampaignLeave(I32 frontServerId,CampaignIdType campaignId, ClanIdType clanId)
	{
        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_CAMPAIGN;
            packet->type    = PT_CAMPAIGN_C2F_LEAVE;

            // 转换逻辑包
            PT_CAMPAIGN_C2F_LEAVE_DATA* sendData = (PT_CAMPAIGN_C2F_LEAVE_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                //sendData->regionId	= regionId;
                sendData->campaignId = campaignId;
                sendData->clanId		= clanId;

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket( frontServerId,dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_CAMPAIGN_C2F_LEAVE_INFO::dataSize );
            }
        }
			
    }

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::sendCampaignList(I32 frontServerId)
	{
        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_CAMPAIGN;
            packet->type    = PT_CAMPAIGN_C2F_CAMPAIGN_LIST;

            // 转换逻辑包
            PT_CAMPAIGN_C2F_CAMPAIGN_LIST_DATA* sendData = (PT_CAMPAIGN_C2F_CAMPAIGN_LIST_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                //sendData->targetRegionId	= regionId;

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket( frontServerId,dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_CAMPAIGN_C2F_CAMPAIGN_LIST_INFO::dataSize );
            }
        }	
    }

	//--------------------------------------------------------------------------
	/*void CampaignNetPacketProcesser::sendCampaignKickClan(const U64 regionId, const U64 campaignId, const U64 myClanId, const U64 kickClanId, const Byte force, const Byte position)
	{
        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_CAMPAIGN;
            packet->type    = PT_CAMPAIGN_C2F_KICK_CLAN;

            // 转换逻辑包
            PT_CAMPAIGN_C2F_KICK_CLAN_DATA* sendData = (PT_CAMPAIGN_C2F_KICK_CLAN_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                sendData->regionId	= regionId;
                sendData->campaignId	= campaignId;
                sendData->clanId		= myClanId;
                sendData->kickClanId = kickClanId;
                sendData->force		= force;
                sendData->position	= position;

                // 发送数据
                //ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                //    GameNetPacketData_INFO::headSize + PT_CAMPAIGN_C2F_KICK_CLAN_DATA_INFO::dataSize );
            }
        }
			
    }*/

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::sendCampaignStart(I32 frontServerId,const CampaignIdType campaignId, const ClanIdType starterClanId )
	{
        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_CAMPAIGN;
            packet->type    = PT_CAMPAIGN_C2F_START;

            // 转换逻辑包
            PT_CAMPAIGN_C2F_START_DATA* sendData = (PT_CAMPAIGN_C2F_START_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                //sendData->regionId	= regionId;
                sendData->campaignId = campaignId;
                sendData->starterClanId	= starterClanId;

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket(frontServerId, dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_CAMPAIGN_C2F_START_INFO::dataSize );
            }
        }
		
	}

	//--------------------------------------------------------------------------
	void CampaignNetPacketProcesser::sendCampaignEndManual(I32 frontServerId,CampaignIdType campaignId)
	{
		if (campaignId <= 0)
		{
			return;
		}

		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_CAMPAIGN;
			packet->type    = PT_CAMPAIGN_C2F_END_MANUAL;

			// 转换逻辑包
			PT_CAMPAIGN_C2F_END_MANUAL_DATA* sendData = (PT_CAMPAIGN_C2F_END_MANUAL_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->campaignId = campaignId;

				// 发送数据
				ClientNetApplyManager::getInstance().sendFrontServerPacket( frontServerId,dataPtr , 
					GameNetPacketData_INFO::headSize + PT_CAMPAIGN_C2F_END_MANUAL_INFO::dataSize );
			}
		}
	}
	//--------------------------------------------------------------------------
	/*void CampaignNetPacketProcesser::sendCampaignArmyList(I32 frontServerId,U64 regionId, U64 campaignId, U64 clanId, 
		U64 playerCharacterId, U64 troopId)
	{
        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_CAMPAIGN;
            packet->type    = PT_CAMPAIGN_CS_ARMYLIST;

            // 转换逻辑包
            PT_CAMPAIGN_CS_ARMYLIST_DATA* sendData = (PT_CAMPAIGN_CS_ARMYLIST_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                sendData->regionId	= regionId;
                sendData->campaignId = campaignId;
                sendData->myClanId	= clanId;
                sendData->playCharacterInfo.playerCharacterId = playerCharacterId;
                sendData->troopInfo.troopId = troopId;

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket(frontServerId, dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_CAMPAIGN_CS_ARMYLIST_DATA_INFO::dataSize );
            }
        }
		
	}*/

}
