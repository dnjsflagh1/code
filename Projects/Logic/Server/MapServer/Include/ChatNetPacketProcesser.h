/******************************************************************************/
#ifndef _CHATNETPACKETPROCESSER_H_
#define _CHATNETPACKETPROCESSER_H_
/******************************************************************************/
#include "MapServerPreqs.h"
#include "GameNetPacket.h"
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

		Bool	processFrontServerPacket(I32 id, NetEventRecv* packet);
		Bool	processChatServerPacket(I32 id, NetEventRecv* packet);

	public:
		//void	sendChatResultToClient();
		//		Õ¨«¯”Ú¡ƒÃÏ
		void	onRecvRegionChatFromChatServer(I32 id, PT_CHAT_A2M_ONE_REGION_DATA* data);
		void	brocastOneRegionChatToClient(Byte channel,Char16* senderClanName,Char8* data,U16 dataSize,SRegionObjectBase* regionObj);
	protected:

	};

}


#endif