/******************************************************************************/
#ifndef _SLUASKILLSYSTEM_H_
#define _SLUASKILLSYSTEM_H_
/******************************************************************************/
#include "MapServerPreqs.h"
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

		/// C++ 调用 Lua的接口

        /// 服务器调用 ： 执行开始技能碰撞影响脚本
		void            execServerCollisionAffectScript(SCharacter* Injecter, SCharacter* affecter, UInt affecterTotal, IdType skillID );
        
	protected:
		/// 注册和Lua相关方法
		void            registerLua();

	};

}

/******************************************************************************/
#endif

