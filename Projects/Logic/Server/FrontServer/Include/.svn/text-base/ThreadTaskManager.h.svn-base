/******************************************************************************/
#ifndef _THREADTASKMANAGER_H_
#define _THREADTASKMANAGER_H_
/******************************************************************************/

#include "FrontServerPreqs.h"
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

		/// 线程更新逻辑心跳
		static void				updateLogicHeartbeatThread(Ptr ptr);

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	public:

		void					addPrepareJoinGameTask(NetEventRecv* netEvent,U32 key = 0);
		Bool					removePrepareJoinGameTask(U32 key);
		void					freePrepareJoinGameTask(PrepareJoinGameTask* task);


		void					addCreateClanTask(NetEventRecv* netEvent,U32 key = 0);
		Bool					removeCreateClanTask(U32 key);
		void					freeCreateClanTask(CreateClanTask* task);

		void                    addDeleteClanTask(I32 clientNetId,NetEventRecv* netEvent,U32 key = 0);
		Bool					removeDeleteClanTask(U32 key);
		void					freeDeleteClanTask(DeleteClanTask* task);

		void					addCreateGeneralTask(NetEventRecv* netEvent,I32 clientNetId,U32 key = 0);
		Bool					removeCreateGeneralTask(U32 key);
		void					freeCreateGeneralTask(CreateGeneralTask* task);

		void					addJoinGameTask(NetEventRecv* netEvent,U32 key = 0);
		Bool					removeJoinGameTask(U32 key);
		void					freeJoinGameTask(JoinGameTask* task);

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	public:

		void					addServerNormalTask(NetEventRecv* netEvent,I32 serverNetId,U32 key = 0);
		void					freeServerNormalTask(ServerNormalTask* task);

        void					addServerNetTranspondSendTask(NetEventRecv* netEvent,I32 serverNetId,U32 key = 0);
        void					freeServerNetTranspondSendTask(ServerNetTranspondSendTask* task);

        void					addServerNetTranspondSaveTask(NetEventRecv* netEvent,I32 serverNetId,U32 key = 0);
        void					freeServerNetTranspondSaveTask(ServerNetTranspondSaveTask* task);

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	private:

		 ObjectPool<PrepareJoinGameTask,false>  mPrepareJoinGameTaskPool;
		 ObjectPool<CreateClanTask,false>       mCreateClanTaskPool;
		 ObjectPool<DeleteClanTask,false>       mDeleteClanTaskPool;
		 ObjectPool<CreateGeneralTask,false>    mCreateGeneralTaskPool;		
		 ObjectPool<JoinGameTask,false>         mJoinGameTaskPool;

		 Critical								mClientTaskCs;
		 ModeTaskThread							mClientTaskThread;
		 
		 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		 ObjectPool<ServerNormalTask,false>     mServerNormalTaskPool;
		 Critical								mServerNormalTaskCs;
		 ModeTaskThread							mServerNormalTaskThread;

         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

         ObjectPool<ServerNetTranspondSendTask,false>
                                                mServerNetTranspondSendTaskPool;
		 Critical								mServerNetTranspondSendTaskCs;
		 ModeTaskThread							mServerNetTranspondSendTaskThread;

         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

         ObjectPool<ServerNetTranspondSaveTask,false> 
                                                mServerNetTranspondSaveTaskPool;
         Critical								mServerNetTranspondSaveTaskCs;

        std::deque<ServerNetTranspondSaveTask*> mServerNetTranspondSaveTaskTempList;

         ModeTaskThread							mServerNetTranspondSaveTaskThread1;
         ModeTaskThread							mServerNetTranspondSaveTaskThread2;
         ModeTaskThread							mServerNetTranspondSaveTaskThread3;
         ModeTaskThread							mServerNetTranspondSaveTaskThread4;
         ModeTaskThread							mServerNetTranspondSaveTaskThread5;

         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		 /// 逻辑心跳线程
		 OneThreadHandle         mLogicHeartbeatThread;
	};
}

#endif