/******************************************************************************/
#ifndef _CAIENTITYGUARD_H_
#define _CAIENTITYGUARD_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "LinedState.h"
#include "CAI.h"

/******************************************************************************/

namespace MG
{
	
    /******************************************************************************/
    // ʵ�� ���� AI
    /******************************************************************************/
    class CAIEntityGuard : public CAI, public LinedStateObject
    {
    public:
        CAIEntityGuard( CCharacterSceneEntity*	characterSceneEntity );
        virtual ~CAIEntityGuard();

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