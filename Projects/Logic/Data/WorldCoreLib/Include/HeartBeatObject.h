/******************************************************************************/
#ifndef _HEARTBEATOBJECT_H_
#define _HEARTBEATOBJECT_H_
/******************************************************************************/

#include "WorldCorePreqs.h"
#include "LinedState.h"
#include "ObjectPool.h"

/******************************************************************************/

namespace MG
{


	/******************************************************************************/
	// ÐÄÌø¶ÔÏó
	/******************************************************************************/
	class HeartBeatObject
	{
	public:
		HeartBeatObject();
		virtual ~HeartBeatObject();
	
        virtual Bool    update( Flt delta ) = 0;

		void            startUpdate();
        void            stopUpdate();
        Bool            isStopUpdate();

        Bool            checkIntervalAndDoOneUpdate( Flt delta );

        void            setUpdateInterval( Flt interval );

    private:
        
        Flt     mUpdateInterval;
        Flt     mLastUpdateDuration;
        Flt     mCurrDuration;
        Bool    mIsStopUpdate;

	};
}


#endif	