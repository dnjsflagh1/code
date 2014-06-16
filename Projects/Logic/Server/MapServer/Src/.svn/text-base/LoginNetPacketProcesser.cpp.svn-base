/******************************************************************************/
#include "stdafx.h"
//#include "GameNetEvent.h"
#include "LoginNetPacketProcesser.h"
#include "ServerManager.h"
#include "LoginNetPacket.h"
#include "SWorldManager.h"
#include "MapServerMain.h"
/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	LoginNetPacketProcesser::LoginNetPacketProcesser()
	{
	}
	//--------------------------------------------------------------------------
	LoginNetPacketProcesser::~LoginNetPacketProcesser()
	{
	}
	//--------------------------------------------------------------------------
	Bool LoginNetPacketProcesser::processFrontServerPacket(I32 id, NetEventRecv* packet)
	{
		if ( packet->getChannel() == GNPC_LOGIN )
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_LOGIN_F2M_CHECK_INFRONTSERVER_RESULT:
				onCheckClientInFrontServerResult(( PT_LOGIN_F2M_CHECK_INFRONTSERVER_RESULT_DATA*)data->data);
				break;
			}
			return true;
		}
		return false;
	}
	//--------------------------------------------------------------------------
	//void LoginNetPacketProcesser::onRecvMapListFromFrontServer( I32 id , PT_F2M_MAPLIST_DATA* data)
	//{
	//	if (data->num > 0)
	//	{
	//	}
	//	//ServerManager::getInstance().addFrontServer(data->mapInfo->port);
	//}
	//-----------------------------------------------------------------------
	void LoginNetPacketProcesser::onCheckClientInFrontServerResult( PT_LOGIN_F2M_CHECK_INFRONTSERVER_RESULT_DATA* data )
	{
		//LoginManager::getInstance().handleCheckClientInFrontServerResult(data->accountName,data->result);
		if (data->result)
		{
			
		}
		else
		{
			DYNAMIC_ASSERT(0);
			//SWorldManager::getInstance().removePlayer(data->clientNetIdInFrontServer);
		}

	}
	//-----------------------------------------------------------------------
	void LoginNetPacketProcesser::sendCheckClientInFrontServer(I32 frontServerId, I32 clientNetIdInFs )
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
			packet->channel = GNPC_LOGIN;
			packet->type    = PT_LOGIN_M2F_CHECK_INFRONTSERVER;

			// 转换逻辑包
			PT_LOGIN_M2F_CHECK_INFRONTSERVER_DATA* sendData = (PT_LOGIN_M2F_CHECK_INFRONTSERVER_DATA*)(packet->data);
			if ( sendData )
			{
				sendData->clientNetIdInFrontServer = clientNetIdInFs;
				// 发送数据
				const Int dataSize = GameNetPacketData_INFO::headSize + PT_LOGIN_L2F_CHECK_INFRONTSERVER_DATA_INFO::dataSize;
				MapServerMain::getInstance().getServerLauncher()->sendServer(dataPtr, dataSize, frontServerId);
				//dataPtr->send( GameNetPacketData_INFO::headSize + PT_LOGIN_L2F_CHECK_INFRONTSERVER_DATA_INFO::dataSize, frontServerId );
			}
		}
	}
	//--------------------------------------------------------------------------
}