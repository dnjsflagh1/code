/******************************************************************************/
#ifndef _CAIENTITYPATHFINDINGPURSUE_H_
#define _CAIENTITYPATHFINDINGPURSUE_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "LinedState.h"
#include "CAI.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************

	******************************************************************************/
	class CAIEntityPathFindingPursue : public CAI, public LinedStateObject
	{
	public:
		CAIEntityPathFindingPursue( CCharacterSceneEntity* characterSceneEntity );
		virtual ~CAIEntityPathFindingPursue();

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

	public:

		//����Ŀ��
		void											setTarget( Vec3 pos );
		void											setTarget( GAMEOBJ_TYPE gameType, GameObjectIdType id, UInt index = 0 );

		////////////////////////////////////////////////////////////////////////

		void											setPursueRadius( Flt pursueRadius );

		void											setStopPursueRadius( Flt stopPursueRadius );

	protected:

		void											updatePursue( Flt delta );

		// ֹͣ˼��
		void											stopThink( Flt time );
		// �ָ�˼��
		void											resumeThink();

		////////////////////////////////////////////////////////////////////////
		void											notifyPursueResult( Bool isFinish );

		void											notifyTargetDied();

	private:

		CAIEntityPathFindingMoveInAdvance*				mPathFindingMoveAI;
		GAMEOBJ_TYPE									mTargetType;
		GameObjectIdType								mTargetId;
		UInt											mTargetIndex;
		Vec3											mTargetPos;
		Bool											mIsFinished;
		Vec3											mMoveToPos;
		Vec3											mLastTargetPos;
		Int												mBlockDiameter;
		Flt												mPauseThinkTime;
		Flt												mPursueRadius;
		Vec3											mPoint;
		Flt												mStopPursueRadius;
	};
}

#endif