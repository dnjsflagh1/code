//**********************************************************************************************************
#ifndef _CBATTLEBUILDNETPACKETPROCESSER_H_
#define _CBATTLEBUILDNETPACKETPROCESSER_H_
//**********************************************************************************************************
#include "ClientPreqs.h"
#include "BuildNetPacket.h"
#include "GameNetEvent.h"

//**********************************************************************************************************

namespace MG
{
    class CBuildingNetPacketProcesser
    {
    public:
        CBuildingNetPacketProcesser();
        ~CBuildingNetPacketProcesser();
        SINGLETON_INSTANCE(CBuildingNetPacketProcesser)

    public:
        Bool	processFrontServerPacket(I32 id,NetEventRecv* packet);

		void	onRecvChangeBelongPlayer( I32 id, PT_BUILD_M2C_CHANGE_BELONG_PLAYER_DATA* data );

    };
}

#endif	//_CBATTLEBUILDNETPACKETPROCESSER_H_
