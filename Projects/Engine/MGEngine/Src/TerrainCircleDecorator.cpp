/******************************************************************************/
#include "stdafx.h"
#include "TerrainCircleDecorator.h"
#include "Scene.h"
#include "MGSceneNode.h"
#include "EngineMain.h"
#include "MGEngineUtility.h"
/******************************************************************************/

namespace MG
{

    /**
    -----------------------------------------------------------------------------
    TerrainCircleLineList
    -----------------------------------------------------------------------------
    */
    TerrainCircleLineList::TerrainCircleLineList()
    {
        mBaseRadian = 0;
        mLastBuildTime = MGTimeOp::getCurrTick();
    }

    //-----------------------------------------------------------------------
    void TerrainCircleLineList::build( TerrainManager* terrainMgr , Vec3 center, Flt radius, Flt gap )
    {
        Flt     girth           = 2 * 3.14 * radius;
        UInt    sectorCount     = girth / gap;
        UInt    maxSectorCount  = 100;
        if ( sectorCount > maxSectorCount )
            sectorCount = maxSectorCount;
        if ( sectorCount < 6 )
            sectorCount = 6;

        Vector3 dir         = Vector3( 0, 0, radius );
        Flt onceRadianValue = 2 * 3.14 / sectorCount;
        Radian onceRadian   = Radian( onceRadianValue );

        //////////////////////////////////////////////////////

        Ogre::Quaternion baseQua;

        Flt delta       = MGTimeOp::getCurrTick() - mLastBuildTime;
        mLastBuildTime  = MGTimeOp::getCurrTick();
        Flt speed       = 0.003;
        mBaseRadian += delta * speed * onceRadianValue;
        if ( mBaseRadian > 2 * 3.14 )
            mBaseRadian = 0;

        baseQua.FromAngleAxis( Radian(mBaseRadian), Vector3::UNIT_Y);
        dir = baseQua * dir;

        //////////////////////////////////////////////////////

        Quaternion q;
        q.FromAngleAxis( onceRadian, Vector3::UNIT_Y);

        //////////////////////////////////////////////////////
        mCircleLine.clear();
        Vec3 pos;
        for ( UInt i=0; i<sectorCount; i++ )
        {
            pos = center + Vec3(dir.x,dir.y,dir.z);

            //////////////////////////////////////////////////////////////////
            
            terrainMgr->getStickHeight( Vec2(pos.x, pos.z), pos.y );
            
            //////////////////////////////////////////////////////////////////
            mCircleLine.push_back( pos );
            dir = q * dir;
        }
    }

    /**
    -----------------------------------------------------------------------------
    TerrainCircleDecorator
    -----------------------------------------------------------------------------
    */
    TerrainCircleDecorator::TerrainCircleDecorator(const String& name, Scene* scene)
        :mScene(scene)
        ,mBoldSize(1)
        ,mColour(ColourValue::Green)
        ,mOgreManualObject(NULL)
        ,mRadius(2)
        ,mBuildPointCount(-1)
    {
        buildMaterial();
        createOgreManualObject();
        buildMesh();
    }

    //-----------------------------------------------------------------------
    TerrainCircleDecorator::~TerrainCircleDecorator()
    {
        destroyOgreManualObject();
    }

    //-----------------------------------------------------------------------
    void TerrainCircleDecorator::rebuild(void)
    {
        mTerrainCircleLineList.build( mScene->getTerrainManager(), mCenter, mRadius );
        buildMesh();
    }

    //-----------------------------------------------------------------------
    void TerrainCircleDecorator::refresh(void)
    {
        if ( getVisible() == false )
            return;

        mTerrainCircleLineList.build( mScene->getTerrainManager(), mCenter, mRadius );
        if ( mBuildPointCount == mTerrainCircleLineList.mCircleLine.size() )
        {
            refreshMesh();
        }else
        {
            buildMesh();
        }
    }

    //-----------------------------------------------------------------------
    void TerrainCircleDecorator::setBoldSize(Flt size)
    {
        mBoldSize = size;
    }

    //-----------------------------------------------------------------------
    Flt TerrainCircleDecorator::getBoldSize(void)
    {
        return mBoldSize;
    }

    //-----------------------------------------------------------------------
    void TerrainCircleDecorator::setColour(Color colour)
    {
        mColour = ColourValue(colour.r,colour.g,colour.b,colour.a);
        refresh();
    }

    //-----------------------------------------------------------------------
    Color TerrainCircleDecorator::getColour()
    {
        return Color(mColour.r,mColour.g,mColour.b,mColour.a);
    }

    //-----------------------------------------------------------------------
    void TerrainCircleDecorator::setVisible(Bool visible)
    {
        if (mSceneNode)
            mSceneNode->setVisible(visible);
        refresh();
    }

    //-----------------------------------------------------------------------
    Bool TerrainCircleDecorator::getVisible()
    {
        if (mSceneNode)
            return mSceneNode->getVisible();
        return false;
    }

    //-----------------------------------------------------------------------
    void TerrainCircleDecorator::setRadius(Flt radius) 
    {
        mRadius = radius;
        refresh();
    }

    //-----------------------------------------------------------------------
    void TerrainCircleDecorator::setCenter(Vec3 pos)
    {
        mCenter = pos;
        refresh();
    }

    //-----------------------------------------------------------------------
    void TerrainCircleDecorator::createOgreManualObject()
    {
        //����ʵ�����
        mOgreManualObject = mScene->getOgreSceneManager()->createManualObject();
        mOgreManualObject->setCastShadows(false);
        //mOgreManualObject->setRenderQueueGroup(Ogre::RENDER_QUEUE_OVERLAY-1);
        mOgreManualObject->setRenderQueueGroup(Ogre::RENDER_QUEUE_9);
       
        DYNAMIC_ASSERT(mOgreManualObject!=NULL);

        if ( mOgreManualObject )
        {
            // ���ð�ʵ�����Ĺ�����
            //mOgreManualObject->setUserAny( Any((ISceneObject*)this) );

            // ����ʵ��ڵ�
            mSceneNode = MG_NEW MGSceneNode(mScene->getOgreSceneManager()->getRootSceneNode(),mScene);

            // ��ʵ��
            mSceneNode->getOgreSceneNode()->attachObject( mOgreManualObject );
        }
    }

    //-----------------------------------------------------------------------
    void TerrainCircleDecorator::destroyOgreManualObject()
    {
        //����ʵ�����
        if ( mOgreManualObject )
        {
            mScene->getOgreSceneManager()->destroyManualObject(mOgreManualObject);
            mOgreManualObject = NULL;
        }

        //����ʵ��ڵ�
        MG_SAFE_DELETE( mSceneNode );
    }

    //-----------------------------------------------------------------------
    void TerrainCircleDecorator::buildMaterial(void)
    {
        Str matName = getMaterialName();

        /// �õ��򴴽�����
        mOgreMaterialPtr = Ogre::MaterialManager::getSingleton().getByName(matName);
        if (mOgreMaterialPtr.isNull())
        {
            mOgreMaterialPtr = Ogre::MaterialManager::getSingleton().create(matName, 
                Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
            mOgreMaterialPtr->setReceiveShadows( false );

            /// �õ���Ⱦͨ��
            Ogre::Pass* pass = mOgreMaterialPtr->getTechnique(0)->getPass(0);
            pass->setLightingEnabled(false);
            pass->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
            pass->setCullingMode(Ogre::CULL_NONE);
            pass->setDepthCheckEnabled( false );
        }
    }

    //-----------------------------------------------------------------------
    Str TerrainCircleDecorator::getMaterialName(void)
    {
        return "_MATERIAL_TERRAINCIRCLEDECORATOR";
    }

    //-----------------------------------------------------------------------
    void TerrainCircleDecorator::buildMesh(void)
    {
        if ( mTerrainCircleLineList.mCircleLine.size() >= 2 )
        {
            mOgreManualObject->clear();

            mOgreManualObject->setDynamic(true);

            mOgreManualObject->begin(  mOgreMaterialPtr->getName(), Ogre::RenderOperation::OT_LINE_LIST );
            {
                std::vector<Vec3>::iterator iter = mTerrainCircleLineList.mCircleLine.begin();
                for ( ; iter != mTerrainCircleLineList.mCircleLine.end(); iter++ )
                {
                    Vec3 pos = *iter;
                    mOgreManualObject->position( pos.x, pos.y, pos.z );
                    mOgreManualObject->colour( mColour );
                }
            }
            mOgreManualObject->end();

            mBuildPointCount = mTerrainCircleLineList.mCircleLine.size();
        }
    }

    //-----------------------------------------------------------------------
    void TerrainCircleDecorator::refreshMesh(void)
    {
        if ( mTerrainCircleLineList.mCircleLine.size() >= 2 )
        {
            if ( mBuildPointCount == mTerrainCircleLineList.mCircleLine.size() )
            {
                if ( mOgreManualObject )
                {
                    mOgreManualObject->beginUpdate(0);
                    {
                        std::vector<Vec3>::iterator iter = mTerrainCircleLineList.mCircleLine.begin();
                        for ( ; iter != mTerrainCircleLineList.mCircleLine.end(); iter++ )
                        {
                            Vec3 pos = *iter;
                            mOgreManualObject->position( pos.x, pos.y, pos.z );
                            mOgreManualObject->colour( mColour );
                        }
                    }

                    mOgreManualObject->end();
                }
            }
        }
    }



}