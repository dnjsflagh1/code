/******************************************************************************/
#include "stdafx.h"
#include "ClientNetApplyManager.h"
#include "NetAddress.h"
//#include "ClientManager.h"

#include "PlayCharacterNetPacketProcesser.h"
#include "PlayerNetPacketProcesser.h"
#include "RegionNetPacketProcesser.h"
#include "TestNetPacketProcesser.h"
#include "LoginNetPacketProcesser.h"
#include "PackNetPacketProcesser.h"
#include "TroopNetPacketProcesser.h"
#include "CampaignNetPacketProcesser.h"
#include "ThreadTaskManager.h"
/******************************************************************************/

namespace MG
{

	//-----------------------------------------------------------------------------
	ClientNetApplyManager::ClientNetApplyManager():
		mNetDriver(-1)
    {
        
    }
    
    //-----------------------------------------------------------------------------
    ClientNetApplyManager::~ClientNetApplyManager()
    {

    }

    //-----------------------------------------------------------------------------
    Bool ClientNetApplyManager::initialize()
    {
        if ( NetManager::initialize() == false )
            return false;
        
		//mNetDriver = createDriver("Client",1200,false,MG_NET_IOCP_BUFFER_SIZE_CLIENT);
		mNetDriver = createDriver(   
			"Client",
			1200,
			false, 
			MG_NET_CLIENT_TIMEOUT_TOUCH_TIME,
			MG_NET_CLIENT_TIMEOUT_DURATION,
			true, 
			MG_GAME_NET_PACKET_NORMAL_MAX_SIZE, 
			MG_GAME_NET_PACKET_BIG_MAX_SIZE,
			MG_NET_BUFFER_SIZE_CLIENT,
			MG_NET_MAX_CLIENT_SOCKET_SENDBUFF_SIZE,
			MG_NET_MAX_CLIENT_SOCKET_RECVBUFF_SIZE,
			DRIVER_TYPE_CLIENT);

		if ( mNetDriver < 0 )
		{
			return false;
		}

		GameNetDriveConfig config;
		config.OnceHandlePacketCount        = 1;
		config.SendCombinePacketMaxSize     = 1024*10;
		config.ReplaceEnableInSendQueue     = true;
		config.ReplaceEnableInRecvQueue     = true;
		config.DiscardEnableInSendQueue     = true;
		config.DiscardEnableInRecvQueue     = true;
		config.BlockWaitEnableInSendQueue   = true;
		config.BlockWaitEnableInRecvQueue   = true;
		configDrive( mNetDriver, config );

        return true;
    }

    //-----------------------------------------------------------------------------
    I32 ClientNetApplyManager::update()
    {
		//FUNDETECTION(__MG_FUNC__);
        I32 res = GameNetPacketManager::update();
		if ( isThreadAutoHandle() == false )
		{
			if ( mNetDriver >= 0 )
			{
				res += manualDoOneL2NHandle( mNetDriver );
				res += manualDoOneN2LHandle( mNetDriver );
			}
		}
        return res;
    }

    //-----------------------------------------------------------------------------
    I32 ClientNetApplyManager::unInitialize()
    {
        I32 res = NetManager::unInitialize();

        return res;
    }

    //-----------------------------------------------------------------------------
    I32 ClientNetApplyManager::connectLoginServer( NetAddress& addr)
    {
        //disconnectLoginServer(loginServerNetId);
        I32 loginServerNetId  = this->connect(mNetDriver, &addr);
		if ( loginServerNetId < 0 )
		{
			DYNAMIC_ASSERT(false);
		}
		Sleep(5);
		return loginServerNetId;
    }

    //-----------------------------------------------------------------------------
    Bool ClientNetApplyManager::disconnectLoginServer(I32 loginServerNetId)
    {
        if ( loginServerNetId >= 0 )
        {
            close(mNetDriver,loginServerNetId);
        }
        return true;
    }

    //-----------------------------------------------------------------------------
    I32 ClientNetApplyManager::connectFrontServer( NetAddress& addr)
    {
        //disconnectFrontServer(frontServerNetId);
        I32 frontServerNetId  = this->connect(mNetDriver, &addr);
		if ( frontServerNetId < 0 )
		{
			DYNAMIC_ASSERT(false);
		}
		Sleep(5);
		return frontServerNetId;
	}
    //-----------------------------------------------------------------------------
    Bool ClientNetApplyManager::disconnectFrontServer(I32 frontServerNetId)
    {
		if ( frontServerNetId >= 0 )
		{
			close(mNetDriver,frontServerNetId);
		}
		return true;
    }

    //-----------------------------------------------------------------------------
    Bool ClientNetApplyManager::disconnectServers()
    {
		closeAll(mNetDriver);
        return true;
    }
	//-----------------------------------------------------------------------------
	GameNetSendDataBufferPtr ClientNetApplyManager::getSendDataBuffer( U32 buffSize  )
	{
		GameNetSendDataBufferPtr netBuffPtr = GameNetPacketManager::getGameNetSendDataBufferPtr( mNetDriver, buffSize );
		return netBuffPtr;
	}

	//-----------------------------------------------------------------------------
	void ClientNetApplyManager::sendLoginServerPacket(I32 loginServerNetId, GameNetSendDataBufferPtr& data, Int dataSize )
	{
		if ( loginServerNetId >= 0 )
		{
			GameNetPacketManager::prepareSend(data,mNetDriver,loginServerNetId,dataSize );
			//data->send( dataSize, loginServerNetId );
		}
	}
	//-----------------------------------------------------------------------------
	void ClientNetApplyManager::sendFrontServerPacket(I32 frontServerNetId, GameNetSendDataBufferPtr& data, Int dataSize )
	{
		if ( frontServerNetId >= 0 )
		{
			GameNetPacketManager::prepareSend(data,mNetDriver,frontServerNetId,dataSize );
			//data->send( dataSize, frontServerNetId );
		}
	}
    //-----------------------------------------------------------------------------
    void ClientNetApplyManager::onAccept(NetEventAccept* netEvent)
    {
        
    }

    //-----------------------------------------------------------------------------
    void ClientNetApplyManager::onConnected(NetEventConnect* netEvent)
    {

    }

    //-----------------------------------------------------------------------------
    void ClientNetApplyManager::onClose(NetEventClose* netEvent)
    {

#ifdef ONE_THREAD
		if (netEvent->getID() < 0)
		{
			DYNAMIC_ASSERT(false);
			return;
		}
		U32 serverFlag = unknownServerPacket;
		//CClient* client = ClientManager::getInstance().getClientbyLoginServerId(netEvent->getID());
		CClient* client =  ThreadTaskManager::getInstance().getClientByLoginServerNetId(netEvent->getID());
		if (!client)
		{
			serverFlag = frontServerPacket;
			//client = ClientManager::getInstance().getClientbyFrontServerId(netEvent->getID());
			client = ThreadTaskManager::getInstance().getClientByFrontServerNetId(netEvent->getID());
		}
		else
		{
			serverFlag = loginServerPacket;
		}

		if (client)
		{
			if (frontServerPacket == serverFlag)
			{
				client->onFrontServerClose();
				client->getOperateManager()->onCloseByFrontServer();
			}
			else if (loginServerPacket == serverFlag)
			{
				client->onLoginServerClose();
				client->getOperateManager()->onCloseByLoginServer();
			}
			else
			{
				DYNAMIC_ASSERT(false);
			}
		}
#else
		I32 netId = netEvent->getID();
		CClient* client = ThreadTaskManager::getInstance().getClientByFrontServerNetId(netId);
		if (!client)
		{
			client = ThreadTaskManager::getInstance().getClientByLoginServerNetId(netId);
		}
		if (!client)
		{
			DYNAMIC_ASSERT(false);
			return;
		}
		ThreadTaskManager::getInstance().addRobotNetTask(client,netEvent);
#endif

		//I32 netId = netEvent->getID();
		//CClient* client = ThreadTaskManager::getInstance().getClientByFrontServerNetId(netId);
		//if (!client)
		//{
		//	client = ThreadTaskManager::getInstance().getClientByLoginServerNetId(netId);
		//}
		//if (!client)
		//{
		//	// 内存池，多线程有误
		//	DYNAMIC_ASSERT(false);
		//	return;
		//}

		//if (client->getFrontServerNetId() == netEvent->getID())
		//{
		//	if (netEvent->getType() == NET_RECV)
		//	{	
		//		ClientNetApplyManager::getInstance().processPacket (client,(NetEventRecv*)netEvent,frontServerPacket);
		//		GameNetPacketData* data = (GameNetPacketData*)(((NetEventRecv*)netEvent)->getData());
		//		client->getOperateManager()->onNetEvent(data->channel,data->type,data->data);
		//	}
		//	else if (netEvent->getType() == NET_CLOSE)
		//	{
		//		client->onFrontServerClose();
		//		client->getOperateManager()->onCloseByFrontServer();
		//	}

		//}
		//else if (client->getLoginServerNetId() == netEvent->getID())
		//{
		//	if (netEvent->getType() == NET_RECV)
		//	{
		//		ClientNetApplyManager::getInstance().processPacket(client,(NetEventRecv*)netEvent,loginServerPacket);
		//		GameNetPacketData* data = (GameNetPacketData*)(((NetEventRecv*)netEvent)->getData());
		//		client->getOperateManager()->onNetEvent(data->channel,data->type,data->data);
		//	}
		//	else if (netEvent->getType() == NET_CLOSE)
		//	{
		//		client->onLoginServerClose();
		//		client->getOperateManager()->onCloseByLoginServer();
		//	}
		//}
		//else
		//{
		//	// 未知网络包
		//	DYNAMIC_ASSERT(false);
		//}


    }

    //-----------------------------------------------------------------------------
    void ClientNetApplyManager::onRecv(NetEventRecv* netEvent)
    {

#ifdef ONE_THREAD
		I32 netId = netEvent->getID();
		U32 serverFlag = unknownServerPacket;
		ClientManager* clientManager =  &ClientManager::getInstance();
		//CClient* client = ClientManager::getInstance().getClientbyFrontServerId(netId);
		CClient* client = ThreadTaskManager::getInstance().getClientByFrontServerNetId(netId);
		if (!client)
		{
			//client = ClientManager::getInstance().getClientbyLoginServerId(netId);
			client = ThreadTaskManager::getInstance().getClientByLoginServerNetId(netId);
			serverFlag = loginServerPacket;
		}
		else
		{
			serverFlag = frontServerPacket;
		}

		if (client)
		{
			GameNetPacketData* data = (GameNetPacketData*)(netEvent->getData());

			processPacket(client,netEvent,serverFlag);
			
			if (data)
			{
				client->getOperateManager()->onNetEvent(data->channel,data->type,data->data);
			}
		}
		else
		{
			DYNAMIC_ASSERT(false);
		}
#else
		// 多线程处理
		//FUNDETECTION(__MG_FUNC__)
		I32 netId = netEvent->getID();
		CClient* client = ThreadTaskManager::getInstance().getClientByFrontServerNetId(netId);
		if (!client)
		{
			client = ThreadTaskManager::getInstance().getClientByLoginServerNetId(netId);
		}
		if (!client)
		{
			DYNAMIC_ASSERT(false);
			return;
		}
		ThreadTaskManager::getInstance().addRobotNetTask(client,netEvent);/**/
#endif

		//I32 netId = netEvent->getID();
		//CClient* client = ThreadTaskManager::getInstance().getClientByFrontServerNetId(netId);
		//if (!client)
		//{
		//	client = ThreadTaskManager::getInstance().getClientByLoginServerNetId(netId);
		//}
		//if (!client)
		//{
		//	// 内存池，多线程有误
		//	DYNAMIC_ASSERT(false);
		//	return;
		//}

		//if (client->getFrontServerNetId() == netEvent->getID())
		//{
		//	if (netEvent->getType() == NET_RECV)
		//	{	
		//		ClientNetApplyManager::getInstance().processPacket (client,(NetEventRecv*)netEvent,frontServerPacket);
		//		GameNetPacketData* data = (GameNetPacketData*)(((NetEventRecv*)netEvent)->getData());
		//		client->getOperateManager()->onNetEvent(data->channel,data->type,data->data);
		//	}
		//	else if (netEvent->getType() == NET_CLOSE)
		//	{
		//		client->onFrontServerClose();
		//		client->getOperateManager()->onCloseByFrontServer();
		//	}

		//}
		//else if (client->getLoginServerNetId() == netEvent->getID())
		//{
		//	if (netEvent->getType() == NET_RECV)
		//	{
		//		ClientNetApplyManager::getInstance().processPacket(client,(NetEventRecv*)netEvent,loginServerPacket);
		//		GameNetPacketData* data = (GameNetPacketData*)(((NetEventRecv*)netEvent)->getData());
		//		client->getOperateManager()->onNetEvent(data->channel,data->type,data->data);
		//	}
		//	else if (netEvent->getType() == NET_CLOSE)
		//	{
		//		client->onLoginServerClose();
		//		client->getOperateManager()->onCloseByLoginServer();
		//	}
		//}
		//else
		//{
		//	// 未知网络包
		//	DYNAMIC_ASSERT(false);
		//}
    }

    //-----------------------------------------------------------------------------
    void ClientNetApplyManager::onError(NetEventErr* netEvent)
    {

    }
	//-----------------------------------------------------------------------------
	void ClientNetApplyManager::processPacket( CClient* client,NetEventRecv* netEvent,U32 serverFlag)
	{
		GameNetPacketData* data = (GameNetPacketData*)(netEvent->getData());
		if (data)
		{
			
		}
		if (serverFlag == unknownServerPacket)
		{
			DYNAMIC_ASSERT(false);
		}
		else if (serverFlag == frontServerPacket)
		{
			if ( LoginNetPacketProcesser::getInstance().processFrontServerPacket(client,netEvent) == true )
			{
				return;
			}
			if ( RegionNetPacketProcesser::getInstance().processFrontServerPacket(client, netEvent) == true)
			{
				return;
			}	
			if (PlayerNetPacketProcesser::getInstance().processFrontServerPacket(client, netEvent) == true)
			{
				return;
			}
			if ( PlayCharacterNetPacketProcesser::getInstance().processFrontServerPacket(client,netEvent) == true)
			{
				return;
			}	
			if (TestNetPacketProcesser::getInstance().processFrontServerPacket(client,netEvent) == true)
			{
				return;
			}			
			if(PackNetPacketProcesser::getInstance().processFrontServerPacket(client,netEvent) == true)
			{
				return;
			}
			if (TroopNetPacketProcesser::getInstance().processFrontServerPacket(client,netEvent) == true)
			{
				return;
			}	
			if (CampaignNetPacketProcesser::getInstance().processFrontServerPacket(client,netEvent) == true) 
			{
				return;
			}				
			
		}
		else if (serverFlag == loginServerPacket)
		{
			
			if ( LoginNetPacketProcesser::getInstance().processLoginServerPacket(client,netEvent) == true )
			{
				return;
			}
			if (TestNetPacketProcesser::getInstance().processLoginServerPacket(client,netEvent) == true)
			{
				return;
			}
		}

	}
}


