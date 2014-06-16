/******************************************************************************/
#ifndef _TERRAINWATERTILES_H_
#define _TERRAINWATERTILES_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "TerrainTiles.h"


/******************************************************************************/
namespace MG
{
    //×××××××××××××××××××××××××××××××××××××××××××××××××
    //×××××××××××××××××××××××××××××××××××××××××××××××××

    /******************************************************************************/
    //地块中的单次渲染区域
    /******************************************************************************/
    class TerrainWaterTileRender : public TerrainTileRender
    {
    public:
        TerrainWaterTileRender( TerrainManager* mgr, TerrainChunk* chunk, TerrainNode* node, TerrainTile* tile, UInt index );
        virtual ~TerrainWaterTileRender();

    public:

        //**********************************************************************************************************************
        //**********************************************************************************************************************

        virtual void                    update( Flt delta ) ;

        virtual void                    load( ) ;
        virtual void                    unload( ) ;

        // 创建地形批次对象
        virtual TerrainBatch*           createTerrainBatch( Scene* scene, TerrainTileRender* tileRender, TerrainBatch* parent, 
                                            const AxisAlignedBox& aabb, Ogre::Rect vertexRectInTile, MovableObject* movableObject);


        /*########################################
        //      材质管理
        #########################################*/

    public:

        /// 应用显示参数修改
        virtual void                    applyRenderConfig();
    };



}

/******************************************************************************/

#endif
