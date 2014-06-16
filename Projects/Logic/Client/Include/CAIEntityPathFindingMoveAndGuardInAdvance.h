/******************************************************************************/
#ifndef _CAIENTITYPATHFINDINGMOVEANDGUARDINADVANCE_H_
#define _CAIENTITYPATHFINDINGMOVEANDGUARDINADVANCE_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "LinedState.h"
#include "FightManager.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    // ʵ�� �̶��� �ƶ� ���� AI
    /******************************************************************************/
    class CAIEntityPathFindingMoveAndGuardInAdvance : public LinedStateObject, public FightManagerListener
    {
		enum MoveAndGuardAIState
		{
			MAGAS_NULL,
			MAGAS_MOVE,
			MAGAS_SEARCH,
			MAGAS_PURSUEATTACK,
		};

    public:
        CAIEntityPathFindingMoveAndGuardInAdvance( CCharacterSceneEntity*	characterSceneEntity );
        virtual ~CAIEntityPathFindingMoveAndGuardInAdvance();

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

		void							setDestination( Vec3 pos );

		////////////////////////////////////////////////////////////////////////

		// ����״̬
		void							setState( MoveAndGuardAIState state );
		//����Ŀ��
		void							setTarget( GAMEOBJ_TYPE targetType, IdType targetId, UInt targetIndex );

	protected:

		////////////////////////////////////////////////////////////////////////
		void							updateSearch( Flt delta );
		void							updatePursueAttack( Flt delta );
		void							updateMoveTo( Flt delta );
		////////////////////////////////////////////////////////////////////////

		//����������
		Bool							getTargetBySearch( GAMEOBJ_TYPE& targetType, IdType& targetId, UInt& targetIndex );
		//���Ŀ����ݳ��
		Bool							getTargetByHate( GAMEOBJ_TYPE& targetType, IdType& targetId, UInt& targetIndex );
		//֪ͨͬ���ӵ�ս��׷��
		void							notifyTroopPursueAndAttack( GAMEOBJ_TYPE targetType, IdType targetId, UInt targetIndex );

		////////////////////////////////////////////////////////////////////////
		//��ʼ׷��
		void							startPursueAndAttack( GAMEOBJ_TYPE targetType, IdType targetId, UInt targetIndex );
		//׷��
		void							pursueAndAttack( GAMEOBJ_TYPE targetType, IdType targetId, UInt targetIndex );
		//����׷��
		void							endPursueAndAttack();

		////////////////////////////////////////////////////////////////////////
		void							onFightInfoChanged( GAMEOBJ_TYPE fightObjectType, IdType fightObjectID );

		////////////////////////////////////////////////////////////////////////
		// ֹͣ˼��
		void							stopThink( Flt time );
		// �ָ�˼��
		void							resumeThink();

    protected:
		CCharacterSceneEntity*			mCharacterSceneEntity;
		Vec3							mDestination;
		GAMEOBJ_TYPE					mTargetType;
		IdType							mTargetId;
		UInt							mTargetIndex;
		Flt								mGuardRadius;
		Flt								mPursueRadius;
		Flt								mViewRadius;
		MoveAndGuardAIState				mState;
		Flt								mPauseThinkTime;
    };
}

#endif