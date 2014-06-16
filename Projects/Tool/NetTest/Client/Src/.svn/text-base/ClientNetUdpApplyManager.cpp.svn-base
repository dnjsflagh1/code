/******************************************************************************/
#include "stdafx.h"
#include "ClientNetUdpApplyManager.h"
#include "NetDefine.h"
/******************************************************************************/

namespace MG
{

	//-----------------------------------------------------------------------------
    ClientNetUdpApplyManager::ClientNetUdpApplyManager()
		:mNetDriver(-1)
    {
        
    }
    
    //-----------------------------------------------------------------------------
    ClientNetUdpApplyManager::~ClientNetUdpApplyManager()
    {

    }

    //-----------------------------------------------------------------------------
    Bool ClientNetUdpApplyManager::initialize()
    {
        if ( NetUdpManager::initialize(UDP_SECTION_PACKET_DEFAULT_SIZE) == false )
            return false;
        
        revertOnceHandlePacketCountByDrive();

		mNetDriver = createDriver( "Client", 4, false, true, 
                                    UDP_LOGIC_PACK_MIN_SIZE,
                                    UDP_LOGIC_PACK_MAX_SIZE);
		if ( mNetDriver < 0 )
		{
			return false;
		}

        this->setOnceHandlePacketCountByDriver( mNetDriver, -1 );

		configLocalSockets(mNetDriver,NULL,100);
        return true;
    }

    //-----------------------------------------------------------------------------
    I32 ClientNetUdpApplyManager::update()
    {
		FUNDETECTION(__MG_FUNC__);
        I32 res = GameNetUdpPacketManager::update();
        
        return res;
    }

    //-----------------------------------------------------------------------------
    I32 ClientNetUdpApplyManager::unInitialize()
    {
        I32 res = NetUdpManager::unInitialize();

        return res;
    }

    //-----------------------------------------------------------------------------
    Bool ClientNetUdpApplyManager::connectLoginServer( NetAddress& addr )
    {
        this->connect(mNetDriver, &addr,0);
		return true;
    }

    //-----------------------------------------------------------------------------
    Bool ClientNetUdpApplyManager::disconnectLoginServer()
    {
        return true;
    }

    //-----------------------------------------------------------------------------
    Bool ClientNetUdpApplyManager::connectFrontServer( NetAddress& addr )
    {
		return true;
    }

    //-----------------------------------------------------------------------------
    Bool ClientNetUdpApplyManager::disconnectFrontServer()
    {

		return true;
    }

    //-----------------------------------------------------------------------------
    Bool ClientNetUdpApplyManager::disconnectServers()
    {
        Bool res = true;

        if ( disconnectLoginServer() == false )
            res = false;
        if ( disconnectFrontServer() == false )
            res = false;

        return res;
    }
    //-----------------------------------------------------------------------------
    void ClientNetUdpApplyManager::onAccept(NetUdpEventAccept* netEvent)
    {
        
    }

    //-----------------------------------------------------------------------------
    void ClientNetUdpApplyManager::onConnected(NetUdpEventConnect* netEvent)
    {
		
    }

    //-----------------------------------------------------------------------------
    void ClientNetUdpApplyManager::onClose(NetUdpEventClose* netEvent)
    {
        
    }

    //-----------------------------------------------------------------------------
    void ClientNetUdpApplyManager::onRecv(NetUdpEventRecv* netEvent)
    {
       
    }

    //-----------------------------------------------------------------------------
    void ClientNetUdpApplyManager::onError(NetUdpEventErr* netEvent)
    {

    }

	LogicSendPacket* ClientNetUdpApplyManager::getLogicSendPacket( I32 handle,Byte channel,Byte type, U32 logicDataSize,Char8* data )
	{
		return NetUdpManager::getLogicSendPacket( handle, channel, type, NetUdpManager::getSectionPacketSize(),  logicDataSize, data);
	}
}


