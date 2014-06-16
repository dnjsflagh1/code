/******************************************************************************/
#include "stdafx.h"
#include "SCharacter.h"
#include "CharacterList.h"
#include "SClan.h"
#include "SSkillUseManager.h"
#include "SSkillOwnManager.h"
#include "SWorldManager.h"
/******************************************************************************/

/******************************************************************************/
namespace MG
{

    //-----------------------------------------------------------------------------
    SCharacter::SCharacter( GAMEOBJ_TYPE type,  GameObjectData* data)
        :GameObject(type, GQT_UNKNOWN, data, data->mId)
        ,mCharacterTempInfo(NULL)
		,mLastInstanceUId(0)
		,mLastRegionId(0)
		,mLastRegionType(ROT_UNKNOWN)
    {

    }

    //-----------------------------------------------------------------------------
    SCharacter::~SCharacter()
    {
        mCharacterTempInfo = NULL;
    }

    //-----------------------------------------------------------------------------------
    // Main
    //-----------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------
    Bool SCharacter::initialize()
    {   
		return true;
    }

    //-----------------------------------------------------------------------------
    Bool SCharacter::unInitialize()
    {
        return true;
    }

    //-----------------------------------------------------------------------------
    void SCharacter::update(Flt delta)
    {

    }

    //-----------------------------------------------------------------------------
    void SCharacter::clear()
    {
		mLastRegionType = ROT_UNKNOWN;
		mLastRegionId = 0;
		mLastInstanceUId = 0;
		mParentClan = NULL;
    }


    //-----------------------------------------------------------------------------------
    // Debug
    //-----------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------
    void SCharacter::print()
    {
        //std::string strOnwnerClan("空");
        //if (NULL != mParentClan)
        //{
        //    MGStrOp::toString(mParentClan->getAccountID(), strOnwnerClan);
        //}

        ////MG_LOG(out_sys, "【SCharacter】 mOwnerClanAccountId[%s]\n",strOnwnerClan.c_str());
        //return;
    }

    //-----------------------------------------------------------------------------------
    // Skill
    //-----------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------
    SSkillOwnManager* SCharacter::getSkillOwnManager() const
    {
        return mSkillOwnManager;
    }
    //-----------------------------------------------------------------------------
    SSkillUseManager* SCharacter::getSkillUseManager() const
    {
        return mSkillUseManager;
    }



    //-----------------------------------------------------------------------------------
    // Base Info
    //-----------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------
    CharacterData* SCharacter::getData()
    {
        return (CharacterData*)GameObject::getGameObjectData();   
    }

    //-----------------------------------------------------------------------------
    MG::U32 SCharacter::getCharacterTemplateID()
    {
        return getData()->mCharacterTemplateID;
    }
    //-----------------------------------------------------------------------------
    void SCharacter::setCharacterTemplateID( U32 id )
    {
        getData()->mCharacterTemplateID = id;
    }
    //-----------------------------------------------------------------------------
    MG::U32 SCharacter::getLevel()
    {
        return getData()->mLevel;
    }
    //-----------------------------------------------------------------------------
    void SCharacter::setLevel( U32 level )
    {
        getData()->mLevel = level;
    }

    //-----------------------------------------------------------------------------
    void SCharacter::setCharacterTempInfo()
    {
        mCharacterTempInfo = CharacterTemplate::getInstance().getCharacterTempInfo(getData()->mCharacterTemplateID);
    }
    //-----------------------------------------------------------------------------
    const CharacterTempInfo* SCharacter::getCharacterTempInfo()
    {
        return mCharacterTempInfo;
    }


    //-----------------------------------------------------------------------------------
    // Region Info
    //-----------------------------------------------------------------------------------


    //-----------------------------------------------------------------------------
	SRegionObjectBase* SCharacter::getCurrentRegionObject()
	{
		return SWorldManager::getInstance().getRegionObject(getData()->mRegionType, getData()->mRegionID);
	}

    //-----------------------------------------------------------------------------
    void SCharacter::setRegion(REGION_OBJ_TYPE regionType, RegionIdType regionId, InstanceUIdType instanceUId)
    {
		DYNAMIC_ASSERT(regionType > ROT_UNKNOWN && regionType < ROT_MAX);

		if (regionType	== getData()->mRegionType && 
			regionId	== getData()->mRegionID && 
			instanceUId == getData()->mInstanceUId)
		{
			return;
		}
		mLastRegionId		= getData()->mRegionID;
		mLastRegionType		= getData()->mRegionType;
		mLastInstanceUId	= getData()->mInstanceUId;

        getData()->mRegionType	= regionType;
        getData()->mRegionID	= regionId;
		getData()->mInstanceUId = instanceUId;
    }

    //-----------------------------------------------------------------------------
    MG::REGION_OBJ_TYPE SCharacter::getRegionType()
    {
        return getData()->mRegionType;
    }

    //-----------------------------------------------------------------------------
    MG::U32 SCharacter::getRegionId()
    {
        return getData()->mRegionID;
    }

	//-----------------------------------------------------------------------------
	InstanceIdType SCharacter::getInstanceUId()
	{
		return getData()->mInstanceUId;
	}

	//-----------------------------------------------------------------------------
	RegionIdType SCharacter::getLastRegionId()
	{
		return mLastRegionId;
	}

    //-----------------------------------------------------------------------------
	REGION_OBJ_TYPE SCharacter::getLastRegionType()
	{
		return mLastRegionType;
	}

	//-----------------------------------------------------------------------------
	InstanceUIdType SCharacter::getLastInstanceUId()
	{
		return mLastInstanceUId;
	}

    //-----------------------------------------------------------------------------------
    // Alive
    //-----------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------
    void SCharacter::dead()
    {
    }

    //-----------------------------------------------------------------------------
    Bool SCharacter::isDead()
    {
        return getHp() <= 0;
    }

    //-----------------------------------------------------------------------------------
    // Attr Info
    //-----------------------------------------------------------------------------------


    //-----------------------------------------------------------------------------
    void SCharacter::calAttr( Bool isFirst )
    {
		
        //计算系统属性和天赋属性
        mSAttributeSystem.calAttrBase(this, isFirst);
        calOtherAttr();
        mSAttributeSystem.calFinalAttr(mCharacterTempInfo->getCharacterFormulaType(), getData());
        //initDirty();
    }

    //-----------------------------------------------------------------------------
	void SCharacter::setMax_HpSpMp()
	{
		setHp(getMaxHp());
		setMp(getMaxMp());
		setSp(getMaxSp());
	}

    //-----------------------------------------------------------------------------
    void SCharacter::setHurtOrRecove( DamageType type, ATTACK_RESULT_TYPE resType, U32 value )
    {
		
        if ( type == DT_HP )
		{
			if (ATTACK_RESULT_TYPE_HURT == resType)
			{
				 setHp( getHp() - value);
			}
			else if(ATTACK_RESULT_TYPE_HURT_CHANGE_RECOVER == resType)
			{
				setHp( getHp() + value);
			}
			else if (ATTACK_RESULT_TYPE_RECOVER == resType)
			{
				setHp(getHp() + value);
			}
			else if(ATTACK_RESULT_TYPE_DEAD)
			{
				setHp(0);
			}
			else
			{
				DYNAMIC_ASSERT(0);

			}
		}
        else if ( type == DT_MP )
		{
			if (ATTACK_RESULT_TYPE_HURT == resType)
			{
				 setMp( getMp() - value );
			}
			else if(ATTACK_RESULT_TYPE_HURT_CHANGE_RECOVER == resType)
			{
                 setMp( getMp() + value);
			}

		}
        else if ( type == DT_SP )
		{
            //setSp( getSp() );
		}
        else if ( type == DT_HPMP )
        {
            //setHp( getHp() );
            //setMp( getMp() );
        }
        else if ( type == DT_PROMILLE_SP )
        {
            ;
        }
        else if ( type == DT_PROMILLE_MP )
        {
            ;
        }
        else if ( type == DT_PROMILLE_HP )
        {
            ;
        }
        else if ( type == DT_PROMILLE_HPMP )
        {
            ;
        }
        else
        {
            DYNAMIC_ASSERT(0);
        }
    }
	//-----------------------------------------------------------------------------
	MG::Int SCharacter::getHp()
	{
		return getData()->mHp;
	}
	//-----------------------------------------------------------------------------
	MG::Int SCharacter::getMp()
	{
		return getData()->mMp;
	}
	//-----------------------------------------------------------------------------
	MG::Int SCharacter::getMaxHp()
	{
		return getSAttributeSystem()->getMaxHp();
	}
	//-----------------------------------------------------------------------------
	MG::Int SCharacter::getMaxMp()
	{
		return getSAttributeSystem()->getMaxMp();
	}
	//-----------------------------------------------------------------------------
	MG::Int SCharacter::getSp()
	{
		return getData()->mSp;
	}
	//-----------------------------------------------------------------------------
	MG::Int SCharacter::getMaxSp()
	{
		return getSAttributeSystem()->getMaxSp();
	}
	//-----------------------------------------------------------------------------
	MG::UInt SCharacter::getLineageNum()
	{
		return getData()->mLineageNum;
	}
	//-----------------------------------------------------------------------------
	void SCharacter::setHp( Int hp )
	{
		Int maxHp = getMaxHp();
		if ( hp > maxHp )
			getData()->mHp = maxHp;
		else if ( hp <= 0 )
		{	
			getData()->mHp = 0;
			dead();
		}
		else
			getData()->mHp = hp;
	}
	//-----------------------------------------------------------------------------
	void SCharacter::setMp( Int mp )
	{
		UInt maxMp = getMaxMp();
		if ( mp > maxMp )
			getData()->mMp = maxMp;
		else if ( mp <= 0 )
			getData()->mMp = 0;
		else
			getData()->mMp = mp;
	}
	//-----------------------------------------------------------------------------
	void SCharacter::setSp( Int sp )
	{
		UInt maxSp = getMaxSp();
		if ( sp > maxSp )
			getData()->mSp = maxSp;
		else if ( sp <= 0 )
			getData()->mSp = 0;
		else
			getData()->mSp = sp;
	}

    //-----------------------------------------------------------------------------------
    // World Info
    //-----------------------------------------------------------------------------------



}