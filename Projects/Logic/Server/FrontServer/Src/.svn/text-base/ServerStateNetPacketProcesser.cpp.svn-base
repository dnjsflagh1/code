/******************************************************************************/
#include "stdafx.h"
#include "ServerManager.h"
#include "ServerStateNetPacketProcesser.h"
#include "SWorldManager.h"
/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	Bool ServerStateNetPacketProcesser::processMapServerPacket( I32 id,NetEventRecv* packet )
	{
		return false;
	}

	//--------------------------------------------------------------------------
	Bool ServerStateNetPacketProcesser::processCenterServerPacket( I32 id,NetEventRecv* packet )
	{
		if ( packet->getChannel() == GNPC_SERVER_STATE )
		{   
			//FUNDETECTION(__MG_FUNC__);
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			//case PT_SERVER_STATE_S2S_SYNC_MAPSERVER_STATE:	
			//	//onRecvSyncServerState( id , (PT_SERVER_STATE_S2S_SYNC_MAPSERVER_STATE_DATA*)data->data);
			//	break;

			case PT_SERVER_STATE_S2S_SYNC_MAPSERVER_STATE_NEW_START:	
				onRecvSyncServerStateNewStart( id , (PT_SERVER_STATE_S2S_SYNC_MAPSERVER_STATE_NEW_START_DATA*)data->data);
				break;
			case PT_SERVER_STATE_S2S_SYNC_MAPSERVER_STATE_NEW:	
				onRecvSyncServerStateNew( id , (PT_SERVER_STATE_S2S_SYNC_MAPSERVER_STATE_NEW_DATA*)data->data);
				break;

			}

			return true;
		}
		return false;
	}

	//--------------------------------------------------------------------------
	void ServerStateNetPacketProcesser::onRecvSyncServerStateNew( I32 id , PT_SERVER_STATE_S2S_SYNC_MAPSERVER_STATE_NEW_DATA* data)
	{
		ServerManager::getInstance().handleSyncServerStateNew(data);
	}

	//--------------------------------------------------------------------------
	void ServerStateNetPacketProcesser::onRecvSyncServerStateNewStart( I32 id , PT_SERVER_STATE_S2S_SYNC_MAPSERVER_STATE_NEW_START_DATA* data)
	{
		ServerManager::getInstance().handleSyncServerStateNewStart(data);
	}
}
