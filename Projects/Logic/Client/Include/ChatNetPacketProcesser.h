//*************************************************************************************
#ifndef _CHATNETPACKETPROCESSER_H_
#define _CHATNETPACKETPROCESSER_H_
//*************************************************************************************
#include "ClientPreqs.h"
#include "ChatNetPacket.h"
#include "GameNetEvent.h"
//*************************************************************************************
namespace MG
{
	class ChatNetPacketProcesser
	{
	public:
		ChatNetPacketProcesser();
		~ChatNetPacketProcesser();
		SINGLETON_INSTANCE(ChatNetPacketProcesser)

		Bool	processFrontServerPacket(I32 id,NetEventRecv* packet);
		Bool	processMapServerPacket(I32 id,NetEventRecv* packet);

		void	sendTwoPersonChatToFrontServer( U32 channelId,CChar16* senderClanName,CChar16* recvClanName, Char8* chatData,I32 size );
		void	onRecvTwoPersonChatContentFromChatServer(I32 id, PT_CHAT_A2C_TWO_PERSON_DATA* data);

		void	sendOneRegionChatToFrontServer( U32 channelId,CChar16* senderClanName,RegionIdType regionId,REGION_OBJ_TYPE regionType,Char8* chatData,I32 size );
		void	onRecvOneRegionContentFromMapServer(I32 id, PT_CHAT_M2C_ONE_REGION_DATA* data);

		void	sendTwoPersonChatToFrontServer( U32 channelId,CChar16* senderClanName, Char8* chatData,I32 size);
		void	onRecvChatResultFromFrontServer(I32 id, PT_CHAT_F2C_RESULT_DATA* data);
		//void	onRecvChatResultFromMapServer

		void    sendFullServerChatToFrontServer(U32 channelID,CChar16* senderClanName,Char8* chatData,I32 size);
		void    onRecvFullServerChatContentFromChatServer(I32 id, PT_CHAT_A2C_FULL_SERVER_DATA* data);
	};
}

#endif	
