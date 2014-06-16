/******************************************************************************/
#include "stdafx.h"
#include "NetTranspondPacketProcesser.h"
//#include "SWorldManager.h"
#include "GameNetPacket.h"
#include "NetTranspondNetPacket.h"
#include "ServerManager.h"
#include "FrontServerMain.h"
#include "SWorldManager.h"
#include "PlayerCharacterNetPacketProcesser.h"
#include "PackNetPacket.h"
/******************************************************************************/

namespace MG
{
    //--------------------------------------------------------------------------
    NetTranspondPacketProcesser::NetTranspondPacketProcesser()
    {

    }

    //--------------------------------------------------------------------------
    NetTranspondPacketProcesser::~NetTranspondPacketProcesser()
    {

    }

    //--------------------------------------------------------------------------
    Bool NetTranspondPacketProcesser::processClientPacket(I32 id, NetEventRecv* packet)
    {

        return false;
    }

    //--------------------------------------------------------------------------
    Bool NetTranspondPacketProcesser::processLoginServerPacket(I32 id, NetEventRecv* packet)
    {

        return false;
    }

    //--------------------------------------------------------------------------
    Bool NetTranspondPacketProcesser::isBelongChannel( NetEventRecv* packet )
    {
        if (packet->getChannel() == GNPC_NET_TRANSPOND)
        {
            return true;
        }
        
        return false;
    }

    //--------------------------------------------------------------------------
    Bool NetTranspondPacketProcesser::processMapServerPacket(I32 id, NetEventRecv* packet)
    {
        if (packet->getChannel() == GNPC_NET_TRANSPOND)
        {
			//FUNDETECTION(__MG_FUNC__);
            GameNetPacketData* data = (GameNetPacketData*)(packet->getData());
            switch (data->type)
            {
            case PT_NETTRANPOND_M2F_GROUP_TO_CLIENT:	// MapServer 发过来的消息
                onServerTranspondClient( (PT_NETTRANPOND_CLIENT_GROUP_DATA*)data->data, packet->getDataSize() - GameNetPacketData_INFO::headSize );
                break;
            }
                
            return true;
        }

        return false;
    }
	//--------------------------------------------------------------------------
	MG::Bool NetTranspondPacketProcesser::processChatServerPacket( I32 id, NetEventRecv* packet )
	{
		if (packet->getChannel() == GNPC_NET_TRANSPOND)
		{
			//FUNDETECTION(__MG_FUNC__);
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());
			switch (data->type)
			{
			case PT_NETTRANPOND_A2F_GROUP_TO_CLIENT:	
				onServerTranspondClient( (PT_NETTRANPOND_CLIENT_GROUP_DATA*)data->data, packet->getDataSize() - GameNetPacketData_INFO::headSize );
				break;
			}

			return true;
		}

		return false;
	}

	//--------------------------------------------------------------------------
	Bool NetTranspondPacketProcesser::processCenterServerPacket(I32 id, NetEventRecv* packet)
	{
		if (packet->getChannel() == GNPC_NET_TRANSPOND)
		{
			//FUNDETECTION(__MG_FUNC__);
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());
			switch (data->type)
			{
			case PT_NETTRANPOND_T2F_GROUP_TO_CLIENT:	// CenterServer 发过来的消息
				onServerTranspondClient( (PT_NETTRANPOND_CLIENT_GROUP_DATA*)data->data, packet->getDataSize() - GameNetPacketData_INFO::headSize );
				break;
			case PT_NETTRANPOND_T2F_GROUP_TO_ALL_CLIENT:
				onServerTranspondBroadToClient( (PT_NETTRANPOND_CLIENT_GROUP_DATA*)data->data, packet->getDataSize() - GameNetPacketData_INFO::headSize );
				break;
			}

			return true;
		}

		return false;
	}

    //--------------------------------------------------------------------------
    void NetTranspondPacketProcesser::sendClientTranspondDataToMapServer( U64 mapID, 
		I32 client_net_id, U64 account_id, 
		GameNetPacketData* data, Int dataSize, I32 mapNetId  )
    {
        //FUNDETECTION(__MG_FUNC__);

		if ( mapNetId == -1 )
			return;

        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
			memcpy( packet, data, dataSize);

			FrontServerMain::getInstance().getServerLauncher()->sendServer(dataPtr,dataSize, mapNetId);
        }
    }
    
    //--------------------------------------------------------------------------
    void NetTranspondPacketProcesser::broadcastClientTranspondDataToMapServer( I32 client_net_id, U64 account_id, GameNetPacketData* data, Int dataSize )
    {
		//FUNDETECTION(__MG_FUNC__);
        ///////////////////////////////////////////////////////////////////////////

        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_NET_TRANSPOND;
            packet->type    = PT_NETTRANPOND_F2S_FROM_CLIENT;

            // 转换逻辑包
            PT_NETTRANPOND_CLIENT_DATA* sendData = (PT_NETTRANPOND_CLIENT_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                sendData->client_net_id = client_net_id;
                sendData->account_id    = account_id;
                sendData->data.channel	= data->channel;
                sendData->data.type		= data->type;
                memcpy( sendData->data.data,data->data, dataSize - GameNetPacketData_INFO::headSize );

                // 发送数据
                ServerManager::getInstance().boardcastNetPacketToAcitveMapServer(dataPtr, 
                    GameNetPacketData_INFO::headSize + PT_NETTRANPOND_CLIENT_DATA_INFO::headSize + dataSize);
            }
        }
    }

    //--------------------------------------------------------------------------
    void NetTranspondPacketProcesser::onServerTranspondClient( PT_NETTRANPOND_CLIENT_GROUP_DATA* data, I32 dataSize )
    {
		sendServerTranspondToClient( data, dataSize );
    }

    //--------------------------------------------------------------------------
    void NetTranspondPacketProcesser::sendServerTranspondToClient( PT_NETTRANPOND_CLIENT_GROUP_DATA* data, I32 dataSize )
    {
		UInt maxClientNetInfoCount = 3000; 

		if ( data->clientNetInfoCount <= 0 )
			return;

		if ( data->clientNetInfoCount > maxClientNetInfoCount )
		{
			DYNAMIC_EEXCEPT_LOG( "NetTranspondPacketProcesser::sendServerTranspondToClient : client too much 3000?" );
			return;
		}
	
        // 获得一个发送【客户端】缓存
        GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr, data->dataSize );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 需要发送给客户端的数据包大小 // GameNetPacketData总大小
            Int sendDataSize = data->dataSize;

            // 复制发送数据
            packet->channel = data->data.channel;
            packet->type    = data->data.type;
            memcpy( packet->data, data->data.data, sendDataSize-GameNetPacketData_INFO::headSize );

            // 遍历转发客户端列表
            {
                // 客户端信息数组指针
                Char8* clientArrayHead      = (Char8*)data + PT_NETTRANPOND_CLIENT_GROUP_DATA_INFO::headSize + sendDataSize;
                // 转换指针
                ClientNetInfo* clientInfo   = (ClientNetInfo*)(clientArrayHead);

                // 开始遍历
				for( UInt i=0; i< data->clientNetInfoCount; i++ )
				{
					FrontServerMain::getInstance().getServerLauncher()->sendClient(
						dataPtr,
						sendDataSize, 
						clientInfo->client_net_id);

					clientInfo++;
				}
            }
        }
    }

	//--------------------------------------------------------------------------
	void NetTranspondPacketProcesser::onServerTranspondBroadToClient( PT_NETTRANPOND_CLIENT_GROUP_DATA* data, I32 dataSize )
	{
		// 获得一个发送【客户端】缓存
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr, data->dataSize );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 需要发送给客户端的数据包大小 // GameNetPacketData总大小
			Int sendDataSize = data->dataSize;

			// 复制发送数据
			packet->channel = data->data.channel;
			packet->type    = data->data.type;
			memcpy( packet->data, data->data.data, sendDataSize - GameNetPacketData_INFO::headSize );

			// 遍历转发客户端列表
			{
				if ( data->clientNetInfoCount > 0 )
				{
					// 客户端信息数组指针
					Char8* clientArrayHead      = (Char8*)data + PT_NETTRANPOND_CLIENT_GROUP_DATA_INFO::headSize + sendDataSize;
					// 转换指针
					ClientNetInfo* clientInfo   = (ClientNetInfo*)(clientArrayHead);
					
					// 遍历playerList
					SPlayerPtr player;
					I32 currPlayerIndex = 0;
					NetIdType clientId = -1;
					Bool isContinue = true;
					while(isContinue)
					{
						//isContinue = SWorldManager::getInstance().getGameObjectManager()->traversalPlayerList(currPlayerIndex,clientId,player);
						if (!isContinue)
						{
							break;
						}

						FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,sendDataSize, clientId);
					}
				}
			}
		}
	}


}