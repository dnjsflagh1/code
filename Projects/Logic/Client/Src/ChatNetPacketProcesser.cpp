#include "stdafx.h"
#include "ChatNetPacketProcesser.h"
#include "ClientNetApplyManager.h"
#include "MessageManager.h"
#include "MessageData.h"

namespace MG
{


	Bool ChatNetPacketProcesser::processFrontServerPacket( I32 id,NetEventRecv* packet )
	{
		if ( packet->getChannel() == GNPC_CHAT )
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_CHAT_A2C_TWO_PERSON:
				onRecvTwoPersonChatContentFromChatServer(id,(PT_CHAT_A2C_TWO_PERSON_DATA*)data->data);
				break;
			case PT_CHAT_F2C_RESULT:
				onRecvChatResultFromFrontServer(id,(PT_CHAT_F2C_RESULT_DATA*)data->data);
				break;
			case PT_CHAT_M2C_ONE_REGION:
				onRecvOneRegionContentFromMapServer(id,(PT_CHAT_M2C_ONE_REGION_DATA*)data->data);
				break;
			case PT_CHAT_A2C_FULL_SERVER:
				onRecvFullServerChatContentFromChatServer(id,(PT_CHAT_A2C_FULL_SERVER_DATA*)data->data);
				break;
			}
			return true;
		}
		return false;
	}

	Bool ChatNetPacketProcesser::processMapServerPacket( I32 id,NetEventRecv* packet )
	{
		GameNetPacketData* data = (GameNetPacketData*)(packet->getData());
		if ( packet->getChannel() == GNPC_CHAT )
		{
			switch (data->type)
			{
			case PT_CHAT_M2C_ONE_REGION:
				onRecvOneRegionContentFromMapServer(id,(PT_CHAT_M2C_ONE_REGION_DATA*)data->data);
				break;
			case PT_CHAT_F2C_RESULT:
				break;
			}
			return true;
		}
	
		return false;
	}

	ChatNetPacketProcesser::ChatNetPacketProcesser()
	{

	}

	ChatNetPacketProcesser::~ChatNetPacketProcesser()
	{

	}

	void ChatNetPacketProcesser::onRecvTwoPersonChatContentFromChatServer( I32 id,PT_CHAT_A2C_TWO_PERSON_DATA* data )
	{
		if (!(MessageManager::getInstance().getRecChatDataListSize() >= MAX_CHAT_CONTENT_ROW_COUNT))
		{
			MessageManager::getInstance().addChatMsg(data->channel,data->senderClanName,(Char16*)data->data,(data->dataSize / sizeof(Char16))-1);
		}
		
		//copy date save to list
		RecChatData* recdata   = (RecChatData*)RamAlloc::getInstance().get(PT_CHAT_A2C_TWO_PERSON_DATA_INFO::dataSize(data),true);
		recdata->channelid = data->channel;
		memcpy(recdata->dataSender,data->senderClanName,MAX_CLAN_NAME*sizeof(data->senderClanName[0]));
		memcpy(recdata->data,data->data,data->dataSize);
        recdata->dataSize = data->dataSize;
		MessageManager::getInstance().addRecChatDateToList(recdata);

		
	}

	void ChatNetPacketProcesser::sendTwoPersonChatToFrontServer( U32 channelId,CChar16* senderClanName,CChar16* recvClanName, Char8* chatData,I32 size )
	{
		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_CHAT;
			packet->type    = PT_CHAT_C2F_TWO_PERSON;

			// 转换逻辑包
			PT_CHAT_C2F_TWO_PERSON_DATA* sendData = (PT_CHAT_C2F_TWO_PERSON_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->channel = channelId;
				sendData->dataSize = size;
				memcpy(sendData->senderClanName,senderClanName,MAX_CLAN_NAME * sizeof(senderClanName[0]));
				memcpy(sendData->recverClanName,recvClanName,MAX_CLAN_NAME * sizeof(recvClanName[0]));
				memcpy(sendData->data,chatData,size);
				// 发送数据
				ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
					GameNetPacketData_INFO::headSize + PT_CHAT_C2F_TWO_PERSON_DATA_INFO::dataSize(sendData));
			}
		}
	}

	void ChatNetPacketProcesser::onRecvChatResultFromFrontServer( I32 id, PT_CHAT_F2C_RESULT_DATA* data )
	{
		Byte result=data->result;
		switch(result)
		{
		case 0:
           //  UIChatCommonShow::getInstance().addChatMsg(data->channel,clanName.c_str(),msg,msg.length());
			 break;
		case 1:
             break;
		case 2:
			break;             //no gold
		case 3:
			break;            // no props
		case 4:
			break;           //props is not enough
		case 5:
			break;          //no permission
		case 6:
			break;          //level limit 

		}
    
	}

	void ChatNetPacketProcesser::sendOneRegionChatToFrontServer( U32 channelId,CChar16* senderClanName,RegionIdType regionId,REGION_OBJ_TYPE regionType,Char8* chatData,I32 size )
	{
		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_CHAT;
			packet->type    = PT_CHAT_C2F_ONE_REGION;

			// 转换逻辑包
			PT_CHAT_C2F_ONE_REGION_DATA* sendData = (PT_CHAT_C2F_ONE_REGION_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->channel = channelId;
				sendData->dataSize = size;
				sendData->regionId = regionId;
				sendData->regionType = regionType;
				memcpy(sendData->senderClanName,senderClanName,MAX_CLAN_NAME * sizeof(senderClanName[0]));
				memcpy(sendData->data,chatData,size);
				// 发送数据
				ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
					GameNetPacketData_INFO::headSize + PT_CHAT_C2F_ONE_REGION_DATA_INFO::dataSize(sendData));
			}
		}
	}

	void ChatNetPacketProcesser::onRecvOneRegionContentFromMapServer( I32 id, PT_CHAT_M2C_ONE_REGION_DATA* data )
	{
		if (!(MessageManager::getInstance().getRecChatDataListSize() >= MAX_CHAT_CONTENT_ROW_COUNT))
		{
			MessageManager::getInstance().addChatMsg(data->channel,data->senderClanName,(Char16*)data->data,(data->dataSize / sizeof(Char16))-1);
		}

		//copy date save to list
		RecChatData* recdata   = (RecChatData*)RamAlloc::getInstance().get(PT_CHAT_M2C_ONE_REGION_DATA_INFO::dataSize(data),true);
		recdata->channelid = data->channel;
		memcpy(recdata->dataSender,data->senderClanName,MAX_CLAN_NAME*sizeof(data->senderClanName[0]));
		memcpy(recdata->data,data->data,data->dataSize);
		recdata->dataSize = data->dataSize;
		MessageManager::getInstance().addRecChatDateToList(recdata);
	}

	void ChatNetPacketProcesser::sendFullServerChatToFrontServer( U32 channelID,CChar16* senderClanName,Char8* chatData,I32 size )
	{
		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_CHAT;
			packet->type    = PT_CHAT_C2F_FULL_SERVER;

			// 转换逻辑包
			PT_CHAT_C2F_FULL_SERVER_DATA* sendData = (PT_CHAT_C2F_FULL_SERVER_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->channel = channelID;
				sendData->dataSize = size;
				memcpy(sendData->senderClanName,senderClanName,MAX_CLAN_NAME * sizeof(senderClanName[0]));
				memcpy(sendData->data,chatData,size);
				// 发送数据
				ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
					GameNetPacketData_INFO::headSize + PT_CHAT_C2F_FULL_SERVER_DATA_INFO::dataSize(sendData));
			}
		}

	}

	void ChatNetPacketProcesser::onRecvFullServerChatContentFromChatServer( I32 id, PT_CHAT_A2C_FULL_SERVER_DATA* data )
	{
		if (!(MessageManager::getInstance().getRecChatDataListSize() >= MAX_CHAT_CONTENT_ROW_COUNT))
		{
			MessageManager::getInstance().addChatMsg(data->channel,data->senderClanName,(Char16*)data->data,(data->dataSize / sizeof(Char16))-1);
		}

		//copy date save to list
		RecChatData* recdata   = (RecChatData*)RamAlloc::getInstance().get(PT_CHAT_A2C_FULL_SERVER_DATA_INFO::dataSize(data),true);
		recdata->channelid = data->channel;
		memcpy(recdata->dataSender,data->senderClanName,MAX_CLAN_NAME*sizeof(data->senderClanName[0]));
		memcpy(recdata->data,data->data,data->dataSize);
		recdata->dataSize = data->dataSize;
		MessageManager::getInstance().addRecChatDateToList(recdata);
	}

}