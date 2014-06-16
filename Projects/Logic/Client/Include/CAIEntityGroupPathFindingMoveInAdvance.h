/******************************************************************************/
#ifndef _CAIENTITYGROUPPATHFINDINGMOVEINADVANCE_H_
#define _CAIENTITYGROUPPATHFINDINGMOVEINADVANCE_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "CAIGroup.h"

/******************************************************************************/

namespace MG
{

	struct AIPosGroupList
	{
		std::map<IdType, Vec3>				posList;	
	};

	struct AIEntityTypePosGroupList
	{
		std::map<IdType, AIPosGroupList>	posGroupList;
	};

	struct GroupRowMoveToPos
	{
		std::vector<Vec3>					moveToPos;
	};

    /******************************************************************************/
    // 实体组寻路移动AI
    /******************************************************************************/
    class CAIEntityGroupPathFindingMoveInAdvance : public CAIEntityGroup, public LinedStateObjectListener
    {
    public:
        CAIEntityGroupPathFindingMoveInAdvance();
        virtual ~CAIEntityGroupPathFindingMoveInAdvance();

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

        void							setDestination(Vec3 pos);

	protected:

		void							calcGroupCharacterEntityPos(Vec3 pos, Vec3 dir, std::map<UInt, GroupRowMoveToPos>& moveToPosList);

		void							calcGroupCharacterEntityMoveToPos(std::map<UInt, GroupRowMoveToPos>& moveToPosList);

		Vec3							calcGroupCenterPos();

		void							onLinedStateLeave(LinedStateObject* obj);

    protected:

        Vec3							mDestination;
		AIEntityTypePosGroupList		mEntityTypePosGroupList;
    };
}

#endif