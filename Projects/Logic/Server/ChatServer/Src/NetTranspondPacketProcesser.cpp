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
        // ���һ�����͡�����ˡ�����
        ChatServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( ptr.mDataPtr, buffSize );
        ptr.mUsedHeadSize       = GameNetPacketData_INFO::headSize + PT_NETTRANPOND_CLIENT_GROUP_DATA_INFO::headSize;
        ptr.mEstimateTailSize   =  PT_NETTRANPOND_CLIENT_GROUP_DATA_INFO::clientNetInfoSize;
    }

    //--------------------------------------------------------------------------
    void NetTranspondPacketProcesser::sendClientTranspondSendDataToFrontServer( NetTranspondSendDataBufferPtr& dataPtr, Int dataSize,
        I32 frontSvrNetID,I32 clientNetIdInFrontServer, U64 accountId)
    {
        // ת���ɱ�׼����ʽ
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr.mDataPtr->getLogicData();
        if ( packet )
        {
            // ���ñ�ǩ
            packet->channel = GNPC_NET_TRANSPOND;
            packet->type    = PT_NETTRANPOND_A2F_GROUP_TO_CLIENT;

            // ת��ת�����ṹ
            PT_NETTRANPOND_CLIENT_GROUP_DATA* clientGroupData = ( PT_NETTRANPOND_CLIENT_GROUP_DATA* )packet->data;
            if ( clientGroupData )
            {
                // ���ת��������
                clientGroupData->clientNetInfoCount = 1;
                clientGroupData->dataSize = dataSize;

                // ת���ͻ�������
                ClientNetInfo* clientData = (ClientNetInfo*)( dataPtr.getTranspondData() + dataSize );
                if ( clientData )
                {
                    // ���ͻ�������
                    clientData->account_id      = accountId;
                    clientData->client_net_id   = clientNetIdInFrontServer;
                }

                // ��������
				ChatServerMain::getInstance().getServerLauncher()->sendServer(dataPtr.mDataPtr,
					GameNetPacketData_INFO::headSize + PT_NETTRANPOND_CLIENT_GROUP_DATA_INFO::dataSize(clientGroupData),frontSvrNetID);
            }
        }
    }

	//------------------------------------------------------------------------------------
	void NetTranspondPacketProcesser::broadcastClientTranspondDataToFrontServer( NetTranspondSendDataBufferPtr& dataPtr, Int dataSize )
	{
		//ת����׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*)dataPtr.mDataPtr->getLogicData();
		if (!packet)
			return;

		//���ñ�ǩ
		packet->channel = GNPC_NET_TRANSPOND;
		packet->type    = PT_NETTRANPOND_A2F_GROUP_TO_CLIENT;

		// ת��ת�����ṹ
		PT_NETTRANPOND_CLIENT_GROUP_DATA* clientGroupData = ( PT_NETTRANPOND_CLIENT_GROUP_DATA* )packet->data;
		if (!clientGroupData)
			return;
		
		//����߼����ݴ�С
		clientGroupData->clientNetInfoCount = 0;
		clientGroupData->dataSize = dataSize;

		// �õ���������ͷ��С
		I32 sendDataHeadSize                = GameNetPacketData_INFO::headSize + PT_NETTRANPOND_CLIENT_GROUP_DATA_INFO::headSize + dataSize;

		ClientNetInfo* clientNetInfoArray   = (ClientNetInfo*)( dataPtr.getTranspondData() + dataSize );
		ClientNetInfo* clientNetInfo        = NULL;

        //------------------------------------------------------------------------------------

		// ���FrontServer������
		Int frontServerID					= 0;
		// ��ǰ�������ݴ�С
		I32 sendDataSize					= sendDataHeadSize;
		// ׼���������ݴ�С
		I32 prepareSendDataSize				= sendDataHeadSize;

        //------------------------------------------------------------------------------------

		//����ȫ�����
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

			// ���FrontServer������
			frontServerID       = tempClientObject->frontServerNetId;

			//------------------------------------------------------------------------------------

			if ( dataPtr.mDataPtr.isNull() == false )
			{
				// ����һ��������ݴ�С���������ݻ����С
				prepareSendDataSize = sendDataSize + PT_NETTRANPOND_CLIENT_GROUP_DATA_INFO::clientNetInfoSize;

				// ������ڻ�������С����
				if ( prepareSendDataSize >= dataPtr.mDataPtr->getLogicDataMaxSize() )
				{   
					// ��������
					ChatServerMain::getInstance().getServerLauncher()->sendServer(
                        dataPtr.mDataPtr,
						sendDataSize,frontServerID);

                    //------------------------------------------------------------------------------------

                    //Clone
                    {
                        ChatServerMain::getInstance().getServerLauncher()->cloneSendDataBuffer( dataPtr.mDataPtr, dataPtr.mDataPtr , UInt(sendDataHeadSize) );

                        packet = (GameNetPacketData*)dataPtr.mDataPtr->getLogicData();
                        if (!packet)  return;
                        //���ñ�ǩ
                        packet->channel = GNPC_NET_TRANSPOND;
                        packet->type    = PT_NETTRANPOND_A2F_GROUP_TO_CLIENT;

                        clientGroupData = ( PT_NETTRANPOND_CLIENT_GROUP_DATA* )packet->data;
                        if (!clientGroupData)  return;
                        //����߼����ݴ�С
                        clientGroupData->clientNetInfoCount = 0;
                        clientGroupData->dataSize = dataSize;

                        clientNetInfoArray   = (ClientNetInfo*)( dataPtr.getTranspondData() + dataSize );
                        clientNetInfo        = NULL;

                        sendDataSize		= sendDataHeadSize;
                    }
				}
			}

			//------------------------------------------------------------------------------------

			// ������Ҽ�¼
			clientNetInfo = clientNetInfoArray + clientGroupData->clientNetInfoCount;
			clientNetInfo->account_id       = tempClientObject->accountId;
			clientNetInfo->client_net_id    = tempClientObject->netIdInFrontServer;

			// ��������
			sendDataSize += PT_NETTRANPOND_CLIENT_GROUP_DATA_INFO::clientNetInfoSize;
			++clientGroupData->clientNetInfoCount;
		}
			
		//------------------------------------------------------------------------------------
		// �����ʣ������
		if ( dataPtr.mDataPtr.isNull() == false )
		{  
            if ( clientGroupData->clientNetInfoCount > 0 )
            {
                // ��������
                ChatServerMain::getInstance().getServerLauncher()->sendServer(
                    dataPtr.mDataPtr,
                    sendDataSize,
                    frontServerID);
            }
		}
	}

	
}