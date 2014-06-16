/******************************************************************************/
#include "stdafx.h"
#include "CClan.h"
#include "CPlayer.h"
#include "LoginNetPacket.h"
#include "CPlayerCharacter.h"
#include "CItemManager.h"

#include "BuildingData.h"
#include "PlayerCharacterData.h"

/******************************************************************************/

namespace MG
{
    //--------------------------------------------------------------------------
    CClan::CClan()
		:mMainPlayerCharacter(NULL)
    {

    }

    //--------------------------------------------------------------------------
    CClan::~CClan()
    {
        removeAllPlayerCharacter();
    }

    //--------------------------------------------------------------------------
    void CClan::init( ClanData* pData )
    {
        setData(pData);
    }
    //--------------------------------------------------------------------------
    void CClan::setOtherInfo()
    {
        CItemManager::getInstance().setSize();
        //游戏币信息
		CItemManager::getInstance().addMoney(mClanData.clanGameMoney,ITEM_MONEY_CLASS_MONEY_GAME);
    }
    //--------------------------------------------------------------------------
    CCharacter* CClan::getCharacter( IdType id, GAMEOBJ_TYPE type )
    {
        if ( type == GOT_PLAYERCHARACTER )
            return getPlayerCharacter(id);



        return NULL;
    }


    //--------------------------------------------------------------------------
    CPlayerCharacter* CClan::addPlayerCharacter(  PlayerCharacterData* pData, Bool& isFirst  )
    {
        //创建角色逻辑对象
        CPlayerCharacter* character = getPlayerCharacter( pData->mId );
        if ( character == NULL)
        {
            character = MG_NEW CPlayerCharacter();
            mPlayerCharacterList[pData->mId] = character;

			isFirst = true;
			return character;
        }

		isFirst = false;
        return character;
    }

	//--------------------------------------------------------------------------
	Bool CClan::hasPlayerCharacter( U64 id )
	{
		std::map<U64, CPlayerCharacter*>::iterator iter = mPlayerCharacterList.find( id );
		if ( iter != mPlayerCharacterList.end() )
		{
			return true;
		}

		return false;
	}

    //--------------------------------------------------------------------------
    CPlayerCharacter* CClan::getPlayerCharacter( U64 id )
    {
        CPlayerCharacter* charater = NULL;

        std::map<U64, CPlayerCharacter*>::iterator iter = mPlayerCharacterList.find( id );
        if ( iter != mPlayerCharacterList.end() )
        {
            charater = iter->second;
        }

        return charater;
    }

    //--------------------------------------------------------------------------
    void CClan::removePlayerCharacter( U64 id )
    {
        CPlayerCharacter* charater = NULL;
        std::map<U64, CPlayerCharacter*>::iterator iter = mPlayerCharacterList.find( id );
        if ( iter != mPlayerCharacterList.end() )
        {
            charater = iter->second;
			charater->unInit();
            MG_SAFE_DELETE( charater );
            mPlayerCharacterList.erase( iter );
        }
    }

    //--------------------------------------------------------------------------
    void CClan::removeAllPlayerCharacter()
    {
        CPlayerCharacter* charater = NULL;
        std::map<U64, CPlayerCharacter*>::iterator iter = mPlayerCharacterList.begin();
        for ( ;iter != mPlayerCharacterList.end();iter++ )
        {
            charater = iter->second;
			charater->unInit();
            MG_SAFE_DELETE( charater );
        }   
        mPlayerCharacterList.clear();
    }

#if 0
    //--------------------------------------------------------------------------
    CPlayerCharacter* CClan::getPlayerCharacterByIndex( U32 index )
    {
        Int nCount = 0;

        std::map<U64, CPlayerCharacter*>::iterator iter = mPlayerCharacterList.begin();
        for ( ;iter != mPlayerCharacterList.end();iter++ )
        {
            if ( nCount++ == index )
                return iter->second;
        }

        return NULL;
    }
#endif
	//--------------------------------------------------------------------------
	CPlayerCharacter* CClan::getMainGenreal()
	{
		return mMainPlayerCharacter;
	}

	void CClan::setMainPlayerCharacter(CPlayerCharacter* playerCharacter)
	{
		DYNAMIC_ASSERT(NULL != playerCharacter);
		mMainPlayerCharacter = playerCharacter;
	}

#if 0
	void CClan::clearRecruitGeneralList()
	{
		mRecruitGeneralList.clear();
	}

	void CClan::loadRecruitGeneralInfo(NetRecuitGeneralInfo* generalInfo)
	{
		std::map<U64, CPlayerCharacter*>::iterator iter = mRecruitGeneralList.find(generalInfo->uin);
		if (iter != mRecruitGeneralList.end())
		{
			//找到， id 重复
			return;
		}

		CPlayerCharacter* character = MG_NEW CPlayerCharacter();
		
		character->getData()->mId					= generalInfo->uin;
		character->getData()->mCharacterTemplateID	= generalInfo->charTemplateId;
		character->getData()->mName					= L"xxa";

		mRecruitGeneralList[generalInfo->uin] = character;
	}

	std::map<U64, CPlayerCharacter*>* CClan::getRecruitGeneralList()
	{
		return &mRecruitGeneralList;
	}
#endif
}