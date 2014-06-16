/******************************************************************************/
#ifndef _SHADOWMANAGER_H_
#define _SHADOWMANAGER_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "IShadow.h"

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	// 阴影构建者
	/******************************************************************************/
	class ShadowMaker
	{
	public:

        /// 得到阴影的摄像机配置
        virtual ShadowCameraSetupPtr        getCurrShadowCameraSetupPtr() = 0;

		/// 得到阴影的PSSM摄像机配置
		virtual PSSMShadowCameraSetup*      getPSSMShadowCameraSetup() = 0;

        virtual void                        shadowTextureCasterPreViewProj(Ogre::Light* light, Ogre::Camera* camera, size_t iteration) = 0;
        virtual void                        shadowTexturesUpdated(size_t numberOfShadowTextures) = 0;
    };


    /******************************************************************************/
    //阴影管理
    /******************************************************************************/
    class ShadowManager : public IShadowManager
    {
    public:
        ShadowManager(Scene* scene);
        virtual ~ShadowManager();

    public:

		////////////////////////////////////////////////////////////////////////////////////

		/// 更新
		void                        update( Flt delta );
		// 初始化和反初始化
		void						initialize();
		void						unInitialize();

        ////////////////////////////////////////////////////////////////////////////////////

        static Bool                 isUsePSSM();

		////////////////////////////////////////////////////////////////////////////////////

        /// 响应配置更改
        void                        applyRenderConfig();

        // 设置地形阴影偏移
        virtual void	            setTerrainShadowOffset(Flt offset);
		// 生成光照贴图
		virtual void	            genarateLightingMap();
		
		////////////////////////////////////////////////////////////////////////////////////

		ShadowMaker*				getActiveShadowMaker();
		DynamicShadowMaker*			getDynamicShadowMaker();
		LightingMapMaker*			getLightingMapMaker();

		////////////////////////////////////////////////////////////////////////////////////
		
    public:

        void                        shadowTextureCasterPreViewProj(Ogre::Light* light, Ogre::Camera* camera, size_t iteration);
        void                        shadowTexturesUpdated(size_t numberOfShadowTextures);

    protected:

		void						test();

        void                        reloadCasterMat( Str name );
        void                        reloadReceiveMat( Str name );

    protected:		

        Scene* mScene;
    
		DynamicShadowMaker*			mDynamicShadowMaker;
		LightingMapMaker*			mLightingMapMaker;
    };

}

/******************************************************************************/

#endif
