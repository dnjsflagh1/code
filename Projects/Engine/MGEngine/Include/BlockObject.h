/******************************************************************************/
#ifndef _BLOCKOBJECT_H_
#define _BLOCKOBJECT_H_
/******************************************************************************/
#include "EnginePreqs.h"
#include "BlockObjectSceneManager.h"

/******************************************************************************/


namespace MG
{

	/******************************************************************************/
	//
	//		BlockObject
	//
	/******************************************************************************/

	class BlockObject
	{
	public:

		BlockObject();
		virtual ~BlockObject();

		//----------------------------------------------------------------
		void													setBlockPosRect( RectF blockPosRect );
		RectF													getBlockPosRect();

		void													setCurrRegionGrid( std::map<UInt, BlockObjectSceneManager::RegionGrid*>& currRegionGridList );
		std::map<UInt, BlockObjectSceneManager::RegionGrid*>*	getCurrRegionGrid();	
		
		//----------------------------------------------------------------

		void													addCurrRegionGrid( std::map<UInt, BlockObjectSceneManager::RegionGrid*>& currRegionGridList );
		void													removeCurrRegionGrid();

	protected:

		// 世界坐标系的所占区域米大小
		RectF													mBlockPosRect;
		// 在管理者中所占的网格
		std::map<UInt, BlockObjectSceneManager::RegionGrid*>	mCurrRegionGridList;

	};
}

#endif