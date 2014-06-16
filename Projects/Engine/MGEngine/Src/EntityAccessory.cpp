/******************************************************************************/
#include "stdafx.h"
#include "EntityAccessory.h"
#include "EngineMain.h"
#include "Scene.h"
#include "ISceneObject.h"
#include "ResourceManager.h"
#include "AnimationController.h"
#include "MaterialManager.h"
#include "Display.h"
/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------
    EntityAccessoryCollection::EntityAccessoryCollection( IEntity* parent, Scene* scene )
        :mParent(parent)
        ,mScene(scene)
    {

    }

    //-----------------------------------------------------------------------
    EntityAccessoryCollection::~EntityAccessoryCollection()
    {
        detachAllObject();
    }

    //-----------------------------------------------------------------------
    void EntityAccessoryCollection::update( Flt delta )
    {
    }

    //-----------------------------------------------------------------------
    void EntityAccessoryCollection::attachObject( Str name, IEntityAccessory& accessory )
    {
        if ( isValidAttachObject( accessory ) )
        {
            if ( getAttachObject( name ) == NULL )
            {
                prepareAttachObject( accessory );
                mAttachs[name] = accessory;
            }
        }
    }

    //-----------------------------------------------------------------------
    void EntityAccessoryCollection::detachObject( Str name )
    {
        std::map< Str, IEntityAccessory >::iterator iter = mAttachs.find( name );
        if (iter!=mAttachs.end())
        {
            IEntityAccessory& accessory = iter->second;
            prepareDetachObject( accessory );

            mAttachs.erase( iter );
        }
    }

    //-----------------------------------------------------------------------
    IEntityAccessory* EntityAccessoryCollection::getAttachObject( Str name )
    {
        std::map< Str, IEntityAccessory >::iterator iter = mAttachs.find( name );
        if (iter!=mAttachs.end())
        {
            return &(iter->second);
        }
        return NULL;
    }

    //-----------------------------------------------------------------------
    UInt EntityAccessoryCollection::getAttachObjectCount()
    {
        return mAttachs.size();
    }

    //-----------------------------------------------------------------------
    IEntityAccessory* EntityAccessoryCollection::getAttachObject(UInt index)
    {
        std::map<Str, IEntityAccessory>::iterator iter =  mAttachs.begin();
        std::advance(iter, index);

        if ( iter != mAttachs.end() )
            return &(iter->second);

        return NULL;
    }

    //-----------------------------------------------------------------------
    void EntityAccessoryCollection::detachAllObject()
    {
        std::map< Str, IEntityAccessory >::iterator iter = mAttachs.begin();
        for ( ; iter!=mAttachs.end() ; iter ++ )
        {
            IEntityAccessory& accessory = iter->second;
            prepareDetachObject( accessory );
        }
        mAttachs.clear();
    }

	//-----------------------------------------------------------------------
	void EntityAccessoryCollection::updateObjectScale( IEntityAccessory& accessory )
	{
		if ( mParent->getType() == SOT_ENTITY )
		{
			Vec3 scale = Vec3(1.0f, 1.0f, 1.0f);

			if ( mParent->getSceneNode() )
				mParent->getSceneNode()->getScale(scale);

			if ( accessory.sceneObject->getType() == SOT_EFFECTENTITY )
			{
				IEffectEntity* effect = dynamic_cast<IEffectEntity*>(accessory.sceneObject);
				if ( effect )
				{
					effect->setScale( scale );
				}
			}
			else
			{
				if ( accessory.sceneObject->getSceneNode() )
				{
					accessory.sceneObject->getSceneNode()->setScale( scale );
				}
			}

				
		}
	}

    //-----------------------------------------------------------------------
    void EntityAccessoryCollection::updateObjectLocation( IEntityAccessory& accessory )
    {
		Vec3 parentPos ;
		Qua parentQua ;
		Vec3 accessoryPos;
		Qua accessoryQuaternion;

		if ( !accessory.bindBoneName.empty() )
		{		
			//if ( mParent->getType()  )
			{
				///////////////////////////////////////////////////////////////////////////////////////////////////

				//Qua  localQua;
				//Vec3 localOffset;

				//localQua = mParent->getModelObject()->getBoneOrientation(accessory.bindBoneName.c_str());
				//localOffset = mParent->getModelObject()->getBonePosition(accessory.bindBoneName.c_str());

				////计算出该骨骼相对玩家NODE的偏移和旋转
				//accessoryPos = localOffset + localQua * accessory.relativePosition;
				//accessoryQuaternion = localQua * accessory.relativeQuaternion;

				//mParent->getSceneNode()->getPosition( parentPos );	
				//mParent->getSceneNode()->getOrientation( parentQua );
				//
				////通过骨骼相对玩家NODE的偏移旋转求出最终结果
				//accessoryPos = parentPos + parentQua * accessoryPos;
				//accessoryQuaternion = parentQua * accessoryQuaternion;

				/////////////////////////////////////////////////////////////////////////////////////////////////
				Vec3 parentPos = mParent->getModelObject()->getBoneWorldPosition(accessory.bindBoneName.c_str());
				Qua parentQua = mParent->getModelObject()->getBoneWorldOrientation(accessory.bindBoneName.c_str());

				parentQua.normalise();

				accessoryPos = parentPos + parentQua * accessory.relativePosition;
				accessoryQuaternion = parentQua * accessory.relativeQuaternion;
				///////////////////////////////////////////////////////////////////////////////////////////////////
			
			}
		}
		else
		{
			mParent->getSceneNode()->getPosition( parentPos );	
			mParent->getSceneNode()->getOrientation( parentQua );
			accessoryPos = parentPos + parentQua * accessory.relativePosition;
			accessoryQuaternion = parentQua * accessory.relativeQuaternion;
		}

        accessory.sceneObject->getSceneNode()->setOrientation( accessoryQuaternion );
        accessory.sceneObject->getSceneNode()->setPosition( accessoryPos );
    }

    //-----------------------------------------------------------------------
    void EntityAccessoryCollection::onAnimationStart(CChar* animName)
    {
        std::map< Str, IEntityAccessory >::iterator iter = mAttachs.begin();
        for ( ; iter!=mAttachs.end() ; iter ++ )
        {
            IEntityAccessory& accessory = iter->second;
            if ( accessory.isSyncAnimation )
            {
                if ( ( accessory.sceneObject->getType() == SOT_ENTITY ) || ( accessory.sceneObject->getType() == SOT_ENTITY_GROUP_UNIT ) )
                {
                    IEntity* entity = (IEntity*)accessory.sceneObject;

                    if ( entity )
                    {
                        entity->getAnimationController()->play( animName );
                    }
                }
            }
        }
    }

    //-----------------------------------------------------------------------
    void EntityAccessoryCollection::onAnimationStop(CChar* animName)
    {
        std::map< Str, IEntityAccessory >::iterator iter = mAttachs.begin();
        for ( ; iter!=mAttachs.end() ; iter ++ )
        {
            IEntityAccessory& accessory = iter->second;
            if ( accessory.isSyncAnimation )
            {
                if ( ( accessory.sceneObject->getType() == SOT_ENTITY ) || ( accessory.sceneObject->getType() == SOT_ENTITY_GROUP_UNIT ) )
                {
                    IEntity* entity = (IEntity*)accessory.sceneObject;

                    if ( entity )
                    {
                        entity->getAnimationController()->stop( animName );
                    }
                }
            }
        }
    }

    //-----------------------------------------------------------------------
    void EntityAccessoryCollection::onAnimationLoop(CChar* animName)
    {
    }
	
	//-----------------------------------------------------------------------
	void EntityAccessoryCollection::onRemove( ISceneNode* node )
	{
		//如果是别的监管对象试图析构SceneNode, 我这边就直接从map去掉SceneNode即可。
		//这时候记得千万不能去删除SceneNode中的监听器， 因为现在就在这个监听器指针的函数中。
		for ( std::map< Str, IEntityAccessory >::iterator iter = mAttachs.begin(); iter != mAttachs.end();)
		{
			IEntityAccessory& entityAccessory = iter->second;

			if ( !entityAccessory.sceneObject || entityAccessory.sceneObject->getSceneNode() == node )
				iter = mAttachs.erase( iter );
			else
				iter++;
		}
	}

    //-----------------------------------------------------------------------
    void EntityAccessoryCollection::prepareAttachObject( IEntityAccessory& accessory )
    {
		// 如果是非托管实体， 加入监听器。 
		if ( /*accessory.isDepositLifeTime == false && */
			accessory.sceneObject && accessory.sceneObject->getSceneNode() )
		{
			Str listener_name = mParent->getName() + "_EntityAccessoryCollectionListener";
			accessory.sceneObject->getSceneNode()->addSceneNodeLisitener( listener_name, this );

			listener_name = "SceneObjectControllerListener";
			accessory.sceneObject->getSceneNode()->addSceneNodeLisitener( listener_name, 
				mScene->getSceneObjectController(false) );

			/*if ( !accessory.bindBoneName.empty() )
			{
				Entity* parent = dynamic_cast<Entity*>(mParent);
				Ogre::Entity* ogreParent = parent->getModelObject()->getOgreEntity();
				
				Entity* attacher = dynamic_cast<Entity*>(accessory.sceneObject);
				Ogre::Entity* ogreAttacher = attacher->getModelObject()->getOgreEntity();

				ogreAttacher->detachFromParent();

				ogreParent->attachObjectToBone( accessory.bindBoneName, ogreAttacher);
			}*/
		}
    }
    
    //-----------------------------------------------------------------------
    void EntityAccessoryCollection::prepareDetachObject( IEntityAccessory& accessory )
    {
        accessory.sceneObject->getSceneNode()->setVisible( false );

		////////////////////////////////////////////////////////////////////////////////////

		// 移除监听
		Str listener_name = mParent->getName() + "_EntityAccessoryCollectionListener";
		accessory.sceneObject->getSceneNode()->removeSceneNodeLisitener( listener_name );

		listener_name = "SceneObjectControllerListener";
		accessory.sceneObject->getSceneNode()->removeSceneNodeLisitener( listener_name );

		////////////////////////////////////////////////////////////////////////////////////

		// 托管实体， 直接销毁。
        if ( accessory.isDepositLifeTime )
        {   
            if ( accessory.sceneObject->getType() == SOT_ENTITY )
            {
                mScene->destroyEntity( accessory.sceneObject->getName().c_str() );
            }else
            if ( accessory.sceneObject->getType() == SOT_EFFECTENTITY )
            {
                mScene->destroyEffectEntity( accessory.sceneObject->getName().c_str() );
            }
        }
    }

    //-----------------------------------------------------------------------
    Bool EntityAccessoryCollection::isValidAttachObject( IEntityAccessory& accessory )
    {
        if ( accessory.sceneObject->getType() == SOT_ENTITY )
            return true;
        if ( accessory.sceneObject->getType() == SOT_EFFECTENTITY )
            return true;
        if ( accessory.sceneObject->getType() == SOT_ENTITY_GROUP_UNIT )
            return true;

		// 如果是里面有相同的ISceneObject, 就返回FALSE
		for ( std::map< Str, IEntityAccessory >::iterator iter = mAttachs.begin(); iter != mAttachs.end(); iter++ )
		{
			IEntityAccessory& accessory_in_list = iter->second;
			if ( accessory.sceneObject->getName() == accessory_in_list.sceneObject->getName() )
			{
				return false;
			}
		}

        return false;
    }
	//-----------------------------------------------------------------------
	void EntityAccessoryCollection::postFindVisibleObjects()
	{
		if ( mAttachs.empty() == false )
		{
			std::map< Str, IEntityAccessory >::iterator iter = mAttachs.begin();
			for ( ; iter!=mAttachs.end() ; iter ++ )
			{
				updateObjectLocation( iter->second );
				updateObjectScale( iter->second );
			}
		}
	}
}

