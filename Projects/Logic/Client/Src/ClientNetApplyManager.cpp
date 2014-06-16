/******************************************************************************/
#include "stdafx.h"
#include "ClientNetApplyManager.h"
#include "NetAddress.h"
#include "LoginNetPacketProcesser.h"
#include "LoginManager.h"
#include "ClientMain.h"
#include "GameMain.h"
#include "PlayCharacterNetPacketProcesser.h"
#include "PlayerNetPacketProcesser.h"
#include "MapNetPacketProcesser.h"
#include "RegionNetPacketProcesser.h"
#include "CampaignNetPacketProcesser.h"
#include "SkillNetPacketProcesser.h"
#include "PlaceNetPacketProcesser.h"
#include "ChatNetPacketProcesser.h"
#include "TroopNetPacketProcesser.h"
#include "CBuildingNetPacketProcesser.h"
#include "QuestNetPacketProcesser.h"
#include "ItemPacketProcesser.h"
#include "ShopPacketProcesser.h"
#include "TestNetPacketProcesser.h"
#include "PackNetPacketProcesser.h"
#include "CAttributeNetPacketProcesser.h"
#include "TimeNetPacketProcesser.h"
#include "CPveNetPacketProcesser.h"
#include "LineUpNetPacketProcesser.h"
#include "MonsterNetPacketProcesser.h"
#include "CGeneralRecruitNetPacketProcessor.h"
#include "CBuffPacketProcesser.h"
/******************************************************************************/

namespace MG
{

	//-----------------------------------------------------------------------------
    ClientNetApplyManager::ClientNetApplyManager()
        :mLoginServerID(-1),
        mFrontServerID(-1),
		mNetDriver(-1)
    {
        
    }
    
    //-----------------------------------------------------------------------------
    ClientNetApplyManager::~ClientNetApplyManager()
    {

    }

    //-----------------------------------------------------------------------------
    Bool ClientNetApplyManager::initialize()
    {
        if ( NetManager::initialize() == false )
            return false;

		mNetDriver = createDriver( "Client", 
                                    4, 
                                    false,
                                    MG_NET_CLIENT_TIMEOUT_TOUCH_TIME,
                                    MG_NET_CLIENT_TIMEOUT_DURATION,
                                    true, 
                                    MG_GAME_NET_PACKET_NORMAL_MAX_SIZE,
                                    MG_GAME_NET_PACKET_NORMAL_MAX_SIZE,
                                    MG_NET_BUFFER_SIZE_CLIENT,
									MG_NET_MAX_CLIENT_SOCKET_SENDBUFF_SIZE,
									MG_NET_MAX_CLIENT_SOCKET_RECVBUFF_SIZE,
									DRIVER_TYPE_CLIENT);
		if ( mNetDriver < 0 )
		{
			return false;
		}

        GameNetDriveConfig config;
        config.OnceHandlePacketCount        = -1;
        config.SendCombinePacketMaxSize     = 1024;
        config.ReplaceEnableInSendQueue     = true;
        config.ReplaceEnableInRecvQueue     = false;
        config.DiscardEnableInSendQueue     = true;
        config.DiscardEnableInRecvQueue     = false;
        config.BlockWaitEnableInSendQueue   = true;
        config.BlockWaitEnableInRecvQueue   = false;
        configDrive( mNetDriver, config );

        return true;
    }

    //-----------------------------------------------------------------------------
    I32 ClientNetApplyManager::update()
    {
		FUNDETECTION(__MG_FUNC__);
        I32 res = GameNetPacketManager::update();
        
        if ( mNetDriver>=0 )
        {
            manualDoOneL2NHandle( mNetDriver );
            manualDoOneN2LHandle( mNetDriver );
        }

        return res;
    }

    //-----------------------------------------------------------------------------
    I32 ClientNetApplyManager::unInitialize()
    {
        I32 res = NetManager::unInitialize();

        mNetDriver = -1;

        return res;
    }

    //-----------------------------------------------------------------------------
    Bool ClientNetApplyManager::connectLoginServer( NetAddress& addr )
    {
        disconnectLoginServer();

        mLoginServerID = this->connect(mNetDriver, &addr);
		if ( mLoginServerID < 0 )
		{
			return false;
		}
		return true;
    }

    //-----------------------------------------------------------------------------
    Bool ClientNetApplyManager::disconnectLoginServer()
    {
        if ( mLoginServerID >= 0 )
        {
            close(mNetDriver,mLoginServerID);
            mLoginServerID = -1;
        }
        return true;
    }

    //-----------------------------------------------------------------------------
    Bool ClientNetApplyManager::connectFrontServer( NetAddress& addr )
    {
        disconnectFrontServer();

        mFrontServerID = this->connect(mNetDriver, &addr);
        if ( mFrontServerID < 0 )
        {
            return false;
        }
        return true;
    }

    //-----------------------------------------------------------------------------
    Bool ClientNetApplyManager::disconnectFrontServer()
    {
		if ( mFrontServerID >= 0 )
		{
			close(mNetDriver,mFrontServerID);
            mFrontServerID = -1;
		}
		return true;
    }

    //-----------------------------------------------------------------------------
    Bool ClientNetApplyManager::disconnectServers()
    {
        Bool res = true;

        if ( disconnectLoginServer() == false )
            res = false;
        if ( disconnectFrontServer() == false )
            res = false;

        return res;
    }
	
    //-----------------------------------------------------------------------------
    GameNetSendDataBufferPtr ClientNetApplyManager::getSendDataBuffer( U32 buffSize  )
    {
        GameNetSendDataBufferPtr ptr ;
        getGameNetSendDataBufferPtr( ptr, mNetDriver, buffSize );
        return ptr;
    }
    
    //-----------------------------------------------------------------------------
    void ClientNetApplyManager::sendLoginServerPacket( GameNetSendDataBufferPtr& data, Int dataSize )
    {
        if ( mLoginServerID >= 0 )
        {
			prepareSend(data,mNetDriver,mLoginServerID,dataSize);
        }
    }

    //-----------------------------------------------------------------------------
    void ClientNetApplyManager::sendFrontServerPacket( GameNetSendDataBufferPtr& data, Int dataSize )
    {
        if ( mFrontServerID >= 0 )
        {
			prepareSend(data,mNetDriver,mFrontServerID,dataSize);
        }
    }

    //-----------------------------------------------------------------------------
    void ClientNetApplyManager::onAccept(NetEventAccept* netEvent)
    {
        
    }

    //-----------------------------------------------------------------------------
    void ClientNetApplyManager::onConnected(NetEventConnect* netEvent)
    {

    }

    //-----------------------------------------------------------------------------
    void ClientNetApplyManager::onClose(NetEventClose* netEvent)
    {
        if ( netEvent->getID() == mLoginServerID )
        {
            LoginManager::getInstance().onLoginServerDisconnect();
        }else
        if ( netEvent->getID() == mFrontServerID )
        {
            //如果是被动断开连接的
            if ( netEvent->isPassivity() == true )
            {
                //弹出连接断开提示

                GameMain::getInstance().stopAndRestore();
            }
        }
    }

    //-----------------------------------------------------------------------------
    void ClientNetApplyManager::onRecv(NetEventRecv* netEvent)
    {
        if ( netEvent->getID() == mLoginServerID )
        {
            if ( LoginNetPacketProcesser::getInstance().processLoginServerPacket(netEvent->getID(),netEvent) == true )
                return;
			if (LineUpNetPacketProcesser::getInstance().processLoginServerPacket(netEvent->getID(),netEvent) == true )
				return;
        }else
        if ( netEvent->getID() == mFrontServerID )
        {
            if ( LoginNetPacketProcesser::getInstance().processFrontServerPacket(netEvent->getID(),netEvent) == true )
                return;
			if ( PlayCharacterNetPacketProcesser::getInstance().processFrontServerPacket(netEvent->getID(),netEvent) == true)
				return;
			if ( MonsterNetPacketProcesser::getInstance().processFrontServerPacket(netEvent->getID(),netEvent) == true)
				return;
            if ( PlayerNetPacketProcesser::getInstance().processFrontServerPacket(netEvent->getID(), netEvent) == true )
                return;
			if ( RegionNetPacketProcesser::getInstance().processFrontServerPacket(netEvent->getID(), netEvent) == true)
				return;
			if ( MapNetPacketProcesser::getInstance().processFrontServerPacket(netEvent->getID(), netEvent) == true)
				return;
			if ( CampaignNetPacketProcesser::getInstance().processFrontServerPacket(netEvent->getID(), netEvent) == true)
				return;
			if( SkillNetPacketProcesser::getInstance().processFrontServerPacket(netEvent->getID(), netEvent) == true)
				return;
			if (PlaceNetPacketProcesser::getInstance().processFrontServerPacket(netEvent->getID(),netEvent) == true)
				return;
			if (ChatNetPacketProcesser::getInstance().processFrontServerPacket(netEvent->getID(),netEvent) == true)
				return;
			if (TroopNetPacketProcesser::getInstance().processFrontServerPacket(netEvent->getID(),netEvent) == true)
				return;
            if (CBuildingNetPacketProcesser::getInstance().processFrontServerPacket(netEvent->getID(), netEvent) == true)
                return;
			if (QuestNetPacketProcesser::getInstance().processFrontServerPacket(netEvent->getID(), netEvent) == true)
				return;
            if (ItemPacketProcesser::getInstance().processFrontServerPacket(netEvent->getID(), netEvent) == true)
                return;
            if (ShopPacketProcesser::getInstance().processFrontServerPacket(netEvent->getID(), netEvent) == true)
                return;
            if (TestNetPacketProcesser::getInstance().processFrontServerPacket(netEvent->getID(), netEvent) == true)
                return;
			if (PackNetPacketProcesser::getInstance().processFrontServerPacket(netEvent->getID(), netEvent) == true)
				return;
            if (CAttributeNetPacketProcesser::getInstance().processFrontServerPacket(netEvent->getID(),netEvent) == true)
                return;
			if (TimeNetPacketProcesser::getInstance().processFrontServerPacket(netEvent->getID(),netEvent) == true)
				return;
			if (CBuildingNetPacketProcesser::getInstance().processFrontServerPacket(netEvent->getID(),netEvent) == true)
				return; 
			if (CPveNetPacketProcesser::getInstance().processFrontServerPacket(netEvent->getID(),netEvent) == true)
				return; 
			if (LineUpNetPacketProcesser::getInstance().processFrontServerPacket(netEvent->getID(),netEvent) == true)
				return;
			if (CGeneralRecruitNetPacketProcessor::getInstance().processFrontServerPacket(netEvent->getID(),netEvent) == true)
				return;
			if ( CBuffPacketProcesser::getInstance().processFrontServerPacket(netEvent->getID(),netEvent) == true )
				return;
        }
    }

    //-----------------------------------------------------------------------------
    void ClientNetApplyManager::onError(NetEventErr* netEvent)
    {

    }

}


