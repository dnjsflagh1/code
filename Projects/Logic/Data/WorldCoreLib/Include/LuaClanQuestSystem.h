/******************************************************************************/
#ifndef _LUACLANQUESTSYSTEM_H_
#define _LUACLANQUESTSYSTEM_H_
/******************************************************************************/

#include "WorldCorePreqs.h"

/******************************************************************************/


namespace MG
{
	/******************************************************************************/
	//游戏技能脚本系统
	/******************************************************************************/
	class LuaClanQuestSystem
	{
	public:
		LuaClanQuestSystem();
		virtual ~LuaClanQuestSystem();

		/// 初始化
		virtual Bool    initialize(LuaManager* luaMgr, Str filePath);
		/// 反初始化
		virtual Bool    uninitialize();

		/// 得到Lua管理对象
		LuaManager*     getLuaManager(){return mLuaMgr;};

        
	protected:

		/// 加载Lua文件
		Bool            loadLuaFile(Str filePath);

		/// 注册和Lua相关方法
		virtual void    registerLua() = 0;

	protected:
        // 脚本管理对象
		LuaManager*		mLuaMgr;
	};

}

/******************************************************************************/
#endif

