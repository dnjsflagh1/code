/******************************************************************************/
#include "stdafx.h"
#include "GameNetPacketManager.h"
#include "GameNetPacketFilter.h"
#include "GameNetEventsHandler.h"
/******************************************************************************/

namespace MG
{
    //-----------------------------------------------------------------------------
    EventOneConnectHandler::EventOneConnectHandler()
        :mDisConnected(0)
        ,mDriverMgr(NULL)
        ,mPacketMgr(NULL)
        ,mPacketFilter(NULL)
    {
        
    }

    //-----------------------------------------------------------------------------
    void EventOneConnectHandler::initialize( Int id,GameNetDriverManager* mgr )
    {
        mDriverMgr      = mgr;
        mPacketMgr      = mDriverMgr->getManager();
        mPacketFilter   = mPacketMgr->getPacketFilter();
        mNetID          = id;
        mDisConnected   = 0;
    }

    //-----------------------------------------------------------------------------
    void EventOneConnectHandler::unInitialize()
    {
        clearEvents();
    }

}



