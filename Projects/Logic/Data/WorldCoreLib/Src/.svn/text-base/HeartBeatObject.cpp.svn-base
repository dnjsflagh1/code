/******************************************************************************/
#include "stdafx.h"
#include "HeartBeatObject.h"
/******************************************************************************/
namespace MG
{

	//--------------------------------------------------------------------------
	HeartBeatObject::HeartBeatObject()
        :mIsStopUpdate(false)
        ,mUpdateInterval(1)
        ,mLastUpdateDuration(0)
        ,mCurrDuration(0)
	{
	}

	//--------------------------------------------------------------------------
	HeartBeatObject::~HeartBeatObject()
	{
	}

    //--------------------------------------------------------------------------
    void HeartBeatObject::startUpdate()
    {
        mIsStopUpdate       = false;
        mLastUpdateDuration = 0;
        mCurrDuration       = 0;
    }

    //--------------------------------------------------------------------------
    void HeartBeatObject::stopUpdate()
    {
        mIsStopUpdate = true;
    }

    //--------------------------------------------------------------------------
    Bool HeartBeatObject::isStopUpdate()
    {
        return mIsStopUpdate;
    }   

    //--------------------------------------------------------------------------
    Bool HeartBeatObject::checkIntervalAndDoOneUpdate( Flt delta )
    {
        mCurrDuration += delta;
        Flt duration = mCurrDuration - mLastUpdateDuration;

        if ( duration >= mUpdateInterval )
        {
            mLastUpdateDuration = mCurrDuration;

            return update( duration );
        }

        return false;
    }

    //--------------------------------------------------------------------------
    void HeartBeatObject::setUpdateInterval( Flt interval )
    {
        mUpdateInterval = interval;
    }
}