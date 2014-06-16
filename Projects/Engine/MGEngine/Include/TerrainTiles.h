/******************************************************************************/
#ifndef _TERRAINTILES_H_
#define _TERRAINTILES_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "MGGrid.h"

/******************************************************************************/
namespace MG
{

    //×××××××××××××××××××××××××××××××××××××××××××××××××
    //×××××××××××××××××××××××××××××××××××××××××××××××××

    //@{
#pragma pack( push )
#pragma pack( 1 )
    /******************************************************************************/
    //一个地块
    /******************************************************************************/
    struct TerrainTile
    {
        // 渲染地块在Surface中的中心坐标
        Flt worldCenterPosX, worldCenterPosZ;
        // 渲染地块在Surface中的半径
        Flt radius;

        // 渲染地块的顶点在Surface中的区域
        Ogre::Rect vertexRectInSurface;

        // 渲染者
        TerrainTileRender* render;
    };

    /******************************************************************************/
    //一个地块批次
    /******************************************************************************/
    struct TerrainBatchGrid
    {
        TerrainBatch* batch;
    };

#pragma pack (pop)
    //@}


    //×××××××××××××××××××××××××××××××××××××××××××××××××
    //×××××××××××××××××××××××××××××××××××××××××××××××××

    /******************************************************************************/
    //地块中的单次渲染区域
    /******************************************************************************/
    class TerrainTileRender : public GridManager<TerrainBatchGrid>
    {
        friend class TerrainBatch;
    public:

        TerrainTileRender( TerrainManager* mgr, TerrainChunk* chunk, 
            TerrainSurface* surface, TerrainNode* node, TerrainTile* tile, UInt index );

        virtual ~TerrainTileRender();

    public:

        //**********************************************************************************************************************
        //**********************************************************************************************************************

        virtual void                    update( Flt delta ) ;
        
        virtual void                    load( ) ;
        virtual void                    unload( ) ;
        /// 设备重置
        virtual void                    reset();

        TerrainSurface*                 getTerrainSurface() { return mTerrainSurface; };
        TerrainChunk*                   getTerrainChunk() { return mTerrainChunk; };
        TerrainManager*                 getTerrainManager() { return mTerrainMgr; };
        

        // 创建栅格
        virtual void                    createGrids();
        /// 创建栅格
        virtual void                    createGrids(Int gridsSideNum, Flt gridSize,  Vec2 centerPos);
        /// 销毁栅格
        virtual void                    destroyGrids();

        const Ogre::Rect&               getWorldBoundingRect(void){ return mWorldBoundingRect; };

        //**********************************************************************************************************************
        //**********************************************************************************************************************

    public:

        /*########################################
        //     批次处理对象
        #########################################*/

        // 加载和卸载批次处理对象
        void                            loadRootBatch();
        void                            resetRootBatch();
        void                            unLoadRootBatch();
        
        // 创建地形批次对象
        virtual TerrainBatch*           createTerrainBatch( Scene* scene, TerrainTileRender* tileRender, TerrainBatch* parent, 
            const AxisAlignedBox& aabb, Ogre::Rect vertexRectInTile, MovableObject* movableObject) = 0;


        /*########################################
        //      CPU顶点数据操作          
        #########################################*/

    public:

        void                            loadRenderData();
        void                            unLoadRenderData();

    protected:

        // 创建和销毁顶点数据
        void                            createCpuVertexData();
        void                            destroyCpuVertexData();

        // 初始化顶点数据
        void                            initializeVertexBuffer();

    public:

        // 得到顶点属性
        UInt                            getOneVertexSize(){ return mOneVertexSize; };
        UInt                            getVertexSideSize(){ return mVertexSideNum; };
        UInt                            getVertexTotalSize(){ return mVertexTotalNum; };

    public:

        // 得到顶点数据
        Ogre::VertexData*               getCpuVertexData(){ return mCpuVertexData; };
        // 更新顶点位置
        void                            updateVertex(const Ogre::Rect& vertexRectInSurface);

       
        /*########################################
        //      材质管理
        #########################################*/

    public:

        /// 应用显示参数修改
        virtual void                    applyRenderConfig(){};

//**********************************************************************************************************************
//**********************************************************************************************************************

    protected:

        ///////////////////////////////////////////////////////////////////////////////
        
        // 管理对象

        TerrainManager* mTerrainMgr;
        TerrainSurface* mTerrainSurface;
        TerrainChunk*   mTerrainChunk;
        TerrainNode*    mTerrainNode;
        TerrainTile*    mOwner;
        UInt            mIndex;

        Ogre::Rect      mWorldBoundingRect;

        ///////////////////////////////////////////////////////////////////////////////

        // 顶点信息
        Ogre::VertexData* mCpuVertexData;
        UInt    mOneVertexSize;
        UInt    mVertexSideNum;
        UInt    mVertexTotalNum;

    public:

        static unsigned short POSITION_BUFFER;

        ///////////////////////////////////////////////////////////////////////////////
        
    };


    
}

/******************************************************************************/

#endif
