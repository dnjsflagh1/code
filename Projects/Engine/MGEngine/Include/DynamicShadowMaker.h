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
	// ��̬��Ӱ����
	/******************************************************************************/
	class DynamicShadowMaker : public ShadowMaker
	{
	public:
		DynamicShadowMaker(Scene* scene);
		virtual ~DynamicShadowMaker();

		/// ��Ӧ���ø���
		void                        applyRenderConfig();

        ShadowCameraSetupPtr        getCurrShadowCameraSetupPtr();
		PSSMShadowCameraSetup*      getPSSMShadowCameraSetup();

	public:

		// ��ʼ���ͷ���ʼ��
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
