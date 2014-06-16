//*********************************************************************************************************
#ifndef _CCD_MANAGER_H_
#define _CCD_MANAGER_H_
//*********************************************************************************************************
#include "ClientPreqs.h"
#include "CDTimer.h"
//*********************************************************************************************************
namespace MG
{
    class CCDManager
    {
    public:
        CCDManager();
        ~CCDManager();
        SINGLETON_INSTANCE(CCDManager);

    public:
        //��ʼ��
        void                    init();
        //��һ����ɫ
        void                    addCharacter(CD_MASTER_TYPE type, IdType id);
        //��ɫɾ��
        void                    deleteCharacter(CD_MASTER_TYPE type, IdType id);

    public:
        Bool                    checkCD(CD_MASTER_TYPE type, IdType id, U32 cdid);
        void                    addCD(CD_MASTER_TYPE type, IdType id, U32 cdid, U32 liveTime, U32 totalTime);
        void                    removeCD(CD_MASTER_TYPE type, IdType id, U32 cdid);
        void                    removeGroupCD(CD_MASTER_TYPE type, IdType id, U32 cdGroupId);
		CDTimerData*			findCD(CD_MASTER_TYPE type, IdType id, U32 cdid);

	public://���cdTimer
		const CDTimer*			getForceCDTimer();
		const CDTimer*			getCityCDTimer();
		const CDTimer*			getClanCDTimer();
		const CDTimer*			getGenrealCDTimer(IdType genrealid);

    private:
        void                    clear();

	private:
		Bool                    isInitialize;

    private:
		CDTimer*					mForceCDTimer;
		CDTimer*					mCityCDTimer;
        CDTimer*                    mClanCDTimer;
        std::map<IdType, CDTimer*>  mMapGenrealCDTimer;
        std::map<IdType, CDTimer*>  mMapTroopCDTimer;

    };
}
//*********************************************************************************************************
#endif
//*********************************************************************************************************