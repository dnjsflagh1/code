/******************************************************************************/
#ifndef _CAIENTITYESCAPE_H_
#define _CAIENTITYESCAPE_H_
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
	class CAIEntityEscape : public CAI, public LinedStateObject
	{
	public:
		CAIEntityEscape( CCharacterSceneEntity*	characterSceneEntity );
		virtual ~CAIEntityEscape();

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