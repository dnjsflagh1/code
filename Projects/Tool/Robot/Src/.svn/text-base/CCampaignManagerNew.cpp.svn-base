/******************************************************************************/

#include "stdafx.h"
#include "CCampaignManagerNew.h"
#include "CCampaign.h"
#include "CClientNew.h"
#include "CampaignNetPacketProcesser.h"
#include "CRegionManager.h" 
#include "InstanceListCsv.h"
#include "MainFrm.h"
#include "MGRobot.h"
#include "CampaignPage.h"
#include "MapListCsv.h"
#include "ThreadTaskManager.h"
/******************************************************************************/

namespace MG
{
	CCampaignManager::CCampaignManager(U32 threadIndex)
	{
		mThreadIndex = threadIndex;
		mCtrlState = CampaignCtrlState_CanntStart;
		mIsEnd = false;
	}
	CCampaignManager::~CCampaignManager()
	{
		clear();
	}
	//-----------------------------------------------------------------------------
	void CCampaignManager::clear()
	{
		std::vector<CCampaign*>::iterator it = mPreassignmentCampaigns.begin();
		for (; it != mPreassignmentCampaigns.end(); it++)
		{
			MG_SAFE_DELETE(*it);
		}

		mPreassignmentCampaigns.clear();
		mOwnedCampaigns.clear();
		
		mCampaignsInServer.clear();

		mRegionsCanCreate.clear();
		mRegionsCanntCreate.clear();
	}
	//-----------------------------------------------------------------------------
	Int CCampaignManager::preassignmentCampaignList( Int campaignNum,Int armyNum,U32 time )
	{
		clear();

		resetRegions();
		std::map<RegionIdType,Str16>::iterator itRegion = mRegionsCanCreate.begin();
		/////////////////////////////////////////////////////////////////////////////////////

		std::vector<CClient*>* clients = ThreadTaskManager::getInstance().getThreadClientVec(mThreadIndex);
		if (!clients)
		{
			return -1;
		}
		std::vector<CClient*>::size_type size = clients->size();
		if (size < armyNum
			|| size < 2)
		{
			return campaignNum;
		}
		std::vector<CClient*> tempClientsAttack;
		std::vector<CClient*> tempClientsDefense;
		Int i = 0;
		Int campCount = 0;

		for (std::vector<CClient*>::iterator it = clients->begin(); it != clients->end(); it++)
		{
			if( i % 2 == 0)
			{
				tempClientsAttack.push_back(*it);
			}
			else
			{
				tempClientsDefense.push_back(*it);
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
				
				campagin->setRegionId(itRegion->first);
				tempClientsAttack.clear();
				tempClientsDefense.clear();
				campagin->setState(CCAMPAIGN_STATE_PREASSIGNMENT);
				mPreassignmentCampaigns.push_back(campagin);
				campCount++;
			}
			i++;
		}
		
		if (time)
		{
			mEndTime = MGTimeOp::getCurrTimestamp() + time;
		}
		mCtrlState = CampaignCtrlState_CanStart;
		return campaignNum - campCount;
	}
	//-----------------------------------------------------------------------------
	void CCampaignManager::getCampaignListFromServer()
	{
		std::vector<CClient*>* clients = ThreadTaskManager::getInstance().getThreadClientVec(mThreadIndex);
		if (!clients)
		{
			DYNAMIC_ASSERT_LOG(false,"找不到客户端链表");
			return;
		}
		if (clients)
		{
			for (std::vector<CClient*>::iterator it = clients->begin(); it != clients->end(); it++)
			{
				CClient* client = *it;
				if (client)
				{
					CampaignNetPacketProcesser::getInstance().sendCampaignList(client->getFrontServerNetId());
					break;
				}
			}

		}	
	}
	//-----------------------------------------------------------------------------
	void CCampaignManager::createCampaignRoomListToServer()
	{
		mIsEnd = false;
		std::vector<CCampaign*>::iterator it = mPreassignmentCampaigns.begin();
		for (; it != mPreassignmentCampaigns.end(); it++)
		{
			if ((*it)->getState() == CCAMPAIGN_STATE_PREASSIGNMENT)
			{
				(*it)->netCreateCampaign();
			}
		}
	}
	//-----------------------------------------------------------------------------
	void CCampaignManager::createCampaignListToServer()
	{
		std::vector<CCampaign*>::iterator it = mPreassignmentCampaigns.begin();
		for (; it != mPreassignmentCampaigns.end(); it++)
		{
			if ((*it)->getState() == CCAMPAIGN_STATE_PREPARED)
			{
				(*it)->startBattle();
			}
		}
	}
	//-----------------------------------------------------------------------------
	void CCampaignManager::endBattleToServer()
	{
		std::vector<CCampaign*>::iterator it = mPreassignmentCampaigns.begin();
		for (; it != mPreassignmentCampaigns.end(); it++)
		{
			if ((*it)->getState() == CCAMPAIGN_STATE_START)
			{
				(*it)->giveUpCampaign();
			}
		}
	}
	//-----------------------------------------------------------------------------
	RegionIdType CCampaignManager::getCCCRegion()
	{
		if (mRegionsCanCreate.empty())
		{
			return 0;
		}
		std::map<RegionIdType,Str16> ::iterator it = mRegionsCanCreate.begin();
		return it->first;
	}
	//-----------------------------------------------------------------------------
	std::map<RegionIdType,Str16>* CCampaignManager::getCCCRegions()
	{
		return &mRegionsCanCreate;
	}
	//-----------------------------------------------------------------------------
	std::map<RegionIdType,Str16>* CCampaignManager::getNCCRegions()
	{
		return &mRegionsCanntCreate;
	}
	//-----------------------------------------------------------------------------
	void CCampaignManager::clearCCCRegions()
	{
		mRegionsCanCreate.clear();
	}
	//-----------------------------------------------------------------------------
	void CCampaignManager::clearNCCRegions()
	{
		mRegionsCanntCreate.clear();
	}
	//-----------------------------------------------------------------------------
	void CCampaignManager::resetRegions()
	{
		std::map<PlaceIdType, CPlaceObject*>* placeList = CRegionManager::getInstance().getPlaceObjectList();
		for(std::map<PlaceIdType, CPlaceObject*>::iterator iter = placeList->begin(); iter != placeList->end(); ++iter)
		{
			//以后需要 读取副本信息 来确定 是否是 战场副本
			PlaceListCsvInfo* placeListCsvInfo = iter->second->getPlaceListCsvInfo();
			InstanceListCsvInfo* instanceInfo = InstanceListCsv::getInstance().getInfoById(placeListCsvInfo->instanceId);
			if (NULL != instanceInfo && InstanceType_Atk == instanceInfo->instanceType)
			{
				std::map<RegionIdType,CampaignIdType>::iterator itCamp = mCampaignsInServer.find(iter->first);
				wstring strId;
				MGStrOp::toString(iter->first, strId);
				strId = placeListCsvInfo->placeName  + strId;
				if (itCamp != mCampaignsInServer.end())
				{
					mRegionsCanntCreate[iter->first] = strId;
				}
				else
				{
					mRegionsCanCreate[iter->first] = strId;
				}
			}
		}
	}
	//-----------------------------------------------------------------------------
	void CCampaignManager::clearCampaignsInServer()
	{
		mCampaignsInServer.clear();
	}
	//-----------------------------------------------------------------------------
	std::map<RegionIdType,CampaignIdType>* CCampaignManager::getCampaignsInServer()
	{

		return &mCampaignsInServer;
	}
	//-----------------------------------------------------------------------------
	void CCampaignManager::addOwnedCampaignById( CampaignIdType id ,CCampaign* campaign )
	{
		mOwnedCampaigns[id] = campaign;
	}
	//-----------------------------------------------------------------------------
	std::map<CampaignIdType,CCampaign*>* CCampaignManager::getOwnedCampaigns()
	{
		return &mOwnedCampaigns;

	}
	//-----------------------------------------------------------------------------
	CCampaign* CCampaignManager::getOwnedCampaignByRegionId( RegionIdType regionId )
	{
		std::map<CampaignIdType,CCampaign*> ::iterator it = mOwnedCampaigns.begin();
		for(; it != mOwnedCampaigns.end(); it++)
		{
			if (it->second->getCampaignTargetRegionId() == regionId)
			{
				return it->second;
			}
		}
		return NULL;
	}
	//-----------------------------------------------------------------------------
	CCampaign* CCampaignManager::getOwnedCampaignById( CampaignIdType id )
	{
		std::map<CampaignIdType,CCampaign*> ::iterator it = mOwnedCampaigns.find(id);
		if (it != mOwnedCampaigns.end())
		{
			return it->second;
		}
		return NULL;
	}
	//-----------------------------------------------------------------------------
	CCampaign* CCampaignManager::removeOwnedCampaignById( CampaignIdType id )
	{
		CCampaign* campaign = NULL;
		std::map<CampaignIdType,CCampaign*> ::iterator it = mOwnedCampaigns.find(id);
		if (it != mOwnedCampaigns.end())
		{
			campaign = it->second;
			mOwnedCampaigns.erase(it);
		}
		return campaign;
	}
	//-----------------------------------------------------------------------------
	std::vector<CCampaign*> CCampaignManager::getPreassignmentCampaigns()
	{
		return mPreassignmentCampaigns;
	}
	//-----------------------------------------------------------------------------
	void CCampaignManager::assignmentCampaign()
	{
		/*std::vector<CCampaign*>::iterator it = mPreassignmentCampaigns.begin();
		std::map<RegionIdType,Str16>::iterator itRegionCanCreate = mRegionsCanCreate.begin();
		std::map<RegionIdType,Str16>::iterator itRegionCanntCreate;
		for (; it != mPreassignmentCampaigns.end(); it++)
		{
			for (itRegionCanntCreate = mRegionsCanntCreate.begin(); itRegionCanntCreate != mRegionsCanntCreate.end(); itRegionCanntCreate++)
			{
				if ((*it)->getCampaignTargetRegionId() == itRegionCanntCreate->first)
				{
					if ((*it)->getState() == CCAMPAIGN_STATE_APPLIING
						|| (*it)->getState() == CCAMPAIGN_STATE_APPLIED
						|| (*it)->getState() == CCAMPAIGN_STATE_ENTER
						|| (*it)->getState() == CCAMPAIGN_STATE_PREPARED)
					{
						(*it)->netDestoryCampaignRoom();
					}
					else if ((*it)->getState() == CCAMPAIGN_STATE_ASSIGNMENT)
					{
						(*it)->setState(CCAMPAIGN_STATE_PREASSIGNMENT);
						(*it)->setRegionId(0);
					}

				}
			}
			
			if ((*it)->getState() == CCAMPAIGN_STATE_PREASSIGNMENT)
			{
				if (itRegionCanCreate != mRegionsCanCreate.end())
				{
					(*it)->setState(CCAMPAIGN_STATE_ASSIGNMENT);
					(*it)->setRegionId(itRegionCanCreate->first);
					itRegionCanCreate++;
				}
			}
		}*/
		/////////////////////////////////////////////////////////////////

	}
	//-----------------------------------------------------------------------------
	Bool CCampaignManager::canCreateCampagin()
	{
		return true;
	}
	//-----------------------------------------------------------------------------
	Bool CCampaignManager::setCanCreateCampagin( Bool canCreate )
	{
		return true;
	}
	//-----------------------------------------------------------------------------
	void CCampaignManager::setThreadIndex( Int threadIndex )
	{
		mThreadIndex = threadIndex;
	}
	//-----------------------------------------------------------------------------
	void CCampaignManager::update()
	{
		if (mEndTime != 0 && MGTimeOp::getCurrTimestamp() >= mEndTime)
		{
			mCtrlState = CampaignCtrlState_Ending;
		}
		if (mCtrlState == CampaignCtrlState_Ending)
		{
			std::map<CampaignIdType,CCampaign*>::iterator it = mOwnedCampaigns.begin();
			for (; it != mOwnedCampaigns.end(); it++)
			{
				it->second->giveUpCampaign();
			}
		}
	}
	//-----------------------------------------------------------------------------
	Bool CCampaignManager::isTimeOut()
	{
		return MGTimeOp::getCurrTimestamp() >= mEndTime;
	}
	//-----------------------------------------------------------------------------
	void CCampaignManager::setTimeOut( U32 time )
	{
		if (time == 0)
		{
			mEndTime = 0;
		}
		else
		{
			mEndTime = time + MGTimeOp::getCurrTimestamp();
		}
		mIsEnd = false;
	}

	CampaignCtrlState CCampaignManager::getCtrlState()
	{
		return mCtrlState;
	}
	//-----------------------------------------------------------------------------
	Bool CCampaignManager::isAllCampaignEnd()
	{
		if (!mEndTime)
		{
			if (mCtrlState != CampaignCtrlState_Ending)
			{
				return false;
			}
			else
			{
				if (mCtrlState == CampaignCtrlState_Ending)
				{
					std::map<CampaignIdType,CCampaign*>::iterator it = mOwnedCampaigns.begin();
					for (; it != mOwnedCampaigns.end(); it++)
					{
						if (it->second->getState() == CCAMPAIGN_STATE_ASSIGNMENT
							||	it->second->getState() == CCAMPAIGN_STATE_APPLIING
							||	it->second->getState() == CCAMPAIGN_STATE_APPLIED
							||	it->second->getState() == CCAMPAIGN_STATE_ENTER
							||	it->second->getState() == CCAMPAIGN_STATE_PREPARED
							||	it->second->getState() == CCAMPAIGN_STATE_START
							||	it->second->getState() == CCAMPAIGN_STATE_ALL_ENTER)
						{
							return false;
						}
					}
				}
			}
			
			mEndTime = true;
			return true;
		}
		else
		{
			return true;
		}
		
	}
	//-----------------------------------------------------------------------------
}
