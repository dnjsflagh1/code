/******************************************************************************/
#ifndef _TERRAINBLOCKOPERATION_H_
#define _TERRAINBLOCKOPERATION_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "EditorOperation.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    //游戏地形障碍操作
    /******************************************************************************/
    class TerrainRegionOperation : public EditorOperation
    {
    public:
        TerrainRegionOperation();
        virtual ~TerrainRegionOperation();

        //响应一次操作
        virtual void    execute( TerrainChunk* chunk, Ogre::Rect& rect );
        //回退一次操作
        virtual void    rollback();

        //影响障碍区域
        virtual void    influenceRegionMap(TerrainGroundSurface* tilesMgr, TerrainRegion* blockRegion, Int x, Int y) {};
    };

    /******************************************************************************/
    //游戏地形增加静障碍操作
    /******************************************************************************/
    class TerrainAddRegionOperation : public TerrainRegionOperation
    {
    public:
        TerrainAddRegionOperation();
        virtual ~TerrainAddRegionOperation();

        //影响障碍区域
        virtual void    influenceRegionMap(TerrainGroundSurface* tilesMgr, TerrainRegion* blockRegion, Int x, Int y) ;
    };

    /******************************************************************************/
    //游戏地形移除障碍操作
    /******************************************************************************/
    class TerrainRemoveRegionOperation : public TerrainRegionOperation
    {
    public:
        TerrainRemoveRegionOperation();
        virtual ~TerrainRemoveRegionOperation();

        //影响障碍区域
        virtual void    influenceRegionMap(TerrainGroundSurface* surface, TerrainRegion* region, Int x, Int y) ;
    };


}

/******************************************************************************/

#endif

