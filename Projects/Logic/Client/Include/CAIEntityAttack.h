/******************************************************************************/
#ifndef _CAIENTITYATTACKINADVANCE_H_
#define _CAIENTITYATTACKINADVANCE_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "LinedState.h"
#include "CAI.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************
 	
	******************************************************************************/
	class CAIEntityAttack : public CAI, public LinedStateObject
	{
		enum AIAttackState
		{
			AIAS_NULL,
			AIAS_START,
			AIAS_END,
		};

	public:
		CAIEntityAttack( CCharacterSceneEntity* characterSceneEntity );
		virtual ~CAIEntityAttack();

		//状态名字
		static Str STATE_NAME;

		///更新事件
		virtual void        							update( Flt delta );
		///是否结束了
		virtual Bool        							isFinished();
		///进去状态事件
		virtual void        							onEnter();
		///离开状态事件
		virtual void        							onLeave();

	public:

		//设置目标
		void											setTarget( Vec3 pos );
		void											setTarget( GAMEOBJ_TYPE gameType, GameObjectIdType id, UInt index = 0 );

		//设置要使用的技能
		void											setUseSkillId( IdType skillId );


		////////////////////////////////////////////////////////////////////////

	protected:

		void											updateAttack( Flt delta );

	protected:

		//使用技能
		void											useSkill( CSkillObject*	skillObject );

		//是否可以攻击
		Bool											isAttack( CCharacterSceneEntity* owner, CCharacterSceneEntity* target );
		////////////////////////////////////////////////////////////////////////

		void											aiEnd();

		////////////////////////////////////////////////////////////////////////

		void											notifyAttackEnd();

		void											notifyTargetDied();

	private:

		GAMEOBJ_TYPE									mTargetType;
		GameObjectIdType								mTargetId;
		UInt											mTargetIndex;
		Vec3											mTargetPos;
		IdType											mSkillId;
		Bool											mIsFinished;
		UInt											mMinIntervalAttackTime;
		UInt											mMaxIntervalAttackTime;
		Flt												mPauseThinkTime;

		AIAttackState									mAIAttackState;

		CSkillObject*									mSkillObject;
	};
}

#endif