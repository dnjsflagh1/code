/******************************************************************************/
/******************************************************************************/

#include "stdafx.h"
#include "DynamicShadowMaker.h"
#include "Scene.h"
#include "Display.h"

/******************************************************************************/

namespace MG
{
	//-----------------------------------------------------------------------
	DynamicShadowMaker::DynamicShadowMaker(Scene* scene)
		:mScene(scene)
		,mPSSMShadowCameraSetup(NULL)
        ,mPlane(NULL)
	{

	}
	//-----------------------------------------------------------------------
	DynamicShadowMaker::~DynamicShadowMaker()
	{
		unInitialize();
	}


	//-----------------------------------------------------------------------
	PSSMShadowCameraSetup* DynamicShadowMaker::getPSSMShadowCameraSetup()
	{
		return mPSSMShadowCameraSetup;
	}

    //-----------------------------------------------------------------------
    ShadowCameraSetupPtr DynamicShadowMaker::getCurrShadowCameraSetupPtr()
    {
        return mCurrentShadowCameraSetup;
    }

	//-----------------------------------------------------------------------
	void  DynamicShadowMaker::applyRenderConfig()
	{
        ///////////////////////////////////////////////////////////////////////////////////////

		initialize();

        ///////////////////////////////////////////////////////////////////////////////////////

		ShadowType st = Display::getSingleton().getShadowType();
        Ogre::Camera* cam           = mScene->getActiveCamera()->getOgreCamera();
        Ogre::SceneManager* scene   = mScene->getOgreSceneManager();

        ///////////////////////////////////////////////////////////////////////////////////////

        if ( st == SCL_NONE )
        {
            // No Shadow
            mScene->getOgreSceneManager()->setShadowTechnique( SHADOWTYPE_NONE );
        }else
        if ((st == SCL_UNIFORM_DEPTH_TEXTURE) || 
            (st == SCL_UNIFORM_FOCUSED_DEPTH_TEXTURE) || 
            (st == SCL_LISPSM_DEPTH_TEXTURE) || 
            (st == SCL_PLANE_OPTIMALDEPTH_TEXTURE) )
        {
            mScene->getOgreSceneManager()->setShadowTechnique( SHADOWTYPE_TEXTURE_ADDITIVE_INTEGRATED );

            mScene->getOgreSceneManager()->setShadowTextureSettings(1024, 1);

            //mScene->getOgreSceneManager()->setShadowTexturePixelFormat(PF_X8R8G8B8);
            mScene->getOgreSceneManager()->setShadowTexturePixelFormat(PF_FLOAT32_R);

            mScene->getOgreSceneManager()->setShadowTextureSelfShadow(true);	
            mScene->getOgreSceneManager()->setShadowCasterRenderBackFaces(true);


            scene->setShadowFarDistance( 200 );

        }else
        if ( (st == SCL_PSSM_DIFFUSE_TEXTURE) || 
            (st == SCL_PSSM_DEPTH_TEXTURE) )
        {
            if ( st == SCL_PSSM_DIFFUSE_TEXTURE )
            {
                //PSSM
                //NoDepthShadow
                mScene->getOgreSceneManager()->setShadowTechnique( SHADOWTYPE_TEXTURE_ADDITIVE_INTEGRATED );

                // 3 textures per directional light (PSSM)
                mScene->getOgreSceneManager()->setShadowTextureCountPerLightType(Ogre::Light::LT_DIRECTIONAL, 3);

                mScene->getOgreSceneManager()->setShadowTextureCount(3);
                mScene->getOgreSceneManager()->setShadowTextureConfig(0, 2048, 2048, PF_X8B8G8R8);
                mScene->getOgreSceneManager()->setShadowTextureConfig(1, 1024, 1024, PF_X8B8G8R8);
                mScene->getOgreSceneManager()->setShadowTextureConfig(2, 1024, 1024, PF_X8B8G8R8);
                mScene->getOgreSceneManager()->setShadowTextureSelfShadow(false);
                mScene->getOgreSceneManager()->setShadowCasterRenderBackFaces(false);
            }else
            if ( st == SCL_PSSM_DEPTH_TEXTURE )
            {
                //PSSM
                //DepthShadow
                mScene->getOgreSceneManager()->setShadowTechnique( SHADOWTYPE_TEXTURE_ADDITIVE_INTEGRATED );

                // 3 textures per directional light (PSSM)
                mScene->getOgreSceneManager()->setShadowTextureCountPerLightType(Ogre::Light::LT_DIRECTIONAL, 3);

                mScene->getOgreSceneManager()->setShadowTextureCount(3);
                mScene->getOgreSceneManager()->setShadowTextureConfig(0, 2048, 2048, PF_FLOAT32_R);
                mScene->getOgreSceneManager()->setShadowTextureConfig(1, 1024, 1024, PF_FLOAT32_R);
                mScene->getOgreSceneManager()->setShadowTextureConfig(2, 1024, 1024, PF_FLOAT32_R);
                mScene->getOgreSceneManager()->setShadowTextureSelfShadow(true);
                mScene->getOgreSceneManager()->setShadowCasterRenderBackFaces(true);
            }

            //PSSM
            if ( mPSSMShadowCameraSetup )
            {
                ///////////////////////////////////////////////////////////////////////////////////////

                Flt camNearClipDistance     = mScene->getActiveCamera()->getOgreCamera()->getNearClipDistance();

                ///////////////////////////////////////////////////////////////////////////////////////

                Flt shadowFarDistance = cam->getNearClipDistance() * Ogre::Math::Sqrt( 1 + Ogre::Math::Sqrt(cam->getAspectRatio()));
                shadowFarDistance = 3000;
                scene->setShadowFarDistance( shadowFarDistance );

                ///////////////////////////////////////////////////////////////////////////////////////

                //Flt mCameraHeight = 100;
                //scene->setShadowDirLightTextureOffset( mCameraHeight / shadowFarDistance );
                //scene->setShadowDirLightTextureOffset( 0.6 );

                ///////////////////////////////////////////////////////////////////////////////////////

                // shadow camera setup
                mPSSMShadowCameraSetup->setSplitPadding(camNearClipDistance);
                //mPSSMShadowCameraSetup->setSplitPadding(10);

                ///////////////////////////////////////////////////////////////////////////////////////

                mPSSMShadowCameraSetup->calculateSplitPoints(3, camNearClipDistance, shadowFarDistance);
                //mPSSMShadowCameraSetup->calculateSplitPoints(3, 1, 6000);

                ///////////////////////////////////////////////////////////////////////////////////////

                mPSSMShadowCameraSetup->setOptimalAdjustFactor(0, 2);
                mPSSMShadowCameraSetup->setOptimalAdjustFactor(1, 1);
                mPSSMShadowCameraSetup->setOptimalAdjustFactor(2, 0.5);

                ///////////////////////////////////////////////////////////////////////////////////////

                mPSSMShadowCameraSetup->setCameraLightDirectionThreshold(Ogre::Degree(5));

                ///////////////////////////////////////////////////////////////////////////////////////
            }
        }

	}

	//-----------------------------------------------------------------------
	void  DynamicShadowMaker::initialize()
	{
        ///////////////////////////////////////////////////////////////////////////////////////

        unInitialize();

        ///////////////////////////////////////////////////////////////////////////////////////

		ShadowType st = Display::getSingleton().getShadowType();
       
		if ( st == SCL_NONE )
		{
			return ;
		}else
        if ( st == SCL_UNIFORM_DEPTH_TEXTURE )
        {
            mCurrentShadowCameraSetup = ShadowCameraSetupPtr(MG_NEW DefaultShadowCameraSetup());
        }else
        if ( st == SCL_UNIFORM_FOCUSED_DEPTH_TEXTURE )
        {
            mCurrentShadowCameraSetup = ShadowCameraSetupPtr(MG_NEW FocusedShadowCameraSetup());
        }else
        if ( st == SCL_LISPSM_DEPTH_TEXTURE )
        {
            mCurrentShadowCameraSetup = ShadowCameraSetupPtr(MG_NEW LiSPSMShadowCameraSetup());
        }else    
        if ( st == SCL_PLANE_OPTIMALDEPTH_TEXTURE )
        {
            // Floor plane (use POSM plane def)
            if ( !mPlane )
            {
                mPlane = MG_NEW MovablePlane("*mPlane");
                mPlane->normal = Vector3::UNIT_Y;
                mPlane->d = 107;
            }

            mCurrentShadowCameraSetup = ShadowCameraSetupPtr(MG_NEW PlaneOptimalShadowCameraSetup(mPlane));
        }else   
        if ( st == SCL_PSSM_DIFFUSE_TEXTURE || st == SCL_PSSM_DEPTH_TEXTURE )
        {
            mCurrentShadowCameraSetup = ShadowCameraSetupPtr(MG_NEW PSSMShadowCameraSetup());
        }

		mScene->getOgreSceneManager()->setShadowCameraSetup(mCurrentShadowCameraSetup);
	}

	//-----------------------------------------------------------------------
	void  DynamicShadowMaker::unInitialize()
	{
		mPSSMShadowCameraSetup = NULL;
	}

    //-----------------------------------------------------------------------
    void DynamicShadowMaker::shadowTextureCasterPreViewProj(Ogre::Light* light, Ogre::Camera* camera, size_t iteration)
    {
		camera->getViewport()->setVisibilityMask( SOV_DYNAMIC_SHADOW );
    }

    //-----------------------------------------------------------------------
    void DynamicShadowMaker::shadowTexturesUpdated(size_t numberOfShadowTextures)
    {
    }

}








