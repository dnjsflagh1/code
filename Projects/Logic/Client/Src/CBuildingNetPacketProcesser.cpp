//**********************************************************************************************************
#include "stdafx.h"
#include "CBuildingNetPacketProcesser.h"
#include "CBuildingEntity.h"
#include "CBattleBuild.h"
#include "CSceneManager.h"
#include "HeadDamageManage.h"
//**********************************************************************************************************
namespace  MG
{
	//-----------------------------------------------------------------------
    CBuildingNetPacketProcesser::CBuildingNetPacketProcesser()
    {

    }

	//-----------------------------------------------------------------------
    CBuildingNetPacketProcesser::~CBuildingNetPacketProcesser()
    {

    }

	//-----------------------------------------------------------------------
    Bool CBuildingNetPacketProcesser::processFrontServerPacket( I32 id,NetEventRecv* packet )
    {
        if ( packet->getChannel() == GNPC_BUILDING )
        {
            GameNetPacketData* data = (GameNetPacketData*)(packet->getData());
			switch (data->type)
			{
			case PT_BUILD_M2C_CHANGE_BELONG_PLAYER:
				onRecvChangeBelongPlayer( id, (PT_BUILD_M2C_CHANGE_BELONG_PLAYER_DATA*)data->data );
				break;
			}
			return true;
        }

        return false;
    }

	//-----------------------------------------------------------------------
	void CBuildingNetPacketProcesser::onRecvChangeBelongPlayer( I32 id, PT_BUILD_M2C_CHANGE_BELONG_PLAYER_DATA* data )
	{
		CBuildingEntity* buildingEntity = NULL;
		for(UInt i = 0; i < data->addNum; ++i)
		{
			buildingEntity = CSceneManager::getInstance().getBuildingEntity(data->addMemberInfo[i].buildingId);
			if(!buildingEntity)
			{
				continue;
			}

			buildingEntity->getDynamicData()->belongPlayerID = data->targetBelongAccountId;
		}
	}
}