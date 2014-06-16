/******************************************************************************/

#include "stdafx.h"
#include "CCampaignManager.h"
#include "CCampaign.h"
//#include "CClientNew.h"
#include "ClientManager.h"
#include "CampaignNetPacketProcesser.h"
#include "CRegionManager.h" 
#include "InstanceListCsv.h"
#include "MainFrm.h"
#include "MGRobot.h"
#include "CampaignPage.h"
#include "MapListCsv.h"
/******************************************************************************/

namespace MG
{
	//-----------------------------------------------------------------------------
	CCampaignManager::CCampaignManager()
	{
		mIsInit = false;
		mIsCanCreate = false;
	}

	//-----------------------------------------------------------------------------
	CCampaignManager::~CCampaignManager()
	{

	}

	MG::Bool CCampaignManager::createCampaign( Int campaignNum,Int armyNum )
	{
		//  预分配战场
		// 预分配战场 以及预分配玩家
		std::map<I32,CClient*>* clients = ClientManager::getInstance().getFrontClients();
		std::map<I32,CClient*>::size_type size = clients->size();
		if (campaignNum < 0 || campaignNum > mRegionsCanCreate.size())
		{
			return false;
		}
		if (size < armyNum 
			|| size < (campaignNum - 1) * armyNum + 2 
			|| size < 2)
		{
			return false;
		}
		std::vector<CClient*> tempClientsAttack;
		std::vector<CClient*> tempClientsDefense;
		Int i = 0;
		Int campCount = 0;
		std::map<RegionIdType,Str16>::iterator itRegion = mRegionsCanCreate.begin();
		for (std::map<I32,CClient*>::iterator it = clients->begin(); it != clients->end(); it++)
		{
			if( i % 2 == 0)
			{
				tempClientsAttack.push_back(it->second);
			}
			else
			{
				tempClientsDefense.push_back(it->second);
			}

			if (i % armyNum == armyNum - 1 || i == size - 1)
			{
				if (campCount >= campaignNum)
				{
					break;
				}
				CCampaign* campagin = MG_NEW CCampaign();	
				campagin->setOwned(true);
				campagin->addMember(FORCE_ATTACK,tempClientsAttack);
				campagin->addMember(FORCE_DEFENSE,tempClientsDefense);
				
				tempClientsAttack.clear();
				tempClientsDefense.clear();

				campagin->setRegionId(itRegion->first);
				mRegionsCanntCreate[itRegion->first] = itRegion->second;
				itRegion = mRegionsCanCreate.erase(itRegion);
				DYNAMIC_ASSERT(campagin->getHost()->getPlayerObj()->getActiveClan());
				mCampaigns[campagin->getHost()->getPlayerObj()->getActiveClan()->getClanID()] = campagin;
				campCount++;
			}
			i++;
		}
		((CMainFrame*)theApp.m_pMainWnd)->GetCampaignPage()->uiFlash();
		return true;
	}
	//-----------------------------------------------------------------------------
	CCampaign* CCampaignManager::getCampaign( CampaignIdType id )
	{
		std::map<CampaignIdType,CCampaign*>::iterator it = mCampaigns.find(id);
		if (it != mCampaigns.end())
		{
			return it->second;
		}
		return NULL;
	}
	//-----------------------------------------------------------------------------
	void CCampaignManager::addCampaign( CampaignIdType id,CCampaign* campaign )
	{
		campaign->setCampaignId(id);
		mCampaigns[id] = campaign;
	}
	//-----------------------------------------------------------------------------
	void CCampaignManager::netCreateCampaign()
	{
		for (std::map<CampaignIdType,CCampaign*>::iterator it = mCampaigns.begin(); it != mCampaigns.end(); it++)
		{
			CCampaign* campaign = it->second;
			if (campaign && campaign->isOwned())
			{
				campaign->netCreateCampaign();
			}
		}
	}
	//-----------------------------------------------------------------------------
	void CCampaignManager::netGetCampaignList()
	{
		map<I32,CClient*>* clients = ClientManager::getInstance().getDataSet();
		if (clients)
		{
			for (map<I32,CClient*>::iterator it = clients->begin(); it != clients->end(); it++)
			{
				CClient* client = it->second;
				if (client)
				{
					CampaignNetPacketProcesser::getInstance().sendCampaignList(client->getFrontServerNetId());
					break;
				}
			}
		
		}		
	}
	//-----------------------------------------------------------------------------
	std::map<RegionIdType,Str16>* CCampaignManager::getRegionsCanCreate()
	{
		return &mRegionsCanCreate;
	}
	//-----------------------------------------------------------------------------
	void CCampaignManager::init()
	{
        
		mRegionsCanCreate.clear();
		mRegionsCanntCreate.clear();
		//读取所有列表
		std::map<PlaceIdType, CPlaceObject*>* placeList = CRegionManager::getInstance().getPlaceObjectList();
		for(std::map<PlaceIdType, CPlaceObject*>::iterator iter = placeList->begin(); iter != placeList->end(); ++iter)
		{
			//以后需要 读取副本信息 来确定 是否是 战场副本
			PlaceListCsvInfo* placeListCsvInfo = iter->second->getPlaceListCsvInfo();
			InstanceListCsvInfo* instanceInfo = InstanceListCsv::getInstance().getInfoById(placeListCsvInfo->instanceId);
			if (NULL != instanceInfo && InstanceType_Atk == instanceInfo->instanceType)
			{
				wstring strId;
				MGStrOp::toString(iter->first, strId);
				strId = placeListCsvInfo->placeName  + strId;

				mRegionsCanCreate[iter->first] = strId;
			}
		}
		
		netGetCampaignList();
        mIsCanCreate =true;	
	}
	//-----------------------------------------------------------------------------
	void CCampaignManager::removeCampaign( CampaignIdType id )
	{
		std::map<CampaignIdType,CCampaign*>::iterator it = mCampaigns.find(id);
		if (it != mCampaigns.end())
		{
			//mRegionsCanCreate[it->second->getCampaignTargetRegionId()] = it->second->
			MG_SAFE_DELETE(it->second);
			mCampaigns.erase(it);
		}
		
		
	}
	//-----------------------------------------------------------------------------
	MG::Bool CCampaignManager::isAllCampaignEnd()
	{
		if (mCampaigns.empty())
		{
			return true;
		}
		return false;
	}
	//-----------------------------------------------------------------------------
	std::map<RegionIdType,Str16>* CCampaignManager::getRegionsCanntCreate()
	{
		return &mRegionsCanntCreate;
	}
	//-----------------------------------------------------------------------------
	std::map<CampaignIdType,CCampaign*>* CCampaignManager::getCampaigns()
	{
		return &mCampaigns;
	}
	//-----------------------------------------------------------------------------
	std::map<RegionIdType,Str16>*		 CCampaignManager::getCanCreateRegions()
	{
		return &mRegionsCanCreate;
	}
	//-----------------------------------------------------------------------------
	RegionIdType CCampaignManager::getCanCreateRegion()
	{
		if (mRegionsCanCreate.empty())
		{
			return 0;
		}
		std::map<RegionIdType,Str16> ::iterator it = mRegionsCanCreate.begin();
		return it->first;
	}
	//-----------------------------------------------------------------------------
	void CCampaignManager::removeCreateRegion( RegionIdType id,Bool canCreate )
	{
		if (canCreate)
		{
			std::map<RegionIdType,Str16>::iterator it = mRegionsCanCreate.find(id);
			if (it != mRegionsCanCreate.end())
			{
				mRegionsCanntCreate[id] = it->second;
				mRegionsCanCreate.erase(it);
			}
		}
		else
		{
			std::map<RegionIdType,Str16>::iterator it = mRegionsCanntCreate.find(id);
			if (it != mRegionsCanntCreate.end())
			{
				mRegionsCanCreate[id] = it->second;
				mRegionsCanntCreate.erase(it);
			}
		}
		
	}
	//-----------------------------------------------------------------------------
	CCampaign* CCampaignManager::getCampaignByRegionId( RegionIdType id )
	{
		std::map<CampaignIdType,CCampaign*>::iterator it = mCampaigns.begin();
		for (; it != mCampaigns.end(); it++)
		{
			if (it->second->getCampaignTargetRegionId() == id)
			{
				return it->second;
			}
		}
		return NULL;
	}
	//-----------------------------------------------------------------------------
	CCampaign* CCampaignManager::getCampaignByRegionId( RegionIdType id, CampaignIdType& campaignId )
	{
		std::map<CampaignIdType,CCampaign*>::iterator it = mCampaigns.begin();
		for (; it != mCampaigns.end(); it++)
		{
			if (it->second->getCampaignTargetRegionId() == id)
			{
				campaignId = it->first;
				return it->second;
			}
		}
		campaignId = 0;
		return NULL;
	}
	//-----------------------------------------------------------------------------
	void CCampaignManager::startBattle()
	{
		std::map<CampaignIdType,CCampaign*>::iterator it = mCampaigns.begin();
		for (; it != mCampaigns.end(); it++)
		{
			if (it->second->isOwned())
			{
				it->second->startBattle();
			}
		}
	}
	//-----------------------------------------------------------------------------
	MG::Bool CCampaignManager::isCanCreate()
	{
         if (mIsCanCreate)
         {
			 return true;
         }
		 return false;
	}

	
	//-----------------------------------------------------------------------------

}
