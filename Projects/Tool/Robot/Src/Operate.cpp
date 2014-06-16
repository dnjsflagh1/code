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
	BaseOperate::BaseOperate( OperateManager* mgr,CClient* client,CClientMessage* msg,OperateType type)
	{
		mManager = mgr;
		mClient = client;
		mMsg = msg;
		mIsEnter = false;
		mIsLeave = false;
		mIsFinish = false;
		mIsNormalExit = true;
		mEnterTick = MG::MGTimeOp::getCurrTick();
		mType = type;
	}
	//----------------------------------------------------------------------
	BaseOperate::~BaseOperate()
	{
		mManager = NULL;
		mClient = NULL;
		mMsg = NULL;
	}
	//----------------------------------------------------------------------
	void BaseOperate::setTimeOut( Bool timeOut /*= true*/ )
	{
		mIsTimeOut = timeOut;
	}
	//----------------------------------------------------------------------
	OperateManager* BaseOperate::getManager()
	{
		return mManager;
	}
	//----------------------------------------------------------------------
	Bool BaseOperate::onEnter()
	{
		if (!mIsEnter)
		{
			mIsEnter = true;
			if (mManager && mClient && mMsg)
			{
				mMsg->AddMsg("<-------准备进入下一操作------->");
				return true;
			}
		}
		return false;
	}
	//----------------------------------------------------------------------
	MG::Bool BaseOperate::isEnter()
	{
		return mIsEnter;
	}
	//----------------------------------------------------------------------
	MG::Bool BaseOperate::isLeave()
	{
		return mIsLeave;
	}
	//----------------------------------------------------------------------
	void BaseOperate::reset()
	{
		mIsTimeOut = false;
		mIsEnter = false;
		mIsLeave = false;
		mIsFinish = false;
		mIsNormalExit = true;
	}

	void BaseOperate::update()
	{
		//TODO:

	}
	
	//----------------------------------------------------------------------
}

