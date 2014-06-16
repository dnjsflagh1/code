
/******************************************************************************/
#include "stdafx.h"
#include "SLuaCharacterForSkill.h"
#include "SLuaSkillSystem.h"
//#include "Character.h"
//#include "RegionObject.h"
/******************************************************************************/

namespace MG
{
    //-----------------------------------------------------------------------

    Str SLuaCharacterForSkill::LUA_TYPE_NAME = "SLuaCharacterForSkill"; 

    //-----------------------------------------------------------------------

    const Str& SLuaCharacterForSkill::getLuaTypeName() const 
    {
        return SLuaCharacterForSkill::LUA_TYPE_NAME;
    }

    //-----------------------------------------------------------------------
    int SLuaCharacterForSkill::getPos(lua_State *L)
    {
        SCharacter* character    = LUA_RETRIEVE_OBJECT(SCharacter,SLuaCharacterForSkill,L); 
        if (NULL == character) { DYNAMIC_ASSERT(0); return 0; }

        Vec3 pos = character->getPos();
        SLuaSkillSystem::getInstance().getLuaManager()->createVector3Table(pos);

        return 1;
    }

    //-----------------------------------------------------------------------
    int SLuaCharacterForSkill::getDir(lua_State *L)
    {
        SCharacter* character    = LUA_RETRIEVE_OBJECT(SCharacter,SLuaCharacterForSkill,L); 
        if (NULL == character) { DYNAMIC_ASSERT(0); return 0; }

        Vec3 dir = character->getDir();
        SLuaSkillSystem::getInstance().getLuaManager()->createVector3Table(dir);

        return 1;
    }


	//-----------------------------------------------------------------------
	int SLuaCharacterForSkill::obtainDamage(lua_State *L)
	{

		Flt para[ATTR_PARA_NUM];

		SCharacter* character    = LUA_RETRIEVE_OBJECT(SCharacter,SLuaCharacterForSkill,L); 
		if (NULL == character) { DYNAMIC_ASSERT(0); return 0; }

		SCharacter* attackerCharacter    = LUA_INDEX_RETRIEVE_OBJECT(SCharacter,SLuaCharacterForSkill,L,2); 
		if (NULL == attackerCharacter) { DYNAMIC_ASSERT(0); return 0; }

		AttackType damagetype = (AttackType)SLuaSkillSystem::getInstance().getLuaManager()->getNumber(3);
		DamageType effectType = (DamageType)SLuaSkillSystem::getInstance().getLuaManager()->getNumber(4);
		UInt paraID = SLuaSkillSystem::getInstance().getLuaManager()->getNumber(5);

		Int valueIndex	= 0;
		if (!lua_istable(L, 6))
		{
			MG_LOG( out_error, ("%s error: para not a valid table \n"), __MG_FUNC__ );
		}

		lua_pushnil( L );  
	
		while (lua_next( L, 6) != 0) {
			para[valueIndex] = luaL_checkinteger( L, -1 );
			valueIndex++;
			lua_pop( L, 1 );
		}

		//character->obtainDamage((Character*)attackerCharacter, damagetype, effectType, (ATTACK_POS)1, paraID, para);

		return 0;
	}

	//-----------------------------------------------------------------------
	//int SLuaCharacterForSkill::getElementNum(lua_State *L)
	//{

	//	CharacterSceneObj* character    = LUA_RETRIEVE_OBJECT(CharacterSceneObj, SLuaCharacterForSkill,L); 
	//	if (NULL == character) { DYNAMIC_ASSERT(0); return 0; }

	//	UInt num = character->getElementNum();

	//	lua_pushnumber(L, num);


	//	return 1;
	//}

	//-----------------------------------------------------------------------






	//-----------------------------------------------------------------------
	int SLuaCharacterForSkill::summonBuilding(lua_State *L)
	{

		//Character* character    = LUA_RETRIEVE_OBJECT(Character,LuaCharacterForSkill,L); 
		//if (NULL == character) { DYNAMIC_ASSERT(0); return 0; }

		//UInt templateId = LuaSkillSystem::getInstance().getLuaManager()->getNumber(2);
		//UInt skillId  = LuaSkillSystem::getInstance().getLuaManager()->getNumber(3);
		//Vec3 pos = LuaSkillSystem::getInstance().getLuaManager()->getVector3FromTable(4);

		//character->summonBuilding(templateId, skillId, pos);

		return 1;
	}

}
