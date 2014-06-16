/*
-----------------------------------------------------------------------------------------------
2012.4.24
作者:陈南
文件:管理Render.根据材质和渲染组别来选择Render.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_PARTICLE_RENDER_MANAGER_H__
#define __PU_PARTICLE_RENDER_MANAGER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseSingleton.h"
#include "ParticleUniverseParticlePool.h"
#include "ParticleUniverseRenderer.h"
#include <map>

namespace ParticleUniverse
{
	class RendererWrapper
	{
	public:
		RendererWrapper();
		~RendererWrapper();

		ParticleRenderer* getRenderer();
		void setRenderer(ParticleRenderer* renderer);

	public:
		int				  mRefCount;
	private:
		ParticleRenderer* mRenderer;
		
	};

	class _ParticleUniverseExport ParticleRendererManager : public Singleton<ParticleRendererManager>
	{
		typedef map<const String, RendererWrapper*> RendererMap;
		typedef map<uint8, RendererMap> GroupRenderer;

		typedef RendererMap::iterator RendererMapIterator;
		typedef GroupRenderer::iterator GroupRendererIterator;
	public:
		ParticleRendererManager();

		~ParticleRendererManager();
		
		// 创建Renderer
		ParticleRenderer* createRenderer(ParticleTechnique* technique, uint8 groupID, const String& rendererType);

		// 移除Renderer
		void removeRenderer(ParticleRenderer* renderer);

		// 销毁Renderer
		void destroyRenderer(ParticleRenderer* renderer);

		// 获取/设置 renderer是否初始化.
		bool isRendererInitialised(ParticleRenderer* renderer);
		void setRendererInitialised(ParticleRenderer* renderer, bool rendererInitialised);

		// 
		void _prepareRenderer(ParticleRenderer* renderer);

		//
		void _unprepareRenderer(ParticleRenderer* renderer);

		//
		String getPSNameIndex(ParticleTechnique* technique);

		//
		ParticleRenderer* findRendererInMap(ParticleRenderer* renderer);

		//
		ParticleRenderer* findRendererInMap(uint8 groupid, ParticleTechnique* technique);

		// 获取指针
		static ParticleRendererManager& getSingleton (void);

		// 获取对象
		static ParticleRendererManager* getSingletonPtr (void);

	private:
		// 存储的Renderer列表
		GroupRenderer		mGroupRenderer;
		RendererMap			mRendererMap;
		RendererWrapper*	mRendererWrapper;
	};
}



#endif