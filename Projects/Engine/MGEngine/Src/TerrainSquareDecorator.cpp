/******************************************************************************/
#include "stdafx.h"
#include "TerrainSquareDecorator.h"
#include "Scene.h"
#include "MGSceneNode.h"
#include "EngineMain.h"
#include "MGEngineUtility.h"
/******************************************************************************/

namespace MG
{

    /**
    -----------------------------------------------------------------------------
    TerrainSquareLineList
    -----------------------------------------------------------------------------
    */
    TerrainSquareLineList::TerrainSquareLineList()
    {
        mLastBuildTime = MGTimeOp::getCurrTick();
		mOffset = 0.0f;
    }

    //-----------------------------------------------------------------------
    void TerrainSquareLineList::build( TerrainManager* terrainMgr , Vec3 center, Flt length, Flt gap )
    {
		Flt sideLength = length;
		Flt halfSideLength = sideLength/2;
		Flt     girth           = 4*sideLength;
		UInt    sectorCount		= girth/gap;
		sectorCount = sectorCount + sectorCount%2; 
		Flt		s				= girth/sectorCount;

		RectF rect;
		rect.left = center.x-halfSideLength;
		rect.top = center.z-halfSideLength;
		rect.right = center.x + halfSideLength;
		rect.bottom = center.z + halfSideLength; 

		Flt delta       = MGTimeOp::getCurrTick() - mLastBuildTime;
		mLastBuildTime  = MGTimeOp::getCurrTick();
		Flt speed = 0.003f;
		mOffset += delta*speed;
		if (mOffset > girth)
			mOffset = .0f;

		mSquareLine.clear();
		Vec3 pos;
		for (UInt i=0; i<sectorCount; ++i)
		{
			if (i*s+mOffset < sideLength)
			{
				pos = Vec3(rect.left+(i*s+mOffset),0,rect.top);
			}
			else if (i*s+mOffset < 2*sideLength)
			{
				pos = Vec3(rect.right, 0, rect.top+(i*s+mOffset)-sideLength);
			}
			else if (i*s+mOffset < 3*sideLength)
			{
				pos = Vec3(rect.right-(i*s+mOffset-2*sideLength), 0, rect.bottom);
			}
			else if (i*s+mOffset < 4*sideLength)
			{
				pos = Vec3(rect.left, 0, rect.bottom-(i*s+mOffset-3*sideLength));
			}
			else 
			{
				if (i*s+mOffset < girth+sideLength)
				{
					pos = Vec3(rect.left+(i*s+mOffset-girth),0,rect.top);
				}
				else if (i*s+mOffset < girth+2*sideLength)
				{
					pos = Vec3(rect.right, 0, rect.top+(i*s+mOffset-girth)-sideLength);
				}
				else if (i*s+mOffset < girth+3*sideLength)
				{
					pos = Vec3(rect.right-(i*s+mOffset-2*sideLength-girth), 0, rect.bottom);
				}
				else if (i*s+mOffset < girth+girth)
				{
					pos = Vec3(rect.left, 0, rect.bottom-(i*s+mOffset-3*sideLength-girth));
				}
			}
			terrainMgr->getStickHeight( Vec2(pos.x, pos.z), pos.y );
			mSquareLine.push_back( pos );
		}
    }

    /**
    -----------------------------------------------------------------------------
    TerrainSquareDecorator
    -----------------------------------------------------------------------------
    */
    TerrainSquareDecorator::TerrainSquareDecorator(const String& name, Scene* scene)
        :mScene(scene)
        ,mBoldSize(1)
        ,mColour(ColourValue::Green)
        ,mOgreManualObject(NULL)
        ,mSideLenght(2)
        ,mBuildPointCount(-1)
    {
        buildMaterial();
        createOgreManualObject();
        buildMesh();
    }

    //-----------------------------------------------------------------------
    TerrainSquareDecorator::~TerrainSquareDecorator()
    {
        destroyOgreManualObject();
    }

    //-----------------------------------------------------------------------
    void TerrainSquareDecorator::rebuild(void)
    {
        mTerrainSquareLineList.build( mScene->getTerrainManager(), mCenter, mSideLenght );
        buildMesh();
    }

    //-----------------------------------------------------------------------
    void TerrainSquareDecorator::refresh(void)
    {
        if ( getVisible() == false )
            return;

        mTerrainSquareLineList.build( mScene->getTerrainManager(), mCenter, mSideLenght );
        if ( mBuildPointCount == mTerrainSquareLineList.mSquareLine.size() )
        {
            refreshMesh();
        }else
        {
            buildMesh();
        }
    }

    //-----------------------------------------------------------------------
    void TerrainSquareDecorator::setBoldSize(Flt size)
    {
        mBoldSize = size;
    }

    //-----------------------------------------------------------------------
    Flt TerrainSquareDecorator::getBoldSize(void)
    {
        return mBoldSize;
    }

    //-----------------------------------------------------------------------
    void TerrainSquareDecorator::setColour(Color colour)
    {
        mColour = ColourValue(colour.r,colour.g,colour.b,colour.a);
        refresh();
    }

    //-----------------------------------------------------------------------
    Color TerrainSquareDecorator::getColour()
    {
        return Color(mColour.r,mColour.g,mColour.b,mColour.a);
    }

    //-----------------------------------------------------------------------
    void TerrainSquareDecorator::setVisible(Bool visible)
    {
        if (mSceneNode)
            mSceneNode->setVisible(visible);
        refresh();
    }

    //-----------------------------------------------------------------------
    Bool TerrainSquareDecorator::getVisible()
    {
        if (mSceneNode)
            return mSceneNode->getVisible();
        return false;
    }

    //-----------------------------------------------------------------------
    void TerrainSquareDecorator::setSideLength(Flt lenght) 
    {
        mSideLenght = lenght;
        refresh();
    }

    //-----------------------------------------------------------------------
    void TerrainSquareDecorator::setCenter(Vec3 pos)
    {
        mCenter = pos;
        refresh();
    }

    //-----------------------------------------------------------------------
    void TerrainSquareDecorator::createOgreManualObject()
    {
        //创建实体对象
        mOgreManualObject = mScene->getOgreSceneManager()->createManualObject();
        mOgreManualObject->setCastShadows(false);
        //mOgreManualObject->setRenderQueueGroup(Ogre::RENDER_QUEUE_OVERLAY-1);
        mOgreManualObject->setRenderQueueGroup(Ogre::RENDER_QUEUE_9);
       
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
    void TerrainSquareDecorator::destroyOgreManualObject()
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
    void TerrainSquareDecorator::buildMaterial(void)
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
    Str TerrainSquareDecorator::getMaterialName(void)
    {
        return "_MATERIAL_TERRAINSQUAREDECORATOR";
    }

    //-----------------------------------------------------------------------
    void TerrainSquareDecorator::buildMesh(void)
    {
        if ( mTerrainSquareLineList.mSquareLine.size() >= 2 )
        {
            mOgreManualObject->clear();

            mOgreManualObject->setDynamic(true);

            mOgreManualObject->begin(  mOgreMaterialPtr->getName(), Ogre::RenderOperation::OT_LINE_LIST );
            {
                std::vector<Vec3>::iterator iter = mTerrainSquareLineList.mSquareLine.begin();
                for ( ; iter != mTerrainSquareLineList.mSquareLine.end(); iter++ )
                {
                    Vec3 pos = *iter;
                    mOgreManualObject->position( pos.x, pos.y, pos.z );
                    mOgreManualObject->colour( mColour );
                }
            }
            mOgreManualObject->end();

            mBuildPointCount = mTerrainSquareLineList.mSquareLine.size();
        }
    }

    //-----------------------------------------------------------------------
    void TerrainSquareDecorator::refreshMesh(void)
    {
        if ( mTerrainSquareLineList.mSquareLine.size() >= 2 )
        {
            if ( mBuildPointCount == mTerrainSquareLineList.mSquareLine.size() )
            {
                if ( mOgreManualObject )
                {
                    mOgreManualObject->beginUpdate(0);
                    {
                        std::vector<Vec3>::iterator iter = mTerrainSquareLineList.mSquareLine.begin();
                        for ( ; iter != mTerrainSquareLineList.mSquareLine.end(); iter++ )
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