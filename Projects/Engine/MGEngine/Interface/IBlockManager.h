/******************************************************************************/
#ifndef _IBLOCKMANAGER_H_
#define _IBLOCKMANAGER_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************/
	//经过的网格障碍
	/******************************************************************************/
	struct PassGridBlock
	{
		UInt passGridBlockIndex;
		Vec3 passGridBlockPos;
	};


	/******************************************************************************/
	//游戏Action管理
	/******************************************************************************/
	class IBlockManager
	{
	public:

		enum VertexPos
		{
			VERTEX_LEFTUP,
			VERTEX_RIGHTUP,
			VERTEX_RIGHTDOWN,
			VERTEX_LEFTDOWN,
			VERTEX_MAX,
		};

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /// 加载静态障碍
        virtual void					loadStaticBlock( Vec2 leftBottomPos, Vec2 rightUpPos ) = 0;
        /// 加载动态障碍
        virtual void					loadDynamicBlock( Vec2 leftBottomPos, Vec2 rightUpPos ) = 0;
        /// 释放所有障碍数据
        virtual void					unLoad() = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// 得到动态障碍网格大小
		virtual	Flt						getDynamicBlockGridSize() = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////

		/// 是否为静态障碍
		virtual Bool					isStaticBlock( Vec3 currPos ) = 0;

		// 是否为动态障碍，依据半径
		virtual Bool					isDynamicBlockByRadius( Vec3 currPos, Int findPathObjectCellDiameter, VertexPos vertexPos = VERTEX_MAX, IDynamicBlockObject* ignoreObj = NULL ) = 0;
		
        // 检测开始点到结束点之间是否有障碍
        virtual Bool					isDynamicBlockBetweenTwoPos( IDynamicBlockObject* ignoreObj, Vec3 startPos, Vec3 endPos, UInt& blockIndex, Int findPathObjectCellDiameter = 1, Bool isPrecise = false  ) = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////

		virtual	Bool					getPosNearestAccessiblePosForDir( const Vec3 centerPos, Vec3 dir, Flt disLen, Int findPathObjectCellDiameter, Vec3& nearestAccessiblePos ) = 0;

        // 得到最近的可进入点
        virtual	Bool			        getPosNearestAccessiblePos( const Vec3 centerPos, Int findPathObjectCellDiameter, Vec3& nearestAccessiblePos, IDynamicBlockObject* ignoreObj ) = 0;
		// 得到最近的可进入点
		virtual Bool					getPosNearestAccessiblePos( const Vec3 centerPos, Vec3 dir, Flt disLen, Int findPathObjectCellDiameter, Vec3& nearestAccessiblePos ) = 0;
		// 得到最近的可进入距离
		virtual Bool					getPosNearestAccessibleDis( const Vec3 centerPos, Vec3 dir, Int findPathObjectCellDiameter, Flt& nearestAccessibleDis ) = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// 得到经过障碍网格
		virtual Bool					getPassBlockGrid( Vec3 startPos, Vec3 endPos, std::vector<PassGridBlock>& passBlockGridList, UInt diameterSize = 1 ) = 0;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////

		// 得到动态障碍对象，根据所指定的网格索引
		virtual IDynamicBlockObject*	getDynamicBlockObjectFromGridBlock(UInt gridIndex) = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////

	};

}

/******************************************************************************/
#endif