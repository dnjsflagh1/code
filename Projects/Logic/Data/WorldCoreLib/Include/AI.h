/******************************************************************************/
#ifndef _AI_H_
#define _AI_H_
/******************************************************************************/
#include "WorldCorePreqs.h"
/******************************************************************************/

enum AIType
{
	AIT_NULL,
	AIT_HATEDETECT,
	AIT_ATTACK,
	AIT_GUARD,
	AIT_KEEPDISTANCE,
	AIT_PURSUE,
	AIT_RANDOMMOVE,
	AIT_SELECTSKILL,
	AIT_RETURN,
	AIT_SEEKHELP,
	AIT_ESCAPE,
};

/******************************************************************************/

namespace MG
{

	/******************************************************************************/
	//AI
	/******************************************************************************/
	class AI
	{
	public:
		AI();
		virtual ~AI();

		///////////////////////////////////////////////////////////////////////

		AIType					getAIType();

		void					addAIListener( AIControllerListener* listener );

		void					removeAIListener( AIControllerListener* listener );

		///////////////////////////////////////////////////////////////////////

		void					notifyEnd();

	protected:


	protected:
		AIControllerListener*	mAIListener;
		AIType					mAIType;
	};
}


#endif	