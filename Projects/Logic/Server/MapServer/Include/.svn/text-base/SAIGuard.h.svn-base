/******************************************************************************/
#ifndef _SAIGUARD_H_
#define _SAIGUARD_H_
/******************************************************************************/

#include "MapServerPreqs.h"
#include "LinedState.h"
#include "SAI.h"

/******************************************************************************/

namespace MG
{
	
    /******************************************************************************/
    // 实体 锁敌 AI
    /******************************************************************************/
    class SAIGuard : public SAI, public LinedStateObject
    {
    public:
        SAIGuard( SCharacter* owner );
        virtual ~SAIGuard();

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