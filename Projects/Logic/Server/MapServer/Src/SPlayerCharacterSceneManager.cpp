
/******************************************************************************/

#include "stdafx.h"
#include "SPlayerCharacterSceneManager.h"

/******************************************************************************/
namespace MG
{
	//-----------------------------------------------------------------------------
	SPlayerCharacterSceneManager::SPlayerCharacterSceneManager()
	{
	}

	//-----------------------------------------------------------------------------
	SPlayerCharacterSceneManager::~SPlayerCharacterSceneManager()
	{
	}

	GameObjectIndexIdInSceneType SPlayerCharacterSceneManager::addPlayerCharacter( SPlayerCharacterPtr& playerCharPtr )
	{
		return 0;
	}

	//-----------------------------------------------------------------------------
	void SPlayerCharacterSceneManager::removePlayerCharacter( GameObjectIndexIdInSceneType objIndex )
	{

	}

	//-----------------------------------------------------------------------------
	Bool SPlayerCharacterSceneManager::hasPlayerCharacter( GameObjectIndexIdInSceneType objIndex )
	{
		return true;
	}

	//-----------------------------------------------------------------------------
	Bool SPlayerCharacterSceneManager::getPlayerCharacter( SPlayerCharacterPtr& ptr, GameObjectIndexIdInSceneType objIndex)
	{
		return true;
	}

	//-----------------------------------------------------------------------------
	void SPlayerCharacterSceneManager::removeAllPlayerCharacter()
	{

	}

	//-----------------------------------------------------------------------------

}	//namespace MG