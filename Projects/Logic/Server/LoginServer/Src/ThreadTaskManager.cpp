//***********************************************************************************************************
#include "stdafx.h"
#include "ThreadTaskManager.h"
#include "LoginServerMain.h"
//***********************************************************************************************************
namespace MG
{
	//-----------------------------------------------------------------------------
	ThreadTaskManager::ThreadTaskManager()
	{
		
	}

	//-----------------------------------------------------------------------------
	ThreadTaskManager::~ThreadTaskManager()
	{
		
	}

	//-----------------------------------------------------------------------------
	Bool ThreadTaskManager::initialize()
	{
        // 线程任务
		mClientNormalTaskThread.create(&mClientNormalTaskThread,"mClientNormalTaskThread");
		mServerNormalTaskThread.create(&mServerNormalTaskThread,"mServerNormalTaskThread");
#ifdef _DEBUG
		Thread::SetThreadName(mClientNormalTaskThread.getThreadId(),"ThreadTaskManager::mClientNormalTaskThread");
		Thread::SetThreadName(mServerNormalTaskThread.getThreadId(),"ThreadTaskManager::mServerNormalTaskThread");
#endif
	
		return true;
	}

	//-----------------------------------------------------------------------------
	Bool ThreadTaskManager::unInitialize()
	{
		mClientNormalTaskThread.destory();
		mServerNormalTaskThread.destory();
		return true;
	}

	//-----------------------------------------------------------------------------
	void ThreadTaskManager::addClientNormalTask(NetEventRecv* netEvent, I32 clientNetId,U32 key /*= 0*/ )
	{
		netEvent->addLocker();

		ClientNormalTask* task = NULL;
		mClientTaskCs.lock();
		{
			task = MG_POOL_NEW(mClientNormalTaskPool,ClientNormalTask,(netEvent,clientNetId,key));
		}
		mClientTaskCs.unlock();
		mClientNormalTaskThread.addTask(task);
	}

	//-----------------------------------------------------------------------------
	void ThreadTaskManager::freeClientNormalTask( ClientNormalTask* task )
	{
        if ( task->mNetEvent->subLocker() <= 0 )
            LoginServerMain::getInstance().freeEvent( task->mNetEvent );

		mClientTaskCs.lock();
		if ( task )
			MG_POOL_DELETE( mClientNormalTaskPool, task);
		mClientTaskCs.unlock();
	}

	//-----------------------------------------------------------------------------
	void ThreadTaskManager::addServerNormalTask(NetEventRecv* netEvent, I32 serverNetId,U32 key /*= 0*/ )
	{
		netEvent->addLocker();

		ServerNormalTask* task = NULL;
		mServerNormalTaskCs.lock();
		{
			task = MG_POOL_NEW(mServerNormalTaskPool,ServerNormalTask,(netEvent,serverNetId,key));
		}
		mServerNormalTaskCs.unlock();
		mServerNormalTaskThread.addTask(task);
	}

	//-----------------------------------------------------------------------------
	void ThreadTaskManager::freeServerNormalTask( ServerNormalTask* task )
	{
        if ( task->mNetEvent->subLocker() <= 0 )
            LoginServerMain::getInstance().freeEvent( task->mNetEvent );

		mServerNormalTaskCs.lock();
		if ( task )
			MG_POOL_DELETE( mServerNormalTaskPool, task);
		mServerNormalTaskCs.unlock();
	}

	//-----------------------------------------------------------------------------

}
//***********************************************************************************************************