/******************************************************************************/
/******************************************************************************/

#include "stdafx.h"
#include "Scene.h"
#include "SceneDebuger.h"
#include "EngineMain.h"
#include "TerrainWaterMaterial.h"

/******************************************************************************/

namespace MG
{
    //-----------------------------------------------------------------------
    SceneDebuger::SceneDebuger(Scene* scene)
        :mScene(scene)
        ,mTextureDebugName("SceneDebuger_Texture_Shower")
        ,mColour(ColourValue::Green)
        ,mOgreManualObject(NULL)
        ,mSceneNode(NULL)
        ,mVisible(false)
    {   
    }

    //-----------------------------------------------------------------------
    SceneDebuger::~SceneDebuger()
    {
        clear();
    }

    //-----------------------------------------------------------------------
    void SceneDebuger::update( Flt delta )
    {

    }


    //-----------------------------------------------------------------------
    void SceneDebuger::postFindVisibleObjects(Ogre::SceneManager* source, 
        Ogre::SceneManager::IlluminationRenderStage irs, Ogre::Viewport* v)
    {
        if ( mOgreManualObject && mVisible )
        {
            RenderQueue *queue = source->getRenderQueue();

            mOgreManualObject->_updateRenderQueue( queue);
        }
    }

    //-----------------------------------------------------------------------
    void SceneDebuger::clear( )
    {
        destroyOgreManualObject();
    }

    //-----------------------------------------------------------------------
    void SceneDebuger::showTexture(Str name)
    {
        createOgreManualObject();

        setTexture( name );

        mVisible = true;
    }

    //-----------------------------------------------------------------------
    void SceneDebuger::hideTexture()
    {
        mSceneNode->setVisible( false );

        mVisible = false;
    }

    //-----------------------------------------------------------------------
    void SceneDebuger::createOgreManualObject()
    {
        if ( mOgreManualObject == NULL )
        {
            mOgreManualObject = mScene->getOgreSceneManager()->createManualObject( mTextureDebugName );
            mOgreManualObject->setCastShadows(false);
            //mOgreManualObject->setRenderQueueGroup(Ogre::RENDER_QUEUE_3);
            mOgreManualObject->setRenderQueueGroup(Ogre::RENDER_QUEUE_OVERLAY);

            mOgreManualObject->setUseIdentityView(true);
            mOgreManualObject->setUseIdentityProjection(true);

            //创建实体节点
            mSceneNode = MG_NEW MGSceneNode(mScene->getOgreSceneManager()->getRootSceneNode(),mScene);
            //绑定实体
            mSceneNode->getOgreSceneNode()->attachObject( mOgreManualObject );

            //build
            buildMaterial();
            buildMesh( mOgreMaterialPtr->getName() );
        }
    }

    //-----------------------------------------------------------------------
    void SceneDebuger::destroyOgreManualObject()
    {
        if ( mOgreManualObject )
        {
            mScene->getOgreSceneManager()->destroyManualObject(mOgreManualObject);
            mOgreManualObject = NULL;
        } 

        //销毁实体节点
        if ( mSceneNode )
            MG_SAFE_DELETE( mSceneNode );
    }


    //-----------------------------------------------------------------------
    void SceneDebuger::setTexture(Str texName)
    {
        /// 得到渲染通道
        Ogre::Pass* pass = mOgreMaterialPtr->getTechnique(0)->getPass(0);
        Ogre::TextureUnitState* textureUnitState = NULL;
        textureUnitState = pass->getTextureUnitState(0);
        
        if ( texName == "shadow" )
        {
            buildMesh("MG/Debug/ShadowTextureShow");
        }else
        {
            if ( texName == "reflect" )
            {
                texName = TerrainWaterMaterial::getWaterReflectionTextureName( 0 );
                textureUnitState->setTextureName( texName );
            }else
            {
                textureUnitState->setTextureName( texName );
            }

            buildMesh( mOgreMaterialPtr->getName() );
        }
    }

    //-----------------------------------------------------------------------
    void SceneDebuger::buildMaterial()
    {
        Str matName = "Material_" + mTextureDebugName;

        /// 得到或创建材质
        mOgreMaterialPtr = Ogre::MaterialManager::getSingleton().getByName(matName);
        if (mOgreMaterialPtr.isNull())
        {
            mOgreMaterialPtr = Ogre::MaterialManager::getSingleton().create(matName, 
                Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
            mOgreMaterialPtr->setReceiveShadows( false );
        }

        /// 得到渲染通道
        Ogre::Pass* pass = mOgreMaterialPtr->getTechnique(0)->getPass(0);
        pass->setLightingEnabled(false);
        pass->setLightingEnabled(false);
        pass->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
        pass->setCullingMode(Ogre::CULL_NONE);
        pass->setDepthCheckEnabled(false);
        pass->setDepthWriteEnabled(true);
        pass->setDepthBias(0.005);

        /// 得到或创建贴图单元
        Ogre::TextureUnitState* textureUnitState = NULL;
        if ( pass->getNumTextureUnitStates() == 0 )
        {
            textureUnitState = pass->createTextureUnitState();
            textureUnitState->setTextureAddressingMode( TextureUnitState::TAM_CLAMP );
        }
    }

    //-----------------------------------------------------------------------
    void SceneDebuger::buildMesh(Str matName)
    {
        mOgreManualObject->clear();

        mOgreManualObject->setDynamic(true);

        mOgreManualObject->begin(  matName, Ogre::RenderOperation::OT_TRIANGLE_LIST );
        //mOgreManualObject->begin(  mOgreMaterialPtr->getName(), Ogre::RenderOperation::OT_LINE_LIST );
        {
            refreshMeshData();
        }

        mOgreManualObject->end();
    }

    //-----------------------------------------------------------------------
    void SceneDebuger::refreshMeshData(void)
    {
        /*
        -y
        |
        |
        w0---------w1
        |          |
        |          |
        |          |
        w2---------w3----+x
        */

        RectF rect;
        rect.left   = 0; 
        rect.right  = 256;
        rect.top    = 0;
        rect.bottom = 256;

        Int screenWidth     = OgreMainInterface::renderWindow->getWidth();
        Int screenHeight    = OgreMainInterface::renderWindow->getHeight();

        rect.left           = rect.left / Flt( screenWidth );
        rect.right          = rect.right / Flt( screenWidth );
        rect.top            = 1 - rect.top / Flt( screenHeight );
        rect.bottom         = 1 - rect.bottom / Flt( screenHeight );

        rect.left           = ( rect.left - 0.5 ) * 2;
        rect.right          = ( rect.right - 0.5 ) * 2;
        rect.top            = ( rect.top - 0.5 ) * 2;
        rect.bottom         = ( rect.bottom - 0.5 ) * 2;

        Vector3 w0 =  Vector3( rect.left, rect.top, 0);
        Vector3 w1 =  Vector3( rect.right, rect.top, 0);
        Vector3 w2 =  Vector3( rect.left, rect.bottom, 0);       
        Vector3 w3 =  Vector3( rect.right, rect.bottom, 0);

        Vec2 uv0 = Vec2(-0.03, -0.03);
        Vec2 uv1 = Vec2(1.03, -0.03);
        Vec2 uv2 = Vec2(-0.03, 1.03);
        Vec2 uv3 = Vec2(1.03, 1.03);


        if ( false )
        {
            mOgreManualObject->position( w0 );
            mOgreManualObject->colour( mColour );
            mOgreManualObject->position( w1 );
            mOgreManualObject->colour( mColour );

            mOgreManualObject->position( w1 );
            mOgreManualObject->colour( mColour );
            mOgreManualObject->position( w3 );
            mOgreManualObject->colour( mColour );

            mOgreManualObject->position( w3 );
            mOgreManualObject->colour( mColour );
            mOgreManualObject->position( w2 );
            mOgreManualObject->colour( mColour );

            mOgreManualObject->position( w2 );
            mOgreManualObject->colour( mColour );
            mOgreManualObject->position( w0 );
            mOgreManualObject->colour( mColour );
        }else
        {
            mOgreManualObject->position( w0 );
            mOgreManualObject->textureCoord( uv0.x, uv0.y );
            mOgreManualObject->position( w1 );
            mOgreManualObject->textureCoord( uv1.x, uv1.y );
            mOgreManualObject->position( w2 );
            mOgreManualObject->textureCoord( uv2.x, uv2.y );
            mOgreManualObject->position( w3 );
            mOgreManualObject->textureCoord( uv3.x, uv3.y );

            mOgreManualObject->index( 0 );
            mOgreManualObject->index( 2 );
            mOgreManualObject->index( 1 );

            mOgreManualObject->index( 1 );
            mOgreManualObject->index( 2 );
            mOgreManualObject->index( 3 );
        }

    }

}

