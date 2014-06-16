
/******************************************************************************/

#include "stdafx.h"
#include "SPlayerManager.h"
#include "SWorldManager.h"
#include "PlaceListCsv.h"
#include "AreaListCsv.h"
#include "ArtMapResCsv.h"
#include "MapListCsv.h"
#include "RelationWorldMapAreaCsv.h"
#include "RelationWorldMapPlaceCsv.h"
#include "SPlayerCharacterNetPacketProcesser.h"
#include "SPlayerNetPacketProcesser.h"
#include "RegionDevideAlgorithm.h"
#include "SInstanceBase.h"
#include "InstanceListCsv.h"
#include "STiroInstance.h"
#include "District.h"
#include "PlaceListCsv.h"
#include "PrintDialog.h"
#include "SWorldObjectFactoryManager.h"
#include "SHeartbeatManager.h"

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

        mSPlayerFactory = SWorldObjectFactoryManager::getInstance().createSPlayerFactory();

        return true;
    }

    //-----------------------------------------------------------------------------
    Bool SPlayerManager::unInitialize()
    {
        removeAllPlayer();

        SWorldObjectFactoryManager::getInstance().destroySPlayerFactory( mSPlayerFactory );

        return true;
    }

    //-----------------------------------------------------------------------------
    void SPlayerManager::update(Flt delta)
    {

    }

    //-----------------------------------------------------------------------------
    Bool SPlayerManager::addPlayer(AccountIdType accountId,  I32 frontId,  I32 client_id, U64 clanId)
    {
        SPlayerPtr player;
        if ( getPlayer( player, accountId ) )
        {
            DYNAMIC_EEXCEPT_LOG("already exist player!");
            removePlayer( accountId );
            player.setNull();
        }
        
        mSPlayerFactory->createSPlayerPtr( player, accountId, frontId, client_id, clanId );
       
        mPlayerMapCs.writeLock();
        {
            mPlayerMap[accountId] = player;
        }
        mPlayerMapCs.writeUnLock();


        SHeartbeatManager::getInstance().addPlayerHeartbeat( player );

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
    void SPlayerManager::removePlayerByFrontServer(const NetIdType frontId)
    {
        mPlayerMapCs.readLock();
        {
            std::map<AccountIdType,SPlayerPtr>::iterator iter = mPlayerMap.begin();
            for ( ;iter != mPlayerMap.end(); iter++ )
            {
                if ( iter->second->getIdentifyInfo()->frontServerId == frontId )
                {
                    iter->second->clear();
                }
            }
        }
        mPlayerMapCs.readUnLock();

        mPlayerMapCs.writeLock();
        {
            std::map<AccountIdType,SPlayerPtr>::iterator iter = mPlayerMap.begin();
            for ( ;iter != mPlayerMap.end(); )
            {
                if ( iter->second->getIdentifyInfo()->frontServerId == frontId )
                {
                    iter = mPlayerMap.erase( iter );
                }else
                {
                    iter++;
                }
            }
        }
        mPlayerMapCs.writeUnLock();
    }

    //-----------------------------------------------------------------------------
    void SPlayerManager::removeAllPlayer()
    {
        mPlayerMapCs.writeLock();
        {
            std::map<AccountIdType,SPlayerPtr>::iterator iter = mPlayerMap.begin();
            for ( ;iter != mPlayerMap.end(); )
            {
                iter->second->clear();
            }

            mPlayerMap.clear();
        }
        mPlayerMapCs.writeUnLock();
    }

}