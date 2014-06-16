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
    //×××××××××××××××××××××××××××××××××××××××××××××××××
    //×××××××××××××××××××××××××××××××××××××××××××××××××

    /******************************************************************************/
    //小批次地块中的单次渲染区域
    /******************************************************************************/
    class TerrainSBGroundTileRender : public TerrainGroundTileRender
    {
    public:
        TerrainSBGroundTileRender( TerrainManager* mgr, TerrainChunk* chunk, TerrainNode* node, TerrainTile* tile, UInt index );
        virtual ~TerrainSBGroundTileRender();

    public:

        /// 得到最大的贴图层数量
        virtual UInt                    getMaxTextureLayerCount();

        // 创建地形批次对象
        virtual TerrainBatch*           createTerrainBatch( Scene* scene, TerrainTileRender* tileRender, TerrainBatch* parent, 
                                            const AxisAlignedBox& aabb, Ogre::Rect vertexRectInTile, MovableObject* movableObject);


        /*########################################
        //      贴图层接口
        #########################################*/

        /// 生成贴图资源
        virtual void                    generateTextureLayerResource() ;
        /// 生成贴图资源
        virtual void                    generateTextureLayerResource(Int layerIndex) ;
        /// 卸载贴图资源
        virtual void                    unLoadTextureLayerResource();

        /*########################################
        //      贴图层操作
        #########################################*/

        /// 生成最多3张贴图
        virtual void                    generateTextureList();
        /// 生成最多3张贴图
        virtual void                    generateTextureList(TextureLayerInstance* instance);
        /// 释放贴图集
        void                            destroyTextureList();

        /// 得到满反射贴图集名字列表
        const StringVector&             getValidDiffuseSpecularTextureNameList();
        /// 得到法线贴图集名字列表
        const StringVector&             getValidNormalHeightTextureNameList();

        /*########################################
        //      材质管理
        #########################################*/

    public:

        /// 应用显示参数修改
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
