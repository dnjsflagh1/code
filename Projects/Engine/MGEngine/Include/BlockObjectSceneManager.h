/******************************************************************************/
#ifndef _BLOCKOBJECTSCENEMANAGER_H_
#define _BLOCKOBJECTSCENEMANAGER_H_
/******************************************************************************/
#include "EnginePreqs.h"
#include "GridPool.h"
#include "IBlockObjectSceneManager.h"

/******************************************************************************/


namespace MG
{


/******************************************************************************/
//
//		BlockObjectSceneManager
//
/******************************************************************************/

	class BlockObjectSceneManager : public IBlockObjectSceneManager
	{
	public:

		struct RegionGrid
		{
			std::map<BlockObject*, BlockObject*> mBlockObjectList;
		};

	//----------------------------------------------------------------

		class RegionGridList : public GridPool<RegionGrid>
		{
			virtual void        clearWorldGrid(Byte memSetNum = 0)
			 {
				 RegionGrid* gridData = NULL;
				 UInt clearNum = mAllocGroupSize;

				 for(UInt i = 0; i < mAllocGroupNum; ++i)
				 {
					 if(i == mAllocGroupNum - 1)
					 {
						 clearNum = mSurplusGridNum;
					 }

					 for(UInt j = 0; j < clearNum; ++j)
					 {
						 mGridDataGroupList[i][j].mBlockObjectList.clear();
					 }
				 }
			 }
		};

	//----------------------------------------------------------------

		BlockObjectSceneManager(Scene* scene);
		virtual ~BlockObjectSceneManager();

	//----------------------------------------------------------------

		virtual void							Init( Vec2 leftBottomPos, Vec2 rightUpPos, Flt regineGridSize );

		virtual void							addBlockObject( BlockObject* blockObject );
		virtual void							removeBlockObject( BlockObject* blockObject );

		virtual void							getBlockObjectList( MG::RectF rect, std::map<BlockObject*, BlockObject*>& blockObjectList );
		virtual void							getBlockObjectList( Vec3 pos, std::map<BlockObject*, BlockObject*>& blockObjectList );

		virtual void							getRegionRectList( MG::RectF rect, std::map<UInt, RegionGrid*>& regionGridList );
		virtual RegionGrid*						getRegionRect( Vec3 pos );

		virtual Bool							isHasBlockObject( MG::RectF rect );
		virtual Bool							isHasBlockObject( Vec3 pos );

		virtual void							refreshBlock( BlockObject* blockObject );

		virtual	Bool							isBlockBetweenTwoPos( IDynamicBlockObject* ignoreObj, Vec3 startPos, 
												Vec3 endPos, 
												Flt blockCheckRadius, 
												IDynamicBlockObject*& collideBlockObject, 
												ISceneNodeGridLineMoveToAction::MoveToPathFindType moveToPathFindType, 
												Flt checkBlcokLenght = 0 );

	protected:

		/*GridPool<RegionGrid>					mRegionGridList;*/
		RegionGridList							mRegionGridList;
		Scene*									mScene;
	};
}

/******************************************************************************/
#endif