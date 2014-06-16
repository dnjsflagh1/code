/******************************************************************************/
#include "stdafx.h"
#include "CClientNew.h"
#include "Operate.h"
#include "OperateManager.h"
#include "GameNetPacket.h"
//#include "LoginNetPacket.h"
//#include "PlayerNetPacket.h"
//#include "RegionNetPacket.h"
//#include "ClientManager.h"
#include "ClientManager.h"
#include "CampaignOperate.h"
#include "CampaignNetPacket.h"
#include "CCampaign.h"
#include "CCampaignManager.h"
#include "MGRobot.h"
#include "MainFrm.h"
#include "CampaignPage.h"
#include "PlayerNetPacket.h"
/******************************************************************************/
namespace MG
{
	Bool CampaignOperate::mIsContinueOperate = false;

	//======================================================================
	CampaignOperate::CampaignOperate( OperateManager* mgr ,CClient* client,CClientMessage* msg,OperateType type)
	: BaseOperate(mgr,client,msg,type)
	{
		mIsActiveDisconnect = false;
	}
	//----------------------------------------------------------------------
	Bool CampaignOperate::onEnter()
	{
		if(BaseOperate::onEnter())
		{
			CCampaign* camp = mClient->getCampaign();
			
			mMsg->AddMsg("【战场】：进入");

			if (!mClient->getState().isJoinGame)
			{
				mMsg->AddMsg("【战场】：未进入游戏");
				mIsNormalExit = false;
				mIsFinish = true;
			}
			if (!camp )
			{
				mMsg->AddMsg("【战场】：未初始化");
				mIsNormalExit = false;
				mIsFinish = true;
				return true;
			}
			
			// 只有CCAMPAIGN_STATE_NULL状态才能开始战场
			if (camp->getState() == CCAMPAIGN_STATE_NULL)
			{
				
				if (mClient->getCampaign()->getHost() != mClient)
				{
					//mMsg->AddMsg("【战场】：不是发起人，不创建战场");
				}
				else
				{
					
					mClient->getCampaign()->netCreateCampaign();
					mMsg->AddMsg("【战场】：创建战场 周期数%d",mClient->getCampaign()->getCycleCount());
				}
			}
			else
			{
				mMsg->AddMsg("【战场】：不符合创建条件");
				mIsNormalExit = false;
				mIsFinish = true;
			}


			
		}
		return true;
	}
	//----------------------------------------------------------------------
	void CampaignOperate::onCloseByLoginServer()
	{	

	}
	//----------------------------------------------------------------------
	void CampaignOperate::onCloseByFrontServer()
	{
		mClient->getState().clear();
		{
			mMsg->AddErrorMsg("【战场%I64d】：服务器断开连接",mClient->getCampaign()->getCampaignId());
			mIsFinish = true;
			mIsNormalExit = false;
		}
	}
	//----------------------------------------------------------------------
	void CampaignOperate::onNetEvent( Byte channel,Byte type,void* data )
	{
		if (channel == GNPC_PLAYER)
		{
			switch (type)
			{
			case PT_PLAYER_F2C_PLAYERCHARACTER_INFO_LIST:
				
				break;
			case PT_PLAYER_F2C_JUMP_REGION:
				{
					if (mClient->getCampaign()->isDenfense(mClient))
					{
						mClient->getCampaign()->getArmyInfo(mClient)->jumpOut 
							= !mClient->getCampaign()->getArmyInfo(mClient)->jumpOut;
						mMsg->AddMsg("【战场%I64d】：防守方 跳地图",mClient->getCampaign()->getCampaignId());
						
						if (mClient->getCampaign()->isAllJumpOut())
						{
							mIsFinish = true;
							mIsNormalExit = true;
							((CMainFrame*)theApp.m_pMainWnd)->GetCampaignPage()->uiFlash();

							MG::CCampaignManager::getInstance().init();
						}
						
					}
					if (mClient->getCampaign()->isAttacket(mClient))
					{
						mClient->getCampaign()->getArmyInfo(mClient)->jumpOut 
							= !mClient->getCampaign()->getArmyInfo(mClient)->jumpOut;
						
						mMsg->AddMsg("【战场%I64d】：攻击方 跳地图",mClient->getCampaign()->getCampaignId());

						if (mClient->getCampaign()->isAllJumpOut())
						{
							mIsFinish = true;
							mIsNormalExit = true;
							((CMainFrame*)theApp.m_pMainWnd)->GetCampaignPage()->uiFlash();

							MG::CCampaignManager::getInstance().init();
						}
					}
				}
				break;
			case PT_PLAYER_M2C_REMAIN_PLAYERCHARACTER_INFO_LIST:
				{

				}
				break;
			case PT_PLAYER_F2C_TROOP_INFO_LIST:
				
				break;
			default:
				{
					DYNAMIC_ASSERT(false);
				}
			}
		}
		else if ( channel == GNPC_CAMPAIGN )
		{
			switch (type)
			{
			case PT_CAMPAIGN_T2C_ERROR:
				{
					PT_CAMPAIGN_T2C_ERROR_DATA* tempData = (PT_CAMPAIGN_T2C_ERROR_DATA*)data;
					Str8 tempName;
					MGStrOp::toString(mClient->getPlayerName(),tempName);
					mMsg->AddErrorMsg("【战场】%s 收到错误,错误号 = %d \n",tempName.c_str(),tempData->error);
					
				}
				break;
			case PT_CAMPAIGN_T2C_CAMPAIGN_LIST:
				break;
			case PT_CAMPAIGN_T2C_CREATE:
				{
					 PT_CAMPAIGN_T2C_CREATE_DATA* createData = (PT_CAMPAIGN_T2C_CREATE_DATA*)data;
					 CCampaign* campaign = mClient->getCampaign();
					 if (campaign 
						 && mClient == campaign->getHost()
						 && campaign == CCampaignManager::getInstance().getCampaign(createData->campaignInfo.campaignId))
					 {
						 if (campaign->getState() == CCAMPAIGN_STATE_APPLIED)
						 { 
							 campaign->enterCampaign();	
							 mMsg->AddMsg("【战场%I64d】：房主收到战场创建成功，所有攻击方进入战场房间中 周期数 = %d",mClient->getCampaign()->getCampaignId(),campaign->getCycleCount()); 
							
						 }
						 else
						 {
							 DYNAMIC_ASSERT(false);
						 }
						
					 }

				}

				break;
			case PT_CAMPAIGN_F2C_ENTER_ATTACK:
				{
					PT_CAMPAIGN_F2C_ENTER_ATTACK_DATA* tempData = (PT_CAMPAIGN_F2C_ENTER_ATTACK_DATA*)data;
					CCampaign* campaign = mClient->getCampaign();
					if (campaign 
						&& mClient == campaign->getHost()
						&& campaign == CCampaignManager::getInstance().getCampaign(tempData->campaignId))
					{
						mMsg->AddMsg("【战场%I64d】：攻击方 进入战场房间 次数 = %d",mClient->getCampaign()->getCampaignId(),campaign->getEnterCampaignRoomNum());
						if (mClient->getCampaign()->checkCompleteEnter())
						{
							mMsg->AddMsg("【战场%I64d】：攻击方 准备中 周期数 = %d",mClient->getCampaign()->getCampaignId(),campaign->getCycleCount());
							mClient->getCampaign()->ready();
						}
					}
				}
				break;
			case PT_CAMPAIGN_F2C_MEMBER_LIST:
				break;
			case PT_CAMPAIGN_M2C_INVITE_DEFENSE_REGION:
				break;
			case PT_CAMPAIGN_M2C_END:
				{
					PT_CAMPAIGN_M2C_END_DATA* tempData = (PT_CAMPAIGN_M2C_END_DATA*)data;
					CCampaign* campaign = CCampaignManager::getInstance().getCampaign(tempData->campaignId);
					if (!campaign )
					{
						return;
					}
					
					if (!campaign->isOwned())
					{
						return;	
					}
					if (campaign != mClient->getCampaign())
					{
						return;
					}
					campaign->reset();
					//mIsFinish = true;
					//mIsNormalExit = true;	
				}
				break;
			case PT_CAMPAIGN_T2C_READY_MYSELF:
				{
					PT_CAMPAIGN_T2C_READY_MYSELF_DATA* tempData = (PT_CAMPAIGN_T2C_READY_MYSELF_DATA*)data;
					CCampaign* campaign = mClient->getCampaign();
					if (campaign 
						&& mClient == campaign->getHost()
						&& campaign == CCampaignManager::getInstance().getCampaign(tempData->campaignId))
					{
						
						mMsg->AddMsg("【战场%I64d】：收到攻击方准备 次数 = %d",tempData->campaignId,campaign->getReadyCampaignRoomNum());
						if (mClient->getCampaign()->checkCompleteConfirm())
						{
							mMsg->AddErrorMsg("【战场%I64d】：开始战斗中 周期数 = %d",tempData->campaignId);
							mClient->getCampaign()->startBattle();
						}
					}
				}
	
				break;
			case PT_CAMPAIGN_T2C_LEAVE:
				break;
			case PT_CAMPAIGN_T2C_DESTROY:
				break;
			case PT_CAMPAIGN_T2C_START_NEW_CAMPAIGN:
				{
					PT_CAMPAIGN_T2C_START_NEW_CAMPAIGN_DATA* tempData = (PT_CAMPAIGN_T2C_START_NEW_CAMPAIGN_DATA*)data;
					CCampaign* campaign = mClient->getCampaign();
					if (campaign 
						&& campaign == CCampaignManager::getInstance().getCampaign(tempData->campaignId))
					{
						if (!campaign->isDenfense(mClient))
						{
							if (mClient == campaign->getHost())
							{
								mMsg->AddMsg("【战场%I64d】：战斗开始 周期数%d",mClient->getCampaign()->getCampaignId(),campaign->getCycleCount());
								mClient->getCampaign()->denfenseEnter();
								mMsg->AddMsg("【战场%I64d】：防守方进入游戏中",mClient->getCampaign()->getCampaignId());
							}
							mIsFinish = true;
							mIsNormalExit = true;
						}		
					}
				}
				break;
			case PT_CAMPAIGN_F2C_ENTER_DEFENSE:
				break;
			case PT_CAMPAIGN_T2C_CAMPAIGN_LIST_BEGIN:
				break;
			case PT_CAMPAIGN_T2C_CAMPAIGN_LIST_END:
				break;
			default:
				DYNAMIC_ASSERT(0);
				break;
			}
		}
	}
	//----------------------------------------------------------------------
	void CampaignOperate::onLeave()
	{
		if (mIsEnter || mIsFinish)
		{
			if (!mIsLeave)
			{
				mIsLeave = true;
				if (mIsNormalExit )
				{
					mMsg->AddMsg("【战场】：完成");
				}
				else
				{
					mMsg->AddErrorMsg("【战场】：丢弃");
				}
				mMsg->AddMsg("<---------【战场】--------->");	
			}			
			if (mClient->getCampaign() && mClient->getCampaign()->getState() == CCAMPAIGN_STATE_END)
			{

				mManager->setCurrentOperate();
			}
		}
	}
	//----------------------------------------------------------------------
	MG::Bool CampaignOperate::isFinish()
	{
		if (mIsFinish)
		{
			return true;
		}
		return false;
	}
	
}

