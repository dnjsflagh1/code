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

		// ����Ѱ·����ͨ���ⲿ���ϰ�������Ϣ
		void											loadPathFinderMap( GridPool<Byte>*	mapBlock );
		// ж��Ѱ·����
		void											unLoadPathFinderMap();

		////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//Ѱ·
		Bool											findPath( Vector3 startPos, Vector3 targetPos, std::vector<UInt>& ignorePosList, std::vector<PathCell>& pathList, Int findPathObjectCellDiameter = 1, Int findCellRadius = 0/*, bool isIgnoreDynamicBlock = false*/ );

		//Ѱ·
		Bool											findPath( PathCell startCell, PathCell targetCell, std::vector<UInt>& ignorePosList, std::vector<PathCell>& pathList, Int findPathObjectCellDiameter = 1, Int findCellRadius = 0/*, bool isIgnoreDynamicBlock = false*/ );

		//Ѱ·
		Bool											findPath( Int startX, Int startZ, Int targetX, Int targetZ, std::vector<UInt>& ignorePosList, std::vector<PathCell>& pathList, Int findPathObjectCellDiameter = 1, Int findRadius = 0/*, bool isIgnoreDynamicBlock = false*/ );

		////////////////////////////////////////////////////////////////////////////////////////////////////////////

        // �õ��ƶ��ķ���
        movedir                                         getMoveDir( PathCell& src , PathCell& des );

		// Ѱ·�ó���·��Listת��Ϊ��������List
		// ����List����л�ȥ���м䷽��һ�µĵ�
		// ͨ����ʼ����յ������λ�ã��Է���ֵ����ƫ��
		void											getWorldPosListByPathList( Vector3 startPos, Vector3 targetPos, std::vector<PathCell>& pathList, std::vector<Vector3>& movePosList, Bool isOffset = false );

		// ����Ѱ··��ת��Ϊ��������
		Vector3											getWorldPosByPathPoint( Int x,  Int z );

		// ������������ת��ΪѰ··��
		PathCell										getPathPointByWorldPos( Vector3 pos );

		// ����Ѱ··�����껻ΪѰ·����
		Int												getPathIndexByPathPoint( Int cellX, Int cellZ );

		// �ѵ�ǰ�ƶ���ת��Ϊ���ĵ�
		void											getCenterPosByMovePos( std::vector<Vector3>& movePosList, Int findPathObjectCellDiameter = 1, IBlockManager::VertexPos vertexPos = IBlockManager::VERTEX_MAX );

		// ����Ѱ·���񵥸����ӵĳ���
		Flt												getTileSize();

		////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// ��Ѱ·�ó���·�����ƽ������
		// �ϲ�����
		void        									pathSmooth( std::vector<Vector3>& movePosList, std::vector<UInt>& ignorePosList, Int findPathObjectCellDiameter = 1 );

		// ����֮���Ƿ����ϰ�
		Bool											isBlockBetweenTwoPos( Vector3 startPos, Vector3 endPos, std::vector<UInt>& ignorePosList, Int findPathObjectCellDiameter = 1 );

		// ����SceneNode֮��ľ����Ƿ�С������SceneNode�뾶�ĺ�
		Bool											senceNode2DIsIntersect( ISceneNode* sceneNode1, ISceneNode* sceneNode2,  Vector3  detectionCollidePos = Vector3(0,0,0) );

	protected:

		//�Ƿ����ϰ�
		bool											isBlock( Int currX, Int currZ, std::vector<UInt>& ignorePosList, Int findPathObjectCellDiameter = 1, IBlockManager::VertexPos vertexPos = IBlockManager::VERTEX_LEFTDOWN );
		
		//�����Ƿ��ڰ뾶֮��
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