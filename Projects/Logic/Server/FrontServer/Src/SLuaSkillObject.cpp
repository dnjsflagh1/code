
/******************************************************************************/
#include "stdafx.h"
#include "SLuaSkillObject.h"
#include "CharacterSceneObj.h"
#include "SSkillObject.h"
#include "SLuaSkillSystem.h"
#include "SWorldManager.h"
#include "SLuaCharacterForSkill.h"
#include "SkillBaseInfo.h"
/******************************************************************************/

namespace MG
{
    //-----------------------------------------------------------------------

    Str SLuaSkillObject::LUA_TYPE_NAME = "SLuaSkillObject"; 

    //-----------------------------------------------------------------------

    const Str& SLuaSkillObject::getLuaTypeName() const 
    {
        return SLuaSkillObject::LUA_TYPE_NAME;
    }

    //-----------------------------------------------------------------------
    int SLuaSkillObject::getOwner(lua_State *L)
    {
#if 0 //king
        SkillObject* skillObject  = LUA_RETRIEVE_OBJECT(SkillObject,SLuaSkillObject,L); 
        if (NULL == skillObject) { DYNAMIC_ASSERT(0); return 0; }
		SCharacter* character = SWorldManager::getInstance().getCharacter(skillObject->getOwnerType(), skillObject->getOwnerID(), skillObject->getOwnerIndex());
		if(!character)
		{
			return 0;
		}
		
		SLuaCharacterForSkill::createUserData(L, character, SLuaCharacterForSkill::LUA_TYPE_NAME.c_str());
#endif
        return 1;
    }

	//-----------------------------------------------------------------------
	int SLuaSkillObject::getTargetPos(lua_State *L)
	{
		SkillObject* skillObject  = LUA_RETRIEVE_OBJECT(SkillObject,SLuaSkillObject,L); 
		if (NULL == skillObject) { DYNAMIC_ASSERT(0); return 0; }
		
		Vec3 pos = skillObject->getTargetPosition();
		SLuaSkillSystem::getInstance().getLuaManager()->createVector3Table(pos);

		return 1;
	}

	//-----------------------------------------------------------------------
	int SLuaSkillObject::getTargetId(lua_State *L)
	{
		SkillObject* skillObject  = LUA_RETRIEVE_OBJECT(SkillObject,SLuaSkillObject,L); 
		if (NULL == skillObject) { DYNAMIC_ASSERT(0); return 0; }

		IdType id = skillObject->getTargetObjectID();

		lua_pushnumber(L, id);
		
		return 1;
	}

	//-----------------------------------------------------------------------
	int SLuaSkillObject::getTargetType(lua_State *L)
	{
		SkillObject* skillObject  = LUA_RETRIEVE_OBJECT(SkillObject,SLuaSkillObject,L); 
		if (NULL == skillObject) { DYNAMIC_ASSERT(0); return 0; }

		GAMEOBJ_TYPE type = skillObject->getTargetObjectType();

		lua_pushnumber(L, type);

		return 1;
	}

	
	//-----------------------------------------------------------------------
	int SLuaSkillObject::skillEnded(lua_State *L)
	{
		SkillObject* skillObject  = LUA_RETRIEVE_OBJECT(SkillObject,SLuaSkillObject,L); 
		if (NULL == skillObject) { DYNAMIC_ASSERT(0); return 0; }

		//skillObject->getSkillEffectSystem()->onSkillEnded(skillObject);
		skillObject->stopUse();

		return 0;
	}

	//-----------------------------------------------------------------------
	int SLuaSkillObject::getSkillId(lua_State *L)
	{
		SkillObject* skillObject  = LUA_RETRIEVE_OBJECT(SkillObject,SLuaSkillObject,L); 
		if (NULL == skillObject) { DYNAMIC_ASSERT(0); return 0; }

		IdType skillId = skillObject->getSkillInfo()->skillId;

		lua_pushnumber(L, skillId);

		return 1;
	}

}