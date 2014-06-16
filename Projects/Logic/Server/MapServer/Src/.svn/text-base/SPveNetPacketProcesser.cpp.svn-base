/******************************************************************************/
#include "stdafx.h"
#include "SPveNetPacketProcesser.h"
#include "MapServerMain.h"
#include "SWorldManager.h"
#include "ServerManager.h"
#include "SPlayerManager.h"
/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	SPveNetPacketProcesser::SPveNetPacketProcesser()
	{

	}

	//--------------------------------------------------------------------------
	SPveNetPacketProcesser::~SPveNetPacketProcesser()
	{

	}

	//--------------------------------------------------------------------------
	Bool SPveNetPacketProcesser::processFrontServerPacket(I32 id, NetEventRecv* packet)
	{
		if ( packet->getChannel() == GNPC_PVE )
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_PVE_F2M_START:
				onRecvPveStartFromFrontServer( id , (PT_PVE_F2M_START_DATA*)data->data);
				break;			
			default:
				{
					DYNAMIC_ASSERT(0);
				}
				break;
			}

			return true;
		}
		return false;
	}

	void SPveNetPacketProcesser::onRecvPveStartFromFrontServer( NetIdType frontServerNetId, PT_PVE_F2M_START_DATA* data )
	{
#if 0
		SPlayerPtr player;
		if (false == SPlayerManager::getInstance().getPlayer(player, data->accountId))
		{
			return;
		}

		DYNAMIC_ASSERT(false == player.isNull());
		if ( player.isNull() )
		{
			return;
		}


		//创建副本，等待玩家进入
		//SInstanceRegion *newRegion = SWorldManager::getInstance().createInstanceRegion(ROT_PVE, data->targetRegionId, data->accountId, JUMP_NORMAL);

		//【广播给区域的人】
		GameNetSendDataBufferPtr dataPtr;
        MapServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr->getLogicData();
		if(packet)
		{
			packet->channel = GNPC_PVE;
			packet->type	= PT_PVE_M2T_START_NEW_INSTANCE;

			PT_PVE_M2T_START_NEW_INSTANCE_DATA* sendData = (PT_PVE_M2T_START_NEW_INSTANCE_DATA*)(packet->data);
			sendData->targetRegionId	= newRegion->getNewRegionObject()->getRegionId();
			sendData->targetInstanceUId	= newRegion->getInstanceUId();
			sendData->roomId			= data->roomId;

			//广播给所有的FrontServer， FrontServer也要保存一份内存
			ServerManager::getInstance().sendNetPacketToCenterServer(dataPtr, 
				GameNetPacketData_INFO::headSize + PT_PVE_M2T_START_NEW_INSTANCE_DATA_INFO::dataSize);	
		}
#endif
	}
}