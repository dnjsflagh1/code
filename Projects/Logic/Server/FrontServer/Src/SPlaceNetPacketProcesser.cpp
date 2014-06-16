/******************************************************************************/
#include "stdafx.h"
#include "SPlaceNetPacketProcesser.h"
#include "PlaceNetPacket.h"
#include "SPlayer.h"
#include "ServerManager.h"
#include "FrontServerMain.h"
#include "SWorldManager.h"
/******************************************************************************/

namespace MG
{

	//--------------------------------------------------------------------------
	SPlaceNetPacketProcesser::SPlaceNetPacketProcesser()
	{

	}

	//--------------------------------------------------------------------------
	SPlaceNetPacketProcesser::~SPlaceNetPacketProcesser()
	{

	}

	//--------------------------------------------------------------------------
	Bool SPlaceNetPacketProcesser::processClientPacket( I32 id, NetEventRecv* packet )
	{
		if(packet->getChannel() == GNPC_PLACE)
		{
			//FUNDETECTION(__MG_FUNC__);
				GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

				switch (data->type)
				{
				case PT_PLACE_C2F_CLICED_INFO:
					onRecvPlaceClickFromClient(id, (PT_PLACE_C2F_CLICED_INFO_DATA*)(data->data));
					break;
				default:
					DYNAMIC_ASSERT(false);
					break;
				}
				return true;
		}
		return false;
	}

	//--------------------------------------------------------------------------
	void SPlaceNetPacketProcesser::onRecvPlaceClickFromClient( I32 netId, PT_PLACE_C2F_CLICED_INFO_DATA* data )
	{
#if NEW_VERSION_LINHU
		SPlayerPtr player;// = SWorldManager::getInstance().getGameObjectManager()->getPlayerByClientNetId(netId);

#else
		SPlayerPtr player = SWorldManager::getInstance().getPlayerByClientNetId(netId);
#endif

        //SPlayer* player = SWorldManager::getInstance().getPlayerByClientNetId(netId);
        if (player.isNull())
        {
            //error 
            //KickPlayer()
            return;
        }

#if NEW_VERSION_LINHU
		SPlaceObject* placeObj = (SPlaceObject*)SWorldManager::getInstance().getRegionObject(ROT_PLACE, data->placeId);

#else
		PlaceObject_OldVersion* placeObj = SWorldManager::getInstance().retrievePlaceObject(data->placeId);
#endif

        //PlaceObject* placeObj = SWorldManager::getInstance().retrievePlaceObject(data->placeId);
        if (!placeObj)
        {
            return;
        }

        // ���һ�����͡�����ˡ�����
        GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

        // ת���ɱ�׼����ʽ
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // ���ñ�ǩ
            packet->channel = GNPC_PLACE;
            packet->type    = PT_PLACE_F2M_CLICED_INFO;

            // ת���߼���
            PT_PLACE_F2M_CLICED_INFO_DATA* sendData = (PT_PLACE_F2M_CLICED_INFO_DATA*)(packet->data);
            if ( sendData )
            {
                // ����߼���
                //IdType mapId = placeObj->getBelongMapID();
				IdType mapId = 0;
                IdType accountId = player->getAccountID();

                sendData->accountId = accountId;
                sendData->placeDir = data->placeDir;
                sendData->placePos = data->placePos;
                sendData->placeId = data->placeId;

                // ��������
                ServerManager::getInstance().sendNetPacketToActiveMapServerByNetId( dataPtr, 
                    GameNetPacketData_INFO::headSize + PT_PLACE_F2M_CLICED_INFO_DATA_INFO::dataSize,
                    mapId );
            }
        }
	}
}