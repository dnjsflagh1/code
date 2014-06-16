
/******************************************************************************/
#include "stdafx.h"
#include "SLuaSkillSystem.h"
#include "SLuaCharacterForSkill.h"

//#include "Character.h"
//#include "GameObject.h"
/******************************************************************************/

namespace MG
{

 //   //-----------------------------------------------------------------------
 //   SLuaSkillSystem::SLuaSkillSystem()
 //   {
 //       
 //   }

 //   //-----------------------------------------------------------------------
 //   SLuaSkillSystem::~SLuaSkillSystem()
 //   {
 //     
 //   }

 //   //-----------------------------------------------------------------------
 //   void SLuaSkillSystem::registerLua()
 //   {
 //       lua_State* L = mLuaMgr->getMainLuaState();

 //        #define REGISTER_CLUABINDER(binderClass, luastate) binderClass binderClass##Object; binderClass##Object.LuaRegister(luastate);
 //                REGISTER_CLUABINDER(SLuaCharacterForSkill, L);
 //        #undef REGISTER_CLUABINDER
 //   }

 //   //-----------------------------------------------------------------------
 //   void SLuaSkillSystem::execServerCollisionAffectScript( SCharacter* Injecter, SCharacter* affecter, UInt affecterTotal, IdType skillID )
 //   {

 //       Bool result = false;
 //       mLuaMgr->startAssertStackBalance();
 //       {
 //           lua_State* L =  mLuaMgr->getMainLuaState();
 //           lua_getglobal( L, "Lua_ExecServerCollisionAffectScript" );

	//		SLuaCharacterForSkill::createUserData(L, Injecter, SLuaCharacterForSkill::LUA_TYPE_NAME.c_str());
	//		SLuaCharacterForSkill::createUserData(L, affecter, SLuaCharacterForSkill::LUA_TYPE_NAME.c_str());
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

	//////-----------------------------------------------------------------------
	//



}