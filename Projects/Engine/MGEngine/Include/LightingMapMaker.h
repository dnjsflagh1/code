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
    //������ͼ����
    /******************************************************************************/
    class LightingMapMaker : public ShadowMaker, public Ogre::RenderTargetListener
    {
    public:
        LightingMapMaker(Scene* scene);
        virtual ~LightingMapMaker();

		/////////////////////////////////////////////////////////////////

		// �Ƿ���
		Bool                        isActive();
        // �Ƿ���
        Bool                        isTest();

        // ���õ�����Ӱƫ��
        void                        setTerrainShadowOffset(Flt offset);
		// ���ɹ�����ͼ
		void                        genarate( Bool isTest = false );

        /// �õ���Ӱ�����������
        ShadowCameraSetupPtr        getCurrShadowCameraSetupPtr();
		PSSMShadowCameraSetup*      getPSSMShadowCameraSetup();

		/////////////////////////////////////////////////////////////////

		/// ��Ӧ���ø���
		void                        applyRenderConfig();
        /// ��Ӧ���ø���
        void                        applyCameraConfig();

		/////////////////////////////////////////////////////////////////

		MaterialPtr&                getTerrainMaterialPtr(TerrainSurfaceType type);
        Bool                        getTerrainCastShadows(TerrainSurfaceType type);

		/////////////////////////////////////////////////////////////////

	public:

		// ��ʼ��
		void						initialize();
        // ����ʼ��
		void						unInitialize();

	protected:

        void						test();

        /////////////////////////////////////////////////////////////////////////////////

        // ���泡��״̬
        void                        saveSceneState();
        // ��ԭ����״̬
        void                        revertSceneState();

        /////////////////////////////////////////////////////////////////////////////////
        // ���ɵ�����ͼ
        void						genarateTerrainLightingMap();
        // ���ɹ�����ͼ
        void						genarateSurfaceLightingMap( TerrainSurface* surface );
        

        /////////////////////////////////////////////////////////////////////////////////

        // ������Ⱦ������ͼ
        void                        loadRenderTexture();
        // ж����Ⱦ������ͼ
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
