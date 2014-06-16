/******************************************************************************/
#ifndef _CSKILLOBJECT_H_
#define _CSKILLOBJECT_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "SkillObject.h"
#include "CSkillEffectSystem.h"
/******************************************************************************/
namespace MG
{

    /******************************************************************************

		# 客户端技能对象

		# 世界场景中用于显示表现的技能对象，包括动作，声音，特效等

		# lua接口

			@ startClant()(服务器通知调用). 
			  中调用Lua_ExecClientStartClantScript脚本.
			@ onClantFinished()(管理器中记时调用).（在收到新的Clant时会调用）
			  中调用Lua_ExecClientEndClantScript脚本.
			@ startInject()(服务器通知调用).
			  中调用Lua_ExecClientStartInjectScript脚本.
			@ onInjectFinished()(管理器中记时调用).（在收到新的Inject时会调用）
			  中调用Lua_ExecClientEndInjectScript脚本.

		# Clant和Inject触发前都会调用PrepareUseSkill(会移除当前活动的SkillObject)

		# 析构角色的时候

    ******************************************************************************/
    class CSkillObject : public SkillObject
    {
    public:
        CSkillObject( CCharacterSceneEntity* owner );
        virtual ~CSkillObject();

    public:
        //得到支配者
        //virtual CCharacterSceneEntity*      getCharacterEntity();

    public:

		///////////////////////////////////////////////////////////////////

		//是否执行脚本
		void								setIsExecScript( Bool isExecScript );

		Bool								getIsExecScript();

		///////////////////////////////////////////////////////////////////

		virtual void						startInject( Bool isUpdate  = false  );

		///////////////////////////////////////////////////////////////////

		Bool								getIsEndBehind();

		///////////////////////////////////////////////////////////////////


		CCharacterSceneEntity*				getOwner();

		///////////////////////////////////////////////////////////////////

    protected:

		///////////////////////////////////////////////////////////////////

		virtual void						onSkillFinished();

		virtual void						onSkillEnd();

		///////////////////////////////////////////////////////////////////

		//skill吟唱开始
		virtual void						onSkillStartClant();
		//skill吟唱Update
		virtual void						onSkillUpdateClant( Flt delta );
		//skill吟唱结束
		virtual void						onSkillEndClant();
		//skill吟唱完成
		virtual void                   		onSkillClantFinished();
		//skill发射前置开始
		virtual	void						onSkillStartFront();
		//skill发射前置结束
		virtual	void						onSkillEndFront();
		//skill发射开始
		virtual void						onSkillStartInject();
		//skill发射Update
		virtual void						onSkillUpdateInject( Flt delta );
		//skill发射结束
		virtual void						onSkillEndInject();
		//skill发射完成
		virtual void                   		onSkillInjectFinished();
		//skill后置开始
		virtual void                        onSkillStartBehind();
		//skill后置结束
		virtual void                        onSkillEndBehind();

		///////////////////////////////////////////////////////////////////

		//执行技能开始吟唱逻辑
		virtual void						execClientSkillStartClantLogic();

		//执行技能吟唱Update逻辑
		virtual void						execClientSkillClantUpdateLogic();

		//执行技能结束吟唱逻辑
		virtual void						execClientSkillEndClantLogic();

		//执行技能吟唱脚本
		virtual void						execClientSkillStartClantScript();

		//执行技能吟唱Update脚本
		virtual void						execClientSkillClantUpdateScript();

		//执行技能结束吟唱脚本
		virtual void						execClientSkillEndClantScript();

		///////////////////////////////////////////////////////////////////

		//执行技能前置开始逻辑
		virtual void						execClientSkillStartFrontLogic();

		//执行技能前置结束逻辑
		virtual void						execClientSkillEndFrontLogic();

		//执行技能前置开始脚本
		virtual void						execClientSkillStartFrontScript();

		//执行技能前置结束脚本
		virtual void						execClientSkillEndFrontScript();

		////////////////////////////////////////////////////////////////////

		//执行技能结束后置开始逻辑
		virtual void						execClientSkillStartBehindLogic();

		//执行技能结束后置结束逻辑
		virtual void						execClientSkillEndBehindLogic();

		//执行技能后置开始脚本
		virtual void						execClientSkillStartBehindScript();

		//执行技能后置结束脚本
		virtual void						execClientSkillEndBehindScript();

		///////////////////////////////////////////////////////////////////

		//执行技能发射逻辑
		virtual void						execClientSkillStartInjectLogic();

		//执行技能发射Update逻辑
		virtual void						execClientSkillInjectUpdateLogic();

		//执行技能结束发射逻辑
		virtual void						execClientSkillEndInjectLogic();

		//执行技能发射脚本
		virtual void						execClientSkillStartInjectScript();

		//执行技能发射Update脚本
		virtual void						execClientSkillInjectUpdateScript();

		//执行技能结束发射脚本
		virtual void						execClientSkillEndInjectScript();


		///////////////////////////////////////////////////////////////////

	protected:

		CCharacterSceneEntity*				mOwner;
		Bool								mIsExecScript;
		Bool								mIsEndBehind;
    };
}

#endif