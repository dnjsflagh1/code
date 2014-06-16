/******************************************************************************/
#include "stdafx.h"
#include "TerrainGridsDecorator.h"
#include "Scene.h"
#include "MGSceneNode.h"
#include "EngineMain.h"
#include "MGEngineUtility.h"
#include "TerrainGroundSurface.h"

/******************************************************************************/

namespace MG
{

    /**
    -----------------------------------------------------------------------------
    TerrainChunkGridsLineList
    -----------------------------------------------------------------------------
    */
    TerrainChunkGridsLineList::TerrainChunkGridsLineList()
    {

    }

    //-----------------------------------------------------------------------
    void TerrainChunkGridsLineList::build( TerrainManager* terrainMgr )
    {
        //////////////////////////////////////////////////////
        mLinePointList.clear();
 
        Vec3 V0,V1,V2,V3;
        UInt count = terrainMgr->getTerrainChunkCount();

        for ( UInt i=0; i<count; i++ )
        {
            TerrainChunk* chunk = terrainMgr->getTerrainChunkByIndex(i);

            if (chunk)
            {
                Ogre::Rect rect = chunk->getBoundingRect();

                /*
                V0    V1
                *-----*
                |     |  
                V2    V3
                *-----*
                */

                V0 = Vec3(rect.left,0,rect.top);
                V1 = Vec3(rect.right,0,rect.top);
                V2 = Vec3(rect.left,0,rect.bottom);
                V3 = Vec3(rect.right,0,rect.bottom);

                mLinePointList.push_back( V0 );
                mLinePointList.push_back( V1 );

                mLinePointList.push_back( V0 );
                mLinePointList.push_back( V2 );

                mLinePointList.push_back( V1 );
                mLinePointList.push_back( V3 );

                mLinePointList.push_back( V2 );
                mLinePointList.push_back( V3 );
            }
        }
    }



    /**
    -----------------------------------------------------------------------------
    TerrainLogicGridsLineList
    -----------------------------------------------------------------------------
    */
    TerrainLogicGridsLineList::TerrainLogicGridsLineList()
    {

    }

    //-----------------------------------------------------------------------
    void TerrainLogicGridsLineList::build( TerrainManager* terrainMgr )
    {
        //////////////////////////////////////////////////////
        mLinePointList.clear();

        Vec3 V0,V1,V2,V3;
        UInt count = terrainMgr->getTerrainChunkCount();

        Flt offset = terrainMgr->getConfig().gridSize *  terrainMgr->getConfig().gridSideNumInBatch;

        for ( UInt i=0; i<count; i++ )
        {
            TerrainChunk* chunk = terrainMgr->getTerrainChunkByIndex(i);

            if (chunk)
            {
                Ogre::Rect rect = chunk->getBoundingRect();


                for (Flt y=rect.top; y<rect.bottom; y+=offset)
                {
                    for (Flt x=rect.left; x<rect.right; x+=offset)
                    {
                        /*
                        V0    V1
                        *-----*
                        |     |  
                        V2    V3
                        *-----*
                        */

                        V0 = Vec3(x,0,y);
                        V1 = Vec3(x+offset,0,y);
                        V2 = Vec3(x,0,y+offset);
                        V3 = Vec3(x+offset,0,y+offset);

                        mLinePointList.push_back( V0 );
                        mLinePointList.push_back( V1 );

                        mLinePointList.push_back( V0 );
                        mLinePointList.push_back( V2 );

                        mLinePointList.push_back( V1 );
                        mLinePointList.push_back( V3 );

                        mLinePointList.push_back( V2 );
                        mLinePointList.push_back( V3 );

                    }
                }
            }
        }
    }

    


    /**
    -----------------------------------------------------------------------------
    TerrainTileGridsLineList
    -----------------------------------------------------------------------------
    */
    TerrainTileGridsLineList::TerrainTileGridsLineList()
    {

    }

    //-----------------------------------------------------------------------
    void TerrainTileGridsLineList::build( TerrainManager* terrainMgr )
    {
        //////////////////////////////////////////////////////
        mLinePointList.clear();

        Vec3 V0,V1,V2,V3;
        UInt count = terrainMgr->getTerrainChunkCount();

        for ( UInt i=0; i<count; i++ )
        {
            TerrainChunk* chunk = terrainMgr->getTerrainChunkByIndex(i);

            if (chunk)
            {
                TerrainGroundSurface* surface = chunk->getTerrainGroundSurface();

                if ( surface )
                {
                    UInt num = surface->getTileSideNumInChunk();

                    for (UInt y=0; y<num; y++)
                    {
                        for (UInt x=0; x<num; x++)
                        {
                            TerrainTile* tile = surface->getTileGridDataByIndex(x,y);
                            
                            if ( tile )
                            {
                                Ogre::Rect rect =  tile->render->getWorldBoundingRect();

                                /*
                                V0    V1
                                *-----*
                                |     |  
                                V2    V3
                                *-----*
                                */

                                V0 = Vec3(rect.left,0,rect.top);
                                V1 = Vec3(rect.right,0,rect.top);
                                V2 = Vec3(rect.left,0,rect.bottom);
                                V3 = Vec3(rect.right,0,rect.bottom);

                                mLinePointList.push_back( V0 );
                                mLinePointList.push_back( V1 );

                                mLinePointList.push_back( V0 );
                                mLinePointList.push_back( V2 );

                                mLinePointList.push_back( V1 );
                                mLinePointList.push_back( V3 );

                                mLinePointList.push_back( V2 );
                                mLinePointList.push_back( V3 );
                            }
                        }
                    }
                }
            }
        }
    }

    /**
    -----------------------------------------------------------------------------
    TerrainCircleDecorator
    -----------------------------------------------------------------------------
    */
    TerrainGridsDecorator::TerrainGridsDecorator(const String& name, Scene* scene)
        :mScene(scene)
        ,mBoldSize(1)
        ,mChunkColour(ColourValue::Red)
        ,mTileColour(ColourValue::Blue)
        ,mLogicColour(ColourValue::White)
        ,mOgreManualObject(NULL)
        ,mTerrainChunkGridsLineBuildPointCount(-1)
        ,mTerrainTileGridsLineBuildPointCount(-1)
        ,mTerrainLogicGridsLineBuildPointCount(-1)
    {
        buildMaterial();
        createOgreManualObject();
        buildMesh();
    }

    //-----------------------------------------------------------------------
    TerrainGridsDecorator::~TerrainGridsDecorator()
    {
        destroyOgreManualObject();
    }

    //-----------------------------------------------------------------------
    void TerrainGridsDecorator::rebuild(void)
    {
        mTerrainChunkGridsLineList.build( mScene->getTerrainManager() );
        mTerrainTileGridsLineList.build( mScene->getTerrainManager() );
        mTerrainLogicGridsLineList.build( mScene->getTerrainManager() );
        buildMesh();
    }

    //-----------------------------------------------------------------------
    void TerrainGridsDecorator::refresh(void)
    {
        if ( getVisible() == false )
            return;

        mTerrainChunkGridsLineList.build( mScene->getTerrainManager() );
        mTerrainTileGridsLineList.build( mScene->getTerrainManager() );
        mTerrainLogicGridsLineList.build( mScene->getTerrainManager() );

        if ( ( mTerrainChunkGridsLineBuildPointCount != mTerrainChunkGridsLineList.mLinePointList.size() ) ||
             ( mTerrainTileGridsLineBuildPointCount != mTerrainTileGridsLineList.mLinePointList.size() ) ||
             ( mTerrainLogicGridsLineBuildPointCount != mTerrainLogicGridsLineList.mLinePointList.size() )
            )
        {
            buildMesh();
        }else
        {
            refreshMesh();
        }


    }

    //-----------------------------------------------------------------------
    void TerrainGridsDecorator::setBoldSize(Flt size)
    {
        mBoldSize = size;
    }

    //-----------------------------------------------------------------------
    Flt TerrainGridsDecorator::getBoldSize(void)
    {
        return mBoldSize;
    }

    //-----------------------------------------------------------------------
    void TerrainGridsDecorator::setColour(Color colour)
    {
        mChunkColour = ColourValue(colour.r,colour.g,colour.b,colour.a);
        refresh();
    }

    //-----------------------------------------------------------------------
    Color TerrainGridsDecorator::getColour()
    {
        return Color(mChunkColour.r,mChunkColour.g,mChunkColour.b,mChunkColour.a);
    }

    //-----------------------------------------------------------------------
    void TerrainGridsDecorator::setChunkColour(Color colour)
    {
        mChunkColour = ColourValue(colour.r,colour.g,colour.b,colour.a);
    }

    //-----------------------------------------------------------------------
    void TerrainGridsDecorator::setTileColour(Color colour)
    {
        mTileColour = ColourValue(colour.r,colour.g,colour.b,colour.a);
    }

    //-----------------------------------------------------------------------
    void TerrainGridsDecorator::setVisible(Bool visible)
    {
        if (mSceneNode)
            mSceneNode->setVisible(visible);
        refresh();
    }

    //-----------------------------------------------------------------------
    Bool TerrainGridsDecorator::getVisible()
    {
        if (mSceneNode)
            return mSceneNode->getVisible();
        return false;
    }


    //-----------------------------------------------------------------------
    void TerrainGridsDecorator::createOgreManualObject()
    {
        //创建实体对象
        mOgreManualObject = mScene->getOgreSceneManager()->createManualObject();
        mOgreManualObject->setCastShadows(false);
        mOgreManualObject->setRenderQueueGroup(Ogre::RENDER_QUEUE_OVERLAY);

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
    void TerrainGridsDecorator::destroyOgreManualObject()
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
    void TerrainGridsDecorator::buildMaterial(void)
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
    Str TerrainGridsDecorator::getMaterialName(void)
    {
        return "_MATERIAL_TERRAINGRIDSDECORATOR";
    }

    //-----------------------------------------------------------------------
    void TerrainGridsDecorator::buildMesh(void)
    {
        mOgreManualObject->setDynamic(true);

        mOgreManualObject->begin(  mOgreMaterialPtr->getName(), Ogre::RenderOperation::OT_LINE_LIST );
        {
			if ( mTerrainLogicGridsLineList.mLinePointList.size() >= 2 )
			{

				std::vector<Vec3>::iterator iter = mTerrainLogicGridsLineList.mLinePointList.begin();
				for ( ; iter != mTerrainLogicGridsLineList.mLinePointList.end(); iter++ )
				{
					Vec3 pos = *iter;
					mOgreManualObject->position( pos.x, pos.y, pos.z );
					mOgreManualObject->colour( mLogicColour );
				}
				mTerrainLogicGridsLineBuildPointCount = mTerrainLogicGridsLineList.mLinePointList.size();
			}

            if ( mTerrainTileGridsLineList.mLinePointList.size() >= 2 )
            {

                std::vector<Vec3>::iterator iter = mTerrainTileGridsLineList.mLinePointList.begin();
                for ( ; iter != mTerrainTileGridsLineList.mLinePointList.end(); iter++ )
                {
                    Vec3 pos = *iter;
                    mOgreManualObject->position( pos.x, pos.y, pos.z );
                    mOgreManualObject->colour( mTileColour );
                }
                mTerrainTileGridsLineBuildPointCount = mTerrainTileGridsLineList.mLinePointList.size();
            }

            if ( mTerrainChunkGridsLineList.mLinePointList.size() >= 2 )
            {
                std::vector<Vec3>::iterator iter = mTerrainChunkGridsLineList.mLinePointList.begin();
                for ( ; iter != mTerrainChunkGridsLineList.mLinePointList.end(); iter++ )
                {
                    Vec3 pos = *iter;
                    mOgreManualObject->position( pos.x, pos.y, pos.z );
                    mOgreManualObject->colour( mChunkColour );
                }
  
                mTerrainChunkGridsLineBuildPointCount = mTerrainChunkGridsLineList.mLinePointList.size();
            }
        }

        mOgreManualObject->end();
    }

    //-----------------------------------------------------------------------
    void TerrainGridsDecorator::refreshMesh(void)
    {
       mOgreManualObject->beginUpdate(0);

       {
		   if ( mTerrainLogicGridsLineList.mLinePointList.size() >= 2 )
		   {
			   if ( mTerrainLogicGridsLineBuildPointCount == mTerrainLogicGridsLineList.mLinePointList.size() )
			   {
				   if ( mOgreManualObject )
				   {
					   {
						   std::vector<Vec3>::iterator iter = mTerrainLogicGridsLineList.mLinePointList.begin();
						   for ( ; iter != mTerrainLogicGridsLineList.mLinePointList.end(); iter++ )
						   {
							   Vec3 pos = *iter;
							   mOgreManualObject->position( pos.x, pos.y, pos.z );
							   mOgreManualObject->colour( mLogicColour );
						   }
					   }
				   }
			   }
		   }

           if ( mTerrainTileGridsLineList.mLinePointList.size() >= 2 )
           {
               if ( mTerrainTileGridsLineBuildPointCount == mTerrainTileGridsLineList.mLinePointList.size() )
               {
                   if ( mOgreManualObject )
                   {
                       {
                           std::vector<Vec3>::iterator iter = mTerrainTileGridsLineList.mLinePointList.begin();
                           for ( ; iter != mTerrainTileGridsLineList.mLinePointList.end(); iter++ )
                           {
                               Vec3 pos = *iter;
                               mOgreManualObject->position( pos.x, pos.y, pos.z );
                               mOgreManualObject->colour( mTileColour );
                           }
                       }
                   }
               }
           }

           if ( mTerrainChunkGridsLineList.mLinePointList.size() >= 2 )
           {
               if ( mTerrainChunkGridsLineBuildPointCount == mTerrainChunkGridsLineList.mLinePointList.size() )
               {
                   if ( mOgreManualObject )
                   {
                       {
                           std::vector<Vec3>::iterator iter = mTerrainChunkGridsLineList.mLinePointList.begin();
                           for ( ; iter != mTerrainChunkGridsLineList.mLinePointList.end(); iter++ )
                           {
                               Vec3 pos = *iter;
                               mOgreManualObject->position( pos.x, pos.y, pos.z );
                               mOgreManualObject->colour( mChunkColour );
                           }
                       }
                   }
               }
           }
       }

        mOgreManualObject->end();

        


    }



}