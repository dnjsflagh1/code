/******************************************************************************/
#ifndef _LUASKILLSYSTEM_H_
#define _LUASKILLSYSTEM_H_
/******************************************************************************/

#include "WorldCorePreqs.h"

/******************************************************************************/


namespace MG
{
	/******************************************************************************/
	//游戏技能脚本系统
	/******************************************************************************/
	class LuaSkillSystem
	{
	public:
		LuaSkillSystem();
		virtual ~LuaSkillSystem();
		//SINGLETON_INSTANCE(LuaSkillSystem)

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

		/// 加载技能基础信息
		Bool			loadSkillBaseInfo();

	private:

		// 得到一个数字的表
		void			getNumberListFromTable( Int tableIndex, Str name, std::vector<U32>& list );
		// 得到一个数字的表
		void			getNumberMapFromTable( Int tableIndex, Str name, std::map<IdType,UInt>& map  );

	protected:

        // 脚本管理对象
		LuaManager*		mLuaMgr;

	};

}

/******************************************************************************/
#endif

