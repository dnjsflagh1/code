/******************************************************************************/
#include "stdafx.h"
#include "ClientNetApplyManager.h"
#include "PlayerCharacterNetPacket.h"
#include "PlayCharacterNetPacketProcesser.h"
//#include "CWorldManager.h"
#include "CPlayerCharacterEntity.h"
#include "CSceneManager.h"
#include "CPlayer.h"
#include "ClientMain.h"
#include "HeadDamageManage.h"
#include "UIMessageBox.h"

#include "PlayerCharacterData.h"

#include "NetPacketPackManager.h"
#include "PlayerNetPacketProcesser.h"
#include "SkillObject.h"
#include "CSkillOwnManager.h"
#include "UIMessageBox.h"
#include "MapListCsv.h"
#include "CRegionManager.h"
#include "MapType2RegionObject.h"
#include "UIInteractiveControl.h"
#include "CAIEntityPathFindingMoveInAdvance.h"
#include "UIClanInfo.h"
/******************************************************************************/
namespace MG
{
    //-----------------------------------------------------------------------
	Bool PlayCharacterNetPacketProcesser::processFrontServerPacket(I32 id,NetEventRecv* packet)
	{
		if ( packet->getChannel() == GNPC_PLAYER_CHARACTER )
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_PLAYERCHARACTER_S2C_MOVE_POS:
				onRecvPlayerCharacterMove( id, (PT_PLAYERCHARACTER_S2C_MOVE_POS_DATA*)data->data );
				break;
			case PT_PLAYERCHARACTER_S2C_STOP_MOVE:
				onRecvPlayerCharacterStopMove(id, (PT_PLAYERCHARACTER_S2C_STOP_MOVE_DATA*)data->data);
				break;
			case PT_PLAYERCHARACTER_F2C_SKILL_INFO:
				onRecvPlayerCharacterSkillInfo( id, (PT_PLAYERCHARACTER_F2C_SKILL_INFO_DATA*)data->data);
				break;
			case PT_PLAYERCHARACTER_F2C_JUMP_REGION:
				onRecvPlayerCharacterJumpRegion( id, (PT_PLAYERCHARACTER_F2C_JUMP_REGION_DATA*)data->data);
				break;
			case PT_PLAYERCHARACTER_S2C_ENTER_FIGHT:
				onRecvPlayerCharacterEnterFight( id, (PT_PLAYERCHARACTER_S2C_ENTER_FIGHT_DATA*)data->data);
				break;
			case PT_PLAYERCHARACTER_S2C_END_FIGHT:
				onRecvPlayerCharacterEndFight( id, (PT_PLAYERCHARACTER_S2C_END_FIGHT_DATA*)data->data);
				break;
			}
			return true;
		}

		return false;
	}
    
    //-----------------------------------------------------------------------
    void PlayCharacterNetPacketProcesser::sendPlayerCharacterMoveToPackBuffer(GameObjectIndexIdInSceneType id, Vec3 startMovePos, Vec3 endMovePos, Bool isBlockCheck)
    {
        //TODO:
		PT_PLAYERCHARACTER_C2S_MOVE_POS_DATA sendData;

			// 填充逻辑包
		sendData.playercharacterIndex = id;
		/*sendData.startMovePos.x = startMovePos.x;
		sendData.startMovePos.z = startMovePos.z;
		sendData.endMovePos.x = endMovePos.x;
		sendData.endMovePos.z = endMovePos.z;*/
		NetVec2 netVec2 = startMovePos;
		sendData.startMovePos = netVec2.getData();
		netVec2 = endMovePos;
		sendData.endMovePos = netVec2.getData();
		sendData.isBlockCheck = isBlockCheck;
		NetPacketPackManager::getInstance().addPacketToBuff( PT_PLAYERCHARACTER_MOVE, GOT_PLAYERCHARACTER, (Char8*)&sendData, id );
    }

    //-----------------------------------------------------------------------
	void PlayCharacterNetPacketProcesser::sendPlayerCharacterMove(GameObjectIndexIdInSceneType id, Vec3 startMovePos, Vec3 endMovePos)
	{
        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_PLAYER_CHARACTER;
            packet->type    = PT_PLAYERCHARACTER_C2S_MOVE_POS;

            // 转换逻辑包
            PT_PLAYERCHARACTER_C2S_MOVE_POS_DATA* sendData = (PT_PLAYERCHARACTER_C2S_MOVE_POS_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                sendData->playercharacterIndex = id;
               /* sendData->startMovePos.x = startMovePos.x;
                sendData->startMovePos.z = startMovePos.z;
				sendData->endMovePos.x = endMovePos.x;
				sendData->endMovePos.z = endMovePos.z;*/
				NetVec2 netVec2 = startMovePos;
				sendData->startMovePos = netVec2.getData();
				netVec2 = endMovePos;
				sendData->endMovePos = netVec2.getData();

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_PLAYERCHARACTER_C2S_MOVE_POS_DATA_INFO::dataSize );
            }
        }

		//CPlayerCharacterEntity* plyerCharacterEntity = CSceneManager::getInstance().getPlayerCharacterEntity(id);
		//if(plyerCharacterEntity)
		//{
		//	plyerCharacterEntity->setIsRecvMove(false);
		//}
		
	}

	//-----------------------------------------------------------------------
	void PlayCharacterNetPacketProcesser::sendPlayerCharacterStopMoveToPackBuffer(GameObjectIndexIdInSceneType id)
	{
		PT_PLAYERCHARACTER_C2S_STOP_MOVE_DATA sendData;

		// 填充逻辑包
		sendData.playercharacterIndex = id;

		NetPacketPackManager::getInstance().addPacketToBuff( PT_PLAYERCHARACTER_STOP_MOVE, GOT_PLAYERCHARACTER, (Char8*)&sendData, id );
	}

    //-----------------------------------------------------------------------
	void PlayCharacterNetPacketProcesser::onRecvPlayerCharacterJumpRegion(I32 id, PT_PLAYERCHARACTER_F2C_JUMP_REGION_DATA* data)
	{
		ChatarcterJumpRegionResult result = (ChatarcterJumpRegionResult)data->jumpResult;


		REGION_OBJ_TYPE	regionType	= (REGION_OBJ_TYPE)data->regionType;
		RegionIdType	regionId	= data->regionId;
		InstanceUIdType	instanceUId	= data->instanceUId;

		if (ChatarcterJumpRegionResult_Succeed != result)
		{
			wchar_t errorHint[128] = L"";
			swprintf( errorHint, L"【角色[%I64i]】跳转副本失败,regionId[%d][%d]", 
				data->playerCharacterId, regionId, instanceUId);

			std::wstring str(errorHint);
			UIMessageBox::getInstance().showHint(str);
			return;
		}
		
		DYNAMIC_ASSERT(ChatarcterJumpRegionResult_Succeed == result);

		CPlayerCharacter* playerCharacter = CPlayer::getInstance().getPlayerCharacter(data->playerCharacterId);
		DYNAMIC_ASSERT(NULL != playerCharacter);
		playerCharacter->setRegion(regionType, regionId, instanceUId);

		CPlayer::getInstance().getActiveClan()->setMainPlayerCharacter(playerCharacter);
		UIClanInfo::getInstance().onHandleSelectGenreal(data->playerCharacterId);
		//角色成功跳转了 摄像机也一起进去
		U64 accountID = CPlayer::getInstance().getAccountID();
		PlayerNetPacketProcesser::getInstance().sendPlayerEnterRegionByCharId(accountID, data->playerCharacterId);
		//const AccountIdType accountId = CPlayer::getInstance().getAccountID();
		//PlayerNetPacketProcesser::getInstance().sendPlayerEnterRegionByCharId(accountId, data->playerCharacterId);
		//PlayerNetPacketProcesser::getInstance().sendPlayerEnterRegion(regionType, regionId, instanceUId);
	}

	//-----------------------------------------------------------------------
	void PlayCharacterNetPacketProcesser::sendPlayerCharacterJumpOutRegion()
	{
		CPlayer* myPlayer = &(CPlayer::getInstance());
		CPlayerCharacter* myCharacter = myPlayer->getActiveClan()->getMainGenreal();
		DYNAMIC_ASSERT(NULL != myCharacter);
		if (MT_Distribution == myCharacter->getRegionType())
		{
			UIMessageBox::getInstance().showHint(L"您当前在 大地图中");
			return;
		}

		sendPlayerCharacterJumpOutRegion(myPlayer->getAccountID(), myCharacter->getID());
	}


	void PlayCharacterNetPacketProcesser::jumpMapForUI(PlayerCharacterIdType playerCharacterId, MapType mapType, RegionIdType mapId, InstanceUIdType instanceId, Int pointId)
	{
		DYNAMIC_ASSERT(instanceId >= 0 && pointId >= 0);
		
		REGION_OBJ_TYPE toRegionType = ROT_UNKNOWN;
		RegionIdType	toRegionId = 0;
		
		MapType2RegionObject::MapTypeChangeRegionObject(mapType, mapId, toRegionType, toRegionId);

		sendPlayerCharacterJumpRegion(playerCharacterId, toRegionType, toRegionId, instanceId, pointId);
	}

    //-----------------------------------------------------------------------
	void PlayCharacterNetPacketProcesser::sendPlayerCharacterJumpRegion(PlayerCharacterIdType playerCharacterId, REGION_OBJ_TYPE toRegionType, RegionIdType toRegionId, InstanceUIdType instanceUId, Int pointId)
	{
        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_PLAYER_CHARACTER;
            packet->type    = PT_PLAYERCHARACTER_C2F_JUMP_REGION;

            // 转换逻辑包
            PT_PLAYERCHARACTER_C2F_JUMP_REGION_DATA* sendData = (PT_PLAYERCHARACTER_C2F_JUMP_REGION_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                sendData->playerCharacterId = playerCharacterId;
                sendData->toRegionId		= toRegionId;
				sendData->toRegionType		= toRegionType;
				sendData->toInstanceUId 	= instanceUId;
				sendData->pointId			= pointId;

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_PLAYERCHARACTER_C2F_JUMP_REGION_INFO::dataSize );
            }
        }
    }

	void PlayCharacterNetPacketProcesser::sendPlayerCharacterJumpTiroRegion(NetIdType mapServerNetId, PlayerCharacterIdType playerCharacterId, REGION_OBJ_TYPE toRegionType, RegionIdType toRegionId, InstanceUIdType instanceUId, Int pointId)
	{
		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_PLAYER_CHARACTER;
			packet->type    = PT_PLAYERCHARACTER_C2F_JUMP_REGION_TIRO;

			// 转换逻辑包
			PT_PLAYERCHARACTER_C2F_JUMP_REGION_TIRO_DATA* sendData = (PT_PLAYERCHARACTER_C2F_JUMP_REGION_TIRO_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->playerCharacterId = playerCharacterId;
				sendData->toRegionId		= toRegionId;
				sendData->toRegionType		= toRegionType;
				sendData->toInstanceUId 	= instanceUId;
				sendData->pointId			= pointId;
				sendData->mapServerNetId	= mapServerNetId;

				// 发送数据
				ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
					GameNetPacketData_INFO::headSize + PT_PLAYERCHARACTER_C2F_JUMP_REGION_TIRO_INFO::dataSize );
			}
		}
	}

	//-----------------------------------------------------------------------
	void PlayCharacterNetPacketProcesser::sendPlayerCharacterJumpOutRegion(AccountIdType accountId, PlayerCharacterIdType playerCharacterId)
	{
		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_PLAYER_CHARACTER;
			packet->type    = PT_PLAYERCHARACTER_C2F_JUMP_OUT_REGION;

			// 转换逻辑包
			PT_PLAYERCHARACTER_C2F_JUMP_OUT_REGION_DATA* sendData = (PT_PLAYERCHARACTER_C2F_JUMP_OUT_REGION_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->accountId			= accountId;
				sendData->playerCharacterId = playerCharacterId;


				// 发送数据
				ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
					GameNetPacketData_INFO::headSize + PT_PLAYERCHARACTER_C2F_JUMP_OUT_REGION_INFO::dataSize );
			}
		}
	}

	//-----------------------------------------------------------------------
	void PlayCharacterNetPacketProcesser::sendPlayerCharacterJumpLastRegion(PlayerCharacterIdType playerCharacterId)
	{
		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_PLAYER_CHARACTER;
			packet->type    = PT_PLAYERCHARACTER_C2F_JUMP_LAST_REGION;

			// 转换逻辑包
			PT_PLAYERCHARACTER_C2F_JUMP_LAST_REGION_DATA* sendData = (PT_PLAYERCHARACTER_C2F_JUMP_LAST_REGION_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->playerCharacterId = playerCharacterId;


				// 发送数据
				ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
					GameNetPacketData_INFO::headSize + PT_PLAYERCHARACTER_C2F_JUMP_LAST_REGION_INFO::dataSize );
			}
		}
	}
	//-----------------------------------------------------------------------
	void PlayCharacterNetPacketProcesser::onRecvPlayerCharacterMove( I32 id, PT_PLAYERCHARACTER_S2C_MOVE_POS_DATA* data )
	{
		//FUNDETECTION(__MG_FUNC__);
		CPlayerCharacterEntity* playerCharacterEntity = CSceneManager::getInstance().getPlayerCharacterEntity(data->playercharacterIndex);
		if (NULL != playerCharacterEntity)
		{
			ISceneNodeGridLineMoveToAction::MoveToPathFindType moveToPathFindType = ISceneNodeGridLineMoveToAction::PFT_NOPATHFIND;
			Bool isBlockCheck = false;
			CRegionObject* currRegion = CSceneManager::getInstance().getCurrRegion();
			if(currRegion && currRegion->getGameType() == GameType_Slg)
			{
				isBlockCheck = data->isBlockCheck;
			}

			if(playerCharacterEntity->getDynamicData()->belongPlayerID == CPlayer::getInstance().getAccountID())
			{
				CAIEntityPathFindingMoveInAdvance* aiEntityPathFindingMoveInAdvance = (CAIEntityPathFindingMoveInAdvance*)playerCharacterEntity->getAIStateManager().getState(CAIEntityPathFindingMoveInAdvance::STATE_NAME, false);
				if(aiEntityPathFindingMoveInAdvance)
				{
					Bool isStaticMove = aiEntityPathFindingMoveInAdvance->getIsStaticMove();
					if(isStaticMove)
					{
						moveToPathFindType = ISceneNodeGridLineMoveToAction::PFT_STATIC;
					}
					else
					{
						moveToPathFindType = ISceneNodeGridLineMoveToAction::PFT_DYNAMIC;
					}
				}

			}

			playerCharacterEntity->doMoveToAction(((NetVec2)data->startMovePos), ((NetVec2)data->endMovePos), data->startMoveTime, isBlockCheck, moveToPathFindType);
		}
	}

	//-----------------------------------------------------------------------
	void PlayCharacterNetPacketProcesser::onRecvPlayerCharacterStopMove( I32 id, PT_PLAYERCHARACTER_S2C_STOP_MOVE_DATA* data )
	{
		CPlayerCharacterEntity* playerCharacterEntity = CSceneManager::getInstance().getPlayerCharacterEntity(data->playercharacter_index);
		if (NULL != playerCharacterEntity)
		{
			playerCharacterEntity->stopMoveToAction();
		}
	}

	//-----------------------------------------------------------------------
	void PlayCharacterNetPacketProcesser::onRecvPlayerCharacterSkillInfo(I32 id, PT_PLAYERCHARACTER_F2C_SKILL_INFO_DATA* data)
	{
		//FUNDETECTION(__MG_FUNC__);
		CPlayerCharacter* playerCharacter = CPlayer::getInstance().getActiveClan()->getPlayerCharacter(data->playercharacterId);
		if (NULL != playerCharacter)
		{
			for(UInt i = 0; i < data->skillNum; ++i)
			{
				playerCharacter->getSkillOwnManager()->addOwnerSkill(data->skillList[i].skillId);
			}
		}
	}

	//-----------------------------------------------------------------------
	void PlayCharacterNetPacketProcesser::onRecvPlayerCharacterEnterFight(I32 id, PT_PLAYERCHARACTER_S2C_ENTER_FIGHT_DATA* data)
	{
		CPlayerCharacterEntity* playerCharacterEntity = CSceneManager::getInstance().getPlayerCharacterEntity(data->playercharacterIndex);
		if (NULL != playerCharacterEntity)
		{
			playerCharacterEntity->setBattleState(true);
		}	
	}

	//-----------------------------------------------------------------------
	void PlayCharacterNetPacketProcesser::onRecvPlayerCharacterEndFight(I32 id, PT_PLAYERCHARACTER_S2C_END_FIGHT_DATA* data)
	{
		CPlayerCharacterEntity* playerCharacterEntity = CSceneManager::getInstance().getPlayerCharacterEntity(data->playercharacterIndex);
		if (NULL != playerCharacterEntity)
		{
			playerCharacterEntity->setBattleState(false);
		}
	}

	//-----------------------------------------------------------------------
	//void PlayCharacterNetPacketProcesser::onRecvPlayerCharacterJumpRegionError(I32 id, PT_PLAYERCHARACTER_F2C_JUMP_REGION_ERROR_DATA* data)
	//{
	//	switch(data->error)
	//	{
	//	case PlayerCharacter_Jump_server_crash:
	//		{
	//			UIMessageBox::getInstance().showHint(L"角色跳转地图失败， MapServer当机");
	//		}
	//		break;
	//	}
	//}

	//-----------------------------------------------------------------------

}