/******************************************************************************/
#include "stdafx.h"
#include "ClientManager.h"
#include "LoginNetPacket.h"
#include "ServerManager.h"
#include "FrontServerMain.h"
#include "PlayerCharacterDB.h"
#include "LoginNetPacketProcesser.h"
#include "PlayerCharacterNetPacketProcesser.h"
#include "QuestNetPacketProcesser.h"
#include "LoginManager.h"
#include "FrontServerMain.h"
#include "SkillNetPacketProcesser.h"
#include "CampaignNetPacketProcesser.h"
#include "SPlaceNetPacketProcesser.h"
#include "ChatNetPacketProcesser.h"
#include "PlayerNetPacketProcesser.h"
#include "TroopNetPacketProcesser.h"
#include "RegionNetPacketProcesser.h"
#include "QuestNetPacketProcesser.h"
#include "ItemPacketProcesser.h"
#include "ShopPacketProcesser.h"
#include "TestNetPacketProcesser.h"
#include "SWorldManager.h"
#include "SPveNetPacketProcessor.h"
#include "LineUpNetPacketProcesser.h"
#include "SGeneralRecruitNetPacketProcessor.h"
#include "SysLogNetPacketProcesser.h"
#include "PackNetPacketProcesser.h"
/******************************************************************************/
namespace MG
{

    //-----------------------------------------------------------------------
    ClientManager::ClientManager()
    {
    }

    //-----------------------------------------------------------------------
    ClientManager::~ClientManager()
    {
    }

    //-----------------------------------------------------------------------------------
    // Main
    //-----------------------------------------------------------------------------------

    //-----------------------------------------------------------------------
    Bool ClientManager::initialize()
    {

        // // 暂时不检测超时，以后让底层去做超时检测
		//if ( mCheckTimeOutThread.create( checkTimeOutThread,this ) == false )
		//{
		//	return false;
		//}
        //#ifdef _DEBUG
        //		Thread::SetThreadName(mCheckTimeOutThread.getThreadId(),"ClientManager::checkTimeOutThread");
        //#endif

        return true;
    }

    //-----------------------------------------------------------------------
    void ClientManager::uninitialize()
    {
		//mCheckTimeOutThread.destory();

        removeAllClientObject();
    }

	//-----------------------------------------------------------------------
	void ClientManager::update()
	{

	}
   

    //-----------------------------------------------------------------------------------
    // Connect Base
    //-----------------------------------------------------------------------------------

    //-----------------------------------------------------------------------
    void ClientManager::onConnected( I32 id, NetAddress*address, INetConnect* connect )
    {
        addClientObject(id, address,connect);

        ClientObject* ptr = getClientObject(id);
        //getClientObject(ptr, id);

        connect->setLogicBinder( ptr);
    }

    //-----------------------------------------------------------------------
    void ClientManager::onDisconnect(I32 id, INetConnect* connect)
    {
        removeClientObject(id);
    }

    //-----------------------------------------------------------------------
    Bool ClientManager::processPacket(I32 id, NetEventRecv* packet, INetConnect* connect)
    {
        DYNAMIC_ASSERT(packet);
        DYNAMIC_ASSERT(connect);

        if ( packet == NULL ) 
        {
            return false;
        }
        if ( connect == NULL ) 
        {
            return false;
        }

        ClientObject* cObj = (ClientObject*) connect->getLogicBinder();
        if ( cObj == NULL )
        {
            DYNAMIC_EEXCEPT_LOG("not find client Object!");
            return false;
        }

        //--------------------------------------------------------------------

        // 登临相关包处理
        if ( LoginNetPacketProcesser::getInstance().processClientPacket( id, packet ) == true )
            return true;

        //--------------------------------------------------------------------

        // 帐号没有验证通过则不处理游戏逻辑包
        if ( cObj->isAccountActive() == false )
            return true;

        //--------------------------------------------------------------------

        // 游戏逻辑包处理

        if ( PlayerCharacterNetPacketProcesser::getInstance().processClientPacket( id, packet ) == true )
            return true;
        if ( QuestNetPacketProcesser::getInstance().processClientPacket( id, packet ) == true )
            return true;
        if ( CampaignNetPacketProcesser::getInstance().processClientPacket( id, packet ) == true )
            return true;
        if (SPveNetPacketProcessor::getInstance().processClientPacket( id, packet ) == true )
            return true;
        if (SPlaceNetPacketProcesser::getInstance().processClientPacket(id,packet) == true)
            return true;
        if (ChatNetPacketProcesser::getInstance().processClientPacket(id,packet) == true)
            return true;
        if (PlayerNetPacketProcesser::getInstance().processClientPacket(id,packet) == true)
            return true;
        if (TroopNetPacketProcesser::getInstance().processClientPacket(id, packet) == true)
            return true;
        if (RegionNetPacketProcesser::getInstance().processClientPacket(id, packet) == true)
            return true;
        if (QuestNetPacketProcesser::getInstance().processClientPacket(id, packet) == true)
            return true;
        if (ItemPacketProcesser::getInstance().processClientPacket(id, packet) == true)
            return true;
        if (ShopPacketProcesser::getInstance().processClientPacket(id, packet) == true)
            return true;
        if (PackNetPacketProcesser::getInstance().processClientPacket(id, packet) == true)
            return true;
        if (LineUpNetPacketProcesser::getInstance().processClientPacket(id,packet) == true)
            return true;
        if ( SGeneralRecruitNetPacketProcessor::getInstance().processClientPacket( id, packet ) == true )
            return true;
        if (TestNetPacketProcesser::getInstance().processClientPacket(id, packet) == true)
            return true;

        return false;
    }


    //-----------------------------------------------------------------------------------
    // ClientObject Manager
    //-----------------------------------------------------------------------------------

    //-----------------------------------------------------------------------
    void ClientManager::addClientObject(NetIdType netId, NetAddress*address,INetConnect* connect)
    {

        removeClientObject( netId );

        //------------------------------------------------------------------------------------

        //ClientObjectPtr cObj;

        //mClientObjectFactory.creatClientObject( cObj, netId );
		ClientObject* newClient = new ClientObject();
		newClient->mNetId = netId;

        mClientObjectMapCs.writeLock();
        {
            mClientObjectMap.insert(std::make_pair(netId, newClient));
        }
        mClientObjectMapCs.writeUnLock();

    }

    //-----------------------------------------------------------------------
    void ClientManager::removeClientObject(NetIdType netId)
    {
		return ;
        //ClientObject** cObj;
        //if ( getClientObject( cObj, netId ) )
        {
            //------------------------------------------------------------------------------------

            //LoginManager::getInstance().handleClientLogout(*cObj );

            //------------------------------------------------------------------------------------

            //cObj->clear();

            //------------------------------------------------------------------------------------

            mClientObjectMapCs.writeLock();
            {
                std::map<NetIdType,ClientObject*>::iterator iter = mClientObjectMap.find( netId );
                if ( iter != mClientObjectMap.end() )
                {
                    mClientObjectMap.erase( iter );
                }
            }
            mClientObjectMapCs.writeUnLock();
        }
    }

    //-----------------------------------------------------------------------
    void ClientManager::removeAllClientObject()
    {
        mClientObjectMapCs.readLock();
        {
            std::map<NetIdType,ClientObject*>::iterator iter = mClientObjectMap.begin();
            for ( ;iter != mClientObjectMap.end(); )
            {
                LoginManager::getInstance().handleClientLogout( iter->second );
            }
        }
        mClientObjectMapCs.readLock();
        

        mClientObjectMapCs.writeLock();
        {
            std::map<NetIdType,ClientObject*>::iterator iter = mClientObjectMap.begin();
            for ( ;iter != mClientObjectMap.end(); )
            {
                iter->second->clear();
            }
            mClientObjectMap.clear();
        }
        mClientObjectMapCs.writeUnLock();
    }

    //-----------------------------------------------------------------------
    Bool ClientManager::hasClientObject(NetIdType netId)
    {
        Bool result = false;

        mClientObjectMapCs.readLock();
        {
            std::map<NetIdType,ClientObject*>::iterator iter = mClientObjectMap.find( netId );
            if ( iter != mClientObjectMap.end() )
            {
                result = true;
            }
        }
        mClientObjectMapCs.readUnLock();

        return result;
    }

    //-----------------------------------------------------------------------
    ClientObject* ClientManager::getClientObject(/*ClientObject** ptr, */NetIdType netId)
    {
        Bool result = false;
		ClientObject* ret = NULL;

        mClientObjectMapCs.readLock();
        {
            std::map<NetIdType,ClientObject*>::iterator iter = mClientObjectMap.find( netId );
            if ( iter != mClientObjectMap.end() )
            {
                ret = (iter->second);
                result = true;
            }
        }
        mClientObjectMapCs.readUnLock();

        return ret;
    }
    
    //-----------------------------------------------------------------------------------
    // TimeOut Check
    //-----------------------------------------------------------------------------------
    
    
	//-----------------------------------------------------------------------
	void ClientManager::checkTimeOutThread(Ptr ptr)
	{
		//OneThreadHandle* thd = (OneThreadHandle*)ptr;
		//if (thd && thd->getParam())
		//{
		//	ClientManager* mgr = (ClientManager *)(thd->getParam());
		//	if (mgr)
		//	{
		//		while( thd->isRun())
		//		{
		//			ClientObject* clientObject = NULL;
		//			Bool isErase = false;
		//			
		//			clientObject = mgr->getClientObjectFrmoQueue();
		//			while(!clientObject)
		//			{
        //              if ( thd->isRun() == false )
        //                  return;
		//				clientObject = mgr->getClientObjectFrmoQueue();
		//				Sleep(10);
		//			}
		//			if (clientObject)
		//			{
		//				if (clientObject->isDestroy)
		//				{
		//					mgr->destroyClientObject(clientObject);
		//				}
		//				else
		//				{
		//					// 不做超时检测
		//					/*U32 currTime = MGTimeOp::getCurrTick();
		//					//如果大于30分钟则断开连接
		//					if ( currTime - clientObject->connectTime > 1800000 )
		//					{
		//						I32 loginServerNetID = ServerManager::getInstance().getLoginServerNetID();
		//						LoginNetPacketProcesser::getInstance().sendClientLogoutToLoginServer( loginServerNetID, clientObject->accName.c_str());
		//						FrontServerMain::getInstance().getServerLauncher()->closeClient(clientObject->netId);
		//						mgr->removeWaitingLoginClient(clientObject->netId);
		//					}*/
		//					mgr->addClientObjectToQueue(clientObject);
		//				}
		//				Sleep(5);
		//			}
		//			
		//		}
		//	}
		//}
	}




}