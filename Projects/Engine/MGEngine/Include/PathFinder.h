/******************************************************************************/
#ifndef __PATHFINDER_H__
#define __PATHFINDER_H__
/******************************************************************************/
#include <stdio.h>
#include <cstdlib>
#include <vector>
#include "ISceneNode.h"
#include "IEntity.h"
#include "IPathFinder.h"
#include "GridPool.h"
#include "BlockManager.h"
/******************************************************************************/

namespace MG
{

	//-----------------------------------------------------------------------
#pragma pack (push)
#pragma pack (1)

	struct CellCost
	{
		//U16 fCost;
		U16 gCost;
		U16 hCost;

		CellCost():/*fCost(0),*/gCost(0),hCost(0)
		{

		}
	};

	//-----------------------------------------------------------------------
	struct OpenPos
	{
		U16 x;
		U16 z;

		I8 parentOffsetX;
		I8 parentOffsetZ;

		Int inOpenListIndex;

		OpenPos():x(0),z(0),parentOffsetX(0),parentOffsetZ(0),inOpenListIndex(0)
		{

		}
	};

	//-----------------------------------------------------------------------
	struct PathCell
	{
		U16 x;
		U16 z;

		PathCell():x(0),z(0)
		{

		}

		PathCell(U16 fx, U16 fz):x(fx),z(fz)
		{

		}

		inline PathCell& operator=(const PathCell& A)
		{
			x = A.x;
			z = A.z;
			return *this;
		}
	};

#pragma pack (pop)


	//-----------------------------------------------------------------------
	class PathFinder : public IPathFinder
	{
	public:

		//-----------------------------------------------------------------------
		enum movedir
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

		PathFinder();
		~PathFinder();

		// 加载寻路数据通过外部的障碍网格信息
		void											loadPathFinderMap( GridPool<Byte>*	mapBlock );
		// 卸载寻路数据
		void											unLoadPathFinderMap();

		////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//寻路
		Bool											findPath( Vector3 startPos, Vector3 targetPos, std::vector<UInt>& ignorePosList, std::vector<PathCell>& pathList, Int findPathObjectCellDiameter = 1, Int findCellRadius = 0/*, bool isIgnoreDynamicBlock = false*/ );

		//寻路
		Bool											findPath( PathCell startCell, PathCell targetCell, std::vector<UInt>& ignorePosList, std::vector<PathCell>& pathList, Int findPathObjectCellDiameter = 1, Int findCellRadius = 0/*, bool isIgnoreDynamicBlock = false*/ );

		//寻路
		Bool											findPath( Int startX, Int startZ, Int targetX, Int targetZ, std::vector<UInt>& ignorePosList, std::vector<PathCell>& pathList, Int findPathObjectCellDiameter = 1, Int findRadius = 0/*, bool isIgnoreDynamicBlock = false*/ );

		////////////////////////////////////////////////////////////////////////////////////////////////////////////

        // 得到移动的方向
        movedir                                         getMoveDir( PathCell& src , PathCell& des );

		// 寻路得出的路点List转换为世界坐标List
		// 坐标List结果中会去除中间方向一致的点
		// 通过起始点和终点的坐标位置，对返回值进行偏移
		void											getWorldPosListByPathList( Vector3 startPos, Vector3 targetPos, std::vector<PathCell>& pathList, std::vector<Vector3>& movePosList, Bool isOffset = false );

		// 单个寻路路点转换为世界坐标
		Vector3											getWorldPosByPathPoint( Int x,  Int z );

		// 单个世界坐标转换为寻路路点
		PathCell										getPathPointByWorldPos( Vector3 pos );

		// 单个寻路路点坐标换为寻路索引
		Int												getPathIndexByPathPoint( Int cellX, Int cellZ );

		// 把当前移动点转化为中心点
		void											getCenterPosByMovePos( std::vector<Vector3>& movePosList, Int findPathObjectCellDiameter = 1, IBlockManager::VertexPos vertexPos = IBlockManager::VERTEX_MAX );

		// 单个寻路网格单个格子的长度
		Flt												getTileSize();

		////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// 对寻路得出的路点进行平滑处理
		// 合并折现
		void        									pathSmooth( std::vector<Vector3>& movePosList, std::vector<UInt>& ignorePosList, Int findPathObjectCellDiameter = 1 );

		// 两点之间是否有障碍
		Bool											isBlockBetweenTwoPos( Vector3 startPos, Vector3 endPos, std::vector<UInt>& ignorePosList, Int findPathObjectCellDiameter = 1 );

		// 两个SceneNode之间的距离是否小于两个SceneNode半径的和
		Bool											senceNode2DIsIntersect( ISceneNode* sceneNode1, ISceneNode* sceneNode2,  Vector3  detectionCollidePos = Vector3(0,0,0) );

	protected:

		//是否有障碍
		bool											isBlock( Int currX, Int currZ, std::vector<UInt>& ignorePosList, Int findPathObjectCellDiameter = 1, IBlockManager::VertexPos vertexPos = IBlockManager::VERTEX_LEFTDOWN );
		
		//坐标是否在半径之内
		Bool											isInDiameter( Int currX, Int currZ, std::vector<UInt>& ignorePosList, Int findPathObjectCellDiameter, IBlockManager::VertexPos vertexPos = IBlockManager::VERTEX_LEFTDOWN );

	private:

	
		GridPool<Byte>									mOpenAndCloseList;
		GridPool<UInt>									mOpenList;

		GridPool<CellCost>								mCellCostList;
		GridPool<OpenPos>								mOpenPosList;

		GridPool<Byte>*									mMapBlock;

		UInt											mPathFindNum;
		UInt											mOnOpenList;
		UInt											mOnCloseList;
	};
}


#endif