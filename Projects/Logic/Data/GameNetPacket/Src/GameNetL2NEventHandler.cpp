/******************************************************************************/
#include "stdafx.h"
#include "GameNetPacketManager.h"
#include "GameNetPacketFilter.h"
#include "GameNetEventsHandler.h"
#include "GameNetL2NEventHandler.h"
#include "GameNetL2NEventData.h"
/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------------
    Logic2NetEventFromOneConnectHandler::Logic2NetEventFromOneConnectHandler()
        :mCurrSendEvents(NULL)
		,mRecvSendEventNetCount(0)
		,mSendNetCount(0)
    {

    }

	//--------------------------------------------------------------------------------
	void Logic2NetEventFromOneConnectHandler::initialize( Int id,GameNetDriverManager* mgr )
	{
		EventOneConnectHandler::initialize( id, mgr );

		clearEvents();

		mCloseEvent = 0;

		mSendNumber = 0;

		mCurrSendEvents = NULL;

		mWaitSend	= 0;

		mRecvSendEventNetCount  = 0;
		mSendNetCount			= 0;
	}

	//--------------------------------------------------------------------------------
	void Logic2NetEventFromOneConnectHandler::unInitialize()
	{
		EventOneConnectHandler::unInitialize();
	}

    //--------------------------------------------------------------------------------
    // 网络层事件
    //--------------------------------------------------------------------------------


    //-----------------------------------------------------------------------------
    void Logic2NetEventFromOneConnectHandler::addAcceptEvent(I32 handle,I32 id,NetAddress&address)
    {
        UNREFERENCED_PARAMETER(handle);
        UNREFERENCED_PARAMETER(id);
        UNREFERENCED_PARAMETER(address);
    }

    //-----------------------------------------------------------------------------
    void Logic2NetEventFromOneConnectHandler::addConnectEvent(I32 handle,I32 id,NetAddress&address)
    {
        UNREFERENCED_PARAMETER(handle);
        UNREFERENCED_PARAMETER(id);
        UNREFERENCED_PARAMETER(address);
    }

    //-----------------------------------------------------------------------------
    void Logic2NetEventFromOneConnectHandler::addCloseEvent(I32 handle,I32 id,Bool isPassivity,NetAddress&address)
    {
        UNREFERENCED_PARAMETER(handle);
        UNREFERENCED_PARAMETER(id);
        UNREFERENCED_PARAMETER(address);
        UNREFERENCED_PARAMETER(isPassivity);

		mCloseEvent++;
    }

    //-----------------------------------------------------------------------------
    void Logic2NetEventFromOneConnectHandler::addSendEvent( NetOnceSendConfig* config )
    {
		mRecvSendEventNetCount++;
        removeWaitSendResponseEvent( config->getSendID() );
    }

    //-----------------------------------------------------------------------------
    void Logic2NetEventFromOneConnectHandler::clearEvents()
    {
        if ( mCurrSendEvents )
        {
            destroyOnceSendEvents( mCurrSendEvents );
            mCurrSendEvents = NULL;
        }
        clearPrepareSendEvent();
        clearWaitSendResponseEvent();
    }

    //-----------------------------------------------------------------------------
    void Logic2NetEventFromOneConnectHandler::freeEvent( INetEvent* netEvent )
    {
        UNREFERENCED_PARAMETER(netEvent);

        DYNAMIC_EEXCEPT_LOG("Logic2NetEventFromOneConnectHandler::freeEvent : not net event !");
    }


    //--------------------------------------------------------------------------------
    // 来自逻辑层的预备发送逻辑
    //--------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------
    void Logic2NetEventFromOneConnectHandler::addPrepareSendEvent( GameNetSendDataBufferPtr& ptr )
    {
        mPrepareSendEventsQueueCs.lock();
        {
            mPrepareSendEventsQueue.push_back( ptr );
        }
        mPrepareSendEventsQueueCs.unlock();
    }

    //-----------------------------------------------------------------------------
    void Logic2NetEventFromOneConnectHandler::clearPrepareSendEvent()
    {
        mPrepareSendEventsQueueCs.lock();
        {
            mPrepareSendEventsQueue.clear();
        }
        mPrepareSendEventsQueueCs.unlock();
    }


    //--------------------------------------------------------------------------------
    // 单个发送事件对象逻辑
    //--------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------
    Logic2NetEventFromOneConnectHandler::OnceSendEvents::OnceSendEvents()
    {
        mSendEventsQueue.reserve( MG_NET_MAX_COMBINE_PACKET_COUNT );
    }

    //-----------------------------------------------------------------------------
    Logic2NetEventFromOneConnectHandler::OnceSendEvents::~OnceSendEvents()
    {

    }

    //-----------------------------------------------------------------------------
    void Logic2NetEventFromOneConnectHandler::OnceSendEvents::clear()
    {
        mSendEventsQueue.clear();
        mGameNetOnceSendConfig.setNull();
        mSendCombinePacketSize  = 0;
		mSendCombinePacketCount = 0;
        mSendID                 = -1;
    }

    //-----------------------------------------------------------------------------
    Bool Logic2NetEventFromOneConnectHandler::OnceSendEvents::isEmpty()
    {
        return mSendCombinePacketSize == 0;
    }

    //-----------------------------------------------------------------------------
    Bool Logic2NetEventFromOneConnectHandler::OnceSendEvents::checkAndAddOrIgnore( GameNetSendDataBufferPtr& ptr, U32 maxSendSize )
    {
        Bool result = false;

		if ( mSendCombinePacketCount >= MG_NET_MAX_COMBINE_PACKET_COUNT )
			return result;

        U32 sendTotalSize = ptr->getLogicDataSendSize() + mSendCombinePacketSize;
        if ( sendTotalSize <= maxSendSize )
        {
            mSendEventsQueue.push_back( ptr );
            mGameNetOnceSendConfig->pushSendData( ptr.getPointer() );
            mSendCombinePacketSize = sendTotalSize;
			mSendCombinePacketCount++;
            result = true;
        }

        return result;
    }


    //-----------------------------------------------------------------------------
    Logic2NetEventFromOneConnectHandler::OnceSendEvents* Logic2NetEventFromOneConnectHandler::createOnceSendEvents()
    {
        Logic2NetEventFromOneConnectHandler::OnceSendEvents* events = NULL;

        mOnceSendEventsPoolCs.lock();
        {
            events = MG_POOL_NEW_ONCE_CONSTRUCTION( mOnceSendEventsPool, OnceSendEvents, ());
        }
        mOnceSendEventsPoolCs.unlock();

        events->clear();
        events->mSendID = mSendNumber++;

        getDriverManager()->mGameNetL2NEventDataFactory->createGameNetOnceSendConfigPtr( 
                                events->mGameNetOnceSendConfig ,
                                getDriverManager()->getDriverID(), 
                                getNetID(), 
                                events->mSendID );

        return events;
    }

    //-----------------------------------------------------------------------------
    void Logic2NetEventFromOneConnectHandler::destroyOnceSendEvents( OnceSendEvents* events )
    {
        if ( events )
        {
            mOnceSendEventsPoolCs.lock();
            {
                events->clear();

                MG_POOL_DELETE_ONCE_DESTRUCTOR( mOnceSendEventsPool, events);
            }
            mOnceSendEventsPoolCs.unlock();
        }
    }

        
    //--------------------------------------------------------------------------------
    // 主处理发送网络层逻辑
    //--------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------
    Int Logic2NetEventFromOneConnectHandler::checkAndUpdateEvents()
    {
        UInt handleCount = 0;

		// quit when close
		if ( mCloseEvent > 0 )
		{
			clearEvents();
			disConnected();
			mCloseEvent = 0;
			return handleCount;
		}

        // quit when wait
        if ( mWaitSend != 0 )
        {
            return handleCount;
        }

        // set curr events
        if ( mCurrSendEvents )
        {
            DYNAMIC_ASSERT_LOG( mCurrSendEvents->mGameNetOnceSendConfig->getNetID() == getNetID(), "Logic2NetEventFromOneConnectHandler::checkAndUpdateEvents : mCurrSendEvents has diff net id! " );
            if ( mCurrSendEvents->mGameNetOnceSendConfig->getNetID() != getNetID() )
            {
                destroyOnceSendEvents( mCurrSendEvents );
                mCurrSendEvents = NULL;
            }
        }

        if ( mCurrSendEvents == NULL )
        {
            mCurrSendEvents = createOnceSendEvents();
        }

        // loop event list and fill event to mCurrSendEvents list
        U32 eventSize = 0;
        mPrepareSendEventsQueueCs.lock();
        {
            eventSize = mPrepareSendEventsQueue.size();
        }
        mPrepareSendEventsQueueCs.unlock();

        GameNetSendDataBufferPtr ptr;
        U32 maxSize = mDriverMgr->getConfig().SendCombinePacketMaxSize;
        Bool isIgnore = false;
        for ( U32 i=0; i<eventSize; i++ )
        {
            mPrepareSendEventsQueueCs.lock();
            {
                ptr = mPrepareSendEventsQueue.front();
                if ( mCurrSendEvents->checkAndAddOrIgnore( ptr, maxSize ) )
                {
                    mPrepareSendEventsQueue.pop_front();
                    handleCount ++ ;
                }else
                {
                    isIgnore = true;
                }
            }
            mPrepareSendEventsQueueCs.unlock();

            if ( isIgnore )
                break;
        }

        // send to net
        if ( mCurrSendEvents->isEmpty() == false )
        {
            addWaitSendResponseEvent( mCurrSendEvents );

            GameNetOnceSendConfigPtr configPtr = mCurrSendEvents->mGameNetOnceSendConfig;

            mWaitSend = 1;

            if ( getPacketManager()->send( configPtr.getPointer() ) )
            {
				mSendNetCount++;

                if ( configPtr->isImmeSend() )
                {
                    mWaitSend = 0;
                }
            }else
            {
                removeWaitSendResponseEvent( mCurrSendEvents->mSendID );
            }

            mCurrSendEvents = NULL;
        }

        return handleCount;
    }



    //--------------------------------------------------------------------------------
    // 来自网络层的发送回应逻辑
    //--------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------
    void Logic2NetEventFromOneConnectHandler::addWaitSendResponseEvent( OnceSendEvents* events )
    {
        mWaitSendResponseEventsQueueCs.lock();
        {
            mWaitSendResponseEventsQueue[events->mSendID] = events;
        }
        mWaitSendResponseEventsQueueCs.unlock();
    }

    //-----------------------------------------------------------------------------
    void Logic2NetEventFromOneConnectHandler::removeWaitSendResponseEvent( I32 sendID )
    {
        OnceSendEvents* sendEvent = NULL;

        mWaitSendResponseEventsQueueCs.lock();
        {
            WaitSendResponseEventsMap::iterator iter =  mWaitSendResponseEventsQueue.find( sendID );
            if ( iter != mWaitSendResponseEventsQueue.end() )
            {
                sendEvent = iter->second;
                mWaitSendResponseEventsQueue.erase( iter );
            }else
            {
                DYNAMIC_EEXCEPT_LOG("addSendEvent : not find event!");
            }

            if ( mWaitSendResponseEventsQueue.empty() )
            {
                mWaitSend = 0;
            }
        }
        mWaitSendResponseEventsQueueCs.unlock();

        if ( sendEvent )
        {
            destroyOnceSendEvents( sendEvent );
        }
    }

    //-----------------------------------------------------------------------------
    void Logic2NetEventFromOneConnectHandler::clearWaitSendResponseEvent()
    {
        OnceSendEvents* sendEvent = NULL;

        mWaitSendResponseEventsQueueCs.lock();
        {
            WaitSendResponseEventsMap::iterator iter =  mWaitSendResponseEventsQueue.begin();
            for ( ; iter != mWaitSendResponseEventsQueue.end() ; iter++ )
            {
                sendEvent = iter->second;

                if ( sendEvent )
                {
                    destroyOnceSendEvents( sendEvent );
                }
            }

            mWaitSendResponseEventsQueue.clear();
        }
        mWaitSendResponseEventsQueueCs.unlock();
    }



}

