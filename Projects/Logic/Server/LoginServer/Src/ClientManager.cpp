/******************************************************************************/
#include "stdafx.h"
#include "ClientManager.h"
#include "LoginNetPacket.h"
#include "ServerManager.h"
#include "PlayerCharacterDB.h"
#include "LoginNetPacketProcesser.h"
#include "LoginServerMain.h"
#include "LoginManager.h"
#include "LineUpNetPacketProcesser.h"
/******************************************************************************/
namespace MG
{

	//-----------------------------------------------------------------------
	ClientManager::ClientManager()
	{
	}
	
	//-----------------------------------------------------------------------
	ClientManager::~ClientManager()
	{
	}
	
	//-----------------------------------------------------------------------
	Bool ClientManager::initialize()
	{
		if ( mCheckTimeOutThread.create( checkTimeOutThread,this ) == false )
		{
			return false;
		}
#ifdef _DEBUG
		Thread::SetThreadName(mCheckTimeOutThread.getThreadId(),"ClientManager::mCheckTimeOutThread");
#endif
		return true;
	}

	//-----------------------------------------------------------------------
	void ClientManager::uninitialize()
	{
		mCheckTimeOutThread.destory();
	}

	//-----------------------------------------------------------------------
	void ClientManager::update()
	{
		
	}	

	//-----------------------------------------------------------------------
	void ClientManager::checkTimeOutThread(Ptr ptr)
	{
		OneThreadHandle* thd = (OneThreadHandle* )ptr;
		if (thd && thd->getParam())
		{
			ClientManager* mgr = (ClientManager *)thd->getParam();
			if (mgr)
			{
				while( thd->isRun() )
				{
					U32 currTime = MGTimeOp::getCurrTick();
					ClientObject* clientObject = mgr->getClientObjectFromQueue();
					if (clientObject)
					{
						if(clientObject->isDisConnected)
						{
							
							//if (currTime - clientObject->disConnectTime >= MAX_CLIENT_TIMEOUT_AFTER_DISCONNECTED)
							{
								//LoginManager::getInstance().removeLogingPlayerByNetId(clientObject->netId);
								mgr->destoryClientObject(clientObject);
							}
							
						}
						else
						{
							//如果大于20分钟则断开连接
							if (currTime - clientObject->connectTime > MAX_CONNECT_TIME_OUT)
							{
								LoginServerMain::getInstance().getServerLauncher()->closeClient(clientObject->netId);
								mgr->removeClientObjectFromMap(clientObject->netId);
								LoginManager::getInstance().removeLoginedPlayerByNetId(clientObject->netId);
								LoginManager::getInstance().removeLogingPlayerByNetId(clientObject->netId);
							}
							else
							{
								mgr->addClientObjectToQueue(clientObject);
							}
						}

					}
					Sleep(5);	
				}
			}
		}
	}
	//-----------------------------------------------------------------------
	void ClientManager::onConnected(I32 id,NetAddress*address)
	{

		if (LoginManager::getInstance().getAllLoginCount() > LoginManager::getInstance().getMaxWaitCount())
		{
			LineUpNetPacketProcesser::getInstance().sendLineUpInfoToClient(id,line_up_busy_lc_server_full);
			LoginServerMain::getInstance().getServerLauncher()->closeClient(id);
			return;
		}
		
		ClientObject* clientObj = getClientFromMap(id);
		if (clientObj)
		{
			DYNAMIC_ASSERT(false);
			clientObj->revert(address->getUin(),*address);
		}
		else
		{
			clientObj = createClientObject(id,address->getUin(),*address);
			addClientObjectToMap(id,clientObj);
			addClientObjectToQueue(clientObj);
		}
	}

	//-----------------------------------------------------------------------
	void ClientManager::onDisconnect(I32 id)
	{
		removeClientObjectFromMap(id);
	}

	//-----------------------------------------------------------------------
	Bool ClientManager::processPacket(I32 id, NetEventRecv* packet)
	{
		DYNAMIC_ASSERT(packet);
		if (!packet)
		{
			return false;
		}

		if ( LoginNetPacketProcesser::getInstance().processClientPacket( id, packet ) == true )
			return true;
		if ( LineUpNetPacketProcesser::getInstance().processClientPacket(id,packet) == true)
			return true;
		
		return false;
	}
	//-----------------------------------------------------------------------
	ClientObject* ClientManager::createClientObject( I32 netId,U64 uin,NetAddress& address )
	{
		mClientObjectPool.threadLock();
		ClientObject* clientObject = MG_POOL_NEW(mClientObjectPool,ClientObject,(netId,netId,address));
		mClientObjectPool.threadUnLock();
		DYNAMIC_ASSERT(clientObject);
		return clientObject;
	}
	//-----------------------------------------------------------------------
	void ClientManager::destoryClientObject( ClientObject* clientObj )
	{
		DYNAMIC_ASSERT(clientObj);
		mClientObjectPool.threadLock();
		MG_POOL_DELETE(mClientObjectPool,clientObj);
		mClientObjectPool.threadUnLock();
	}
	//-----------------------------------------------------------------------
	void ClientManager::addClientObjectToMap( I32 netId, ClientObject* clientObj )
	{	
		DYNAMIC_ASSERT(clientObj);
		mClientObjectListLock.lock();
			mClientObjectList[netId] = clientObj;
		mClientObjectListLock.unlock();
	}
	//-----------------------------------------------------------------------
	ClientObject* ClientManager::getClientFromMap( I32 netId )
	{
		ClientObject* clientObject = NULL;
		mClientObjectListLock.lock();
		std::map<I32, ClientObject*>::iterator iter = mClientObjectList.find(netId);
		if ( iter != mClientObjectList.end() )
		{
			clientObject = iter->second;
		}
		mClientObjectListLock.unlock();
		return clientObject;
	}
	//-----------------------------------------------------------------------
	void ClientManager::removeClientObjectFromMap( I32 netId )
	{
		ClientObject* clientObject = NULL;
		mClientObjectListLock.lock();
		std::map<I32, ClientObject*>::iterator iter = mClientObjectList.find(netId);
		if ( iter != mClientObjectList.end() )
		{
			clientObject = iter->second;
			if (clientObject)
			{
				mClientObjectList.erase(iter);
				mClientObjectListLock.unlock();
				clientObject->disConnected();
			}
			else
			{
				DYNAMIC_ASSERT(false);
				mClientObjectListLock.unlock();
			}
		}
		else
		{
			DYNAMIC_ASSERT(false);
			mClientObjectListLock.unlock();
		}
	}
	//-----------------------------------------------------------------------
	void ClientManager::addClientObjectToQueue( ClientObject* clientObj )
	{
		DYNAMIC_ASSERT(clientObj);
		mClientObjectQueueLock.lock();
		mClientObjectQueue.push(clientObj);
		mClientObjectQueueLock.unlock();
	}
	//-----------------------------------------------------------------------
	ClientObject* ClientManager::getClientObjectFromQueue()
	{
		ClientObject* clientObj = NULL;
		mClientObjectQueueLock.lock();
		if (!mClientObjectQueue.empty())
		{
			clientObj = mClientObjectQueue.front();
			mClientObjectQueue.pop();
		}
		mClientObjectQueueLock.unlock();
		return clientObj;

	}
	//-----------------------------------------------------------------------


}
