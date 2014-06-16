/******************************************************************************/
#include "stdafx.h"
#include "GameNetPacketManager.h"
#include "GameNetL2NEventData.h"
/******************************************************************************/

namespace MG
{
    
    //--------------------------------------------------------------------------------
    // Send Data Buff Smart Ptr
    //--------------------------------------------------------------------------------
    
    void GameNetSendDataBufferPtr::destroy(void)
    {
        mFactory->destroyGameNetSendDataBufferPtr( *this );
    }

	//--------------------------------------------------------------------------------
	void GameNetSendDataBufferPtr::setCheckReduplicateSend(Bool isChecked)
	{
		mIsCheckReduplicateSend = isChecked;
	}

	//--------------------------------------------------------------------------------
	void GameNetSendDataBufferPtr::check()
	{
#ifdef _DEBUG

		if ( isNull() == false )
		{
			if ( getPointer()->getLogicDataMaxSize() > mLogicDataMaxSize )
			{
				DYNAMIC_EEXCEPT_LOG("ptr.mLogicDataMaxSize is diff ptr->getLogicDataMaxSize()!");
				DYNAMIC_ASSERT(false);
			}
		}
#endif
	}

    //--------------------------------------------------------------------------------
    //  Once Send Config Smart Ptr
    //--------------------------------------------------------------------------------

    void GameNetOnceSendConfigPtr::destroy(void)
    {
        mFactory->destroyGameNetOnceSendConfigPtr( *this );
    }


    /******************************************************************************/
    // Logic2Net游戏数据工厂
    /******************************************************************************/


    //--------------------------------------------------------------------------------
    GameNetL2NEventDataFactory::GameNetL2NEventDataFactory(GameNetDriverManager* mgr)
        :mDriverMgr(mgr)
    {
        mThreadGameNetSendDataBufferPool.reserve(100);
        mThreadGameNetOnceSendConfigPool.reserve(100);
    }

    //--------------------------------------------------------------------------------
    GameNetL2NEventDataFactory::~GameNetL2NEventDataFactory()
    {
    }

    //--------------------------------------------------------------------------------
    void GameNetL2NEventDataFactory::switchObjectPool()
    {
        switchGameNetSendDataBufferPool();
        switchGameNetOnceSendConfigPool();
    }

    //--------------------------------------------------------------------------------
    void GameNetL2NEventDataFactory::clear()
    {
        destroyAllGameNetSendDataBufferPtr();
        destroyAllGameNetOnceSendConfigPtr();
    }

    //--------------------------------------------------------------------------------
    void GameNetL2NEventDataFactory::switchGameNetSendDataBufferPool()
    {
        // swap when empty in handler queue
        mThreadGameNetSendDataBufferPoolCs.lock();
        {
            Int count  = mThreadGameNetSendDataBufferPool.size();
            for ( Int i=0; i < count ; i++ )
            {
                GameNetSendDataBufferPoolManager* mgr = mThreadGameNetSendDataBufferPool[i];

                GameNetSendDataBufferPool* pool1 = mgr->m_CreateObjectList;
                GameNetSendDataBufferPool* pool2 = mgr->m_DestroyObjectList;
                
                pool1->mPoolCs.lock();
                {
                    pool2->mPoolCs.lock();
                    {
                        GameNetSendDataBufferPool*  swapObj = mgr->m_CreateObjectList;
                        mgr->m_CreateObjectList  =   mgr->m_DestroyObjectList;
                        mgr->m_DestroyObjectList =   swapObj;
                    }
                    pool2->mPoolCs.unlock();
                }
                pool1->mPoolCs.unlock();

            }
        }
        mThreadGameNetSendDataBufferPoolCs.unlock();
    }
    
    //--------------------------------------------------------------------------------
    void GameNetL2NEventDataFactory::switchGameNetOnceSendConfigPool()
    {
        mThreadGameNetOnceSendConfigPoolCs.lock();
        {
            Int count  = mThreadGameNetOnceSendConfigPool.size();
            for ( Int i=0; i < count ; i++ )
            {
                GameNetOnceSendConfigPoolManager* mgr = mThreadGameNetOnceSendConfigPool[i];

                GameNetOnceSendConfigPool* pool1 = mgr->m_CreateObjectList;
                GameNetOnceSendConfigPool* pool2 = mgr->m_DestroyObjectList;

                pool1->mPoolCs.lock();
                {
                    pool2->mPoolCs.lock();
                    {
                        GameNetOnceSendConfigPool*  swapObj = mgr->m_CreateObjectList;
                        mgr->m_CreateObjectList  =   mgr->m_DestroyObjectList;
                        mgr->m_DestroyObjectList =   swapObj;
                    }
                    pool2->mPoolCs.unlock();
                }
                pool1->mPoolCs.unlock();

            }
        }
        mThreadGameNetOnceSendConfigPoolCs.unlock();
    }

    //--------------------------------------------------------------------------------
    GameNetL2NEventDataFactory::GameNetSendDataBufferPoolManager* GameNetL2NEventDataFactory::createOrRetrieveGameNetSendDataBufferPoolManager( UInt threadID )
    {
        GameNetL2NEventDataFactory::GameNetSendDataBufferPoolManager* matchMgr  = retrieveGameNetSendDataBufferPoolManager( threadID );

        if ( matchMgr == NULL )
        {
            matchMgr = MG_NEW GameNetL2NEventDataFactory::GameNetSendDataBufferPoolManager();

            matchMgr->mThreadID             = threadID;
            matchMgr->m_CreateObjectList    = &matchMgr->m_IdleObjectList1;
            matchMgr->m_DestroyObjectList   = &matchMgr->m_IdleObjectList2;

            matchMgr->mCreateCount          = 0;
            matchMgr->mDestroyCount         = 0;

            mThreadGameNetSendDataBufferPoolCs.lock();
            {
                mThreadGameNetSendDataBufferPool.push_back( matchMgr );
            }
            mThreadGameNetSendDataBufferPoolCs.unlock();
        }

        return matchMgr;
    }

    //--------------------------------------------------------------------------------
    GameNetL2NEventDataFactory::GameNetSendDataBufferPoolManager* GameNetL2NEventDataFactory::retrieveGameNetSendDataBufferPoolManager( UInt threadID )
    {
        GameNetL2NEventDataFactory::GameNetSendDataBufferPoolManager* matchMgr  = NULL;
        GameNetL2NEventDataFactory::GameNetSendDataBufferPoolManager* mgr       = NULL;

        UInt count = mThreadGameNetSendDataBufferPool.size();

        for ( UInt i=0; i<count ; i++ )
        {
            mgr = mThreadGameNetSendDataBufferPool[i];

            if ( mgr->mThreadID == threadID )
            {
                matchMgr = mgr;
                break;
            }
        }

        return matchMgr;
    }

    //--------------------------------------------------------------------------------
    GameNetL2NEventDataFactory::GameNetOnceSendConfigPoolManager* GameNetL2NEventDataFactory::createOrRetrieveGameNetOnceSendConfigPoolManager( UInt threadID )
    {
        GameNetL2NEventDataFactory::GameNetOnceSendConfigPoolManager* matchMgr  = retrieveGameNetOnceSendConfigPoolManager( threadID );
       
        if ( matchMgr == NULL )
        {
            matchMgr = MG_NEW GameNetL2NEventDataFactory::GameNetOnceSendConfigPoolManager();

            matchMgr->mThreadID             = threadID;
            matchMgr->m_CreateObjectList    = &matchMgr->m_IdleObjectList1;
            matchMgr->m_DestroyObjectList   = &matchMgr->m_IdleObjectList2;

            matchMgr->mCreateCount          = 0;
            matchMgr->mDestroyCount         = 0;

            mThreadGameNetOnceSendConfigPoolCs.lock();
            {
                mThreadGameNetOnceSendConfigPool.push_back( matchMgr );
            }
            mThreadGameNetOnceSendConfigPoolCs.unlock();
        }

        return matchMgr;
    }

    //--------------------------------------------------------------------------------
    GameNetL2NEventDataFactory::GameNetOnceSendConfigPoolManager* GameNetL2NEventDataFactory::retrieveGameNetOnceSendConfigPoolManager( UInt threadID )
    {
        GameNetL2NEventDataFactory::GameNetOnceSendConfigPoolManager* matchMgr  = NULL;
        GameNetL2NEventDataFactory::GameNetOnceSendConfigPoolManager* mgr       = NULL;

        UInt count = mThreadGameNetOnceSendConfigPool.size();

        for ( UInt i=0; i<count ; i++ )
        {
            mgr = mThreadGameNetOnceSendConfigPool[i];

            if ( mgr->mThreadID == threadID )
            {
                matchMgr = mgr;
                break;
            }
        }

        return matchMgr;
    }

	//--------------------------------------------------------------------------------
	void GameNetL2NEventDataFactory::setNearestSendedGameNetSendDataBufferPtr(GameNetSendDataBufferPtr& ptr)
	{
		GameNetSendDataBufferPoolManager* poolMgr   = NULL;
		DWORD threadId = GetCurrentThreadId();
		poolMgr = createOrRetrieveGameNetSendDataBufferPoolManager( threadId );
		if ( poolMgr )
		{
            poolMgr->mNearestSendPtr.setNull();
			poolMgr->mNearestSendPtr = ptr;
		}
	}

    //--------------------------------------------------------------------------------
    void GameNetL2NEventDataFactory::createGameNetSendDataBufferPtr(GameNetSendDataBufferPtr& ptr, U32 buffSize)
    {
        NetSendDataBuffer* buffObj                  = NULL;
        std::deque<NetSendDataBuffer*>* idleList    = NULL;
        GameNetSendDataBufferPool*      pool        = NULL;
        GameNetSendDataBufferPoolManager* poolMgr   = NULL;

        DWORD threadId = GetCurrentThreadId();
        poolMgr = createOrRetrieveGameNetSendDataBufferPoolManager( threadId );
        if ( poolMgr )
        {
            Bool isNormalBuff   = true;

            pool                = poolMgr->m_CreateObjectList;

            // 如果小于默认值, 则分配缓存等于默认值
            if ( buffSize <= MG_GAME_NET_PACKET_NORMAL_MAX_SIZE )
            {
                buffSize        = MG_GAME_NET_PACKET_NORMAL_MAX_SIZE;
                isNormalBuff    = true;
            }else
            if ( buffSize <= MG_GAME_NET_PACKET_BIG_MAX_SIZE )
            {
                buffSize        = MG_GAME_NET_PACKET_BIG_MAX_SIZE;
                isNormalBuff    = false;
            }else
            {
                DYNAMIC_EEXCEPT_LOG("createGameNetSendDataBufferPtr : too long buffsize ");
                return;
            }

            pool->mPoolCs.lock();
            {
                if ( isNormalBuff )
                {
                    idleList = &pool->m_IdleNormalObjectList;
                }else
                {
                    idleList = &pool->m_IdleBigObjectList;
                }

                if ( idleList->size() > 0 )
                {
                    buffObj = idleList->back();
                    idleList->pop_back();
                }else
                {
                    buffObj = mDriverMgr->mMgr->createNetSendDataBuffer( buffSize );
                }
            }
            pool->mPoolCs.unlock();


            poolMgr->mCreateCount++;

        }else
        {
            DYNAMIC_EEXCEPT_LOG("createGameNetSendDataBufferPtr: not register thread !");
        }

        if ( buffObj )
        {
            buffObj->initialize();
			buffObj->setActive( true );

            ptr.setNull();
            ptr.mFactory            = this;
            ptr.mCreateThreadID     = threadId;
            ptr.mNearestSendNetID   = -1;
            ptr.mLogicDataMaxSize   = buffSize;
            ptr.bind( buffObj );

            if ( poolMgr )
            {
                poolMgr->mNearestCreatePtr.setNull();
                poolMgr->mNearestCreatePtr = ptr;
            }
        }
    }

    //--------------------------------------------------------------------------------
    void GameNetL2NEventDataFactory::cloneGameNetSendDataBufferPtr(GameNetSendDataBufferPtr& srcPtr, GameNetSendDataBufferPtr& desPtr, Bool isCopyHeader)
    {
        GameNetSendDataBufferPtr tempDesPtr;
        GameNetL2NEventDataFactory::createGameNetSendDataBufferPtr( tempDesPtr, srcPtr->getLogicDataMaxSize());

        if ( tempDesPtr.isNull() == false )
        {
            if ( isCopyHeader && (srcPtr.isNull() == false) )
            {
                GameNetPacketData* srcData = (GameNetPacketData*)srcPtr->getLogicData();
                GameNetPacketData* desData = (GameNetPacketData*)tempDesPtr->getLogicData();

                desData->channel    = srcData->channel;
                desData->type       = srcData->type;       
            }
        }
        tempDesPtr.mIsAllowDestroy = srcPtr.mIsAllowDestroy;

        desPtr = tempDesPtr;
    }

	//--------------------------------------------------------------------------------
	void GameNetL2NEventDataFactory::cloneGameNetSendDataBufferPtr(GameNetSendDataBufferPtr& srcPtr, GameNetSendDataBufferPtr& desPtr, UInt cloneSize)
	{
        GameNetSendDataBufferPtr tempDesPtr;
        GameNetL2NEventDataFactory::createGameNetSendDataBufferPtr( tempDesPtr, srcPtr->getLogicDataMaxSize());

		if ( tempDesPtr.isNull() == false )
		{
			if ( srcPtr.isNull() == false) 
			{
				Char8* srcData = srcPtr->getLogicData();
				Char8* desData = tempDesPtr->getLogicData();

				if ( (cloneSize > 0) && 
					 (cloneSize < srcPtr->getLogicDataMaxSize()) &&
					 (cloneSize < tempDesPtr->getLogicDataMaxSize()) 
					)
				{
					memcpy( desData, srcData, cloneSize );
				}else
				{
					DYNAMIC_EEXCEPT_LOG("GameNetL2NEventDataFactory::cloneGameNetSendDataBufferPtr : clone size is except!");
				}
			}
		}

        tempDesPtr.mIsAllowDestroy = srcPtr.mIsAllowDestroy;

        desPtr = tempDesPtr;
	}

    //--------------------------------------------------------------------------------
    void GameNetL2NEventDataFactory::destroyGameNetSendDataBufferPtr(GameNetSendDataBufferPtr& ptr)
    {
        if ( ptr.isNull() )
            return;

        DWORD threadId = ptr.mCreateThreadID;
        Bool isNormalBuff = true;
        std::deque<NetSendDataBuffer*>* idleList = NULL;

        GameNetSendDataBufferPoolManager* mgr = retrieveGameNetSendDataBufferPoolManager( threadId );
        if ( mgr )
        {
            if ( ptr.mLogicDataMaxSize == MG_GAME_NET_PACKET_NORMAL_MAX_SIZE )
            {
                isNormalBuff    = true;

                if ( ptr->getLogicDataMaxSize() > MG_GAME_NET_PACKET_NORMAL_MAX_SIZE )
                {
                    DYNAMIC_EEXCEPT_LOG("ptr.mLogicDataMaxSize is diff ptr->getLogicDataMaxSize()!");
                    DYNAMIC_ASSERT(false);
                    isNormalBuff = false;
                }
            }else
            if ( ptr.mLogicDataMaxSize == MG_GAME_NET_PACKET_BIG_MAX_SIZE )
            {
                isNormalBuff    = false;

                if ( ptr->getLogicDataMaxSize() > MG_GAME_NET_PACKET_BIG_MAX_SIZE )
                {
                    DYNAMIC_EEXCEPT_LOG( "ptr.mLogicDataMaxSize is diff ptr->getLogicDataMaxSize()! and too long buffsize ");
                    DYNAMIC_ASSERT(false);
                    return;
                }
            }else
            {
                DYNAMIC_EEXCEPT_LOG("destroyGameNetSendDataBufferPtr : too long buffsize ");
                return;
            }

            GameNetSendDataBufferPool* pool = mgr->m_DestroyObjectList;

            pool->mPoolCs.lock();
            {
                if ( isNormalBuff )
                {
                    idleList = &pool->m_IdleNormalObjectList;
                }else
                {
                    idleList = &pool->m_IdleBigObjectList;
                }

				if ( ptr->getActive() )
				{
					ptr->setActive( false );
					idleList->push_back( ptr.getPointer() );
				}else
				{
					DYNAMIC_EEXCEPT_LOG("destroyGameNetSendDataBufferPtr : reduplicate destroy send buff obj! ");
				}
            }
            pool->mPoolCs.unlock();

            mgr->mDestroyCount++;

        }else
        {
            DYNAMIC_EEXCEPT_LOG("destroyGameNetSendDataBufferPtr: not register thread !");
        }
    }

    //--------------------------------------------------------------------------------
    void GameNetL2NEventDataFactory::destroyAllGameNetSendDataBufferPtr()
    {
        mThreadGameNetSendDataBufferPoolCs.lock();
        {
            Int count =  mThreadGameNetSendDataBufferPool.size();
            for ( Int i=0; i<count; i++ )
            {
                GameNetSendDataBufferPoolManager* mgr = mThreadGameNetSendDataBufferPool[i];

                mgr->m_IdleObjectList1.mPoolCs.lock();
                {
                    std::deque<NetSendDataBuffer*>::iterator bigIter = mgr->m_IdleObjectList1.m_IdleBigObjectList.begin();
                    for ( ; bigIter != mgr->m_IdleObjectList1.m_IdleBigObjectList.end(); bigIter++ )
                    {
                        mDriverMgr->mMgr->destroyNetSendDataBuffer( *bigIter );
                    }
                    mgr->m_IdleObjectList1.m_IdleBigObjectList.clear();

                    std::deque<NetSendDataBuffer*>::iterator normalIter = mgr->m_IdleObjectList1.m_IdleNormalObjectList.begin();
                    for ( ; normalIter != mgr->m_IdleObjectList1.m_IdleNormalObjectList.end(); normalIter++ )
                    {
                        mDriverMgr->mMgr->destroyNetSendDataBuffer( *normalIter );
                    }
                    mgr->m_IdleObjectList1.m_IdleNormalObjectList.clear();
                }
                mgr->m_IdleObjectList1.mPoolCs.unlock();

                mgr->m_IdleObjectList2.mPoolCs.lock();
                {
                    std::deque<NetSendDataBuffer*>::iterator bigIter = mgr->m_IdleObjectList2.m_IdleBigObjectList.begin();
                    for ( ; bigIter != mgr->m_IdleObjectList2.m_IdleBigObjectList.end(); bigIter++ )
                    {
                        mDriverMgr->mMgr->destroyNetSendDataBuffer( *bigIter );
                    }
                    mgr->m_IdleObjectList2.m_IdleBigObjectList.clear();

                    std::deque<NetSendDataBuffer*>::iterator normalIter = mgr->m_IdleObjectList2.m_IdleNormalObjectList.begin();
                    for ( ; normalIter != mgr->m_IdleObjectList2.m_IdleNormalObjectList.end(); normalIter++ )
                    {
                        mDriverMgr->mMgr->destroyNetSendDataBuffer( *normalIter );
                    }
                    mgr->m_IdleObjectList2.m_IdleNormalObjectList.clear();
                }
                mgr->m_IdleObjectList2.mPoolCs.unlock();
            } 
        }
        mThreadGameNetSendDataBufferPoolCs.unlock();
    }

    //--------------------------------------------------------------------------------
    void GameNetL2NEventDataFactory::createGameNetOnceSendConfigPtr(GameNetOnceSendConfigPtr& ptr, I32 driverID, I32 netID, I32 sendID)
    {
        NetOnceSendConfig* configObj                = NULL;
        std::deque<NetOnceSendConfig*>* idleList    = NULL;
        GameNetOnceSendConfigPool*      pool        = NULL;
        GameNetOnceSendConfigPoolManager* poolMgr   = NULL;

        DWORD threadId = GetCurrentThreadId();
        poolMgr = createOrRetrieveGameNetOnceSendConfigPoolManager( threadId );
        if ( poolMgr )
        {
            pool    = poolMgr->m_CreateObjectList;

            pool->mPoolCs.lock();
            {

                idleList = &pool->m_IdleObjectList;
               
                if ( idleList->size() > 0 )
                {
                    configObj = idleList->back();
                    idleList->pop_back();
                }else
                {
                    configObj = mDriverMgr->mMgr->createNetOnceSendConfig();
                }
            }
            pool->mPoolCs.unlock();

            poolMgr->mCreateCount++;

        }else
        {
            DYNAMIC_EEXCEPT_LOG("createGameNetOnceSendConfigPtr: not register thread !");
        }

        if ( configObj )
        {
            configObj->initialize(driverID,netID,sendID);
			configObj->setActive( true );

            ptr.setNull();
            ptr.mFactory            = this;
            ptr.mCreateThreadID     = threadId;
            ptr.bind( configObj );

            if ( poolMgr )
            {
                poolMgr->mNearestCreatePtr.setNull();
                poolMgr->mNearestCreatePtr = ptr;
            }
        }
    }

    //--------------------------------------------------------------------------------
    void GameNetL2NEventDataFactory::destroyGameNetOnceSendConfigPtr(GameNetOnceSendConfigPtr& ptr)
    {
        if ( ptr.isNull() )
            return;

        DWORD threadId = ptr.mCreateThreadID;
        std::deque<NetOnceSendConfig*>* idleList = NULL;

        GameNetOnceSendConfigPoolManager* mgr = retrieveGameNetOnceSendConfigPoolManager( threadId );
        if ( mgr )
        {
            GameNetOnceSendConfigPool* pool = mgr->m_DestroyObjectList;
            pool->mPoolCs.lock();
            {
				if ( ptr->getActive() )
				{
					ptr->setActive( false );
					idleList = &pool->m_IdleObjectList;
					idleList->push_back( ptr.getPointer() );
				}else
				{
					DYNAMIC_EEXCEPT_LOG("destroyGameNetOnceSendConfigPtr : reduplicate destroy send config obj! ");
				}
            }
            pool->mPoolCs.unlock();

            mgr->mDestroyCount++;
        }else
        {
            DYNAMIC_EEXCEPT_LOG("destroyGameNetOnceSendConfigPtr: not register thread !");
        }
    }

    //--------------------------------------------------------------------------------
    void GameNetL2NEventDataFactory::destroyAllGameNetOnceSendConfigPtr()
    {
        mThreadGameNetOnceSendConfigPoolCs.lock();
        {
            Int count =  mThreadGameNetOnceSendConfigPool.size();
            for ( Int i=0; i<count; i++ )
            {
                GameNetOnceSendConfigPoolManager* mgr = mThreadGameNetOnceSendConfigPool[i];

                mgr->m_IdleObjectList1.mPoolCs.lock();
                {
                    std::deque<NetOnceSendConfig*>::iterator bigIter = mgr->m_IdleObjectList1.m_IdleObjectList.begin();
                    for ( ; bigIter != mgr->m_IdleObjectList1.m_IdleObjectList.end(); bigIter++ )
                    {
                        mDriverMgr->mMgr->destroyNetOnceSendConfig( *bigIter );
                    }
                    mgr->m_IdleObjectList1.m_IdleObjectList.clear();
                }
                mgr->m_IdleObjectList1.mPoolCs.unlock();

                mgr->m_IdleObjectList2.mPoolCs.lock();
                {
                    std::deque<NetOnceSendConfig*>::iterator bigIter = mgr->m_IdleObjectList2.m_IdleObjectList.begin();
                    for ( ; bigIter != mgr->m_IdleObjectList2.m_IdleObjectList.end(); bigIter++ )
                    {
                        mDriverMgr->mMgr->destroyNetOnceSendConfig( *bigIter );
                    }
                    mgr->m_IdleObjectList2.m_IdleObjectList.clear();
                }
                mgr->m_IdleObjectList2.mPoolCs.unlock();
            }
        }
        mThreadGameNetOnceSendConfigPoolCs.unlock();
    }
}

