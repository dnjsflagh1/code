/******************************************************************************/
#include "stdafx.h"
#include "MGSceneNode.h"
#include "PUEffect.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "ParticleUniverseRibbonTrailRenderer.h"
/******************************************************************************/

namespace MG
{

	//-----------------------------------------------------------------------
	PUEffect::PUEffect(CChar* PUName, CChar* effectTemplateName, Scene* scene,Bool isAutoDestroy,Bool isAutoStart)
		:mScene(scene)
		,mPUParticleSystem(NULL)
		,mIsAutoDestroy(isAutoDestroy)
		,mEffectTemplateName(effectTemplateName)
		,mStartDelta(0)
		,mEffectResID(0)
		,mIsStart(false)
	{
		DYNAMIC_ASSERT(mScene!=NULL);

		setName(PUName);

		createPUEffect(effectTemplateName, isAutoStart );
	}
	//-----------------------------------------------------------------------
	PUEffect::PUEffect( CChar* PUName, U32 effectResID, Scene* scene,Bool isAutoDestroy /*= true*/, Bool isAutoStart /*= true*/ )
		:mScene(scene)
		,mPUParticleSystem(NULL)
		,mIsAutoDestroy(isAutoDestroy)
		,mEffectTemplateName("")
		,mStartDelta(0)
		,mEffectResID(effectResID)
		,mIsStart(false)
	{
		DYNAMIC_ASSERT(mScene!=NULL);

		setName(PUName);

		createPUEffect(effectResID, isAutoStart );
	}
	//-----------------------------------------------------------------------
	PUEffect::~PUEffect()
	{
		destroyPUEffect();
	}
	//-----------------------------------------------------------------------
	void PUEffect::createPUEffect(CChar* effectTemplateName, Bool isAutoStart)
	{
		ParticleUniverse::ParticleSystemManager* pManager = ParticleUniverse::ParticleSystemManager::getSingletonPtr();
		DYNAMIC_ASSERT(pManager!=NULL);

		mPUParticleSystem = pManager->createParticleSystem( Str8(getName().c_str()), effectTemplateName, mScene->getOgreSceneManager());

		if ( mPUParticleSystem )
		{
			//设置绑定实体对象的管理者
			mPUParticleSystem->setUserAny( Any((ISceneObject*)this) );

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

		////开始特效
		//if ( isAutoStart )
		//	start();

	}
	//-----------------------------------------------------------------------
	void PUEffect::createPUEffect( U32 effectResID, Bool isAutoStart )
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

		////开始特效
		//if ( isAutoStart )
		//	start();

	}
	//-----------------------------------------------------------------------
	void PUEffect::destroyPUEffect()
	{
		if ( mPUParticleSystem )
		{
			mPUParticleSystem->stop();
			ParticleUniverse::ParticleSystemManager* pManager = ParticleUniverse::ParticleSystemManager::getSingletonPtr();
			pManager->destroyParticleSystem(mPUParticleSystem,mScene->getOgreSceneManager());
			mPUParticleSystem = NULL;

		}
		//销毁实体节点
		MG_SAFE_DELETE( mSceneNode );
	}

	//-----------------------------------------------------------------------
	MGSceneNode* PUEffect::getSceneNode()
	{
		return mSceneNode;
	}

	//-----------------------------------------------------------------------
	SceneObjectTypes PUEffect::getType()
	{
		return EOT_PU;
	}
	//-----------------------------------------------------------------------
	void PUEffect::start()
	{
		if ( mPUParticleSystem )
		{
			mPUParticleSystem->start();

			mStartDelta = 0;

			mIsStart = true;
		}
	}
	//-----------------------------------------------------------------------
	void PUEffect::stop()
	{
		if ( mPUParticleSystem )
		{
			mPUParticleSystem->stop();

			mStartDelta = 0;

			mIsStart = false;
		}
	}
	//-----------------------------------------------------------------------
	Bool PUEffect::update( Flt delta )
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
	void PUEffect::setScale( Vec3 scale )
	{
		if ( mPUParticleSystem )
		{
			mPUParticleSystem->setScale( Vector3( scale.x, scale.y, scale.z) );
		}
	}
	//-----------------------------------------------------------------------
	void PUEffect::setTrailLength( U32 length )
	{
		if (!mPUParticleSystem)
			return;

		ParticleUniverse::ParticleTechnique* technique = 
			mPUParticleSystem->getTechnique(0);

		if (!technique)
			return;

		ParticleUniverse::ParticleRenderer* render =
			technique->getRenderer();

		if (!render)
			return;

		Str renderType = render->getRendererType();
		if (StrCmp(renderType.c_str(), "RibbonTrail") == 0)
		{
			ParticleUniverse::RibbonTrailRenderer* trailRender = 
				dynamic_cast<ParticleUniverse::RibbonTrailRenderer*>(render);

			trailRender->setTrailLength(length);
		}

	}
	//-----------------------------------------------------------------------
	void PUEffect::setTrailWidth( U32 width )
	{
		if (!mPUParticleSystem)
			return;

		ParticleUniverse::ParticleTechnique* technique = 
			mPUParticleSystem->getTechnique(0);

		if (!technique)
			return;

		ParticleUniverse::ParticleRenderer* render =
			technique->getRenderer();

		if (!render)
			return;

		Str renderType = render->getRendererType();
		if (StrCmp(renderType.c_str(), "RibbonTrail") == 0)
		{
			ParticleUniverse::RibbonTrailRenderer* trailRender = 
				dynamic_cast<ParticleUniverse::RibbonTrailRenderer*>(render);

			trailRender->setTrailWidth(width);
		}

	}
	//-----------------------------------------------------------------------
	void PUEffect::setTrailLiveTime( Flt time )
	{
		if (!mPUParticleSystem)
			return;

		ParticleUniverse::ParticleTechnique* technique = 
			mPUParticleSystem->getTechnique(0);

		if (!technique)
			return;

		ParticleUniverse::ParticleEmitter* emitter = 
			technique->getEmitter(0);

		if (!emitter)
			return;

		emitter->setTotalTimeToLive(time);
	}
	//-----------------------------------------------------------------------
	Bool PUEffect::bind(IEntity* parent, Bool attachToModel)
	{
		return true;
	}	

	//-----------------------------------------------------------------------
	Bool PUEffect::initialised()
	{
		return true;
	}

}

