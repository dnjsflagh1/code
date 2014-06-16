/******************************************************************************/
#include "stdafx.h"
#include "ChatNetPacket.h"
#include "ChatNetPacketProcesser.h"
#include "ServerManager.h"
#include "FrontServerMain.h"
#include "SWorldManager.h"
#include "ChatInterValCheckManager.h"

/******************************************************************************/


namespace MG
{
	//--------------------------------------------------------------------------

	const static U32 FULL_SERVER_CHAT_INTERVAL = 1500;
	const static U32 ONE_REGION_CHAT_INTERVAL =  1000;
	const static U32 COMMON_CHAT_INTERVAL     =  500;
	//--------------------------------------------------------------------------
	ChatNetPacketProcesser::ChatNetPacketProcesser()
	{

	}
	//--------------------------------------------------------------------------
	ChatNetPacketProcesser::~ChatNetPacketProcesser()
	{

	}
	//--------------------------------------------------------------------------
	Bool ChatNetPacketProcesser::processClientPacket( I32 id, NetEventRecv* packet )
	{
		if(packet->getChannel() == GNPC_CHAT)
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_CHAT_C2F_TWO_PERSON:
				onRecvTwoPersonChatFromClient(id, (PT_CHAT_C2F_TWO_PERSON_DATA*)(data->data));
				return true;
			case PT_CHAT_C2F_ONE_REGION:
				onRecvOneRegionChatFromClient(id, (PT_CHAT_C2F_ONE_REGION_DATA*)(data->data));
				return true;
			case PT_CHAT_C2F_FULL_SERVER:
				onRecvFullServerChatFromClient(id,(PT_CHAT_C2F_FULL_SERVER_DATA*)(data->data));
				return true;
			}
		}
		return false;

	}

	//--------------------------------------------------------------------------
	MG::Bool ChatNetPacketProcesser::processChatServerPacket( I32 id, NetEventRecv* packet )
	{
		if(packet->getChannel() == GNPC_CHAT)
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_CHAT_A2F_RESULT:
				onRecvChatResultFromChatServer(id, (PT_CHAT_A2F_RESULT_DATA*)(data->data));
				return true;
			}
		}
		return false;
	}

	//--------------------------------------------------------------------------
	void ChatNetPacketProcesser::onRecvTwoPersonChatFromClient( I32 id,PT_CHAT_C2F_TWO_PERSON_DATA* data )
	{
		//过滤非法包
		if (isNeedFilterIllegalPacket(FILTER_CHAT_PACKET_TYPE_COMMON,id) == true)
		{
			return;
		}
		//过滤 于家族本身属性相关条件
		Bool success = true;
		if (success)
		{
			sendTwoPersonChatToChatServer(
				data->channel,data->senderClanName,id,data->recverClanName,data->data,data->dataSize);
		}
	}

	//----------------------------------------------------------------------------------------------------
	void ChatNetPacketProcesser::onRecvChatResultFromChatServer( I32 id,PT_CHAT_A2F_RESULT_DATA* data )
	{
		if (data->result == chat_result_success)
		// 修改相关属性
		{

		}
		sendChatResultToClient(data->senderNetIdInFront,data->channel,data->result);
	}

	//----------------------------------------------------------------------------------------------------
	void ChatNetPacketProcesser::sendChatResultToClient( I32 id, Byte channel,Byte chatReslt )
	{
		// 获得一个发送【客户端】缓存
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_CHAT;
			packet->type    = PT_CHAT_F2C_RESULT;

			// 转换逻辑包
			PT_CHAT_F2C_RESULT_DATA* sendData = (PT_CHAT_F2C_RESULT_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->channel = channel;
				sendData->result = chatReslt;

				// 发送数据
				FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					 GameNetPacketData_INFO::headSize + PT_CHAT_F2C_RESULT_DATA_INFO::dataSize,
					 id );
			}
		}
	}

	//----------------------------------------------------------------------------------------------------
	void ChatNetPacketProcesser::sendTwoPersonChatToChatServer(Byte channel,Char16* senderClanName,I32 senderNetId,Char16* recverClanName,Char8* data,U16 dataSize )
	{

        //----------------------------------------------------------------------------------------------------

        I32 id = ServerManager::getInstance().getChatServerNetId();
        if ( id < 0 )
            return;

        //----------------------------------------------------------------------------------------------------


		// 获得一个发送【客户端】缓存
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_CHAT;
			packet->type    = PT_CHAT_F2A_TWO_PERSON;

			// 转换逻辑包
			PT_CHAT_F2A_TWO_PERSON_DATA* sendData = (PT_CHAT_F2A_TWO_PERSON_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->channel = channel;
				memcpy(sendData->senderClanName,senderClanName,MAX_CLAN_NAME * sizeof(senderClanName[0]));
				memcpy(sendData->recverClanName,recverClanName,MAX_CLAN_NAME * sizeof(recverClanName[0]));
				memcpy(sendData->data,data,dataSize);
				sendData->dataSize = dataSize;
				sendData->senderNetIdInFront = senderNetId;

				// 发送数据
				FrontServerMain::getInstance().getServerLauncher()->sendServer(dataPtr,
					GameNetPacketData_INFO::headSize + PT_CHAT_F2A_TWO_PERSON_DATA_INFO::dataSize(sendData), 
					id );
			}
		}
	}

	//----------------------------------------------------------------------------------------------------
	void ChatNetPacketProcesser::onRecvOneRegionChatFromClient( I32 id,PT_CHAT_C2F_ONE_REGION_DATA* data )
	{
        
		//过滤非法包
		if (isNeedFilterIllegalPacket(FILTER_CHAT_PACKET_TYPE_COMMON,id) == true)
		{
			return;
		}

		//过滤 于家族本身属性相关条件
		Bool success = true;
		SRegionObjectBase* region = SWorldManager::getInstance().getRegionObject((REGION_OBJ_TYPE)data->regionType, data->regionId);
		//SRegionObjectBase* region = SWorldManager::getInstance().getRegionObject(ROT_UNKNOWN, data->regionId);
		if (!region)
		{
			DYNAMIC_ASSERT(false);
			success = false;
		}

		NetIdType mapServerNetId = region->getMapServerNetId();
		if( -1 == mapServerNetId)
		{
			//mapServer未开启
			success = false;
		}
		U32 serverId = FrontServerMain::getInstance().getServerLauncher()->getServerIdByNetId(mapServerNetId);
		if (!serverId)
		{
			//serverId未找到
			success = false;
		}
		if (success)
		{
			sendOneRegionChatToChatServer(
				data->channel,data->senderClanName,id,data->regionId,data->regionType,serverId,data->data,data->dataSize);
		}
		else
		{
			sendChatResultToClient(id,data->channel,chat_result_unknown);
		}
	}

	//----------------------------------------------------------------------------------------------------
	void ChatNetPacketProcesser::sendOneRegionChatToChatServer( Byte channel,Char16* senderClanName,I32 senderNetId,U32 regionId,U16 regionType,U32 mapServerId,Char8* data,U16 dataSize )
	{
        I32 id = ServerManager::getInstance().getChatServerNetId();
        if ( id < 0 )
            return;

        //--------------------------------------------------------------------------

		// 获得一个发送【客户端】缓存
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_CHAT;
			packet->type    = PT_CHAT_F2A_ONE_REGION;

			// 转换逻辑包
			PT_CHAT_F2A_ONE_REGION_DATA* sendData = (PT_CHAT_F2A_ONE_REGION_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->channel = channel;
				sendData->regionId = regionId;
				sendData->regionType = regionType;
				sendData->senderNetIdInFrontServer = senderNetId;
				sendData->dataSize = dataSize;
				sendData->mapServerId = mapServerId;
				memcpy(sendData->senderClanName,senderClanName,MAX_CLAN_NAME * sizeof(senderClanName[0]));
				memcpy(sendData->data,data,dataSize);
				// 发送数据
				FrontServerMain::getInstance().getServerLauncher()->sendServer(dataPtr,
					GameNetPacketData_INFO::headSize + PT_CHAT_F2A_ONE_REGION_DATA_INFO::dataSize(sendData),
					id );
			}
		}
	}

	//--------------------------------------------------------------------------
	void ChatNetPacketProcesser::onRecvFullServerChatFromClient( I32 id,PT_CHAT_C2F_FULL_SERVER_DATA* data )
	{
		
		//过滤非法包
        if (isNeedFilterIllegalPacket(FILTER_CHAT_PACKET_TYPE_FULLSERVER,id) == true)
        {
			return;
        }
        Bool sucess = true;
		if(sucess)
		{
			sendFullServerChatToChatServer(
				data->channel,data->senderClanName,id,data->data,data->dataSize);

		}
	}

	//--------------------------------------------------------------------------
	void ChatNetPacketProcesser::sendFullServerChatToChatServer( Byte channel,Char16* senderClanName,I32 senderNetId,Char8* data,U16 dataSize )
	{
        //--------------------------------------------------------------------------

        I32 id = ServerManager::getInstance().getChatServerNetId();
        if ( id < 0 )
            return;

        //--------------------------------------------------------------------------

		// 获得一个发送【客户端】缓存
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_CHAT;
			packet->type    = PT_CHAT_F2A_FULL_SERVER;

			// 转换逻辑包
			PT_CHAT_F2A_FULL_SERVER_DATA* sendData = (PT_CHAT_F2A_FULL_SERVER_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->channel = channel;
				memcpy(sendData->senderClanName,senderClanName,MAX_CLAN_NAME * sizeof(senderClanName[0]));
				memcpy(sendData->data,data,dataSize);
				sendData->dataSize = dataSize;
				sendData->senderNetIdInFront = senderNetId;

				// 发送数据
				FrontServerMain::getInstance().getServerLauncher()->sendServer(dataPtr,
					GameNetPacketData_INFO::headSize + PT_CHAT_F2A_FULL_SERVER_DATA_INFO::dataSize(sendData),
					id );
			}
		}
	}

	//--------------------------------------------------------------------------
	Bool ChatNetPacketProcesser::isNeedFilterIllegalPacket( FilterChatPacketType type,NetIdType netId )
	{
         //过滤时间间隔内的包
		ClientChatTickRecord* clientRecord = NULL;
		switch(type)
		 {
		 case FILTER_CHAT_PACKET_TYPE_COMMON:
			 {
				 
				 clientRecord = ChatIntervalCheckManager::getInstance().getClientChatTickRecordByClientNetID(netId);
				 if (clientRecord == NULL)
				 {
					 return true;
				 }
				 U32 lastCommonChatTick = 0;
				 U32 currentCommonChatTick = 0;
				 lastCommonChatTick = clientRecord->commonChatTick;
					 if (lastCommonChatTick > 0)  //排除第一次
					 {
						 currentCommonChatTick = MG::MGTimeOp::getCurrTick();
						 if((currentCommonChatTick - lastCommonChatTick) <= COMMON_CHAT_INTERVAL )
						 {
							 //过滤掉包
							 clientRecord->setCommonChatTick(currentCommonChatTick);
							 return true;

						 }
						 else
						 {
							 clientRecord->setCommonChatTick(currentCommonChatTick);
							 return false;
						 }

					 }
					 else
					 {
						 currentCommonChatTick = MG::MGTimeOp::getCurrTick();
						 clientRecord->setCommonChatTick(currentCommonChatTick);
						 return false;
					 }
               
			 }
			 break;
		 case FILTER_CHAT_PACKET_TYPE_FULLSERVER:
			 {
				 
				 clientRecord = ChatIntervalCheckManager::getInstance().getClientChatTickRecordByClientNetID(netId);
				 if (clientRecord == NULL)
				 {
					 return true;
				 }
				 U32 lastFullServerChatTick = 0;
				 U32 currentFullServerChatTick = 0;
				 lastFullServerChatTick = clientRecord->fullServerChatTick;
				 if (lastFullServerChatTick > 0)  //排除第一次
				 {
					 currentFullServerChatTick = MG::MGTimeOp::getCurrTick();
					 if((currentFullServerChatTick - lastFullServerChatTick) <= FULL_SERVER_CHAT_INTERVAL )
					 {
						 //过滤掉包
						 clientRecord->setFullServerChatTick(currentFullServerChatTick);
						 return true;

					 }
					 else
					 {
						 clientRecord->setFullServerChatTick(currentFullServerChatTick);
						 return false;
					 }

				 }
				 else
				 {
					 currentFullServerChatTick = MG::MGTimeOp::getCurrTick();
					 clientRecord->setFullServerChatTick(currentFullServerChatTick);
					  return false;
				 }
			 }
			 break;
		 }
	}
}