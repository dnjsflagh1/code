/******************************************************************************/
#include "stdafx.h"
#include "ScreenRectWireframeDecorator.h"
#include "Scene.h"
#include "MGSceneNode.h"
#include "EngineMain.h"
#include "MGEngineUtility.h"
/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------
    ScreenRectWireframeDecorator::ScreenRectWireframeDecorator(const String& name, Scene* scene)
        :mScene(scene)
        ,mBoldSize(1)
        ,mColour(ColourValue::Green)
        ,mOgreManualObject(NULL)
        ,mIsOnceShow(-1)
    {
        mRect = RectF(0,0,1,1);
        buildMaterial();
        createOgreManualObject();
        buildMesh();
    }

    //-----------------------------------------------------------------------
    ScreenRectWireframeDecorator::~ScreenRectWireframeDecorator()
    {
        destroyOgreManualObject();
    }

    //-----------------------------------------------------------------------
    void ScreenRectWireframeDecorator::update(void)
    {
        if ( mIsOnceShow >= 0 )
        {     
			mIsOnceShow--;
			if ( mIsOnceShow == 0 )
				this->setVisible( false );
        }
    }

    //-----------------------------------------------------------------------
    void ScreenRectWireframeDecorator::rebuild(void)
    {
        buildMesh();
    }

    //-----------------------------------------------------------------------
    void ScreenRectWireframeDecorator::refresh(void)
    {
        refreshMesh();
    }

    //-----------------------------------------------------------------------
    void ScreenRectWireframeDecorator::setBoldSize(Flt size)
    {
        mBoldSize = size;
    }

    //-----------------------------------------------------------------------
    Flt ScreenRectWireframeDecorator::getBoldSize(void)
    {
        return mBoldSize;
    }

    //-----------------------------------------------------------------------
    void ScreenRectWireframeDecorator::setColour(Color colour)
    {
        mColour = ColourValue(colour.r,colour.g,colour.b,colour.a);
    }

    //-----------------------------------------------------------------------
    Color ScreenRectWireframeDecorator::getColour()
    {
        return Color(mColour.r,mColour.g,mColour.b,mColour.a);
    }

    //-----------------------------------------------------------------------
    void ScreenRectWireframeDecorator::setVisible(Bool visible)
    {
        if (mSceneNode)
            mSceneNode->setVisible(visible);
    }

    //-----------------------------------------------------------------------
    Bool ScreenRectWireframeDecorator::getVisible()
    {
        if (mSceneNode)
            return mSceneNode->getVisible();
        return false;
    }

    //-----------------------------------------------------------------------
    void ScreenRectWireframeDecorator::setRect(RectF rect, Bool isOnce)
    {
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

        mRect           = rect;

		if ( isOnce )
			mIsOnceShow = 2;

        //if ( mIsOnceShow )
        //    setVisible( true );

        refreshMesh();
    }
    
    //-----------------------------------------------------------------------
    void ScreenRectWireframeDecorator::postFindVisibleObjects(Ogre::SceneManager* source, 
        Ogre::SceneManager::IlluminationRenderStage irs, Ogre::Viewport* v)
    {
        if ( mOgreManualObject && (mIsOnceShow >= 0) )
        {
            RenderQueue *queue = source->getRenderQueue();

            mOgreManualObject->_updateRenderQueue( queue);
        }
    }

    //-----------------------------------------------------------------------
    void ScreenRectWireframeDecorator::createOgreManualObject()
    {
        //创建实体对象
        mOgreManualObject = mScene->getOgreSceneManager()->createManualObject();
        mOgreManualObject->setCastShadows(false);
        mOgreManualObject->setRenderQueueGroup(Ogre::RENDER_QUEUE_OVERLAY);

        mOgreManualObject->setUseIdentityView(true);
        mOgreManualObject->setUseIdentityProjection(true);

        DYNAMIC_ASSERT(mOgreManualObject!=NULL);

        if ( mOgreManualObject )
        {
            // 设置绑定实体对象的管理者
            //mOgreManualObject->setUserAny( Any((ISceneObject*)this) );

            // 创建实体节点
            mSceneNode = MG_NEW MGSceneNode(mScene->getOgreSceneManager()->getRootSceneNode(),mScene);

            // 绑定实体
            mSceneNode->getOgreSceneNode()->attachObject( mOgreManualObject );
        }
    }

    //-----------------------------------------------------------------------
    void ScreenRectWireframeDecorator::destroyOgreManualObject()
    {
        //销毁实体对象
        if ( mOgreManualObject )
        {
            mScene->getOgreSceneManager()->destroyManualObject(mOgreManualObject);
            mOgreManualObject = NULL;
        }

        //销毁实体节点
        MG_SAFE_DELETE( mSceneNode );
    }

    //-----------------------------------------------------------------------
    void ScreenRectWireframeDecorator::buildMaterial(void)
    {
        Str matName = getMaterialName();

        /// 得到或创建材质
        mOgreMaterialPtr = Ogre::MaterialManager::getSingleton().getByName(matName);
        if (mOgreMaterialPtr.isNull())
        {
            mOgreMaterialPtr = Ogre::MaterialManager::getSingleton().create(matName, 
                Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
            mOgreMaterialPtr->setReceiveShadows( false );

            /// 得到渲染通道
            Ogre::Pass* pass = mOgreMaterialPtr->getTechnique(0)->getPass(0);
            pass->setLightingEnabled(false);
            pass->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
            pass->setCullingMode(Ogre::CULL_NONE);
            pass->setDepthCheckEnabled( false );
        }
    }

    //-----------------------------------------------------------------------
    Str ScreenRectWireframeDecorator::getMaterialName(void)
    {
        return "_MATERIAL_SCREENRECTWIREFRAMEDECORATOR";
    }

    //-----------------------------------------------------------------------
    void ScreenRectWireframeDecorator::buildMesh(void)
    {
        mOgreManualObject->clear();

        mOgreManualObject->setDynamic(true);

        mOgreManualObject->begin(  mOgreMaterialPtr->getName(), Ogre::RenderOperation::OT_LINE_LIST );

        {
            refreshMeshData();
        }

        mOgreManualObject->end();
    }

    //-----------------------------------------------------------------------
    void ScreenRectWireframeDecorator::refreshMesh(void)
    {
        if ( mOgreManualObject )
        {
            mOgreManualObject->beginUpdate(0);

            refreshMeshData();

            mOgreManualObject->end();
        }
    }

    //-----------------------------------------------------------------------
    void ScreenRectWireframeDecorator::refreshMeshData(void)
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

        Vector3 w0 =  Vector3( mRect.left, mRect.top, 0);
        Vector3 w1 =  Vector3( mRect.right, mRect.top, 0);
        Vector3 w2 =  Vector3( mRect.left, mRect.bottom, 0);       
        Vector3 w3 =  Vector3( mRect.right, mRect.bottom, 0);

        //Vector3 w0 =  Vector3( 0, 1, -100 );
        //Vector3 w1 =  Vector3( 100, 1, -100 );
        //Vector3 w2 =  Vector3( 0, 1, 0 );       
        //Vector3 w3 =  Vector3( 100, 1, 0 );

        //Vector3 w0 =  Vector3( -0.3, 0.3, 0 );
        //Vector3 w1 =  Vector3( 0.3, 0.3, 0 );
        //Vector3 w2 =  Vector3( -0.3, -0.3, 0 );
        //Vector3 w3 =  Vector3( 0.3, -0.3, 0 );

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
    }

    

}