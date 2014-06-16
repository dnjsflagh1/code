/******************************************************************************/
#include "stdafx.h"
#include "ServerManager.h"
#include "TimeNetPacketProcesser.h"
#include "MGameTimeSystem.h"
#include "GameNetPacket.h"
#include "MapServerMain.h"
/******************************************************************************/
namespace MG
{
	//--------------------------------------------------------------------------
	Bool MG::TimeNetPacketProcesser::processCenterServerPacket( I32 id,NetEventRecv* packet )
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
		MGameTimeSystem::getInstance().setCurrActualTime(data->currTime);
	}
	//--------------------------------------------------------------------------
	void TimeNetPacketProcesser::getTimeFromCenterServer()
	{
		///////////////////////////////////////////////////////////////////////////

		// 获得一个发送【客户端】缓存
		GameNetSendDataBufferPtr dataPtr;
        MapServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_TIME;
			packet->type    = PT_TIME_S2E_GET;

			PT_TIME_S2E_GETTIME_DATA* sendData = (PT_TIME_S2E_GETTIME_DATA*)packet->data;

			// 发送数据
			ServerManager::getInstance().sendNetPacketToCenterServer( dataPtr,
				GameNetPacketData_INFO::headSize + PT_TIME_S2E_GETTIME_DATA_INFO::dataSize );
		}
	}
	//--------------------------------------------------------------------------

}
