/******************************************************************************/
#include "stdafx.h"
#include "AI.h"
#include "AIController.h"
/******************************************************************************/
namespace MG
{

	//--------------------------------------------------------------------------
	AI::AI()
		:mAIListener(NULL), mAIType(AIT_NULL)
	{

	}

	//--------------------------------------------------------------------------
	AI::~AI()
	{

	}

	//--------------------------------------------------------------------------
	AIType AI::getAIType()
	{
		return mAIType;
	}

	//--------------------------------------------------------------------------
	void AI::addAIListener( AIControllerListener* listener )
	{
		mAIListener = listener;
	}

	//--------------------------------------------------------------------------
	void AI::removeAIListener( AIControllerListener* listener )
	{
		mAIListener = NULL;
	}

	//--------------------------------------------------------------------------
	void AI::notifyEnd()
	{
		if(mAIListener)
		{
			mAIListener->onEnd(this);
		}
	}
}