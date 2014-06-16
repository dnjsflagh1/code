/******************************************************************************/
#ifndef __PATHFINDER21_H__
#define __PATHFINDER21_H__
/******************************************************************************/

#include "IPathFinder.h"

#include "GridPool.h"
#include "GridFast.h"
#include "BinaryHeap.h"
#include "FastStructPool.h"
#include "BlockManager.h"
#include "ISceneNodeAction.h"

/******************************************************************************/

namespace MG
{

	//-----------------------------------------------------------------------
#pragma pack (push)
#pragma pack (1)

	struct FindPathCell21
	{
		//-----------------------------------------------------------------------
		enum FindPathState
		{
			FS_NULL				= 0,
			FS_IDLE				= 1,  // 自由状态
			FS_IN_OPEN_LIST		= 2,  // 在开启列表中
			FS_IN_CLOSE_LIST	= 3,  // 在关闭列表中
		};

		//-----------------------------------------------------------------------
		enum BlockState
		{
			BS_NULL_CHECK       = 0,
			BS_OUT_BLOCK        = 1,  // 在障碍外面
			BS_IN_SELF_BLOCK	= 2,
			BS_IN_STATIC_BLOCK	= 3,  // 在静态障碍中
			BS_IN_DYNAMIC_BLOCK	= 4,  // 在动态障碍中
		};

		// 寻路状态
		Byte findPathState;
		// 障碍状态
		Byte blockState;

		// 自身所处网格位置
		UInt x;
		UInt z;

		// 父节点所处网格
		FindPathCell21* parent;

		// 对象池索引
		UInt poolIndex;

		/** 
		二叉堆索引,
		由二叉堆管理器自动维护和修改。
		*/
		UInt binaryHeapIndex;

		/** 
		二叉堆索引规定的字段,用于比较大小.
		在这里描述为总移动耗损 : binaryHeapCost = gCost + hCost
		*/
		U16 binaryHeapCost;
		/// 起点到当前点的移动耗损,根据已求出路径来计算
		U16 gCost;
		/// 当前点到终点的移动耗损,使用启发式曼哈顿方法来计算
		//U16 hCost;

	};

#pragma pack (pop)


	/******************************************************************************/
	// 寻路算法
	/**
	1，把起始格添加到开启列表。
	2，重复如下的工作：
	a) 寻找开启列表中F值最低的格子。我们称它为当前格。
	b) 把它切换到关闭列表。
	c) 对相邻的8格中的每一个？
	* 如果它不可通过或者已经在关闭列表中，略过它。反之如下。
	* 如果它不在开启列表中，把它添加进去。把当前格作为这一格的父节点。记录这一格的F,G,和H值。
	* 如果它已经在开启列表中，用G值为参考检查新的路径是否更好。更低的G值意味着更好的路径。
	如果是这样，就把这一格的父节点改成当前格，并且重新计算这一格的G和F值。
	如果你保持你的开启列表按F值排序，改变之后你可能需要重新对开启列表排序。
	d) 停止，当你
	* 把目标格添加进了关闭列表(注解)，这时候路径被找到，或者
	* 没有找到目标格，开启列表已经空了。这时候，路径不存在。
	3.保存路径。从目标格开始，沿着每一格的父节点移动直到回到起始格。
	*/
	/******************************************************************************/
	class PathFinder21 : public IPathFinder
	{
	public:
		//-----------------------------------------------------------------------
		// 寻路类型
		enum PathFinderType
		{
			PT_NULL,
			PT_ALWAYS_NEAREST,  // 总是找最近点
			PT_SPREAD_SEARCH,   // 扩展式寻路
		};

		//-----------------------------------------------------------------------
		// 移动方向
		enum Movedir
		{
			md_null,
			md_up,
			md_down,
			md_left,
			md_right,
			md_upleft,
			md_upright,
			md_downleft,
			md_downright,
		};

		PathFinder21();
		~PathFinder21();

		
		// 加载寻路数据通过外部的障碍网格信息
		void						load(  Scene* scene, UInt pathFinderGridWidth, UInt pathFinderGridHeight );
		// 卸载寻路数据
		void						unLoad();
		// 是否已经加载
		Bool						isLoaded();
		// 设置寻路类型
		void						setType ( PathFinderType type );

		////////////////////////////////////////////////////////////////////////////////////////////////////////////

		/** 寻路计算
		@remarks
			可以根据一定策略中断寻路计算
		@param startPos
			开始寻路的坐标
		@param targetPos
			目标寻路的坐标
		@param findPathRect
			世界坐标系的寻路最大范围
		@param ignoreBlockRect
			世界坐标系的忽略障碍寻路最大范围
		@param checkMaxPath
			用于描述最大的寻路路径长度，如果为-1则表示无限长
		@param checkMaxDynamicBlock
			用于描述最多检测几次动态障碍后退出寻路计算，如果为-1则表示无限制。
		@returns
			0 : 表示寻路错误
			1 : 表示不需要寻路
			2 : 表示寻路成功
			3 : 表示寻路超过最长寻路路径退出
			4 : 表示寻路检测超过限定动态障碍次数后退出
			@par
		//
		*/
		PathFindingResult           findPath( BlockObject* pathFinder,
			Vec3 startPos,
			Vec3 targetPos, 
			RectF findPathRect,
			Int checkMaxPath = -1, 
			Int checkMaxDynamicBlock = -1 );

		// 世界坐标转换为网格坐标
		void						convertWorldPositionToGridPoint( Vec3 startPos, VecU2& CellPoint );


		// 得到寻路网格完整的结果 ,  注意是倒序的
		std::vector<VecU2>&			getFullFindCellPathResult();
		// 得到寻路节点完整的结果 ,  正序
		std::vector<Vec3>&		    getFullFindPathNodeResult();

		// 得到寻路网格合并的结果 ,  正序
		std::vector<VecU2>&			getCombineFindCellPathResult();
		// 得到寻路节点合并的结果 ,  正序
		std::vector<Vec3>&		    getCombineFindPathNodeResult();
		// 得到寻路节点平滑后的结果 ,正序
		std::vector<Vec3>&		    getSmoothFindPathNodeResult();

		////////////////////////////////////////////////////////////////////////////////////////////////////////////

	protected:

		// 检测坐标点是否在地图外面
		inline Bool		isOutMap( VecU2& cellPoint )
		{
			if ( cellPoint.x <= 0 )
				return true;

			if ( cellPoint.y <=0 )
				return true;

			if ( cellPoint.x >= mMapGridWidth )
				return true;

			if ( cellPoint.y >= mMapGridHeight )
				return true;

			return false;
		}


		// 增加和激活寻路网格
		inline void		activeFindPathCell( VecU2& cellPoint, FindPathCell21*& cell )
		{
			if ( isOutMap(cellPoint) )
			{
				cell = NULL;
				return;
			}

			// 得到当前寻路信息指针网格中的数据
			FindPathCell21*& currCell = mCellGrids.getGridDataByGridPointFast( cellPoint );

			// 判断数据是否是旧的,是则清空
			if ( currCell )
			{
				// 根据对象池的索引和对象池当前的创建数量来判断
				if ( currCell->poolIndex >= mCellPool->getMallocObjectCount() )
				{
					currCell->findPathState = FindPathCell21::FS_NULL;
					currCell->blockState = FindPathCell21::BS_NULL_CHECK;
					currCell = NULL;
				}
			}

			// 如果没有则创建
			if ( currCell == NULL )
			{
				// 从对象池中创建一个数据保存到网格中
				currCell = mCellPool->mallocObject();

				// 如果创建的数据之前已经在另一个网格中，则清空另一个网格数据
				if ( currCell->findPathState != FindPathCell21::FS_NULL )
				{
					if ( (currCell->x != cellPoint.x) || (currCell->z != cellPoint.y) )
					{
						mCellGrids.getGridDataByGridPointFast( currCell->x, currCell->z ) = NULL;
					}
				}

				// 初始化数据
				currCell->findPathState = FindPathCell21::FS_IDLE;
				currCell->blockState    = FindPathCell21::BS_NULL_CHECK;
				currCell->x = cellPoint.x; // 保存当前所在的网格坐标
				currCell->z = cellPoint.y; // 保存当前所在的网格坐标

				currCell->parent = NULL;

				currCell->poolIndex = mCellPool->getMallocObjectCount() - 1; // 保存当前在对象池中的索引

				currCell->binaryHeapIndex = 0;
				currCell->binaryHeapCost = 0;
				currCell->gCost = 0;
			}

			cell = currCell;
		}

		// 得到父节点到当前节点的移动消耗
		inline UInt					getMoveGCost( FindPathCell21*& cell, FindPathCell21*& parentCell )
		{
			if( (cell->x != parentCell->x) && (cell->z != parentCell->z) )
			{
				// 斜角移动
				return parentCell->gCost + 14;
			}
			else
			{
				// 直角移动
				return parentCell->gCost + 10;
			}

			return 0;
		}

		// 得到当前节点到目标点的移动消耗
		inline UInt					getMoveHCost( FindPathCell21*& cell, FindPathCell21*& destCell )
		{
			return abs( (Int)cell->x - (Int)destCell->x) * 10 + abs( (Int)cell->z - (Int)destCell->z) * 10;
		}

		//-----------------------------------------------------------------------
		inline Movedir              getMoveDir( VecU2& src , VecU2& des )
		{
			if(des.x > src.x)
			{
				if(des.y == src.y)
				{
					return md_right;
				}
				else 
					if(des.y > src.y)
					{
						return md_downright;
					}
					else 
						if(des.y < src.y)
						{
							return md_upright;
						}
			}
			else
				if(des.x < src.x)
				{
					if(des.y == src.y)
					{
						return md_left;
					}
					else 
						if(des.y > src.y)
						{
							return md_downleft;
						}
						else 
							if(des.y < src.y)
							{
								return md_upleft;
							}
				}
				else 
					if(des.x == src.x)
					{
						if(des.y == src.y)
						{
							DYNAMIC_ASSERT( false );
						}
						else 
							if(des.y > src.y)
							{
								return md_down;
							}
							else
								if(des.y < src.y)
								{   
									return md_up;
								}
					}

					return md_null;
		}

		//-----------------------------------------------------------------------
		inline Bool				checkBlock( FindPathCell21*& blockCell )
		{
			if ( blockCell == NULL )
			{
				// 边界则定义为静态碰撞
				return true;
			}

			Byte* blockFlag = mMapBlock.getGridDataByPoint( blockCell->x, blockCell->z );
			if(!blockFlag)
			{
				return true;
			}

			if((*blockFlag) == 0)
			{
				return false;
			}
			
			if ( *blockFlag & FindPathCell21::BS_IN_SELF_BLOCK )
			{
				return false;
			}
			else if ( *blockFlag & FindPathCell21::BS_IN_STATIC_BLOCK )
			{
				// 设置为静态障碍 
				blockCell->blockState = FindPathCell21::BS_IN_STATIC_BLOCK;
				return true;
			}
			else if ( *blockFlag & FindPathCell21::BS_IN_DYNAMIC_BLOCK )
			{
				// 设置为动态障碍 
				blockCell->blockState = FindPathCell21::BS_IN_DYNAMIC_BLOCK;
				return true;
			}

			return false;

			//else if ( blockCell->blockState == FindPathCell::BS_IN_STATIC_BLOCK  )
			//{
			//	// 如果周围一格为静态碰撞，则返回有障碍
			//	return true;
			//}
			//else if ( blockCell->blockState == FindPathCell::BS_IN_DYNAMIC_BLOCK  )
			//{
			//	// 如果周围一格为动态碰撞，则返回有障碍
			//	return true;
			//}
			//else if ( blockCell->blockState == FindPathCell::BS_NULL_CHECK)
			//{
			//	// 如果周围一格还没有检测，则检测

			//	Byte* blockFlag = mMapBlock->getGridDataByPoint( blockCell->x, blockCell->z );
			//	if(!blockFlag)
			//	{
			//		return true;
			//	}

			//	// TODO:
			//	// 需要优化
			//	if ( *blockFlag & BlockManager::BLF_TERRAIN_BLOCK )
			//	{
			//		// 设置为静态障碍 
			//		blockCell->blockState = FindPathCell::BS_IN_STATIC_BLOCK;
			//		return true;
			//	}
			//	else if ( *blockFlag & BlockManager::BLF_ENTITY_ALLSIDE_BLOCK )
			//	{
			//		// 设置为动态障碍 
			//		blockCell->blockState = FindPathCell::BS_IN_DYNAMIC_BLOCK;
			//		return true;
			//	}
			//	else if ( !(*blockFlag & BlockManager::BLF_STRUCTURE_PASSAGE) )
			//	{
			//		if ( *blockFlag & BlockManager::BLF_STRUCTURE_ALLSIDE_BLOCK )
			//		{
			//			// 设置为静态障碍 
			//			blockCell->blockState = FindPathCell::BS_IN_STATIC_BLOCK;
			//			return true;
			//		}
			//		else if ( *blockFlag & BlockManager::BLF_STRUCTURE_INSIDE_BLOCK )
			//		{
			//			// 设置为静态障碍 
			//			blockCell->blockState = FindPathCell::BS_IN_STATIC_BLOCK;
			//			return true;
			//		}
			//		else if ( *blockFlag & BlockManager::BLF_STRUCTURE_OUTSIDE_BLOCK )
			//		{
			//			// 设置为静态障碍
			//			blockCell->blockState = FindPathCell::BS_IN_STATIC_BLOCK;
			//			return true;
			//		}
			//	}
			//	else
			//	{
			//		// 设置为无障碍
			//		blockCell->blockState = FindPathCell::BS_OUT_BLOCK;
			//	}
			//}

			return false;
		}

		////-----------------------------------------------------------------------
		//// 检测是否是障碍
		//inline Bool             checkBlock( FindPathCell21* checkCell)
		//{
		//	//------------------------------------------------------------------------------------
		//	//@ 检测障碍
		//	//------------------------------------------------------------------------------------

		//	if(checkBlock(checkCell))
		//	{
		//		return true;
		//	} 

		//	return false;
		//}

	private:

		// 两点之间是否有障碍
		Bool                    isBlockBetweenTwoPos( Vec3 startPos, Vec3 endPos, Flt ignoreRange = 0 );

		void					setBlockGrid( RectF setBlockRect, BlockObject* ignoreBlockObject );

		void					setBlockGrid( RectF setBlockRect, FindPathCell21::BlockState blockState );

		void					clearBlockGrid();

	private:

		// 寻路类型
		PathFinderType                  mPathFinderType;

		// 地图障碍网格信息
		GridPool<Byte>					mMapBlock;
		UInt							mMapGridWidth;
		UInt							mMapGridHeight;

		UInt							mMapGridMaxWidth;
		UInt							mMapGridMaxHeight;

		Flt								mMapOneGridSize;
		Flt								mBlockObjRadius;

		// 寻路信息指针网格列表
		GridFast<FindPathCell21*>			mCellGrids;
		// 寻路信息网格数据池
		FastStructPool<FindPathCell21>*	mCellPool;

		// 开启列表, 使用二叉堆数据结构
		BinaryHeap<FindPathCell21*>*		mOpenList;

		// 寻路完整的全网格列表结果
		std::vector<VecU2>				mFindPathCellFullResult;
		// 得到完整的全路点列表结果
		std::vector<Vec3>			    mFindPathNodeFullResult;

		// 寻路合并后的网格列表结果
		std::vector<VecU2>				mFindPathCellCombineResult;
		// 得到合并后的全路点列表结果
		std::vector<Vec3>			    mFindPathNodeCombineResult;
		// 得到平滑后的全路点列表结果
		std::vector<Vec3>			    mFindPathNodeSmoothResult;

		// 寻路周围8网格偏移数组
		std::vector<VecI82>				mFindPathEightCellOffset;

		Scene*							mScene;


	};
}


#endif