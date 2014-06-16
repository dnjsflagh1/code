/******************************************************************************/
#ifndef _CLUASKILLSYSTEM_H_
#define _CLUASKILLSYSTEM_H_
/******************************************************************************/

#include "LuaSkillSystem.h"
#include "CSkillObject.h"

/******************************************************************************/


namespace MG
{
	/******************************************************************************/
	//游戏技能脚本系统
	/******************************************************************************/
	class CLuaSkillSystem : public LuaSkillSystem
	{
	public:
		CLuaSkillSystem();
		virtual ~CLuaSkillSystem();
		SINGLETON_INSTANCE(CLuaSkillSystem)

		/// 客户端调用：执行开始吟唱技能脚本，由服务器消息驱动
		void							execClientStartClantScript(CSkillObject* skillObject);
		/// 客户端调用：执行吟唱技能计时脚本，由时间线驱动
		void							execClientUpdateClantScript(CSkillObject* skillObject, Flt time);
		/// 客户端调用：执行结束吟唱技能脚本，由服务器消息驱动
		void							execClientEndClantScript(CSkillObject* skillObject);
		
		/// 客户端调用：执行技能前置开始脚本，由服务器消息驱动
		void							execClientStartFrontScript(CSkillObject* skillObject);
		/// 客户端调用：执行技能前置开始脚本，由服务器消息驱动
		void							execClientEndFrontScript(CSkillObject* skillObject);
		/// 客户端调用：执行技能后置结束脚本，由时间线驱动
		void							execClientStartBehindScript(CSkillObject* skillObject);
		/// 客户端调用：执行技能后置结束脚本，由时间线驱动
		void							execClientEndBehindScript(CSkillObject* skillObject);
		/// 客户端调用：执行开始释放技能脚本，由服务器消息驱动
		void							execClientStartInjectScript(CSkillObject* skillObject);
		/// 客户端调用：执行释放技能计时脚本，由时间线驱动
		void							execClientUpdateInjectScript(CSkillObject* skillObject, Flt time);
		/// 客户端调用：执行结束技能计时脚本，由时间线驱动
		void							execClientEndInjectScript(CSkillObject* skillObject);


        /// 客户端调用 ： 执行开始技能碰撞影响脚本
        void							execClientCollisionAffectScript(CCharacterSceneEntity* affecter, UInt addecterTotal, CSkillObject* skillObject, CSkillEffect* skillEffect);

	protected:
		virtual void					registerLua();

	};

}

/******************************************************************************/
#endif

