/******************************************************************************/
#include "stdafx.h"
#include "ServerManager.h"
#include "MapServerMain.h"
#include "ServerStateNetPacketProcesser.h"
//#include "SWorldManager.h"
#include "SWorldManager.h"
/******************************************************************************/
namespace MG
{
	//--------------------------------------------------------------------------------------
	Bool ServerStateNetPacketProcesser::processCenterServerPacket( I32 id,NetEventRecv* packet )
	{
		if ( packet->getChannel() == GNPC_SERVER_STATE )
		{   
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			//case PT_SERVER_STATE_S2S_SYNC_MAPSERVER_STATE:
			//	onRecvSyncServerState(id, (PT_SERVER_STATE_S2S_SYNC_MAPSERVER_STATE_DATA*)(data->data));
			//	break;
			case PT_SERVER_STATE_S2S_SYNC_MAPSERVER_STATE_NEW:
				onRecvSyncServerStateNew(id, (PT_SERVER_STATE_S2S_SYNC_MAPSERVER_STATE_NEW_DATA*)(data->data));
				break;
			}

			return true;
		}
		return false;
	}

#if 0
	//--------------------------------------------------------------------------------------
	void ServerStateNetPacketProcesser::onRecvSyncServerState( I32 id , PT_SERVER_STATE_S2S_SYNC_MAPSERVER_STATE_DATA* data )
	{
		for(I32 i = 0; i < data->mapServerNum; i++)
		{
			if (data->serverStates[i].serverUniqueFlag == MapServerMain::getInstance().getServerLauncher()->getUniqueFlag())
			{
				//�յ�ͬ��������״̬ʱ��  ��Ҫ����load��ͼ��Ϣ
				SWorldManager::getInstance().reLoadByCenterServerDevideInfo(data->serverStates[i].mapNum,data->serverStates[i].mapId);
				break;
			}
		}
		//SWorldManagerNew::getInstance().printWorldObject();
	}
#endif

	//--------------------------------------------------------------------------------------
	void ServerStateNetPacketProcesser::onRecvSyncServerStateNew( I32 id , PT_SERVER_STATE_S2S_SYNC_MAPSERVER_STATE_NEW_DATA* data)
	{
		MG_LOG(out_sys, "\n ��ʼ������ͼ ������\n ");
		for(I32 i = 0; i < data->mapServerNum; i++)
		{
			if (data->serverUniqueFlag == MapServerMain::getInstance().getServerLauncher()->getUniqueFlag())
			{
				//�յ�ͬ��������״̬ʱ��  ��Ҫ����load��ͼ��Ϣ
				SWorldManager::getInstance().reLoadByCenterServerDevideInfoNew(data->mapServerNum,data->mapServerIndex);
				break;
			}
		}
		MG_LOG(out_sys, "\n ������ͼ ���\n ");

		SWorldManager::getInstance().printActiveRegionObject();
	}

};
