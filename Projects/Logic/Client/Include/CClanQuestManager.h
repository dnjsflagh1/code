/******************************************************************************/
#ifndef _CCLANQUESTMANAGER_H_
#define _CCLANQUESTMANAGER_H_
/******************************************************************************/
#include "QuestNetPacket.h"
#include "WorldCorePreqs.h"
#include "ClanQuestManager.h"
#include "ClientPreqs.h"
/******************************************************************************/
namespace MG
{
    
	/******************************************************************************/

	/******************************************************************************/
	class CClanQuestManager : public ClanQuestManager
	{
		friend class UIQuestManager;
	public:
		CClanQuestManager(){ setQuestMaxCount(16); }
		virtual ~CClanQuestManager(){}
		static	CClanQuestManager&	getInstance();
		void    setParentPlayer();

	public:
		// 操作任务接口
		void	acceptClanQuest(U32 questInfoId,PlayerCharacterIdType charId);
		void	submitClanQuest(U32 questInfoId);
		void	giveupClanQuest(U32 questInfoId);

	public:
		void	 handleRecvDoingQuestList(DOING_QUEST_DATA* questData, Int count);
		void	 handleRecvFinishedQuestList(FINISHED_QUEST_DATA* questData, Int count);
		void	 handleAcceptQuestResult(U32 questInfoId, PT_QUEST_F2C_ACCEPT_RESULT result);
		void	 handleSubmitQuestResult(U32 questInfoId, Byte result);
		void	 handleGiveupQuestResult(U32 questInfoId, Bool success);
		void	 setQuestState(U32 questInfoId, Byte completeState);
		void     handleRecvConditionVariable(U32 questInfoId,Byte varPos,Int varValue);
		void	 showQuestHintStr(U32 questInfoId, Str16& outStr);
	private:
        GAMEJUDGE_TYPE     questGameJudge(U32 questInfoId);
		CClanQuestManager(const CClanQuestManager&);

	};
}
#endif



