/******************************************************************************/
#ifndef _CAIENTITYPATHFINDINGMOVEANDGUARDINADVANCE_H_
#define _CAIENTITYPATHFINDINGMOVEANDGUARDINADVANCE_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "LinedState.h"
#include "FightManager.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    // 实体 固定点 移动 锁敌 AI
    /******************************************************************************/
    class CAIEntityPathFindingMoveAndGuardInAdvance : public LinedStateObject, public FightManagerListener
    {
		enum MoveAndGuardAIState
		{
			MAGAS_NULL,
			MAGAS_MOVE,
			MAGAS_SEARCH,
			MAGAS_PURSUEATTACK,
		};

    public:
        CAIEntityPathFindingMoveAndGuardInAdvance( CCharacterSceneEntity*	characterSceneEntity );
        virtual ~CAIEntityPathFindingMoveAndGuardInAdvance();

        //状态名字
        static Str STATE_NAME;

        ///更新事件
        virtual void        			update( Flt delta );
        ///是否结束了
        virtual Bool        			isFinished();
        ///进去状态事件
        virtual void        			onEnter();
        ///离开状态事件
        virtual void        			onLeave();

		void							setDestination( Vec3 pos );

		////////////////////////////////////////////////////////////////////////

		// 设置状态
		void							setState( MoveAndGuardAIState state );
		//设置目标
		void							setTarget( GAMEOBJ_TYPE targetType, IdType targetId, UInt targetIndex );

	protected:

		////////////////////////////////////////////////////////////////////////
		void							updateSearch( Flt delta );
		void							updatePursueAttack( Flt delta );
		void							updateMoveTo( Flt delta );
		////////////////////////////////////////////////////////////////////////

		//获得搜索结果
		Bool							getTargetBySearch( GAMEOBJ_TYPE& targetType, IdType& targetId, UInt& targetIndex );
		//获得目标根据仇恨
		Bool							getTargetByHate( GAMEOBJ_TYPE& targetType, IdType& targetId, UInt& targetIndex );
		//通知同军队的战友追击
		void							notifyTroopPursueAndAttack( GAMEOBJ_TYPE targetType, IdType targetId, UInt targetIndex );

		////////////////////////////////////////////////////////////////////////
		//开始追击
		void							startPursueAndAttack( GAMEOBJ_TYPE targetType, IdType targetId, UInt targetIndex );
		//追击
		void							pursueAndAttack( GAMEOBJ_TYPE targetType, IdType targetId, UInt targetIndex );
		//结束追击
		void							endPursueAndAttack();

		////////////////////////////////////////////////////////////////////////
		void							onFightInfoChanged( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID );

		////////////////////////////////////////////////////////////////////////
		// 停止思考
		void							stopThink( Flt time );
		// 恢复思考
		void							resumeThink();

    protected:
		CCharacterSceneEntity*			mCharacterSceneEntity;
		Vec3							mDestination;
		GAMEOBJ_TYPE					mTargetType;
		IdType							mTargetId;
		UInt							mTargetIndex;
		Flt								mGuardRadius;
		Flt								mPursueRadius;
		Flt								mViewRadius;
		MoveAndGuardAIState				mState;
		Flt								mPauseThinkTime;
    };
}

#endif