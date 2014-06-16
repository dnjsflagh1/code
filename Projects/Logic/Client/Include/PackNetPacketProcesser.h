/******************************************************************************/
#ifndef _PACKNETPACKETPROCESSER_H_
#define _PACKNETPACKETPROCESSER_H_
/******************************************************************************/
#include "ClientPreqs.h"
#include "CommonGameDefine.h"
#include "PackNetPacket.h"
#include "GameNetEvent.h"
/******************************************************************************/
namespace MG
{
	class PackNetPacketProcesser
	{
	public:
		SINGLETON_INSTANCE(PackNetPacketProcesser)

		Bool	processFrontServerPacket(I32 id,NetEventRecv* packet);

	protected:
		void    onRecvCharacterPackFromFrontServer( I32 id, PT_PACK_S2C_CHARACTER_DATA* data );

	};
}

#endif