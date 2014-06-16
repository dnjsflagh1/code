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
            case PT_NETTRANPOND_M2F_GROUP_TO_CLIENT:	// MapServer ����������Ϣ
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
			case PT_NETTRANPOND_T2F_GROUP_TO_CLIENT:	// CenterServer ����������Ϣ
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

        // ���һ�����͡�����ˡ�����
        GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

        // ת���ɱ�׼����ʽ
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // ���ñ�ǩ
			memcpy( packet, data, dataSize);

			FrontServerMain::getInstance().getServerLauncher()->sendServer(dataPtr,dataSize, mapNetId);
        }
    }
    
    //--------------------------------------------------------------------------
    void NetTranspondPacketProcesser::broadcastClientTranspondDataToMapServer( I32 client_net_id, U64 account_id, GameNetPacketData* data, Int dataSize )
    {
		//FUNDETECTION(__MG_FUNC__);
        ///////////////////////////////////////////////////////////////////////////

        // ���һ�����͡�����ˡ�����
        GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

        // ת���ɱ�׼����ʽ
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // ���ñ�ǩ
            packet->channel = GNPC_NET_TRANSPOND;
            packet->type    = PT_NETTRANPOND_F2S_FROM_CLIENT;

            // ת���߼���
            PT_NETTRANPOND_CLIENT_DATA* sendData = (PT_NETTRANPOND_CLIENT_DATA*)(packet->data);
            if ( sendData )
            {
                // ����߼���
                sendData->client_net_id = client_net_id;
                sendData->account_id    = account_id;
                sendData->data.channel	= data->channel;
                sendData->data.type		= data->type;
                memcpy( sendData->data.data,data->data, dataSize - GameNetPacketData_INFO::headSize );

                // ��������
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
	
        // ���һ�����͡��ͻ��ˡ�����
        GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr, data->dataSize );

        // ת���ɱ�׼����ʽ
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // ��Ҫ���͸��ͻ��˵����ݰ���С // GameNetPacketData�ܴ�С
            Int sendDataSize = data->dataSize;

            // ���Ʒ�������
            packet->channel = data->data.channel;
            packet->type    = data->data.type;
            memcpy( packet->data, data->data.data, sendDataSize-GameNetPacketData_INFO::headSize );

            // ����ת���ͻ����б�
            {
                // �ͻ�����Ϣ����ָ��
                Char8* clientArrayHead      = (Char8*)data + PT_NETTRANPOND_CLIENT_GROUP_DATA_INFO::headSize + sendDataSize;
                // ת��ָ��
                ClientNetInfo* clientInfo   = (ClientNetInfo*)(clientArrayHead);

                // ��ʼ����
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
		// ���һ�����͡��ͻ��ˡ�����
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr, data->dataSize );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ��Ҫ���͸��ͻ��˵����ݰ���С // GameNetPacketData�ܴ�С
			Int sendDataSize = data->dataSize;

			// ���Ʒ�������
			packet->channel = data->data.channel;
			packet->type    = data->data.type;
			memcpy( packet->data, data->data.data, sendDataSize - GameNetPacketData_INFO::headSize );

			// ����ת���ͻ����б�
			{
				if ( data->clientNetInfoCount > 0 )
				{
					// �ͻ�����Ϣ����ָ��
					Char8* clientArrayHead      = (Char8*)data + PT_NETTRANPOND_CLIENT_GROUP_DATA_INFO::headSize + sendDataSize;
					// ת��ָ��
					ClientNetInfo* clientInfo   = (ClientNetInfo*)(clientArrayHead);
					
					// ����playerList
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