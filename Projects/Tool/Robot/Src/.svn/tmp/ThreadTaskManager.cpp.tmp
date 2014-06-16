//***********************************************************************************************************
#include "stdafx.h"
#include "ThreadTaskManager.h"
#include "RobotTaskThread.h"
#include "GameNetEvent.h"
#include "ClientNetApplyManager.h"
#include "CCampaignManagerNew.h"
//***********************************************************************************************************
namespace MG
{
	//-----------------------------------------------------------------------------
	ThreadTaskManager::ThreadTaskManager()
		:mThreadCount(0)
		,mIsInit(false)
		,mIsCampaignSet(false)
	{
		
	}

	//-----------------------------------------------------------------------------
	ThreadTaskManager::~ThreadTaskManager()
	{
		unInitialize();
	}

	//-----------------------------------------------------------------------------
	Bool ThreadTaskManager::initialize(U32 threadCount)
	{
		
		mTaskThread = MG_NEW RobotTaskThread[threadCount];
		mThreadCount = threadCount;

		

#ifdef TEST_THREAD_USE
		//----------------------------------------------------
		mThreadClients = MG_NEW CClient**[threadCount];
		mClientCount = MG_NEW Int[threadCount];
		for (Int i = 0; i < threadCount; i++)
		{
			mTaskThread[i].setManager(this,i);
			if (!mTaskThread[i].create(&mTaskThread[i],"ThreadTaskManager::mTaskThread[]",0))
			{
				return false;
			}
			Char8 threadName[256] = {0};
			MGStrOp::sprintf(threadName,256,"RobotTaskThread%d",i);
			MG::Thread::SetThreadName(mTaskThread[i].getThreadId(),threadName);

			mThreadClients[i] = NULL;
			mClientCount[i] = 0;

		}
		//----------------------------------------------------
#else
		mThreadClientVec.clear();
		for (Int i = 0; i < threadCount; i++)
		{

			mTaskThread[i].setManager(this,i);
			if (!mTaskThread[i].create(&mTaskThread[i],"ThreadTaskManager::mTaskThread[]",0))
			{
				return false;
			}
			Char8 threadName[256] = {0};
			MGStrOp::sprintf(threadName,256,"RobotTaskThread%d",i);
			MG::Thread::SetThreadName(mTaskThread[i].getThreadId(),threadName);
			std::vector<CClient*>* clients = MG_NEW std::vector<CClient*>();
			mThreadClientVec.push_back(clients);

		}	
#endif 

		return true;
	}

	//-----------------------------------------------------------------------------
	Bool ThreadTaskManager::unInitialize()
	{
		
		// 先销毁线程
		for (Int i = 0; i < mThreadCount; i++)
		{	
			mTaskThread[i].destory();
		}
		MG_SAFE_DELETE_ARRAY(mTaskThread);
		mThreadCount = 0;
#ifdef TEST_THREAD_USE
		for(Int i = 0; i < mThreadCount; i++)
		{
			for (Int j = 0; j < mClientCount[i]; j++)
			{
				mThreadClients[i][j] = NULL;
			}
			MG_SAFE_DELETE_ARRAY(mThreadClients[i]);
		}
		MG_SAFE_DELETE_ARRAY(mThreadClients);
#else
		// 再将 线程使用数据 清空
		for (std::vector<std::vector<CClient*>*> ::iterator it = mThreadClientVec.begin(); it != mThreadClientVec.end(); it++)
		{
			MG_SAFE_DELETE(*it);
		}
		mThreadClientVec.clear();
#endif
		

		// 再回收内存
		for (std::map<I32,CClient*>::iterator it = mClientMap.begin(); it != mClientMap.end(); it++)
		{
			if (it->second)
			{
				MG_POOL_DELETE(mClientPool,it->second);
			}
		}
		mClientMap.clear();
		return true;
	}
	//-----------------------------------------------------------------------------
	void ThreadTaskManager::addRobotNetTask( CClient* client,INetEvent* netEvent,U32 key /*= 0*/ )
	{
		if (mTaskThread 
			&& client
			&& client->getThreadIndex() > -1 
			&& client->getThreadIndex() < mThreadCount)
		{	
			netEvent->addLocker();
			mRobotNetTaskPool.threadLock();
			RobotNetTask* task  
				= MG_POOL_NEW_ONCE_CONSTRUCTION(mRobotNetTaskPool,RobotNetTask,());
			mRobotNetTaskPool.threadUnLock();
			if (!task)
			{
				DYNAMIC_ASSERT(false);
				return;
			}
			task->reset(netEvent,client,key);
			client->setTaskNumber();
			task->setNumber(client->getTaskNumber());
			I32 taskCount = mTaskThread[client->getThreadIndex()].addTask(task);
			//MG_LOG(out_debug,"添加任务的数量 ===== %d\n",taskCount);
		}
		else
		{
			DYNAMIC_ASSERT(false);
		}
	}
	//-----------------------------------------------------------------------------
	void ThreadTaskManager::freeRobotNetTask( RobotNetTask* task )
	{
		if ( task )
		{
			if ( task->mNetEvent->subLocker() <= 0 )
				ClientNetApplyManager::getInstance().freeEvent( task->mNetEvent);

			mRobotNetTaskPool.threadLock();
			MG_POOL_DELETE_ONCE_DESTRUCTOR( mRobotNetTaskPool, task);
			mRobotNetTaskPool.threadUnLock();
		}
	}
	//----------------------------------------------------------------------------- 
	void ThreadTaskManager::createClient( I32 index, Char* service,Char16* accountName,Char16* password,I32 nClan,U32 threadIndex )
	{
		
		CClient* client = MG_POOL_NEW(mClientPool,CClient,(index, service,accountName, password,nClan,threadIndex));
		client->setThreadIndex(threadIndex);
#ifdef TEST_THREAD_USE
		//-------------------------------------------------------
		static I32 tempIndex = -1;
		if (threadIndex != tempIndex)
		{
			tempIndex = threadIndex;
			mThreadClients[threadIndex] = MG_NEW CClient*[MAX_CLIENT_COUNT_PRE_THREAD];
			for (Int i = 0; i < MAX_CLIENT_COUNT_PRE_THREAD; i++)
			{
				mThreadClients[threadIndex][i] = NULL;
			}
		}
		mThreadClients[threadIndex][mClientCount[tempIndex]++] = client;
		//-------------------------------------------------------
#else
		mThreadClientVec[threadIndex]->push_back(client);
#endif

		mClientMap[index] = client;
	}
	//-----------------------------------------------------------------------------
	std::map<I32,CClient*>* ThreadTaskManager::getClientMap()
	{
		return &mClientMap;
	}
	//-----------------------------------------------------------------------------
	CClient* ThreadTaskManager::getClientByFrontServerNetId( frontNetId netId )
	{
		mClientFrontMapCs.lock();
		std::map<frontNetId,CClient*>::iterator it = mClientFrontMap.find(netId);
		if (it != mClientFrontMap.end())
		{
			mClientFrontMapCs.unlock();
			return it->second;
		}
		mClientFrontMapCs.unlock();
		return NULL;
	}
	//-----------------------------------------------------------------------------
	CClient* ThreadTaskManager::getClientByLoginServerNetId( loginNetId netId )
	{
		mClientLoginMapCs.lock();
		std::map<loginNetId,CClient*>::iterator it = mClientLoginMap.find(netId);
		if (it != mClientLoginMap.end())
		{
			mClientLoginMapCs.unlock();
			return it->second;
		}
		mClientLoginMapCs.unlock();
		return NULL;
	}
	//-----------------------------------------------------------------------------
	std::vector<CClient*>* ThreadTaskManager::getThreadClientVec( Int threadIndex )
	{
#ifdef TEST_THREAD_USE
		return NULL;
#else
		if (threadIndex >= mThreadCount )
		{
			return NULL;
		}
		return mThreadClientVec[threadIndex];
#endif
	}
	//-----------------------------------------------------------------------------
	void ThreadTaskManager::addLoginClient( loginNetId netId,CClient* client )
	{
		if (!client)
		{
			return;
		}
		CClient* tempClient = getClientByLoginServerNetId(netId);
		if (tempClient)
		{
			// 出错：
			DYNAMIC_ASSERT(false);
		}
		
		//此锁需要扩大范围
		//mClientLoginMapCs.lock();
		client->setLoginServerNetId(netId);
		mClientLoginMap[netId] = client;
		//mClientLoginMapCs.unlock();
	}
	//-----------------------------------------------------------------------------
	void ThreadTaskManager::removeLoginClient( loginNetId netId )
	{
		mClientLoginMapCs.lock();
		std::map<loginNetId,CClient*>::iterator it = mClientLoginMap.find(netId);
		if (it != mClientLoginMap.end())
		{
			mClientLoginMap.erase(it);
		}
		mClientLoginMapCs.unlock();
	}
	//-----------------------------------------------------------------------------
	void ThreadTaskManager::addFrontClient( frontNetId netId,CClient* client )
	{
		if (!client)
		{
			return;
		}
		CClient* tempClient = getClientByFrontServerNetId(netId);
		if (tempClient)
		{
			// 出错：
			DYNAMIC_ASSERT(false);
		}
		//mClientFrontMapCs.lock();
		client->setFrontServerNetId(netId);
		mClientFrontMap[netId] = client;
		//mClientFrontMapCs.unlock();
	}
	//-----------------------------------------------------------------------------
	void ThreadTaskManager::removeFrontClient( frontNetId netId )
	{
		mClientFrontMapCs.lock();
		std::map<loginNetId,CClient*>::iterator it = mClientFrontMap.find(netId);
		if (it != mClientFrontMap.end())
		{
			mClientFrontMap.erase(it);
		}
		mClientFrontMapCs.unlock();
	}
	//-----------------------------------------------------------------------------
	void ThreadTaskManager::prepareThread( )
	{
		for (Int i = 0; i < mThreadCount; i++)
		{
			mTaskThread[i].prepare();
		}
		mIsInit = true;
	}
	//-----------------------------------------------------------------------------
	RobotTaskThread* ThreadTaskManager::getThread( Int threadIndex )
	{
		if (threadIndex > mThreadCount)
		{
			return NULL;
		}
		if (!mTaskThread)
		{
			return NULL;
		}
		return &mTaskThread[threadIndex];
	}
	//-----------------------------------------------------------------------------
	void ThreadTaskManager::lockLoginClients()
	{
		mClientLoginMapCs.lock();
	}
	//-----------------------------------------------------------------------------
	void ThreadTaskManager::unlockLoginClients()
	{
		mClientLoginMapCs.unlock();
	}
	//-----------------------------------------------------------------------------
	void ThreadTaskManager::lockFrontClients()
	{
		mClientFrontMapCs.lock();
	}
	//-----------------------------------------------------------------------------
	void ThreadTaskManager::unlockFrontClients()
	{
		mClientFrontMapCs.unlock();
	}
	//-----------------------------------------------------------------------------
	Bool ThreadTaskManager::isInit()
	{
		return mIsInit;
	}
	//-----------------------------------------------------------------------------
	Bool ThreadTaskManager::preassignmentCampaginList( I32 campaignNum,I32 generalNum, U32 time)
	{
		// 预分配战场
		// 预分配战场 以及预分配玩家
		if (mClientFrontMap.empty())
		{
			MessageOut("请先登录");
			return false;
		}
		if (campaignNum <= 0 
			|| generalNum > 10
			|| mClientFrontMap.size() < generalNum)
		{
			return false;
		}
		
		Int remainCampaignNum = campaignNum;
		for (Int i = 0; i < mThreadCount; i++)
		{
			remainCampaignNum = mTaskThread[i].preassignmentCampaginList(remainCampaignNum,generalNum,time);
			if (remainCampaignNum <= 0)
			{
				break;
			}
		}
		if (remainCampaignNum == campaignNum)
		{
			return false;
		}
		mIsCampaignSet = true;
		return true;
	}
	//-----------------------------------------------------------------------------
	void ThreadTaskManager::getCampListFromServer()
	{
		for (Int i = 0; i < mThreadCount; i++)
		{
			mTaskThread[i].getCampaignMgr()->getCampaignListFromServer();
		}
	}
	//-----------------------------------------------------------------------------
	void ThreadTaskManager::resetCampaign()
	{
		for (Int i = 0; i < mThreadCount; i++)
		{
			mTaskThread[i].getCampaignMgr()->clear();
		}
	}
	//-----------------------------------------------------------------------------
	void ThreadTaskManager::startCampaign()
	{
		if (!mIsCampaignSet)
		{
			MG::MessageOut("未设置战场");
			return;
		}
		
		
		for (Int i = 0; i < mThreadCount; i++)
		{
			mTaskThread[i].getCampaignMgr()->createCampaignRoomListToServer();
		}
		//
	}

	Bool ThreadTaskManager::isCampaignSet()
	{
		return mIsCampaignSet;	
	}
	
	//-----------------------------------------------------------------------------
}
//***********************************************************************************************************