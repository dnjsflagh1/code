
/******************************************************************************/

#include "stdafx.h"
#include "SSceneObjectFactory.h"
#include "SPlaceSceneObject.h"
#include "SHomeSceneObject.h"
#include "SPveSceneObject.h"
#include "STiroSceneObject.h"

/******************************************************************************/

namespace MG
{
	/******************************************************************************/
	// 攻城副本地图工厂
	/******************************************************************************/
	//-----------------------------------------------------------------------------
	SPlaceSceneObjectFactory::SPlaceSceneObjectFactory()
	{
	}

	//-----------------------------------------------------------------------------
	SPlaceSceneObjectFactory::~SPlaceSceneObjectFactory()
	{
	}

	//-----------------------------------------------------------------------------
	void SPlaceSceneObjectFactory::createPlaceSceneObjectPtr(SPlaceSceneObjectPtr& ptr, InstanceUIdType instanceUid)
	{
		SPlaceSceneObject* atkSceneObj = NULL;
		mPlaceSceneObjectPoolCs.lock();
		{
			atkSceneObj = MG_POOL_NEW_ONCE_CONSTRUCTION(mPlaceSceneObjectPool, SPlaceSceneObject, ());
		}
		mPlaceSceneObjectPoolCs.unlock();

		atkSceneObj->clear();
		//atkSceneObj->initialize(data);
		atkSceneObj->setInstanceUId(instanceUid);

		ptr.bind( atkSceneObj );

		ptr.mFactory = this;
	}

	//-----------------------------------------------------------------------------
	void SPlaceSceneObjectFactory::destroyPlaceSceneObjectPtr( SPlaceSceneObjectPtr& ptr )
	{
		SPlaceSceneObject* atkSceneObj = ptr.getPointer();
        destroySceneObject( atkSceneObj );
	}

    //-----------------------------------------------------------------------------
    void SPlaceSceneObjectFactory::destroySceneObject( SSceneObject* sceneObj )
    {
        if ( sceneObj )
        {
            sceneObj->clear();
            sceneObj->unInitialize();
			
			SPlaceSceneObject* placeObj = (SPlaceSceneObject*)sceneObj;

            mPlaceSceneObjectPoolCs.lock();
            {
                MG_POOL_DELETE_ONCE_DESTRUCTOR(mPlaceSceneObjectPool, placeObj);
            }
            mPlaceSceneObjectPoolCs.unlock();
        }else
        {
            DYNAMIC_EEXCEPT_LOG("placeSceneObj pointer is null!");
        }
    }


	/******************************************************************************/
	// 【家园副本地图】工厂
	/******************************************************************************/

	//-----------------------------------------------------------------------------
	SHomeSceneObjectFactory::SHomeSceneObjectFactory()
	{
	}

	//-----------------------------------------------------------------------------
	SHomeSceneObjectFactory::~SHomeSceneObjectFactory()
	{
	}

	//-----------------------------------------------------------------------------
	void SHomeSceneObjectFactory::createSHomeSceneObjectPtr(SHomeSceneObjectPtr& ptr, InstanceUIdType instanceUid)
	{
		SHomeSceneObject* homeSceneObj = NULL;
		mSHomeSceneObjectPoolCs.lock();
		{
			homeSceneObj = MG_POOL_NEW_ONCE_CONSTRUCTION(mSHomeSceneObjectPool, SHomeSceneObject, ());
		}
		mSHomeSceneObjectPoolCs.unlock();

		homeSceneObj->clear();
		//homeSceneObj->initialize(data);
		homeSceneObj->setInstanceUId(instanceUid);

		ptr.bind( homeSceneObj );

		ptr.mFactory = this;
	}

	//-----------------------------------------------------------------------------
	void SHomeSceneObjectFactory::destroySHomeSceneObjectPtr( SHomeSceneObjectPtr& ptr )
	{
		SHomeSceneObject* homeSceneObj = ptr.getPointer();
        destroySceneObject( homeSceneObj );
	}

    //-----------------------------------------------------------------------------
    void SHomeSceneObjectFactory::destroySceneObject( SSceneObject* sceneObj )
    {
        if ( sceneObj )
        {
            sceneObj->clear();
            sceneObj->unInitialize();

			SHomeSceneObject* homeObj = (SHomeSceneObject*)sceneObj;

            mSHomeSceneObjectPoolCs.lock();
            {
                MG_POOL_DELETE_ONCE_DESTRUCTOR(mSHomeSceneObjectPool, homeObj);
            }
            mSHomeSceneObjectPoolCs.unlock();
        }else
        {
            DYNAMIC_EEXCEPT_LOG("homeSceneObj pointer is null!");
        }
    }

	/******************************************************************************/
	// 【Pve副本地图】工厂
	/******************************************************************************/

	//-----------------------------------------------------------------------------
	SPveSceneObjectFactory::SPveSceneObjectFactory()
	{
	}

	//-----------------------------------------------------------------------------
	SPveSceneObjectFactory::~SPveSceneObjectFactory()
	{
	}

	//-----------------------------------------------------------------------------
	void SPveSceneObjectFactory::createSPveSceneObjectPtr(SPveSceneObjectPtr& ptr, InstanceUIdType instanceUid)
	{
		SPveSceneObject* pveSceneObj = NULL;
		mSPveSceneObjectPoolCs.lock();
		{
			pveSceneObj = MG_POOL_NEW_ONCE_CONSTRUCTION(mSPveSceneObjectPool, SPveSceneObject, ());
		}
		mSPveSceneObjectPoolCs.unlock();

		pveSceneObj->clear();
		//pveSceneObj->initialize(data);
		pveSceneObj->setInstanceUId(instanceUid);

		ptr.bind( pveSceneObj );

		ptr.mFactory = this;
	}

	//-----------------------------------------------------------------------------
	void SPveSceneObjectFactory::destroySPveSceneObjectPtr( SPveSceneObjectPtr& ptr )
	{
		SPveSceneObject* pveSceneObj = ptr.getPointer();

        destroySceneObject( pveSceneObj );
	}

    //-----------------------------------------------------------------------------
    void SPveSceneObjectFactory::destroySceneObject( SSceneObject* sceneObj )
    {
        if ( sceneObj )
        {
            sceneObj->clear();
            sceneObj->unInitialize();

			SPveSceneObject* pveObj = (SPveSceneObject*)sceneObj;
            mSPveSceneObjectPoolCs.lock();
            {
                MG_POOL_DELETE_ONCE_DESTRUCTOR(mSPveSceneObjectPool, pveObj);
            }
            mSPveSceneObjectPoolCs.unlock();
        }else
        {
            DYNAMIC_EEXCEPT_LOG("SPveSceneObject pointer is null!");
        }
    }

	/******************************************************************************/
	// 【新手村副本地图】工厂
	/******************************************************************************/

	//-----------------------------------------------------------------------------
	STiroSceneObjectFactory::STiroSceneObjectFactory()
	{
	}

	//-----------------------------------------------------------------------------
	STiroSceneObjectFactory::~STiroSceneObjectFactory()
	{
	}

	//-----------------------------------------------------------------------------
	void STiroSceneObjectFactory::createSTiroSceneObjectPtr(STiroSceneObjectPtr& ptr, InstanceUIdType instanceUid)
	{
		STiroSceneObject* tiroSceneObj = NULL;
		mSTiroSceneObjectPoolCs.lock();
		{
			tiroSceneObj = MG_POOL_NEW_ONCE_CONSTRUCTION(mSTiroSceneObjectPool, STiroSceneObject, ());
		}
		mSTiroSceneObjectPoolCs.unlock();

		tiroSceneObj->clear();
		//tiroSceneObj->initialize(data);
		tiroSceneObj->setInstanceUId(instanceUid);

		ptr.bind( tiroSceneObj );

		ptr.mFactory = this;
	}

	//-----------------------------------------------------------------------------
	void STiroSceneObjectFactory::destroySTiroSceneObjectPtr( STiroSceneObjectPtr& ptr )
	{
		STiroSceneObject* tiroSceneObj = ptr.getPointer();

        destroySceneObject( tiroSceneObj );
	}

    //-----------------------------------------------------------------------------
    void STiroSceneObjectFactory::destroySceneObject( SSceneObject* sceneObj )
    {
        if ( sceneObj )
        {
            sceneObj->clear();
            sceneObj->unInitialize();

			STiroSceneObject* tiroObj = (STiroSceneObject*)sceneObj;
            mSTiroSceneObjectPoolCs.lock();
            {
                MG_POOL_DELETE_ONCE_DESTRUCTOR(mSTiroSceneObjectPool, tiroObj);
            }
            mSTiroSceneObjectPoolCs.unlock();
        }else
        {
            DYNAMIC_EEXCEPT_LOG("STiroSceneObject pointer is null!");
        }
    }



}