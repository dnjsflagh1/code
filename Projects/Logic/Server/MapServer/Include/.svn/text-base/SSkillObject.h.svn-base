/******************************************************************************/
#ifndef _SSKILLOBJECT_H_
#define _SSKILLOBJECT_H_
/******************************************************************************/
#include "MapServerPreqs.h"
#include "SkillObject.h"
/******************************************************************************/
namespace MG
{

	class SSkillObject: public SkillObject
	{
    public:
        SSkillObject( SCharacter* owner );
        virtual ~SSkillObject();

		virtual void								update( Flt delta );

    protected:

		virtual void								onSkillStartClant();

		virtual void								onSkillUpdateClant( Flt delta );

		virtual void								onSkillEndClant();

		virtual void                				onSkillClantFinished();

		virtual void								onSkillStartInject();

		virtual void								onSkillUpdateInject( Flt delta );

		virtual void								onSkillEndInject();

		virtual void                				onSkillInjectFinished();


		///////////////////////////////////////////////////////////////////

		//执行技能开始吟唱逻辑
		virtual void								execServerSkillStartClantLogic();

		//执行技能吟唱Update逻辑
		virtual void								execServerSkillClantUpdateLogic();

		//执行技能结束吟唱逻辑
		virtual void								execServerSkillEndClantLogic();

		//执行技能吟唱脚本
		virtual void								execServerSkillStartClantScript();

		//执行技能吟唱Update脚本
		virtual void								execServerSkillClantUpdateScript();

		//执行技能结束吟唱脚本
		virtual void								execServerSkillEndClantScript();

		///////////////////////////////////////////////////////////////////

		//执行技能发射逻辑
		virtual void								execServerSkillStartInjectLogic();

		//执行技能发射Update逻辑
		virtual void								execServerSkillInjectUpdateLogic();

		//执行技能结束发射逻辑
		virtual void								execServerSkillEndInjectLogic();

		//执行技能发射脚本
		virtual void								execServerSkillStartInjectScript();

		//执行技能发射Update脚本
		virtual void								execServerSkillInjectUpdateScript();

		//执行技能结束发射脚本
		virtual void								execServerSkillEndInjectScript();


		///////////////////////////////////////////////////////////////////

	private:
		Flt             							mLastTime;
		SCharacter*									mOwner;
		Bool										mIsExecScript;
	};
}

#endif