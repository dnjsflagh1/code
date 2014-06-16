/******************************************************************************/
#ifndef _CHATNETPACKETPROCESSER_H_
#define _CHATNETPACKETPROCESSER_H_
/******************************************************************************/
#include "ChatNetPacket.h"
#include "ClientManager.h"
/******************************************************************************/

namespace MG
{
	class ChatNetPacketProcesser
	{
	public:
		SINGLETON_INSTANCE(ChatNetPacketProcesser);
		ChatNetPacketProcesser();
		~ChatNetPacketProcesser();

		Bool	processFrontPacket(I32 id, NetEventRecv* packet);
		
		// 发送聊天结果
		void	sendChatResultToFrontServer(I32 id, Byte channel,I32 senderNetIdInFrontServer,Byte result);
		
		// 关系聊天
		void	onRecvTwoPersonChatFromFrontServer(I32 id, PT_CHAT_F2A_TWO_PERSON_DATA* data);
		void	sendTwoPersonChatContentToClient(Byte channel, Char16* senderClanName,Char8* data,U16 dataSize,ClientObject* recvClientObj);
	
		// 范围聊天
		void	onRecvOneRegionChatFromFrontServer(I32 id, PT_CHAT_F2A_ONE_REGION_DATA* data);
		void	sendOneRegionChatToMapServer(NetIdType mapServerNetId,Byte channel, Char16* senderClanName,U64 accountId,Char8* data,U16 dataSize);	

		//全服聊天
		void	onRecvFullServerChatFromFrontServer(I32 id, PT_CHAT_F2A_FULL_SERVER_DATA* data);
		void	sendFullServerChatContentToClient(Byte channel, Char16* senderClanName,Char8* data,U16 dataSize);   
	 };
}
#endif