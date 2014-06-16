/******************************************************************************/
#ifndef _DYNAMICBLOCKOBJECTSCENEMANAGER_H_
#define _DYNAMICBLOCKOBJECTSCENEMANAGER_H_
/******************************************************************************/
#include "BlockObjectSceneManager.h"

/******************************************************************************/


namespace MG
{


	/******************************************************************************/
	//
	//		DynamicBlockObjectSceneManager
	//
	/******************************************************************************/

	class DynamicBlockObjectSceneManager : public BlockObjectSceneManager
	{
	public:
		//----------------------------------------------------------------
		DynamicBlockObjectSceneManager(Scene* scene);
		virtual ~DynamicBlockObjectSceneManager();
	};
}

/******************************************************************************/
#endif