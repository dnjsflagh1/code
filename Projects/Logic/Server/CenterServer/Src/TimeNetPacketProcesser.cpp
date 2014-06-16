/******************************************************************************/
#include "stdafx.h"
#include "TimeNetPacketProcesser.h"
#include "CenterGameTimeSystem.h"
/******************************************************************************/
namespace MG
{
	Bool MG::TimeNetPacketProcesser::processMapServerPacket( I32 id,NetEventRecv* packet )
	{
		if (packet->getChannel() == GNPC_TIME)
		{   
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_TIME_S2E_GET:	
				onRecvGetTime( id );
				break;
			}

			return true;
		}
		return false;
	}

	Bool MG::TimeNetPacketProcesser::processFrontServerPacket( I32 id,NetEventRecv* packet )
	{
		if (packet->getChannel() == GNPC_TIME)
		{   
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_TIME_S2E_GET:	
				onRecvGetTime( id);
				break;
			}

			return true;
		}
		return false;
	}
	TimeNetPacketProcesser::TimeNetPacketProcesser()
	{

	}
	TimeNetPacketProcesser::~TimeNetPacketProcesser()
	{

	}

	void TimeNetPacketProcesser::onRecvGetTime( I32 id )
	{
		CenterGameTimeSystem::getInstance().syncTimeToAllServer(CenterGameTimeSystem::getInstance().getCurrActualTime());
	}

}

