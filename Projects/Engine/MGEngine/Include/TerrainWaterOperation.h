/******************************************************************************/
#ifndef _TERRAINWATEROPERATION_H_
#define _TERRAINWATEROPERATION_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "EditorOperation.h"
#include "ITerrain.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    //游戏水操作
    /******************************************************************************/
    class TerrainWaterOperation : public EditorOperation
    {
    public:
        TerrainWaterOperation();
        virtual ~TerrainWaterOperation();

        //响应一次操作
        virtual void    execute( TerrainChunk* chunk, Ogre::Rect& worldRect );
        //回退一次操作
        virtual void    rollback();


        //影响批次对象
        virtual void    influenceBatch( TerrainWaterSurface* surface, TerrainWaterBatch* batch ) {};
    };



    /******************************************************************************/
    //游戏水显示
    /******************************************************************************/
    class TerrainWaterShowOperation : public TerrainWaterOperation
    {
    public:
        TerrainWaterShowOperation();
        virtual ~TerrainWaterShowOperation();

        //影响批次对象
        virtual void    influenceBatch( TerrainWaterSurface* surface, TerrainWaterBatch* batch );

    };

    /******************************************************************************/
    //游戏水隐藏
    /******************************************************************************/
    class TerrainWaterHideOperation : public TerrainWaterOperation
    {
    public:
        TerrainWaterHideOperation();
        virtual ~TerrainWaterHideOperation();

        //影响批次对象
        virtual void    influenceBatch( TerrainWaterSurface* surface, TerrainWaterBatch* batch );

    };

    
}

/******************************************************************************/

#endif

