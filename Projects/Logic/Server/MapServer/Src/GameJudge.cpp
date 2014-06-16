//**********************************************************************************************************
#include "stdafx.h"
#include "GameJudge.h"
#include "CharacterJudgeTemplate.h"
#include "ClanJudgeTemplate.h"
#include "SCharacter.h"
#include "AttributeAppend.h"
#include "SSkillOwnManager.h"
#include "SBuffManager.h"
#include "BuffObject.h"
#include "SCDManager.h"
#include "SAttributeSystem.h"
//**********************************************************************************************************
namespace MG
{
	
	Bool CharacterJudge::checkAttrAppendId(SCharacter* pSCharacter, U32 attrAppendId)
	{
		if ( 0 != attrAppendId )
		{
			const AttributeAppendInfo* pAttributeAppendInfo = AttributeAppend::getInstance().getAttributeAppendInfo(attrAppendId);
			DYNAMIC_ASSERT(pAttributeAppendInfo);
			for (Int i=0; i<APPENDATTR_NUM; i++)
			{
				if ( 0 == pAttributeAppendInfo->AppendAttrList[i].id )
					continue;
				if ( pSCharacter->getSAttributeSystem()->getFanalValue(pAttributeAppendInfo->AppendAttrList[i].id) < pAttributeAppendInfo->AppendAttrList[i].value )
					return false;
			}
		}
		return true;
	}
	//--------------------------------------------------------------------------------------------
	Bool CharacterJudge::checkSkillId(SCharacter* pSCharacter, U32 skillId)
	{
		if ( 0 != skillId )
		{
			if ( false == pSCharacter->getSkillOwnManager()->isOwnSkill(skillId) )
				return false;
		}
		return true;
	}
	//--------------------------------------------------------------------------------------------
	Bool CharacterJudge::checkBuff(SCharacter* pSCharacter, U32 buffId, U32 addNum)
	{
		if ( 0 != buffId )
		{
			//是否有这个buff
			BuffObject* pBuffObject = pSCharacter->getSBuffManager()->findBuffByBuffId<BuffObject>(buffId);
			if ( NULL == pBuffObject ) return false;
			//buff的层次是否达到
			BuffData* pBuffData = pBuffObject->getBuffData();
			DYNAMIC_ASSERT(pBuffData);
			if ( pBuffData->mCurAddNum < addNum ) return false;
		}

		return true;
	}
	//--------------------------------------------------------------------------------------------
	Bool CharacterJudge::checkSpecialStatus(SCharacter* pSCharacter, U32 stateFlag)
	{
		if ( 0 == stateFlag ) return true;

		if ( stateFlag & ( 1 << (STATUS_STATUSSYSTYPE_VERDIGO-1) ) )
		{
			if ( pSCharacter->getSBuffManager()->isHaveSpecialEffect(STATUS_STATUSSYSTYPE_VERDIGO) )
				return false;
		}
		if ( stateFlag & ( 1 << (STATUS_STATUSSYSTYPE_CHAOS-1) ) )
		{
			if ( pSCharacter->getSBuffManager()->isHaveSpecialEffect(STATUS_STATUSSYSTYPE_CHAOS) )
				return false;
		}
		if ( stateFlag & ( 1 << (STATUS_STATUSSYSTYPE_BLOCKADE-1) ) )
		{
			if ( pSCharacter->getSBuffManager()->isHaveSpecialEffect(STATUS_STATUSSYSTYPE_BLOCKADE) )
				return false;
		}
		if ( stateFlag & ( 1 << (STATUS_STATUSSYSTYPE_SLOWDOWN-1) ) )
		{
			if ( pSCharacter->getSBuffManager()->isHaveSpecialEffect(STATUS_STATUSSYSTYPE_SLOWDOWN) )
				return false;
		}
		if ( stateFlag & ( 1 << (STATUS_STATUSSYSTYPE_POISON-1) ) )
		{
			if ( pSCharacter->getSBuffManager()->isHaveSpecialEffect(STATUS_STATUSSYSTYPE_POISON) )
				return false;
		}
		if ( stateFlag & ( 1 << (STATUS_STATUSSYSTYPE_BLEED-1) ) )
		{
			if ( pSCharacter->getSBuffManager()->isHaveSpecialEffect(STATUS_STATUSSYSTYPE_BLEED) )
				return false;
		}
		if ( stateFlag & ( 1 << (STATUS_STATUSSYSTYPE_DEAD-1) ) )
		{
			if ( pSCharacter->getSBuffManager()->isHaveSpecialEffect(STATUS_STATUSSYSTYPE_DEAD) )
				return false;
		}
		if ( stateFlag & ( 1 << (STATUS_STATUSSYSTYPE_INVISIBILITY-1) ) )
		{
			if ( pSCharacter->getSBuffManager()->isHaveSpecialEffect(STATUS_STATUSSYSTYPE_INVISIBILITY) )
				return false;
		}

		return true;
	}
	//--------------------------------------------------------------------------------------------
	Bool CharacterJudge::checkTimepieceID(SCharacter* pSCharacter, U32 cdId)
	{
		if ( 0 == cdId )
			return true;

		if ( false == pSCharacter->getSCDManager()->checkCD(CD_MASTER_TYPE_CHARACTER, cdId) )
			return false;

		return true;
	}
	//--------------------------------------------------------------------------------------------
	MG::Bool CharacterJudge::checkCharacterJudge( SCharacter* pSCharacter, U32 characterJudgeId )
	{
		DYNAMIC_ASSERT(pSCharacter);
		if ( characterJudgeId == 0 ) return true;

		const CharacterJudgeInfo* pCharacterJudgeInfo = CharacterJudgeTemplate::getInstance().getCharacterJudgeInfo(characterJudgeId);
		DYNAMIC_ASSERT(pCharacterJudgeInfo);

		//角色属性使用下线。
		if ( false == checkAttrAppendId(pSCharacter, pCharacterJudgeInfo->AbilityAppendId) ) 
			return false;

		//如果自己没有SkillId，则不能使用。
		if ( false == checkSkillId(pSCharacter, pCharacterJudgeInfo->SkillId) )
			return false;

		//状态id，和 num
		if ( false == checkBuff(pSCharacter, pCharacterJudgeInfo->StateId, pCharacterJudgeInfo->AddNum) )
			return false;

		//检查特殊状态标志。
		if ( false == checkSpecialStatus(pSCharacter, pCharacterJudgeInfo->StateFlag) )
			return false;

		//检查CD id
		if ( false == checkTimepieceID(pSCharacter, pCharacterJudgeInfo->TimepieceId) )
			return false;

		return true;
	}
	//--------------------------------------------------------------------------------------------
	MG::Bool GameJudge::checkGameJudge( SCharacter* pSCharacter, U32 characterJudgeId )
	{
		//角色判断：如果需要判断，并且判断为误，返回false
		if (  false == mCharacterJudge.checkCharacterJudge(pSCharacter, characterJudgeId) )	
		{
			return  false;
		}
	
		return true;
	}
}   