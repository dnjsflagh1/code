/******************************************************************************/
#include "stdafx.h"
#include "CSkillUseManager.h"
#include "CLuaSkillSystem.h"
#include "CCharacterSceneEntity.h"
#include "SkillInfoList.h"
#include "ShortRangeGeneralAttackSkillTemplate.h"
#include "LongRangeGeneralAttackSkillTemplate.h"
#include "SingleTargetSkillTemplate.h"
#include "CCDManager.h"
#include "CGoUpAndDownSkill.h"
/******************************************************************************/

namespace MG
{

	//-----------------------------------------------------------------------
    CSkillUseManager::CSkillUseManager( CCharacterSceneEntity* character )
        :SkillUseManager( character )
    {
		GAMEOBJ_TYPE gameObjectType = mOwnerCharacter->getType();

		switch(gameObjectType)
		{
		case GOT_PLAYERCHARACTER:
			mCDMasterType = CD_MASTER_TYPE_CHARACTER;
			break;

		case GOT_SOLDIER:
			mCDMasterType = CD_MASTER_TYPE_TROOP;
			break;

		case GOT_BUILDING:
			mCDMasterType = CD_MASTER_TYPE_BUILD;
			break;
		default:
			mCDMasterType = CD_MASTER_TYPE_NULL;
			break;
		}
    }

    //-----------------------------------------------------------------------
    CSkillUseManager::~CSkillUseManager()
    {
        
    }

    //-----------------------------------------------------------------------
    CSkillObject* CSkillUseManager::createSkillObject( IdType skillId )
    {
		SkillInfo* skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(skillId);
		if(!skillInfo)
		{
			return NULL;
		}

		CCharacterSceneEntity* character = getCharacterEntity();

		if(skillInfo && character)
		{
			if(skillInfo->skillType == SKT_GOUPANDDOWN)
			{
				mCurrUseSkill = MG_POOL_NEW(mSkillObjectPool, CGoUpAndDownSkill, (character));
				((CSkillObject*)mCurrUseSkill)->setIsExecScript(false);
			}
			else
			{
				mCurrUseSkill = MG_POOL_NEW(mSkillObjectPool, CSkillObject, (character));
			}
			
			mCurrUseSkill->setSkillInfo(skillInfo);
			return (CSkillObject*)mCurrUseSkill;
		}
		
		return NULL;
    }

	//-----------------------------------------------------------------------
	void CSkillUseManager::destroySkillObject( SkillObject*& skillObject )
	{
		if ( skillObject )
		{
			CSkillObject*& tempSkillObject = (CSkillObject*&)skillObject;
			MG_POOL_DELETE(mSkillObjectPool, tempSkillObject);
			skillObject = NULL;
		}
	}

    //-----------------------------------------------------------------------
    CCharacterSceneEntity* CSkillUseManager::getCharacterEntity()
    {
        return dynamic_cast<CCharacterSceneEntity*>( SkillUseManager::getCharacter() );
    }

	//-----------------------------------------------------------------------
	SkillObject* CSkillUseManager::prepareUseSkill( IdType skillId )
	{
		//FUNDETECTION(__MG_FUNC__);
		SkillObject* skillObject = SkillUseManager::prepareUseSkill(skillId);
		if(!((CSkillObject*)skillObject)->getIsEndBehind())
		{
			return NULL;
		}

		return skillObject;
	}

	//-----------------------------------------------------------------------
	Bool CSkillUseManager::isCanUseSkill( IdType skillId, CCharacter* targetCharacter )
	{
		return true;
	}

	//-----------------------------------------------------------------------
	Bool CSkillUseManager::isCanUseSkill( SkillInfo* skillInfo, CCharacter* targetCharacter )
	{
	/*	if(!skillInfo)
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

			if(!GameJudge::getInstance().checkGameJudge((CCharacter*)mOwnerCharacter, initiativeSkillBasicInfo->characterJudgeId1))
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

		}*/

		return true;
	}

	//-----------------------------------------------------------------------
	Bool CSkillUseManager::checkCD( IdType skillId, AddAndCheckSkillCDType addSkillCDType )
	{
		SkillInfo* skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(skillId);
		if(!skillInfo)
		{
			return true;
		}

		return checkCD(skillInfo, addSkillCDType);
	}

	//-----------------------------------------------------------------------
	void CSkillUseManager::addCD( IdType skillId, AddAndCheckSkillCDType addSkillCDType )
	{
		SkillInfo* skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(skillId);
		if(!skillInfo)
		{
			return;
		}

		addCD(skillInfo, addSkillCDType);
	}

	//-----------------------------------------------------------------------
	Bool CSkillUseManager::checkCD( SkillInfo* skillInfo, AddAndCheckSkillCDType addSkillCDType )
	{
		if(!skillInfo)
		{
			return true;
		}

		if(skillInfo->skillShowType == SKILL_SHOW_TYPE_TWO)
		{
			return true;
		}

		InitiativeSkillBasicInfo* initiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)skillInfo->skillInfo;
		if(!initiativeSkillBasicInfo)
		{
			return true;
		}

		IdType owmerId = mOwnerCharacter->getID();

		if(addSkillCDType == AACSCT_PUBLIC || addSkillCDType == AACSCT_ALL)
		{
			if(CCDManager::getInstance().checkCD(mCDMasterType, owmerId, initiativeSkillBasicInfo->publicTimepieceId))
			{
				return true;
			}
		}

		if(addSkillCDType == AACSCT_OWNER || addSkillCDType == AACSCT_ALL)
		{
			if(CCDManager::getInstance().checkCD(mCDMasterType, owmerId, initiativeSkillBasicInfo->ownerTimepieceId))
			{
				return true;
			}
		}

		return false;
	}

	//-----------------------------------------------------------------------
	void CSkillUseManager::addCD( SkillInfo* skillInfo, AddAndCheckSkillCDType addSkillCDType )
	{
		if(!skillInfo)
		{
			return;
		}

		if(skillInfo->skillShowType == SKILL_SHOW_TYPE_TWO)
		{
			return;
		}

		InitiativeSkillBasicInfo* initiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)skillInfo->skillInfo;
		if(!initiativeSkillBasicInfo)
		{
			return;
		}

		IdType owmerId = mOwnerCharacter->getID();

		if(addSkillCDType == AACSCT_PUBLIC || addSkillCDType == AACSCT_ALL)
		{
			CCDManager::getInstance().addCD(
				mCDMasterType, 
				owmerId, 
				initiativeSkillBasicInfo->publicTimepieceId, 
				initiativeSkillBasicInfo->publicTimepieceDelay, 
				initiativeSkillBasicInfo->publicTimepieceDelay
				);
		}

		if(addSkillCDType == AACSCT_OWNER || addSkillCDType == AACSCT_ALL)
		{
			CCDManager::getInstance().addCD(
				mCDMasterType, 
				owmerId, 
				initiativeSkillBasicInfo->ownerTimepieceId, 
				initiativeSkillBasicInfo->ownerTimepieceDelay, 
				initiativeSkillBasicInfo->ownerTimepieceDelay
				);
		}
	}

}