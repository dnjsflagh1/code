/******************************************************************************/
#ifndef _LIGHTINGMAPMAKER_H_
#define _LIGHTINGMAPMAKER_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "ShadowManager.h"
#include "ITerrain.h"

/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    //光照贴图生成
    /******************************************************************************/
    class LightingMapMaker : public ShadowMaker, public Ogre::RenderTargetListener
    {
    public:
        LightingMapMaker(Scene* scene);
        virtual ~LightingMapMaker();

		/////////////////////////////////////////////////////////////////

		// 是否活动中
		Bool                        isActive();
        // 是否活动中
        Bool                        isTest();

        // 设置地形阴影偏移
        void                        setTerrainShadowOffset(Flt offset);
		// 生成光照贴图
		void                        genarate( Bool isTest = false );

        /// 得到阴影的摄像机配置
        ShadowCameraSetupPtr        getCurrShadowCameraSetupPtr();
		PSSMShadowCameraSetup*      getPSSMShadowCameraSetup();

		/////////////////////////////////////////////////////////////////

		/// 响应配置更改
		void                        applyRenderConfig();
        /// 响应配置更改
        void                        applyCameraConfig();

		/////////////////////////////////////////////////////////////////

		MaterialPtr&                getTerrainMaterialPtr(TerrainSurfaceType type);
        Bool                        getTerrainCastShadows(TerrainSurfaceType type);

		/////////////////////////////////////////////////////////////////

	public:

		// 初始化
		void						initialize();
        // 反初始化
		void						unInitialize();

	protected:

        void						test();

        /////////////////////////////////////////////////////////////////////////////////

        // 保存场景状态
        void                        saveSceneState();
        // 还原场景状态
        void                        revertSceneState();

        /////////////////////////////////////////////////////////////////////////////////
        // 生成地形贴图
        void						genarateTerrainLightingMap();
        // 生成光照贴图
        void						genarateSurfaceLightingMap( TerrainSurface* surface );
        

        /////////////////////////////////////////////////////////////////////////////////

        // 加载渲染光照贴图
        void                        loadRenderTexture();
        // 卸载渲染光照贴图
        void                        unLoadRenderTexture();

        /////////////////////////////////////////////////////////////////////////////////

	protected:

        /// Overridden from RenderTargetListener
        virtual void			    preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);
        virtual void			    postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);
        virtual void                shadowTextureCasterPreViewProj(Ogre::Light* light, Ogre::Camera* camera, size_t iteration);
        virtual void                shadowTexturesUpdated(size_t numberOfShadowTextures);

    protected:

        Scene* mScene;
		Bool	mActive;
        Bool    mIsTest;
		ShadowCameraSetupPtr	mCurrentShadowCameraSetup;
		PSSMShadowCameraSetup*	mPSSMShadowCameraSetup;

		MaterialPtr				mTerrainMaterialPtr;

        Flt                     mLightingMapCameraHeight;

        TexturePtr              mRenderLightingMapTexture;
        Viewport*               mRenderLightingMapTextureViewport;
        uint32                  mCurrCasterVisibilityMask;
        Flt                     mTerrainShadowOffset;

        ShadowTechnique         mCurrShadowTechnique;
        Bool                    mCurrAutoAspectRatio;
        Flt                     mCurrAspectRatio;
        Radian                  mCurrFov;
        Ogre::Quaternion        mCurrCamQua;
        Ogre::Vector3           mCurrCamPos;

    };

}

/******************************************************************************/

#endif
