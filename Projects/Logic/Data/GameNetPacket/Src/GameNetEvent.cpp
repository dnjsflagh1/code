/******************************************************************************/
#include "stdafx.h"
#include "GameNetEvent.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/

    //------------------------------------------------------
    INetConnect::INetConnect()
        :mLogicBinder(NULL)
    {
    }

    //------------------------------------------------------
    INetConnect::~INetConnect()
    {
    }

    //------------------------------------------------------
    void INetConnect::setLogicBinder( Ptr binder )
    {
        mLogicBinder = binder;
    }

    //------------------------------------------------------
    Ptr INetConnect::getLogicBinder()
    {
        return mLogicBinder;
    }

    /******************************************************************************/

    INetEvent::INetEvent(I32 handle,I32 id,NET_EVENT_TYPE type,INetEventPool* pool)
        :mType(type),
        mHandle(handle),
        mID(id),
        mLockedCount(0),
        mPool(pool)
    {
    }
    
    INetEvent::INetEvent(NET_EVENT_TYPE type,INetEventPool* pool)
        :mType(type),
        mHandle(0),
        mID(0),
        mLockedCount(0),
        mPool(pool)
    {
    }

    /******************************************************************************/

	NetEventRecv::NetEventRecv( I32 buffSize,INetEventPool* pool )
        :INetEvent(NET_RECV,pool)
	{
        mBuff       = MG_NEW Char8[buffSize];
        mBuffLen    = buffSize;
	}
    
    //-----------------------------------------------------------------------------
	NetEventRecv::~NetEventRecv()
	{
        MG_DELETE_ARRAY mBuff;
	}

    //-----------------------------------------------------------------------------
    void NetEventRecv::init(I32 handle, I32 id, I32 buffSize)
    {
        if ( mBuffLen != buffSize )
        {
            DYNAMIC_EEXCEPT_LOG("NetEventRecv::init : diff buff size!");

            MG_DELETE_ARRAY mBuff;
            mBuff       = MG_NEW Char8[buffSize];
            mBuffLen    = buffSize;
        }

        mHandle         = handle;
        mID             = id;
        mLockedCount    = 0;
    }

    //-----------------------------------------------------------------------------
    void NetEventRecv::unInit()
    {
        mHandle = 0;
        mID = 0; 
    }
    
    //-----------------------------------------------------------------------------
    I32 NetEventRecv::getBuffMaxSize()
    {
        return mBuffLen;
    }

    //-----------------------------------------------------------------------------
    void NetEventRecv::copyData( CChar8* data, I32 dataSize )
    {
        DYNAMIC_ASSERT( dataSize <= mBuffLen );

        if ( dataSize <= mBuffLen )
        {
            mDataLen = dataSize;
            memcpy(mBuff,data,dataSize);
        }else
        {
            dataSize = 0;
        }
    }

    //-----------------------------------------------------------------------------
    I32 NetEventRecv::getDataSize()
    {
        return mDataLen;
    }

    //-----------------------------------------------------------------------------
    Char8* NetEventRecv::getData()
    {
        return mBuff;
    }

    //-----------------------------------------------------------------------------
    Byte NetEventRecv::getChannel()
    {
        GameNetPacketHeader* header = (GameNetPacketHeader*)getData();
        if ( header )
            return header->channel;

        return GNT_UNKOWN;
    }
    
}
