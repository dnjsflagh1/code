
/******************************************************************************/

#include "stdafx.h"
#include "SWorldObjectFactoryManager.h"
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

/******************************************************************************/

namespace MG
{

    //--------------------------------------------------------------------------------------
    SPlayerFactory::SPlayerFactory()
    {
    }

    //--------------------------------------------------------------------------------------
    SPlayerFactory::~SPlayerFactory()
    {
    }

    //-----------------------------------------------------------------------------
    void SPlayerFactory::createSPlayerPtr( SPlayerPtr& ptr, 
                                            AccountIdType accountId, 
                                            I32 frontId, 
                                            I32 client_id,
                                            U64 clanId )
    {
        SPlayer* player = NULL;
        mSPlayerPoolCs.lock();
        {
            player = MG_POOL_NEW_ONCE_CONSTRUCTION(mSPlayerPool, SPlayer, ());
        }
        mSPlayerPoolCs.unlock();

        player->clear();
        player->initialize();

        SPlayerIdentifyInfo* info = player->getIdentifyInfo();
        info->accountId                  = accountId;
        info->frontServerId              = frontId;
        info->clientNetIdInFrontServer   = client_id;
        info->clanId                     = clanId;

        ptr.bind( player );

        ptr.mFactory = this;
    }

    //-----------------------------------------------------------------------------
    void SPlayerFactory::destroySPlayerPtr( SPlayerPtr& ptr )
    {
        SPlayer* player = ptr.getPointer();

        if ( player )
        {
            player->clear();
            player->unInitialize();

            mSPlayerPoolCs.lock();
            {
                MG_POOL_DELETE_ONCE_DESTRUCTOR(mSPlayerPool, player);
            }
            mSPlayerPoolCs.unlock();
        }else
        {
            DYNAMIC_EEXCEPT_LOG("player pointer is null!");
        }
    }


}