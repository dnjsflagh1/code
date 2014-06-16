/******************************************************************************/
#ifndef _CAIENTITYHATEDETECT_H_
#define _CAIENTITYHATEDETECT_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "LinedState.h"
#include "CAI.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************/

	/******************************************************************************/
	class CAIEntityHateDetect : public CAI, public LinedStateObject
	{
	public:
		CAIEntityHateDetect( CCharacterSceneEntity*	characterSceneEntity );
		virtual ~CAIEntityHateDetect();

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

		Bool					getTargetByHate( GAMEOBJ_TYPE& targetType, IdType& targetId, UInt& targetIndex );

		////////////////////////////////////////////////////////////////////////
		
		void					setHateRatio( Bool hateRatio );

		////////////////////////////////////////////////////////////////////////

		void					setCurrTarget( GAMEOBJ_TYPE	currTargetType, IdType currTargetId, UInt currTargetIndex );

		////////////////////////////////////////////////////////////////////////

	protected:

		void					notifyReturnFinish();

	protected:

		Bool					mIsMoveTo;
		Vec3					mReturnPos;
		Flt						mPauseThinkTime;
		U16						mHateRatio;	
		GAMEOBJ_TYPE			mCurrTargetType; 
		IdType					mCurrTargetId; 
		UInt					mCurrTargetIndex;
	};
}

#endif