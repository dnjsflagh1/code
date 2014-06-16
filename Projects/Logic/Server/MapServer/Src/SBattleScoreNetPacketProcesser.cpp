/******************************************************************************/
#include "stdafx.h"
#include "SBattleScoreNetPacketProcesser.h"
#include "BattleScoreNetPacket.h"
#include "NetTranspondPacketProcesser.h"

/******************************************************************************/

namespace MG
{

	//--------------------------------------------------------------------------
	SBattleScoreNetPacketProcesser::SBattleScoreNetPacketProcesser()
	{

	}

	//--------------------------------------------------------------------------
	SBattleScoreNetPacketProcesser::~SBattleScoreNetPacketProcesser()
	{

	}

	//--------------------------------------------------------------------------
	void SBattleScoreNetPacketProcesser::sendBattleScoreNotify(const Int rankId, SRegionObjectBase* region)
	{
		DYNAMIC_ASSERT(NULL != region);

		NetTranspondSendDataBufferPtr dataPtr ;
        NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if (NULL == packet)
		{
			DYNAMIC_ASSERT(0);
			return ;
		}

		packet->channel = GNPC_BATTLE_SCORE;
		packet->type    = PT_BATTLESCORE_M2C_NOTIFY;
		PT_BATTLESCORE_M2C_NOTIFY_DATA* sendData = (PT_BATTLESCORE_M2C_NOTIFY_DATA*)(packet->data);

		//��ʼ��� Begin
		sendData->rankId = rankId;
		//��ʼ��� End

		NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(dataPtr, 
			GameNetPacketData_INFO::headSize + PT_BATTLESCORE_M2C_NOTIFY_DATA_INFO::dataSize, region);
	}

	//--------------------------------------------------------------------------
}