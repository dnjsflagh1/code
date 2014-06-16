/******************************************************************************/
#include "stdafx.h"
#include "ServerManager.h"
#include "ChatServerMain.h"
//#include "ClientManager.h"
//#include "LoginNetPacketProcesser.h"
#include "LoginNetPacketProcesser.h"
#include "ChatNetPacketProcesser.h"
/******************************************************************************/
namespace MG
{

	//-----------------------------------------------------------------------------
	ServerManager::ServerManager()
		:mMaxMapServerNum(0)
		,mSysLogServerNetID(-1)
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
			DYNAMIC_ASSERT( mSysLogServerNetID == -1 );

			mSysLogServerNetID = id;
		}
	}

	//-----------------------------------------------------------------------------
	void ServerManager::onDisconnect(I32 id)
	{
		
		if (getFrontServer(id))
		{
			ClientManager::getInstance().removeClientByFrontServerNetId(id);
			removeFrontServer(id);
		}
		else if (getMapServer(id))
		{
			removeMapServer(id);
		}
		else if ( id == mSysLogServerNetID )
			mSysLogServerNetID = -1;
	}

	//-----------------------------------------------------------------------------
	Bool ServerManager::processPacket(I32 id, NetEventRecv* packet)
	{
		//根据ID分派不同的服务器消息
		if (getFrontServer(id))
		{
			if (ChatNetPacketProcesser::getInstance().processFrontPacket(id,packet))
				return true;
			if (LoginNetPacketProcesser::getInstance().processFrontPacket(id,packet))
				return true;
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
	void ServerManager::boardcastNetPacketToServers( GameNetSendDataBufferPtr packetPtr ,I32 dataSize )

	{
		{
			std::vector<ServerInfo* >::iterator iter = mMapServerList.begin();
			for (; iter != mMapServerList.end(); iter++)
			{
				I32 netID = (*iter)->netId;
				// 发送数据
				ChatServerMain::getInstance().getServerLauncher()->sendServer(packetPtr,dataSize,netID);
			}
		}


		{
			std::list<ServerInfo* >::iterator iterFront = mFrontServerList.begin();
			for (; iterFront != mFrontServerList.end(); iterFront++)
			{
				I32 netID = (*iterFront)->netId;
				// 发送数据
				ChatServerMain::getInstance().getServerLauncher()->sendServer(packetPtr,dataSize,netID);
			}
		}

	}

	//-----------------------------------------------------------------------------
	void ServerManager::sendNetPacketToMapServer(NetIdType mapServerId, GameNetSendDataBufferPtr packetPtr ,I32 dataSize)
	{
		std::vector<ServerInfo* >::iterator iter = mMapServerList.begin();
		for (; iter != mMapServerList.end(); iter++)
		{
			I32 netID = (*iter)->netId;
			if (netID == mapServerId)
			{
				// 发送数据
				ChatServerMain::getInstance().getServerLauncher()->sendServer(packetPtr,dataSize,netID);
				continue;
			}
		}
	}

	//-----------------------------------------------------------------------------
	void ServerManager::sendNetPacketToFrontServer(NetIdType frontServerId, GameNetSendDataBufferPtr packetPtr ,I32 dataSize)
	{
		std::list< ServerInfo* >::iterator iter = mFrontServerList.begin();
		for (; iter != mFrontServerList.end(); iter++)
		{
			I32 netID = (*iter)->netId;
			if (netID == frontServerId)
			{
				// 发送数据
				ChatServerMain::getInstance().getServerLauncher()->sendServer(packetPtr,dataSize,netID);
				continue;
			}
		}
	}

}
