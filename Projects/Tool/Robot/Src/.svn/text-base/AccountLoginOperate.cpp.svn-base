/******************************************************************************/
#include "stdafx.h"
#include "CClientNew.h"
#include "OperateManager.h"
#include "GameNetPacket.h"
#include "LoginNetPacket.h"
#include "PlayerNetPacket.h"
#include "AccountLoginOperate.h"

#include "ThreadTaskManager.h"
//#include "ClientManager.h"
/******************************************************************************/
namespace MG
{

	//======================================================================
	AccountLoginOperate::AccountLoginOperate( OperateManager* mgr ,CClient* client,CClientMessage* msg,OperateType type)
		: BaseOperate(mgr,client,msg,type)
	{

	}
	//----------------------------------------------------------------------
	AccountLoginOperate::~AccountLoginOperate()
	{

	}
	//----------------------------------------------------------------------
	Bool AccountLoginOperate::onEnter()
	{
		if(BaseOperate::onEnter())
		{
			mMsg->AddMsg("¡¾ÕËºÅµÇÂ½¡¿£º½øÈë");
			if (mClient->isDisconnect())
			{
				NetAddress addr(mClient->getIp(),2000);
				I32 netId = mClient->stateConnectLoginServer(addr);
				if(netId > -1)
				{
					mClient->getState().clear();
					//ClientManager::getInstance().addClientToLoginMap(mClient->getLoginServerNetId(),mClient);
					ThreadTaskManager::getInstance().addLoginClient(netId,mClient);
					mMsg->AddMsg("¡¾ÕËºÅµÇÂ½¡¿£ºÁ´½ÓµÇÂ½·þÎñÆ÷³É¹¦");
					mClient->stateNetAccountloginLoginServer();
				}
				else
				{
					mMsg->AddErrorMsg("¡¾ÕËºÅµÇÂ½¡¿£ºÁ´½ÓµÇÂ½·þÎñÆ÷Ê§°Ü");
					
					mIsFinish = true;
					mIsNormalExit = false;
				}
					
			}
			else
			{
				mMsg->AddErrorMsg("¡¾ÕËºÅµÇÂ½¡¿£ºÒÑ¾­Á´½ÓÉÏ·þÎñÆ÷");
				mIsFinish = true;
				mIsNormalExit = false;
			}
				
		}
		return true;
	}
	//----------------------------------------------------------------------
	void AccountLoginOperate::onNetEvent( Byte channel,Byte type,void* data )
	{
		if ( channel == GNPC_LOGIN )
		{
			switch(type)
			{
			case PT_LOGIN_L2C_ACC_LOGIN_FAIL:
				{
					PT_LOGIN_L2C_LOGIN_FAIL_DATA* tempData = (PT_LOGIN_L2C_LOGIN_FAIL_DATA*)data;
					switch(tempData->errResult)
					{
					case LFFT_LOGIN_UNKNOW:
						mMsg->AddErrorMsg("¡¾ÕËºÅµÇÂ½¡¿£ºÎ´ÖªµÄµÇÂ½´íÎó");
						break;
					case LCFT_LOGIN_REDUPLICATE:
						mMsg->AddErrorMsg("¡¾ÕËºÅµÇÂ½¡¿£ºÖØ¸´µÇÂ½");
						break;
					case LCFT_LOGIN_NONE_FRONTSERVER:
						mMsg->AddErrorMsg("¡¾ÕËºÅµÇÂ½¡¿£ºÇ°¶Ë·þÎñÆ÷Î´¿ªÆô");
						break;
					case LCFT_LOGIN_IDENTITY_ERROR:
						mMsg->AddErrorMsg("¡¾ÕËºÅµÇÂ½¡¿£ºÕËºÅ»òÃÜÂë´íÎó");
						break;
					case LCFT_LOGIN_IDENTITY_ERROR_MAX:
						mMsg->AddErrorMsg("¡¾ÕËºÅµÇÂ½¡¿£ºÕËºÅ»òÃÜÂë´íÎó´ÎÊýÌ«¶à");
						break;
					case LCFT_LOGIN_LOCK:
						mMsg->AddErrorMsg("¡¾ÕËºÅµÇÂ½¡¿£ºÕËºÅ±»Ëø¶¨");
						break;
					default:
						DYNAMIC_ASSERT(false);
						break;
					}
					mClient->stateNetClose();
					//onLeave(false);
				}
				break;

			case PT_LOGIN_L2C_ACC_LOGIN_SUCCESS:	
				{
					PT_LOGIN_L2C_LOGIN_SUCCESS_DATA* tempData = (PT_LOGIN_L2C_LOGIN_SUCCESS_DATA*)data;
					NetAddress addr(tempData->ip,tempData->port);
					I32 netId = mClient->stateConnectFrontServer(addr);
					if (netId > -1)
					{
						ThreadTaskManager::getInstance().addFrontClient(netId,mClient);
						//ClientManager::getInstance().addClientToFrontMap(mClient->getFrontServerNetId(),mClient);
						mMsg->AddMsg("¡¾ÕËºÅµÇÂ½¡¿£ºµÇÂ½Ç°¶Ë·þÎñÆ÷");
						mClient->stateNetAccountloginFrontServer();
					}
					else
					{
						mMsg->AddErrorMsg("¡¾ÕËºÅµÇÂ½¡¿£ºÁ´½ÓÕËºÅ·þÎñÆ÷Ê§°Ü");
						mClient->stateNetClose();
						//onLeave(false);
					}
				}
				break;
			/*case PT_LOGIN_L2C_ACC_LOGIN_QUEUE_INFO:
				{
					PT_LOGIN_L2C_ACC_LOGIN_QUEUE_INFO_DATA* tempData = (PT_LOGIN_L2C_ACC_LOGIN_QUEUE_INFO_DATA*)data;
					mMsg->AddErrorMsg("¡¾ÕËºÅµÇÂ½¡¿£ºÇ°Ãæ»¹ÓÐ%d¸öÈËÔÚµÈ´ý",tempData->waitCount);
				}
				break*/;
			case PT_LOGIN_F2C_ACC_LOGIN_RESULT:
				{
					PT_LOGIN_F2C_LOGIN_RESULT_DATA* tempData = (PT_LOGIN_F2C_LOGIN_RESULT_DATA*)data;
					switch(tempData->result)
					{
					case LCFT_LOGIN_UNKNOW:
							mMsg->AddErrorMsg("¡¾ÕËºÅµÇÂ½¡¿£ºÎ´ÖªµÄµÇÂ½Ç°¶Ë·þÎñÆ÷´íÎó");
							mClient->stateNetClose();
						break;
					case LCFT_LOGIN_SUCCESS:
						mClient->getState().isRecvLoginSucess = true;
						mMsg->AddMsg("¡¾ÕËºÅµÇÂ½¡¿£ºµÇÂ½Ç°¶Ë·þÎñÆ÷³É¹¦");
						break;
					case LCFT_LOGIN_FAIL:
						mMsg->AddErrorMsg("¡¾ÕËºÅµÇÂ½¡¿£ºµÇÂ½Ç°¶Ë·þÎñÆ÷Ê§°Ü");
						mClient->stateNetClose();
						break;
					}
					
				}
				break;
			case PT_LOGIN_F2C_OPEN_CREATECLANUI:
				{
					
					mClient->stateNetCreateClan();
					mMsg->AddMsg("¡¾ÕËºÅµÇÂ½¡¿£º¼Ò×å²»´æÔÚ£¬´´½¨¼Ò×å");
					mClient->getState().isRecvCreateClan = true;

				}
				break;
			case PT_LOGIN_F2C_OPEN_CLANCONTROLUI:
				mClient->getState().isRecvOpenClan = true;
				break;
			case PT_LOGIN_F2C_CREATE_CLAN_RESULT:
				{
					PT_LOGIN_F2C_CREATE_CLAN_RESULT_DATA* tempData = (PT_LOGIN_F2C_CREATE_CLAN_RESULT_DATA*)data;
					if(tempData->result == CreateClanResult_Succeed)
					{
						mMsg->AddMsg("¡¾ÕËºÅµÇÂ½¡¿£º´´½¨¼Ò×å³É¹¦");
					}
					else
					{
						mMsg->AddMsg("¡¾ÕËºÅµÇÂ½¡¿£º´´½¨¼Ò×åÊ§°Ü");
						mClient->stateNetClose();
					}
				}
				break;
			case PT_LOGIN_F2C_CREATE_GENERAL_RESULT:
				DYNAMIC_ASSERT(false);
				break;
			case PT_LOGIN_F2C_OPENCRETEGENREALUI:
				mMsg->AddMsg("¡¾ÕËºÅµÇÂ½¡¿£º½øÈë´ò¿ª¼Ò×å½çÃæ");
				mClient->getState().isRecvOpenClan = true;
				break;
			}
		}
		else if (channel == GNPC_PLAYER)
		{
			switch (type)
			{
			case PT_PLAYER_F2C_PLAYERCHARACTER_INFO_LIST:
				mClient->getState().isRecvHeroList = true;
				//onRecvClientGenrealInfoFromFrontServer( client, (PT_PLAYER_F2C_PLAYERCHARACTER_INFO_LIST_DATA*)data->data );
				break;
			case PT_PLAYER_F2C_JUMP_REGION:
				mClient->getState().isRecvJumpRegion = true;
				//onRecvPlayerJumpMap( client, (PT_PLAYER_F2C_JUMP_REGION_DATA*)data->data );
				break;
			case PT_PLAYER_M2C_REMAIN_PLAYERCHARACTER_INFO_LIST:
				//onRecvRemainPlayerCharacterListFromMapServer( client, (PT_PLAYER_M2C_REMAIN_PLAYERCHARACTER_INFO_LIST_DATA*)data->data );
				break;
			case PT_PLAYER_F2C_TROOP_INFO_LIST:
				mClient->getState().isRecvTroopList = true;
				//onRecvClientTroopListFromFrontServer(client, (PT_PLAYER_F2C_TROOP_INFO_LIST_DATA*)data->data);
				break;
			default:
				{
					DYNAMIC_ASSERT(false);
				}
			}
		}
	}
	//----------------------------------------------------------------------
	void AccountLoginOperate::onLeave()
	{	
		if (mIsEnter || mIsFinish)
		{
			if (!mIsLeave)
			{
				mIsLeave = true;
				if (mIsNormalExit )
				{
					mMsg->AddMsg("¡¾ÕËºÅµÇÂ½¡¿£ºÍê³É");
				}
				else
				{
					mMsg->AddErrorMsg("¡¾ÕËºÅµÇÂ½¡¿£º¶ªÆú");
				}
				mMsg->AddMsg("<---------¡¾ÕËºÅµÇÂ½¡¿--------->");
				mManager->setCurrentOperate();
			}
			
		}
	}
	//----------------------------------------------------------------------
	MG::Bool AccountLoginOperate::isFinish()
	{
		if (mIsFinish)
		{
			return true;
		}
		ClientState& state = mClient->getState();
		if ( state.isRecvLoginSucess && state.isRecvOpenClan)
		{
			return true;
		}
		return false;
	}
	//----------------------------------------------------------------------
	void AccountLoginOperate::onCloseByLoginServer()
	{
		if (mClient->getFrontServerNetId() > -1)
		{
			// ÕËºÅµÇÂ½Íê³ÉÓ¦¸Ã¶Ï¿ªLoginServerÁ´½Ó
		}
		else
		{
			mClient->getState().clear();
			mMsg->AddErrorMsg("¡¾ÕËºÅµÇÂ½¡¿£ºµÇÂ¼·þÎñÆ÷¶Ï¿ªÁ´½Ó");
			mIsFinish = true;
			mIsNormalExit = false;
		}
	}
	//----------------------------------------------------------------------
	void AccountLoginOperate::onCloseByFrontServer()
	{
		if (mClient->getLoginServerNetId() > -1)
		{
			mMsg->AddErrorMsg("¡¾ÕËºÅµÇÂ½¡¿£ºÇ°¶Ë·þÎñÆ÷¶Ï¿ªÁ´½Ó");
			mClient->stateNetClose();
		}
		else
		{
			mMsg->AddErrorMsg("¡¾ÕËºÅµÇÂ½¡¿£ºÇ°¶Ë·þÎñÆ÷¶Ï¿ªÁ´½Ó");
			mIsFinish = true;
			mIsNormalExit = false;
		}
		mClient->getState().clear();
	}
	
}

