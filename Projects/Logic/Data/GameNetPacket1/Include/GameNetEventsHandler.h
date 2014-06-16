/******************************************************************************/
#ifndef _GAMENETEVENTSHANDLER_H_
#define _GAMENETEVENTSHANDLER_H_
/******************************************************************************/

#include "GameNetPreqs.h"
#include "GameNetEvent.h"
#include "Lock.h"
#include "ObjectPool.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    // 游戏消息处理者
    /******************************************************************************/

    // 单连接事件处理基类
    class EventOneConnectHandler : public INetEventPool
    {
    public:

        EventOneConnectHandler();

        Int                     getNetID( ){return mNetID;};
        GameNetDriverManager*   getDriverManager(){return mDriverMgr;};
        GameNetPacketManager*   getPacketManager(){return mPacketMgr;};
        GameNetPacketFilter*    getPacketFilter(){return mPacketFilter;};

        virtual void            disConnected(){mDisConnected=1;};
        virtual Bool            isDisConnected(){return mDisConnected > 0;};

        virtual void            initialize( Int id,GameNetDriverManager* mgr );
        virtual void            unInitialize();

        virtual Int             checkAndUpdateEvents() = 0;
        virtual void            clearEvents() = 0;

    protected:

        GameNetDriverManager* mDriverMgr;
        GameNetPacketManager* mPacketMgr;
        GameNetPacketFilter*  mPacketFilter;
        Int mNetID;
        InterLocked mDisConnected;

    };

    
}

/******************************************************************************/

#endif

