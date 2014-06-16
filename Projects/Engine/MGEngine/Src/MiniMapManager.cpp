/******************************************************************************/
/******************************************************************************/

#include "stdafx.h"
#include "MiniMapManager.h"
#include "Scene.h"
#include "Display.h"
#include "EngineMain.h"
#include "ResourceManager.h"

/******************************************************************************/

namespace MG
{
    //-----------------------------------------------------------------------
    MiniMapManager::MiniMapManager(Scene* scene)
        :mScene(scene)
        ,mActive(false)
        ,mIsTest(false)
    {   

    }

    //-----------------------------------------------------------------------
    MiniMapManager::~MiniMapManager()
    {

    }

    //-----------------------------------------------------------------------
    Bool MiniMapManager::isActive()
    {
        return mActive;
    }

    //-----------------------------------------------------------------------
    Bool MiniMapManager::isTest()
    {
        return mIsTest;   
    }

    //-----------------------------------------------------------------------
    void MiniMapManager::applyCameraConfig()
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
    void  MiniMapManager::genarateMiniMap(Vec2 center, Vec2 size, Str savePath, Vec2 mapSize)
    {
        mActive = true;

        if ( mActive )
        {
            saveSceneState();

            applyCameraConfig();
            loadRenderTexture();

            startGenarateMiniMap(center,size,savePath,mapSize);

            unLoadRenderTexture();
            revertSceneState();
        }

        mActive = false;
    }

    //-----------------------------------------------------------------------
    void MiniMapManager::saveSceneState()
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
    void MiniMapManager::revertSceneState()
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
    void MiniMapManager::loadRenderTexture()
    {
        Ogre::Camera* cam           = mScene->getActiveCamera()->getOgreCamera();
        Ogre::SceneManager* scene   = mScene->getOgreSceneManager();

        Str texName = "MiniMapMaker_MiniMap";
        mRenderLightingMapTexture = TextureManager::getSingleton().getByName( texName );
        if (mRenderLightingMapTexture.isNull()==true)
        {
            mRenderLightingMapTexture = TextureManager::getSingleton().createManual(texName,
                ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, TEX_TYPE_2D, 4096, 4096, 0, PF_A8R8G8B8, TU_RENDERTARGET);
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
    void MiniMapManager::unLoadRenderTexture()
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
    void MiniMapManager::preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt)
    {

    }

    //-----------------------------------------------------------------------
    void MiniMapManager::postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt)
    {
        
    }

    //-----------------------------------------------------------------------
    void MiniMapManager::startGenarateMiniMap(Vec2 center, Vec2 size, Str savePath, Vec2 mapSize)
    {
        //////////////////////////////////////////////////////////////////////////////////////

        Ogre::Camera* cam           = mScene->getActiveCamera()->getOgreCamera();
        Ogre::SceneManager* scene   = mScene->getOgreSceneManager();

        Image::Box texBox;
        Ogre::Image tempImg;

        //////////////////////////////////////////////////////////////////////////////////////

        cam->setOrthoWindowWidth( size.x );
        cam->setOrthoWindowHeight( size.y );
        cam->setPosition( center.x, 50, center.y );

        //////////////////////////////////////////////////////////////////////////////////////

        mRenderLightingMapTextureViewport->clear( FBT_COLOUR | FBT_DEPTH, ColourValue::White );

        OgreMainInterface::root->renderOneFrame();

        //////////////////////////////////////////////////////////////////////////////////////

        mRenderLightingMapTexture->convertToImage( tempImg, false );

        tempImg.resize( mapSize.x, mapSize.y, Ogre::Image::FILTER_BILINEAR );

        Str realFilePath   = FileOp::getFullFilePath( savePath, Str("MiniMap.png") );
        tempImg.save( realFilePath );

        //////////////////////////////////////////////////////////////////////////////////////

    }

}

