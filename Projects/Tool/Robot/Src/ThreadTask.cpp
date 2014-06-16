//***********************************************************************************************************
#include "stdafx.h"
#include "ThreadTask.h"
#include "ClientNetApplyManager.h"
#include "ThreadTaskManager.h"
//***********************************************************************************************************
namespace MG
{
	
    //***********************************************************************************************************
    // RobotNetTask
    //***********************************************************************************************************
	RobotNetTask::RobotNetTask()
		: ModeTask( U32(TTT_ROBOT_NET_TASK))

	{
		mNetEvent = NULL;
		mClient = NULL;
		mTaskNumber = 0;
	}
	//----------------------------------------------------------------------
	RobotNetTask::RobotNetTask(INetEvent* netEvent,CClient* client,U32 key )
		: ModeTask( U32(TTT_ROBOT_NET_TASK) ,key)
		
	{
		DYNAMIC_ASSERT(client);
		mNetEvent = netEvent;
		mClient = client;
	}
	//----------------------------------------------------------------------
	RobotNetTask::~RobotNetTask()
	{
		mNetEvent = NULL;
		mClient = NULL;
	}
	//----------------------------------------------------------------------
	void RobotNetTask::reset(INetEvent* netEvent,CClient* client,U32 key)
	{
		mNetEvent = netEvent;
		mClient = client;
		DYNAMIC_ASSERT(mClient);
		ModeTask::reset((U32)TTT_ROBOT_NET_TASK,key);
	}
	//----------------------------------------------------------------------
	void RobotNetTask::setNumber( Int number )
	{
		mTaskNumber = number;
	}
	//----------------------------------------------------------------------
	void RobotNetTask::process()
	{
		
		//FUNDETECTION(__MG_FUNC__)
		if (!mClient)
		{
			// 内存池，多线程有误
			DYNAMIC_ASSERT(false);
			return;
		}
		
		Str8 tempName;
		MGStrOp::toString(mClient->getPlayerName(),tempName);
		//MG_LOG(out_game_logic,"用户名:%s 处理编号:%d\n",tempName.c_str(),mTaskNumber);
		if (mClient->getFrontServerNetId() == mNetEvent->getID())
		{
			if (mNetEvent->getType() == NET_RECV)
			{	
				ClientNetApplyManager::getInstance().processPacket (mClient,(NetEventRecv*)mNetEvent,frontServerPacket);
				//GameNetPacketData* data = (GameNetPacketData*)(((NetEventRecv*)mNetEvent)->getData());
				//mClient->getOperateManager()->onNetEvent(data->channel,data->type,data->data);
			}
			else if (mNetEvent->getType() == NET_CLOSE)
			{
				mClient->onFrontServerClose();
				//mClient->getOperateManager()->onCloseByFrontServer();
			}
		
		}
		else if (mClient->getLoginServerNetId() == mNetEvent->getID())
		{
			if (mNetEvent->getType() == NET_RECV)
			{
				ClientNetApplyManager::getInstance().processPacket(mClient,(NetEventRecv*)mNetEvent,loginServerPacket);
				//GameNetPacketData* data = (GameNetPacketData*)(((NetEventRecv*)mNetEvent)->getData());
				//mClient->getOperateManager()->onNetEvent(data->channel,data->type,data->data);
			}
			else if (mNetEvent->getType() == NET_CLOSE)
			{
				mClient->onLoginServerClose();
				//mClient->getOperateManager()->onCloseByLoginServer();
			}
		}
		else
		{
			// 未知网络包
			DYNAMIC_ASSERT(false);
		}
		mClient->onNetEvent(mNetEvent);
	}
	//----------------------------------------------------------------------
	void RobotNetTask::free()
	{
		
		mClient = NULL;
		ThreadTaskManager::getInstance().freeRobotNetTask(this);

	}
	//----------------------------------------------------------------------
	Char8* RobotNetTask::getPlayerName()
	{
		Str8 tempName ;
		MGStrOp::toString(mClient->getPlayerName(),tempName);
		Char8 temp[64] = {0};
		StrCpy(temp,tempName.c_str());
		return temp;
	}

	//----------------------------------------------------------------------

}
//***********************************************************************************************************