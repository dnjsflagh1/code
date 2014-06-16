/******************************************************************************/
#include "stdafx.h"
#include "PolylineWireframeDecorator.h"
#include "Scene.h"
#include "MGSceneNode.h"
#include "EngineMain.h"
#include "MGEngineUtility.h"
#include "ManualMeshManager.h"
/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------
    PolylineWireframeDecorator::PolylineWireframeDecorator(const String& name, Scene* scene)
        :mSyncEnable(true)
        ,mScene(scene)
        ,mBoldSize(1)
        ,mColour(ColourValue::Green)
        ,mOgreManualObject(NULL)
    {
        mPolyline = MG_NEW Polyline();
        createOgreManualObject();
    }

    //-----------------------------------------------------------------------
    PolylineWireframeDecorator::~PolylineWireframeDecorator()
    {
        destroyOgreManualObject();
        MG_SAFE_DELETE(mPolyline);
    }

    //-----------------------------------------------------------------------
    void PolylineWireframeDecorator::rebuild(void)
    {
        buildMeshData();
        buildOgreManualObject();
    }

    //-----------------------------------------------------------------------
    void PolylineWireframeDecorator::refresh(void)
    {
        buildMeshData();
        refreshOgreManualObject();
    }

    //-----------------------------------------------------------------------
    Polyline* PolylineWireframeDecorator::getPolyline(void)
    {
        return mPolyline;
    }

    //-----------------------------------------------------------------------
    void PolylineWireframeDecorator::setSyncEnable(Bool enable)
    {
        mSyncEnable = enable;
    }

    //-----------------------------------------------------------------------
    void PolylineWireframeDecorator::setBoldSize(Flt size)
    {
        mBoldSize = size;
    }

    //-----------------------------------------------------------------------
    Flt PolylineWireframeDecorator::getBoldSize(void)
    {
        return mBoldSize;
    }

    //-----------------------------------------------------------------------
    void PolylineWireframeDecorator::setColour(Color colour)
    {
        mColour = ColourValue(colour.r,colour.g,colour.b,colour.a);
    }

    //-----------------------------------------------------------------------
    Color PolylineWireframeDecorator::getColour()
    {
        return Color(mColour.r,mColour.g,mColour.b,mColour.a);
    }

    //-----------------------------------------------------------------------
    void PolylineWireframeDecorator::setVisible(Bool visible)
    {
        if (mSceneNode)
            mSceneNode->setVisible(visible);
    }

    //-----------------------------------------------------------------------
    Bool PolylineWireframeDecorator::getVisible()
    {
        if (mSceneNode)
            return mSceneNode->getVisible();
        return false;
    }

    //-----------------------------------------------------------------------
    void PolylineWireframeDecorator::createOgreManualObject()
    {
        //创建实体对象
        mOgreManualObject = mScene->getOgreSceneManager()->createManualObject();
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
    void PolylineWireframeDecorator::destroyOgreManualObject()
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
    String PolylineWireframeDecorator::createOrRetrieveOgreMaterial(void)
    {
        String matname = "_MATERIAL_POLYLINE_ENTITY";

        mOgreMaterialPtr = Ogre::MaterialManager::getSingleton().getByName(matname);

        if ( mOgreMaterialPtr.isNull() )
        {
            mOgreMaterialPtr = Ogre::MaterialManager::getSingleton().create(matname, 
                Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        }

        if ( !mOgreMaterialPtr.isNull() )
        {
            mOgreMaterialPtr->setReceiveShadows( false );

            Ogre::Pass* pass = mOgreMaterialPtr->getTechnique(0)->getPass(0);

            pass->setLightingEnabled(false);
            pass->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
            pass->setCullingMode(Ogre::CULL_NONE);
        }

        return matname;
    }

    //-----------------------------------------------------------------------
    void PolylineWireframeDecorator::buildMeshData(void)
    {
        mTwistyBoxMeshDatas.clear();

        size_t pointcount = mPolyline->getKeyPointCount();
        size_t n =0;
        TwistyBoxMeshData newMeshData;
        TwistyBoxMeshData priorMeshData;
        for(size_t i=1; i<pointcount; ++i,++n)
        {
            Vector3 startpoint = mPolyline->getKeyPoint(i-1).position;
            Vector3 endpoint = mPolyline->getKeyPoint(i).position;

            ManualMeshManager::getInstance().rebuildTwistyBoxMeshData(newMeshData, startpoint, endpoint, mBoldSize, mBoldSize);

            newMeshData.colour = mColour;

            mTwistyBoxMeshDatas.push_back(newMeshData);
        }
    }

    //-----------------------------------------------------------------------
    void PolylineWireframeDecorator::buildOgreManualObject(void)
    {
        mOgreManualObject->clear();

        mOgreManualObject->setDynamic(true);

        mOgreManualObject->setRenderQueueGroup(Ogre::RENDER_QUEUE_OVERLAY-2);

        String matname = createOrRetrieveOgreMaterial();
        mOgreManualObject->begin( matname, Ogre::RenderOperation::OT_TRIANGLE_LIST );
        {
            fillMeshDataInOgreManualObject();
        }
        mOgreManualObject->end();
    }

    //-----------------------------------------------------------------------
    void PolylineWireframeDecorator::refreshOgreManualObject(void)
    {
        if ( (mOgreManualObject) && (mOgreManualObject->getNumSections() > 0) )
        {
            mOgreManualObject->beginUpdate(0);
            {
                fillMeshDataInOgreManualObject();
            }
            mOgreManualObject->end();
        }
    }

    //-----------------------------------------------------------------------
    void PolylineWireframeDecorator::fillMeshDataInOgreManualObject(void)
    {
        TwistyBoxMeshData meshData;
        for(TwistyBoxMeshDataList::iterator i = mTwistyBoxMeshDatas.begin(); i != mTwistyBoxMeshDatas.end(); ++i)
        {
            meshData = (*i);

            for (size_t n=0; n < TwistyBoxMeshData::REAL_VERTEX_COUNT; ++n )
            {
                size_t realVertexIndexs = meshData.realVertexIndexs[n];
                mOgreManualObject->position( meshData.referVertexs[realVertexIndexs] );
                mOgreManualObject->colour(meshData.colour);
            }
        }

        size_t meshIndex = 0;
        for(TwistyBoxMeshDataList::iterator i = mTwistyBoxMeshDatas.begin(); i != mTwistyBoxMeshDatas.end(); ++i, ++meshIndex)
        {
            meshData = (*i);

            size_t startIndex = meshIndex * TwistyBoxMeshData::REAL_VERTEX_COUNT;
            for ( size_t n=0; n < TwistyBoxMeshData::TRIANGLE_INDEX_COUNT; ++n )
            {
                mOgreManualObject->index( Ogre::uint32( startIndex + n ) );
            }
        }
    }

}