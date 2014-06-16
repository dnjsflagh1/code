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
    // ʵ�� ����� �ƶ� ���� AI
    /******************************************************************************/
    class CAIEntityRandomPathFindingMoveAndGuardInAdvance : public LinedStateObject
    {
    public:
        CAIEntityRandomPathFindingMoveAndGuardInAdvance(CCharacterSceneEntity*	characterSceneEntity);
        virtual ~CAIEntityRandomPathFindingMoveAndGuardInAdvance();

        //״̬����
        static Str STATE_NAME;

        ///�����¼�
        virtual void        update( Flt delta );
        ///�Ƿ������
        virtual Bool        isFinished();
        ///��ȥ״̬�¼�
        virtual void        onEnter();
        ///�뿪״̬�¼�
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