/******************************************************************************/
#include "stdafx.h"
#include "ServerManager.h"
#include "MapServerMain.h"
#include "LoginNetPacketProcesser.h"
#include "SPlayerNetPacketProcesser.h"
#include "SPlayerCharacterNetPacketProcesser.h"
#include "ServerStateNetPacketProcesser.h"
#include "SCampaignNetPacketProcesser.h"
#include "SSkillNetPacketProcesser.h"
#include "SPlaceNetPacketProcesser.h"
#include "ChatNetPacketProcesser.h"
#include "STroopNetPacketProcesser.h"
#include "SRegionNetPacketProcesser.h"
#include "TestNetPacketProcesser.h"
#include "SWorldManager.h"
#include "SPackNetPacketProcesser.h"
#include "SAttributePacketProcesser.h"
#include "SItemPacketProcesser.h"
#include "ShopPacketProcesser.h"
#include "TimeNetPacketProcesser.h"
#include "SPveNetPacketProcesser.h"
#include "SBuffPacketProcesser.h"
/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //ServerConnectInfo
    /******************************************************************************/


    //-----------------------------------------------------------------------------
    ServerConnectInfo::ServerConnectInfo()
        :mNetId(-1)
    {
    }

    //-----------------------------------------------------------------------------
    ServerConnectInfo::~ServerConnectInfo()
    {
    }

    //-----------------------------------------------------------------------------
    void ServerConnectInfo::onConnected(I32 id)
    {
        DYNAMIC_ASSERT_LOG(id!=-1,"invalid netid connect  map server");
        DYNAMIC_ASSERT_LOG(mNetId!=id,"reduplicate connect map server");
        DYNAMIC_ASSERT_LOG(mNetId==-1,"already connect map server");
        mNetId = id;
    }

    //-----------------------------------------------------------------------------
    void ServerConnectInfo::onDisConnected()
    {
        mNetId = -1;
    }

    //-----------------------------------------------------------------------------
    Bool ServerConnectInfo::isConnected()
    {
        return mNetId >= 0;
    }

    //-----------------------------------------------------------------------------
    void ServerConnectInfo::disConnected()
    {
        if ( isConnected() )
        {
            MapServerMain::getInstance().getServerLauncher()->closeServer(mNetId);
            mNetId = -1;
        }
    }

    /******************************************************************************/
    //ServerManager
    /******************************************************************************/

    //-----------------------------------------------------------------------------
	ServerManager::ServerManager()
    {
    }

    //-----------------------------------------------------------------------------
    ServerManager::~ServerManager()
    {
    }

    //-----------------------------------------------------------------------------
    Bool ServerManager::initialize()
    {

        return true;
    }

    //-----------------------------------------------------------------------------
    void ServerManager::update()
    {
    }

    //-----------------------------------------------------------------------------
    Bool ServerManager::unInitialize()
    {
        removeAllFrontServer();
        mCenterServerConnect.disConnected();
        mSysLogServerConnect.disConnected();
        mChatServerConnect.disConnected();

        return true;
    }

    //-----------------------------------------------------------------------------
    void ServerManager::onConnected(I32 id,GameNetType type,U32 serverId, NetAddress*address)
    {
		if ( type == GNT_FRONT_SERVER )
		{
			//1. save FrontServer list
			addFrontServer(id);
            onConnectFrontServer(id);
		}else 
        if ( type == GNT_MAP_SERVER )
		{
            DYNAMIC_EEXCEPT_LOG("no need connect map server");
		}else 
        if (type == GNT_CENTER_SERVER)
		{
            mCenterServerConnect.onConnected( id );
            onConnectCenterServer(id);
		}
        else 
        if ( type == GNT_SYSLOG_SERVER )
        {
            mSysLogServerConnect.onConnected( id );
            onConnectSysLogServer(id);
        }
		else
        if ( type == GNT_CHAT_SERVER)
		{
            mChatServerConnect.onConnected( id );
            onConnectChatServer(id);
		}
		else
		{
            DYNAMIC_EEXCEPT_LOG("not distinguish this invalid connect");
		}
    }
    
    //-----------------------------------------------------------------------------
    void ServerManager::onDisconnect(I32 id)
    {
        if ( id == mCenterServerConnect.mNetId )
        {
			mCenterServerConnect.onDisConnected();
            onDisconnectCenterServer(id);
        }
        else 
        if ( id == mSysLogServerConnect.mNetId  )
        {
            mSysLogServerConnect.onDisConnected();
            onDisconnectSysLogServer(id);
        }
		else 
        if ( id == mChatServerConnect.mNetId )
		{
			mChatServerConnect.onDisConnected();
            onDisconnectChatServer(id);
		}
		else 
        if ( hasFrontServer(id) )
		{
			removeFrontServer(id);
            onDisconnectFrontServer(id);
		}
    }

    //-----------------------------------------------------------------------------
    Bool ServerManager::processPacket(I32 id, NetEventRecv* packet)
    {
        //根据ID分派不同的服务器消息
        if ( hasFrontServer(id) )
        {
			//FUNDETECTION(__MG_FUNC__);
			if (LoginNetPacketProcesser::getInstance().processFrontServerPacket(id, packet) == true)
				return true;
            if ( SPlayerNetPacketProcesser::getInstance().processFrontServerPacket(id,packet) == true )
				return true;
            if ( SPlayerCharacterNetPacketProcesser::getInstance().processFrontServerPacket(id,packet) == true )
				return true;
			if ( SCampaignNetPacketProcesser::getInstance().processFrontServerPacket(id, packet) == true)
				return true;
			if ( SSkillNetPacketProcesser::getInstance().processFrontServerPacket(id, packet) == true)
				return true;
			if (SPlaceNetPacketProcesser::getInstance().processFrontServerPacket(id,packet) == true)
				return true;
			if (ChatNetPacketProcesser::getInstance().processFrontServerPacket(id,packet) == true)
				return true;
			if (STroopNetPacketProcesser::getInstance().processFrontServerPacket(id,packet) == true)
				return true;
			if (SRegionNetPacketProcesser::getInstance().processFrontServerPacket(id,packet) == true)
				return true;
            if (TestNetPacketProcesser::getInstance().processFrontServerPacket(id,packet) == true)
                return true;
			if (SPackNetPacketProcesser::getInstance().processFrontServerPacket(id,packet) == true)
				return true;
            if (SAttributePacketProcesser::getInstance().processFrontServerPacket(id, packet) == true)
                return true;
            if (SItemPacketProcesser::getInstance().processFrontServerPacket(id, packet) == true)
                return true;
			if (SPveNetPacketProcesser::getInstance().processFrontServerPacket(id, packet) == true)
				return true;
			if ( SBuffPacketProcesser::getInstance().processFrontServerPacket(id, packet) == true )
				return true;
        }
		else 
        if ( id == mSysLogServerConnect.mNetId  )
		{
			if (ServerStateNetPacketProcesser::getInstance().processCenterServerPacket(id,packet) == true)
			{
				return true;
			}
			if (SCampaignNetPacketProcesser::getInstance().processCenterServerPacket(id,packet) == true)
			{
				return true;
			}
			if (TimeNetPacketProcesser::getInstance().processCenterServerPacket(id,packet) == true)
			{
				return true;
			}
			
		}
        if ( id == mChatServerConnect.mNetId )
		{
			if (ChatNetPacketProcesser::getInstance().processChatServerPacket(id,packet) == true)
				return true;
		}
        if ( id == mCenterServerConnect.mNetId )
        {
             DYNAMIC_EEXCEPT_LOG("not recv packet from center server");
        }
		else
		{
            DYNAMIC_EEXCEPT_LOG("not distinguish this invalid packet connect");
		}

        return false;
    }

    //-----------------------------------------------------------------------------
    void ServerManager::onConnectFrontServer(I32 id)
    {
    }

    //-----------------------------------------------------------------------------
    void ServerManager::onConnectCenterServer(I32 id)
    {
    }

    //-----------------------------------------------------------------------------
    void ServerManager::onConnectChatServer(I32 id)
    {
    }

    //-----------------------------------------------------------------------------
    void ServerManager::onConnectSysLogServer(I32 id)
    {
    }

    //-----------------------------------------------------------------------------
    void ServerManager::onDisconnectFrontServer(I32 id)
    {
		DYNAMIC_ASSERT(0);
        //踢出所有玩家
        //SWorldManager::getInstance().removePlayerByFrontServer(id);
    }

    //-----------------------------------------------------------------------------
    void ServerManager::onDisconnectCenterServer(I32 id)
    {
    }

    //-----------------------------------------------------------------------------
    void ServerManager::onDisconnectChatServer(I32 id)
    {
    }

    //-----------------------------------------------------------------------------
    void ServerManager::onDisconnectSysLogServer(I32 id)
    {
    }

    //-----------------------------------------------------------------------------
    Bool ServerManager::hasFrontServer(NetIdType netId)
    {
        Bool result = false;

        mFrontServerListCs.readLock();
        {
            if ( mFrontServerList.empty() == false )
            {
                std::map< NetIdType, ServerConnectInfo >::iterator it = mFrontServerList.find(netId);
                if (it != mFrontServerList.end())
                {
                    result = true;
                }
            }
        }
        mFrontServerListCs.readUnLock();

		return result;
    }

    //-----------------------------------------------------------------------------
    void ServerManager::getFrontServerList(std::vector<NetIdType>& netList)
    {
        netList.clear();
        mFrontServerListCs.readLock();
        {
            std::map< NetIdType, ServerConnectInfo >::iterator it = mFrontServerList.begin();
            for ( ; it != mFrontServerList.end() ; it++ )
            {
                netList.push_back( it->second.mNetId );
            }
        }
        mFrontServerListCs.readUnLock();
    }
    
    //-----------------------------------------------------------------------------
    void ServerManager::addFrontServer(NetIdType netId)
    {   
        DYNAMIC_ASSERT_LOG(netId!=-1,"invalid netid connect  map server");

        if ( hasFrontServer(netId) == false )
        {
            mFrontServerListCs.writeLock();
            {
                ServerConnectInfo connect;
                connect.onConnected(netId);
                mFrontServerList[netId] = connect;
            }
            mFrontServerListCs.writeUnLock();

        }else
        {
            DYNAMIC_EEXCEPT_LOG("already connect front server");
        }
    }
    
    //-----------------------------------------------------------------------------
    void ServerManager::removeFrontServer(NetIdType netId)
    {
        DYNAMIC_ASSERT_LOG(netId!=-1,"invalid netid connect  map server");

        if ( hasFrontServer(netId) )
        {
            mFrontServerListCs.writeLock();
            {
                std::map< NetIdType, ServerConnectInfo >::iterator it = mFrontServerList.find(netId);
                if (it != mFrontServerList.end())
                {
                    mFrontServerList.erase(it);
                }
            }
            mFrontServerListCs.writeUnLock();

        }else
        {
            DYNAMIC_EEXCEPT_LOG("not find removeconnect front server");
        }
    }

    //-----------------------------------------------------------------------------
    void ServerManager::removeAllFrontServer()
    {
        mFrontServerListCs.writeLock();
        {
            std::map< NetIdType, ServerConnectInfo >::iterator it = mFrontServerList.begin();
            for ( ; it != mFrontServerList.end() ; it++ )
            {
                it->second.disConnected();
            }
            mFrontServerList.clear();
        }
        mFrontServerListCs.writeUnLock();
    }

	//-----------------------------------------------------------------------
	void ServerManager::boardcastNetPacketToAllFrontServer( GameNetSendDataBufferPtr& dataPtr,I32 dataSize )
	{
        mFrontServerListCs.readLock();
        {
            std::map< NetIdType, ServerConnectInfo >::iterator it = mFrontServerList.begin();
            for ( ; it != mFrontServerList.end() ; it++ )
            {
                NetIdType netID = it->second.mNetId;
                MapServerMain::getInstance().getServerLauncher()->sendServer( dataPtr, dataSize, netID );
            }
            mFrontServerList.clear();
        }
        mFrontServerListCs.readUnLock();
	}

    //-----------------------------------------------------------------------
    void ServerManager::sendNetPacketToCenterServer(GameNetSendDataBufferPtr& dataPtr,I32 dataSize)
    {
        if ( mCenterServerConnect.isConnected() )
        {
	        MapServerMain::getInstance().getServerLauncher()->sendServer( dataPtr,dataSize, mCenterServerConnect.mNetId );
        }
    }
        
    //-----------------------------------------------------------------------
    void ServerManager::sendNetPacketToSysServer(GameNetSendDataBufferPtr& dataPtr,I32 dataSize)
    {
        if ( mSysLogServerConnect.isConnected() )
        {
            MapServerMain::getInstance().getServerLauncher()->sendServer( dataPtr,dataSize, mCenterServerConnect.mNetId );
        }
    }

    //-----------------------------------------------------------------------
    void ServerManager::sendNetPacketToChatServer(GameNetSendDataBufferPtr& dataPtr,I32 dataSize)
    {
        if ( mChatServerConnect.isConnected() )
        {
            MapServerMain::getInstance().getServerLauncher()->sendServer( dataPtr,dataSize, mChatServerConnect.mNetId );
        }
    }
}