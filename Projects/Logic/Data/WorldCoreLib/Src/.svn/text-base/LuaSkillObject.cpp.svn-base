
/******************************************************************************/
#include "stdafx.h"
#include "LuaSkillObject.h"
#include "NEW_Client_LuaCharacterForSkill.h"
#include "NEW_Server_LuaCharacterForSkill.h"
#include "CharacterSceneEntity.h"
#include "CharacterSceneObj.h"
#include "SkillObject.h"
#include "LuaSkillEffect.h"
#include "SkillEffectSystem.h"
#include "LuaSkillSystem.h"
/******************************************************************************/

namespace MG
{
    //-----------------------------------------------------------------------

    Str LuaSkillObject::LUA_TYPE_NAME = "LuaSkillObject"; 

    //-----------------------------------------------------------------------

    const Str& LuaSkillObject::getLuaTypeName() const 
    {
        return LuaSkillObject::LUA_TYPE_NAME;
    }

    //-----------------------------------------------------------------------
    int LuaSkillObject::getOwner(lua_State *L)
    {
        SkillObject* skillObject  = LUA_RETRIEVE_OBJECT(SkillObject,LuaSkillObject,L); 
        if (NULL == skillObject) { DYNAMIC_ASSERT(0); return 0; }

#ifdef _SERVER
        CharacterSceneObj* character = skillObject->getCharacterObj();
        NEW_SLuaCharacterForSkill::createUserData(L, character, NEW_SLuaCharacterForSkill::LUA_TYPE_NAME.c_str());
        
#else
        //CharacterSceneEntity* character = skillObject->getCharacterEntity();
        //NEW_CLuaCharacterForSkill::createUserData(L, character, NEW_CLuaCharacterForSkill::LUA_TYPE_NAME.c_str()); 
#endif

        return 1;
    }

    //-----------------------------------------------------------------------
    int LuaSkillObject::addPointEffect(lua_State *L)
    {
        SkillObject* skillObject  = LUA_RETRIEVE_OBJECT(SkillObject,LuaSkillObject,L); 
        if (NULL == skillObject) { DYNAMIC_ASSERT(0); return 0; }

            
        //SkillEffectSystem* system = skillObject->getSkillEffectSystem();
        //PointSkillEffect* effect = system->addPointEffect( skillObject );
        //LUA_RETURN_OBJECT( effect, LuaPointSkillEffect, L )

        return 1;
    }

    //-----------------------------------------------------------------------
    int LuaSkillObject::addEmitterSkillEffect(lua_State *L)
    {
        SkillObject* skillObject  = LUA_RETRIEVE_OBJECT(SkillObject,LuaSkillObject,L); 
        if (NULL == skillObject) { DYNAMIC_ASSERT(0); return 0; }

       // SkillEffectSystem* system = skillObject->getSkillEffectSystem();
        //EmitterSkillEffect* effect = system->addEmitterSkillEffect( skillObject );
        //LUA_RETURN_OBJECT( effect, LuaEmitterSkillEffect, L )

        return 1;
    }

	//-----------------------------------------------------------------------
	int LuaSkillObject::getTargetPos(lua_State *L)
	{
		SkillObject* skillObject  = LUA_RETRIEVE_OBJECT(SkillObject,LuaSkillObject,L); 
		if (NULL == skillObject) { DYNAMIC_ASSERT(0); return 0; }
		
		Vec3 pos = skillObject->getTargetPosition();
		LuaSkillSystem::getInstance().getLuaManager()->createVector3Table(pos);

		return 1;
	}

	//-----------------------------------------------------------------------
	int LuaSkillObject::addObjectSkillEffect(lua_State *L)
	{
		SkillObject* skillObject  = LUA_RETRIEVE_OBJECT(SkillObject,LuaSkillObject,L); 
		if (NULL == skillObject) { DYNAMIC_ASSERT(0); return 0; }

		//SkillEffectSystem* system = skillObject->getSkillEffectSystem();
		//ObjectSkillEffect* effect = system->addObjectSkillEffect( skillObject );
		//LUA_RETURN_OBJECT( effect, LuaObjectSkillEffect, L )

		return 1;
	}

	//-----------------------------------------------------------------------
	int LuaSkillObject::addInstantSkillEffect(lua_State *L)
	{
		SkillObject* skillObject  = LUA_RETRIEVE_OBJECT(SkillObject,LuaSkillObject,L); 
		if (NULL == skillObject) { DYNAMIC_ASSERT(0); return 0; }

		//SkillEffectSystem* system = skillObject->getSkillEffectSystem();
		//InstantSkillEffect* effect = system->addInstantSkillEffect( skillObject );
		//LUA_RETURN_OBJECT( effect, LuaInstantSkillEffect, L )

		return 1;
	}

	//-----------------------------------------------------------------------
	int LuaSkillObject::addSprintSkillEffect(lua_State *L)
	{
		SkillObject* skillObject  = LUA_RETRIEVE_OBJECT(SkillObject,LuaSkillObject,L); 
		if (NULL == skillObject) { DYNAMIC_ASSERT(0); return 0; }

		//SkillEffectSystem* system = skillObject->getSkillEffectSystem();
		//SprintSkillEffect* effect = system->addSprintSkillEffect( skillObject );
		//LUA_RETURN_OBJECT( effect, LuaSprintSkillEffect, L )

			return 1;
	}

	//-----------------------------------------------------------------------
	int LuaSkillObject::getTargetId(lua_State *L)
	{
		SkillObject* skillObject  = LUA_RETRIEVE_OBJECT(SkillObject,LuaSkillObject,L); 
		if (NULL == skillObject) { DYNAMIC_ASSERT(0); return 0; }

		IdType id = skillObject->getTargetObjectID();

		lua_pushnumber(L, id);
		
		return 1;
	}

	//-----------------------------------------------------------------------
	int LuaSkillObject::getTargetType(lua_State *L)
	{
		SkillObject* skillObject  = LUA_RETRIEVE_OBJECT(SkillObject,LuaSkillObject,L); 
		if (NULL == skillObject) { DYNAMIC_ASSERT(0); return 0; }

		GAMEOBJ_TYPE type = skillObject->getTargetObjectType();

		lua_pushnumber(L, type);

		return 1;
	}

	//-----------------------------------------------------------------------
	int LuaSkillObject::getSkillLevel(lua_State *L)
	{
		SkillObject* skillObject  = LUA_RETRIEVE_OBJECT(SkillObject,LuaSkillObject,L); 
		if (NULL == skillObject) { DYNAMIC_ASSERT(0); return 0; }

		Int level = skillObject->getSkillLevel();

		lua_pushnumber(L, level);

		return 1;
	}

	
	//-----------------------------------------------------------------------
	int LuaSkillObject::skillEnded(lua_State *L)
	{
		SkillObject* skillObject  = LUA_RETRIEVE_OBJECT(SkillObject,LuaSkillObject,L); 
		if (NULL == skillObject) { DYNAMIC_ASSERT(0); return 0; }

		//skillObject->getSkillEffectSystem()->onSkillEnded(skillObject);
		skillObject->stopUse();

		return 0;
	}

	//-----------------------------------------------------------------------
	int LuaSkillObject::getSkillId(lua_State *L)
	{
		SkillObject* skillObject  = LUA_RETRIEVE_OBJECT(SkillObject,LuaSkillObject,L); 
		if (NULL == skillObject) { DYNAMIC_ASSERT(0); return 0; }

		IdType skillId = skillObject->getBaseInfo()->id;

		lua_pushnumber(L, skillId);

		return 1;
	}

}