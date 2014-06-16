
/******************************************************************************/

#include "stdafx.h"
#include "ServerManager.h"
#include "CenterServerMain.h"
#include "ServerStateNetPacketProcesser.h"
#include "SWorldManager.h"
#include "SCampaignNetPacketProcesser.h"
#include "SPveNetPacketProcesser.h"

/******************************************************************************/

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
	void ServerManager::onConnected(I32 id,GameNetType type, U32 serverId,U64 serverUniqueFlag, NetAddress*address)
	{
		if (type == GNT_MAP_SERVER)
		{
			ServerInfo* server = MG_NEW ServerInfo;
			server->netId = id;
			server->serverUniqueFlag = serverUniqueFlag;
			addMapServer(server);
			//syncMapServersStateToAllServer();
			syncMapServersStateToAllServerNewByLinhu();
		}
		else if (type == GNT_FRONT_SERVER)
		{
			ServerInfo* server = MG_NEW ServerInfo;
			server->netId = id;
			server->serverUniqueFlag = serverUniqueFlag;
			addFrontServer(server);
			//syncMapServersStateToAllServer();
			syncMapServersStateToAllServerNewByLinhu();
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
		removeMapServer(id);
		removeFrontServer(id);
        if ( id == mSysLogServerNetID )
            mSysLogServerNetID = -1;
		//syncMapServersStateToAllServer();
	}

	//-----------------------------------------------------------------------------
	Bool ServerManager::processPacket(I32 id, NetEventRecv* packet)
	{
		//根据ID分派不同的服务器消息
		if (SCampaignNetPacketProcesser::getInstance().processFrontServerPacket(id, packet) == true)
			return true;
		if (SPveNetPacketProcesser::getInstance().processFrontServerPacket(id, packet) == true)
			return true;
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
	ServerInfo* ServerManager::getFrontServerByIndex(I32 index)
	{
		Int curIndex = 0;
		ServerInfo * server = NULL;
		std::list< ServerInfo* >::iterator it = mFrontServerList.begin();
		for (; it != mFrontServerList.end(); it++, curIndex)
		{
			if ((*it) != NULL && curIndex == index)
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

		SPveNetPacketProcesser::getInstance().processFrontServerDisconnect(netId);
		
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
	void ServerManager::boardcastToFrontServers(GameNetSendDataBufferPtr& packetPtr ,I32 dataSize)
	{
		std::list<ServerInfo* >::iterator iterFront = mFrontServerList.begin();
		for (; iterFront != mFrontServerList.end(); iterFront++)
		{
			I32 netID = (*iterFront)->netId;
			CenterServerMain::getInstance().getServerLauncher()->sendServer(packetPtr, dataSize, netID);
			//packetPtr->send( dataSize, netID );
		}
	}

	//-----------------------------------------------------------------------------
	void ServerManager::boardcastToMapServers(GameNetSendDataBufferPtr& packetPtr ,I32 dataSize)
	{
		std::vector<ServerInfo* >::iterator iter = mMapServerList.begin();
		for (; iter != mMapServerList.end(); iter++)
		{
			I32 netID = (*iter)->netId;

			CenterServerMain::getInstance().getServerLauncher()->sendServer(
				packetPtr,
				dataSize,
				netID );
		}
	}
	//-----------------------------------------------------------------------------
	void ServerManager::boardcastNetPacketToServers( GameNetSendDataBufferPtr& packetPtr ,I32 dataSize )
	{
		boardcastToMapServers(packetPtr, dataSize);
		boardcastToFrontServers(packetPtr, dataSize);
	}

	//-----------------------------------------------------------------------------
	void ServerManager::boardcastNetPacketToMapServers(GameNetSendDataBufferPtr& packetPtr ,I32 dataSize)
	{
		std::vector<ServerInfo* >::iterator iter = mMapServerList.begin();
		for (; iter != mMapServerList.end(); iter++)
		{
			I32 netID = (*iter)->netId;
			//if (netID == mapServerId)
			{
				CenterServerMain::getInstance().getServerLauncher()->sendServer(
					packetPtr,
					dataSize,
					netID );
			}
		}
	}

	//-----------------------------------------------------------------------------
	void ServerManager::sendNetPacketToMapServer(NetIdType mapServerId, GameNetSendDataBufferPtr& packetPtr ,I32 dataSize)
	{
		std::vector<ServerInfo* >::iterator iter = mMapServerList.begin();
		for (; iter != mMapServerList.end(); iter++)
		{
			I32 netID = (*iter)->netId;
			if (netID == mapServerId)
			{
				CenterServerMain::getInstance().getServerLauncher()->sendServer(
					packetPtr,
					dataSize,
					netID );
				continue;
			}
		}
	}

	//-----------------------------------------------------------------------------
	void ServerManager::sendNetPacketToFrontServer(NetIdType frontServerId, GameNetSendDataBufferPtr& packetPtr ,I32 dataSize)
	{
		FrontServerListContainer::iterator iter = mFrontServerList.begin();
		for (; iter != mFrontServerList.end(); iter++)
		{
			I32 netID = (*iter)->netId;
			if (netID == frontServerId)
			{
				CenterServerMain::getInstance().getServerLauncher()->sendServer(
					packetPtr,
					dataSize,
					netID );
				continue;
			}
		}
	}

	//-----------------------------------------------------------------------------
	void ServerManager::sendToFrontServerSyncMapServersStateStart()
	{
		GameNetSendDataBufferPtr dataPtr;
        CenterServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( NULL == packet )
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		packet->channel = GNPC_SERVER_STATE;
		packet->type    = PT_SERVER_STATE_S2S_SYNC_MAPSERVER_STATE_NEW_START;
		PT_SERVER_STATE_S2S_SYNC_MAPSERVER_STATE_NEW_START_DATA* data = (PT_SERVER_STATE_S2S_SYNC_MAPSERVER_STATE_NEW_START_DATA*)(packet->data);
		if (NULL == data)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// 当前发送数据头大小
		I32 sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_SERVER_STATE_S2S_SYNC_MAPSERVER_STATE_NEW_START_DATA_INFO::dataSize;
		// 当前发送数据大小
		I32 sendDataSize        = sendDataHeadSize;
		// 准备发送数据大小
		I32 prepareSendDataSize = sendDataHeadSize;

		boardcastToFrontServers( dataPtr ,  sendDataSize);
	}

	//-----------------------------------------------------------------------------	
	void ServerManager::syncMapServersStateToAllServerNewByLinhu()
	{
		sendToFrontServerSyncMapServersStateStart();

		//-----------------------------------------------------------------------------

		GameNetSendDataBufferPtr dataPtr;
		GameNetPacketData* packet = NULL;
		PT_SERVER_STATE_S2S_SYNC_MAPSERVER_STATE_NEW_DATA* data = NULL;
		// 当前发送数据头大小
		I32 sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_SERVER_STATE_S2S_SYNC_MAPSERVER_STATE_NEW_DATA_INFO::dataSize;
		// 当前发送数据大小
		I32 sendDataSize        = sendDataHeadSize;
		// 准备发送数据大小
		I32 prepareSendDataSize = sendDataHeadSize;

		std::vector<IdType>	mapIdVec;

		std::vector< ServerInfo* >::iterator it = mMapServerList.begin();
		for (int mapServerIndex = 0; it != mMapServerList.end(); it++,mapServerIndex++)
		{
			if ( dataPtr.isNull() )
			{
				CenterServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );
				packet	= (GameNetPacketData*) dataPtr->getLogicData();
				if ( NULL == packet )
				{
					DYNAMIC_ASSERT(0);
					return;
				}

				packet->channel = GNPC_SERVER_STATE;
				packet->type    = PT_SERVER_STATE_S2S_SYNC_MAPSERVER_STATE_NEW;
				data = (PT_SERVER_STATE_S2S_SYNC_MAPSERVER_STATE_NEW_DATA*)(packet->data);
				if (NULL == data)
				{
					DYNAMIC_ASSERT(0);
					return;
				}

				//设置MapServer的个数
				data->mapServerNum = mMapServerList.size();

				// 当前发送数据头大小
				sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_SERVER_STATE_S2S_SYNC_MAPSERVER_STATE_NEW_DATA_INFO::dataSize;
				// 当前发送数据大小
				sendDataSize        = sendDataHeadSize;
				// 准备发送数据大小
				prepareSendDataSize = sendDataHeadSize;
			}

			data->mapServerIndex	= mapServerIndex;
			data->serverUniqueFlag	= (*it)->serverUniqueFlag;

			boardcastNetPacketToServers( dataPtr ,  sendDataSize);

			dataPtr.setNull();
		}
	}

	//-----------------------------------------------------------------------------
	std::list< ServerInfo*>* ServerManager::getFrontServerList()
	{
		return &mFrontServerList;
	}

}