/******************************************************************************/
#ifndef _TERRAINWATERTILES_H_
#define _TERRAINWATERTILES_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "TerrainTiles.h"


/******************************************************************************/
namespace MG
{
    //��������������������������������������������������������������������������������������������������
    //��������������������������������������������������������������������������������������������������

    /******************************************************************************/
    //�ؿ��еĵ�����Ⱦ����
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

        // �����������ζ���
        virtual TerrainBatch*           createTerrainBatch( Scene* scene, TerrainTileRender* tileRender, TerrainBatch* parent, 
                                            const AxisAlignedBox& aabb, Ogre::Rect vertexRectInTile, MovableObject* movableObject);


        /*########################################
        //      ���ʹ���
        #########################################*/

    public:

        /// Ӧ����ʾ�����޸�
        virtual void                    applyRenderConfig();
    };



}

/******************************************************************************/

#endif
