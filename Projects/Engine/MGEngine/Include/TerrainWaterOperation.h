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
    //��Ϸˮ����
    /******************************************************************************/
    class TerrainWaterOperation : public EditorOperation
    {
    public:
        TerrainWaterOperation();
        virtual ~TerrainWaterOperation();

        //��Ӧһ�β���
        virtual void    execute( TerrainChunk* chunk, Ogre::Rect& worldRect );
        //����һ�β���
        virtual void    rollback();


        //Ӱ�����ζ���
        virtual void    influenceBatch( TerrainWaterSurface* surface, TerrainWaterBatch* batch ) {};
    };



    /******************************************************************************/
    //��Ϸˮ��ʾ
    /******************************************************************************/
    class TerrainWaterShowOperation : public TerrainWaterOperation
    {
    public:
        TerrainWaterShowOperation();
        virtual ~TerrainWaterShowOperation();

        //Ӱ�����ζ���
        virtual void    influenceBatch( TerrainWaterSurface* surface, TerrainWaterBatch* batch );

    };

    /******************************************************************************/
    //��Ϸˮ����
    /******************************************************************************/
    class TerrainWaterHideOperation : public TerrainWaterOperation
    {
    public:
        TerrainWaterHideOperation();
        virtual ~TerrainWaterHideOperation();

        //Ӱ�����ζ���
        virtual void    influenceBatch( TerrainWaterSurface* surface, TerrainWaterBatch* batch );

    };

    
}

/******************************************************************************/

#endif

