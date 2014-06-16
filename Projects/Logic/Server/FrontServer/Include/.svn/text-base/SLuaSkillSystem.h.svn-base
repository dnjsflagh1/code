/******************************************************************************/
#ifndef _SLUASKILLSYSTEM_H_
#define _SLUASKILLSYSTEM_H_
/******************************************************************************/

#include "LuaSkillSystem.h"

/******************************************************************************/


namespace MG
{
	/******************************************************************************/
	//游戏技能脚本系统
	/******************************************************************************/
	class SLuaSkillSystem : public LuaSkillSystem
	{
	public:
		SLuaSkillSystem();
		virtual ~SLuaSkillSystem();
		SINGLETON_INSTANCE(SLuaSkillSystem)

		/// 得到Lua管理对象
		LuaManager*     getLuaManager(){return mLuaMgr;};

		/// 得到技能基础信息
		//SkillBaseInfo*	getSkillBaseInfo(IdType skillId);

		/// C++ 调用 Lua的接口
		/// 服务器调用 ： 执行开始释放技能脚本
        void            execServerStartInjectScript(SkillObject* skillObject);
        /// 服务器调用 ： 执行释放技能计时脚本，由时间线驱动
        void            execServerUpdateInjectScript(SkillObject* skillObject, Flt time);
		/// 服务器调用 ： 执行结束技能计时脚本，由时间线驱动
		void            execServerEndInjectScript(SkillObject* skillObject);

        /// 服务器调用 ： 执行开始技能碰撞影响脚本
		//void            execServerCollisionAffectScript(Character* Injecter, Character* affecter, UInt affecterTotal, IdType skillID );
        
	protected:

		/// 注册和Lua相关方法
		virtual void     registerLua();

	};

}

/******************************************************************************/
#endif

