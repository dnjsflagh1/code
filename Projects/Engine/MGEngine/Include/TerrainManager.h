/******************************************************************************/
#ifndef _TERRAINMANAGER_H_
#define _TERRAINMANAGER_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "ITerrain.h"
#include "TerrainRegionManager.h"
#include "TerrainSurfaceManager.h"
#include "TerrainChunk.h"

/******************************************************************************/
namespace MG
{

    #define TERRAIN_MAX_TEXTURE  16
    #define TERRAIN_MAX_DETAIL_TEXTURE_LAYER  8

    /******************************************************************************/
    /**游戏地形管理器
        @remarks
            负责描述地形统一配置。
            负责管理所有的地形块。

        @remarks:
            地形Movable挂接到地形根节点SceneNode
            SceneNode会在每帧访问挂接的Movable中是否有需要渲染的对象到渲染队列中RenderQueue中。
            TerrainManager会分派这些访问事件到各个模块，比如地貌，水，植被等对象。
    */
    /******************************************************************************/

    class TerrainManager : public ITerrainManager
    {
    public:
		enum
		{
			TERRAIN_MTL_NORMAL,
			TERRAIN_MTL_REFLECTION,
			TERRAIN_MTL_REFRACTION,

			TERRAIN_MTL_NR,
		};
        TerrainManager(Scene* scene);
        virtual ~TerrainManager();

        /// 更新地形组
        virtual Bool                    update( Flt delta );
        
        /// 加载地形数据
        virtual void                    load(Str path);
        /// 保存地形数据
        virtual void                    save(Str path);
        /// 清空地形数据
        virtual void                    unLoad();
        /// 当设备重置
        void                            reset();
		/// 裁剪地形数据
		virtual void                    clip(Str path, RectF rect);

		/// 重排序并保存地形贴图层数据
		virtual void                    _reorderTextureLayer(Str& path);


        /// 应用渲染选项
        void                            applyRenderConfig();


        ////////////////////////////////////////////////////////////////////////////////////

        /// 最大的高度
        static Flt MaxHeight;
        
        // 得到场景
        Scene*                          getScene(){ return mScene; };

        /// 得到节点对象
        virtual ISceneNode*             getSceneNode() { return NULL; };

        /// 设置和获取地形中心位置
        void                            setCenterPosition(Vec3 pos){ mCenterPos = pos; };
        Vec3                            getCenterPosition(){ return mCenterPos; };

        /// 创建配置
        virtual void                    setConfig( TerrainDeclare& declare ){ mTerrainDeclare = declare; };
        /// 得到配置
        virtual TerrainDeclare&         getConfig(){ return mTerrainDeclare; };


        /// 得到区域管理对象
        TerrainRegionManager*           getTerrainRegionManager(){ return mRegionMgr; };
        /// 得到地表管理对象
        TerrainSurfaceManager*          getTerrainSurfaceManager(){ return mSurfaceMgr; };

        ////////////////////////////////////////////////////////////////////////////////////


        /// 创建地快
        virtual TerrainChunk*           createTerrainChunk( I8 x, I8 y, TerrainChunkDeclare& decl );
        /// 得到地快
        virtual TerrainChunk*           getTerrainChunk( I8 x, I8 y );
        /// 销毁地快
        virtual void                    destroyAllTerrainChunk();
        /// 得到地块编号
                U32                     getTerrainChunkUID( I8 x, I8 y );

        /// 加载地块
                void                    loadTerrainChunk(Str path);
        /// 保存地块
                void                    saveTerrainChunk(Str path);
        /// 卸载地块
                void                    unLoadTerrainChunk();
        /// 更新地块
                void                    updateTerrainChunk( Flt delta );

        /// 得到地快数量
        virtual UInt                    getTerrainChunkCount();
        /// 得到地快通过索引
        virtual TerrainChunk*           getTerrainChunkByIndex(UInt index);
        /// 得到地快
        virtual TerrainChunk*           getTerrainChunkByWorldPos( Vec2 worldPos ) ;

        /// 得到地块大小
        Flt                             getTerrainChunkSize(){ return mChunkSize; };
        Flt                             getTerrainChunkHalfSize(){ return mChunkHalfSize; };

        ////////////////////////////////////////////////////////////////////////////////////

        /// 得到鼠标射线查询结果
        virtual Bool                    getMouseRayIntersection(Vec3& intersectPos,Bool isPrecise = false);
        /// 得到射线交点
        virtual Bool                    getRayIntersection(Vec3& pos, Vec3& dir, Vec3& intersectPos,Bool isPrecise = false);
        /// 得到高度
        virtual Bool                    getStickHeight( Vec2 worldPos , Flt& height );


        ////////////////////////////////////////////////////////////////////////////////////
		Int								getTerrainWidth();
		Int								getTerrainHeight();

		Flt								getTerrainChunkBlockGridSize();

		////////////////////////////////////////////////////////////////////////////////////

    private:

        /// 场景对象
        Scene* mScene;

        /// 地形中心位置
        Vec3 mCenterPos;
        Vec3 mIndexCenterPos;
        /// 地块大小
        Flt mChunkSize;
        /// 地块一般大小
        Flt mChunkHalfSize;
        /// 声明
        TerrainDeclare mTerrainDeclare;

        ///////////////////////////////////////////////////////////////////////////////

        /// 地表管理
        TerrainSurfaceManager* mSurfaceMgr;
        /// 区域管理
        TerrainRegionManager* mRegionMgr;

        ///////////////////////////////////////////////////////////////////////////////

        std::map<U32 ,TerrainChunk*> mTerrainChunks;
        Vec2                         mMaxTerrainChunkRect;

        ///////////////////////////////////////////////////////////////////////////////

		Int							 mTerrainWidth; 
		Int							 mTerrainHeight;

		Flt							 mTerrainChunkBlockGridSize;

		MaterialPtr					 mTerrainMtls[TERRAIN_MTL_NR];
    };

}

/******************************************************************************/

#endif
