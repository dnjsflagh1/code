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
	// ��Ӱ������
	/******************************************************************************/
	class ShadowMaker
	{
	public:

        /// �õ���Ӱ�����������
        virtual ShadowCameraSetupPtr        getCurrShadowCameraSetupPtr() = 0;

		/// �õ���Ӱ��PSSM���������
		virtual PSSMShadowCameraSetup*      getPSSMShadowCameraSetup() = 0;

        virtual void                        shadowTextureCasterPreViewProj(Ogre::Light* light, Ogre::Camera* camera, size_t iteration) = 0;
        virtual void                        shadowTexturesUpdated(size_t numberOfShadowTextures) = 0;
    };


    /******************************************************************************/
    //��Ӱ����
    /******************************************************************************/
    class ShadowManager : public IShadowManager
    {
    public:
        ShadowManager(Scene* scene);
        virtual ~ShadowManager();

    public:

		////////////////////////////////////////////////////////////////////////////////////

		/// ����
		void                        update( Flt delta );
		// ��ʼ���ͷ���ʼ��
		void						initialize();
		void						unInitialize();

        ////////////////////////////////////////////////////////////////////////////////////

        static Bool                 isUsePSSM();

		////////////////////////////////////////////////////////////////////////////////////

        /// ��Ӧ���ø���
        void                        applyRenderConfig();

        // ���õ�����Ӱƫ��
        virtual void	            setTerrainShadowOffset(Flt offset);
		// ���ɹ�����ͼ
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
