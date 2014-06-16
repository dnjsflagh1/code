/******************************************************************************/
#include "stdafx.h"
#include "InstanceType2GameType.h"

/******************************************************************************/
namespace MG
{
	//-----------------------------------------------------------------------
	GameType InstanceType2GameType::InstanceTypeChangeGameType( const REGION_OBJ_TYPE regionType )
	{
		if (ROT_HOME	== regionType	||
			ROT_TIRO	== regionType	||
			ROT_PVE		== regionType	||
			ROT_GROWUP	== regionType)
		{
			//RPG
			return GameType_Rpg;
		}
		else if(ROT_PLACE == regionType		||
				ROT_HISTORY == regionType	||
				ROT_SPORT	== regionType	||
				ROT_HISTORY == regionType	||
				ROT_TRAIN	== regionType)
		{
			//SLG
			return GameType_Slg;
		}
		else if(ROT_MAP_DISTRIBUTION == regionType)
		{
			return GameType_Max;
		}
		else
		{
			DYNAMIC_ASSERT(0);
		}

		DYNAMIC_ASSERT(0);
		return GameType_Null;
	}
}