
/******************************************************************************/

#include "stdafx.h"
#include "SPlaceSceneObject.h"

/******************************************************************************/
namespace MG
{
	//-----------------------------------------------------------------------------
	SPlaceSceneObject::SPlaceSceneObject()
	{
	}

	//-----------------------------------------------------------------------------
	SPlaceSceneObject::~SPlaceSceneObject()
	{
	}

	Bool SPlaceSceneObject::initialize()
	{
		return true;
	}

	Bool SPlaceSceneObject::unInitialize()
	{
		return true;
	}

	void SPlaceSceneObject::clear()
	{

	}

	void SPlaceSceneObject::update(Flt delta)
	{

	}

	GameType SPlaceSceneObject::getGameType()
	{ 
		if (getInstanceUId() == 0)
		{
			return GameType_Rpg;
		}
		else if(getInstanceUId() > 0)
		{
			return GameType_Slg;
		}
		else
		{
			DYNAMIC_EEXCEPT_LOG("getInstanceUId < 0!");
		}

		return GameType_Null;
	}
	//-----------------------------------------------------------------------------

}	//namespace MG