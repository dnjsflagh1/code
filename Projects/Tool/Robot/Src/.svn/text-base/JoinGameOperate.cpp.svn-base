/******************************************************************************/
#include "stdafx.h"
#include "CClientNew.h"
#include "Operate.h"
#include "OperateManager.h"
#include "GameNetPacket.h"
#include "LoginNetPacket.h"
#include "PlayerNetPacket.h"
//#include "ClientManager.h"
/******************************************************************************/
namespace MG
{
	//======================================================================
	JoinGameOperate::JoinGameOperate( OperateManager* mgr ,CClient* client,CClientMessage* msg,OperateType type)
		: BaseOperate(mgr,client,msg,type)
	{
		
	}
	//----------------------------------------------------------------------
	Bool JoinGameOperate::onEnter()
	{
		if(BaseOperate::onEnter())
		{
			mMsg->AddMsg("【进入游戏】：进入");
			if (mClient->getState().isRecvOpenClan && !mClient->getState().isJoinGame)
			{
				mClient->stateNetJoinGame();

				//小虎测试
				//Sleep(5);
			}
			else
			{
				mMsg->AddErrorMsg("【进入游戏】：条件不符合");
				mIsFinish = true;
				mIsNormalExit = false;
			}
		}
		return true;
	}
	//----------------------------------------------------------------------
	void JoinGameOperate::onNetEvent( Byte channel,Byte type,void* data )
	{
		if ( channel == GNPC_LOGIN )
		{
			switch(type)
			{
			case PT_LOGIN_L2C_ACC_LOGIN_FAIL:
				DYNAMIC_ASSERT(false);
				break;
			case PT_LOGIN_L2C_ACC_LOGIN_SUCCESS:	
				DYNAMIC_ASSERT(false);
				break;
			/*case PT_LOGIN_L2C_ACC_LOGIN_QUEUE_INFO:
				DYNAMIC_ASSERT(false);
				break;*/
			case PT_LOGIN_F2C_ACC_LOGIN_RESULT:
				DYNAMIC_ASSERT(false);
				break;
			case PT_LOGIN_F2C_OPEN_CREATECLANUI:
				DYNAMIC_ASSERT(false);
				break;
			case PT_LOGIN_F2C_OPEN_CLANCONTROLUI:
				DYNAMIC_ASSERT(false);;
				break;
			case PT_LOGIN_F2C_CREATE_CLAN_RESULT:
				DYNAMIC_ASSERT(false);
				break;
			case PT_LOGIN_F2C_CREATE_GENERAL_RESULT:
				{
					PT_LOGIN_F2C_CREATE_GENERAL_RESULT_DATA* tempData = (PT_LOGIN_F2C_CREATE_GENERAL_RESULT_DATA*)data;
					if (tempData->result == CreateGenrealResult_Succeed)
					{
						mMsg->AddMsg("【进入游戏】：创建武将成功,进入游戏");
						mClient->stateNetJoinGame();
					}
					else
					{
						mMsg->AddMsg("【进入游戏】：创建武将失败,关闭连接");
						mClient->stateNetClose();
					}
				}
				break;
			case PT_LOGIN_F2C_OPENCRETEGENREALUI:
				{
					mMsg->AddMsg("【进入游戏】：武将不存在，创建武将");
					mClient->stateNetCreateCharacter();
				}
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
	}
	//----------------------------------------------------------------------
	void JoinGameOperate::onLeave()
	{
		if (mIsEnter || mIsFinish)
		{
			if (!mIsLeave)
			{
				mIsLeave = true;
				if (mIsNormalExit )
				{
					mMsg->AddMsg("【进入游戏】：完成");
				}
				else
				{
					mMsg->AddErrorMsg("【进入游戏】：丢弃");
				}
				mMsg->AddMsg("<---------【进入游戏】--------->");
				mManager->setCurrentOperate();
			}
		}
	}
	//----------------------------------------------------------------------
	MG::Bool JoinGameOperate::isFinish()
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
			return true;
		}
		return false;
	}
	//----------------------------------------------------------------------
	void JoinGameOperate::onCloseByLoginServer()
	{

	}
	//----------------------------------------------------------------------
	void JoinGameOperate::onCloseByFrontServer()
	{
		mMsg->AddErrorMsg("【进入游戏】：前端服务器断开链接");
		mClient->getState().clear();
		mIsFinish = true;
		mIsNormalExit = false;
	}
}

