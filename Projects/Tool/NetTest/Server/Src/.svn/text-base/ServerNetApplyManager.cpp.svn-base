/******************************************************************************/
#include "stdafx.h"
#include "ServerNetApplyManager.h"
#include "SServerSetting.h"
/******************************************************************************/
namespace MG
{
    //-----------------------------------------------------------------------------
    ServerNetApplyManager::ServerNetApplyManager()
		:mClientDriver(-1),
		mServerDriver(-1),
		mUniqueFlag(0)
    {
    }

    //-----------------------------------------------------------------------------
    ServerNetApplyManager::~ServerNetApplyManager()
    {
    }

    //-----------------------------------------------------------------------------
    Bool ServerNetApplyManager::initialize()
    {
        if ( GameNetPacketManager::initialize() == false )
            return false;

        revertOnceHandlePacketCountByDrive();

		SServerSetting& setting = SServerSetting::getInstance();

		if ( setting.isClientLisiten() )
		{
			mClientDriver = createDriver(   "Client",
                                            setting.getClientListenInfo()->maxConnects,
                                            false, 
                                            true, 
                                            MG_GAME_NET_PACKET_NORMAL_MAX_SIZE, 
                                            MG_GAME_NET_PACKET_BIG_MAX_SIZE,
                                            MG_NET_BUFFER_SIZE_CLIENT );
			if ( mClientDriver < 0 )
			{
				return false;
			}
			NetAddress addr(setting.getClientListenInfo()->addr);
			if ( lisiten( mClientDriver, &addr ) == false )
			{
				return false;
			}
            setOnceHandlePacketCountByDriver( mClientDriver, 10 );
		}
		
		if (setting.getServerListenInfo())
		{	
			mServerDriver = createDriver(   "Server",
                                            setting.getServerListenInfo()->maxConnects,
                                            false, 
                                            false, 
                                            MG_GAME_NET_PACKET_NORMAL_MAX_SIZE, 
                                            MG_GAME_NET_PACKET_BIG_MAX_SIZE,
                                            MG_NET_BUFFER_SIZE_SERVER);
			if (mServerDriver < 0)
			{
				return false;
			}
            setOnceHandlePacketCountByDriver( mServerDriver, -1 );
		}
		else
		{
			return false;
		}
		
		if (!setting.getCoreInfo())
		{
			return false;
		}
		
		if ( setting.isServerLisiten())
		{

			if ( lisiten( mServerDriver,&(setting.getServerListenInfo()->addr) ) == false )
			{
				return false;
			}
			mUniqueFlag = setting.getServerListenInfo()->addr.getIP() * ::GetCurrentProcessId();
			if (setting.getConnectServers()->maxConnects > 0)
			{
				SServerSetting::ConnectionIt it = setting.getConnectServers()->connectServers.begin();
				for (; it != setting.getConnectServers()->connectServers.end(); it++)
				{
                    ConnectRemoteInfo* connectInfo = it->second;
					I32 netID = connect( mServerDriver, &(connectInfo->addr),true );
				}
			}

			return true;
		}
		
		return true;
	}
    //-----------------------------------------------------------------------------
    I32 ServerNetApplyManager::update()
    {
		FUNDETECTION( __MG_FUNC__ )
        I32 res = GameNetPacketManager::update();

        return res;
    }

    //-----------------------------------------------------------------------------
    I32 ServerNetApplyManager::unInitialize()
    {
        I32 res = NetManager::unInitialize();
        return res;
    } 
    //-----------------------------------------------------------------------------
    void ServerNetApplyManager::onAccept(NetEventAccept* netEvent)
    {
		std::map<I32,Bool>::iterator it = mRemoteConnects.find(netEvent->getID());
		if (it != mRemoteConnects.end())
		{
			DYNAMIC_ASSERT(false);
		}
		else
		{
			mRemoteConnects[netEvent->getID()] = true;
		}
    }

    //-----------------------------------------------------------------------------
    void ServerNetApplyManager::onConnected(NetEventConnect* netEvent)
    {
		std::map<I32,Bool>::iterator it = mRemoteConnects.find(netEvent->getID());
		if (it != mRemoteConnects.end())
		{
			DYNAMIC_ASSERT(false);
		}
		else
		{
			mRemoteConnects[netEvent->getID()] = true;
		}
    }
    
    //-----------------------------------------------------------------------------
    void ServerNetApplyManager::onClose(NetEventClose* netEvent) 
    {
      
    }

    //-----------------------------------------------------------------------------
    void ServerNetApplyManager::onRecv(NetEventRecv* netEvent)
    {
		static U32 i = 0;
		static U32 time = MG::MGTimeOp::getCurrTick();
		static U32 temp;
		static Dbl xl;
		i++;
		if ( i == 100000)
		{
			temp = MG::MGTimeOp::getCurrTick();
			xl = (Flt) (temp  - time)/ 100000;
			time = temp;
			i = 0;
			MG_LOG(out_error,"TCP 一个包消耗时间 %f\n",xl);
		}
    }

    //-----------------------------------------------------------------------------
    void ServerNetApplyManager::onError(NetEventErr* netEvent) 
    {
        
    }

	//-----------------------------------------------------------------------------
	I32 ServerNetApplyManager::getServerHandle()
	{
		return mServerDriver;
	}

    //-----------------------------------------------------------------------------
	I32 ServerNetApplyManager::getClientHandle()
	{
		return mClientDriver;
	}

    //-----------------------------------------------------------------------------
    void ServerNetApplyManager::closeAllClient()
    {
        closeAll(mClientDriver);
    }

    //-----------------------------------------------------------------------------
	void ServerNetApplyManager::closeClient( I32 id )
	{
		close(mClientDriver,id);
	}

	//-----------------------------------------------------------------------------
	void ServerNetApplyManager::closeServer(I32 id)
	{
		close(mServerDriver,id);
	}

    //-----------------------------------------------------------------------------
	U64 ServerNetApplyManager::getClientUid(I32 id)
	{
        return getAddressUin(mClientDriver,id);
	}

    //-----------------------------------------------------------------------------
	U64 ServerNetApplyManager::getServerUid( I32 id )
	{
        return getAddressUin(mServerDriver,id);
	}
	//-----------------------------------------------------------------------------
	I32 ServerNetApplyManager::connect( I32 handle,NetAddress* addr,Bool reConnect )
	{	
		I32 res = NetManager::connect(handle,addr);
		return res;
	}
	//-----------------------------------------------------------------------------
	Bool ServerNetApplyManager::isAllowedConnect( CChar16* ip )
	{
		SServerSetting& setting = SServerSetting::getInstance();
		if (!setting.getAllowedServerIpCollection()->isValid)
		{
			return true;
		}
		else
		{
			std::vector<Str16>::iterator it = setting.getAllowedServerIpCollection()->allowedIps.begin();
			for (; it != setting.getAllowedServerIpCollection()->allowedIps.end(); it++)
			{
				if ((*it).compare(ip) == 0)
				{
					return true;
				}
			}
		}
		return false;
	}
	//-----------------------------------------------------------------------------
	Bool ServerNetApplyManager::isAllowedConnect( CChar8* ip )
	{
		SServerSetting& setting = SServerSetting::getInstance();
		if (!setting.getAllowedServerIpCollection()->isValid)
		{
			return true;
		}
		else
		{
			Str16 wIp;
			MGStrOp::toString(ip,wIp);
			std::vector<Str16>::iterator it = setting.getAllowedServerIpCollection()->allowedIps.begin();
			for (; it != setting.getAllowedServerIpCollection()->allowedIps.end(); it++)
			{
				if ((*it).compare(wIp.c_str()) == 0)
				{
					return true;
				}
			}
		}
		return false;
	}
	//-----------------------------------------------------------------------------
	NetConnectInfo* ServerNetApplyManager::getClientNetInfo()
	{
		return getNetInfo(mClientDriver);
	}
	//-----------------------------------------------------------------------------
	NetConnectInfo* ServerNetApplyManager::getServerNetInfo()
	{
		return getNetInfo(mServerDriver);
	}
	//-----------------------------------------------------------------------------
	NetConnectInfo* ServerNetApplyManager::getClientConnectInfo( I32 id )
	{
		return getConnectInfo(mClientDriver,id);
	}
	//-----------------------------------------------------------------------------
	NetConnectInfo* ServerNetApplyManager::getServerConnectInfo( I32 id )
	{
		return getConnectInfo(mServerDriver,id);
	}
	//-----------------------------------------------------------------------------
	I32 ServerNetApplyManager::getServerCurrConnectionCount()
	{
		return getCurrConnectionCount(mServerDriver);	
	}
	//-----------------------------------------------------------------------------
	I32 ServerNetApplyManager::getClientCurrConnectionCount()
	{
		return getCurrConnectionCount(mClientDriver);
	}
	//-----------------------------------------------------------------------------
	U64 ServerNetApplyManager::getUniqueFlag()
	{
		return mUniqueFlag;
	}

    
}


