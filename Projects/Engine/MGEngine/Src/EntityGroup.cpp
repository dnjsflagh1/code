/******************************************************************************/
#include "stdafx.h"
#include "Entity.h"
#include "EngineMain.h"
#include "MGSceneNode.h"
#include "Scene.h"
#include "ISceneObject.h"
#include "ResourceManager.h"
#include "AnimationController.h"
#include "MeterialEffectSystem.h"
#include "OgreEntityWrapper.h"
#include "EntityGroup.h"
#include "SceneNodeAction.h"
#include "DynamicBlockObject.h"
#include "EntityAccessory.h"
#include "MGEngineUtility.h"
#include "CollisionObject.h"
#include "OgreInstancedGeometry.h"
/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //EntityGroupInstance
    /******************************************************************************/
    EntityGroupInstance::EntityGroupInstance(Str groupName,EntityGroup* entityGroup, 
		InstancedGeometry::InstancedObject* instancedObj, InstancedGeometry::BatchInstance* batchInstance)
        :mInstancedObject(instancedObj)
		,mBatchInstance(batchInstance)
        ,mEntityGroup(entityGroup)
        ,mVisible(false)
        ,mAnimationController(NULL)
        ,mDynamicBlockObject(NULL)
        ,mCollisionObject(NULL)
    {
        ///////////////////////////////////////////////////////////

        mLocalDirectionVector = Vector3::NEGATIVE_UNIT_Z;
        mWorldDirectionNormalisedVector = mInstancedObject->getOrientation() *( mLocalDirectionVector ).normalisedCopy();

        mTerrainRayDir1 = Vec3(0,-1,0);
        mTerrainRayDir2 = Vec3(0,1,0);

		mPositionOffset = Vec3(0,0,0);
		mInitScale = Vec3(1,1,1);

        ///////////////////////////////////////////////////////////

        createAnimationController(groupName);

        ///////////////////////////////////////////////////////////

        mEntityAccessoryCollection = MG_NEW EntityAccessoryCollection(this,mEntityGroup->getScene());
        mAnimationController->addAnimationLisitener( "EntityAccessoryCollection", mEntityAccessoryCollection );

		///////////////////////////////////////////////////////////
    }
    //-----------------------------------------------------------------------
    EntityGroupInstance::~EntityGroupInstance()
    {
        ///////////////////////////////////////////////////////////

        destroyAnimationController();

        ///////////////////////////////////////////////////////////

        MG_SAFE_DELETE( mEntityAccessoryCollection );

        ///////////////////////////////////////////////////////////

        destroyDynamicBlockObject();
        destroyCollisionObject();

    }

    //-----------------------------------------------------------------------
    void EntityGroupInstance::preRendering()
    {
		mRendering = false;
    }

    //-----------------------------------------------------------------------
    void EntityGroupInstance::postRendering()
    {

    }

    //-----------------------------------------------------------------------
    void EntityGroupInstance::update( Flt delta )
    {
        mLinedStateManager.update( delta );
        mEntityAccessoryCollection->update( delta );
        updateAnimationController( delta );

		if ( mDynamicBlockObject )
			mDynamicBlockObject->update( delta );
    }

	//-----------------------------------------------------------------------
	Bool EntityGroupInstance::isRendering()
	{
		return mRendering;
	}

    //-----------------------------------------------------------------------
    void EntityGroupInstance::setRenderingDirty()
    {
        mRendering = true;
    }

    //-----------------------------------------------------------------------
    SceneObjectTypes EntityGroupInstance::getType()
    {
        return SOT_ENTITY_GROUP_UNIT; 
    }
    //-----------------------------------------------------------------------
    ISceneNode* EntityGroupInstance::getSceneNode()
    {
        return this;
    }
    //-----------------------------------------------------------------------
    OgreEntityWrapper* EntityGroupInstance::getModelObject()
    {
        return mEntityGroup->mOgreEntityTemplate;
    }

    //-----------------------------------------------------------------------
    IAnimationController* EntityGroupInstance::getAnimationController()
    {
        return mAnimationController;
    }

	//-----------------------------------------------------------------------
	IDynamicBlockObject* EntityGroupInstance::getDynamicBlockObject()
	{
		return mDynamicBlockObject;
	}

    //-----------------------------------------------------------------------
    IDynamicBlockObject* EntityGroupInstance::createOrRetrieveDynamicBlockObject()
    {
        if ( !mDynamicBlockObject )
            mDynamicBlockObject = mEntityGroup->getScene()->getBlockManager()->createDynamicBlockObject( 
                                        mEntityGroup->getScene(), this, getModelObject()->getPatherRadius() );
        return mDynamicBlockObject;
    }
    //-----------------------------------------------------------------------
    void EntityGroupInstance::destroyDynamicBlockObject()
    {
        if ( mDynamicBlockObject )
        {
            mEntityGroup->getScene()->getBlockManager()->destroyDynamicBlockObject( mDynamicBlockObject );
            mDynamicBlockObject = NULL;
        }
    }
    //-----------------------------------------------------------------------
    ICollisionObject* EntityGroupInstance::createOrRetrieveCollisionObject()
    {
        if ( !mCollisionObject )
        {
            mCollisionObject = mEntityGroup->getScene()->getCollisionSystem()->createCollisionObject( this );
        }
        return mCollisionObject;
    }
    //-----------------------------------------------------------------------
    void EntityGroupInstance::destroyCollisionObject()
    {
        if ( mCollisionObject )
        {
            mEntityGroup->getScene()->getCollisionSystem()->destroyCollisionObject( mCollisionObject );
            mCollisionObject = NULL;
        }
    }
    //-----------------------------------------------------------------------
    IEntityAccessoryCollection* EntityGroupInstance::getEntityAccessoryCollection()
    {
        return mEntityAccessoryCollection;
    }
    //-----------------------------------------------------------------------
    IScene* EntityGroupInstance::getScene()
    {
        return mEntityGroup->mScene;
    }
    //-----------------------------------------------------------------------
    void EntityGroupInstance::createAnimationController(Str groupName)
    {
        if ( !mAnimationController )
        {
            mAnimationController = MG_NEW AnimationController;

            if ( mInstancedObject->getSkeletonInstance() )
            {
                Ogre::AnimationStateSet* animSet = mInstancedObject->getAllAnimationStates();
                Ogre::SkeletonInstance* skeleton = mInstancedObject->getSkeletonInstance();
                mAnimationController->loadSkeletonAnimation( animSet, skeleton );
            }

			if ( mEntityGroup && mEntityGroup->getModelObject() )
				mAnimationController->setParentModelDeclID( mEntityGroup->getModelObject()->getModelDeclarationID( ));
        }
    }
    //-----------------------------------------------------------------------
    void EntityGroupInstance::destroyAnimationController()
    {
        MG_SAFE_DELETE( mAnimationController );
    }
    //-----------------------------------------------------------------------
    void EntityGroupInstance::updateAnimationController( Flt delta )
    {
        if ( mAnimationController )
        {
            mAnimationController->update( delta );
        }
    }
    //-----------------------------------------------------------------------
    void EntityGroupInstance::setVisible(Bool visible)
    {
        mVisible = visible;
        mInstancedObject->setVisible(visible);

        notifyVisibleChanged( visible );
    }
    //-----------------------------------------------------------------------
    Bool EntityGroupInstance::getVisible()
    {
        return mVisible;
    }
    //-----------------------------------------------------------------------
    void EntityGroupInstance::setPosition(Vec3& pos)
    {
		pos += mPositionOffset;
        if (!mVisible)
        {
            mInstancedObject->setPosition(Vector3(pos.x,-1000,pos.z));
        }else
        {
			Vec3 lastPos = MGEngineUtility::toVec3(mInstancedObject->getPosition());
            mInstancedObject->setPosition(Vector3(pos.x,pos.y,pos.z));

            if( lastPos.x != pos.x || 
                lastPos.y != pos.y || 
                lastPos.z != pos.z 
                )
			{
				notifyPositionChanged(lastPos, pos);
			}
        }
    }
    //-----------------------------------------------------------------------
    void EntityGroupInstance::getPosition(Vec3& pos)
    {
        const Vector3& ogreVec3 = mInstancedObject->getPosition();
        pos.x = ogreVec3.x-mPositionOffset.x;
        pos.y = ogreVec3.y-mPositionOffset.x;
        pos.z = ogreVec3.z-mPositionOffset.x;
    }

	void EntityGroupInstance::setPositionOffset(const Vec3& offset)
	{		
		mPositionOffset = offset;
	}
	//-----------------------------------------------------------------------
	const Vec3& EntityGroupInstance::getPositionOffset() const
	{
		return mPositionOffset;
	}

	//-----------------------------------------------------------------------
	void EntityGroupInstance::getScreenPosition(Vec2& outPos)
	{
		Vec3 worldPos;
		getPosition(worldPos);

		IScene* pScene = getScene();
		ICamera* pCamera = pScene->getActiveCamera();
		pCamera->worldPointToScreenPoint(worldPos, outPos);
	}
    //-----------------------------------------------------------------------
    Bool EntityGroupInstance::getPositionDirty()
    {
        return false;
    }
    //-----------------------------------------------------------------------
    void EntityGroupInstance::clearPositionDirty()
    {
    }
    //-----------------------------------------------------------------------
    void EntityGroupInstance::setScale(Vec3& scale)
    {
		Vec3 tempScale = scale;
		tempScale *= mInitScale;
        mInstancedObject->setScale(Vector3(tempScale.x,tempScale.y,tempScale.z));
    }
    //-----------------------------------------------------------------------
    void  EntityGroupInstance::getScale(Vec3& scale)
    {
        const Vector3& ogreVec3 = mInstancedObject->getScale();
        scale.x = ogreVec3.x/mInitScale.x;
        scale.y = ogreVec3.y/mInitScale.y;
        scale.z = ogreVec3.z/mInitScale.z;
    }

	//-----------------------------------------------------------------------
	void EntityGroupInstance::setInitScale(const Vec3& scale)
	{		
		mInitScale = scale;
		setScale(Vec3(1,1,1));
	}
	//-----------------------------------------------------------------------
	const Vec3& EntityGroupInstance::getInitScale() const
	{
		return mInitScale;
	}

    //----------------------------------------------------------------------- 
    Bool  EntityGroupInstance::getScaleDirty()
    {
        return false;
    }
    //-----------------------------------------------------------------------
    void  EntityGroupInstance::clearScaleDirty()
    {
        
    }
    //-----------------------------------------------------------------------
    void  EntityGroupInstance::setOrientation(Qua& quaternion)
    {
        mInstancedObject->setOrientation(Quaternion(quaternion.w,quaternion.x,quaternion.y,quaternion.z));
    }
    //-----------------------------------------------------------------------
    void  EntityGroupInstance::getOrientation(Qua& quaternion)
    {
        const Quaternion& ogreQua = mInstancedObject->getOrientation();
        quaternion.w = ogreQua.w;
        quaternion.x = ogreQua.x;
        quaternion.y = ogreQua.y;
        quaternion.z = ogreQua.z;
    }
    //-----------------------------------------------------------------------
    Bool  EntityGroupInstance::getOrientationDirty()
    {
        return false;
    }

    //-----------------------------------------------------------------------
    void  EntityGroupInstance::clearOrientationDirty()
    {

    }

    //-----------------------------------------------------------------------
    void  EntityGroupInstance::setDirection(Vec3& vec, TransformSpace relativeTo)
    {
        // Do nothing if given a zero vector
        if (vec == Vec3(0,0,0))
            return;

        Vector3 targetDir = Vector3(vec.x,vec.y,vec.z);
        targetDir.normalise();

        Quaternion targetOrientation;

        // Calculate the quaternion for rotate local Z to target direction
        Vector3 xVec = Vector3::UNIT_Y.crossProduct(targetDir);
        xVec.normalise();
        Vector3 yVec = targetDir.crossProduct(xVec);
        yVec.normalise();
        Quaternion unitZToTarget = Quaternion(xVec, yVec, targetDir);

        if (mLocalDirectionVector == Vector3::NEGATIVE_UNIT_Z)
        {
            // Specail case for avoid calculate 180 degree turn
            targetOrientation =
                Quaternion(-unitZToTarget.y, -unitZToTarget.z, unitZToTarget.w, unitZToTarget.x);
        }
        else
        {
            // Calculate the quaternion for rotate local direction to target direction
            Quaternion localToUnitZ = mLocalDirectionVector.getRotationTo(Vector3::UNIT_Z);
            targetOrientation = unitZToTarget * localToUnitZ;
        }

        mInstancedObject->setOrientation(targetOrientation);
    }

    //-----------------------------------------------------------------------
    void  EntityGroupInstance::getDirection(Vec3& vec)
    {
        Vector3 ogreVec3;
        const Quaternion& quaternion = mInstancedObject->getOrientation();
        ogreVec3 = quaternion * mWorldDirectionNormalisedVector ;

        vec = Vec3( ogreVec3.x, ogreVec3.y, ogreVec3.z );
    }

    //-----------------------------------------------------------------------
    void  EntityGroupInstance::lookAt(Vec3& targetPoint, TransformSpace relativeTo)
    {

    }

    //-----------------------------------------------------------------------
    void  EntityGroupInstance::translate(Vec3& d, TransformSpace relativeTo)
    {
        mInstancedObject->translate(Vector3(d.x,d.y,d.z));
    }

    //-----------------------------------------------------------------------
    void  EntityGroupInstance::roll( Flt angle, TransformSpace relativeTo)
    {
		mInstancedObject->roll(Ogre::Radian(angle));
    }
    //-----------------------------------------------------------------------
    void  EntityGroupInstance::pitch( Flt angle, TransformSpace relativeTo)
    {
		mInstancedObject->pitch(Ogre::Radian(angle));
    }
    //-----------------------------------------------------------------------
    void  EntityGroupInstance::yaw( Flt angle, TransformSpace relativeTo )
    {
		mInstancedObject->yaw(Ogre::Radian(angle));
    }

    //-----------------------------------------------------------------------
    void  EntityGroupInstance::rotate( Vec3& axis, Flt& angle, TransformSpace relativeTo)
    {
        //mInstancedObject->rotate(Vector3(axis.x,axis.y,axis.z), Ogre::Radian(angle));
    }

    //-----------------------------------------------------------------------
    void  EntityGroupInstance::stickTerrain()
    {
		Flt height = 0;
		if ( getScene()->getCollisionSystem()->getStickHeight(this,height ) )
		{
            Vec3 pos;
            getPosition( pos );
			pos.y = height;
			setPosition(pos);
		}
    }

    
    /******************************************************************************/
    //EntityGroup
    /******************************************************************************/
    EntityGroup::EntityGroup(CChar* entityName, ModelDeclaration* modelDeclaration, Scene* scene, UInt num)
        :mScene(scene)
        ,mInstancedGeometry(NULL)
        ,mEntityInstanceNameGenerator("EntityGroupInstance")
    {
        mOgreEntityTemplate = MG_NEW OgreEntityWrapper(this,entityName,modelDeclaration,scene);
        if ( mOgreEntityTemplate )
        {
            mOgreEntityTemplate->createOgreEntity(modelDeclaration, false, true);
            createInstancedGeometry(entityName,modelDeclaration,num);
            applyVisibleFlag();
        }
    }
    //-----------------------------------------------------------------------
    EntityGroup::~EntityGroup()
    {
        destroyInstancedGeometry();
        MG_SAFE_DELETE(mOgreEntityTemplate);
    }

    //-----------------------------------------------------------------------
    void EntityGroup::preRendering()
    {
        EntityGroupInstancesMap::iterator iter = mEntityGroupInstanceMap.begin();
        for (;iter!=mEntityGroupInstanceMap.end();iter++)
        {
            EntityGroupInstancesList& list = iter->second;
            for ( UInt i=0;i<list.size();i++)
            {
                list[i]->preRendering();
            }
        }
    }

    //-----------------------------------------------------------------------
    void EntityGroup::postRendering()
    {
        EntityGroupInstancesMap::iterator iter = mEntityGroupInstanceMap.begin();
        for (;iter!=mEntityGroupInstanceMap.end();iter++)
        {
            EntityGroupInstancesList& list = iter->second;
            for ( UInt i=0;i<list.size();i++)
            {
                list[i]->postRendering();
            }
        }  
    }

	//-----------------------------------------------------------------------
	Bool EntityGroup::update( Flt delta )
	{
        if (mOgreEntityTemplate)
        {
            mOgreEntityTemplate->update( delta );
        }
        
        EntityGroupInstancesMap::iterator iter = mEntityGroupInstanceMap.begin();
        for (;iter!=mEntityGroupInstanceMap.end();iter++)
        {
            EntityGroupInstancesList& list = iter->second;
            for ( UInt i=0;i<list.size();i++)
            {
                list[i]->update( delta );
            }
        }
		return true;
	}

    //-----------------------------------------------------------------------
    void EntityGroup::refresh()
    {
        applyVisibleFlag();
    }

    //-----------------------------------------------------------------------
    void EntityGroup::applyRenderConfig()
    {
        if ( mOgreEntityTemplate )
        {
            mOgreEntityTemplate->applyRenderConfig();
            applyVisibleFlag();
        }
    }

    //-----------------------------------------------------------------------
    void EntityGroup::applyVisibleFlag()
    {
        if ( mOgreEntityTemplate )
        {
            InstancedGeometry::BatchInstanceMap::iterator iter = mInstancedGeometry->mBatchInstanceMap.begin();
            for ( ;iter!=mInstancedGeometry->mBatchInstanceMap.end(); iter++ )
            {
                InstancedGeometry::BatchInstance* batchInstance = iter->second;
                if (batchInstance)
                {
                    uint32 flag = mOgreEntityTemplate->getOgreEntity()->getVisibilityFlags();
                    batchInstance->setVisibilityFlags( flag );
                    batchInstance->setCastShadows( true );
                }
            }
        }
    }
    //-----------------------------------------------------------------------
    SceneObjectTypes EntityGroup::getType()
    {
        return SOT_ENTITY_GROUP; 
    }
    //-----------------------------------------------------------------------
    ISceneNode* EntityGroup::getSceneNode()
    {
        return NULL;
    }
	//-----------------------------------------------------------------------
	UInt EntityGroup::getEntityNum()
	{
		return mEntityGroupInstanceList.size();
	}
	//-----------------------------------------------------------------------
	IEntity* EntityGroup::getEntity(UInt index)
	{
		if ( index>=mEntityGroupInstanceList.size() )
            return NULL;
		return mEntityGroupInstanceList[index];
	}
    //-----------------------------------------------------------------------
    OgreEntityWrapper* EntityGroup::getModelObject()
    {
        return mOgreEntityTemplate;
    }
    //-----------------------------------------------------------------------
    void EntityGroup::createInstancedGeometry( CChar* entityName, ModelDeclaration* modelDeclaration, UInt num )
    {
        mInstancedGeometry = mScene->getOgreSceneManager()->createInstancedGeometry(entityName);
        if ( mInstancedGeometry )
        {
            mInstancedGeometry->setBatchInstanceDimensions(Vector3(1000000, 1000000, 1000000));
            mInstancedGeometry->setOrigin(Vector3(-500000, -500000, -500000));
            mInstancedGeometry->setCastShadows(true);

            Ogre::Entity *ent = mOgreEntityTemplate->getOgreEntity();

            UInt bones = 1;
            if (ent->hasSkeleton())
                bones = ent->getSkeleton()->getNumBones();

            // per batch
            UInt maxObjectsPerBatch = 80 / bones;
            if (maxObjectsPerBatch==0)
                return;

            ///////////////////////////////////////////////////////////////////////////////////////////////////////////

            const size_t batchSize = (num > maxObjectsPerBatch) ? maxObjectsPerBatch :num;
            for(size_t i = 0; i < batchSize ; i++)
            {
                mInstancedGeometry->addEntity(ent, Vector3::ZERO);
            }

            ///////////////////////////////////////////////////////////////////////////////////////////////////////////

            // build
            mInstancedGeometry->build();

            ///////////////////////////////////////////////////////////////////////////////////////////////////////////

            // batch
            UInt batchCount = 1;
            UInt entityNum = num;
            while(entityNum>maxObjectsPerBatch)
            {
                batchCount++;
                entityNum-=maxObjectsPerBatch;
            }

            for (size_t k = 0; k < batchCount-1; k++)
            {
                mInstancedGeometry->addBatchInstance();
            }
            
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////

            uint32 flag = ent->getVisibilityFlags();
            InstancedGeometry::BatchInstanceMap::iterator iter = mInstancedGeometry->mBatchInstanceMap.begin();
            for ( ;iter!=mInstancedGeometry->mBatchInstanceMap.end(); iter++ )
            {
                InstancedGeometry::BatchInstance* batchInstance = iter->second;
                if (batchInstance)
                {
                    //设置绑定实体对象的管理者
                    batchInstance->setUserAny( Any((ISceneObject*)this) );
                    ////设置查询标志位
                    batchInstance->setQueryFlags(Scene::getQueryMask(this->getType()));
                    // 设置可见度
                    batchInstance->setVisibilityFlags( flag );
                }
            }
            
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////

            InstancedGeometry::BatchInstanceIterator regIt = mInstancedGeometry->getBatchInstanceIterator();
            size_t k = 0;
            while (regIt.hasMoreElements ())
            {

                InstancedGeometry::BatchInstance *r = regIt.getNext();

                r->setListener( this );

                EntityGroupInstancesList& list = mEntityGroupInstanceMap[r];

                InstancedGeometry::BatchInstance::InstancedObjectIterator bit = r->getObjectIterator();
                int j = 0;
                while(bit.hasMoreElements())
                {
                    InstancedGeometry::InstancedObject* obj = bit.getNext();

                    EntityGroupInstance* groupInstance = MG_NEW EntityGroupInstance(modelDeclaration->path,this,obj,r);

			        String intanceName = Str(entityName) + mEntityInstanceNameGenerator.generate();
                    groupInstance->setName( intanceName );

					//根据模型表初始化缩放
					Vec3 scale(modelDeclaration->zoonX,modelDeclaration->zoonY,modelDeclaration->zoonZ);
					groupInstance->getSceneNode()->setInitScale(scale);

					//根据模型表初始化悬空
					groupInstance->getSceneNode()->setPositionOffset(Vec3(0,modelDeclaration->offsetY,0));
                
                    mEntityGroupInstanceList.push_back(groupInstance);
                    list.push_back( groupInstance );
                    
                    ++j;
                }
                k++;

            }
            mInstancedGeometry->setVisible(true);
        }
    }
    //-----------------------------------------------------------------------
    void EntityGroup::destroyInstancedGeometry()
    {
        if ( mInstancedGeometry )
        {
            EntityGroupInstancesMap::iterator iter = mEntityGroupInstanceMap.begin();
            for (;iter!=mEntityGroupInstanceMap.end();iter++)
            {
                EntityGroupInstancesList& list = iter->second;
                for ( UInt i=0;i<list.size();i++)
                {
                    MG_SAFE_DELETE( list[i] );
                }
            }
            mEntityGroupInstanceMap.clear();
            mEntityGroupInstanceList.clear();

            mScene->getOgreSceneManager()->destroyInstancedGeometry( mInstancedGeometry->getName() );
            mInstancedGeometry = NULL;
        }
    }
	 //-----------------------------------------------------------------------
	Scene* EntityGroup::getScene()
	{
		return mScene;
	}
   
    //-----------------------------------------------------------------------
    bool EntityGroup::objectRendering(const MovableObject* obj, const Ogre::Camera* cam)
    {
        EntityGroupInstancesList& list = mEntityGroupInstanceMap[obj];
        for ( UInt i=0;i<list.size();i++)
        {
            list[i]->setRenderingDirty();
        }
        return true;
    }

}

