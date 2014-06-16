/******************************************************************************/
#ifndef _CAIENTITYGUARD_H_
#define _CAIENTITYGUARD_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "LinedState.h"
#include "CAI.h"

/******************************************************************************/

namespace MG
{
	
    /******************************************************************************/
    // 实体 锁敌 AI
    /******************************************************************************/
    class CAIEntityGuard : public CAI, public LinedStateObject
    {
    public:
        CAIEntityGuard( CCharacterSceneEntity*	characterSceneEntity );
        virtual ~CAIEntityGuard();

        //状态名字
        static Str STATE_NAME;

        ///更新事件
        virtual void        	update( Flt delta );
        ///是否结束了
        virtual Bool        	isFinished();
        ///进去状态事件
        virtual void        	onEnter();
        ///离开状态事件
        virtual void        	onLeave();

		////////////////////////////////////////////////////////////////////////

		Bool					getTargetBySearch( GAMEOBJ_TYPE& targetType, IdType& targetId, UInt& targetIndex );

        ////////////////////////////////////////////////////////////////////////
		
		void					setAIParam( Flt	guardIntervalTime, Flt guardRadius, UInt assaultableClant, UInt	assaultableChar );

		////////////////////////////////////////////////////////////////////////

	protected:

		void					notifySearchTarget(  GAMEOBJ_TYPE targetType, IdType targetId, UInt targetIndex );

    protected:

		Flt						mGuardRadius;
		Flt						mGuardIntervalTime;
		UInt					mAssaultableClant;
		UInt					mAssaultableChar;

		Flt						mPauseThinkTime;
    };
}

#endif