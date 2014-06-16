/******************************************************************************/
#ifndef _IBLOCKOBJECTSCENEMANAGER_H_
#define _IBLOCKOBJECTSCENEMANAGER_H_
/******************************************************************************/
#include "ISceneNodeAction.h"
/******************************************************************************/


namespace MG
{

	/******************************************************************************/
	//
	//		IBlockObjectSceneManager
	//
	/******************************************************************************/

	class IBlockObjectSceneManager
	{
	public:

		//----------------------------------------------------------------

		virtual void							Init( Vec2 leftBottomPos, Vec2 rightUpPos, Flt regineGridSize ) = 0;
		//virtual void							addBlockObject( BlockObject* blockObject ) = 0;
		//virtual void							removeBlockObject( BlockObject* blockObject ) = 0;

		//virtual void							getBlockObjectList( MG::RectF rect, std::map<BlockObject*, BlockObject*>& blockObjectList ) = 0;
		//virtual void							getBlockObjectList( Vec3 pos, std::map<BlockObject*, BlockObject*>& blockObjectList ) = 0;

		//virtual void							getRegionRectList( MG::RectF rect, std::map<UInt, RegionGrid*>& regionGridList ) = 0;
		//virtual RegionGrid*						getRegionRect( Vec3 pos ) = 0;

		virtual Bool							isHasBlockObject( MG::RectF rect ) = 0;
		virtual Bool							isHasBlockObject( Vec3 pos ) = 0;

		virtual	Bool							isBlockBetweenTwoPos( IDynamicBlockObject* ignoreObj, Vec3 startPos, 
													Vec3 endPos, 
													Flt blockCheckCellRadius, 
													IDynamicBlockObject*& collideBlockObject, 
													ISceneNodeGridLineMoveToAction::MoveToPathFindType moveToPathFindType, 
													Flt checkBlcokLenght = 0 ) = 0;

		//virtual void							refreshBlock( BlockObject* blockObject ) = 0;
	};
}

/******************************************************************************/
#endif