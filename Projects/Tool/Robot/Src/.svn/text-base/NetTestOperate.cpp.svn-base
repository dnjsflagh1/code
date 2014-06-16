/******************************************************************************/
#include "stdafx.h"
#include "CClientNew.h"
#include "Operate.h"
#include "OperateManager.h"
#include "GameNetPacket.h"
#include "LoginNetPacket.h"
#include "PlayerNetPacket.h"
#include "ClientManager.h"
/******************************************************************************/
namespace MG
{
	U32	NetTestOperate::mEnterTick = 0;
	U32	NetTestOperate::mIntervalTime = 10;
	//----------------------------------------------------------------------
	NetTestOperate::NetTestOperate( OperateManager* mgr,CClient* client,CClientMessage* msg,OperateType type )
		: BaseOperate(mgr,client,msg,type)
	{

	}
	//----------------------------------------------------------------------
	Bool NetTestOperate::onEnter()
	{

		if(BaseOperate::onEnter())
		{
			mEnterTick = MGTimeOp::getCurrTick();
			//mMsg->AddMsg("【随机移动】：进入");
			if (mClient->getState().isJoinGame)
			{
				mClient->stateTestNet();
				mIsNormalExit = true;
			}
			else
			{
				//mMsg->AddErrorMsg("【随机移动】：没有进入游戏");
				mIsNormalExit = false;
				mIsFinish = true;
			}

		}
		return true;
	}
	//----------------------------------------------------------------------
	void NetTestOperate::onCloseByLoginServer()
	{	
		mClient->getState().clear();
		DYNAMIC_ASSERT(false);
		mIsFinish = true;
		mIsNormalExit = false;
	}
	//----------------------------------------------------------------------
	void NetTestOperate::onCloseByFrontServer()
	{
		mClient->getState().clear();
		mIsFinish = true;
		mIsNormalExit = false;
	}
	//----------------------------------------------------------------------
	MG::Bool NetTestOperate::isFinish()
	{
		if (mIsFinish)
		{
			return true;
		}
		ClientState& state = mClient->getState();
		if ( state.isJoinGame &&  MGTimeOp::getCurrTick() - mEnterTick >= mIntervalTime)
		{
			return true;
		}
		return false;
	}
	//----------------------------------------------------------------------
	void NetTestOperate::onNetEvent( Byte channel,Byte type,void* data )
	{

	}
	//----------------------------------------------------------------------
	void NetTestOperate::onLeave()
	{
		if (mIsEnter || mIsFinish)
		{
			if (!mIsLeave)
			{
				mIsLeave = true;
				if (mIsNormalExit )
				{
					//mMsg->AddMsg("【随机移动】：完成");
				}
				else
				{
					mMsg->AddErrorMsg("【随机移动】：丢弃");
				}
				mMsg->AddMsg("<---------【随机移动】--------->");
				mManager->setCurrentOperate();
			}
		}
	}
}

