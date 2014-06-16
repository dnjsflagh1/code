/******************************************************************************/
#ifndef _CLOBJECTSKILLEFFECT_H_
#define _CLOBJECTSKILLEFFECT_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "CSkillEffect.h"

/******************************************************************************/

namespace MG
{   

	/******************************************************************************
		#Ŀ�꼼����Ч

		������������Ŀ��

		createFlyEntity() -> effectMoveTo() -> effectCollision()

		createFlyEntity()������Ч�������ʿ������IEntityʵ�壬���򴴽�IEffectEntityʵ��

		effectMoveTo()��Ч���У� �����IEffectEntityʵ���Ǹ���Ԥ�ȼ�����е�ʱ�����ж��Ƿ���У�
		IEntityʵ���Ǹ���ʵ���Ŀ��ľ������жϻ���

		effectCollision()���У� ����ǻ������Ǳ��ͻ��ˣ����ͻ��а�

	******************************************************************************/
	class CObjectSkillEffect : public CSkillEffect
	{
		enum ObjectSkillEffectState
		{
			OSES_NULL,
			OSES_CREATEEFFECT,
			OSES_MOVETO,
			OSES_COLLISION,
		};
	public:
		CObjectSkillEffect( CSkillObject* object );
		virtual ~CObjectSkillEffect();

		/// ��ʼ
		virtual void           	 	start();
		/// ����
		virtual void           	 	end();
		/// ����
		virtual void           	 	update( Flt delta );
		
		///////////////////////////////////////////////////////////////////////////////////////
		/// ���ÿ�ʼ��λ��
		virtual void           	 	setStartPos( Vec3 pos );
		/// ���þ���
		virtual void           	 	setDistance( Flt dis );
		///����Ŀ��id
		virtual void				setTargetIndex( UInt index );
		///����Ŀ��id
		virtual void				setTargetID( IdType id );
		///����Ŀ������
		virtual void				setTargetType( GAMEOBJ_TYPE type );

		virtual void				setMoveSpeed( Flt speed );

		///////////////////////////////////////////////////////////////////////////////////////

	protected:

		//////////////////////////////////////////////////////////////////////////////////////////

		IEntity*					createFlyEntity( UInt effectId, Vec3 pos, Vec3 dir, Bool isVisible );

		// CN_MODIFY
		IEffectComponent*			createEffectComponent( UInt effectId, Vec3 pos, Vec3 dir, Bool isAutoDestroy );

		void						moveToPos( ISceneNode* sceneNode, Vec3 pos );

		////////////////////////////////////////////////////////////////////////////////////////

		// ֹͣ
		void						stopUpdate( Flt time );
		// �ָ�
		void						resumeUpdate();

		///////////////////////////////////////////////////////////////////////////////////////
		//������Ч
		void						createEffect( CCharacterSceneEntity* owner, CCharacterSceneEntity* target );
		//��Ч�ƶ�
		void						effectMoveTo( CCharacterSceneEntity* owner, CCharacterSceneEntity* target );
		//��Ч����
		void						effectCollision(  CCharacterSceneEntity* owner, CCharacterSceneEntity* target );

	protected:
		Vec3						mPos;
		Vec3						mDir;
		Flt							mDis;
		Flt							mMoveSpeed;

		UInt						mTargetIndex;
		IdType						mTargetId;
		GAMEOBJ_TYPE				mTargetType;

		ObjectSkillEffectState		mState;

		// ������Чʵ��
		IEffectComponent*			mEffectComponent;

		// ������Чʵ��
		IEntity*					mFlyEntity;

		Bool						mIsSendCollisionPacket;

		Flt							mPauseThinkTime;
	};



}

/******************************************************************************/
#endif