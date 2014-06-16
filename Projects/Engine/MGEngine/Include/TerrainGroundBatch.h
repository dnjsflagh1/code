/******************************************************************************/
#ifndef _TERRAINGROUNDBATCH_H_
#define _TERRAINGROUNDBATCH_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "TerrainBatch.h"
#include "TerrainTilesLayerBlendMap.h"
#include "TerrainTilesMaterial.h"
#include "TerrainTilesGpu.h"


/******************************************************************************/
namespace MG
{

    //×××××××××××××××××××××××××××××××××××××××××××××××××
    //×××××××××××××××××××××××××××××××××××××××××××××××××

    /******************************************************************************/
    //地块中的单次渲染管理
    /******************************************************************************/
    class TerrainGroundBatch : public TerrainBatch
    {
    public:
        TerrainGroundBatch( Scene* scene, TerrainTileRender* tileRender, TerrainBatch* parent, 
            const AxisAlignedBox& aabb, Ogre::Rect vertexRectInTile,
            MovableObject* movableObject );
        virtual ~TerrainGroundBatch();

    public:

        // 加载和卸载资源
        virtual void                    load();
        virtual void                    unLoad();

        /// Get the material being used for the terrain
        virtual MaterialPtr&            getOrGenerateMaterialPtr();
    };



}


/******************************************************************************/

#endif