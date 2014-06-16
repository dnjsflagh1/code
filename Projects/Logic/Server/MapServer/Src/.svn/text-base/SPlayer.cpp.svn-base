/******************************************************************************/

#include "stdafx.h"
#include "SPlayer.h"
#include "SPlayerManager.h"
#include "SWorldManager.h"
#include "SBuilding.h"
#include "SCDManager.h"
#include "SRegionNetPacketProcesser.h"
#include "SPlayerObjectFactory.h"
#include "SGameObjectFactory.h"
#include "SPlayerCharacter.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //SPlayerPtr
    /******************************************************************************/
    
    void SPlayerPtr::destroy(void)
    {
        mFactory->destroySPlayerPtr( *this );
    }

    
    /******************************************************************************/
    //SPlayer
    /******************************************************************************/

	//-----------------------------------------------------------------------------
	SPlayer::SPlayer()
		:mSPlayerCharacterFactory(NULL)
	{
		if ( mSPlayerCharacterFactory )
		{
			mSPlayerCharacterFactory = MG_NEW SPlayerCharacterFactory;
		}
	}

	//-----------------------------------------------------------------------------
	SPlayer::~SPlayer()
	{
		MG_SAFE_DELETE(mSPlayerCharacterFactory);
	}

    //-----------------------------------------------------------------------------------
    // Main
    //-----------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------
    Bool SPlayer::initialize()
    {
        //TODO:
        {
            mSCDManager = new SCDManager(CD_MASTER_TYPE_CLAN);
        }

        //startUpdate();

        return true;
    }

    //-----------------------------------------------------------------------
    Bool SPlayer::unInitialize()
    {
        //stopUpdate();

        //TODO:
        {
            MG_SAFE_DELETE(mSCDManager);
        }

        return true;
    }

	//-----------------------------------------------------------------------
    void SPlayer::clear()
    {

        //stopUpdate();

        //---------------------------------------------------------------------

        //将玩家从战斗房间中踢出
        //player->leaveFromCampaign();

        //---------------------------------------------------------------------

        // 脱离区域
        //jumpToRegion(NULL);
        // 副本在心跳内判断玩家数量，数量为空时则释放

        //---------------------------------------------------------------------

        destroyAllPlayerCharacters();
        mMainSPlayerCharacterID = 0;

        //---------------------------------------------------------------------

        mCanSeeByCamera = false;
        mSPlayerIdentifyInfo.clear();

    }


    //-----------------------------------------------------------------------
    Bool SPlayer::update(Flt delta)
    {
#if 0
        // TODO:
        {
            std::map<MG::PlayerCharacterIdType, MG::SCharacter*>* playerCharacterList = mPlayerCharacterList.getDataList();
            SPlayerCharacter* playerCharacter = NULL;

            std::map<MG::PlayerCharacterIdType, MG::SCharacter*>::iterator it = playerCharacterList->begin();
            for(; it != playerCharacterList->end(); ++it)
            {
                playerCharacter = (SPlayerCharacter*)it->second;
                if(!playerCharacter)
                {
                    continue;
                }

                playerCharacter->update(delta);
            }
        }

#endif

        return false;

    }

    //-----------------------------------------------------------------------------------
    // Debug
    //-----------------------------------------------------------------------------------

    //-----------------------------------------------------------------------
    void SPlayer::print()
    {
        //std::string strCurrentRegionObject("空");
        //if (NULL != mCurrentRealRegionObj && mCurrentRealRegionObj->getNewRegionObject() != NULL)
        //{
        //    MGStrOp::toString(mCurrentRealRegionObj->getNewRegionObject()->getRegionId(), strCurrentRegionObject);
        //}

        ////遍历武将id
        //std::string strPlayerCharacterIds;
        //{
        //    std::map<IdType, SCharacter*>* playerList = mPlayerCharacterList.getDataList();
        //    std::map<IdType, SCharacter*>::iterator iter = playerList->begin();
        //    for ( ; iter != playerList->end(); iter++)
        //    {
        //        std::string id;
        //        MGStrOp::toString(iter->second->getID(), id);
        //        if (strPlayerCharacterIds.empty())
        //        {
        //            strPlayerCharacterIds = strPlayerCharacterIds + id;
        //        }
        //        else
        //        {
        //            strPlayerCharacterIds = strPlayerCharacterIds + ", " + id;
        //        }
        //    }

        //    if (strPlayerCharacterIds.empty())
        //    {
        //        strPlayerCharacterIds = "空";
        //    }
        //}

        ////遍历军队id
        //std::string strTroopGroupId;
        //{
        //}

        //MG_LOG(out_sys, " accountId[%I64i], mClanId[%I64i], mFrontID[%d], mClientNetIdInFrontServer[%d], \
        //                mActiveByCamera[%d], mCurrentRegionObjId[%s], SPlayerCharacter列表[%s], mTroopGroupList列表[%s]\n",
        //                getAccountID(), mClanId, getFrontServerId(), mClientNetIdInFrontServer,
        //                getCanSeeByCamera(),strCurrentRegionObject.c_str(), strPlayerCharacterIds.c_str(), strTroopGroupId.c_str());
    }

    //-----------------------------------------------------------------------------------
    // Base Info
    //-----------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------
    SPlayerIdentifyInfo* SPlayer::getIdentifyInfo()
    {
        return &mSPlayerIdentifyInfo;
    }

    //-----------------------------------------------------------------------------
    Bool SPlayer::getCanSeeByCamera() const
    {
        return mCanSeeByCamera;
    }

    //-----------------------------------------------------------------------------
    void SPlayer::setCanSeeByCamera(Bool canSee)
    {
        mCanSeeByCamera = canSee;
    }

    //-----------------------------------------------------------------------------------
    // PlayerCharacter
    //-----------------------------------------------------------------------------------
    void SPlayer::createPlayerCharacter(  SPlayerCharacterPtr charPtr, PlayerCharacterIdType playerCharacterId, PlayerCharacterData& data )
    {
        if ( retrievePlayerCharacter( charPtr, playerCharacterId ) )
        {
            DYNAMIC_EEXCEPT_LOG("already exist playercharacter!");
            destroyPlayerCharacter( playerCharacterId );
            charPtr.setNull();
        }

        mSPlayerCharacterFactory->createSPlayerCharacterPtr( charPtr, playerCharacterId, data );

        SPlayerPtr sPlayer;
        SPlayerManager::getInstance().getPlayer( sPlayer, getIdentifyInfo()->accountId );
        DYNAMIC_ASSERT_LOG( sPlayer.isNull() == false, " not find player ptr!" );
        charPtr->setPlayer( sPlayer );
    
        mPlayerCharacterListCs.writeLock();
        {
            mPlayerCharacterList[playerCharacterId] = charPtr;
        }
        mPlayerCharacterListCs.writeUnLock();
    }

    //-----------------------------------------------------------------------------
    Bool SPlayer::retrievePlayerCharacter(SPlayerCharacterPtr& ptr, PlayerCharacterIdType id)
    {
        Bool result = false;

        mPlayerCharacterListCs.readLock();
        {
            std::map<PlayerCharacterIdType,SPlayerCharacterPtr>::iterator iter = mPlayerCharacterList.find( id );
            if ( iter != mPlayerCharacterList.end() )
            {
                ptr = iter->second;
                result = true;
            }
        }
        mPlayerCharacterListCs.readUnLock();

        return result;
    }

    //-----------------------------------------------------------------------------
    Bool SPlayer::hasPlayerCharacter(PlayerCharacterIdType id)
    {
        Bool result = false;

        mPlayerCharacterListCs.readLock();
        {
            std::map<PlayerCharacterIdType,SPlayerCharacterPtr>::iterator iter = mPlayerCharacterList.find( id );
            if ( iter != mPlayerCharacterList.end() )
            {
                result = true;
            }
        }
        mPlayerCharacterListCs.readUnLock();

        return result;
    }

    //-----------------------------------------------------------------------------
    void SPlayer::destroyPlayerCharacter(PlayerCharacterIdType id)
    {
        mPlayerCharacterListCs.writeLock();
        {
            std::map<PlayerCharacterIdType,SPlayerCharacterPtr>::iterator iter = mPlayerCharacterList.find( id );
            if ( iter != mPlayerCharacterList.end() )
            {
                SPlayerPtr ptr;
                iter->second->clear();
                iter->second->setPlayer( ptr );

                mPlayerCharacterList.erase( iter );
            }
        }
        mPlayerCharacterListCs.writeUnLock();
    }

    //-----------------------------------------------------------------------------
    void SPlayer::destroyAllPlayerCharacters()
    {
        mPlayerCharacterListCs.writeLock();
        {
            SPlayerPtr ptr;

            std::map<PlayerCharacterIdType,SPlayerCharacterPtr>::iterator iter = mPlayerCharacterList.begin();
            for ( ;iter != mPlayerCharacterList.end(); iter++ )
            {
                iter->second->clear();
                iter->second->setPlayer( ptr );
            }
            mPlayerCharacterList.clear();

        }
        mPlayerCharacterListCs.writeUnLock();
    }

    //-----------------------------------------------------------------------------
    Bool SPlayer::getMainPlayerCharacter(SPlayerCharacterPtr& ptr)
    {
        return retrievePlayerCharacter( ptr, mMainSPlayerCharacterID );
    }

    //-----------------------------------------------------------------------------
    void SPlayer::setMainPlayerCharacter(PlayerCharacterIdType id)
    {
        mMainSPlayerCharacterID = id;
    }

    //-----------------------------------------------------------------------------------
    // Region
    //-----------------------------------------------------------------------------------
	void SPlayer::setBelongScene( SSceneObjectPtr& ptr )
	{
		mSceneObjectPtr = ptr;
	}

	//-----------------------------------------------------------------------------------
	void SPlayer::getBelongScene( SSceneObjectPtr& ptr )
	{
		ptr = mSceneObjectPtr;
	}


    //-----------------------------------------------------------------------------------
    // AI
    //-----------------------------------------------------------------------------------

	//-----------------------------------------------------------------------
	void SPlayer::addControlAIMonsterId(GameObjectIdType monsterId)
	{
		std::vector<GameObjectIdType>::iterator iter = find(mControlAIMonster.begin(), mControlAIMonster.end(), monsterId);
		if (iter != mControlAIMonster.end())
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		mControlAIMonster.push_back(monsterId);
	}

	//-----------------------------------------------------------------------
	void SPlayer::clearControlAIMonsterId()
	{
		mControlAIMonster.clear();
	}
	
	//-----------------------------------------------------------------------
	std::vector<GameObjectIdType>* SPlayer::getControlAIMonsterIdList()
	{
		return &mControlAIMonster;
	}
    
    
    //-----------------------------------------------------------------------------------
    // CD
    //-----------------------------------------------------------------------------------

	//-----------------------------------------------------------------------
	SCDManager* SPlayer::getSCDManager()
	{
		return mSCDManager;
	}

	//-----------------------------------------------------------------------
	AccountIdType SPlayer::getAccountId()
	{
		return mSPlayerIdentifyInfo.accountId;
	}

	//-----------------------------------------------------------------------
	NetIdType SPlayer::getFrontServerId()
	{
		return mSPlayerIdentifyInfo.frontServerId;
	}

	//-----------------------------------------------------------------------
	NetIdType SPlayer::getClientNetIdInFrontServer()
	{
		return mSPlayerIdentifyInfo.clientNetIdInFrontServer;
	}

	//-----------------------------------------------------------------------
	ClanIdType SPlayer::getClanId()
	{
		return mSPlayerIdentifyInfo.clanId;
	}

}