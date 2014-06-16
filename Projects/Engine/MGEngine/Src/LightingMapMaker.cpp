/******************************************************************************/
/******************************************************************************/

#include "stdafx.h"
#include "LightingMapMaker.h"
#include "Scene.h"
#include "EngineMain.h"
#include "ILight.h"

/******************************************************************************/

namespace MG
{
    //-----------------------------------------------------------------------
    LightingMapMaker::LightingMapMaker(Scene* scene)
        :mScene(scene)
		,mActive(false)
        ,mIsTest(false)
		,mPSSMShadowCameraSetup(NULL)
        ,mTerrainShadowOffset(1)
    {

    }
    //-----------------------------------------------------------------------
    LightingMapMaker::~LightingMapMaker()
    {
		unInitialize();
    }

	//-----------------------------------------------------------------------
	void LightingMapMaker::genarate( Bool isTest )
	{
        //mIsTest = isTest;
        if ( isTest )
        {
            mActive = !mActive;

            if ( mActive )
            {
                applyRenderConfig();
                applyCameraConfig();
            }

		    test();
        }else
        {
            mActive = true;

            if ( mActive )
            {
                saveSceneState();
                applyRenderConfig();
                applyCameraConfig();
                loadRenderTexture();

                genarateTerrainLightingMap();

                unLoadRenderTexture();
                revertSceneState();
            }

            mActive = false;
        }
	}

    //-----------------------------------------------------------------------
    void LightingMapMaker::saveSceneState()
    {
        ///////////////////////////////////////////////////////////////////////////////////////

        Ogre::Camera* cam           = mScene->getActiveCamera()->getOgreCamera();
        Ogre::SceneManager* scene   = mScene->getOgreSceneManager();

        ///////////////////////////////////////////////////////////////////////////////////////

        mCurrShadowTechnique    = scene->getShadowTechnique();
        mCurrAspectRatio        = cam->getAspectRatio();
        mCurrAutoAspectRatio    = cam->getAutoAspectRatio();
        mCurrFov                = cam->getFOVy();
        mCurrCamQua             = cam->getOrientation();
        mCurrCamPos             = cam->getPosition();
    }
    
    //-----------------------------------------------------------------------
    void LightingMapMaker::revertSceneState()
    {
        ///////////////////////////////////////////////////////////////////////////////////////

        Ogre::Camera* cam           = mScene->getActiveCamera()->getOgreCamera();
        Ogre::SceneManager* scene   = mScene->getOgreSceneManager();

        ///////////////////////////////////////////////////////////////////////////////////////

        scene->setShadowTechnique( mCurrShadowTechnique );
        cam->setAspectRatio( mCurrAspectRatio );
        cam->setAutoAspectRatio( mCurrAutoAspectRatio );
        cam->setFOVy( mCurrFov );
        cam->setOrientation( mCurrCamQua );
        cam->setPosition( mCurrCamPos );

        cam->setProjectionType( Ogre::PT_PERSPECTIVE );
    }

	//-----------------------------------------------------------------------
	MaterialPtr& LightingMapMaker::getTerrainMaterialPtr(TerrainSurfaceType type)
	{
        MaterialPtr mat;
        Bool isInit         = false;

        IDisplay* display   = EngineMain::getInstance().display();
        ShadowType st       = display->getShadowType();

        if ( mTerrainMaterialPtr.isNull() == true )
        {
            if ( (st == SCL_PSSM_DIFFUSE_TEXTURE) || (st == SCL_PSSM_DEPTH_TEXTURE) )
            {
                mTerrainMaterialPtr = Ogre::MaterialManager::getSingleton().getByName("MG/Terrain/PSSM/Shadow/Receive/LightingMap");
            }else
            {
                mTerrainMaterialPtr = Ogre::MaterialManager::getSingleton().getByName("MG/Terrain/PSSM/Shadow/Receive/LightingMap");
               // mTerrainMaterialPtr = Ogre::MaterialManager::getSingleton().getByName("MG/Terrain/Shadow/Receive/LightingMap");
            }
            isInit = true;
        }

        mat = mTerrainMaterialPtr;

        if ( mCurrCasterVisibilityMask == SOV_GROUND )
            mTerrainMaterialPtr->setSceneBlending( SBF_ONE, SBF_ZERO );
        else
            mTerrainMaterialPtr->setSceneBlending( SBF_DEST_COLOUR, SBF_ZERO );
        
        if ( isInit )
        {
           // mat->setDepthWriteEnabled( false );
            mat->setDepthCheckEnabled( true );

			PSSMShadowCameraSetup* pssmCam = mScene->getShadowManager()->getActiveShadowMaker()->getPSSMShadowCameraSetup();
            //PSSMShadowCameraSetup* pssmCam = mPSSMShadowCameraSetup;
			if ( pssmCam )
			{
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

            if ( mat->isLoaded() == false )
                mat->load();
		}

		return mTerrainMaterialPtr;
	}

	//-----------------------------------------------------------------------
	PSSMShadowCameraSetup* LightingMapMaker::getPSSMShadowCameraSetup()
	{
		return mPSSMShadowCameraSetup;
	}

    //-----------------------------------------------------------------------
    ShadowCameraSetupPtr LightingMapMaker::getCurrShadowCameraSetupPtr()
    {
        return mCurrentShadowCameraSetup;
    }

	//-----------------------------------------------------------------------
	Bool LightingMapMaker::isActive()
	{
		return mActive;
	}

    //-----------------------------------------------------------------------
    Bool LightingMapMaker::isTest()
    {
        return mIsTest;
    }

	//-----------------------------------------------------------------------
	void LightingMapMaker::applyRenderConfig()
	{
		///////////////////////////////////////////////////////////////////////////////////////

		initialize();

		///////////////////////////////////////////////////////////////////////////////////////

        Ogre::Camera* cam           = mScene->getActiveCamera()->getOgreCamera();
        Ogre::SceneManager* scene   = mScene->getOgreSceneManager();

        ///////////////////////////////////////////////////////////////////////////////////////

		//PSSM
		//DepthShadow
		scene->setShadowTechnique( SHADOWTYPE_TEXTURE_ADDITIVE_INTEGRATED );

        // 3 textures per directional light (PSSM)
        scene->setShadowTextureCountPerLightType(Ogre::Light::LT_DIRECTIONAL, 3);
		//mScene->getOgreSceneManager()->setShadowTexturePixelFormat(PF_FLOAT32_R);

		scene->setShadowTextureCount(3);
		scene->setShadowTextureConfig(0, 4096, 4096, PF_FLOAT32_R);
		scene->setShadowTextureConfig(1, 4096, 4096, PF_FLOAT32_R);
		scene->setShadowTextureConfig(2, 4096, 4096, PF_FLOAT32_R);
		scene->setShadowTextureSelfShadow(true);
		scene->setShadowCasterRenderBackFaces(true);

        ///////////////////////////////////////////////////////////////////////////////////////

        Flt camNearClipDistance     = mScene->getActiveCamera()->getOgreCamera()->getNearClipDistance();

        Flt shadowFarDistance = cam->getNearClipDistance() * Ogre::Math::Sqrt( 1 + Ogre::Math::Sqrt(cam->getAspectRatio()));
        shadowFarDistance = 800;
        scene->setShadowFarDistance( shadowFarDistance );

        mLightingMapCameraHeight = 50;
        scene->setShadowDirLightTextureOffset( mLightingMapCameraHeight / shadowFarDistance );

        ///////////////////////////////////////////////////////////////////////////////////////

        if ( mPSSMShadowCameraSetup )
        {
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

    //-----------------------------------------------------------------------
    void LightingMapMaker::applyCameraConfig()
    {
        Ogre::Camera* cam           = mScene->getActiveCamera()->getOgreCamera();

        cam->setAutoAspectRatio( true );
        cam->setProjectionType( Ogre::PT_ORTHOGRAPHIC );
        cam->setFOVy( Ogre::Degree(90) );

        Ogre::Quaternion camQua;
        camQua.FromAxes( Ogre::Vector3::UNIT_X, Ogre::Vector3::NEGATIVE_UNIT_Z, Ogre::Vector3::UNIT_Y );
        cam->setOrientation( camQua );
    }

	//-----------------------------------------------------------------------
	void LightingMapMaker::initialize()
	{

		if ( mPSSMShadowCameraSetup == NULL )
		{
			mPSSMShadowCameraSetup = MG_NEW PSSMShadowCameraSetup();
			mCurrentShadowCameraSetup.bind( mPSSMShadowCameraSetup );
		}

		mScene->getOgreSceneManager()->setShadowCameraSetup(mCurrentShadowCameraSetup);
	}

	//-----------------------------------------------------------------------
	void LightingMapMaker::unInitialize()
	{
		mPSSMShadowCameraSetup = NULL;
		mCurrentShadowCameraSetup.setNull();
	}


    //-----------------------------------------------------------------------
    void LightingMapMaker::genarateTerrainLightingMap()
    {
        UInt chunkCount = mScene->getTerrainManager()->getTerrainChunkCount();

        for ( UInt i=0; i<chunkCount; i++ )
        {
            TerrainChunk* chunk = mScene->getTerrainManager()->getTerrainChunkByIndex(i);
            if ( chunk )
            {
                TerrainGroundSurface* groundSurface =  chunk->getTerrainGroundSurface();
                TerrainWaterSurface* waterSurface =  chunk->getTerrainWaterSurface();

                genarateSurfaceLightingMap( groundSurface );
                //genarateSurfaceLightingMap( waterSurface );
            }
        }
    }

    //-----------------------------------------------------------------------
    void LightingMapMaker::genarateSurfaceLightingMap( TerrainSurface* surface )
    {
        Ogre::Camera* cam           = mScene->getActiveCamera()->getOgreCamera();
        Ogre::SceneManager* scene   = mScene->getOgreSceneManager();

        TexturePtr texPtr           = surface->getLightmap();

        if ( surface->getType() == TST_GROUND )
        {
            mRenderLightingMapTextureViewport->setVisibilityMask( SOV_GROUND | SOV_WATER );
           // mRenderLightingMapTextureViewport->setVisibilityMask( SOV_GROUND );
        }

        if ( (mRenderLightingMapTexture.isNull() == false) && (texPtr.isNull() == false) )
        {
            Flt worldSize = surface->getWorldSize();
			Flt oneRenderDefalutSize = 128;

			Vec2 centerPos			= surface->getCenterPos();
			Vec2 leftBottomPos		= surface->getLeftBottomPos();
			Vec2 oneRenderCenterPos;
			Flt oneRenderWidth		= oneRenderDefalutSize;
			Flt oneRenderHeight		= oneRenderDefalutSize;

			Flt texScaleWidth		= texPtr->getWidth()  / worldSize;
			Flt texScaleHeight		= texPtr->getHeight() / worldSize;
			Flt texX = 0;
			Flt texY = texPtr->getHeight();
			Flt texDx;
			Flt texDy;

			Image::Box texBox;
			Ogre::Image tempImg;

			for ( UInt y = 0; y < worldSize; )
			{
				oneRenderHeight = worldSize - y;
				if ( oneRenderHeight > oneRenderDefalutSize )
				{
					oneRenderHeight = oneRenderDefalutSize;
				}

				oneRenderCenterPos.y  = leftBottomPos.y - y - oneRenderHeight * 0.5;
				texDy				  = oneRenderHeight * texScaleHeight;
				
				texX = 0;
				texY -= texDy;
				if ( texY < 0 )
					texY = 0;

				for ( UInt x = 0; x < worldSize; )
				{
					oneRenderWidth = worldSize - x;
					if ( oneRenderWidth > oneRenderDefalutSize )
					{
						oneRenderWidth = oneRenderDefalutSize;
					}

					oneRenderCenterPos.x  = leftBottomPos.x + x + oneRenderWidth * 0.5;
					texDx				  = oneRenderWidth * texScaleHeight;

					//////////////////////////////////////////////////////////////////////////////////////

					cam->setOrthoWindowWidth( oneRenderWidth );
					cam->setOrthoWindowHeight( oneRenderHeight );
					cam->setPosition( oneRenderCenterPos.x, mLightingMapCameraHeight, oneRenderCenterPos.y );

					//////////////////////////////////////////////////////////////////////////////////////

                    mRenderLightingMapTextureViewport->clear( FBT_COLOUR | FBT_DEPTH, ColourValue::White );

                    // render terrain
                    // mRenderLightingMapTextureViewport->clear( FBT_DEPTH, ColourValue::White );
                    Vec3 lDir = mScene->getDefaultLight()->getDirection();
                    Vec3 tDir = Vec3(lDir.x,0,lDir.z);
                    tDir.normalise();
                    tDir = Vec3(tDir.x,-mTerrainShadowOffset,tDir.z);
                    mScene->getDefaultLight()->setDirection(tDir);
                    mCurrCasterVisibilityMask = SOV_GROUND;
                    OgreMainInterface::root->renderOneFrame();
                    mScene->getDefaultLight()->setDirection(lDir);

                    // render object
                    //mRenderLightingMapTextureViewport->clear( FBT_DEPTH, ColourValue::White );
                    mCurrCasterVisibilityMask = SOV_STATIC_SHADOW;
                    OgreMainInterface::root->renderOneFrame();
                  
					//////////////////////////////////////////////////////////////////////////////////////

					mRenderLightingMapTexture->convertToImage( tempImg, false );

					texBox = Image::Box(texX, texY, texX + texDx, texY + texDy);
					tempImg.resize( texDx, texDy, Ogre::Image::FILTER_BILINEAR );
                    
					texPtr->getBuffer()->blitFromMemory(tempImg.getPixelBox(),texBox);

					//////////////////////////////////////////////////////////////////////////////////////

					x += oneRenderWidth;
					texX += texDx;
				}

				y += oneRenderHeight;
			}

			surface->setLightingMapChangeDirty( true );

        }
    }

    //-----------------------------------------------------------------------
    void LightingMapMaker::setTerrainShadowOffset(Flt offset)
    {
        mTerrainShadowOffset = offset;
    }

    //-----------------------------------------------------------------------
    Bool LightingMapMaker::getTerrainCastShadows(TerrainSurfaceType type)
    {
        if ( !mActive )
            return false;

        if (mCurrCasterVisibilityMask!=SOV_GROUND)
            return false;

        return true;
    }

    //-----------------------------------------------------------------------
    void LightingMapMaker::loadRenderTexture()
    {
        Ogre::Camera* cam           = mScene->getActiveCamera()->getOgreCamera();
        Ogre::SceneManager* scene   = mScene->getOgreSceneManager();

        Str texName = "LightingMapMaker_LightingMap";
        mRenderLightingMapTexture = TextureManager::getSingleton().getByName( texName );
        if (mRenderLightingMapTexture.isNull()==true)
        {
            mRenderLightingMapTexture = TextureManager::getSingleton().createManual(texName,
                ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, TEX_TYPE_2D, 4096, 4096, 0, PF_L8, TU_RENDERTARGET);
        }

        if (mRenderLightingMapTexture.isNull()==false)
        {
            RenderTarget* renderTarget = mRenderLightingMapTexture->getBuffer()->getRenderTarget();

            if (renderTarget->getNumViewports()==0)
            {
                Viewport* viewport = renderTarget->addViewport(cam);
                viewport->setOverlaysEnabled( false );
                viewport->setShadowsEnabled( true );
                viewport->setSkiesEnabled( false );
                viewport->setOverlaysEnabled( false );
                viewport->setBackgroundColour(Ogre::ColourValue(1,1,1,1));
                viewport->setClearEveryFrame( false );

                renderTarget->addListener(this);

                mRenderLightingMapTextureViewport = viewport;
            }
        }
    }

    //-----------------------------------------------------------------------
    void LightingMapMaker::unLoadRenderTexture()
    {
        if (mRenderLightingMapTexture.isNull()==false)
        {
            RenderTarget* renderTarget = mRenderLightingMapTexture->getBuffer()->getRenderTarget();

            renderTarget->removeAllViewports();
            renderTarget->removeAllListeners();

            TextureManager::getSingleton().remove( mRenderLightingMapTexture->getHandle() );

            mRenderLightingMapTexture.setNull();

            mRenderLightingMapTextureViewport = NULL;
        }
    }

    //-----------------------------------------------------------------------
    void LightingMapMaker::preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt)
    {
        RenderTarget* renderTarget = evt.source;
        Viewport* viewPort = renderTarget->getViewport(0);

        if ( viewPort )
        {

        }
    }

    //-----------------------------------------------------------------------
    void LightingMapMaker::postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt)
    {
        
    }

    //-----------------------------------------------------------------------
    void LightingMapMaker::shadowTextureCasterPreViewProj(Ogre::Light* light, Ogre::Camera* camera, size_t iteration)
    {
        camera->getViewport()->setVisibilityMask( mCurrCasterVisibilityMask );
    }

    //-----------------------------------------------------------------------
    void LightingMapMaker::shadowTexturesUpdated(size_t numberOfShadowTextures)
    {

    }

	//-----------------------------------------------------------------------
	void LightingMapMaker::test()
	{

	
	}



}

