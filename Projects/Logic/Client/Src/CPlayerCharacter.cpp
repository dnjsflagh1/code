/******************************************************************************/
#include "stdafx.h"
#include "CPlayerCharacter.h"
#include "LoginNetPacket.h"
#include "ClientMain.h"
#include "IEntity.h"
//#include "CWorldManager.h"
#include "UIGenrealPicture.h"
#include "PlayerCharacterData.h"
#include "UIClanInfo.h"
#include "CPlayerCharacterEntity.h"
#include "CSceneManager.h"
#include "CBuffManager.h"
#include "CItemManager.h"
#include "CSkillOwnManager.h"
#include "CCDManager.h"
/******************************************************************************/

namespace MG
{

	//--------------------------------------------------------------------------------
	CPlayerCharacter::CPlayerCharacter()
        :CCharacter(GOT_PLAYERCHARACTER, MG_NEW PlayerCharacterData() )
	{
	}
    
	//--------------------------------------------------------------------------------
	CPlayerCharacter::~CPlayerCharacter()
	{
       
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

        setCharacterTempInfo();

        calAttr();

		//创建CD管理器
		CCDManager::getInstance().addCharacter(CD_MASTER_TYPE_CHARACTER, pData->mId);
		//根据id创建武将背包，装备栏
		CItemManager::getInstance().createItemBag(pData->mId);
    }
    //--------------------------------------------------------------------------------
    void CPlayerCharacter::calOtherAttr()
    {
		//技能
		getSkillOwnManager()->calAttrAllBase();
		//装备
		CItemManager::getInstance().calAttrAllBase(this);
		//buff
		CPlayerCharacterEntity* pCPlayerCharacterEntity = CSceneManager::getInstance().getPlayerCharacterEntity(getID());
		if (pCPlayerCharacterEntity)
			pCPlayerCharacterEntity->getCBuffManager()->calAttrAllBase();
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
	//--------------------------------------------------------------------------------
    void CPlayerCharacter::setHp( Int val )
    {

        CCharacter::setHp(val);
		UIGenrealPicture::getInstance().setHp( getData()->mId );
    }
	//--------------------------------------------------------------------------------
    void CPlayerCharacter::setMp( Int val )
    {
	    CCharacter::setMp(val);
		UIGenrealPicture::getInstance().setMp( getData()->mId );
    }
	//--------------------------------------------------------------------------------
    void CPlayerCharacter::setSp( Int val )
    {
		//CCharacter::setSp(val);
    }
	//--------------------------------------------------------------------------------
	MG::Str16 CPlayerCharacter::getNormalName()
	{
		return getData()->charSurName + getData()->mName;
	}
	//--------------------------------------------------------------------------------

	MG::U32 CPlayerCharacter::getExp()
	{
		return getData()->charExp1;
	}
	//--------------------------------------------------------------------------------
	MG::UInt CPlayerCharacter::getDBAttrInitID()
	{
		return getData()->charAttrAppendId;
	}
	//--------------------------------------------------------------------------------
	MG::UInt CPlayerCharacter::getDBAttrLvlAddID()
	{
		return getData()->charAttrAppendLvlAddId;
	}
	//--------------------------------------------------------------------------------
	void CPlayerCharacter::unInit()
	{
		//创建CD管理器
		CCDManager::getInstance().deleteCharacter(CD_MASTER_TYPE_CHARACTER, getID());
		//根据id创建武将背包，装备栏
		CItemManager::getInstance().eraseItemBag(getID());
	}
}