/******************************************************************************/
#include "stdafx.h"
#include "CPlayer.h"
#include "LoginNetPacket.h"
#include "CPlayerCharacter.h"
//#include "CCampaignSystemInRegion.h"
//#include "CPlaceObject.h"
//#include "CWorldManager.h"
/******************************************************************************/

namespace MG
{

	//--------------------------------------------------------------------------------
	CPlayer::CPlayer()
		:mClan(NULL)
		//,mCampaignSystem(NULL)
		,mInstanceUid(0)
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
		MG_LOG(out_debug,"¼Ò×åid = %I64d\n",clanID);
        if (mClanList.end() != iter)
        {
            mClan = iter->second;
            mClan->setOtherInfo();
            return ;
        }

        DYNAMIC_ASSERT(0);
    }

	//--------------------------------------------------------------------------------
	CPlayerCharacter* CPlayer::getPlayerCharacter(PlayerCharacterIdType playerCharacterId)
	{
		CClan* myClan = getActiveClan();
		//DYNAMIC_ASSERT(NULL != myClan);
		if ( myClan ==NULL)
		   return NULL;

		return myClan->getPlayerCharacter(playerCharacterId);
	}
}