/******************************************************************************/
#include "stdafx.h"
#include "CClientNew.h"
#include "Operate.h"
#include "OperateManager.h"
#include "GameNetPacket.h"
#include "LoginNetPacket.h"
#include "PlayerNetPacket.h"
#include "ClientManager.h"
#include "ChatOperate.h"
/******************************************************************************/
namespace MG
{
	
	I32 ChatOperate::mSize = 0;
	ChannelInfo* ChatOperate::mSelectChannelInfo = NULL;
	U32	 ChatOperate::mIntervalTime = 0;	
	//U32	 ChatOperate::mFullServerIntervalTime = 2000;

	//--------------------------------------------------------------------------------
	ChatOperate::ChatOperate( OperateManager* mgr,CClient* client,CClientMessage* msg,OperateType type )
		: BaseOperate(mgr,client,msg,type)
	{
		mIsEnter = 0;
	}

	MG::Bool ChatOperate::onEnter()
	{
		if (BaseOperate::onEnter())
          {
			  mEnterTick = MGTimeOp::getCurrTick();
			  if (mClient->getState().isJoinGame)
			  {
				  mClient->stateNetChat(mSelectChannelInfo->id,mSize);
				  mIsNormalExit = true;
			  }
			  else
			  {
				  mMsg->AddErrorMsg("【聊天】：没有进入游戏");
				  mIsNormalExit = false;
				  mIsFinish = true;
			  }
          }
		return true;

	}


	void ChatOperate::onNetEvent( Byte channel,Byte type,void* data )
	{


	}

	MG::Bool ChatOperate::isFinish()
	{
		if (mIsFinish)
		{
			return true;
		}
		ClientState& state = mClient->getState();
        
		
		if ( state.isJoinGame && MGTimeOp::getCurrTick() - mEnterTick >= mIntervalTime)
		{
			return true;
		}
		     
		return false;
	}

	void ChatOperate::onLeave()
	{
		if (mIsEnter || mIsFinish)
		{
			if (!mIsLeave)
			{
				mIsLeave = true;
				if (mIsNormalExit )
				{
					mMsg->AddMsg("【聊天】：完成");
				}
				else
				{
					mMsg->AddErrorMsg("【聊天】：丢弃");
				}
				mMsg->AddMsg("<---------【聊天】--------->");
				mManager->setCurrentOperate();
			}
		}

	}

	void ChatOperate::onCloseByLoginServer()
	{
		mClient->getState().clear();
		mIsFinish = true;
		mIsNormalExit = false;
	}

	void ChatOperate::onCloseByFrontServer()
	{
		mClient->getState().clear();
		mIsFinish = true;
		mIsNormalExit = false;
	}
}