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
    // ʵ�� ����� �ƶ� AI
    /******************************************************************************/
	class SAIRandomMove : public SAI, public LinedStateObject
    {
    public:
        SAIRandomMove( SCharacter* owner );
        virtual ~SAIRandomMove();

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