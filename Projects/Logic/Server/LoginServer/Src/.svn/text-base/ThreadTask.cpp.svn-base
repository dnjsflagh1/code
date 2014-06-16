//***********************************************************************************************************
#include "stdafx.h"
#include "ThreadTask.h"
#include "LoginServerMain.h"
#include "ThreadTask.h"
#include "ThreadTaskManager.h"
#include "ClientManager.h"
#include "ServerManager.h"
//***********************************************************************************************************
namespace MG
{
	
	//***********************************************************************************************************
	// ClientNormalTask
	//***********************************************************************************************************
	//----------------------------------------------------------------------
	ClientNormalTask::ClientNormalTask( NetEventRecv* netEvent,I32 clientNetId, U32 key /*= 0*/ )
		:ModeTask( U32(TTT_NORMAL_CLIENT),key)
	{
		mNetEvent = netEvent;
		mClientNetId = clientNetId;
	}

	//----------------------------------------------------------------------
	ClientNormalTask::~ClientNormalTask()
	{

	}

	//----------------------------------------------------------------------
	void ClientNormalTask::process()
	{
		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		ClientManager::getInstance().processPacket(mClientNetId, mNetEvent);

	}
	//----------------------------------------------------------------------
	void ClientNormalTask::free()
	{
		ThreadTaskManager::getInstance().freeClientNormalTask(this);
	}
   
    //***********************************************************************************************************
    // ServerNormalTask
    //***********************************************************************************************************
    //----------------------------------------------------------------------
	ServerNormalTask::ServerNormalTask( NetEventRecv* netEvent,I32 serverNetId, U32 key /*= 0*/ )
		:ModeTask( U32(TTT_NORMAL_SERVER),key)
	{
		mNetEvent = netEvent;
		mServerNetId = serverNetId;
	}

    //----------------------------------------------------------------------
	ServerNormalTask::~ServerNormalTask()
	{

	}

    //----------------------------------------------------------------------
	void ServerNormalTask::process()
	{
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
		ServerManager::getInstance().processPacket(mServerNetId,mNetEvent);
		
	}
    //----------------------------------------------------------------------
	void ServerNormalTask::free()
	{
		ThreadTaskManager::getInstance().freeServerNormalTask(this);
	}
}
//***********************************************************************************************************