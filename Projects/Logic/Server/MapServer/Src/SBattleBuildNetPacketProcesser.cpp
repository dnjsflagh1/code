/******************************************************************************/
#include "stdafx.h"
#include "SBattleBuildNetPacketProcesser.h"
#include "NetTranspondPacketProcesser.h"
#include "SBuilding.h"
#include "SPlayer.h"
/******************************************************************************/
namespace MG
{
    SBattleBuildNetPacketProcesser::SBattleBuildNetPacketProcesser()
    {

    }

    //-----------------------------------------------------------------------------------
    SBattleBuildNetPacketProcesser::~SBattleBuildNetPacketProcesser()
    {

    }

	//-----------------------------------------------------------------------------------
	void SBattleBuildNetPacketProcesser::broadChangeBuildingBelongPlayerToRegion(SRegionObjectBase* targetRegion, std::map<BuildingIdType, SBuilding*>* buildingList, SPlayerPtr& belongPlayer)
	{
		NetTranspondSendDataBufferPtr dataPtr  ;
		GameNetPacketData* packet = NULL;
		PT_BUILD_M2C_CHANGE_BELONG_PLAYER_DATA* sendData = NULL;

		// 当前发送数据头大小
		I32 sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_BUILD_M2C_CHANGE_BELONG_PLAYER_INFO::headSize;
		// 当前发送数据大小
		I32 sendDataSize        = sendDataHeadSize;
		// 准备发送数据大小
		I32 prepareSendDataSize = 0;

		// 遍历角色队列
		std::map<BuildingIdType, SBuilding*>::iterator iter = buildingList->begin();

		while( buildingList->end() != iter )
		{
			//-----------------------------------------------------------------

			if ( dataPtr.mDataPtr.isNull() == false )
			{
				// 递增一个角色数据大小到发送数据缓存大小
				prepareSendDataSize = sendDataSize + PT_BUILD_M2C_CHANGE_BELONG_PLAYER_INFO::netAddMemberInfoSize;

				// 如果大于缓存最大大小则发送
				if ( prepareSendDataSize >= dataPtr.getTranspondDataMaxSize(100) )
				{
					NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(dataPtr, 
						sendDataSize, targetRegion);
					dataPtr.mDataPtr.setNull();
				}
			}

			//-----------------------------------------------------------------

			if ( dataPtr.mDataPtr.isNull() )
			{
				NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );
				packet			= (GameNetPacketData*) dataPtr.getTranspondData();
				if ( !packet )
					return;

				packet->channel = GNPC_BUILDING;
				packet->type    = PT_BUILD_M2C_CHANGE_BELONG_PLAYER;
				sendData = (PT_BUILD_M2C_CHANGE_BELONG_PLAYER_DATA*)(packet->data);
				sendData->addNum				= 0;
				sendData->targetBelongAccountId	= belongPlayer->getAccountId();

				// 当前发送数据头大小
				sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_BUILD_M2C_CHANGE_BELONG_PLAYER_INFO::headSize;
				// 当前发送数据大小
				sendDataSize        = sendDataHeadSize;
				// 准备发送数据大小
				prepareSendDataSize = sendDataHeadSize;
			}

			//-----------------------------------------------------------------

			//开始填充
			NetBuildChangeBelongPlayerInfo* tempSend = &(sendData->addMemberInfo[sendData->addNum]);
			tempSend->buildingId = iter->second->getID();


			sendDataSize += PT_BUILD_M2C_CHANGE_BELONG_PLAYER_INFO::netAddMemberInfoSize;

			++sendData->addNum;
			++iter;
		}

		//-----------------------------------------------------------------
		if ( dataPtr.mDataPtr.isNull() == false )
		{
			NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(dataPtr, 
				sendDataSize, targetRegion);
			dataPtr.mDataPtr.setNull();
		}
		
	}
}