
/******************************************************************************/
#include "stdafx.h"
#include "TroopNetPacketProcesser.h"
#include "ClientNetApplyManager.h"
#include "CPlayer.h"
#include "NetPacketPackManager.h"
#include "CClientNew.h"
#include "CTroopSoldier.h"
/******************************************************************************/

namespace MG
{
	//-----------------------------------------------------------------------------
	Bool TroopNetPacketProcesser::processFrontServerPacket(CClient* client, NetEventRecv *packet)
	{
		if ( packet->getChannel() == GNPC_TROOP )
		{
			//FUNDETECTION(__MG_FUNC__);
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_TROOP_S2C_MOVE_POS:
				onRecvTroopEntityMove( client, (PT_TROOP_S2C_MOVE_POS_DATA*)data->data );
				break;
			case PT_TROOP_SOLDIER_S2C_MOVE_POS:
				//onRecvTroopSoldierMove( client, (PT_TROOP_SOLDIER_S2C_MOVE_POS_DATA*)data->data );
				break;
			case PT_TROOP_GROUP_F2C_SKILL_INFO:
				onRecvTroopSkillInfo( client, (PT_TROOP_GROUP_F2C_SKILL_INFO_DATA*)data->data );
				break;
			case PT_TROOP_GROUP_S2C_MOVE_OBJECT:
				onRecvTroopGroupMoveToObject( client, (PT_TROOP_GROUP_S2C_MOVE_OBJECT_DATA*)data->data );
				break;
			case PT_TROOP_S2C_MOVE_OBJECT:
				onRecvTroopMoveToObject( client, (PT_TROOP_S2C_MOVE_OBJECT_DATA*)data->data );
				break;
			case PT_TROOP_GROUP_S2C_YAW_DIR:
				onRecvTroopGroupYawToDir( client, (PT_TROOP_GROUP_S2C_YAW_DIR_DATA*)data->data );
				break;
			case PT_TROOP_S2C_STOP_MOVE:
				onRecvTroopEntityStopMove( client, (PT_TROOP_S2C_STOP_MOVE_DATA*)data->data );
				break;
			}
			return true;
		}
		return false;
	}

	//-----------------------------------------------------------------------------
	void TroopNetPacketProcesser::sendTroopGroupJumpRegion(I32 frontServerNetId,IdType troopId, IdType toRegionId,REGION_OBJ_TYPE toRegionType)
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
                ClientNetApplyManager::getInstance().sendFrontServerPacket(frontServerNetId, dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_TROOP_GROUP_C2F_JUMP_REGION_DATA_INFO::dataSize );
            }
        }

       	
    }

	//-----------------------------------------------------------------------------
	void TroopNetPacketProcesser::sendTroopGroupMove(I32 frontServerNetId,IdType troopId, Vec3 pos)
	{
        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_TROOP;
            packet->type    = PT_TROOP_C2S_MOVE_POS;

            // 转换逻辑包
            PT_TROOP_C2S_MOVE_POS_DATA* sendData = (PT_TROOP_C2S_MOVE_POS_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                sendData->troopId = troopId;
				sendData->endMovePos = ((NetVec2)pos).getData();

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket( frontServerNetId,dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_TROOP_C2S_MOVE_POS_DATA_INFO::dataSize );
            }
        }

	}

	//-----------------------------------------------------------------------------
	void TroopNetPacketProcesser::sendTroopEntityMoveToPackBuffer( CClient* client,REGION_OBJ_TYPE regionType,  RegionIdType regionId, InstanceUIdType instanceUid, IdType troopId, Vec3 startMovePos, Vec3 endMovePos )
	{
		PT_TROOP_C2S_MOVE_POS_DATA sendData;

		// 填充逻辑包
		sendData.regionType = regionType;
		sendData.regionID = regionId;
		sendData.instanceUid = instanceUid;
		sendData.troopId = troopId;
		sendData.startMovePos = ((NetVec2)startMovePos).getData();
		sendData.endMovePos = ((NetVec2)endMovePos).getData();
		client->getPackManager()->addPacketToBuff( PT_TROOP_MOVE, GOT_TROOP, (Char8*)&sendData , troopId);
	}
	//-----------------------------------------------------------------------------
	void TroopNetPacketProcesser::onRecvTroopEntityMove( CClient* client, PT_TROOP_S2C_MOVE_POS_DATA* data )
	{
		std::map<IdType, CTroopObject*>* troopList = client->getPlayerObj()->getActiveClan()->getMainGenreal()->getTroopList();
		if (troopList)
		{
			std::map<IdType, CTroopObject*>::iterator it = troopList->find(data->troopId);
			if (it != troopList->end())
			{
				CTroopObject* troop = it->second;
				troop->getBaseData()->mPos = NetVec2(data->endMovePos);
			}

		}
	}

	void TroopNetPacketProcesser::onRecvTroopGroupMoveToObject( CClient* client, PT_TROOP_GROUP_S2C_MOVE_OBJECT_DATA* data )
	{

	}

	void TroopNetPacketProcesser::onRecvTroopMoveToObject( CClient* client, PT_TROOP_S2C_MOVE_OBJECT_DATA* data )
	{

	}

	void TroopNetPacketProcesser::onRecvTroopGroupYawToDir( CClient* client, PT_TROOP_GROUP_S2C_YAW_DIR_DATA* data )
	{

	}

	void TroopNetPacketProcesser::onRecvTroopEntityStopMove( CClient* client, PT_TROOP_S2C_STOP_MOVE_DATA* data )
	{

	}


	//-----------------------------------------------------------------------------
	void TroopNetPacketProcesser::onRecvTroopSoldierMove( CClient* client, PT_TROOP_SOLDIER_S2C_MOVE_POS_DATA* data )
	{
	}

	void TroopNetPacketProcesser::onRecvTroopSoldierStopMove( CClient* client, PT_TROOP_SOLDIER_S2C_STOP_MOVE_DATA* data )
	{

	}

	//-----------------------------------------------------------------------
	void TroopNetPacketProcesser::onRecvTroopSkillInfo(CClient* client, PT_TROOP_GROUP_F2C_SKILL_INFO_DATA* data)
	{

	}

	//-----------------------------------------------------------------------
	void TroopNetPacketProcesser::sendTroopGroupMoveToObject(I32 frontServerNetId,IdType troopGroupId, IdType targetId, GAMEOBJ_TYPE targetType, Flt radius, Bool isCommand)
	{
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_TROOP;
            packet->type    = PT_TROOP_GROUP_C2S_MOVE_OBJECT;

            // 转换逻辑包
            PT_TROOP_GROUP_C2S_MOVE_OBJECT_DATA* sendData = (PT_TROOP_GROUP_C2S_MOVE_OBJECT_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                sendData->troopGroupId = troopGroupId;
                sendData->objectId = targetId;
                sendData->objectType = targetType;
                sendData->radius = radius;
                sendData->isCommand = isCommand;

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket( frontServerNetId,dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_TROOP_GROUP_C2S_MOVE_OBJECT_DATA_INFO::dataSize );
            }
        }

			
    }

	//-----------------------------------------------------------------------
	void TroopNetPacketProcesser::sendTroopGroupYawToDir(I32 frontServerNetId,IdType troopGroupId, Vec3 dir)
	{
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_TROOP;
            packet->type    = PT_TROOP_GROUP_C2S_YAW_DIR;

            // 转换逻辑包
            PT_TROOP_GROUP_C2S_YAW_DIR_DATA* sendData = (PT_TROOP_GROUP_C2S_YAW_DIR_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                sendData->troopGroupId = troopGroupId;
                /*sendData->dir.x = dir.x;
                sendData->dir.z = dir.z;*/
				sendData->dir = ((NetVec2)dir).getData();

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket(frontServerNetId, dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_TROOP_GROUP_C2S_YAW_DIR_DATA_INFO::dataSize );
            }
        }

			
    }

	//-----------------------------------------------------------------------
	void TroopNetPacketProcesser::sendTroopEntityStopMoveToPackBuffer(CClient* client, REGION_OBJ_TYPE regionType,  RegionIdType regionId, InstanceUIdType instanceUid, IdType troopId )
	{
		PT_TROOP_C2S_STOP_MOVE_DATA sendData;

		// 填充逻辑包
		sendData.regionType = regionType;
		sendData.regionID = regionId;
		sendData.instanceUid = instanceUid;

		client->getPackManager()->addPacketToBuff(PT_TROOP_STOP_MOVE, GOT_TROOP, (Char8*)&sendData , troopId );
	}

	void TroopNetPacketProcesser::sendTroopGroupStopMove(I32 frontServerNetId,IdType troopGroupId)
	{
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_TROOP;
            packet->type    = PT_TROOP_C2S_STOP_MOVE;

            // 转换逻辑包
            PT_TROOP_C2S_STOP_MOVE_DATA* sendData = (PT_TROOP_C2S_STOP_MOVE_DATA*)(packet->data);
            if ( sendData )
            {
				// 填充逻辑包
				sendData->troopId = troopGroupId;

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket( frontServerNetId,dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_TROOP_C2S_STOP_MOVE_DATA_INFO::dataSize );
            }
        }

			
    }

	//-----------------------------------------------------------------------
	void TroopNetPacketProcesser::sendTroopMoveToObject(I32 frontServerNetId,IdType troopGroupId, Int troopIndex, IdType targetId, Int targetIndex, GAMEOBJ_TYPE targetType, Flt radius, Bool isCommand)
	{
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_TROOP;
            packet->type    = PT_TROOP_C2S_MOVE_OBJECT;

            // 转换逻辑包
            PT_TROOP_C2S_MOVE_OBJECT_DATA* sendData = (PT_TROOP_C2S_MOVE_OBJECT_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                sendData->troopGroupId = troopGroupId;
                sendData->troopIndex = troopIndex;
                sendData->objectId = targetId;
                sendData->objectIndex = targetIndex;
                sendData->objectType = targetType;
                sendData->radius = radius;
                sendData->isCommand = isCommand;

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket( frontServerNetId,dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_TROOP_C2S_MOVE_OBJECT_DATA_INFO::dataSize );
            }
        }

	}
	
	//-----------------------------------------------------------------------
	void TroopNetPacketProcesser::sendTroopSoldierMove( I32 frontServerNetId,IdType troopId, Int troopIndex, Vec3 startMovePos, Vec3 endMovePos )
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
				sendData->troopId = troopId;
				sendData->troopIndex = troopIndex;
				sendData->startMovePos = ((NetVec2)startMovePos).getData();
				sendData->endMovePos = ((NetVec2)endMovePos).getData();
				/*sendData->startMovePos.x = startMovePos.x;
				sendData->startMovePos.z = startMovePos.z;*/
				/*sendData->endMovePos.x = endMovePos.x;
				sendData->endMovePos.z = endMovePos.z;*/
				
				// 发送数据
				ClientNetApplyManager::getInstance().sendFrontServerPacket( frontServerNetId,dataPtr , 
					GameNetPacketData_INFO::headSize + PT_TROOP_SOLDIER_C2S_MOVE_POS_DATA_INFO::dataSize );
			}
		}
	}

	//-----------------------------------------------------------------------
	void TroopNetPacketProcesser::sendTroopSoldierMoveToPackBuffer(CClient* client, REGION_OBJ_TYPE regionType,  RegionIdType regionId, InstanceUIdType instanceUid, IdType troopId, Int troopIndex, Vec3 startMovePos, Vec3 endMovePos )
	{
		PT_TROOP_SOLDIER_C2S_MOVE_POS_DATA sendData;

		// 填充逻辑包
		sendData.regionType = regionType;
		sendData.regionID = regionId;
		sendData.instanceUid = instanceUid;
		sendData.troopId = troopId;
		sendData.troopIndex = troopIndex;
		sendData.startMovePos = ((NetVec2)startMovePos).getData();
		sendData.startMovePos = ((NetVec2)endMovePos).getData();

		client->getPackManager()->addPacketToBuff( PT_TROOP_SOLDIER_MOVE, GOT_SOLDIER, (Char8*)&sendData , troopId, troopIndex );
	}

	//-----------------------------------------------------------------------
	void TroopNetPacketProcesser::sendTroopSoldierStopMoveToPackBuffer(CClient* client,REGION_OBJ_TYPE regionType,  RegionIdType regionId, InstanceUIdType instanceUid, IdType troopId, Int troopIndex )
	{
		PT_TROOP_SOLDIER_C2S_STOP_MOVE_DATA sendData;

		// 填充逻辑包
		sendData.regionType = regionType;
		sendData.regionID = regionId;
		sendData.instanceUid = instanceUid;
		sendData.troopId = troopId;
		sendData.troopIndex = troopIndex;
		client->getPackManager()->addPacketToBuff( PT_TROOP_SOLDIER_STOP_MOVE, GOT_SOLDIER, (Char8*)&sendData , troopId, troopIndex );
		//NetPacketPackManager::getInstance().addPacketToBuff( PT_TROOP_SOLDIER_STOP_MOVE, GOT_SOLDIER, (Char8*)&sendData , troopId, troopIndex );
	}
}