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