
/******************************************************************************/
#include "stdafx.h"
#include "SSkillObject.h"
#include "SLuaSkillObject.h"
#include "SLuaSkillSystem.h"
#include "SLuaCharacterForSkill.h"
#include "SkillBaseInfo.h"
//#include "Character.h"
//#include "GameObject.h"
/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------
    SLuaSkillSystem::SLuaSkillSystem()
    {
        
    }

    //-----------------------------------------------------------------------
    SLuaSkillSystem::~SLuaSkillSystem()
    {
  
    }

    //-----------------------------------------------------------------------
    void SLuaSkillSystem::registerLua()
    {
        lua_State* L = mLuaMgr->getMainLuaState();

        #define REGISTER_CLUABINDER(binderClass, luastate) binderClass binderClass##Object; binderClass##Object.LuaRegister(luastate);

                REGISTER_CLUABINDER(SLuaSkillObject, L);
                REGISTER_CLUABINDER(SLuaCharacterForSkill, L);
   
        #undef REGISTER_CLUABINDER
    }

	//-----------------------------------------------------------------------
    void SLuaSkillSystem::execServerStartInjectScript(SkillObject* skillObject)
    {
        Bool result = false;
        mLuaMgr->startAssertStackBalance();
        {
            lua_State* L =  mLuaMgr->getMainLuaState();
            lua_getglobal( L, "Lua_ExecServerStartInjectScript" );

            SLuaSkillObject::createUserData(L, skillObject, SLuaSkillObject::LUA_TYPE_NAME.c_str());
            lua_pushinteger(L, (Int)skillObject->getSkillInfo()->skillId);

            if ( mLuaMgr->luaPcall( 2, 1 ) )
                result = (lua_toboolean(L,-1) == 1 ? true : false);
            else
                result = false;

            lua_pop(L, 1);
        }
        mLuaMgr->endAssertStackBalance();
    }

    //-----------------------------------------------------------------------
    void SLuaSkillSystem::execServerUpdateInjectScript(SkillObject* skillObject, Flt time)
    {
        Bool result = false;
        mLuaMgr->startAssertStackBalance();
        {
            lua_State* L =  mLuaMgr->getMainLuaState();
            lua_getglobal( L, "Lua_ExecServerUpdateInjectScript" );

            SLuaSkillObject::createUserData(L, skillObject, SLuaSkillObject::LUA_TYPE_NAME.c_str());
            lua_pushinteger(L, (Int)skillObject->getSkillInfo()->skillId);
            lua_pushinteger(L, (Int)(time*1000) );

            if ( mLuaMgr->luaPcall( 3, 1 ) )
                result = (lua_toboolean(L,-1) == 1 ? true : false);
            else
                result = false;

            lua_pop(L, 1);
        }
        mLuaMgr->endAssertStackBalance();
    }

	//-----------------------------------------------------------------------
	void SLuaSkillSystem::execServerEndInjectScript(SkillObject* skillObject)
	{
		Bool result = false;
		mLuaMgr->startAssertStackBalance();
		{
			lua_State* L =  mLuaMgr->getMainLuaState();
			lua_getglobal( L, "Lua_ExecServerEndInjectScript" );

			SLuaSkillObject::createUserData(L, skillObject, SLuaSkillObject::LUA_TYPE_NAME.c_str());
			lua_pushinteger(L, (Int)skillObject->getSkillInfo()->skillId);

			if ( mLuaMgr->luaPcall( 2, 1 ) )
				result = (lua_toboolean(L,-1) == 1 ? true : false);
			else
				result = false;

			lua_pop(L, 1);
		}
		mLuaMgr->endAssertStackBalance();
	}

    //-----------------------------------------------------------------------
 //   void LuaSkillSystem::execServerCollisionAffectScript( Character* Injecter, Character* affecter, UInt affecterTotal, IdType skillID )
 //   {

 //       Bool result = false;
 //       mLuaMgr->startAssertStackBalance();
 //       {
 //           lua_State* L =  mLuaMgr->getMainLuaState();
 //           lua_getglobal( L, "Lua_ExecServerCollisionAffectScript" );

	//		LuaCharacterForSkill::createUserData(L, Injecter, LuaCharacterForSkill::LUA_TYPE_NAME.c_str());
	//		LuaCharacterForSkill::createUserData(L, affecter, LuaCharacterForSkill::LUA_TYPE_NAME.c_str());
 //           lua_pushinteger(L, (Int)affecterTotal);
 //           lua_pushinteger(L, (Int)skillID);

 //           if ( mLuaMgr->luaPcall( 4, 1 ) )
 //               result = (lua_toboolean(L,-1) == 1 ? true : false);
 //           else
 //               result = false;

 //           lua_pop(L, 1);
 //       }
 //       mLuaMgr->endAssertStackBalance();
 //   }

	////-----------------------------------------------------------------------
	



}