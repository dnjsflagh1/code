#include "stdafx.h"
#include "SkillOwnManager.h"
#include "SkillObject.h"

namespace MG
{
	//--------------------------------------------------------------------------
	SkillOwnManager::SkillOwnManager( GameObject* owner ) : mOwner(owner)
	{

	}

	//--------------------------------------------------------------------------
	SkillOwnManager::~SkillOwnManager()
	{

	}

	//--------------------------------------------------------------------------
	void SkillOwnManager::addOwnerSkill( IdType skillId )
	{
		if(isOwnSkill(skillId))
		{
			return;
		}

		mSkillList.push_back(skillId);
	}

	//--------------------------------------------------------------------------
	Bool SkillOwnManager::isLearnSkill( IdType skillId )
	{
		if(!isOwnSkill(skillId))
		{
			return true;
		}

		return false;
	}

	//--------------------------------------------------------------------------
	Bool SkillOwnManager::isOwnSkill( IdType skillId )
	{
		for(UInt i = 0; i < mSkillList.size(); ++i)
		{
			if(mSkillList[i] == skillId)
			{
				return true;
			}
		}

		return false;
	}

	//--------------------------------------------------------------------------
	UInt SkillOwnManager::getOwnSkillNum()
	{
		return mSkillList.size();
	}

	//--------------------------------------------------------------------------
	IdType SkillOwnManager::getOwnerSkillByIndex( UInt index )
	{
		if(index >= mSkillList.size())
		{
			return 0;
		}

		return mSkillList[index];
	}
	
	//--------------------------------------------------------------------------
	Bool SkillOwnManager::learnSkill( IdType skillId )
	{
		if(isLearnSkill(skillId))
		{
			return false;
		}

		addOwnerSkill(skillId);
		return true;
	}


}