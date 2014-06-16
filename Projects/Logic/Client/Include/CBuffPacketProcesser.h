//***************************************************************************************
#ifndef _H_CBUFFPACKETPROCESSER_
#define _H_CBUFFPACKETPROCESSER_
//***************************************************************************************
#include "ClientPreqs.h"
#include "BuffNetPacket.h"
//***************************************************************************************
namespace MG
{
	class CBuffPacketProcesser
	{
	public:
		CBuffPacketProcesser(){;}
		~CBuffPacketProcesser(){;}
		SINGLETON_INSTANCE(CBuffPacketProcesser);

	public:
		Bool	processFrontServerPacket(I32 id, NetEventRecv* packet);

	protected:
	private:
		void	recvPlayerCharacterBuffDataListFromMapServer(I32 id, PT_BUFF_M2C_PLAYERCHARACTER_BUFFDATA_LIST_Data* pData);
		void	recvPlayerCharacterBuffDataFromMapServer(I32 id, PT_BUFF_M2C_PLAYERCHARACTER_BUFFDATA_Data* pData);
	};
}
//***************************************************************************************
#endif
//***************************************************************************************