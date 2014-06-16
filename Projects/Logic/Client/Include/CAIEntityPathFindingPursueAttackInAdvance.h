/******************************************************************************/
#ifndef _CAIENTITYPATHFINDINGPURSUEATTACKINADVANCE_H_
#define _CAIENTITYPATHFINDINGPURSUEATTACKINADVANCE_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "LinedState.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************
      # 攻击 AI
	  # 包含三种小AI:
			1.瞬发攻击
			2.目标点攻击
			3.活动目标攻击
	  #  	
    ******************************************************************************/
    class CAIEntityPathFindingPursueAttackInAdvance : public LinedStateObject
    {
		enum PursueAttackAIState
		{
			PAS_NULL,
			PAS_PURSUE,
			PAS_ATTACK,
			PAS_THINK,
		};

    public:
        CAIEntityPathFindingPursueAttackInAdvance( CCharacterSceneEntity* characterSceneEntity );
        virtual ~CAIEntityPathFindingPursueAttackInAdvance();

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

		void											setAIEntityGroup( CAIEntityGroup* aiEntityGroup );

		//是否连续攻击
		void											setIsLoopAttack( Bool isLoopAttack );

		//是否重新选择目标
		void											setIsSelectTargetObject( Bool isSelectTargetObject );

        ////////////////////////////////////////////////////////////////////////

		void											getTarget( GAMEOBJ_TYPE& gameType, GameObjectIdType& id, UInt& index );

	protected:

		void											updatePursue( Flt delta );

		void											updateAttack( Flt delta );

		void											updateThink( Flt delta );

		// 停止思考
		void											stopThink( Flt time );
		// 恢复思考
		void											resumeThink();

    protected:

		//获得默认技能
		IdType											getDefaultSkill();

		//选择目标
		void											selectTargetObject();

		//使用技能
		void											useSkill( CSkillObject*	skillObject, SkillInfo*	skillInfo );

		//是否可以攻击
		Bool											isAttack( CCharacterSceneEntity* owner, CCharacterSceneEntity* target );

		////////////////////////////////////////////////////////////////////////

		Flt												getAttackRange();

		////////////////////////////////////////////////////////////////////////

		Bool											isTroopCompanionTarget( GAMEOBJ_TYPE gameType, GameObjectIdType id, UInt index = 0 );

		////////////////////////////////////////////////////////////////////////

		Flt												clacPursueTime( CCharacterSceneEntity* owner, CCharacterSceneEntity* target, Vec3& pursuePos );

	private:
		
		CAIEntityPathFindingMoveInAdvance*				mPathFindingMoveAI;
		CCharacterSceneEntity*							mCharacterSceneEntity;
		SkillInfo*										mSkillInfo;
		GAMEOBJ_TYPE									mTargetType;
		GameObjectIdType								mTargetId;
		UInt											mTargetIndex;
		Vec3											mTargetPos;
		Vec3											mTargetTargetPos;
		UInt											mSkillId;
		Bool											mIsFinished;
		Flt												mAttackIntervalTime;
		CSkillObject*									mSkillObject;
		Vec3											mMoveToPos;
		Vec3											mLastTargetPos;
		Vec3											mLastTargetTargetPos;
		CAIEntityGroup*									mAIEntityGroup;
		Int												mBlockDiameter;
		PursueAttackAIState								mState;
		Bool											mIsLoopAttack;
		Bool											mIsSelectTargetObject;
		Flt												mPauseThinkTime;
		Flt												mPausePursueThinkTime;
		Flt												mAttackRange;
    };
}

#endif