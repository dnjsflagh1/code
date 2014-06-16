//*************************************************************************************
#ifndef _PLACENETPACKETPROCESSER_H_
#define _PLACENETPACKETPROCESSER_H_
//*************************************************************************************
#include "ClientPreqs.h"
#include "PlaceNetPacket.h"
#include "GameNetEvent.h"
//*************************************************************************************
namespace MG
{
	class PlaceNetPacketProcesser
	{
	public:
		PlaceNetPacketProcesser();
		~PlaceNetPacketProcesser();
		SINGLETON_INSTANCE(PlaceNetPacketProcesser)

		Bool	processFrontServerPacket(I32 id,NetEventRecv* packet);
		void	sendPlaceClickToMapServer(IdType placeId, NetVec2 placePos, NetVec2 placeDir);
		//void	sendEnterPlaceToMapServer(IdType placeId);

		//Ω” ’
		void	onRecvPlaceInfoFromMapServer( I32 id, PT_PLACE_M2C_CLICED_INFO_DATA* data);
		//void	onRecveEnterPlaceFromFrontServer( I32 id, PT_PLACE_F2C_ENTER_RESULT_DATA* data);
	};
}

#endif