/******************************************************************************/
#ifndef _SAIRETURN_H_
#define _SAIRETURN_H_
/******************************************************************************/

#include "MapServerPreqs.h"
#include "LinedState.h"
#include "SAI.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************/
	// ʵ�� ���� AI
	/******************************************************************************/
	class SAIReturn : public SAI, public LinedStateObject
	{
	public:
		enum ReturnType
		{
			RT_NULL,
			RT_INSTANT,
			RT_MOVETO,
		};

		SAIReturn( SCharacter*	owner );
		virtual ~SAIReturn();

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

		void					setReturnType( ReturnType returnType );

		void					setReturnToPos( Vec3 pos );

		////////////////////////////////////////////////////////////////////////

	protected:

		void					notifyReturnFinish();

	protected:

		Vec3					mReturnPos;

		Flt						mPauseThinkTime;

		ReturnType				mReturnType;
	};
}

#endif