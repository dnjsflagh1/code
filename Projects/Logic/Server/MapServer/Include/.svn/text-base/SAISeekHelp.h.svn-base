/******************************************************************************/
#ifndef _SAISEEKHELP_H_
#define _SAISEEKHELP_H_
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
	class SAISeekHelp : public SAI, public LinedStateObject
	{
	public:
		SAISeekHelp( SCharacter* owner );
		virtual ~SAISeekHelp();

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


		////////////////////////////////////////////////////////////////////////

		void					setSeekHelpRadius( Flt seekHelpRadius );

		void					setSeekHelpTemplate( std::vector<UInt>&	seekHelpTemplateList );

		void					setTarget( GAMEOBJ_TYPE targetType, IdType targetId, UInt targetIndex );

		////////////////////////////////////////////////////////////////////////


	protected:

		Flt						mSeekHelpRadius;
		GAMEOBJ_TYPE			mTargetType; 
		IdType					mTargetId;
		UInt					mTargetIndex;
		std::vector<UInt>		mSeekHelpTemplateList;
	};
}

#endif