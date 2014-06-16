/******************************************************************************/
#ifndef _SCLANQUESTMANAGER_H_
#define _SCLANQUESTMANAGER_H_
/******************************************************************************/
#include "Lock.h"
#include "LoginNetPacket.h"
#include "FrontServerPreqs.h"
#include "WorldCorePreqs.h"
#include "ClanQuestManager.h"
/******************************************************************************/
namespace MG
{
    
	/******************************************************************************/

	/******************************************************************************/
	class SClanQuestManager : public ClanQuestManager
	{
	public:

		SClanQuestManager();
		virtual ~SClanQuestManager(){};

	public:              

		//	载入db
		void				loadClanQuest(std::vector<dbDoingClanQuestObject>& doingQuestData,std::vector<FinishedClanQuestObject>& finishedQuestData );
        void                saveQuestDataToDataBase();

	public:

		// 通知任务事件 当外部有此相关的 事件时调用此接口
		void 				notifyTalktoNpc(U32 questInfoId,U32 npcId);
		void 				notifyKillMonster(U32 mosterId);
		void 				notifyGetOrDropItem(U64 itemId,Bool isGet);
		void 				notifyGetGeneral(U64 generalId);
		void 				notifyLeaveMap();
		void				notifyInGameTime();

	public:

		QUEST_COMPLETE_STATE checkClanQuestState(ClanQuestObject* clanQuestObj);
		Bool				 isClanQuestTimeOut(ClanQuestObject* clanQuestObj);

		void				handleAcceptQuest(U32 questInfoId,U64 generalId);
		void				handleSubmitQuest(U32 questInfoId);
		void				handleGiveupQuest(U32 questInfoId);
		void				handleFinishQuest(U32 questInfoId);
		void				handleFailQuest(U32 questInfoId);

		// 对内存操作
		void				processQuestFailedMemory(U32 questInfoId);
		ClanQuestObject*	processQuestFinishedMemory(U32 questInfoId);
		ClanQuestObject*	processAcceptClanQuestMemory(U32 questInfoId);
		ClanQuestObject*	processSubmitClanQuestMemory(U32 questInfoId);
		void				processGiveupClanQuestMemory(U32 questInfoId);

	private:
        
		//  接任务前 预处理
        void                preProcessAcceptQuest(ClanQuestObject* questObj);
		GAMEJUDGE_TYPE      questGameJudge(U32 questInfoId,U64 generalId);
		//
		SItemManager*       getSItemManager();
		

	};
}
#endif



