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
	CloseOperate::CloseOperate( OperateManager* mgr ,CClient* client,CClientMessage* msg,OperateType type)
		: BaseOperate(mgr,client,msg,type)
	{

	}
	//----------------------------------------------------------------------
	Bool CloseOperate::onEnter()
	{
		if(BaseOperate::onEnter())
		{
			mMsg->AddMsg("【关闭游戏】：进入");
			if(!mClient->isDisconnect())
			{
				mClient->stateNetClose();
			}
			else
			{
				mMsg->AddErrorMsg("【关闭游戏】：链接已断开");
				mIsFinish = true;
				mIsNormalExit = false;
			}
		}
		return true;
	}
	//----------------------------------------------------------------------
	void CloseOperate::onNetEvent( Byte channel,Byte type,void* data )
	{

	}
	//----------------------------------------------------------------------
	void CloseOperate::onLeave()
	{
		if (mIsEnter || mIsFinish)
		{
			if (!mIsLeave)
			{
				mIsLeave = true;
				if (mIsNormalExit )
				{
					mMsg->AddMsg("【关闭游戏】：完成");
				}
				else
				{
					mMsg->AddErrorMsg("【关闭游戏】：丢弃");
				}
				mMsg->AddMsg("<---------【关闭游戏】--------->");
				mManager->setCurrentOperate();
			}
		}

	}
	//----------------------------------------------------------------------
	MG::Bool CloseOperate::isFinish()
	{
		if (mIsFinish)
		{
			return true;
		}
		ClientState& state = mClient->getState();
		return false;
	}
	//----------------------------------------------------------------------
	void CloseOperate::onCloseByLoginServer()
	{
		if(mClient->getFrontServerNetId() < 0)
		{
			mIsFinish = true;
			mIsNormalExit = true;
			mClient->getPlayerObj()->deleteAllClan();
		}
		mClient->getState().clear();
		
	}
	//----------------------------------------------------------------------
	void CloseOperate::onCloseByFrontServer()
	{
		//if(mClient->getLoginServerNetId() < 0)
		{
			mIsFinish = true;
			mIsNormalExit = true;
			mClient->getPlayerObj()->deleteAllClan();
		}
		mClient->getState().clear();
	}

}

