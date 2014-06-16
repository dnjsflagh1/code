/******************************************************************************/
#include "stdafx.h"
#include "Win32IocpNetUdpData.h"
#include "GameNetUdpPacketManager.h"
/******************************************************************************/

namespace MG
{

	//-----------------------------------------------------------------------------
	GameNetUdpPacketManager::GameNetUdpPacketManager()
	{

	}

	//-----------------------------------------------------------------------------
	GameNetUdpPacketManager::~GameNetUdpPacketManager()
	{

	}
	//-----------------------------------------------------------------------------
	Bool GameNetUdpPacketManager::initialize(U16 sectionPacketSize)
	{
		return NetUdpManager::initialize(sectionPacketSize);
	}
	//-----------------------------------------------------------------------------
	I32 GameNetUdpPacketManager::unInitialize()
	{
		return -1;
	}  
	//-----------------------------------------------------------------------------
	void GameNetUdpPacketManager::addUdpAcceptEvent(I32 handle,I32 id,U32 logicId,NetAddress&address)
	{
		NetUdpEventAccept* event = NULL;
		mNetEventsPoolCs.lock();
		{
			event = MG_POOL_NEW(mNetUdpEventAcceptPool,NetUdpEventAccept,(handle,id,address));
		}
		mNetEventsPoolCs.unlock();

		mNetEventsPreparedListCs.lock();
		{
			INetUdpEvent* tempEvent;
			NetEventsList& events = mNetEventsMap[handle];
			std::map<U32,INetUdpEvent*>::iterator it = events[id].preparedEventsList.find(logicId);
			if (it != events[id].preparedEventsList.end())
			{
				DYNAMIC_ASSERT(false);
				tempEvent = it->second; 
				events[id].preparedEventsList[logicId] = event;
				mNetEventsPreparedListCs.unlock();
				freeEvent(tempEvent);
				return;
			}

			events[id].preparedEventsList[logicId] = event;
		}
		mNetEventsPreparedListCs.unlock();
	}
	//-----------------------------------------------------------------------------
	void GameNetUdpPacketManager::addUdpConnectEvent(I32 handle,I32 id,U32 logicId,NetAddress&address)
	{
		NetUdpEventConnect* event = NULL;
		mNetEventsPoolCs.lock();
		{
			event = MG_POOL_NEW(mNetUdpEventConnectPool,NetUdpEventConnect,(handle,id,address));
		}
		mNetEventsPoolCs.unlock();

		mNetEventsPreparedListCs.lock();
		{
			INetUdpEvent* tempEvent;
			NetEventsList& events = mNetEventsMap[handle];
			std::map<U32,INetUdpEvent*>::iterator it = events[id].preparedEventsList.find(logicId);
			if (it != events[id].preparedEventsList.end())
			{
				DYNAMIC_ASSERT(false);
				tempEvent = it->second; 
				events[id].preparedEventsList[logicId] = event;
				mNetEventsPreparedListCs.unlock();
				freeEvent(tempEvent);
				return;
			}

			events[id].preparedEventsList[logicId] = event;
		}
		mNetEventsPreparedListCs.unlock();
	}
	//-----------------------------------------------------------------------------
	void GameNetUdpPacketManager::addUdpCloseEvent(I32 handle,I32 id,U32 logicId,Bool isPassivity,NetAddress&address)
	{
		NetUdpEventClose* event = NULL;
		mNetEventsPoolCs.lock();
		{
			event = MG_POOL_NEW(mNetUdpEventClosePool,NetUdpEventClose,(handle,id,isPassivity,address));
		}
		mNetEventsPoolCs.unlock();

		mNetEventsPreparedListCs.lock();
		{
			INetUdpEvent* tempEvent;
			NetEventsList& events = mNetEventsMap[handle];
			std::map<U32,INetUdpEvent*>::iterator it = events[id].preparedEventsList.find(logicId);
			if (it != events[id].preparedEventsList.end())
			{
				DYNAMIC_ASSERT(false);
				tempEvent = it->second; 
				events[id].preparedEventsList[logicId] = event;
				mNetEventsPreparedListCs.unlock();
				freeEvent(tempEvent);
				return;
			}

			events[id].preparedEventsList[logicId] = event;
		}
		mNetEventsPreparedListCs.unlock();
	}
	//-----------------------------------------------------------------------------
	NetUdpEventRecv* GameNetUdpPacketManager::createNetUdpEventRecv( I32 id, U16 sectionPacketSize,U32 sectionCount )
	{
		// 如果小于默认值, 则分配缓存等于默认值

			// 获得对应缓存大小的对象池
			ObjectPool<NetUdpEventRecv>& objPool = mNetEventNormalRecvPools[ sectionPacketSize * sectionCount ];

			// 分配一个对象
			NetUdpEventRecv* object = NULL;

			mNetEventsPoolCs.lock();
			{
				object = MG_POOL_NEW_ONCE_CONSTRUCTION(objPool,NetUdpEventRecv,(id,sectionPacketSize,sectionCount));
			}
			mNetEventsPoolCs.unlock();

			// 清空属性
			object->clear();

			return object;
	}
	//-----------------------------------------------------------------------------
	void GameNetUdpPacketManager::destoryNetUdpEventRecv( NetUdpEventRecv* recvEvent )
	{
		ObjectPool<NetUdpEventRecv>& objPool = mNetEventNormalRecvPools[ recvEvent->getBuffMaxSize()];
		mNetEventsPoolCs.lock();
		{
			MG_POOL_DELETE_ONCE_DESTRUCTOR(objPool,recvEvent);
		}
		mNetEventsPoolCs.unlock();
	}
	//-----------------------------------------------------------------------------
	void GameNetUdpPacketManager::addUdpRecvEvent(I32 handle,I32 id,U32 logicId,IocpNetUdpSectionPacket* packet)
	{
		NetUdpEventRecv* event = NULL;
		NetEventsList& events = mNetEventsMap[handle];
		mNetEventsPreparingListCs.lock();
		std::map<U32,INetUdpEvent*>::iterator it = events[id].preparingEventsList.find(logicId);
		if (it != events[id].preparingEventsList.end())
		{
			event = dynamic_cast<NetUdpEventRecv*>(it->second);
			DYNAMIC_ASSERT(event);
			event->copyData(packet->sectionIndex,packet->data,packet->dataLen);
			if (event->isFinished())
			{
				events[id].preparingEventsList.erase(it);
				mNetEventsPreparingListCs.unlock();

				mNetEventsPreparedListCs.lock();
				events[id].preparedEventsList[logicId] = event;
				mNetEventsPreparedListCs.unlock();
				return;
			}
			mNetEventsPreparingListCs.unlock();
		}
		else
		{
			event = createNetUdpEventRecv(id,getSectionPacketSize(),packet->sectionCount);
			event->copyData(packet->sectionIndex,packet->data,packet->dataLen);
			event->setPacketHead(packet->channel,packet->type);

			if (event->isFinished())
			{
				mNetEventsPreparingListCs.unlock();
				mNetEventsPreparedListCs.lock();
				events[id].preparedEventsList[logicId] = event;
				mNetEventsPreparedListCs.unlock();
			}
			else
			{
				events[id].preparingEventsList[logicId] = event;
				mNetEventsPreparingListCs.unlock();
			}
		}

	}
	//-----------------------------------------------------------------------------
	void GameNetUdpPacketManager::addUdpErrEvent(I32 handle,I32 id,U32 logicId)
	{
		NetUdpEventErr* event = NULL;
		mNetEventsPoolCs.lock();
		{
			event = MG_POOL_NEW(mNetUdpEventErrPool,NetUdpEventErr,(handle,id));
		}
		mNetEventsPoolCs.unlock();

		mNetEventsPreparedListCs.lock();
		{
			INetUdpEvent* tempEvent;
			NetEventsList& events = mNetEventsMap[handle];
			std::map<U32,INetUdpEvent*>::iterator it = events[id].preparedEventsList.find(logicId);
			if (it != events[id].preparedEventsList.end())
			{
				DYNAMIC_ASSERT(false);
				tempEvent = it->second; 
				events[id].preparedEventsList[logicId] = event;
				mNetEventsPreparedListCs.unlock();
				freeEvent(tempEvent);
				return;
			}

			events[id].preparedEventsList[logicId] = event;
		}
		mNetEventsPreparedListCs.unlock();
	}
	//-----------------------------------------------------------------------------
	void GameNetUdpPacketManager::freeEvent(INetUdpEvent* netEvent)
	{
		if ( netEvent )
		{
			mNetEventsPoolCs.lock();
			{
				if (netEvent->getType() == NET_RECV)
				{
					NetUdpEventRecv* netUdpEventRecv = dynamic_cast<NetUdpEventRecv*>(netEvent);
					DYNAMIC_ASSERT( netUdpEventRecv );
					if ( netUdpEventRecv )
					{
						netUdpEventRecv->unInit();
						ObjectPool<NetUdpEventRecv>& ObjPool = mNetEventNormalRecvPools[netUdpEventRecv->getBuffMaxSize()];
						MG_POOL_DELETE_ONCE_DESTRUCTOR( ObjPool, netUdpEventRecv);
					}
				}
				else 
					if (netEvent->getType() == NET_ACCEPT)
					{
						NetUdpEventAccept* netUdpEventAccept = dynamic_cast<NetUdpEventAccept*>(netEvent);
						DYNAMIC_ASSERT( netUdpEventAccept );
						if ( netUdpEventAccept )
							MG_POOL_DELETE( mNetUdpEventAcceptPool, netUdpEventAccept);
					}
					else 
						if (netEvent->getType() == NET_CONNECT)
						{
							NetUdpEventConnect* netUdpEventConnect = dynamic_cast<NetUdpEventConnect*>(netEvent);
							DYNAMIC_ASSERT( netUdpEventConnect );
							if ( netUdpEventConnect )
								MG_POOL_DELETE( mNetUdpEventConnectPool, netUdpEventConnect);
						}
						else
							if (netEvent->getType() == NET_CLOSE)
							{
								NetUdpEventClose* netUdpEventClose = dynamic_cast<NetUdpEventClose*>(netEvent);
								DYNAMIC_ASSERT( netUdpEventClose );
								if ( netUdpEventClose )
									MG_POOL_DELETE( mNetUdpEventClosePool, netUdpEventClose);
							}
							else
								if (netEvent->getType() == NET_ERR)
								{
									NetUdpEventErr* netUdpEventError = dynamic_cast<NetUdpEventErr*>(netEvent);
									DYNAMIC_ASSERT( netUdpEventError );
									if ( netUdpEventError )
										MG_POOL_DELETE( mNetUdpEventErrPool, netUdpEventError);
								}else
								{
									DYNAMIC_ASSERT(0);
								}
			}
			mNetEventsPoolCs.unlock();
		}
	}

	//-----------------------------------------------------------------------------
	void GameNetUdpPacketManager::setOnceHandlePacketCountByDriver(I32 handle,I32 onceHandlePacketCount)
	{
		mOnceHandlePacketCount[handle] = onceHandlePacketCount;
	}

	//-----------------------------------------------------------------------------
	Int GameNetUdpPacketManager::getOnceHandlePacketCountByDriver(I32 handle)
	{
		std::map<I32, Int>::iterator iter = mOnceHandlePacketCount.find(handle);
		if ( iter != mOnceHandlePacketCount.end() )
		{
			return iter->second;
		}

		return 1;
	}

	//-----------------------------------------------------------------------------
	void GameNetUdpPacketManager::revertOnceHandlePacketCountByDrive()
	{
		mOnceHandlePacketCount.clear();
	}

	//-----------------------------------------------------------------------------
	I32 GameNetUdpPacketManager::update()
	{
		NetUdpManager::update();
		if (mNetEventsMap.empty())
		{
			return 0;
		}

		Int size = 0;
		INetUdpEvent* netEvent = NULL;
		Bool isContinue = false;
		UInt currHandlePacketCount;
		std::map<I32, NetEventsList>::iterator iter = mNetEventsMap.begin();
		std::map<I32, NetEventsList>::iterator iter_end = mNetEventsMap.end();
		for (; iter != iter_end; iter++)
		{
			Int handlePacketCount = getOnceHandlePacketCountByDriver(iter->first);

			NetEventsList& eventList = iter->second;

			NetEventsList::iterator jiter   = eventList.begin();
			for (; jiter != eventList.end(); )
			{
				NetEventsSet& eventsSet = jiter->second;

				//如果参数有效则使用,否则按照当前最大数处理
				if (handlePacketCount>0)
				{
					currHandlePacketCount = handlePacketCount;
				}else
				{
					mNetEventsPreparedListCs.lock();
					{
						currHandlePacketCount = eventsSet.preparedEventsList.size();
					}
					mNetEventsPreparedListCs.unlock();
				}

				isContinue = true;
				for ( UInt i=0;i<currHandlePacketCount;i++)
				{
					mNetEventsPreparedListCs.lock();
					{
						if ( eventsSet.preparedEventsList.empty() == false )
						{
							std::map<U32, INetUdpEvent*>::iterator it = eventsSet.preparedEventsList.begin();
							netEvent = it->second;
							eventsSet.preparedEventsList.erase(it);
						}else
						{
							isContinue = false;
						}
					}
					mNetEventsPreparedListCs.unlock();

					if (isContinue==false)
						break; 

					size++;

					handleNetEvent(netEvent);
				}

				mNetEventsPreparedListCs.lock();
				{
					// TODO：
					// 是否需要清空队列策略当无效时
					if ( ( eventsSet.preparedEventsList.empty() == true ) && ( eventsSet.isValid == false ) )
					{
						jiter = eventList.erase( jiter );
					}else
					{
						jiter++;
					}
				}
				mNetEventsPreparedListCs.unlock();
			}
		}

		return size;
	}

	//-----------------------------------------------------------------------------
	void GameNetUdpPacketManager::handleNetEvent(INetUdpEvent* netEvent)
	{
		if ( netEvent )
		{
			if ( netEvent->getType() == NET_RECV  )
			{
				NetUdpEventRecv* netUdpEventRecv = dynamic_cast<NetUdpEventRecv*>(netEvent);
				if ( netUdpEventRecv )
				{
					//if ( checkRecvPacketValid(netEvent->getHandle(),netEvent->getID(),
					//        (GameNetPacketHeader*)NetUdpEventRecv->getData(),NetUdpEventRecv->getDataSize()) )
					onRecv(netUdpEventRecv);
				}
			}
			else if (netEvent->getType() == NET_ACCEPT)
			{
				NetUdpEventAccept* netUdpEventAccept = dynamic_cast<NetUdpEventAccept*>(netEvent);
				if ( netUdpEventAccept )
				{
					onAccept(netUdpEventAccept);
				}
			}
			else if (netEvent->getType() == NET_CONNECT)
			{
				NetUdpEventConnect* netUdpEventConnect = dynamic_cast<NetUdpEventConnect*>(netEvent);
				if ( netUdpEventConnect )
				{
					onConnected(netUdpEventConnect);
				}
			}
			else if (netEvent->getType() == NET_CLOSE)
			{
				NetUdpEventClose* netUdpEventClose = dynamic_cast<NetUdpEventClose*>(netEvent);
				if ( netUdpEventClose )
				{
					onClose(netUdpEventClose);
				}
			}
			else if (netEvent->getType() == NET_ERR)
			{
				NetUdpEventErr* netUdpEventError = dynamic_cast<NetUdpEventErr*>(netEvent);
				if ( netUdpEventError )
				{
					onError(netUdpEventError);
				}
			}

			if ( netEvent->isNeedGc() )
			{
				freeEvent( netEvent );
			}
		}
	}
	//-----------------------------------------------------------------------------
	Bool GameNetUdpPacketManager::checkRecvPacketValid( I32 handle, I32 id, GameNetUdpPacketHeader* packet, I32 packetSize )
	{
		/*if ( packet->channel < GNPC_NORMAL_MAX )
		{

		}else
		{

		}

		handle = 0;
		id = 0;
		packetSize = 0;*/
		return true;
	}


}


