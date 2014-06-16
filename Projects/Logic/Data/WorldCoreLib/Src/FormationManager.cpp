/******************************************************************************/
#include "stdafx.h"
#include "FormationManager.h"
#include "Formation.h"
/******************************************************************************/

namespace MG
{
	FormationManager::FormationManager():mFormaion(NULL)
	{

	}
	
	//-----------------------------------------------------------------------
	FormationManager::~FormationManager()
	{
		destroyFormation();
	}

	//-----------------------------------------------------------------------
	Formation* FormationManager::createFormation( FormationType formationType )
	{
		mFormaion = new Formation( formationType );
		return mFormaion;
	}

	//-----------------------------------------------------------------------
	void FormationManager::destroyFormation()
	{
		MG_SAFE_DELETE(mFormaion);
	}

	//-----------------------------------------------------------------------
	Formation* FormationManager::getCurrFormation()
	{
		return mFormaion;
	}
}

/******************************************************************************/