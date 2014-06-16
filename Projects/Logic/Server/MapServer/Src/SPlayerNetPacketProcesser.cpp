/******************************************************************************/

#include "stdafx.h"
#include "SPlayerNetPacketProcesser.h"
#include "NetTranspondPacketProcesser.h"
#include "MapServerMain.h"
#include "STiroInstance.h"
#include "SWorldManager.h"
#include "ThreadTaskManager.h"
#include "SPlayerNetPacketProcesser.h"
#include "STiroInstance.h"
#include "SPlayerManager.h"

/******************************************************************************/

/******************************************************************************/


namespace MG
{
    //--------------------------------------------------------------------------
    SPlayerNetPacketProcesser::SPlayerNetPacketProcesser()
    {

    }

    //--------------------------------------------------------------------------
    SPlayerNetPacketProcesser::~SPlayerNetPacketProcesser()
    {

    }

    //--------------------------------------------------------------------------
    Bool SPlayerNetPacketProcesser::processFrontServerPacket(I32 id, NetEventRecv* packet)
    {
		if ( packet->getChannel() == GNPC_PLAYER )
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_PLAYER_F2M_PRINT_TEST:
				//SWorldManager::getInstance().printWorldObject();
				break;
			case PT_PLAYER_F2M_LOGIN:
				{
#ifdef MULTI_THREAD
					ThreadTaskManager::getInstance().addJumpRegionTask(packet, id);
#else
					onRecvPlayerLogin( id , (PT_PLAYER_F2M_LOGIN_DATA*)data->data);
#endif
				}
				break;
			case PT_PLAYER_F2M_LOGOUT:
				{
#ifdef MULTI_THREAD
					ThreadTaskManager::getInstance().addJumpRegionTask(packet, id);
#else
					onRecvPlayerLogout( id , (PT_PLAYER_F2M_LOGOUT_DATA*)data->data);
#endif
				}
				break;
			case PT_PLAYER_F2M_PLAYERCHARACTER_INFO_LIST:
				{
#ifdef MULTI_THREAD
					ThreadTaskManager::getInstance().addJumpRegionTask(packet, id);
#else
					onRecvPlayerCharacterList(id, (PT_PLAYER_F2M_PLAYERCHARACTER_INFO_LIST_DATA*)data->data);
#endif
				}
				break;
			case PT_PLAYER_F2M_TROOP_INFO_LIST:
				onRecvTroopList(id, (PT_PLAYER_F2M_TROOP_INFO_LIST_DATA*)data->data);
				break;
			case PT_PLAYER_S2S_SYNC_ALL_LIST_END:
				onRecvSyncAllListEnd(id, (PT_PLAYER_S2S_SYNC_ALL_LIST_END_DATA*)data->data);
				break;
			case PT_PLAYER_F2M_BATTLE_INFO_LIST:
				break;
			case PT_PLAYER_F2M_JUMP_REGION:
				{
#ifdef MULTI_THREAD
					ThreadTaskManager::getInstance().addJumpRegionTask(packet, id);
#else
					onRecvPlayerJumpToRegion(id, (PT_PLAYER_F2M_JUMP_REGION_DATA*)data->data);
#endif
				}
				break;
			case PT_PLAYER_F2M_JUMP_REGION_BY_CHAR_ID:
				{
					onRecvPlayerJumpToRegionByCharId(id, (PT_PLAYER_F2M_JUMP_REGION_BY_CHAR_ID_DATA*)data->data);
				}
				break;
			case PT_PLAYER_F2M_TIRO_LIST:
				onRecvTiroList(id, (PT_PLAYER_F2M_TIRO_LIST_DATA*)data->data);
				break;
			case PT_PLAYER_F2M_PLAYERCHARACTER_EQUIP_INFO_LIST:
				onRecvPlayerCharacterEquipList(id, (PT_PLAYER_F2M_PLAYERCHARACTER_EQUIP_INFO_LIST_DATA*)data->data);
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
	void SPlayerNetPacketProcesser::sendRemainedPlayerCharacterListToClient_New(SPlayer* player)
	{
		return;	//暂时不发
	}

	//--------------------------------------------------------------------------
	void SPlayerNetPacketProcesser::sendPlayerJumpRegionToFrontServer(AccountIdType accountId, REGION_OBJ_TYPE regionType, RegionIdType regionId, InstanceUIdType instanceUid, PlayerJumpResult jumpResult)
	{
		DYNAMIC_ASSERT(instanceUid >= 0);

		SPlayerPtr player;
		if (false == SPlayerManager::getInstance().getPlayer(player, accountId))
		{
			return;
		}

		DYNAMIC_ASSERT(false == player.isNull());
		if ( player.isNull() )
			return;

		SPlayerCharacterPtr myPlayerCharacter;
		
		if (false == player->getMainPlayerCharacter(myPlayerCharacter))
		{
			return;
		}

		GameNetSendDataBufferPtr dataPtr ;
        MapServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer(dataPtr,MG_GAME_NET_PACKET_BIG_MAX_SIZE);

		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			packet->channel = GNPC_PLAYER;
			packet->type    = PT_PLAYER_M2F_JUMP_REGION;

			PT_PLAYER_M2F_JUMP_REGION_DATA* sendData = (PT_PLAYER_M2F_JUMP_REGION_DATA*)(packet->data);
			if(sendData)
			{

				sendData->client_net_id = player->getClientNetIdInFrontServer();
				sendData->force			= (Byte)myPlayerCharacter->getForce();
				sendData->regionId		= regionId;
				sendData->regionType	= regionType;
				sendData->instanceUid	= instanceUid;
				sendData->jumpResult	= jumpResult;
				sendData->pos			= ((NetVec2)myPlayerCharacter->getPos()).getData();
				sendData->dir			= ((NetVec2)myPlayerCharacter->getDir()).getData();


				const Int dataSize = GameNetPacketData_INFO::headSize+PT_PLAYER_M2F_JUMP_REGION_INFO::dataSize;
				MapServerMain::getInstance().getServerLauncher()->sendServer(dataPtr, dataSize, player->getFrontServerId());
			}
		}
	}

	//--------------------------------------------------------------------------
	void SPlayerNetPacketProcesser::sendPlayerJumpRegionToFrontServer(U64 account_id, SRegionObjectBase* region,PlayerJumpResult jumpResult)
	{
#if 0
		if (NULL == region)
		{
			return;
		}

		SInstanceRegion* parentRealRegionObj = region->getParentRegionInstance();
		DYNAMIC_ASSERT(NULL != parentRealRegionObj);
		sendPlayerJumpRegionToFrontServer(account_id, region->getRegionType(), region->getRegionId(), parentRealRegionObj->getInstanceUId(), jumpResult);
		return;
#endif
	}

	//--------------------------------------------------------------------------
	void SPlayerNetPacketProcesser::sendTiroListToClientBegin(SPlayerPtr& player, NetIdType mapServerNetId)
	{
		NetTranspondSendDataBufferPtr dataPtr;
        NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if (NULL == packet)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		I32 sendDataSize = GameNetPacketData_INFO::headSize + PT_PLAYER_M2C_TIRO_LIST_BEGIN_INFO::dataSize;

		packet->channel = GNPC_PLAYER;
		packet->type    = PT_PLAYER_M2C_TIRO_LIST_BEGIN;
		PT_PLAYER_M2C_TIRO_LIST_BEGIN_DATA* sendData = (PT_PLAYER_M2C_TIRO_LIST_BEGIN_DATA*)(packet->data);
		if(sendData)
		{
			sendData->mapServerNetId = mapServerNetId;

			NetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(dataPtr, 
				sendDataSize, 
				player->getFrontServerId(), 
				player->getClientNetIdInFrontServer(), player->getAccountId());
		}
	}

	//--------------------------------------------------------------------------
	void SPlayerNetPacketProcesser::sendTiroListToClientEnd(SPlayerPtr& player, NetIdType mapServerNetId)
	{
		NetTranspondSendDataBufferPtr dataPtr ;
        NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if (NULL == packet)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		I32 sendDataSize = GameNetPacketData_INFO::headSize + PT_PLAYER_M2C_TIRO_LIST_END_INFO::dataSize;

		packet->channel = GNPC_PLAYER;
		packet->type    = PT_PLAYER_M2C_TIRO_LIST_END;
		PT_PLAYER_M2C_TIRO_LIST_END_DATA* sendData = (PT_PLAYER_M2C_TIRO_LIST_END_DATA*)(packet->data);
		if(sendData)
		{
			sendData->mapServerNetId = mapServerNetId;

			NetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(dataPtr, sendDataSize, 
				player->getFrontServerId(), player->getClientNetIdInFrontServer(), player->getAccountId());
		}
	}

	//--------------------------------------------------------------------------
	void SPlayerNetPacketProcesser::sendTiroListToClient(SPlayerPtr& player, std::map<RegionIdType, SBigRegionObject*>* tiroList, NetIdType mapServerNetId)
	{
#if 0
		//--------------------------------------------------------------------------

		sendTiroListToClientBegin(player, mapServerNetId);

		//--------------------------------------------------------------------------

		NetTranspondSendDataBufferPtr dataPtr ;
		GameNetPacketData* packet       = NULL;
		PT_PLAYER_M2C_TIRO_LIST_DATA* sendData = NULL;
		
		// 当前发送数据头大小
		I32 sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_PLAYER_M2C_TIRO_LIST_INFO::headSize;
		// 当前发送数据大小
		I32 sendDataSize        = sendDataHeadSize;
		// 准备发送数据大小
		I32 prepareSendDataSize = 0;

		// 遍历角色队列
		std::map<RegionIdType, SBigRegionObject*>::iterator iterBig = tiroList->begin();
		for(; iterBig != tiroList->end(); ++iterBig)
		{
			//所有的副本列表
			SBigRegionObject* bigRegonObj = iterBig->second;
			std::map<InstanceIdType, SInstanceRegion*>* instanceRegionList = bigRegonObj->getInstanceRegionList();
			std::map<InstanceIdType, SInstanceRegion*>::iterator iter = instanceRegionList->begin();
			for (; iter != instanceRegionList->end(); ++iter)
			{
				//--------------------------------------------------------------------------

				if ( dataPtr.mDataPtr.isNull() == false )
				{
					// 递增一个角色数据大小到发送数据缓存大小
					prepareSendDataSize = sendDataSize + PT_PLAYER_M2C_TIRO_LIST_INFO::netAddTiroInfoSize;

					// 如果大于缓存最大大小则发送
					if ( prepareSendDataSize >= dataPtr.getTranspondDataMaxSize(100) )
					{
						SPlayerIdentifyInfo* playerIdendifyInfo = player->getIdentifyInfo();

						NetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(dataPtr, sendDataSize, 
							player->getFrontServerId(), player->getClientNetIdInFrontServer(), player->getAccountId());
						dataPtr.mDataPtr.setNull();
					}
				}

				//--------------------------------------------------------------------------

				if ( dataPtr.mDataPtr.isNull() )
				{
					NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );
					packet       = (GameNetPacketData*) dataPtr.getTranspondData();
					if ( !packet )
						return;

					packet->channel = GNPC_PLAYER;
					packet->type    = PT_PLAYER_M2C_TIRO_LIST;
					sendData = (PT_PLAYER_M2C_TIRO_LIST_DATA*)(packet->data);

					sendData->mapServerNetId = mapServerNetId;
					sendData->addTiroNum = 0;

					// 当前发送数据头大小
					sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_PLAYER_M2C_TIRO_LIST_INFO::headSize;
					// 当前发送数据大小
					sendDataSize        = sendDataHeadSize;
					// 准备发送数据大小
					prepareSendDataSize = sendDataHeadSize;
				}

				//--------------------------------------------------------------------------

				SInstanceRegion* instanceRegion = iter->second;
				NetAddTiroInfo* tempSend = &(sendData->addTiroInfo[sendData->addTiroNum]);
				sendData->regionId		= instanceRegion->getNewRegionObject()->getRegionId();
				sendData->regionType	= instanceRegion->getNewRegionObject()->getRegionType();
				tempSend->instanceUId	= instanceRegion->getInstanceUId();
				tempSend->curPlayerNum	= instanceRegion->getNewRegionObject()->getPlayerCharacterList()->size();
				tempSend->maxPlayerNum	= ((STiroInstance*)(bigRegonObj->getNewInstanceBase()))->getTiroCsv()->characterMaxNum;

				sendDataSize += PT_PLAYER_M2C_TIRO_LIST_INFO::netAddTiroInfoSize;

				++sendData->addTiroNum;
			}
		}

		if ( dataPtr.mDataPtr.isNull() == false )
		{
			SPlayerIdentifyInfo* playerIdendifyInfo = player->getIdentifyInfo();

			NetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(dataPtr, 
				sendDataSize, player->getFrontServerId(), player->getClientNetIdInFrontServer(), player->getAccountId());
			dataPtr.mDataPtr.setNull();
		}

		//--------------------------------------------------------------------------

		sendTiroListToClientEnd(player, mapServerNetId);
#endif
	}

	//--------------------------------------------------------------------------
	void SPlayerNetPacketProcesser::onRecvPlayerLogin( I32 frontId , PT_PLAYER_F2M_LOGIN_DATA* data)
	{
		DYNAMIC_ASSERT(0);
		SPlayerManager::getInstance().addPlayer(data->accountId, frontId, data->clientId, data->clanId);
	}

	//--------------------------------------------------------------------------
	void SPlayerNetPacketProcesser::onRecvPlayerLogout( I32 frontId , PT_PLAYER_F2M_LOGOUT_DATA* data)
	{
		SPlayerManager::getInstance().removePlayer(data->accountId);

		MG_LOG(out_sys, "\n ====================玩家退出游戏 Begin===================================================== \n ");
		SWorldManager::getInstance().printWorldObject();
		MG_LOG(out_sys, "\n ====================玩家退出游戏 End===================================================== \n ");
	}

	//--------------------------------------------------------------------------
	void SPlayerNetPacketProcesser::onRecvPlayerCharacterList( I32 frontId , PT_PLAYER_F2M_PLAYERCHARACTER_INFO_LIST_DATA* data)
	{
		DYNAMIC_ASSERT(data->playerCharacterNum < 100);
        
        // quit
        if ( data->playerCharacterNum == 0 )
            return;
        
        // get player
        AccountIdType accountId = data->playerCharacter[0].accountId;

        SPlayerPtr playerPtr;

        if ( SPlayerManager::getInstance().getPlayer( playerPtr, accountId ) == false )
        {
            DYNAMIC_EEXCEPT_LOG("not find player");
            return;
        }
        
        // loop
        for ( int i=0; i < data->playerCharacterNum; ++i )
        {
            NetPlayerCharacterInfo* curPlayerChar = &(data->playerCharacter[i]);
            PlayerCharacterData playerCharacterData;

            //初始化角色的相关属性
            playerCharacterData.mId                            = curPlayerChar->Id								;
            playerCharacterData.charClanId                     = curPlayerChar->charClanId						;
            playerCharacterData.mPos                           = (NetVec2)curPlayerChar->genrealPos				;
            playerCharacterData.mName                          = curPlayerChar->name							;			    ;
            playerCharacterData.charSurName                    = curPlayerChar->surName                         ;
            playerCharacterData.mRegionType                    = ROT_UNKNOWN;    
            playerCharacterData.mRegionID                      = 0;				;
            playerCharacterData.mCharacterTemplateID           = curPlayerChar->characterTemplateID				;
            playerCharacterData.charCurAge                     = curPlayerChar->charCurAge						;
            playerCharacterData.charLifeSpan				   = curPlayerChar->charLifeSpan                    ;
            playerCharacterData.mLevel                         = curPlayerChar->charLvl	            			;
            playerCharacterData.charExp1                       = curPlayerChar->charExp1	            		;
            playerCharacterData.charExp2                       = curPlayerChar->charExp2		        		;
            playerCharacterData.charExp3                       = curPlayerChar->charExp3						;
            playerCharacterData.mHp							   = curPlayerChar->charHP			        		;
            playerCharacterData.mMp                            = curPlayerChar->charMP	                		;
            playerCharacterData.mLineageNum                    = curPlayerChar->charLineageNum	        		;
            playerCharacterData.charArtMashID1                 = curPlayerChar->charArtMashID1		    		;
            playerCharacterData.charArtMashID2                 = curPlayerChar->charArtMashID2					;
            playerCharacterData.charArtIcon                    = curPlayerChar->charArtIcon						;
            playerCharacterData.charInfluenceID                = curPlayerChar->charInfluenceID					;
            playerCharacterData.charSkillPointAll              = curPlayerChar->charSkillPointAll				;
            playerCharacterData.charNoAssignSkillPoint         = curPlayerChar->charNoAssignSkillPoint			;
            playerCharacterData.charState                      = (CHAR_STATE)curPlayerChar->charState	        ;
            playerCharacterData.charLifeState                  = (CHAR_LIFE_STATE)curPlayerChar->charLifeState	;
            playerCharacterData.mDir                           = (NetVec2)curPlayerChar->charDir				;
            playerCharacterData.charAttrAppendId			   = curPlayerChar->charAttrAppendId;
            playerCharacterData.charAttrAppendLvlAddId		   = curPlayerChar->charAttrAppendLvlAddId;

            for (Int j=0; j<DB_RECORD_ATTR_NUM; j++)
            {
                playerCharacterData.charAttrRand[j]             = curPlayerChar->attrRand[j];
                playerCharacterData.charAttrRandAdd[j]          = curPlayerChar->attrRandAdd[j];
            }


            //SPlayerCharacterPtr playerChar;
            //playerPtr->createPlayerCharacter( playerCharacterData.mId, playerCharacterData );
            //playerChar.setHp(curPlayerChar->charHP);
            //playerChar.setMp(curPlayerChar->charMP);
        }
	}

	//--------------------------------------------------------------------------
	void SPlayerNetPacketProcesser::onRecvTroopList( I32 frontId , PT_PLAYER_F2M_TROOP_INFO_LIST_DATA* data)
	{
	}
    
    //--------------------------------------------------------------------------
	void SPlayerNetPacketProcesser::onRecvSyncAllListEnd( I32 frontId , PT_PLAYER_S2S_SYNC_ALL_LIST_END_DATA* data)
	{
	}
    
	//--------------------------------------------------------------------------
	void SPlayerNetPacketProcesser::onRecvPlayerJumpToRegion( I32 frontId , PT_PLAYER_F2M_JUMP_REGION_DATA* data)
	{
		//SWorldManager::getInstance().playerJumpRegion(data->accountId, (REGION_OBJ_TYPE)data->regionType, data->regionId, data->instanceUid, frontId);

		MG_LOG(out_sys, "\n ====================玩家跳转 Begin===================================================== \n ");
		SWorldManager::getInstance().printWorldObject();
		MG_LOG(out_sys, "\n ====================玩家跳转 End===================================================== \n ");
	}

	//--------------------------------------------------------------------------
	void SPlayerNetPacketProcesser::onRecvPlayerJumpToRegionByCharId( I32 frontId , PT_PLAYER_F2M_JUMP_REGION_BY_CHAR_ID_DATA* data)
	{
#if 0
        SPlayerPtr playerPtr;
        if ( SPlayerManager::getInstance().getPlayer( playerPtr, data->accountId ) == false )
        {
            DYNAMIC_EEXCEPT_LOG("not find player");
            return;
        }
        SPlayerCharacterPtr playerCharPtr;
        if ( playerPtr->retrievePlayerCharacter( playerCharPtr, data->playerCharacterId ) == false )
        {
            DYNAMIC_EEXCEPT_LOG("not find playerCharacter");
            return;
        }
       

		SRegionObjectBase* regionObj = playerCharPtr->getCurrentRegionObject();
		if (NULL == regionObj)
		{
			return;
		}

		//if (NULL != regionObj->getPlayer(data->accountId))
		//{
		//	//已经在地图中
		//	return;
		//}

		const RegionIdType regionId = regionObj->getRegionId();
		const REGION_OBJ_TYPE regionType = regionObj->getRegionType();
		const InstanceUIdType instanceUid = regionObj->getInstanceUId();

		DYNAMIC_ASSERT(playerCharacter->getAccountId() == data->accountId);

		SWorldManager::getInstance().playerJumpRegion(data->accountId, regionType, regionId, instanceUid, frontId);
#endif
	}

	//--------------------------------------------------------------------------
	void SPlayerNetPacketProcesser::onRecvTiroList( I32 frontId , PT_PLAYER_F2M_TIRO_LIST_DATA* data)
	{
		SPlayerPtr player;
		if (false == SPlayerManager::getInstance().getPlayer(player, data->accountId))
		{
			return;
		}

		DYNAMIC_ASSERT(false == player.isNull());
		if ( player.isNull() )
		{
			return;
		}

		std::map<RegionIdType, SBigRegionObject*>* tiroList = NULL;//SWorldManager::getInstance().getBigTiroRegionList();

		SPlayerNetPacketProcesser::getInstance().sendTiroListToClient(player, tiroList, data->mapServerNetId);
	}

	//--------------------------------------------------------------------------
	void SPlayerNetPacketProcesser::onRecvPlayerCharacterEquipList( I32 frontId, PT_PLAYER_F2M_PLAYERCHARACTER_EQUIP_INFO_LIST_DATA* data )
	{
       //SWorldManager::getInstance().attchPlayerCharacterListEquipInfo(frontId,data->playerCharacterEquip,data->playerCharacterNum);
	}


	//--------------------------------------------------------------------------
}