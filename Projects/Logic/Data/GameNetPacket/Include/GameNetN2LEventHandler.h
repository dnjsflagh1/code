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
    // Net2Logic��Ϸ��Ϣ������
    // ÿ����������ӵ��һ��
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

        // �����¼�
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

        // �����¼����кͶ����
        struct NetEventsQueueAndPool
        {
            // ����
            // TODO: �޸ĳ�Ԥ������������
            std::deque<INetEvent*>                  mNetEventsQueue;
            Critical                                mNetEventsQueueCs;

            // �����
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
        
        // �Ƿ��л����кͻ����
        Bool                                        mIsSwapQueueAndPool;
        // ���ܶ��кͶ����
        NetEventsQueueAndPool*                      mAddedNetEventsQueue;
        // ������кͶ����
        NetEventsQueueAndPool*                      mHandlerNetEventsQueue;

        // ���кͶ����1
        NetEventsQueueAndPool                       mNetEventsQueueAndPool1;
        // ���кͶ����2
        NetEventsQueueAndPool                       mNetEventsQueueAndPool2;

        // �����ⲿ�ͷ��¼��������ʱ�������
        // TODO: �޸ĳ�Ԥ������������
        std::deque<INetEvent*>                      mNetEventFreePool;
        Critical                                    mNetEventsFreePoolCs;


    //**************************************************************************************
    //**************************************************************************************

    protected:

        //--------------------------------------------------------------------------------
        // ��Ч�Բ���
        //--------------------------------------------------------------------------------
        Bool                checkPacketValid(I32 handle,I32 id, Char8* buff, I32 buffLen);

        //--------------------------------------------------------------------------------
        // �滻����
        //--------------------------------------------------------------------------------
        NetEventRecv*       checkPacketReplace(I32 handle,I32 id, Char8* buff, I32 buffLen);

        //--------------------------------------------------------------------------------
        // ��������
        //--------------------------------------------------------------------------------
        Bool                checkPacketDiscard(I32 handle,I32 id, Char8* buff, I32 buffLen);
        
        //--------------------------------------------------------------------------------
        // ��ֹ��������
        //--------------------------------------------------------------------------------
        Bool                checkPacketAttacked(I32 handle,I32 id, Char8* buff, I32 buffLen);

        //--------------------------------------------------------------------------------
        // ��Ҳ���
        //--------------------------------------------------------------------------------
        Bool                checkPacketCheatPlug(I32 handle,I32 id, Char8* buff, I32 buffLen);
        
        //--------------------------------------------------------------------------------
        // �ȴ��������
        //--------------------------------------------------------------------------------

        // �Ƿ���������
        Bool                checkPacketBlockHandle();
        // ִ��һ�������ȴ�����
        void                pushOneWaitHandle(I32 handle,I32 id, Char8* buff, I32 buffLen);
        // ���յ���Ӧ�¼�
        void                onReplyHandleEvents(I32 handle,I32 id, Char8* buff, I32 buffLen);


    //**************************************************************************************
    //**************************************************************************************

    protected:

        //--------------------------------------------------------------------------------
        // Event Handle
        //--------------------------------------------------------------------------------

        // �����¼�����
        void                swapEventsQueueAndPool();

        // ��⴦��͹ر��¼�
        void                handleEvents( INetEvent* netEvent );


    //**************************************************************************************
    //**************************************************************************************

    protected:

        //--------------------------------------------------------------------------------
        // Event Clear
        //--------------------------------------------------------------------------------

        // ����¼�
        virtual void        clearEvents();
        // ����¼�����
        virtual void        clearEventsQueueAndPool(NetEventsQueueAndPool* eqp);
        // �����¼� 
        virtual void        recallEvent( INetEvent* netEvent, NetEventsQueueAndPool* eqp, Bool isLock );

        // �����ⲿ���¼�,����recallEvent
        virtual void        recallFreeEvents(Bool isTryLock,NetEventsQueueAndPool* eqp);

        // �ͷ��¼�,һ�����߼����̵߳��� 
        virtual void        freeEvent( INetEvent* netEvent );


    };

    /******************************************************************************/
    // Net2Logic��Ϸ��Ϣ����������ָ��
    // ÿ����������ӵ��һ��
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