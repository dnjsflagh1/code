//*************************************************************************************************//
#include "stdafx.h"
#include "CQuestManager.h"
#include "CQuestPlayerCharacter.h"
//*************************************************************************************************//

namespace MG
{
	//--------------------------------------------------------------------------
	CQuestManager::CQuestManager(CClan* clan)
		:QuestSysManagerBase((Clan*)clan)
	{
		setQuestPlayerCharacter(MG_NEW CQuestPlayerCharacter((Clan*)clan));
	}

	//--------------------------------------------------------------------------
	CQuestManager::~CQuestManager()
	{
        //MG_SAFE_DELETE(mPlayerCharacter);
	}

	//--------------------------------------------------------------------------
	QuestPlayerCharacter* CQuestManager::createLuaQuestPlayerCharacter(Clan* clan)
	{
		return (QuestPlayerCharacter*)MG_NEW CQuestPlayerCharacter(clan);
	}

	//--------------------------------------------------------------------------
}
/******************************************************************************/