/******************************************************************************/
#include "stdafx.h"
#include "LuaClanQuestSystem.h"
/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------
    LuaClanQuestSystem::LuaClanQuestSystem()
        :mLuaMgr(NULL)
    {
        
    }

    //-----------------------------------------------------------------------
    LuaClanQuestSystem::~LuaClanQuestSystem()
    {
        uninitialize();
    }

    //-----------------------------------------------------------------------
    Bool LuaClanQuestSystem::initialize(LuaManager* luaMgr, Str filePath)
	    {
		//FUNDETECTION(__MG_FUNC__);
        mLuaMgr = luaMgr;

        if ( loadLuaFile(filePath) == false )
            return false;
        
        registerLua();
        

        return true;
    }

    //-----------------------------------------------------------------------
    Bool LuaClanQuestSystem::uninitialize()
    {
        return true;
    }


    //-----------------------------------------------------------------------
    Bool LuaClanQuestSystem::loadLuaFile(Str filePath)
    {
        if ( mLuaMgr->dofile(filePath.c_str()) == false ) 
        {
            lua_State* L =  mLuaMgr->getMainLuaState();
            MG_LOG( out_error, ("%s error: lua_load_clan_quest error\n"), lua_tostring(L, -1) );
            return false;
        }
        return true;
    }
	//-----------------------------------------------------------------------
	



}