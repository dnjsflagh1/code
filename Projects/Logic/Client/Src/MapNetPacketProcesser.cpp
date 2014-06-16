
#include "stdafx.h"
#include "MapNetPacketProcesser.h"

namespace MG
{
	MapNetPacketProcesser::MapNetPacketProcesser()
	{

	}

	MapNetPacketProcesser::~MapNetPacketProcesser()
	{

	}

	Bool MapNetPacketProcesser::processFrontServerPacket(I32 id,NetEventRecv* packet)
	{
		if ( packet->getChannel() == GNPC_MAP )
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_MAP_M2C_BASE_INFO:
				onRecvMapBaseInfoFrommapServer( id, (PT_MAP_M2C_BASE_INFO_DATA*)data->data );
				break;
			}
			return true;
		}
		return false;
	}
	Bool MapNetPacketProcesser::processMapServerPacket(I32 id,NetEventRecv* packet)
	{
		return true;
	}

	void MapNetPacketProcesser::onRecvMapBaseInfoFrommapServer( I32 id, PT_MAP_M2C_BASE_INFO_DATA* data )
	{
		//FUNDETECTION(__MG_FUNC__);
	}
}