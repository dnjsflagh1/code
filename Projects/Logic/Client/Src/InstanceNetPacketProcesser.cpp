
/******************************************************************************/

#include "stdafx.h"
#include "InstanceNetPacketProcesser.h"
#include "InstanceNetPacket.h"
#include "UITiroChangeInstance.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	InstanceNetPacketProcesser::InstanceNetPacketProcesser()
	{

	}

	//--------------------------------------------------------------------------
	InstanceNetPacketProcesser::~InstanceNetPacketProcesser()
	{

	}

	//--------------------------------------------------------------------------
	Bool InstanceNetPacketProcesser::processFrontServerPacket(I32 id, NetEventRecv *packet)
	{
		if ( packet->getChannel() == GNPC_INSTANCE )
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			//case PT_INSTANCE_M2C_TIRO_LIST:
			//	onRecvTiroListFromFrontServer( id, (PT_INSTANCE_M2C_TIRO_LIST_DATA*)data->data );
			//	break;

			}
			return true;
		}
		return false;
	}

	//--------------------------------------------------------------------------
	void InstanceNetPacketProcesser::sendTiroListPacketToFrontServer()
	{
	}
#if 0
	//--------------------------------------------------------------------------
	void InstanceNetPacketProcesser::onRecvTiroListFromFrontServer( I32 id , PT_PLAYER_M2C_TIRO_LIST_DATA* data )
	{

		for (Int i=0; i<data->addTiroNum; ++i)
		{
			NetAddTiroInfo* addTiroInfo = &(data->tiroInfo[i]);
			DYNAMIC_ASSERT(NULL != addTiroInfo);

			UIInstanceInfo instanceInfo;
			instanceInfo.regionId		= data->regionId;
			instanceInfo.regionType		= data->regionType;

			instanceInfo.instanceId		= addTiroInfo->instanceId;
			instanceInfo.curPlayerNum	= addTiroInfo->curPlayerNum;
			instanceInfo.maxPlayerNum	= addTiroInfo->maxPlayerNum;


			UITiroChangeInstance::getInstance().addInstanceInfo(&instanceInfo);
		}

		UITiroChangeInstance::getInstance().openGui();
		UITiroChangeInstance::getInstance().UIReFresh();

	}
#endif
}