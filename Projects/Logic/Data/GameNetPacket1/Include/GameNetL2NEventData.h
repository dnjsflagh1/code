/******************************************************************************/
#ifndef _GAMENETL2NEVENTDATA_H_
#define _GAMENETL2NEVENTDATA_H_
/******************************************************************************/

#include "GameNetPreqs.h"
#include "GameNetEvent.h"
#include "Lock.h"
#include "ObjectPool.h"

/******************************************************************************/

namespace MG
{

    //--------------------------------------------------------------------------------
    // Send Data Buff Smart Ptr
    //--------------------------------------------------------------------------------

    class GameNetSendDataBufferPtr : public SharedPtr<NetSendDataBuffer> 
    {
        friend class GameNetPacketManager;
        friend class GameNetL2NEventDataFactory;

    protected:

        GameNetL2NEventDataFactory* mFactory;
        DWORD                       mCreateThreadID;
		Bool						mIsCheckReduplicateSend;
        I32                         mNearestSendNetID;
        I32                         mLogicDataMaxSize;

    public:

        virtual ~GameNetSendDataBufferPtr() { release(); }
        GameNetSendDataBufferPtr() : SharedPtr<NetSendDataBuffer>(),mFactory(NULL),mCreateThreadID(0),mIsCheckReduplicateSend(true),mNearestSendNetID(-1),mLogicDataMaxSize(0) {}
        explicit GameNetSendDataBufferPtr(NetSendDataBuffer* rep) : SharedPtr<NetSendDataBuffer>(rep),mFactory(NULL),mCreateThreadID(0),mIsCheckReduplicateSend(true),mNearestSendNetID(-1),mLogicDataMaxSize(0) {}
        GameNetSendDataBufferPtr(const GameNetSendDataBufferPtr& r) : SharedPtr<NetSendDataBuffer>(r),mFactory(r.mFactory),mCreateThreadID(r.mCreateThreadID),mIsCheckReduplicateSend(r.mIsCheckReduplicateSend),mNearestSendNetID(r.mNearestSendNetID),mLogicDataMaxSize(r.mLogicDataMaxSize) {check();} 

        GameNetSendDataBufferPtr& operator=(const GameNetSendDataBufferPtr& r) 
        {
            if (pRep == r.pRep)
                return *this;

            GameNetSendDataBufferPtr tmp(r);
            if ( isNull() == false )
            {
                tmp.mFactory                = mFactory;
                tmp.mCreateThreadID         = mCreateThreadID;    
                tmp.mIsCheckReduplicateSend = mIsCheckReduplicateSend;
                tmp.mNearestSendNetID       = mNearestSendNetID;
                tmp.mLogicDataMaxSize       = mLogicDataMaxSize;
                tmp.mIsAllowDestroy         = mIsAllowDestroy;
            }

            swap(tmp);

			mFactory					= r.mFactory;
			mCreateThreadID				= r.mCreateThreadID;
			mIsCheckReduplicateSend		= r.mIsCheckReduplicateSend;
			mNearestSendNetID			= r.mNearestSendNetID;
			mLogicDataMaxSize			= r.mLogicDataMaxSize;
			mIsAllowDestroy		        = r.mIsAllowDestroy; 

			check();

            return *this;
        }

    protected:

        virtual void                        destroy(void);
        virtual void                        setCheckReduplicateSend(Bool isChecked);
        virtual void                        check();
    };


    //--------------------------------------------------------------------------------
    //  Once Send Config Smart Ptr
    //--------------------------------------------------------------------------------

    class GameNetOnceSendConfigPtr : public SharedPtr<NetOnceSendConfig> 
    {
        friend class GameNetL2NEventDataFactory;

    protected:

        GameNetL2NEventDataFactory* mFactory;
        DWORD                       mCreateThreadID;
        
    public:

        virtual ~GameNetOnceSendConfigPtr() { release(); }
        GameNetOnceSendConfigPtr() : SharedPtr<NetOnceSendConfig>(),mFactory(NULL),mCreateThreadID(0) {}
        explicit GameNetOnceSendConfigPtr(NetOnceSendConfig* rep) : SharedPtr<NetOnceSendConfig>(rep),mFactory(NULL),mCreateThreadID(0) {}
        GameNetOnceSendConfigPtr(const GameNetOnceSendConfigPtr& r) : SharedPtr<NetOnceSendConfig>(r),mFactory(r.mFactory),mCreateThreadID(r.mCreateThreadID) {} 
        GameNetOnceSendConfigPtr& operator=(const GameNetOnceSendConfigPtr& r) 
        {
            if (pRep == r.pRep)
                return *this;

            GameNetOnceSendConfigPtr tmp(r);
            if ( isNull() == false )
            {
				tmp.mFactory        = mFactory;
				tmp.mCreateThreadID = mCreateThreadID;
            }
            
            swap(tmp);

			mFactory        = r.mFactory;
			mCreateThreadID = r.mCreateThreadID;

            return *this;
        }

    protected:    
            
        virtual void destroy(void);

    };


    /******************************************************************************/
    // Logic2Net游戏数据工厂
    /******************************************************************************/
    class GameNetL2NEventDataFactory
    {
        friend class GameNetPacketManager;
    public:

        GameNetL2NEventDataFactory(GameNetDriverManager* mgr);
        virtual~GameNetL2NEventDataFactory();

        void                                switchObjectPool();
        void                                clear();

    protected:

        GameNetDriverManager* mDriverMgr;
 
    protected:

        struct GameNetSendDataBufferPool
        {
            std::deque<NetSendDataBuffer*>  m_IdleBigObjectList;
            std::deque<NetSendDataBuffer*>  m_IdleNormalObjectList;

            Critical mPoolCs;
        };

        struct GameNetSendDataBufferPoolManager
        {
            DWORD                       mThreadID;

            GameNetSendDataBufferPtr    mNearestCreatePtr;
			GameNetSendDataBufferPtr    mNearestSendPtr;

            GameNetSendDataBufferPool*  m_CreateObjectList;
            GameNetSendDataBufferPool*  m_DestroyObjectList;

            GameNetSendDataBufferPool   m_IdleObjectList1;
            GameNetSendDataBufferPool   m_IdleObjectList2;

            UInt                        mCreateCount;
            UInt                        mDestroyCount;
        };

        Critical                                        mThreadGameNetSendDataBufferPoolCs;
        std::vector<GameNetSendDataBufferPoolManager*>  mThreadGameNetSendDataBufferPool;

    protected:

        struct GameNetOnceSendConfigPool
        {
            std::deque<NetOnceSendConfig*>  m_IdleObjectList;
            Critical mPoolCs;
        };

        struct GameNetOnceSendConfigPoolManager
        {
            DWORD                       mThreadID;

            GameNetOnceSendConfigPtr    mNearestCreatePtr;

            GameNetOnceSendConfigPool*  m_CreateObjectList;
            GameNetOnceSendConfigPool*  m_DestroyObjectList;

            GameNetOnceSendConfigPool   m_IdleObjectList1;
            GameNetOnceSendConfigPool   m_IdleObjectList2;

            UInt                        mCreateCount;
            UInt                        mDestroyCount;
        };

        Critical                                        mThreadGameNetOnceSendConfigPoolCs;
        std::vector<GameNetOnceSendConfigPoolManager*>  mThreadGameNetOnceSendConfigPool;

    public:

        GameNetSendDataBufferPoolManager*   createOrRetrieveGameNetSendDataBufferPoolManager( UInt threadID );
        GameNetSendDataBufferPoolManager*   retrieveGameNetSendDataBufferPoolManager( UInt threadID );

        void                                createGameNetSendDataBufferPtr(GameNetSendDataBufferPtr& ptr, U32 buffSize = MG_NET_DEFAULT_SEND_BUFFER_SIZE);
        void                                cloneGameNetSendDataBufferPtr(GameNetSendDataBufferPtr& srcPtr, GameNetSendDataBufferPtr& desPtr, Bool isCopyHeader);
        void                                cloneGameNetSendDataBufferPtr(GameNetSendDataBufferPtr& srcPtr, GameNetSendDataBufferPtr& desPtr, UInt cloneSize);
		
        void                                destroyGameNetSendDataBufferPtr(GameNetSendDataBufferPtr& ptr);
        void                                destroyAllGameNetSendDataBufferPtr();

		void								setNearestSendedGameNetSendDataBufferPtr(GameNetSendDataBufferPtr& ptr);

        void                                switchGameNetSendDataBufferPool();


        GameNetOnceSendConfigPoolManager*   createOrRetrieveGameNetOnceSendConfigPoolManager( UInt threadID );
        GameNetOnceSendConfigPoolManager*   retrieveGameNetOnceSendConfigPoolManager( UInt threadID );

        void                                createGameNetOnceSendConfigPtr(GameNetOnceSendConfigPtr& ptr, I32 driverID, I32 netID, I32 sendID);
        void                                destroyGameNetOnceSendConfigPtr(GameNetOnceSendConfigPtr& ptr);
        void                                destroyAllGameNetOnceSendConfigPtr();
        void                                switchGameNetOnceSendConfigPool();
    };

 




}

/******************************************************************************/

#endif