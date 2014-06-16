/******************************************************************************/
#ifndef _NETEVENT_
#define _NETEVENT_
/******************************************************************************/
#include "NetManager.h"
#include "NetDefine.h"
#include "NetAddress.h"
#include "ObjectPool.h"
#include "GameNetPacket.h"
/******************************************************************************/
namespace MG
{

    /******************************************************************************/

    class INetConnect
    {
    public:
        INetConnect();
        virtual~INetConnect();

        virtual void    setLogicBinder( Ptr binder );
        virtual Ptr     getLogicBinder();

    private:

        Ptr mLogicBinder;

    };

    /******************************************************************************/

    class INetEvent;
    class INetEventPool : public INetConnect
    {
    public:
        virtual void freeEvent( INetEvent* netEvent ) = 0;
    };

    /******************************************************************************/
    /******************************************************************************/


	class INetEvent
	{
        friend class INetEventPool;
    protected:

		INetEvent(I32 handle,I32 id,NET_EVENT_TYPE type,INetEventPool* pool);
        INetEvent(NET_EVENT_TYPE type,INetEventPool* pool);
		virtual ~INetEvent(){};

    public:

        INetConnect*    getNetConnect(){return mPool;};
        NET_EVENT_TYPE	getType() {return mType;} ;
        I32             getHandle() {return mHandle;} ;
        I32             getID() {return mID;} ;

        /// 增加一把锁
        I32             addLocker() { return ++mLockedCount;} ;
        I32             subLocker() { return --mLockedCount;} ;
        I32             getLockerCount() { return mLockedCount;} ;
        Bool            isLocked() { return mLockedCount>0;} ;
        
        // 释放自己
        void            free(){ mPool->freeEvent(this); };

    protected:

		NET_EVENT_TYPE		mType;
		I32					mHandle;
		I32					mID;
        InterLocked         mLockedCount;
        INetEventPool*      mPool;
        
	};

    /******************************************************************************/
    /******************************************************************************/


    //--------------------------------------------------------------------------------
    // Recv
    //--------------------------------------------------------------------------------
    class NetEventRecv : public INetEvent
    {
    public:

        NetEventRecv(I32 buffSize,INetEventPool* pool);
        virtual ~NetEventRecv();

    public:
                     
        void            init(I32 handle, I32 id, I32 buffSize); 
        void            unInit();

        void            copyData( CChar8* data, I32 dataSize );
        I32             getDataSize();
        Char8*          getData();
        I32             getBuffMaxSize();
        Byte            getChannel();

    protected:

        Char8*	mBuff;
        I32		mBuffLen;
        I32     mDataLen;
    };
    
    //--------------------------------------------------------------------------------
    // Accept
    //--------------------------------------------------------------------------------
	class NetEventAccept : public INetEvent
	{
        friend class Net2LogicEventFromOneConnectHandler;
        friend class GameNetPacketManager;
        friend class ObjectPool<NetEventAccept,false>;
    protected:
        NetEventAccept(I32 handle,I32 id,NetAddress&address,INetEventPool* pool):INetEvent(handle,id,NET_ACCEPT,pool){mNetAddress=address;};
    public:
		NetAddress&     getNetAddress(){return mNetAddress;};
	protected:
		NetAddress mNetAddress;
	};

    //--------------------------------------------------------------------------------
    // Connect
    //--------------------------------------------------------------------------------
	class NetEventConnect : public INetEvent
	{
        friend class Net2LogicEventFromOneConnectHandler;
        friend class GameNetPacketManager;
        friend class ObjectPool<NetEventConnect,false>;
    protected:
		NetEventConnect(I32 handle,I32 id,NetAddress&address,INetEventPool* pool):INetEvent(handle,id,NET_CONNECT,pool){mNetAddress=address;};
    public:
		NetAddress& getNetAddress(){return mNetAddress;};
	protected:
		NetAddress mNetAddress;
	};

    //--------------------------------------------------------------------------------
    // Close
    //--------------------------------------------------------------------------------
    class NetEventClose : public INetEvent
    {
        friend class Net2LogicEventFromOneConnectHandler;
        friend class GameNetPacketManager;
        friend class ObjectPool<NetEventClose,false>;
    protected:
        NetEventClose(I32 handle,I32 id,Bool isPassivity,NetAddress&address,INetEventPool* pool):INetEvent(handle,id,NET_CLOSE,pool){mNetAddress=address;mIsPassivity=isPassivity;};
    public:
        NetAddress& getNetAddress(){return mNetAddress;};
        Bool isPassivity(){return mIsPassivity;};
    protected:
        NetAddress mNetAddress;
        Bool mIsPassivity;
    };

    //--------------------------------------------------------------------------------
    // Err
    //--------------------------------------------------------------------------------
	class NetEventErr : public INetEvent
	{
        friend class Net2LogicEventFromOneConnectHandler;
        friend class GameNetPacketManager;
        friend class ObjectPool<NetEventErr,false>;
    protected:
		NetEventErr(I32 handle,I32 id, INetEventPool* pool):INetEvent(handle,id,NET_ERR,pool){};
	};

    /******************************************************************************/

}

#endif
