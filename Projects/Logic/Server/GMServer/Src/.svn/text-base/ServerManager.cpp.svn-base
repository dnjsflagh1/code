/******************************************************************************/
#include "stdafx.h"
#include "ServerManager.h"
/******************************************************************************/
namespace MG
{
	//-----------------------------------------------------------------------------
	ServerManager::ServerManager()
		:mSysLogServerNetId(-1)
		,mChatServerNetId(-1)
		,mCenterServerNetId(-1)

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
		}
		else if (type == GNT_FRONT_SERVER)
		{
			ServerInfo* server = MG_NEW ServerInfo;
			server->netId = id;
			server->serverUniqueFlag = serverUniqueFlag;
			server->serverId = serverId;
			addFrontServer(server);
		}
		else if ( type == GNT_SYSLOG_SERVER )
		{
			DYNAMIC_ASSERT( mSysLogServerNetId == -1 );

			mSysLogServerNetId = id;
		}
		else if (type == GNT_CHAT_SERVER)
		{
			DYNAMIC_ASSERT( mChatServerNetId == -1 );

			mChatServerNetId = id;
		}
		else if (type == GNT_CENTER_SERVER)
		{
			DYNAMIC_ASSERT( mCenterServerNetId == -1 );

			mCenterServerNetId = id;
		}
	}

	//-----------------------------------------------------------------------------
	void ServerManager::onDisconnect(I32 id)
	{
		
		if (getFrontServer(id))
		{
			//ClientManager::getInstance().removeClientByFrontServerNetId(id);
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
		else if ( id == mChatServerNetId )
		{
			mChatServerNetId = -1;
		}
		else if ( id == mCenterServerNetId )
		{
			mCenterServerNetId = -1;
		}
			
	}

	//-----------------------------------------------------------------------------
	Bool ServerManager::processPacket(I32 id, NetEventRecv* packet)
	{
		//根据ID分派不同的服务器消息
		if (id == mCenterServerNetId)
		{
			return true;
		}
		else if (id == mSysLogServerNetId)
		{
			return true;
		}
		else if (id == mChatServerNetId)
		{
			return true;
		}
		if (getFrontServer(id))
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
		return server;
	}

	//-----------------------------------------------------------------------------
	void ServerManager::addFrontServer(ServerInfo* serverinfo)
	{

	}

	//-----------------------------------------------------------------------------
	void ServerManager::removeFrontServer(I32 netId)
	{
		
	}
	//-----------------------------------------------------------------------------
	ServerInfo* ServerManager::getMapServer( I32 netId )
	{
		ServerInfo * server = NULL;
		return server;
	}
	//-----------------------------------------------------------------------------
	void ServerManager::addMapServer( ServerInfo* serverinfo )
	{
	}
	//-----------------------------------------------------------------------------
	void ServerManager::removeMapServer( I32 netId )
	{

	}
	//-----------------------------------------------------------------------------
	void ServerManager::boardcastNetPacketToServers( GameNetSendDataBufferPtr packetPtr ,I32 dataSize )
	{

	}
	//-----------------------------------------------------------------------------
	void ServerManager::boardcastNetPacketToMapServers( Byte channel,Byte type,Char8* data,I32 dataSize,U64 code )
	{
	
	}
	//-----------------------------------------------------------------------------
	void ServerManager::boardcastNetPacketToFrontServers( Byte channel,Byte type,Char8* data,I32 dataSize,U64 code )
	{

	}
	//-----------------------------------------------------------------------------
	void ServerManager::sendNetPacketToServer(NetIdType serverNetId, GameNetSendDataBufferPtr packetPtr ,I32 dataSize)
	{

	}
}
