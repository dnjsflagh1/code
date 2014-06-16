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
	//˲��������Ч
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

		/// ��ʼ
		virtual void                start();
		/// ����
		virtual void                end();
		/// ����
		virtual void                update( Flt delta );
		/// ���ÿ�ʼ��λ��
		virtual void				setPos( Vec3 pos );

		virtual void				setTargetIndex( UInt index );
		///����Ŀ��id
		virtual void				setTargetID( IdType id );
		///����Ŀ������
		virtual void				setTargetType( GAMEOBJ_TYPE type );

	protected:
		void						effectCollision( CCharacterSceneEntity* owner, CCharacterSceneEntity* target );

		////////////////////////////////////////////////////////////////////////////////////
		// ֹͣ
		void						stopUpdate( Flt time );
		// �ָ�
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