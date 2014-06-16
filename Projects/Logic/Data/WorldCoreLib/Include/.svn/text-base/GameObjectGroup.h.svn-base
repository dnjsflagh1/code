/******************************************************************************/
#ifndef _GAMEOBJECTGROUP_H_
#define _GAMEOBJECTGROUP_H_
/******************************************************************************/
#include "WorldCorePreqs.h"
/******************************************************************************/
namespace MG
{
	class GameObjectGroup
	{
	public:
		GameObjectGroup();
		~GameObjectGroup();

		void										addGameObject(GameObject* gameObject);
		void										delGameObject(GameObject* gameObject);

	protected:
		std::map<IdType, GameObject*>				mGameObjectList;
	};
}
/******************************************************************************/
#endif