/******************************************************************************/
#ifndef _NETUDPEVENT_H_
#define _NETUDPEVENT_H_
/******************************************************************************/
#include "NetUdpManager.h"
#include "NetDefine.h"
#include "NetAddress.h"
#include "ObjectPool.h"
#include "GameNetUdpPacket.h"
/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	class INetUdpEvent
	{
	protected:
		INetUdpEvent(I32 handle,I32 id,NET_EVENT_TYPE type);
		INetUdpEvent(NET_EVENT_TYPE type);
		virtual ~INetUdpEvent(){};

	public:

		NET_EVENT_TYPE	getType() {return mType;} ;
		I32             getHandle() {return mHandle;} ;
		I32             getID() {return mID;} ;

		///是否需要系统回收
		void            setNeedGc(Bool needGc) {mNeedGc = needGc;} ;
		Bool            isNeedGc() {return mNeedGc;} ;

	protected:

		NET_EVENT_TYPE		mType;
		I32					mHandle;
		I32					mID;
		Bool                mNeedGc;

	};

	/******************************************************************************/
	class NetUdpEventRecv : public INetUdpEvent
	{
	public:

		NetUdpEventRecv(I32 id,U16 sectionPacketSize,U32 sectionCount);
		virtual ~NetUdpEventRecv();

	public:

		void            init(I32 handle, I32 id, U16 sectionPacketSize,U32 sectionCount); 
		void            unInit();
		void			clear();

		Bool*			getRecvFlag();
		Bool			isFinished();
		
		I32             getBuffMaxSize();
		I32             getDataSize();
		Char8*          getData();
		void            copyData(U32 index, CChar8* data, U16 dataSize );
		void			setPacketHead(Byte channel,Byte type);

		Byte            getChannel();
	protected:

		Char8*	mBuff;
		I32		mBuffLen;
		I32     mDataLen;
		U32		mSectionCount;
		U16		mSectionSize;
	};

	/******************************************************************************/
	class NetUdpEventAccept : public INetUdpEvent
	{
		friend class GameNetUdpPacketManager;
		friend class ObjectPool<NetUdpEventAccept>;
	protected:
		NetUdpEventAccept(I32 handle,I32 id,NetAddress&address):INetUdpEvent(handle,id,NET_ACCEPT){mNetAddress=address;};
	public:
		NetAddress& getNetAddress(){return mNetAddress;};
	protected:
		NetAddress mNetAddress;
	};

	/******************************************************************************/
	class NetUdpEventConnect : public INetUdpEvent
	{
		friend class GameNetUdpPacketManager;
		friend class ObjectPool<NetUdpEventConnect>;
	protected:
		NetUdpEventConnect(I32 handle,I32 id,NetAddress&address):INetUdpEvent(handle,id,NET_CONNECT){mNetAddress=address;};
	public:
		NetAddress& getNetAddress(){return mNetAddress;};
	protected:
		NetAddress mNetAddress;
	};

	/******************************************************************************/
	class NetUdpEventClose : public INetUdpEvent
	{
		friend class GameNetUdpPacketManager;
		friend class ObjectPool<NetUdpEventClose>;
	protected:
		NetUdpEventClose(I32 handle,I32 id,Bool isPassivity,NetAddress&address):INetUdpEvent(handle,id,NET_CLOSE){mNetAddress=address;mIsPassivity=isPassivity;};
	public:
		NetAddress& getNetAddress(){return mNetAddress;};
		Bool isPassivity(){return mIsPassivity;};
	protected:
		NetAddress mNetAddress;
		Bool mIsPassivity;
	};

	/******************************************************************************/
	class NetUdpEventErr : public INetUdpEvent
	{
		friend class GameNetUdpPacketManager;
		friend class ObjectPool<NetUdpEventErr>;
	protected:
		NetUdpEventErr(I32 handle,I32 id):INetUdpEvent(handle,id,NET_ERR){};
	};
}

#endif
