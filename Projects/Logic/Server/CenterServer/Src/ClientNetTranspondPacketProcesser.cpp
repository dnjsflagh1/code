/******************************************************************************/
#include "stdafx.h"
#include "GameNetPacket.h"
#include "NetTranspondNetPacket.h"
#include "ServerManager.h"
#include "CenterServerMain.h"
#include "ClientNetTranspondPacketProcesser.h"
/******************************************************************************/

namespace MG
{
	/******************************************************************************/
	// NetTranspondSendDataBufferPtr
	/******************************************************************************/

	ClientNetTranspondSendDataBufferPtr::ClientNetTranspondSendDataBufferPtr()
		:mUsedHeadSize(0)
		,mEstimateTailSize(0)
	{

	}

    //--------------------------------------------------------------------------
	ClientNetTranspondSendDataBufferPtr::ClientNetTranspondSendDataBufferPtr(GameNetSendDataBufferPtr& dataPtr, Int usedHeadSize, Int estimateTailSize)
		:mDataPtr(dataPtr)
		,mUsedHeadSize(usedHeadSize)
		,mEstimateTailSize(estimateTailSize)
	{
	}

	//--------------------------------------------------------------------------
	Char8* ClientNetTranspondSendDataBufferPtr::getTranspondData()
	{
		return mDataPtr->getLogicData() + mUsedHeadSize;
	}

	//--------------------------------------------------------------------------
	U32 ClientNetTranspondSendDataBufferPtr::getTranspondDataMaxSize(UInt maxClientCount)
	{
        UInt transpondDefineNeedSize    = mUsedHeadSize + maxClientCount*mEstimateTailSize;
        UInt sysLogicSize               = mDataPtr->getLogicDataMaxSize();
        Int transponddataMaxSize        = sysLogicSize - transpondDefineNeedSize;

        if ( transponddataMaxSize <= 0 )
        {
            DYNAMIC_ASSERT_LOG("too much client!");
            DYNAMIC_ASSERT(false);
            return 0;
        }
        
		return transponddataMaxSize;
	}
    

	/******************************************************************************/
	// ClientNetTranspondPacketProcesser
	/******************************************************************************/
	ClientNetTranspondPacketProcesser::ClientNetTranspondPacketProcesser()
	{

	}

	//--------------------------------------------------------------------------
	ClientNetTranspondPacketProcesser::~ClientNetTranspondPacketProcesser()
	{

	}

	//--------------------------------------------------------------------------
	Bool ClientNetTranspondPacketProcesser::processClientPacket(I32 id, NetEventRecv* packet)
	{

		return false;
	}

	//--------------------------------------------------------------------------
	Bool ClientNetTranspondPacketProcesser::processLoginServerPacket(I32 id, NetEventRecv* packet)
	{

		return false;
	}

	//--------------------------------------------------------------------------
	Bool ClientNetTranspondPacketProcesser::processMapServerPacket(I32 id, NetEventRecv* packet)
	{
		if (packet->getChannel() == GNPC_NET_TRANSPOND)
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_NETTRANPOND_F2S_FROM_CLIENT:
				break;
			}

			return true;
		}

		return false;
	}

	//--------------------------------------------------------------------------
	void ClientNetTranspondPacketProcesser::getClientTranspondSendDataBuffer( ClientNetTranspondSendDataBufferPtr& ptr, U32 buffSize )
	{
        // 获得一个发送【服务端】缓存
        CenterServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( ptr.mDataPtr, buffSize );
        ptr.mUsedHeadSize       = GameNetPacketData_INFO::headSize+PT_NETTRANPOND_CLIENT_GROUP_DATA_INFO::headSize;
        ptr.mEstimateTailSize   = PT_NETTRANPOND_CLIENT_GROUP_DATA_INFO::clientNetInfoSize;
	}

	//--------------------------------------------------------------------------
	void ClientNetTranspondPacketProcesser::sendClientTranspondSendDataToFrontServer( ClientNetTranspondSendDataBufferPtr& dataPtr, Int dataSize,
		NetIdType frontSvrNetID, NetIdType client_net_id, AccountIdType account_id )
	{
		//DYNAMIC_ASSERT(frontSvrNetID > 0 && client_net_id > 0 && account_id > 0);
		
		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr.mDataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_NET_TRANSPOND;
			packet->type    = PT_NETTRANPOND_T2F_GROUP_TO_CLIENT;

			// 转换转发包结构
			PT_NETTRANPOND_CLIENT_GROUP_DATA* clientGroupData = ( PT_NETTRANPOND_CLIENT_GROUP_DATA* )packet->data;
			if ( clientGroupData )
			{
				// 填充转发包数据
				clientGroupData->clientNetInfoCount = 1;
				clientGroupData->dataSize = dataSize;

				// 转换客户端数据
				ClientNetInfo* clientData = (ClientNetInfo*)( dataPtr.getTranspondData() + dataSize );
				if ( clientData )
				{
					// 填充客户端数据
					clientData->account_id      = account_id;
					clientData->client_net_id   = client_net_id;
				}

				// 发送数据
				CenterServerMain::getInstance().getServerLauncher()->sendServer(
					dataPtr.mDataPtr,
					GameNetPacketData_INFO::headSize + PT_NETTRANPOND_CLIENT_GROUP_DATA_INFO::dataSize(clientGroupData),
					frontSvrNetID );
			}
		}
	}

	//--------------------------------------------------------------------------
	void ClientNetTranspondPacketProcesser::broadClientTranspondSendDataToFrontServer( ClientNetTranspondSendDataBufferPtr& dataPtr, Int dataSize)
	{
		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr.mDataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_NET_TRANSPOND;
			packet->type    = PT_NETTRANPOND_T2F_GROUP_TO_ALL_CLIENT;

			// 转换转发包结构
			PT_NETTRANPOND_CLIENT_GROUP_DATA* clientGroupData = ( PT_NETTRANPOND_CLIENT_GROUP_DATA* )packet->data;
			if ( clientGroupData )
			{
				// 填充转发包数据
				clientGroupData->clientNetInfoCount = 1;
				clientGroupData->dataSize = dataSize;

				// 转换客户端数据
				ClientNetInfo* clientData = (ClientNetInfo*)( dataPtr.getTranspondData() + dataSize );
				if ( clientData )
				{
					// 填充客户端数据
					clientData->account_id      = 0;
					clientData->client_net_id   = 0;
				}


				std::list< ServerInfo*>*	frontServerList = ServerManager::getInstance().getFrontServerList();
				std::list<ServerInfo* >::iterator iterFront = frontServerList->begin();
				for (; iterFront != frontServerList->end(); iterFront++)
				{
					I32 frontSvrNetID = (*iterFront)->netId;

					CenterServerMain::getInstance().getServerLauncher()->sendServer(
						dataPtr.mDataPtr,
						GameNetPacketData_INFO::headSize + PT_NETTRANPOND_CLIENT_GROUP_DATA_INFO::dataSize(clientGroupData),
						frontSvrNetID );
				}
			}
		}
	}
}