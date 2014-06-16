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
	//�������ݼ�����Ч
	/******************************************************************************/
	class CGoUpAndDownSkillEffect : public CSkillEffect
	{
	public:
		CGoUpAndDownSkillEffect( CSkillObject* object );
		virtual ~CGoUpAndDownSkillEffect();

		/// ��ʼ
		virtual void                start();
		/// ����
		virtual void                end();
		/// ����
		virtual void                update( Flt delta );
		/// ���ÿ�ʼ��λ��
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