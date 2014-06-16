/******************************************************************************/
#include "stdafx.h"
#include "ServerStateNetPacketProcesser.h"
/******************************************************************************/
namespace MG
{
	Bool MG::ServerStateNetPacketProcesser::processMapServerPacket( I32 id,NetEventRecv* packet )
	{
		return false;
	}

	Bool MG::ServerStateNetPacketProcesser::processFrontServerPacket( I32 id,NetEventRecv* packet )
	{
		return false;
	}
}

