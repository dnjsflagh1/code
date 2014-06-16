/******************************************************************************/
#ifndef _GAMENETDRIVERMANAGER_H_
#define _GAMENETDRIVERMANAGER_H_
/******************************************************************************/

#include "GameNetPreqs.h"
#include "GameNetEvent.h"
#include "Lock.h"
#include "ObjectPool.h"
#include "GameNetEventsHandler.h"
#include "GameNetN2LEventHandler.h"
#include "GameNetL2NEventHandler.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    // ��Ϸ��Ϣ������
    /******************************************************************************/

    // ���ò���
    struct GameNetDriveConfig
    {
        // ����һ�δ����������
        // handlePacketCount = ���������
        // -1,Ϊȫ������
        I32     OnceHandlePacketCount;

        // �ϲ����������
        I32     SendCombinePacketMaxSize;

        // �Ƿ��滻�����ڷ��Ͷ�
        Bool    ReplaceEnableInSendQueue;
        // �Ƿ��滻�����ڽ��ܶ�
        Bool    ReplaceEnableInRecvQueue;

        // �Ƿ��������ڷ��Ͷ�
        Bool    DiscardEnableInSendQueue;
        // �Ƿ��������ڽ��ܶ�
        Bool    DiscardEnableInRecvQueue;

        // �Ƿ������ȴ������ڷ��Ͷ�
        Bool    BlockWaitEnableInSendQueue;
        // �Ƿ������ȴ������ڽ��ܶ�
        Bool    BlockWaitEnableInRecvQueue;

        GameNetDriveConfig()
            :OnceHandlePacketCount(-1)
            ,SendCombinePacketMaxSize(1024)
            ,ReplaceEnableInSendQueue(false)
            ,ReplaceEnableInRecvQueue(false)
            ,DiscardEnableInSendQueue(false)
            ,DiscardEnableInRecvQueue(false)
            ,BlockWaitEnableInSendQueue(false)
            ,BlockWaitEnableInRecvQueue(false)
        {
        }
    };


    /******************************************************************************/
    // Drive�����¼����й�����
    /******************************************************************************/
    template<class T, class P>
    class EventOneDriveHandler
    {
        friend T;
        friend P;

    public:

        // ��������
        GameNetDriverManager* mMgr;

        //----------------------------------------------------------------------------------------

        /* 
            @ �����¼�����
            @ �����������ӱ�ŷ���
        */
        typedef std::map<I32, P, less<I32>, StlSoloAllocator<P>> NetConnectEventsMap;
        typedef std::list<P> NetConnectEventsList;

        // �����¼�������Map
        NetConnectEventsMap                         mNetConnectEventsMap;
        // �߳���
        RWLocker                                    mNetEventsMapCs;

        // �����¼�������List
        NetConnectEventsList                        mNetConnectEventsList;
        // �߳���
        Critical                                    mNetEventsListCs;

        //----------------------------------------------------------------------------------------

        // �����¼����ж����
        ObjectPool<T,false>                         mNetConnectEventsQueuePool;
        // �߳���
        Critical                                    mNetEventsPoolCs;
        
    public:

        //----------------------------------------------------------------------------------------
        EventOneDriveHandler()
            :mMgr(NULL)
        {
        }
		
        //----------------------------------------------------------------------------------------
        // ���ºͼ���¼��б������Ӷ�����
        //----------------------------------------------------------------------------------------
        virtual Int    checkAndUpdateEvents()
        {
            Int checkAndUpdateCount = 0;
            Bool isDestroyNetConnect = false;
            P ptr;

			NetConnectEventsMap::iterator mapIter;
			NetConnectEventsList::iterator listIter;
			mNetEventsListCs.lock();
			{
				listIter = mNetConnectEventsList.begin();
			}
			mNetEventsListCs.unlock();

            Bool isLoop = true;
            while( isLoop )
            {
                isDestroyNetConnect = false;

                mNetEventsListCs.lock();
                {
                    if ( listIter != mNetConnectEventsList.end() )
                    {
                        // get ptr
						
                        ptr = (*listIter);

                        // get destroy flag
                        isDestroyNetConnect = ptr->isDisConnected();

                        // erase in list
                        if ( isDestroyNetConnect )
                        {
                            listIter = mNetConnectEventsList.erase( listIter );
                        }else
                        {
                            listIter++;
                        }
                    }else
                    {
                        // quit on exceed count in list
                        mNetEventsListCs.unlock();
                        isLoop = false;
                        break;
                    }
                }
                mNetEventsListCs.unlock();


                if ( isDestroyNetConnect == false )
                {
                    // do
                    checkAndUpdateCount += ptr->checkAndUpdateEvents();
                }else
                {
                    // erase in map
                    mNetEventsMapCs.writeLock();
                    {
                        mapIter = mNetConnectEventsMap.find( ptr->getNetID() );
                        if ( mapIter != mNetConnectEventsMap.end() )
                        {
                            mNetConnectEventsMap.erase( mapIter );
                        }else
                        {
                            DYNAMIC_EEXCEPT_LOG( "EventOneDriveHandler:checkAndUpdateEvents : Not Find Handler In Map! " );
                        } 
                    }
                    mNetEventsMapCs.writeUnLock();
                }
            }

            // return handle event count
            return checkAndUpdateCount;
        }

        //----------------------------------------------------------------------------------------
        // ���������¼�������
        //----------------------------------------------------------------------------------------
        virtual P       createOneConnectEventHandler( I32 netid )
        {
            P   ptr;
            T*  point = NULL;
            NetConnectEventsList::iterator listIter;
            NetConnectEventsMap::iterator mapIter;

            // get ptr in map
            ptr = retrieveOneConnectEventHandler( netid, false );

            if ( ptr.isNull() == false )
            {
                DYNAMIC_EEXCEPT_LOG( "EventOneDriveHandler : Duplicate Handler In Map! " );
            }else
            {
                // get new point
                mNetEventsPoolCs.lock();
                {
                    point = MG_POOL_NEW_ONCE_CONSTRUCTION( mNetConnectEventsQueuePool , T, ());
                }
                mNetEventsPoolCs.unlock();

                // init
                {
                    point->initialize( netid, mMgr );
                    setExternalRecallManager( point );
                    ptr.bind( point );
                }

                // push in map
                mNetEventsMapCs.writeLock();
                {
                    mNetConnectEventsMap[ netid ] = ptr;
                }
                mNetEventsMapCs.writeUnLock();

                // push in list
                mNetEventsListCs.lock();
                {
                    mNetConnectEventsList.push_back(ptr);
                }
                mNetEventsListCs.unlock();
            }

            // return ptr
            return ptr;
        }

        //----------------------------------------------------------------------------------------
        // �õ������¼�������
        //----------------------------------------------------------------------------------------
        virtual P       retrieveOneConnectEventHandler( I32 netid, Bool isCheck = true )
        {
            P   ptr;
            NetConnectEventsMap::iterator mapIter;

            mNetEventsMapCs.readLock();
            {
                mapIter = mNetConnectEventsMap.find( netid );
                if ( mapIter != mNetConnectEventsMap.end() )
                {
                    ptr = mapIter->second;
                }else
                {
                    if ( isCheck )
                    {
                        DYNAMIC_EEXCEPT_LOG( "EventOneDriveHandler:retrieveOneConnectEventHandler : Not Find Handler In Map!! " );
                    }
                }
            }
            mNetEventsMapCs.readUnLock();

            return ptr;
        }

        //----------------------------------------------------------------------------------------
        // ���������¼�������
        //----------------------------------------------------------------------------------------
        virtual void    clearAllOneConnectEventHandler()
        {
            P ptr;
            NetConnectEventsList::iterator listIter;
            NetConnectEventsMap::iterator mapIter;

            mNetEventsListCs.lock();
            {
				NetConnectEventsList::iterator iter = mNetConnectEventsList.begin();
                for ( ; iter!=mNetConnectEventsList.end(); iter++ )
                {
                    recallOneConnectEventHandler( (*iter).getPointer() );
                }
                mNetConnectEventsList.clear();
            }
            mNetEventsListCs.unlock();

            mNetEventsMapCs.writeLock();
            {
                mNetConnectEventsMap.clear();
            }
            mNetEventsMapCs.writeUnLock();
        }

    protected:

        //----------------------------------------------------------------------------------------
        // ���������¼�������
        //----------------------------------------------------------------------------------------
        virtual void    recallOneConnectEventHandler( T* handler )
        {
            // uinit
            handler->unInitialize();

            // push in pool
            mNetEventsPoolCs.lock();
            {
                MG_POOL_DELETE_ONCE_DESTRUCTOR( mNetConnectEventsQueuePool , handler);
            }
            mNetEventsPoolCs.unlock();   
        }

        //----------------------------------------------------------------------------------------
        // �����ⲿ���������¼�������
        //----------------------------------------------------------------------------------------
        virtual void setExternalRecallManager( T* point ) = 0;

    };

    /******************************************************************************/
    // Logic 2 Net
    /******************************************************************************/
    class Logic2NetEventOneDriveHandler
         : public EventOneDriveHandler<Logic2NetEventFromOneConnectHandler,Logic2NetEventFromOneConnectHandlerPtr>
         , public ExternalRecallL2NManager
    {
    public:

        //----------------------------------------------------------------------------------------
        virtual void recall( Logic2NetEventFromOneConnectHandler* handler )
        {
            EventOneDriveHandler<Logic2NetEventFromOneConnectHandler,Logic2NetEventFromOneConnectHandlerPtr>::recallOneConnectEventHandler(handler);
        }

        //----------------------------------------------------------------------------------------
        virtual void setExternalRecallManager( Logic2NetEventFromOneConnectHandler* point )
        {
            point->mExternalRecallMgr = this;
        }
    };

    /******************************************************************************/
    // Net 2 Logic
    /******************************************************************************/
    class Net2LogicEventOneDriveHandler
        : public EventOneDriveHandler<Net2LogicEventFromOneConnectHandler,Net2LogicEventFromOneConnectHandlerPtr>
        , public ExternalRecallN2LManager
    {
    public:

        //----------------------------------------------------------------------------------------
        virtual void recall( Net2LogicEventFromOneConnectHandler* handler )
        {
            EventOneDriveHandler<Net2LogicEventFromOneConnectHandler,Net2LogicEventFromOneConnectHandlerPtr>::recallOneConnectEventHandler(handler);
        }

        //----------------------------------------------------------------------------------------
        virtual void setExternalRecallManager( Net2LogicEventFromOneConnectHandler* point )
        {
            point->mExternalRecallMgr = this;
        }
    };


    /******************************************************************************/
    // Drive�¼�������
    // ÿ��Driveӵ��һ��
    /******************************************************************************/
    class GameNetDriverManager
    {
        friend class GameNetPacketManager;
        friend class GameNetL2NEventDataFactory;

    public:
    
        GameNetDriverManager();

        void                            clear();

        void                            setActive( Bool active ){mActive=active;};
        Bool                            getActive(){ return mActive; };

        void                            setDriverID( I32 id ){mDriverID=id;};
        I32                             getDriverID(){ return mDriverID; };

        void                            setManager( GameNetPacketManager* mgr ){mMgr=mgr;};
        GameNetPacketManager*           getManager(){ return mMgr; };
        GameNetDriveConfig&             getConfig(){return mConfig;};

        Logic2NetEventOneDriveHandler&  getL2NHandler() { return mLogic2NetEventOneDriveHandler; };
        Net2LogicEventOneDriveHandler&  getN2LHandler() { return mNet2LogicEventOneDriveHandler; };

        // thread
        virtual void                    startThreadAutoHandle();
        virtual void                    endThreadAutoHandle();
        static  void                    checkAndUpdateL2NEvents( Ptr ptr );
        static  void                    checkAndUpdateN2LEvents( Ptr ptr );

    protected:

        I32                             mDriverID;

        OneThreadHandle                 mL2NThreadHandles;
        OneThreadHandle                 mN2LThreadHandles;

        Logic2NetEventOneDriveHandler   mLogic2NetEventOneDriveHandler;
        Net2LogicEventOneDriveHandler   mNet2LogicEventOneDriveHandler;

        // ��������
        Bool                            mActive;
        GameNetDriveConfig              mConfig;
        GameNetPacketManager*           mMgr;

    public:

        GameNetL2NEventDataFactory*     mGameNetL2NEventDataFactory;
    };


}


/******************************************************************************/

#endif


