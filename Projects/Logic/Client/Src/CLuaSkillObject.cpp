
/******************************************************************************/
#include "stdafx.h"
#include "LuaSkillObject.h"
//#include "NEW_Client_LuaCharacterForSkill.h"
//#include "NEW_Server_LuaCharacterForSkill.h"
#include "CLuaCharacterForSkill.h"
//#include "CharacterSceneEntity.h"
#include "CharacterSceneObj.h"
#include "CSkillObject.h"
#include "CLuaSkillEffect.h"
#include "CSkillEffectSystem.h"
#include "CLuaSkillSystem.h"
#include "CLuaSkillObject.h"
#include "CSceneManager.h"
#include "SkillBaseInfo.h"
/******************************************************************************/

namespace MG
{
    //-----------------------------------------------------------------------

    Str CLuaSkillObject::LUA_TYPE_NAME = "CLuaSkillObject"; 

    //-----------------------------------------------------------------------

    const Str& CLuaSkillObject::getLuaTypeName() const 
    {
        return CLuaSkillObject::LUA_TYPE_NAME;
    }

    //-----------------------------------------------------------------------
    int CLuaSkillObject::getOwner(lua_State *L)
    {
        CSkillObject* skillObject  = LUA_RETRIEVE_OBJECT(CSkillObject,CLuaSkillObject,L); 
        if (NULL == skillObject) { DYNAMIC_ASSERT(0); return 0; }

		CCharacterSceneEntity* character = CSceneManager::getInstance().getCharacterSceneEntity(skillObject->getOwnerType(), skillObject->getOwnerID(), skillObject->getOwnerIndex());
		if(!character)
		{
			return 0;
		}
  
        CLuaCharacterForSkill::createUserData(L, character, CLuaCharacterForSkill::LUA_TYPE_NAME.c_str()); 

        return 1;
    }

    //-----------------------------------------------------------------------
    int CLuaSkillObject::addPointEffect(lua_State *L)
    {
        CSkillObject* skillObject  = LUA_RETRIEVE_OBJECT(CSkillObject,CLuaSkillObject,L); 
        if (NULL == skillObject) { DYNAMIC_ASSERT(0); return 0; }

            
		CSkillEffectSystem* system = CSceneManager::getInstance().getSkillEffectSystem();
        CPointSkillEffect* effect = system->addPointEffect( skillObject );
        LUA_RETURN_OBJECT( effect, CLuaPointSkillEffect, L )

        return 1;
    }

    //-----------------------------------------------------------------------
    int CLuaSkillObject::addEmitterSkillEffect(lua_State *L)
    {
        CSkillObject* skillObject  = LUA_RETRIEVE_OBJECT(CSkillObject,CLuaSkillObject,L); 
        if (NULL == skillObject) { DYNAMIC_ASSERT(0); return 0; }

        CSkillEffectSystem* system = CSceneManager::getInstance().getSkillEffectSystem();
        CEmitterSkillEffect* effect = system->addEmitterSkillEffect( skillObject );
        LUA_RETURN_OBJECT( effect, CLuaEmitterSkillEffect, L )

        return 1;
    }

	//-----------------------------------------------------------------------
	int CLuaSkillObject::getTargetPos(lua_State *L)
	{
		CSkillObject* skillObject  = LUA_RETRIEVE_OBJECT(CSkillObject,CLuaSkillObject,L); 
		if (NULL == skillObject) { DYNAMIC_ASSERT(0); return 0; }
		
		Vec3 pos = skillObject->getTargetPosition();
		CLuaSkillSystem::getInstance().getLuaManager()->createVector3Table(pos);

		return 1;
	}

	//-----------------------------------------------------------------------
	int CLuaSkillObject::addObjectSkillEffect(lua_State *L)
	{
		CSkillObject* skillObject  = LUA_RETRIEVE_OBJECT(CSkillObject,CLuaSkillObject,L); 
		if (NULL == skillObject) { DYNAMIC_ASSERT(0); return 0; }

		CSkillEffectSystem* system = CSceneManager::getInstance().getSkillEffectSystem();
		CObjectSkillEffect* effect = system->addObjectSkillEffect( skillObject );
		LUA_RETURN_OBJECT( effect, CLuaObjectSkillEffect, L )

		return 1;
	}

	//-----------------------------------------------------------------------
	int CLuaSkillObject::addInstantSkillEffect(lua_State *L)
	{
		CSkillObject* skillObject  = LUA_RETRIEVE_OBJECT(CSkillObject,CLuaSkillObject,L); 
		if (NULL == skillObject) { DYNAMIC_ASSERT(0); return 0; }

		CSkillEffectSystem* system = CSceneManager::getInstance().getSkillEffectSystem();
		CInstantSkillEffect* effect = system->addInstantSkillEffect( skillObject );
		LUA_RETURN_OBJECT( effect, CLuaInstantSkillEffect, L )

		return 1;
	}

	//-----------------------------------------------------------------------
	int CLuaSkillObject::addSprintSkillEffect(lua_State *L)
	{
		CSkillObject* skillObject  = LUA_RETRIEVE_OBJECT(CSkillObject,CLuaSkillObject,L); 
		if (NULL == skillObject) { DYNAMIC_ASSERT(0); return 0; }

		CSkillEffectSystem* system = CSceneManager::getInstance().getSkillEffectSystem();
		CSprintSkillEffect* effect = system->addSprintSkillEffect( skillObject );
		LUA_RETURN_OBJECT( effect, CLuaSprintSkillEffect, L )

			return 1;
	}

	//-----------------------------------------------------------------------
	int CLuaSkillObject::getTargetIndex(lua_State *L)
	{
		CSkillObject* skillObject  = LUA_RETRIEVE_OBJECT(CSkillObject,CLuaSkillObject,L); 
		if (NULL == skillObject) { DYNAMIC_ASSERT(0); return 0; }

		UInt index = skillObject->getTargetObjectIndex();

		lua_pushnumber(L, index);

		return 1;
	}

	//-----------------------------------------------------------------------
	int CLuaSkillObject::getTargetId(lua_State *L)
	{
		CSkillObject* skillObject  = LUA_RETRIEVE_OBJECT(CSkillObject,CLuaSkillObject,L); 
		if (NULL == skillObject) { DYNAMIC_ASSERT(0); return 0; }

		IdType id = skillObject->getTargetObjectID();

		lua_pushnumber(L, id);
		
		return 1;
	}

	//-----------------------------------------------------------------------
	int CLuaSkillObject::getTargetType(lua_State *L)
	{
		CSkillObject* skillObject  = LUA_RETRIEVE_OBJECT(CSkillObject,CLuaSkillObject,L); 
		if (NULL == skillObject) { DYNAMIC_ASSERT(0); return 0; }

		GAMEOBJ_TYPE type = skillObject->getTargetObjectType();

		lua_pushnumber(L, type);

		return 1;
	}

	//-----------------------------------------------------------------------
	int CLuaSkillObject::skillEnded(lua_State *L)
	{
		CSkillObject* skillObject  = LUA_RETRIEVE_OBJECT(CSkillObject,CLuaSkillObject,L); 
		if (NULL == skillObject) { DYNAMIC_ASSERT(0); return 0; }

		//skillObject->getSkillEffectSystem()->onSkillEnded(skillObject);
		skillObject->stopUse();

		return 0;
	}

	//-----------------------------------------------------------------------
	int CLuaSkillObject::getSkillId(lua_State *L)
	{
		CSkillObject* skillObject  = LUA_RETRIEVE_OBJECT(CSkillObject,CLuaSkillObject,L); 
		if (NULL == skillObject) { DYNAMIC_ASSERT(0); return 0; }

		IdType skillId = skillObject->getSkillInfo()->skillId;

		lua_pushnumber(L, skillId);

		return 1;
	}

}