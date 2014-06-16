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
		#目标技能特效

		发射飞行体跟随目标

		createFlyEntity() -> effectMoveTo() -> effectCollision()

		createFlyEntity()创建特效，如果是士兵创建IEntity实体，否则创建IEffectEntity实体

		effectMoveTo()特效飞行， 如果是IEffectEntity实体是根据预先计算飞行的时间来判断是否击中，
		IEntity实体是根据实体和目标的距离来判断击中

		effectCollision()击中， 如果是击中者是本客户端，发送击中包

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

		/// 开始
		virtual void           	 	start();
		/// 结束
		virtual void           	 	end();
		/// 更新
		virtual void           	 	update( Flt delta );
		
		///////////////////////////////////////////////////////////////////////////////////////
		/// 设置开始的位置
		virtual void           	 	setStartPos( Vec3 pos );
		/// 设置距离
		virtual void           	 	setDistance( Flt dis );
		///设置目标id
		virtual void				setTargetIndex( UInt index );
		///设置目标id
		virtual void				setTargetID( IdType id );
		///设置目标类型
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

		// 停止
		void						stopUpdate( Flt time );
		// 恢复
		void						resumeUpdate();

		///////////////////////////////////////////////////////////////////////////////////////
		//创建特效
		void						createEffect( CCharacterSceneEntity* owner, CCharacterSceneEntity* target );
		//特效移动
		void						effectMoveTo( CCharacterSceneEntity* owner, CCharacterSceneEntity* target );
		//特效击中
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

		// 引擎特效实体
		IEffectComponent*			mEffectComponent;

		// 引擎特效实体
		IEntity*					mFlyEntity;

		Bool						mIsSendCollisionPacket;

		Flt							mPauseThinkTime;
	};



}

/******************************************************************************/
#endif