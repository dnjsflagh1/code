/******************************************************************************/
#include "stdafx.h"
#include "CBattleScoreNetPacketProcesser.h"


/******************************************************************************/

namespace MG
{

	//--------------------------------------------------------------------------
	CBattleScoreNetPacketProcesser::CBattleScoreNetPacketProcesser()
	{

	}

	//--------------------------------------------------------------------------
	CBattleScoreNetPacketProcesser::~CBattleScoreNetPacketProcesser()
	{

	}

	//--------------------------------------------------------------------------
	Bool CBattleScoreNetPacketProcesser::processFrontServerPacket(I32 id, NetEventRecv *packet)
	{
		if ( packet->getChannel() == GNPC_BATTLE_SCORE )
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_BATTLESCORE_M2C_NOTIFY:
				onRecvBattleScoreNotifyFromFrontServer( id, (PT_BATTLESCORE_M2C_NOTIFY_DATA*)data->data );
				break;
			default:
				{
					DYNAMIC_ASSERT(0);
				}
				break;
			}
			return true;
		}
		return false;
	}

	//--------------------------------------------------------------------------
	void CBattleScoreNetPacketProcesser::onRecvBattleScoreNotifyFromFrontServer(I32 id, PT_BATTLESCORE_M2C_NOTIFY_DATA* data)
	{
		int kk = 0;
	}

	//--------------------------------------------------------------------------
}