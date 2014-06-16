
/******************************************************************************/
#include "stdafx.h"
#include "SLuaClanQuestSystem.h"
#include "SLuaClanForClanQuest.h"
#include "ClanQuestObject.h"
#include "QuestList.h"
#include "ClanQuestInfoBase.h"
/******************************************************************************/

namespace MG
{
	SLuaClanQuestSystem::SLuaClanQuestSystem()
	{

	}

	SLuaClanQuestSystem::~SLuaClanQuestSystem()
	{

	}

	Bool SLuaClanQuestSystem::execAcceptQuestScript(SClan* clan,ClanQuestObject* clanQuestObj)
	{
		Bool result = false;
		if (!clanQuestObj)
		{
			return result;
		}
		if (!clanQuestObj->mInfo)
		{
			return result;
		}
		if (!clanQuestObj->mInfo->questInfo)
		{
			return result;
		}
		Str8& acceptScript = clanQuestObj->mInfo->questInfo->getAcceptScript();
		if (acceptScript.empty() || acceptScript == "" || acceptScript.compare("0") == 0)
		{
			return result;
		}

		mLuaMgr->startAssertStackBalance();
		{
			lua_State* L =  mLuaMgr->getMainLuaState();
			lua_getglobal( L, acceptScript.c_str());
			SLuaClanForClanQuest::createUserData(L, clan, SLuaClanForClanQuest::LUA_TYPE_NAME.c_str());
			lua_pushinteger(L,(Int)clanQuestObj->mInfo->id);

			if ( mLuaMgr->luaPcall( 2, 1 ) )
				result = (lua_toboolean(L,-1) == 1 ? true : false);
			else
				result = false;

			lua_pop(L, 1);
		}
		mLuaMgr->endAssertStackBalance();
		return result;
	}

	Bool SLuaClanQuestSystem::execSubbmitQuestScript(SClan* clan,ClanQuestObject* clanQuestObj)
	{
		Bool result = false;
		if (!clanQuestObj)
		{
			return result;
		}
		if (!clanQuestObj->mInfo)
		{
			return result;
		}
		if (!clanQuestObj->mInfo->questInfo)
		{
			return result;
		}
		Str8& submitScript = clanQuestObj->mInfo->questInfo->getSubmitScript();
		if (submitScript.empty() || submitScript == "")
		{
			return result;
		}

		mLuaMgr->startAssertStackBalance();
		{
			lua_State* L =  mLuaMgr->getMainLuaState();
			lua_getglobal( L, submitScript.c_str() );
			SLuaClanForClanQuest::createUserData(L, clan, SLuaClanForClanQuest::LUA_TYPE_NAME.c_str());
			lua_pushinteger(L,(Int)clanQuestObj->mInfo->id);

			if ( mLuaMgr->luaPcall( 2, 1 ) )
				result = (lua_toboolean(L,-1) == 1 ? true : false);
			else
				result = false;

			lua_pop(L, 1);
		}
		mLuaMgr->endAssertStackBalance();
		return result;
	}

	void SLuaClanQuestSystem::registerLua()
	{

	}
}