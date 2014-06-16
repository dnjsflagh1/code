/******************************************************************************/
#ifndef _TERRAINSBGROUNDSURFACE_H_
#define _TERRAINSBGROUNDSURFACE_H_
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
    class TerrainSBGroundSurface : public TerrainGroundSurface
    {
    public:
        TerrainSBGroundSurface(TerrainManager* terrainMgr, Scene* scene, TerrainChunk* chunk);
        virtual ~TerrainSBGroundSurface();

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

        // ���ػ����ͼ
        void                        loadBlendTextures( Str& path );
        //  ɾ�������ͼ
        void                        destroyAllBlendTexture();
        /// �õ������ͼ�����б�
        const StringVector&         getValidBlendTextureNameList();


    private:

        //################# �����ͼ���� ###############

        StringVector    mBlendTextureNameList;
        StringVector    mValidBlendTextureNameList;
        TexturePtrList  mBlendTextureList;

    };

}

/******************************************************************************/

#endif
