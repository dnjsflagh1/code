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
    //×××××××××××××××××××××××××××××××××××××××××××××××××
    //×××××××××××××××××××××××××××××××××××××××××××××××××

    /******************************************************************************/
    //大批次地块中的单次渲染区域
    /******************************************************************************/
    class TerrainBBGroundTileRender : public TerrainGroundTileRender
    {
    public:
        TerrainBBGroundTileRender( TerrainManager* mgr, TerrainChunk* chunk, TerrainNode* node, TerrainTile* tile, UInt index );
        virtual ~TerrainBBGroundTileRender();

    public:

        /// 得到最大的贴图层数量
        virtual UInt                    getMaxTextureLayerCount();

        // 创建地形批次对象
        virtual TerrainBatch*           createTerrainBatch( Scene* scene, TerrainTileRender* tileRender, TerrainBatch* parent, 
                                            const AxisAlignedBox& aabb, Ogre::Rect vertexRectInTile, MovableObject* movableObject);
        
        /*########################################
        //      贴图层操作
        #########################################*/

        /// 生成贴图资源
        virtual void                    generateTextureLayerResource() ;
        /// 生成贴图资源
        virtual void                    generateTextureLayerResource(Int layerIndex) ;
        /// 卸载贴图资源
        virtual void                    unLoadTextureLayerResource();


        /*########################################
        //      贴图集操作          
        #########################################*/

    public:

        /// 生成贴图集名字列表。
        void                            generateTextureAtlasNameList();

        /// 生成最多2张贴图集，每张最多支持4种纹理。
        virtual void                    generateTextureAtlasList();
        /// 生成最多2张贴图集，每张最多支持4种纹理。
        virtual void                    generateTextureAtlasList(TextureLayerInstance* instance);

        /// 释放贴图集
        void                            destroyAllTextureAtlas();
        /// 得到满反射贴图集名字列表
        const StringVector&             getValidDiffuseSpecularTextureAtlasNameList();
        /// 得到法线贴图集名字列表
        const StringVector&             getValidNormalHeightTextureAtlasNameList();

        // 得到格式
        static PixelFormat              getColorTexturFormat();
        // 得到格式
        static Int                      getColorTexturMipMapNum();

    protected:

        /// 内部合并生成贴图集合Texture Atlas
        Int                             addDiffuseSpecularTextureToSet(Int selfIndex,String textureName,Vec2& texSetPos,Vec2& texSetSize);
        Int                             addNormalHeightTextureToSet(Int selfIndex,String textureName,Vec2& texSetPos,Vec2& texSetSize);
        void                            copyTextureToSet(Int selfIndex, Ogre::Image& img, TexturePtr& texSet, Vec2& texSetPos, Vec2& texSetSize, Int type);
        TexturePtr                      createOrRetriveTextureToSet( String texSetName, PixelFormat format, Vec4 defaultColor );


        /*########################################
        //      材质管理
        #########################################*/

    public:

        /// 应用显示参数修改
        virtual void                    applyRenderConfig();






    //#############################################################################################
    //#############################################################################################
    private:

        // 颜色纹理集列表
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
