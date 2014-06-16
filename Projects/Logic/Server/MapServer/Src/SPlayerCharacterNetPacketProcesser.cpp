/******************************************************************************/

#include "stdafx.h"
#include "SPlayerCharacterNetPacketProcesser.h"
#include "NetTranspondPacketProcesser.h"
#include "MapServerMain.h"
#include "SWorldManager.h"
#include "MGameTimeSystem.h"
#include "SSkillOwnManager.h"
#include "ThreadTaskManager.h"
#include "SSceneGridManager.h"
#include "SSceneObject.h"
#include "SPlayerManager.h"
/******************************************************************************/

namespace MG
{
    //--------------------------------------------------------------------------
    SPlayerCharacterNetPacketProcesser::SPlayerCharacterNetPacketProcesser()
    {

    }

    //--------------------------------------------------------------------------
    SPlayerCharacterNetPacketProcesser::~SPlayerCharacterNetPacketProcesser()
    {
        
    }

    //--------------------------------------------------------------------------
    Bool SPlayerCharacterNetPacketProcesser::processFrontServerPacket(I32 id, NetEventRecv* packet)
    {
		if ( packet->getChannel() == GNPC_PLAYER_CHARACTER )
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			//case PT_PLAYERCHARACTER_C2S_MOVE_POS:
			//	onRecvPlayerCharacterMoveFromFrontServer( id, (PT_PLAYERCHARACTER_C2S_MOVE_POS_DATA*)data->data);
			//	break;
			/*case PT_PLAYERCHARACTER_F2M_ATTR:
				onRecvPlayerCharacterAttrFormFrontServer( id, (PT_PLAYERCHARACTER_F2M_ATTR_DATA*)data->data);
				break;*/
			case PT_PLAYERCHARACTER_F2M_JUMP_REGION:
				{
#ifdef MULTI_THREAD
					ThreadTaskManager::getInstance().addJumpRegionTask(packet, id);
#else
					onRecvPlayerCharacterJumpFromFrontServer( id, (PT_PLAYERCHARACTER_F2M_JUMP_REGION_DATA*)data->data);
#endif
				}
				break;
			case PT_PLAYERCHARACTER_F2M_JUMP_CAMPAIGN_REGION:
				{
#ifdef MULTI_THREAD
					ThreadTaskManager::getInstance().addJumpRegionTask(packet, id);
#else
					onRecvPlayerCharacterJumpCampaignRegionFormFrontServer( id, (PT_PLAYERCHARACTER_F2M_JUMP_CAMPAIGN_REGION_DATA*)data->data);
#endif
				}
				break;
			case PT_PLAYERCHARACTER_F2M_SKILL_INFO:
				{
#ifdef MULTI_THREAD
					ThreadTaskManager::getInstance().addJumpRegionTask(packet, id);
#else
					onRecvPlayerCharacterSkillList(id, (PT_PLAYERCHARACTER_F2M_SKILL_INFO_DATA*)data->data);
#endif
				}
				break;
			case PT_PLAYERCHARACTER_F2M_JUMP_EMPTY_REGION:
				{
#ifdef MULTI_THREAD
					ThreadTaskManager::getInstance().addJumpRegionTask(packet, id);
#else
					onRecvPlayerCharacterJumpEmptyRegionFromFrontServer( id, (PT_PLAYERCHARACTER_F2M_JUMP_EMPTY_REGION_DATA*)data->data);
#endif
				}
				break;
			default:
				{
					DYNAMIC_ASSERT(0);
				}
				break;
			}

			return true;
		}
        return false;
    }

	//--------------------------------------------------------------------------
	void SPlayerCharacterNetPacketProcesser::onRecvPlayerCharacterMoveFromFrontServer( I32 id, Byte	regionType, U64	regionId, I32 instanceId, PT_PLAYERCHARACTER_C2S_MOVE_POS_DATA* data )
	{
		SSceneObject* sceneObject = NULL; //SWorldManager::getInstance().getSceneObject((REGION_OBJ_TYPE)regionType, regionId, instanceId);
		if(!sceneObject)
		{
			return;
		}

		SPlayerCharacterPtr playerCharacter;
		//if(sceneObject->getPlayerCharacter(playerCharacter, data->playercharacterIndex) == false)
			return;

		if(playerCharacter->isDead())
			return;

		playerCharacter->moveToPos((NetVec2)data->startMovePos, (NetVec2)data->endMovePos, data->isBlockCheck);
	}

	//--------------------------------------------------------------------------
	void SPlayerCharacterNetPacketProcesser::onRecvPlayerCharacterStopMoveFromFrontServer( I32 id, Byte	regionType, U64	regionId, I32 instanceId, PT_PLAYERCHARACTER_C2S_STOP_MOVE_DATA* data )
	{
		SSceneObject* sceneObject = NULL; //SWorldManager::getInstance().getSceneObject((REGION_OBJ_TYPE)regionType, regionId, instanceId);
		if(!sceneObject)
		{
			return;
		}

		SPlayerCharacterPtr playerCharacter;
		//if(sceneObject->getPlayerCharacter(playerCharacter, data->playercharacterIndex) == false)
			return;

		if(playerCharacter->isDead())
			return;

		playerCharacter->stopMove();
	}

	//--------------------------------------------------------------------------
	void SPlayerCharacterNetPacketProcesser::onRecvPlayerCharacterJumpFromFrontServer(I32 id, PT_PLAYERCHARACTER_F2M_JUMP_REGION_DATA* data)
	{
		DYNAMIC_ASSERT(0);
		//SWorldManager::getInstance().playerCharacterJumpRegion(0 , data->playerCharacterId, (REGION_OBJ_TYPE)data->toRegionType, data->toRegionId, data->toInstanceId, JUMP_NORMAL, 0, data->pointId);

		MG_LOG(out_sys, "\n ====================角色跳转地图 Begin===================================================== \n ");
		SWorldManager::getInstance().printWorldObject();
		MG_LOG(out_sys, "\n ====================角色跳转地图 End===================================================== \n ");

	}

    //--------------------------------------------------------------------------
	void SPlayerCharacterNetPacketProcesser::onRecvPlayerCharacterJumpEmptyRegionFromFrontServer(I32 id, PT_PLAYERCHARACTER_F2M_JUMP_EMPTY_REGION_DATA* data)
	{
        SPlayerPtr player;
		if (false == SPlayerManager::getInstance().getPlayer(player, data->accountId))
		{
			return;
		}
		
		DYNAMIC_ASSERT(false == player.isNull());
		if ( player.isNull() )
			return;

		SPlayerCharacterPtr playerCharacter;
		if (false == player->retrievePlayerCharacter(playerCharacter, data->playerCharacterId))
		{
			return;
		}

		DYNAMIC_ASSERT(false == playerCharacter.isNull());
        if ( playerCharacter.isNull() )
            return;

        if(playerCharacter->isDead())
            return;

		//playerCharacter->jumpToRegion(NULL, NULL);
		//player->jumpToRegion(NULL);
	}

	//--------------------------------------------------------------------------
	void SPlayerCharacterNetPacketProcesser::onRecvPlayerCharacterJumpCampaignRegionFormFrontServer(I32 id, PT_PLAYERCHARACTER_F2M_JUMP_CAMPAIGN_REGION_DATA* data)
	{
		//SWorldManager::getInstance().playerCharacterJumpCampaignRegion(data->playerCharacterId, (REGION_OBJ_TYPE)data->toRegionType, data->toRegionId, data->toInstanceId, (JUMP_TYPE)data->jumpType, data->jumpIndex, data->isBattleLeader, data);
	}
	
	//--------------------------------------------------------------------------
	void SPlayerCharacterNetPacketProcesser::broadcastPlayerCharacterMove(SPlayerCharacter* playerCharacter, NetVec2 startMovePos, NetVec2 endMovePos, Bool isBlockCheck)
	{
#if 0
		if(playerCharacter && !playerCharacter->isDead())
		{
			NetTranspondSendDataBufferPtr dataPtr;
            NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

			GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
			if(packet)
			{
				packet->type = PT_PLAYERCHARACTER_S2C_MOVE_POS;
				packet->channel = GNPC_PLAYER_CHARACTER;

				PT_PLAYERCHARACTER_S2C_MOVE_POS_DATA* sendData = (PT_PLAYERCHARACTER_S2C_MOVE_POS_DATA*)packet->data;
				if(sendData)
				{
					sendData->playercharacterIndex = playerCharacter->getID();
					sendData->startMovePos  = startMovePos.getData();
					sendData->endMovePos  = endMovePos.getData();
					sendData->startMoveTime = MGameTimeSystem::getInstance().getCurrActualTime();
					sendData->isBlockCheck = isBlockCheck;

					SRegionObjectBase* regionObj = playerCharacter->getCurrentRegionObject();
					Int dataSize = GameNetPacketData_INFO::headSize + PT_PLAYERCHARACTER_S2C_MOVE_POS_DATA_INFO::dataSize;
					if (regionObj->getRegionType() == ROT_MAP_DISTRIBUTION)
					{
						//大地图 不广播移动
						SPlayerIdentifyInfoInPlayerCharacter* myPlayerInfo = playerCharacter->getPlayerIdentifyInfo();
						NetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(dataPtr, dataSize,
							myPlayerInfo->frontServerId, myPlayerInfo->clientNetIdInFrontServer, myPlayerInfo->accountId );
					}
					else if(regionObj->getRegionType() == ROT_PLACE 	|| 
							regionObj->getRegionType() == ROT_TIRO		||
							regionObj->getRegionType() == ROT_PVE		||
							regionObj->getRegionType() == ROT_HOME		||
							regionObj->getRegionType() == ROT_PVP		||
							regionObj->getRegionType() == ROT_GROWUP	||
							regionObj->getRegionType() == ROT_HISTORY	||
							regionObj->getRegionType() == ROT_SPORT		||
							regionObj->getRegionType() == ROT_FIGHT		||
							regionObj->getRegionType() == ROT_TRAIN)
					{
						//广播
						SRegionObjectBase* regionObjectBase = playerCharacter->getCurrentRegionObject();
						if(regionObjectBase)
						{
							NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(dataPtr, dataSize, playerCharacter->getSceneObjectInSceneGridsManager()->currSceneGrid, NULL, regionObj, 0);
						}
					}
					else
					{
						DYNAMIC_ASSERT(0);
					}
				}
			}
		}
#endif
	}

	//--------------------------------------------------------------------------
	void  SPlayerCharacterNetPacketProcesser::broadcastPlayerCharacterStopMove(SPlayerCharacter* playerCharacter)
	{
		if(playerCharacter)
		{
			NetTranspondSendDataBufferPtr dataPtr  ;
            NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

			GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
			if(packet)
			{
				packet->type = PT_PLAYERCHARACTER_S2C_STOP_MOVE;
				packet->channel = GNPC_PLAYER_CHARACTER;

				PT_PLAYERCHARACTER_S2C_STOP_MOVE_DATA* sendData = (PT_PLAYERCHARACTER_S2C_STOP_MOVE_DATA*)packet->data;
				if(sendData)
				{
					sendData->playercharacter_index = playerCharacter->getID();

					SRegionObjectBase* regionObjectBase;// = playerCharacter->getCurrentRegionObject();
					if(regionObjectBase)
					{
						//NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(dataPtr, GameNetPacketData_INFO::headSize + PT_PLAYERCHARACTER_S2C_STOP_MOVE_DATA_INFO::dataSize, playerCharacter->getSceneObjectInSceneGridsManager()->currSceneGrid, NULL, regionObjectBase, 0);
					}

				}
			}
		}
	}

	//--------------------------------------------------------------------------
	void  SPlayerCharacterNetPacketProcesser::broadcastPlayerCharacterEnterFight(SPlayerCharacter* playerCharacter)
	{
		if(playerCharacter)
		{
			NetTranspondSendDataBufferPtr dataPtr;
            NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

			GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
			if(packet)
			{
				packet->type = PT_PLAYERCHARACTER_S2C_ENTER_FIGHT;
				packet->channel = GNPC_PLAYER_CHARACTER;

				PT_PLAYERCHARACTER_S2C_ENTER_FIGHT_DATA* sendData = (PT_PLAYERCHARACTER_S2C_ENTER_FIGHT_DATA*)packet->data;
				if(sendData)
				{
					sendData->playercharacterIndex = playerCharacter->getID();

					SRegionObjectBase* regionObjectBase;// = playerCharacter->getCurrentRegionObject();
					if(regionObjectBase)
					{
						//NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(dataPtr, GameNetPacketData_INFO::headSize + PT_PLAYERCHARACTER_S2C_ENTER_FIGHT_DATA_INFO::dataSize, playerCharacter->getSceneObjectInSceneGridsManager()->currSceneGrid, NULL, regionObjectBase, 0);
					}
				}
			}
		}
	}

	//--------------------------------------------------------------------------
	void  SPlayerCharacterNetPacketProcesser::broadcastPlayerCharacterEndFight(SPlayerCharacter* playerCharacter)
	{
#if 0
		if(playerCharacter)
		{
			NetTranspondSendDataBufferPtr dataPtr ;
            NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

			GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
			if(packet)
			{
				packet->type = PT_PLAYERCHARACTER_S2C_END_FIGHT;
				packet->channel = GNPC_PLAYER_CHARACTER;

				PT_PLAYERCHARACTER_S2C_END_FIGHT_DATA* sendData = (PT_PLAYERCHARACTER_S2C_END_FIGHT_DATA*)packet->data;
				if(sendData)
				{
					sendData->playercharacterIndex = playerCharacter->getID();

					SRegionObjectBase* regionObjectBase = playerCharacter->getCurrentRegionObject();
					if(regionObjectBase)
					{
						NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(dataPtr, GameNetPacketData_INFO::headSize + PT_PLAYERCHARACTER_S2C_END_FIGHT_DATA_INFO::dataSize, playerCharacter->getSceneObjectInSceneGridsManager()->currSceneGrid, NULL, regionObjectBase, 0);
					}
				}
			}
		}
#endif
	}

	//--------------------------------------------------------------------------
	void SPlayerCharacterNetPacketProcesser::sendPlayerCharacterJumpregionResult(SPlayerCharacterPtr& playerCharacter, ChatarcterJumpRegionResult result)
	{
#if 0
		SPlayerIdentifyInfo* playerIdentify = playerCharacter->getPlayerIdentifyInfo();

		GameNetSendDataBufferPtr dataPtr ;
        MapServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		GameNetPacketData* packet			= (GameNetPacketData*) dataPtr->getLogicData();
		if(packet)
		{
			packet->channel = GNPC_PLAYER_CHARACTER;
			packet->type = PT_PLAYERCHARACTER_M2F_JUMP_REGION;

			PT_PLAYERCHARACTER_M2F_JUMP_REGION_DATA* sendData = (PT_PLAYERCHARACTER_M2F_JUMP_REGION_DATA*)packet->data;
			if(sendData)
			{
				sendData->clientNetIdInFront= playerIdentify->clientNetIdInFrontServer;
				sendData->jumpResult		= result;
				sendData->playerCharacterId = playerCharacter->getID();
				sendData->toRegionType		= playerCharacter->getRegionType();
				sendData->toRegionId		= playerCharacter->getRegionID();
				if (NULL != playerCharacter->getCurrentRealRegionObject())
				{
					sendData->toInstanceId	= playerCharacter->getCurrentRealRegionObject()->getInstanceUId();
				}
				else
				{
					sendData->toInstanceId = 0;
				}

				const Int dataSize = GameNetPacketData_INFO::headSize + PT_PLAYERCHARACTER_M2F_JUMP_REGION_INFO::dataSize;

				MapServerMain::getInstance().getServerLauncher()->sendServer(dataPtr, dataSize, playerIdentify->frontServerId);
			}
		}
#endif
	}

	//--------------------------------------------------------------------------
	void SPlayerCharacterNetPacketProcesser::onRecvPlayerCharacterSkillList( I32 id, PT_PLAYERCHARACTER_F2M_SKILL_INFO_DATA* data )
	{
		SPlayerCharacter* playerCharacter = NULL; //SWorldManager::getInstance().getPlayerCharacterFromMemory(data->playercharacterId);
		if (NULL != playerCharacter)
		{
			for(UInt i = 0; i < data->skillNum; ++i)
			{
				( (SkillOwnManager*)playerCharacter->getSkillOwnManager() )->addOwnerSkill(data->skillList[i].skillId);
			}
		}
	}

	//--------------------------------------------------------------------------
}	//namespace MG