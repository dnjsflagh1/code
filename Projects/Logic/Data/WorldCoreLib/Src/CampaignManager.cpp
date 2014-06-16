/******************************************************************************/

#include "stdafx.h"
#include "CampaignManager.h"

/******************************************************************************/

namespace MG
{
	//-----------------------------------------------------------------------------
	CampaignManager::CampaignManager()
	{

	}

	//-----------------------------------------------------------------------------
	CampaignManager::~CampaignManager()
	{
		mOnBattleList.clearData();
		mPrepareCompaignList.destroyAll();
		
	}
	
	//-----------------------------------------------------------------------------
	void CampaignManager::update()
	{
		const U64 curTime = GetCurrentTime();
		
		checkCampaignTimeOut(curTime);
		checkCampaignDestroy(curTime);
	}

	//-----------------------------------------------------------------------------
	std::map<ClanIdType, SCampaign*>* CampaignManager::getPrepareCampaignList()
	{
		return mPrepareCompaignList.getDataSet();
	}

	//-----------------------------------------------------------------------------
	std::map<CampaignIdType, SCampaign*>* CampaignManager::getOnBattleCampaignList()
	{
		return mOnBattleList.getDataList();
	}

	std::map<ClanIdType, SCampaign*>* CampaignManager::getEndCampaignList()
	{
		return mEndBattleList.getDataList();
	}

	//-----------------------------------------------------------------------------
	SCampaign* CampaignManager::getBattleCampaign(CampaignIdType campaignId)
	{
		return mOnBattleList.getSecondData(campaignId);
	}

	//-----------------------------------------------------------------------------
	SCampaign* CampaignManager::getPrepareCampaign(CampaignIdType campaignId)
	{
		return mPrepareCompaignList.getData(campaignId);
	}

	//-----------------------------------------------------------------------------
	SCampaign* CampaignManager::popPrepareCampaign(CampaignIdType campaignId)
	{
		return mPrepareCompaignList.popData(campaignId);
	}

	SCampaign* CampaignManager::getEndCampaign(CampaignIdType campaignId)
	{
		return mEndBattleList.getSecondData(campaignId);
	}

	//-----------------------------------------------------------------------------
	void CampaignManager::destroyCampaign(CampaignIdType campaignId)
	{
		mOnBattleList.eraseData(campaignId);
		mPrepareCompaignList.destroy(campaignId);
	}

	void CampaignManager::delEndCampaign(CampaignIdType campaignId)
	{
		mEndBattleList.eraseData(campaignId);
	}

	//-----------------------------------------------------------------------------
	SCampaign* CampaignManager::createCampaign(NetIdType frontServerNetId, AccountIdType creatorAccountId, ClanIdType creatorClanId, const Char16* creatorClanName, const Char16* campaignName, 
										RegionIdType targetRegionId, REGION_OBJ_TYPE targetRegionType)
	{
		//1. ��������ͼ�Ƿ���Ȩ�޿� ���Ǹ���
		//SRealRegionObjectInRegion* targetRealRegionObjInRegion = SWorldManager::getInstance().getRealRegionObjectInRegion(targetRegionId);
		//if (NULL == targetRealRegionObjInRegion || false == targetRealRegionObjInRegion->getRealRegionList()->empty())
		//{
		//	return false;
		//}


		//2. �Ƿ��Ѿ�����ս��
		if (true == _isCampaignExist(creatorClanId))
		{
			return NULL;
		}
//#if 0
		//3. ��������Ƿ��ظ�
		if (true == _isCampaignNameExist(campaignName))
		{
			//�����ظ�
			return NULL;
		}
//#endif	//���ԣ� ��ʱ������Щ���

		////4. ��������
		//SRealRegionObject* campaignInstance = targetRealRegionObjInRegion->getRegionObjectInstanceWithCreate(creatorAccountId);
		//DYNAMIC_ASSERT(NULL != campaignInstance);
		
		//5. ����ս�� //����Ϸ��ʼ���ٴ��������� ����ս����������
		SCampaign* newCampaign = mPrepareCompaignList.createOrRetrieve<AccountIdType, ClanIdType, const Char16*, const Char16*, RegionIdType>
			(creatorClanId,creatorAccountId, creatorClanId, creatorClanName, campaignName, targetRegionId, targetRegionType);

		enterCampaignJoinAttackList(frontServerNetId, creatorAccountId, newCampaign, creatorClanId, creatorClanName);

		return newCampaign;
	}

	//-----------------------------------------------------------------------------
	Bool CampaignManager::_isCampaignExist(ClanIdType clanID)
	{
		SCampaign* prepareCompaign = mPrepareCompaignList.getData(clanID);
		if ( NULL != prepareCompaign)
		{
			return true;
		}

		SCampaign* activeCompaign = mOnBattleList.getSecondData(clanID);
		if ( NULL != activeCompaign)
		{
			return true;
		}

		return false;
	}

	//-----------------------------------------------------------------------------
	Bool CampaignManager::_isCampaignNameExist(const Char16* campaignName)
	{
		//mPrepareCompaignList ����
		{
			std::map<CampaignIdType, SCampaign*>* prepareCompaignList = mPrepareCompaignList.getDataSet();
			std::map<CampaignIdType, SCampaign*>::iterator iter = prepareCompaignList->begin();
			for (iter = prepareCompaignList->begin(); iter != prepareCompaignList->end(); ++iter)
			{
				SCampaign* campaign = iter->second;
				if(0 == WStrnCmp(campaign->getCampaignName().c_str(), campaignName, MAX_CAMPAIGN_NAME))
				{
					return true;
				}

			}
		}


		//mOnBattleList ����
		{
			std::map<CampaignIdType, SCampaign*>* BattleList = mOnBattleList.getDataList();
			std::map<CampaignIdType, SCampaign*>::iterator iter = BattleList->begin();
			for (iter = BattleList->begin(); iter != BattleList->end(); ++iter)
			{
				SCampaign* campaign = iter->second;
				if(0 == WStrnCmp(campaign->getCampaignName().c_str(), campaignName, MAX_CAMPAIGN_NAME))
				{
					return true;
				}
			}
		}

		return false;
	}

	//-----------------------------------------------------------------------------
	SCampaign* CampaignManager::enterCampaignJoinAttackList(NetIdType frontServerNetId, const AccountIdType accountId, const ClanIdType campainId, const ClanIdType myClanId, const Char16* clanName)
	{
		SCampaign* campaign = mPrepareCompaignList.getData(campainId);

		if (NULL == campaign)
		{
			return false;
		}

		return enterCampaignJoinAttackList(frontServerNetId, accountId, campaign, myClanId, clanName);
	}

	//-----------------------------------------------------------------------------
	SCampaign* CampaignManager::enterCampaignJoinAttackList(NetIdType frontServerNetId, const AccountIdType accountId, SCampaign* campaign, const ClanIdType myClanId, const Char16* clanName)
	{
		if (NULL == campaign)
		{
			return false;
		}

		Bool	bSuccess = campaign->joinAttackList(frontServerNetId, accountId, myClanId, clanName);
		if (true == bSuccess)
		{
			//�ɹ�
			Int memberNum = campaign->getAttackRealMemberNum();
			campaign->setAttackRealMemberNum(++memberNum);
			return campaign;
		}
		else
		{
			//ʧ��
			return NULL;
		}
	}

	//-----------------------------------------------------------------------------
	Bool CampaignManager::setCampaignReadyStateMySelf(CampaignIdType campaignId, ClanIdType myClanId, ARMY_READY_STATE readyState)
	{
		SCampaign* campaign = mPrepareCompaignList.getData(campaignId);

		if (NULL == campaign)
		{
			return false;
		}

		return campaign->setCampaignReadyStateMySelf(myClanId, readyState);
	}

	//-----------------------------------------------------------------------------
	Bool CampaignManager::addCampaignStart(SCampaign* campaign, U64 battleSecond)
	{
		DYNAMIC_ASSERT(NULL != campaign);
		campaign->setEndBattleTime(battleSecond);						//����ս������ʱ�� ���롿
		mOnBattleList.addData(campaign->getCampaignId(), campaign);
		return true;
	}

	//-----------------------------------------------------------------------------
	bool CampaignManager::checkCampaignTimeOut(const U64 curTime)
	{
		if (curTime < mLastCheckEndTime)
		{
			return false;
		}

		CampaignIdType endBattleCampaignId = 0;
		mLastCheckEndTime = curTime + 2*1000;

		std::map<CampaignIdType, SCampaign*>* battleList = mOnBattleList.getDataList();
		for ( std::map<CampaignIdType, SCampaign*>::iterator iter = battleList->begin(); 
			iter != battleList->end(); )
		{
			SCampaign* tempCampaign = iter->second;
			if (curTime >= tempCampaign->getEndBattleTime())
			{
				//�ҵ� ʱ�䵽��ս��
				endBattleCampaignId = iter->first;
				break;
			}
			else
			{
				++iter;
			}
		}

		if (endBattleCampaignId > 0)
		{
			SCampaign* endCampaign = mOnBattleList.getSecondData(endBattleCampaignId);

			sendCampaignEndPacket(endCampaign, FORCE_DEFENSE);
			InstanceTimeListCsvInfo* instanceTimeListInfo = endCampaign->getTimeListInfo();
			DYNAMIC_ASSERT(instanceTimeListInfo->time4 + instanceTimeListInfo->time5 <= instanceTimeListInfo->time6);
			endCampaign->setDestroyBattleTime(instanceTimeListInfo->time6);
			mEndBattleList.addData(endBattleCampaignId, endCampaign);

			mOnBattleList.eraseData(endBattleCampaignId);
		}
	

		return true;

	}

	//-----------------------------------------------------------------------------
	bool CampaignManager::checkCampaignDestroy(const U64 curTime)
	{
		if (curTime < mLastCheckDestroyTime)
		{
			return false;
		}

		mLastCheckDestroyTime = curTime + 2*1000;

		std::map<CampaignIdType, SCampaign*>* endBattleList = mEndBattleList.getDataList();

		for ( std::map<CampaignIdType, SCampaign*>::iterator iter = endBattleList->begin(); 
			iter != endBattleList->end(); )
		{
			SCampaign* tempCampaign = iter->second;
			if (curTime >= tempCampaign->getDestroyBattleTime())
			{
				//�ҵ� ʱ�䵽��ս�������б�ɾ��ս��
				DYNAMIC_ASSERT(tempCampaign->getWinnerForce() == FORCE_ATTACK || 
					tempCampaign->getWinnerForce() == FORCE_DEFENSE);

				sendCampaignDestroyPacket(iter->second, tempCampaign->getWinnerForce());
				endBattleList->erase(iter++);
			}
			else
			{
				++iter;
			}
		}

		return true;

	}

	//-----------------------------------------------------------------------------
	void CampaignManager::clear()
	{
		//mPrepareCompaignList.destroyAll();
		//mOnBattleList.destroyAll();
	}

	//-----------------------------------------------------------------------------
	void CampaignManager::clearPrepareCampaign()
	{
		mOnBattleList.clearData();
		mPrepareCompaignList.destroyAll();
	}
	//-----------------------------------------------------------------------------
	void CampaignManager::mainCampDestroy(const CampaignIdType campaignId, const FORCE winnerForce)
	{
		SCampaign* endCampaign = mOnBattleList.getSecondData(campaignId);

		sendCampaignEndPacket(endCampaign, winnerForce);
		endCampaign->setDestroyBattleTime(7);
		mEndBattleList.addData(campaignId, endCampaign);

		mOnBattleList.eraseData(campaignId);
	}

	//-----------------------------------------------------------------------------
}