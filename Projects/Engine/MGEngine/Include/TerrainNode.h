/******************************************************************************/
#ifndef _TERRAINNODE_H_
#define _TERRAINNODE_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "MGGrid.h"
#include "TerrainTiles.h"

/******************************************************************************/
namespace MG
{


	//×××××××××××××××××××××××××××××××××××××××××××××××××
	//×××××××××××××××××××××××××××××××××××××××××××××××××

	//@{
#pragma pack( push )
#pragma pack( 1 )

	/******************************************************************************/
	//一个地块节点
	/******************************************************************************/
	struct TerrainNodeGrid
	{
		// 渲染地块在Surface中的中心坐标
		Flt worldCenterPosX, worldCenterPosZ;
		// 渲染地块在Surface中的半径
		Flt radius;

		// 渲染地块的顶点在Surface中的区域
		Ogre::Rect vertexRectInSurface;

		// 渲染者
		TerrainNode* node;
	};

#pragma pack (pop)
	//@}


    //×××××××××××××××××××××××××××××××××××××××××××××××××
    //×××××××××××××××××××××××××××××××××××××××××××××××××

    /******************************************************************************/
    //地块中的节点
    /******************************************************************************/
    class TerrainNode : public GridManager<TerrainTile>
    {
        friend class TerrainBatch;
    public:
		TerrainNode( TerrainManager* mgr, TerrainChunk* chunk, TerrainSurface* surface, TerrainNodeGrid* grid, UInt index );
        virtual ~TerrainNode();

    public:

		// 更新
		virtual void                    update( Flt delta ) ;
		/// 响应渲染配置
		virtual void					applyRenderConfig();

        /// 得到序列号
        virtual UInt					getIndex(){ return mIndex; };
        
        /// 得到网格对象
        virtual TerrainNodeGrid*        getOwner(){ return mOwner; };
        
	public:

		// 创建栅格
		virtual void                    createGrids();
		// 创建栅格
		virtual void                    createGrids(Int gridsSideNum, Flt gridSize,  Vec2 centerPos);
		// 销毁栅格
		virtual void                    destroyGrids();

	public:

		// 加载
		virtual void                    load();
		// 卸载
		virtual void                    unload();
		// 设备重置
		virtual void                    reset();

	public:

		// 更新顶点位置
		void                            updateVertex(const Ogre::Rect& vertexRectInSurface);

    public:

        /*########################################
        //     渲染对象， 可移动对象
        #########################################*/
        
        /// 地形的移动对象
        class Movable : public MovableObject
        {

        protected:

            TerrainNode*    mTerrainNode;
            AxisAlignedBox  mAABB; //relative to mLocalCentre
            AxisAlignedBox  mRenderAABB; //relative to mLocalCentre
            Ogre::Rect      mRect;
            Real            mBoundingRadius; //relative to mLocalCentre

        public:

            Movable(TerrainNode* node, AxisAlignedBox& aabb, AxisAlignedBox& worldAAbb);
            virtual ~Movable();

            // necessary overrides
            virtual const String&           getMovableType(void) const;
            virtual const AxisAlignedBox&   getBoundingBox(void) const;
            virtual Real                    getBoundingRadius(void) const;

            virtual void                    findVisibleObject();

            virtual void                    _updateRenderQueue(RenderQueue* queue);
            virtual void                    visitRenderables(Renderable::Visitor* visitor,  bool debugRenderables = false);

            virtual uint32                  getVisibilityFlags(void) const;
            virtual uint32                  getQueryFlags(void) const;
            virtual bool                    getCastShadows(void) const;

            const Ogre::Rect&               getWorldBoundingRect(void){ return mRect; };
        };

        /////////////////////////////////////////////////////////////////////////////////////////////////////

        // 加载和卸载可移动对象
        void                                loadMovableObject();
        void                                unLoadMovableObject();

        // 得到movable
        Movable*                            getMovable(){return mMovable;}

        friend class Movable;

	protected:

		TerrainManager*			mTerrainMgr;
		TerrainSurface*			mTerrainSurface;
		TerrainChunk*			mTerrainChunk;
		TerrainNodeGrid*		mOwner;
		UInt					mIndex;

		// Tile 一边 数量 
		Int             mTileSideNumInNode;
		Flt             mTileSize;

        // 场景节点和移动对象
        Movable*        mMovable;
        MGSceneNode*    mSceneNode; 


    };



}


/******************************************************************************/

#endif