/******************************************************************************/
#ifndef _SLUACLANQUESTSYSTEM_H_
#define _SLUACLANQUESTSYSTEM_H_
/******************************************************************************/

#include "LuaClanQuestSystem.h"
#include "FrontServerPreqs.h"
/******************************************************************************/


namespace MG
{
	/******************************************************************************/
	//游戏家族任务脚本系统
	/******************************************************************************/
	class SLuaClanQuestSystem : public LuaClanQuestSystem
	{
	public:
		SLuaClanQuestSystem();
		virtual ~SLuaClanQuestSystem();
		SINGLETON_INSTANCE(SLuaClanQuestSystem)

		/// 得到Lua管理对象
		LuaManager*     getLuaManager(){return mLuaMgr;};

		/// C++ 调用 Lua的接口
        Bool            execAcceptQuestScript(SClan* clan,ClanQuestObject* clanQuestObj);
        Bool            execSubbmitQuestScript(SClan* clan,ClanQuestObject* clanQuestObj);
		
	protected:
		/// 注册和Lua相关方法
		virtual void     registerLua();

	};

}

/******************************************************************************/
#endif

