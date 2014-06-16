/******************************************************************************/
#ifndef _CAIENTITYRANDOMPATHFINDINGMOVEANDGUARDINADVANCE_H_
#define _CAIENTITYRANDOMPATHFINDINGMOVEANDGUARDINADVANCE_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "LinedState.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    // 实体 随机点 移动 锁敌 AI
    /******************************************************************************/
    class CAIEntityRandomPathFindingMoveAndGuardInAdvance : public LinedStateObject
    {
    public:
        CAIEntityRandomPathFindingMoveAndGuardInAdvance(CCharacterSceneEntity*	characterSceneEntity);
        virtual ~CAIEntityRandomPathFindingMoveAndGuardInAdvance();

        //状态名字
        static Str STATE_NAME;

        ///更新事件
        virtual void        update( Flt delta );
        ///是否结束了
        virtual Bool        isFinished();
        ///进去状态事件
        virtual void        onEnter();
        ///离开状态事件
        virtual void        onLeave();

        ////////////////////////////////////////////////////////////////////////
	protected:
		Vec3				getRandomMoveToPos();



    protected:
		CCharacterSceneEntity*	mCharacterSceneEntity;
		Flt						mGuardRadius;
		Vec3					mDestination;
    };
}

#endif