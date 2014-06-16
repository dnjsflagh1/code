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

    // ��Ч��������
    UInt EffectEntity::EffectCreateCount = 0;
    // ��Ч��������
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
            //���ð�ʵ�����Ĺ�����
            mOgreParticleSystem->setUserAny( Any((ISceneObject*)this) );

            //���ò�ѯ��־λ
            mOgreParticleSystem->setQueryFlags(Scene::getQueryMask(this->getType()));

            // ���ÿɼ���
            mOgreParticleSystem->setVisibilityFlags( SOV_EFFECTENTITY );

            //����ʵ��ڵ�
            mSceneNode = MG_NEW MGSceneNode(mScene->getOgreSceneManager()->getRootSceneNode(),mScene);

            //��ʵ��
            mSceneNode->getOgreSceneNode()->attachObject( mOgreParticleSystem );
        }
    }

    //-----------------------------------------------------------------------
    void EffectEntity::destroyOgreEffect()
    {
        //����ʵ�����
        if ( mOgreParticleSystem )
        {
            mScene->getOgreSceneManager()->destroyParticleSystem(mOgreParticleSystem);
            mOgreParticleSystem = NULL;
        }

        //����ʵ��ڵ�
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
			//������Ч����Դģ��ID;
			mEffectResID = effectResID;

            //���ð�ʵ�����Ĺ�����
            mPUParticleSystem->setUserAny( Any((ISceneObject*)this) );

            //���ò�ѯ��־λ
            mPUParticleSystem->setQueryFlags(Scene::getQueryMask(this->getType()));

            // ���ÿɼ���
            mPUParticleSystem->setVisibilityFlags( SOV_EFFECTENTITY );

			//��Ч���ý����İ�Χ��
			mPUParticleSystem->setTightBoundingBox(true);

            //����ʵ��ڵ�
            mSceneNode = MG_NEW MGSceneNode(mScene->getOgreSceneManager()->getRootSceneNode(),mScene);

            //��ʵ��
            mSceneNode->getOgreSceneNode()->attachObject( mPUParticleSystem );
        }else
        {
            DYNAMIC_ASSERT(false);
        }

		//��ʼ��Ч
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
        //����ʵ��ڵ�
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

