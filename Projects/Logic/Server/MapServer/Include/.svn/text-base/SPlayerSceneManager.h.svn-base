
/******************************************************************************/

#ifndef _S_PLAYER_SCENE_MANAGER_H_
#define _S_PLAYER_SCENE_MANAGER_H_

/******************************************************************************/

#include "MapServerPreqs.h"

/******************************************************************************/

namespace MG
{
	class SPlayerSceneManager
	{
	public:
		SPlayerSceneManager();
		~SPlayerSceneManager();


		void 	addPlayer( SPlayerPtr& playerPtr );
		void 	removePlayer( SPlayerPtr& playerPtr );
		Bool 	hasPlayer( const AccountIdType accountId );
		Bool 	getPlayer( SPlayerPtr& ptr, const AccountIdType accountId);
		void 	removeAllPlayer();

	};
}

#endif	//_S_PLAYER_SCENE_MANAGER_H_