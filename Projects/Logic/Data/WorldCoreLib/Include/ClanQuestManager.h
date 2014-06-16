//**********************************************************************************************************
#ifndef _CLANQUESTMANAGER_H_
#define _CLANQUESTMANAGER_H_
//**********************************************************************************************************
#include "WorldCorePreqs.h"
#include "ClanQuestObject.h"
#include "ObjectPool.h"
//**********************************************************************************************************
namespace MG
{
    class ClanQuestManager
    {
    public:

		ClanQuestManager():mClan(NULL){}
		virtual	~ClanQuestManager();

	public:

        // 清空
        void                        clear();

        // 设置家族
        void                        setClan( Clan* clan ){ mClan = clan ;};
		Clan*						getClan();

		// 创建任务对象 
		ClanQuestObject*			createQuest(U32 questInfoId);
        FinishedClanQuestObject*    createFinishedQuest();
		// 任务内存操作
		ClanQuestObject*			getQuest(U32 questInfoId);
		void						addQuest(ClanQuestObject* quest);
		ClanQuestObject*			removeQuest(U32 questInfoId);
		void						destory(U32 questInfoId);
		void						destory(ClanQuestObject* clanQuestObj);
        Bool                        isExistInFinishedQuests(U32 questInfoId);
		Bool						isExistInSubmitQuests(U32 questInfoId);

		//
		void                        setQuestMaxCount(U32 count);
		U32                         getQuestMaxCount() const;
    public:

		// 任务操作判断
		virtual	Bool				canAccept(U32 questInfoId);
		virtual	Bool				canSubmit(U32 questInfoId);
		virtual	Bool				canGiveup(U32 questInfoId);

    private:
		std::map< U32 , ClanQuestObject*>	mSubmitedQuests;
		std::map< U32 , ClanQuestObject*>	mFailQuests;
		std::map< U32 , ClanQuestObject*>	mTimeOutQuests;

		ObjectPool<ClanQuestObject>			mQuestPool;
		ObjectPool<FinishedClanQuestObject> mFinishedQuestPool;

	protected:
        
		Clan*								mClan;
        U32                                 mQuestMaxCount;
		
		//
		std::map< U32 , ClanQuestObject*>				mAllDoingQuests;
		std::map< U32 , ClanQuestObject*>				mAcceptedQuests;
		std::map<U32,FinishedClanQuestObject*>          mFinishedQuests;

		std::map<U32,ClanQuestObject*>                  mIdleQuestObjects;

    };

   
}
//**********************************************************************************************************
#endif
//**********************************************************************************************************