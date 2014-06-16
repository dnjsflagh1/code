/******************************************************************************/
#ifndef _S_CLIENT_NET_TRANSPOND_PACKET_PROCESSER_H_
#define _S_CLIENT_NET_TRANSPOND_PACKET_PROCESSER_H_
/******************************************************************************/


#include "CenterServerPreqs.h"

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	// 网络转发包缓存
	/******************************************************************************/
	class ClientNetTranspondPacketProcesser;
	class ClientNetTranspondSendDataBufferPtr
	{

		friend class ClientNetTranspondPacketProcesser;

	public:

		ClientNetTranspondSendDataBufferPtr();
		ClientNetTranspondSendDataBufferPtr(GameNetSendDataBufferPtr& dataPtr, Int usedHeadSize, Int estimateTailSize);

		// 得到缓存
		virtual Char8*      getTranspondData();
		// 得到缓存大小
		virtual U32         getTranspondDataMaxSize(UInt maxClientCount);

	public:

		GameNetSendDataBufferPtr mDataPtr;

		//已经使用掉的数据大小
		Int mUsedHeadSize;

		//预估尾部的数据大小
		Int mEstimateTailSize;

	public:

		ClientNetTranspondSendDataBufferPtr(const ClientNetTranspondSendDataBufferPtr& r)
			:mDataPtr(r.mDataPtr),
			mUsedHeadSize(r.mUsedHeadSize),
			mEstimateTailSize(r.mEstimateTailSize)
		{
		}

		ClientNetTranspondSendDataBufferPtr& operator=(const ClientNetTranspondSendDataBufferPtr& r) {
			mDataPtr = r.mDataPtr;
			mUsedHeadSize = r.mUsedHeadSize;
			mEstimateTailSize = r.mEstimateTailSize;
			return *this;
		}
	};

	/******************************************************************************/
	//CenterServer服务器转发客户端相关消息处理
	/******************************************************************************/
	class ClientNetTranspondPacketProcesser
	{
		ClientNetTranspondPacketProcesser();
		~ClientNetTranspondPacketProcesser();

		SINGLETON_INSTANCE(ClientNetTranspondPacketProcesser);


		Bool	processClientPacket(I32 id, NetEventRecv* packet);
		Bool	processLoginServerPacket(I32 id, NetEventRecv* packet);
		Bool	processMapServerPacket(I32 id, NetEventRecv* packet);

		// 得到网络转发发送数据缓存
		void    getClientTranspondSendDataBuffer( ClientNetTranspondSendDataBufferPtr& ptr, U32 buffSize = MG_GAME_NET_PACKET_NORMAL_MAX_SIZE );
		
		// 发送网络转发客户端数据包到FrontServer
		void                                  sendClientTranspondSendDataToFrontServer( 
                                                                ClientNetTranspondSendDataBufferPtr& dataPtr, 
                                                                Int dataSize,
			                                                    NetIdType frontSvrNetID, 
                                                                NetIdType client_net_id, 
                                                                AccountIdType account_id );

        // 广播网络转发客户端数据包到FrontServer
		void                                    broadClientTranspondSendDataToFrontServer(
                                                                ClientNetTranspondSendDataBufferPtr& dataPtr, 
                                                                Int dataSize);
	};
}

#endif	//_S_CLIENT_NET_TRANSPOND_PACKET_PROCESSER_H_