/******************************************************************************/
#ifndef _GAMENETL2NEVENTHANDLER_H_
#define _GAMENETL2NEVENTHANDLER_H_
/******************************************************************************/

#include "GameNetPreqs.h"
#include "GameNetEvent.h"
#include "Lock.h"
#include "ObjectPool.h"
#include "GameNetEventsHandler.h"
#include "GameNetL2NEventData.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    // Logic2Net游戏消息处理者
    // 每个网络连接拥有一份
    /******************************************************************************/

    class Logic2NetEventFromOneConnectHandler : public EventOneConnectHandler
    {
    public:

        Logic2NetEventFromOneConnectHandler();

        //--------------------------------------------------------------------------------
        // 网络层事件
        //--------------------------------------------------------------------------------


		virtual void        initialize( Int id,GameNetDriverManager* mgr );
		virtual void        unInitialize();


        virtual	void	    addAcceptEvent(I32 handle,I32 id,NetAddress&address);
        virtual	void	    addConnectEvent(I32 handle,I32 id,NetAddress&address);
        virtual	void	    addCloseEvent(I32 handle,I32 id,Bool isPassivity,NetAddress&address);
        void                addSendEvent( NetOnceSendConfig* config );
        virtual void        clearEvents();

        virtual void        freeEvent( INetEvent* netEvent );

	protected:

		// 等待发送
		InterLocked         mCloseEvent;

        //--------------------------------------------------------------------------------
        // 来自逻辑层的预备发送逻辑
        //--------------------------------------------------------------------------------

    protected:

        // 准备发送队列
        std::deque<GameNetSendDataBufferPtr>        mPrepareSendEventsQueue;
        Critical                                    mPrepareSendEventsQueueCs;

    public:

        // 增加准备发送事件
        void                addPrepareSendEvent( GameNetSendDataBufferPtr& ptr );

    protected:

        void                clearPrepareSendEvent();

        //--------------------------------------------------------------------------------
        // 单个发送事件对象逻辑
        //--------------------------------------------------------------------------------

    protected:

        struct OnceSendEvents
        {
            std::vector<GameNetSendDataBufferPtr>   mSendEventsQueue;
            Int                                     mSendCombinePacketSize;
			Int                                     mSendCombinePacketCount;
            Int                                     mSendID;
            GameNetOnceSendConfigPtr                mGameNetOnceSendConfig;

            OnceSendEvents();
            virtual ~OnceSendEvents();

            Bool    checkAndAddOrIgnore( GameNetSendDataBufferPtr& ptr, U32 maxSendSize );
            void    clear();
            Bool    isEmpty();
        };
        Critical                                    mOnceSendEventsPoolCs;
        ObjectPool<OnceSendEvents,true>             mOnceSendEventsPool;
        // 发送编号
        InterLocked                                 mSendNumber;

        OnceSendEvents* createOnceSendEvents();
        void            destroyOnceSendEvents( OnceSendEvents* events );

        //--------------------------------------------------------------------------------
        // 主处理发送网络层逻辑
        //--------------------------------------------------------------------------------

    public:

        virtual Int     checkAndUpdateEvents();

    protected:

        OnceSendEvents*     mCurrSendEvents;
        // 等待发送
        InterLocked         mWaitSend;


        //--------------------------------------------------------------------------------
        // 来自网络层的发送回应逻辑
        //--------------------------------------------------------------------------------

    protected:

        // 等待发送回应队列
        typedef std::map<I32, OnceSendEvents*
            ,less<I32>, 
            StlSoloAllocator<OnceSendEvents*>>	    WaitSendResponseEventsMap;  
        WaitSendResponseEventsMap                   mWaitSendResponseEventsQueue;
        Critical                                    mWaitSendResponseEventsQueueCs;
      
        // 增加发送事件
        void                addWaitSendResponseEvent( OnceSendEvents* events );
        void                removeWaitSendResponseEvent( I32 sendID );
        void                clearWaitSendResponseEvent();

        //--------------------------------------------------------------------------------
        // 其他参数
        //--------------------------------------------------------------------------------

    public:

        ExternalRecallL2NManager*                   mExternalRecallMgr;

    };



    /******************************************************************************/
    // Logic2Net游戏消息处理者智能指针
    // 每个网络连接拥有一份
    /******************************************************************************/
    class ExternalRecallL2NManager
    {
    public:
        virtual void recall( Logic2NetEventFromOneConnectHandler* handler ) = 0;
    };

    class Logic2NetEventFromOneConnectHandlerPtr : public SharedPtr<Logic2NetEventFromOneConnectHandler> 
    {
    public:
        virtual ~Logic2NetEventFromOneConnectHandlerPtr(){ release(); }
        Logic2NetEventFromOneConnectHandlerPtr() : SharedPtr<Logic2NetEventFromOneConnectHandler>() {}
        explicit Logic2NetEventFromOneConnectHandlerPtr(Logic2NetEventFromOneConnectHandler* rep) : SharedPtr<Logic2NetEventFromOneConnectHandler>(rep){}
        Logic2NetEventFromOneConnectHandlerPtr(const Logic2NetEventFromOneConnectHandlerPtr& r) : SharedPtr<Logic2NetEventFromOneConnectHandler>(r) {} 
        virtual void destroy(void)
        {
            Logic2NetEventFromOneConnectHandler* pointer = getPointer();
            ExternalRecallL2NManager* mgr = pointer->mExternalRecallMgr;
            mgr->recall( pointer );
        }
        Logic2NetEventFromOneConnectHandlerPtr& operator=(const Logic2NetEventFromOneConnectHandlerPtr& r) 
        {
            if (pRep == r.pRep)
                return *this;
            Logic2NetEventFromOneConnectHandlerPtr tmp(r);
            swap(tmp);
            return *this;
        }
    };

    







}

/******************************************************************************/

#endif