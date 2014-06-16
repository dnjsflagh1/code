/******************************************************************************/
#ifndef _CLINEFLYSKILLEFFECT_H_
#define _CLINEFLYSKILLEFFECT_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "CSkillEffect.h"

/******************************************************************************/

namespace MG
{   

    /******************************************************************************/
    //�㼼����Ч
    /******************************************************************************/
    class CEmitterSkillEffect : public CSkillEffect
    {
		enum EmitterSkillEffectState
		{
			ESES_NULL,
			ESES_CREATEEFFECT,
			ESES_CHECKCOLLISION,
		};

    public:

		struct EffectEntityInfo
		{
			ISceneObject*		effectEntity;
			// ������Чʵ�������λ��
			Vec3				effectEntityLastPos;

			EffectEntityInfo(){effectEntity = NULL;}
		};

		enum EmitType
		{
			ET_PARALLEL,		//ƽ�з���
			ET_SCATTER,			//��ɢ����
		};

		enum FlyTrackType
		{
			FTT_LINE,				//ֱ��
			FTT_GATHERED,			//�ۼ�
			FTT_DIVERGENT,			//��ɢ
			FTT_HELICAL,			//����
		};

		CEmitterSkillEffect( CSkillObject* object );
		virtual ~CEmitterSkillEffect();


		/// ��ʼ
		virtual void                	start();
		/// ����
		virtual void                	end();
		/// ����
		virtual void                	update( Flt delta );

		/// ���ÿ�ʼ��λ��
		virtual void            		setStartPos( Vec3 pos );
		/// ���ÿ�ʼ�ķ���
		virtual void            		setStartDir( Vec3 dir );
		/// ���þ���
		virtual void            		setDistance( Flt dis );
		/// ����ɢ���Ƕ�
		virtual void					setScatterAngle( Flt angle );
		/// ���÷�������
		virtual void					setPitchAngle( Flt angle );
		/// ����ƫ��
		virtual void					setYawAngle( Flt angle );
		/// ���÷���������
		virtual void					setEmitterNum( UInt num );
		///����ƽ�м�ļ��
		virtual void					setEmitterInterval(UInt interval);
		/// �Ƿ���׹
		virtual void					setIsParabola( Bool IsParabola );
		/// ���÷�������
		virtual void					setEmitType( EmitType emitType);
		///���÷��й켣����
		virtual void            		setFlyTrackType( FlyTrackType flyTrackType );
		///����Ŀ��λ��
		virtual void					setTargetPos( Vec3 pos );
		///�����Ƿ񴩴�
		virtual void					setIsPuncture( Bool isPuncture );

		virtual void					setMoveSpeed( Flt speed );

	protected:
		////////////////////////////////////////////////////////////////////////////////////////////////
		Bool							getIsCanHit( CCharacterSceneEntity* hitCharacterSceneEntity );

		////////////////////////////////////////////////////////////////////////////////////////////////
		void							createEffect( CCharacterSceneEntity* characterSceneEntity );

		void							checkCollision( CCharacterSceneEntity* characterSceneEntity );

		void							effectCollision( CCharacterSceneEntity* characterSceneEntity,  CCharacterSceneEntity* hitCharacterSceneEntity );

		////////////////////////////////////////////////////////////////////////////////////////////////

		//���ƽ�з���������յ�
		void							getParllelEmitStartPosAndEndPos( UInt index, UInt emitterNum, UInt emitterInterval, Vec3& startPos, Vec3& endPos );
		//��÷�ɢ����ĽǶ�
		Flt								getScatterEmitAngle( UInt index, UInt emitterNum, Flt scatterAngle );

	protected:

		Vec3							mPos;
		Vec3							mDir;
		Vec3							mTargetPos;
		Flt								mDis;
		Flt								mScatterAngle;
		Flt								mPitchAngle;
		Flt								mYawAngle;
		UInt							mEmitterInterval;
		UInt							mEmitterNum;
		Bool							mIsParabola;
		EmitType						mEmitType;
		FlyTrackType					mFlyTrackType;
		Bool							mIsPuncture;
		Flt								mMoveSpeed;

		EmitterSkillEffectState			mState;

    private:

		std::vector<EffectEntityInfo*>	mEffectEntity;
		IdType							mMapId;
    };



}

/******************************************************************************/
#endif

