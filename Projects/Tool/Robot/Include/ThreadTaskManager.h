/******************************************************************************/
#ifndef _THREADTASKMANAGER_H_
#define _THREADTASKMANAGER_H_
/******************************************************************************/
#include "ThreadTask.h"
#include "CClientNew.h"
#include "UIOperateManager.h"
/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//线程任务管理器
	/******************************************************************************/
	class RobotTaskThread;
	class ThreadTaskManager
	{
		typedef I32 loginNetId;
		typedef I32 frontNetId;
		typedef I32	indexType;
		friend class RobotTaskThread;
	public:		

		ThreadTaskManager();
		~ThreadTaskManager();
		SINGLETON_INSTANCE(ThreadTaskManager);

	public:
		// 初始化 反初始化
		virtual Bool			initialize(U32 threadCount);
		virtual Bool			unInitialize();
		
		Bool					isInit();
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	public:
		// net
		void					addRobotNetTask(CClient* client,INetEvent* netEvent,U32 key = 0);
		void					freeRobotNetTask(RobotNetTask* task);
		
	public:
		// client
		void					createClient(I32 index,  Char* service,Char16* accountName,Char16* password,I32 nClan,U32 threadIndex);
		std::map<I32,CClient*>*	getClientMap();
		CClient*				getClientByFrontServerNetId(frontNetId netId);
		CClient*				getClientByLoginServerNetId(loginNetId netId);
		std::vector<CClient*>*	getThreadClientVec(Int threadIndex);

		void					addLoginClient(loginNetId netId,CClient* client);
		void					removeLoginClient(loginNetId netId);
		void					addFrontClient(frontNetId netId,CClient* client);
		void					removeFrontClient(frontNetId netId);
		
		// thread
		void					prepareThread();
		RobotTaskThread*		getThread(Int threadIndex);
		
		void					lockLoginClients();
		void					unlockLoginClients();
		void					lockFrontClients();
		void					unlockFrontClients();
		
		void					resetCampaign();
		Bool					preassignmentCampaginList(I32 campaginNum,I32 generalNum,U32 time = 0);
		void					getCampListFromServer();
		void					startCampaign();

		Bool					isCampaignSet();
		// test
		//void					update();
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	private:
		 ObjectPool<RobotNetTask,false>			mRobotNetTaskPool;
		 ObjectPool<CClient>					mClientPool;
		
		 // 线程
		 RobotTaskThread*						mTaskThread;
		 U32									mThreadCount;
		
#ifdef TEST_THREAD_USE
		 //test
		 CClient***								mThreadClients;
		 Int*									mClientCount;
#else
		  std::vector<std::vector<CClient*>*>	mThreadClientVec;
#endif // TEST_THREAD_USE

		 // I32 序列索引 
		 std::map<I32,CClient*>					mClientMap;
		 Critical								mClientMapLock;
		 
		 // 网络Id 供外部查询 线程间要同步 
		 std::map<loginNetId,CClient*>			mClientLoginMap;
		 Critical								mClientLoginMapCs;
		 std::map<frontNetId,CClient*>			mClientFrontMap;
		 Critical								mClientFrontMapCs;

		 Bool									mIsInit;

		 Bool									mIsCampaignSet;
	};
}

#endif