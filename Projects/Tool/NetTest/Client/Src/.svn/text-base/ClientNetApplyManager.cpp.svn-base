/******************************************************************************/
#include "stdafx.h"
#include "ClientNetApplyManager.h"
#include "NetAddress.h"
/******************************************************************************/

namespace MG
{

	//-----------------------------------------------------------------------------
    ClientNetApplyManager::ClientNetApplyManager()
        :mLoginServerID(-1),
        mFrontServerID(-1),
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
        
        revertOnceHandlePacketCountByDrive();

		mNetDriver = createDriver( "Client", 4, false, true, 
                                    MG_GAME_NET_PACKET_NORMAL_MAX_SIZE,
                                    MG_GAME_NET_PACKET_NORMAL_MAX_SIZE,
                                    MG_NET_BUFFER_SIZE_CLIENT);
		if ( mNetDriver < 0 )
		{
			return false;
		}

        this->setOnceHandlePacketCountByDriver( mNetDriver, -1 );

        return true;
    }

    //-----------------------------------------------------------------------------
    I32 ClientNetApplyManager::update()
    {
		FUNDETECTION(__MG_FUNC__);
        I32 res = GameNetPacketManager::update();
        
        return res;
    }

    //-----------------------------------------------------------------------------
    I32 ClientNetApplyManager::unInitialize()
    {
        I32 res = NetManager::unInitialize();

        return res;
    }

    //-----------------------------------------------------------------------------
    Bool ClientNetApplyManager::connectLoginServer( NetAddress& addr )
    {
        disconnectLoginServer();

        mLoginServerID = this->connect(mNetDriver, &addr);
		if ( mLoginServerID < 0 )
		{
			return false;
		}
		return true;
    }

    //-----------------------------------------------------------------------------
    Bool ClientNetApplyManager::disconnectLoginServer()
    {
        if ( mLoginServerID >= 0 )
        {
            close(mNetDriver,mLoginServerID);
            mLoginServerID = -1;
        }
        return true;
    }

    //-----------------------------------------------------------------------------
    Bool ClientNetApplyManager::connectFrontServer( NetAddress& addr )
    {
        disconnectFrontServer();

        mFrontServerID = this->connect(mNetDriver, &addr);
        if ( mFrontServerID < 0 )
        {
            return false;
        }
        return true;
    }

    //-----------------------------------------------------------------------------
    Bool ClientNetApplyManager::disconnectFrontServer()
    {
		if ( mFrontServerID >= 0 )
		{
			close(mNetDriver,mFrontServerID);
            mFrontServerID = -1;
		}
		return true;
    }

    //-----------------------------------------------------------------------------
    Bool ClientNetApplyManager::disconnectServers()
    {
        Bool res = true;

        if ( disconnectLoginServer() == false )
            res = false;
        if ( disconnectFrontServer() == false )
            res = false;

        return res;
    }
	
    //-----------------------------------------------------------------------------
    NetSendDataBufferPtr ClientNetApplyManager::getSendDataBuffer( U32 buffSize  )
    {
        return NetManager::getSendDataBuffer( mNetDriver, buffSize );
    }

    //-----------------------------------------------------------------------------
    void ClientNetApplyManager::sendLoginServerPacket( NetSendDataBufferPtr& data, Int dataSize )
    {
        if ( mLoginServerID >= 0 )
        {
            data->send( dataSize, mLoginServerID );
        }
    }

    //-----------------------------------------------------------------------------
    void ClientNetApplyManager::sendFrontServerPacket( NetSendDataBufferPtr& data, Int dataSize )
    {
        if ( mFrontServerID >= 0 )
        {
            data->send( dataSize, mFrontServerID );
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


