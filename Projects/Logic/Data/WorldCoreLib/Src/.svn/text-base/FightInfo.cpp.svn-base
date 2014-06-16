/******************************************************************************/
#include "stdafx.h"
#include "FightInfo.h"
/******************************************************************************/

namespace MG
{
	void FightInfo::updateInfo( GameObject* fightObject, UInt hateVal )
	{
		if(this->fightObject != fightObject)
		{
			return;
		}

		endTime = MGTimeOp::getCurrTick();
		if(beginTime == 0)
		{
			beginTime = endTime;
		}

		this->hateVal += hateVal;
	}

	//--------------------------------------------------------------------------------------------
}