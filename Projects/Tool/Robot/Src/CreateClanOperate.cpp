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
/******************************************************************************/
namespace MG
{

	//======================================================================
	CreateClanOperate::CreateClanOperate( OperateManager* mgr ,CClient* client,CClientMessage* msg,OperateType type)
		: BaseOperate(mgr,client,msg,type)
	{

	}
	//----------------------------------------------------------------------
	Bool CreateClanOperate::onEnter()
	{
		
		if(BaseOperate::onEnter())
		{
			mMsg->AddMsg("���������塿������");
			if (mClient->getState().isRecvOpenClan && !mClient->getState().isJoinGame)
			{
				mClient->stateNetCreateClan();
			}
			else
			{
				mMsg->AddErrorMsg("���������塿������������");
				mIsFinish = true;
				mIsNormalExit = false;
			}
		}
		return true;
	}
	//----------------------------------------------------------------------
	void CreateClanOperate::onNetEvent( Byte channel,Byte type,void* data )
	{
		if ( channel == GNPC_LOGIN )
		{
			switch(type)
			{
			case PT_LOGIN_L2C_ACC_LOGIN_FAIL:
				{
					DYNAMIC_ASSERT(false);
				}
				break;

			case PT_LOGIN_L2C_ACC_LOGIN_SUCCESS:	
				{
					DYNAMIC_ASSERT(false);
				}
				break;
		/*	case PT_LOGIN_L2C_ACC_LOGIN_QUEUE_INFO:
				{
					DYNAMIC_ASSERT(false);
				}
				break;*/
			case PT_LOGIN_F2C_ACC_LOGIN_RESULT:
				{
					DYNAMIC_ASSERT(false);
				}
				break;
			case PT_LOGIN_F2C_OPEN_CREATECLANUI:
				DYNAMIC_ASSERT(false);
				break;
			case PT_LOGIN_F2C_OPEN_CLANCONTROLUI:
				mClient->getState().isRecvOpenClan = true;
				break;
			case PT_LOGIN_F2C_CREATE_CLAN_RESULT:
				{
					PT_LOGIN_F2C_CREATE_CLAN_RESULT_DATA* tempData = (PT_LOGIN_F2C_CREATE_CLAN_RESULT_DATA*)data;
					if(tempData->result == CreateClanResult_Succeed)
					{
						mMsg->AddMsg("���������塿����������ɹ�");
					}
					else
					{
						mMsg->AddMsg("���������塿����������ʧ��");
						mClient->stateNetClose();
					}
				}
				break;
			case PT_LOGIN_F2C_CREATE_GENERAL_RESULT:
				DYNAMIC_ASSERT(false);
				break;
			case PT_LOGIN_F2C_OPENCRETEGENREALUI:
				DYNAMIC_ASSERT(false);
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
	void CreateClanOperate::onLeave()
	{
		if (mIsEnter || mIsFinish)
		{
			if (!mIsLeave)
			{
				mIsLeave = true;
				if (mIsNormalExit )
				{
					mMsg->AddMsg("���������塿�����");
				}
				else
				{
					mMsg->AddErrorMsg("���������塿������");
				}
				mMsg->AddMsg("<---------���������塿--------->");
				mManager->setCurrentOperate();
			}
		}
	}
	//----------------------------------------------------------------------
	MG::Bool CreateClanOperate::isFinish()
	{
		if (mIsFinish)
		{
			return true;
		}
		ClientState& state = mClient->getState();
		if (state.isRecvOpenClan)
		{
			return true;
		}
		return false;
	}

	void CreateClanOperate::onCloseByLoginServer()
	{

	}

	void CreateClanOperate::onCloseByFrontServer()
	{
		mMsg->AddErrorMsg("���������塿��ǰ�˷������Ͽ�����");
		mIsFinish = true;
		mIsNormalExit = false;;
	}

	//  [6/5/2012 wangyuan]
	//======================================================================
	CreateTroopOperate::CreateTroopOperate( OperateManager* mgr ,CClient* client,CClientMessage* msg,OperateType type)
		: BaseOperate(mgr,client,msg,type)
	{

	}
	//----------------------------------------------------------------------
	Bool CreateTroopOperate::onEnter()
	{

		if(BaseOperate::onEnter())
		{
			mMsg->AddMsg("���������ӡ�������");
			if (mClient->getState().isJoinGame)
			{
				//mClient->stateNetCreateClan();
				mClient->stateCreateTroop();
				//RegionNetPacketProcesser::getInstance().sendAddTroopTest(mClient->getFrontServerNetId(),mClient->getPlayerObj()->getAccountID());
			}
			else
			{
				mMsg->AddErrorMsg("���������ӡ�������������");
				mIsFinish = true;
				mIsNormalExit = false;
			}
		}
		return true;
	}
	//----------------------------------------------------------------------
	void CreateTroopOperate::onNetEvent( Byte channel,Byte type,void* data )
	{
		if (channel == GNPC_REGION)
		{
			switch (type)
			{
			case PT_REGION_M2C_ADD_TROOP:
				mIsFinish = true;
				break;
			default:
				{
					//DYNAMIC_ASSERT(false);
				}
			}
		}
	}
	//----------------------------------------------------------------------
	void CreateTroopOperate::onLeave()
	{
		if (mIsEnter || mIsFinish)
		{
			if (!mIsLeave)
			{
				mIsLeave = true;
				if (mIsNormalExit )
				{
					mMsg->AddMsg("���������ӡ������");
				}
				else
				{
					mMsg->AddErrorMsg("���������ӡ�������");
				}
				mMsg->AddMsg("<---------���������ӡ�--------->");
				mManager->setCurrentOperate();
			}
		}
	}
	//----------------------------------------------------------------------
	MG::Bool CreateTroopOperate::isFinish()
	{
		if (mIsFinish)
		{
			return true;
		}
		ClientState& state = mClient->getState();
		if (state.isRecvOpenClan)
		{
			return true;
		}
		return false;
	}

	void CreateTroopOperate::onCloseByLoginServer()
	{

	}

	void CreateTroopOperate::onCloseByFrontServer()
	{
		mMsg->AddErrorMsg("���������ӡ���ǰ�˷������Ͽ�����");
		mIsFinish = true;
		mIsNormalExit = false;;
	}

}

