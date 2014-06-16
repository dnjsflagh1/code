#ifndef _MAPNETPACKETPROCESSER_H_
#define _MAPNETPACKETPROCESSER_H_

#include "ClientPreqs.h"
#include "MapNetPacket.h"
#include "GameNetEvent.h"		//???

namespace MG
{
	class MapNetPacketProcesser
	{
	public:
		MapNetPacketProcesser();
		~MapNetPacketProcesser();
		SINGLETON_INSTANCE(MapNetPacketProcesser)

		Bool	processFrontServerPacket(I32 id,NetEventRecv* packet);
		Bool	processMapServerPacket(I32 id,NetEventRecv* packet);

		//Ω” ’

		void	onRecvMapBaseInfoFrommapServer( I32 id, PT_MAP_M2C_BASE_INFO_DATA* data );
	};
}

#endif	//_MAPNETPACKETPROCESSER_H_
