/******************************************************************************/

#include "stdafx.h"
#include "SPlayer.h"
#include "LoginManager.h"
#include "FrontServerMain.h"
#include "ClanDataBase.h"
#include "PlayerCharacterDB.h"
#include "SClan.h"
#include "LoginNetPacketProcesser.h"
#include "PlayerNetPacketProcesser.h"
#include "SWorldManager.h"
#include "SClanQuestManager.h"
#include "SHeartBeatManager.h"
#include "SPlayerFactory.h"
#include "SGameObjectFactory.h"

/******************************************************************************/
namespace MG
{


    /******************************************************************************/
    //SPlayer
    /******************************************************************************/

    void SPlayerPtr::destroy(void)
    {
        mFactory->destroySPlayerPtr(*this);
    }
    

    /******************************************************************************/
    //SPlayerPtr
    /******************************************************************************/

	//-----------------------------------------------------------------------------
	SPlayer::SPlayer()
        :mClientNetId(-1)
		,mCurrentMapServerNetId(-1)
		,mCampaignId(0)
		,mPveRoomId(0)
		,mCurrentRegionType(ROT_UNKNOWN)
		,mCurrentRegionId(0)
		,mCurrentInstanceUid(0)
	{
	}

	//-----------------------------------------------------------------------------
	SPlayer::~SPlayer()
	{

	}

    //-----------------------------------------------------------------------------------
    // Main
    //-----------------------------------------------------------------------------------
    
    //-----------------------------------------------------------------------------
    Bool SPlayer::initialize( AccountIdType accountId, I32 client_id, Str16& accName )
    {
        mClientNetId = client_id;
        setAccountID( accountId );
        //setName(accName.c_str());
		mClanIDBuilderManager.init(10);
        

		return true;
    }

    //-----------------------------------------------------------------------------
    Bool SPlayer::unInitialize()
    {
		mClanIDBuilderManager.unInit();
		return true;
    }

    //-----------------------------------------------------------------------------
    Bool SPlayer::update(Flt delta)
    {

        
        return false;
    }

    //-----------------------------------------------------------------------------
    void SPlayer::clear()
    {
        stopUpdate();

        mClientNetId = -1;
        mCurrentMapServerNetId = -1;

        mMainClanID = 0;

        setAccountID( 0 );
        //setName("");

		removeAllClan();
		mClanIDBuilderManager.clear();

    }


    //-----------------------------------------------------------------------------------
    // Print
    //-----------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------
    void SPlayer::print()
    {
        ////��������id
        //std::string strClanIds;
        //{
        //    std::map<ClanIdType, SClan*>::iterator iter = mClanList.begin();
        //    for ( ; iter != mClanList.end(); iter++)
        //    {
        //        std::string id;
        //        MGStrOp::toString(iter->second->getClanID(), id);
        //        if (strClanIds.empty())
        //        {
        //            strClanIds = strClanIds + id;
        //        }
        //        else
        //        {
        //            strClanIds = strClanIds + ", " + id;
        //        }
        //    }

        //    if (strClanIds.empty())
        //    {
        //        strClanIds = "��";
        //    }
        //}

        //std::string strMainClan("��");
        //if (NULL != mMainClan)
        //{
        //    MGStrOp::toString(mMainClan->getClanID(), strMainClan);
        //}
    }


    //-----------------------------------------------------------------------------------
    // Net Info
    //-----------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------
    NetIdType SPlayer::getClientNetID() const
    {
        return mClientNetId;
    }

    //-----------------------------------------------------------------------------
    NetIdType SPlayer::getMapServerNetID() const	
    {
        return mCurrentMapServerNetId;		
    }

    //-----------------------------------------------------------------------------
    void SPlayer::setMapServerNetID(NetIdType mapServerNetID)
    { 
        DYNAMIC_ASSERT(mapServerNetID >= 0);
        mCurrentMapServerNetId = mapServerNetID; 
    }

    //-----------------------------------------------------------------------------
    Bool SPlayer::isCheckDisconnect()
    {
		return true;
    }

    //-----------------------------------------------------------------------------------
    // Region
    //-----------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------
    void SPlayer::setCurrentRegion(REGION_OBJ_TYPE regionType, RegionIdType regionId, InstanceUIdType instanceUid)
    {
        DYNAMIC_ASSERT(regionType > ROT_UNKNOWN && regionType < ROT_MAX);
        mCurrentRegionType	= regionType;
        mCurrentRegionId	= regionId;
        mCurrentInstanceUid = instanceUid;
    }

    //-----------------------------------------------------------------------------
    REGION_OBJ_TYPE	SPlayer::getCurrentRegionType() const
    {
        return mCurrentRegionType;
    }

    //-----------------------------------------------------------------------------
    RegionIdType SPlayer::getCurrentRegionId() const
    {
        return mCurrentRegionId;
    }

    //-----------------------------------------------------------------------------
    InstanceUIdType SPlayer::getCurrentInstanceUid() const
    {
        return mCurrentInstanceUid;
    }

    //-----------------------------------------------------------------------------------
    // Campaign
    //-----------------------------------------------------------------------------------


    //-----------------------------------------------------------------------
    void SPlayer::setCampaignId(const CampaignIdType campaignId)
    {
        mCampaignId = campaignId;
    }

    //-----------------------------------------------------------------------
    CampaignIdType SPlayer::getCampaignId() const
    {
        return mCampaignId;
    }

    //-----------------------------------------------------------------------------------
    // Pve
    //-----------------------------------------------------------------------------------

    //-----------------------------------------------------------------------
    void SPlayer::setPveRoomId(Int pveRoomId)
    {
        mPveRoomId = pveRoomId;
    }

    //-----------------------------------------------------------------------
    Int SPlayer::getPveRoomId() const
    {
        return mPveRoomId;
    }

   

    //-----------------------------------------------------------------------------------
    // Clan
    //-----------------------------------------------------------------------------------


    //-----------------------------------------------------------------------------
    Bool SPlayer::addClan( SClanPtr& clan, ClanData& clanData )
    {
		//����ID, ���û�У��ʹ���ID
		//��SClan����IDBuilderManager�����ID�ظ���
		clan.getPointer()->setClanID(clanData.clanId);
		clan.getPointer()->setParentPlayer(this);
		mClanIDBuilderManager.addIDObject((IDObject*)(clan.getPointer()));
		clanData.clanId = clan.getPointer()->getClanID();

        if ( hasClan( clanData.clanId ) )
        {
            DYNAMIC_EEXCEPT_LOG("already exist clan!");
            removeClan( clanData.clanId );
        }

        mSClanFactory.createSClanPtr( clan, clanData.clanId, clanData.accountId, clanData );

        mClanMapCs.writeLock();
        {
            mClanMap[clanData.clanId] = clan;
        }
        mClanMapCs.writeUnLock();

        

        return true;
    }

    //-----------------------------------------------------------------------------
    void SPlayer::removeClan(ClanIdType clanId)
    {
        SClanPtr clanPtr;

        if ( getClan( clanPtr, clanId ) )
        {
            //------------------------------------------------------------------------------------
			//IDBuilderManagerɾ������
			mClanIDBuilderManager.removeIDObject(clanId);
			//����߼�����
            clanPtr->clear();
            //------------------------------------------------------------------------------------

            mClanMapCs.writeLock();
            {
                std::map<ClanIdType,SClanPtr>::iterator iter = mClanMap.find( clanId );
                if ( iter != mClanMap.end() )
                {
                    mClanMap.erase( iter );
                }
            }
            mClanMapCs.writeUnLock();
        }
    }

    //-----------------------------------------------------------------------------
    Bool SPlayer::getClan(SClanPtr& clan, ClanIdType clanId)
    {
        Bool result = false;

        mClanMapCs.readLock();
        {
            std::map<ClanIdType,SClanPtr>::iterator iter = mClanMap.find( clanId );
            if ( iter != mClanMap.end() )
            {
                clan = iter->second;
                result = true;
            }
        }
        mClanMapCs.readUnLock();

        return result;
    }

    //-----------------------------------------------------------------------------
    Bool SPlayer::hasClan(ClanIdType clanId)
    {
        Bool result = false;

        mClanMapCs.readLock();
        {
            std::map<ClanIdType,SClanPtr>::iterator iter = mClanMap.find( clanId );
            if ( iter != mClanMap.end() )
            {
                result = true;
            }
        }
        mClanMapCs.readUnLock();

        return result;
    }

    //-----------------------------------------------------------------------------
    Bool SPlayer::hasClan()
    {
        Bool result = false;

        mClanMapCs.readLock();
        {
            if ( mClanMap.size() > 0 )
            {
                result = true;
            }
        }
        mClanMapCs.readUnLock();

        return result;
    }

    //-----------------------------------------------------------------------------
    void SPlayer::removeAllClan()
    {
        mClanMapCs.writeLock();
        {
            std::map<ClanIdType,SClanPtr>::iterator iter = mClanMap.begin();
            for ( ;iter != mClanMap.end(); iter++ )
            {
                iter->second->clear();
            }
            mClanMap.clear();
        }
        mClanMapCs.writeUnLock();
    }

    //-----------------------------------------------------------------------------
    Bool SPlayer::getMainClan( SClanPtr& clan )
    {
        return getClan( clan, mMainClanID );
    }

    //-----------------------------------------------------------------------------
    void SPlayer::setFirstMainClan()
    {
        Bool isHasClan = false;
        ClanIdType clanID = 0;
        mClanMapCs.readLock();
        {
            std::map<ClanIdType,SClanPtr>::iterator iter = mClanMap.begin();
            if ( iter != mClanMap.end() )
            {
                clanID = iter->first;
                isHasClan = true;
            }
        }
        mClanMapCs.readUnLock();

        if ( isHasClan )
        {
            setMainClan( clanID );
        }
    }

    //-----------------------------------------------------------------------------
    void SPlayer::setMainClan(ClanIdType clanId)
    {
        SClanPtr clan;

        if ( getClan( clan, clanId ) )
        {
            mMainClanID = clanId;
        }
    }

}