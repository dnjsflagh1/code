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
    // ʵ����Ѱ·׷��AI
    /******************************************************************************/
    class CAIEntityGroupPathFindingPursueAttackInAdvance : public CAIEntityGroup
    {
    public:
        CAIEntityGroupPathFindingPursueAttackInAdvance();
        virtual ~CAIEntityGroupPathFindingPursueAttackInAdvance();

        //״̬����
        static Str STATE_NAME;

        ///�����¼�
        virtual void        							update( Flt delta );
        ///�Ƿ������
        virtual Bool        							isFinished();
        ///��ȥ״̬�¼�
        virtual void        							onEnter();
        ///�뿪״̬�¼�
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