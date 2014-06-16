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
  
    //��������������������������������������������������������������������������������������������������
    //��������������������������������������������������������������������������������������������������


    /******************************************************************************/
    /** ��Ϸ��ò�ؿ���Ⱦ����
    @remarks:
    World space align is X_Z; Y is height.
    -Z
    ||||  
    -X---0---X
    |  
    Z

    @remarks:
    Terrain space: ��λΪ���� (0,0)-(1,1)
    (0,0) is the bottom-left of the terrain, and (1,1) is the top-right.

    ���� X_Y �غ��� World space X_-Z.

    where x/y represents the terrain plane and z represents the up vector

    Y
    |
    0---X

    @remarks:
    VertexPoint space : ��λΪ����
    UV space : ��λΪ���ر��� (0,0)-(1,1)
    ����X_Y, �غ��� World space X_-Z.
    Y
    |
    0---X

    @remarks:
    ÿ����ͼ��Ӧһ��TerrainTilesLayerBlendMap����
    ÿ�Ĳ���ͼ(�Լ�TerrainTilesLayerBlendMap)ͨ��һ�ŵ�ɫ����ͼ(BlendTexture)��ϡ�
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
        //                  ������        
        #########################################*/

        virtual TerrainSurfaceType  getType() = 0;
        virtual SceneObjectTypes    getSceneObjectTypes() = 0;
        virtual UInt                getSceneVisibleFlags() = 0;
        // �õ���Ⱦ����
        virtual uint8               getRenderQueueGroup() = 0;

        /// ����ѡ��
        virtual void                configOptions();
		/// ��Ӧ��Ⱦ����
		virtual void                applyRenderConfig();


        /// �������� 
        virtual void                load( Str path );
        /// ж������
        virtual void                unLoad();
        /// �豸����
        virtual void                reset();
        /// ��������
        virtual void                save( Str path );
        /// ����
        virtual void                update(Flt delta, bool synchronous = false);



        /// ����դ��
        virtual void                createGrids(Int gridsSideNum, Flt gridSize,  Vec2 centerPos);
        /// ����դ��
        virtual void                destroyGrids();

        /// ������������
        virtual void                loadGridData();
        /// ж����������
        virtual void                unLoadGridData();
        /// ������������
        void                        updateGridData(Flt delta);

        /// �����������
        void                        dirtyRect(const Ogre::Rect& rect);
        /// �����������
        void                        dirtyRect(Int x, Int y);

        /// �õ���Ⱦ����
        TerrainTile*                getTileGridDataByIndex( UInt x, UInt y );


		// �����ֿ�ڵ�
		virtual TerrainNode*		createTerrainNode( TerrainManager* mgr, TerrainChunk* chunk, 
										TerrainNodeGrid* nodeGrid, UInt index );
		// �����ֿ���Ⱦ��
		virtual TerrainTileRender*  createTerrainTileRender( TerrainManager* mgr, TerrainChunk* chunk, TerrainNode* node,
										TerrainTile* tile, UInt index ) = 0;
        
        //**********************************************************************************************************************
        //**********************************************************************************************************************


        /*########################################
        //               �ռ�ת��          
        #########################################*/

        /// �õ����߲�ѯ
        Bool                        getRayIntersection(Vec3& pos, Vec3& dir, Vec3& intersectPos,Bool isPrecise);
        Bool                        getRayIntersection2(Vec3& pos, Vec3& dir, Vec3& intersectPos,Bool isPrecise);

        Bool                        getRayIntersectionTri3DInGridByWorldPosition( Ogre::Ray& ray, Vector3& worldPos, Vec3& intersectPos );
        Bool                        getRayIntersectionTri3DInGridByVertexPoint( Ogre::Ray& ray, UInt x, UInt y, Vec3& intersectPos );

        /// Get the minimum height of the terrain
        Real                        getMinHeight() const;
        /// Get the maximum height of the terrain
        Real                        getMaxHeight() const;

        /// �õ��߶�ָ������ͨ������
        Bool                        hasHeightData() const;
        /// �õ��߶�ָ������ͨ������
        Flt*                        getHeightData(Int x, Int y) const;
        /// �õ��߶�����ͨ��������
        Flt                         getHeightAtPoint(Int x, Int y);
        /// ���ø߶�����ͨ��������
        void                        setHeightAtPoint(Int x, Int y, Flt h);

        /// �õ��߶�����ͨ�����������
        Flt                         getHeightAtWorldPosition(Real x, Real y);

        /// �õ����ε���Ƭ // �������ϵ��Ҫע��
        Bool                        getTerrainTri3DByTerrainPosition(Flt x, Flt y, 
            Triangle3D& tri3D1, Triangle3D& tri3D2);
        /// �õ����ε���Ƭ // �������ϵ��Ҫע��
        Bool                        getTerrainTri3DByVertexPoint(UInt x, UInt y, 
            Triangle3D& tri3D1, Triangle3D& tri3D2);

        /// �õ����ε���Ƭ 
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
        //               ������������ݲ���          
        #########################################*/

        /// �õ�һ�ߵĶ�������
        UInt                        getVertexSideNum()  const { return mVertexSideNum; }

        /// �õ�Tileһ�ߵĶ�������
        UInt                        getVertexSideNumInTile() const { return mVertexSideNumInTile; }

        /// �õ�һ�ߵĶ�������С
        Real                        getVertexOffset()  const { return mVertexOffset; }

        /// �õ�Tileһ�ߵ�������һ��Chunk��
        UInt                        getTileSideNumInChunk() const { return mTileSideNumInChunk; }
        
        ///////////////////////////////////////////////////////////////////////////////

        /// ���ظ߶�����
        virtual void                loadHeightData( Str path ) = 0;
        /// ���ظ߶�����
        void                        loadHeightData( Str path, Str fileName );
        /// �ͷŸ߶�����
        void                        unLoadHeightData();

        /// ����߶�����
        virtual void                saveHeightData( Str path ) = 0;
        /// ����߶�����
        void                        saveHeightData( Str path, Str fileName );

        ///////////////////////////////////////////////////////////////////////////////

        /// ���¶���
        void                        updateGeometry();
        /// ���¶���
        virtual void                updateGeometry( Ogre::Rect rect ){};


    public:

        //**********************************************************************************************************************
        //**********************************************************************************************************************


        /*########################################
        //          ���߲����      
        #########################################*/

    public:

        /// �õ����߲�����ͨ������
        Flt*                        getNormalDataByIndex(Int x, Int y) const;
        /// �õ����߲�����ͨ������
        Flt*                        getTangentDataByIndex(Int x, Int y) const;

        /// �õ����߲�����һ����λ��������
        UInt                        getNTOnePixelNum() {return mNTOnePixelNum;};

    protected:

        /// ���ط��߲�����
        virtual void                loadNormalTangentMapData( Str path ) = 0;
        /// ���ط��߲�����
        void                        loadNormalTangentMapData( Str path, Str normalFilename, Str tangentFileName );
        /// ж�ط��߲�����
        void                        unLoadNormalTangentMapData();

        /// ���淨�߲�����
        virtual void                saveNormalTangentMapData( Str path ) = 0;
        /// ���淨�߲�����
        void                        saveNormalTangentMapData( Str path, Str normalFilename, Str tangentFileName );

        /// ˢ�·�������
        void                        refreshNormalTangent(const Rect& rect);

    private:

        /// ��������
        Bool                        loadNTMapData( Str path, Str filename, Flt*&date );
        ///  ��������
        Bool                        saveNTMapData( Str path, Str filename, Flt*&date );

//**********************************************************************************************************************
//**********************************************************************************************************************


        /*########################################
        //          ��ɫ�����      
        #########################################*/

    public:

        /// �õ���ɫ������ͨ������
        U8*                         getColorDataByIndex(Int x, Int y) const;

        /// �õ���ɫ������һ����λ��������
        UInt                        getColorOnePixelNum() {return mColorOnePixelNum;};

    protected:

        /// ������ɫ������
        virtual void                loadColorMapData( Str path ) = 0;
        /// ������ɫ������
        void                        loadColorMapData( Str path, Str filename );
        /// ж����ɫ������
        void                        unLoadColorMapData();

        /// ������ɫ������
        virtual void                saveColorMapData( Str path ) = 0;
        /// ������ɫ������
        void                        saveColorMapData( Str path, Str filename );

        /// ˢ����ɫ����
        virtual void                refreshColors(const Rect& rect) = 0;

   
//**********************************************************************************************************************
//**********************************************************************************************************************

        /*########################################
        //          ��Ӱ�����       
        #########################################*/

    protected:

        /// ���ع�Ӱ������
        virtual void                loadLightMapData( Str& path ) = 0;
        /// ������ɫ������
        void                        loadLightMapData( Str path, Str filename );


        /// ж�ع�Ӱ������
        void                        unLoadLightMapData();

        /// �����Ӱ������
        virtual void                saveLightMapData( Str& path ) = 0;
        /// �����Ӱ������
        void                        saveLightMapData( Str path, Str filename );

        /// ���õƹ���ͼ���߷���
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

        /// ˢ�¹�Ӱ������
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

        /// ���ι�����
        TerrainManager* mTerrainMgr;
        Scene* mScene;
        TerrainChunk* mChunk;
        
        // ·��
        Str mPath;

        /// ���ĵ�
        Vector3     mPos;
        /// ��������ĵ�ƫ��
        Real        mBaseOffset;
        /// ������
        Real        mVertexOffset;
        /// ����һ����
        Real        mVertexHalfOffset;
        /// ��������, ����һ��
        UInt        mVertexSideNum;
        /// ��������, ����tile
        UInt        mVertexSideNumInTile;
		/// ��������, ����node
		UInt        mVertexSideNumInNode;

        // Node һ�� ���� 
		Int         mNodeSideNumInChunk;
        Flt         mNodeSize;

		 // Tile һ�� ���� 
		Int         mTileSideNumInChunk;
        Int         mTileSideNumInNode;
		Flt         mTileSize;
        
        //################# ʵʱ���²��� ###############

        // ���±�ʾλ
        bool mModified;
        bool mHeightDataModified;

        // ������·�Χ
        Ogre::Rect mDirtyGeometryRect;
        Ogre::Rect mDirtyDerivedDataRect;
        Ogre::Rect mDirtyGeometryRectForNeighbours;


        //################# �߶����� ###############

        // @remarks: ��СΪmVertexSideNum * mVertexSideNum + 1
        Flt* mHeightData;
        // �߶ȵ�����ֵ
        Flt mHeightScale;
        // �߶ȵ����ֵ
        Flt mHeightMax;
        // �߶ȵ���Сֵ
        Flt mHeightMin;
        Bool mHeightDataCreated;


        //################# ȫ�ַ��߲��� ###############

        Flt* mNormalData;
        Flt* mTangentData;

        UInt mNTOnePixelNum;
        UInt mNTPixelNum;
        UInt mNTDataSize;
        bool mNormalMapRequired;

        //################# ȫ����ɫ���� ###############

        U8*  mColorData;
        UInt mColorOnePixelNum;
        UInt mColorPixelNum;
        UInt mColorDataSize;
        bool mColorMapRequired;


        //################# ��Ӱ��ͼ���� ###############

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
