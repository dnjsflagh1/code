//******************************************************************************************
#ifndef _CLANQUESTINFOBASE_H_
#define _CLANQUESTINFOBASE_H_
//******************************************************************************************
#include "WorldCorePreqs.h"
//******************************************************************************************
namespace MG
{
#define QUEST_SCRIPT_NAME_MAX_LEN 64
#define MAX_CLAN_QUEST_VALUE_COUNT	4

	struct ClanQuestInfoBase
	{
		virtual QuestTextInfo*	getTextInfo() = 0;
		virtual	Str8&			getAcceptScript() = 0;
		virtual	Str8&			getSubmitScript() = 0;
		virtual	CYCLE_TYPE		getQuestCycleType() = 0;
		virtual	Int				getValue(Bool success,Int index) = 0;
		virtual	Int				getValueChangeGroupInfo(std::vector<QuestValueChangeInfo*>& changeValues) = 0;
		virtual U32             getItemGroupId() = 0;
		virtual U32             getItemDelGroupId() = 0;
		virtual U32             getclanJudgeId() = 0;
		virtual U32             getcharacterJudgeId() = 0;
	};

}
#endif