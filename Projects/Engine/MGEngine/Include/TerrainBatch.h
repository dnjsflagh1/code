/******************************************************************************/
#ifndef _TERRAINBATCH_H_
#define _TERRAINBATCH_H_
/******************************************************************************/

#include "EnginePreqs.h"

/******************************************************************************/
namespace MG
{

    //×××××××××××××××××××××××××××××××××××××××××××××××××
    //×××××××××××××××××××××××××××××××××××××××××××××××××

    /******************************************************************************/
    //地块中的单次渲染管理
    /******************************************************************************/
    class TerrainBatch
    {
    public:
        TerrainBatch( Scene* scene, TerrainTileRender* tileRender, TerrainBatch* parent, 
            const AxisAlignedBox& aabb, Ogre::Rect vertexRectInTile,
            MovableObject* movableObject );
        virtual ~TerrainBatch();

    public:


        // 加载和卸载资源
        virtual void                    load();
        virtual void                    unLoad();
        /// 设备重置
        virtual void                    reset();

        void                            setRenderEnable( bool enable );
        Bool                            getRenderEnable(){return mRenderEnable;};
        
        // 更新渲染可见状态
        void                            updateVisible( AxisAlignedBox& visibleAAbb );

        // 增加和访问渲染对象
        virtual void                    addRenderable(RenderQueue* queue);
        virtual void                    visitRenderables(Renderable::Visitor* visitor);

        // 是否可渲染的有效距离
        virtual Bool                    isValidRenderableDistance(Ogre::Camera* cam) ;

        /*########################################
        //       Batch 管理     
        #########################################*/

    protected:

        // 创建和销毁批次处理子批次对象
        void                            loadChilds();
        void                            unLoadChilds();


        /*########################################
        //      GPU顶点数据操作          
        #########################################*/

    public:

        // 刷新顶点
        void                            updateVertexData( const Ogre::Rect& vertexRectInTile );

    protected:

        // 创建和销毁顶点和索引资源
        void                            createGpuVertexData();
        void                            destroyGpuVertexData();
        // 销毁顶点后台缓冲数据，销毁和不能锁定缓存区修改内存，但是可以渲染
        void                            destroyGpuVertexBackupData();
        // 检测顶点后台缓冲数据
        void                            checkAndUpdateGpuVertexBackupData();

        void                            createGpuIndexData();
        void                            destroyGpuIndexData();
        // 销毁索引后台缓冲数据，销毁和不能锁定缓存区修改内存，但是可以渲染
        void                            destroyGpuIndexBackupData();
        // 检测索引后台缓冲数据
        void                            checkAndUpdateGpuIndexBackupData();

        void                            populateIndexData();


    public:

        static UInt                     getNumIndexesForBatchSize(U16 batchSize);
        /** Utility method to populate a (locked) index buffer.
        @param pIndexes Pointer to an index buffer to populate
        @param batchSize The number of vertices down one side of the batch
        */
        static void                     populateIndexBuffer(uint32* pI, U16 batchSize);


        /*########################################
        //      渲染实例
        #########################################*/

    protected:

        void                            loadRenderableObject();
        void                            unLoadRenderableObject();

    public:

        /// Get the material being used for the terrain
        virtual MaterialPtr&            getOrGenerateMaterialPtr() =0;


    public:

        /// 地形的批次渲染实例
        class Rend : public Renderable, public GeneralAllocatedObject
        {
        protected:
            TerrainTileRender*  mTileRender;
            MovableObject*      mMovableObject;
            Vector3             mCenterPos;
            TerrainBatch*       mBatch;
            IDisplay*           mDisplay;
        public:
            Rend(TerrainTileRender* tileRender, TerrainBatch* batch, MovableObject* movableObject, Vector3 centerPos);
            virtual ~Rend();

            virtual const MaterialPtr&  getMaterial(void) const;
            virtual Technique*          getTechnique(void) const;
            virtual void                getRenderOperation(RenderOperation& op);
            virtual void                getWorldTransforms(Matrix4* xform) const;
            virtual Real                getSquaredViewDepth(const Ogre::Camera* cam) const;
            virtual const LightList&    getLights(void) const;
            virtual bool                getCastsShadows(void) const;
        };

        friend class Rend;

    protected:

        ///////////////////////////////////////////////////////////////////////////////

        Scene*                  mScene;    
        TerrainManager*         mTerrainManager;
        TerrainSurfaceManager*  mSurfaceManager;
        TerrainChunk*           mTerrainChunk;
        TerrainTileRender*      mTileRender;
        TerrainBatch*           mParent;

        MovableObject*          mMovableObject;
        Rend*                   mRender;

        Bool                    mIsLoaded;
        Bool                    mIsVisible;

        ///////////////////////////////////////////////////////////////////////////////

        AxisAlignedBox          mBoundingBox;
        AxisAlignedBox          mNodeBoundingBox;
        Ogre::Rect              mVertexRectInTile;
         
        //////////////////////////////////////////////////////////////////////

        Ogre::VertexData*       mGpuVertexData;
        Ogre::IndexData*        mGpuIndexData;

        UInt                    mOneVertexSize;         //单个顶点占用缓存大小
        UInt                    mVertexSideNum;
        UInt                    mVertexTotalNum;
                        
        //////////////////////////////////////////////////////////////////////

        Bool                    mRenderEnable;
        

    };



}


/******************************************************************************/

#endif