/******************************************************************************/
#include "stdafx.h"
#include "SAIManager.h"
/******************************************************************************/
namespace MG
{

	//--------------------------------------------------------------------------
	SAIManager::SAIManager()
		:mLastUpdateTime(0)
	{

	}

	//--------------------------------------------------------------------------

	SAIManager::~SAIManager()
	{

	}

	//--------------------------------------------------------------------------
	void SAIManager::update()
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