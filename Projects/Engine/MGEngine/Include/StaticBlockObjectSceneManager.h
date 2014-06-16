/******************************************************************************/
#ifndef _STATICBLOCKOBJECTSCENEMANAGER_H_
#define _STATICBLOCKOBJECTSCENEMANAGER_H_
/******************************************************************************/
#include "BlockObjectSceneManager.h"

/******************************************************************************/


namespace MG
{


	/******************************************************************************/
	//
	//		StaticBlockObjectSceneManager
	//
	/******************************************************************************/

	class StaticBlockObjectSceneManager : public BlockObjectSceneManager
	{
	public:
		//----------------------------------------------------------------
		StaticBlockObjectSceneManager(Scene* scene);
		virtual ~StaticBlockObjectSceneManager();

		virtual void							Init( Vec2 leftBottomPos, Vec2 rightUpPos, Flt regineGridSize );

	protected:
		void									combinationBlockRect( UInt x, UInt y, std::vector<Rect>& blockRectList );

	};
}

/******************************************************************************/
#endif