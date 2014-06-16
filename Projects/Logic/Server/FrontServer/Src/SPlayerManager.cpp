
/******************************************************************************/

#include "stdafx.h"
#include "SPlayerManager.h"
#include "SHeartBeatManager.h"
//#include "SWorldObjectFactoryManager.h"

/******************************************************************************/

namespace MG
{

    //--------------------------------------------------------------------------------------
    SPlayerManager::SPlayerManager()
        :mSPlayerFactory(NULL)
    {
    }

    //--------------------------------------------------------------------------------------
    SPlayerManager::~SPlayerManager()
    {
    }

    //--------------------------------------------------------------------------------------
    Bool SPlayerManager::initialize(ServerLauncherInterface* launcher)
    {
        DYNAMIC_ASSERT(NULL != launcher);

        //mSPlayerFactory = SWorldObjectFactoryManager::getInstance().createSPlayerFactory();

        return true;
    }

    //-----------------------------------------------------------------------------
    Bool SPlayerManager::unInitialize()
    {
        removeAllPlayer();

        //SWorldObjectFactoryManager::getInstance().destroySPlayerFactory( mSPlayerFactory );

        return true;
    }

    //-----------------------------------------------------------------------------
    void SPlayerManager::update(Flt delta)
    {

    }

    //-----------------------------------------------------------------------------
    Bool SPlayerManager::addPlayer( SPlayerPtr& player, AccountIdType accountId, I32 client_id, Str16& accName )
    {
        if ( getPlayer( player, accountId ) )
        {
            DYNAMIC_EEXCEPT_LOG("already exist player!");
            removePlayer( accountId );
            player.setNull();
        }

        mSPlayerFactory->createSPlayerPtr( player, accountId, client_id, accName );

        mPlayerMapCs.writeLock();
        {
            mPlayerMap[accountId] = player;
        }
        mPlayerMapCs.writeUnLock();

        //SHeartBeatManager::getInstance().addPlayerHeartbeat( player );

        return true;
    }

    //-----------------------------------------------------------------------------
    void SPlayerManager::removePlayer(AccountIdType accountId)
    {
        SPlayerPtr player;

        if ( getPlayer( player, accountId) )
        {
            //------------------------------------------------------------------------------------

            player->stopUpdate();

            player->clear();

            //------------------------------------------------------------------------------------

            mPlayerMapCs.writeLock();
            {
                std::map<AccountIdType,SPlayerPtr>::iterator iter = mPlayerMap.find( accountId );
                if ( iter != mPlayerMap.end() )
                {
                    mPlayerMap.erase( iter );
                }
            }
            mPlayerMapCs.writeUnLock();
        }
    }

    //-----------------------------------------------------------------------------
    Bool SPlayerManager::getPlayer(SPlayerPtr& player, AccountIdType accountId)
    {
        Bool result = false;

        mPlayerMapCs.readLock();
        {
            std::map<AccountIdType,SPlayerPtr>::iterator iter = mPlayerMap.find( accountId );
            if ( iter != mPlayerMap.end() )
            {
                player = iter->second;
                result = true;
            }
        }
        mPlayerMapCs.readUnLock();

        return result;
    }

    //-----------------------------------------------------------------------------
    void SPlayerManager::removeAllPlayer()
    {
        mPlayerMapCs.writeLock();
        {
            std::map<AccountIdType,SPlayerPtr>::iterator iter = mPlayerMap.begin();
            for ( ;iter != mPlayerMap.end(); iter++ )
            {
                iter->second->clear();
            }

            mPlayerMap.clear();
        }
        mPlayerMapCs.writeUnLock();
    }

}