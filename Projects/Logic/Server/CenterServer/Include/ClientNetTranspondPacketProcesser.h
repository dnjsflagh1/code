/******************************************************************************/
#ifndef _S_CLIENT_NET_TRANSPOND_PACKET_PROCESSER_H_
#define _S_CLIENT_NET_TRANSPOND_PACKET_PROCESSER_H_
/******************************************************************************/


#include "CenterServerPreqs.h"

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	// ����ת��������
	/******************************************************************************/
	class ClientNetTranspondPacketProcesser;
	class ClientNetTranspondSendDataBufferPtr
	{

		friend class ClientNetTranspondPacketProcesser;

	public:

		ClientNetTranspondSendDataBufferPtr();
		ClientNetTranspondSendDataBufferPtr(GameNetSendDataBufferPtr& dataPtr, Int usedHeadSize, Int estimateTailSize);

		// �õ�����
		virtual Char8*      getTranspondData();
		// �õ������С
		virtual U32         getTranspondDataMaxSize(UInt maxClientCount);

	public:

		GameNetSendDataBufferPtr mDataPtr;

		//�Ѿ�ʹ�õ������ݴ�С
		Int mUsedHeadSize;

		//Ԥ��β�������ݴ�С
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
	//CenterServer������ת���ͻ��������Ϣ����
	/******************************************************************************/
	class ClientNetTranspondPacketProcesser
	{
		ClientNetTranspondPacketProcesser();
		~ClientNetTranspondPacketProcesser();

		SINGLETON_INSTANCE(ClientNetTranspondPacketProcesser);


		Bool	processClientPacket(I32 id, NetEventRecv* packet);
		Bool	processLoginServerPacket(I32 id, NetEventRecv* packet);
		Bool	processMapServerPacket(I32 id, NetEventRecv* packet);

		// �õ�����ת���������ݻ���
		void    getClientTranspondSendDataBuffer( ClientNetTranspondSendDataBufferPtr& ptr, U32 buffSize = MG_GAME_NET_PACKET_NORMAL_MAX_SIZE );
		
		// ��������ת���ͻ������ݰ���FrontServer
		void                                  sendClientTranspondSendDataToFrontServer( 
                                                                ClientNetTranspondSendDataBufferPtr& dataPtr, 
                                                                Int dataSize,
			                                                    NetIdType frontSvrNetID, 
                                                                NetIdType client_net_id, 
                                                                AccountIdType account_id );

        // �㲥����ת���ͻ������ݰ���FrontServer
		void                                    broadClientTranspondSendDataToFrontServer(
                                                                ClientNetTranspondSendDataBufferPtr& dataPtr, 
                                                                Int dataSize);
	};
}

#endif	//_S_CLIENT_NET_TRANSPOND_PACKET_PROCESSER_H_