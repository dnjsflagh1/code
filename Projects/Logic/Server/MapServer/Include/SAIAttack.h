/******************************************************************************/
#ifndef _SAIATTACK_H_
#define _SAIATTACK_H_
/******************************************************************************/

#include "LinedState.h"
#include "SAI.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************
 	
	******************************************************************************/
	class SAIAttack : public SAI, public LinedStateObject
	{
		enum AIAttackState
		{
			AIAS_NULL,
			AIAS_START,
			AIAS_END,
		};

	public:
		SAIAttack( SCharacter* owner );
		virtual ~SAIAttack();

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
		void											useSkill( SSkillObject*	skillObject );

		//是否可以攻击
		Bool											isAttack( SCharacter* owner, SCharacter* target );
		////////////////////////////////////////////////////////////////////////

		void											aiEnd();

		////////////////////////////////////////////////////////////////////////

		void											notifyAttackEnd();

		void											notifyTargetDied();

		////////////////////////////////////////////////////////////////////////

		Bool											isTargetCharSkill( SkillInfo* skillInfo );

		Bool											isTargetPosSkill( SkillInfo* skillInfo );

	private:

		GAMEOBJ_TYPE									mTargetType;
		GameObjectIdType								mTargetId;
		UInt											mTargetIndex;
		Vec3											mTargetPos;
		IdType											mSkillId;
		Bool											mIsFinished;
		Flt												mPauseThinkTime;
		UInt											mMinIntervalAttackTime;
		UInt											mMaxIntervalAttackTime;

		AIAttackState									mAIAttackState;

		SSkillObject*									mSkillObject;
	};
}

#endif