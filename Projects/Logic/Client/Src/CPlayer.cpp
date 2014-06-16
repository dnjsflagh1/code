/******************************************************************************/
#include "stdafx.h"
#include "CPlayer.h"
#include "LoginNetPacket.h"
#include "CPlayerCharacter.h"
//#include "CCampaignSystemInRegion.h"
//#include "CPlaceObject.h"
//#include "CWorldManager.h"
#include "SCampaign.h"
#include "CCampaignManager.h"
/******************************************************************************/

namespace MG
{

	//--------------------------------------------------------------------------------
	CPlayer::CPlayer()
		:mClan(NULL)
		//,mCampaignSystem(NULL)
		,mInstanceUid(0)
		,mCampaign(NULL)
	{
#if 0
		mCampaignSystem = MG_NEW CCampaignSystemInRegion(NULL, &CWorldManager_OldVersion::getInstance());
#endif
	}
	
	//--------------------------------------------------------------------------------
	CPlayer::~CPlayer()
	{
        ClearAllData();
	}

	//--------------------------------------------------------------------------------
	void CPlayer::ClearAllData()
	{
		deleteAllClan();
		setMyCampaign(NULL);
		CCampaignManager::getInstance().clear();
		//MG_SAFE_DELETE( mCampaignSystem );
	}

    //--------------------------------------------------------------------------------
    void CPlayer::restore()
    {
        setAccountID( 0 );
        setName(L"");
        setPassword(L"");

        ClearAllData();

#if 0
		if(NULL == mCampaignSystem)
		{
			mCampaignSystem = MG_NEW CCampaignSystemInRegion(NULL, &CWorldManager_OldVersion::getInstance());
		}
#endif
    }


    //--------------------------------------------------------------------------------
    void CPlayer::restoreActiveClan()
    {
        deleteAllClan();
    }
    
	//--------------------------------------------------------------------------------
    CClan* CPlayer::getActiveClan()
	{
		return mClan;
	}

	//--------------------------------------------------------------------------------
	ClanIdType CPlayer::getActiveClanId() const
	{
		return mClan->getClanID();
	}


	////--------------------------------------------------------------------------------
	//CCampaignSystemInRegion* CPlayer::getCampaignSystemInRegion()
	//{
	//	return mCampaignSystemInRegion;
	//}

	//--------------------------------------------------------------------------------
	//void CPlayer::setCampaignSystemInRegion(CampaignSystemInRegion* campaignSystem)
	//{
	//	mCampaignSystemInRegion = (CCampaignSystemInRegion*)campaignSystem;
	//}
    //--------------------------------------------------------------------------------
    CClan* CPlayer::addClan( ClanData* pData )
    {
        std::map<U64, CClan*>::iterator iter = mClanList.find(pData->clanId);
        if ( mClanList.end() != iter )
        {
            DYNAMIC_ASSERT(0);
        }
        else
        {
            CClan* tempClan = MG_NEW CClan;
            tempClan->init( pData );
            mClanList[pData->clanId] = tempClan;

            return tempClan;
        }

        return NULL;
    }
    //--------------------------------------------------------------------------------
    void CPlayer::deleteClan( U64 clanId )
    {
        std::map<U64, CClan*>::iterator iter = mClanList.find(clanId);
        if ( mClanList.end() != iter )
        {
            MG_SAFE_DELETE(iter->second);
            mClanList.erase(iter);
        }   
    }
    //--------------------------------------------------------------------------------
    void CPlayer::deleteAllClan()
    {
        std::map<U64, CClan*>::iterator::iterator front = mClanList.begin();
        std::map<U64, CClan*>::iterator::iterator back = mClanList.end();
        while (front != back)
        {
            MG_SAFE_DELETE(front->second);
            ++front;
        }

        mClanList.clear();

		mClan = NULL;
    }
    //--------------------------------------------------------------------------------
    void CPlayer::testAttr()
    {
        

    }
    //--------------------------------------------------------------------------------
    void CPlayer::testHurt()
    {
        
        
    }

    //--------------------------------------------------------------------------------
    void CPlayer::setActive( U64 clanID )
    {
        std::map<U64, CClan*>::iterator iter = mClanList.find(clanID);
        if (mClanList.end() != iter)
        {
            mClan = iter->second;
            mClan->setOtherInfo();
            return ;
        }

        DYNAMIC_ASSERT(0);
    }

	//--------------------------------------------------------------------------------
	void CPlayer::setForce(const FORCE force)
	{
		DYNAMIC_ASSERT(force >= FORCE_INIT && force < FORCE_MAX);
		mForce = force;
	}

	//--------------------------------------------------------------------------------
	FORCE CPlayer::getForce() const
	{
		return mForce;
	}

	//--------------------------------------------------------------------------------
	CPlayerCharacter* CPlayer::getPlayerCharacter(PlayerCharacterIdType playerCharacterId)
	{
		CClan* myClan = getActiveClan();
		DYNAMIC_ASSERT(NULL != myClan);

		return myClan->getPlayerCharacter(playerCharacterId);
	}

	void CPlayer::setMyCampaignByCampaignId(CampaignIdType campaignId)
	{
		SCampaign* myCampaign = CCampaignManager::getInstance().getPrepareCampaign(campaignId);
		DYNAMIC_ASSERT(NULL != myCampaign);
		setMyCampaign(myCampaign);
	}
	//--------------------------------------------------------------------------------
	void CPlayer::setMyCampaign(SCampaign* myCampaign)
	{
		mCampaign = myCampaign;
	}

	//--------------------------------------------------------------------------------
	SCampaign* CPlayer::getMyCampaign()
	{
		return mCampaign;
	}

	//--------------------------------------------------------------------------------
	CampaignIdType CPlayer::getMyCampaignId()
	{
		if (NULL == mCampaign)
		{
			return 0;
		}
		return mCampaign->getCampaignId();
	}

	//--------------------------------------------------------------------------------
	Bool CPlayer::campaignCreatorIsMe()
	{
		if (NULL == mCampaign)
		{
			return false;
		}

		return mCampaign->getCampaignId() == mClan->getClanID();
	}

	//--------------------------------------------------------------------------------
	CPlayerCharacter* CPlayer::getMainGenreal()
	{
		return mClan->getMainGenreal();
	}

	PlayerCharacterIdType CPlayer::getMainPlayerCharacterId()
	{
		return getMainGenreal()->getID();
	}
}