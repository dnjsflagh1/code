/******************************************************************************/
#include "stdafx.h"
#include "Entity.h"
#include "IEntityAccessory.h"
#include "EngineMain.h"
#include "MGSceneNode.h"
#include "Scene.h"
#include "ISceneObject.h"
#include "ResourceManager.h"
#include "AnimationController.h"
/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------

    // 特效创建数量
    UInt EffectEntity::EffectCreateCount = 0;
    // 特效销毁数量
    UInt EffectEntity::EffectDestroyCount = 0;

    //-----------------------------------------------------------------------
    EffectEntity::EffectEntity(CChar* entityName, U32 effectResID, Scene* scene,Bool isAutoDestroy,Bool isAutoStart)
        :mScene(scene)
        ,mEffectResID(effectResID)
        ,mOgreParticleSystem(NULL)
        ,mPUParticleSystem(NULL)
        ,mIsAutoDestroy(isAutoDestroy)
        ,mStartDelta(0)
        ,mIsStart(false)
    {
        DYNAMIC_ASSERT(mScene!=NULL);

        setName(entityName);

        //createOgreEffect( effectFileName );
        createPUEffect( mEffectResID, isAutoStart );
    }

    //-----------------------------------------------------------------------
    EffectEntity::~EffectEntity()
    {
        //destroyOgreEffect();
        destroyPUEffect();
    }

    //-----------------------------------------------------------------------
    void EffectEntity::createOgreEffect(U32 effectResID)
    {
		EffectResourceDeclaration* effectElmResDecls = ResourceManager::getSingletonPtr()->getEffectResourceDeclaration(effectResID);

		if ( !effectElmResDecls ||
			effectElmResDecls->fileName.empty() ||
			effectElmResDecls->filePath.empty() )
		{
			return;
		}

        mOgreParticleSystem = mScene->getOgreSceneManager()->createParticleSystem(getName(), effectElmResDecls->fileName);
        
        DYNAMIC_ASSERT(mOgreParticleSystem!=NULL);
        
        if ( mOgreParticleSystem )
        {
            //设置绑定实体对象的管理者
            mOgreParticleSystem->setUserAny( Any((ISceneObject*)this) );

            //设置查询标志位
            mOgreParticleSystem->setQueryFlags(Scene::getQueryMask(this->getType()));

            // 设置可见度
            mOgreParticleSystem->setVisibilityFlags( SOV_EFFECTENTITY );

            //创建实体节点
            mSceneNode = MG_NEW MGSceneNode(mScene->getOgreSceneManager()->getRootSceneNode(),mScene);

            //绑定实体
            mSceneNode->getOgreSceneNode()->attachObject( mOgreParticleSystem );
        }
    }

    //-----------------------------------------------------------------------
    void EffectEntity::destroyOgreEffect()
    {
        //销毁实体对象
        if ( mOgreParticleSystem )
        {
            mScene->getOgreSceneManager()->destroyParticleSystem(mOgreParticleSystem);
            mOgreParticleSystem = NULL;
        }

        //销毁实体节点
        MG_SAFE_DELETE( mSceneNode );
    }

    //-----------------------------------------------------------------------
    void EffectEntity::createPUEffect(U32 effectResID,Bool isAutoStart)
    {
		mEffectResID = 0;

		EffectResourceDeclaration* effectElmResDecls = ResourceManager::getSingletonPtr()->getEffectResourceDeclaration(effectResID);

		if ( !effectElmResDecls ||
			effectElmResDecls->filePath.empty() ||
			effectElmResDecls->fileName.empty() )
		{
			return;
		}

        ParticleUniverse::ParticleSystemManager* pManager = ParticleUniverse::ParticleSystemManager::getSingletonPtr();
        DYNAMIC_ASSERT(pManager!=NULL);

		Ogre::String effectSystemName = effectElmResDecls->fileName;
		mPUParticleSystem = pManager->createParticleSystem( Str8(getName().c_str()), effectSystemName, mScene->getOgreSceneManager());

        if ( mPUParticleSystem )
        {
			//设置特效的资源模版ID;
			mEffectResID = effectResID;

            //设置绑定实体对象的管理者
            mPUParticleSystem->setUserAny( Any((ISceneObject*)this) );

            //设置查询标志位
            mPUParticleSystem->setQueryFlags(Scene::getQueryMask(this->getType()));

            // 设置可见度
            mPUParticleSystem->setVisibilityFlags( SOV_EFFECTENTITY );

			//特效设置紧缩的包围盒
			mPUParticleSystem->setTightBoundingBox(true);

            //创建实体节点
            mSceneNode = MG_NEW MGSceneNode(mScene->getOgreSceneManager()->getRootSceneNode(),mScene);

            //绑定实体
            mSceneNode->getOgreSceneNode()->attachObject( mPUParticleSystem );
        }else
        {
            DYNAMIC_ASSERT(false);
        }

		//开始特效
        if ( isAutoStart )
		    start();

        //EffectCreateCount++;
    }

    //-----------------------------------------------------------------------
    void EffectEntity::destroyPUEffect()
    {
        if ( mPUParticleSystem )
        {
            mPUParticleSystem->stop();
            ParticleUniverse::ParticleSystemManager* pManager = ParticleUniverse::ParticleSystemManager::getSingletonPtr();
            pManager->destroyParticleSystem(mPUParticleSystem,mScene->getOgreSceneManager());
            mPUParticleSystem = NULL;

            //EffectDestroyCount++;
        }
        //销毁实体节点
        MG_SAFE_DELETE( mSceneNode );
    }

    //-----------------------------------------------------------------------
    MGSceneNode* EffectEntity::getSceneNode()
    {
        return mSceneNode;
    }
    
    //-----------------------------------------------------------------------
    SceneObjectTypes EffectEntity::getType()
    {
        return SOT_EFFECTENTITY;
    }
    //-----------------------------------------------------------------------
    void EffectEntity::start()
    {
        if ( mPUParticleSystem )
        {
            mPUParticleSystem->start();

            mStartDelta = 0;

            mIsStart = true;
        }
    }
    //-----------------------------------------------------------------------
    Bool EffectEntity::update( Flt delta )
    {
        if ( mSceneNode )
        {
            mSceneNode->update( delta ); 

            if ( mIsAutoDestroy )
            {
                if ( mPUParticleSystem )
                {
                    ParticleUniverse::ParticleSystem::ParticleSystemState state = mPUParticleSystem->getState();
                    if (  state == ParticleUniverse::ParticleSystem::PSS_STOPPED )
                    {
                        return false;
                    }

                    if ( mIsStart )
                    {
                        mStartDelta += delta;
                        if ( mStartDelta > 5 )
                            return false;
                    }
                }
            }
        }
        return true;
    } 
	//-----------------------------------------------------------------------
	void EffectEntity::setScale( Vec3 scale )
	{
		if ( mPUParticleSystem )
		{
			mPUParticleSystem->setScale( Vector3( scale.x, scale.y, scale.z) );
		}
	}
	//-----------------------------------------------------------------------
	Bool EffectEntity::bind(IEntity* parent, Bool attachToModel)
	{
		bool result = false;

		if ( parent && 
			parent->getModelObject() &&  
			mPUParticleSystem && 
			mSceneNode )
		{
			EffectResourceDeclaration* effectElmResDecls = ResourceManager::getSingletonPtr()->getEffectResourceDeclaration(mEffectResID);

			if ( !effectElmResDecls )
				return false;

			IEntityAccessory entityAccessory;
			entityAccessory.isDepositLifeTime = false;
			entityAccessory.isSyncAnimation = false;
			entityAccessory.relativePosition = Vec3(0,0,0);
			entityAccessory.relativeQuaternion = Qua(1,0,0,0);
			entityAccessory.bindBoneName.clear();
			entityAccessory.sceneObject = this;

			if ( effectElmResDecls->bindBoxHeightRate > 0 )
			{
				Vec3 pos = parent->getModelObject()->getCenterPosition((Flt)effectElmResDecls->bindBoxHeightRate / 1000.0f, attachToModel);
				entityAccessory.relativePosition = pos;
				result = true;
			}
			else if ( !effectElmResDecls->bindBoneName.empty() )
			{
				entityAccessory.bindBoneName = effectElmResDecls->bindBoneName;
				result = true;
			}
			
			if ( result )
			{
				if ( attachToModel )
				{
					result = mScene->createEntityDynamicAccessorys( parent, getName().c_str(), mEffectResID, SOT_EFFECTENTITY, &entityAccessory);
				}
				else
				{
					mSceneNode->setPosition( entityAccessory.relativePosition );
				}
			}
		}
		return result;
	}	

	//-----------------------------------------------------------------------
	Bool EffectEntity::initialised()
	{
		return mEffectResID != 0;
	}

}

