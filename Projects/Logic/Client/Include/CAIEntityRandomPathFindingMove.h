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
    // ʵ�� ����� �ƶ� AI
    /******************************************************************************/
	class CAIEntityRandomPathFindingMove : public CAI, public LinedStateObject
    {
    public:
        CAIEntityRandomPathFindingMove(CCharacterSceneEntity*	characterSceneEntity);
        virtual ~CAIEntityRandomPathFindingMove();

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