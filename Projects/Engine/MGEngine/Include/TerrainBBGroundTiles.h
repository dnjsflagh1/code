/******************************************************************************/
#ifndef _TERRAINBBGROUNDTILES_H_
#define _TERRAINBBGROUNDTILES_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "TerrainTiles.h"
#include "TerrainTilesLayerBlendMap.h"
#include "TerrainTilesMaterial.h"
#include "TerrainTilesGpu.h"
#include "TerrainGroundTiles.h"

#include "TerrainNode.h"

/******************************************************************************/
namespace MG
{
    //��������������������������������������������������������������������������������������������������
    //��������������������������������������������������������������������������������������������������

    /******************************************************************************/
    //�����εؿ��еĵ�����Ⱦ����
    /******************************************************************************/
    class TerrainBBGroundTileRender : public TerrainGroundTileRender
    {
    public:
        TerrainBBGroundTileRender( TerrainManager* mgr, TerrainChunk* chunk, TerrainNode* node, TerrainTile* tile, UInt index );
        virtual ~TerrainBBGroundTileRender();

    public:

        /// �õ�������ͼ������
        virtual UInt                    getMaxTextureLayerCount();

        // �����������ζ���
        virtual TerrainBatch*           createTerrainBatch( Scene* scene, TerrainTileRender* tileRender, TerrainBatch* parent, 
                                            const AxisAlignedBox& aabb, Ogre::Rect vertexRectInTile, MovableObject* movableObject);
        
        /*########################################
        //      ��ͼ�����
        #########################################*/

        /// ������ͼ��Դ
        virtual void                    generateTextureLayerResource() ;
        /// ������ͼ��Դ
        virtual void                    generateTextureLayerResource(Int layerIndex) ;
        /// ж����ͼ��Դ
        virtual void                    unLoadTextureLayerResource();


        /*########################################
        //      ��ͼ������          
        #########################################*/

    public:

        /// ������ͼ�������б�
        void                            generateTextureAtlasNameList();

        /// �������2����ͼ����ÿ�����֧��4������
        virtual void                    generateTextureAtlasList();
        /// �������2����ͼ����ÿ�����֧��4������
        virtual void                    generateTextureAtlasList(TextureLayerInstance* instance);

        /// �ͷ���ͼ��
        void                            destroyAllTextureAtlas();
        /// �õ���������ͼ�������б�
        const StringVector&             getValidDiffuseSpecularTextureAtlasNameList();
        /// �õ�������ͼ�������б�
        const StringVector&             getValidNormalHeightTextureAtlasNameList();

        // �õ���ʽ
        static PixelFormat              getColorTexturFormat();
        // �õ���ʽ
        static Int                      getColorTexturMipMapNum();

    protected:

        /// �ڲ��ϲ�������ͼ����Texture Atlas
        Int                             addDiffuseSpecularTextureToSet(Int selfIndex,String textureName,Vec2& texSetPos,Vec2& texSetSize);
        Int                             addNormalHeightTextureToSet(Int selfIndex,String textureName,Vec2& texSetPos,Vec2& texSetSize);
        void                            copyTextureToSet(Int selfIndex, Ogre::Image& img, TexturePtr& texSet, Vec2& texSetPos, Vec2& texSetSize, Int type);
        TexturePtr                      createOrRetriveTextureToSet( String texSetName, PixelFormat format, Vec4 defaultColor );


        /*########################################
        //      ���ʹ���
        #########################################*/

    public:

        /// Ӧ����ʾ�����޸�
        virtual void                    applyRenderConfig();






    //#############################################################################################
    //#############################################################################################
    private:

        // ��ɫ�����б�
        StringVector        mDiffuseTextureAtlasNameList;
        StringVector        mNormalTextureAtlasNameList;
        StringVector        mValidDiffuseTextureAtlasNameList;
        StringVector        mValidNormalTextureAtlasNameList;

        TexturePtrList      mDiffuseTextureAtlasList;
        TexturePtrList      mNormalTextureAtlasList;

        static PixelFormat  mColorPixelFormat;
        static Int          mColorTexturMipMapNum;

    };

}

/******************************************************************************/

#endif
