/******************************************************************************/
#ifndef _ITERRAIN_H_
#define _ITERRAIN_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"
#include "ISceneObject.h"
#include "IResourceManager.h"

/******************************************************************************/

namespace MG
{
   
    //××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××
    //××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××

    /********************************************************/
    //地形声明
    /********************************************************/
    enum TerrainGroundMaterialType
    {
        TMS_BIG = 0,
        TMS_SMALL
    };


    /********************************************************/
    //地形声明
    /********************************************************/
    struct TerrainChunkDeclare
    {
		Int							gridSideNumInNode;				/// 地形节点一边网格数量
        Int							gridSideNumInTile;              /// 地形分块一边网格数量
        Int							blendMapSizeInTile;             /// 混合贴图映射大小


        TerrainChunkDeclare()
        {
            reset();
        }

        void reset()
        {
			gridSideNumInNode		= 512;
            gridSideNumInTile       = 512;
            blendMapSizeInTile      = gridSideNumInTile;
        }
    };

	struct TerrainDeclare
	{
		Int							gridSideNumInChunk;             /// 地形格一边的数量在一个Chunk里面
		Int							gridSideNumInBatch;             /// 渲染格一边的格子数量
		Flt							gridSize;                       /// 地形格大小
		Int							lightingMapSize;                /// 光影贴图映射大小			

		Flt							heightScale;
		Flt							minHeight;
		Flt							maxHeight;

		TerrainGroundMaterialType	groundMatType; /// 地形表面材质类型

		std::vector<VecI2>			trunkIndexList;		/// thunk索引列表

		TerrainChunkDeclare         chunkDecl;

		TerrainDeclare()
		{
			reset();
		}

		void reset()
		{
			gridSideNumInChunk      = 1024;
			gridSideNumInBatch      = 128;
			gridSize                = 1;
			lightingMapSize         = 1024;

			heightScale             = 20;
			minHeight               = 0;
			maxHeight               = 100;

			groundMatType           = TMS_BIG;

			chunkDecl				= TerrainChunkDeclare();

			trunkIndexList.clear();
			trunkIndexList.push_back(VecI2(1,1));
		}
	};




    //××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××
    //××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××

    enum TerrainSurfaceType
    {
        TST_NULL,
        TST_GROUND,
        TST_WATER
    };

    /********************************************************/
    //游戏地块网格显示
    /********************************************************/
    class ITerrainGroundSurface
    {
    };
    class ITerrainWaterSurface
    {
    };


    struct TerrainWaterGroupDeclaration
    {
        UInt        groupID;
        U32         wMatID;
        //MaterialDeclaration* matDecl;
        Vec3        reflectPostion;
        Vec3        reflectDirection;
        TerrainWaterGroupDeclaration()
            :reflectPostion(0,0,0)
            ,reflectDirection(0,-1,0)
        {

        }
    };


    class ITerrainSurfaceManager
    {
    public:
        virtual Int                                 getGlobleTextureLayerMaxCount() = 0;
        virtual TerrainTextureLayerDeclaration*     getGlobleTextureLayer( Int index ) = 0;
        virtual void                                addGlobleTextureLayer(Str name) = 0;
        
        virtual Int                                 getGlobleWaterGroupMaxCount() = 0;
        virtual TerrainWaterGroupDeclaration*       getGlobleWaterGroupByIndex( UInt index ) = 0;
        virtual TerrainWaterGroupDeclaration*       getGlobleWaterGroup( U32 groupID ) = 0;
        virtual TerrainWaterGroupDeclaration*       addGlobleWaterGroup( U32 groupID ) = 0;
    };
    

    /********************************************************/
    //游戏自定义区域
    /********************************************************/
    struct CustomRegionDeclaration
    {
        Str  name;
        Bool visible;
    };
    class ITerrainChunkRegions
    {
    public:

    };
    class ITerrainRegionManager
    {
    public:

        // 设置障碍网格可见性
        virtual void                            setBlockRegionVisible(Bool visible) = 0;
        // 设置自定义网格可见性
        virtual void                            setCustomRegionVisible( Int index, Bool visible ) = 0;
        // 应用网格可见性
        virtual void                            applyRegionVisible() = 0;

        // 增加和得到自定义区域
        virtual void                            clearCustomRegion() = 0;
        virtual void                            addCustomRegion() = 0;
        virtual void                            removeCustomRegion( Int index ) = 0;
        virtual Int                             getCustomRegionCount() = 0;
        virtual CustomRegionDeclaration*        getCustomRegionDeclaration( UInt index ) = 0;
    };


    //××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××
    //××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××

    /********************************************************/
    //游戏地形主接口
    /********************************************************/
    class ITerrainChunk
    {
    public:
        /// 得到地表显示对象
        virtual ITerrainGroundSurface*          getTerrainGroundSurface() = 0;
        /// 得到地表显示对象
        virtual ITerrainChunkRegions*           getTerrainRegion() = 0;

        // 得到Chunk定义
        virtual const TerrainChunkDeclare&      getTerrainChunkConfig() = 0;
    };

   
	/********************************************************/
	//地形管理
	/********************************************************/
	class ITerrainManager //: public ISceneObject
	{
	public:

        /// 创建配置
        virtual void                            setConfig( TerrainDeclare& declare ) = 0;
        /// 得到配置
        virtual TerrainDeclare&                 getConfig() = 0;

        //////////////////////////////////////////////////////////////////////////////////////////////////

        /// 创建地快
        virtual ITerrainChunk*                  createTerrainChunk( I8 x, I8 y, TerrainChunkDeclare& decl ) = 0;
        /// 得到地快
        virtual ITerrainChunk*                  getTerrainChunk( I8 x, I8 y ) = 0;
        /// 销毁地快
        virtual void                            destroyAllTerrainChunk() = 0;

        /// 得到地快数量
        virtual UInt                            getTerrainChunkCount() = 0;
        /// 得到地快通过索引
        virtual ITerrainChunk*                  getTerrainChunkByIndex(UInt index) = 0;
        /// 得到地快
        virtual ITerrainChunk*                  getTerrainChunkByWorldPos( Vec2 worldPos ) = 0;

        //////////////////////////////////////////////////////////////////////////////////////////////////

        /// 加载地形数据 
        virtual void                            load(Str path) = 0;
        /// 保存地形数据
        virtual void                            save(Str path) = 0;
        /// 清除地形数据 
        virtual void                            unLoad() = 0;
		/// 裁剪地形数据
		virtual void                            clip(Str path, RectF clipRect) = 0;
		/// 重排序并保存地形贴图层数据
		virtual void							_reorderTextureLayer(Str& path) = 0;

        //////////////////////////////////////////////////////////////////////////////////////////////////

        /// 得到区域管理对象
        virtual ITerrainRegionManager*          getTerrainRegionManager() = 0;
        /// 得到地表管理对象
        virtual ITerrainSurfaceManager*         getTerrainSurfaceManager() = 0;

        //////////////////////////////////////////////////////////////////////////////////////////////////

        /// 得到鼠标射线交点
        virtual Bool                            getMouseRayIntersection(Vec3& intersectPos,Bool isPrecise = false) = 0;
        /// 得到射线交点
        virtual Bool                            getRayIntersection(Vec3& pos, Vec3& dir, Vec3& intersectPos,Bool isPrecise = false) = 0;
        /// 得到高度
        virtual Bool                            getStickHeight( Vec2 worldPos , Flt& height ) = 0;

		///
		virtual Int								getTerrainWidth() = 0;
		
		///
		virtual Int								getTerrainHeight() = 0;

		/// 设置和获取地形中心位置
		virtual void							setCenterPosition(Vec3 pos) = 0;
		virtual Vec3							getCenterPosition() = 0;
    };

}

/******************************************************************************/
#endif
