/******************************************************************************/
#include "stdafx.h"
#include "ServerManager.h"
#include "SMapNetPacketProcesser.h"
#include "SPlayer.h"
#include "MapNetPacket.h"
#include "NetTranspondPacketProcesser.h"
/******************************************************************************/

namespace MG
{

	//--------------------------------------------------------------------------
	SMapNetPacketProcesser::SMapNetPacketProcesser()
	{

	}

	//--------------------------------------------------------------------------
	SMapNetPacketProcesser::~SMapNetPacketProcesser()
	{

	}

	//--------------------------------------------------------------------------
	Bool SMapNetPacketProcesser::processFrontServerPacket(I32 id, NetEventRecv* packet)
	{
		if ( packet->getChannel() == GNPC_MAP )
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
				break;
			}

			return true;
		}
		return false;
	}

	//--------------------------------------------------------------------------
	void SMapNetPacketProcesser::sendMapBaseInfoToPlayer( SPlayer* player, SMapObject* mapObject )
	{
		SPlayer* playerInfo = (SPlayer*)player;

		NetTranspondSendDataBufferPtr dataPtr;
        NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

		GameNetPacketData* packet = (GameNetPacketData*) dataPtr.getTranspondData();
		if ( packet )
		{
			packet->channel = GNPC_MAP;
			packet->type    = PT_MAP_M2C_BASE_INFO;

			PT_MAP_M2C_BASE_INFO_DATA* sendData = (PT_MAP_M2C_BASE_INFO_DATA*)(packet->data);
			if ( sendData )
			{
				sendData->numTest = 10000;

				NetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer( dataPtr, 
					GameNetPacketData_INFO::headSize + PT_MAP_M2C_BASE_INFO_INFO::dataSize, 
					player->getFrontServerId(), player->getClientNetIdInFrontServer(), playerInfo->getAccountId());
			}
		}
	}
}