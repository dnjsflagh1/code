//***********************************************************************************************************
#include "stdafx.h"
#include "ThreadTaskManager.h"
#include "RobotTaskThread.h"
#include "GameNetEvent.h"
#include "ClientNetApplyManager.h"
//***********************************************************************************************************
namespace MG
{
	//-----------------------------------------------------------------------------
	ThreadTaskManager::ThreadTaskManager()
		:mThreadCount(0)
		,mIsInit(false)
	{
		
	}

	//-----------------------------------------------------------------------------
	ThreadTaskManager::~ThreadTaskManager()
	{
		
	}

	//-----------------------------------------------------------------------------
	Bool ThreadTaskManager::initialize(U32 threadCount)
	{
		mThreadClientVec.clear();
		mTaskThread = MG_NEW RobotTaskThread[threadCount];
		mThreadCount = threadCount;
		for (Int i = 0; i < threadCount; i++)
		{
			mTaskThread[i].setManager(this,i);
			if (!mTaskThread[i].create(&mTaskThread[i],0))
			{
				return false;
			}
			std::vector<CClient*>* clients = MG_NEW std::vector<CClient*>();
			mThreadClientVec.push_back(clients);
		}
		
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

		// 再将 线程使用数据 清空
		for (std::vector<std::vector<CClient*>*> ::iterator it = mThreadClientVec.begin(); it != mThreadClientVec.end(); it++)
		{
			MG_SAFE_DELETE(*it);
		}
		mThreadClientVec.clear();

		// 再回收内存
		for (std::map<I32,CClient*>::iterator it = mClientMap.begin(); it != mClientMap.end(); it++)
		{
			if (it->second)
			{
				MG_POOL_DELETE(mClientPool,it->second);
			}
		}
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
			mTaskThread[client->getThreadIndex()].addTask(task);
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
		mClientMap[index] = client;
		mThreadClientVec[threadIndex]->push_back(client);
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
		if (threadIndex >= mThreadCount )
		{
			return NULL;
		}
		return mThreadClientVec[threadIndex];
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
		
		mClientLoginMapCs.lock();
		client->setLoginServerNetId(netId);
		mClientLoginMap[netId] = client;
		mClientLoginMapCs.unlock();
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
		mClientFrontMapCs.lock();
		client->setFrontServerNetId(netId);
		mClientFrontMap[netId] = client;
		mClientFrontMapCs.unlock();
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
	Bool ThreadTaskManager::isInit()
	{
		return mIsInit;
	}

	//-----------------------------------------------------------------------------
}
//***********************************************************************************************************