/******************************************************************************/
#include "stdafx.h"
#include "GameObjectGroup.h"
#include "GameObject.h"
/******************************************************************************/

namespace MG
{
	//-----------------------------------------------------------------------
	GameObjectGroup::GameObjectGroup()
	{

	}

	//-----------------------------------------------------------------------
	GameObjectGroup::~GameObjectGroup()
	{

	}

	//-----------------------------------------------------------------------
	void GameObjectGroup::addGameObject(GameObject* gameObject)
	{
		if(!gameObject)
		{
			return;
		}

		mGameObjectList[gameObject->getID()] = gameObject;
	}

	//-----------------------------------------------------------------------
	void GameObjectGroup::delGameObject(GameObject *gameObject)
	{
		std::map<IdType, GameObject*>::iterator it = mGameObjectList.find(gameObject->getID());
		if(it == mGameObjectList.end())
		{
			return;
		}

		mGameObjectList.erase(it);
	}

}