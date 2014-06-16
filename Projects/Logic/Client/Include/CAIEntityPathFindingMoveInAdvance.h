/******************************************************************************/
#ifndef _CAIENTITYPATHFINDINGMOVEINADVANCE_H_
#define _CAIENTITYPATHFINDINGMOVEINADVANCE_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "LinedState.h"
#include "SceneEntityAction.h"

/******************************************************************************/

namespace MG
{

    //******************************************************************************

	enum AIEntityMoveType
	{
        /// 普通状态中
		AIEMT_NORMAL,
        /// 动态障碍寻路移动中
		AIEMT_DYNAMICMOVE,
        /// 静态障碍寻路移动中
		AIEMT_STATICMOVE,
	};
     
    //******************************************************************************
    /** 实体寻路移动AI 
    */

    /** 寻路流程
        @   使用【静态网格障碍数据】【A*算法】计算出寻路【折线】路线
        @   然后计算路线的直线多余【折点】，然后减去多余【折点】,生成新的【折线】
        @   然后提取最近2折点，开始寻路网格移动
        @   准备移动到新寻路网格的时候采用抢占式占用模式
        @   遇到寻路网格有动态障碍的时候，根据动态障碍上的元素状态判断是否停止或者动态计算新的寻路路线
    */
    //******************************************************************************/
    class CAIEntityPathFindingMoveInAdvance : public LinedStateObject, public LinedStateManagerListener
    {
    public:
        CAIEntityPathFindingMoveInAdvance( CCharacterSceneEntity* characterSceneEntity );
        virtual ~CAIEntityPathFindingMoveInAdvance();

        //状态名字
        static Str STATE_NAME;

        ///更新事件
        virtual void									update( Flt delta );
        ///是否结束了
        virtual Bool									isFinished();
        ///进去状态事件
        virtual void									onEnter();
        ///离开状态事件
        virtual void									onLeave();


        ////////////////////////////////////////////////////////////////////////

		// 得到当前状态
        CMoveAcionState                                 getMoveAcionState();

		// 得到或设置全局目标点
        void											setDestination(Vec3 pos);

		void											setUnblockPosDestination(Vec3 pos);

		Vec3											getDestination();

		// 得到逻辑角色对象
		CCharacterSceneEntity*							getOwner();

		// 设置AI组对象
		void											setAIEntityGroup( CAIEntityGroup* aiEntityGroup );

		/////////////////////////////////////////////////////////////////////////////////////////////////////

		Bool											getIsStaticMove();

	protected:

		// 检查和更新状态
		void											checkAndUpdateState( Flt delta );

		// 重新调整静态寻路
		PathFindingResult                               calculateAndDoStaticPathFinding();
        // 重新调整动态寻路
        PathFindingResult                               calculateAndDoDynamicPathFinding();

		/////////////////////////////////////////////////////////////////////////////////////////////////////

		// 停止思考
		void											stopThink( Flt time );
		// 恢复思考
		void											resumeThink();


		// 是否到达当前目标点 
		Bool											isArriveOnDestination( Vec3 des );
		// 得到最近可进入的点
		Bool											getNearestAccessiblePos( Vec3 centerPos, Vec3& nearestAccessiblePos );

		// 停止移动，发送消息到服务端
		void											requestStopMove();
		// 请求移动，发送消息到服务端
		void											requestMoveTo( Vec3 moveToPos, Bool isBlockCheck );

    protected:

		virtual void									onLinedStateAdd(LinedStateObject* obj);
		virtual void									onLinedStateRemove(LinedStateObject* obj);

    protected:

		// 逻辑层角色
		CCharacterSceneEntity*							mCharacterSceneEntity;
		// 寻路算法对象
		ISceneNodePathFindingMoveInAdvanceAction*		mPathFindingMoveInAdvanceAction;
		// AI层移动状态
		AIEntityMoveType								mState;
		// 所属组AI
		CAIEntityGroup*									mAIEntityGroup;

        // 总思考时间
        Flt												mTotleThinkTime;
		// 停止思考时间
		Flt												mPauseThinkTime;
		// 实际可以走的目的地
		Vec3											mRealDestination;
		// 理论目的地
        Vec3											mDestination;
		// 静态节点位置
		Vec3											mStaticCurrDestinationNodePos;
		// 动态节点位置
		Vec3											mDynamicCurrDestinationNodePos;

        // 请求开始的点
        Vec3                                            mRequestStartPosition;

		Flt												mMoveLength;
		Flt												mPatherRadius;
		Int												mBlockDiameter;

		Flt												mCheckBlockTime;
		Bool											mIsBlockCheck;

		Flt												mStartPathFindTime;
		Bool											mIsStartDynamicFind;

		Bool											mIsPathFinderWait;

		Bool											mIsStaticMove;
    };
}

#endif