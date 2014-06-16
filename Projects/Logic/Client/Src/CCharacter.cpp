/******************************************************************************/
#include "stdafx.h"
#include "CCharacter.h"
#include "CharacterList.h"
#include "CSkillOwnManager.h"
#include "UIAliveRpg.h"
#include "UIAliveSlg.h"
#include "InstanceType2GameType.h"
/******************************************************************************/
namespace MG
{
    CCharacter::CCharacter( GAMEOBJ_TYPE type, GameObjectData* data, PlayerCharacterIdType id )
        :GameObject(type, GQT_UNKNOWN, data)
        ,mCharacterTempInfo(NULL)
        ,mSkillOwnManager(MG_NEW CSkillOwnManager(this))
    {
		
    }
    //-----------------------------------------------------------------------------
    CCharacter::~CCharacter()
    {
        mCharacterTempInfo = NULL;
    }
    //-----------------------------------------------------------------------------
    MG::U32 CCharacter::getCharacterTemplateID()
    {
        return getCharacterData()->mCharacterTemplateID;
    }
    //-----------------------------------------------------------------------------
    void CCharacter::setCharacterTemplateID( U32 id )
    {
        getCharacterData()->mCharacterTemplateID = id;
    }
    //-----------------------------------------------------------------------------
    MG::U32 CCharacter::getLevel()
    {
        return getCharacterData()->mLevel;
    }
    //-----------------------------------------------------------------------------
    void CCharacter::setLevel( U32 level )
    {
        getCharacterData()->mLevel = level;
    }
    //-----------------------------------------------------------------------------
    void CCharacter::setRegion( REGION_OBJ_TYPE type, U32 id, InstanceIdType instanceId, Bool isCalBelongMapID/*=false*/ )
    {
        getCharacterData()->mRegionType = type;
        getCharacterData()->mRegionID = id;
		 getCharacterData()->mInstanceUId = instanceId;
    }
    //-----------------------------------------------------------------------------
    MG::REGION_OBJ_TYPE CCharacter::getRegionType()
    {
        return getCharacterData()->mRegionType;
    }
    //-----------------------------------------------------------------------------
    MG::U32 CCharacter::getRegionID()
    {
        return getCharacterData()->mRegionID;
    }

	//-----------------------------------------------------------------------------
	InstanceIdType CCharacter::getInstanceUId()
	{
		 return getCharacterData()->mInstanceUId;
	}

    //-----------------------------------------------------------------------------
    void CCharacter::setCharacterTempInfo()
    {
        mCharacterTempInfo = CharacterTemplate::getInstance().getCharacterTempInfo(getCharacterData()->mCharacterTemplateID);
    }
    //-----------------------------------------------------------------------------
    const CharacterTempInfo* CCharacter::getCharacterTempInfo()
    {
        return mCharacterTempInfo;
    }
    //-----------------------------------------------------------------------------
    void CCharacter::calAttr(  )
    {
        //计算系统属性和天赋属性
		mCAttributeSystem.getCalAttrInfo()->resetAllValue();
        mCAttributeSystem.calBaseAttr(this);
        calOtherAttr();
        mCAttributeSystem.calFinalAttr(mCharacterTempInfo->getCharacterFormulaType(), getCharacterData());
    }
    //-----------------------------------------------------------------------------
    MG::Int CCharacter::getFanalValue( U32 id )
    {
        return mCAttributeSystem.getFanalValue(id); 
    }
    //-----------------------------------------------------------------------------
    void CCharacter::setFanalValue( U32 id, Flt val )
    {
        mCAttributeSystem.setFanalValue(id, val);
    }
    //-----------------------------------------------------------------------------
    CSkillOwnManager* CCharacter::getSkillOwnManager()
    {
        return mSkillOwnManager;
    }

    //-----------------------------------------------------------------------------
    void CCharacter::setHpMpSp( Flt num, DamageType type, ATTACK_RESULT_TYPE resType )
    {
        //死亡
        if ( ATTACK_RESULT_TYPE_DEAD == resType )
        {    
            setHp(0);

			const REGION_OBJ_TYPE regionType = getRegionType();

			const GameType gameType = InstanceType2GameType::InstanceTypeChangeGameType(regionType);
			if (GameType_Rpg == gameType)
			{
				//RPG
				UIAliveRpg::getInstance().openGui();
			}
			else if(GameType_Slg == gameType)
			{
				//SLG
				UIAliveSlg::getInstance().openGui();
			}
			else
			{
				DYNAMIC_ASSERT(0);
			}

        }
        //恢复
        if ( ATTACK_RESULT_TYPE_RECOVER == resType )
        {
            if ( type == DT_HP )
            {
                setHp(getHp()+num);
            }
            else if ( type == DT_MP )
            {
                setMp(getMp()+num);
            }
            else if ( type == DT_SP )
            {
                setSp(getSp()+num);
            }
            else if ( type == DT_HPMP )
            {
                setHp(getHp()+num);
                setMp(getMp()+num);
            }

        }
        //伤害
        if ( ATTACK_RESULT_TYPE_HURT == resType )
        {
            if ( type == DT_HP )
            {
                setHp(getHp()-num);
            }
            else if ( type == DT_MP )
            {
                setMp(getMp() - num);
            }
            else if ( type == DT_SP )
            {
                setSp(getSp() - num);
            }
            else if ( type == DT_HPMP )
            {
                setHp(getHp() - num);
                setMp(getMp() - num);
            }
        }
    }
    //-----------------------------------------------------------------------------
    CharacterData* CCharacter::getCharacterData()
    {
        return (CharacterData*)GameObject::getGameObjectData();
    }
	//-----------------------------------------------------------------------------
	MG::UInt CCharacter::getHp()
	{
		return getCharacterData()->mHp;
	}
	//-----------------------------------------------------------------------------
	MG::UInt CCharacter::getMp()
	{
		return getCharacterData()->mMp;
	}
	//-----------------------------------------------------------------------------
	void CCharacter::setHp( Int val )
	{
		Int maxHp = getMaxHp();
		if ( val > maxHp )
			getCharacterData()->mHp = maxHp;
		else if ( val <= 0 )
		{	
			getCharacterData()->mHp = 0;
		}
		else
			getCharacterData()->mHp = val;
	}
	//-----------------------------------------------------------------------------
	void CCharacter::setMp( Int val )
	{
		Int maxMp = getMaxMp();
		if ( val > maxMp )
			getCharacterData()->mMp = maxMp;
		else if ( val <= 0 )
		{	
			getCharacterData()->mMp = 0;
		}
		else
			getCharacterData()->mMp = val;
	}
	//-----------------------------------------------------------------------------
	MG::UInt CCharacter::getMaxHp()
	{
		return mCAttributeSystem.getMaxHp();
	}
	//-----------------------------------------------------------------------------
	MG::UInt CCharacter::getMaxMp()
	{
		return mCAttributeSystem.getMaxMp();
	}
	//-----------------------------------------------------------------------------
	MG::UInt CCharacter::getSp()
	{
		return getCharacterData()->mSp;
	}
	//-----------------------------------------------------------------------------
	MG::UInt CCharacter::getMaxSp()
	{
		return mCAttributeSystem.getMaxSp();
	}
	//-----------------------------------------------------------------------------
	void CCharacter::setSp( Int val )
	{
		DYNAMIC_ASSERT(val >= 0);
		getCharacterData()->mSp = val;
	}
	//-----------------------------------------------------------------------------
	void CCharacter::setMax_HpSpMp()
	{
		setHp( getMaxHp() );
		setMp( getMaxMp() );
		setSp( getMaxSp() );
	}
	//-----------------------------------------------------------------------------
	MG::UInt CCharacter::getLineageNum()
	{
		return getCharacterData()->mLineageNum;
	}
	//-----------------------------------------------------------------------------
}