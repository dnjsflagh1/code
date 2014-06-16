/******************************************************************************/
#include "stdafx.h"
#include "GameNetUdpEvent.h"
#include "GameNetUdpPacket.h"
#include "Win32IocpNetUdpData.h"
/******************************************************************************/
namespace MG
{

	/******************************************************************************/

	INetUdpEvent::INetUdpEvent(I32 handle,I32 id,NET_EVENT_TYPE type)
		:mType(type),
		mHandle(handle),
		mID(id),
		mNeedGc(true)
	{
	}

	INetUdpEvent::INetUdpEvent(NET_EVENT_TYPE type)
		:mType(type),
		mHandle(0),
		mID(0),
		mNeedGc(true)
	{
	}

	/******************************************************************************/

	NetUdpEventRecv::NetUdpEventRecv(I32 id,U16 sectionPacketSize,U32 sectionCount )
		:INetUdpEvent(NET_RECV)
	{	
		mID = id;
		mSectionSize = sectionPacketSize;
		mSectionCount = sectionCount;
		mBuffLen    = sectionPacketSize * sectionCount;
		mBuff       = MG_NEW Char8[mBuffLen];
	}

	//-----------------------------------------------------------------------------
	NetUdpEventRecv::~NetUdpEventRecv()
	{
		MG_DELETE_ARRAY mBuff;
	}

	//-----------------------------------------------------------------------------
	void NetUdpEventRecv::init(I32 handle, I32 id, U16 sectionPacketSize,U32 sectionCount)
	{
		if ( mBuffLen != sectionPacketSize * sectionCount )
		{
			DYNAMIC_ASSERT(0);
			MG_DELETE_ARRAY mBuff;
			mBuffLen    = sectionPacketSize * sectionCount;
			mBuff       = MG_NEW Char8[mBuffLen];
			mSectionCount = sectionCount;
		}

		mHandle = handle;
		mID = id;
	}

	//-----------------------------------------------------------------------------
	void NetUdpEventRecv::unInit()
	{
		mHandle = 0;
		mID = 0; 
	}

	//-----------------------------------------------------------------------------
	I32 NetUdpEventRecv::getBuffMaxSize()
	{
		return mBuffLen;
	}

	//-----------------------------------------------------------------------------
	void NetUdpEventRecv::copyData(U32 index, CChar8* data, U16 dataSize)
	{
		mDataLen += dataSize;
		if ( dataSize <= mBuffLen )
		{
			//×é°ü
			U16 sectionPacketDataSize = mSectionSize - IocpNetUdpSectionPacket_INFO::headSize;
			U32 offset =  GameNetUdpPacketData_INFO::headSize + index * sectionPacketDataSize;
			memcpy(mBuff + offset,data,dataSize);
			Bool* sectionDataReceived = getRecvFlag();
			sectionDataReceived[index] = true;
		}else
		{
			DYNAMIC_ASSERT(false);
			dataSize = 0;
		}
	}

	//-----------------------------------------------------------------------------
	I32 NetUdpEventRecv::getDataSize()
	{
		return mDataLen;
	}

	//-----------------------------------------------------------------------------
	Char8* NetUdpEventRecv::getData()
	{
		return mBuff;
	}

	//-----------------------------------------------------------------------------
	Byte NetUdpEventRecv::getChannel()
	{
		GameNetUdpPacketHeader* header = (GameNetUdpPacketHeader*)getData();
		if ( header )
			return header->channel;

		return 0;
	}
	//-----------------------------------------------------------------------------
	void NetUdpEventRecv::clear()
	{
		Bool* flag = getRecvFlag();
		for (I32 i = 0; i < mSectionCount; i++)
		{
			flag[i] = false;
		}
		mDataLen = 0;
	}
	//-----------------------------------------------------------------------------
	Bool* NetUdpEventRecv::getRecvFlag()
	{
		return (Bool*)(mBuff - mSectionCount * sizeof(Bool));
	}
	//-----------------------------------------------------------------------------
	MG::Bool NetUdpEventRecv::isFinished()
	{
		Bool* sectionDataReceived = getRecvFlag();
		for (Int i = 0; i < mSectionCount; i++)
		{
			if(!sectionDataReceived[i])
			{
				return false;
			}
		}
		return true;
	}

	void NetUdpEventRecv::setPacketHead( Byte channel,Byte type )
	{
		GameNetUdpPacketData* packet = (GameNetUdpPacketData*)mBuff;
		packet->channel = channel;
		packet->type = type;
	}
}
