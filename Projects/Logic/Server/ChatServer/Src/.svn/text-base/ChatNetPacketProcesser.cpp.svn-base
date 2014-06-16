/******************************************************************************/
#include "stdafx.h"
#include "ChatNetPacketProcesser.h"
#include "ClientManager.h"
#include "ChatServerMain.h"
#include "NetTranspondPacketProcesser.h"
#include "ChatServerMain.h"
#include "ServerDllInterface.h"
/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	ChatNetPacketProcesser::ChatNetPacketProcesser()
	{

	}

	//--------------------------------------------------------------------------
	ChatNetPacketProcesser::~ChatNetPacketProcesser()
	{

	}

	//--------------------------------------------------------------------------
	Bool ChatNetPacketProcesser::processFrontPacket( I32 id, NetEventRecv* packet )
	{
		if(packet->getChannel() == GNPC_CHAT)
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_CHAT_F2A_TWO_PERSON:
				onRecvTwoPersonChatFromFrontServer(id, (PT_CHAT_F2A_TWO_PERSON_DATA*)(data->data));
				break;
			case PT_CHAT_F2A_ONE_REGION:
				onRecvOneRegionChatFromFrontServer(id,(PT_CHAT_F2A_ONE_REGION_DATA*)(data->data));
				break;
			case PT_CHAT_F2A_FULL_SERVER:
                onRecvFullServerChatFromFrontServer(id,(PT_CHAT_F2A_FULL_SERVER_DATA*)(data->data));
				break;
			}
			return true;
		}
		return false;

	}

	//--------------------------------------------------------------------------
	void ChatNetPacketProcesser::onRecvTwoPersonChatFromFrontServer( I32 id, PT_CHAT_F2A_TWO_PERSON_DATA* data )
	{
		// 过滤与玩家属性无关内容,如屏蔽字等
		Bool success = true;
		ClientObject* recver = ClientManager::getInstance().getClientObject(data->recverClanName);
		if (!recver)
		{
			success = false;
		}
		if (success)
		{	
			sendTwoPersonChatContentToClient(data->channel,data->senderClanName,data->data,data->dataSize,recver);
			
			sendChatResultToFrontServer(id,data->channel,data->senderNetIdInFront,chat_result_success);
		}
		else
		{
			//好友不在线
			sendChatResultToFrontServer(id,data->channel,data->senderNetIdInFront,chat_result_friend_absence);
		}
	}

	//--------------------------------------------------------------------------
	void ChatNetPacketProcesser::sendChatResultToFrontServer( I32 id, Byte channel,I32 senderNetIdInFrontServer,Byte result )
	{
		///////////////////////////////////////////////////////////////////////////

		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr;
        ChatServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_CHAT;
			packet->type    = PT_CHAT_A2F_RESULT;

			// 转换逻辑包
			PT_CHAT_A2F_RESULT_DATA* sendData = (PT_CHAT_A2F_RESULT_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->channel = channel;
				sendData->senderNetIdInFront = senderNetIdInFrontServer;
				sendData->result = result;

				// 发送数据
				ChatServerMain::getInstance().getServerLauncher()->sendServer(dataPtr
					,GameNetPacketData_INFO::headSize + PT_CHAT_A2F_RESULT_DATA_INFO::dataSize, id);
			}
		}
	}

	//--------------------------------------------------------------------------
	void ChatNetPacketProcesser::sendTwoPersonChatContentToClient(Byte channel,Char16* senderClanName,Char8* data,U16 dataSize,ClientObject* recvClientObj)
	{
		if (!recvClientObj)
		{
			return;
		}
		NetTranspondSendDataBufferPtr dataPtr;
        NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr );

		GameNetPacketData* packet = (GameNetPacketData*) dataPtr.getTranspondData();
		if ( packet )
		{
			packet->channel = GNPC_CHAT;
			packet->type    = PT_CHAT_A2C_TWO_PERSON;

			PT_CHAT_A2C_TWO_PERSON_DATA* sendData = (PT_CHAT_A2C_TWO_PERSON_DATA*)(packet->data);
			if ( sendData )
			{
				sendData->channel = channel;
				sendData->dataSize = dataSize;
				memcpy(sendData->data,data,dataSize);
				memcpy(sendData->senderClanName,senderClanName,MAX_CLAN_NAME * sizeof(senderClanName[0]));

				NetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer( dataPtr, 
					GameNetPacketData_INFO::headSize + PT_CHAT_A2C_TWO_PERSON_DATA_INFO::dataSize(sendData), recvClientObj->frontServerNetId, recvClientObj->netIdInFrontServer,recvClientObj->accountId);
			}
		}
	}

	//--------------------------------------------------------------------------
	void ChatNetPacketProcesser::onRecvOneRegionChatFromFrontServer( I32 id, PT_CHAT_F2A_ONE_REGION_DATA* data )
	{
		// 过滤与玩家属性无关内容,如屏蔽字等
		Bool success = true;

		ClientObject* sender = ClientManager::getInstance().getClientObject(data->senderClanName);
		if (!sender)
		{
			// 找不到发送者
			success = false;
		}
		NetIdType mapServerNetId = ChatServerMain::getInstance().getServerLauncher()->getNetIdByServerId(data->mapServerId);
		if (mapServerNetId <= -1)
		{
			// 找不到地图服务器
			success = false;
		}

		if (success)
		{	
			sendOneRegionChatToMapServer(mapServerNetId,data->channel,data->senderClanName,sender->accountId,data->data,data->dataSize);
		}
		else
		{
			sendChatResultToFrontServer(id,data->channel,data->senderNetIdInFrontServer,chat_result_unknown);
		}
	}

	//--------------------------------------------------------------------------
	void ChatNetPacketProcesser::sendOneRegionChatToMapServer(NetIdType mapServerNetId, Byte channel, Char16* senderClanName,U64 accountId,Char8* data,U16 dataSize )
	{
		///////////////////////////////////////////////////////////////////////////

		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr;
        ChatServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_CHAT;
			packet->type    = PT_CHAT_A2M_ONE_REGION;

			// 转换逻辑包
			PT_CHAT_A2M_ONE_REGION_DATA* sendData = (PT_CHAT_A2M_ONE_REGION_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包

				sendData->channel = channel;
				sendData->accountId = accountId;
				sendData->dataSize = dataSize;
				memcpy(sendData->data,data,dataSize);
				memcpy(sendData->senderClanName,senderClanName,MAX_CLAN_NAME * sizeof(senderClanName[0]));
				
				// 发送数据
				ChatServerMain::getInstance().getServerLauncher()->sendServer( 
					dataPtr, 
					GameNetPacketData_INFO::headSize + PT_CHAT_A2M_ONE_REGION_DATA_INFO::dataSize(sendData), 
					mapServerNetId );
			}
		}
	}
    
    //-------------------------------------------------------------------------------------------
	void ChatNetPacketProcesser::onRecvFullServerChatFromFrontServer( I32 id, PT_CHAT_F2A_FULL_SERVER_DATA* data )
	{
         Bool success = true;
		 if (ClientManager::getInstance().getClients().element.empty())
		 {
             success = false;
		 }
              
		 
		 if (success)
		 {
              sendFullServerChatContentToClient(data->channel,data->senderClanName,data->data,data->dataSize);
		 }
		 else
		 {
             sendChatResultToFrontServer(id,data->channel,data->senderNetIdInFront,chat_result_unknown);
		 }

	}

    //-------------------------------------------------------------------------------------------
	void ChatNetPacketProcesser::sendFullServerChatContentToClient( Byte channel, Char16* senderClanName,Char8* data,U16 dataSize )
	{
         
		NetTranspondSendDataBufferPtr dataPtr;
        NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr );

		GameNetPacketData* packet = (GameNetPacketData*) dataPtr.getTranspondData();
		if ( packet )
		{
			packet->channel = GNPC_CHAT;
			packet->type    = PT_CHAT_A2C_FULL_SERVER;

			PT_CHAT_A2C_FULL_SERVER_DATA* sendData = (PT_CHAT_A2C_FULL_SERVER_DATA*)(packet->data);
			if ( sendData )
			{
				sendData->channel = channel;
				sendData->dataSize = dataSize;
				memcpy(sendData->data,data,dataSize);
				memcpy(sendData->senderClanName,senderClanName,MAX_CLAN_NAME * sizeof(senderClanName[0]));

				NetTranspondPacketProcesser::getInstance().broadcastClientTranspondDataToFrontServer( dataPtr,
                    GameNetPacketData_INFO::headSize + PT_CHAT_A2C_FULL_SERVER_DATA_INFO::dataSize(sendData));
			}
		}
	}
}