/******************************************************************************/
#include "stdafx.h"
#include "Entity.h"
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
    EffectEntity::EffectEntity(CChar* entityName, CChar* effectFileName, Scene* scene,Bool isAutoDestroy)
        :mScene(scene)
        ,mEffectFileName(effectFileName)
        ,mOgreParticleSystem(NULL)
        ,mPUParticleSystem(NULL)
        ,mIsAutoDestroy(isAutoDestroy)
    {
        DYNAMIC_ASSERT(mScene!=NULL);

        setName(entityName);

        //createOgreEffect( effectFileName );
        createPUEffect( effectFileName );
    }

    //-----------------------------------------------------------------------
    EffectEntity::~EffectEntity()
    {
        //destroyOgreEffect();
        destroyPUEffect();
    }

    //-----------------------------------------------------------------------

	void EffectEntity::setRenderGroup( uint8 groupid )
	{
		if ( mPUParticleSystem )
		{
			mPUParticleSystem->setRenderGroupID(groupid);
		}
	}

	//-----------------------------------------------------------------------
    void EffectEntity::createOgreEffect(CChar* effectFileName)
    {
        mOgreParticleSystem = mScene->getOgreSceneManager()->createParticleSystem(getName(), mEffectFileName);
        
        DYNAMIC_ASSERT(mOgreParticleSystem!=NULL);
        
        if ( mOgreParticleSystem )
        {
            //设置绑定实体对象的管理者
            mOgreParticleSystem->setUserAny( Any((ISceneObject*)this) );

            //设置查询标志位
            mOgreParticleSystem->setQueryFlags(Scene::getQueryMask(this->getType()));

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
    void EffectEntity::createPUEffect(CChar* effectFileName)
    {
        ParticleUniverse::ParticleSystemManager* pManager = ParticleUniverse::ParticleSystemManager::getSingletonPtr();
        DYNAMIC_ASSERT(pManager!=NULL);
		
        std::string name = getName().c_str();
        std::string fileName = effectFileName;

		mPUParticleSystem = pManager->createParticleSystem( std::string(getName().c_str()), std::string(effectFileName), mScene->getOgreSceneManager());

        if ( mPUParticleSystem )
        {
            //设置绑定实体对象的管理者
            mPUParticleSystem->setUserAny( Any((ISceneObject*)this) );

            //创建实体节点
            mSceneNode = MG_NEW MGSceneNode(mScene->getOgreSceneManager()->getRootSceneNode(),mScene);

            //绑定实体
            mSceneNode->getOgreSceneNode()->attachObject( mPUParticleSystem );

            //开始
            mPUParticleSystem->start();
        }
    }

    //-----------------------------------------------------------------------
    void EffectEntity::destroyPUEffect()
    {
        if ( mPUParticleSystem )
        {
            ParticleUniverse::ParticleSystemManager* pManager = ParticleUniverse::ParticleSystemManager::getSingletonPtr();
            pManager->destroyParticleSystem(mPUParticleSystem,mScene->getOgreSceneManager());
            mPUParticleSystem = NULL;
        }
        //销毁实体节点
        MG_SAFE_DELETE( mSceneNode );
    }

    //-----------------------------------------------------------------------
    ISceneNode* EffectEntity::getSceneNode()
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
                    if ( mPUParticleSystem->getState() == ParticleUniverse::ParticleSystem::PSS_STOPPED )
                    {
                        return false;
                    }
                }
            }
        }
        return true;
    }   
}

