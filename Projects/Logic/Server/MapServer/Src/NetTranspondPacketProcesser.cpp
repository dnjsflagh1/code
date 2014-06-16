//******************************************************************************/
#include "stdafx.h"
#include "GameNetPacket.h"
#include "NetTranspondNetPacket.h"
#include "ServerManager.h"
#include "MapServerMain.h"
#include "NetTranspondPacketProcesser.h"
#include "SPlayer.h"
#include "SSceneGrid.h"
#include "SSceneGridManager.h"
#include "MapServerMain.h"
//******************************************************************************/

namespace MG
{
    /******************************************************************************/
    // NetTranspondSendDataBufferPtr
    /******************************************************************************/

	//--------------------------------------------------------------------------
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
            //DYNAMIC_ASSERT_LOG("too much client!");
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
        MapServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( ptr.mDataPtr, buffSize );
        ptr.mUsedHeadSize = GameNetPacketData_INFO::headSize+PT_NETTRANPOND_CLIENT_GROUP_DATA_INFO::headSize;
        ptr.mEstimateTailSize = PT_NETTRANPOND_CLIENT_GROUP_DATA_INFO::clientNetInfoSize;
    }

    //--------------------------------------------------------------------------
    Bool NetTranspondPacketProcesser::sendClientTranspondSendDataToFrontServer( 
		NetTranspondSendDataBufferPtr& dataPtr, Int dataSize,
        I32 frontSvrNetID, I32 client_net_id, U64 account_id )
    {
        // ת���ɱ�׼����ʽ
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr.mDataPtr->getLogicData();
        if ( packet )
        {
            // ���ñ�ǩ
            packet->channel = GNPC_NET_TRANSPOND;
            packet->type    = PT_NETTRANPOND_M2F_GROUP_TO_CLIENT;

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
                    clientData->account_id      = account_id;
                    clientData->client_net_id   = client_net_id;
                }

                // ��������
				MapServerMain::getInstance().getServerLauncher()->sendServer( 
					dataPtr.mDataPtr,
					GameNetPacketData_INFO::headSize + PT_NETTRANPOND_CLIENT_GROUP_DATA_INFO::dataSize(clientGroupData),
					frontSvrNetID );

				return true;
            }
        }

		return true;
    }

	//-----------------------------------------------------------------------------------
	void NetTranspondPacketProcesser::gridsBroadcastClientTranspondPackToFrontServer( 
		SSceneGrid* currSceneGrid, 
        SSceneGrid* lastSceneGrid,
		NetTranspondSendDataBufferPtr& dataPtr, 
        Int dataSize, 
		PlayerIdType ignorePlayerId, 
        GridsBroadcastType broadcastType )
	{
#if 0
		//-----------------------------------------------------------------------------------
		// ͨ��pos�õ���������(һ��)
		// ͨ���������õ���Ҫ�㲥������б�(����FrontServer����)
		//-----------------------------------------------------------------------------------
		if (NULL == currSceneGrid && broadcastType == GBT_CURR)
		{
			/*DYNAMIC_ASSERT(0);*/
			return;
		}
			
		//-----------------------------------------------------------------------------------

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr.mDataPtr->getLogicData();
		if (NULL == packet)
		{
			DYNAMIC_ASSERT(0);
			return;
		}
		// ���ñ�ǩ
		packet->channel = GNPC_NET_TRANSPOND;
		packet->type    = PT_NETTRANPOND_M2F_GROUP_TO_CLIENT;

		// ת��ת�����ṹ
		PT_NETTRANPOND_CLIENT_GROUP_DATA* clientGroupData = ( PT_NETTRANPOND_CLIENT_GROUP_DATA* )packet->data;
		if (NULL == clientGroupData)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// ��ʼ���߼����ݴ�С
		clientGroupData->dataSize			= dataSize;
		clientGroupData->clientNetInfoCount = 0;

		// �õ���������ͷ��С
		I32 sendDataHeadSize                = GameNetPacketData_INFO::headSize + PT_NETTRANPOND_CLIENT_GROUP_DATA_INFO::headSize + dataSize;
		ClientNetInfo* clientNetInfoArray   = (ClientNetInfo*)( dataPtr.getTranspondData() + dataSize );
		ClientNetInfo* clientNetInfo        = 0;

		// ��ǰ�������ݴ�С
		I32 sendDataSize        = sendDataHeadSize;
		// ׼���������ݴ�С
		I32 prepareSendDataSize = 0;

		//-----------------------------------------------------------------------------------

		// ��Ҷ���
		SPlayer* player = NULL;
		// frontSvr������
		NetIdType frontServerID = 0;
		// ����б�
		std::map<PlayerIdType, SPlayer*>* playerList = NULL;
		// ����б�iterator
		std::map<PlayerIdType, SPlayer*>::iterator playerIter;

		// �Ƿ��¡�µķ������ݶ���
		std::map<NetIdType, std::map<PlayerIdType, SPlayer*>> newPlayerListList;

		//-----------------------------------------------------------------------------------

		if(broadcastType == GBT_CURR || !lastSceneGrid)
		{
			std::map<NetIdType, PlayerListInGrid*>* currPlayerListList = 0;//currSceneGrid->getPlayerInteractionListList();


			PlayerListInGrid* currGridPlayerList = NULL;
			for(std::map<NetIdType, PlayerListInGrid*>::iterator currListIt = currPlayerListList->begin(); currListIt != currPlayerListList->end(); ++currListIt)
			{
	
				currGridPlayerList = currListIt->second;
				for(std::map<PlayerIdType, PlayerInGrid*>::iterator currIt = currGridPlayerList->mPlayerList.begin(); currIt != currGridPlayerList->mPlayerList.end(); ++currIt)
				{
					newPlayerListList[currListIt->first][currIt->first] = currIt->second->player;
				}
			}
		}
		else if((broadcastType == GBT_LAST))
		{
			std::map<NetIdType, PlayerListInGrid*>* lastPlayerListList = lastSceneGrid->getPlayerInteractionListList();

			PlayerListInGrid* lastGridPlayerList = NULL;
			for(std::map<NetIdType, PlayerListInGrid*>::iterator lastListIt = lastPlayerListList->begin(); lastListIt != lastPlayerListList->end(); ++lastListIt)
			{
				lastGridPlayerList = lastListIt->second;
				for(std::map<PlayerIdType, PlayerInGrid*>::iterator lastIt = lastGridPlayerList->mPlayerList.begin(); lastIt != lastGridPlayerList->mPlayerList.end(); ++lastIt)
				{
					newPlayerListList[lastListIt->first][lastIt->first] = lastIt->second->player;
				}
			}
		}
		else if(broadcastType == GBT_FILTER_LAST)
		{
			subSceneGridsPlayerList(lastSceneGrid, currSceneGrid, newPlayerListList);
		}
		else if(broadcastType == GBT_FILTER_CURR)
		{
			subSceneGridsPlayerList(currSceneGrid, lastSceneGrid, newPlayerListList);
		}
		else
		{
			return;
		}

		//-----------------------------------------------------------------------------------

		for (std::map<NetIdType, std::map<PlayerIdType, SPlayer*>>::iterator playerListIt = newPlayerListList.begin(); 
			playerListIt != newPlayerListList.end(); 
			++playerListIt)
		{
			// �������б�
			playerList = &(playerListIt->second);

			// ���Ϊ��������
			if ( playerList == NULL )
			{
				continue;
			}
			if ( playerList->size() == 0 )
			{
				continue;
			}

			frontServerID = playerListIt->first;

			// ��������б�
			for ( playerIter = playerList->begin(); playerIter != playerList->end(); ++playerIter )
			{

				//-----------------------------------------------------------------------------------

				// �����Ҷ���
				player = playerIter->second;

				if ( player->getAccountId() != (U64)playerIter->first )
				{
					//DYNAMIC_EEXCEPT_LOG("player->getAccountID != playerIter->first");
					//DYNAMIC_ASSERT(false);
					continue;
				}

				if(ignorePlayerId == player->getAccountId())
				{
					continue;
				}

				//-----------------------------------------------------------------------------------

				if ( dataPtr.mDataPtr.isNull() == false )
				{
					// ����һ�����׼���������ݴ�С���������ݻ����С
					prepareSendDataSize = sendDataSize + PT_NETTRANPOND_CLIENT_GROUP_DATA_INFO::clientNetInfoSize;

					// ���׼���������ݴ��ڻ��������������
					if ( prepareSendDataSize >= dataPtr.mDataPtr->getLogicDataMaxSize() )
					{
						MapServerMain::getInstance().getServerLauncher()->sendServer( dataPtr.mDataPtr, sendDataSize, frontServerID );

                        //------------------------------------------------------------------------------------

                        // Clone
                        {
                            MapServerMain::getInstance().getServerLauncher()->cloneSendDataBuffer( dataPtr.mDataPtr , dataPtr.mDataPtr, UInt(sendDataHeadSize) );

                            // ת���ɱ�׼����ʽ
                            packet = (GameNetPacketData*) dataPtr.mDataPtr->getLogicData();
                            if (NULL == packet)
                            {
                                DYNAMIC_ASSERT(0);
                                return;
                            }

                            // ���ñ�ǩ
                            packet->channel = GNPC_NET_TRANSPOND;
                            packet->type    = PT_NETTRANPOND_M2F_GROUP_TO_CLIENT;

                            // ת��ת�����ṹ
                            clientGroupData = ( PT_NETTRANPOND_CLIENT_GROUP_DATA* )packet->data;
                            if (NULL == clientGroupData)
                            {
                                DYNAMIC_ASSERT(0);
                                return;
                            }

                            // ��ʼ���߼����ݴ�С
                            clientGroupData->dataSize = dataSize;
                            clientGroupData->clientNetInfoCount = 0;

                            // �ͻ�����Ϣ
                            clientNetInfoArray		= (ClientNetInfo*)( dataPtr.getTranspondData() + dataSize );

                            // ��ǰ�������ݴ�С
                            sendDataSize			= sendDataHeadSize;
                        }
					}
				}

				//-----------------------------------------------------------------------------------

				// ������Ҽ�¼
				clientNetInfo					= clientNetInfoArray + clientGroupData->clientNetInfoCount;
				clientNetInfo->account_id		= player->getAccountId();
				clientNetInfo->client_net_id    = player->getClientNetIdInFrontServer();

				// ��������
				sendDataSize					+= PT_NETTRANPOND_CLIENT_GROUP_DATA_INFO::clientNetInfoSize;
				clientGroupData->clientNetInfoCount++;
			}

			// �����ʣ������
			if ( dataPtr.mDataPtr.isNull() == false )
			{
				if ( clientGroupData->clientNetInfoCount > 0 )
				{
					MapServerMain::getInstance().getServerLauncher()->sendServer( 
                        dataPtr.mDataPtr, 
                        sendDataSize, 
                        frontServerID );
					dataPtr.mDataPtr.setNull();
				}
			}
		}

#endif
	}

	//-----------------------------------------------------------------------------------
	void NetTranspondPacketProcesser::broadcastClientTranspondPackToFrontServer(
																				NetTranspondSendDataBufferPtr& dataPtr,
																				Int dataSize,
																				SSceneGrid* currSceneGrid, 
																				SSceneGrid* lastSceneGrid, 
																				SRegionObjectBase* regionObjectBase,  
																				PlayerIdType ignorepPlayerId,
																				GridsBroadcastType broadcastType)
	{
#if 0
		if(regionObjectBase->getGameType() == GameType_Rpg)
		{
			NetTranspondPacketProcesser::getInstance().gridsBroadcastClientTranspondPackToFrontServer(currSceneGrid, lastSceneGrid, dataPtr, 
				dataSize, ignorepPlayerId, broadcastType);
		}
		else
		{
			NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(dataPtr, dataSize, regionObjectBase);
		}
#endif
	}

	//-----------------------------------------------------------------------------------
	void NetTranspondPacketProcesser::broadcastClientTranspondPackToFrontServer( 
		NetTranspondSendDataBufferPtr& dataPtr, Int dataSize, SRegionObjectBase* region)
	{
#if 0
		//---------------------------------------------------------------------

		if (NULL == region)
		{
			DYNAMIC_EEXCEPT_LOG("NetTranspondPacketProcesser::broadcastClientTranspondPackToFrontServer : not find region!");
			return;
		}

		//---------------------------------------------------------------------

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr.mDataPtr->getLogicData();
		if (NULL == packet)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// ���ñ�ǩ
		packet->channel = GNPC_NET_TRANSPOND;
		packet->type    = PT_NETTRANPOND_M2F_GROUP_TO_CLIENT;

		// ת��ת�����ṹ
		PT_NETTRANPOND_CLIENT_GROUP_DATA* clientGroupData = ( PT_NETTRANPOND_CLIENT_GROUP_DATA* )packet->data;
		if (NULL == clientGroupData)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// ��ʼ���߼����ݴ�С
		clientGroupData->dataSize = dataSize;
		clientGroupData->clientNetInfoCount = 0;

		// �õ���������ͷ��С
		I32 sendDataHeadSize                = GameNetPacketData_INFO::headSize + PT_NETTRANPOND_CLIENT_GROUP_DATA_INFO::headSize + dataSize;
		ClientNetInfo* clientNetInfoArray   = (ClientNetInfo*)( dataPtr.getTranspondData() + dataSize );
		ClientNetInfo* clientNetInfo        = NULL;

		// ��ǰ�������ݴ�С
		I32 sendDataSize					= sendDataHeadSize;

		// ׼���������ݴ�С
		I32 prepareSendDataSize				= 0;

		//---------------------------------------------------------------------

		// ��Ҷ���
		SPlayer* player = NULL;

		// frontSvr������
		NetIdType frontServerID = 0;

		// ����б�
		std::map<AccountIdType, Player*>* playerList = NULL;
		// ����б�iterator
		std::map<AccountIdType, Player*>::iterator playerIter;

		// ��������б�����FrontServerSlot����

        std::vector<NetIdType> netList;
        ServerManager::getInstance().getFrontServerList( netList );
		for ( UInt i=0; i<netList.size(); i++ )
		{
			// frontSvr������
			frontServerID = netList[i];
			// �������б�
			playerList = region->getPlayerListByFronServerId(frontServerID);

            // ���Ϊ��������
            if ( playerList == NULL )
            {
                continue;
            }
			if ( playerList->size() == 0 )
			{
				continue;
			}

			// ��������б�
			for ( playerIter = playerList->begin(); playerIter != playerList->end(); ++playerIter )
			{
				//---------------------------------------------------------------------

				// �����Ҷ���
				player = (SPlayer*)playerIter->second;

				//---------------------------------------------------------------------

				if ( dataPtr.mDataPtr.isNull() == false )
				{
					// ����һ�����׼���������ݴ�С���������ݻ����С
					prepareSendDataSize = sendDataSize + PT_NETTRANPOND_CLIENT_GROUP_DATA_INFO::clientNetInfoSize;

					// ���׼���������ݴ��ڻ��������������
					if ( prepareSendDataSize >= dataPtr.mDataPtr->getLogicDataMaxSize() )
					{
						MapServerMain::getInstance().getServerLauncher()->sendServer( dataPtr.mDataPtr, sendDataSize, frontServerID );


                        //------------------------------------------------------------------------------------
                        //Clone
                        {
                            // clone
                            MapServerMain::getInstance().getServerLauncher()->cloneSendDataBuffer( dataPtr.mDataPtr, dataPtr.mDataPtr, UInt(sendDataHeadSize) );

                            // ת���ɱ�׼����ʽ
                            packet	= (GameNetPacketData*) dataPtr.mDataPtr->getLogicData();
                            if (NULL == packet)
                            {
                                DYNAMIC_ASSERT(0);
                                return;
                            }

                            // ���ñ�ǩ
                            packet->channel = GNPC_NET_TRANSPOND;
                            packet->type    = PT_NETTRANPOND_M2F_GROUP_TO_CLIENT;

                            // ת��ת�����ṹ
                            clientGroupData = ( PT_NETTRANPOND_CLIENT_GROUP_DATA* )packet->data;
                            if (NULL == clientGroupData)
                            {
                                DYNAMIC_ASSERT(0);
                                return;
                            }

                            // ��ʼ���߼����ݴ�С
                            clientGroupData->dataSize = dataSize;
                            clientGroupData->clientNetInfoCount = 0;

                            // �õ���������ͷ��С
                            clientNetInfoArray   = (ClientNetInfo*)( dataPtr.getTranspondData() + dataSize );

                            // ��ǰ�������ݴ�С
                            sendDataSize	= sendDataHeadSize;
                        }
					}
				}

				//---------------------------------------------------------------------

				// ������Ҽ�¼
				clientNetInfo = clientNetInfoArray + clientGroupData->clientNetInfoCount;
				clientNetInfo->account_id       = player->getAccountId();
				clientNetInfo->client_net_id    = player->getClientNetIdInFrontServer();

				// ��������
				sendDataSize += PT_NETTRANPOND_CLIENT_GROUP_DATA_INFO::clientNetInfoSize;
				clientGroupData->clientNetInfoCount++;
			}
					

			//---------------------------------------------------------------------

			// �����ʣ������
			if ( dataPtr.mDataPtr.isNull() == false )
			{
				if ( clientGroupData->clientNetInfoCount > 0 )
				{
					MapServerMain::getInstance().getServerLauncher()->sendServer( 
                        dataPtr.mDataPtr, 
                        sendDataSize, 
                        frontServerID );
					dataPtr.mDataPtr.setNull();
				}
			}
		}
#endif
	}

	//-----------------------------------------------------------------------------------
	void NetTranspondPacketProcesser::subSceneGridsPlayerList( SSceneGrid* regionGrids1, SSceneGrid* regionGrids2, std::map<NetIdType, std::map<PlayerIdType, SPlayer*>>& playerList )
	{
#if 0
		playerList.clear();

		PlayerListInGrid* gridPlayerList1 = NULL;
		PlayerListInGrid* gridPlayerList2 = NULL;

		std::map<NetIdType, PlayerListInGrid*>* playerListList1 = regionGrids1->getPlayerInteractionListList();
		std::map<NetIdType, PlayerListInGrid*>* playerListList2 = regionGrids2->getPlayerInteractionListList();

		for(std::map<NetIdType, PlayerListInGrid*>::iterator playerListIt1 = playerListList1->begin(); playerListIt1 != playerListList1->end(); ++playerListIt1)
		{
			std::map<NetIdType, PlayerListInGrid*>::iterator playerListIt2 = playerListList2->find(playerListIt1->first);
			if(playerListIt2 == playerListList2->end())
			{
				continue;
			}
			
			gridPlayerList1 = playerListIt1->second;
			gridPlayerList2 = playerListIt2->second;
			for(std::map<PlayerIdType, PlayerInGrid*>::iterator playerIt1 = gridPlayerList1->mPlayerList.begin(); playerIt1 != gridPlayerList1->mPlayerList.end(); ++playerIt1)
			{
				std::map<PlayerIdType, PlayerInGrid*>::iterator playerIt2 = gridPlayerList2->mPlayerList.find(playerIt1->first);
				if(playerIt2 != gridPlayerList2->mPlayerList.end())
				{
					continue;
				}

				playerList[playerListIt1->first][playerIt1->first] = playerIt1->second->player;
			}
		}
#endif
	}
}