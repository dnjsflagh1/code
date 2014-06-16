/******************************************************************************/
#ifndef _TERRAINSURFACEMANAGER_H_
#define _TERRAINSURFACEMANAGER_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "ITerrain.h"
#include "TerrainTilesGpu.h"


/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    /** 地形贴图层
    /******************************************************************************/
    struct GlobleTerrainTextureLayer
    {
        Bool usedDirty;
        TerrainTextureLayerDeclaration* decl;
        GlobleTerrainTextureLayer()
            :usedDirty(true)
            ,decl(NULL)
        {
            
        }
    };

    /******************************************************************************/
    /** 游戏地貌地块渲染管理
    // TerrainSurfaceManager
    /******************************************************************************/
    class TerrainSurfaceManager : public ITerrainSurfaceManager
    {
    public:
        TerrainSurfaceManager(TerrainManager* mgr, Scene* scene);
        virtual ~TerrainSurfaceManager();


        //////////////////////////////////////////////////
        void                                update( Flt delta );
        //////////////////////////////////////////////////
       
        /// 全局贴图声明
        void                                clearGlobleTextureLayer();
        void                                addGlobleTextureLayer(Int index, Str name);
        void                                addGlobleTextureLayer(Str name);
        Bool                                hasGlobleTextureLayer(Str name);
        Int                                 getGlobleTextureLayerMaxCount();
        TerrainTextureLayerDeclaration*     getGlobleTextureLayer( Int index );
        void                                clearGlobleTextureLayerUsedDirty();                        
        void                                cleanNoUsedGlobleTextureLayer();  
        
        // 创建地形表面
        TerrainBBGroundSurface*             createTerrainBBGroundSurface(TerrainChunk* chunk);
        // 创建地形表面
        TerrainSBGroundSurface*             createTerrainSBGroundSurface(TerrainChunk* chunk);

        // 删除地形表面
        void                                destroyTerrainGroundSurface(TerrainGroundSurface* surface);

        // 创建水表面
        TerrainWaterSurface*                createTerrainWaterSurface(TerrainChunk* chunk);
        // 删除地形表面
        void                                destroyTerrainWaterSurface(TerrainWaterSurface* surface);


        // 得到GPU索引分配
        DefaultTerrainTilesGpuBufferAllocator&
            getDefaultTerrainTilesGpuBufferAllocator(){return mCustomGpuBufferAllocator;};

        ///////////////////////////////////////////////////////////////////////////////////////////////

        Int                                 getGlobleWaterGroupMaxCount();
        TerrainWaterGroupDeclaration*       getGlobleWaterGroupByIndex( UInt index );
        TerrainWaterGroupDeclaration*       getGlobleWaterGroup( U32 groupID );
        TerrainWaterGroupDeclaration*       addGlobleWaterGroup( U32 groupID );
        void                                clearGlobleWaterGroups();  

        // 得到Water GPU索引分配
        TerrainWaterMaterial*               getTerrainWaterMaterial(){return mTerrainWaterMaterial;};
        
    private:

        /// 所属地形组对象.
        TerrainManager* mOwner;
        /// 所属场景对象.
        Scene* mScene;

        /// 地形贴图列表
        std::map<Int, GlobleTerrainTextureLayer> mGlobleTerrainTextureLayerList;

        /// 地形水列表
        std::map<Int, TerrainWaterGroupDeclaration> mGlobleTerrainWaterGroupList;

        ///Gpu缓存分配
        DefaultTerrainTilesGpuBufferAllocator mCustomGpuBufferAllocator;

        TerrainWaterMaterial*    mTerrainWaterMaterial;
    };

}

/******************************************************************************/

#endif
