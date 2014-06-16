/******************************************************************************/
#ifndef _DYNAMICSHADOWMAKER_H_
#define _DYNAMICSHADOWMAKER_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "ShadowManager.h"

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	// 动态阴影生成
	/******************************************************************************/
	class DynamicShadowMaker : public ShadowMaker
	{
	public:
		DynamicShadowMaker(Scene* scene);
		virtual ~DynamicShadowMaker();

		/// 响应配置更改
		void                        applyRenderConfig();

        ShadowCameraSetupPtr        getCurrShadowCameraSetupPtr();
		PSSMShadowCameraSetup*      getPSSMShadowCameraSetup();

	public:

		// 初始化和反初始化
		void						initialize();
		void						unInitialize();

	public:

        virtual void                shadowTextureCasterPreViewProj(Ogre::Light* light, Ogre::Camera* camera, size_t iteration);
        virtual void                shadowTexturesUpdated(size_t numberOfShadowTextures);

	protected:

		Scene* mScene;
	    MovablePlane*                   mPlane;
		ShadowCameraSetupPtr	        mCurrentShadowCameraSetup;
		PSSMShadowCameraSetup*	        mPSSMShadowCameraSetup;
	};

}

/******************************************************************************/

#endif
