/******************************************************************************/
#ifndef _CAIENTITYGROUPPATHFINDINGGATHERINADVANCE_H_
#define _CAIENTITYGROUPPATHFINDINGGATHERINADVANCE_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "CAIGroup.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    // 实体组寻路聚集AI
    /******************************************************************************/
    class CAIEntityGroupPathFindingGatherInAdvance : public CAIEntityGroup
    {
    public:
        CAIEntityGroupPathFindingGatherInAdvance();
        virtual ~CAIEntityGroupPathFindingGatherInAdvance();
        
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

    protected:


    };
}

#endif