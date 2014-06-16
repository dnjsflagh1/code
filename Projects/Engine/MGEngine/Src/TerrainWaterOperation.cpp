/******************************************************************************/
#include "stdafx.h"
#include "TerrainWaterOperation.h"
#include "Scene.h"
#include "TerrainChunk.h"
#include "BrushSystem.h"
#include "TerrainTiles.h"
#include "TerrainWaterOperationManager.h"
#include "BrushStyle.h"
#include "BrushShape.h"
#include "TerrainWaterSurface.h"
#include "TerrainWaterBatch.h"
#include "TerrainWaterTiles.h"
#include "EditorSystem.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //TerrainWaterOperation
    /******************************************************************************/
    TerrainWaterOperation::TerrainWaterOperation()
    {

    }

    //-----------------------------------------------------------------------
    TerrainWaterOperation::~TerrainWaterOperation()
    {

    }

    //-----------------------------------------------------------------------
    void TerrainWaterOperation::execute( TerrainChunk* chunk, Ogre::Rect& worldRect )
    {
        TerrainWaterSurface* surface = chunk->getTerrainWaterSurface();

        if ( surface )
        {

            Vec3 brushPos   = BrushSystem::getInstance().getStartPos();
            Flt brushSize   = BrushSystem::getInstance().getSize();

            /* // 世界坐标

            -z
            |
            |
            w0---------w1
            |          |
            | [brush]  |
            |          |
            w2---------w3----+x
            */

            // 世界坐标Rect
            Vec2 w0 = Vec2( worldRect.left,   worldRect.top );
            Vec2 w1 = Vec2( worldRect.right,  worldRect.top );
            Vec2 w2 = Vec2( worldRect.left,   worldRect.bottom );
            Vec2 w3 = Vec2( worldRect.right,  worldRect.bottom );

            /* // 地形Tile坐标
            +y
            |
            |
            t0---------t1
            |          |
            | [brush]  |
            |          |
            t2---------t3----+x
            */
            // 地形坐标Rect

            Vec2 t0,t1,t2,t3; 
            surface->convertWorldPositionToGridPoint(w0, t0);
            surface->convertWorldPositionToGridPoint(w1, t1);
            surface->convertWorldPositionToGridPoint(w2, t2);
            surface->convertWorldPositionToGridPoint(w3, t3);

            for (uint16 y = t2.y; y <= t0.y; y ++)
            {
                for (uint16 x = t0.x; x <= t1.x; x ++)
                {
                    TerrainNodeGrid* node = surface->getGridDataByIndex(x,y);
                    if ( node && node->node )
                    {
                        Vec2 n0,n1,n2,n3; 

                        node->node->convertWorldPositionToGridPoint(w0, n0);
                        node->node->convertWorldPositionToGridPoint(w1, n1);
                        node->node->convertWorldPositionToGridPoint(w2, n2);
                        node->node->convertWorldPositionToGridPoint(w3, n3);

                        // loop tile in node
                        for (uint16 y2 = n2.y; y2 <= n0.y; y2 ++)
                        {
                            for (uint16 x2 = n0.x; x2 <= n1.x; x2 ++)
                            {
                                TerrainTile* tile = node->node->getGridDataByIndex(x2,y2);


                                if ( tile && tile->render )
                                {
                                    TerrainWaterTileRender* render = (TerrainWaterTileRender*)tile->render;
                                    if ( render == NULL )
                                        break;

                                    
                                    /* // 地形Batch坐标
                                    +y
                                    |
                                    |
                                    b0---------b1
                                    |          |
                                    | [brush]  |
                                    |          |
                                    b2---------b3----+x
                                    */
                                    // 地形坐标Rect

                                    Vec2 b0,b1,b2,b3; 
                                    render->convertWorldPositionToGridPoint(w0, b0);
                                    render->convertWorldPositionToGridPoint(w1, b1);
                                    render->convertWorldPositionToGridPoint(w2, b2);
                                    render->convertWorldPositionToGridPoint(w3, b3);


                                    for (uint16 batchIndexY = b2.y; batchIndexY <= b0.y; batchIndexY ++)
                                    {
                                        for (uint16 batchIndexX = b0.x; batchIndexX <= b1.x; batchIndexX ++)
                                        {
                                            TerrainBatchGrid* batchGrid = render->getGridDataByIndex(batchIndexX,batchIndexY);
                                            if ( batchGrid && batchGrid->batch )
                                            {
                                                TerrainWaterBatch* batch = (TerrainWaterBatch*)batchGrid->batch;
                                                if ( batch == NULL )
                                                    break;

                                                influenceBatch( surface, batch );
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    //-----------------------------------------------------------------------
    void TerrainWaterOperation::rollback()
    {

    }

    /******************************************************************************/
    //TerrainWaterShowOperation
    /******************************************************************************/
    TerrainWaterShowOperation::TerrainWaterShowOperation()
    {

    }

    //-----------------------------------------------------------------------
    TerrainWaterShowOperation::~TerrainWaterShowOperation()
    {

    }

    //-----------------------------------------------------------------------
    void TerrainWaterShowOperation::influenceBatch( TerrainWaterSurface* surface, TerrainWaterBatch* batch )
    {
        UInt matGroupID = EditorSystem::getInstance().getTerrainWaterShowOperationManager()->getWaterGroupID();
        batch->setMaterialGroupID( matGroupID );
        batch->setRenderEnable( true );
        batch->load();
    }

    /******************************************************************************/
    //TerrainWaterHideOperation
    /******************************************************************************/
    TerrainWaterHideOperation::TerrainWaterHideOperation()
    {

    }

    //-----------------------------------------------------------------------
    TerrainWaterHideOperation::~TerrainWaterHideOperation()
    {

    }

    //-----------------------------------------------------------------------
    void TerrainWaterHideOperation::influenceBatch( TerrainWaterSurface* surface, TerrainWaterBatch* batch )
    {
        batch->setRenderEnable( false );
    }
}


