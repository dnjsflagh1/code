/******************************************************************************/
#ifndef _SKILLOBJECT_H_
#define _SKILLOBJECT_H_
/******************************************************************************/

#include "WorldCorePreqs.h"
#include "WorldCoreDefine.h"
#include "CLuaBinder.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    //技能状态
    /******************************************************************************/
    enum SkillState
    {
        SKILLSTATE_NONE = 0,
        SKILLSTATE_CLANT,   //吟唱阶段
        SKILLSTATE_INJECT,  //发起阶段
    };

	enum SkillPhases
	{
		SKILLPHASES_NONE = 0,

		SKILLPHASES_START,   //吟唱开始阶段
		SKILLPHASES_UPDATE,
		SKILLPHASES_END,
	};

    /******************************************************************************/
    //技能操作类型
    /******************************************************************************/
    enum SkillOpType
    {
        SKILLOPTYPE_NONE        = 0,    //无意义
        SKILLOPTYPE_PASSIVITY   = 1,    //被动
		SKILLOPTYPE_EMITTER		= 2,
		//SKILLOPTYPE_INSTANT     = 2,    //瞬发
        SKILLOPTYPE_POINT       = 3,    //点攻击
        SKILLOPTYPE_OBJECT      = 4,    //锁定目标
    };
		
    enum STRATEGY_TYPE
    {
        ST_NONE     = 0,    //无意义
		ST_GENERAL  = 1,
        ST_METHOD   = 2,    //战法
        ST_PLAN     = 3,    //计策
        ST_ARMY     = 4,    //军略
        ST_POLITICS = 5,    //政略
    };


    enum AFFECT_TYPE
    {
        AT_NONE         = 0,    //无意义
        AT_SYSTEM       = 1,    //系统
        AT_NORMAL       = 2,    //一般
        AT_BENEFICIAL   = 3,    //有利
        AT_HARMFUL      = 4,    //不利
    };

    /******************************************************************************/
    //技能对象
    //用于描述技能相关功能接口，客户端和服务端分别继承实现各自对应的功能接口
    /******************************************************************************/
    class SkillObject : public CLuaReference
	{
	public:
		SkillObject();
		SkillObject( GAMEOBJ_TYPE ownerType, GameObjectIdType ownerId, UInt ownerIndex );
		virtual ~SkillObject();

    public:
        //得到基础配置数据
		virtual  SkillInfo*					getSkillInfo();

		virtual  void						setSkillInfo( SkillInfo* skillInfo );

		/////////////////////////////////////////////////////////////////////////////////////////
        //设置目标，一般用在发射指定方向的技能，SkillOpType = SKILLOPTYPE_POINT
        void								setTargetPosition(Vec3 pos);
        //得到目标
        Vec3								getTargetPosition();

        //设置目标，一般用在发射锁定目标的技能，SkillOpType = SKILLOPTYPE_OBJECT
        void								setTargetObject(GAMEOBJ_TYPE targetType, IdType targetId, Int targetIndex = -1);
        //得到目标
        GAMEOBJ_TYPE						getTargetObjectType();
        //得到目标		
        IdType								getTargetObjectID();

		UInt								getTargetObjectIndex();

		/////////////////////////////////////////////////////////////////////////////////////////
        //更新操作
		virtual void						update( Flt delta );

        //停止使用技能
        virtual void						stopUse();
        
		/////////////////////////////////////////////////////////////////////////////////////////

		//是否在吟唱技能
		virtual Bool						isClanting();
        //开始吟唱技能 //isCheckTiming:是否监听吟唱结束时间
        virtual void						startClant( Bool isUpdate = false );

		/////////////////////////////////////////////////////////////////////////////////////////
		//是否在释放技能
		virtual Bool						isInjecting();
        //开始释放技能
        virtual void						startInject( Bool isUpdate = false );

        //是否全部完成
                Bool                		isFinished(){ return mIsFinished;};
	public:
		GameObjectIdType					getOwnerID();

		GAMEOBJ_TYPE						getOwnerType();

		UInt								getOwnerIndex();

		//PlayerIdType						getPlayerID();

    protected:
		//skill开始使用
		virtual void						onSkillStart();
		//skillUpdate
		virtual void						onSkillUpdate( Flt delta );
		//skill使用结束
		virtual void						onSkillEnd();
		//skill完成使用
		virtual void						onSkillFinished();
		//skill吟唱开始
		virtual void						onSkillStartClant() = 0;
		//skill吟唱Update
		virtual void						onSkillUpdateClant( Flt delta ) = 0;
		//skill吟唱结束
		virtual void						onSkillEndClant() = 0;
		//skill吟唱完成
		virtual void                		onSkillClantFinished() = 0;
		//skill发射开始
		virtual void						onSkillStartInject() = 0;
		//skill发射Update
		virtual void						onSkillUpdateInject( Flt delta ) = 0;
		//skill发射结束
		virtual void						onSkillEndInject() = 0;
		//skill发射完成
		virtual void                		onSkillInjectFinished() = 0;

	
		/////////////////////////////////////////////////////////////////////////////////////////

		void								setUpdateTime( Flt time );

		void								setStopUpdateTime( Flt time );

		/////////////////////////////////////////////////////////////////////////////////////////

	protected:

		SkillState							mState;

		SkillPhases							mPhases;

		// 技能目标位置
		Vec3								mTargetPosition;

		// 技能目标对象
		GAMEOBJ_TYPE    					mTargetObjectType;
		IdType          					mTargetObjectID;
		Int									mTargetObjectIndex;

		// 是否检测时间
		Bool								mIsUpdate;

		// 现在时间
		Flt            						mCurrTiming;
		// 总时间
		Flt            						mTotalTiming;
		// 是否计时全部完成
		Bool								mIsFinished;

		GameObjectIdType					mOwnerId;
		UInt								mOwnerIndex;
		GAMEOBJ_TYPE						mOwnerType;

		//技能基础属性
		SkillInfo*							mSkillInfo;

		Flt									mUpdateTime;

		Flt									mPauseUpdateTime;
	
	};
}

#endif