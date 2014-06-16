/******************************************************************************/
#ifndef _SAIRANDOMMOVE_H_
#define _SAIRANDOMMOVE_H_
/******************************************************************************/

#include "MapServerPreqs.h"
#include "LinedState.h"
#include "SAI.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    // 实体 随机点 移动 AI
    /******************************************************************************/
	class SAIRandomMove : public SAI, public LinedStateObject
    {
    public:
        SAIRandomMove( SCharacter* owner );
        virtual ~SAIRandomMove();

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

		////////////////////////////////////////////////////////////////////////

		void							setAIParam( Vec3 centerPos, Flt minInterval, Flt maxInterval, Flt minMoveRadius, Flt maxMoveRadius );

        ////////////////////////////////////////////////////////////////////////
	protected:
		Vec3							getRandomMoveToPos();



    protected:
		Flt								mMinMoveRadius;
		Flt								mMaxMoveRadius;
		Vec3							mCenterPos;
		Flt								mMinInterval;
		Flt								mMaxInterval;
		Vec3							mDestination;
		Bool							mIsStartMove;
		Flt								mPauseThinkTime;
    };
}

#endif