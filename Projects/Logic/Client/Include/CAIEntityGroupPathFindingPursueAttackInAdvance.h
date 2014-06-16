/******************************************************************************/
#ifndef _CAIENTITYGROUPPATHFINDINGPURSUEATTACKINADVANCE_H_
#define _CAIENTITYGROUPPATHFINDINGPURSUEATTACKINADVANCE_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "CAIGroup.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    // 实体组寻路追击AI
    /******************************************************************************/
    class CAIEntityGroupPathFindingPursueAttackInAdvance : public CAIEntityGroup
    {
    public:
        CAIEntityGroupPathFindingPursueAttackInAdvance();
        virtual ~CAIEntityGroupPathFindingPursueAttackInAdvance();

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

		void											setTarget(Vec3 pos);
		void											setTarget(GAMEOBJ_TYPE gameType, GameObjectIdType id, UInt index = 0);
		void											setUseSkillId(IdType skillId);

	protected:

    protected:

		GAMEOBJ_TYPE									mTargetType;
		GameObjectIdType								mTargetId;
		UInt											mTargetIndex;
		Vec3											mTargetPos;
		IdType											mSkillId;
        
    };
}

#endif