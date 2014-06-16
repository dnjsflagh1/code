//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Server\MapServer\Include\SGameObjectManager.h
//        Author: yuanlinhu
//          Date: 2012-3-28
//          Time: 14:15
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-28      add
//////////////////////////////////////////////////////////////

/******************************************************************************/
#ifndef _S_GAME_OBJECT_MANAGER_H_
#define _S_GAME_OBJECT_MANAGER_H_
/******************************************************************************/

#include "MapServerPreqs.h"

#include "DataSetManager.h"

#include "SPlayer.h"
#include "SPlayerCharacter.h"
#include "SBuilding.h"

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//GameObjectπ‹¿Ì’ﬂ
	/******************************************************************************/
	class SGameObjectManager
	{
	public:
		SGameObjectManager();
		~SGameObjectManager();

		SPlayer*				createPlayerFromMemory(AccountIdType accountId);
		SPlayerCharacter*		createPlayerCharacterFromMemory(PlayerCharacterIdType id, SPlayer* player);
		//STroopGroup*			createTroopGroupFromMemory(TroopGroupIdType id, SPlayer* player);
		//SBattleBuilding*		createBattleBuildingFromMemory(BattleBuildingIdType id, SPlayer* player);

		SPlayer*				getPlayerFromMemory(AccountIdType accountID);
		SPlayerCharacter*		getPlayerCharacterFromMemory(PlayerCharacterIdType id);

		void					destroyPlayerFromMemory(SPlayer* player);
		void					destroyPlayerFromMemory(AccountIdType accountID);
		void					destroyPlayerCharacterFromMemory(SPlayerCharacter* playerCharacter);
		void					destroyPlayerCharacterFromMemory(PlayerCharacterIdType id);



		std::map<AccountIdType,			SPlayer*>			*			getPlayerList();
		std::map<PlayerCharacterIdType, SPlayerCharacter*>	*			getPlayerCharacterList();

		void					update(Flt delta);



		void					print();
	private:
		SimpleMapDataSetManager<AccountIdType,			SPlayer>				mPlayerList;
		SimpleMapDataSetManager<PlayerCharacterIdType,	SPlayerCharacter>		mPlayerCharacterList;
		//SimpleMapDataSetManager<BuildingIdType,	SBuilding>		mBattleBuildingList;

	};
}

#endif	//_S_GAME_OBJECT_MANAGER_H_