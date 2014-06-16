
/******************************************************************************/

#include "stdafx.h"
#include "SWorldObjectFactoryManager.h"
#include "SGameObjectFactory.h"
#include "SPlayerObjectFactory.h"
/******************************************************************************/

namespace MG
{
    
    //-----------------------------------------------------------------------------
    SWorldObjectFactoryManager::SWorldObjectFactoryManager()
    {
    }

    //-----------------------------------------------------------------------------
    SWorldObjectFactoryManager::~SWorldObjectFactoryManager()
    {
    }

    //-----------------------------------------------------------------------------
    Bool SWorldObjectFactoryManager::initialize()
    {
        return true;
    }

    //-----------------------------------------------------------------------------
    Bool SWorldObjectFactoryManager::unInitialize()
    {
        return true;
    }

    //-----------------------------------------------------------------------------
    void SWorldObjectFactoryManager::update(Flt delta)
    {
    }

    //-----------------------------------------------------------------------------
    SPlayerFactory* SWorldObjectFactoryManager::createSPlayerFactory()
    {
        SPlayerFactory* factory = NULL;
        mSPlayerFactoryPoolCs.lock();
        {
            factory = MG_POOL_NEW_ONCE_CONSTRUCTION(mSPlayerFactoryPool, SPlayerFactory, ());
        }
        mSPlayerFactoryPoolCs.unlock();
        return factory;
    }

    //-----------------------------------------------------------------------------
    void SWorldObjectFactoryManager::destroySPlayerFactory( SPlayerFactory* factory )
    {
        if ( factory )
        {
            mSPlayerFactoryPoolCs.lock();
            {
                MG_POOL_DELETE_ONCE_DESTRUCTOR(mSPlayerFactoryPool, factory);
            }
            mSPlayerFactoryPoolCs.unlock();
        }else
        {
            DYNAMIC_EEXCEPT_LOG("factory pointer is null!");
        }
    }

}