//*******************************************************************************************************
#ifndef _H_CDTIMER_
#define _H_CDTIMER_
//*******************************************************************************************************
#include "WorldCorePreqs.h"
#include "CDTemplate.h"
//*******************************************************************************************************
namespace MG
{
	//cd时间单位，毫秒
	//逻辑层面cd时间单位以毫秒为准

    //DB专用
    struct CDDBData
    {
        U32                     cdTempId;
        U32                     lastTime;
        U64                     saveTime;
		U32						mTotalTime;				 //总时间
    };
    //------------------------------------------------------------------------------
    struct CDTimerData
    {   
        U32                     mStartTime;              //开始时间。
        U32                     mLastTime;               //剩余时间
		U32						mTotalTime;				 //总时间
        const CDTempInfo*       mCdtempInfo;             //时钟模板信息
        //------------------------------------------------------------
        //构造
        CDTimerData(const CDTempInfo* info, U32 lastTime, U32 totalTime)
            :mCdtempInfo(info)
            ,mStartTime(MGTimeOp::getCurrTick())
            ,mLastTime(lastTime)
			,mTotalTime(totalTime)
        {
            ;
        }
        //------------------------------------------------------------
        void reset(U32 lastTime, U32 totalTime)
        {
            mStartTime = MGTimeOp::getCurrTick();
            mLastTime = lastTime;
			mTotalTime = totalTime;
        }
    };
    //---------------------------------------------------------------------------------------------
    class CDTimer 
    {
    public:
       CDTimer(){;}
       virtual ~CDTimer();

    public:
        // 加CD
        CDTimerData*    addTimer( U32 CDID, U32 liveTime, U32 totalTime );
        // 删除CD
        CDTimerData*    removeTimer( U32 CDID );
        // 删除同一个Group的CD
        void            removeGroupTimer( U32 groupID, std::vector<CDTimerData*>& pTimerDataVector);
        void            removeGroupTimer( U32 groupID);
        // 检查CD是否在运行
        Bool            ifGoing( U32 CDID );
        // 找到CD
        CDTimerData*    findTimer( U32 CDID );
        // 获得所有的CD信息。
        const std::map<U32, CDTimerData*>*      
                        getAllCDTimeData()const{return &mCDTimerDataMapWork;}

    private:
        void            clear();

    private:
        std::map<U32, CDTimerData*> mCDTimerDataMapWork;        //正在CD的timer

    };
}
//*******************************************************************************************************
#endif //_H_CDTIMER_
//*******************************************************************************************************