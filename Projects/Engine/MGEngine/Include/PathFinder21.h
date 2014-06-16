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
			FS_IDLE				= 1,  // ����״̬
			FS_IN_OPEN_LIST		= 2,  // �ڿ����б���
			FS_IN_CLOSE_LIST	= 3,  // �ڹر��б���
		};

		//-----------------------------------------------------------------------
		enum BlockState
		{
			BS_NULL_CHECK       = 0,
			BS_OUT_BLOCK        = 1,  // ���ϰ�����
			BS_IN_SELF_BLOCK	= 2,
			BS_IN_STATIC_BLOCK	= 3,  // �ھ�̬�ϰ���
			BS_IN_DYNAMIC_BLOCK	= 4,  // �ڶ�̬�ϰ���
		};

		// Ѱ·״̬
		Byte findPathState;
		// �ϰ�״̬
		Byte blockState;

		// ������������λ��
		UInt x;
		UInt z;

		// ���ڵ���������
		FindPathCell21* parent;

		// ���������
		UInt poolIndex;

		/** 
		���������,
		�ɶ���ѹ������Զ�ά�����޸ġ�
		*/
		UInt binaryHeapIndex;

		/** 
		����������涨���ֶ�,���ڱȽϴ�С.
		����������Ϊ���ƶ����� : binaryHeapCost = gCost + hCost
		*/
		U16 binaryHeapCost;
		/// ��㵽��ǰ����ƶ�����,���������·��������
		U16 gCost;
		/// ��ǰ�㵽�յ���ƶ�����,ʹ������ʽ�����ٷ���������
		//U16 hCost;

	};

#pragma pack (pop)


	/******************************************************************************/
	// Ѱ·�㷨
	/**
	1������ʼ����ӵ������б�
	2���ظ����µĹ�����
	a) Ѱ�ҿ����б���Fֵ��͵ĸ��ӡ����ǳ���Ϊ��ǰ��
	b) �����л����ر��б�
	c) �����ڵ�8���е�ÿһ����
	* ���������ͨ�������Ѿ��ڹر��б��У��Թ�������֮���¡�
	* ��������ڿ����б��У�������ӽ�ȥ���ѵ�ǰ����Ϊ��һ��ĸ��ڵ㡣��¼��һ���F,G,��Hֵ��
	* ������Ѿ��ڿ����б��У���GֵΪ�ο�����µ�·���Ƿ���á����͵�Gֵ��ζ�Ÿ��õ�·����
	������������Ͱ���һ��ĸ��ڵ�ĳɵ�ǰ�񣬲������¼�����һ���G��Fֵ��
	����㱣����Ŀ����б�Fֵ���򣬸ı�֮���������Ҫ���¶Կ����б�����
	d) ֹͣ������
	* ��Ŀ�����ӽ��˹ر��б�(ע��)����ʱ��·�����ҵ�������
	* û���ҵ�Ŀ��񣬿����б��Ѿ����ˡ���ʱ��·�������ڡ�
	3.����·������Ŀ���ʼ������ÿһ��ĸ��ڵ��ƶ�ֱ���ص���ʼ��
	*/
	/******************************************************************************/
	class PathFinder21 : public IPathFinder
	{
	public:
		//-----------------------------------------------------------------------
		// Ѱ·����
		enum PathFinderType
		{
			PT_NULL,
			PT_ALWAYS_NEAREST,  // �����������
			PT_SPREAD_SEARCH,   // ��չʽѰ·
		};

		//-----------------------------------------------------------------------
		// �ƶ�����
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

		
		// ����Ѱ·����ͨ���ⲿ���ϰ�������Ϣ
		void						load(  Scene* scene, UInt pathFinderGridWidth, UInt pathFinderGridHeight );
		// ж��Ѱ·����
		void						unLoad();
		// �Ƿ��Ѿ�����
		Bool						isLoaded();
		// ����Ѱ·����
		void						setType ( PathFinderType type );

		////////////////////////////////////////////////////////////////////////////////////////////////////////////

		/** Ѱ·����
		@remarks
			���Ը���һ�������ж�Ѱ·����
		@param startPos
			��ʼѰ·������
		@param targetPos
			Ŀ��Ѱ·������
		@param findPathRect
			��������ϵ��Ѱ·���Χ
		@param ignoreBlockRect
			��������ϵ�ĺ����ϰ�Ѱ·���Χ
		@param checkMaxPath
			������������Ѱ··�����ȣ����Ϊ-1���ʾ���޳�
		@param checkMaxDynamicBlock
			������������⼸�ζ�̬�ϰ����˳�Ѱ·���㣬���Ϊ-1���ʾ�����ơ�
		@returns
			0 : ��ʾѰ·����
			1 : ��ʾ����ҪѰ·
			2 : ��ʾѰ·�ɹ�
			3 : ��ʾѰ·�����Ѱ··���˳�
			4 : ��ʾѰ·��ⳬ���޶���̬�ϰ��������˳�
			@par
		//
		*/
		PathFindingResult           findPath( BlockObject* pathFinder,
			Vec3 startPos,
			Vec3 targetPos, 
			RectF findPathRect,
			Int checkMaxPath = -1, 
			Int checkMaxDynamicBlock = -1 );

		// ��������ת��Ϊ��������
		void						convertWorldPositionToGridPoint( Vec3 startPos, VecU2& CellPoint );


		// �õ�Ѱ·���������Ľ�� ,  ע���ǵ����
		std::vector<VecU2>&			getFullFindCellPathResult();
		// �õ�Ѱ·�ڵ������Ľ�� ,  ����
		std::vector<Vec3>&		    getFullFindPathNodeResult();

		// �õ�Ѱ·����ϲ��Ľ�� ,  ����
		std::vector<VecU2>&			getCombineFindCellPathResult();
		// �õ�Ѱ·�ڵ�ϲ��Ľ�� ,  ����
		std::vector<Vec3>&		    getCombineFindPathNodeResult();
		// �õ�Ѱ·�ڵ�ƽ����Ľ�� ,����
		std::vector<Vec3>&		    getSmoothFindPathNodeResult();

		////////////////////////////////////////////////////////////////////////////////////////////////////////////

	protected:

		// ���������Ƿ��ڵ�ͼ����
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


		// ���Ӻͼ���Ѱ·����
		inline void		activeFindPathCell( VecU2& cellPoint, FindPathCell21*& cell )
		{
			if ( isOutMap(cellPoint) )
			{
				cell = NULL;
				return;
			}

			// �õ���ǰѰ·��Ϣָ�������е�����
			FindPathCell21*& currCell = mCellGrids.getGridDataByGridPointFast( cellPoint );

			// �ж������Ƿ��Ǿɵ�,�������
			if ( currCell )
			{
				// ���ݶ���ص������Ͷ���ص�ǰ�Ĵ����������ж�
				if ( currCell->poolIndex >= mCellPool->getMallocObjectCount() )
				{
					currCell->findPathState = FindPathCell21::FS_NULL;
					currCell->blockState = FindPathCell21::BS_NULL_CHECK;
					currCell = NULL;
				}
			}

			// ���û���򴴽�
			if ( currCell == NULL )
			{
				// �Ӷ�����д���һ�����ݱ��浽������
				currCell = mCellPool->mallocObject();

				// �������������֮ǰ�Ѿ�����һ�������У��������һ����������
				if ( currCell->findPathState != FindPathCell21::FS_NULL )
				{
					if ( (currCell->x != cellPoint.x) || (currCell->z != cellPoint.y) )
					{
						mCellGrids.getGridDataByGridPointFast( currCell->x, currCell->z ) = NULL;
					}
				}

				// ��ʼ������
				currCell->findPathState = FindPathCell21::FS_IDLE;
				currCell->blockState    = FindPathCell21::BS_NULL_CHECK;
				currCell->x = cellPoint.x; // ���浱ǰ���ڵ���������
				currCell->z = cellPoint.y; // ���浱ǰ���ڵ���������

				currCell->parent = NULL;

				currCell->poolIndex = mCellPool->getMallocObjectCount() - 1; // ���浱ǰ�ڶ�����е�����

				currCell->binaryHeapIndex = 0;
				currCell->binaryHeapCost = 0;
				currCell->gCost = 0;
			}

			cell = currCell;
		}

		// �õ����ڵ㵽��ǰ�ڵ���ƶ�����
		inline UInt					getMoveGCost( FindPathCell21*& cell, FindPathCell21*& parentCell )
		{
			if( (cell->x != parentCell->x) && (cell->z != parentCell->z) )
			{
				// б���ƶ�
				return parentCell->gCost + 14;
			}
			else
			{
				// ֱ���ƶ�
				return parentCell->gCost + 10;
			}

			return 0;
		}

		// �õ���ǰ�ڵ㵽Ŀ�����ƶ�����
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
				// �߽�����Ϊ��̬��ײ
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
				// ����Ϊ��̬�ϰ� 
				blockCell->blockState = FindPathCell21::BS_IN_STATIC_BLOCK;
				return true;
			}
			else if ( *blockFlag & FindPathCell21::BS_IN_DYNAMIC_BLOCK )
			{
				// ����Ϊ��̬�ϰ� 
				blockCell->blockState = FindPathCell21::BS_IN_DYNAMIC_BLOCK;
				return true;
			}

			return false;

			//else if ( blockCell->blockState == FindPathCell::BS_IN_STATIC_BLOCK  )
			//{
			//	// �����Χһ��Ϊ��̬��ײ���򷵻����ϰ�
			//	return true;
			//}
			//else if ( blockCell->blockState == FindPathCell::BS_IN_DYNAMIC_BLOCK  )
			//{
			//	// �����Χһ��Ϊ��̬��ײ���򷵻����ϰ�
			//	return true;
			//}
			//else if ( blockCell->blockState == FindPathCell::BS_NULL_CHECK)
			//{
			//	// �����Χһ��û�м�⣬����

			//	Byte* blockFlag = mMapBlock->getGridDataByPoint( blockCell->x, blockCell->z );
			//	if(!blockFlag)
			//	{
			//		return true;
			//	}

			//	// TODO:
			//	// ��Ҫ�Ż�
			//	if ( *blockFlag & BlockManager::BLF_TERRAIN_BLOCK )
			//	{
			//		// ����Ϊ��̬�ϰ� 
			//		blockCell->blockState = FindPathCell::BS_IN_STATIC_BLOCK;
			//		return true;
			//	}
			//	else if ( *blockFlag & BlockManager::BLF_ENTITY_ALLSIDE_BLOCK )
			//	{
			//		// ����Ϊ��̬�ϰ� 
			//		blockCell->blockState = FindPathCell::BS_IN_DYNAMIC_BLOCK;
			//		return true;
			//	}
			//	else if ( !(*blockFlag & BlockManager::BLF_STRUCTURE_PASSAGE) )
			//	{
			//		if ( *blockFlag & BlockManager::BLF_STRUCTURE_ALLSIDE_BLOCK )
			//		{
			//			// ����Ϊ��̬�ϰ� 
			//			blockCell->blockState = FindPathCell::BS_IN_STATIC_BLOCK;
			//			return true;
			//		}
			//		else if ( *blockFlag & BlockManager::BLF_STRUCTURE_INSIDE_BLOCK )
			//		{
			//			// ����Ϊ��̬�ϰ� 
			//			blockCell->blockState = FindPathCell::BS_IN_STATIC_BLOCK;
			//			return true;
			//		}
			//		else if ( *blockFlag & BlockManager::BLF_STRUCTURE_OUTSIDE_BLOCK )
			//		{
			//			// ����Ϊ��̬�ϰ�
			//			blockCell->blockState = FindPathCell::BS_IN_STATIC_BLOCK;
			//			return true;
			//		}
			//	}
			//	else
			//	{
			//		// ����Ϊ���ϰ�
			//		blockCell->blockState = FindPathCell::BS_OUT_BLOCK;
			//	}
			//}

			return false;
		}

		////-----------------------------------------------------------------------
		//// ����Ƿ����ϰ�
		//inline Bool             checkBlock( FindPathCell21* checkCell)
		//{
		//	//------------------------------------------------------------------------------------
		//	//@ ����ϰ�
		//	//------------------------------------------------------------------------------------

		//	if(checkBlock(checkCell))
		//	{
		//		return true;
		//	} 

		//	return false;
		//}

	private:

		// ����֮���Ƿ����ϰ�
		Bool                    isBlockBetweenTwoPos( Vec3 startPos, Vec3 endPos, Flt ignoreRange = 0 );

		void					setBlockGrid( RectF setBlockRect, BlockObject* ignoreBlockObject );

		void					setBlockGrid( RectF setBlockRect, FindPathCell21::BlockState blockState );

		void					clearBlockGrid();

	private:

		// Ѱ·����
		PathFinderType                  mPathFinderType;

		// ��ͼ�ϰ�������Ϣ
		GridPool<Byte>					mMapBlock;
		UInt							mMapGridWidth;
		UInt							mMapGridHeight;

		UInt							mMapGridMaxWidth;
		UInt							mMapGridMaxHeight;

		Flt								mMapOneGridSize;
		Flt								mBlockObjRadius;

		// Ѱ·��Ϣָ�������б�
		GridFast<FindPathCell21*>			mCellGrids;
		// Ѱ·��Ϣ�������ݳ�
		FastStructPool<FindPathCell21>*	mCellPool;

		// �����б�, ʹ�ö�������ݽṹ
		BinaryHeap<FindPathCell21*>*		mOpenList;

		// Ѱ·������ȫ�����б���
		std::vector<VecU2>				mFindPathCellFullResult;
		// �õ�������ȫ·���б���
		std::vector<Vec3>			    mFindPathNodeFullResult;

		// Ѱ·�ϲ���������б���
		std::vector<VecU2>				mFindPathCellCombineResult;
		// �õ��ϲ����ȫ·���б���
		std::vector<Vec3>			    mFindPathNodeCombineResult;
		// �õ�ƽ�����ȫ·���б���
		std::vector<Vec3>			    mFindPathNodeSmoothResult;

		// Ѱ·��Χ8����ƫ������
		std::vector<VecI82>				mFindPathEightCellOffset;

		Scene*							mScene;


	};
}


#endif