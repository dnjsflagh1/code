/******************************************************************************/
#ifndef _CAIENTITYRANDOMPATHFINDINGMOVEINADVANCE_H_
#define _CAIENTITYRANDOMPATHFINDINGMOVEINADVANCE_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "LinedState.h"
#include "CAI.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    // 实体 随机点 移动 AI
    /******************************************************************************/
	class CAIEntityRandomPathFindingMove : public CAI, public LinedStateObject
    {
    public:
        CAIEntityRandomPathFindingMove(CCharacterSceneEntity*	characterSceneEntity);
        virtual ~CAIEntityRandomPathFindingMove();

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

		void							setAIParam( Vec3 centerPos, Flt minInterval, Flt maxInterval, Flt moveRadius );

        ////////////////////////////////////////////////////////////////////////
	protected:
		Vec3							getRandomMoveToPos();



    protected:

		Flt								mMoveRadius;
		Vec3							mCenterPos;
		Flt								mMinInterval;
		Flt								mMaxInterval;
		Vec3							mDestination;
		Bool							mIsStartMove;
		Flt								mPauseThinkTime;
    };
}

#endif