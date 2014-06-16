/******************************************************************************/
#include "stdafx.h"
#include "GameNetPacketManager.h"
#include "GameNetPacketFilter.h"
#include "GameNetEventsHandler.h"
#include "GameNetDriverManager.h"
#include "GameNetL2NEventData.h"
/******************************************************************************/

namespace MG
{


    /******************************************************************************/
    // Logic2NetEventOneDriveHandler
    /******************************************************************************/


    /******************************************************************************/
    // Net2LogicEventOneDriveHandler
    /******************************************************************************/



    /******************************************************************************/
    // GameNetDriverManager
    /******************************************************************************/

    //-----------------------------------------------------------------------------
    GameNetDriverManager::GameNetDriverManager()
        :mMgr(NULL)
        ,mActive(false)
        ,mDriverID(-1)
    {
        mLogic2NetEventOneDriveHandler.mMgr = this;
        mNet2LogicEventOneDriveHandler.mMgr = this;

        mGameNetL2NEventDataFactory = MG_NEW GameNetL2NEventDataFactory(this);
    }

    //-----------------------------------------------------------------------------
    void GameNetDriverManager::startThreadAutoHandle()
    {
        if ( mL2NThreadHandles.isRun() == false )
        {
            mL2NThreadHandles.create(checkAndUpdateL2NEvents,this);
        }
  
        if ( mN2LThreadHandles.isRun() == false )
        {
            mN2LThreadHandles.create(checkAndUpdateN2LEvents,this);
        }

        MG_SAFE_DELETE(mGameNetL2NEventDataFactory);
    }

    //-----------------------------------------------------------------------------
    void GameNetDriverManager::clear()
    {
        mLogic2NetEventOneDriveHandler.clearAllOneConnectEventHandler();
        mNet2LogicEventOneDriveHandler.clearAllOneConnectEventHandler();
        mGameNetL2NEventDataFactory->clear();
    }

    //-----------------------------------------------------------------------------
    void GameNetDriverManager::endThreadAutoHandle()
    {
        mL2NThreadHandles.destory();
        mN2LThreadHandles.destory();
        Sleep(10);
    }

    //-----------------------------------------------------------------------------
    void GameNetDriverManager::checkAndUpdateL2NEvents( Ptr ptr )
    {
    #ifdef _DEBUG
        MG_EXCEPTION_BEGIN
    #endif

        OneThreadHandle* thd = (OneThreadHandle* )ptr;
        if ( thd )
        {
            GameNetDriverManager* mgr = static_cast<GameNetDriverManager*>(thd->getParam());

            //DYNAMIC_ASSERT_LOG( (mgr!=NULL), "checkAndUpdateL2NEvents is wrong!" );

            if ( mgr )
            {
                Int handleCount = 0;
                while( thd->isRun())
                {
                    handleCount = 0;

                    handleCount = mgr->mLogic2NetEventOneDriveHandler.checkAndUpdateEvents();

                    if ( mgr->mGameNetL2NEventDataFactory )
                        mgr->mGameNetL2NEventDataFactory->switchObjectPool();

                    if ( handleCount == 0 )
                    {
                        Sleep(2);
                    }
                }
            }
        }
    #ifdef _DEBUG
        MG_EXCEPTION_END("GameNetDriverManager : checkAndUpdateL2NEvents");
    #endif
    }

    //-----------------------------------------------------------------------------
    void GameNetDriverManager::checkAndUpdateN2LEvents( Ptr ptr )
    {
    #ifdef _DEBUG
        MG_EXCEPTION_BEGIN
    #endif
        OneThreadHandle* thd = (OneThreadHandle* )ptr;
        if ( thd )
        {
            GameNetDriverManager* mgr = (GameNetDriverManager* )(thd->getParam());

            //DYNAMIC_ASSERT_LOG( mgr!=NULL, "checkAndUpdateN2LEvents is wrong!" );

            if ( mgr )
            {
                Int handleCount = 0;
                while( thd->isRun())
                {
                    handleCount = 0;

                    handleCount = mgr->mNet2LogicEventOneDriveHandler.checkAndUpdateEvents();

                    if ( handleCount == 0 )
                    {
                        Sleep(2);
                    }
                }
            }
        }
    #ifdef _DEBUG
        MG_EXCEPTION_END("GameNetDriverManager : checkAndUpdateN2LEvents");
    #endif
    }
    


}

