
/******************************************************************************/
#include "stdafx.h"
#include "CLuaCharacterForSkill.h"
#include "CLuaSkillSystem.h"
//#include "CCharacterSceneEntity.h"
//#include "Character.h"
//#include "RegionObject.h"
/******************************************************************************/

namespace MG
{
    //-----------------------------------------------------------------------

    Str CLuaCharacterForSkill::LUA_TYPE_NAME = "CLuaCharacterForSkill"; 

    //-----------------------------------------------------------------------

    const Str& CLuaCharacterForSkill::getLuaTypeName() const 
    {
        return CLuaCharacterForSkill::LUA_TYPE_NAME;
    }

    //-----------------------------------------------------------------------
    int CLuaCharacterForSkill::getPos(lua_State *L)
    {

        CCharacterSceneEntity* character    = LUA_RETRIEVE_OBJECT(CCharacterSceneEntity,CLuaCharacterForSkill,L); 
        if (NULL == character) { DYNAMIC_ASSERT(0); return 0; }

        Vec3 pos;
        character->getEntity()->getSceneNode()->getPosition( pos );
        CLuaSkillSystem::getInstance().getLuaManager()->createVector3Table(pos);

        return 1;
    }

    //-----------------------------------------------------------------------
    int CLuaCharacterForSkill::getDir(lua_State *L)
    {

        CCharacterSceneEntity* character    = LUA_RETRIEVE_OBJECT(CCharacterSceneEntity,CLuaCharacterForSkill,L);
        if (NULL == character) { DYNAMIC_ASSERT(0); return 0; }

        Vec3 dir;
        character->getEntity()->getSceneNode()->getDirection( dir );

        CLuaSkillSystem::getInstance().getLuaManager()->createVector3Table(dir);

        return 1;
    }

    //-----------------------------------------------------------------------
    int CLuaCharacterForSkill::getBonePos(lua_State *L)
    {

        CCharacterSceneEntity* character    = LUA_RETRIEVE_OBJECT(CCharacterSceneEntity,CLuaCharacterForSkill,L);
        if (NULL == character) { DYNAMIC_ASSERT(0); return 0; }

        Str boneName = "Bip01 R Hand";
        Vec3 pos = character->getEntityBonePos( boneName );

        CLuaSkillSystem::getInstance().getLuaManager()->createVector3Table(pos);

        return 1;
    }

    //-----------------------------------------------------------------------
    int CLuaCharacterForSkill::playAnimation(lua_State *L)
    {
		//FUNDETECTION(__MG_FUNC__);
        CCharacterSceneEntity* character    = LUA_RETRIEVE_OBJECT(CCharacterSceneEntity,CLuaCharacterForSkill,L);
        if (NULL == character) { DYNAMIC_ASSERT(0); return 0; }

        Str name    = CLuaSkillSystem::getInstance().getLuaManager()->getString(2);
        Bool isLoop = CLuaSkillSystem::getInstance().getLuaManager()->getBoolean(3);

		character->playAnimation( name, false, isLoop );

        return 0;
    }

	//-----------------------------------------------------------------------
	int CLuaCharacterForSkill::stopAnimation(lua_State *L)
	{
        CCharacterSceneEntity* character    = LUA_RETRIEVE_OBJECT(CCharacterSceneEntity,CLuaCharacterForSkill,L);
        if (NULL == character) { DYNAMIC_ASSERT(0); return 0; }

		Str name    = CLuaSkillSystem::getInstance().getLuaManager()->getString(2);
		character->stopAnimation( name );

		return 0;
	}

    //-----------------------------------------------------------------------
    int CLuaCharacterForSkill::stopAll(lua_State *L)
    {
        CCharacterSceneEntity* character    = LUA_RETRIEVE_OBJECT(CCharacterSceneEntity,CLuaCharacterForSkill,L); 
        if (NULL == character) { DYNAMIC_ASSERT(0); return 0; }

        character->stopAllAnimation();

        return 0;
    }

	//-----------------------------------------------------------------------
	int CLuaCharacterForSkill::obtainDamage(lua_State *L)
	{
		//Flt para[ATTR_PARA_NUM];

		//CharacterSceneEntity* character    = LUA_RETRIEVE_OBJECT(CharacterSceneEntity,CLuaCharacterForSkill,L);
		//if (NULL == character) { DYNAMIC_ASSERT(0); return 0; }

		//CharacterSceneEntity* attackerCharacter    = LUA_RETRIEVE_OBJECT(CharacterSceneEntity,CLuaCharacterForSkill,L,2);
		//if (NULL == attackerCharacter) { DYNAMIC_ASSERT(0); return 0; }

		//AttackType damagetype = (AttackType)LuaSkillSystem::getInstance().getLuaManager()->getNumber(3);
		//DamageType effectType = (DamageType)LuaSkillSystem::getInstance().getLuaManager()->getNumber(4);
		//UInt paraID = LuaSkillSystem::getInstance().getLuaManager()->getNumber(5);

		//Int valueIndex	= 0;
		//if (!lua_istable(L, 6))
		//{
		//	MG_LOG( out_error, ("%s error: para not a valid table \n"), __MG_FUNC__ );
		//}

		//lua_pushnil( L );  
	
		//while (lua_next( L, 6) != 0) {
		//	para[valueIndex] = luaL_checkinteger( L, -1 );
		//	valueIndex++;
		//	lua_pop( L, 1 );
		//}

		//CharacterSceneEntity->obtainDamage((CharacterSceneEntity*)attackerCharacter, damagetype, effectType, (ATTACK_POS)1, paraID, para);

		return 0;
	}

	//-----------------------------------------------------------------------
	int CLuaCharacterForSkill::getElementNum(lua_State *L)
	{
		CCharacterSceneEntity* character    = LUA_RETRIEVE_OBJECT(CCharacterSceneEntity,CLuaCharacterForSkill,L); 
		if (NULL == character) { DYNAMIC_ASSERT(0); return 0; }

		//UInt num = character->getElementNum();

		//lua_pushnumber(L, num);

		return 1;
	}

	//-----------------------------------------------------------------------
	int CLuaCharacterForSkill::getElementPos(lua_State *L)
	{
		CCharacterSceneEntity* character    = LUA_RETRIEVE_OBJECT(CCharacterSceneEntity,CLuaCharacterForSkill,L);
		if (NULL == character) { DYNAMIC_ASSERT(0); return 0; }

		//UInt index = CLuaSkillSystem::getInstance().getLuaManager()->getNumber(2);
		//Vec3 pos  = character->getElementPos(index);
		//CLuaSkillSystem::getInstance().getLuaManager()->createVector3Table(pos);

		return 1;
	}

	//-----------------------------------------------------------------------
	int CLuaCharacterForSkill::getElementDir(lua_State *L)
	{
		CCharacterSceneEntity* character    = LUA_RETRIEVE_OBJECT(CCharacterSceneEntity,CLuaCharacterForSkill,L);
		if (NULL == character) { DYNAMIC_ASSERT(0); return 0; }

		//UInt index = CLuaSkillSystem::getInstance().getLuaManager()->getNumber(2);
		//Vec3 dir  = character->getElementDir(index);
		//CLuaSkillSystem::getInstance().getLuaManager()->createVector3Table(dir);

		return 1;
	}

	//-----------------------------------------------------------------------
	int CLuaCharacterForSkill::setIsCtrl(lua_State *L)
	{
		CCharacterSceneEntity* character    = LUA_RETRIEVE_OBJECT(CCharacterSceneEntity,CLuaCharacterForSkill,L);
		if (NULL == character) { DYNAMIC_ASSERT(0); return 0; }

		//Bool isCtrl = CLuaSkillSystem::getInstance().getLuaManager()->getBoolean(2);
		//character->setIsCtrl(isCtrl);

		return 0;
	}

	//-----------------------------------------------------------------------
	int CLuaCharacterForSkill::addEffect(lua_State *L)
	{

		//FUNDETECTION(__MG_FUNC__);
		CCharacterSceneEntity* character    = LUA_RETRIEVE_OBJECT(CCharacterSceneEntity,CLuaCharacterForSkill,L);
		if (NULL == character) { DYNAMIC_ASSERT(0); return 0; }

		UINT effectId = CLuaSkillSystem::getInstance().getLuaManager()->getNumber(2);
		Bool isAutoDestroy = CLuaSkillSystem::getInstance().getLuaManager()->getBoolean(3);
		//Vec3 pos =  CLuaSkillSystem::getInstance().getLuaManager()->getVector3FromTable(3);
		character->addEffect(effectId, isAutoDestroy);
	}

	//-----------------------------------------------------------------------
	int CLuaCharacterForSkill::endEffect(lua_State *L)
	{

		CCharacterSceneEntity* character    = LUA_RETRIEVE_OBJECT(CCharacterSceneEntity,CLuaCharacterForSkill,L);
		if (NULL == character) { DYNAMIC_ASSERT(0); return 0; }

		UINT effectId = CLuaSkillSystem::getInstance().getLuaManager()->getNumber(2);

		character->endEffect(effectId);
	}

	//-----------------------------------------------------------------------
	int CLuaCharacterForSkill::summonBuilding(lua_State *L)
	{
		return 0;


		//Character* character    = LUA_RETRIEVE_OBJECT(Character,LuaCharacterForSkill,L); 
		//if (NULL == character) { DYNAMIC_ASSERT(0); return 0; }

		//UInt templateId = LuaSkillSystem::getInstance().getLuaManager()->getNumber(2);
		//UInt skillId  = LuaSkillSystem::getInstance().getLuaManager()->getNumber(3);
		//Vec3 pos = LuaSkillSystem::getInstance().getLuaManager()->getVector3FromTable(4);

		//character->summonBuilding(templateId, skillId, pos);

	}

}
