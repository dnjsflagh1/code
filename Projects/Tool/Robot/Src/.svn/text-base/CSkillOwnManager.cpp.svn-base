/******************************************************************************/
#include "stdafx.h"
#include "CSkillOwnManager.h"
#include "CCharacter.h"
#include "SkillInfoList.h"
//#include "CSkillObject.h"
/******************************************************************************/

namespace MG
{

	//-----------------------------------------------------------------------
	CSkillOwnManager::CSkillOwnManager( CCharacter* character )
		: SkillOwnManager(character)
		,mDefaultSkill(0)
	{

	}

	//-----------------------------------------------------------------------
	CSkillOwnManager::~CSkillOwnManager()
	{

	}

	//-----------------------------------------------------------------------
	void CSkillOwnManager::addOwnerSkill( IdType skillId )
	{
		SkillInfo* skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(skillId);
		if(mDefaultSkill == 0 && skillInfo && (skillInfo->skillType == SKT_SHORTRANGEGENERAL || skillInfo->skillType == SKT_LONGRANGEGENERAL))
		{
			mDefaultSkill = skillId;
		}

		SkillOwnManager::addOwnerSkill(skillId);
	}

	//-----------------------------------------------------------------------
	UInt CSkillOwnManager::getDefaultSkill()
	{
		return mDefaultSkill;
	}
}