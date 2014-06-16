/******************************************************************************/
#include "stdafx.h"
#include "Entity.h"
#include "EngineMain.h"
#include "Scene.h"
#include "ISceneObject.h"
#include "ResourceManager.h"
#include "AnimationController.h"
#include "MeterialEffectSystem.h"
#include "OgreEntityWrapper.h"
#include "DynamicBlockObject.h"
#include "BlockManager.h"
#include "EntityAccessory.h"
#include "CollisionObject.h"

/******************************************************************************/

    #define OGREENTITYWRAPPER_POOL_CATEGORY 3211
    #define ENTITYACCESSORYCOLLECTION_POOL_CATEGORY 3212

namespace MG
{

	//-----------------------------------------------------------------------
	Entity::Entity(CChar* entityName, ModelDeclaration* modelDeclaration, Scene* scene)
        :mAnimationController(NULL)
        ,mDynamicBlockObject(NULL)
        ,mCollisionObject(NULL)
        ,mScene(scene)
		,mRendering(false)
	{
        setName(entityName);

		if ( modelDeclaration )
		{
            //////////////////////////////////////////////////////////////////////////////////////////

            mOgreEntityWrapper = MG_POOL_NEW_T(OgreEntityWrapper, OGREENTITYWRAPPER_POOL_CATEGORY)(this,entityName,modelDeclaration,scene);
			//mOgreEntityWrapper = MG_NEW OgreEntityWrapper(this,entityName,modelDeclaration,scene);
			
            //////////////////////////////////////////////////////////////////////////////////////////

			mOgreEntityWrapper->createOgreEntity(modelDeclaration,true,false);
			createAnimationController(modelDeclaration->id, modelDeclaration->path);
			mOgreEntityWrapper->getOgreEntity()->setListener( this );

            //////////////////////////////////////////////////////////////////////////////////////////

            mEntityAccessoryCollection = MG_POOL_NEW_T(EntityAccessoryCollection, ENTITYACCESSORYCOLLECTION_POOL_CATEGORY)(this,scene);
            //mEntityAccessoryCollection = MG_NEW EntityAccessoryCollection(this,scene);

            mAnimationController->addAnimationLisitener( "EntityAccessoryCollection", mEntityAccessoryCollection );

		}else
		{
			DYNAMIC_ASSERT(false);
		}
	}
    //-----------------------------------------------------------------------
    Entity::Entity(CChar* entityName, CChar* groupName, CChar* modelname, Scene* scene)
        :mAnimationController(NULL)
		,mDynamicBlockObject(NULL)
		,mCollisionObject(NULL)
        ,mEntityAccessoryCollection(NULL)
        ,mScene(scene)
    {
       // mOgreEntityWrapper = MG_NEW OgreEntityWrapper(this,entityName,groupName,modelname,scene);
        mOgreEntityWrapper = MG_POOL_NEW_T(OgreEntityWrapper, OGREENTITYWRAPPER_POOL_CATEGORY)(this,entityName,groupName,modelname,scene);
        if ( mOgreEntityWrapper )
        {
            mOgreEntityWrapper->createOgreEntity(modelname,true,false);
        }
    }
    //-----------------------------------------------------------------------
    Entity::~Entity()
    {
		mOgreEntityWrapper->getSceneNode()->getLinedStateManager()->clear();

        //////////////////////////////////////////////////////////////////////////////////////////

        destroyAnimationController();

        //////////////////////////////////////////////////////////////////////////////////////////
        
        destroyDynamicBlockObject();

        destroyCollisionObject();
       
        //////////////////////////////////////////////////////////////////////////////////////////

        MG_POOL_DELETE_T(mEntityAccessoryCollection,EntityAccessoryCollection,ENTITYACCESSORYCOLLECTION_POOL_CATEGORY);
        MG_POOL_DELETE_T( mOgreEntityWrapper ,OgreEntityWrapper, OGREENTITYWRAPPER_POOL_CATEGORY);
        //MG_SAFE_DELETE(mEntityAccessoryCollection);
        //MG_SAFE_DELETE(mOgreEntityWrapper);

        //////////////////////////////////////////////////////////////////////////////////////////
    }

    //-----------------------------------------------------------------------
    SceneObjectTypes Entity::getType()
    {
        return SOT_ENTITY;
    }
    //-----------------------------------------------------------------------
    MGSceneNode* Entity::getSceneNode()
    {
        return mOgreEntityWrapper->getSceneNode();
    }

    //-----------------------------------------------------------------------
    OgreEntityWrapper* Entity::getModelObject()
    {
        return mOgreEntityWrapper;
    }

    //-----------------------------------------------------------------------
    IAnimationController* Entity::getAnimationController()
    {
        return mAnimationController;
    }

	//-----------------------------------------------------------------------
	IDynamicBlockObject* Entity::getDynamicBlockObject()
	{
		return mDynamicBlockObject;
	}

    //-----------------------------------------------------------------------
    IDynamicBlockObject* Entity::createOrRetrieveDynamicBlockObject()
    {
        if ( !mDynamicBlockObject )
            mDynamicBlockObject = mScene->getBlockManager()->createDynamicBlockObject( mScene, this, mOgreEntityWrapper->getPatherRadius() );
        return mDynamicBlockObject;
    }

    //-----------------------------------------------------------------------
    void Entity::destroyDynamicBlockObject()
    {
        if ( mDynamicBlockObject )
        {
            mScene->getBlockManager()->destroyDynamicBlockObject( mDynamicBlockObject );
            mDynamicBlockObject = NULL;
        }
    }

    //-----------------------------------------------------------------------
    ICollisionObject* Entity::createOrRetrieveCollisionObject()
    {
        if ( !mCollisionObject )
        {
            mCollisionObject = mScene->getCollisionSystem()->createCollisionObject( this );
        }
        return mCollisionObject;
    }

    //-----------------------------------------------------------------------
    void Entity::destroyCollisionObject()
    {
        if ( mCollisionObject )
        {
            mScene->getCollisionSystem()->destroyCollisionObject( mCollisionObject );
            mCollisionObject = NULL;
        }
    }

    //-----------------------------------------------------------------------
    IEntityAccessoryCollection* Entity::getEntityAccessoryCollection()
    {
        return mEntityAccessoryCollection;
    }

    //-----------------------------------------------------------------------
    void Entity::createAnimationController(U32 modelDeclId, Str path)
    {
        if ( mOgreEntityWrapper && !mAnimationController )
        {
            mAnimationController = MG_NEW AnimationController;

            if ( mOgreEntityWrapper->getOgreEntity()->hasSkeleton() )
            {
                Ogre::AnimationStateSet* animSet = mOgreEntityWrapper->getOgreEntity()->getAllAnimationStates();
                Ogre::SkeletonInstance* skeleton = mOgreEntityWrapper->getOgreEntity()->getSkeleton();
                mAnimationController->loadSkeletonAnimation( animSet, skeleton );
            }          

            if ( mOgreEntityWrapper->getOgreEntity()->hasVertexAnimation() )
            {
                mAnimationController->loadVertexAnimation( mOgreEntityWrapper->getOgreEntity() );
            }

			mAnimationController->setParentModelDeclID(modelDeclId);
        }
    }

    //-----------------------------------------------------------------------
    void Entity::destroyAnimationController()
    {
        MG_SAFE_DELETE( mAnimationController );
    }

    //-----------------------------------------------------------------------
    void Entity::updateAnimationController( Flt delta )
    {
        if ( mAnimationController )
        {
            mAnimationController->update( delta );
        }
    }

    //-----------------------------------------------------------------------
    void Entity::preRendering()
    {
        mRendering = false;
    }

    //-----------------------------------------------------------------------
    void Entity::postRendering()
    {
        
    }

    //-----------------------------------------------------------------------
    void Entity::update( Flt delta )
    {
        if ( mOgreEntityWrapper )
        {
            mOgreEntityWrapper->update( delta ); 
        }
        updateAnimationController( delta );

        mEntityAccessoryCollection->update( delta );

		if ( mDynamicBlockObject )
			mDynamicBlockObject->update( delta );
    }   

	//-----------------------------------------------------------------------
	Bool Entity::isRendering()
	{
		return mRendering;
	}

	//-----------------------------------------------------------------------
	bool Entity::objectRendering(const MovableObject*, const Ogre::Camera*)
	{
		mRendering = true;
		return true;
	}

	//-----------------------------------------------------------------------
	void Entity::setRenderGroup( U8 group, U8 priority/* = 100 */)
	{
		if ( mOgreEntityWrapper )
		{
			if ( mOgreEntityWrapper->getOgreEntity() )
			{
				mOgreEntityWrapper->getOgreEntity()->setRenderQueueGroupAndPriority(group, priority);
			}
		}
	}	
}

