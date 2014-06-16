/******************************************************************************/
#include "stdafx.h"
#include "SRegionNetPacketProcesser.h"
#include "ServerManager.h"
#include "MapServerMain.h"
#include "NetTranspondPacketProcesser.h"
#include "TroopNetPacket.h"
#include "SPlayer.h"
#include "SCharacter.h"
#include "SPlayerCharacter.h"
#include "SWorldManager.h"
#include "PlayerCharacterData.h"
#include "SCamp.h"
#include "SSceneGrid.h"
#include "SWorldManager.h"
#include "SActionManager.h"
#include "SCharacterMoveToAction.h"
#include "ItemNetPacket.h"
#include "SBuffPacketProcesser.h"
#include "SItemPacketProcesser.h"
#include "SBuffManager.h"
#include "BuffData.h"
#include "SMonster.h"
/******************************************************************************/

namespace MG
{

	//--------------------------------------------------------------------------
	SRegionNetPacketProcesser::SRegionNetPacketProcesser()
	{
	}

	//--------------------------------------------------------------------------
	SRegionNetPacketProcesser::~SRegionNetPacketProcesser()
	{
	}

	//--------------------------------------------------------------------------
	Bool SRegionNetPacketProcesser::processFrontServerPacket(I32 id, NetEventRecv* packet)
	{
		if ( packet->getChannel() == GNPC_REGION )
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_REGION_F2M_ADD_BUILDING:
				onRecvAddBatleFromFrontServer( id , (PT_REGION_F2M_ADD_BUILDING_DATA*)data->data);
				break;
			case PT_REGION_F2M_REMOVE_BUILDING:
				onRecvRemoveBatleFromFrontServer(id , (PT_REGION_F2M_REMOVE_BUILDING_DATA*)data->data );
				break;
			case PT_REGION_F2M_CREATE_TROOP_RET:
				onRecvCreateTroopRetFromFrontServer(id , (PT_REGION_F2M_CREATE_TROOP_RET_DATA*)data->data );
				break;
			case PT_REGION_C2M_ADD_TROOP_TEST:
				onRecvAddTroopTestFromFrontServer(id , (PT_REGION_C2M_ADD_TROOP_TEST_DATA*)data->data );
				break;
			case PT_REGION_F2M_PLAYER_CHARACTER_ALIVE:
				onRecvPlayerCharacterSetAliveFromFrontServer(id , (PT_REGION_F2M_PLAYER_CHARACTER_ALIVE_DATA*)data->data );
				break;
			case PT_REGION_C2M_TEST:
				onRecvTestFromFrontServer(id , (PT_REGION_C2M_TEST_DATA*)data->data );
				break;
			case PT_REGION_C2M_TEST1:
				onRecvTest1FromFrontServer(id , (PT_REGION_C2M_TEST_DATA*)data->data );
				break;
			}

			return true;
		}
		return false;
	}

	//--------------------------------------------------------------------------
	void SRegionNetPacketProcesser::sendPlayerCharacterListToPlayer_New( SPlayer* player, std::map<PlayerCharacterIdType, SCharacter*>* playerCharacterList, GameType gameType )
	{
		if(gameType != GameType_Rpg)
		{
			NetTranspondSendDataBufferPtr dataPtr ;
			GameNetPacketData* packet       = NULL;
			PT_REGION_M2C_ADD_PLAYER_CHARACTER_DATA* sendData = NULL;

			// 当前发送数据头大小
			I32 sendDataHeadSize    = 0;
			// 当前发送数据大小
			I32 sendDataSize        = 0;
			// 准备发送数据大小
			I32 prepareSendDataSize = 0;
			
			// 遍历角色队列
			std::map<PlayerCharacterIdType, SCharacter*>::iterator iter = playerCharacterList->begin();
			while( playerCharacterList->end() != iter )
			{

				//--------------------------------------------------------------------------

				SPlayerCharacter* playerCharacter = (SPlayerCharacter*)iter->second;
				if (false == playerCharacter->getCanSeeByCamera())
				{
					//这是看不到的武将信息
					++iter;
					continue;
				}

				//--------------------------------------------------------------------------

				if ( dataPtr.mDataPtr.isNull() == false )
				{
					// 递增一个角色数据大小到发送数据缓存大小
					prepareSendDataSize = sendDataSize + PT_REGION_M2C_ADD_PLAYER_CHARACTER_INFO::netAddPlayerCharacterInfoSize;

					// 如果大于缓存最大大小则发送
					if ( prepareSendDataSize >= dataPtr.getTranspondDataMaxSize(100) )
					{
						SPlayerIdentifyInfo* playerIdendifyInfo = player->getIdentifyInfo();

						NetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(
							dataPtr, sendDataSize, 
							player->getFrontServerId(), 
							player->getClientNetIdInFrontServer(), 
							player->getAccountId());
						dataPtr.mDataPtr.setNull() ;
					}
				}

				//--------------------------------------------------------------------------

				if ( dataPtr.mDataPtr.isNull() )
				{
					NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );
					packet	= (GameNetPacketData*) dataPtr.getTranspondData();
					if ( !packet )
						return;

					packet->channel = GNPC_REGION;
					packet->type    = PT_REGION_M2C_ADD_PLAYER_CHARACTER;
					sendData = (PT_REGION_M2C_ADD_PLAYER_CHARACTER_DATA*)(packet->data);
					sendData->addPlayerNum = 0;

					sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_REGION_M2C_ADD_PLAYER_CHARACTER_INFO::headSize;
					sendDataSize        = sendDataHeadSize;
					prepareSendDataSize = sendDataHeadSize;
				}

				//--------------------------------------------------------------------------

				NetAddPlayerCharacterInfo* tempSend = &(sendData->addPlayerInfo[sendData->addPlayerNum]);
				tempSend->playerId = playerCharacter->getAccountId();
				tempSend->character_id = playerCharacter->getID();
				WStrnCpyS(tempSend->name, playerCharacter->getName().c_str(), MAX_CHARACTER_NAME_LEN);
				WStrnCpyS(sendData->addPlayerInfo->surNmae, playerCharacter->getPlayerCharacterData()->charSurName.c_str(), MAX_CHARACTER_NAME_LEN);
				tempSend->characterTemplateID = ((SPlayerCharacter*)playerCharacter)->getPlayerCharacterData()->mCharacterTemplateID;
				tempSend->pos	= ((NetVec2)playerCharacter->getPos()).getData();
				tempSend->dir	= ((NetVec2)playerCharacter->getDir()).getData();
				tempSend->hp	= playerCharacter->getHp();
				tempSend->mp	= playerCharacter->getMp();
				tempSend->pos	= ((NetVec2)playerCharacter->getPos()).getData();
				tempSend->force = playerCharacter->getForce();
				tempSend->isBattleLeader = playerCharacter->getIsBattleLeader();
				tempSend->moveSpeed = playerCharacter->getMoveSpeed();
				sendData->addPlayerInfo->artIconId	= playerCharacter->getPlayerCharacterData()->charArtIcon;
				sendData->addPlayerInfo->level		= playerCharacter->getLevel();

				sendDataSize += PT_REGION_M2C_ADD_PLAYER_CHARACTER_INFO::netAddPlayerCharacterInfoSize;

				++sendData->addPlayerNum;
				++iter;
			}

			//--------------------------------------------------------------------------

			if ( dataPtr.mDataPtr.isNull() == false )
			{
				NetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(
					dataPtr, sendDataSize, 
					player->getFrontServerId(), 
					player->getClientNetIdInFrontServer(), 
					player->getAccountId());
				dataPtr.mDataPtr.setNull();
			}
		}
	}

	//--------------------------------------------------------------------------
	void SRegionNetPacketProcesser::broadcastPlayerCharacterEnterToRegion_New(SPlayerCharacter* playerCharacter, SRegionObjectBase* region)
	{
#if 0
		NetTranspondSendDataBufferPtr dataPtr ;
        NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if ( packet )
		{
			packet->channel = GNPC_REGION;
			packet->type    = PT_REGION_M2C_ADD_PLAYER_CHARACTER;
			PT_REGION_M2C_ADD_PLAYER_CHARACTER_DATA* sendData = (PT_REGION_M2C_ADD_PLAYER_CHARACTER_DATA*)(packet->data);
			if(sendData)
			{
				sendData->addPlayerNum = 1;

				sendData->addPlayerInfo->playerId				= playerCharacter->getAccountId();
				sendData->addPlayerInfo->character_id			= playerCharacter->getID();
				WStrnCpyS(sendData->addPlayerInfo->name, playerCharacter->getName().c_str(), MAX_CHARACTER_NAME_LEN);
				WStrnCpyS(sendData->addPlayerInfo->surNmae, playerCharacter->getPlayerCharacterData()->charSurName.c_str(), MAX_CHARACTER_NAME_LEN);
				sendData->addPlayerInfo->characterTemplateID	= (playerCharacter)->getPlayerCharacterData()->mCharacterTemplateID;
				sendData->addPlayerInfo->pos					= ((NetVec2)playerCharacter->getPos()).getData();
				sendData->addPlayerInfo->dir					= ((NetVec2)playerCharacter->getDir()).getData();
				sendData->addPlayerInfo->hp						= playerCharacter->getHp();
				sendData->addPlayerInfo->mp						= playerCharacter->getMp();
				sendData->addPlayerInfo->hpmax					= playerCharacter->getMaxHp();
				sendData->addPlayerInfo->mpmax					= playerCharacter->getMaxMp();
				sendData->addPlayerInfo->force					= playerCharacter->getForce();
				sendData->addPlayerInfo->isBattleLeader			= playerCharacter->getIsBattleLeader();
				sendData->addPlayerInfo->moveSpeed				= playerCharacter->getMoveSpeed();
				sendData->addPlayerInfo->artIconId              = playerCharacter->getPlayerCharacterData()->charArtIcon;
				sendData->addPlayerInfo->level                  = playerCharacter->getLevel();

				Int dataSize = GameNetPacketData_INFO::headSize + PT_REGION_M2C_ADD_PLAYER_CHARACTER_INFO::dataSize(sendData);
				if (region->getRegionType() == ROT_MAP_DISTRIBUTION)
				{
					NetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(
						dataPtr, dataSize,
						playerCharacter->getFrontServerId(), 
						playerCharacter->getClientNetIdInFrontServer(), 
						playerCharacter->getAccountId());
					
				}
				else
				{
					SRegionObjectBase* regionObjectBase = playerCharacter->getCurrentRegionObject();
					if(regionObjectBase)
					{
						NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(
							dataPtr, dataSize, 
							playerCharacter->getSceneObjectInSceneGridsManager()->currSceneGrid, 
							NULL, regionObjectBase, 0);
					}	
				}
			}
		}
#endif
	}

	//--------------------------------------------------------------------------
	void SRegionNetPacketProcesser::broadcastPlayerCharacterLeaveToRegion_New(SCharacter* playerCharacter, SRegionObjectBase* region)
	{
		NetTranspondSendDataBufferPtr dataPtr ;
        NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if(packet)
		{
			packet->type = PT_REGION_M2C_REMOVE_PLAYER_CHARACTER;
			packet->channel = GNPC_REGION;

			PT_REGION_M2C_REMOVE_PLAYER_CHARACTER_DATA* sendData = (PT_REGION_M2C_REMOVE_PLAYER_CHARACTER_DATA*)(packet->data);
			if(sendData)
			{
				sendData->character_id = (playerCharacter)->getID();

				//SRegionObjectBase* regionObjectBase = playerCharacter->getCurrentRegionObject();
				//if(regionObjectBase)
				//{
				//	NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(
				//		dataPtr, 
				//		GameNetPacketData_INFO::headSize + PT_REGION_M2C_REMOVE_PLAYER_CHARACTER_INFO::dataSize, 
				//		playerCharacter->getSceneObjectInSceneGridsManager()->currSceneGrid, 
				//		NULL, regionObjectBase, 0);
				//}
			}
		}
	}

	//--------------------------------------------------------------------------
	void SRegionNetPacketProcesser::broadcastCreateAndAppearPlayerCharacterToRegionToOther( SPlayerCharacter* playerCharacter, SRegionObjectBase* region, Bool isFilterSelf )
	{
#if 0
		NetTranspondSendDataBufferPtr dataPtr ;
        NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if ( packet )
		{
			packet->channel = GNPC_REGION;
			packet->type    = PT_REGION_M2C_CREATE_APPEAR_PLAYER_CHARACTER;
			PT_REGION_M2C_CREATE_APPEAR_PLAYER_CHARACTER_DATA* sendData = (PT_REGION_M2C_CREATE_APPEAR_PLAYER_CHARACTER_DATA*)(packet->data);
			if(sendData)
			{
				sendData->addPlayerNum = 1;

				sendData->addPlayerInfo->playerId				= playerCharacter->getAccountId();
				sendData->addPlayerInfo->character_id			= playerCharacter->getID();
				WStrnCpyS(sendData->addPlayerInfo->name, playerCharacter->getName().c_str(), MAX_CHARACTER_NAME_LEN);
				WStrnCpyS(sendData->addPlayerInfo->surNmae, playerCharacter->getPlayerCharacterData()->charSurName.c_str(), MAX_CHARACTER_NAME_LEN);
				sendData->addPlayerInfo->characterTemplateID	= (playerCharacter)->getPlayerCharacterData()->mCharacterTemplateID;
				sendData->addPlayerInfo->pos					= ((NetVec2)playerCharacter->getPos()).getData();

				SCharacterMoveToAction* moveToAction = (SCharacterMoveToAction*)playerCharacter->getActionManager()->getState("SCharacterMoveToAction", false);
				if(moveToAction)
				{
					sendData->addPlayerInfo->moveToPos			= ((NetVec2)moveToAction->getMoveToPos()).getData();
				}
				else
				{
					sendData->addPlayerInfo->moveToPos          = ((NetVec2)Vec3(0,0,0)).getData();
				}

				sendData->addPlayerInfo->dir					= ((NetVec2)playerCharacter->getDir()).getData();
				sendData->addPlayerInfo->hp						= playerCharacter->getHp();
				sendData->addPlayerInfo->mp						= playerCharacter->getMp();
				sendData->addPlayerInfo->mpmax					= playerCharacter->getMaxMp();
				sendData->addPlayerInfo->hpmax					= playerCharacter->getMaxHp();
				sendData->addPlayerInfo->force					= playerCharacter->getForce();
				sendData->addPlayerInfo->isBattleLeader			= playerCharacter->getIsBattleLeader();
				sendData->addPlayerInfo->moveSpeed				= playerCharacter->getMoveSpeed();
                sendData->addPlayerInfo->artIconId              = playerCharacter->getPlayerCharacterData()->charArtIcon;
                sendData->addPlayerInfo->level                  = playerCharacter->getLevel();

				Int dataSize = GameNetPacketData_INFO::headSize + PT_REGION_M2C_CREATE_APPEAR_PLAYER_CHARACTER_DATA_INFO::dataSize(sendData);

				if (region->getRegionType() == ROT_MAP_DISTRIBUTION)
				{
	
					NetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(
						dataPtr, dataSize,
						playerCharacter->getFrontServerId(), 
						playerCharacter->getClientNetIdInFrontServer(), 
						playerCharacter->getAccountId());
				}
				else
				{
					PlayerIdType playerId = 0;
					if(isFilterSelf)
					{
						playerId = playerCharacter->getAccountId();
					}

					SSceneObjectInSceneGridsManager* sceneObjectInSceneGridsManager = playerCharacter->getSceneObjectInSceneGridsManager();
					NetTranspondPacketProcesser::getInstance().gridsBroadcastClientTranspondPackToFrontServer(
						sceneObjectInSceneGridsManager->currSceneGrid, 
						sceneObjectInSceneGridsManager->lastSceneGrid, 
						dataPtr, dataSize, playerId);
				}
			}
		}
#endif
	}

	//--------------------------------------------------------------------------
	void SRegionNetPacketProcesser::broadcastCreateAndAppearPlayerCharacterToRegionToSelf( SPlayerCharacter* playerCharacter, SPlayer* myPlayer )
	{
		NetTranspondSendDataBufferPtr dataPtr ;
        NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if ( packet )
		{
			packet->channel = GNPC_REGION;
			packet->type    = PT_REGION_M2C_CREATE_APPEAR_PLAYER_CHARACTER;
			PT_REGION_M2C_CREATE_APPEAR_PLAYER_CHARACTER_DATA* sendData = (PT_REGION_M2C_CREATE_APPEAR_PLAYER_CHARACTER_DATA*)(packet->data);
			if(sendData)
			{
				sendData->addPlayerNum = 1;

				sendData->addPlayerInfo->playerId				= playerCharacter->getAccountId();
				sendData->addPlayerInfo->character_id			= playerCharacter->getID();
				WStrnCpyS(sendData->addPlayerInfo->name, playerCharacter->getName().c_str(), MAX_CHARACTER_NAME_LEN);
                WStrnCpyS(sendData->addPlayerInfo->surNmae, playerCharacter->getPlayerCharacterData()->charSurName.c_str(), MAX_CHARACTER_NAME_LEN);
				sendData->addPlayerInfo->characterTemplateID	= (playerCharacter)->getPlayerCharacterData()->mCharacterTemplateID;
				sendData->addPlayerInfo->pos					= ((NetVec2)playerCharacter->getPos()).getData();

				SCharacterMoveToAction* moveToAction = (SCharacterMoveToAction*)playerCharacter->getActionManager()->getState("SCharacterMoveToAction", false);
				if(moveToAction)
				{
					sendData->addPlayerInfo->moveToPos			= ((NetVec2)moveToAction->getMoveToPos()).getData();
				}
				else
				{
					sendData->addPlayerInfo->moveToPos          = ((NetVec2)Vec3(0,0,0)).getData();
				}

				sendData->addPlayerInfo->dir					= ((NetVec2)playerCharacter->getDir()).getData();
				sendData->addPlayerInfo->hp						= playerCharacter->getHp();
				sendData->addPlayerInfo->mp						= playerCharacter->getMp();
				sendData->addPlayerInfo->mpmax					= playerCharacter->getMaxMp();
				sendData->addPlayerInfo->hpmax					= playerCharacter->getMaxHp();
				sendData->addPlayerInfo->force					= playerCharacter->getForce();
				sendData->addPlayerInfo->isBattleLeader			= playerCharacter->getIsBattleLeader();
				sendData->addPlayerInfo->moveSpeed				= playerCharacter->getMoveSpeed();
				sendData->addPlayerInfo->artIconId              = playerCharacter->getPlayerCharacterData()->charArtIcon;
				sendData->addPlayerInfo->level                  = playerCharacter->getLevel();

				Int dataSize = GameNetPacketData_INFO::headSize + PT_REGION_M2C_CREATE_APPEAR_PLAYER_CHARACTER_DATA_INFO::dataSize(sendData);

				NetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(
					dataPtr, dataSize,
					playerCharacter->getFrontServerId(), 
					playerCharacter->getClientNetIdInFrontServer(), 
					playerCharacter->getAccountId());
			}
		}
	}


	//--------------------------------------------------------------------------
	void SRegionNetPacketProcesser::broadcastDestroyAndDisappearPlayerCharacterToRegionToSelf( SCharacter* playerCharacter, SPlayer* myPlayer )
	{

		NetTranspondSendDataBufferPtr dataPtr ;
        NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if ( packet )
		{
			packet->channel = GNPC_REGION;
			packet->type    = PT_REGION_M2C_DESTROY_DISAPPEAR_PLAYER_CHARACTER;
			PT_REGION_M2C_DESTROY_DISAPPEAR_PLAYER_CHARACTER_DATA* sendData = (PT_REGION_M2C_DESTROY_DISAPPEAR_PLAYER_CHARACTER_DATA*)(packet->data);
			if(sendData)
			{
				sendData->characterIndex = playerCharacter->getID();

				Int dataSize = GameNetPacketData_INFO::headSize + PT_REGION_M2C_DESTROY_DISAPPEAR_PLAYER_CHARACTER_DATA_INFO::dataSize;

				NetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(
					dataPtr, dataSize,
					myPlayer->getFrontServerId(),
					myPlayer->getClientNetIdInFrontServer(), 
					myPlayer->getAccountId());
			}
		}
	}

	//--------------------------------------------------------------------------
	void SRegionNetPacketProcesser::broadcastDestroyAndDisappearPlayerCharacterToRegionToOther( SCharacter* playerCharacter, SRegionObjectBase* region, Bool isFilterSelf )
	{
#if 0
		NetTranspondSendDataBufferPtr dataPtr ;
        NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if(packet)
		{
			packet->type = PT_REGION_M2C_DESTROY_DISAPPEAR_PLAYER_CHARACTER;
			packet->channel = GNPC_REGION;

			PT_REGION_M2C_DESTROY_DISAPPEAR_PLAYER_CHARACTER_DATA* sendData = (PT_REGION_M2C_DESTROY_DISAPPEAR_PLAYER_CHARACTER_DATA*)(packet->data);
			if(sendData)
			{
				sendData->characterIndex = playerCharacter->getID();

				PlayerIdType playerId = 0;
				if(isFilterSelf)
				{
					playerId = playerCharacter->getAccountId();
				}

				SSceneObjectInSceneGridsManager* sceneObjectInSceneGridsManager = playerCharacter->getSceneObjectInSceneGridsManager();
				NetTranspondPacketProcesser::getInstance().gridsBroadcastClientTranspondPackToFrontServer(
					sceneObjectInSceneGridsManager->currSceneGrid, 
					sceneObjectInSceneGridsManager->lastSceneGrid, 
					dataPtr, 
					GameNetPacketData_INFO::headSize + PT_REGION_M2C_DESTROY_DISAPPEAR_PLAYER_CHARACTER_DATA_INFO::dataSize, 
					playerId, 
					NetTranspondPacketProcesser::GBT_LAST);
			}
		}
#endif
	}

	//--------------------------------------------------------------------------
	void SRegionNetPacketProcesser::broadcastAppearPlayerCharacterToRegionToSelf( SPlayerCharacter* playerCharacter, std::map<UInt, SSceneGrid*>& regionGridList, Bool isFilterSelf )
	{
#if 0
		SSceneGrid* regionGrid = NULL;
		SPlayer* myPlayer = NULL; //playerCharacter->getOwnerPlayer();
		if(!myPlayer)
		{
			DYNAMIC_EEXCEPT_LOG("SRegionNetPacketProcesser::broadcastAppearPlayerCharacterToRegionToSelf : not find player!");
			return;
		}

		for(std::map<UInt, SSceneGrid*>::iterator regionGridIt = regionGridList.begin(); regionGridIt != regionGridList.end(); ++regionGridIt)
		{
			SPlayerCharacter* otherPlayerCharacter = NULL;
			regionGrid = regionGridIt->second;
			std::map<PlayerCharacterIdType, SPlayerCharacter*>* playerCharacterList = regionGrid->getPlayerCharacterList();
			for(std::map<PlayerCharacterIdType, SPlayerCharacter*>::iterator playerCharacterIt = playerCharacterList->begin(); playerCharacterIt != playerCharacterList->end(); ++playerCharacterIt)
			{
				otherPlayerCharacter = playerCharacterIt->second;
				if(isFilterSelf && playerCharacter == otherPlayerCharacter)
				{
					continue;
				}

				if(otherPlayerCharacter->isDead())
				{
					continue;
				}

				broadcastCreateAndAppearPlayerCharacterToRegionToSelf(otherPlayerCharacter, myPlayer);
				broadcastBuffListToRegionToSelf(otherPlayerCharacter, myPlayer);
				broadcastCreateAndAppearPlayerCharacterEquipListToRegionToSelf(otherPlayerCharacter,myPlayer);
			}
		}
#endif
	}

	//--------------------------------------------------------------------------
	void SRegionNetPacketProcesser::broadcastAppearPlayerCharacterToRegionToOther( SPlayerCharacter* playerCharacter, SRegionObjectBase* region, Bool isFilterSelf )
	{
		broadcastCreateAndAppearPlayerCharacterToRegionToOther(playerCharacter, region, isFilterSelf);
		SBuffPacketProcesser::getInstance().syncPlayerCharacterBuffDataListToClient(playerCharacter, isFilterSelf);
		SItemPacketProcesser::getInstance().broadcastEquipList(playerCharacter, region, isFilterSelf);
	}

	//--------------------------------------------------------------------------
	void SRegionNetPacketProcesser::broadcastDisappearPlayerCharacterToRegionToSelf( SCharacter* playerCharacter, std::map<UInt, SSceneGrid*>& regionGridList, Bool isFilterSelf )
	{
#if 0
		//--------------------------------------------------------------------------

		SSceneGrid* regionGrid = NULL;
		SPlayer* myPlayer = NULL;//playerCharacter->getOwnerPlayer();
		if(!myPlayer)
		{
			DYNAMIC_EEXCEPT_LOG("SRegionNetPacketProcesser::broadcastDisappearPlayerCharacterToRegionToSelf : not find player!");
			return;
		}

		//--------------------------------------------------------------------------

		for(std::map<UInt, SSceneGrid*>::iterator regionGridIt = regionGridList.begin(); regionGridIt != regionGridList.end(); ++regionGridIt)
		{
			SPlayerCharacter* otherPlayerCharacter = NULL;
			regionGrid = regionGridIt->second;
			std::map<PlayerCharacterIdType, SPlayerCharacter*>* playerCharacterList = regionGrid->getPlayerCharacterList();
			for(std::map<PlayerCharacterIdType, SPlayerCharacter*>::iterator playerCharacterIt = playerCharacterList->begin(); playerCharacterIt != playerCharacterList->end(); ++playerCharacterIt)
			{
				otherPlayerCharacter = playerCharacterIt->second;
				if(isFilterSelf && playerCharacter == otherPlayerCharacter)
				{
					continue;
				}

				if(otherPlayerCharacter->isDead())
				{
					continue;
				}

				broadcastDestroyAndDisappearPlayerCharacterToRegionToSelf(otherPlayerCharacter, myPlayer);
			}
		}
#endif
	}

	//--------------------------------------------------------------------------
	void SRegionNetPacketProcesser::broadcastDisappearPlayerCharacterToRegionToOther( SCharacter* playerCharacter, SRegionObjectBase* region, Bool isFilterSelf )
	{
		broadcastDestroyAndDisappearPlayerCharacterToRegionToOther(playerCharacter, region, isFilterSelf);
	}

	//--------------------------------------------------------------------------
	void SRegionNetPacketProcesser::broadcastAppearPlayerCharacterToRegionToSelf(SPlayerCharacter* playerCharacter, SRegionObjectBase* region)
	{
#if 0
		SSceneGrid* regionGrid = NULL;
		std::map<UInt, SSceneGrid*>* interactionGridList = &(playerCharacter->getSceneObjectInSceneGridsManager()->interactionGridList);
		for(std::map<UInt, SSceneGrid*>::iterator regionGridIt = interactionGridList->begin(); regionGridIt != interactionGridList->end(); ++regionGridIt)
		{
			SPlayerCharacter* otherPlayerCharacter = NULL;
			regionGrid = regionGridIt->second;
			std::map<PlayerCharacterIdType, SPlayerCharacter*>* playerCharacterList = regionGrid->getPlayerCharacterList();
			for(std::map<PlayerCharacterIdType, SPlayerCharacter*>::iterator playerCharacterIt = playerCharacterList->begin(); playerCharacterIt != playerCharacterList->end(); ++playerCharacterIt)
			{
				otherPlayerCharacter = playerCharacterIt->second;

				NetTranspondSendDataBufferPtr dataPtr ;
                NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

				GameNetPacketData* packet             = (GameNetPacketData*) dataPtr.getTranspondData();
				if ( packet )
				{
					packet->channel = GNPC_REGION;
					packet->type    = PT_REGION_M2C_APPEAR_PLAYER_CHARACTER;
					PT_REGION_M2C_APPEAR_PLAYER_CHARACTER_DATA* sendData = (PT_REGION_M2C_APPEAR_PLAYER_CHARACTER_DATA*)(packet->data);
					if(sendData)
					{
						sendData->appearPlayerNum = 1;

						sendData->appearPlayerInfo->playerId				= otherPlayerCharacter->getAccountId();
						sendData->appearPlayerInfo->characterIndex			= otherPlayerCharacter->getID();
						WStrnCpyS(sendData->appearPlayerInfo->name, otherPlayerCharacter->getName().c_str(), MAX_CHARACTER_NAME_LEN);
						sendData->appearPlayerInfo->characterTemplateID	= (otherPlayerCharacter)->getPlayerCharacterData()->mCharacterTemplateID;
						sendData->appearPlayerInfo->pos						= ((NetVec2)otherPlayerCharacter->getPos()).getData();
						sendData->appearPlayerInfo->dir						= ((NetVec2)otherPlayerCharacter->getDir()).getData();
						sendData->appearPlayerInfo->hp						= otherPlayerCharacter->getPlayerCharacterData()->mHp;
						sendData->appearPlayerInfo->mp						= otherPlayerCharacter->getPlayerCharacterData()->mMp;
						sendData->appearPlayerInfo->mpmax					= otherPlayerCharacter->getMaxMp();
						sendData->appearPlayerInfo->hpmax					= otherPlayerCharacter->getMaxHp();
						sendData->appearPlayerInfo->force					= otherPlayerCharacter->getForce();
						sendData->appearPlayerInfo->isBattleLeader			= otherPlayerCharacter->getIsBattleLeader();
						sendData->appearPlayerInfo->moveSpeed				= otherPlayerCharacter->getMoveSpeed();

						Int dataSize = GameNetPacketData_INFO::headSize + PT_REGION_M2C_APPEAR_PLAYER_CHARACTER_DATA_INFO::dataSize(sendData);

						SPlayer* myPlayer = NULL;//playerCharacter->getOwnerPlayer();
						if (NULL != myPlayer)
						{
							NetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(
								dataPtr, dataSize,
								myPlayer->getFrontServerId(),
								myPlayer->getClientNetIdInFrontServer(), 
								myPlayer->getAccountId());
						}else
						{
							DYNAMIC_EEXCEPT_LOG("SRegionNetPacketProcesser::broadcastAppearPlayerCharacterToRegionToSelf : not find player!");
						}
					}
				}
			}
		}
#endif
	}

	//--------------------------------------------------------------------------
	void SRegionNetPacketProcesser::broadcastAppearPlayerCharacterToRegionToOther(SPlayerCharacter* playerCharacter, SRegionObjectBase* region)
	{
#if 0
		NetTranspondSendDataBufferPtr dataPtr ;
        NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if ( packet )
		{
			packet->channel = GNPC_REGION;
			packet->type    = PT_REGION_M2C_APPEAR_PLAYER_CHARACTER;
			PT_REGION_M2C_APPEAR_PLAYER_CHARACTER_DATA* sendData = (PT_REGION_M2C_APPEAR_PLAYER_CHARACTER_DATA*)(packet->data);
			if(sendData)
			{
				sendData->appearPlayerNum = 1;

				sendData->appearPlayerInfo->playerId				= playerCharacter->getAccountId();
				sendData->appearPlayerInfo->characterIndex			= playerCharacter->getID();
				WStrnCpyS(sendData->appearPlayerInfo->name, playerCharacter->getName().c_str(), MAX_CHARACTER_NAME_LEN);
				sendData->appearPlayerInfo->characterTemplateID	= (playerCharacter)->getPlayerCharacterData()->mCharacterTemplateID;
				sendData->appearPlayerInfo->pos						= ((NetVec2)playerCharacter->getPos()).getData();
				sendData->appearPlayerInfo->dir						= ((NetVec2)playerCharacter->getDir()).getData();
				sendData->appearPlayerInfo->hp						= playerCharacter->getHp();
				sendData->appearPlayerInfo->mp						= playerCharacter->getMp();
				sendData->appearPlayerInfo->mpmax					= playerCharacter->getMaxMp();
				sendData->appearPlayerInfo->hpmax					= playerCharacter->getMaxHp();
				sendData->appearPlayerInfo->force					= playerCharacter->getForce();
				sendData->appearPlayerInfo->isBattleLeader			= playerCharacter->getIsBattleLeader();
				sendData->appearPlayerInfo->moveSpeed				= playerCharacter->getMoveSpeed();

				Int dataSize = GameNetPacketData_INFO::headSize + PT_REGION_M2C_APPEAR_PLAYER_CHARACTER_DATA_INFO::dataSize(sendData);
				if (region->getRegionType() == ROT_MAP_DISTRIBUTION)
				{
					SPlayer* myPlayer = NULL;//playerCharacter->getOwnerPlayer();
					if (NULL != myPlayer)
					{
						NetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(
							dataPtr, dataSize,
							myPlayer->getFrontServerId(), 
							myPlayer->getClientNetIdInFrontServer(), 
							myPlayer->getAccountId());
					}
				}
				else
				{
					SSceneObjectInSceneGridsManager* sceneObjectInSceneGridsManager = playerCharacter->getSceneObjectInSceneGridsManager();
					NetTranspondPacketProcesser::getInstance().gridsBroadcastClientTranspondPackToFrontServer(
						sceneObjectInSceneGridsManager->currSceneGrid, 
						sceneObjectInSceneGridsManager->lastSceneGrid, 
						dataPtr, dataSize, 0);
				}
			}
		}
#endif
	}

	//--------------------------------------------------------------------------
	void SRegionNetPacketProcesser::broadcastDisappearPlayerCharacterToRegionToSelf(SCharacter* playerCharacter, SRegionObjectBase* region)
	{
#if 0
		SSceneGrid* regionGrid = NULL;
		std::map<UInt, SSceneGrid*>* interactionGridList = &(playerCharacter->getSceneObjectInSceneGridsManager()->interactionGridList);
		for(std::map<UInt, SSceneGrid*>::iterator regionGridIt = interactionGridList->begin(); regionGridIt != interactionGridList->end(); ++regionGridIt)
		{
			SPlayerCharacter* otherPlayerCharacter = NULL;
			regionGrid = regionGridIt->second;
			std::map<PlayerCharacterIdType, SPlayerCharacter*>* playerCharacterList = regionGrid->getPlayerCharacterList();
			for(std::map<PlayerCharacterIdType, SPlayerCharacter*>::iterator playerCharacterIt = playerCharacterList->begin(); playerCharacterIt != playerCharacterList->end(); ++playerCharacterIt)
			{
				otherPlayerCharacter = playerCharacterIt->second;

				NetTranspondSendDataBufferPtr dataPtr;
                NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

				GameNetPacketData* packet				= (GameNetPacketData*) dataPtr.getTranspondData();
				if ( packet )
				{
					packet->channel = GNPC_REGION;
					packet->type    = PT_REGION_M2C_DISAPPEAR_PLAYER_CHARACTER;
					PT_REGION_M2C_DISAPPEAR_PLAYER_CHARACTER_DATA* sendData = (PT_REGION_M2C_DISAPPEAR_PLAYER_CHARACTER_DATA*)(packet->data);
					if( sendData )
					{
						sendData->characterIndex = otherPlayerCharacter->getID();

						Int dataSize = GameNetPacketData_INFO::headSize + PT_REGION_M2C_DISAPPEAR_PLAYER_CHARACTER_DATA_INFO::dataSize;

						SPlayer* myPlayer = NULL;//playerCharacter->getOwnerPlayer();
						if (NULL != myPlayer)
						{
							NetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(dataPtr, dataSize,
								myPlayer->getFrontServerId(), myPlayer->getClientNetIdInFrontServer(), 
								myPlayer->getAccountId());
						}else
						{
							DYNAMIC_EEXCEPT_LOG("SRegionNetPacketProcesser::broadcastDisappearPlayerCharacterToRegionToSelf : not find player!");
						}
					}
				}
			}
		}
#endif
	}

	//--------------------------------------------------------------------------
	void SRegionNetPacketProcesser::broadcastDisappearPlayerCharacterToRegionToOther(SCharacter* playerCharacter, SRegionObjectBase* region)
	{
#if 0
		NetTranspondSendDataBufferPtr dataPtr ;
        NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if(packet)
		{
			packet->type = PT_REGION_M2C_DISAPPEAR_PLAYER_CHARACTER;
			packet->channel = GNPC_REGION;

			PT_REGION_M2C_DISAPPEAR_PLAYER_CHARACTER_DATA* sendData = (PT_REGION_M2C_DISAPPEAR_PLAYER_CHARACTER_DATA*)(packet->data);
			if(sendData)
			{
				sendData->characterIndex = playerCharacter->getID();

				NetTranspondPacketProcesser::getInstance().gridsBroadcastClientTranspondPackToFrontServer(
					playerCharacter->getSceneObjectInSceneGridsManager()->currSceneGrid, 
					NULL, 
					dataPtr,
					GameNetPacketData_INFO::headSize + PT_REGION_M2C_DISAPPEAR_PLAYER_CHARACTER_DATA_INFO::dataSize, 
					0);
			}
		}
#endif
	}

	//--------------------------------------------------------------------------
	void SRegionNetPacketProcesser::broadcastPlayerCharacterAliveToRegion(SPlayerCharacter* playerCharacter, SRegionObjectBase* region)
	{
#if 0
		NetTranspondSendDataBufferPtr dataPtr  ;
        NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if ( packet )
		{
			packet->channel = GNPC_REGION;
			packet->type    = PT_REGION_M2C_PLAYER_CHARACTER_ALIVE;
			PT_REGION_M2C_PLAYER_CHARACTER_ALIVE_DATA* sendData = (PT_REGION_M2C_PLAYER_CHARACTER_ALIVE_DATA*)(packet->data);
			if(sendData)
			{
				sendData->playerInfo.playerId				= playerCharacter->getAccountId();
				sendData->playerInfo.character_id			= playerCharacter->getID();
				WStrnCpyS(sendData->playerInfo.name, playerCharacter->getName().c_str(), MAX_CHARACTER_NAME_LEN);
				sendData->playerInfo.characterTemplateID	= (playerCharacter)->getPlayerCharacterData()->mCharacterTemplateID;
				sendData->playerInfo.pos					= ((NetVec2)playerCharacter->getPos()).getData();
				sendData->playerInfo.dir					= ((NetVec2)playerCharacter->getDir()).getData();
				sendData->playerInfo.hp						= playerCharacter->getHp();
				sendData->playerInfo.mp						= playerCharacter->getMp();
				sendData->playerInfo.hpmax					= playerCharacter->getMaxHp();
				sendData->playerInfo.mpmax					= playerCharacter->getMaxMp();
				sendData->playerInfo.force					= playerCharacter->getForce();
				sendData->playerInfo.isBattleLeader			= playerCharacter->getIsBattleLeader();

				SRegionObjectBase* regionObjectBase = playerCharacter->getCurrentRegionObject();
				if(regionObjectBase)
				{
					NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(
						dataPtr, 
						GameNetPacketData_INFO::headSize + PT_REGION_M2C_PLAYER_CHARACTER_ALIVE_INFO::dataSize, 
						playerCharacter->getSceneObjectInSceneGridsManager()->currSceneGrid, 
						NULL, regionObjectBase, 0);
				}
			}
		}
#endif
	}

	//--------------------------------------------------------------------------
	void SRegionNetPacketProcesser::sendPlayerCharacterAliveToFrontServer(SPlayerCharacter* playerCharacter)
	{
		GameNetSendDataBufferPtr dataPtr;
        MapServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr->getLogicData();

		NetIdType frontServerId = playerCharacter->getFrontServerId();
		if(packet)
		{
			packet->channel = GNPC_REGION;
			packet->type = PT_REGION_M2F_PLAYER_CHARACTER_ALIVE;

			PT_REGION_M2F_PLAYER_CHARACTER_ALIVE_DATA* sendData = (PT_REGION_M2F_PLAYER_CHARACTER_ALIVE_DATA*)packet->data;
			if(sendData)
			{
				sendData->accountId			= playerCharacter->getAccountId();
				sendData->playerCharacterId	= playerCharacter->getID();
				const Int dataSize = GameNetPacketData_INFO::headSize + PT_REGION_M2F_PLAYER_CHARACTER_ALIVE_INFO::dataSize;
				MapServerMain::getInstance().getServerLauncher()->sendServer(dataPtr, dataSize, frontServerId);
			}
		}
	}

	//--------------------------------------------------------------------------
	void SRegionNetPacketProcesser::broadcastTroopEnterToRegion(SCharacter* troop, SRegionObjectBase* region)
	{
#if 0
		NetTranspondSendDataBufferPtr dataPtr ;
        NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if ( packet )
		{
			packet->channel = GNPC_REGION;
			packet->type    = PT_REGION_M2C_ADD_TROOP;
			PT_REGION_M2C_ADD_TROOP_DATA* sendData = (PT_REGION_M2C_ADD_TROOP_DATA*)(packet->data);
			if(sendData)
			{
				sendData->addTroopNum = 1;

				STroop*	tempTroop = (STroop*)troop;
				//开始填充 Begin
				sendData->addTroopInfo->force			= (tempTroop->getParentPlayer())->getPlayerCharacterList()->begin()->second->getForce();
				sendData->addTroopInfo->playerId		= tempTroop->getParentPlayer()->getAccountId();
				sendData->addTroopInfo->troopId			= tempTroop->getID();
				sendData->addTroopInfo->troopTemplateId = tempTroop->getTroopData()->mCharacterTemplateID;
				sendData->addTroopInfo->pos				= ((NetVec2)tempTroop->getPos()).getData();
				sendData->addTroopInfo->dir				= ((NetVec2)tempTroop->getDir()).getData();
				sendData->addTroopInfo->hp				= tempTroop->getHp();
				sendData->addTroopInfo->mp				= tempTroop->getMp();
				sendData->addTroopInfo->maxHp			= tempTroop->getMaxHp();
				sendData->addTroopInfo->maxMp			= tempTroop->getMaxMp();
				sendData->addTroopInfo->moveSpeed       = tempTroop->getSAttributeSystem()->getMoveSpeed();
				sendData->addTroopInfo->soldierNum		= tempTroop->getSoldierNum();

				//开始填充 End
				NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(
					dataPtr, 
					GameNetPacketData_INFO::headSize + PT_REGION_M2C_ADD_TROOP_INFO::dataSize(sendData), 
					region);
			}
		}
#endif
	}

	//--------------------------------------------------------------------------
	void SRegionNetPacketProcesser::broadcastTroopLeaveToRegion(SCharacter* troop, SRegionObjectBase* region)
	{
	}

	//--------------------------------------------------------------------------
	void SRegionNetPacketProcesser::sendBattleBuildingListToPlayer_NEW( SPlayer* player, std::map<BuildingIdType, GameObject*>* buildingList )
	{
	}

	//--------------------------------------------------------------------------
	void SRegionNetPacketProcesser::broadcastBattleBuildingEnterToRegion_NEW(SCharacter* building, SRegionObjectBase* region)
	{
	}

	//--------------------------------------------------------------------------
	void SRegionNetPacketProcesser::broadcastBattleBuildingLeaveToRegion_NEW(SCharacter* building, SRegionObjectBase* region)
	{

		NetTranspondSendDataBufferPtr dataPtr ;
        NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if ( packet )
		{
			packet->channel = GNPC_REGION;
			packet->type    = PT_REGION_M2C_REMOVE_BUILDING;
			PT_REGION_M2C_REMOVE_BUILDING_DATA* sendData = (PT_REGION_M2C_REMOVE_BUILDING_DATA*)(packet->data);
			if(sendData)
			{
				sendData->buildingId = building->getID();
				NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(
					dataPtr,
					GameNetPacketData_INFO::headSize + PT_REGION_M2C_REMOVE_BUILDING_DATA_INFO::dataSize,
					region);
			}
		}
	}

	//----------------------------------------------------------------------------------------------------------------------
	void SRegionNetPacketProcesser::broadcastMonsterAliveToRegion(SMonster* monster, SRegionObjectBase* region)
	{
#if 0
		NetTranspondSendDataBufferPtr dataPtr  ;
        NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if ( packet )
		{
			packet->channel = GNPC_REGION;
			packet->type    = PT_REGION_M2C_MONSTER_ALIVE;
			PT_REGION_M2C_MONSTER_ALIVE_DATA* sendData = (PT_REGION_M2C_MONSTER_ALIVE_DATA*)(packet->data);
			if(sendData)
			{
				sendData->monsterInfo.monsterId				= monster->getID();
				sendData->monsterInfo.charTemplateId		= monster->getCharacterTemplateID();
				sendData->monsterInfo.pos					= ((NetVec2)monster->getPos()).getData();
				sendData->monsterInfo.dir					= ((NetVec2)monster->getDir()).getData();
				sendData->monsterInfo.maxHp					= monster->getMaxHp();
				sendData->monsterInfo.maxMp					= monster->getMaxMp();
				sendData->monsterInfo.hp					= monster->getHp();
				sendData->monsterInfo.mp					= monster->getMp();
				sendData->monsterInfo.moveSpeed				= monster->getMoveSpeed();

				SRegionObjectBase* regionObjectBase = monster->getCurrentRegionObject();
				if(regionObjectBase)
				{
					NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(
						dataPtr, 
						GameNetPacketData_INFO::headSize + PT_REGION_M2C_MONSTER_ALIVE_INFO::dataSize, 
						monster->getSceneObjectInSceneGridsManager()->currSceneGrid, 
						NULL, regionObjectBase, 0);
				}
			}
		}
#endif
	}

	//----------------------------------------------------------------------------------------------------------------------
	void SRegionNetPacketProcesser::broadcastMonsterAppearToRegion( SPlayerCharacter* playerCharacter, std::map<UInt, SSceneGrid*>& regionGridList )
	{
		broadcastMonsterCreateAndAppearToRegion(playerCharacter, regionGridList);
	}

	//----------------------------------------------------------------------------------------------------------------------
	void SRegionNetPacketProcesser::broadcastMonsterDisappearToRegion( SPlayerCharacter* playerCharacter, std::map<UInt, SSceneGrid*>& regionGridList )
	{
		broadcastMonsterDestroyAndDisappearToRegion(playerCharacter, regionGridList);
	}

	//----------------------------------------------------------------------------------------------------------------------
	void SRegionNetPacketProcesser::broadcastMonsterCreateAndAppearToRegion( SPlayerCharacter* playerCharacter, std::map<UInt, SSceneGrid*>& regionGridList )
	{

		//---------------------------------------------------------------------

		if(!playerCharacter)
		{
			DYNAMIC_EEXCEPT_LOG(" SRegionNetPacketProcesser::broadcastMonsterCreateAndAppearToRegion : not find playerCharacter");
			return;
		}

		SSceneGrid* regionGrid = NULL;
		SPlayer* myPlayer = NULL;//playerCharacter->getOwnerPlayer();
		if(!myPlayer)
		{
			DYNAMIC_EEXCEPT_LOG(" SRegionNetPacketProcesser::broadcastMonsterCreateAndAppearToRegion : not find player");
			return;
		}

		//---------------------------------------------------------------------
		// 发送的数据缓存智能指针
		NetTranspondSendDataBufferPtr dataPtr;
		// 发送的逻辑数据指针
		GameNetPacketData*  packet = NULL;
		PT_REGION_M2C_CREATE_APPEAR_MONSTER_DATA* sendData = NULL;
		// 当前发送数据头大小
		I32 sendDataHeadSize    = 0;
		// 当前发送数据大小
		I32 sendDataSize        = 0;
		// 准备发送数据大小
		I32 prepareSendDataSize = 0;
	
		//---------------------------------------------------------------------

		for(std::map<UInt, SSceneGrid*>::iterator regionGridIt = regionGridList.begin(); regionGridIt != regionGridList.end(); ++regionGridIt)
		{
			SMonster* monster = NULL;
			regionGrid = regionGridIt->second;

			std::map<MonsterIdType, SMonster*>* monsterList;// = regionGrid->getMonsterList();
			for(std::map<MonsterIdType, SMonster*>::iterator monsterIt = monsterList->begin(); monsterIt != monsterList->end(); ++monsterIt)
			{
				//---------------------------------------------------------------------

				monster = monsterIt->second;

				if(monster->isDead())
				{
					continue;
				}

				//---------------------------------------------------------------------

				if ( dataPtr.mDataPtr.isNull() == false )
				{
					prepareSendDataSize = sendDataSize + PT_REGION_M2C_CREATE_APPEAR_MONSTER_DATA_INFO::netAddInfoSize;

					// 如果大于缓存最大大小则发送
					if ( prepareSendDataSize >= dataPtr.getTranspondDataMaxSize(100) )
					{

						NetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(
							dataPtr, sendDataSize, 
							myPlayer->getFrontServerId(), 
							myPlayer->getClientNetIdInFrontServer(), 
							myPlayer->getAccountId());

						dataPtr.mDataPtr.setNull();
					}
				}

				//---------------------------------------------------------------------
				// create new send buff
				if ( dataPtr.mDataPtr.isNull() )
				{
					NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );
					packet	= (GameNetPacketData*) dataPtr.getTranspondData();
					if ( !packet )
					{
						return;
					}

					packet->channel = GNPC_REGION;
					packet->type    = PT_REGION_M2C_CREATE_APPEAR_MONSTER;
					sendData		= (PT_REGION_M2C_CREATE_APPEAR_MONSTER_DATA*)(packet->data);
					if( !sendData )
					{
						return;
					}
					sendData->addNum = 0;
					sendData->regionId	 = 0;//myPlayer->getCurrentRegionObj()->getRegionId();

					sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_REGION_M2C_CREATE_APPEAR_MONSTER_DATA_INFO::headSize;
					sendDataSize        = sendDataHeadSize;
					prepareSendDataSize = sendDataHeadSize;
				}

				//---------------------------------------------------------------------

				NetAddMonsterInfo* tempSend = &(sendData->addInfo[sendData->addNum]);
				tempSend->monsterId			= monster->getID();
				tempSend->charTemplateId	= monster->getCharacterTemplateID();
				tempSend->pos				= ((NetVec2)monster->getPos()).getData();

				SCharacterMoveToAction* moveToAction = (SCharacterMoveToAction*)monster->getActionManager()->getState("SCharacterMoveToAction", false);
				if(moveToAction)
				{
					tempSend->moveToPos			= ((NetVec2)moveToAction->getMoveToPos()).getData();
				}
				else
				{
					tempSend->moveToPos          = ((NetVec2)Vec3(0,0,0)).getData();
				}

				tempSend->dir				= ((NetVec2)monster->getDir()).getData();
				tempSend->maxHp				= monster->getMaxHp();
				tempSend->maxMp				= monster->getMaxMp();
				tempSend->hp				= monster->getHp();
				tempSend->mp				= monster->getMp();
				tempSend->moveSpeed			= monster->getMoveSpeed();

				sendDataSize +=PT_REGION_M2C_CREATE_APPEAR_MONSTER_DATA_INFO::netAddInfoSize;

				++sendData->addNum;
			}

			//---------------------------------------------------------------------

			if ( dataPtr.mDataPtr.isNull() == false )
			{
				NetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(
					dataPtr, sendDataSize, 
					myPlayer->getFrontServerId(), 
					myPlayer->getClientNetIdInFrontServer(), 
					myPlayer->getAccountId());
				dataPtr.mDataPtr.setNull();
			}
		}
	}

	//----------------------------------------------------------------------------------------------------------------------
	void SRegionNetPacketProcesser::broadcastMonsterDestroyAndDisappearToRegion( SPlayerCharacter* playerCharacter, std::map<UInt, SSceneGrid*>& regionGridList )
	{
#if 0
		//---------------------------------------------------------------------

		if(!playerCharacter)
		{
			return;
		}

		SSceneGrid* regionGrid = NULL;
		SPlayer* myPlayer = NULL;//playerCharacter->getOwnerPlayer();
		if(!myPlayer)
		{
			return;
		}

		//---------------------------------------------------------------------

		NetTranspondSendDataBufferPtr dataPtr ;
		GameNetPacketData* packet	= NULL;
		PT_REGION_M2C_DESTROY_DISAPPEAR_MONSTER_DATA* sendData = NULL;
		// 当前发送数据头大小
		I32 sendDataHeadSize    = 0;
		// 当前发送数据大小
		I32 sendDataSize        = 0;
		// 准备发送数据大小
		I32 prepareSendDataSize = 0;

		for(std::map<UInt, SSceneGrid*>::iterator regionGridIt = regionGridList.begin(); regionGridIt != regionGridList.end(); ++regionGridIt)
		{
			SMonster* monster = NULL;
			regionGrid = regionGridIt->second;

			std::map<MonsterIdType, SMonster*>* monsterList = regionGrid->getMonsterList();
			for(std::map<MonsterIdType, SMonster*>::iterator monsterIt = monsterList->begin(); monsterIt != monsterList->end(); ++monsterIt)
			{
				//---------------------------------------------------------------------

				monster = monsterIt->second;

				if (monster->isDead())
				{
					continue;
				}

				//---------------------------------------------------------------------

				if ( dataPtr.mDataPtr.isNull() == false )
				{
					// 递增一个角色数据大小到发送数据缓存大小
					prepareSendDataSize = sendDataSize + PT_REGION_M2C_DESTROY_DISAPPEAR_MONSTER_DATA_INFO::netAddInfoSize;

					// 如果大于缓存最大大小则发送
					if ( prepareSendDataSize >= dataPtr.getTranspondDataMaxSize(100) )
					{
						NetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(
							dataPtr, sendDataSize,
							myPlayer->getFrontServerId(), 
							myPlayer->getClientNetIdInFrontServer(), 
							myPlayer->getAccountId());
						dataPtr.mDataPtr.setNull();
					}
				}

				//---------------------------------------------------------------------

				if ( dataPtr.mDataPtr.isNull() )
				{
					NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );
					packet	= (GameNetPacketData*) dataPtr.getTranspondData();
					if ( !packet )
					{
						return;
					}

					packet->channel = GNPC_REGION;
					packet->type    = PT_REGION_M2C_DESTROY_DISAPPEAR_MONSTER;
					sendData = (PT_REGION_M2C_DESTROY_DISAPPEAR_MONSTER_DATA*)(packet->data);
					if(!sendData)
					{
						return;
					}
					sendData->num = 0;
					sendData->regionId	 = myPlayer->getCurrentRegionObj()->getRegionId();

					sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_REGION_M2C_DESTROY_DISAPPEAR_MONSTER_DATA_INFO::headSize;
					sendDataSize        = sendDataHeadSize;
					prepareSendDataSize = sendDataHeadSize;
				}

				//---------------------------------------------------------------------

				sendData->monsterIndex[sendData->num] = monster->getID();

				sendDataSize += PT_REGION_M2C_DESTROY_DISAPPEAR_MONSTER_DATA_INFO::netAddInfoSize;

				++sendData->num;
			}

			//---------------------------------------------------------------------

			if ( dataPtr.mDataPtr.isNull() == false )
			{
				NetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(
					dataPtr, sendDataSize, 
					myPlayer->getFrontServerId(), 
					myPlayer->getClientNetIdInFrontServer(), 
					myPlayer->getAccountId());
				dataPtr.mDataPtr.setNull();
            }
		}
#endif
	}

	//--------------------------------------------------------------------------
	void SRegionNetPacketProcesser::sendMonsterListToPlayer( SPlayer* toPlayer, std::map<MonsterIdType, SMonster*>* monsterList)
	{
#if 0
		//---------------------------------------------------------------------

		NetTranspondSendDataBufferPtr dataPtr  ;
		GameNetPacketData* packet = NULL;
		PT_REGION_M2C_ADD_MONSTER_DATA* sendData = NULL;
		// 当前发送数据头大小
		I32 sendDataHeadSize    = 0;
		// 当前发送数据大小
		I32 sendDataSize        = 0;
		// 准备发送数据大小
		I32 prepareSendDataSize = 0;

		// 遍历角色队列
		std::map<GameObjectIdType, SMonster*>::iterator iter = monsterList->begin();
		for(; iter != monsterList->end(); ++iter )
		{

			//---------------------------------------------------------------------

			if (iter->second->isDead())
			{
				continue;
			}

			//---------------------------------------------------------------------

			if ( dataPtr.mDataPtr.isNull() == false )
			{
				// 递增一个角色数据大小到发送数据缓存大小
				prepareSendDataSize = sendDataSize + PT_REGION_M2C_ADD_MONSTER_INFO::netAddInfoSize;

				// 如果大于缓存最大大小则发送
				if ( prepareSendDataSize >= dataPtr.getTranspondDataMaxSize(100) )
				{
					NetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(dataPtr, sendDataSize, 
						toPlayer->getFrontServerId(), toPlayer->getClientNetIdInFrontServer(), toPlayer->getAccountId());
					dataPtr.mDataPtr.setNull();
				}
			}

			//---------------------------------------------------------------------

			if ( dataPtr.mDataPtr.isNull() )
			{
				NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );
				packet			= (GameNetPacketData*) dataPtr.getTranspondData();
				if ( !packet )
					return;
				packet->channel		= GNPC_REGION;
				packet->type		= PT_REGION_M2C_ADD_MONSTER;

				sendData = (PT_REGION_M2C_ADD_MONSTER_DATA*)(packet->data);
				sendData->addNum	= 0;
				sendData->regionId	= toPlayer->getCurrentRegionObj()->getRegionId();

				sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_REGION_M2C_ADD_MONSTER_INFO::headSize;
				sendDataSize        = sendDataHeadSize;
				prepareSendDataSize = sendDataHeadSize;
			}

			//---------------------------------------------------------------------

			NetAddMonsterInfo* tempSend = &(sendData->addInfo[sendData->addNum]);
			tempSend->monsterId			= iter->second->getID();
			tempSend->charTemplateId	= iter->second->getCharacterTemplateID();
			tempSend->pos				= ((NetVec2)iter->second->getPos()).getData();
			tempSend->dir				= ((NetVec2)iter->second->getDir()).getData();
			tempSend->maxHp				= iter->second->getMaxHp();
			tempSend->maxMp				= iter->second->getMaxMp();
			tempSend->hp				= iter->second->getHp();
			tempSend->mp				= iter->second->getMp();
			tempSend->moveSpeed			= iter->second->getMoveSpeed();

			sendDataSize += PT_REGION_M2C_ADD_MONSTER_INFO::netAddInfoSize;

			++sendData->addNum;
		}

		//---------------------------------------------------------------------

		if ( dataPtr.mDataPtr.isNull() == false )
		{
			NetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(
				dataPtr, sendDataSize, 
				toPlayer->getFrontServerId(), 
				toPlayer->getClientNetIdInFrontServer(), 
				toPlayer->getAccountId());
            dataPtr.mDataPtr.setNull();
		}
#endif
	}

	//--------------------------------------------------------------------------
	void SRegionNetPacketProcesser::sendCampListToPlayer( SPlayer* toPlayer, std::map<CampIdType, SCamp*>* campList)
	{
		//---------------------------------------------------------------------

		//if (true == campList->empty())
		//{
		//	//必须要有军营
		//	DYNAMIC_ASSERT(0);
		//	return;
		//}

		//---------------------------------------------------------------------

		NetTranspondSendDataBufferPtr dataPtr ;
		GameNetPacketData* packet       = NULL;
		PT_REGION_M2C_ADD_BUILDING_DATA* sendData = NULL;
		// 当前发送数据头大小
		I32 sendDataHeadSize    = 0;
		// 当前发送数据大小
		I32 sendDataSize        = 0;
		// 准备发送数据大小
		I32 prepareSendDataSize = 0;

		// 遍历角色队列
		std::map<CampIdType, SCamp*>::iterator iter = campList->begin();
		for( ; campList->end() != iter; ++iter)
		{

			//---------------------------------------------------------------------

			if ( dataPtr.mDataPtr.isNull() == false )
			{
				// 递增一个角色数据大小到发送数据缓存大小
				prepareSendDataSize = sendDataSize + PT_REGION_M2C_ADD_BUILDING_INFO::netAddBuildingInfoSize;

				// 如果大于缓存最大大小则发送
				if ( prepareSendDataSize >= dataPtr.getTranspondDataMaxSize(100) )
				{
					NetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(
						dataPtr, sendDataSize, 
						toPlayer->getFrontServerId(), 
						toPlayer->getClientNetIdInFrontServer(), 
						toPlayer->getAccountId());
					dataPtr.mDataPtr.setNull() ;
				}
			}

			//---------------------------------------------------------------------

			if ( dataPtr.mDataPtr.isNull() )
			{
				NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );
				packet       = (GameNetPacketData*) dataPtr.getTranspondData();
				if (! packet )
					return;

				packet->channel = GNPC_REGION;
				packet->type    = PT_REGION_M2C_ADD_BUILDING;
				sendData = (PT_REGION_M2C_ADD_BUILDING_DATA*)(packet->data);
				sendData->addBuildingNum = 0;

				sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_REGION_M2C_ADD_BUILDING_INFO::headSize;
				sendDataSize        = sendDataHeadSize;
				prepareSendDataSize = sendDataHeadSize;
			}

			//---------------------------------------------------------------------

			SCamp* tempCamp = iter->second;
			NetAddBuildingInfo* tempSend 	= &(sendData->addBuildingInfo[sendData->addBuildingNum]);
			tempSend->uId			 		= tempCamp->getID();
			tempSend->belongAccountId		= tempCamp->getAccountId();
			tempSend->buildingTemplateId	= tempCamp->getCampTemplateId();
			tempSend->buildingType			= CHAR_BUILD_TYPE_BARRACKS;
			tempSend->force		 			= tempCamp->getForce();
			tempSend->pos					= ((NetVec2)tempCamp->getPos()).getData();
			tempSend->dir					= ((NetVec2)tempCamp->getDir()).getData();
			tempSend->regionId				= 0;
			tempSend->hp					= tempCamp->getHp();

			sendDataSize += PT_REGION_M2C_ADD_BUILDING_INFO::netAddBuildingInfoSize;

			++sendData->addBuildingNum;
		}

		//---------------------------------------------------------------------

		if ( dataPtr.mDataPtr.isNull() == false )
		{
			NetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(
				dataPtr, sendDataSize, 
				toPlayer->getFrontServerId(), 
				toPlayer->getClientNetIdInFrontServer(), 
				toPlayer->getAccountId());
			dataPtr.mDataPtr.setNull() ;
		}
	}

	//--------------------------------------------------------------------------
	void SRegionNetPacketProcesser::sendBuildingListToPlayer( SPlayer* toPlayer, std::map<BuildingIdType, SBuilding*>* buildingList)
	{
		//---------------------------------------------------------------------

		NetTranspondSendDataBufferPtr dataPtr  ;
		GameNetPacketData* packet = NULL;
		PT_REGION_M2C_ADD_BUILDING_DATA* sendData = NULL;

		// 当前发送数据头大小
		I32 sendDataHeadSize    = 0;
		// 当前发送数据大小
		I32 sendDataSize        = 0;
		// 准备发送数据大小
		I32 prepareSendDataSize = 0;

		// 遍历角色队列
		std::map<BuildingIdType, SBuilding*>::iterator iter = buildingList->begin();
		for(; buildingList->end() != iter; ++iter)
		{
			SBuilding* tempBuilding = iter->second;

			//---------------------------------------------------------------------

			if ( dataPtr.mDataPtr.isNull() == false )
			{
				// 递增一个角色数据大小到发送数据缓存大小
				prepareSendDataSize = sendDataSize + PT_REGION_M2C_ADD_BUILDING_INFO::netAddBuildingInfoSize;

				// 如果大于缓存最大大小则发送
				if ( prepareSendDataSize >= dataPtr.getTranspondDataMaxSize(100) )
				{
					NetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(
						dataPtr, sendDataSize, 
						toPlayer->getFrontServerId(), 
						toPlayer->getClientNetIdInFrontServer(), 
						toPlayer->getAccountId());
					dataPtr.mDataPtr.setNull() ;
				}
			}

			//---------------------------------------------------------------------

			if ( dataPtr.mDataPtr.isNull() )
			{
				NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );
				packet	= (GameNetPacketData*) dataPtr.getTranspondData();
				if ( !packet )
					return;

				packet->channel = GNPC_REGION;
				packet->type    = PT_REGION_M2C_ADD_BUILDING;
				sendData		= (PT_REGION_M2C_ADD_BUILDING_DATA*)(packet->data);

				sendData->addBuildingNum = 0;

				sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_REGION_M2C_ADD_BUILDING_INFO::headSize;;
				sendDataSize        = sendDataHeadSize;
				prepareSendDataSize = sendDataHeadSize;
			}

			//---------------------------------------------------------------------
		
			NetAddBuildingInfo* tempSend 	= &(sendData->addBuildingInfo[sendData->addBuildingNum]);
			tempSend->uId			 		= tempBuilding->getID();
			tempSend->belongAccountId		= tempBuilding->getAccountId();
			tempSend->buildingTemplateId	= tempBuilding->getBuildingData()->mCharacterTemplateID;
			tempSend->buildingType			= tempBuilding->getBuildingType();
			tempSend->force		 			= tempBuilding->getForce();
			tempSend->pos					= ((NetVec2)tempBuilding->getPos()).getData();
			tempSend->dir					= ((NetVec2)tempBuilding->getDir()).getData();
			tempSend->regionId				= 0;
			tempSend->hp					= tempBuilding->getHp();

			sendDataSize += PT_REGION_M2C_ADD_BUILDING_INFO::netAddBuildingInfoSize;

			++sendData->addBuildingNum;
		}

		//---------------------------------------------------------------------

		if ( dataPtr.mDataPtr.isNull() == false )
		{
			NetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(
				dataPtr, sendDataSize, 
				toPlayer->getFrontServerId(), 
				toPlayer->getClientNetIdInFrontServer(), 
				toPlayer->getAccountId());
			dataPtr.mDataPtr.setNull();
		}
	}

	//--------------------------------------------------------------------------
	void SRegionNetPacketProcesser::broadcastBuildingEnterToRegion(SBuilding* building, SRegionObjectBase* region)
	{
		NetTranspondSendDataBufferPtr dataPtr ;
        NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );
		GameNetPacketData* packet             = (GameNetPacketData*) dataPtr.getTranspondData();
		if ( !packet )
			return;
		
		packet->channel = GNPC_REGION;
		packet->type    = PT_REGION_M2C_ADD_BUILDING;
		PT_REGION_M2C_ADD_BUILDING_DATA* sendData = (PT_REGION_M2C_ADD_BUILDING_DATA*)(packet->data);
		if(sendData)
		{
			sendData->addBuildingNum = 1;

			sendData->addBuildingInfo->uId					= building->getID();
			sendData->addBuildingInfo->belongAccountId		= building->getAccountId();
			sendData->addBuildingInfo->buildingTemplateId	= building->getBuildingData()->mCharacterTemplateID;
			sendData->addBuildingInfo->buildingType			= building->getBuildingType();
			sendData->addBuildingInfo->force				= building->getForce();
			sendData->addBuildingInfo->pos					= ((NetVec2)building->getPos()).getData();
			sendData->addBuildingInfo->dir					= ((NetVec2)building->getDir()).getData();
			sendData->addBuildingInfo->regionId				= 0;
			sendData->addBuildingInfo->hp					= building->getHp();

			NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(dataPtr, 
				GameNetPacketData_INFO::headSize + PT_REGION_M2C_ADD_BUILDING_INFO::dataSize(sendData), region);
		}
	}

	//--------------------------------------------------------------------------
	void SRegionNetPacketProcesser::broadcastCampEnterToRegion(SCamp* camp, SRegionObjectBase* region)
	{
		NetTranspondSendDataBufferPtr dataPtr ;
        NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if ( packet )
		{
			packet->channel = GNPC_REGION;
			packet->type    = PT_REGION_M2C_ADD_BUILDING;
			PT_REGION_M2C_ADD_BUILDING_DATA* sendData = (PT_REGION_M2C_ADD_BUILDING_DATA*)(packet->data);
			if(sendData)
			{
				sendData->addBuildingNum = 1;
				
				sendData->addBuildingInfo->uId					= camp->getID();
				sendData->addBuildingInfo->belongAccountId		= camp->getAccountId();
				sendData->addBuildingInfo->buildingTemplateId	= camp->getCampTemplateId();
				sendData->addBuildingInfo->buildingType			= CHAR_BUILD_TYPE_BARRACKS;
				sendData->addBuildingInfo->force				= camp->getForce();
				sendData->addBuildingInfo->pos				= ((NetVec2)camp->getPos()).getData();
				sendData->addBuildingInfo->dir				= ((NetVec2)camp->getDir()).getData();
				sendData->addBuildingInfo->regionId				= 0;
				sendData->addBuildingInfo->hp					= camp->getHp();

				NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(dataPtr, 
					GameNetPacketData_INFO::headSize + PT_REGION_M2C_ADD_BUILDING_INFO::dataSize(sendData), region);
			}
		}
	}

	//--------------------------------------------------------------------------
	void SRegionNetPacketProcesser::sendTroopListToPlayer( SPlayer* toPlayer, std::map<TroopIdType, SCharacter*>* troopList)
	{
		//--------------------------------------------------------------------------
#if 0
		if (true == troopList->empty())
		{
			//DYNAMIC_EEXCEPT_LOG("SRegionNetPacketProcesser::sendTroopListToPlayer : troopList is empty!");
			return;
		}

		//--------------------------------------------------------------------------

		NetTranspondSendDataBufferPtr dataPtr;
		GameNetPacketData* packet	  = NULL;
		PT_REGION_M2C_ADD_TROOP_DATA* sendData = NULL;

		// 当前发送数据头大小
		I32 sendDataHeadSize    = 0;
		// 当前发送数据大小
		I32 sendDataSize        = 0;
		// 准备发送数据大小
		I32 prepareSendDataSize = 0;

		// 遍历角色队列
		std::map<TroopIdType, SCharacter*>::iterator iter = troopList->begin();
		while( troopList->end() != iter )
		{

			//--------------------------------------------------------------------------

			if ( dataPtr.mDataPtr.isNull() == false )
			{
				// 递增一个角色数据大小到发送数据缓存大小
				prepareSendDataSize = sendDataSize + PT_REGION_M2C_ADD_TROOP_INFO::netAddTroopInfoSize;

				// 如果大于缓存最大大小则发送
				if ( prepareSendDataSize >= dataPtr.getTranspondDataMaxSize(100) )
				{	
					NetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(
						dataPtr, sendDataSize, 
						toPlayer->getFrontServerId(), 
						toPlayer->getClientNetIdInFrontServer(), 
						toPlayer->getAccountId());
			
					dataPtr.mDataPtr.setNull() ;
				}
			}

			//--------------------------------------------------------------------------

			if ( dataPtr.mDataPtr.isNull() )
			{
				NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );
				packet       = (GameNetPacketData*) dataPtr.getTranspondData();
				if ( !packet )
					return;

				packet->channel = GNPC_REGION;
				packet->type    = PT_REGION_M2C_ADD_TROOP;
				sendData = (PT_REGION_M2C_ADD_TROOP_DATA*)(packet->data);
				sendData->addTroopNum = 0;

				sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_REGION_M2C_ADD_TROOP_INFO::headSize;
				sendDataSize        = sendDataHeadSize;
				prepareSendDataSize = sendDataHeadSize;
			}

			//--------------------------------------------------------------------------

			STroop* tempTroop = (STroop*)iter->second;
			NetAddTroopInfo* tempSend 	= &(sendData->addTroopInfo[sendData->addTroopNum]);
			
			SPlayer* tempParentPlayer = tempTroop->getParentPlayer();
			SPlayerCharacter* tempPlayerCharacter = NULL;//(SPlayerCharacter*)tempParentPlayer->getPlayerCharacterList()->begin()->second;
			tempSend->force				= tempPlayerCharacter->getForce();
			tempSend->playerId			= tempTroop->getAccountId();
			tempSend->troopId			= tempTroop->getID();
			tempSend->troopTemplateId	= tempTroop->getTroopData()->mCharacterTemplateID;
			tempSend->pos				= ((NetVec2)tempTroop->getPos()).getData();
			tempSend->dir				= ((NetVec2)tempTroop->getDir()).getData();
			tempSend->hp				= (Int)tempTroop->getHp();
			tempSend->mp				= (Int)tempTroop->getMp();
			tempSend->maxHp				= (Int)tempTroop->getMaxHp();
			tempSend->maxMp				= (Int)tempTroop->getMaxMp();
			tempSend->moveSpeed			= tempTroop->getSAttributeSystem()->getMoveSpeed();
			tempSend->soldierNum		= tempTroop->getSoldierNum();

			sendDataSize += PT_REGION_M2C_ADD_TROOP_INFO::netAddTroopInfoSize;

			++sendData->addTroopNum;
			++iter;
		}

		//--------------------------------------------------------------------------

		if ( dataPtr.mDataPtr.isNull() == false )
		{
			NetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(
				dataPtr, sendDataSize, 
				toPlayer->getFrontServerId(), 
				toPlayer->getClientNetIdInFrontServer(), 
				toPlayer->getAccountId());
			dataPtr.mDataPtr.setNull() ;
		}
#endif
	}

	//--------------------------------------------------------------------------------------------------------------------------
	void SRegionNetPacketProcesser::sendCreateTroopGroupToOwnerPlayer(STroopGroup* newTroopGroup, SRegionObjectBase* regionObj, Int index)
	{
#if 0
		//------------------------------------------------------

		if ( true == newTroopGroup->getIsInitTroopPos())
		{
			DYNAMIC_EEXCEPT_LOG("SRegionNetPacketProcesser::sendCreateTroopGroupToOwnerPlayer : not InitTroopPos");
			return;
		}

		SPlayerIdentifyInfoInCamp* playerIndentify = (newTroopGroup->getOwnerCamp())->getSPlayerIdentifyInfo();
		if ( NULL == playerIndentify )
		{
			DYNAMIC_EEXCEPT_LOG("SRegionNetPacketProcesser::sendCreateTroopGroupToOwnerPlayer : not find playerIndentify!");
			return;
		}

		//------------------------------------------------------
		
		NetTranspondSendDataBufferPtr dataPtr  ;
        NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );
		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if ( !packet )
			return;

		I32 sendDataSize = GameNetPacketData_INFO::headSize + PT_REGION_M2C_CREATE_TROOP_INFO::dataSize;

		PT_REGION_M2C_CREATE_TROOP_DATA* sendData = (PT_REGION_M2C_CREATE_TROOP_DATA*)(packet->data);
		
		if(sendData)
		{
			packet->channel = GNPC_REGION;
			packet->type    = PT_REGION_M2C_CREATE_TROOP;

#if 0
			sendData->troopGroupId	= newTroopGroup->getID();
			sendData->troopTemplateId = newTroopGroup->getCharacterTemplateID();
			sendData->troopNum		= newTroopGroup->getTroopList()->size();
			sendData->soldierNum	= newTroopGroup->getSoldierNum() / sendData->troopNum;

			sendData->pos			= ((NetVec2)newTroopGroup->getOwnerCamp()->getTroopBornPos(index)).getData();
			sendData->dir			= ((NetVec2)newTroopGroup->getOwnerCamp()->getTroopBornDir(index)).getData();
			sendData->regionId		= regionObj->getRegionId();
			sendData->regionType	= (Int)regionObj->getRegionType();
			sendData->instanceId	= regionObj->getParentRegionInstance()->getInstanceUId();
			sendData->campId		= newTroopGroup->getOwnerCamp()->getCampId();
#endif
			NetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(
				dataPtr, sendDataSize, 
				playerIndentify->frontServerId, 
				playerIndentify->clientNetIdInFrontServer, 
				playerIndentify->accountId);
		}
#endif
	}

	//--------------------------------------------------------------------------------------------------------------------------
	void SRegionNetPacketProcesser::sendCreateTroopGroupListToOwnerPlayer(std::map<TroopGroupIdType, STroopGroup*>* troopGroupList, SRegionObjectBase* regionObj)
	{
		Int index = 0;
		for (std::map<TroopGroupIdType, STroopGroup*>::iterator iter = troopGroupList->begin(); iter != troopGroupList->end(); ++iter)
		{
			STroopGroup* troopGroup = iter->second;
			sendCreateTroopGroupToOwnerPlayer(troopGroup, regionObj, index++);
		}
	}


	//--------------------------------------------------------------------------
	void SRegionNetPacketProcesser::onRecvAddBatleFromFrontServer( I32 id , PT_REGION_F2M_ADD_BUILDING_DATA* data)
	{
	}

	//--------------------------------------------------------------------------
	void SRegionNetPacketProcesser::onRecvRemoveBatleFromFrontServer( I32 id , PT_REGION_F2M_REMOVE_BUILDING_DATA* data)
	{
	}

	//--------------------------------------------------------------------------
	void SRegionNetPacketProcesser::onRecvCreateTroopRetFromFrontServer( I32 id , PT_REGION_F2M_CREATE_TROOP_RET_DATA* data)
	{
		AccountIdType accountId		= data->accountId;
		RegionIdType regionId		= data->regionId;
		REGION_OBJ_TYPE regionType	= (REGION_OBJ_TYPE)data->regionType;
		InstanceUIdType instanceUId = data->instanceUId;

		//SWorldManager::getInstance().addTroop(id, accountId, regionId, regionType, instanceUId, data->troopGroupId, data->troopNum, data->troopPos);
	}

	//--------------------------------------------------------------------------
	void SRegionNetPacketProcesser::onRecvAddTroopTestFromFrontServer( I32 id , PT_REGION_C2M_ADD_TROOP_TEST_DATA* data)
	{
		//-------------------------------------------------------------------------

		SPlayer* player = NULL;//SWorldManager::getInstance().getPlayerFromMemory(data->accountId);
		if (NULL == player)
		{
			DYNAMIC_EEXCEPT_LOG("SRegionNetPacketProcesser::onRecvAddTroopTestFromFrontServer : not find player!");
			return;
		}

		//-------------------------------------------------------------------------

		SInstanceRegion* curRegion;// = player->getCurrentRealRegionObj();

		std::map<PlayerCharacterIdType,	SPlayerCharacterPtr>* playerCharacterList;// = player->getPlayerCharacterList();
		//curRegion->getNewRegionObject()->createCampByPlayerForTest((Player*)player, playerCharacterList->begin()->second->getPos());


		//SRegionNetPacketProcesser::getInstance().sendCampListToPlayer((SPlayer*)player, getCampList() );
		//让客户端计算军队的位置
		//sendCreateTroopListToOwnerPlayer(curRegion->getNewRegionObject()->getCampList(), curRegion->getNewRegionObject());
	}

	//--------------------------------------------------------------------------------------------------------------------------
	void SRegionNetPacketProcesser::onRecvPlayerCharacterSetAliveFromFrontServer( I32 id , PT_REGION_F2M_PLAYER_CHARACTER_ALIVE_DATA* data)
	{
		//-------------------------------------------------------------------------
		SPlayerCharacter* playerCharacter = NULL;//SWorldManager::getInstance().getPlayerCharacterFromMemory(data->playerCharacterId);
		if (NULL == playerCharacter)
		{
			DYNAMIC_EEXCEPT_LOG("SRegionNetPacketProcesser::onRecvPlayerCharacterSetAliveFromFrontServer : not find playercharactor!");
			return;
		}

		//-------------------------------------------------------------------------
		if (playerCharacter->getHp() > 0)
		{
			return;
		}

		playerCharacter->setAlive((AliveType)data->aliveType);
	}

	//--------------------------------------------------------------------------
	void SRegionNetPacketProcesser::onRecvTestFromFrontServer( I32 id , PT_REGION_C2M_TEST_DATA* data)
	{
#if 0
		//-------------------------------------------------------------------------

		SPlayer* player = NULL;//SWorldManager::getInstance().getPlayerFromMemory(data->accountId);
		if (NULL == player)
		{
			DYNAMIC_EEXCEPT_LOG("SRegionNetPacketProcesser::onRecvTestFromFrontServer : not find player!");
			return;
		}

		//-------------------------------------------------------------------------

		SInstanceRegion* curRegion;// = player->getCurrentRealRegionObj();

		SRegionObjectBase* myRegionObj;// = curRegion->getNewRegionObject();

		std::map<CampIdType, SCamp*>* monsterList;// = myRegionObj->getCampList();

		SCamp* myCamp = monsterList->begin()->second;

		if (false == myCamp->isDead())
		{
			myCamp->killMySelfForTest();
		}
#endif
	}

	//--------------------------------------------------------------------------
	void SRegionNetPacketProcesser::onRecvTest1FromFrontServer( I32 id , PT_REGION_C2M_TEST_DATA* data)
	{
#if 0
		//-------------------------------------------------------------------------

		SPlayer* player = NULL;//SWorldManager::getInstance().getPlayerFromMemory(data->accountId);
		if (NULL == player)
		{
			DYNAMIC_EEXCEPT_LOG("SRegionNetPacketProcesser::onRecvTest1FromFrontServer : not find player!");
			return;
		}

		//-------------------------------------------------------------------------

		SInstanceRegion* curRegion;// = player->getCurrentRealRegionObj();
		SRegionObjectBase* myRegionObj;// = curRegion->getNewRegionObject();


		//-------------------------------------------------------------------------
		{
			std::map<CampIdType, SCamp*>* campList = myRegionObj->getCampList();

			SCamp* myCamp = campList->begin()->second;

			std::map<TroopGroupIdType, STroopGroup*>* troopGroupList = myCamp->getCurControlTroopGroupList();
			for (std::map<TroopGroupIdType, STroopGroup*>::iterator iterGroup = troopGroupList->begin(); iterGroup != troopGroupList->end(); ++iterGroup)
			{
				STroopGroup* troopGroup = iterGroup->second;
				if (false)
				{
					continue;
				}

				std::map<TroopIdType, STroop*>* troopList = troopGroup->getTroopList();
				for (std::map<TroopIdType, STroop*>::iterator iter = troopList->begin(); iter != troopList->end(); ++iter)
				{
					if (false == iter->second->isDead())
					{
						iter->second->killMySelfForTest();
						return;
					}
				}

			}

			return;
		}
		

		//-------------------------------------------------------------------------
		{
			SPlayerCharacterPtr myPlayerCharacter;

			if (false == player->getMainPlayerCharacter(myPlayerCharacter))
			{
				return;
			}
			myPlayerCharacter->killMySelfForTest();
			return;
		}

		//-------------------------------------------------------------------------
		{
			//怪物
			std::map<GameObjectIdType, SMonster*>* monsterList = myRegionObj->getMonsterList();

			SMonster* myMonster = monsterList->begin()->second;

			myMonster->killMySelfForTest();
			return;
		}
#endif
	}

	//--------------------------------------------------------------------------
	void SRegionNetPacketProcesser::sendMonsterAIControlToPlayerList(std::map<AccountIdType, Player*>* playerList)
	{
		//for (std::map<AccountIdType, Player*>::iterator iter = playerList->begin(); iter != playerList->end(); ++iter)
		//{
		//	SPlayer* tempPlayer = (SPlayer*)iter->second;

		//	sendMonsterAIControlToPlayer(tempPlayer);
		//}
	}

	//--------------------------------------------------------------------------
	void SRegionNetPacketProcesser::sendMonsterAIControlToPlayer(SPlayer* player)
	{
		//-------------------------------------------------------------------------

		NetTranspondSendDataBufferPtr dataPtr ;
		GameNetPacketData* packet       = NULL;
		PT_REGION_M2C_MONSTER_AI_CONTROL_DATA* sendData = NULL;

		// 当前发送数据头大小
		I32 sendDataHeadSize    = 0;
		// 当前发送数据大小
		I32 sendDataSize        = 0;
		// 准备发送数据大小
		I32 prepareSendDataSize = 0;

		// 遍历角色队列
		std::vector<GameObjectIdType>* monsterList = player->getControlAIMonsterIdList();
		std::vector<GameObjectIdType>::iterator iter = monsterList->begin();
		while( monsterList->end() != iter )
		{

			//-------------------------------------------------------------------------
			
			if ( dataPtr.mDataPtr.isNull() == false )
			{
				// 递增一个角色数据大小到发送数据缓存大小
				prepareSendDataSize = sendDataSize + PT_REGION_M2C_MONSTER_AI_CONTROL_INFO::netAddMonsterAIInfoSize;

				// 如果大于缓存最大大小则发送
				if ( prepareSendDataSize >= dataPtr.getTranspondDataMaxSize(100) )
				{
					NetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(
						dataPtr, 
						sendDataSize, 
						player->getFrontServerId(), 
						player->getClientNetIdInFrontServer(), 
						player->getAccountId());

					dataPtr.mDataPtr.setNull() ;
				}
			}

			//-------------------------------------------------------------------------

			if ( dataPtr.mDataPtr.isNull() )
			{
				NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );
				packet       = (GameNetPacketData*) dataPtr.getTranspondData();
				if ( !packet )
					return;

				packet->channel = GNPC_REGION;
				packet->type    = PT_REGION_M2C_MONSTER_AI_CONTROL;
				sendData = (PT_REGION_M2C_MONSTER_AI_CONTROL_DATA*)(packet->data);
				sendData->controlerAccountId = player->getAccountId();
				sendData->addMonsterAINum = 0;

				sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_REGION_M2C_MONSTER_AI_CONTROL_INFO::headSize;
				sendDataSize        = sendDataHeadSize;
				prepareSendDataSize = sendDataHeadSize;
			}

			//-------------------------------------------------------------------------

			NetMonsterIdInfo* tempSend 	= &(sendData->addMonsterAIInfo[sendData->addMonsterAINum]);
			tempSend->monsterId				= *iter;

			sendDataSize += PT_REGION_M2C_MONSTER_AI_CONTROL_INFO::netAddMonsterAIInfoSize;

			++sendData->addMonsterAINum;
			++iter;
		}

		//-------------------------------------------------------------------------

		if ( dataPtr.mDataPtr.isNull() == false )
		{
			NetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(
				dataPtr, 
				sendDataSize, 
				player->getFrontServerId(), 
				player->getClientNetIdInFrontServer(), 
				player->getAccountId());

			dataPtr.mDataPtr.setNull() ;
		}
		
	}

	//--------------------------------------------------------------------------

	void SRegionNetPacketProcesser::sendEndLoadScene(SPlayer* player)
	{
		//--------------------------------------------------------------------------

		NetTranspondSendDataBufferPtr dataPtr;
        NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );
		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if (NULL == packet)
		{
			return;
		}

		//--------------------------------------------------------------------------

		I32 sendDataSize = GameNetPacketData_INFO::headSize + PT_REGION_M2C_CREATE_TROOP_INFO::dataSize;
		
		packet->channel = GNPC_REGION;
		packet->type    = PT_REGION_M2C_END_LOAD_SCENE;
		PT_REGION_M2C_END_LOAD_SCENE_DATA* sendData = (PT_REGION_M2C_END_LOAD_SCENE_DATA*)(packet->data);
		if(sendData)
		{
			NetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(
				dataPtr, sendDataSize, 
				player->getFrontServerId(), 
				player->getClientNetIdInFrontServer(), 
				player->getAccountId());
		}
		
	}
	//--------------------------------------------------------------------------
	void SRegionNetPacketProcesser::broadcastBuffListToRegionToSelf( SPlayerCharacter* playerCharacter, SPlayer* myPlayer )
	{
		//--------------------------------------------------------------------------

		std::map<U32, BuffData> mapBuffData;
		playerCharacter->getSBuffManager()->getBuffData(mapBuffData);

		//--------------------------------------------------------------------------

		NetTranspondSendDataBufferPtr dataPtr ;
		GameNetPacketData* packet       = NULL;
		PT_BUFF_M2C_PLAYERCHARACTER_BUFFDATA_LIST_Data* sendData = NULL;
	
		//封包头的大小，CDNetData的大小
		UInt headSize = 0;
		UInt elemSize = 0;
		//封包大小
		UInt bagSize = 0;

		std::map<U32, BuffData>::iterator  front = mapBuffData.begin();
		std::map<U32, BuffData>::iterator  back = mapBuffData.end();
		for ( ;front != back ; front++ )
		{
			//--------------------------------------------------------------------------

			if ( front->second.mTimeUse == false )
			{
				continue;
			}

			//--------------------------------------------------------------------------
			
			if ( dataPtr.mDataPtr.isNull() == false )
			{
				//检查是否需要发送
				if ( (bagSize + elemSize) > dataPtr.getTranspondDataMaxSize(100) )
				{
					// 发送数据
					NetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(
						dataPtr, bagSize,
						myPlayer->getFrontServerId(), 
						myPlayer->getClientNetIdInFrontServer(),
						myPlayer->getAccountId());
					dataPtr.mDataPtr.setNull() ;
				}
			}

			//--------------------------------------------------------------------------

			if ( dataPtr.mDataPtr.isNull() )
			{
				NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );
				packet       = (GameNetPacketData*) dataPtr.getTranspondData();
				if ( !packet )
					return;

				packet->type = PT_BUFF_M2C_PLAYERCHARACTER_BUFFDATA_LIST;
				packet->channel = GNPC_BUFF;
				sendData = (PT_BUFF_M2C_PLAYERCHARACTER_BUFFDATA_LIST_Data*)packet->data;

				//封包头
				sendData->dbId = playerCharacter->getID();
				sendData->ncount = 0;

				headSize = GameNetPacketData_INFO::headSize + PT_BUFF_M2C_PLAYERCHARACTER_BUFFDATA_LIST_INFO_Data::dataSize - netBuffInfoData::dataSize;
				elemSize = netBuffInfoData::dataSize;
				bagSize = headSize;
			}

			//--------------------------------------------------------------------------

			//填充
			sendData->buffdatalist[sendData->ncount].buffId =  front->second.mBuffId;
			sendData->buffdatalist[sendData->ncount].timeUse =  front->second.mTimeUse;
			sendData->buffdatalist[sendData->ncount].curAddNum =  front->second.mCurAddNum;

			//更新记录数据
			bagSize += elemSize;
			++sendData->ncount;
		}

		//--------------------------------------------------------------------------

		if ( dataPtr.mDataPtr.isNull() == false )
		{
			// 发送数据
			NetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(
				dataPtr, bagSize,
				myPlayer->getFrontServerId(), 
				myPlayer->getClientNetIdInFrontServer(), 
				myPlayer->getAccountId());

			dataPtr.mDataPtr.setNull() ;
		}
	}

	//--------------------------------------------------------------------------
	void SRegionNetPacketProcesser::broadcastCreateAndAppearPlayerCharacterEquipListToRegionToSelf( SPlayerCharacter* playerCharacter, SPlayer* myPlayer )
	{
#if 0
		NetTranspondSendDataBufferPtr dataPtr ;
        NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );
		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if ( packet )
		{
			packet->channel = GNPC_ITEM;
			packet->type    = PT_ITEM_M2C_EQUIP_LIST;
			PT_ITEM_M2C_EQUIP_LIST_DATA* sendData = (PT_ITEM_M2C_EQUIP_LIST_DATA*)packet->data;
			if(sendData)
			{
				sendData->charid = playerCharacter->getID();
				playerCharacter->getEquipItem()->getEquipItemList(sendData->equipId);
				SRegionObjectBase* tempRegion = playerCharacter->getCurrentRegionObject();

				if ( tempRegion )
					NetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(
					dataPtr, 
					GameNetPacketData_INFO::headSize + PT_ITEM_M2C_EQUIP_LIST_DATA_INFO::dataSize, 
					myPlayer->getFrontServerId(), 
					myPlayer->getClientNetIdInFrontServer(), 
					myPlayer->getAccountId());
			}
	  }
#endif
	}

	//--------------------------------------------------------------------------

}