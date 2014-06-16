/******************************************************************************/
#include "stdafx.h"

#include "TerrainWaterSurface.h"
#include "TerrainWaterTiles.h"
#include "TerrainWaterBatch.h"
#include "TerrainChunk.h"
#include "EngineMain.h"
#include "Scene.h"
#include "TerrainTiles.h"
#include "TerrainNode.h"

/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------
    TerrainWaterTileRender::TerrainWaterTileRender( TerrainManager* mgr, TerrainChunk* chunk, TerrainNode* node, TerrainTile* tile, UInt index )
        :TerrainTileRender(mgr,chunk,chunk->getTerrainWaterSurface(), node, tile,index)
    {
    }

    //-----------------------------------------------------------------------
    TerrainWaterTileRender::~TerrainWaterTileRender()
    {
        unLoadRenderData();
    }

    //-----------------------------------------------------------------------
    void TerrainWaterTileRender::update( Flt delta )
    {
        TerrainTileRender::update( delta );


    }

    //-----------------------------------------------------------------------
    void TerrainWaterTileRender::load( )
    {
        TerrainTileRender::load();

    }

    //-----------------------------------------------------------------------
    void TerrainWaterTileRender::unload( )
    {
        TerrainTileRender::unload();

    }

    //-----------------------------------------------------------------------
    TerrainBatch*   TerrainWaterTileRender::createTerrainBatch( Scene* scene, TerrainTileRender* tileRender, TerrainBatch* parent, 
        const AxisAlignedBox& aabb, Ogre::Rect vertexRectInTile, MovableObject* movableObject)
    {
        return MG_NEW TerrainWaterBatch( scene, tileRender, parent, aabb, vertexRectInTile, movableObject);
    }

    //**********************************************************************************************************************
    //**********************************************************************************************************************



    //**********************************************************************************************************************
    //**********************************************************************************************************************

    //---------------------------------------------------------------------
    void TerrainWaterTileRender::applyRenderConfig()
    {
        TerrainTileRender::applyRenderConfig();

        /////////////////////////////////////////////////////////

    }



}

