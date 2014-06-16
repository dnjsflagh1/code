/******************************************************************************/
#include "stdafx.h"
#include "CClientNew.h"
#include "Operate.h"
#include "OperateManager.h"
#include "GameNetPacket.h"
#include "LoginNetPacket.h"
#include "PlayerNetPacket.h"
#include "RegionNetPacket.h"

//#include "ClientManager.h"
#include "ThreadTaskManager.h"

#include "AutoJoinGameOperate.h"
/******************************************************************************/
namespace MG
{

	//======================================================================
	AutoJoinGameOperate::AutoJoinGameOperate( OperateManager* mgr ,CClient* client,CClientMessage* msg,OperateType type)
	: BaseOperate(mgr,client,msg,type)
	{
		mIsActiveDisconnect = false;
	}
	//----------------------------------------------------------------------
	Bool AutoJoinGameOperate::onEnter()
	{
		if(BaseOperate::onEnter())
		{
			mMsg->AddMsg("���Զ�������Ϸ��������");
			if (mClient->getState().isJoinGame)
			{
				mIsActiveDisconnect = true;
				mClient->stateNetClose();
				//�ȴ��������ͷ���Դ
				//Sleep(1);
			}
			if (mClient->isDisconnect())
			{
				NetAddress addr(mClient->getIp(),2000);
				I32 netId = mClient->stateConnectLoginServer(addr);
				if(netId > -1)
				{
					//ClientManager::getInstance().addClientToLoginMap(mClient->getLoginServerNetId(),mClient);
					ThreadTaskManager::getInstance().addLoginClient(netId,mClient);
					mMsg->AddMsg("���Զ�������Ϸ�������ӵ�½�������ɹ�");
					mClient->stateNetAccountloginLoginServer();
				}
				else
				{
					mMsg->AddErrorMsg("���Զ�������Ϸ�������ӵ�½������ʧ��");
					mIsFinish = true;
					mIsNormalExit = false;
				}
			}
			
		}
		return true;
	}
	//----------------------------------------------------------------------
	void AutoJoinGameOperate::onCloseByLoginServer()
	{	
		mClient->getState().clear();
		if (mClient->getFrontServerNetId() < 0)
		{
			mIsFinish = true;
			mIsNormalExit = false;
		}
		/*if (mIsActiveDisconnect)
		{
			if (mClient->isDisconnect())
			{
				NetAddress addr(mClient->getIp(),2000);
				if(mClient->stateConnectLoginServer(addr))
				{
					mMsg->AddMsg("���Զ�������Ϸ�������ӵ�½�������ɹ�");
					mClient->stateNetAccountloginLoginServer();
				}
				else
				{
					mMsg->AddErrorMsg("���Զ�������Ϸ�������ӵ�½������ʧ��");
					mIsFinish = true;
					mIsNormalExit = false;
				}
			}
		}
		else(mClient->isDisconnect())
		{
			mIsFinish = true;
			mIsNormalExit = false;
		}*/
	}
	//----------------------------------------------------------------------
	void AutoJoinGameOperate::onCloseByFrontServer()
	{
		mClient->getState().clear();
		if (mIsActiveDisconnect)
		{
			if (mClient->isDisconnect())
			{
				NetAddress addr(mClient->getIp(),2000);
				if(mClient->stateConnectLoginServer(addr))
				{
					//ClientManager::getInstance().addClientToLoginMap(mClient->getLoginServerNetId(),mClient);
					ThreadTaskManager::getInstance().addLoginClient(mClient->getLoginServerNetId(),mClient);
					mMsg->AddMsg("���Զ�������Ϸ�������ӵ�½�������ɹ�");
					mClient->stateNetAccountloginLoginServer();
				}
				else
				{
					mMsg->AddErrorMsg("���Զ�������Ϸ�������ӵ�½������ʧ��");
					mIsFinish = true;
					mIsNormalExit = false;
				}
			}
		}
		else
		{
			mIsFinish = true;
			mIsNormalExit = false;
		}
	}
	//----------------------------------------------------------------------
	void AutoJoinGameOperate::onNetEvent( Byte channel,Byte type,void* data )
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
						mMsg->AddErrorMsg("���Զ�������Ϸ����δ֪�ĵ�½����");
						break;
					case LCFT_LOGIN_REDUPLICATE:
						mMsg->AddErrorMsg("���Զ�������Ϸ�����ظ���½");
						break;
					case LCFT_LOGIN_NONE_FRONTSERVER:
						mMsg->AddErrorMsg("���Զ�������Ϸ����ǰ�˷�����δ����");
						break;
					case LCFT_LOGIN_IDENTITY_ERROR:
						mMsg->AddErrorMsg("���Զ�������Ϸ�����˺Ż��������");
						break;
					case LCFT_LOGIN_IDENTITY_ERROR_MAX:
						mMsg->AddErrorMsg("���Զ�������Ϸ�����˺Ż�����������̫��");
						break;
					case LCFT_LOGIN_LOCK:
						mMsg->AddErrorMsg("���Զ�������Ϸ�����˺ű�����");
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
					static int recvFrontServerInfo = 0;
					PT_LOGIN_L2C_LOGIN_SUCCESS_DATA* tempData = (PT_LOGIN_L2C_LOGIN_SUCCESS_DATA*)data;
					NetAddress addr(tempData->ip,tempData->port);
					recvFrontServerInfo++;
					I32 netId = mClient->stateConnectFrontServer(addr);
					if (netId > -1)
					{
						//ClientManager::getInstance().addClientToFrontMap(mClient->getFrontServerNetId(),mClient);
						ThreadTaskManager::getInstance().addFrontClient(netId,mClient);
						mMsg->AddMsg("���Զ�������Ϸ������½ǰ�˷�����");
						mClient->stateNetAccountloginFrontServer();
						MG_LOG(out_error,"��¼FrontServer\n");
					}
					else
					{
						mMsg->AddErrorMsg("���Զ�������Ϸ���������˺ŷ�����ʧ��");
						mClient->stateNetClose();
					}
				}
				break;
			/*case PT_LOGIN_L2C_ACC_LOGIN_QUEUE_INFO:
				{
					PT_LOGIN_L2C_ACC_LOGIN_QUEUE_INFO_DATA* tempData = (PT_LOGIN_L2C_ACC_LOGIN_QUEUE_INFO_DATA*)data;
					mMsg->AddErrorMsg("���Զ�������Ϸ����ǰ�滹��%d�����ڵȴ�",tempData->waitCount);
				}
				break;*/
			case PT_LOGIN_F2C_ACC_LOGIN_RESULT:
				{
					PT_LOGIN_F2C_LOGIN_RESULT_DATA* tempData = (PT_LOGIN_F2C_LOGIN_RESULT_DATA*)data;
					switch(tempData->result)
					{
					case LCFT_LOGIN_UNKNOW:
						mMsg->AddErrorMsg("���Զ�������Ϸ����δ֪�ĵ�½ǰ�˷���������");
						mClient->stateNetClose();
						break;
					case LCFT_LOGIN_SUCCESS:
						mClient->getState().isRecvLoginSucess = true;
						mMsg->AddMsg("���Զ�������Ϸ������½ǰ�˷������ɹ�");
						break;
					case LCFT_LOGIN_FAIL:
						mMsg->AddErrorMsg("���Զ�������Ϸ������½ǰ�˷�����ʧ��");
						mClient->stateNetClose();
						break;
					}

				}
				break;
			case PT_LOGIN_F2C_OPEN_CREATECLANUI:
				{
					Int clanSize = mClient->getPlayerObj()->getClanList()->size();
					if ( clanSize>0 )
					{
                         int stop = 1;
                         break;
					}                    
					mClient->stateNetCreateClan();
					mMsg->AddMsg("���Զ�������Ϸ�������岻���ڣ���������");
					mClient->getState().isRecvCreateClan = true;
				}
				break;
			case PT_LOGIN_F2C_OPEN_CLANCONTROLUI:
				mClient->getState().isRecvOpenClan = true;
				mMsg->AddMsg("���Զ�������Ϸ����������Ϸ��");
				mClient->stateNetJoinGame();
				break;
			case PT_LOGIN_F2C_CREATE_CLAN_RESULT:
				{
					PT_LOGIN_F2C_CREATE_CLAN_RESULT_DATA* tempData = (PT_LOGIN_F2C_CREATE_CLAN_RESULT_DATA*)data;
					if(tempData->result == CreateClanResult_Succeed)
					{
						mMsg->AddMsg("���Զ�������Ϸ������������ɹ�");
					}
					else
					{
						mMsg->AddMsg("���Զ�������Ϸ������������ʧ��");
						mClient->stateNetClose();
					}
				}
				break;
			case PT_LOGIN_F2C_CREATE_GENERAL_RESULT:
				{
					PT_LOGIN_F2C_CREATE_GENERAL_RESULT_DATA* tempData = (PT_LOGIN_F2C_CREATE_GENERAL_RESULT_DATA*)data;
					if (tempData->result == CreateGenrealResult_Succeed)
					{
						mMsg->AddMsg("���Զ�������Ϸ����������ɫ�ɹ�,������Ϸ");
						mClient->stateNetJoinGame();
					}
					else
					{
						mMsg->AddMsg("���Զ�������Ϸ����������ɫʧ��");
						mClient->stateNetClose();
					}
				}
				break;
			case PT_LOGIN_F2C_OPENCRETEGENREALUI:
				mMsg->AddMsg("���Զ�������Ϸ������ɫ�����ڣ�������ɫ");
				mClient->getState().isRecvOpenClan = true;
				mClient->stateNetCreateCharacter();
				break;
			}
		}
		else if (channel == GNPC_PLAYER)
		{
			switch (type)
			{
			case PT_PLAYER_F2C_PLAYERCHARACTER_INFO_LIST:
				mClient->getState().isRecvHeroList = true;
				break;
			case PT_PLAYER_F2C_JUMP_REGION:
				mClient->getState().isRecvJumpRegion = true;
				break;
			case PT_PLAYER_M2C_REMAIN_PLAYERCHARACTER_INFO_LIST:
				break;
			case PT_PLAYER_F2C_TROOP_INFO_LIST:
				mClient->getState().isRecvTroopList = true;
				break;
			default:
				{
					DYNAMIC_ASSERT(false);
				}
			}
		}
		else if (channel == GNPC_REGION)
		{


				switch (type)
				{
				case PT_REGION_M2C_ADD_PLAYER_CHARACTER:
					{
						PT_REGION_M2C_ADD_PLAYER_CHARACTER_DATA* tempData = (PT_REGION_M2C_ADD_PLAYER_CHARACTER_DATA*)data;
						for(Int i = 0; i < tempData->addPlayerNum; ++i)
						{
							CPlayerCharacter* character = mClient->getPlayerObj()->getPlayerCharacter(tempData->addPlayerInfo[i].character_id);
							if (character)
							{
								mClient->getState().isRecvJumpRegion = true;
								character->setJoinRegion(true);
							}
						}
					}
					break;
				case PT_REGION_M2C_REMOVE_PLAYER_CHARACTER:
					{
						PT_REGION_M2C_REMOVE_PLAYER_CHARACTER_DATA* tempData = (PT_REGION_M2C_REMOVE_PLAYER_CHARACTER_DATA*)data;
						CPlayerCharacter* character = mClient->getPlayerObj()->getPlayerCharacter(tempData->character_id);
						if (character)
						{
							mClient->getState().isRecvJumpRegion = false;
							character->setJoinRegion(false);
						}

					}
	
					break;
#if 0
				case PT_REGION_M2C_ADD_TROOP_GROUP:		
					break;
				case PT_REGION_M2C_REMOVE_TROOP_GROUP:
					break;
#endif
				case PT_REGION_M2C_ADD_BUILDING:
					
					break;
				case PT_REGION_M2C_REMOVE_BUILDING:
				
					break;
//				case PT_REGION_M2C_ADD_TRITH_PART_CHARACTER:
				
					//break;
				//case PT_REGION_M2C_ADD_CAMP:
				//
				//	break;
				case PT_REGION_M2C_CREATE_TROOP:
	
					break;
				case PT_REGION_M2C_ADD_TROOP:
					break;
				}
		}
	}
	//----------------------------------------------------------------------
	void AutoJoinGameOperate::onLeave()
	{
		if (mIsEnter || mIsFinish)
		{
			if (!mIsLeave)
			{
				mIsLeave = true;
				if (mIsNormalExit )
				{
					mMsg->AddMsg("���Զ�������Ϸ�������");
				}
				else
				{
					mMsg->AddErrorMsg("���Զ�������Ϸ��������");
				}
				mMsg->AddMsg("<---------���Զ�������Ϸ��--------->");
				mManager->setCurrentOperate();
			}
		}
	}
	//----------------------------------------------------------------------
	MG::Bool AutoJoinGameOperate::isFinish()
	{
		if (mIsFinish)
		{
			return true;
		}
		ClientState& state = mClient->getState();
		if ( state.isRecvJumpRegion && state.isRecvOpenClan)
		{
			state.isJoinGame = true;
			state.isRecvJumpRegion = false;
			mIsNormalExit = true;
			return true;
		}
		return false;
	}
	
}

