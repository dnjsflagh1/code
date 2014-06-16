/******************************************************************************/
#ifndef _GAMENETN2LEVENTHANDLER_H_
#define _GAMENETN2LEVENTHANDLER_H_
/******************************************************************************/

#include "GameNetPreqs.h"
#include "GameNetEvent.h"
#include "Lock.h"
#include "ObjectPool.h"

/******************************************************************************/

namespace MG
{


    /******************************************************************************/
    // Net2Logic游戏消息处理者
    // 每个网络连接拥有一份
    /******************************************************************************/

    class Net2LogicEventFromOneConnectHandler : public EventOneConnectHandler
    {
    public:

        Net2LogicEventFromOneConnectHandler();

        virtual void        initialize( Int id,GameNetDriverManager* mgr );
        virtual void        unInitialize();
        virtual Int         checkAndUpdateEvents();

    //**************************************************************************************
    //**************************************************************************************

    public:

        //--------------------------------------------------------------------------------
        // Net Event
        //--------------------------------------------------------------------------------

        // 增加事件
        virtual	void	    addAcceptEvent(I32 handle,I32 id,NetAddress&address);
        virtual	void	    addConnectEvent(I32 handle,I32 id,NetAddress&address);
        virtual	void	    addCloseEvent(I32 handle,I32 id,Bool isPassivity,NetAddress&address);
        virtual	void	    addRecvEvent(I32 handle,I32 id, Char8* buff, I32 buffLen);
        virtual	void	    addErrEvent(I32 handle,I32 id);


    //**************************************************************************************
    //**************************************************************************************

    public:

        // Mgr
        ExternalRecallN2LManager*   mExternalRecallMgr;

    protected:

        // 网络事件队列和对象池
        struct NetEventsQueueAndPool
        {
            // 队列
            // TODO: 修改成预设容量的容器
            std::deque<INetEvent*>                  mNetEventsQueue;
            Critical                                mNetEventsQueueCs;

            // 对象池
            ObjectPool<NetEventAccept,false>        mNetEventAcceptPool;
            ObjectPool<NetEventConnect,false>       mNetEventConnectPool;
            ObjectPool<NetEventClose,false>         mNetEventClosePool;
            ObjectPool<NetEventRecv,false>          mNetEventNormalRecvPool;
            ObjectPool<NetEventRecv,false>          mNetEventBigRecvPool;
            ObjectPool<NetEventErr,false>           mNetEventErrPool;
            Critical                                mNetEventsPoolCs;

            NetEventsQueueAndPool()
            {
                mNetEventAcceptPool.setCheckExceptEnable(false);
                mNetEventConnectPool.setCheckExceptEnable(false);
                mNetEventClosePool.setCheckExceptEnable(false);
                mNetEventNormalRecvPool.setCheckExceptEnable(false);
                mNetEventBigRecvPool.setCheckExceptEnable(false);
                mNetEventErrPool.setCheckExceptEnable(false);
            }
        };
        
        // 是否切换队列和缓存池
        Bool                                        mIsSwapQueueAndPool;
        // 接受队列和对象池
        NetEventsQueueAndPool*                      mAddedNetEventsQueue;
        // 处理队列和对象池
        NetEventsQueueAndPool*                      mHandlerNetEventsQueue;

        // 队列和对象池1
        NetEventsQueueAndPool                       mNetEventsQueueAndPool1;
        // 队列和对象池2
        NetEventsQueueAndPool                       mNetEventsQueueAndPool2;

        // 回收外部释放事件对象的临时保存队列
        // TODO: 修改成预设容量的容器
        std::deque<INetEvent*>                      mNetEventFreePool;
        Critical                                    mNetEventsFreePoolCs;


    //**************************************************************************************
    //**************************************************************************************

    protected:

        //--------------------------------------------------------------------------------
        // 有效性策略
        //--------------------------------------------------------------------------------
        Bool                checkPacketValid(I32 handle,I32 id, Char8* buff, I32 buffLen);

        //--------------------------------------------------------------------------------
        // 替换策略
        //--------------------------------------------------------------------------------
        NetEventRecv*       checkPacketReplace(I32 handle,I32 id, Char8* buff, I32 buffLen);

        //--------------------------------------------------------------------------------
        // 丢弃策略
        //--------------------------------------------------------------------------------
        Bool                checkPacketDiscard(I32 handle,I32 id, Char8* buff, I32 buffLen);
        
        //--------------------------------------------------------------------------------
        // 防止攻击策略
        //--------------------------------------------------------------------------------
        Bool                checkPacketAttacked(I32 handle,I32 id, Char8* buff, I32 buffLen);

        //--------------------------------------------------------------------------------
        // 外挂策略
        //--------------------------------------------------------------------------------
        Bool                checkPacketCheatPlug(I32 handle,I32 id, Char8* buff, I32 buffLen);
        
        //--------------------------------------------------------------------------------
        // 等待处理策略
        //--------------------------------------------------------------------------------

        // 是否阻塞处理
        Bool                checkPacketBlockHandle();
        // 执行一条阻塞等待处理
        void                pushOneWaitHandle(I32 handle,I32 id, Char8* buff, I32 buffLen);
        // 当收到回应事件
        void                onReplyHandleEvents(I32 handle,I32 id, Char8* buff, I32 buffLen);


    //**************************************************************************************
    //**************************************************************************************

    protected:

        //--------------------------------------------------------------------------------
        // Event Handle
        //--------------------------------------------------------------------------------

        // 交换事件队列
        void                swapEventsQueueAndPool();

        // 检测处理和关闭事件
        void                handleEvents( INetEvent* netEvent );


    //**************************************************************************************
    //**************************************************************************************

    protected:

        //--------------------------------------------------------------------------------
        // Event Clear
        //--------------------------------------------------------------------------------

        // 清空事件
        virtual void        clearEvents();
        // 清空事件队列
        virtual void        clearEventsQueueAndPool(NetEventsQueueAndPool* eqp);
        // 回收事件 
        virtual void        recallEvent( INetEvent* netEvent, NetEventsQueueAndPool* eqp, Bool isLock );

        // 回收外部的事件,调用recallEvent
        virtual void        recallFreeEvents(Bool isTryLock,NetEventsQueueAndPool* eqp);

        // 释放事件,一般由逻辑层线程调用 
        virtual void        freeEvent( INetEvent* netEvent );


    };

    /******************************************************************************/
    // Net2Logic游戏消息处理者智能指针
    // 每个网络连接拥有一份
    /******************************************************************************/
    class ExternalRecallN2LManager
    {
    public:

        virtual void recall( Net2LogicEventFromOneConnectHandler* handler ) = 0;
    };

    class Net2LogicEventFromOneConnectHandlerPtr : public SharedPtr<Net2LogicEventFromOneConnectHandler> 
    {
    public:

        virtual ~Net2LogicEventFromOneConnectHandlerPtr(){ release(); }
        Net2LogicEventFromOneConnectHandlerPtr() : SharedPtr<Net2LogicEventFromOneConnectHandler>() {}
        explicit Net2LogicEventFromOneConnectHandlerPtr(Net2LogicEventFromOneConnectHandler* rep) : SharedPtr<Net2LogicEventFromOneConnectHandler>(rep){}
        Net2LogicEventFromOneConnectHandlerPtr(const Net2LogicEventFromOneConnectHandlerPtr& r) : SharedPtr<Net2LogicEventFromOneConnectHandler>(r) {} 
        virtual void destroy(void)
        {
            Net2LogicEventFromOneConnectHandler* pointer = getPointer();
            ExternalRecallN2LManager* mgr = pointer->mExternalRecallMgr;
            mgr->recall( pointer );
        }
        Net2LogicEventFromOneConnectHandlerPtr& operator=(const Net2LogicEventFromOneConnectHandlerPtr& r) 
        {
            if (pRep == r.pRep)
                return *this;
            Net2LogicEventFromOneConnectHandlerPtr tmp(r);
            swap(tmp);
            return *this;
        }
    };
}

/******************************************************************************/

#endif