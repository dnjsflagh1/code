
/******************************************************************************/
#include "stdafx.h"
#include "CSkillObject.h"
#include "CLuaSkillObject.h"
#include "CLuaSkillSystem.h"
#include "CLuaCharacterForSkill.h"
#include "CLuaSkillEffect.h"
#include "SkillBaseInfo.h"

//#include "Character.h"
//#include "GameObject.h"
/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------
    CLuaSkillSystem::CLuaSkillSystem()
    {
        
    }

    //-----------------------------------------------------------------------
    CLuaSkillSystem::~CLuaSkillSystem()
    {

    }

    //-----------------------------------------------------------------------
    void CLuaSkillSystem::execClientStartClantScript(CSkillObject* skillObject)
    {
        Bool result = false;
        mLuaMgr->startAssertStackBalance();
        {
            lua_State* L =  mLuaMgr->getMainLuaState();
            lua_getglobal( L, "Lua_ExecClientStartClantScript" );

            CLuaSkillObject::createUserData(L, skillObject, CLuaSkillObject::LUA_TYPE_NAME.c_str());
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
    void CLuaSkillSystem::execClientUpdateClantScript(CSkillObject* skillObject, Flt time)
    {
        
    }

	//-----------------------------------------------------------------------
	void CLuaSkillSystem::execClientEndClantScript(CSkillObject* skillObject)
	{
		Bool result = false;
		mLuaMgr->startAssertStackBalance();
		{
			lua_State* L =  mLuaMgr->getMainLuaState();
			lua_getglobal( L, "Lua_ExecClientEndClantScript" );

			CLuaSkillObject::createUserData(L, skillObject, CLuaSkillObject::LUA_TYPE_NAME.c_str());
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
	void CLuaSkillSystem::execClientStartFrontScript(CSkillObject* skillObject)
	{
		Bool result = false;
		mLuaMgr->startAssertStackBalance();
		{
			lua_State* L =  mLuaMgr->getMainLuaState();
			lua_getglobal( L, "Lua_ExecClientStartFrontScript" );

			CLuaSkillObject::createUserData(L, skillObject, CLuaSkillObject::LUA_TYPE_NAME.c_str());
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
	void CLuaSkillSystem::execClientEndFrontScript(CSkillObject* skillObject)
	{
		Bool result = false;
		mLuaMgr->startAssertStackBalance();
		{
			lua_State* L =  mLuaMgr->getMainLuaState();
			lua_getglobal( L, "Lua_ExecClientEndFrontScript" );

			CLuaSkillObject::createUserData(L, skillObject, CLuaSkillObject::LUA_TYPE_NAME.c_str());
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
	void CLuaSkillSystem::execClientStartBehindScript(CSkillObject* skillObject)
	{
		Bool result = false;
		mLuaMgr->startAssertStackBalance();
		{
			lua_State* L =  mLuaMgr->getMainLuaState();
			lua_getglobal( L, "Lua_ExecClientStartBehindScript" );

			CLuaSkillObject::createUserData(L, skillObject, CLuaSkillObject::LUA_TYPE_NAME.c_str());
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
	void CLuaSkillSystem::execClientEndBehindScript(CSkillObject* skillObject)
	{
		Bool result = false;
		mLuaMgr->startAssertStackBalance();
		{
			lua_State* L =  mLuaMgr->getMainLuaState();
			lua_getglobal( L, "Lua_ExecClientEndBehindScript" );

			CLuaSkillObject::createUserData(L, skillObject, CLuaSkillObject::LUA_TYPE_NAME.c_str());
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
    void CLuaSkillSystem::execClientStartInjectScript(CSkillObject* skillObject)
    {
        Bool result = false;
        mLuaMgr->startAssertStackBalance();
        {
            lua_State* L =  mLuaMgr->getMainLuaState();
            lua_getglobal( L, "Lua_ExecClientStartInjectScript" );

            CLuaSkillObject::createUserData(L, skillObject, CLuaSkillObject::LUA_TYPE_NAME.c_str());
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
	void CLuaSkillSystem::execClientEndInjectScript(CSkillObject* skillObject)
	{
		Bool result = false;
		mLuaMgr->startAssertStackBalance();
		{
			lua_State* L =  mLuaMgr->getMainLuaState();
			lua_getglobal( L, "Lua_ExecClientEndInjectScript" );

			CLuaSkillObject::createUserData(L, skillObject, CLuaSkillObject::LUA_TYPE_NAME.c_str());
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
    void CLuaSkillSystem::execClientUpdateInjectScript(CSkillObject* skillObject, Flt time)
    {
        Bool result = false;
        mLuaMgr->startAssertStackBalance();
        {
            lua_State* L =  mLuaMgr->getMainLuaState();
            lua_getglobal( L, "Lua_ExecClientUpdateInjectScript" );

            CLuaSkillObject::createUserData(L, skillObject, CLuaSkillObject::LUA_TYPE_NAME.c_str());
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
    void CLuaSkillSystem::execClientCollisionAffectScript(CCharacterSceneEntity* affecter, UInt addecterTotal, CSkillObject* skillObject, CSkillEffect* skillEffect)
    {
        Bool result = false;
        mLuaMgr->startAssertStackBalance();
        {
            lua_State* L =  mLuaMgr->getMainLuaState();
            lua_getglobal( L, "Lua_ExecClientCollisionAffectScript" );

            LUA_RETURN_OBJECT( affecter, CLuaCharacterForSkill, L )
            lua_pushinteger(L, (Int)addecterTotal);
			LUA_RETURN_OBJECT( skillObject, CLuaSkillObject, L )
            LUA_RETURN_OBJECT( skillEffect, CLuaSkillEffect, L )
            lua_pushinteger(L, (Int)skillEffect->getSkillID());

            if ( mLuaMgr->luaPcall( 5, 1 ) )
                result = (lua_toboolean(L,-1) == 1 ? true : false);
            else
                result = false;

            lua_pop(L, 1);
        }
        mLuaMgr->endAssertStackBalance();
    }

//    //-----------------------------------------------------------------------

	void CLuaSkillSystem::registerLua()
	{
	    lua_State* L = mLuaMgr->getMainLuaState();

	    #define REGISTER_CLUABINDER(binderClass, luastate) binderClass binderClass##Object; binderClass##Object.LuaRegister(luastate);

	            REGISTER_CLUABINDER(CLuaSkillObject, L);
	            REGISTER_CLUABINDER(CLuaCharacterForSkill, L);
	            REGISTER_CLUABINDER(CLuaSkillEffect, L);
				REGISTER_CLUABINDER(CLuaPointSkillEffect, L);
				REGISTER_CLUABINDER(CLuaEmitterSkillEffect, L);
				REGISTER_CLUABINDER(CLuaObjectSkillEffect, L);
				REGISTER_CLUABINDER(CLuaInstantSkillEffect, L);
				REGISTER_CLUABINDER(CLuaSprintSkillEffect, L);

	    #undef REGISTER_CLUABINDER
	}

}