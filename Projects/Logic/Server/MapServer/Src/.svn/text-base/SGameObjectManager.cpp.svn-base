/******************************************************************************/

#include "stdafx.h"
#include "SGameObjectManager.h"

/******************************************************************************/

namespace MG
{
	//-----------------------------------------------------------------------
	SGameObjectManager::SGameObjectManager()
	{

	}

	//-----------------------------------------------------------------------
	SGameObjectManager::~SGameObjectManager()
	{

	}

	//-----------------------------------------------------------------------------
	void SGameObjectManager::update(Flt delta)
	{
		std::map<AccountIdType, SPlayer*>* playerList = getPlayerList();
		SPlayer* player = NULL;

		for(std::map<AccountIdType, SPlayer*>::iterator it = playerList->begin(); it != playerList->end(); ++it)
		{
			player = it->second;
			if(!player)
			{
				continue;
			}

			player->update(delta);
		}
	}

	//-----------------------------------------------------------------------------
	SPlayer* SGameObjectManager::createPlayerFromMemory(AccountIdType accountId)
	{
		SPlayer* player = getPlayerFromMemory(accountId);
		if (NULL == player)
		{
			player = mPlayerList.createOrRetrieve<AccountIdType>(accountId,accountId);
		}
		else
		{
			DYNAMIC_ASSERT(0);
		}
		return player;
	}	

	//-----------------------------------------------------------------------------
	SPlayerCharacter* SGameObjectManager::createPlayerCharacterFromMemory(PlayerCharacterIdType id, SPlayer* player)
	{
		SPlayerCharacter* playerCharacter = getPlayerCharacterFromMemory(id);
		if (NULL == playerCharacter)
		{
			playerCharacter = mPlayerCharacterList.createOrRetrieve<PlayerCharacterIdType, SPlayer*>(id,id,player);
			playerCharacter->setID(id);
		}
		else
		{
			DYNAMIC_ASSERT(0);
		}
		return playerCharacter;
	}

	//-----------------------------------------------------------------------------
	/*STroopGroup* SGameObjectManager::createTroopGroupFromMemory(TroopGroupIdType id, SPlayer* player)
	{
		STroopNew* troop = gettr(id);
		if (NULL == troop)
		{
			troop = mTroopGroupList.createOrRetrieve<TroopGroupIdType, SPlayer*>(id, id, player, false);
			troop->setID(id);

		}
		else
		{
			DYNAMIC_ASSERT(0);
		}
		return troop;
	}*/

	//-----------------------------------------------------------------------------
	/*SBattleBuilding* SGameObjectManager::createBattleBuildingFromMemory(BattleBuildingIdType id, SPlayer* player)
	{
		SBattleBuilding* building = getBattleBuildingFromMemory(id);
		if (NULL == building)
		{
			building = mBattleBuildingList.createOrRetrieve<BattleBuildingIdType, SPlayer*>(id, id, player, false);
		}
		else
		{
			DYNAMIC_ASSERT(0);
		}
		return building;
	}*/


	//-----------------------------------------------------------------------

	//-----------------------------------------------------------------------------
	SPlayer* SGameObjectManager::getPlayerFromMemory(AccountIdType accountID)
	{
		return mPlayerList.getData(accountID);
	}

	//-----------------------------------------------------------------------------
	SPlayerCharacter* SGameObjectManager::getPlayerCharacterFromMemory(PlayerCharacterIdType id)
	{
		return mPlayerCharacterList.getData(id);
	}

	//-----------------------------------------------------------------------------
	/*STroopGroup* SGameObjectManager::getTroopGroupFromMemory(TroopGroupIdType id)
	{
		return mTroopGroupList.getData(id,false);
	}*/

	//-----------------------------------------------------------------------------
	/*SBattleBuilding* SGameObjectManager::getBattleBuildingFromMemory(BattleBuildingIdType id, RegionIdType regionId, InstanceUIdType instanceUid)
	{
		return mBattleBuildingList.getData(id,false);
	}*/

		/*SCharacter* SGameObjectManager::getCharacterFromMemory(GameObjectIdType id, GAMEOBJ_TYPE type)
		{
			SCharacter* character = NULL;
			switch(type)
			{
			case GOT_PLAYERCHARACTER:
				{
					character = getPlayerCharacterFromMemory(id);
				}break;
			case GOT_BATTLE_BUILDING:
				{
					character = getBattleBuildingFromMemory(id);
				}break;
			default:
				{
					DYNAMIC_ASSERT(0);
				}break;
			}

			return character;
		}*/
	//-----------------------------------------------------------------------------
	void SGameObjectManager::destroyPlayerFromMemory(AccountIdType accountID)
	{
		mPlayerList.destroy(accountID);
	}

	//-----------------------------------------------------------------------------
	void SGameObjectManager::destroyPlayerFromMemory(SPlayer* player)
	{
		if (NULL == player)
		{
			DYNAMIC_ASSERT(0);
			return;
		}
		destroyPlayerFromMemory(player->getAccountID());
	}

	//-----------------------------------------------------------------------------
	void SGameObjectManager::destroyPlayerCharacterFromMemory(PlayerCharacterIdType id)
	{
		mPlayerCharacterList.destroy(id);
	}

	//-----------------------------------------------------------------------------
	void SGameObjectManager::destroyPlayerCharacterFromMemory(SPlayerCharacter* playerCharacter)
	{
		if (NULL == playerCharacter)
		{
			return;
		}

		destroyPlayerCharacterFromMemory(playerCharacter->getID());
	}


	//-----------------------------------------------------------------------------
	std::map<AccountIdType, SPlayer*>* SGameObjectManager::getPlayerList()
	{
		return mPlayerList.getDataSet();
	}

	//-----------------------------------------------------------------------------
	std::map<PlayerCharacterIdType, SPlayerCharacter*>* SGameObjectManager::getPlayerCharacterList()
	{
		return mPlayerCharacterList.getDataSet();
	}


	////-----------------------------------------------------------------------------
	//std::map<BuildingIdType, SBuilding*>* SGameObjectManager::getBattleBuildingList()
	//{
	//	return mBattleBuildingList.getDataSet();
	//}

	//-----------------------------------------------------------------------------
	void SGameObjectManager::print()
	{
		MG_LOG(out_sys, "\n=============================================================================\n ");
		MG_LOG(out_sys, "\n ------------------- 打印 SGameObjectManager 内存 开始 ------------------- \n ");
		//1. 【玩家】
		{
			MG_LOG(out_sys, "\n ------------------- 【玩家列表信息】开始 ------------------- \n ");
			std::map<PlayerIdType, SPlayer*>* playerList = getPlayerList();
			std::map<PlayerIdType, SPlayer*>::iterator iter = playerList->begin();

			Int count = 1;
			for ( ; iter != playerList->end(); ++iter, ++count)
			{
				//if (iter->second->getCanSeeByCamera() == false)
				//{
				//	continue;
				//}
				MG_LOG(out_sys, "\n【第[%d]个玩家】开始\n ", count);
				iter->second->print();
				MG_LOG(out_sys, "\n【第[%d]个玩家】结束\n ",count);
			}
			MG_LOG(out_sys, "\n ------------------- 【玩家列表信息】结束 ------------------- \n ");
		}

		//2. 【武将】
		{
			MG_LOG(out_sys, "\n ------------------- 【武将列表信息】开始 ------------------- \n ");
			std::map<PlayerCharacterIdType, SPlayerCharacter*>* playerCharacterList = getPlayerCharacterList();
			std::map<PlayerCharacterIdType, SPlayerCharacter*>::iterator iter = playerCharacterList->begin();
			Int count = 1;
			for ( ; iter != playerCharacterList->end(); ++iter, ++count)
			{
				//if (iter->second->getCanSeeByCamera() == false)
				//{
				//	continue;
				//}
				MG_LOG(out_sys, "\n【第[%d]个武将】开始\n ", count);
				iter->second->print();
				MG_LOG(out_sys, "\n【第[%d]个武将】结束\n ", count);
			}
			MG_LOG(out_sys, "\n ------------------- 【武将列表信息】结束 ------------------- \n ");
		}

		MG_LOG(out_sys, "\n ------------------- 打印 SGameObjectManager 内存 结束 ------------------- \n ");
		MG_LOG(out_sys, "\n=============================================================================\n ");

	}


}