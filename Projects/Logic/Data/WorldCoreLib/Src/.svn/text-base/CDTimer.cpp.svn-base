//*******************************************************************************************************
#include "stdafx.h"
#include "CDTimer.h"
//*******************************************************************************************************
namespace MG
{
    //------------------------------------------------------------------------------------------
    CDTimer::~CDTimer()
    {
        clear();
    }
    //------------------------------------------------------------------------------------------
    CDTimerData* CDTimer::addTimer( U32 ID, U32 liveTime, U32 totalTime )
    {
        const CDTempInfo* pInfo = NULL;
        CDTimerData* pData = NULL;
        std::map<U32, CDTimerData*>::iterator iter = mCDTimerDataMapWork.find(ID);
        if ( iter != mCDTimerDataMapWork.end() )
        {
            pData = iter->second;
            pData->reset(liveTime, totalTime);
        }
        else
        {
            pInfo = CDTemplate::getInstance().getCDTempInfo(ID);
            DYNAMIC_ASSERT(pInfo);
            pData = new CDTimerData(pInfo, liveTime, totalTime);
            mCDTimerDataMapWork[ID] = pData;
        }
        
        return pData;
    }
    //------------------------------------------------------------------------------------------
    CDTimerData* CDTimer::removeTimer( U32 ID )
    {
        std::map<U32, CDTimerData*>::iterator iter = mCDTimerDataMapWork.find(ID);
        if ( iter != mCDTimerDataMapWork.end() )
        {
            iter->second->mLastTime = 0; 
			iter->second->mTotalTime = 0;
            return iter->second;
        } 
        return NULL;
    }
    //------------------------------------------------------------------------------------------
    void CDTimer::removeGroupTimer( U32 groupID, std::vector<CDTimerData*>& pTimerDataVector )
    {
        std::map<U32, CDTimerData*>::iterator front = mCDTimerDataMapWork.begin();
        std::map<U32, CDTimerData*>::iterator back = mCDTimerDataMapWork.end();
        while ( front != back )
        {
            if ( front->second->mCdtempInfo->TimepieceGroupId == groupID )
            {
                front->second->mLastTime = 0;
				front->second->mTotalTime = 0;
                pTimerDataVector.push_back(front->second);
            } 
            ++front;
        } 
    }
    //------------------------------------------------------------------------------------------
    void CDTimer::removeGroupTimer( U32 groupID )
    {
        std::map<U32, CDTimerData*>::iterator front = mCDTimerDataMapWork.begin();
        std::map<U32, CDTimerData*>::iterator back = mCDTimerDataMapWork.end();
        while ( front != back )
        {
            if ( front->second->mCdtempInfo->TimepieceGroupId == groupID )
            {
                front->second->mLastTime = 0;
				front->second->mTotalTime = 0;
            } 
            ++front;
        } 
    }
    //------------------------------------------------------------------------------------------
    MG::Bool CDTimer::ifGoing( U32 ID )
    {
        std::map<U32, CDTimerData*>::iterator iter = mCDTimerDataMapWork.find(ID);
        if ( iter != mCDTimerDataMapWork.end() )
        {
            if ( iter->second->mLastTime + iter->second->mStartTime  >  MGTimeOp::getCurrTick() )
                return true; 
        }
        return false;
    }
    //------------------------------------------------------------------------------------------
    CDTimerData* CDTimer::findTimer( U32 ID )
    {
        std::map<U32, CDTimerData*>::iterator iter = mCDTimerDataMapWork.find(ID);
        if ( iter != mCDTimerDataMapWork.end() )
        {
            return iter->second;
        }
        return NULL;
    }
    //------------------------------------------------------------------------------------------
    void CDTimer::clear()
    {
        std::map<U32, CDTimerData*>::iterator front = mCDTimerDataMapWork.begin();
        std::map<U32, CDTimerData*>::iterator back = mCDTimerDataMapWork.end();
        while ( front != back )
        {
            delete front->second;
            ++front;
        }
        mCDTimerDataMapWork.clear();
    }

    
}