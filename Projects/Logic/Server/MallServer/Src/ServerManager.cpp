/******************************************************************************/
#include "stdafx.h"
#include "ServerManager.h"
#include "MallServerMain.h"
#include "ServerNetPacketProcesser.h"
/******************************************************************************/

/******************************************************************************/
namespace MG
{

	//-----------------------------------------------------------------------------
	ServerManager::ServerManager()
	{

	}

	//-----------------------------------------------------------------------------
	ServerManager::~ServerManager()
	{

	}

	//-----------------------------------------------------------------------
	Bool ServerManager::initialize(SServerSetting* setting)
	{
		//FUNDETECTION(__MG_FUNC__);
		DYNAMIC_ASSERT(setting);
		if (setting)
		{
			//mServerSetting = setting;
		}
		return true;
	}

	//-----------------------------------------------------------------------
	void ServerManager::uninitialize()
	{
		//FUNDETECTION(__MG_FUNC__);
	}


	//-----------------------------------------------------------------------------
	void ServerManager::onConnected(I32 id,GameNetType type, U32 serverId, U64 serverUniqueFlag, NetAddress*address)
	{
		ServerInfo* server = MG_NEW ServerInfo;
        server->type = type;
		server->netId = id;
		server->serverUniqueFlag = serverUniqueFlag;

        if ( getServerInfo(id) == NULL )
		    addServerInfo(server);
	}

	//-----------------------------------------------------------------------------
	void ServerManager::onDisconnect(I32 id)
	{
		removeServerInfo(id);
	}

	//-----------------------------------------------------------------------------
	Bool ServerManager::processPacket(I32 id, NetEventRecv* packet)
	{
		//根据ID分派不同的服务器消息

        //ServerNetPacketProcesser::getInstance().

		return false;
	}

	//-----------------------------------------------------------------------------
	ServerInfo* ServerManager::getServerInfo(I32 netId)
	{
        std::list< ServerInfo* >::iterator front = mServerList.begin();
        std::list< ServerInfo* >::iterator back = mServerList.end();
        while (front != back)
        {
            if ( (*front)->netId == netId )
                return (*front);

            ++front;
        }

        return NULL;
	}
	//-----------------------------------------------------------------------------
	void ServerManager::addServerInfo(ServerInfo* serverinfo)
	{
        mServerList.push_back(serverinfo);
	}

	//-----------------------------------------------------------------------------
	void ServerManager::removeServerInfo(I32 netId)
	{
        std::list< ServerInfo* >::iterator front = mServerList.begin();
        std::list< ServerInfo* >::iterator back = mServerList.end();
        while (front != back)
        {
            if ( (*front)->netId == netId )
            { 
                mServerList.erase(front);
                break;
            }

            ++front;
        }
	}
    //-----------------------------------------------------------------------------
    void ServerManager::boardcastNetPacketToServers( GameNetSendDataBufferPtr packetPtr, I32 dataSize, GameNetType type )
    {
        std::list< ServerInfo* >::iterator front = mServerList.begin();
        std::list< ServerInfo* >::iterator back = mServerList.end();
        while (front != back)
        {
            if ( (*front)->type == type )
            {
                MallServerMain::getInstance().getServerLauncher()->sendServer( packetPtr, dataSize, (*front)->netId );
            }
        }
        
    }
}