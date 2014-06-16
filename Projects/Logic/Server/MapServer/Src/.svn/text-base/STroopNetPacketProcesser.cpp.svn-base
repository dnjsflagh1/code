/******************************************************************************/

#include "stdafx.h"
#include "STroopNetPacketProcesser.h"
//#include "SWorldManager.h"
//#include "SPlayer.h"

#include "NetTranspondPacketProcesser.h"
#include "MapServerMain.h"
#include "NetTranspondPacketProcesser.h"
#include "TroopNetPacket.h"
#include "SWorldManager.h"
#include "MGameTimeSystem.h"
#include "STroop.h"
#include "SPlayerManager.h"
#include "SSceneObject.h"
/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	STroopNetPacketProcesser::STroopNetPacketProcesser()
	{

	}

	//--------------------------------------------------------------------------
	STroopNetPacketProcesser::~STroopNetPacketProcesser()
	{

	}

	//--------------------------------------------------------------------------
	Bool STroopNetPacketProcesser::processFrontServerPacket(I32 id, NetEventRecv* packet)
	{
		if ( packet->getChannel() == GNPC_TROOP )
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_TROOP_GROUP_F2M_JUMP_REGION:
				onRecvTroopJumpRegion( id, (PT_TROOP_GROUP_F2M_JUMP_REGION_DATA*)data->data);
				break;
            /*case PT_TROOP_F2M_ATTR:
                onRecvTroopAttrFormFrontServer( id, (PT_TROOP_F2M_ATTR_DATA*)data->data);
                break;*/
			//case PT_TROOP_C2S_MOVE_POS:
			//	onRecvTroopMove( id, (PT_TROOP_C2S_MOVE_POS_DATA*)data->data);
			//	break;
			//case PT_TROOP_SOLDIER_C2S_MOVE_POS:
			//	onRecvTroopSoldierMove( id, (PT_TROOP_SOLDIER_C2S_MOVE_POS_DATA*)data->data);
			//	break;

			}

			return true;
		}
		return false;
	}

	//--------------------------------------------------------------------------
	void STroopNetPacketProcesser::onRecvTroopJumpRegion(I32 id, PT_TROOP_GROUP_F2M_JUMP_REGION_DATA* data)
	{
	}

    //--------------------------------------------------------------------------

	void STroopNetPacketProcesser::onRecvTroopMove(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_TROOP_C2S_MOVE_POS_DATA* data)
	{
#if 0
		SPlayerPtr player;
		if (false == SPlayerManager::getInstance().getPlayer(player, 0))
		{
			return;
		}

		DYNAMIC_ASSERT(false == player.isNull());
		if ( player.isNull() )
		{
			return;
		}

		//SSceneObject* sceneObject = SWorldManager::getInstance().getSceneObject((REGION_OBJ_TYPE)regionType, regionId, instanceId);
		//if(!sceneObject)
		//{
		//	return;
		//}

		//STroopPtr troop;
		//if(sceneObject->getTroop(troop, data->troopIndex) == false)
		//	return;

		//if(troop.isNull() || troop->isDead())
		//	return;

		DYNAMIC_ASSERT(0);
		//SPlayerPtr ownerPlayer;
		//troop->getPlayer(ownerPlayer);
		//if(ownerPlayer.isNull())
		//{
		//	return;
		//}

		//if(player->getAccountID() != ownerPlayer->getAccountID())
		//{
		//	return;
		//}

		//SRegionObjectBase* region = troop->getCurrentRegionObject();
		//if (NULL == region/* || false == region->checkPos(data->x, data->z)*/)
		//{
		//	//send error msg
		//	return;
		//}

		//NetVec2 netVec2EndMovePos = data->endMovePos;
		//NetVec2 netVec2StartMovePos = data->startMovePos;
		//Vec3	vec3EndPos = netVec2EndMovePos;

		//troop->moveToPos((NetVec2)data->startMovePos, (NetVec2)data->endMovePos);
		/*troop->setPos(vec3EndPos);*/
		broadcastTroopMove(region, data->troopIndex, netVec2StartMovePos, netVec2EndMovePos, data->isBlockCheck);
#endif
	}

	//--------------------------------------------------------------------------
	void STroopNetPacketProcesser::onRecvTroopStopMove(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_TROOP_C2S_STOP_MOVE_DATA* data)
	{
		SPlayerPtr player;
		DYNAMIC_ASSERT(0);
		if (false == SPlayerManager::getInstance().getPlayer(player, 0))
		{
			return;
		}

		DYNAMIC_ASSERT(false == player.isNull());
		if ( player.isNull() )
		{
			return;
		}

		//SSceneObject* sceneObject = SWorldManager::getInstance().getSceneObject((REGION_OBJ_TYPE)regionType, regionId, instanceId);
		//if(!sceneObject)
		//{
		//	return;
		//}

		//STroopPtr troop;
		//if(sceneObject->getTroop(sceneObject, data->troopIndex) == false)
		//	return;

		//if(troop.isNull() || troop->isDead())
		//	return;

		DYNAMIC_ASSERT(0);
		//SPlayerPtr ownerPlayer;
		//troop->getPlayer(ownerPlayer);
		//if(ownerPlayer.isNull())
		//{
		//	return;
		//}

		//if(player->getAccountID() != ownerPlayer->getAccountID())
		//{
		//	return;
		//}

		//SRegionObjectBase* region = troop->getCurrentRegionObject();
		//if (NULL == region/* || false == region->checkPos(data->x, data->z)*/)
		//{
		//	//send error msg
		//	return;
		//}

		//troop->stopMove();

		//broadcastTroopStopMove(region, data->troopIndex);
	}

	//--------------------------------------------------------------------------
	void STroopNetPacketProcesser::broadcastTroopEnterFight(STroop* troop)
	{
#if 0
		if(troop)
		{
			NetTranspondSendDataBufferPtr dataPtr  ;
            NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

			GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
			if(packet)
			{
				packet->type = PT_TROOP_S2C_ENTER_FIGHT;
				packet->channel = GNPC_TROOP;

				PT_TROOP_S2C_ENTER_FIGHT_DATA* sendData = (PT_TROOP_S2C_ENTER_FIGHT_DATA*)packet->data;
				if(sendData)
				{
					sendData->troopIndex = troop->getID();

					SRegionObjectBase* regionObjectBase = troop->getCurrentRegionObject();
					if(regionObjectBase)
					{
						//if(regionObjectBase->getGameType() == GameType_Rpg)
						//{
						//	NetTranspondPacketProcesser::getInstance().gridsBroadcastClientTranspondPackToFrontServer(troop->getSceneObjectInSceneGridsManager()->currSceneGrid, NULL, dataPtr,
						//		GameNetPacketData_INFO::headSize + PT_PLAYERCHARACTER_S2C_ENTER_FIGHT_DATA_INFO::dataSize, 0);
						//}
						//else
						//{
							NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(dataPtr, 
								GameNetPacketData_INFO::headSize + PT_TROOP_S2C_ENTER_FIGHT_DATA_INFO::dataSize, 
								troop->getCurrentRegionObject());
						//}
					}
				}
			}
		}
#endif
	}

	//--------------------------------------------------------------------------
	void STroopNetPacketProcesser::broadcastTroopEndFight(STroop* troop)
	{
		if(troop)
		{
			NetTranspondSendDataBufferPtr dataPtr ;
            NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

			GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
			if(packet)
			{
				packet->type = PT_TROOP_S2C_END_FIGHT;
				packet->channel = GNPC_TROOP;

				PT_TROOP_S2C_END_FIGHT_DATA* sendData = (PT_TROOP_S2C_END_FIGHT_DATA*)packet->data;
				if(sendData)
				{
					sendData->troopIndex = troop->getID();
#if 0
					SRegionObjectBase* regionObjectBase = troop->getCurrentRegionObject();
					if(regionObjectBase)
					{
						//if(regionObjectBase->getGameType() == GameType_Rpg)
						//{
						//	NetTranspondPacketProcesser::getInstance().gridsBroadcastClientTranspondPackToFrontServer(playerCharacter->getSceneObjectInSceneGridsManager()->currSceneGrid, NULL, dataPtr,
						//		GameNetPacketData_INFO::headSize + PT_PLAYERCHARACTER_S2C_END_FIGHT_DATA_INFO::dataSize, 0);
						//}
						//else
						//{
							NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(dataPtr, 
								GameNetPacketData_INFO::headSize + PT_TROOP_S2C_END_FIGHT_DATA_INFO::dataSize, 
								troop->getCurrentRegionObject());
						//}
					}
#endif
				}
			}
		}
	}



	//-------------------------------------------------------------------------
	void STroopNetPacketProcesser::onRecvTroopSoldierMove(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_TROOP_SOLDIER_C2S_MOVE_POS_DATA* data)
	{
#if 0
		DYNAMIC_ASSERT(0);
		SPlayerPtr player;
		if (false == SPlayerManager::getInstance().getPlayer(player, 0/*data->accountId*/))
		{
			return;
		}

		DYNAMIC_ASSERT(false == player.isNull());
		if ( player.isNull() )
		{
			return;
		}

		SSceneObject* sceneObject = SWorldManager::getInstance().getSceneObject((REGION_OBJ_TYPE)regionType, regionId, instanceId);
		if(!sceneObject)
		{
			return;
		}

		STroopPtr troop;
		if(sceneObject->getTroop(sceneObject, data->troopIndex) == false)
			return;

		if(troop.isNull() || troop->isDead())
			return;

		DYNAMIC_ASSERT(0);
		SPlayerPtr ownerPlayer;
		//troop->getPlayer(ownerPlayer);
		//if(ownerPlayer.isNull())
		//{
		//	return;
		//}

		//if(player->getAccountID() != ownerPlayer->getAccountID())
		//{
		//	return;
		//}

		SRegionObjectBase* region = troop->getCurrentRegionObject();
		if (NULL == region/* || false == region->checkPos(data->x, data->z)*/)
		{
			//send error msg
			return;
		}

		STroopSoldier* troopSoldier = troop->getTroopSoldier(data->troopIndex);
		if (NULL == troopSoldier)
		{
			return;
		}
		NetVec2 netVec2EndMovePos = data->endMovePos;
		NetVec2 netVec2StartMovePos = data->startMovePos;
		Vec3	vec3EndPos = netVec2EndMovePos;
		troopSoldier->setPos(vec3EndPos);
		broadcastTroopSoldierMove(region, data->troopId, data->troopIndex, netVec2StartMovePos, netVec2EndMovePos/*, troopGroup->getOwnerPlayer()*/);
#endif
	}

	//--------------------------------------------------------------------------
	void STroopNetPacketProcesser::onRecvTroopSoldierStopMove(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_TROOP_SOLDIER_C2S_STOP_MOVE_DATA* data)
	{
#if 0
		DYNAMIC_ASSERT(0);
		SPlayerPtr player;
		if (false == SPlayerManager::getInstance().getPlayer(player, 0))
		{
			return;
		}

		DYNAMIC_ASSERT(false == player.isNull());
		if ( player.isNull() )
		{
			return;
		}

		SSceneObject* sceneObject = SWorldManager::getInstance().getSceneObject((REGION_OBJ_TYPE)regionType, regionId, instanceId);
		if(!sceneObject)
		{
			return;
		}

		STroopPtr troop;
		if(sceneObject->getTroop(troop, data->troopIndex) == false)
			return;

		if(troop.isNull() || troop->isDead())
			return;

		//SPlayerPtr ownerPlayer;
		//troop->getPlayer(ownerPlayer);
		//if(ownerPlayer.isNull())
		//{
		//	return;
		//}

		if(player->getAccountId() != troop->getAccountId())
		{
			return;
		}

		SRegionObjectBase* region = troop->getCurrentRegionObject();
		if (NULL == region/* || false == region->checkPos(data->x, data->z)*/)
		{
			//send error msg
			return;
		}

		STroopSoldier* troopSoldier = troop->getTroopSoldier(data->soldierIndex);
		if (NULL == troopSoldier)
		{
			return;
		}

		broadcastTroopSoldierStopMove(region, data->troopIndex, data->soldierIndex);
#endif
	}

	//--------------------------------------------------------------------------
	void STroopNetPacketProcesser::broadcastTroopMove(SRegionObjectBase* region, GameObjectIndexIdInSceneType troopIndex, NetVec2 startMovePos, NetVec2 endMovePos, Bool isBlockCheck, SPlayer* owner)
	{
		NetTranspondSendDataBufferPtr dataPtr ;
        NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if ( packet )
		{
			packet->channel = GNPC_TROOP;
			packet->type    = PT_TROOP_S2C_MOVE_POS;
			PT_TROOP_S2C_MOVE_POS_DATA* sendData = (PT_TROOP_S2C_MOVE_POS_DATA*)(packet->data);
			if(sendData)
			{
				sendData->troopIndex = troopIndex;
				/*sendData->pos.x  = pos.x;
				sendData->pos.z  = pos.z;*/
				sendData->startMovePos  = startMovePos.getData();
				sendData->endMovePos  = endMovePos.getData();
				sendData->startMoveTime = MGameTimeSystem::getInstance().getCurrActualTime();
				sendData->isBlockCheck = isBlockCheck;

				NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(dataPtr, GameNetPacketData_INFO::headSize+PT_TROOP_S2C_MOVE_POS_DATA_INFO::dataSize,region);
			}
		}
	}


	//--------------------------------------------------------------------------
	void STroopNetPacketProcesser::broadcastTroopStopMove(SRegionObjectBase* region, GameObjectIndexIdInSceneType troopIndex, SPlayer* owner)
	{
		NetTranspondSendDataBufferPtr dataPtr ;
        NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if ( packet )
		{
			packet->channel = GNPC_TROOP;
			packet->type    = PT_TROOP_S2C_STOP_MOVE;
			PT_TROOP_S2C_STOP_MOVE_DATA* sendData = (PT_TROOP_S2C_STOP_MOVE_DATA*)(packet->data);
			if(sendData)
			{
				sendData->troopIndex = troopIndex;

				NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(dataPtr, GameNetPacketData_INFO::headSize+PT_TROOP_S2C_STOP_MOVE_DATA_INFO::dataSize,region);
			}
		}
	}


	//--------------------------------------------------------------------------
	void STroopNetPacketProcesser::broadcastTroopSoldierMove(SRegionObjectBase* region, GameObjectIndexIdInSceneType troopIndex, Byte troopSoldierIndex, NetVec2 startMovePos, NetVec2 endMovePos, SPlayer* owner)
	{
		NetTranspondSendDataBufferPtr dataPtr ;
        NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if ( packet )
		{
			packet->channel = GNPC_TROOP;
			packet->type    = PT_TROOP_SOLDIER_S2C_MOVE_POS;
			PT_TROOP_SOLDIER_S2C_MOVE_POS_DATA* sendData = (PT_TROOP_SOLDIER_S2C_MOVE_POS_DATA*)(packet->data);
			if(sendData)
			{
				sendData->troopIndex = troopIndex;
				sendData->soldierIndex = troopSoldierIndex;
				/*sendData->startMovePos.x  = startMovePos.x;
				sendData->startMovePos.z  = startMovePos.z;
				sendData->endMovePos.x  = endMovePos.x;
				sendData->endMovePos.z  = endMovePos.z;*/
				sendData->startMovePos  = startMovePos.getData();
				sendData->endMovePos  = endMovePos.getData();
				sendData->startMoveTime = MGameTimeSystem::getInstance().getCurrActualTime();

				NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(dataPtr, GameNetPacketData_INFO::headSize + PT_TROOP_SOLDIER_S2C_MOVE_POS_DATA_INFO::dataSize, region);
			}
		}
	}

	//--------------------------------------------------------------------------
	void STroopNetPacketProcesser::broadcastTroopSoldierStopMove(SRegionObjectBase* region, GameObjectIndexIdInSceneType troopIndex, Byte troopSoldierIndex, SPlayer* owner)
	{
		NetTranspondSendDataBufferPtr dataPtr ;
        NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if ( packet )
		{
			packet->channel = GNPC_TROOP;
			packet->type    = PT_TROOP_SOLDIER_S2C_STOP_MOVE;
			PT_TROOP_SOLDIER_S2C_STOP_MOVE_DATA* sendData = (PT_TROOP_SOLDIER_S2C_STOP_MOVE_DATA*)(packet->data);
			if(sendData)
			{
				sendData->troopIndex = troopIndex;
				sendData->soldierIndex = troopSoldierIndex;

				NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(dataPtr, GameNetPacketData_INFO::headSize + PT_TROOP_SOLDIER_S2C_STOP_MOVE_DATA_INFO::dataSize, region);
			}
		}
	}

    //--------------------------------------------------------------------------

}	//namespace MG