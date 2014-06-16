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

    //��������������������������������������������������������������������������������������������������
    //��������������������������������������������������������������������������������������������������


    /******************************************************************************/
    /*
    @remarks:
    ÿ����ͼ��Ӧһ��TerrainTilesLayerBlendMap����
    ÿ�Ĳ���ͼ(�Լ�TerrainTilesLayerBlendMap)ͨ��һ�ŵ�ɫ����ͼ(BlendTexture)��ϡ�
    */
    /******************************************************************************/
    class TerrainBBGroundSurface :  public TerrainGroundSurface
    {
    public:
        TerrainBBGroundSurface(TerrainManager* terrainMgr, Scene* scene, TerrainChunk* chunk);
        virtual ~TerrainBBGroundSurface();

    public:

        // �����ֿ���Ⱦ��
        virtual TerrainTileRender*  createTerrainTileRender( TerrainManager* mgr, TerrainChunk* chunk, 
            TerrainNode* node, TerrainTile* tile, UInt index );

        /*########################################
        //          ��ͼ��ͻ�ϲ����         
        #########################################*/

        virtual void                loadBlendLayerMap( Str& path );
        virtual void                unLoadBlendLayerMap();
        virtual void                saveBlendLayerMap( Str& path );

		//��������BlendMapTex��ͼ��(�˺����������Զ��ü���ͼǰ��������blendMap)
		virtual void                _reorderBlendLayerMap( const Str& path );

    private:


    };

}

/******************************************************************************/

#endif
