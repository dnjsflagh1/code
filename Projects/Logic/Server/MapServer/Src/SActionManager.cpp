/******************************************************************************/
#include "stdafx.h"
#include "SActionManager.h"
/******************************************************************************/
namespace MG
{

	//--------------------------------------------------------------------------
	SActionManager::SActionManager()
		:mLastUpdateTime(0)
	{

	}

	//--------------------------------------------------------------------------

	SActionManager::~SActionManager()
	{

	}

	//--------------------------------------------------------------------------
	void SActionManager::update()
	{
		Flt delta = 0;
		Flt currTick = MGTimeOp::getCurrTick();

		if(mLastUpdateTime != 0)
		{
			delta = (currTick - mLastUpdateTime) / 1000;
		}

		LinedStateManager::update(delta);

		mLastUpdateTime = currTick;
	}
}