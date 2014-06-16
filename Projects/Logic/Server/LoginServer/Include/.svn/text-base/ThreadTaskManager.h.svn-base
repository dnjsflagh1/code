/******************************************************************************/
#ifndef _THREADTASKMANAGER_H_
#define _THREADTASKMANAGER_H_
/******************************************************************************/
#include "ThreadTask.h"
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
	
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	public:

		void					addClientNormalTask(NetEventRecv* netEvent,I32 clientNetId,U32 key = 0);
		void					freeClientNormalTask(ClientNormalTask* task);


		void					addServerNormalTask(NetEventRecv* netEvent,I32 serverNetId,U32 key = 0);
		void					freeServerNormalTask(ServerNormalTask* task);

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	private:

		ObjectPool<ClientNormalTask,false>
												mClientNormalTaskPool;
		 Critical								mClientTaskCs;
		 ModeTaskThread							mClientNormalTaskThread;
		 
		 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		 ObjectPool<ServerNormalTask,false>     mServerNormalTaskPool;
		 Critical								mServerNormalTaskCs;
		 ModeTaskThread							mServerNormalTaskThread;

	};
}

#endif