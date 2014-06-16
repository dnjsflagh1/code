/******************************************************************************/
#ifndef _CAIENTITYKEEPDISTANCE_H_
#define _CAIENTITYKEEPDISTANCE_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "LinedState.h"
#include "CAI.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************
	/******************************************************************************/

	class CAIEntityKeepDistance : public CAI, public LinedStateObject
	{
	public:
		CAIEntityKeepDistance( CCharacterSceneEntity* characterSceneEntity );
		virtual ~CAIEntityKeepDistance();

		//状态名字
		static Str STATE_NAME;

		///更新事件
		virtual void        							update( Flt delta );
		///是否结束了
		virtual Bool        							isFinished();
		///进去状态事件
		virtual void        							onEnter();
		///离开状态事件
		virtual void        							onLeave();

		//////////////////////////////////////////////////////////////////////////////////////

		void											setAIParam( Flt checkInterval, UInt checkRatio, Flt keepDistance, GAMEOBJ_TYPE	targetType, GameObjectIdType targetId, UInt	targetIndex );

	protected:

		void											notifyKeepDistance( Vec3 keepDisPos );

		void											notifyTargetDied();

		////////////////////////////////////////////////////////////////////////

		Bool											isKeepDistance( Vec3& pos );


	private:

		Flt												mCheckInterval;
		UInt											mCheckRatio;
		Flt												mKeepDistance;
		Flt												mPauseThinkTime;
		GAMEOBJ_TYPE									mTargetType;
		GameObjectIdType								mTargetId;
		UInt											mTargetIndex;

	};
}

#endif