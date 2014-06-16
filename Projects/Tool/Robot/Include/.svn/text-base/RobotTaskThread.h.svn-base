//***********************************************************************************************************
#ifndef _ROBOTTASKTHREAD_H_
#define _ROBOTTASKTHREAD_H_
//***********************************************************************************************************
//#include "CClientNew.h"
#include "Thread.h"
//***********************************************************************************************************
namespace MG
{

	//***********************************************************************************************************
	// ¼àÌýÏß³Ì
	//***********************************************************************************************************
    class ThreadTaskManager;
	class CClient;
	class CCampaignManager;
	class RobotTaskThread : public ModeTaskListenThreadNew
    {	
    public:
		RobotTaskThread();
        virtual	~RobotTaskThread();

	public:
		void			setManager(ThreadTaskManager* mgr,Int index);
		void			prepare();

		virtual	void	listenEvent();
		void			OneThreadGameUpdate();

		Int				preassignmentCampaginList(I32 campaignNum,I32 generalNum,I32 time = 0);
		CCampaignManager* getCampaignMgr();
	private:
		ThreadTaskManager*				mManager;
		Int								mIndex;
		Int								mCurrClient;

		Bool							mCanRun;
		U32								mLastTick;
		CCampaignManager*				mCampaignMgr;

#ifdef TEST_THREAD_USE
		CClient**						mClientTest;
		Int								mClientCount;
		Int								mCurrClientIndex;
#else
		std::vector<CClient*>::iterator mClientIt;
		std::vector<CClient*>*			mClients;
#endif
    };

}
//***********************************************************************************************************
#endif
//***********************************************************************************************************