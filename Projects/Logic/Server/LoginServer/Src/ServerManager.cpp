/******************************************************************************/
#include "stdafx.h"
#include "ClientManager.h"
#include "ServerManager.h"
#include "LoginNetPacketProcesser.h"
#include "LoginServerMain.h"
/******************************************************************************/
namespace MG
{
	//-----------------------------------------------------------------------
	ServerManager::ServerManager()
        :mSysLogServerNetID(-1)
	{
	}

	//-----------------------------------------------------------------------
	ServerManager::~ServerManager()
	{
	}

	//-----------------------------------------------------------------------
	Bool ServerManager::initialize()
	{
		return true;
	}

	//-----------------------------------------------------------------------
	void ServerManager::uninitialize()
	{
	}

	//-----------------------------------------------------------------------
	void ServerManager::update()
	{

	}	

	//-----------------------------------------------------------------------
	void ServerManager::onConnected(I32 id,GameNetType type,U32 serverId,U64 serverUniqueFlag, NetAddress*address)
	{
        switch ( type )
        {
        case  GNT_FRONT_SERVER:
            addFrontServer(id, address->getIPStr(), address->getPort());
            break;
        case GNT_SYSLOG_SERVER:
            setSysLogServerNetID(id);
            break;
        }
	}

	//-----------------------------------------------------------------------
	void ServerManager::onDisconnect(I32 id)
	{
		LoginManager::getInstance().handleFrontServerDisconnect( id );
        removeFrontServer(id);
        if ( id == mSysLogServerNetID )
            setSysLogServerNetID(-1);
	}

	//-----------------------------------------------------------------------
	Bool ServerManager::processPacket(I32 id, NetEventRecv* packet)
	{
		DYNAMIC_ASSERT(packet);
		if (!packet)
			return false;
		
        if ( getFrontServer( id ) != NULL )
        {
            if ( LoginNetPacketProcesser::getInstance().processFrontServerPacket( id, packet ) == true )
                return true;
        }

		return false;
	}

    //-----------------------------------------------------------------------
    FrontServerInfo* ServerManager::getFrontServer(I32 netId)
    {
        FrontServerInfo* result = NULL;
        std::map< I32, FrontServerInfo >::iterator iter = mFrontServerList.find( netId );
        if ( iter != mFrontServerList.end() )
        {
            result = &iter->second; 
        }
        return result;
    }

    //-----------------------------------------------------------------------
    void ServerManager::addFrontServer(I32 netId)
    {
        FrontServerInfo& frontSvr = mFrontServerList[netId];
        frontSvr.isValid = false;
    }

	//-----------------------------------------------------------------------
	void ServerManager::addFrontServer(I32 netId, CChar*	ip, I32 port)
	{
		FrontServerInfo& frontSvr = mFrontServerList[netId];
		frontSvr.netId = netId;
		frontSvr.listenClientIp = ip;
		frontSvr.listenClientPort = port;
        frontSvr.isValid = true;
	}

	//-----------------------------------------------------------------------
	void ServerManager::removeFrontServer(I32 netId)
	{
		std::map< I32, FrontServerInfo >::iterator iter = mFrontServerList.find( netId );
		if ( iter != mFrontServerList.end() )
		{
			mFrontServerList.erase(iter);
		}
	}

	//-----------------------------------------------------------------------
	FrontServerInfo* ServerManager::allocClientConnect()
	{
        //分配策略，找出连接数最小的frontServer给客户端。
		FrontServerInfo* frontSvr = NULL;
		std::map< I32, FrontServerInfo >::iterator iter = mFrontServerList.begin( );
		std::map< I32, FrontServerInfo >::iterator end_iter = mFrontServerList.end( );
		for ( ;iter != end_iter; iter++ )
		{
            if ( iter->second.isValid == true )
            {
                if (frontSvr==NULL)
                {
                    frontSvr = &(iter->second);
                }else
                {
                    if ( iter->second.clientNum < frontSvr->clientNum )
                    {
                        frontSvr = &(iter->second);
                    }
                }
            }
		}
		if (frontSvr)
		{
			frontSvr->clientNum++;
		}

		return frontSvr;
	}

	//-----------------------------------------------------------------------
	void ServerManager::freeClientConnect(I32 netId)
	{
		FrontServerInfo* frontSvr = getFrontServer(netId);
		if ( frontSvr )
		{
			if ( frontSvr->clientNum > 0 )
				frontSvr->clientNum --;
		}
	}
    //-----------------------------------------------------------------------
    void ServerManager::setSysLogServerNetID( I32 netID )
    {
        mSysLogServerNetID = netID;
    }
}
