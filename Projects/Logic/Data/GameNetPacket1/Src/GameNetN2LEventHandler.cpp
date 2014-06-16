/******************************************************************************/
#include "stdafx.h"
#include "GameNetPacketManager.h"
#include "GameNetPacketFilter.h"
#include "GameNetEventsHandler.h"
#include "GameNetN2LEventHandler.h"
/******************************************************************************/

namespace MG
{
    
    //-----------------------------------------------------------------------------
    Net2LogicEventFromOneConnectHandler::Net2LogicEventFromOneConnectHandler()
        :mExternalRecallMgr(NULL)
        ,mAddedNetEventsQueue(NULL)
        ,mHandlerNetEventsQueue(NULL)
    {
    }

    //-----------------------------------------------------------------------------
    void Net2LogicEventFromOneConnectHandler::initialize( Int id,GameNetDriverManager* mgr )
    {
        EventOneConnectHandler::initialize( id, mgr );

        if ( mgr->getConfig().BlockWaitEnableInRecvQueue == false )
        {
            mIsSwapQueueAndPool = true;
        }else
        {
            mIsSwapQueueAndPool = false;
        }

        if ( mIsSwapQueueAndPool )
        {
            mAddedNetEventsQueue    = &mNetEventsQueueAndPool1;
            mHandlerNetEventsQueue  = &mNetEventsQueueAndPool2;
        }else
        {
            mAddedNetEventsQueue    = &mNetEventsQueueAndPool1;
            mHandlerNetEventsQueue  = &mNetEventsQueueAndPool1;
        }

		clearEvents();
    }

    //-----------------------------------------------------------------------------
    void Net2LogicEventFromOneConnectHandler::unInitialize()
    {
        EventOneConnectHandler::unInitialize();
    }

    //-----------------------------------------------------------------------------
    void Net2LogicEventFromOneConnectHandler::addAcceptEvent(I32 handle,I32 id,NetAddress&address)
    {
        NetEventAccept* netEvent = NULL;

        NetEventsQueueAndPool* eqp = mAddedNetEventsQueue;

        eqp->mNetEventsPoolCs.lock();
        {
            netEvent = MG_POOL_NEW(eqp->mNetEventAcceptPool,NetEventAccept,(handle,id,address,this));
        }
        eqp->mNetEventsPoolCs.unlock();

        eqp->mNetEventsQueueCs.lock();
        {
            eqp->mNetEventsQueue.push_back( netEvent );
        }
        eqp->mNetEventsQueueCs.unlock();
    }

    //-----------------------------------------------------------------------------
    void Net2LogicEventFromOneConnectHandler::addConnectEvent(I32 handle,I32 id,NetAddress&address)
    {
        NetEventConnect* netEvent = NULL;
        NetEventsQueueAndPool* eqp = mAddedNetEventsQueue;

        eqp->mNetEventsPoolCs.lock();
        {
            netEvent = MG_POOL_NEW(eqp->mNetEventConnectPool,NetEventConnect,(handle,id,address,this));
        }
        eqp->mNetEventsPoolCs.unlock();

        eqp->mNetEventsQueueCs.lock();
        {
            eqp->mNetEventsQueue.push_back( netEvent );
        }
        eqp->mNetEventsQueueCs.unlock();
    }

    //-----------------------------------------------------------------------------
    void Net2LogicEventFromOneConnectHandler::addCloseEvent(I32 handle,I32 id,Bool isPassivity,NetAddress&address)
    {
        // 清空所有事件队列,只增加关闭事件
        clearEvents();

        NetEventClose* netEvent = NULL;
        NetEventsQueueAndPool* eqp = mAddedNetEventsQueue;

        eqp->mNetEventsPoolCs.lock();
        {
            netEvent = MG_POOL_NEW(eqp->mNetEventClosePool,NetEventClose,(handle,id,isPassivity,address,this));
        }
        eqp->mNetEventsPoolCs.unlock();

        eqp->mNetEventsQueueCs.lock();
        {
            eqp->mNetEventsQueue.push_back( netEvent );
        }
        eqp->mNetEventsQueueCs.unlock();
    }

    //-----------------------------------------------------------------------------
    void Net2LogicEventFromOneConnectHandler::addRecvEvent(I32 handle,I32 id, Char8* buff, I32 buffLen)
    {
        //-----------------------------------------------------------------------------

        NetEventRecv* netEvent = NULL;

        //-----------------------------------------------------------------------------

        // check packet valid
        if ( checkPacketValid( handle,id, buff, buffLen ) == false )
        {
            return ;
        }
        // check packet attack
        if ( checkPacketAttacked( handle,id, buff, buffLen ) == true )
        {
            return ;
        }
        // check packet attack
        if ( checkPacketCheatPlug( handle,id, buff, buffLen ) == true )
        {
            return ;
        }

        //-----------------------------------------------------------------------------

        // check packet replace
        netEvent = checkPacketReplace( handle,id, buff, buffLen );
      
        // check packet discard
        checkPacketDiscard( handle,id, buff, buffLen );

        //-----------------------------------------------------------------------------

        NetEventsQueueAndPool* eqp = mAddedNetEventsQueue;

        // get new event
        if ( netEvent == NULL )
        {
            if ( buffLen <= MG_GAME_NET_PACKET_NORMAL_MAX_SIZE )
            {
                eqp->mNetEventsPoolCs.lock();
                {
                    netEvent = MG_POOL_NEW_ONCE_CONSTRUCTION(eqp->mNetEventNormalRecvPool,NetEventRecv,(MG_GAME_NET_PACKET_NORMAL_MAX_SIZE,this));
                }
                eqp->mNetEventsPoolCs.unlock();

                netEvent->init(handle,id, MG_GAME_NET_PACKET_NORMAL_MAX_SIZE);

            }else
            if ( buffLen <= MG_GAME_NET_PACKET_BIG_MAX_SIZE )
            {
                eqp->mNetEventsPoolCs.lock();
                {
                    netEvent = MG_POOL_NEW_ONCE_CONSTRUCTION(eqp->mNetEventBigRecvPool,NetEventRecv,(MG_GAME_NET_PACKET_BIG_MAX_SIZE,this));
                }
                eqp->mNetEventsPoolCs.unlock();

                netEvent->init(handle,id, MG_GAME_NET_PACKET_BIG_MAX_SIZE);
            }
        }

        if ( netEvent )
        {
            // Copy
            // TODO: 复制效率
            netEvent->copyData( buff, buffLen );

            DYNAMIC_ASSERT_LOG( isDisConnected() == false, "addRecvEvent : error by disconnected!" );

            eqp->mNetEventsQueueCs.lock();
            {
                eqp->mNetEventsQueue.push_back( netEvent );
            }
            eqp->mNetEventsQueueCs.unlock();
        }
    }

    //-----------------------------------------------------------------------------
    void Net2LogicEventFromOneConnectHandler::addErrEvent(I32 handle,I32 id)
    {
        NetEventErr* netEvent = NULL;

        NetEventsQueueAndPool* eqp = mAddedNetEventsQueue;


        eqp->mNetEventsPoolCs.lock();
        {
            netEvent = MG_POOL_NEW(eqp->mNetEventErrPool,NetEventErr,(handle,id,this));
        }
        eqp->mNetEventsPoolCs.unlock();

        DYNAMIC_ASSERT_LOG( isDisConnected() == false, "addErrEvent : error by disconnected!" );

        eqp->mNetEventsQueueCs.lock();
        {
            eqp->mNetEventsQueue.push_back( netEvent );
        }
        eqp->mNetEventsQueueCs.unlock();
    }

    //-----------------------------------------------------------------------------
    Int Net2LogicEventFromOneConnectHandler::checkAndUpdateEvents()
    {
        UInt handleCount = 0;

        //-------------------------------------------------------------------------------------------

        //  quit when block Wait 
        if ( checkPacketBlockHandle() )
        {
            return handleCount;
        }

        //-------------------------------------------------------------------------------------------
        NetEventsQueueAndPool* eqp = mHandlerNetEventsQueue;

        //loop
        Int loopCount = 0;
        eqp->mNetEventsQueueCs.lock();
        {
            loopCount = eqp->mNetEventsQueue.size();
        }
        eqp->mNetEventsQueueCs.unlock();

        if ( mDriverMgr->getConfig().OnceHandlePacketCount > 0 )
        {
            if ( mDriverMgr->getConfig().OnceHandlePacketCount < loopCount )
            {
                loopCount = mDriverMgr->getConfig().OnceHandlePacketCount;
            }
        }

        INetEvent* netEvent = NULL;
        Bool isEmptyInHandlerNetEventsQueue = (loopCount==0);
        
        if ( isEmptyInHandlerNetEventsQueue == false )
        {
            for ( Int i=0; i<loopCount; i++)
            {
                eqp->mNetEventsQueueCs.lock();
                {
                    if ( eqp->mNetEventsQueue.empty() == false )
                    {
                        netEvent = eqp->mNetEventsQueue.front();
                        eqp->mNetEventsQueue.pop_front();
                    }else
                    {
                        isEmptyInHandlerNetEventsQueue = true;
                        netEvent = NULL;
                    }
                }
                eqp->mNetEventsQueueCs.unlock();

                if ( isEmptyInHandlerNetEventsQueue == false )
                {
                    if (netEvent)
                    {
                        handleCount++;

                        // handle event
                        handleEvents(netEvent);

                        // recall external events
                        recallFreeEvents( true, eqp );
                    }
                }else
                {
                    break;
                }

                if ( checkPacketBlockHandle() )
                {
                    break;
                }
            }
        }else
        {
            // recall external events
            recallFreeEvents( true, eqp );
        }

        //-------------------------------------------------------------------------------------------

        // swap when empty in handler queue
        if ( isEmptyInHandlerNetEventsQueue )
        {
            swapEventsQueueAndPool();
        }

        return loopCount;
    }


    //-----------------------------------------------------------------------------
    void Net2LogicEventFromOneConnectHandler::swapEventsQueueAndPool()
    {
        // swap when empty in handler queue
        if ( mIsSwapQueueAndPool &&  (mAddedNetEventsQueue!=mHandlerNetEventsQueue)  )
        {
            NetEventsQueueAndPool* eqp1 = mAddedNetEventsQueue;
            NetEventsQueueAndPool* eqp2 = mHandlerNetEventsQueue;

            eqp1->mNetEventsQueueCs.lock();
            eqp1->mNetEventsPoolCs.lock();
            {
                eqp2->mNetEventsQueueCs.lock();
                eqp2->mNetEventsPoolCs.lock();
                {
                    if ( mHandlerNetEventsQueue->mNetEventsQueue.empty() == true )
                    {
                        NetEventsQueueAndPool*  swapObj = mAddedNetEventsQueue;
                        mAddedNetEventsQueue = mHandlerNetEventsQueue;
                        mHandlerNetEventsQueue =   swapObj;
                    }
                }
                eqp2->mNetEventsPoolCs.unlock();
                eqp2->mNetEventsQueueCs.unlock();
            }
            eqp1->mNetEventsPoolCs.unlock();
            eqp1->mNetEventsQueueCs.unlock();
        }
    }

    //-----------------------------------------------------------------------------
    void Net2LogicEventFromOneConnectHandler::pushOneWaitHandle(I32 handle,I32 id, Char8* buff, I32 buffLen)
    {
        UNREFERENCED_PARAMETER(handle);
        UNREFERENCED_PARAMETER(id);
        UNREFERENCED_PARAMETER(buff);
        UNREFERENCED_PARAMETER(buffLen);

        if ( mDriverMgr->getConfig().BlockWaitEnableInRecvQueue )
        {
            //TODO:



        }
    }

    //-----------------------------------------------------------------------------
    Bool Net2LogicEventFromOneConnectHandler::checkPacketValid(I32 handle,I32 id, Char8* buff, I32 buffLen)
    {
        UNREFERENCED_PARAMETER(handle);
        UNREFERENCED_PARAMETER(id);
        UNREFERENCED_PARAMETER(buff);
        UNREFERENCED_PARAMETER(buffLen);

        Bool packetValid = getPacketFilter()->checkRecvPacketValid( handle, id, (GameNetPacketHeader*)buff, buffLen );

        return packetValid;
    }

    //--------------------------------------------------------------------------------
    NetEventRecv* Net2LogicEventFromOneConnectHandler::checkPacketReplace(I32 handle,I32 id, Char8* buff, I32 buffLen)
    {
        UNREFERENCED_PARAMETER(handle);
        UNREFERENCED_PARAMETER(id);
        UNREFERENCED_PARAMETER(buff);
        UNREFERENCED_PARAMETER(buffLen);

        return NULL;
    }

    //--------------------------------------------------------------------------------
    Bool Net2LogicEventFromOneConnectHandler::checkPacketDiscard(I32 handle,I32 id, Char8* buff, I32 buffLen)
    {
        UNREFERENCED_PARAMETER(handle);
        UNREFERENCED_PARAMETER(id);
        UNREFERENCED_PARAMETER(buff);
        UNREFERENCED_PARAMETER(buffLen);

        return false;
    }

    //--------------------------------------------------------------------------------
    Bool Net2LogicEventFromOneConnectHandler::checkPacketAttacked(I32 handle,I32 id, Char8* buff, I32 buffLen)
    {
        UNREFERENCED_PARAMETER(handle);
        UNREFERENCED_PARAMETER(id);
        UNREFERENCED_PARAMETER(buff);
        UNREFERENCED_PARAMETER(buffLen);

        return false;
    }

    //--------------------------------------------------------------------------------
    Bool Net2LogicEventFromOneConnectHandler::checkPacketCheatPlug(I32 handle,I32 id, Char8* buff, I32 buffLen)
    {
        UNREFERENCED_PARAMETER(handle);
        UNREFERENCED_PARAMETER(id);
        UNREFERENCED_PARAMETER(buff);
        UNREFERENCED_PARAMETER(buffLen);

        return false;
    }

    //-----------------------------------------------------------------------------
    Bool Net2LogicEventFromOneConnectHandler::checkPacketBlockHandle()
    {
        if ( mDriverMgr->getConfig().BlockWaitEnableInRecvQueue )
        {
            //TODO:



        }

        return false;
    }

    //-----------------------------------------------------------------------------
    void Net2LogicEventFromOneConnectHandler::onReplyHandleEvents(I32 handle,I32 id, Char8* buff, I32 buffLen)
    {
        UNREFERENCED_PARAMETER(handle);
        UNREFERENCED_PARAMETER(id);
        UNREFERENCED_PARAMETER(buff);
        UNREFERENCED_PARAMETER(buffLen);


        if ( mDriverMgr->getConfig().BlockWaitEnableInRecvQueue )
        {
            //TODO:



        }
    }

    //-----------------------------------------------------------------------------
    void Net2LogicEventFromOneConnectHandler::handleEvents( INetEvent* netEvent )
    {
        if ( netEvent )
        {
            netEvent->addLocker();

            if ( netEvent->getType() == NET_RECV  )
            {
                NetEventRecv* netEventRecv = dynamic_cast<NetEventRecv*>(netEvent);
                if ( netEventRecv )
                {
                    {
                        getPacketManager()->onRecv(netEventRecv);

                        pushOneWaitHandle(
                            netEvent->getHandle(),
                            netEvent->getID(), 
                            netEventRecv->getData(),
                            netEventRecv->getDataSize() ) ;
                    }
                }
            }
            else 
            if ( netEvent->getType() == NET_ACCEPT )
            {
                NetEventAccept* netEventAccept = dynamic_cast<NetEventAccept*>(netEvent);
                if ( netEventAccept )
                {
                    getPacketManager()->onAccept(netEventAccept);
                }
            }
            else 
            if ( netEvent->getType() == NET_CONNECT )
            {
                NetEventConnect* netEventConnect = dynamic_cast<NetEventConnect*>(netEvent);
                if ( netEventConnect )
                {
                    getPacketManager()->onConnected(netEventConnect);
                }
            }
            else 
            if ( netEvent->getType() == NET_CLOSE )
            {
                NetEventClose* netEventClose = dynamic_cast<NetEventClose*>(netEvent);
                if ( netEventClose )
                {
                    getPacketManager()->onClose(netEventClose);
                }
                
                disConnected();
            }
            else 
            if ( netEvent->getType() == NET_ERR )
            {
                NetEventErr* netEventError = dynamic_cast<NetEventErr*>(netEvent);
                if ( netEventError )
                {
                    getPacketManager()->onError(netEventError);
                }
            }

            if ( netEvent->subLocker() <= 0 )
            {
                recallEvent( netEvent, mHandlerNetEventsQueue, true );
            }
        }
    }

    //-----------------------------------------------------------------------------
    void Net2LogicEventFromOneConnectHandler::clearEvents()
    {
        // clear add queue
        // clear handle queue
        clearEventsQueueAndPool( &mNetEventsQueueAndPool1 );
        clearEventsQueueAndPool( &mNetEventsQueueAndPool2 );

        // recall external events
        recallFreeEvents( false, mHandlerNetEventsQueue );

        UInt bigRecvActiveCount = mNetEventsQueueAndPool1.mNetEventBigRecvPool.activeCount() + mNetEventsQueueAndPool2.mNetEventBigRecvPool.activeCount();
        UInt normalRecvActiveCount = mNetEventsQueueAndPool1.mNetEventNormalRecvPool.activeCount() + mNetEventsQueueAndPool2.mNetEventNormalRecvPool.activeCount();

        //DYNAMIC_ASSERT_LOG( bigRecvActiveCount==0,"Net2LogicEventFromOneConnectHandler::clearEvents : logic has no recall event!" );
        //DYNAMIC_ASSERT_LOG( normalRecvActiveCount==0,"Net2LogicEventFromOneConnectHandler::clearEvents : logic has no recall event!" );
    }
    
    //-----------------------------------------------------------------------------
    void Net2LogicEventFromOneConnectHandler::clearEventsQueueAndPool(NetEventsQueueAndPool* eqp)
    {
        eqp->mNetEventsQueueCs.lock();
        {
            eqp->mNetEventsPoolCs.lock();
            {
                std::deque<INetEvent*>::iterator iter = eqp->mNetEventsQueue.begin();
                for ( ; iter!=eqp->mNetEventsQueue.end(); iter++ )
                {
                    recallEvent( (*iter), eqp, false );
                }
                eqp->mNetEventsQueue.clear();
            }
            eqp->mNetEventsPoolCs.unlock();
        }
        eqp->mNetEventsQueueCs.unlock();
    }

    //-----------------------------------------------------------------------------
    void Net2LogicEventFromOneConnectHandler::recallFreeEvents(Bool isTryLock, NetEventsQueueAndPool* eqp)
    {
        Bool isLocked = false;

        if ( isTryLock )
        {
            isLocked = mNetEventsFreePoolCs.tryLock();
        }
        else
        {
            mNetEventsFreePoolCs.lock();
            isLocked = true;
        }

        if ( isLocked )
        {
            std::deque<INetEvent*>::iterator iter = mNetEventFreePool.begin();
            for ( ; iter!=mNetEventFreePool.end(); iter++ )
            {
                recallEvent( (*iter), eqp, true );
            }
            mNetEventFreePool.clear();
        }
        if ( isLocked )
            mNetEventsFreePoolCs.unlock();
    }

    //-----------------------------------------------------------------------------
    void Net2LogicEventFromOneConnectHandler::recallEvent( INetEvent* netEvent, NetEventsQueueAndPool* eqp, Bool isLock )
    {
        if ( netEvent->getLockerCount() != 0 )
        {
            return;
        }

        if ( netEvent )
        {
            if (netEvent->getType() == NET_RECV)
            {
                NetEventRecv* netEventRecv = dynamic_cast<NetEventRecv*>(netEvent);
                DYNAMIC_ASSERT( netEventRecv );
                if ( netEventRecv )
                {
                    netEventRecv->unInit();

                    if ( netEventRecv->getBuffMaxSize() <= MG_GAME_NET_PACKET_NORMAL_MAX_SIZE )
                    {
                        if ( isLock )
                            eqp->mNetEventsPoolCs.lock();
                        {
                            MG_POOL_DELETE_ONCE_DESTRUCTOR( eqp->mNetEventNormalRecvPool, netEventRecv);
                        }
                        if ( isLock )
                            eqp->mNetEventsPoolCs.unlock();
                    }else
                    if ( netEventRecv->getBuffMaxSize() <= MG_GAME_NET_PACKET_BIG_MAX_SIZE )
                    {
                        if ( isLock )
                            eqp->mNetEventsPoolCs.lock();
                        {
                            MG_POOL_DELETE_ONCE_DESTRUCTOR( eqp->mNetEventBigRecvPool, netEventRecv);
                        }
                        if ( isLock )
                            eqp->mNetEventsPoolCs.unlock();
                    }
                }
            }else 
            if (netEvent->getType() == NET_ACCEPT)
            {
                NetEventAccept* netEventAccept = dynamic_cast<NetEventAccept*>(netEvent);
                DYNAMIC_ASSERT( netEventAccept );
                if ( netEventAccept )
                {
                    if ( isLock )
                        eqp->mNetEventsPoolCs.lock();
                    {
                        MG_POOL_DELETE( eqp->mNetEventAcceptPool, netEventAccept);
                    }
                    if ( isLock )
                        eqp->mNetEventsPoolCs.unlock();
                }
            }else 
            if (netEvent->getType() == NET_CONNECT)
            {
                NetEventConnect* netEventConnect = dynamic_cast<NetEventConnect*>(netEvent);
                DYNAMIC_ASSERT( netEventConnect );
                if ( netEventConnect )
                {
                    if ( isLock )
                        eqp->mNetEventsPoolCs.lock();
                    {
                        MG_POOL_DELETE( eqp->mNetEventConnectPool, netEventConnect);
                    }
                    if ( isLock )
                        eqp->mNetEventsPoolCs.unlock();
                }
            }else
            if (netEvent->getType() == NET_CLOSE)
            {
                NetEventClose* netEventClose = dynamic_cast<NetEventClose*>(netEvent);
                DYNAMIC_ASSERT( netEventClose );
                if ( netEventClose )
                {
                    if ( isLock )
                        eqp->mNetEventsPoolCs.lock();
                    {
                        MG_POOL_DELETE( eqp->mNetEventClosePool, netEventClose);
                    }
                    if ( isLock )
                        eqp->mNetEventsPoolCs.unlock();
                }
            }else
            if (netEvent->getType() == NET_ERR)
            {
                NetEventErr* netEventError = dynamic_cast<NetEventErr*>(netEvent);
                DYNAMIC_ASSERT( netEventError );
                if ( netEventError )
                {
                    if ( isLock )
                        eqp->mNetEventsPoolCs.lock();
                    {
                        MG_POOL_DELETE( eqp->mNetEventErrPool, netEventError);
                    }
                    if ( isLock )
                        eqp->mNetEventsPoolCs.unlock();
                }
            }else
            {
                DYNAMIC_EEXCEPT_LOG("Net2LogicEventFromOneConnectHandler::recallEvent : not find type!");
            }
        }
    }

    //----------------------------------------------------------------------------- 
    void Net2LogicEventFromOneConnectHandler::freeEvent( INetEvent* netEvent )
    {
        mNetEventsFreePoolCs.lock();
        {
            mNetEventFreePool.push_back( netEvent );
        }
        mNetEventsFreePoolCs.unlock();
    }
}

