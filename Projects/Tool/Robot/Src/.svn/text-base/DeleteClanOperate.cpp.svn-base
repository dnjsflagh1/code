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
	DeleteClanOperate::DeleteClanOperate( OperateManager* mgr ,CClient* client,CClientMessage* msg,OperateType type)
		: BaseOperate(mgr,client,msg,type)
	{

	}
	//----------------------------------------------------------------------
	Bool DeleteClanOperate::onEnter()
	{
		return true;
	}
	//----------------------------------------------------------------------
	void DeleteClanOperate::onNetEvent( Byte channel,Byte type,void* data )
	{

	}
	//----------------------------------------------------------------------
	void DeleteClanOperate::onLeave()
	{

	}
	//----------------------------------------------------------------------
	MG::Bool DeleteClanOperate::isFinish()
	{
		if (mIsFinish)
		{
			return true;
		}
		ClientState& state = mClient->getState();
		return true;
	}
	//----------------------------------------------------------------------
	void DeleteClanOperate::onCloseByLoginServer()
	{

	}
	//----------------------------------------------------------------------
	void DeleteClanOperate::onCloseByFrontServer()
	{
		mMsg->AddErrorMsg("【删除家族】：前端服务器断开链接");
		mClient->getState().clear();
		mIsFinish = true;
		mIsNormalExit = false;
	}
}

