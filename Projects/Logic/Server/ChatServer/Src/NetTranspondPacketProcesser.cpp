/******************************************************************************/
#include "stdafx.h"
#include "GameNetPacket.h"
#include "NetTranspondNetPacket.h"
#include "ServerManager.h"
#include "ClientManager.h"
#include "ChatServerMain.h"
#include "NetTranspondPacketProcesser.h"
/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    // NetTranspondSendDataBufferPtr
    /******************************************************************************/

    NetTranspondSendDataBufferPtr::NetTranspondSendDataBufferPtr()
        :mUsedHeadSize(0)
        ,mEstimateTailSize(0)
    {

    }

    //--------------------------------------------------------------------------
    NetTranspondSendDataBufferPtr::NetTranspondSendDataBufferPtr(GameNetSendDataBufferPtr& dataPtr, Int usedHeadSize, Int estimateTailSize)
        :mDataPtr(dataPtr)
        ,mUsedHeadSize(usedHeadSize)
        ,mEstimateTailSize(estimateTailSize)
    {
    }

    //--------------------------------------------------------------------------
    Char8* NetTranspondSendDataBufferPtr::getTranspondData()
    {
        return mDataPtr->getLogicData() + mUsedHeadSize;
    }

    //--------------------------------------------------------------------------
    U32 NetTranspondSendDataBufferPtr::getTranspondDataMaxSize( UInt maxClientCount )
    {
        UInt transpondDefineNeedSize    = mUsedHeadSize + maxClientCount*mEstimateTailSize;
        UInt sysLogicSize               = mDataPtr->getLogicDataMaxSize();
        Int transponddataMaxSize        = sysLogicSize - transpondDefineNeedSize;

        if ( transponddataMaxSize <= 0 )
        {
            DYNAMIC_EEXCEPT_LOG("too much client!");
            DYNAMIC_ASSERT(false);
            return 0;
        }

        return transponddataMaxSize;
    }


    /******************************************************************************/
    // NetTranspondPacketProcesser
    /******************************************************************************/
    NetTranspondPacketProcesser::NetTranspondPacketProcesser()
    {

    }

    //--------------------------------------------------------------------------
    NetTranspondPacketProcesser::~NetTranspondPacketProcesser()
    {

    }
    //--------------------------------------------------------------------------
    Bool NetTranspondPacketProcesser::processMapServerPacket(I32 id, NetEventRecv* packet)
    {
        if (packet->getChannel() == GNPC_NET_TRANSPOND)
        {
            GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

            switch (data->type)
            {
            case PT_NETTRANPOND_F2S_FROM_CLIENT:
                break;
            }

            return true;
        }

        return false;
    }

    //--------------------------------------------------------------------------
    void NetTranspondPacketProcesser::getClientTranspondSendDataBuffer( NetTranspondSendDataBufferPtr& ptr, U32 buffSize )
    {
        // 获得一个发送【服务端】缓存
        ChatServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( ptr.mDataPtr, buffSize );
        ptr.mUsedHeadSize       = GameNetPacketData_INFO::headSize + PT_NETTRANPOND_CLIENT_GROUP_DATA_INFO::headSize;
        ptr.mEstimateTailSize   =  PT_NETTRANPOND_CLIENT_GROUP_DATA_INFO::clientNetInfoSize;
    }

    //--------------------------------------------------------------------------
    void NetTranspondPacketProcesser::sendClientTranspondSendDataToFrontServer( NetTranspondSendDataBufferPtr& dataPtr, Int dataSize,
        I32 frontSvrNetID,I32 clientNetIdInFrontServer, U64 accountId)
    {
        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr.mDataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_NET_TRANSPOND;
            packet->type    = PT_NETTRANPOND_A2F_GROUP_TO_CLIENT;

            // 转换转发包结构
            PT_NETTRANPOND_CLIENT_GROUP_DATA* clientGroupData = ( PT_NETTRANPOND_CLIENT_GROUP_DATA* )packet->data;
            if ( clientGroupData )
            {
                // 填充转发包数据
                clientGroupData->clientNetInfoCount = 1;
                clientGroupData->dataSize = dataSize;

                // 转换客户端数据
                ClientNetInfo* clientData = (ClientNetInfo*)( dataPtr.getTranspondData() + dataSize );
                if ( clientData )
                {
                    // 填充客户端数据
                    clientData->account_id      = accountId;
                    clientData->client_net_id   = clientNetIdInFrontServer;
                }

                // 发送数据
				ChatServerMain::getInstance().getServerLauncher()->sendServer(dataPtr.mDataPtr,
					GameNetPacketData_INFO::headSize + PT_NETTRANPOND_CLIENT_GROUP_DATA_INFO::dataSize(clientGroupData),frontSvrNetID);
            }
        }
    }

	//------------------------------------------------------------------------------------
	void NetTranspondPacketProcesser::broadcastClientTranspondDataToFrontServer( NetTranspondSendDataBufferPtr& dataPtr, Int dataSize )
	{
		//转换标准包格式
		GameNetPacketData* packet = (GameNetPacketData*)dataPtr.mDataPtr->getLogicData();
		if (!packet)
			return;

		//设置标签
		packet->channel = GNPC_NET_TRANSPOND;
		packet->type    = PT_NETTRANPOND_A2F_GROUP_TO_CLIENT;

		// 转换转发包结构
		PT_NETTRANPOND_CLIENT_GROUP_DATA* clientGroupData = ( PT_NETTRANPOND_CLIENT_GROUP_DATA* )packet->data;
		if (!clientGroupData)
			return;
		
		//填充逻辑数据大小
		clientGroupData->clientNetInfoCount = 0;
		clientGroupData->dataSize = dataSize;

		// 得到发送数据头大小
		I32 sendDataHeadSize                = GameNetPacketData_INFO::headSize + PT_NETTRANPOND_CLIENT_GROUP_DATA_INFO::headSize + dataSize;

		ClientNetInfo* clientNetInfoArray   = (ClientNetInfo*)( dataPtr.getTranspondData() + dataSize );
		ClientNetInfo* clientNetInfo        = NULL;

        //------------------------------------------------------------------------------------

		// 获得FrontServer网络编号
		Int frontServerID					= 0;
		// 当前发送数据大小
		I32 sendDataSize					= sendDataHeadSize;
		// 准备发送数据大小
		I32 prepareSendDataSize				= sendDataHeadSize;

        //------------------------------------------------------------------------------------

		//遍历全服玩家
		ClientHashMap& tempClientHashMap = ClientManager::getInstance().getClients();
		if (tempClientHashMap.element.empty())
		{
			return;
		}
		stdext::hash_map< Str16,ClientObject* >::iterator front = tempClientHashMap.element.begin();
		stdext::hash_map< Str16,ClientObject* >::iterator back  = tempClientHashMap.element.end();
		for ( ;front != back; front++ )
		{
			ClientObject* tempClientObject = front->second;

			// 获得FrontServer网络编号
			frontServerID       = tempClientObject->frontServerNetId;

			//------------------------------------------------------------------------------------

			if ( dataPtr.mDataPtr.isNull() == false )
			{
				// 递增一个玩家数据大小到发送数据缓存大小
				prepareSendDataSize = sendDataSize + PT_NETTRANPOND_CLIENT_GROUP_DATA_INFO::clientNetInfoSize;

				// 如果大于缓存最大大小则发送
				if ( prepareSendDataSize >= dataPtr.mDataPtr->getLogicDataMaxSize() )
				{   
					// 发送数据
					ChatServerMain::getInstance().getServerLauncher()->sendServer(
                        dataPtr.mDataPtr,
						sendDataSize,frontServerID);

                    //------------------------------------------------------------------------------------

                    //Clone
                    {
                        ChatServerMain::getInstance().getServerLauncher()->cloneSendDataBuffer( dataPtr.mDataPtr, dataPtr.mDataPtr , UInt(sendDataHeadSize) );

                        packet = (GameNetPacketData*)dataPtr.mDataPtr->getLogicData();
                        if (!packet)  return;
                        //设置标签
                        packet->channel = GNPC_NET_TRANSPOND;
                        packet->type    = PT_NETTRANPOND_A2F_GROUP_TO_CLIENT;

                        clientGroupData = ( PT_NETTRANPOND_CLIENT_GROUP_DATA* )packet->data;
                        if (!clientGroupData)  return;
                        //填充逻辑数据大小
                        clientGroupData->clientNetInfoCount = 0;
                        clientGroupData->dataSize = dataSize;

                        clientNetInfoArray   = (ClientNetInfo*)( dataPtr.getTranspondData() + dataSize );
                        clientNetInfo        = NULL;

                        sendDataSize		= sendDataHeadSize;
                    }
				}
			}

			//------------------------------------------------------------------------------------

			// 增加玩家记录
			clientNetInfo = clientNetInfoArray + clientGroupData->clientNetInfoCount;
			clientNetInfo->account_id       = tempClientObject->accountId;
			clientNetInfo->client_net_id    = tempClientObject->netIdInFrontServer;

			// 递增参数
			sendDataSize += PT_NETTRANPOND_CLIENT_GROUP_DATA_INFO::clientNetInfoSize;
			++clientGroupData->clientNetInfoCount;
		}
			
		//------------------------------------------------------------------------------------
		// 如果有剩余则发送
		if ( dataPtr.mDataPtr.isNull() == false )
		{  
            if ( clientGroupData->clientNetInfoCount > 0 )
            {
                // 发送数据
                ChatServerMain::getInstance().getServerLauncher()->sendServer(
                    dataPtr.mDataPtr,
                    sendDataSize,
                    frontServerID);
            }
		}
	}

	
}