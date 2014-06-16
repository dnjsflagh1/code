//**********************************************************************************************************
#include "stdafx.h"
#include "GameJudge.h"
#include "CharacterJudgeTemplate.h"
#include "ClanJudgeTemplate.h"
#include "CClan.h"
#include "CCharacter.h"
#include "CClanQuestManager.h"
#include "CItemManager.h"
#include "CCDManager.h"
#include "CSkillOwnManager.h"
#include "CharacterList.h"
#include "AttributeAppend.h"
#include "CPlayer.h"
#include "CSceneManager.h"
#include "CCharacterSceneEntity.h"
#include "CBuffManager.h"
#include "BuffObject.h"
//**********************************************************************************************************
namespace MG
{
	Bool ClanJudge::checkClanLevel(CClan* pSClan, U32 level)
	{
		return true;
	}
	//--------------------------------------------------------------------------------------------
	Bool ClanJudge::checkClanQuest(CClan* pSClan, U32 questId)
	{
		if ( 0 == questId ) return true;

		if ( false == CClanQuestManager::getInstance().isExistInFinishedQuests(questId) )
			return false;

		return true;
	}
	//--------------------------------------------------------------------------------------------
	Bool ClanJudge::checkClanItemAndNum(CClan* pSClan, U32 itemTemplateId, U32 num)
	{
		if ( 0 == itemTemplateId ) return true;

		U32 tempNum = CItemManager::getInstance().findItemCountByTemplateId(itemTemplateId, ITEM_SITE_TYPE_CLAN);
		if ( tempNum < num )
			return false;

		return true;
	}
	//--------------------------------------------------------------------------------------------
	GAMEJUDGE_TYPE ClanJudge::checkClanJudge( CClan* pSClan, U32 clanJudgeId )
	{
		if ( 0 == clanJudgeId ) return GAMEJUDGE_TYPE_SUCCESS;

		const ClanJudgeInfo* pClanJudgeInfo = ClanJudgeTemplate::getInstance().getClanJudgeInfo(clanJudgeId);
		if (!pClanJudgeInfo)
		{
			DYNAMIC_ASSERT_LOG(pClanJudgeInfo,"error: pClanJudgeInfo==NULL!");
			return GAMEJUDGE_TYPE_UNKNOWN_ERROR;
		}

		if ( false == checkClanLevel(pSClan, pClanJudgeInfo->Level) )
			return GAMEJUDGE_TYPE_CLAN_LEVEL_ERROR;

		if ( false == checkClanQuest(pSClan, pClanJudgeInfo->QuestId) )
			return GAMEJUDGE_TYPE_CLAN_COMPLETE_QUEST_ERROR;

		if ( false == checkClanItemAndNum(pSClan, pClanJudgeInfo->ItemTemplateId, pClanJudgeInfo->ItemNum) )
			return GAMEJUDGE_TYPE_UNKNOWN_ERROR;

		return GAMEJUDGE_TYPE_SUCCESS;
	}
	//--------------------------------------------------------------------------------------------
	Bool CharacterJudge::checkkCharacterType(CCharacterSceneEntity* pCCharacterSceneEntity, CCharacter* pSCharacter, U32 characterType)
	{
		if ( 0 == characterType ) return true;

		if ( pSCharacter )
		{
			if ( characterType & ( 1 << (pSCharacter->getCharacterTempInfo()->getCharacterType()-1) ) )
				return true;
		}
		else
		{
			if ( characterType & ( 1 << (pCCharacterSceneEntity->getCharacterTempInfo()->getCharacterType()-1) ) )
				return true;
		}

		return false;
	}
	//--------------------------------------------------------------------------------------------
	Bool CharacterJudge::checkkCharacterLevel(CCharacterSceneEntity* pCCharacterSceneEntity, CCharacter* pSCharacter, U32 characterLevel)
	{
		if ( 0 == characterLevel ) return true;

		if ( pSCharacter )
		{
			if ( pSCharacter->getLevel() < characterLevel )
				return false;
		}
		else
		{
			if ( pCCharacterSceneEntity->getDynamicData()->mLevel < characterLevel )
				return false;
		}
		

		return true;
	}
	//--------------------------------------------------------------------------------------------
	Bool CharacterJudge::checkkCharacterLineageLevel(CCharacterSceneEntity* pCCharacterSceneEntity, CCharacter* pSCharacter, U32 characterLineageLevel)
	{
		if ( 0 == characterLineageLevel ) return true;
		
		if ( pSCharacter )
		{
			if ( pSCharacter->getLineageNum() < characterLineageLevel )
				return false;
		}
		else
		{
			if ( pCCharacterSceneEntity->getDynamicData()->mLineageNum < characterLineageLevel )
				return false;
		}

		return true;
	}
	//--------------------------------------------------------------------------------------------
	Bool CharacterJudge::checkkCharacterGenderType(CCharacterSceneEntity* pCCharacterSceneEntity, CCharacter* pSCharacter, U32 characterGenderType)
	{
		if ( 0 == characterGenderType ) return true;

		if ( pSCharacter )
		{
			if ( characterGenderType != pSCharacter->getCharacterTempInfo()->getCharacterGenderType() )
				return false;
		}
		else
		{
			if ( characterGenderType != pCCharacterSceneEntity->getCharacterTempInfo()->getCharacterGenderType() )
				return false;
		}

		return true;
	}
	//--------------------------------------------------------------------------------------------
	//只有将领才会检查
	Bool CharacterJudge::checkkGenrealPowerfullType(CCharacterSceneEntity* pCCharacterSceneEntity, CCharacter* pSCharacter, U32 genrealPowerfullType)
	{
		if ( GOT_PLAYERCHARACTER != pSCharacter->getType() ) return true;

		if ( 0 == genrealPowerfullType ) return true;

		if ( pSCharacter )
		{
			if ( genrealPowerfullType & ( 1 << (pSCharacter->getCharacterTempInfo()->getGenrealPowerfulType() - 1) ) )
				return true;
		}
		else
		{
			if ( genrealPowerfullType & ( 1 << (pCCharacterSceneEntity->getCharacterTempInfo()->getGenrealPowerfulType() - 1) ) )
				return true;
		}

		return false;
	}
	//--------------------------------------------------------------------------------------------
	//除了军队，其它都为特殊兵种。
	Bool CharacterJudge::checkkArmyType(CCharacterSceneEntity* pCCharacterSceneEntity, CCharacter* pSCharacter, U32 armyType)
	{
		if ( 0 == armyType ) return true;

		if ( pSCharacter )
		{
			if ( armyType & ( 1 << ( pSCharacter->getCharacterTempInfo()->getCharacterArmyType() -1 ) ) )
				return true;
		}
		else
		{
			if ( armyType & ( 1 << ( pCCharacterSceneEntity->getCharacterTempInfo()->getCharacterArmyType() -1 ) ) )
				return true;
		}
		

		return false;
	}
	Bool CharacterJudge::checkAttrAppendId(CCharacterSceneEntity* pCCharacterSceneEntity, CCharacter* pSCharacter, U32 attrAppendId)
	{
		if ( 0 != attrAppendId )
		{
			const AttributeAppendInfo* pAttributeAppendInfo = AttributeAppend::getInstance().getAttributeAppendInfo(attrAppendId);
			DYNAMIC_ASSERT(pAttributeAppendInfo);
			for (Int i=0; i<APPENDATTR_NUM; i++)
			{
				if ( 0 == pAttributeAppendInfo->AppendAttrList[i].id )
					continue;
				if ( pSCharacter->getFanalValue(pAttributeAppendInfo->AppendAttrList[i].id) < pAttributeAppendInfo->AppendAttrList[i].value )
					return false;
			}
		}
		return true;
	}
	//--------------------------------------------------------------------------------------------
	Bool CharacterJudge::checkSkillId(CCharacterSceneEntity* pCCharacterSceneEntity, CCharacter* pSCharacter, U32 skillId)
	{
		if ( 0 != skillId )
		{
			if ( false == pSCharacter->getSkillOwnManager()->isOwnSkill(skillId) )
				return false;
		}
		return true;
	}
	//--------------------------------------------------------------------------------------------
	Bool CharacterJudge::checkBuff(CCharacterSceneEntity* pCCharacterSceneEntity, CCharacter* pSCharacter, U32 buffId, U32 addNum)
	{
		if ( 0 != buffId )
		{
			//是否有这个buff
			BuffObject* pBuffObject = pCCharacterSceneEntity->getCBuffManager()->findBuffByBuffId<BuffObject>(buffId);
			if ( NULL == pBuffObject ) return false;
			//buff的层次是否达到
			BuffData* pBuffData = pBuffObject->getBuffData();
			DYNAMIC_ASSERT(pBuffData);
			if ( pBuffData->mCurAddNum < addNum ) return false;
		}

		return true;
	}
	//--------------------------------------------------------------------------------------------
	Bool CharacterJudge::checkSpecialStatus(CCharacterSceneEntity* pCCharacterSceneEntity, CCharacter* pSCharacter, U32 stateFlag)
	{
		if ( 0 == stateFlag ) return true;

		if ( stateFlag & ( 1 << (STATUS_STATUSSYSTYPE_VERDIGO-1) ) )
		{
			if ( pCCharacterSceneEntity->getCBuffManager()->isHaveSpecialEffect(STATUS_STATUSSYSTYPE_VERDIGO) )
				return false;
		}
		if ( stateFlag & ( 1 << (STATUS_STATUSSYSTYPE_CHAOS-1) ) )
		{
			if ( pCCharacterSceneEntity->getCBuffManager()->isHaveSpecialEffect(STATUS_STATUSSYSTYPE_CHAOS) )
				return false;
		}
		if ( stateFlag & ( 1 << (STATUS_STATUSSYSTYPE_BLOCKADE-1) ) )
		{
			if ( pCCharacterSceneEntity->getCBuffManager()->isHaveSpecialEffect(STATUS_STATUSSYSTYPE_BLOCKADE) )
				return false;
		}
		if ( stateFlag & ( 1 << (STATUS_STATUSSYSTYPE_SLOWDOWN-1) ) )
		{
			if ( pCCharacterSceneEntity->getCBuffManager()->isHaveSpecialEffect(STATUS_STATUSSYSTYPE_SLOWDOWN) )
				return false;
		}
		if ( stateFlag & ( 1 << (STATUS_STATUSSYSTYPE_POISON-1) ) )
		{
			if ( pCCharacterSceneEntity->getCBuffManager()->isHaveSpecialEffect(STATUS_STATUSSYSTYPE_POISON) )
				return false;
		}
		if ( stateFlag & ( 1 << (STATUS_STATUSSYSTYPE_BLEED-1) ) )
		{
			if ( pCCharacterSceneEntity->getCBuffManager()->isHaveSpecialEffect(STATUS_STATUSSYSTYPE_BLEED) )
				return false;
		}
		if ( stateFlag & ( 1 << (STATUS_STATUSSYSTYPE_DEAD-1) ) )
		{
			if ( pCCharacterSceneEntity->getCBuffManager()->isHaveSpecialEffect(STATUS_STATUSSYSTYPE_DEAD) )
				return false;
		}
		if ( stateFlag & ( 1 << (STATUS_STATUSSYSTYPE_INVISIBILITY-1) ) )
		{
			if ( pCCharacterSceneEntity->getCBuffManager()->isHaveSpecialEffect(STATUS_STATUSSYSTYPE_INVISIBILITY) )
				return false;
		}

		return true;
	}
	//--------------------------------------------------------------------------------------------
	Bool CharacterJudge::checkTimepieceID(CCharacterSceneEntity* pCCharacterSceneEntity, CCharacter* pSCharacter, U32 cdId)
	{
		if ( 0 == cdId )
			return true;

		if ( false == CCDManager::getInstance().checkCD(CD_MASTER_TYPE_CHARACTER, pCCharacterSceneEntity->getID(), cdId) )
			return false;

		return true;
	}
	//--------------------------------------------------------------------------------------------
	GAMEJUDGE_TYPE CharacterJudge::checkCharacterJudge( CCharacterSceneEntity* pCCharacterSceneEntity, CCharacter* pSCharacter, U32 characterJudgeId )
	{
		if ( 0 == characterJudgeId ) return GAMEJUDGE_TYPE_SUCCESS;

		const CharacterJudgeInfo* pCharacterJudgeInfo = CharacterJudgeTemplate::getInstance().getCharacterJudgeInfo(characterJudgeId);
        if (!pCharacterJudgeInfo)
        {
			DYNAMIC_ASSERT_LOG(pCharacterJudgeInfo,"pCharacterJudgeInfo == NULL!");
			return GAMEJUDGE_TYPE_UNKNOWN_ERROR;
        }

		if ( false == checkkCharacterType(pCCharacterSceneEntity, pSCharacter, pCharacterJudgeInfo->CharacterType) ) 
			return GAMEJUDGE_TYPE_CHARACTER_TYPE_ERROR;

		if ( false == checkkCharacterLevel(pCCharacterSceneEntity, pSCharacter, pCharacterJudgeInfo->Level) ) 
			return GAMEJUDGE_TYPE_CHARACTER_LEVEL_ERROR;

		if ( false == checkkCharacterLineageLevel(pCCharacterSceneEntity, pSCharacter, pCharacterJudgeInfo->LineageLevel) ) 
			return GAMEJUDGE_TYPE_UNKNOWN_ERROR;

		if ( false == checkkCharacterGenderType(pCCharacterSceneEntity, pSCharacter, pCharacterJudgeInfo->GenderType) ) 
			return GAMEJUDGE_TYPE_CHARACTER_GENDER_TYPE_ERROR;

		if ( false == checkkGenrealPowerfullType(pCCharacterSceneEntity, pSCharacter, pCharacterJudgeInfo->PowerfulType) ) 
			return GAMEJUDGE_TYPE_CHARACTER_POWERFULL_TYPE_ERROR;

		if ( false == checkkArmyType(pCCharacterSceneEntity, pSCharacter, pCharacterJudgeInfo->ArmyType) ) 
			return GAMEJUDGE_TYPE_UNKNOWN_ERROR;

		//角色属性使用下线。
		if ( false == checkAttrAppendId(pCCharacterSceneEntity, pSCharacter, pCharacterJudgeInfo->AbilityAppendId) ) 
			return GAMEJUDGE_TYPE_UNKNOWN_ERROR;

		//如果自己没有SkillId，则不能使用。
		if ( false == checkSkillId(pCCharacterSceneEntity, pSCharacter, pCharacterJudgeInfo->SkillId) )
			return GAMEJUDGE_TYPE_UNKNOWN_ERROR;

		//状态id，和 num
		if ( false == checkBuff(pCCharacterSceneEntity, pSCharacter, pCharacterJudgeInfo->StateId, pCharacterJudgeInfo->AddNum) )
			return GAMEJUDGE_TYPE_UNKNOWN_ERROR;

		//检查特殊状态标志。
		if ( false == checkSpecialStatus(pCCharacterSceneEntity, pSCharacter, pCharacterJudgeInfo->StateFlag) )
			return GAMEJUDGE_TYPE_UNKNOWN_ERROR;

		//检查CD id
		if ( false == checkTimepieceID(pCCharacterSceneEntity, pSCharacter, pCharacterJudgeInfo->TimepieceId) )
			return GAMEJUDGE_TYPE_UNKNOWN_ERROR;

		return GAMEJUDGE_TYPE_SUCCESS;
	}
	//--------------------------------------------------------------------------------------------
	GAMEJUDGE_TYPE GameJudge::checkGameJudge( CClan* pSClan, CCharacterSceneEntity* pCCharacterSceneEntity, CCharacter* pSCharacter, U32 clanJudgeId, U32 characterJudgeId )
	{
        
        GAMEJUDGE_TYPE judegeType;

		//角色判断：如果需要判断，并且判断为误，返回false
		judegeType = mCharacterJudge.checkCharacterJudge(pCCharacterSceneEntity, pSCharacter, characterJudgeId);
		if (judegeType != GAMEJUDGE_TYPE_SUCCESS)
		{
			return judegeType;
		}
		
		//氏族判断：如果需要判断，并且判断为误，返回false
		judegeType = mClanJudge.checkClanJudge(pSClan, clanJudgeId);	
		if (judegeType != GAMEJUDGE_TYPE_SUCCESS)
		{
			return judegeType;
		}

		return GAMEJUDGE_TYPE_SUCCESS;
	}
	//--------------------------------------------------------------------------------------------
	GAMEJUDGE_TYPE GameJudge::checkClanJudge( CClan* pSClan, U32 clanJudgeId )
	{  
		if (!pSClan)
		{ 
			DYNAMIC_ASSERT_LOG(pSClan,"error: pSClan == NULL!");
			return GAMEJUDGE_TYPE_UNKNOWN_ERROR;
		}
		return mClanJudge.checkClanJudge(pSClan, clanJudgeId);
		
	}
	//--------------------------------------------------------------------------------------------
	GAMEJUDGE_TYPE GameJudge::checkCharacterJudge( CCharacterSceneEntity* pCCharacterSceneEntity, CCharacter* pSCharacter, U32 characterJudgeId )
	{
		if ( pCCharacterSceneEntity == NULL )
		{
			DYNAMIC_ASSERT_LOG(pSCharacter,"error: pCCharacterSceneEntity ==NULL!");
			if (!pSCharacter)
			{
				return GAMEJUDGE_TYPE_UNKNOWN_ERROR;
			}
			pCCharacterSceneEntity = CSceneManager::getInstance().getCharacterSceneEntity(pSCharacter->getType(), pSCharacter->getID());
			DYNAMIC_ASSERT_LOG(pCCharacterSceneEntity,"error: pCCharacterSceneEntity ==NULL!");
			if (!pCCharacterSceneEntity)
			{
                return GAMEJUDGE_TYPE_UNKNOWN_ERROR;
			} 
		}

		if ( pSCharacter == NULL )
		{   
			if (!pCCharacterSceneEntity)
			{   
                 DYNAMIC_ASSERT_LOG(pCCharacterSceneEntity,"error: pCCharacterSceneEntity ==NULL!");
                 return GAMEJUDGE_TYPE_UNKNOWN_ERROR;
			}
			pSCharacter = CPlayer::getInstance().getActiveClan()->getCharacter(pCCharacterSceneEntity->getID(), pCCharacterSceneEntity->getType());
		}
        return  mCharacterJudge.checkCharacterJudge(pCCharacterSceneEntity, pSCharacter, characterJudgeId);
		
	}
}   