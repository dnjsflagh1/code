
/******************************************************************************/
#include "stdafx.h"
#include "SkillUseManager.h"
#include "SkillObject.h"
#include "LuaSkillSystem.h"
#include "GameObject.h"
#include "SkillBaseInfo.h"
/******************************************************************************/

namespace MG
{
    //-----------------------------------------------------------------------
	SkillUseManager::SkillUseManager( GameObject* character )
        : mOwnerCharacter(character)
		, mCurrUseSkill(NULL)
		, mLastUseSkillId(0)
    {

    }

    //-----------------------------------------------------------------------
    SkillUseManager::~SkillUseManager()
    {

    }

    //-----------------------------------------------------------------------
    void SkillUseManager::update( Flt delta )
    {
		if(mCurrUseSkill)
		{
			mCurrUseSkill->update(delta);
		}
    }

    //-----------------------------------------------------------------------
    SkillObject* SkillUseManager::prepareUseSkill( IdType skillId )
    {
		//FUNDETECTION(__MG_FUNC__);
		if(skillId != mLastUseSkillId)
		{
			destroySkillObject(mCurrUseSkill);
			mCurrUseSkill = createSkillObject(skillId);
			mLastUseSkillId = mCurrUseSkill->getSkillInfo()->skillId;
		}
		else if(mLastUseSkillId != 0 && mCurrUseSkill)
		{
			if(!mCurrUseSkill->isFinished()) 
			{
				mCurrUseSkill->stopUse();
			}
		}

        return mCurrUseSkill;
    }

    //-----------------------------------------------------------------------
	SkillObject* SkillUseManager::getPreparedUseSkill()
    {
        return mCurrUseSkill;
    }


    //-----------------------------------------------------------------------
    GameObject* SkillUseManager::getCharacter()
    {
        return mOwnerCharacter;
    }

}