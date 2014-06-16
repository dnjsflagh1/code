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
    // ʵ����Ѱ·�ƶ�AI
    /******************************************************************************/
    class CAIEntityGroupPathFindingMoveInAdvance : public CAIEntityGroup, public LinedStateObjectListener
    {
    public:
        CAIEntityGroupPathFindingMoveInAdvance();
        virtual ~CAIEntityGroupPathFindingMoveInAdvance();

        //״̬����
        static Str STATE_NAME;

        ///�����¼�
        virtual void        			update( Flt delta );
        ///�Ƿ������
        virtual Bool        			isFinished();
        ///��ȥ״̬�¼�
        virtual void        			onEnter();
        ///�뿪״̬�¼�
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