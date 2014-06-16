
//*************************************************************************************************//
#include "stdafx.h"
#include "CQuestPlayerCharacter.h"
#include "CClan.h"
//*************************************************************************************************//

namespace MG
{
	//--------------------------------------------------------------------------
	CQuestPlayerCharacter::CQuestPlayerCharacter(Clan* clan)
		:QuestPlayerCharacter(clan)
	{
	}

	//--------------------------------------------------------------------------
	CQuestPlayerCharacter::~CQuestPlayerCharacter()
	{
	}

	//--------------------------------------------------------------------------
	Bool CQuestPlayerCharacter::addQuest(Int questID)
	{
		return getClan()->addQuest(questID);
	}

	//--------------------------------------------------------------------------
	Bool CQuestPlayerCharacter::submitQuest(Int questID)
	{
		return getClan()->submitQuest(questID);
	}

	//--------------------------------------------------------------------------
	Bool CQuestPlayerCharacter::giveupQuest(Int questID)
	{
		return getClan()->giveupQuest(questID);
	}



	//--------------------------------------------------------------------------

}