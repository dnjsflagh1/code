/******************************************************************************/
#include "stdafx.h"
#include "CClan.h"
#include "CPlayer.h"
#include "LoginNetPacket.h"
#include "CPlayerCharacter.h"
#include "BuildingData.h"
#include "PlayerCharacterData.h"

/******************************************************************************/

namespace MG
{
    //--------------------------------------------------------------------------
    CClan::CClan()
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
    }
    //--------------------------------------------------------------------------
    CCharacter* CClan::getCharacter( IdType id, GAMEOBJ_TYPE type )
    {
        if ( type == GOT_PLAYERCHARACTER )
            return getPlayerCharacter(id);



        return NULL;
    }


    //--------------------------------------------------------------------------
    CPlayerCharacter* CClan::addPlayerCharacter(  PlayerCharacterData* pData  )
    {
        //创建角色逻辑对象
        CPlayerCharacter* character = getPlayerCharacter( pData->mId );
        if ( character == NULL)
        {
            character = MG_NEW CPlayerCharacter();
            mPlayerCharacterList[pData->mId] = character;
        }

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
            MG_SAFE_DELETE( charater );
        }   
        mPlayerCharacterList.clear();
    }
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

	//--------------------------------------------------------------------------
	CPlayerCharacter* CClan::getMainGenreal()
	{
		return getPlayerCharacterByIndex(0);
	}
}