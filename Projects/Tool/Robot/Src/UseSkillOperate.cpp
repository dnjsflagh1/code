/******************************************************************************/
#include "stdafx.h"
#include "CClientNew.h"
#include "Operate.h"
#include "OperateManager.h"
#include "GameNetPacket.h"
#include "LoginNetPacket.h"
#include "PlayerNetPacket.h"
//#include "ClientManager.h"
#include "UseSkillOperate.h"
/******************************************************************************/
namespace MG
{

	U32	UseSkillOperate::mEnterTick = 0;
	U32	UseSkillOperate::mIntervalTime = 1000;
	//----------------------------------------------------------------------
	UseSkillOperate::UseSkillOperate( OperateManager* mgr,CClient* client,CClientMessage* msg,OperateType type )
		: BaseOperate(mgr,client,msg,type)
	{

	}
	//----------------------------------------------------------------------
	Bool UseSkillOperate::onEnter()
	{
		
		if(BaseOperate::onEnter())
		{
			mEnterTick = MGTimeOp::getCurrTick();
			mMsg->AddMsg("【使用技能】：进入");
			if (mClient->getState().isJoinGame)
			{
				mClient->stateSendClantSkillRequest();
				mClient->stateSendEmitterSkillRequest();
				mClient->stateSendCollisionAffectRequest();
				mIsNormalExit = true;
			}
			else
			{
				mMsg->AddErrorMsg("【使用技能】：没有进入游戏");
				mIsNormalExit = false;
				mIsFinish = true;
			}

		}
		return true;
	}
	//----------------------------------------------------------------------
	void UseSkillOperate::onCloseByLoginServer()
	{	
		mClient->getState().clear();
		DYNAMIC_ASSERT(false);
		mIsFinish = true;
		mIsNormalExit = false;
	}
	//----------------------------------------------------------------------
	void UseSkillOperate::onCloseByFrontServer()
	{
		mClient->getState().clear();
		mIsFinish = true;
		mIsNormalExit = false;
	}
	//----------------------------------------------------------------------
	MG::Bool UseSkillOperate::isFinish()
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
	//----------------------------------------------------------------------
	void UseSkillOperate::onNetEvent( Byte channel,Byte type,void* data )
	{

	}
	//----------------------------------------------------------------------
	void UseSkillOperate::onLeave()
	{
		if (mIsEnter || mIsFinish)
		{
			if (!mIsLeave)
			{
				mIsLeave = true;
				if (mIsNormalExit )
				{
					mMsg->AddMsg("【使用技能】：完成");
				}
				else
				{
					mMsg->AddErrorMsg("【使用技能】：丢弃");
				}
				mMsg->AddMsg("<---------【使用技能】--------->");
				mManager->setCurrentOperate();
			}
		}
	}

}

