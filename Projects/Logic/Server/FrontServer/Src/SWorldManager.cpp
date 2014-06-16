
/******************************************************************************/

#include "stdafx.h"
#include "SWorldManager.h"
#include "SPlayer.h"
#include "PlayerCharacterData.h"
#include "LoginNetPacketProcesser.h"
#include "PlayerNetPacketProcesser.h"
#include "CampaignNetPacketProcesser.h"
#include "SPveNetPacketProcessor.h"
#include "ServerManager.h"
#include "RegionDevideAlgorithm.h"
#include "FrontServerMain.h"
#include "SHeartBeatManager.h"
#include "ClientManager.h"
#include "PlayerCharacterNetPacketProcesser.h"
#include "SGeneralRecruitNetPacketProcessor.h"
#include "SysLogNetPacketProcesser.h"

/******************************************************************************/

namespace MG
{

	//--------------------------------------------------------------------------
	SWorldManager::SWorldManager( )
		:mHeartBeatManager(NULL)
	{

	}

	//--------------------------------------------------------------------------
	SWorldManager::~SWorldManager( )
	{

	}

	//-----------------------------------------------------------------------------
	Bool SWorldManager::initialize(ServerLauncherInterface* launcher)
	{
		if (false == mRegionObjectManager.loadCsvAndCreateRegion())
		{
			DYNAMIC_ASSERT(0);
			return false;
		}
	
		//mHeartBeatManager = MG_NEW SHeartBeatManager;
		//mHeartBeatManager->setHeartBeatTimeLength(100000);

		return true;
	}

    //-----------------------------------------------------------------------------
    Bool SWorldManager::unInitialize()
    {
        MG_SAFE_DELETE( mHeartBeatManager );

        return true;
    }

    //-----------------------------------------------------------------------------
    void SWorldManager::update()
    {
        if(mHeartBeatManager)
        {
            //mHeartBeatManager->update();
        }
    }
	//-----------------------------------------------------------------------------
	std::map<MapDistributionIdType,	SMapDistribution*>* SWorldManager::getMapDistributionObjList()
	{
		return mRegionObjectManager.getMapDistributionObjList();
	}
	//-----------------------------------------------------------------------------
	std::map<PlaceIdType, SPlaceObject*>* SWorldManager::getPlaceObjectList()
	{
		return mRegionObjectManager.getPlaceObjectList();
	}
	//-----------------------------------------------------------------------------
	std::map<InstanceIdType, STiroObject*>*	SWorldManager::getTiroObjectList()
	{
		return mRegionObjectManager.getTiroObjectList();
	}

	//-----------------------------------------------------------------------------
	SRegionObjectBase* SWorldManager::getRegionObject(const REGION_OBJ_TYPE regionType, const RegionIdType id)
	{
		return mRegionObjectManager.getRegionObject(regionType, id);
	}

	NetIdType SWorldManager::getMapServerNetIdByRegion(REGION_OBJ_TYPE regionType, RegionIdType id)
	{
		NetIdType mapServerNetId = -1;
		switch(regionType)
		{
		case ROT_MAP_DISTRIBUTION:
		case ROT_PLACE:
			{
				SRegionObjectBase* regionObj = getRegionObject(regionType, id);
				DYNAMIC_ASSERT(NULL != regionObj);
				mapServerNetId = regionObj->getMapServerNetId();
			}
			break;
		case ROT_TIRO:
		case ROT_PVE:
		case ROT_HOME:
		case ROT_PVP:
		case ROT_GROWUP:
		case ROT_HISTORY:
		case ROT_SPORT:
		case ROT_FIGHT:
		case ROT_TRAIN:
			{
				//随机分配一个MapServerNetId
				//mapServerNetId = ServerManager::getInstance().getRandMapServerNetId();
			}
			break;
		default:
			{
				DYNAMIC_ASSERT(0);
			}
			break;
		}
		DYNAMIC_ASSERT(mapServerNetId > 0);
		return mapServerNetId;
	}

	SMapDistribution* SWorldManager::getMapDistributionByDistrictId(const DistrictIdType districtId)
	{
		return mRegionObjectManager.getMapDistributionByDistrictId(districtId);
	}
	//-----------------------------------------------------------------------
	void SWorldManager::boardcastNetPacketToAllClient(GameNetSendDataBufferPtr dataPtr, I32 dataSize)
	{
		// 遍历playerList
		SPlayerPtr player;
		I32 currPlayerIndex = 0;
		NetIdType clientId = -1;
		Bool isContinue = true;
		while(isContinue)
		{
			//isContinue = SWorldManager::getInstance().getGameObjectManager()->traversalPlayerList(currPlayerIndex,clientId,player);
			if (!isContinue)
			{
				break;
			}
			FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,dataSize, clientId);
		}
	}

	//-----------------------------------------------------------------------------
	void SWorldManager::printWorldObject()
	{
		MG_LOG(out_sys, "\n=============================================================================\n ");
		MG_LOG(out_sys, "\n ------------------- FrontServer整个打印开始 ------------------- \n ");
		//4. 【RegionObject】
		mRegionObjectManager.printRegionObjectMapServerId();
		MG_LOG(out_sys, "\n -------------------FrontServer 整个打印结束 ------------------- \n ");
		MG_LOG(out_sys, "\n=============================================================================\n ");

	}

}