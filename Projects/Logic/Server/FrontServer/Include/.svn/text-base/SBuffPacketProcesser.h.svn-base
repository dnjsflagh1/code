//***************************************************************************************
#ifndef _H_SBUFFPACKETPROCESSER_
#define _H_SBUFFPACKETPROCESSER_
//***************************************************************************************
#include "FrontServerPreqs.h"
#include "BuffNetPacket.h"
//***************************************************************************************
namespace MG
{
	class SBuffPacketProcesser
	{
	public:
		SBuffPacketProcesser(){}
		~SBuffPacketProcesser(){}
		SINGLETON_INSTANCE(SBuffPacketProcesser);

	public:
		Bool	processMapServerPacket(I32 id, NetEventRecv* packet);

	public:
		//向MapServer发送DB中的Buff信息
		void	sendBuffDataListToMapServer(I32 id, PlayerCharacterIdType charId, std::map<UInt, BuffData>* pBuffDataVec);

	protected:
	private:
		//接受从mapServer来的Buff更新信息。
		void	recvBuffDataFromMapServer(I32 id, PT_BUFF_M2F_PLAYERCHARACTER_BUFFDATA_Data* pData);

	};
}
//***************************************************************************************
#endif
//***************************************************************************************