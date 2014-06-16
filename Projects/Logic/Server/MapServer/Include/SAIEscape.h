/******************************************************************************/
#ifndef _SAIESCAPE_H_
#define _SAIESCAPE_H_
/******************************************************************************/

#include "MapServerPreqs.h"
#include "LinedState.h"
#include "SAI.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************/
	// AI
	/******************************************************************************/
	class SAIEscape : public SAI, public LinedStateObject
	{
	public:
		SAIEscape( SCharacter* owner );
		virtual ~SAIEscape();

		//状态名字
		static Str STATE_NAME;

		///更新事件
		virtual void        			update( Flt delta );
		///是否结束了
		virtual Bool        			isFinished();
		///进去状态事件
		virtual void        			onEnter();
		///离开状态事件
		virtual void        			onLeave();

		////////////////////////////////////////////////////////////////////////

		Vec3							getEscapeMoveToPos();

		void							setAIParam( UInt escapeRadius,  Flt escapeTime , Flt minInterval, Flt maxInterval );


		////////////////////////////////////////////////////////////////////////

	protected:

		void							notifyEscapeEnd();

	protected:
		UInt							mEscapeRadius;
		Flt								mEscapeTime;
		Flt								mStartEscapeTime;
		Vec3							mCenterPos;
		Flt								mMinInterval;
		Flt								mMaxInterval;
		Vec3							mDestination;
		Bool							mIsStartMove;
		Flt								mPauseThinkTime;
	};
}

#endif