/******************************************************************************/

#include "stdafx.h"
#include "SGameObjectManager.h"
#include "ClientManager.h"
#include "SWorldManager.h"
#include "FrontServerMain.h"
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
	//-----------------------------------------------------------------------
	Bool SGameObjectManager::initialize()
	{
		// 不做客户端超时检测 
		/*if ( mCheckPlayerThread.create( checkPlayerThread,this ) == false )
		{
			return false;
		}*/

#ifdef _DEBUG
		//Thread::SetThreadName(mCheckPlayerThread.getThreadId(),"SGameObjectManager::checkPlayerThread");
#endif

		return true;
	}
	//-----------------------------------------------------------------------
	void SGameObjectManager::unInitialize()
	{
		mCheckPlayerThread.destory();

		clearPlayerFromList();
	}
	//-----------------------------------------------------------------------------
	SPlayerCharacter* SGameObjectManager::createPlayerCharacterFromMemory(PlayerCharacterIdType id, SClan* parentClan)
	{
		SPlayerCharacter* playerCharacter  = NULL;
		mSPlayerCharacterPoolCs.lock();
		{
			playerCharacter = MG_POOL_NEW(mSPlayerCharacterPool,SPlayerCharacter,(parentClan,id));
		}
		mSPlayerCharacterPoolCs.unlock();
		return playerCharacter;
	}
	//-----------------------------------------------------------------------------
	SClan* SGameObjectManager::createClanFromMemory(SPlayer* parentPlayer)
	{
		SClan* clan  = NULL;
		mSClanPoolCs.lock();
		{
			clan = MG_POOL_NEW(mSClanPool,SClan,(parentPlayer));
		}
		mSClanPoolCs.unlock();
		return clan;
	}
	//-----------------------------------------------------------------------------
	void SGameObjectManager::destroyPlayerCharacterFromMemory(SPlayerCharacter* playerCharacter)
	{
		if (!playerCharacter)
		{
			return;
		}
		mSPlayerCharacterPoolCs.lock();
		MG_POOL_DELETE( mSPlayerCharacterPool, playerCharacter);
		mSPlayerCharacterPoolCs.unlock();
	}
	//-----------------------------------------------------------------------------
	void SGameObjectManager::destroyClanFromMemory(SClan* clan)
	{
		if (!clan)
		{
			return;
		}
		clan->destroyAllPlayerCharacter();
		mSClanPoolCs.lock();
		MG_POOL_DELETE( mSClanPool, clan);
		mSClanPoolCs.unlock();
	}
	//-----------------------------------------------------------------------------
	void SGameObjectManager::update()
	{
		//std::map<NetIdType, SPlayerPtr>::iterator it;
		//mPlayerListCs.lock();
		//for(it = mPlayerList.begin(); it != mPlayerList.end();)
		//{
		//	SPlayerPtr playerPtr = it->second;
		//	if (playerPtr.isNull())
		//	{
		//		it = mPlayerList.erase(it);
		//	}
		//	else
		//	{
		//		// 更新角色
		//		std::map<ClanIdType, SClan*>* clanList = playerPtr->getClanList();
		//		if (clanList)
		//		{
		//			std::map<ClanIdType, SClan*>::iterator itClan = clanList->begin();
		//			for (; itClan != clanList->end(); itClan++)
		//			{
		//				std::map<PlayerCharacterIdType, SPlayerCharacter*>* playerCharacterList = itClan->second->getPlayerCharacterList();
		//				if (playerCharacterList)
		//				{
		//					std::map<PlayerCharacterIdType, SPlayerCharacter*>::iterator itPlayerCharacter = playerCharacterList->begin();
		//					for (; itPlayerCharacter != playerCharacterList->end(); itPlayerCharacter++)
		//					{
		//						itPlayerCharacter->second->update();
		//					}
		//				}
		//			}
		//		}
		//		it++;
		//	}
		//	
		//}
		//mPlayerListCs.unlock();


		//-----------------------------------------------------------------------------
		SPlayerPtr player;
		I32 currPlayerIndex = 0;
		NetIdType clientId = -1;
		Bool isContinue = true;
		while(isContinue)
		{
			isContinue = SWorldManager::getInstance().getGameObjectManager()->traversalPlayerList(currPlayerIndex,clientId,player);
			if (!isContinue)
			{
				// 遍历结束
				break;
			}
			if (player.isNull())
			{
				continue;
			}

			// 更新角色
			SClan* clan = player->getMainClan();
			if (clan)
			{
				std::map<PlayerCharacterIdType, SPlayerCharacter*>* playerCharacterList = clan->getPlayerCharacterList();
				if (playerCharacterList)
				{
					std::map<PlayerCharacterIdType, SPlayerCharacter*>::iterator itPlayerCharacter = playerCharacterList->begin();
					for (; itPlayerCharacter != playerCharacterList->end(); itPlayerCharacter++)
					{
						itPlayerCharacter->second->update();
					}
				}

			}
		}
	}


	//-----------------------------------------------------------------------------
	SPlayerPtr SGameObjectManager::createPlayerFromMemory(NetIdType clientID, Char16* accName, Char16* accPsw, AccountIdType accountId)
	{

		SPlayerPtr playerPtr = getPlayerByClientNetId(clientID);
		if (playerPtr.isNull())
		{
			SPlayer* player = NULL;
			mPlayerPoolCs.lock();
			{
				player = MG_POOL_NEW(mSPlayerPool,SPlayer,(clientID, accountId, accName, accPsw,this));
			}
			mPlayerPoolCs.unlock();
			if (player)
			{
				playerPtr.bind(player);
				playerPtr->setInWorld(true);
				mPlayerListCs.lock();
				mPlayerList[clientID] = playerPtr;
				mPlayerListCs.unlock();
				//addPlayerToQueue(playerPtr);
			}

		}
		else
		{
			DYNAMIC_ASSERT(0);
		}
		return playerPtr;
	}
	//-----------------------------------------------------------------------------
	SPlayerPtr SGameObjectManager::getPlayerByClientNetId(const NetIdType clientNetId)
	{
		SPlayerPtr playerPtr;
		mPlayerListCs.lock();
		{
			std::map<NetIdType, SPlayerPtr>::iterator it = mPlayerList.find(clientNetId);
			if (it != mPlayerList.end())
			{
				playerPtr = it->second;
			}
		}
		mPlayerListCs.unlock();
		return playerPtr;
	}
	//-----------------------------------------------------------------------------
	SPlayerPtr SGameObjectManager::getPlayerByAccountId(const AccountIdType accountId)
	{
		SPlayerPtr playerPtr;
		mPlayerListCs.lock();
		for (std::map<NetIdType, SPlayerPtr>::iterator iter = mPlayerList.begin(); iter != mPlayerList.end();)
		{
			if (!iter->second.isNull() )
			{
				if( accountId == iter->second->getAccountID())
				{
					playerPtr = iter->second;
					break;
				}
				iter++;
			}
			else
			{
				iter = mPlayerList.erase(iter);
			}

		}
		mPlayerListCs.unlock();
		return playerPtr;
	}
	//--------------------------------------------------------------------------
	void SGameObjectManager::destroyPlayerFromMemory( SPlayer* player )
	{	
		if (!player)
		{
			return;
		}

		player->destroyAllClanInfo();

		mPlayerPoolCs.lock();
		{
			MG_POOL_DELETE( mSPlayerPool, player);
		}
		mPlayerPoolCs.unlock();
	}
	//--------------------------------------------------------------------------
	void SGameObjectManager::removePlayerFromList( NetIdType clientNetId )
	{
		mPlayerListCs.lock();
		std::map<NetIdType, SPlayerPtr>::iterator it = mPlayerList.find(clientNetId);
		if (it != mPlayerList.end())
		{
			SPlayerPtr player = it->second;
			DYNAMIC_ASSERT(player.isNull() == false);
			mPlayerList.erase(it);
			player->setInWorld(false);
		}
		mPlayerListCs.unlock();

	}
	//--------------------------------------------------------------------------
	void SGameObjectManager::removePlayerFromList(SPlayerPtr playerPtr)
	{
		if(playerPtr.isNull())
		{
			return;
		}
		mPlayerListCs.lock();
		std::map<NetIdType, SPlayerPtr>::iterator it = mPlayerList.find(playerPtr->getClientNetID());
		if (it != mPlayerList.end())
		{
			mPlayerList.erase(it);
			playerPtr->setInWorld(false);
		}
		mPlayerListCs.unlock();
	}
	//--------------------------------------------------------------------------
	void SGameObjectManager::clearPlayerFromList()
	{
		mPlayerListCs.lock();
		{
			mPlayerList.clear();
		}
		mPlayerListCs.unlock();

		/*SPlayerPtr player = getPlayerFromQueue();
		while(!player.isNull())
		{
			player = getPlayerFromQueue();
		}

		DYNAMIC_ASSERT(mPlayerQueue.empty());*/
	}

	////--------------------------------------------------------------------------
	//std::map<NetIdType, SPlayerPtr>* SGameObjectManager::getPlayerList()
	//{
	//	return &mPlayerList;
	//}
	////--------------------------------------------------------------------------
	//void SGameObjectManager::lockPlayerList()
	//{
	//	mPlayerListCs.lock();
	//}
	////--------------------------------------------------------------------------
	//void SGameObjectManager::unLockPlayerList()
	//{
	//	mPlayerListCs.unlock();
	//}
	//--------------------------------------------------------------------------
	Bool SGameObjectManager::traversalPlayerList(I32& playerIndex, NetIdType& clientNetId,SPlayerPtr& player )
	{
		mPlayerListCs.lock();	
		if (playerIndex < mPlayerList.size() && !mPlayerList.empty())
		{
			std::map<NetIdType, SPlayerPtr>::iterator it =  mPlayerList.begin();
			std::advance(it,playerIndex++);
			player = it->second;
			clientNetId = it->first;
			DYNAMIC_ASSERT(player.isNull() == false);
			DYNAMIC_ASSERT(clientNetId != -1);
		}
		else
		{
			mPlayerListCs.unlock();
			return false;
		}
		mPlayerListCs.unlock();
		return true;
	}
	//--------------------------------------------------------------------------
	/*SPlayerPtr SGameObjectManager::getPlayerFromQueue()
	{
		SPlayerPtr player;
		mPlayerQueueCs.lock();
		if (!mPlayerQueue.empty())
		{
			player = mPlayerQueue.front();
			mPlayerQueue.pop();
		}
		mPlayerQueueCs.unlock();
		return player;
	}*/
	//--------------------------------------------------------------------------
	/*void SGameObjectManager::addPlayerToQueue(SPlayerPtr player)
	{

		DYNAMIC_ASSERT(player.isNull() == false)
		mPlayerQueueCs.lock();
		mPlayerQueue.push(player);
		mPlayerQueueCs.unlock();
	}*/
	//--------------------------------------------------------------------------
	void SGameObjectManager::checkPlayerThread( Ptr ptr )
	{
		/*OneThreadHandle* thd = (OneThreadHandle*)ptr;
		if (thd && thd->getParam())
		{
			SGameObjectManager* mgr = (SGameObjectManager*)(thd->getParam());
			if (mgr)
			{
				while( thd->isRun())
				{

					SPlayerPtr player = mgr->getPlayerFromQueue();

					while( player.isNull() )
					{
                        if ( thd->isRun() ==false )
                            return;

						player = mgr->getPlayerFromQueue();

						Sleep(10);
					}

                    if ( player.isNull() == false )
                    {
                        if (!player->inWorld())
                        {
                            // 不再加入队列
                        }
                        else
                        {
                            if (player->isCheckDisconnect())
                            {
                                // 不再加入队列
                            }
                            else
                            {
                                // 检测异常
                                ClientObject* clientObj = ClientManager::getInstance().getWaitingLoginClient(player->getClientNetID());
                                if (!clientObj)
                                {
                                    SWorldManager::getInstance().logoutPlayer(player->getClientNetID());
                                    FrontServerMain::getInstance().getServerLauncher()->closeClient(player->getClientNetID());
                                }
                            }

                        }
                        Sleep(5);
                    }
				}
			}
		}*/
	}
//--------------------------------------------------------------------------
}