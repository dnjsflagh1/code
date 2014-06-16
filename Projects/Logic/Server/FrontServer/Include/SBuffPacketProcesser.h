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
		//��MapServer����DB�е�Buff��Ϣ
		void	sendBuffDataListToMapServer(I32 id, PlayerCharacterIdType charId, std::map<UInt, BuffData>* pBuffDataVec);

	protected:
	private:
		//���ܴ�mapServer����Buff������Ϣ��
		void	recvBuffDataFromMapServer(I32 id, PT_BUFF_M2F_PLAYERCHARACTER_BUFFDATA_Data* pData);

	};
}
//***************************************************************************************
#endif
//***************************************************************************************