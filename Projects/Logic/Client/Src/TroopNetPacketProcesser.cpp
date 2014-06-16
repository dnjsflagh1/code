
/******************************************************************************/
#include "stdafx.h"
#include "TroopNetPacketProcesser.h"
#include "ClientNetApplyManager.h"
#include "CPlayer.h"
#include "CSceneManager.h"
#include "HeadDamageManage.h"
#include "CTroopEntity.h"
#include "NetPacketPackManager.h"
#include "CTroopSoldierEntity.h"
#include "CAIEntityPathFindingMoveInAdvance.h"
/******************************************************************************/

namespace MG
{
	//-----------------------------------------------------------------------------
	Bool TroopNetPacketProcesser::processFrontServerPacket(I32 id, NetEventRecv *packet)
	{
		if ( packet->getChannel() == GNPC_TROOP )
		{
			FUNDETECTION(__MG_FUNC__);
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_TROOP_S2C_MOVE_POS:
				onRecvTroopEntityMove( id, (PT_TROOP_S2C_MOVE_POS_DATA*)data->data );
				break;
			case PT_TROOP_SOLDIER_S2C_MOVE_POS:
				//onRecvTroopSoldierMove( id, (PT_TROOP_SOLDIER_S2C_MOVE_POS_DATA*)data->data );
				break;
			case PT_TROOP_GROUP_F2C_SKILL_INFO:
				onRecvTroopSkillInfo( id, (PT_TROOP_GROUP_F2C_SKILL_INFO_DATA*)data->data );
				break;
			case PT_TROOP_S2C_STOP_MOVE:
				onRecvTroopEntityStopMove( id, (PT_TROOP_S2C_STOP_MOVE_DATA*)data->data );
				break;
			case PT_TROOP_S2C_ENTER_FIGHT:
				onRecvTroopEnterFight( id, (PT_TROOP_S2C_ENTER_FIGHT_DATA*)data->data );
				break;
			case PT_TROOP_S2C_END_FIGHT:
				onRecvTroopEndFight( id, (PT_TROOP_S2C_END_FIGHT_DATA*)data->data );
				break;
			}
			return true;
		}
		return false;
	}

	//-----------------------------------------------------------------------------
	void TroopNetPacketProcesser::sendTroopGroupJumpRegion(IdType troopId, IdType toRegionId,REGION_OBJ_TYPE toRegionType)
	{
        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_TROOP;
            packet->type    = PT_TROOP_GROUP_C2F_JUMP_REGION;

            // 转换逻辑包
            PT_TROOP_GROUP_C2F_JUMP_REGION_DATA* sendData = (PT_TROOP_GROUP_C2F_JUMP_REGION_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                sendData->troopId		= troopId;
                sendData->toRegionType	= (Byte)toRegionType;
                sendData->toRegionId		= toRegionId;

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_TROOP_GROUP_C2F_JUMP_REGION_DATA_INFO::dataSize );
            }
        }

       	
    }


	//-----------------------------------------------------------------------------
	void TroopNetPacketProcesser::sendTroopEntityMoveToPackBuffer( GameObjectIndexIdInSceneType troopIndex, Vec3 startMovePos, Vec3 endMovePos, Bool isBlockCheck )
	{
		PT_TROOP_C2S_MOVE_POS_DATA sendData;

		sendData.troopIndex = troopIndex;
		/*sendData.startMovePos.x = startMovePos.x;
		sendData.startMovePos.z = startMovePos.z;
		sendData.endMovePos.x = endMovePos.x;
		sendData.endMovePos.z = endMovePos.z;*/
		sendData.startMovePos = ((NetVec2)startMovePos).getData();
		sendData.endMovePos = ((NetVec2)endMovePos).getData();
		sendData.isBlockCheck = isBlockCheck;

		NetPacketPackManager::getInstance().addPacketToBuff( PT_TROOP_MOVE, GOT_TROOP, (Char8*)&sendData , troopIndex );
	}

	//-----------------------------------------------------------------------------
	//void TroopNetPacketProcesser::sendTroopSoldierMove(IdType troopId, Byte troopIndex, Vec3 pos)
	//{  
 //       // 获得一个发送【服务端】缓存
 //       GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

 //       // 转换成标准包格式
 //       GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getData();
 //       if ( packet )
 //       {
 //           // 设置标签
 //           packet->channel = GNPC_TROOP;
 //           packet->type    = PT_TROOP_SOLDIER_C2S_MOVE_POS;

 //           // 转换逻辑包
 //           PT_TROOP_SOLDIER_C2S_MOVE_POS_DATA* sendData = (PT_TROOP_SOLDIER_C2S_MOVE_POS_DATA*)(packet->data);
 //           if ( sendData )
 //           {
 //               // 填充逻辑包
 //               sendData->troopId = troopId;
 //               sendData->troopIndex = troopIndex;
 //               sendData->pos.x = pos.x;
 //               sendData->pos.z = pos.z;

 //               // 发送数据
 //               ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
 //                   GameNetPacketData_INFO::headSize + PT_TROOP_SOLDIER_C2S_MOVE_POS_DATA_INFO::dataSize );
 //           }
 //       }
	//
 //   }

	//-----------------------------------------------------------------------------
	void TroopNetPacketProcesser::onRecvTroopEntityMove( I32 id, PT_TROOP_S2C_MOVE_POS_DATA* data )
	{
		//FUNDETECTION(__MG_FUNC__);
		CTroopEntity* troopEntity = CSceneManager::getInstance().getTroopEntity(data->troopIndex);
		if(troopEntity)
		{
			ISceneNodeGridLineMoveToAction::MoveToPathFindType moveToPathFindType = ISceneNodeGridLineMoveToAction::PFT_NOPATHFIND;

			CAIEntityPathFindingMoveInAdvance* aiEntityPathFindingMoveInAdvance = (CAIEntityPathFindingMoveInAdvance*)troopEntity->getAIStateManager().getState(CAIEntityPathFindingMoveInAdvance::STATE_NAME, false);
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

			troopEntity->doMoveToAction((NetVec2)data->startMovePos, (NetVec2)data->endMovePos, data->startMoveTime, data->isBlockCheck, moveToPathFindType);
		}
	}

	//-----------------------------------------------------------------------------
	void TroopNetPacketProcesser::onRecvTroopEntityStopMove( I32 id, PT_TROOP_S2C_STOP_MOVE_DATA* data )
	{
		CTroopEntity* troopObject = CSceneManager::getInstance().getTroopEntity(data->troopIndex);
		if(NULL == troopObject)
		{
			//error
			return;
		}
	
		troopObject->stopMoveToAction();
	}


	//-----------------------------------------------------------------------------
	void TroopNetPacketProcesser::onRecvTroopSoldierMove( I32 id, PT_TROOP_SOLDIER_S2C_MOVE_POS_DATA* data )
	{
		//FUNDETECTION(__MG_FUNC__);
		CTroopEntity* troopObject = CSceneManager::getInstance().getTroopEntity(data->troopIndex);
		if(NULL == troopObject)
		{
			//error
			return;
		}
		CTroopSoldierEntity* troopSoldierEntity = troopObject->getSoldierEntitys(data->soldierIndex);
		if (NULL != troopSoldierEntity)
		{
			//troopEntity->getAIManager()->setTargetDir(Vec3(0, 0, 0));
			//troopEntity->getAIManager()->setTargetPos(Vec3(data->pos.x, 0, data->pos.z));
			//troopEntity->getAIManager()->setAIState(move);
			troopSoldierEntity->doMoveToAction((NetVec2)data->startMovePos, (NetVec2)data->endMovePos, data->startMoveTime);
		}
	}

	//-----------------------------------------------------------------------------
	void TroopNetPacketProcesser::onRecvTroopSoldierStopMove( I32 id, PT_TROOP_SOLDIER_S2C_STOP_MOVE_DATA* data )
	{
		CTroopEntity* troopObject = CSceneManager::getInstance().getTroopEntity(data->troopIndex);
		if(NULL == troopObject)
		{
			//error
			return;
		}

		CTroopSoldierEntity* troopSoldierEntity = troopObject->getSoldierEntitys(data->soldierIndex);
		if (NULL != troopSoldierEntity)
		{
			troopSoldierEntity->stopMoveToAction();
		}
	}

	//-----------------------------------------------------------------------
	void TroopNetPacketProcesser::onRecvTroopSkillInfo(I32 id, PT_TROOP_GROUP_F2C_SKILL_INFO_DATA* data)
	{
		//FUNDETECTION(__MG_FUNC__);
		//CPlayerTroopGroup* playerTroopGroup = CPlayer::getInstance().getActiveClan()->getPlayerTroopGroup(data->troopGroupId);
		//CPlayerTroop* playerTroop = NULL;
		////SkillData skillData;
		//if (NULL != playerTroopGroup)
		{				
			/*for(UInt i = 0; i < playerTroopGroup->getTroopNum(); ++i)
			{					
				playerTroop = (CPlayerTroop*)playerTroopGroup->getTroop(i);
				if(playerTroop)
				{
					for(UInt j = 0; j < data->skillNum; ++j)
					{
						skillData.skillId = data->skillList[j].skillId;
						skillData.skillLevel = data->skillList[j].skillLevel;
						playerTroop->addSkill(skillData);
					}
				}

			}*/
		}
	}


	//-----------------------------------------------------------------------
	void TroopNetPacketProcesser::sendTroopEntityStopMoveToPackBuffer( GameObjectIndexIdInSceneType troopIndex )
	{
		PT_TROOP_C2S_STOP_MOVE_DATA sendData;

		sendData.troopIndex = troopIndex;
		/*sendData.startMovePos.x = startMovePos.x;
		sendData.startMovePos.z = startMovePos.z;
		sendData.endMovePos.x = endMovePos.x;
		sendData.endMovePos.z = endMovePos.z;*/

		NetPacketPackManager::getInstance().addPacketToBuff( PT_TROOP_STOP_MOVE, GOT_TROOP, (Char8*)&sendData , troopIndex );
	}

	
	//-----------------------------------------------------------------------
	void TroopNetPacketProcesser::sendTroopSoldierMove( GameObjectIndexIdInSceneType troopIndex, Int soldierIndex, Vec3 startMovePos, Vec3 endMovePos )
	{
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_TROOP;
			packet->type    = PT_TROOP_SOLDIER_C2S_MOVE_POS;

			// 转换逻辑包
			PT_TROOP_SOLDIER_C2S_MOVE_POS_DATA* sendData = (PT_TROOP_SOLDIER_C2S_MOVE_POS_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->troopIndex = troopIndex;
				sendData->soldierIndex = soldierIndex;
				/*sendData->startMovePos.x = startMovePos.x;
				sendData->startMovePos.z = startMovePos.z;
				sendData->endMovePos.x = endMovePos.x;
				sendData->endMovePos.z = endMovePos.z;*/
				sendData->startMovePos = ((NetVec2)startMovePos).getData();
				sendData->endMovePos = ((NetVec2)endMovePos).getData();

				// 发送数据
				ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
					GameNetPacketData_INFO::headSize + PT_TROOP_SOLDIER_C2S_MOVE_POS_DATA_INFO::dataSize );
			}
		}
	}

	//-----------------------------------------------------------------------
	void TroopNetPacketProcesser::sendTroopSoldierMoveToPackBuffer( GameObjectIndexIdInSceneType troopIndex, Int soldierIndex, Vec3 startMovePos, Vec3 endMovePos )
	{
		PT_TROOP_SOLDIER_C2S_MOVE_POS_DATA sendData;

		// 填充逻辑包
		//sendData->troopIndex = troopIndex;
		//sendData->soldierIndex = soldierIndex;
		///*sendData->startMovePos.x = startMovePos.x;
		//sendData->startMovePos.z = startMovePos.z;
		//sendData->endMovePos.x = endMovePos.x;
		//sendData->endMovePos.z = endMovePos.z;*/
		//sendData->startMovePos = ((NetVec2)startMovePos).getData();
		//sendData->endMovePos = ((NetVec2)endMovePos).getData();

		NetPacketPackManager::getInstance().addPacketToBuff( PT_TROOP_SOLDIER_MOVE, GOT_SOLDIER, (Char8*)&sendData , troopIndex ,soldierIndex );
	}

	//-----------------------------------------------------------------------
	void TroopNetPacketProcesser::sendTroopSoldierStopMoveToPackBuffer( GameObjectIndexIdInSceneType troopIndex, Int soldierIndex )
	{
		PT_TROOP_SOLDIER_C2S_STOP_MOVE_DATA sendData;

		// 填充逻辑包
		sendData.troopIndex= troopIndex;
		sendData.soldierIndex = soldierIndex;

		NetPacketPackManager::getInstance().addPacketToBuff( PT_TROOP_SOLDIER_STOP_MOVE, GOT_SOLDIER, (Char8*)&sendData , troopIndex, soldierIndex );
	}

	//-----------------------------------------------------------------------
	void TroopNetPacketProcesser::onRecvTroopEnterFight(I32 id, PT_TROOP_S2C_ENTER_FIGHT_DATA* data)
	{
		CTroopEntity* troopEntity = CSceneManager::getInstance().getTroopEntity(data->troopIndex);
		if(troopEntity)
		{
			troopEntity->setBattleState(true);
		}	
	}

	//-----------------------------------------------------------------------
	void TroopNetPacketProcesser::onRecvTroopEndFight(I32 id, PT_TROOP_S2C_END_FIGHT_DATA* data)
	{
		CTroopEntity* troopEntity = CSceneManager::getInstance().getTroopEntity(data->troopIndex);
		if (NULL != troopEntity)
		{
			troopEntity->setBattleState(false);
		}
	}

}