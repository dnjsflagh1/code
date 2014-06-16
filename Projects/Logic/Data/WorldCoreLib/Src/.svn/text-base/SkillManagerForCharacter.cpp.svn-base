
/******************************************************************************/
#include "stdafx.h"
#include "SkillManagerForCharacter.h"
#include "SkillObject.h"
#include "LuaSkillSystem.h"
#include "GameObject.h"
/******************************************************************************/

namespace MG
{
    //-----------------------------------------------------------------------
	SkillManagerForCharacter::SkillManagerForCharacter( GameObject* character )
        : mOwnerCharacter(character)
    {

    }

    //-----------------------------------------------------------------------
    SkillManagerForCharacter::~SkillManagerForCharacter()
    {
		destroyAllSkill();
    }

    //-----------------------------------------------------------------------
    void SkillManagerForCharacter::update( Flt delta )
    {
        updateAllSkill( delta );
    }

    //-----------------------------------------------------------------------
    Bool SkillManagerForCharacter::isCanLearnSkill(IdType id)
    {
        return true;
    }

    //-----------------------------------------------------------------------
    Bool SkillManagerForCharacter::isCanUseSkill(IdType id)
    {
        return true;
    }

    //-----------------------------------------------------------------------
    SkillObject* SkillManagerForCharacter::addOrGetSkill(IdType id)
    {
		//FUNDETECTION(__MG_FUNC__);
		SkillObjListIt it = mSkillObjList.find(id);
		if(it != mSkillObjList.end())
		{
			return it->second;
		}

		SkillObject* skillObject = createSkillObject(id);

		if(skillObject)
		{
			mSkillObjList[id] = skillObject;
			return skillObject;
		}

        return NULL;
    }

    //-----------------------------------------------------------------------
	SkillObject* SkillManagerForCharacter::getSkill(IdType id)
    {
		SkillObjListIt it = mSkillObjList.find(id);
		if(it != mSkillObjList.end() && it->second)
		{
			return it->second;
		}

        return NULL;
    }

	//-----------------------------------------------------------------------
	SkillObject* SkillManagerForCharacter::getSkill(UInt index)
	{
		UInt skillIndex = 0;

		for(SkillObjListIt it = mSkillObjList.begin(); it != mSkillObjList.end(); ++it)
		{
			if(skillIndex == index)
			{
				return it->second;
			}

			skillIndex++;
		}

		return NULL;
	}

	//-----------------------------------------------------------------------
	UInt SkillManagerForCharacter::getSkillNum()
	{
		return mSkillObjList.size();
	}

    //-----------------------------------------------------------------------
    GameObject* SkillManagerForCharacter::getCharacter()
    {
        return mOwnerCharacter;
    }

    //-----------------------------------------------------------------------
    void SkillManagerForCharacter::destroyAllSkill()
    {
		for(SkillObjListIt it = mSkillObjList.begin(); it != mSkillObjList.end(); ++it)
		{
			SkillObject* skillObject = it->second;
			if(skillObject)
			{
				delete skillObject;
				skillObject = NULL;
			}
		}
    }

    //-----------------------------------------------------------------------
    void SkillManagerForCharacter::updateAllSkill( Flt delta )
    {
        for(SkillObjListIt it = mSkillObjList.begin(); it != mSkillObjList.end(); ++it)
        {
            it->second->update( delta );
        }
    }

	
}