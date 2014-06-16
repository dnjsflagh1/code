/******************************************************************************/
#ifndef _CSKILLEFFECTSYSTEM_H_
#define _CSKILLEFFECTSYSTEM_H_
/******************************************************************************/
#include "ClientPreqs.h"
/******************************************************************************/

namespace MG
{   
    
    /******************************************************************************
	#	游戏技能特效系统.

	#	在技能的发射过程中被生成，分为在脚本中生成和在代码中生成.

	#	销毁分为2种
		1.自身销毁和
		2.技能结束销毁，通常由脚本技能对象控制销毁.通过脚本调用effect:end() (别忘记设置脚本特效对象为空)

	#	人为控制特效销毁的话，注意产生和销毁要成对.

	#	增加超时检测释放，等脚本和C++对象释放通知底层机制完成后加
    ******************************************************************************/
    class CSkillEffectSystem
    {
    public:
        CSkillEffectSystem();
        virtual ~CSkillEffectSystem();
		//SINGLETON_INSTANCE(CSkillEffectSystem)

        /// 初始化
        virtual Bool                    	initialize();
        /// 反初始化
        virtual Bool                    	uninitialize();
        /// 更新
        virtual void                    	update( Flt delta );
        // 清空所有技能
        virtual void                    	clear();
        // 当技能结束时
        virtual void                    	onSkillEnded( CSkillObject* skillObject );


        // 增加点特效
        virtual  CPointSkillEffect*			addPointEffect( CSkillObject* skillObject );
        // 增加点特效
        virtual CEmitterSkillEffect*		addEmitterSkillEffect( CSkillObject* skillObject );
		// 增目标特效
		virtual CObjectSkillEffect*			addObjectSkillEffect( CSkillObject* skillObject );
		// 增瞬间特效
		virtual CInstantSkillEffect*		addInstantSkillEffect( CSkillObject* skillObject );
		// 增冲刺特效
		virtual CSprintSkillEffect*			addSprintSkillEffect( CSkillObject* skillObject );

		virtual CGoUpAndDownSkillEffect*    addGoUpAndDownSkillEffect( CSkillObject* skillObject );

    protected:
		
  //      // 创建点特效
  //      virtual  CPointSkillEffect*       createPointEffect( SkillObject* skillObject ) = 0;
  //      // 创建直线飞行特效
  //      virtual CEmitterSkillEffect*     createLineFlyEffect( SkillObject* skillObject ) = 0;
		//// 创建目标特效
		//virtual CObjectSkillEffect*		createObjectEffect( SkillObject* skillObject ) = 0;
		//// 创建瞬间特效
		//virtual CInstantSkillEffect*		createInstantEffect( SkillObject* skillObject ) = 0;
		//// 创建冲刺特效
		//virtual CSprintSkillEffect*		createSprintEffect( SkillObject* skillObject ) = 0;

        
        // 技能特效列表
        std::list< CSkillEffect* >			mSkillEffectList;
    };

}

/******************************************************************************/
#endif

