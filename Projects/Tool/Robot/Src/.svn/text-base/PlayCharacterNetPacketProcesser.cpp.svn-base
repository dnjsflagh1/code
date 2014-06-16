/******************************************************************************/
#include "stdafx.h"
#include "ClientNetApplyManager.h"
#include "PlayerCharacterNetPacket.h"
#include "PlayCharacterNetPacketProcesser.h"
//#include "CWorldManager.h"
#include "CPlayer.h"
#include "PlayerCharacterData.h"
#include "PlayerNetPacketProcesser.h"
#include "CClientNew.h"
/******************************************************************************/
namespace MG
{
    //-----------------------------------------------------------------------
	Bool PlayCharacterNetPacketProcesser::processFrontServerPacket(CClient* client,NetEventRecv* packet)
	{
		if ( packet->getChannel() == GNPC_PLAYER_CHARACTER )
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_PLAYERCHARACTER_S2C_MOVE_POS:
				onRecvPlayerCharacterMove( client, (PT_PLAYERCHARACTER_S2C_MOVE_POS_DATA*)data->data );
				break;
			/*case PT_PLAYERCHARACTER_S2C_DAMAGE:
				onRecvSyncPlayerCharacterDamage( client, (PT_PLAYERCHARACTER_S2C_DAMAGE_DATA*)data->data );
				break;
			case PT_PLAYERCHARACTER_F2C_DAMAGE:
				onRecvPlayerCharacterDamage( client, (PT_PLAYERCHARACTER_F2C_DAMAGE_DATA*)data->data );
				break;*/
			case PT_PLAYERCHARACTER_F2C_SKILL_INFO:
				onRecvPlayerCharacterSkillInfo( client, (PT_PLAYERCHARACTER_F2C_SKILL_INFO_DATA*)data->data);
				break;
			//case PT_PLAYERCHARACTER_F2C_JUMP_REGION_ERROR:
			//	onRecvPlayerCharacterJumpRegionError( client, (PT_PLAYERCHARACTER_F2C_JUMP_REGION_ERROR_DATA*)data->data);
			//	break;
			case PT_PLAYERCHARACTER_F2C_JUMP_REGION:
				onRecvPlayerCharacterJumpRegion( client, (PT_PLAYERCHARACTER_F2C_JUMP_REGION_DATA*)data->data);
				break;
			}
			return true;
		}

		return false;
	}
    
    //-----------------------------------------------------------------------
    void PlayCharacterNetPacketProcesser::sendPlayerCharacterMoveToPackBuffer(CClient* client,IdType id, Vec3 startMovePos, Vec3 endMovePos)
    {
        //TODO:
		PT_PLAYERCHARACTER_C2S_MOVE_POS_DATA sendData;

			// 填充逻辑包
		sendData.playercharacter_id = id;
		/*sendData.startMovePos.x = startMovePos.x;
		sendData.startMovePos.z = startMovePos.z;
		sendData.endMovePos.x = endMovePos.x;
		sendData.endMovePos.z = endMovePos.z;*/
		sendData.startMovePos = ((NetVec2)startMovePos).getData();
		sendData.endMovePos = ((NetVec2)endMovePos).getData();

		client->getPackManager()->addPacketToBuff( PT_PLAYERCHARACTER_MOVE, GOT_PLAYERCHARACTER, (Char8*)&sendData, id );
    }

    //-----------------------------------------------------------------------
	void PlayCharacterNetPacketProcesser::sendPlayerCharacterMove(I32 frontServerNetId,IdType id, Vec3 startMovePos, Vec3 endMovePos)
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
                sendData->playercharacter_id = id;
                /*sendData->startMovePos.x = startMovePos.x;
                sendData->startMovePos.z = startMovePos.z;
				sendData->endMovePos.x = endMovePos.x;
				sendData->endMovePos.z = endMovePos.z;*/
				sendData->startMovePos = ((NetVec2)startMovePos).getData();
				sendData->endMovePos = ((NetVec2)endMovePos).getData();

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket(frontServerNetId, dataPtr , 
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
	void PlayCharacterNetPacketProcesser::onRecvPlayerCharacterJumpRegion(CClient* client, PT_PLAYERCHARACTER_F2C_JUMP_REGION_DATA* data)
	{
		ChatarcterJumpRegionResult result = (ChatarcterJumpRegionResult)data->jumpResult;


		REGION_OBJ_TYPE	regionType	= (REGION_OBJ_TYPE)data->regionType;
		RegionIdType	regionId	= data->regionId;
		InstanceIdType	instanceId	= data->instanceUId;

		if (ChatarcterJumpRegionResult_Succeed != result)
		{
			wchar_t errorHint[128] = L"";
			//swprintf( errorHint, L"【角色】跳转副本失败 PlayerCharacterIdType[%I64i], regionType[%d],regionId[%d], instanceId[%d]", 
				//data->playerCharacterId, regionType, regionId, instanceId);
			swprintf( errorHint, L"【角色】跳转副本失败 PlayerCharacterIdType[%I64i],regionId[%d], instanceId[%d]", 
			data->playerCharacterId, regionId, instanceId);

			//std::wstring str(errorHint);
			//UIMessageBox::getInstance().showHint(str);
			return;
		}
		
		DYNAMIC_ASSERT(ChatarcterJumpRegionResult_Succeed == result);

		CPlayerCharacter* playerCharacter = client->getPlayerObj()->getPlayerCharacter(data->playerCharacterId);
		if ( playerCharacter )
		{
			playerCharacter->setRegion(regionType, regionId, instanceId);
		}
		//DYNAMIC_ASSERT(NULL != playerCharacter);

		//角色成功跳转了 摄像机也一起进去
		//PlayerNetPacketProcesser::getInstance().sendPlayerEnterRegion(regionId, regionType);
	}

 //   //-----------------------------------------------------------------------
	//void PlayCharacterNetPacketProcesser::onRecvSyncPlayerCharacterDamage(I32 id, PT_PLAYERCHARACTER_S2C_DAMAGE_DATA* data)
	//{
	//	//FUNDETECTION(__MG_FUNC__);
	//	CPlayerCharacterEntity* entity = CSceneManager::getInstance().getPlayerCharacterEntity( data->playercharacterId );
	//	if(entity)
	//	{
 //           if ( data->val == 0 )
 //               HeadDamageManage::getInstance().addMiss( entity->getPos() );
 //           else if(entity->getData()->charHP > 0)
	//		{
 //               HeadDamageManage::getInstance().addNum( entity->getPos(), (EFFECT_TYPE)data->damageType, data->val, false );
	//			entity->getData()->charHP -= data->val;
	//			if(entity->getData()->charHP <= 0)
	//			{
	//				entity->die();
	//				//CSceneManager::getInstance().destroyPlayerCharacterEntity(entity->getID());
	//			}
	//		}
	//	}
	//}

 //   //-----------------------------------------------------------------------
	//void PlayCharacterNetPacketProcesser::onRecvPlayerCharacterDamage(I32 id, PT_PLAYERCHARACTER_F2C_DAMAGE_DATA* data)
	//{
	//	//FUNDETECTION(__MG_FUNC__);
	//	CPlayerCharacter* playerCharacter = CPlayer::getInstance().getActiveClan()->getPlayerCharacter(data->playercharacterId);
	//	if(playerCharacter)
	//	{
 //           playerCharacter->reduce(data->val, (EFFECT_TYPE)data->damageType);
	//	}
	//}

    //-----------------------------------------------------------------------
	void PlayCharacterNetPacketProcesser::sendPlayerCharacterJumpRegion( I32 frontServerNetId,IdType playerCharacterId,IdType toRegionId,REGION_OBJ_TYPE toRegionType, InstanceIdType instanceId,Int pointId)
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
                //sendData->toRegionType 		= toRegionType;
				sendData->toInstanceUId 		= instanceId;
				sendData->pointId =				pointId;
                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket( frontServerNetId,dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_PLAYERCHARACTER_C2F_JUMP_REGION_INFO::dataSize );
            }
        }
	
    }

	//-----------------------------------------------------------------------
	void PlayCharacterNetPacketProcesser::onRecvPlayerCharacterMove( CClient* client, PT_PLAYERCHARACTER_S2C_MOVE_POS_DATA* data )
	{

        CClan* tempClan = NULL;
		tempClan = client->getPlayerObj()->getActiveClan();
		if (tempClan == NULL)
		{
		    return;
		}
        CPlayerCharacter* character = NULL;
		character = tempClan->getMainGenreal();
		if (character == NULL)
		{
			return;
		}
		if (data->playercharacter_id == character->getID())
		{
			character->getCharacterData()->mPos = (NetVec2)data->endMovePos; //Vec3(data->endMovePos.x, 0, data->endMovePos.z);
		}
		
		//FUNDETECTION(__MG_FUNC__);
		//CPlayerCharacterEntity* playerCharacterEntity = CSceneManager::getInstance().getPlayerCharacterEntity(data->playercharacter_id);
		//if (NULL != playerCharacterEntity)
		{
			//playerCharacterEntity->doMoveToAction(Vec3(data->startMovePos.x, 0, data->startMovePos.z), Vec3(data->endMovePos.x, 0, data->endMovePos.z), data->startMoveTime, true);
			//playerCharacterEntity->moveTo( Vec3(data->pos.x, 0, data->pos.z) );

			//if(playerCharacterEntity->getBelongPlayerID() == CPlayer::getInstance().getAccountID())
			//{
			//	playerCharacterEntity->setIsRecvMove(true);
			//}
		}
	}

	//-----------------------------------------------------------------------
	void PlayCharacterNetPacketProcesser::onRecvPlayerCharacterSkillInfo(CClient* client, PT_PLAYERCHARACTER_F2C_SKILL_INFO_DATA* data)
	{
		//FUNDETECTION(__MG_FUNC__);
		/*CPlayerCharacter* playerCharacter = client->getPlayerObj()->getActiveClan()->getPlayerCharacter(data->playercharacterId);
		SkillData skillData;
		if (NULL != playerCharacter)
		{
			for(UInt i = 0; i < data->skillNum; ++i)
			{
				skillData.skillId = data->skillList[i].skillId;
				skillData.skillLevel = data->skillList[i].skillLevel;
				playerCharacter->addSkill(skillData);
			}
		}
		*/
	}

	//-----------------------------------------------------------------------
	//void PlayCharacterNetPacketProcesser::onRecvPlayerCharacterJumpRegionError(CClient* client, PT_PLAYERCHARACTER_F2C_JUMP_REGION_ERROR_DATA* data)
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