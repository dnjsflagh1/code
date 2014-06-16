/******************************************************************************/
#include "stdafx.h"
#include "CSkillObject.h"
#include "CSkillEffect.h"
#include "GameObject.h"
#include "SkillBaseInfo.h"
/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //游戏技能特效
    /******************************************************************************/
    CSkillEffect::CSkillEffect( CSkillObject* object )
    {
  //      mSkillID            = object->getBaseInfo()->id; 
		//mUserType           = object->getOwner()->getType();

  //      //xkc
  //      mUserID             = object->getOwner()->getID();
		
        mIsCheckCollsion    = false;
        mEffectFileId		= 0;
        mSkillEffectState   = SES_NONE;
        mIsEndOnSkillEned   = true;
		mSkillObject = object;
    }

    //-----------------------------------------------------------------------
    CSkillEffect::~CSkillEffect()
    {
        
    }

    //-----------------------------------------------------------------------
    void CSkillEffect::start()
    {
        mSkillEffectState   = SES_START;

    }

    //-----------------------------------------------------------------------
    void CSkillEffect::end()
    {
        mSkillEffectState   = SES_END;

    }

   //-----------------------------------------------------------------------
    void CSkillEffect::update( Flt delta )
    {
        
    }

	//-----------------------------------------------------------------------
	CSkillObject* CSkillEffect::getSkillObject()
	{
		return mSkillObject;
	}

    //-----------------------------------------------------------------------
    CSkillEffect::SkillEffectState CSkillEffect::getState()
    {
        return mSkillEffectState;
    }

    //-----------------------------------------------------------------------
    Bool CSkillEffect::isBelongSkill( CSkillObject* object )
    {
        if ( getSkillID() != object->getSkillInfo()->skillId )
            return false;

        return true;
    }
    //-----------------------------------------------------------------------
    Bool CSkillEffect::isEndOnSkillEned()
    {
        return mIsEndOnSkillEned;
    }

    //-----------------------------------------------------------------------
    void  CSkillEffect::setIsEndOnSkillEned( Bool isEnded )
    {
        mIsEndOnSkillEned = isEnded;
    }

    //-----------------------------------------------------------------------
    void CSkillEffect::setEffect(  UInt effectFileId  )
    {
        mEffectFileId = effectFileId;
    }

    //-----------------------------------------------------------------------
    void CSkillEffect::setCollisionCheck( Bool isCheckCollsion )
    {
        mIsCheckCollsion = isCheckCollsion;
    }

    //-----------------------------------------------------------------------
    Bool CSkillEffect::getCollisionCheck()
    {
        return mIsCheckCollsion;
    }

    //-----------------------------------------------------------------------
    IdType CSkillEffect::getSkillID()
    {
        return mSkillObject->getSkillInfo()->skillId;
    }   
    
    //-----------------------------------------------------------------------
    IdType CSkillEffect::getUserID()
    {
        return mSkillObject->getOwnerID();
    }
    
    //-----------------------------------------------------------------------
    GAMEOBJ_TYPE CSkillEffect::getUserType()
    {
        return mSkillObject->getOwnerType();
    }
}