/******************************************************************************/
#include "stdafx.h"
#include "Formation.h"
////#include "Troop.h"
/******************************************************************************/

namespace MG
{
	Formation::Formation( FormationType formationType ): mFormationType(formationType)
	{

	}

	//-----------------------------------------------------------------------
	Formation::~Formation()
	{

	}

	//-----------------------------------------------------------------------
	void Formation::setFormationType(FormationType formationType)
	{
		mFormationType = formationType;
	}

	//-----------------------------------------------------------------------
	void Formation::changeFormationType( FormationType formationType )
	{
		mFormationType = formationType;
	}

	//-----------------------------------------------------------------------
	void Formation::moveTo( Vec3 pos, Bool isBreakAction, Str actionName )
	{

	}

	//-----------------------------------------------------------------------
	void Formation::yawToDir( Vec3 dir )
	{

	}
}

/******************************************************************************/