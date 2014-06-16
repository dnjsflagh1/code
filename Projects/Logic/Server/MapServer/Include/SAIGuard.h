/******************************************************************************/
#ifndef _SAIGUARD_H_
#define _SAIGUARD_H_
/******************************************************************************/

#include "MapServerPreqs.h"
#include "LinedState.h"
#include "SAI.h"

/******************************************************************************/

namespace MG
{
	
    /******************************************************************************/
    // ʵ�� ���� AI
    /******************************************************************************/
    class SAIGuard : public SAI, public LinedStateObject
    {
    public:
        SAIGuard( SCharacter* owner );
        virtual ~SAIGuard();

        //״̬����
        static Str STATE_NAME;

        ///�����¼�
        virtual void        	update( Flt delta );
        ///�Ƿ������
        virtual Bool        	isFinished();
        ///��ȥ״̬�¼�
        virtual void        	onEnter();
        ///�뿪״̬�¼�
        virtual void        	onLeave();

		////////////////////////////////////////////////////////////////////////

		Bool					getTargetBySearch( GAMEOBJ_TYPE& targetType, IdType& targetId, UInt& targetIndex );

        ////////////////////////////////////////////////////////////////////////
		
		void					setAIParam( Flt	guardIntervalTime, Flt guardRadius, UInt assaultableClant, UInt	assaultableChar );

		////////////////////////////////////////////////////////////////////////

	protected:

		void					notifySearchTarget(  GAMEOBJ_TYPE targetType, IdType targetId, UInt targetIndex );

    protected:

		Flt						mGuardRadius;
		Flt						mGuardIntervalTime;
		UInt					mAssaultableClant;
		UInt					mAssaultableChar;

		Flt						mPauseThinkTime;
    };
}

#endif