/******************************************************************************/
#include "stdafx.h"
#include "GameNetPacketManager.h"
#include "GameNetPacketFilter.h"
#include "GameNetL2NEventData.h"
/******************************************************************************/

namespace MG
{
    /*####################################################################
    //      # Main Init
    ####################################################################*/

    //-----------------------------------------------------------------------------
    GameNetPacketManager::GameNetPacketManager()
        :mThreadAutoHandleStart(false)
    {
    }

    //-----------------------------------------------------------------------------
    GameNetPacketManager::~GameNetPacketManager()
    {
    }

	//-----------------------------------------------------------------------------
	Bool GameNetPacketManager::initialize()
	{
        Bool result = true;

        if ( NetManager::initialize() == false )
            result = false;

        if ( mGameNetPacketFilter.initialize() == false )
            result = false;

		return result;
	}

    //-----------------------------------------------------------------------------
    I32 GameNetPacketManager::update()
    {
        NetManager::update();
        return 0;
    }
	//-----------------------------------------------------------------------------
	I32 GameNetPacketManager::unInitialize()
	{
        mGameNetPacketFilter.unInitialize();

        NetManager::unInitialize();

        clearAllGameNetDriverManager();

		return -1;
	}  

    //-----------------------------------------------------------------------------
    void GameNetPacketManager::startThreadAutoHandle()
    {
        mThreadAutoHandleForAllDriver = true;
        if ( mThreadAutoHandleForAllDriver )
        {
            if ( mL2NThreadHandlesForAllDriver.isRun() == false )
            {
                mL2NThreadHandlesForAllDriver.create(checkAndUpdateL2NEventsFromAllDriver,this);
            }

            if ( mN2LThreadHandlesForAllDriver.isRun() == false )
            {
                mN2LThreadHandlesForAllDriver.create(checkAndUpdateN2LEventsFromAllDriver,this);
            }
        }else
        {
            std::map<I32, GameNetDriverManager*>::iterator iter = mNetDriverEventsMap.begin();
            for ( ;iter!=mNetDriverEventsMap.end();iter++ )
            {
                iter->second->startThreadAutoHandle();
            }
        }

        mThreadAutoHandleStart = true;
    }

    //-----------------------------------------------------------------------------
    void GameNetPacketManager::endThreadAutoHandle()
    {
        mThreadAutoHandleStart = false;

        if ( mThreadAutoHandleForAllDriver )
        {
            mL2NThreadHandlesForAllDriver.destory();
            mN2LThreadHandlesForAllDriver.destory();
        }else
        {
            std::map<I32, GameNetDriverManager*>::iterator iter = mNetDriverEventsMap.begin();
            for ( ;iter!=mNetDriverEventsMap.end();iter++ )
            {
                iter->second->endThreadAutoHandle();
            }
        }
    }

    //-----------------------------------------------------------------------------
    Bool GameNetPacketManager::isThreadAutoHandle()
    {
        return mThreadAutoHandleStart;
    }

    //-----------------------------------------------------------------------------
    I32 GameNetPacketManager::manualDoOneL2NHandle( I32 handle )
    {
		UInt count = 0;
        if ( mThreadAutoHandleStart == false )
        {
            GameNetDriverManager* mgr = retrieveGameNetDriverManager( handle );

            if ( mgr )
            {
                count = mgr->getL2NHandler().checkAndUpdateEvents();
            }

            if ( mgr->mGameNetL2NEventDataFactory )
                mgr->mGameNetL2NEventDataFactory->switchObjectPool();
        }
        return count;
    }

    //-----------------------------------------------------------------------------
    I32 GameNetPacketManager::manualDoOneN2LHandle( I32 handle )
    {
		UInt count = 0;
        if ( mThreadAutoHandleStart == false )
        {
            GameNetDriverManager* mgr = retrieveGameNetDriverManager( handle );

            if ( mgr )
            {
                count = mgr->getN2LHandler().checkAndUpdateEvents();
            }
        }
        return count;
    }


    //-----------------------------------------------------------------------------
    void GameNetPacketManager::checkAndUpdateL2NEventsFromAllDriver(Ptr ptr)
    {
    //#ifdef _DEBUG
    //    MG_EXCEPTION_BEGIN
    //#endif
        OneThreadHandle* thd = (OneThreadHandle* )ptr;
        if ( thd )
        {
            GameNetPacketManager* mgr = (GameNetPacketManager* )(thd->getParam());

            //DYNAMIC_ASSERT_LOG( mgr!=NULL, "checkAndUpdateL2NEventsFromAllDriver is wrong!" );

            if ( mgr )
            {
                Int handleCount = 0;
                while( thd->isRun())
                {
                    handleCount = 0;

                    std::map<I32, GameNetDriverManager*>::iterator iter = mgr->mNetDriverEventsMap.begin();
                    for ( ;iter!=mgr->mNetDriverEventsMap.end();iter++ )
                    {
                        handleCount = iter->second->getL2NHandler().checkAndUpdateEvents();

                        if ( iter->second->mGameNetL2NEventDataFactory )
                            iter->second->mGameNetL2NEventDataFactory->switchObjectPool();
                    }

                    if ( handleCount == 0 )
                    {
                        Sleep(2);
                    }
                }
            }
        }
    //#ifdef _DEBUG
    //    MG_EXCEPTION_END("GameNetPacketManager : checkAndUpdateL2NEventsFromAllDriver");
    //#endif
    }

    //-----------------------------------------------------------------------------
    void GameNetPacketManager::checkAndUpdateN2LEventsFromAllDriver(Ptr ptr)
    {
    //#ifdef _DEBUG
    //    MG_EXCEPTION_BEGIN
    //#endif

        OneThreadHandle* thd = (OneThreadHandle* )ptr;
        if ( thd )
        {
            GameNetPacketManager* mgr = (GameNetPacketManager* )(thd->getParam());

            //DYNAMIC_ASSERT_LOG( mgr!=NULL, "checkAndUpdateN2LEventsFromAllDriver is wrong!" );

            if ( mgr )
            {
                Int handleCount = 0;
                while( thd->isRun())
                {
                    handleCount = 0;

                    std::map<I32, GameNetDriverManager*>::iterator iter = mgr->mNetDriverEventsMap.begin();
                    for ( ;iter!=mgr->mNetDriverEventsMap.end();iter++ )
                    {
                        handleCount = iter->second->getN2LHandler().checkAndUpdateEvents();
                    }

                    if ( handleCount == 0 )
                    {
                        Sleep(2);
                    }
                }
            }
        }
    //#ifdef _DEBUG
    //    MG_EXCEPTION_END("GameNetPacketManager : checkAndUpdateN2LEventsFromAllDriver");
    //#endif
    }


    /*####################################################################
    //      NetEvent From Logic To NetLib
    ####################################################################*/

    //-----------------------------------------------------------------------------
    void GameNetPacketManager::getGameNetSendDataBufferPtr( GameNetSendDataBufferPtr& ptr, I32 handle, U32 buffSize )
    {
        GameNetDriverManager* mgr = retrieveGameNetDriverManager( handle );

        if ( mgr )
        {
            mgr->mGameNetL2NEventDataFactory->createGameNetSendDataBufferPtr( ptr, buffSize );
        }

		ptr.mIsAllowDestroy = false;
    }

    //-----------------------------------------------------------------------------
    void GameNetPacketManager::cloneSendDataBuffer(GameNetSendDataBufferPtr& srcPtr, GameNetSendDataBufferPtr& desPtr, Bool isCopyHeader)
    {
        srcPtr.mFactory->cloneGameNetSendDataBufferPtr( srcPtr, desPtr, isCopyHeader );
    }

    //-----------------------------------------------------------------------------
    void GameNetPacketManager::cloneSendDataBuffer(GameNetSendDataBufferPtr& srcPtr, GameNetSendDataBufferPtr& desPtr, UInt cloneSize)
    {
        srcPtr.mFactory->cloneGameNetSendDataBufferPtr( srcPtr, desPtr, cloneSize );
    }

    //-----------------------------------------------------------------------------
    void GameNetPacketManager::prepareSend( GameNetSendDataBufferPtr& ptr, I32 handle, I32 id, I32 sendSize )
    {
        if ( ptr.isNull() )
        {
            DYNAMIC_EEXCEPT_LOG( "GameNetPacketManager::send : send buff ptr is none!  ) !" );
            return;
        }

        if ( id < 0 )
        {
            DYNAMIC_EEXCEPT_LOG( "GameNetPacketManager::send : this net connect is diconnect!  ) !" );
            return;
        }

        if ( ptr.mIsCheckReduplicateSend && ptr.mNearestSendNetID == id )
        {
            DYNAMIC_EEXCEPT_LOG( "GameNetPacketManager::send : reduplicate net id ( a send buff can't change after send! but can send diff net connect!  ) !" );
            return;
        }

        ptr.mNearestSendNetID = id;
        ptr->setLogicDataSendSize( sendSize );
        
        GameNetDriverManager* mgr = retrieveGameNetDriverManager( handle );

        if ( mgr )
        {
            ptr.mIsAllowDestroy = true;
            {
                if ( ptr.mFactory->mDriverMgr == mgr )
                {
                    Logic2NetEventFromOneConnectHandlerPtr handlerPtr = mgr->getL2NHandler().retrieveOneConnectEventHandler(id,false);

                    if ( handlerPtr.isNull() == false )
                    {
                        handlerPtr->addPrepareSendEvent( ptr );
                    }
                }else
                {
                    DYNAMIC_EEXCEPT_LOG( "GameNetPacketManager::send : different driver !" );
                }
                mgr->mGameNetL2NEventDataFactory->setNearestSendedGameNetSendDataBufferPtr( ptr );
            }
            ptr.mIsAllowDestroy = false;
        }else
        {
            DYNAMIC_EEXCEPT_LOG( "GameNetPacketManager::send : not find driver !" );
        }
    }

    /*####################################################################
    //      NetEvent From NetLib To Logic
    ####################################################################*/

    //-----------------------------------------------------------------------------
    void GameNetPacketManager::addAcceptEvent(I32 handle,I32 id,NetAddress&address)
    {
        GameNetDriverManager* mgr = retrieveGameNetDriverManager( handle );

        if (mgr==NULL)
        {
            DYNAMIC_EEXCEPT_LOG("GameNetPacketManager::addAcceptEvent : not find driver!");
            return;
        }

        {
            Net2LogicEventFromOneConnectHandlerPtr handlerPtr = mgr->getN2LHandler().createOneConnectEventHandler(id);

            if ( handlerPtr.isNull() == false )
            {
                handlerPtr->addAcceptEvent( handle,id,address );
            }else
            {
                DYNAMIC_EEXCEPT_LOG("GameNetPacketManager::addAcceptEvent : not find connect!");
            }
        }
        
        {
            Logic2NetEventFromOneConnectHandlerPtr handlerPtr = mgr->getL2NHandler().createOneConnectEventHandler(id);

            if ( handlerPtr.isNull() == false )
            {
                handlerPtr->addAcceptEvent( handle,id,address );
            }else
            {
                DYNAMIC_EEXCEPT_LOG("GameNetPacketManager::addAcceptEvent : not find connect!");
            }
        }
    }
    //-----------------------------------------------------------------------------
    void GameNetPacketManager::addConnectEvent(I32 handle,I32 id,NetAddress&address)
    {
        GameNetDriverManager* mgr = retrieveGameNetDriverManager( handle );

        if (mgr==NULL)
        {
            DYNAMIC_EEXCEPT_LOG("GameNetPacketManager::addConnectEvent : not find driver!");
            return;
        }

        {
            Net2LogicEventFromOneConnectHandlerPtr handlerPtr = mgr->getN2LHandler().createOneConnectEventHandler(id);

            if ( handlerPtr.isNull() == false )
            {
                handlerPtr->addConnectEvent( handle,id,address );
            }else
            {
                DYNAMIC_EEXCEPT_LOG("GameNetPacketManager::addConnectEvent : not find connect!");
            }
        }

        {
            Logic2NetEventFromOneConnectHandlerPtr handlerPtr = mgr->getL2NHandler().createOneConnectEventHandler(id);

            if ( handlerPtr.isNull() == false )
            {
                handlerPtr->addConnectEvent( handle,id,address );
            }else
            {
                DYNAMIC_EEXCEPT_LOG("GameNetPacketManager::addConnectEvent : not find connect!");
            }
        }
    }
	//-----------------------------------------------------------------------------
    void GameNetPacketManager::addCloseEvent(I32 handle,I32 id,Bool isPassivity,NetAddress&address)
	{
        GameNetDriverManager* mgr = retrieveGameNetDriverManager( handle );

        if (mgr==NULL)
        {
            DYNAMIC_EEXCEPT_LOG("GameNetPacketManager::addCloseEvent : not find driver!");
            return;
        }

        {
            Net2LogicEventFromOneConnectHandlerPtr handlerPtr = mgr->getN2LHandler().retrieveOneConnectEventHandler(id,false);

            if ( handlerPtr.isNull() == false )
            {
                handlerPtr->addCloseEvent( handle,id, isPassivity, address );
            }/*else
            {
                DYNAMIC_EEXCEPT_LOG("GameNetPacketManager::addCloseEvent : not find connect!");
            }*/
        }

        {
            Logic2NetEventFromOneConnectHandlerPtr handlerPtr = mgr->getL2NHandler().retrieveOneConnectEventHandler(id,false);

            if ( handlerPtr.isNull() == false )
            {
                handlerPtr->addCloseEvent( handle,id, isPassivity, address );
            }/*else
            {
                DYNAMIC_EEXCEPT_LOG("GameNetPacketManager::addCloseEvent : not find connect!");
            }*/
        }
	}
    //-----------------------------------------------------------------------------
    void GameNetPacketManager::addRecvEvent(I32 handle,I32 id, Char8* buff, I32 buffLen)
    {
        GameNetDriverManager* mgr = retrieveGameNetDriverManager( handle );

        if (mgr==NULL)
        {
            DYNAMIC_EEXCEPT_LOG("GameNetPacketManager::addRecvEvent : not find driver!");
            return;
        }

        Net2LogicEventFromOneConnectHandlerPtr handlerPtr = mgr->getN2LHandler().retrieveOneConnectEventHandler(id,true);

        if ( handlerPtr.isNull() == false )
        {
            handlerPtr->addRecvEvent(handle,id,buff,buffLen);  
        }else
        {
            DYNAMIC_EEXCEPT_LOG("GameNetPacketManager::addRecvEvent : not find connect!");
        }
    }
    //-----------------------------------------------------------------------------
    void GameNetPacketManager::addErrEvent(I32 handle,I32 id)
    {
        GameNetDriverManager* mgr = retrieveGameNetDriverManager( handle );

        if (mgr==NULL)
        {
            DYNAMIC_EEXCEPT_LOG("GameNetPacketManager::addErrEvent : not find driver!");
            return;
        }

        Net2LogicEventFromOneConnectHandlerPtr handlerPtr = mgr->getN2LHandler().retrieveOneConnectEventHandler(id,true);

        if ( handlerPtr.isNull() == false )
        {
            handlerPtr->addErrEvent(handle,id);
        }else
        {
            DYNAMIC_EEXCEPT_LOG("GameNetPacketManager::addErrEvent : not find connect!");
        }
    }

    //-----------------------------------------------------------------------------
    void GameNetPacketManager::addSendEvent(NetOnceSendConfig* config)
    {
        I32 handle  = config->getDriverID();
        I32 id      = config->getNetID();

        GameNetDriverManager* mgr = retrieveGameNetDriverManager( handle );

        if (mgr==NULL)
        {
            DYNAMIC_EEXCEPT_LOG("GameNetPacketManager::addSendEvent : not find driver!");
            return;
        }

        {
            Logic2NetEventFromOneConnectHandlerPtr handlerPtr =  mgr->getL2NHandler().retrieveOneConnectEventHandler(id,true);

            if ( handlerPtr.isNull() == false )
            {
                handlerPtr->addSendEvent(config);
            }else
            {
                DYNAMIC_EEXCEPT_LOG("GameNetPacketManager::addSendEvent : not find connect!");
            }
        }
    }

    //-----------------------------------------------------------------------------
    void GameNetPacketManager::freeEvent(INetEvent* netEvent)
    {
        netEvent->free();
    }

    /*####################################################################
    //      NetEvent From Drive
    ####################################################################*/


    //-----------------------------------------------------------------------------
    GameNetDriverManager* GameNetPacketManager::createOrRetrieveGameNetDriverManager( I32 handle )
    {
        GameNetDriverManager* mgr = NULL;

        std::map<I32, GameNetDriverManager*>::iterator iter = mNetDriverEventsMap.find( handle );
        if ( iter != mNetDriverEventsMap.end() )
        {
            mgr = iter->second;
            DYNAMIC_ASSERT_LOG( mgr->getActive(), "createOrRetrieveGameNetDriverManager : Driver is not active" );
        }else
        {
            mgr = MG_POOL_NEW(mNetDriverEventsPool,GameNetDriverManager,());
            mgr->setManager(this);
            mgr->setDriverID(handle);
            mNetDriverEventsMap[handle] = mgr;
        }
        
        return mgr;
    }

    //-----------------------------------------------------------------------------
    GameNetDriverManager* GameNetPacketManager::retrieveGameNetDriverManager( I32 handle )
    {
        GameNetDriverManager* mgr = NULL;

        std::map<I32, GameNetDriverManager*>::iterator iter = mNetDriverEventsMap.find( handle );
        if ( iter != mNetDriverEventsMap.end() )
        {
            mgr = iter->second;
            DYNAMIC_ASSERT_LOG( mgr->getActive(), "createOrRetrieveGameNetDriverManager : Driver is not active" );
        }

        return mgr;
    }

    //-----------------------------------------------------------------------------
    void GameNetPacketManager::clearAllGameNetDriverManager()
    {
        GameNetDriverManager* mgr = NULL;

        std::map<I32, GameNetDriverManager*>::iterator iter = mNetDriverEventsMap.begin();
        for ( ; iter != mNetDriverEventsMap.end() ; iter ++ )
        {
            mgr = iter->second;
            mgr->clear();

            MG_POOL_DELETE(mNetDriverEventsPool,mgr);
        } 
        mNetDriverEventsMap.clear();
    }

    //-----------------------------------------------------------------------------
    void GameNetPacketManager::configDrive(I32 handle,GameNetDriveConfig& config)
    {
        GameNetDriverManager* mgr = createOrRetrieveGameNetDriverManager(handle);
        mgr->getConfig() = config;
        mgr->setActive( true );
    }

    //-----------------------------------------------------------------------------
    GameNetPacketFilter* GameNetPacketManager::getPacketFilter()
    {
        return &mGameNetPacketFilter;
    }

}


