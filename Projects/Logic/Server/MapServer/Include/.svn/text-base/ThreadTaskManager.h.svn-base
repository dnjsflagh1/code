/******************************************************************************/
#ifndef _THREADTASKMANAGER_H_
#define _THREADTASKMANAGER_H_
/******************************************************************************/
#include "MapServerPreqs.h"
#include "JumpRegionTask.h"
#include "Thread.h"
/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//线程任务管理器
	/******************************************************************************/
	class ThreadTaskManager
	{
	public:		
		ThreadTaskManager();
		~ThreadTaskManager();
		SINGLETON_INSTANCE(ThreadTaskManager);

	public:

		virtual Bool			initialize();
		virtual Bool			unInitialize();
	
	public:

		void					addJumpRegionTask(NetEventRecv* netEvent,U32 key);
		void					freeJumpRegionTask(JumpRegionTask* task);

	private:

		 ObjectPool<JumpRegionTask, false>      mJumpRegionTaskPool;
		 Critical								mServerTaskCs;
		 ModeTaskThread							mServerTaskThread;
	};

}

#endif