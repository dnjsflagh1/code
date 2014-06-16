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
    // Logic2Net��Ϸ��Ϣ������
    // ÿ����������ӵ��һ��
    /******************************************************************************/

    class Logic2NetEventFromOneConnectHandler : public EventOneConnectHandler
    {
    public:

        Logic2NetEventFromOneConnectHandler();

        //--------------------------------------------------------------------------------
        // ������¼�
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

		// �ȴ�����
		InterLocked         mCloseEvent;

        //--------------------------------------------------------------------------------
        // �����߼����Ԥ�������߼�
        //--------------------------------------------------------------------------------

    protected:

        // ׼�����Ͷ���
        std::deque<GameNetSendDataBufferPtr>        mPrepareSendEventsQueue;
        Critical                                    mPrepareSendEventsQueueCs;

    public:

        // ����׼�������¼�
        void                addPrepareSendEvent( GameNetSendDataBufferPtr& ptr );

    protected:

        void                clearPrepareSendEvent();

        //--------------------------------------------------------------------------------
        // ���������¼������߼�
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
        // ���ͱ��
        InterLocked                                 mSendNumber;

        OnceSendEvents* createOnceSendEvents();
        void            destroyOnceSendEvents( OnceSendEvents* events );

        //--------------------------------------------------------------------------------
        // ��������������߼�
        //--------------------------------------------------------------------------------

    public:

        virtual Int     checkAndUpdateEvents();

    protected:

        OnceSendEvents*     mCurrSendEvents;
        // �ȴ�����
        InterLocked         mWaitSend;


        //--------------------------------------------------------------------------------
        // ���������ķ��ͻ�Ӧ�߼�
        //--------------------------------------------------------------------------------

    protected:

        // �ȴ����ͻ�Ӧ����
        typedef std::map<I32, OnceSendEvents*
            ,less<I32>, 
            StlSoloAllocator<OnceSendEvents*>>	    WaitSendResponseEventsMap;  
        WaitSendResponseEventsMap                   mWaitSendResponseEventsQueue;
        Critical                                    mWaitSendResponseEventsQueueCs;
      
        // ���ӷ����¼�
        void                addWaitSendResponseEvent( OnceSendEvents* events );
        void                removeWaitSendResponseEvent( I32 sendID );
        void                clearWaitSendResponseEvent();

        //--------------------------------------------------------------------------------
        // ��������
        //--------------------------------------------------------------------------------

    public:

        ExternalRecallL2NManager*                   mExternalRecallMgr;

    };



    /******************************************************************************/
    // Logic2Net��Ϸ��Ϣ����������ָ��
    // ÿ����������ӵ��һ��
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