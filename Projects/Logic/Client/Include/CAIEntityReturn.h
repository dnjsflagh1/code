/******************************************************************************/
#ifndef _CAIENTITYRETURN_H_
#define _CAIENTITYRETURN_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "LinedState.h"
#include "CAI.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************/
	// AI
	/******************************************************************************/
	class CAIEntityReturn : public CAI, public LinedStateObject
	{
	public:
		CAIEntityReturn( CCharacterSceneEntity*	characterSceneEntity );
		virtual ~CAIEntityReturn();

		//状态名字
		static Str STATE_NAME;

		///更新事件
		virtual void        	update( Flt delta );
		///是否结束了
		virtual Bool        	isFinished();
		///进去状态事件
		virtual void        	onEnter();
		///离开状态事件
		virtual void        	onLeave();

		////////////////////////////////////////////////////////////////////////

		void					setIsMoveTo( Bool isMoveTo );

		void					setReturnToPos( Vec3 pos );

		////////////////////////////////////////////////////////////////////////

	protected:

		void					notifyReturnFinish();

	protected:

		Bool					mIsMoveTo;

		Vec3					mReturnPos;

		Flt						mPauseThinkTime;
	};
}

#endif