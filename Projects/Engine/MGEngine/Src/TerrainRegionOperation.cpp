/******************************************************************************/
#include "stdafx.h"
#include "TerrainRegionOperationManager.h"
#include "TerrainRegionOperation.h"
#include "Scene.h"
#include "TerrainChunk.h"
#include "BrushSystem.h"
#include "TerrainTiles.h"
#include "BrushStyle.h"
#include "BrushShape.h"
#include "EngineUtil.h"
#include "TerrainRegionManager.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //TerrainBlockOperation
    /******************************************************************************/
    TerrainRegionOperation::TerrainRegionOperation()
    {

    }

    //-----------------------------------------------------------------------
    TerrainRegionOperation::~TerrainRegionOperation()
    {

    }

    //-----------------------------------------------------------------------
    void TerrainRegionOperation::execute( TerrainChunk* chunk, Ogre::Rect& rect )
    {
        if ( getScene() )
        {
            TerrainManager* terrain = static_cast<TerrainManager*>(getScene()->getTerrainManager());
            if ( terrain )
            {
                TerrainGroundSurface* surface             = chunk->getTerrainGroundSurface();
                TerrainRegionManager* regionManager = terrain->getTerrainRegionManager();
                TerrainChunkRegions* chunkRegions   = chunk->getTerrainRegion();
                TerrainRegion* visibledRegion       = NULL;
                
                if ( regionManager->getBlockRegionVisible() )
                {
                    visibledRegion = chunkRegions->getTerrainBlockBaseRegion();     
                }else
                {            
                    visibledRegion = chunkRegions->getVisibledCustomRegion();
                }

                if ( !visibledRegion )
                    return;

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
                Vector3 w0 = Vector3( (brushPos.x - brushSize), 0, (brushPos.z -brushSize) );
                Vector3 w1 = Vector3( (brushPos.x + brushSize), 0, (brushPos.z - brushSize) );
                Vector3 w2 = Vector3( (brushPos.x - brushSize), 0, (brushPos.z + brushSize) );
                Vector3 w3 = Vector3( (brushPos.x + brushSize), 0, (brushPos.z + brushSize) );


                /* // 地形静态物件层坐标
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
                visibledRegion->convertWorldPositionToGridPoint(Vec2(w0.x,w0.z),b0);
                visibledRegion->convertWorldPositionToGridPoint(Vec2(w1.x,w1.z),b1);
                visibledRegion->convertWorldPositionToGridPoint(Vec2(w2.x,w2.z),b2);
                visibledRegion->convertWorldPositionToGridPoint(Vec2(w3.x,w3.z),b3);

                // 遍历区域
                UInt top,bottom,left,right;
                bottom  = b2.y ;
                top     = b0.y ;
                left    = b2.x ;
                right   = b3.x ;

                Vec2 margin;
                for (uint16 y = bottom; y <= top; y ++)
                {
                    for (uint16 x = left; x <= right; x ++)
                    {
                        // 得到世界坐标
                        Vec2 world2DPos;
                        visibledRegion->convertGridPointToWorldPosition(Vec2(x,y),world2DPos);

                        // 判断是否在笔刷范围内
                        //if ( BrushSystem::getInstance().getActiveShape()->isValidPos( world2DPos, margin ) )
                        {
                            influenceRegionMap(surface,visibledRegion,x,y);
                        }
                    }
                }
            }
        }
    }

    //-----------------------------------------------------------------------
    void TerrainRegionOperation::rollback()
    {

    }

    /******************************************************************************/
    //TerrainAddBlockOperation
    /******************************************************************************/
    TerrainAddRegionOperation::TerrainAddRegionOperation()
    {

    }

    //-----------------------------------------------------------------------
    TerrainAddRegionOperation::~TerrainAddRegionOperation()
    {

    }

    //-----------------------------------------------------------------------
    void TerrainAddRegionOperation::influenceRegionMap(TerrainGroundSurface* tilesMgr, TerrainRegion* blockRegion, Int x, Int y)
    {
        TerrainRegionGridData* gridData  = blockRegion->getGridDataByIndex(x,y);
        if ( gridData )
        {
            gridData->mask = 255;
        }

        // 设置网格周围四个顶点
        tilesMgr->setRegionDisplay( x, y , 1);
    }

    /******************************************************************************/
    //TerrainRemoveRegionOperation
    /******************************************************************************/
    TerrainRemoveRegionOperation::TerrainRemoveRegionOperation()
    {

    }

    //-----------------------------------------------------------------------
    TerrainRemoveRegionOperation::~TerrainRemoveRegionOperation()
    {

    }
    //-----------------------------------------------------------------------
    void TerrainRemoveRegionOperation::influenceRegionMap(TerrainGroundSurface* surface, TerrainRegion* region, Int x, Int y)
    {
        TerrainRegionGridData* gridData  = region->getGridDataByIndex(x,y);
        if ( gridData )
        {
            gridData->mask = 0;
        }

        // 设置网格周围四个顶点
        surface->setRegionDisplay( x, y , 0);
    }
}


