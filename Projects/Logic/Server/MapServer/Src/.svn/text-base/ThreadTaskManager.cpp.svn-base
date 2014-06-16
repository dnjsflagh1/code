//***********************************************************************************************************
#include "stdafx.h"
#include "ThreadTaskManager.h"
#include "MapServerMain.h"
//***********************************************************************************************************
namespace MG
{
    //-----------------------------------------------------------------------
	ThreadTaskManager::ThreadTaskManager()
	{
		
	}

    //-----------------------------------------------------------------------
	ThreadTaskManager::~ThreadTaskManager()
	{

	}

    //-----------------------------------------------------------------------
	Bool ThreadTaskManager::initialize()
	{
#ifdef MULTI_THREAD
		if (false == mServerTaskThread.create(&mServerTaskThread,102400))
		{
			DYNAMIC_ASSERT(0);
			return false;
		}
#ifdef _DEBUG
		Thread::SetThreadName(mClientNormalTaskThread.getThreadId(),"ThreadTaskManager::mServerTaskThread");
#endif
#endif
		return true;
		
	}

    //-----------------------------------------------------------------------
	Bool ThreadTaskManager::unInitialize()
	{
		mServerTaskThread.destory();
		return true;
	}

    //-----------------------------------------------------------------------
	void ThreadTaskManager::addJumpRegionTask( NetEventRecv* netEvent,U32 key)
	{
		netEvent->addLocker();

		JumpRegionTask* task = NULL;
		mServerTaskCs.lock();
		{
			task = MG_POOL_NEW(mJumpRegionTaskPool,JumpRegionTask,(netEvent,key, key));
		}
		mServerTaskCs.unlock();

		mServerTaskThread.addTask(task);
	}

    //-----------------------------------------------------------------------
	void ThreadTaskManager::freeJumpRegionTask( JumpRegionTask* task )
	{
        if ( task->mNetEvent->subLocker() <= 0 )
            MapServerMain::getInstance().freeEvent( task->mNetEvent );

		mServerTaskCs.lock();
		if ( task )
			MG_POOL_DELETE( mJumpRegionTaskPool, task);
		mServerTaskCs.unlock();
	}

}
//***********************************************************************************************************