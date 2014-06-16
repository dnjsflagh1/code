/******************************************************************************/

#include "stdafx.h"
#include "CCampaign.h"
#include "CClientNew.h"
#include "CampaignNetPacketProcesser.h"
/******************************************************************************/
namespace MG
{
	//-----------------------------------------------------------------------------
	CCampaign::CCampaign()
	{
		mIsOwned = false;
		mState = CCAMPAIGN_STATE_NULL;
		mMemberNum = 0;
		mCycleCount = 0;
		mCampaignId = 0;
	}

	//-----------------------------------------------------------------------------
	CCampaign::~CCampaign()
	{
		clear();
	}

	//-----------------------------------------------------------------------------
	Str16& CCampaign::getCampaignName()
	{
		return mCampaignName;
	}
	//-----------------------------------------------------------------------------
	RegionIdType CCampaign::getCampaignTargetRegionId() const
	{
		return mCampaignTargetRegionId;
	}
	//-----------------------------------------------------------------------------
	void CCampaign::setCampaignInstanceId(InstanceUIdType campaignInstanceUid)
	{
		mCampaignInstanceUid = campaignInstanceUid;
	}
	//-----------------------------------------------------------------------------
	InstanceUIdType CCampaign::getCampaignInstance()
	{
		return mCampaignInstanceUid;
	}
	//-----------------------------------------------------------------------------
	void CCampaign::setBattleTime(const U64 seconds)
	{ 
		mEndBattleTime = GetCurrentTime() + (seconds * 1000); 
	}

	//-----------------------------------------------------------------------------
	U64 CCampaign::getBattleTime() const
	{
		return mEndBattleTime;
	}
	//-----------------------------------------------------------------------------
	Int CCampaign::getMemberNum() const
	{
		return mMemberNum;
	}
	//-----------------------------------------------------------------------------
	void CCampaign::netCreateCampaign()
	{
		if (mState != CCAMPAIGN_STATE_PREASSIGNMENT)
		{
			return;
		}
		if (!isOwned())
		{
			return;
		}
		mCycleCount++;
		CampaignNetPacketProcesser::getInstance().sendCampaignCreate(
			mClanAttackHost->getFrontServerNetId(),
			mClanAttackHost->getPlayerObj()->getActiveClan()->getClanID(),
			getCampaignTargetRegionId(),
			mClanAttackHost->getPlayerObj()->getActiveClan()->getName().c_str());
	}
	//-----------------------------------------------------------------------------
	void CCampaign::addMember( FORCE force,std::vector<CClient*>& members )
	{
		Int index = 0;
		if (force == FORCE_ATTACK)
		{
			mClanAttackHost = members[0];
			for (std::vector<CClient*>::iterator it = members.begin(); it != members.end();it++)
			{
				mClanAttackList[*it] = MG_NEW CCampaignArmyInfo();
				mMemberNum++;
				(*it)->setCampaign(this);
			}
			
		}
		else if(force == FORCE_DEFENSE)
		{
			for (std::vector<CClient*>::iterator it = members.begin(); it != members.end();it++)
			{
				mClanDenfenseList[*it] = MG_NEW CCampaignArmyInfo();
				mMemberNum++;
				(*it)->setCampaign(this);
			}
		}
		else
		{
			DYNAMIC_ASSERT(false);
		}
	}
	//-----------------------------------------------------------------------------
	void CCampaign::enterCampaign()
	{
		if (isOwned())
		{
			if (mClanAttackHost && mState == CCAMPAIGN_STATE_APPLIED)
			{
				std::map<CClient*,CCampaignArmyInfo*>::iterator it = mClanAttackList.begin();
				for (; it != mClanAttackList.end(); it++)
				{
					CClient* client = it->first;
					if (it->first == mClanAttackHost)
					{
						continue;
					}
					CampaignNetPacketProcesser::getInstance().sendCampaignEnter(client->getFrontServerNetId(),client->getPlayerObj()->getActiveClan()->getClanID(),mClanAttackHost->getPlayerObj()->getActiveClan()->getClanID());
				}
			
			}
		}
	}
	//-----------------------------------------------------------------------------
	void CCampaign::ready()
	{
		if (mState == CCAMPAIGN_STATE_PREPARED)
		{
			return;
		}
		if (isOwned())
		{
			if (mClanAttackHost && mState == CCAMPAIGN_STATE_ENTER)
			{
				std::map<CClient*,CCampaignArmyInfo*>::iterator it = mClanAttackList.begin();
				for (; it != mClanAttackList.end(); it++)
				{
					CClient* client = it->first;
					if (it->first == mClanAttackHost)
					{
						continue;
					}
					MG::Str16 name = client->getPlayerName();
					MG::Str8 tempName;
					MG::MGStrOp::toString(name.c_str(),tempName);
				
					if(it->second->state == CCAMPAIGN_ARMY_STATE_ENTER 
						||it->second->state == CCAMPAIGN_ARMY_STATE_CANCEL )
					{
						CampaignNetPacketProcesser::getInstance().sendCampaignReadyMySelf(
							client->getFrontServerNetId(),
							mClanAttackHost->getPlayerObj()->getActiveClan()->getClanID(),
							client->getPlayerObj()->getActiveClan()->getClanID(),
							client->getPlayerObj()->getActiveClan()->getMainGenrealID());
						//client->getClientMessage()->AddErrorMsg("=======%s开始准备======\n",tempName.c_str());
					}
					
				}

			}
		}
	}
	//-----------------------------------------------------------------------------
	void CCampaign::cancle()
	{

		if (isOwned())
		{
			if (mClanAttackHost && mState == CCAMPAIGN_STATE_PREPARED )
			{
				std::map<CClient*,CCampaignArmyInfo*>::iterator it = mClanAttackList.begin();
				for (; it != mClanAttackList.end(); it++)
				{
					CClient* client = it->first;
					if (it->first == mClanAttackHost)
					{
						continue;
					}
					if(it->second->state == CCAMPAIGN_ARMY_STATE_CONFIRM)
					{
						CampaignNetPacketProcesser::getInstance().sendCampaignReadyMySelf(
							client->getFrontServerNetId(),
							mClanAttackHost->getPlayerObj()->getActiveClan()->getClanID(),
							client->getPlayerObj()->getActiveClan()->getClanID(),
							client->getPlayerObj()->getActiveClan()->getMainGenrealID());
					}
				}
			}
		}

	}
	//-----------------------------------------------------------------------------
	void CCampaign::startBattle()
	{

		if (isOwned())
		{
			MG_LOG(out_error,"hostAddr = %d, state = %d\n",mClanAttackHost,mState);
			if (mClanAttackHost && mState == CCAMPAIGN_STATE_PREPARED )
			{
				MG_LOG(out_error,"startBattle id = %I64d \n",mClanAttackHost->getPlayerObj()->getActiveClan()->getClanID());
				CampaignNetPacketProcesser::getInstance().sendCampaignStart(
					mClanAttackHost->getFrontServerNetId(),
					mClanAttackHost->getPlayerObj()->getActiveClan()->getClanID(),
					mClanAttackHost->getPlayerObj()->getActiveClan()->getClanID());
			}
		}
	}
	//-----------------------------------------------------------------------------
	Bool CCampaign::canStartBattle()
	{
		std::map<CClient*,CCampaignArmyInfo*>::iterator it = mClanAttackList.begin();
		for (; it != mClanAttackList.end(); it++)
		{
			CClient* client = it->first;
			if (it->first == mClanAttackHost)
			{
				continue;
			}
			if(it->second->state != CCAMPAIGN_ARMY_STATE_CONFIRM )
			{
				return false;
			}

		}
		return true;
	}
	//-----------------------------------------------------------------------------
	CClient* CCampaign::getHost()
	{
		return mClanAttackHost;
	}
	//-----------------------------------------------------------------------------
	MG::CCAMPAIGN_STATE CCampaign::getState()
	{
		return mState;
	}
	//-----------------------------------------------------------------------------
	void CCampaign::setState( CCAMPAIGN_STATE state )
	{
		mState = state;
	}
	//-----------------------------------------------------------------------------
	Bool CCampaign::isOwned()
	{
		return mIsOwned; 
	}
	//-----------------------------------------------------------------------------
	void CCampaign::setOwned( Bool isOwned )
	{
		mIsOwned = isOwned;
	}
	//-----------------------------------------------------------------------------
	void CCampaign::setRegionId( RegionIdType id)
	{
		mCampaignTargetRegionId = id;
	}
	//-----------------------------------------------------------------------------
	void CCampaign::setCampaignId(CampaignIdType id)
	{
		mCampaignId = id;
	}
	CampaignIdType CCampaign::getCampaignId()
	{
		return mCampaignId;
	}
	//-----------------------------------------------------------------------------
	void CCampaign::setMemberNum(Int number)
	{
		if (!isOwned())
		{
			mMemberNum = number; 
		}
	}
	//-----------------------------------------------------------------------------
	Int CCampaign::getEnterCampaignRoomNum()
	{
		std::map<CClient*,CCampaignArmyInfo*>::iterator it = mClanAttackList.begin();
		Int count = 0;
		for (; it != mClanAttackList.end(); it++)
		{
			if (it->second->state >= CCAMPAIGN_ARMY_STATE_ENTER)
			{
				count++;
			}
		}
		return count;
	}
	//-----------------------------------------------------------------------------
	Int CCampaign::getReadyCampaignRoomNum()
	{
		std::map<CClient*,CCampaignArmyInfo*>::iterator it = mClanAttackList.begin();
		Int count = 0;
		for (; it != mClanAttackList.end(); it++)
		{
			if (it->second->state >= CCAMPAIGN_ARMY_STATE_CONFIRM)
			{
				count++;
			}
		}
		return count;
	}
	//-----------------------------------------------------------------------------
	void CCampaign::setCampaignName( Char16* name )
	{
		mCampaignName = name;
	}
	//-----------------------------------------------------------------------------
	CCampaignArmyInfo* CCampaign::getArmyInfo(CClient* client)
	{
		std::map<CClient*,CCampaignArmyInfo*>::iterator it = mClanAttackList.find(client);
		if (it != mClanAttackList.end())
		{
			return it->second;
		}
		else
		{
			it = mClanDenfenseList.find(client);
			if (it != mClanDenfenseList.end())
			{
				return it->second;
			}
			return NULL;
		}
	}
	//-----------------------------------------------------------------------------
	CCampaignArmyInfo* CCampaign::getArmyInfo( PlayerCharacterIdType id )
	{
		for (std::map<CClient*,CCampaignArmyInfo*>::iterator it = mClanAttackList.begin(); it != mClanAttackList.end(); it++)
		{
			Clan* clan = it->first->getPlayerObj()->getActiveClan();
			if (!clan)
			{
				return NULL;
			}

			if (clan->getMainGenrealID() == id)
			{
				return it->second;
			}
			
		}
		return NULL;
	}
	//-----------------------------------------------------------------------------
	std::map<CClient*,CCampaignArmyInfo*>* CCampaign::getAttackList()
	{
		return &mClanAttackList;
	}
	//-----------------------------------------------------------------------------
	Bool CCampaign::isAllJumpOut()
	{
		std::map<CClient*,CCampaignArmyInfo*>::iterator it = mClanAttackList.begin();
		for (; it != mClanAttackList.end(); it++)
		{
			if (it->second->jumpOut == false)
			{
				return false;
			}
		}
		std::map<CClient*,CCampaignArmyInfo*>::iterator it1 = mClanDenfenseList.begin();
		for (; it1 != mClanDenfenseList.end(); it1++)
		{
			if (it1->second->jumpOut == false)
			{
				return false;
			}
		}
		return true;
	}
	//-----------------------------------------------------------------------------
	Bool CCampaign::isStart()
	{
		return mIsStart;
	}
	//-----------------------------------------------------------------------------
	Bool CCampaign::checkCompleteEnter()
	{
		if (mState == CCAMPAIGN_STATE_ENTER)
		{
			return false;
		}
		for (std::map<CClient*,CCampaignArmyInfo*>::iterator it = mClanAttackList.begin(); it != mClanAttackList.end(); it++)
		{
			if (it->second->state != CCAMPAIGN_ARMY_STATE_ENTER)
			{
				return false;
			}
		}
		mState = CCAMPAIGN_STATE_ENTER;
		return true;
	}
	//-----------------------------------------------------------------------------
	Bool CCampaign::checkCompleteConfirm()
	{
		if (mState == CCAMPAIGN_STATE_PREPARED)
		{
			return false;
		}
		for (std::map<CClient*,CCampaignArmyInfo*>::iterator it = mClanAttackList.begin(); it != mClanAttackList.end(); it++)
		{
			if (it->first == mClanAttackHost)
			{
				continue;
			}
			if (it->second->state != CCAMPAIGN_ARMY_STATE_CONFIRM)
			{
				return false;
			}
		}
		mState = CCAMPAIGN_STATE_PREPARED;
		return true;
	}
	//-----------------------------------------------------------------------------
	void CCampaign::denfenseEnter()
	{
		if (mClanAttackHost)
		{
			std::map<CClient*,CCampaignArmyInfo*>::iterator it = mClanDenfenseList.begin();
			for (; it != mClanDenfenseList.end(); it++)
			{
				CClient* client = it->first;
					CampaignNetPacketProcesser::getInstance().sendCampaignJoinDefense(
						client->getFrontServerNetId(),
						mCampaignTargetRegionId,
						mClanAttackHost->getPlayerObj()->getActiveClan()->getClanID(),
						it->first->getPlayerObj()->getActiveClan()->getClanID());

			}

		}
	}
	//-----------------------------------------------------------------------------
	void CCampaign::clear()
	{
		for (std::map<CClient*,CCampaignArmyInfo*>::iterator it =mClanAttackList.begin(); it != mClanAttackList.end(); it++)
		{
			it->first->setCampaign(NULL);
			MG_SAFE_DELETE(it->second);
		}
	}
	void CCampaign::reset()
	{
		std::map<CClient*,CCampaignArmyInfo*>::iterator it = mClanAttackList.begin();
		for (; it != mClanAttackList.end(); it++)
		{
			it->second->state = CCAMPAIGN_ARMY_STATE_NULL;
		}
		std::map<CClient*,CCampaignArmyInfo*>::iterator it1 = mClanDenfenseList.begin();
		for (; it1 != mClanDenfenseList.end(); it1++)
		{
			it1->second->state = CCAMPAIGN_ARMY_STATE_NULL;
		}
	}
	//-----------------------------------------------------------------------------
	Bool CCampaign::isDenfense( CClient* client )
	{
		std::map<CClient*,CCampaignArmyInfo*>::iterator it =mClanDenfenseList.find(client);
		if (it != mClanDenfenseList.end())
		{
			return true;
		}
		return false;
	}
	//-----------------------------------------------------------------------------
	Bool CCampaign::isAttacket(CClient* client)
	{
		std::map<CClient*,CCampaignArmyInfo*>::iterator it =mClanAttackList.find(client);
		if (it != mClanAttackList.end())
		{
			return true;
		}
		return false;
	}
	//-----------------------------------------------------------------------------
	Int CCampaign::getCycleCount()
	{
		return mCycleCount;
	}
	//-----------------------------------------------------------------------------
	void CCampaign::giveUpCampaign()
	{
		if (mState == CCAMPAIGN_STATE_ENTER
			|| mState == CCAMPAIGN_STATE_APPLIED)
		{
			CampaignNetPacketProcesser::getInstance().sendCampaignLeave(mClanAttackHost->getFrontServerNetId(),mCampaignId,
				mClanAttackHost->getPlayerObj()->getActiveClan()->getClanID());

		}
		else if (mState == CCAMPAIGN_STATE_START
			|| mState == CCAMPAIGN_STATE_ALL_ENTER)
		{
			CampaignNetPacketProcesser::getInstance().sendCampaignEndManual(mClanAttackHost->getFrontServerNetId(),mCampaignId);
		}

	}
	//-----------------------------------------------------------------------------
}