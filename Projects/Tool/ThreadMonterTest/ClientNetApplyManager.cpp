/******************************************************************************/
#include "stdafx.h"
#include "ClientNetApplyManager.h"
#include "NetAddress.h"


/******************************************************************************/
using namespace MG;
namespace MG
{

	/*InterLocked netId[MAX_CONNECT];
	Critical connectLock;
	std::map<I32,Int> connectIndexs;*/
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
			5000,
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
		config.OnceHandlePacketCount        = -1;
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
		I32 res = GameNetPacketManager::unInitialize();

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
		GameNetSendDataBufferPtr netBuffPtr;
		GameNetPacketManager::getGameNetSendDataBufferPtr(netBuffPtr, mNetDriver, buffSize );
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
		/*for (Int i = 0; i < 2000; i++)
		{
			if (netId[i] == netEvent->getID())
			{
				netId[i] = -1;
			}
		}*/

		/*connectLock.lock();
		std::map<I32,Int>::iterator it = connectIndexs.find(netEvent->getID());
		if (it != connectIndexs.end())
		{
			netId[it->second] = -1;
			connectIndexs.erase(it);
		}
		connectLock.unlock();*/
    }

    //-----------------------------------------------------------------------------
    void ClientNetApplyManager::onRecv(NetEventRecv* netEvent)
    {


    }

    //-----------------------------------------------------------------------------
    void ClientNetApplyManager::onError(NetEventErr* netEvent)
    {

    }
}


