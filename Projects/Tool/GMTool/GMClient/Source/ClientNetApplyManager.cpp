/******************************************************************************/
#include "stdafx.h"
#include "ClientNetApplyManager.h"
#include "NetAddress.h"
#include "GMAccountOpNetPacketProcesser.h"
/******************************************************************************/

namespace MG
{

	//-----------------------------------------------------------------------------
    ClientNetApplyManager::ClientNetApplyManager()
        :mGMServerManagerId(-1),
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

		mNetDriver = createDriver( "Client", 
                                    4, 
                                    false,
                                    MG_NET_CLIENT_TIMEOUT_TOUCH_TIME,
                                    MG_NET_CLIENT_TIMEOUT_DURATION,
                                    true, 
                                    MG_GAME_NET_PACKET_NORMAL_MAX_SIZE,
                                    MG_GAME_NET_PACKET_NORMAL_MAX_SIZE,
                                    MG_NET_BUFFER_SIZE_CLIENT,
									MG_NET_MAX_CLIENT_SOCKET_SENDBUFF_SIZE,
									MG_NET_MAX_CLIENT_SOCKET_RECVBUFF_SIZE,
									DRIVER_TYPE_SERVER);
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
    Bool ClientNetApplyManager::connectGMServerManager( NetAddress& addr )
    {
        disconnectGMServerManager();
        mGMServerManagerId = this->connect(mNetDriver, &addr);
		if ( mGMServerManagerId < 0 )
		{
			return false;
		}
		return true;
    }

    //-----------------------------------------------------------------------------
    Bool ClientNetApplyManager::disconnectGMServerManager()
    {
        if ( mGMServerManagerId >= 0 )
        {
            close(mNetDriver,mGMServerManagerId);
            mGMServerManagerId = -1;
        }
        return true;
	}

    //-----------------------------------------------------------------------------
    NetSendDataBufferPtr ClientNetApplyManager::getSendDataBuffer( U32 buffSize  )
    {
        return NetManager::getSendDataBuffer( mNetDriver, buffSize );
    }

    //-----------------------------------------------------------------------------
    void ClientNetApplyManager::sendPacket( NetSendDataBufferPtr& data, Int dataSize )
    {
        if ( mGMServerManagerId >= 0 )
        {
            data->send( dataSize, mGMServerManagerId );
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
        if ( netEvent->getID() == mGMServerManagerId )
        {
			//如果是被动断开连接的
			if ( netEvent->isPassivity() == true )
			{
				//弹出连接断开提示
			}
        }
		else
        {
            DYNAMIC_ASSERT_LOG(false,"与服务器断开连接");
        }
    }

    //-----------------------------------------------------------------------------
    void ClientNetApplyManager::onRecv(NetEventRecv* netEvent)
    {
        if ( netEvent->getID() == mGMServerManagerId )
        {
			if (GMAccountOpNetPacketProcesser::getInstance().processGMServerManagerPacket(mGMServerManagerId,netEvent))
			{
				return;
			}
			
        }
		else
        {
           	 DYNAMIC_ASSERT_LOG(false,"网络连接异常");
        }
    }

    //-----------------------------------------------------------------------------
    void ClientNetApplyManager::onError(NetEventErr* netEvent)
    {

    }
	//-----------------------------------------------------------------------------
	void ClientNetApplyManager::closeNet()
	{
		close(mNetDriver,mGMServerManagerId);
	}
}


