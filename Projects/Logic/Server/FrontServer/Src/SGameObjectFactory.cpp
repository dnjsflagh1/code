
/******************************************************************************/

#include "stdafx.h"
#include "SGameObjectFactory.h"
#include "SClan.h"
#include "SPlayerCharacter.h"

/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    // SClanFactory
    /******************************************************************************/

    //--------------------------------------------------------------------------------------
    SClanFactory::SClanFactory()
    {
    }

    //--------------------------------------------------------------------------------------
    SClanFactory::~SClanFactory()
    {
    }

    //-----------------------------------------------------------------------------
    void SClanFactory::createSClanPtr( SClanPtr& ptr, ClanIdType clanId, AccountIdType accountId, ClanData& clanData )
    {
        SClan* clan = NULL;
        mSClanPtrPoolCs.lock();
        {
            clan = MG_POOL_NEW_ONCE_CONSTRUCTION(mSClanPtrPool, SClan, ());
        }
        mSClanPtrPoolCs.unlock();

        clan->clear();
        clan->initialize( clanData );

        ptr.bind( clan );

        ptr.mFactory = this;
    }

    //-----------------------------------------------------------------------------
    void SClanFactory::destroySClanPtr( SClanPtr& ptr )
    {
        SClan* clan = ptr.getPointer();

        if ( clan )
        {
            clan->clear();
            clan->unInitialize();

            mSClanPtrPoolCs.lock();
            {
                MG_POOL_DELETE_ONCE_DESTRUCTOR(mSClanPtrPool, clan);
            }
            mSClanPtrPoolCs.unlock();
        }else
        {
            DYNAMIC_EEXCEPT_LOG("clan pointer is null!");
        }
    }


    /******************************************************************************/
    // SPlayerCharacterFactory
    /******************************************************************************/

    //--------------------------------------------------------------------------------------
    SPlayerCharacterFactory::SPlayerCharacterFactory()
    {
    }

    //--------------------------------------------------------------------------------------
    SPlayerCharacterFactory::~SPlayerCharacterFactory()
    {
    }

    //-----------------------------------------------------------------------------
    void SPlayerCharacterFactory::createSPlayerCharacterPtr( SPlayerCharacterPtr& ptr, PlayerCharacterData& charData )
    {
        SPlayerCharacter* playerCharacter = NULL;
        mSPlayerCharacterPoolCs.lock();
        {
            playerCharacter = MG_POOL_NEW_ONCE_CONSTRUCTION(mSPlayerCharacterPool, SPlayerCharacter, ());
        }
        mSPlayerCharacterPoolCs.unlock();

        playerCharacter->clear();
        playerCharacter->initialize( charData );

        ptr.bind( playerCharacter );

        ptr.mFactory = this;
    }

    //-----------------------------------------------------------------------------
    void SPlayerCharacterFactory::destroySPlayerCharacterPtr( SPlayerCharacterPtr& ptr )
    {
        SPlayerCharacter* playerCharacter = ptr.getPointer();

        if ( playerCharacter )
        {
            playerCharacter->clear();
            playerCharacter->unInitialize();

            mSPlayerCharacterPoolCs.lock();
            {
                MG_POOL_DELETE_ONCE_DESTRUCTOR(mSPlayerCharacterPool, playerCharacter);
            }
            mSPlayerCharacterPoolCs.unlock();
        }else
        {
            DYNAMIC_EEXCEPT_LOG("SPlayerCharacter pointer is null!");
        }
    }


}