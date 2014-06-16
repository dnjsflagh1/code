/******************************************************************************/
#include "stdafx.h"
#include "SSkillUseManager.h"
#include "SPlayer.h"
#include "SLuaSkillSystem.h"
#include "CharacterSkillTempLate.h"
#include "SCharacter.h"
#include "SkillDB.h"
#include "CharacterList.h"
#include "SkillInfoList.h"
#include "SkillBaseInfo.h"
#include "ShortRangeGeneralAttackSkillTemplate.h"
#include "LongRangeGeneralAttackSkillTemplate.h"
#include "SingleTargetSkillTemplate.h"
#include "GameJudge.h"
/******************************************************************************/
namespace MG
{

    //-----------------------------------------------------------------------
    SSkillUseManager::SSkillUseManager( SCharacter* character )
        :SkillUseManager(character)
    {

    }

    //-----------------------------------------------------------------------
    SSkillUseManager::~SSkillUseManager()
    {
        destroySkillObject(mCurrUseSkill);
    }

    //-----------------------------------------------------------------------
    SkillObject* SSkillUseManager::createSkillObject(IdType id)
    {
		SkillInfo* skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(id);
		if(!skillInfo)
		{
			return NULL;
		}

		SCharacter* character = getSCharacter();
		if(skillInfo && character)
		{
			mCurrUseSkill= MG_POOL_NEW(mSkillObjectPool, SSkillObject, (character)); 
			mCurrUseSkill->setSkillInfo(skillInfo);
			return mCurrUseSkill;
		}

		return NULL;
    }

	//-----------------------------------------------------------------------
	Bool SSkillUseManager::isCanUseSkill(IdType skillId, SCharacter* targetCharacter)
	{
		SkillInfo* skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(skillId);
		if(!skillInfo)
		{
			return false;
		}

		return isCanUseSkill(skillInfo, targetCharacter);
	}

	//-----------------------------------------------------------------------
	Bool SSkillUseManager::isCanUseSkill(SkillInfo* skillInfo, SCharacter* targetCharacter)
	{
		if(!skillInfo)
		{
			return false;
		}

		if(skillInfo->skillType != SKT_PASSIVENESS)
		{
			InitiativeSkillBasicInfo* initiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)skillInfo->skillInfo;
			if(!initiativeSkillBasicInfo)
			{
				return false;
			}

			if(!GameJudge::getInstance().checkGameJudge((SCharacter*)mOwnerCharacter, initiativeSkillBasicInfo->characterJudgeId1))
			{
				return false;
			}

			if(targetCharacter)
			{
				if(!GameJudge::getInstance().checkGameJudge(targetCharacter, initiativeSkillBasicInfo->characterJudgeId2))
				{
					return false;
				}
			}
		}
		else
		{

		}

		return true;
	}

	//-----------------------------------------------------------------------
	void SSkillUseManager::destroySkillObject(SkillObject*& skillObject)
	{
		SSkillObject*& tempskillObject = (SSkillObject*&)skillObject;
		MG_POOL_DELETE(mSkillObjectPool, tempskillObject);
		skillObject = NULL;
	}

	//-----------------------------------------------------------------------
    SCharacter* SSkillUseManager::getSCharacter()
    {
        return dynamic_cast<SCharacter*>( SkillUseManager::getCharacter() );
    }
}