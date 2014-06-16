/******************************************************************************/
#ifndef _CPOINTSKILLEFFECT_H_
#define _CPOINTSKILLEFFECT_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "CSkillEffect.h"

/******************************************************************************/

namespace MG
{   

    /******************************************************************************/
    //�㼼����Ч
    /******************************************************************************/
    class CPointSkillEffect : public  CSkillEffect
    {
		enum PointSkillEffectState
		{
			PSES_NULL,
			PSES_CREATEEFFECT,
			PSES_MOVETO,
			PSES_CHECKCOLLISION,
		};
    public:
        CPointSkillEffect( CSkillObject* object );
        virtual ~CPointSkillEffect();

        /// ��ʼ
        virtual void                start();
        /// ����
        virtual void                end();
        /// ����
        virtual void                update( Flt delta );

		/// ����λ��
		virtual void            	setPos( Vec3 pos );
		virtual void				setStartPos( Vec3 pos );
		virtual void            	setFlyEffectId( UInt flyEffectID );
		//virtual void				setHight( UInt hight);
		virtual void				setRadius( UInt radius );
		virtual void				setAffectIntervalTime( Flt time );
		virtual void				setMoveSpeed( Flt moveSpeed );
		virtual void				setAffectNum( UInt num );
		virtual void				setAttackNum( UInt num );

	protected:
		void						getCanAttackNum(ISceneObjectCollisionCallback* callback, CCharacterSceneEntity* ownerCharacterSceneEntity);

		void						createEffect();

		void						effectMoveTo();

		void						checkCollision( CCharacterSceneEntity* owner );

		////////////////////////////////////////////////////////////////////////////////////
		// ֹͣ
		void						stopUpdate( Flt time );
		// �ָ�
		void						resumeUpdate();

	protected:
		Vec3						mPos;       //�����ͷŵ�λ��
		//UInt						mHight;	
		UInt						mAffectNum;
		UInt						mCurrAffectNum;
		UInt						mRadius;
		Flt							mAffectIntervalTime;
		UInt						mAttackNum;
		UInt						mCanAttackNum;
		UInt						mCurrAttackNum;
		PointSkillEffectState		mState;

	private:
		// CN_MODIFY
		IEffectComponent*			mEffectComponent;
		IEffectComponent*			mFlyEffectComponent;
		IdType						mMapId;
		Flt							mMoveSpeed;
		UInt						mFlyEffectID;
		Vec3						mStartPos;
		Flt							mPauseThinkTime;

    };



}

/******************************************************************************/
#endif

