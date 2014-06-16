/******************************************************************************/
#include "stdafx.h"
#include "LoginNetPacket.h"
#include "ServerManager.h"
#include "FrontServerMain.h"
#include "ClientManager.h"
#include "LoginNetPacketProcesser.h"
#include "LoginManager.h"
#include "PlayerCharacterNetPacketProcesser.h"
#include "PlayerNetPacketProcesser.h"
#include "CommonGameDefine.h"
#include "NetTranspondPacketProcesser.h"
#include "ServerStateNetPacketProcesser.h"
#include "CampaignNetPacketProcesser.h"
#include "TroopNetPacketProcesser.h"
#include "ShopPacketProcesser.h"
#include "SCDNetPacketProcesser.h"
#include "SAttributeNetPacketProcesser.h"
#include "LogSystem.h"
#include "TimeNetPacketProcesser.h"
#include "ChatNetPacketProcesser.h"
#include "SWorldManager.h"
#include "RegionNetPacketProcesser.h"
#include "RegionDevideAlgorithm.h"
#include "District.h"
#include "ThreadTaskManager.h"
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
            FrontServerMain::getInstance().getServerLauncher()->closeServer(mNetId);
            mNetId = -1;
        }
    }

	NetIdType ServerConnectInfo::getNetId() const
	{
		return mNetId;
	}


    /******************************************************************************/
    //MapServerConnectInfo
    /******************************************************************************/

    //-----------------------------------------------------------------------------
    void MapServerConnectInfo::onConnected(I32 id)
    {
        ServerConnectInfo::onConnected( id );

        mServerUniqueFlag	= 0;
        mClientNum			= 0;
        mIsValid            = false;
        mMapServerNum		= 0;
        mMapServerIndex		= -1;
    }
    
    //-----------------------------------------------------------------------------
    void MapServerConnectInfo::onDisConnected()
    {
        //ServerConnectInfo::onDisConnected( id );
    }

    /******************************************************************************/
    //ServerManager
    /******************************************************************************/

    //-----------------------------------------------------------------------
	ServerManager::ServerManager()
        :mServerSetting(NULL)
    {
	}

    //-----------------------------------------------------------------------
    ServerManager::~ServerManager()
    {
		uninitialize();
    }


    //-----------------------------------------------------------------------------------
    // Main
    //-----------------------------------------------------------------------------------


    //-----------------------------------------------------------------------
    Bool ServerManager::initialize(SServerSetting* setting)
    {
		DYNAMIC_ASSERT(setting);
		if (setting)
		{
			mServerSetting = setting;
		}
        return true;
    }

    //-----------------------------------------------------------------------
    void ServerManager::uninitialize()
    {
        mServerSetting = NULL;

        removeAllConnectMapServer();
        removeAllActiveMapServer();

        mLoginServerConnect.disConnected();
        mCenterServerConnect.disConnected();
        mSysLogServerConnect.disConnected();
        mChatServerConnect.disConnected();
    }

    //-----------------------------------------------------------------------
    void ServerManager::printServer()
    {
        /*{
            MG_LOG(out_sys, "\n ------------------- 【mConnectMapServerList列表信息】开始 ------------------- \n ");
            std::map<NetIdType, MapServerInfo*>::iterator iter = mConnectMapServerList.begin();
            Int count = 1;
            for ( ; iter != mConnectMapServerList.end(); ++iter, ++count)
            {
                MapServerInfo* temp  = (MapServerInfo*)iter->second;

                MG_LOG(out_sys, "MapServerInfo count = [%d] netId[%d], serverUniqueFlag[%I64i], isValid[%d]\n",
                    count, temp->netId, temp->serverUniqueFlag, temp->isValid);

            }
            MG_LOG(out_sys, "\n ------------------- 【mConnectMapServerList列表信息】结束 ------------------- \n ");
        }


        {
            MG_LOG(out_sys, "\n ------------------- 【mActiveMapServerNetList列表信息】开始 ------------------- \n ");
            std::map<ServerUniqueFlagIdType, MapServerInfo*>*	activeMapServerList = mActiveMapServerNetListMap.getDataSet();
            std::map<ServerUniqueFlagIdType, MapServerInfo*>::iterator iter = activeMapServerList->begin();
            Int count = 1;
            for ( ; iter != activeMapServerList->end(); ++iter, ++count)
            {
                MapServerInfo* temp  = iter->second;
                if (NULL != temp)
                {
                    MG_LOG(out_sys, "MapServerInfo count = [%d] netId[%d], serverUniqueFlag[%I64i], isValid[%d]\n",
                        count, temp->netId, temp->serverUniqueFlag, temp->isValid);
                }
            }
            MG_LOG(out_sys, "\n ------------------- 【mActiveMapServerNetList列表信息】结束 ------------------- \n ");
        }

        {
            MG_LOG(out_sys, "\n ------------------- 【mActiveMapServerVector列表信息】开始 ------------------- \n ");
            std::vector<MapServerInfo*>::iterator iter = mActiveMapServerVector.begin();
            Int count = 1;
            for ( ; iter != mActiveMapServerVector.end(); ++iter, ++count)
            {
                MapServerInfo* temp = *iter;
                if (NULL != temp)
                {
                    MG_LOG(out_sys, "MapServerInfo count = [%d] netId[%d], serverUniqueFlag[%I64i], isValid[%d]\n",
                        count, temp->netId, temp->serverUniqueFlag, temp->isValid);
                }
            }
            MG_LOG(out_sys, "\n ------------------- 【mActiveMapServerVector列表信息】结束 ------------------- \n ");
        }*/
    }
    
    //-----------------------------------------------------------------------------------
    // Connect Base
    //-----------------------------------------------------------------------------------

    //-----------------------------------------------------------------------
    void ServerManager::onConnected(I32 id, GameNetType type,U32 serverId, U64 serverUniqueFlag, NetAddress* address)
    {
        if ( type == GNT_MAP_SERVER )
        {
            //1. save FrontServer list
            addConnectMapServer(id,serverId,serverUniqueFlag);
            onConnectMapServer(id,serverId,serverUniqueFlag);
        }else 
        if ( type == GNT_LOGIN_SERVER )
        {
            mLoginServerConnect.onConnected( id );
            onConnectLoginServer(id);
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

    //-----------------------------------------------------------------------
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
        if ( id == mLoginServerConnect.mNetId )
        {
            mLoginServerConnect.onDisConnected();
            onDisconnectLoginServer(id);
        }
        else 
        if ( hasConnectMapServer(id) )
        {
            removeConnectMapServer(id);
            onDisconnectMapServer(id);
        }
    }
	
    //-----------------------------------------------------------------------
    void ServerManager::onConnectLoginServer(I32 id)
    {
        //发送客户端监听信息给LoginServer
        CChar* ip = mServerSetting->getListenInfoSendToClient()->addr.getIPStr();
        I32 port  = mServerSetting->getListenInfoSendToClient()->addr.getPort();
        //LoginNetPacketProcesser::getInstance().sendClientListenInfoToLoginServer( id, ip, port);
    }

    //-----------------------------------------------------------------------
    void ServerManager::onConnectMapServer(I32 id, U32 serverId, U64 serverUniqueFlag)
    {
        // 之后用线程任务完成
        // Loop Player
        //{
            //PlayerNetPacketProcesser::getInstance().broadcastPlayerLoginToMapServer(player, mapServerId);
            //PlayerNetPacketProcesser::getInstance().broadcastPlayerCharacterListToMapServer(player, mapServerId);
            //PlayerNetPacketProcesser::getInstance().broadcastTroopGroupListToMapServer(player, mapServerId);
        //}
        //PlayerNetPacketProcesser::getInstance().broadcastAllListEndToMapServer(mapServerId);

        addActiveMapServer( id, serverId, serverUniqueFlag);

        divideRegionForActiveMapServer();

        //MG_LOG(out_sys, "MapServerNetId[%d] 连接成功， 打印开始\n", id);
        //printServer();
        //SWorldManager::getInstance().printWorldObject();
        //MG_LOG(out_sys, "MapServerNetId[%d] 连接成功， 打印结束\n", id);
    }

    //-----------------------------------------------------------------------
    void ServerManager::onConnectCenterServer(I32 id)
    {

    }

    //-----------------------------------------------------------------------
    void ServerManager::onConnectChatServer(I32 id)
    {
        // 发送客户端信息
        LoginNetPacketProcesser::getInstance().sendClientListInGameToChatServer();
    }

    //-----------------------------------------------------------------------
    void ServerManager::onConnectSysLogServer(I32 id)
    {
    }

    //-----------------------------------------------------------------------
    void ServerManager::onDisconnectLoginServer(I32 id)
    {
          LoginManager::getInstance().handleLoginServerDisconnect();
    }

    //-----------------------------------------------------------------------
    void ServerManager::onDisconnectMapServer(I32 id)
    {
        closeAllClientsByMapServerId(id);

        removeActiveMapServer(id);

        freezePartRegionFromActiveMapServer(id);

        //MG_LOG(out_sys, "MapServerNetId[%d] 断开成功， 打印开始\n", id);
        //printServer();
        //MG_LOG(out_sys, "MapServerNetId[%d] 断开成功， 打印结束\n", id);
        //SWorldManager::getInstance().printWorldObject();
    }

    //-----------------------------------------------------------------------
    void ServerManager::onDisconnectCenterServer(I32 id)
    {

    }

    //-----------------------------------------------------------------------
    void ServerManager::onDisconnectChatServer(I32 id)
    {

    }

    //-----------------------------------------------------------------------
    void ServerManager::onDisconnectSysLogServer(I32 id)
    {

    }





















    //-----------------------------------------------------------------------
    Bool ServerManager::processPacket(I32 id,NetEventRecv* packet)
    {
		ThreadTaskManager::getInstance().addServerNormalTask(packet,id,id);
        
        return true;
    }
	//-----------------------------------------------------------------------
	//Bool ServerManager::addMapServerInfoToConnectList(I32 netId,U32 serverId,U64 serverUniqueFlag)
	//{
#if 0
		MapServerConnectInfo* serverInfo = getConnectMapServerInfoById(netId);
		if (!serverInfo)
		{ 
			serverInfo = MG_NEW MapServerConnectInfo;
			mConnectMapServerList[netId] = serverInfo;
		}
		serverInfo->clear();
		serverInfo->serverUniqueFlag = serverUniqueFlag;
		serverInfo->netId = netId;

		I32 index = 0;
		//MapServerInfo* activeServer = getActiveMapServerByFlag(serverInfo->serverUniqueFlag,index);
		//if (activeServer)
		//{
		//	//activeServer->netId = netId;
		//	//activeServer->isValid = true;
		//	//更新mapId->netId映射表
		//	{
		//		std::vector<IdType> mapsId;
		//		I32 size = SWorldManager::getInstance().getActiveMapsId(mapsId,index,getActiveMapServerNum());
		//		if (size > 0)
		//		{
		//			std::vector<IdType>::iterator it = mapsId.begin();
		//			for (; it != mapsId.end(); it++)
		//			{
		//				mActiveMapServerNetMap[*it] = netId;
		//			}
		//			
		//		}
		//	}
		//}
#endif
	//	return true;
	//}

    //-----------------------------------------------------------------------
    void ServerManager::boardcastNetPacketToAcitveMapServer(  GameNetSendDataBufferPtr& dataPtr,I32 dataSize  )
    {
#if 0
		std::map<ServerUniqueFlagIdType, ServerConnectInfo*>* mapServerList = mActiveMapServerNetListMap.getDataSet();
		std::map<ServerUniqueFlagIdType, ServerConnectInfo*>::iterator iter = mapServerList->begin();
		for ( ; iter != mapServerList->end(); ++iter)
		{
			MapServerConnectInfo* mapServerInfo = iter->second;
			if ((mapServerInfo->isValid) == true)
			{
				NetIdType netID = mapServerInfo->netId;
				DYNAMIC_ASSERT(netID >= 0);
				FrontServerMain::getInstance().getServerLauncher()->sendServer(dataPtr,dataSize,netID);
			}
		}
#endif
    }

#if 0
    //-----------------------------------------------------------------------
    MG::MapServerConnectInfo* ServerManager::getConnectMapServerInfoById( I32 netId )
    {
#if 0
        std::map< I32, MapServerConnectInfo >::iterator iter = mConnectMapServerList.find(netId);
        if ( iter != mConnectMapServerList.end() )
            return (MapServerConnectInfo)iter->second;
        return NULL;
#endif
		return NULL;
    }
#endif

    //-----------------------------------------------------------------------
	//void ServerManager::clearActiveMapServerNetList()
	//{
	//	//mActiveMapServerNetListMap.destroyAll();
	//}

#if 0
    //-----------------------------------------------------------------------
	void ServerManager::copyConnectMapServerListToActiveMapServerList()
	{
#if 0
		std::map<ServerUniqueFlagIdType, MapServerInfo*>* mapServerList = mActiveMapServerNetListMap.getDataSet();
		std::map<ServerUniqueFlagIdType, MapServerInfo*>::iterator iter = mapServerList->begin();
		for ( ; iter != mapServerList->end(); ++iter)
		{
			MapServerInfo* serverInfo = iter->second;
			
			const U64 serverUniqueFlag = serverInfo->serverUniqueFlag; 
			for (std::map< I32, MapServerInfo* >::iterator  connectServerIt = mConnectMapServerList.begin();
				connectServerIt != mConnectMapServerList.end(); 
				++connectServerIt )
			{
				MapServerInfo* mapInfo = connectServerIt->second;
				if (NULL != mapInfo && serverUniqueFlag == mapInfo->serverUniqueFlag)
				{
					serverInfo->netId		= mapInfo->netId;
					serverInfo->serverId	= mapInfo->serverId;
					serverInfo->clientNum	= mapInfo->clientNum;
					serverInfo->isValid		= true;
				}
			}
		}
#endif
	}
#endif
	//-------------------------------------------------------------------------------
	void ServerManager::openReginObjectByDistrictId(const DistrictIdType districtId, const NetIdType mapServerNetId)
	{
		//州 大地图
		{
			std::map<MapDistributionIdType, SMapDistribution*>*	mapObjList = SWorldManager::getInstance().getMapDistributionObjList();
			std::map<MapDistributionIdType, SMapDistribution*>::iterator iter = mapObjList->begin();
			for (; iter != mapObjList->end(); iter++)
			{
				SMapDistribution* mapObj = iter->second;

				DYNAMIC_ASSERT(mapObj->getDistrictRankType() == DRT_ZHOU);

				if (mapObj->getDistrictId() == districtId)
				{
					iter->second->setMapServerNetId(mapServerNetId);
				}
			}
		}

		// Place 开启
		{
			std::map<PlaceIdType, SPlaceObject*>*	placeObjList = SWorldManager::getInstance().getPlaceObjectList();
			std::map<PlaceIdType, SPlaceObject*>::iterator iter = placeObjList->begin();
			for (; iter != placeObjList->end(); iter++)
			{
				SPlaceObject* tempObj = iter->second;

				DYNAMIC_ASSERT(tempObj->getDistrictRankType() == DRT_ZHOU ||
					tempObj->getDistrictRankType() == DRT_JUN || 
					tempObj->getDistrictRankType() == DRT_XIAN);

				if (tempObj->getDistrictId() == districtId)
				{
					iter->second->setMapServerNetId(mapServerNetId);
				}
			}
		}
	}

	//-------------------------------------------------------------------------------
	void ServerManager::openReginObjectBySlaveDistrictInfo(DistrictListCsvInfo* childDistrictListCsvInfo, const NetIdType mapServerNetId)
	{
		std::map<DistrictIdType, DistrictListCsvInfo*>* slaveList =  childDistrictListCsvInfo->getSlaveList();
		
		//把自己激活
		openReginObjectByDistrictId(childDistrictListCsvInfo->getDistrictId(), mapServerNetId);

		//激活儿子节点的place
		for (std::map<DistrictIdType, DistrictListCsvInfo*>::iterator iter = slaveList->begin(); iter != slaveList->end(); ++iter)
		{
			openReginObjectBySlaveDistrictInfo(iter->second, mapServerNetId);
		}
	}

#if 0
	//-----------------------------------------------------------------------
	void ServerManager::setRegionObjectMapServerId()
	{
		std::map<ServerUniqueFlagIdType, MapServerConnectInfo*>::iterator iter = mConnectMapServerList->begin();
		for ( ; iter != mConnectMapServerList->end(); ++iter)
		{
			MapServerConnectInfo* serverInfo = iter->second;

			const NetIdType mapServerNetId = getMapServerIdByUniqueFlag(serverInfo->mServerUniqueFlag);
			if (mapServerNetId < 0)
			{
				return;
			}

			std::vector<DistrictIdType>	allRegionZhouIdVec;	//找到跟
			{
				std::map<MapDistributionIdType, SMapDistribution*>* mapList = SWorldManager::getInstance().getMapDistributionObjList();
				std::map<MapDistributionIdType, SMapDistribution*>::iterator iter = mapList->begin();
				for (; iter != mapList->end(); iter++)
				{
					SMapDistribution* tempRegionObj = iter->second;
					DYNAMIC_ASSERT(tempRegionObj->getRegionType() == ROT_MAP_DISTRIBUTION);
					DYNAMIC_ASSERT(tempRegionObj->getDistrictRankType() == DRT_ZHOU);
					allRegionZhouIdVec.push_back(tempRegionObj->getDistrictId());

				}
			}

			DYNAMIC_ASSERT(false == allRegionZhouIdVec.empty());

			//找MapServer分配方式
			const MapDistributionType mapServerId = (MapDistributionType)(serverInfo->mMapServerIndex  +1);
			std::vector<DistrictIdType> myOpenDistrictId;
			for (std::vector<DistrictIdType>::iterator iter = allRegionZhouIdVec.begin(); 
				iter != allRegionZhouIdVec.end(); 
				++iter)
			{
				SMapDistribution* mapObj = SWorldManager::getInstance().getMapDistributionByDistrictId(*iter);
				if (mapObj->getMapDistributionType() == mapServerId)
				{
					myOpenDistrictId.push_back(*iter);
				}
			}

			if (myOpenDistrictId.empty())
			{
				return;
			}

			DYNAMIC_ASSERT(false == myOpenDistrictId.empty());

			
			//由我开启的州列表里的地图全部开启来
			for (std::vector<DistrictIdType>::iterator iter = myOpenDistrictId.begin(); 
				iter != myOpenDistrictId.end(); 
				++iter)
			{
				DistrictListCsvInfo* districtChildNode = District::getInstance().getDistrictInfo(*iter);
				//openReginObjectBySlaveDistrictInfo(districtChildNode, mapServerNetId);
			}
		}

		int kk = 0;
	}
#endif

	//-----------------------------------------------------------------------
	void ServerManager::setAllMapObjectByDisConnectMapServer(const I32 mapServerNetId)
	{
		//州 大地图
		{
			std::map<MapDistributionIdType, SMapDistribution*>*	mapObjList = SWorldManager::getInstance().getMapDistributionObjList();
			std::map<MapDistributionIdType, SMapDistribution*>::iterator iter = mapObjList->begin();
			for (; iter != mapObjList->end(); iter++)
			{
				SMapDistribution* mapObj = iter->second;

				DYNAMIC_ASSERT(mapObj->getDistrictRankType() == DRT_ZHOU);

				if (mapObj->getDistrictId() == districtId)
				{
					iter->second->setMapServerNetId(0);
				}
			}
		}

		// Place 开启
		{
			std::map<PlaceIdType, SPlaceObject*>*	placeObjList = SWorldManager::getInstance().getPlaceObjectList();
			std::map<PlaceIdType, SPlaceObject*>::iterator iter = placeObjList->begin();
			for (; iter != placeObjList->end(); iter++)
			{
				SPlaceObject* tempObj = iter->second;

				DYNAMIC_ASSERT(tempObj->getDistrictRankType() == DRT_ZHOU ||
					tempObj->getDistrictRankType() == DRT_JUN || 
					tempObj->getDistrictRankType() == DRT_XIAN);

				if (tempObj->getDistrictId() == districtId)
				{
					iter->second->setMapServerNetId(0);
				}
			}
		}
	}

    //-----------------------------------------------------------------------
	void ServerManager::addActiveMapServer(NetIdType netId, ServerIdType serverId,ServerUniqueFlagIdType serverUniqueFlag)
	{
#if 0
		if (true == mActiveMapServerNetListMap.hasData(serverUniqueFlag))
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		MapServerInfo* mapServerInfo = mActiveMapServerNetListMap.createOrRetrieve(serverUniqueFlag);
		mapServerInfo->serverUniqueFlag = serverUniqueFlag;
		mapServerInfo->mapServerNum		= mapServerNum;
		mapServerInfo->mapServerIndex	= mapServerIndex;
		mapServerInfo->isValid			= false;
		mapServerInfo->netId			= -1;

		mMapServerNum++;
		mActiveMapServerVector.push_back(mapServerInfo);
#endif
	}

#if 0
    //-----------------------------------------------------------------------
	MapServerInfo* ServerManager::getActiveMapServerByNetId(const NetIdType netId )
	{
#if 0
		MapServerConnectInfo* mapServerInfo = NULL;
		std::map<ServerUniqueFlagIdType, MapServerConnectInfo*>::iterator iter = mActiveMapServerList->begin();
		for ( ; iter != mActiveMapServerList->end(); ++iter)
		{	
			mapServerInfo  = iter->second;
			if (NULL != iter->second
				&& iter->second->netId == netId 
				&& iter->second->isValid)
			{
				mapServerInfo = iter->second;
				break;
			}
		}
		return mapServerInfo;
#endif
		return NULL;
	}
#endif

	//-----------------------------------------------------------------------
	void ServerManager::removeActiveMapServer( NetIdType netId )
	{
#if 0
		//1.
		{
			std::map< NetIdType, MapServerInfo* >::iterator it = mConnectMapServerList.find(netId);
			if (it != mConnectMapServerList.end())
			{
				MG_SAFE_DELETE(it->second);
				mConnectMapServerList.erase(it);
			}
		}

		//2.
		{
			std::map<ServerUniqueFlagIdType, MapServerInfo*>*	mapServerList = mActiveMapServerNetListMap.getDataSet();
			std::map<ServerUniqueFlagIdType, MapServerInfo*>::iterator activeServerIt = mapServerList->begin();
			for (; activeServerIt != mapServerList->end(); activeServerIt++)
			{
				MapServerInfo* mapServerInfo = activeServerIt->second;
				if ( NULL != mapServerInfo  &&
					mapServerInfo->netId == netId )
				{
					mActiveMapServerNetListMap.destroy(activeServerIt);
					mMapServerNum--;
					break;
				}
			}
		}

		//3.
		{
			std::vector<MapServerInfo*>::iterator iter = mActiveMapServerVector.begin();
			for (; iter != mActiveMapServerVector.end(); iter++)
			{
				MapServerInfo* temp = *iter;
				if ( (NULL != temp)  && (temp->netId == netId) )
				{
					mActiveMapServerVector.erase(iter);
					break;
				}
			}
		}
#endif
	}

	//-------------------------------------------------------------------------------
	void ServerManager::sendNetPacketToActiveMapServerByRegionId(GameNetSendDataBufferPtr& dataPtr,
        I32 dataSize,REGION_OBJ_TYPE regionType, RegionIdType regionId)
	{
		SRegionObjectBase* region = SWorldManager::getInstance().getRegionObject(regionType, regionId);
		DYNAMIC_ASSERT(NULL != region);
		const NetIdType mapServerNetId = region->getMapServerNetId();
		DYNAMIC_ASSERT(mapServerNetId > 0);
		sendNetPacketToActiveMapServerByNetId(dataPtr, dataSize , mapServerNetId);
	}

	//-----------------------------------------------------------------------
	void ServerManager::sendNetPacketToActiveMapServerByNetId( GameNetSendDataBufferPtr& dataPtr,
        I32 dataSize, NetIdType mapServerId)
	{
		FrontServerMain::getInstance().getServerLauncher()->sendServer(dataPtr,dataSize,mapServerId);
	}

	//-----------------------------------------------------------------------
	NetIdType ServerManager::getRandActiveMapServerNetId()
	{
#if 0
		static Int num = 0;
		if (num++ >= 555)
		{
			num = 0;
		}

        DYNAMIC_ASSERT_LOG(mMapServerNum > 0 , "ServerManager::getRandMapServerNetId : not find map server");
		Int index = num % mMapServerNum;

		MapServerInfo* mapServerInfo = mActiveMapServerVector[index];
        DYNAMIC_ASSERT_LOG(mapServerInfo->isValid == true , "ServerManager::getRandMapServerNetId : map server is unactive");
		const NetIdType mapServerNetId = mapServerInfo->netId;
		DYNAMIC_ASSERT(mapServerNetId > 0);
        DYNAMIC_ASSERT_LOG(mMapServerNum > 0 , "ServerManager::getRandMapServerNetId : not find map server");

		return mapServerNetId;
#endif
		return 0;
	}

#if 0
	//-----------------------------------------------------------------------
	void ServerManager::broadOrSendNetPacketToActiveMapServer(GameNetSendDataBufferPtr& dataPtr,
        I32 dataSize, NetIdType mapServerId)
	{
		if (mapServerId > 0)
		{
			//sendNetPacketToActiveMapServerByNetId(dataPtr, dataSize, mapServerId);
		}
		else
		{
			//boardcastNetPacketToAcitveMapServer(dataPtr, dataSize);
		}
	}
#endif

    //-----------------------------------------------------------------------
    void ServerManager::removeAllActiveMapServer()
    {
#if 0
        std::map< I32, MapServerInfo* >::iterator front = mConnectMapServerList.begin();
        std::map< I32, MapServerInfo* >::iterator end = mConnectMapServerList.end();
        if (front != end)
        {
            MG_SAFE_DELETE(front->second);
            ++front;
        }
		mConnectMapServerList.clear();
#endif
    }

	//-----------------------------------------------------------------------
	Bool ServerManager::isMapServerCrash(const REGION_OBJ_TYPE reginType, const RegionIdType regionId)
	{
		SRegionObjectBase* region = SWorldManager::getInstance().getRegionObject(reginType, regionId);
		

		if (NULL == region)
		{
			return true;
		}

		if (region->getRegionType() == ROT_TIRO || 
			region->getRegionType() == ROT_PVE	||
			region->getRegionType() == ROT_HOME)
		{
			return false;
		}

		return region->getMapServerNetId() <= 0;
	
	}

	//-----------------------------------------------------------------------
	void ServerManager::closeAllClientsByMapServerId(I32 mapServerNetId)
	{
#if 0
		// 遍历playerList
		SPlayerPtr player;
		I32 currPlayerIndex = 0;
		NetIdType clientId = -1;
		Bool isContinue = true;
		while(isContinue)
		{
			isContinue = SWorldManager::getInstance().getGameObjectManager()->traversalPlayerList(currPlayerIndex,clientId,player);
			if (!isContinue)
			{
				break;
			}
			if (player->getMapServerNetID() == mapServerNetId)
			{
				FrontServerMain::getInstance().getServerLauncher()->closeClient(clientId);
			}
		}
#endif
	}

	//-----------------------------------------------------------------------
	void ServerManager::syncAllListEndToMapServer(NetIdType mapServerId)
	{	
#if 0
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		// 遍历playerList
		SPlayerPtr player;
		I32 currPlayerIndex = 0;
		NetIdType clientId = -1;
		Bool isContinue = true;
		while(isContinue)
		{
			isContinue = SWorldManager::getInstance().getGameObjectManager()->traversalPlayerList(currPlayerIndex,clientId,player);
			if (!isContinue)
			{
				break;
			}
			if (!player.isNull())
			{
				PlayerNetPacketProcesser::getInstance().broadcastPlayerLoginToMapServer(player, mapServerId);
				PlayerNetPacketProcesser::getInstance().broadcastPlayerCharacterListToMapServer(player, mapServerId);
				PlayerNetPacketProcesser::getInstance().broadcastTroopGroupListToMapServer(player, mapServerId);
			}
		}
		PlayerNetPacketProcesser::getInstance().broadcastAllListEndToMapServer(mapServerId);
#endif
	}

	

	//-----------------------------------------------------------------------
	void ServerManager::handleSyncServerStateNewStart(PT_SERVER_STATE_S2S_SYNC_MAPSERVER_STATE_NEW_START_DATA* data)
	{
		mMapServerNum = 0;
		//mActiveMapServerVector.clear();
		//mActiveMapServerNetListMap.destroyAll();
	}

	NetIdType ServerManager::getLoginServerNetId()
	{
		return mLoginServerConnect.getNetId();
	}
	NetIdType ServerManager::getCenterServerNetId()
	{
		return mCenterServerConnect.getNetId();
	}
	NetIdType ServerManager::getChatServerNetId()
	{
		return mChatServerConnect.getNetId();
	}	

	NetIdType ServerManager::getMapServer(NetIdType netId)
	{
		return netId;
	}
	//-----------------------------------------------------------------------
	void ServerManager::handleSyncServerStateNew(PT_SERVER_STATE_S2S_SYNC_MAPSERVER_STATE_NEW_DATA* data)
	{
		addActiveMapServer(data->serverUniqueFlag, data->mapServerNum, data->mapServerIndex);
		
		//copyConnectMapServerListToActiveMapServerList();
		
		//setRegionObjectMapServerId();

		MG_LOG(out_sys, "handleSyncServerStateNew， 打印开始\n");
		printServer();
		SWorldManager::getInstance().printWorldObject();
		MG_LOG(out_sys, "handleSyncServerStateNew， 打印结束\n");
	}

#if 0
	//-----------------------------------------------------------------------
	NetIdType ServerManager::getMapServerIdByUniqueFlag(const ServerUniqueFlagIdType serverUniqueFlag) 
	{
#if 0
		MapServerInfo* mapServerInfo = mActiveMapServerNetListMap.getData(serverUniqueFlag);

		if (NULL == mapServerInfo || 
			false == mapServerInfo->isValid )
		{
			//DYNAMIC_ASSERT(0);
			return 0;
		}

		return mapServerInfo->netId;
#endif
	}
#endif
	//-----------------------------------------------------------------------
	void ServerManager::sendNetPacketToCenterServer(GameNetSendDataBufferPtr& dataPtr,I32 dataSize)
	{
		//DYNAMIC_ASSERT(mCenterServerNetID > 0);
		//FrontServerMain::getInstance().getServerLauncher()->sendServer(dataPtr,dataSize,mCenterServerNetID);
	}

	//-------------------------------------------------------------------------------
	/*std::map<ServerUniqueFlagIdType, ServerConnectInfo*>* ServerManager::getActiveMapServerList()
	{
		return mActiveMapServerNetListMap.getDataSet();
	}*/

	void ServerManager::sendNetPacketToLoginServer(GameNetSendDataBufferPtr& dataPtr,I32 dataSize)
	{

	}
}
