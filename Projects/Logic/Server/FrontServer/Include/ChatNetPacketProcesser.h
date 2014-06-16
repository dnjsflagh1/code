/******************************************************************************/
#ifndef _CHATNETPACKETPROCESSER_H_
#define _CHATNETPACKETPROCESSER_H_
/******************************************************************************/
#include "ChatNetPacket.h"

/******************************************************************************/

namespace MG
{
	class ChatNetPacketProcesser
	{
	public:
		SINGLETON_INSTANCE(ChatNetPacketProcesser);
		ChatNetPacketProcesser();
		~ChatNetPacketProcesser();
        

		Bool	processClientPacket(I32 id, NetEventRecv* packet);
		Bool	processChatServerPacket(I32 id, NetEventRecv* packet);

		//��������
		void	onRecvTwoPersonChatFromClient(I32 id,PT_CHAT_C2F_TWO_PERSON_DATA* data);
		void	sendTwoPersonChatToChatServer(Byte channel,Char16* senderClanName,I32 senderNetId,Char16* recverClanName,Char8* data,U16 dataSize);
		// ͬ��ͼ
		void	onRecvOneRegionChatFromClient(I32 id,PT_CHAT_C2F_ONE_REGION_DATA* data);
		void	sendOneRegionChatToChatServer(Byte channel,Char16* senderClanName,I32 senderNetId,U32 regionId,U16 regionType,U32 mapServerId,Char8* data,U16 dataSize);
		
		//ȫ��
        void    onRecvFullServerChatFromClient(I32 id,PT_CHAT_C2F_FULL_SERVER_DATA* data);
		void	sendFullServerChatToChatServer(Byte channel,Char16* senderClanName,I32 senderNetId,Char8* data,U16 dataSize);
        

		void	onRecvChatResultFromChatServer(I32 id,PT_CHAT_A2F_RESULT_DATA* data);	
		void	sendChatResultToClient( I32 id,Byte channel,Byte chatReslt);

		
		
		
		//////////////////////////////////////////////////////////////////////////////////
		//���˷Ƿ������,���ڹ涨����ʱ����֮��
		enum FilterChatPacketType
		{
			FILTER_CHAT_PACKET_TYPE_COMMON = 1,
			FILTER_CHAT_PACKET_TYPE_FULLSERVER
		};
        //�ж��Ƿ���Ҫ���˵��˰�
		Bool   isNeedFilterIllegalPacket( FilterChatPacketType type,NetIdType netId);
		
	};
}
#endif