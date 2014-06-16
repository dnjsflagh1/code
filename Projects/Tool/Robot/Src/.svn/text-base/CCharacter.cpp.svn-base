/******************************************************************************/
#include "stdafx.h"
#include "CCharacter.h"
#include "CharacterList.h"
//#include "CSkillUseManager.h"
#include "CTroopObject.h"
/******************************************************************************/
namespace MG
{
    CCharacter::CCharacter( GAMEOBJ_TYPE type, GameObjectData* data, PlayerCharacterIdType id )
        :GameObject(type, GQT_PLAYERCHARACTER,data, id)
        ,mCharacterTempInfo(NULL)
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
        //mCAttributeSystem.calBaseAttr(this);
        //calOtherAttr();
        //mCAttributeSystem.calFinalAttr(mCharacterTempInfo->getCharacterFormulaType(), this);
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
    void CCharacter::setHpMpSp( Flt num, DamageType type, ATTACK_RESULT_TYPE resType )
    {
        //死亡
        if ( ATTACK_RESULT_TYPE_DEAD == resType )
        {    
            setHp(0);
        }
        //恢复
        if ( ATTACK_RESULT_TYPE_RECOVER == resType )
        {
            if ( type & DT_HP )
            {
                setHp(getHp()+num);
            }
            if ( type & DT_MP )
            {
                //mCAttributeSystem.addValue(ATTR_ID_Mp, num);
                setMp(getMp()+num);
            }
            if ( type & DT_SP )
            {
                //mCAttributeSystem.addValue(ATTR_ID_Sp, num);
                setSp(getSp()+num);
            }

        }
        //伤害
        if ( ATTACK_RESULT_TYPE_HURT == resType )
        {
            if ( type & DT_HP )
            {
                //mCAttributeSystem.addValue(ATTR_ID_Hp, -num);
                setHp(getHp()-num);
            }
            if ( type & DT_MP )
            {
                //mCAttributeSystem.addValue(ATTR_ID_Mp, -num);
                setMp(getMp()-num);
            }
            if ( type & DT_SP )
            {
                //mCAttributeSystem.addValue(ATTR_ID_Sp, -num);
                setSp(getSp()-num);
            }
        }
    }
    //-----------------------------------------------------------------------------
    CharacterData* CCharacter::getCharacterData()
    {
        return (CharacterData*)GameObject::getGameObjectData();
    }
	//-----------------------------------------------------------------------------
	CTroopObject* CCharacter::createTroopObject( TroopData* data, CCharacterSceneEntityDynamicData* dynamicData)
	{
		CTroopObject* troopObject = getTroopObject( data->mId );
		if ( troopObject == NULL )
		{
			troopObject = MG_NEW CTroopObject();
			mCTroopObjectList[data->mId] = troopObject;

			// copy data
			*(troopObject->getBaseData())       = *data;
			*(troopObject->getDynamicData())    = *dynamicData;
			//必须在创建Soldier之后调用
			troopObject->initialize();
		}

		return troopObject;
	}
	//-----------------------------------------------------------------------------
	CTroopObject* CCharacter::getTroopObject( IdType id )
	{
		TroopObjectListIt it = mCTroopObjectList.find(id);
		if(it != mCTroopObjectList.end() && it->second)
		{
			return it->second;
		}
		return NULL;
	}


	//-----------------------------------------------------------------------------
}