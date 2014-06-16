#include "ParticleUniversePCH.h"
#include "ParticleUniverseRendererManager.h"

#ifndef PARTICLE_UNIVERSE_EXPORTS
#define PARTICLE_UNIVERSE_EXPORTS
#endif

template<> ParticleUniverse::ParticleRendererManager* ParticleUniverse::Singleton<ParticleUniverse::ParticleRendererManager>::ms_Singleton = 0;
namespace ParticleUniverse
{
	/*******************************************************************/
	// RendererWrapper
	/*******************************************************************/
	RendererWrapper::RendererWrapper()
	{
		mRenderer = 0;
		mRefCount = 0;
	}

	RendererWrapper::~RendererWrapper()
	{

	}

	ParticleRenderer* RendererWrapper::getRenderer()
	{
		return mRenderer;
	}

	void RendererWrapper::setRenderer(ParticleRenderer* renderer)
	{
		 mRenderer = renderer;
	}
	/*******************************************************************/
	// ParticleRendererManager
	/*******************************************************************/
	ParticleRendererManager::ParticleRendererManager()
	{
		mRendererWrapper = NULL;
	}

	ParticleRendererManager::~ParticleRendererManager()
	{
		mRendererMap.clear();
		mGroupRenderer.clear();
	}

	ParticleRenderer* ParticleRendererManager::createRenderer(ParticleTechnique* technique, uint8 groupID,const String& rendererType)
	{
		ParticleRenderer* renderer = findRendererInMap(groupID, technique);
		if (!renderer)
		{
			const String PUNameIndex = getPSNameIndex(technique);
			if (PUNameIndex == "")
			{
				return ParticleSystemManager::getSingletonPtr()->createRenderer(rendererType);
			}
			else
			{
				mRendererWrapper = new RendererWrapper();
				ParticleRenderer* renderer = ParticleSystemManager::getSingletonPtr()->createRenderer(rendererType);
				mRendererWrapper->setRenderer(renderer);
				mRendererWrapper->mRefCount++;

				mRendererMap[PUNameIndex] = mRendererWrapper;
				mGroupRenderer[groupID] = mRendererMap;

				return mRendererWrapper->getRenderer();
			}
		}
		else
		{
			return renderer;
		}
	}

	void ParticleUniverse::ParticleRendererManager::removeRenderer(ParticleRenderer* renderer )
	{
		GroupRendererIterator groupit;
		RendererMapIterator mapit;

		uint8 groupid = renderer->getParentTechnique()->getParentSystem()->getRenderGroupID();
		const String PUNameIndex = getPSNameIndex(renderer->getParentTechnique());
		groupit = mGroupRenderer.find(groupid);
		if (groupit != mGroupRenderer.end())
		{
			mapit = groupit->second.find(PUNameIndex);
			if ( (mapit != groupit->second.end()) && (mapit->second->getRenderer() == renderer))
			{
				RendererWrapper* wrapper = mapit->second;
				if (wrapper->mRefCount > 0)
				{
					wrapper->mRefCount--;
				}
				else
				{
					mRendererMap.erase(mapit);
					mGroupRenderer.erase(groupit);

					mapit->second->setRenderer(0);
					mapit->second->getRenderer()->setParentTechnique(0);
				}
			}
		}
	}

	void ParticleRendererManager::destroyRenderer(ParticleRenderer* renderer)
	{
		GroupRendererIterator groupit;
		RendererMapIterator mapit;

		uint8 groupid = renderer->getParentTechnique()->getParentSystem()->getRenderGroupID();
		const String PUNameIndex = getPSNameIndex(renderer->getParentTechnique());
		groupit = mGroupRenderer.find(groupid);
		if (groupit != mGroupRenderer.end())
		{
			mapit = groupit->second.find(PUNameIndex);
			if ( (mapit != groupit->second.end()) && (mapit->second->getRenderer() == renderer))
			{
				RendererWrapper* wrapper = mapit->second;
				if (wrapper->mRefCount > 0)
				{
					wrapper->mRefCount--;
				}
				else
				{
					mRendererMap.erase(mapit);
					mGroupRenderer.erase(groupit);

					ParticleSystemManager::getSingletonPtr()->destroyRenderer(mapit->second->getRenderer());
					mapit->second->setRenderer(0);
				}
			}
		}
	}

	bool ParticleRendererManager::isRendererInitialised(ParticleRenderer* renderer)
	{
		ParticleRenderer* pRenderer = findRendererInMap(renderer);
		if (pRenderer)
		{
			return pRenderer->isRendererInitialised();
		}
		else
			return false;
	}

	void ParticleRendererManager::setRendererInitialised(ParticleRenderer* renderer, bool rendererInitialised)
	{
		ParticleRenderer* pRenderer = findRendererInMap(renderer);
		if (pRenderer)
		{
			pRenderer->setRendererInitialised(rendererInitialised);
		}
	}

	void ParticleRendererManager::_prepareRenderer(ParticleRenderer* renderer)
	{
		ParticleRenderer* pRenderer = findRendererInMap(renderer);
		if (pRenderer)
		{
			if (pRenderer && !pRenderer->isRendererInitialised())
			{
				pRenderer->_prepare(pRenderer->getParentTechnique());
				pRenderer->setRendererInitialised(true);
			}
		}
	}

	void ParticleRendererManager::_unprepareRenderer(ParticleRenderer* renderer)
	{
		ParticleRenderer* pRenderer = findRendererInMap(renderer);
		if (pRenderer)
		{
			if (pRenderer && pRenderer->isRendererInitialised())
			{
				pRenderer->_unprepare(pRenderer->getParentTechnique());
				pRenderer->setRendererInitialised(false);
			}
		}
	}

	Ogre::String ParticleRendererManager::getPSNameIndex( ParticleTechnique* technique )
	{
		ParticleSystem* system = technique->getParentSystem();
		int num = system->getNumTechniques();
		char TechIndex[10];
		for (int i = 0; i < num; i++)
		{
			if ( technique == system->getTechnique(i) )
			{
				itoa(i, TechIndex, 10);
				break;
			}
		}
		
		String systemName = system->getTemplateName();
		if ( systemName == "")
			return systemName;
		else
			return (systemName + "_" +TechIndex);
	}

	ParticleRenderer* ParticleRendererManager::findRendererInMap( ParticleRenderer* renderer )
	{
		GroupRendererIterator groupit;
		RendererMapIterator mapit;

		uint8 groupid = renderer->getParentTechnique()->getParentSystem()->getRenderGroupID();
		const String PUNameIndex = getPSNameIndex(renderer->getParentTechnique());

		groupit = mGroupRenderer.find(groupid);
		if (groupit != mGroupRenderer.end())
		{
			mapit = groupit->second.find(PUNameIndex);
			if ( (mapit != groupit->second.end()) && (mapit->second->getRenderer() == renderer))
			{
				return mapit->second->getRenderer();
			}
		}
	}

	ParticleRenderer* ParticleRendererManager::findRendererInMap( uint8 groupid, ParticleTechnique* technique )
	{
		GroupRendererIterator groupit;
		RendererMapIterator mapit;

		groupit = mGroupRenderer.find(groupid);
		if (groupit != mGroupRenderer.end())
		{
			const String PUNameIndex = getPSNameIndex(technique);
			mapit = groupit->second.find(PUNameIndex);
			if ( mapit != groupit->second.end() )
			{
				mapit->second->mRefCount++;
				return mapit->second->getRenderer();
			}
		}

		return NULL;
	}

	ParticleRendererManager& ParticleRendererManager::getSingleton( void )
	{
		assert( ms_Singleton );  return ( *ms_Singleton );
	}

	ParticleRendererManager* ParticleRendererManager::getSingletonPtr( void )
	{
		return ms_Singleton;
	}

}
