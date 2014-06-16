/******************************************************************************/
#include "stdafx.h"
#include "CPlayerCharacter.h"
#include "LoginNetPacket.h"
//#include "CWorldManager.h"
#include "PlayerCharacterData.h"
#include "CSkillOwnManager.h"
/******************************************************************************/

namespace MG
{

	//--------------------------------------------------------------------------------
	CPlayerCharacter::CPlayerCharacter()
        :CCharacter(GOT_PLAYERCHARACTER, MG_NEW PlayerCharacterData() )
	{
		mSkillOwerMgr = MG_NEW CSkillOwnManager(this);
	}
    
	//--------------------------------------------------------------------------------
	CPlayerCharacter::~CPlayerCharacter()
	{
       MG_SAFE_DELETE(mSkillOwerMgr);
	}
    //--------------------------------------------------------------------------------
    PlayerCharacterData* CPlayerCharacter::getData()
    {
        return (PlayerCharacterData*)GameObject::getGameObjectData();
    }
    //--------------------------------------------------------------------------------
    void CPlayerCharacter::init( PlayerCharacterData* pData )
    {
        *getData() = *pData;

        //setCharacterTempInfo();

        //calAttr();
    }
    //--------------------------------------------------------------------------------
    void CPlayerCharacter::calOtherAttr()
    {

    }
    //--------------------------------------------------------------------------------
    MG::U32 CPlayerCharacter::getMp()
    {
        return getData()->mMp;
    }
    //--------------------------------------------------------------------------------
    MG::U32 CPlayerCharacter::getHp()
    {
        return getData()->mHp;
    }
    //--------------------------------------------------------------------------------
    //MG::U32 CPlayerCharacter::getSp()
    //{
    //    return getData()->charSP;
    //}
    //--------------------------------------------------------------------------------
    MG::UInt CPlayerCharacter::getLineageNum()
    {
        return getData()->mLineageNum;
    }
    //--------------------------------------------------------------------------------
    MG::Flt CPlayerCharacter::getDBAttrInit( UInt index )
    {
        return getData()->charAttrRand[index];
    }
    //--------------------------------------------------------------------------------
    MG::Flt CPlayerCharacter::getDBAttrLvlAdd( UInt index )
    {
        return getData()->charAttrRandAdd[index];
    }

    void CPlayerCharacter::setHp( UInt val )
    {

    }

    void CPlayerCharacter::setMp( UInt val )
    {

    }

    void CPlayerCharacter::setSp( UInt val )
    {

    }

	MG::Bool CPlayerCharacter::getJoinRegion()
	{
		return mIsJoinRegion;
	}

	void CPlayerCharacter::setJoinRegion( Bool isJoinRegion )
	{
		mIsJoinRegion = isJoinRegion;
	}

	/*void CPlayerCharacter::addSkill( SkillData skillData )
	{
		mSkillOwerMgr->addSkillData(skillData);
	}*/
}