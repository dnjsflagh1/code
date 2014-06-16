/******************************************************************************/
#include "stdafx.h"
#include "TimeNetPacketProcesser.h"
#include "CGameTimeSystem.h"
#include "GameNetPacket.h"
/******************************************************************************/
namespace MG
{
	//--------------------------------------------------------------------------
	Bool MG::TimeNetPacketProcesser::processFrontServerPacket( I32 id,NetEventRecv* packet )
	{
		if (packet->getChannel() == GNPC_TIME)
		{   
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_TIME_E2S_SYNC:	
				onRecvSyncTime( id , (PT_TIME_E2S_SYNC_DATA*)data->data);
				break;
			}

			return true;
		}
		return false;
	}

	//--------------------------------------------------------------------------
	void MG::TimeNetPacketProcesser::onRecvSyncTime( I32 id , PT_TIME_E2S_SYNC_DATA* data )
	{
		CGameTimeSystem::getInstance().setCurrActualTime(data->currTime);
	}

}
