/******************************************************************************/
#ifndef _TERRAINBBGROUNDSURFACE_H_
#define _TERRAINBBGROUNDSURFACE_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "ITerrain.h"
#include "MGGrid.h"
#include "TerrainTiles.h"
#include "TerrainTilesMaterial.h"
#include "TerrainTilesLayerBlendMap.h"
#include "TerrainSurface.h"
#include "TerrainGroundSurface.h"

/******************************************************************************/
namespace MG
{

    //×××××××××××××××××××××××××××××××××××××××××××××××××
    //×××××××××××××××××××××××××××××××××××××××××××××××××


    /******************************************************************************/
    /*
    @remarks:
    每层贴图对应一个TerrainTilesLayerBlendMap对象。
    每四层贴图(以及TerrainTilesLayerBlendMap)通过一张调色板贴图(BlendTexture)混合。
    */
    /******************************************************************************/
    class TerrainBBGroundSurface :  public TerrainGroundSurface
    {
    public:
        TerrainBBGroundSurface(TerrainManager* terrainMgr, Scene* scene, TerrainChunk* chunk);
        virtual ~TerrainBBGroundSurface();

    public:

        // 创建分块渲染者
        virtual TerrainTileRender*  createTerrainTileRender( TerrainManager* mgr, TerrainChunk* chunk, 
            TerrainNode* node, TerrainTile* tile, UInt index );

        /*########################################
        //          贴图层和混合层操作         
        #########################################*/

        virtual void                loadBlendLayerMap( Str& path );
        virtual void                unLoadBlendLayerMap();
        virtual void                saveBlendLayerMap( Str& path );

		//重新排序BlendMapTex的图层(此函数仅用于自动裁剪地图前从新排序blendMap)
		virtual void                _reorderBlendLayerMap( const Str& path );

    private:


    };

}

/******************************************************************************/

#endif
