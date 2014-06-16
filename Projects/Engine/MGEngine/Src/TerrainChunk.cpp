/******************************************************************************/
#include "stdafx.h"
#include "TerrainChunk.h"
#include "TerrainManager.h"
#include "EngineMain.h"
#include "Scene.h"
#include "MGSceneNode.h"
#include "CollisionSystem.h"
#include "ResourceManager.h"

#include "TerrainRegionManager.h"
#include "TerrainGroundSurface.h"
#include "TerrainWaterSurface.h"

#include "TerrainBBGroundSurface.h"
#include "TerrainSBGroundSurface.h"

/******************************************************************************/

namespace MG
{

	//-----------------------------------------------------------------------
	TerrainChunk::TerrainChunk(TerrainManager* mgr, Scene* scene, Vec2 indexPos, Vec2 worldCenterPos, TerrainChunkDeclare& decl)
        :mOwner(mgr)
        ,mScene(scene)
        ,mTerrainGroupIndex(indexPos)
        ,mWorldCenterPos(worldCenterPos)
        ,mTerrainGroundSurface(NULL)
        ,mTerrainWaterSurface(NULL)
        ,mTerrainRegion(NULL)
        ,mChunkDecl(decl)
	{
 
        /////////////////////////////////////////////////////////////////

        {
            std::ostringstream s;
            s << "TerrainChunk_" << mTerrainGroupIndex.x << "_" << mTerrainGroupIndex.y;
            mName = s.str();
        }
        {
            std::ostringstream s;
            s << mTerrainGroupIndex.x << "_" << mTerrainGroupIndex.y;
            mDirectionName = s.str();
        }

        /////////////////////////////////////////////////////////////////

        // 创建地形表面

        if ( mgr->getConfig().groundMatType == TMS_SMALL )
        {
            mTerrainGroundSurface = mOwner->getTerrainSurfaceManager()->createTerrainSBGroundSurface( this );
        }else
        {
            mTerrainGroundSurface = mOwner->getTerrainSurfaceManager()->createTerrainBBGroundSurface( this );
        }

        // 创建水形表面
        mTerrainWaterSurface = mOwner->getTerrainSurfaceManager()->createTerrainWaterSurface( this );

        // 创建地形区域
        mTerrainRegion  = mOwner->getTerrainRegionManager()->createTerrainChunkRegions( this );

        /////////////////////////////////////////////////////////////////
	}   
    
	//-----------------------------------------------------------------------
	TerrainChunk::~TerrainChunk()
	{
        unLoad();

        // 删除地形表面
        mOwner->getTerrainSurfaceManager()->destroyTerrainGroundSurface( mTerrainGroundSurface );
        // 删除水表面
        mOwner->getTerrainSurfaceManager()->destroyTerrainWaterSurface( mTerrainWaterSurface );
        // 删除地形区域
        mOwner->getTerrainRegionManager()->destroyTerrainChunkRegions( mTerrainRegion );
	}

    //-----------------------------------------------------------------------
    void TerrainChunk::update( Flt delta )
    {
        if ( mTerrainGroundSurface )
        {
            mTerrainGroundSurface->update( delta );
        }
        if ( mTerrainWaterSurface )
        {
            mTerrainWaterSurface->update( delta );
        }
    }

    //-----------------------------------------------------------------------
    void TerrainChunk::load(Str path)
    {
        ////////////////////////////////////////////////////////////////////////////

        generateBoundingShape();

        ////////////////////////////////////////////////////////////////////////////

		if ( EngineMain::getInstance().getMode() == EM_EDITOR )
		{
			if (!FileOp::isExistDirectory(path))
			{
				FileOp::createDirectory( path );
			}
		}

		mResourcePath = FileOp::getFullFilePath( path, mDirectionName );
		if ( EngineMain::getInstance().getMode() == EM_EDITOR )
		{
			if (!FileOp::isExistDirectory(mResourcePath))
			{
				FileOp::createDirectory( mResourcePath );
			}
		}
        Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mResourcePath.c_str(), "FileSystem", 
            mResourcePath.c_str(), false);

        ////////////////////////////////////////////////////////////////////////////
        
        if ( EngineMain::getInstance().display()->isDebugNoTerrain() == false )
        {
            if ( mTerrainGroundSurface )
            {
                mTerrainGroundSurface->load( mResourcePath );
                mTerrainGroundSurface->loadGridData();
            }
        }

        ////////////////////////////////////////////////////////////////////////////

        if ( EngineMain::getInstance().display()->isDebugNoWater() == false )
        {
            if ( mTerrainWaterSurface )
            {
                mTerrainWaterSurface->load( mResourcePath );
                mTerrainWaterSurface->loadGridData();
            }
        }

        ////////////////////////////////////////////////////////////////////////////
        
        if ( mTerrainRegion )
            mTerrainRegion->load( mResourcePath );
    }

    //-----------------------------------------------------------------------
    void TerrainChunk::save(Str path)
    {
        ////////////////////////////////////////////////////////////////////////////

		if ( EngineMain::getInstance().getMode() != EM_EDITOR )
		{
			return;
		}

		if (!FileOp::isExistDirectory(path))
			FileOp::createDirectory(path);
        Str chunkPath = FileOp::getFullFilePath( path, mDirectionName );
        FileOp::cleanDirectory( chunkPath );
        FileOp::createDirectory( chunkPath );
        
        ////////////////////////////////////////////////////////////////////////////
        
        if ( mTerrainGroundSurface )
            mTerrainGroundSurface->save( chunkPath );

        ////////////////////////////////////////////////////////////////////////////

        if ( mTerrainWaterSurface )
            mTerrainWaterSurface->save( chunkPath );

        ////////////////////////////////////////////////////////////////////////////

        if ( mTerrainRegion )
            mTerrainRegion->save( chunkPath );

    }

    //-----------------------------------------------------------------------
    void TerrainChunk::unLoad()
    {
        ////////////////////////////////////////////////////////////////////////////

        if ( mTerrainGroundSurface )
        {
            mTerrainGroundSurface->unLoadGridData();
            mTerrainGroundSurface->unLoad();
        }

        if ( mTerrainWaterSurface )
        {
            mTerrainWaterSurface->unLoadGridData();
            mTerrainWaterSurface->unLoad();
        }

        if ( mTerrainRegion )
            mTerrainRegion->unLoad();

        ////////////////////////////////////////////////////////////////////////////

        if ( mResourcePath.empty() == false )
        {
            Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup(mResourcePath.c_str());
            mResourcePath = "";
        }
    }

	//-----------------------------------------------------------------------
	void TerrainChunk::_reorderTextureLayer(const Str &path)
	{
		if ( mTerrainGroundSurface )
		{
			mTerrainGroundSurface->_reorderColorTextureLayerData(path);
		}
	}
 
    //-----------------------------------------------------------------------
    TerrainSurface* TerrainChunk::getTerrainSurface( TerrainSurfaceType type )
    {
        if ( type == TST_GROUND )
        {
            return mTerrainGroundSurface;
        }else
        if ( type == TST_WATER )
        {
            return mTerrainWaterSurface;
        }
        return NULL;
    }

    //-----------------------------------------------------------------------
    void TerrainChunk::generateBoundingShape()
    {
        ///////////////////////////////////////////////////////////////////////////////

        TerrainDeclare& decl    = mOwner->getConfig();
        Flt chunkHalfSize       = mOwner->getTerrainChunkHalfSize();
        Vector3 maximum         = Vector3(mWorldCenterPos.x + chunkHalfSize , decl.maxHeight , mWorldCenterPos.y + chunkHalfSize);
        Vector3 minimum         = Vector3(mWorldCenterPos.x - chunkHalfSize , decl.minHeight , mWorldCenterPos.y - chunkHalfSize);
        
        mBoundingBox.setMaximum(maximum);
        mBoundingBox.setMinimum(minimum);


        mBoundingRect.left      = mWorldCenterPos.x - chunkHalfSize;
        mBoundingRect.right     = mWorldCenterPos.x + chunkHalfSize;
        mBoundingRect.top       = mWorldCenterPos.y - chunkHalfSize;
        mBoundingRect.bottom    = mWorldCenterPos.y + chunkHalfSize;
    }


   
}

