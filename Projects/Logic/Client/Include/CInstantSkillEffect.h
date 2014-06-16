/******************************************************************************/
#ifndef _CINSTANTSKILLEFFECT_H_
#define _CINSTANTSKILLEFFECT_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "CSkillEffect.h"

/******************************************************************************/

namespace MG
{   

	/******************************************************************************/
	//瞬发技能特效
	/******************************************************************************/
	class CInstantSkillEffect : public CSkillEffect
	{
		enum InstantSkillEffectState
		{
			ISES_NULL,
			ISES_COLLISION,
		};

	public:
		CInstantSkillEffect( CSkillObject* object );
		virtual ~CInstantSkillEffect();

		/// 开始
		virtual void                start();
		/// 结束
		virtual void                end();
		/// 更新
		virtual void                update( Flt delta );
		/// 设置开始的位置
		virtual void				setPos( Vec3 pos );

		virtual void				setTargetIndex( UInt index );
		///设置目标id
		virtual void				setTargetID( IdType id );
		///设置目标类型
		virtual void				setTargetType( GAMEOBJ_TYPE type );

	protected:
		void						effectCollision( CCharacterSceneEntity* owner, CCharacterSceneEntity* target );

		////////////////////////////////////////////////////////////////////////////////////
		// 停止
		void						stopUpdate( Flt time );
		// 恢复
		void						resumeUpdate();

	protected:
		Vec3						mPos;

		UInt						mTargetIndex;
		IdType						mTargetId;
		GAMEOBJ_TYPE				mTargetType;

		InstantSkillEffectState		mState;

	private:
		IEffectEntity*				mEffectEntity;
		Flt							mPauseThinkTime;
	};



}

/******************************************************************************/
#endif