
/******************************************************************************/

#ifndef _S_PLAYER_CHARACTER_SCENE_MANAGER_H_
#define _S_PLAYER_CHARACTER_SCENE_MANAGER_H_

/******************************************************************************/

#include "MapServerPreqs.h"

/******************************************************************************/

namespace MG
{
	class SPlayerCharacterSceneManager
	{
	public:
		SPlayerCharacterSceneManager();
		~SPlayerCharacterSceneManager();

		GameObjectIndexIdInSceneType	addPlayerCharacter( SPlayerCharacterPtr& playerCharPtr );
		void 							removePlayerCharacter( GameObjectIndexIdInSceneType objIndex );
		Bool 							hasPlayerCharacter( GameObjectIndexIdInSceneType objIndex );
		Bool 							getPlayerCharacter( SPlayerCharacterPtr& ptr, GameObjectIndexIdInSceneType objIndex);
		void 							removeAllPlayerCharacter();

	};
}

#endif	//_S_PLAYER_CHARACTER_SCENE_MANAGER_H_