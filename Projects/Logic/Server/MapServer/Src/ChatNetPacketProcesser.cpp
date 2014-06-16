#include "stdafx.h"
#include "ChatNetPacketProcesser.h"
#include "NetTranspondPacketProcesser.h"
#include "SWorldManager.h"
#include "SPlayerManager.h"

namespace MG
{


	ChatNetPacketProcesser::ChatNetPacketProcesser()
	{

	}

	ChatNetPacketProcesser::~ChatNetPacketProcesser()
	{

	}

	Bool ChatNetPacketProcesser::processFrontServerPacket( I32 id, NetEventRecv* packet )
	{
        //此处压力测试会出错
        //故暂时屏蔽    
        return false;

		if ( packet->getChannel() == GNPC_CHAT )
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());
			{

			}
			return true;
		}
		return false;
	}

	void ChatNetPacketProcesser::onRecvRegionChatFromChatServer( I32 id, PT_CHAT_A2M_ONE_REGION_DATA* data )
	{
		//过滤和地图有关的条件
		Bool success = true;
		SPlayerPtr player;
		if (false == SPlayerManager::getInstance().getPlayer(player, data->accountId))
		{
			return;
		}

		DYNAMIC_ASSERT(false == player.isNull());
		if ( player.isNull() )
			return;

		SRegionObjectBase* regionObj = NULL;//player->getCurrentRegionObj();
		if (!regionObj)
		{
			// mapServer找不到地图
			success = false;
		}

		if (success)
		{
			brocastOneRegionChatToClient(data->channel,data->senderClanName,data->data,data->dataSize,regionObj);
		}
		else
		{
			//send....err
		}


	}

	void ChatNetPacketProcesser::brocastOneRegionChatToClient( Byte channel,Char16* senderClanName,Char8* data,U16 dataSize,SRegionObjectBase* regionObj )
	{
		NetTranspondSendDataBufferPtr dataPtr ;
        NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if ( packet )
		{
			packet->channel = GNPC_CHAT;
			packet->type    = PT_CHAT_M2C_ONE_REGION;
			PT_CHAT_M2C_ONE_REGION_DATA* sendData = (PT_CHAT_M2C_ONE_REGION_DATA*)(packet->data);
			if(sendData)
			{
				sendData->channel = channel;
				sendData->dataSize = dataSize;
				memcpy(sendData->senderClanName,senderClanName,MAX_CLAN_NAME * sizeof(senderClanName[0]));
				memcpy(sendData->data,data,dataSize);
				NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(dataPtr,
					GameNetPacketData_INFO::headSize + PT_CHAT_M2C_ONE_REGION_DATA_INFO::dataSize(sendData),
					regionObj);
			}
		}
	}

	Bool ChatNetPacketProcesser::processChatServerPacket( I32 id, NetEventRecv* packet )
	{
		if ( packet->getChannel() == GNPC_CHAT )
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_CHAT_A2M_ONE_REGION:
				onRecvRegionChatFromChatServer(id,(PT_CHAT_A2M_ONE_REGION_DATA*)data->data);
				break;
			}

			return true;
		}
		return false;
	}
}