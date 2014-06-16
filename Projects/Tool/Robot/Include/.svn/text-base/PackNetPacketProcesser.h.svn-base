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

		Bool	processFrontServerPacket(CClient* client,NetEventRecv* packet);

	protected:
		void    onRecvCharacterPackFromFrontServer( CClient* client, PT_PACK_S2C_CHARACTER_DATA* data );

	};
}

#endif