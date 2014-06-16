//***********************************************************************************************************
#include "stdafx.h"
#include "SHeartbeatManager.h"
#include "SPlayer.h"

//***********************************************************************************************************
namespace MG
{
    //-----------------------------------------------------------------------
    SHeartbeatManager::SHeartbeatManager()
    {

    }

    //-----------------------------------------------------------------------
    SHeartbeatManager::~SHeartbeatManager()
    {

    }

    //-----------------------------------------------------------------------------------
    // Main
    //-----------------------------------------------------------------------------------

    //-----------------------------------------------------------------------
    Bool SHeartbeatManager::initialize()
    {
        return true;
    }

    //-----------------------------------------------------------------------
    Bool SHeartbeatManager::unInitialize()
    {
        return true;
    }

    //-----------------------------------------------------------------------
    void SHeartbeatManager::updateLogicHeartbeatThread(Ptr ptr)
    {
        
    }

    //-----------------------------------------------------------------------------------
    // Player
    //-----------------------------------------------------------------------------------


    //-----------------------------------------------------------------------
    void SHeartbeatManager::addPlayerHeartbeat(SPlayerPtr& ptr)
    {
        ptr->setUpdateInterval( 10 );
        ptr->startUpdate();

        mSPlayerPtrListCs.lock();
        {
            mSPlayerPtrList.push_back( ptr );
        }
        mSPlayerPtrListCs.unlock();
    }

    //-----------------------------------------------------------------------
    Bool SHeartbeatManager::updatePlayerHeartbeat(Flt delta)
    {
        UInt updateCount = 0;
        Bool isDestroyOneHeartbeat = false;

        SPlayer* player = NULL;

        std::list<SPlayerPtr>::iterator listIter;
        mSPlayerPtrListCs.lock();
        {
            listIter = mSPlayerPtrList.begin();
        }
        mSPlayerPtrListCs.unlock();

        Bool isLoop = true;
        while( isLoop )
        {
            isDestroyOneHeartbeat = false;
            player = NULL;

            mSPlayerPtrListCs.lock();
            {
                if ( listIter != mSPlayerPtrList.end() )
                {

                    // get Ptr
                    player = (*listIter).getPointer();

                    // get destroy flag
                    isDestroyOneHeartbeat = player->isStopUpdate();

                    // erase in list
                    if ( isDestroyOneHeartbeat )
                    {
                        listIter = mSPlayerPtrList.erase( listIter );
                        player = NULL;
                    }else
                    {
                        listIter++;
                    }
                }else
                {
                    // quit on exceed count in list
                    mSPlayerPtrListCs.unlock();
                    isLoop = false;
                    break;
                }
            }
            mSPlayerPtrListCs.unlock();


            if ( (isDestroyOneHeartbeat==false) && player )
            {
                // do
                if ( player->checkIntervalAndDoOneUpdate( delta ) )
                {
                    updateCount++ ;
                }
            }
        }

        return (updateCount > 0);
    }


    //-----------------------------------------------------------------------------------
    // Region
    //-----------------------------------------------------------------------------------
    




}
//***********************************************************************************************************