/******************************************************************************/
#ifndef _TERRAINSURFACE_H_
#define _TERRAINSURFACE_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "ITerrain.h"
#include "MGGrid.h"
#include "TerrainTiles.h"
#include "ManualMeshManager.h"
#include "TerrainNode.h"

/******************************************************************************/
namespace MG
{
  
    //×××××××××××××××××××××××××××××××××××××××××××××××××
    //×××××××××××××××××××××××××××××××××××××××××××××××××


    /******************************************************************************/
    /** 游戏地貌地块渲染管理
    @remarks:
    World space align is X_Z; Y is height.
    -Z
    ||||  
    -X---0---X
    |  
    Z

    @remarks:
    Terrain space: 单位为比例 (0,0)-(1,1)
    (0,0) is the bottom-left of the terrain, and (1,1) is the top-right.

    方向 X_Y 重合于 World space X_-Z.

    where x/y represents the terrain plane and z represents the up vector

    Y
    |
    0---X

    @remarks:
    VertexPoint space : 单位为顶点
    UV space : 单位为像素比例 (0,0)-(1,1)
    方向X_Y, 重合于 World space X_-Z.
    Y
    |
    0---X

    @remarks:
    每层贴图对应一个TerrainTilesLayerBlendMap对象。
    每四层贴图(以及TerrainTilesLayerBlendMap)通过一张调色板贴图(BlendTexture)混合。
    */
    /******************************************************************************/
    class TerrainSurface : public GridManager<TerrainNodeGrid>
    {
		friend class TerrainNode;
		friend class TerrainTileRender;
		friend class TerrainBatch;
    public:
        TerrainSurface(TerrainManager* terrainMgr, Scene* scene, TerrainChunk* chunk);
        virtual ~TerrainSurface();

        enum TerrainSurfaceSpace
        {
            /// Simple global world space, axes and positions are all in world space
            WORLD_SPACE = 0, 
            /// As world space, but positions are relative to the terrain world position
            LOCAL_SPACE = 1, 
            /** x & y are parametric values on the terrain from 0 to 1, with the
            origin at the bottom left. z is the world space height at that point.
            */
            TERRAIN_SPACE = 2,
            /** x & y are integer points on the terrain from 0 to size-1, with the
            origin at the bottom left. z is the world space height at that point.
            */
            POINT_SPACE = 3
        };


        //**********************************************************************************************************************
        //**********************************************************************************************************************

        /*########################################
        //                  主方法        
        #########################################*/

        virtual TerrainSurfaceType  getType() = 0;
        virtual SceneObjectTypes    getSceneObjectTypes() = 0;
        virtual UInt                getSceneVisibleFlags() = 0;
        // 得到渲染队列
        virtual uint8               getRenderQueueGroup() = 0;

        /// 配置选项
        virtual void                configOptions();
		/// 响应渲染配置
		virtual void                applyRenderConfig();


        /// 加载数据 
        virtual void                load( Str path );
        /// 卸载数据
        virtual void                unLoad();
        /// 设备重置
        virtual void                reset();
        /// 保存数据
        virtual void                save( Str path );
        /// 更新
        virtual void                update(Flt delta, bool synchronous = false);



        /// 创建栅格
        virtual void                createGrids(Int gridsSideNum, Flt gridSize,  Vec2 centerPos);
        /// 销毁栅格
        virtual void                destroyGrids();

        /// 加载网格数据
        virtual void                loadGridData();
        /// 卸载网格数据
        virtual void                unLoadGridData();
        /// 加载网格数据
        void                        updateGridData(Flt delta);

        /// 设置区域更新
        void                        dirtyRect(const Ogre::Rect& rect);
        /// 设置区域更新
        void                        dirtyRect(Int x, Int y);

        /// 得到渲染对象
        TerrainTile*                getTileGridDataByIndex( UInt x, UInt y );


		// 创建分块节点
		virtual TerrainNode*		createTerrainNode( TerrainManager* mgr, TerrainChunk* chunk, 
										TerrainNodeGrid* nodeGrid, UInt index );
		// 创建分块渲染者
		virtual TerrainTileRender*  createTerrainTileRender( TerrainManager* mgr, TerrainChunk* chunk, TerrainNode* node,
										TerrainTile* tile, UInt index ) = 0;
        
        //**********************************************************************************************************************
        //**********************************************************************************************************************


        /*########################################
        //               空间转换          
        #########################################*/

        /// 得到射线查询
        Bool                        getRayIntersection(Vec3& pos, Vec3& dir, Vec3& intersectPos,Bool isPrecise);
        Bool                        getRayIntersection2(Vec3& pos, Vec3& dir, Vec3& intersectPos,Bool isPrecise);

        Bool                        getRayIntersectionTri3DInGridByWorldPosition( Ogre::Ray& ray, Vector3& worldPos, Vec3& intersectPos );
        Bool                        getRayIntersectionTri3DInGridByVertexPoint( Ogre::Ray& ray, UInt x, UInt y, Vec3& intersectPos );

        /// Get the minimum height of the terrain
        Real                        getMinHeight() const;
        /// Get the maximum height of the terrain
        Real                        getMaxHeight() const;

        /// 得到高度指针数据通过索引
        Bool                        hasHeightData() const;
        /// 得到高度指针数据通过索引
        Flt*                        getHeightData(Int x, Int y) const;
        /// 得到高度数据通过索引点
        Flt                         getHeightAtPoint(Int x, Int y);
        /// 设置高度数据通过索引点
        void                        setHeightAtPoint(Int x, Int y, Flt h);

        /// 得到高度数据通过世界坐标点
        Flt                         getHeightAtWorldPosition(Real x, Real y);

        /// 得到地形的面片 // 面的坐标系需要注意
        Bool                        getTerrainTri3DByTerrainPosition(Flt x, Flt y, 
            Triangle3D& tri3D1, Triangle3D& tri3D2);
        /// 得到地形的面片 // 面的坐标系需要注意
        Bool                        getTerrainTri3DByVertexPoint(UInt x, UInt y, 
            Triangle3D& tri3D1, Triangle3D& tri3D2);

        /// 得到地形的面片 
        /*
        0    1
        *----*
        |    |  
        2    3
        *----*
        */
        void                        getTerrainPlaneByWorldPosition(Flt x, Flt y, 
            Vector3& p0, Vector3& p1, Vector3& p2, Vector3& p3);

        /** Get a Vector3 of the world-space point on the terrain, aligned as per
        options.
        @note This point is relative to Terrain::getPosition
        */
        void                        convertVertexPointToWorldPosition(long x, long y,  Vector3* outWSpos);
        /** Get a Vector3 of the world-space point on the terrain, supplying the
        height data manually (can be more optimal). 
        @note This point is relative to Terrain::getPosition
        */
        void                        convertVertexPointToWorldPosition(long x, long y,  Vector2* outWSpos);

        void                        convertVertexPointToWorldPosition(long x, long y, float height, Vector3* outWSpos);
        void                        convertVertexPointToWorldPosition(const Vector3& VSpos, Vector3* outWSpos);

        void                        convertWorldPositionToVertexPoint(const Vector3& WSpos, Vector3* outWSpos);

        /** Convert a position from world space to terrain basis space. 
        @param WSpos 
        World space position (setup according to current alignment). 
        @param outTSpos 
        Terrain space output position, where (0,0) is the bottom-left of the
        terrain, and (1,1) is the top-right. The Z coordinate is in absolute
        height units.
        */
        void                        convertWorldPositionToTerrainPosition(const Vector3& WSpos, Vector3* outTSpos);

        /** Convert a position from terrain basis space to world space based on a specified alignment. 
        @param TSpos 
        Terrain space position, where (0,0) is the bottom-left of the
        terrain, and (1,1) is the top-right. The Z coordinate is in absolute
        height units.
        @param 
        outWSpos World space output position (setup according to alignment). 
        */
        void                        convertTerrainPositionToWorldPosition(const Vector3& TSpos, Vector3* outTSpos);
        void                        convertTerrainPositionToWorldPosition(Real x, Real y, Real z, Vector3* outWSpos);


        /** Convert a position from one space to another with respect to this terrain.
        @param inSpace The space that inPos is expressed as
        @param inPos The incoming position
        @param outSpace The space which outPos should be expressed as
        @param outPos The output position to be populated
        */
        void                        convertPositionSpace(TerrainSurfaceSpace inSpace, const Vector3& inPos, TerrainSurfaceSpace outSpace, Vector3& outPos) const;
        /** Convert a position from one space to another with respect to this terrain.
        @param inSpace The space that inPos is expressed as
        @param inPos The incoming position
        @param outSpace The space which outPos should be expressed as
        @returns The output position 
        */
        Vector3                     convertPositionSpace(TerrainSurfaceSpace inSpace, const Vector3& inPos, TerrainSurfaceSpace outSpace) const;
        /** Convert a direction from one space to another with respect to this terrain.
        @param inSpace The space that inDir is expressed as
        @param inDir The incoming direction
        @param outSpace The space which outDir should be expressed as
        @param outDir The output direction to be populated
        */
        void                        convertDirectionSpace(TerrainSurfaceSpace inSpace, const Vector3& inDir, TerrainSurfaceSpace outSpace, Vector3& outDir) const;
        /** Convert a direction from one space to another with respect to this terrain.
        @param inSpace The space that inDir is expressed as
        @param inDir The incoming direction
        @param outSpace The space which outDir should be expressed as
        @returns The output direction 
        */
        Vector3                     convertDirectionSpace(TerrainSurfaceSpace inSpace, const Vector3& inDir, TerrainSurfaceSpace outSpace) const;

        void                        convertSpace(TerrainSurfaceSpace inSpace, const Vector3& inVec, TerrainSurfaceSpace outSpace, Vector3& outVec, bool translation) const;
        Vector3                     convertWorldToTerrainAxes(const Vector3& inVec) const;
        Vector3                     convertTerrainToWorldAxes(const Vector3& inVec) const;

        /// Utility method to convert axes from world space to terrain space (xy terrain, z up)
        static void                 convertWorldToTerrainAxes(const Vector3& worldVec, Vector3* terrainVec);
        /// Utility method to convert axes from terrain space (xy terrain, z up) tp world space
        static void                 convertTerrainToWorldAxes(const Vector3& terrainVec, Vector3* worldVec);


        /** Widen a rectangular area of terrain to take into account an extrusion vector.
        @param vec A vector in world space
        @param inRect Input rectangle
        @param inRect Output rectangle
        */
        void                        widenRectByVector(const Vector3& vec, const Rect& inRect, Rect& outRect);

        /** Widen a rectangular area of terrain to take into account an extrusion vector, 
        but specify the min / max heights to extrude manually.
        @param vec A vector in world space
        @param inRect Input rectangle
        @param minHeight, maxHeight The extents of the height to extrude
        @param inRect Output rectangle
        */
        void                        widenRectByVector(const Vector3& vec, const Rect& inRect, 
            Real minHeight, Real maxHeight, Rect& outRect);


        //**********************************************************************************************************************
        //**********************************************************************************************************************


        /*########################################
        //               顶点和索引数据操作          
        #########################################*/

        /// 得到一边的顶点数量
        UInt                        getVertexSideNum()  const { return mVertexSideNum; }

        /// 得到Tile一边的顶点数量
        UInt                        getVertexSideNumInTile() const { return mVertexSideNumInTile; }

        /// 得到一边的顶点间隔大小
        Real                        getVertexOffset()  const { return mVertexOffset; }

        /// 得到Tile一边的数量在一个Chunk内
        UInt                        getTileSideNumInChunk() const { return mTileSideNumInChunk; }
        
        ///////////////////////////////////////////////////////////////////////////////

        /// 加载高度数据
        virtual void                loadHeightData( Str path ) = 0;
        /// 加载高度数据
        void                        loadHeightData( Str path, Str fileName );
        /// 释放高度数据
        void                        unLoadHeightData();

        /// 保存高度数据
        virtual void                saveHeightData( Str path ) = 0;
        /// 保存高度数据
        void                        saveHeightData( Str path, Str fileName );

        ///////////////////////////////////////////////////////////////////////////////

        /// 更新顶点
        void                        updateGeometry();
        /// 更新顶点
        virtual void                updateGeometry( Ogre::Rect rect ){};


    public:

        //**********************************************************************************************************************
        //**********************************************************************************************************************


        /*########################################
        //          法线层操作      
        #########################################*/

    public:

        /// 得到法线层数据通过索引
        Flt*                        getNormalDataByIndex(Int x, Int y) const;
        /// 得到切线层数据通过索引
        Flt*                        getTangentDataByIndex(Int x, Int y) const;

        /// 得到法线层数据一个单位像素数量
        UInt                        getNTOnePixelNum() {return mNTOnePixelNum;};

    protected:

        /// 加载法线层数据
        virtual void                loadNormalTangentMapData( Str path ) = 0;
        /// 加载法线层数据
        void                        loadNormalTangentMapData( Str path, Str normalFilename, Str tangentFileName );
        /// 卸载法线层数据
        void                        unLoadNormalTangentMapData();

        /// 保存法线层数据
        virtual void                saveNormalTangentMapData( Str path ) = 0;
        /// 保存法线层数据
        void                        saveNormalTangentMapData( Str path, Str normalFilename, Str tangentFileName );

        /// 刷新法线数据
        void                        refreshNormalTangent(const Rect& rect);

    private:

        /// 加载数据
        Bool                        loadNTMapData( Str path, Str filename, Flt*&date );
        ///  保存数据
        Bool                        saveNTMapData( Str path, Str filename, Flt*&date );

//**********************************************************************************************************************
//**********************************************************************************************************************


        /*########################################
        //          颜色层操作      
        #########################################*/

    public:

        /// 得到颜色层数据通过索引
        U8*                         getColorDataByIndex(Int x, Int y) const;

        /// 得到颜色层数据一个单位像素数量
        UInt                        getColorOnePixelNum() {return mColorOnePixelNum;};

    protected:

        /// 加载颜色层数据
        virtual void                loadColorMapData( Str path ) = 0;
        /// 加载颜色层数据
        void                        loadColorMapData( Str path, Str filename );
        /// 卸载颜色层数据
        void                        unLoadColorMapData();

        /// 保存颜色层数据
        virtual void                saveColorMapData( Str path ) = 0;
        /// 保存颜色层数据
        void                        saveColorMapData( Str path, Str filename );

        /// 刷新颜色数据
        virtual void                refreshColors(const Rect& rect) = 0;

   
//**********************************************************************************************************************
//**********************************************************************************************************************

        /*########################################
        //          光影层操作       
        #########################################*/

    protected:

        /// 加载光影层数据
        virtual void                loadLightMapData( Str& path ) = 0;
        /// 加载颜色层数据
        void                        loadLightMapData( Str path, Str filename );


        /// 卸载光影层数据
        void                        unLoadLightMapData();

        /// 保存光影层数据
        virtual void                saveLightMapData( Str& path ) = 0;
        /// 保存光影层数据
        void                        saveLightMapData( Str path, Str filename );

        /// 设置灯光贴图光线方向
        void                        setLightMapDirection(Vec3 dir);

    public:

        /** Get the requested size of lightmap for this terrain. 
        Note that where hardware limits this, the actual lightmap may be lower
        resolution. This option is derived from TerrainGlobalOptions when the
        terrain is created.
        */
        uint16                      getLightmapSize() const { return mLightmapSize; }

        /// Get access to the lightmap, if enabled (as requested by the material generator)
        const TexturePtr&           getLightmap() const { return mLightmap; }

        void                        setLightingMapChangeDirty( Bool isChange ){ mLightingMapChangeDirty = isChange; };

    protected:

        /// 刷新光影层数据
        void                        refreshLightmap(const Rect& rect);

        void                        createOrDestroyGPULightmap( Str& path );

        /** Calculate (or recalculate) the terrain lightmap
        @param rect Rectangle describing the area of heights that were changed
        @param extraTargetRect Rectangle describing a target area of the terrain that
        needs to be calculated additionally (e.g. from a neighbour)
        @param outFinalRect Output rectangle describing the area updated in the lightmap
        @returns Pointer to a PixelBox full of lighting data (caller responsible for deletion)
        */
        PixelBox*                   calculateLightmap(const Rect& rect, const Rect& extraTargetRect, Rect& outFinalRect);

//**********************************************************************************************************************
//**********************************************************************************************************************


    protected:

        ///////////////////////////////////////////////////////////////////////////////////

        /// 地形管理器
        TerrainManager* mTerrainMgr;
        Scene* mScene;
        TerrainChunk* mChunk;
        
        // 路径
        Str mPath;

        /// 中心点
        Vector3     mPos;
        /// 相对于中心点偏移
        Real        mBaseOffset;
        /// 顶点间隔
        Real        mVertexOffset;
        /// 顶点一半间隔
        Real        mVertexHalfOffset;
        /// 顶点数量, 沿着一边
        UInt        mVertexSideNum;
        /// 顶点数量, 沿着tile
        UInt        mVertexSideNumInTile;
		/// 顶点数量, 沿着node
		UInt        mVertexSideNumInNode;

        // Node 一边 数量 
		Int         mNodeSideNumInChunk;
        Flt         mNodeSize;

		 // Tile 一边 数量 
		Int         mTileSideNumInChunk;
        Int         mTileSideNumInNode;
		Flt         mTileSize;
        
        //################# 实时更新参数 ###############

        // 更新表示位
        bool mModified;
        bool mHeightDataModified;

        // 区域更新范围
        Ogre::Rect mDirtyGeometryRect;
        Ogre::Rect mDirtyDerivedDataRect;
        Ogre::Rect mDirtyGeometryRectForNeighbours;


        //################# 高度数据 ###############

        // @remarks: 大小为mVertexSideNum * mVertexSideNum + 1
        Flt* mHeightData;
        // 高度的缩放值
        Flt mHeightScale;
        // 高度的最高值
        Flt mHeightMax;
        // 高度的最小值
        Flt mHeightMin;
        Bool mHeightDataCreated;


        //################# 全局法线参数 ###############

        Flt* mNormalData;
        Flt* mTangentData;

        UInt mNTOnePixelNum;
        UInt mNTPixelNum;
        UInt mNTDataSize;
        bool mNormalMapRequired;

        //################# 全局颜色参数 ###############

        U8*  mColorData;
        UInt mColorOnePixelNum;
        UInt mColorPixelNum;
        UInt mColorDataSize;
        bool mColorMapRequired;


        //################# 光影贴图参数 ###############

        Bool mLightingMapChangeDirty;
        uint16 mLightmapSize;
        uint16 mLightmapSizeActual;
        TexturePtr mLightmap;
        uint8* mCpuLightmapStorage;

        bool mLightMapRequired;
        bool mLightMapShadowsOnly;

        Vector3 mLightMapDirection;

    };

}

/******************************************************************************/

#endif
