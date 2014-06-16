/******************************************************************************/
#ifndef _FIGHTINFO_H_
#define _FIGHTINFO_H_
/******************************************************************************/

#include "WorldCorePreqs.h"
#include "WorldCoreDefine.h"

/******************************************************************************/



/******************************************************************************/
//’Ω∂∑–≈œ¢
/******************************************************************************/
namespace MG
{
	struct FightInfo
	{
		IdType				fightID;
		FIGHT_TYPE			fightType;
		GameObject*			fightObject;
		Bool				isInitiative;
		U64					beginTime;
		U64					endTime;
		UInt				hateVal;

		FightInfo():
		fightID(0),
		fightType(FIGHT_TYPE_NULL),
		fightObject(NULL),
		isInitiative(false),
		beginTime(0),
		endTime(0),
		hateVal(0)
		{

		}

		void updateInfo( GameObject* fightObject, UInt hateVal );
	};
}

#endif