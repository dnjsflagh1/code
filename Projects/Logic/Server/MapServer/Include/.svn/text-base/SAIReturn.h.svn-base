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
	// 实体 锁敌 AI
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