/******************************************************************************/
#ifndef _CGOUPANDDOWNSKILLEFFECT_H_
#define _CGOUPANDDOWNSKILLEFFECT_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "CSkillEffect.h"

/******************************************************************************/

namespace MG
{   

	/******************************************************************************/
	//架设云梯技能特效
	/******************************************************************************/
	class CGoUpAndDownSkillEffect : public CSkillEffect
	{
	public:
		CGoUpAndDownSkillEffect( CSkillObject* object );
		virtual ~CGoUpAndDownSkillEffect();

		/// 开始
		virtual void                start();
		/// 结束
		virtual void                end();
		/// 更新
		virtual void                update( Flt delta );
		/// 设置开始的位置
		virtual void				setTargetPos( Vec3 pos );
		virtual void				setDir( Vec3 dir );

	protected:
		Vec3						mTargetPos;
		Vec3						mDir;

	private:
		IEffectComponent*			mEffectComponent;
		Bool						mIsGoUp;
		Flt							mPlayAnimationTime;
		Flt							mCurrInterValTime;
	};



}

/******************************************************************************/
#endif