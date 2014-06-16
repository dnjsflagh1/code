/******************************************************************************/
#ifndef _TERRAINSBGROUNDTILES_H_
#define _TERRAINSBGROUNDTILES_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "TerrainTiles.h"
#include "TerrainTilesLayerBlendMap.h"
#include "TerrainTilesMaterial.h"
#include "TerrainTilesGpu.h"
#include "TerrainGroundTiles.h"

/******************************************************************************/
namespace MG
{
    //��������������������������������������������������������������������������������������������������
    //��������������������������������������������������������������������������������������������������

    /******************************************************************************/
    //С���εؿ��еĵ�����Ⱦ����
    /******************************************************************************/
    class TerrainSBGroundTileRender : public TerrainGroundTileRender
    {
    public:
        TerrainSBGroundTileRender( TerrainManager* mgr, TerrainChunk* chunk, TerrainNode* node, TerrainTile* tile, UInt index );
        virtual ~TerrainSBGroundTileRender();

    public:

        /// �õ�������ͼ������
        virtual UInt                    getMaxTextureLayerCount();

        // �����������ζ���
        virtual TerrainBatch*           createTerrainBatch( Scene* scene, TerrainTileRender* tileRender, TerrainBatch* parent, 
                                            const AxisAlignedBox& aabb, Ogre::Rect vertexRectInTile, MovableObject* movableObject);


        /*########################################
        //      ��ͼ��ӿ�
        #########################################*/

        /// ������ͼ��Դ
        virtual void                    generateTextureLayerResource() ;
        /// ������ͼ��Դ
        virtual void                    generateTextureLayerResource(Int layerIndex) ;
        /// ж����ͼ��Դ
        virtual void                    unLoadTextureLayerResource();

        /*########################################
        //      ��ͼ�����
        #########################################*/

        /// �������3����ͼ
        virtual void                    generateTextureList();
        /// �������3����ͼ
        virtual void                    generateTextureList(TextureLayerInstance* instance);
        /// �ͷ���ͼ��
        void                            destroyTextureList();

        /// �õ���������ͼ�������б�
        const StringVector&             getValidDiffuseSpecularTextureNameList();
        /// �õ�������ͼ�������б�
        const StringVector&             getValidNormalHeightTextureNameList();

        /*########################################
        //      ���ʹ���
        #########################################*/

    public:

        /// Ӧ����ʾ�����޸�
        virtual void                    applyRenderConfig();

      
    //#############################################################################################
    //#############################################################################################

    private:

        std::map<UInt,Str>  mDiffuseTextureNameMap;
        std::map<UInt,Str>  mNormalTextureNameMap;

        StringVector        mDiffuseTextureNameList;
        StringVector        mNormalTextureNameList;

    };

}

/******************************************************************************/

#endif
