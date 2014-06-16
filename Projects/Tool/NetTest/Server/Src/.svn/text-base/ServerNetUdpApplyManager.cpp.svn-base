/******************************************************************************/
#include "stdafx.h"
#include "ServerNetUdpApplyManager.h"
#include "SServerSetting.h"
#include "GameNetPacket.h"
/******************************************************************************/
namespace MG
{
    //-----------------------------------------------------------------------------
    ServerNetUdpApplyManager::ServerNetUdpApplyManager()
		:mClientDriver(-1),
		mServerDriver(-1),
		mUniqueFlag(0)
    {

    }

    //-----------------------------------------------------------------------------
    ServerNetUdpApplyManager::~ServerNetUdpApplyManager()
    {

    }

    //-----------------------------------------------------------------------------
    Bool ServerNetUdpApplyManager::initialize(U16 sectionPacketSize)
    {
        if ( GameNetUdpPacketManager::initialize(sectionPacketSize) == false )
            return false;

        revertOnceHandlePacketCountByDrive();

		SServerSetting& setting = SServerSetting::getInstance();

		if ( setting.isClientLisiten() )
		{
			mClientDriver = createDriver(   "Client",
                                            setting.getClientListenInfo()->maxConnects,
                                            false, 
                                            true, 
                                            UDP_LOGIC_PACK_MIN_SIZE, 
                                            UDP_LOGIC_PACK_MAX_SIZE);
			if ( mClientDriver < 0 )
			{
				return false;
			}

			NetAddress addr(setting.getClientListenInfo()->addr);
	
			setOnceHandlePacketCountByDriver( mClientDriver, 10 );
			
			if (!configLocalSockets(mClientDriver,&addr,1))
			{
				return false;
			}
		}
		
		if (setting.getServerListenInfo())
		{	
			mServerDriver = createDriver(   "Server",
                                            setting.getServerListenInfo()->maxConnects,
                                            false, 
                                            false, 
                                            MG_GAME_NET_PACKET_NORMAL_MAX_SIZE, 
                                            MG_GAME_NET_PACKET_BIG_MAX_SIZE);
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
		return true;
	}
    //-----------------------------------------------------------------------------
    I32 ServerNetUdpApplyManager::update()
    {
		FUNDETECTION( __MG_FUNC__ )
        I32 res = GameNetUdpPacketManager::update();

        return res;
    }

    //-----------------------------------------------------------------------------
    I32 ServerNetUdpApplyManager::unInitialize()
    {
        I32 res = NetUdpManager::unInitialize();
        return res;
    }
    //-----------------------------------------------------------------------------
    void ServerNetUdpApplyManager::onAccept(NetUdpEventAccept* netEvent)
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
    void ServerNetUdpApplyManager::onConnected(NetUdpEventConnect* netEvent)
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
    void ServerNetUdpApplyManager::onClose(NetUdpEventClose* netEvent) 
    {
       
    }

    //-----------------------------------------------------------------------------
    void ServerNetUdpApplyManager::onRecv(NetUdpEventRecv* netEvent)
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
		   MG_LOG(out_error,"UDP 一个包消耗时间 %f\n",xl);
	   }
    }

    //-----------------------------------------------------------------------------
    void ServerNetUdpApplyManager::onError(NetUdpEventErr* netEvent) 
    {
		
    }

	//-----------------------------------------------------------------------------
	I32 ServerNetUdpApplyManager::getServerHandle()
	{
		return mServerDriver;
	}

    //-----------------------------------------------------------------------------
	I32 ServerNetUdpApplyManager::getClientHandle()
	{
		return mClientDriver;
	}

    //-----------------------------------------------------------------------------
    void ServerNetUdpApplyManager::closeAllClient()
    {
        closeAll(mClientDriver);
    }

    //-----------------------------------------------------------------------------
	void ServerNetUdpApplyManager::closeClient( I32 id )
	{
		close(mClientDriver,id);
	}

	//-----------------------------------------------------------------------------
	void ServerNetUdpApplyManager::closeServer(I32 id)
	{
		close(mServerDriver,id);
	}

    //-----------------------------------------------------------------------------
	U64 ServerNetUdpApplyManager::getClientUid(I32 id)
	{
        return getAddressUin(mClientDriver,id);
	}

    //-----------------------------------------------------------------------------
	U64 ServerNetUdpApplyManager::getServerUid( I32 id )
	{
        return getAddressUin(mServerDriver,id);
	}
	//-----------------------------------------------------------------------------
	void ServerNetUdpApplyManager::connect( I32 handle,NetAddress* addr,Bool reConnect )
	{
		I32 res = -1;
		if (reConnect)
		{
			NetUdpManager::connect(handle,addr,0);
		}
		else
		{
			NetUdpManager::connect(handle,addr,0);
		}


	}
	//-----------------------------------------------------------------------------
	Bool ServerNetUdpApplyManager::isAllowedConnect( CChar16* ip )
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
	Bool ServerNetUdpApplyManager::isAllowedConnect( CChar8* ip )
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
	NetConnectInfo* ServerNetUdpApplyManager::getClientNetInfo()
	{
		return getNetInfo(mClientDriver);
	}
	//-----------------------------------------------------------------------------
	NetConnectInfo* ServerNetUdpApplyManager::getServerNetInfo()
	{
		return getNetInfo(mServerDriver);
	}
	//-----------------------------------------------------------------------------
	NetConnectInfo* ServerNetUdpApplyManager::getClientConnectInfo( I32 id )
	{
		return getConnectInfo(mClientDriver,id);
	}
	//-----------------------------------------------------------------------------
	NetConnectInfo* ServerNetUdpApplyManager::getServerConnectInfo( I32 id )
	{
		return getConnectInfo(mServerDriver,id);
	}
	//-----------------------------------------------------------------------------
	I32 ServerNetUdpApplyManager::getServerCurrConnectionCount()
	{
		return getCurrConnectionCount(mServerDriver);	
	}
	//-----------------------------------------------------------------------------
	I32 ServerNetUdpApplyManager::getClientCurrConnectionCount()
	{
		return getCurrConnectionCount(mClientDriver);
	}
	//-----------------------------------------------------------------------------
	U64 ServerNetUdpApplyManager::getUniqueFlag()
	{
		return mUniqueFlag;
	}

    
}


