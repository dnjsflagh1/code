/******************************************************************************/
/******************************************************************************/

#include "stdafx.h"
#include "ShadowManager.h"
#include "Scene.h"
#include "Display.h"
#include "Display.h"
#include "DynamicShadowMaker.h"
#include "LightingMapMaker.h"

/******************************************************************************/

namespace MG
{
    //-----------------------------------------------------------------------
    ShadowManager::ShadowManager(Scene* scene)
        :mScene(scene)
		,mLightingMapMaker(NULL)
        ,mDynamicShadowMaker(NULL)
    {   
		mDynamicShadowMaker = MG_NEW DynamicShadowMaker( mScene );
		mLightingMapMaker	= MG_NEW LightingMapMaker( mScene );
    }

    //-----------------------------------------------------------------------
    ShadowManager::~ShadowManager()
    {
		MG_SAFE_DELETE( mDynamicShadowMaker );
		MG_SAFE_DELETE( mLightingMapMaker );
    }

 
    //-----------------------------------------------------------------------
    void  ShadowManager::update( Flt delta )
    {
		
    }

	//-----------------------------------------------------------------------
	void ShadowManager::initialize()
	{
		
	}

	//-----------------------------------------------------------------------
	void ShadowManager::unInitialize()
	{
		mLightingMapMaker->unInitialize();
		mDynamicShadowMaker->unInitialize();
	}

    //-----------------------------------------------------------------------
    Bool ShadowManager::isUsePSSM()
    {
        Bool isPssm = false;

		ShadowType st = Display::getSingleton().getShadowType();

        if ( (st == SCL_UNIFORM_DEPTH_TEXTURE) || 
             (st == SCL_UNIFORM_FOCUSED_DEPTH_TEXTURE) || 
             (st == SCL_LISPSM_DEPTH_TEXTURE) || 
             (st == SCL_PLANE_OPTIMALDEPTH_TEXTURE) )
        {
            isPssm = false;
        }else
        if ( (st == SCL_PSSM_DIFFUSE_TEXTURE) || 
             (st == SCL_PSSM_DEPTH_TEXTURE) )
        {
            isPssm = true;
        }

        return isPssm;
    }

    //-----------------------------------------------------------------------
    void  ShadowManager::applyRenderConfig()
    {
		if ( mLightingMapMaker->isActive() == false )
		    mDynamicShadowMaker->applyRenderConfig();

        //test();
    }

	//-----------------------------------------------------------------------
	ShadowMaker* ShadowManager::getActiveShadowMaker()
	{
		if ( mLightingMapMaker->isActive() )
			return mLightingMapMaker;
		return mDynamicShadowMaker;
	}

	//-----------------------------------------------------------------------
	DynamicShadowMaker* ShadowManager::getDynamicShadowMaker()
	{
		return mDynamicShadowMaker;
	}

	//-----------------------------------------------------------------------
	LightingMapMaker* ShadowManager::getLightingMapMaker()
	{
		return mLightingMapMaker;
	}

    //-----------------------------------------------------------------------
    void ShadowManager::setTerrainShadowOffset(Flt offset)
    {
        mLightingMapMaker->setTerrainShadowOffset( offset );
    }

    //-----------------------------------------------------------------------
    void ShadowManager::genarateLightingMap()
    {
        Bool isTest = false;

		mLightingMapMaker->genarate( isTest );

        if ( isTest )
            test();
    }

    //-----------------------------------------------------------------------
    void ShadowManager::shadowTextureCasterPreViewProj(Ogre::Light* light, Ogre::Camera* camera, size_t iteration)
    {
        getActiveShadowMaker()->shadowTextureCasterPreViewProj( light, camera, iteration );
    }

    //-----------------------------------------------------------------------
    void ShadowManager::shadowTexturesUpdated(size_t numberOfShadowTextures)
    {
        getActiveShadowMaker()->shadowTexturesUpdated( numberOfShadowTextures );
    }

    //-----------------------------------------------------------------------
    void ShadowManager::reloadCasterMat( Str name )
    {
        {
            MaterialPtr mat = Ogre::MaterialManager::getSingleton().getByName(name);

            Technique* technique = mat->getTechnique(0);
            if ( technique )
            {
                GpuProgramPtr vertexProgram = technique->getPass(0)->getVertexProgram();
                GpuProgramPtr fragmentProgram = technique->getPass(0)->getFragmentProgram();

                //vertexProgram->resetCompileError();
                vertexProgram->reload();

                //fragmentProgram->resetCompileError();
                fragmentProgram->reload();
            }

            mat->reload();
        }
    }

    //-----------------------------------------------------------------------
    void ShadowManager::reloadReceiveMat( Str name )
    {
        PSSMShadowCameraSetup* pssmCam = mScene->getShadowManager()->getActiveShadowMaker()->getPSSMShadowCameraSetup();
        //PSSMShadowCameraSetup* pssmCam = mPSSMShadowCameraSetup;
        if ( pssmCam )
        {
            MaterialPtr mat = Ogre::MaterialManager::getSingleton().getByName(name);

            Technique* apply_tech = mat->getTechnique(0);
            if ( apply_tech )
            {
                Pass* apply_pass = apply_tech->getPass(0);
                if ( apply_pass )
                {
                    GpuProgramPtr fragmentProgram = apply_pass->getFragmentProgram();
                    if ( fragmentProgram.isNull() == false )
                    {
                        //GpuProgramParametersSharedPtr gp = fragmentProgram->getDefaultParameters();
                        GpuProgramParametersSharedPtr gp = apply_pass->getFragmentProgramParameters();

                        gp->setIgnoreMissingParams( true );

                        if ( gp.isNull() == false )
                        {
                            Vector4 splitPoints;
                            const PSSMShadowCameraSetup::SplitPointList& splitPointList = pssmCam->getSplitPoints();
                            for (int i = 0; i < 3; ++i)
                            {
                                splitPoints[i] = splitPointList[i];
                            }
                            gp->setNamedConstant("pssmSplitPoints", splitPoints);
                        }
                    }
                }
            }	
        }
    }

	//-----------------------------------------------------------------------
	void ShadowManager::test()
	{

#ifdef _DEBUG
        
        Ogre::Camera* cam = mScene->getActiveCamera()->getOgreCamera();

        if ( getLightingMapMaker()->isActive() )
        {
            //test
           // cam->setOrthoWindowWidth( 128 );
           // cam->setOrthoWindowHeight( 128 );
            ///cam->setPosition( 192, 100, -64 );
        }

        if ( getLightingMapMaker()->isActive() )
		{
			Vec4 sbs = Display::getSingleton().getScaleBiasSpecular();

			PSSMShadowCameraSetup* pssmCam = getActiveShadowMaker()->getPSSMShadowCameraSetup();
            Vector3 camPos = mScene->getActiveCamera()->getOgreCamera()->getPosition();
            Flt camNearClipDistance     = mScene->getActiveCamera()->getOgreCamera()->getNearClipDistance();

			//mScene->getOgreSceneManager()->setShadowDirLightTextureOffset(sbs.w);// default 0.6


           // Flt camShadowFarDistance = 10000;
            Flt camShadowFarDistance = sbs.w;
            

            //mScene->getOgreSceneManager()->setShadowFarDistance(camShadowFarDistance);
            //pssmCam->calculateSplitPoints(3, camNearClipDistance, camShadowFarDistance);


            ////////////////////////////////////////////////////////////////////////////////

           // mScene->getOgreSceneManager()->setShadowDirLightTextureOffset( camPos.y / camShadowFarDistance );
		    //mScene->getOgreSceneManager()->setSh adowDirLightTextureOffset(1);// default 0.6


			////////////////////////////////////////////////////////////////////////////////

			//pssmCam->setSplitPadding( sbs.w );

			//pssmCam->calculateSplitPoints(3, sbs.x, sbs.y);

			//pssmCam->setOptimalAdjustFactor(0, sbs.w);
			//pssmCam->setOptimalAdjustFactor(1, sbs.w * 0.5 );
			//pssmCam->setOptimalAdjustFactor(2, sbs.w * 0.25 );

			//pssmCam->setCameraLightDirectionThreshold(Ogre::Degree(sbs.w));

			//pssmCam->setUseSimpleOptimalAdjust( Int(sbs.x) == 1 );

			//pssmCam->setUseAggressiveFocusRegion( Int(sbs.y) == 1 );

   //         mScene->getOgreSceneManager()->setShadowDirLightTextureOffset(sbs.z);

		}


        ////////////////////////////////////////////////////////////////

        {
            reloadReceiveMat( "MG/Terrain/Shadow/Receive/LightingMap");
            reloadCasterMat( "MG/Terrain/DepthShadow/Caster");
            reloadCasterMat( "MG/DepthShadow/Caster");
            reloadCasterMat( "MG/DepthShadow/Caster/Alpha");
            reloadCasterMat( "MG/Entity/Diffuse/Shadow");
            
        }

#endif
	}

    
}

