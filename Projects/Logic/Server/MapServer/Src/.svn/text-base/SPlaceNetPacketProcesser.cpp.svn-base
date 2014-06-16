/******************************************************************************/
#include "stdafx.h"
#include "ServerManager.h"
#include "SPlaceNetPacketProcesser.h"
#include "PlaceNetPacket.h"
#include "MapServerMain.h"
//#include "SPlayer.h"
#include "NetTranspondPacketProcesser.h"
//#include "SWorldManager.h"
#include "SPlayer.h"
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
	Bool SPlaceNetPacketProcesser::processFrontServerPacket(I32 id, NetEventRecv* packet)
	{
		if ( packet->getChannel() == GNPC_PLACE )
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_PLACE_F2M_CLICED_INFO:
				onRecvPlaceClickFromFrontServer(id,(PT_PLACE_F2M_CLICED_INFO_DATA*)data->data);
				break;
			}

			return true;
		}
		return false;
	}

	//--------------------------------------------------------------------------
	void SPlaceNetPacketProcesser::onRecvPlaceClickFromFrontServer( I32 id, PT_PLACE_F2M_CLICED_INFO_DATA* data )
	{
	}

	//--------------------------------------------------------------------------
	void SPlaceNetPacketProcesser::sendPlaceBaseInfoToPlayer( Player* player, SMapObject* placeObject )
	{
		SPlayer* playerInfo = (SPlayer*)player;
		if (!playerInfo)
		{
			return;
		}

		GameNetSendDataBufferPtr dataPtr ;
        MapServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			packet->channel = GNPC_PLACE;
			packet->type    = PT_PLACE_S2C_BASE_INFO;

			PT_PLACE_S2C_BASE_INFO_DATA* sendData = (PT_PLACE_S2C_BASE_INFO_DATA*)(packet->data);
			if ( sendData )
			{
				sendData->nNum = 10000;

				const Int dataSize = sizeof GameNetPacketData_INFO::headSize + PT_PLACE_S2C_BASE_INFO_DATA_INFO::dataSize;
				MapServerMain::getInstance().getServerLauncher()->sendServer(dataPtr, dataSize, playerInfo->getFrontServerId());
			}
		}
	}

}