//***************************************************************************************
#ifndef _H_SBUFFPACKETPROCESSER_
#define _H_SBUFFPACKETPROCESSER_
//***************************************************************************************
#include "MapServerPreqs.h"
#include "BuffNetPacket.h"
//***************************************************************************************
namespace MG
{
	class SBuffPacketProcesser
	{
	public:
		SBuffPacketProcesser(){;}
		~SBuffPacketProcesser(){;}
		SINGLETON_INSTANCE(SBuffPacketProcesser);

	public:
		Bool	processFrontServerPacket(I32 id, NetEventRecv* packet);

	public:
		//发送buff给FrontServer更新DB
		void	sendBuffDataToFrontServer(I32 frontId, IdType accountId, PlayerCharacterIdType charId, BuffData* pBuffData );
		//同步playercharacterBUff列表到客户端
		void	syncPlayerCharacterBuffDataListToClient(SPlayerCharacter* pSPlayerCharacter, Bool isFilterSelf = false);
		//同步playercharacterBUff到客户端
		void	syncPlayerCharacterBuffDataToClient(SPlayerCharacter* pSPlayerCharacter, UInt buffId, UInt addNum, UInt useTime);

	protected:
	private:
		//接受从DB加载的Buff信息
		void	recvBuffDataListFromFrontServer(I32 id, PT_BUFF_F2M_PLAYERCHARACTER_BUFFDATA_LIST_Data* pData);

	};
}
//***************************************************************************************
#endif
//***************************************************************************************