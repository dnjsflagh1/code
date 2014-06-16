/******************************************************************************/
#include "stdafx.h"
#include "ServerManager.h"
#include "TimeNetPacketProcesser.h"
#include "FGameTimeSystem.h"
#include "GameNetPacket.h"
#include "FrontServerMain.h"
#include "SWorldManager.h"
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
		FGameTimeSystem::getInstance().setCurrActualTime(data->currTime);
		bocastTimeToClient(data->currTime);
	}
	//--------------------------------------------------------------------------
	void TimeNetPacketProcesser::bocastTimeToClient( U64 currTime )
	{
		///////////////////////////////////////////////////////////////////////////

		// 获得一个发送【客户端】缓存
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );


		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_TIME;
			packet->type    = PT_TIME_E2S_SYNC;
			
			PT_TIME_E2S_SYNC_DATA* sendData = (PT_TIME_E2S_SYNC_DATA*)packet->data;
			sendData->currTime = currTime;

			// 发送数据
			SWorldManager::getInstance().boardcastNetPacketToAllClient( dataPtr,
				GameNetPacketData_INFO::headSize + PT_TIME_E2S_SYNC_DATA_INFO::dataSize );
		}
	}
	//--------------------------------------------------------------------------
	void TimeNetPacketProcesser::getTimeFromCenterServer()
	{
		///////////////////////////////////////////////////////////////////////////

		// 获得一个发送【客户端】缓存
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );


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
