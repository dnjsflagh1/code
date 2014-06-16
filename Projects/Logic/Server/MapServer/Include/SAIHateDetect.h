/******************************************************************************/
#ifndef _SAIHATEDETECT_H_
#define _SAIHATEDETECT_H_
/******************************************************************************/

#include "MapServerPreqs.h"
#include "LinedState.h"
#include "SAI.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************/

	/******************************************************************************/
	class SAIHateDetect : public SAI, public LinedStateObject
	{
	public:
		SAIHateDetect( SCharacter* owner );
		virtual ~SAIHateDetect();

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

		Bool					getTargetByHate( GAMEOBJ_TYPE& targetType, IdType& targetId, UInt& targetIndex );

		////////////////////////////////////////////////////////////////////////
		
		void					setHateRatio( U16 hateRatio );

		////////////////////////////////////////////////////////////////////////

		void					setCurrTarget( GAMEOBJ_TYPE	currTargetType, IdType currTargetId, UInt currTargetIndex );

		////////////////////////////////////////////////////////////////////////

	protected:

		void					notifySearchTarget(  GAMEOBJ_TYPE targetType, IdType targetId, UInt targetIndex );

	protected:

		Flt						mPauseThinkTime;
		U16						mHateRatio;	
		GAMEOBJ_TYPE			mCurrTargetType; 
		IdType					mCurrTargetId; 
		UInt					mCurrTargetIndex;
	};
}

#endif