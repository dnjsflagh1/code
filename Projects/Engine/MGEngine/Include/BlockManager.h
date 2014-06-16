/******************************************************************************/
#ifndef _BLOCKMANAGER_H_
#define _BLOCKMANAGER_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "IBlockManager.h"
#include "GridPool.h"
#include "ManualMeshManager.h"
/******************************************************************************/
namespace MG
{

	/******************************************************************************/
	//碰撞对象列表
	/******************************************************************************/
	struct CollisionBlockObjectList
	{
		std::vector<DynamicBlockObject*> dynamicBlockObjectList;

		void removeDynamicBlockObject(DynamicBlockObject* dynamicBlockObject)
		{
			for(std::vector<DynamicBlockObject*>::iterator it = dynamicBlockObjectList.begin(); it != dynamicBlockObjectList.end(); ++it)
			{
				if((*it) == dynamicBlockObject)
				{
					dynamicBlockObjectList.erase(it);
					return;
				}
			} 
		}

		void addDynamicBlockObject(DynamicBlockObject* dynamicBlockObject)
		{
			removeDynamicBlockObject(dynamicBlockObject);
			dynamicBlockObjectList.push_back(dynamicBlockObject);
		}
	};

    /******************************************************************************/
    //碰撞系统
    /******************************************************************************/
	class BlockManager : public IBlockManager
    {
    public:
        BlockManager( Scene* scene );
        virtual ~BlockManager();

        //////////////////////////////////////////////////////////////////////////////////////////////////

        /// 静态障碍网格大小
        static Real STATIC_BLOCK_GRID_SIZE ;
        /// 动态障碍网格大小
        static Real DYNAMIC_BLOCK_GRID_SIZE;

        enum BLOCK_FLAG
        {
            BLF_NULL							= 0,		// 无定义,可理解为无障碍
            BLF_TERRAIN_BLOCK					= BIT(0),	// 地形静态障碍
            BLF_ENTITY_ALLSIDE_BLOCK			= BIT(1),	// 实体和建筑完整轮廓所占绝对障碍
			BLF_STRUCTURE_ALLSIDE_BLOCK			= BIT(2),	// 
			BLF_STRUCTURE_INSIDE_BLOCK			= BIT(3),	// 建筑内部障碍，用于在建筑内部寻路使用的障碍
			BLF_STRUCTURE_OUTSIDE_BLOCK			= BIT(4),	// 建筑外部障碍，用于在建筑外部寻路使用的障碍

			BLF_STRUCTURE_ROAD					= BIT(5),	// 建筑内部道路，作用域最小，用来判断是否处于在建筑内部还是外部
			BLF_STRUCTURE_PASSAGE				= BIT(6),	// 建筑与建筑的通路，
															// 作用域大于 BLF_STRUCTURE_INSIDE_BLOCK，BLF_STRUCTURE_OUTSIDE_BLOCK
															// 作用域小于 BLF_ENTITY_STRUCTURE_ALLSIDE_BLOCK
        };

		enum LAYER_FLAG
		{
			LLF_NULL				= 0,		// 无定义
			LLF_STRUCTURE_INSIDE	= BIT(0),	// 在建筑内部
			LLF_STRUCTURE_OUTSIDE	= BIT(1),	// 在建筑外部
		};

		/****************************
		//通用方法
		/****************************/


        /// 加载静态障碍数据
		virtual void            loadStaticBlock( Vec2 leftBottomPos, Vec2 rightUpPos );
        /// 加载动态障碍数据
		virtual void            loadDynamicBlock( Vec2 leftBottomPos, Vec2 rightUpPos );

        /// 卸载所有障碍数据
        virtual void            unLoad();

        /// 更新
        void                    update(Flt delta);

		// 检测实体碰撞
		void                    checkEntityBlock();

		void					clearAllStaticBlock();
		void					clearAllDynamicBlock();
		void					clearMapAllBlock();	

        
        //////////////////////////////////////////////////////////////////////////////////////////////////

		// 得到静态网格列表
		GridPool<Byte>*			getStaticBlockList();
		// 得到静态网格列表
		GridPool<Byte>*			getDynamicBlockList();

		// 得到动态障碍宽度，单位宽度一边的网格数量
		Int                     getDynamicBlockMapWidth();
		// 得到动态障碍网格大小
		virtual	Flt				getDynamicBlockGridSize();
        // 得到静态障碍网格大小
		virtual	Flt				getStaticBlockGridSize();

		/**************************************************************
		//动态和静态障碍坐标和索引等转换方法
		/**************************************************************/

		// 设置动态障碍通过索引点
		void                    setDynamicBlockByPoint( Int x, Int z, BLOCK_FLAG flag );
		// 设置动态障碍通过索引
		void                    setDynamicBlockByIndex( UInt index, BLOCK_FLAG flag );
		// 动态障碍通过世界坐标
		void					setDynamicBlockByPos( Vec3 pos, BLOCK_FLAG flag, Int diameterSize = 1 );

		// 清空动态障碍通过索引
		void                    clearDynamicBlock( UInt index, BLOCK_FLAG flag );
		// 清空动态障碍通过世界坐标
		void                    clearDynamicBlock( Vec3 pos, BLOCK_FLAG flag, Int diameterSize = 1 );

		// 得到动态障碍索引通过世界坐标
		UInt					getDynamicBlockIndexByWorldPos( Vec3 pos );
		// 得到动态障碍索引点通过世界坐标
		void					getDynamicBlockPointByWorldPos( Vec3 pos, Int& x, Int& z );
		// 得到动态障碍索引通过索引点
		UInt					getDynamicBlockIndexByPoint( Int x, Int z );
		// 得到动态网格障碍中心点通过索引
		Vec3					getDynamicBlockGridCenterPosByIndex( UInt index );

		//////////////////////////////////////////////////////////////////////////////////////////////////

		// 设置静态障碍通过索引点
		void                    setStaticBlockByPoint( Int x, Int z, BLOCK_FLAG flag );
		// 设置静态障碍通过索引
		void                    setStaticBlockByIndex( UInt index, BLOCK_FLAG flag );

		// 清空静态障碍通过索引
		void                    clearStaticBlock( UInt index, BLOCK_FLAG flag );

		// 得到静态障碍网格索引通过世界坐标
		UInt					getStaticBlockIndexByWorldPos( Vec3 pos );
		// 得到静态索引点通过世界坐标点
		void					getStaticBlockPointByWorldPos( Vec3 pos, Int& x, Int& z );
		// 得到静态索引通过索引点
		UInt					getStaticBlockIndexByPoint( Int x, Int z );
		// 得到静态网格障碍中心点通过索引
		Vec3					getStaticBlockGridCenterPosByIndex( UInt index );

		/**************************************************************
		//三角面操作相关
		/**************************************************************/

		// 设置动态和静态障碍通过三角面列表
		void					setBlockByTriangle3DList( std::vector<Triangle3D>& worldTriangle3DList, BLOCK_FLAG flag );

		// 得到网格索引点列表通过三角面列表, 根据开关判断是否为静态或动态障碍网格
		void					getBlockGridListByTriangle3DList(  std::map<UInt, VecU2>& gridPointList, std::vector<Triangle3D>&  mWorldTriangle3DList, Bool isStaticBlock );

		// 得到网格索引点列表 通过 行扫描 一个三角面，步长计算
		void					getGridByOneWorldBlockTriangleByRowScan( GridPool<Byte>* mapBlock, Vector3* posList, Vec2 minPoint, Vec2 maxPoint, Int stepSize, std::map<UInt, VecU2>& gridPointList );
		// 得到网格索引点列表 通过 列扫描 一个三角面，步长计算
		void					getGridByOneWorldBlockTriangleByColScan( GridPool<Byte>* mapBlock, Vector3* posList, Vec2 minPoint, Vec2 maxPoint, Int stepSize, std::map<UInt, VecU2>& gridPointList );

		Bool					getLineTriangleIntersectPoint( Vector2 lineP, Vector2 lineD, Vector3* trianglePosList, Vector2* intersectPos );

		/**************************************************************
		//判断是否为障碍相关方法
		/**************************************************************/

        // 是否是障碍
        static Bool             isBlockFlag( Byte* flag, LAYER_FLAG layerFlag );
		// 是否是动态障碍
		static Bool             isDynamicBlockFlag( Byte* flag );

        // 是否有静态标志位
        Bool                    hasStaticBlockFlagByIndex( UInt index, Byte flag );

		// 是否为静态障碍通过世界坐标点
		virtual Bool			isStaticBlock( Vec3 currPos );
		// 是否为静态障碍通过索引点
		Bool					isStaticBlock( Int currX, Int currZ );
        // 是否为静态障碍通过索引
        Bool					isStaticBlockByIndex( UInt index );

        // 是否有动态标志位
        Bool                    hasDynamicBlockFlagByIndex( UInt index, Byte flag );

        // 是否为动态障碍
        virtual Bool			isDynamicBlockByIndex( UInt index );

		// 是否为动态障碍，依据半径
		virtual Bool			isDynamicBlockByRadius( Vec3 currPos, Int findPathObjectCellDiameter, VertexPos vertexPos = VERTEX_MAX, IDynamicBlockObject* ignoreObj = NULL );

        // 检测开始点到结束点之间是否有障碍
		virtual Bool			isDynamicBlockBetweenTwoPos( IDynamicBlockObject* ignoreObj, Vec3 startPos, Vec3 endPos, UInt& blockIndex, Int findPathObjectCellDiameter = 1, Bool isPrecise = false );

        
		/**************************************************************
		//计算网格相关方法
		/**************************************************************/

        // 得到最近的可进入点, 选取中心点周围方向
        virtual	Bool			getPosNearestAccessiblePos( const Vec3 centerPos, Int findPathObjectCellDiameter, Vec3& nearestAccessiblePos, IDynamicBlockObject* ignoreObj );
		// 得到最近的可进入点, 优先选取指定方向
		virtual	Bool			getPosNearestAccessiblePosForDir( const Vec3 centerPos, Vec3 dir, Flt disLen, Int findPathObjectCellDiameter, Vec3& nearestAccessiblePos );

		virtual	Bool			getPosNearestAccessiblePos( const Vec3 centerPos, Vec3 dir, Flt disLen, Int findPathObjectCellDiameter, Vec3& nearestAccessiblePos );
		// 得到最近的可进入距离
		virtual	Bool			getPosNearestAccessibleDis( const Vec3 centerPos, Vec3 dir, Int findPathObjectCellDiameter, Flt& nearestAccessibleDis );

		/*virtual	Bool			getPosNearestAccessiblePosForGridScan( const Vec3 centerPos, Vec3 dir, Flt disLen, Int findPathObjectCellDiameter, Vec3& nearestAccessiblePos );*/

        //////////////////////////////////////////////////////////////////////////////////////////////////
	
		// 得到经过障碍网格
		virtual	Bool			getPassBlockGrid( Vec3 startPos, Vec3 endPos, std::vector<PassGridBlock>& passBlockGridList, UInt diameterSize = 1 );

		virtual	Bool			getPassBlockGrid( Vec3 startPos, Vec3 endPos, std::map<UInt, VecU2>& passBlockGridList );

		//////////////////////////////////////////////////////////////////////////////////////////////////

		// 得到指定点周围的障碍网格列表，根据所占网格大小
		Bool					getBlockGridListByRect( Vec3 pos, std::map<UInt, UInt>& blockGridList, VecI2& minPoint, VecI2& maxPoint, Int diameterSize = 1, VertexPos vertexPos = VERTEX_MAX );
        // 得到新增加的障碍网格列表
        Bool					getNewAddBlockGridListByRect( Vec3 oldPos, Vec3 newPos, std::map<UInt, UInt>& blockGridList, VecI2& minPoint, VecI2& maxPoint, Int diameterSize = 1 );

		Bool					getOldBlockGridListByRect( Vec3 pos, VecI2 minPoint, VecI2 maxPoint, std::map<UInt, UInt>& blockGridList, Int diameterSize = 1, VertexPos vertexPos = VERTEX_MAX );

		//////////////////////////////////////////////////////////////////////////////////////////////////

		VertexPos				getPosNearestVertexPos( Vec3 pos, Vec2& vertexPosPos );
	
		/**************************************************************
		//障碍对象相关方法
		/**************************************************************/

		// 创建和销毁动态障碍对象
		DynamicBlockObject*     createDynamicBlockObject(Scene* scene, IEntity* sceneObject, Flt objectRadius);
		void                    destroyDynamicBlockObject(DynamicBlockObject* obj);

		// 增加一个动态对象到网格
		void					addDynamicBlockObjectToGridBlock(UInt gridIndex, IDynamicBlockObject* object, Byte flag);
		// 移除一个网格对象从网格
		Bool					removeDynamicBlockObjectFromGridBlock(UInt gridIndex, IDynamicBlockObject* object, Byte flag);

		// 得到障碍对象通过索引
        virtual IDynamicBlockObject*	getDynamicBlockObjectFromGridBlock(UInt gridIndex);
		IDynamicBlockObject*	        getDynamicBlockObjectFromGridBlock(UInt gridIndex, Byte flag);

		//////////////////////////////////////////////////////////////////////////////////////////////////

        // 得到射线与指定索引点的动态网格的相交点
        Bool                    isIntersectionWithDynamicGridByGridIndex( Vec3 startPos, Vec3 endPos, UInt index );
        
        //////////////////////////////////////////////////////////////////////////////////////////////////

        // 得到动态障碍对象列表
        typedef std::map<UInt, IDynamicBlockObject*> DynamicBlockObjectList;
        DynamicBlockObjectList& getDynamicBlockObjectList( Byte flag );

		Bool				    isBlockByPointAround(Vec3 pos, UInt findPathObjectCellDiameter);


    private:

        // 游戏场景
        Scene*  				mScene;
		GridPool<Byte>			mMapStaticBlock;
		GridPool<Byte>			mMapDynamicBlock;

        std::map<Byte, DynamicBlockObjectList> mDynamicBlockObjectListMap;
    };
}

/******************************************************************************/

#endif
