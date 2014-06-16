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

		//	����db
		void				loadClanQuest(std::vector<dbDoingClanQuestObject>& doingQuestData,std::vector<FinishedClanQuestObject>& finishedQuestData );
        void                saveQuestDataToDataBase();

	public:

		// ֪ͨ�����¼� ���ⲿ�д���ص� �¼�ʱ���ô˽ӿ�
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

		// ���ڴ����
		void				processQuestFailedMemory(U32 questInfoId);
		ClanQuestObject*	processQuestFinishedMemory(U32 questInfoId);
		ClanQuestObject*	processAcceptClanQuestMemory(U32 questInfoId);
		ClanQuestObject*	processSubmitClanQuestMemory(U32 questInfoId);
		void				processGiveupClanQuestMemory(U32 questInfoId);

	private:
        
		//  ������ǰ Ԥ����
        void                preProcessAcceptQuest(ClanQuestObject* questObj);
		GAMEJUDGE_TYPE      questGameJudge(U32 questInfoId,U64 generalId);
		//
		SItemManager*       getSItemManager();
		

	};
}
#endif



