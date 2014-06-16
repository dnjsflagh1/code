/******************************************************************************/
#include "stdafx.h"
#include "ServerManager.h"
#include "DbServerMain.h"
//#include "ClientManager.h"
//#include "LoginNetPacketProcesser.h"
//#include "LoginNetPacketProcesser.h"
//#include "ChatNetPacketProcesser.h"
/******************************************************************************/
namespace MG
{

	//-----------------------------------------------------------------------------
	ServerManager::ServerManager()
		:mMaxMapServerNum(0)
		,mSysLogServerNetId(-1)
		,mLoginServerNetId(-1)
	{

	}

	//-----------------------------------------------------------------------------
	ServerManager::~ServerManager()
	{

	}

	//-----------------------------------------------------------------------
	Bool ServerManager::initialize(SServerSetting* setting)
	{
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
		if (type == GNT_MAP_SERVER)
		{
			ServerInfo* server = MG_NEW ServerInfo;
			server->netId = id;
			server->serverUniqueFlag = serverUniqueFlag;
			server->serverId = serverId;
			addMapServer(server);
			//syncMapServersStateToAllServer();
		}
		else if (type == GNT_FRONT_SERVER)
		{
			ServerInfo* server = MG_NEW ServerInfo;
			server->netId = id;
			server->serverUniqueFlag = serverUniqueFlag;
			server->serverId = serverId;
			addFrontServer(server);
			//syncMapServersStateToAllServer();
		}
		else if ( type == GNT_SYSLOG_SERVER )
		{
			DYNAMIC_ASSERT( mSysLogServerNetId == -1 );

			mSysLogServerNetId = id;
		}
		else if( type = GNT_LOGIN_SERVER)
		{
			DYNAMIC_ASSERT( GNT_LOGIN_SERVER == -1 );
			mLoginServerNetId = serverId;
		}
	}

	//-----------------------------------------------------------------------------
	void ServerManager::onDisconnect(I32 id)
	{
		
		if (getFrontServer(id))
		{
			removeFrontServer(id);
		}
		else if (getMapServer(id))
		{
			removeMapServer(id);
		}
		else if ( id == mSysLogServerNetId )
		{
			mSysLogServerNetId = -1;
		}
		else if (id == mLoginServerNetId)
		{
			mLoginServerNetId = -1;
		}
	}

	//-----------------------------------------------------------------------------
	Bool ServerManager::processPacket(I32 id, NetEventRecv* packet)
	{
		//根据ID分派不同的服务器消息
		if (id == mLoginServerNetId)
		{
		}
		else if (getFrontServer(id))
		{
			//if (ChatNetPacketProcesser::getInstance().processFrontPacket(id,packet))
			//	return true;
			//if (LoginNetPacketProcesser::getInstance().processFrontPacket(id,packet))
			//	return true;
		}
		else if (getMapServer(id))
		{
			return true;
		}
		return false;
	}

	//-----------------------------------------------------------------------------
	ServerInfo* ServerManager::getFrontServer(I32 netId)
	{
		ServerInfo * server = NULL;
		std::list< ServerInfo* >::iterator it = mFrontServerList.begin();
		for (; it != mFrontServerList.end(); it++)
		{
			if ((*it) != NULL && (*it)->netId == netId)
			{
				server = (*it);
			}
		}
		return server;
	}

	//-----------------------------------------------------------------------------
	void ServerManager::addFrontServer(ServerInfo* serverinfo)
	{
		FrontServerListContainer::iterator iter = mFrontServerList.begin();
		for (; iter != mFrontServerList.end(); ++iter)
		{
			if ((*iter)->serverUniqueFlag >= serverinfo->serverUniqueFlag)
			{
				break;
			}
		}

		mFrontServerList.insert(iter, serverinfo);
	}

	//-----------------------------------------------------------------------------
	void ServerManager::removeFrontServer(I32 netId)
	{
		if (mFrontServerList.empty())
		{
			return;
		}
		std::list< ServerInfo* >::iterator it = mFrontServerList.begin();
		for (; it != mFrontServerList.end(); it++)
		{
			if ((*it) != NULL && (*it)->netId == netId)
			{
				MG_SAFE_DELETE(*it); 
				mFrontServerList.erase(it);
				return;
			}
		}
	}
	//-----------------------------------------------------------------------------
	ServerInfo* ServerManager::getMapServer( I32 netId )
	{
		ServerInfo * server = NULL;
		std::vector< ServerInfo* >::iterator it = mMapServerList.begin();
		for (; it != mMapServerList.end(); it++)
		{
			if ((*it) != NULL && (*it)->netId == netId)
			{
				server = (*it);
				break;
			}
		}
		return server;
	}
	//-----------------------------------------------------------------------------
	void ServerManager::addMapServer( ServerInfo* serverinfo )
	{
		std::vector< ServerInfo* >::iterator iter = mMapServerList.begin();
		for (; iter != mMapServerList.end(); ++iter)
		{
			if ((*iter)->serverUniqueFlag >= serverinfo->serverUniqueFlag)
			{
				break;
			}
		}

		mMapServerList.insert(iter, serverinfo);
	}
	//-----------------------------------------------------------------------------
	void ServerManager::removeMapServer( I32 netId )
	{
		if (mMapServerList.empty())
		{
			return;
		}
		std::vector< ServerInfo* >::iterator it = mMapServerList.begin();
		for (; it != mMapServerList.end(); it++)
		{
			if ((*it) != NULL && (*it)->netId == netId)
			{
				ServerInfo* server = *it;
				MG_SAFE_DELETE(server); 
				mMapServerList.erase(it);
				break;
			}
		}
	}
	//-----------------------------------------------------------------------------
	void ServerManager::boardcastNetPacketToServers( NetSendDataBufferPtr packetPtr ,I32 dataSize )

	{
		{
			std::vector<ServerInfo* >::iterator iter = mMapServerList.begin();
			for (; iter != mMapServerList.end(); iter++)
			{
				I32 netID = (*iter)->netId;
				packetPtr->send( dataSize, netID );
			}
		}


		{
			std::list<ServerInfo* >::iterator iterFront = mFrontServerList.begin();
			for (; iterFront != mFrontServerList.end(); iterFront++)
			{
				I32 netID = (*iterFront)->netId;
				packetPtr->send( dataSize, netID );
			}
		}

	}

	//-----------------------------------------------------------------------------
	void ServerManager::sendNetPacketToMapServer(NetIdType mapServerId, NetSendDataBufferPtr packetPtr ,I32 dataSize)
	{
		std::vector<ServerInfo* >::iterator iter = mMapServerList.begin();
		for (; iter != mMapServerList.end(); iter++)
		{
			I32 netID = (*iter)->netId;
			if (netID == mapServerId)
			{
				packetPtr->send( dataSize, netID );
				continue;
			}
		}
	}

	//-----------------------------------------------------------------------------
	void ServerManager::sendNetPacketToFrontServer(NetIdType frontServerId, NetSendDataBufferPtr packetPtr ,I32 dataSize)
	{
		std::list< ServerInfo* >::iterator iter = mFrontServerList.begin();
		for (; iter != mFrontServerList.end(); iter++)
		{
			I32 netID = (*iter)->netId;
			if (netID == frontServerId)
			{
				packetPtr->send( dataSize, netID );
				continue;
			}
		}
	}
}
