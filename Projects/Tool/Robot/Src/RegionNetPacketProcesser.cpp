/******************************************************************************/
#include "stdafx.h"
#include "ClientNetApplyManager.h"
#include "RegionNetPacketProcesser.h"
#include "CPlayer.h"
#include "BuildingData.h"
#include "PlayerCharacterData.h"
#include "CClientNew.h"
#include "CTroopObject.h"
/******************************************************************************/
namespace MG
{

    //-----------------------------------------------------------------------------
	Bool RegionNetPacketProcesser::processFrontServerPacket(CClient *client,NetEventRecv* packet)
	{
		if ( packet->getChannel() == GNPC_REGION )
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_REGION_M2C_CREATE_APPEAR_PLAYER_CHARACTER:
				onRecvPlayerCharacterCreateAndAppear(client, (PT_REGION_M2C_CREATE_APPEAR_PLAYER_CHARACTER_DATA*)data->data);
				break;
			case PT_REGION_M2C_DESTROY_DISAPPEAR_PLAYER_CHARACTER:
				onRecvPlayerCharacterDestroyAndDisappear(client, (PT_REGION_M2C_DESTROY_DISAPPEAR_PLAYER_CHARACTER_DATA*)data->data);
				break;
			case PT_REGION_M2C_ADD_PLAYER_CHARACTER:
				onRecvPlayerCharacterEnter( client, (PT_REGION_M2C_ADD_PLAYER_CHARACTER_DATA*)data->data );
				break;
			case PT_REGION_M2C_REMOVE_PLAYER_CHARACTER:
				onRecvPlayerCharacterLeave( client, (PT_REGION_M2C_REMOVE_PLAYER_CHARACTER_DATA*)data->data );
				break;
#if 0
			case PT_REGION_M2C_ADD_TROOP_GROUP:
				onRecvTroopGroupEnter( id, (PT_REGION_M2C_ADD_TROOP_GROUP_DATA*)data->data );
				break;
			case PT_REGION_M2C_REMOVE_TROOP_GROUP:
				onRecvTroopGroupLeave( id, (PT_REGION_M2C_REMOVE_TROOP_GROUP_DATA*)data->data );
				break;
#endif
			case PT_REGION_M2C_ADD_BUILDING:
				onRecvBattleBuildingEnter( client, (PT_REGION_M2C_ADD_BUILDING_DATA*)data->data );
				break;
			case PT_REGION_M2C_REMOVE_BUILDING:
				onRecvBattleBuildingLeave( client, (PT_REGION_M2C_REMOVE_BUILDING_DATA*)data->data );
				break;
			//case PT_REGION_M2C_ADD_TRITH_PART_CHARACTER:
				//onRecvThirdPartCharacterEnter( client, (PT_REGION_M2C_ADD_TRITH_PART_CHARACTER_DATA*)data->data );
				//break;
			//case PT_REGION_M2C_ADD_CAMP:
			//	onRecvCampEnter( client, (PT_REGION_M2C_ADD_CAMP_DATA*)data->data );
			//	break;
			case PT_REGION_M2C_CREATE_TROOP:
				onRecvTroopCreate( client, (PT_REGION_M2C_CREATE_TROOP_DATA*)data->data );
				break;
			case PT_REGION_M2C_ADD_TROOP:
				onRecvTroopEnter( client, (PT_REGION_M2C_ADD_TROOP_DATA*)data->data );
				break;
			
			}
			return true;
		}
		return false;
	}
	//-----------------------------------------------------------------------------
	void RegionNetPacketProcesser::onRecvPlayerCharacterCreateAndAppear( CClient* client, PT_REGION_M2C_CREATE_APPEAR_PLAYER_CHARACTER_DATA* data )
	{
		DYNAMIC_ASSERT_LOG( data->addPlayerNum < 1000, "onRecvPlayerCharacterCreateAndAppear Too Much!" );
		for(Int i = 0; i < data->addPlayerNum; ++i)
		{
			CPlayerCharacter* character =  client->getPlayerObj()->getActiveClan()->getPlayerCharacter(data->addPlayerInfo[i].character_id);
			if (!character)
			{
				continue;
			}
			PlayerCharacterData* charData = character->getData();


			charData->mId  = data->addPlayerInfo[i].character_id;
			charData->mCharacterTemplateID = data->addPlayerInfo[i].characterTemplateID;
			charData->mDir = (Vec3)((NetVec2)data->addPlayerInfo[i].dir);
			charData->mHp = data->addPlayerInfo[i].hp;
			charData->mMp = data->addPlayerInfo[i].mp;
			charData->mName = data->addPlayerInfo[i].name;
			charData->charSurName = data->addPlayerInfo[i].surNmae;
			charData->mPos = (NetVec2)(data->addPlayerInfo[i].pos);
			charData->mBirthPos = charData->mPos;

		}

	}

	//-----------------------------------------------------------------------------
	void RegionNetPacketProcesser::onRecvPlayerCharacterDestroyAndDisappear(CClient* client, PT_REGION_M2C_DESTROY_DISAPPEAR_PLAYER_CHARACTER_DATA* data )
	{
		//CSceneManager::getInstance().destroyPlayerCharacterEntity(data->character_id);
	}
    //-----------------------------------------------------------------------------
	void RegionNetPacketProcesser::onRecvPlayerCharacterEnter( CClient *client, PT_REGION_M2C_ADD_PLAYER_CHARACTER_DATA* data )
	{
		CPlayer* myPlayer = client->getPlayerObj();
		//Campaign* campaign = myPlayer->getCampaignSystem()->getMyCampaign();

		NetAddPlayerCharacterInfo* playerCgaracterInfos = data->addPlayerInfo;

		for(Int i = 0; i < data->addPlayerNum; ++i)
		{
			//UIMessageBox::getInstance().showHint(L"新玩家 进来  ~!!!!\n");
            PlayerCharacterData pcData;
            pcData.mId  = data->addPlayerInfo[i].character_id;
            pcData.mCharacterTemplateID = data->addPlayerInfo[i].characterTemplateID;
			NetVec2 nvec2 = data->addPlayerInfo[i].dir;

            pcData.mDir = nvec2;
            pcData.mHp = data->addPlayerInfo[i].hp;
            pcData.mMp = data->addPlayerInfo[i].mp;
            pcData.mName = data->addPlayerInfo[i].name;
			nvec2 = data->addPlayerInfo[i].pos;
            pcData.mPos = nvec2;
            

			CPlayerCharacter* character = myPlayer->getPlayerCharacter(data->addPlayerInfo[i].character_id);
			if (character != NULL)
			{
				*character->getCharacterData() = pcData;
				character->setJoinRegion(true);
			}
        }

		
	}

    //-----------------------------------------------------------------------------
	void RegionNetPacketProcesser::onRecvPlayerCharacterLeave( CClient *client, PT_REGION_M2C_REMOVE_PLAYER_CHARACTER_DATA* data )
	{
		CPlayer* myPlayer = client->getPlayerObj();
		CPlayerCharacter* character = myPlayer->getPlayerCharacter(data->character_id);
		if (character != NULL)
		{
			character->setJoinRegion(false);
		}
	}

	//-----------------------------------------------------------------------------
	void RegionNetPacketProcesser::onRecvBattleBuildingEnter( CClient *client, PT_REGION_M2C_ADD_BUILDING_DATA* data )
	{
		
		
	}

	//-----------------------------------------------------------------------------
	void RegionNetPacketProcesser::onRecvBattleBuildingLeave( CClient *client, PT_REGION_M2C_REMOVE_BUILDING_DATA* data )
	{
		
	}

	//-----------------------------------------------------------------------------
	/*void RegionNetPacketProcesser::onRecvThirdPartCharacterEnter( CClient *client, PT_REGION_M2C_ADD_TRITH_PART_CHARACTER_DATA* data )
	{
		int jj = 0;
	}*/

	//-----------------------------------------------------------------------------
	void RegionNetPacketProcesser::onRecvCampEnter( CClient *client, PT_REGION_M2C_ADD_BUILDING_DATA* data )
	{
		for (Int i=0; i<data->addBuildingNum; ++i)
		{
			NetAddBuildingInfo* addCampInfo = &(data->addBuildingInfo[i]);
			int jj = 0;
		}
		int jj = 0;
	}

	//-----------------------------------------------------------------------------
	void RegionNetPacketProcesser::onRecvTroopCreate( CClient *client, PT_REGION_M2C_CREATE_TROOP_DATA* data )
	{
		//计算士兵的位子，并把结果反馈到服务器， 由服务器负责广播给其他客户端

		sendCreateTroopReturn(client->getFrontServerNetId(),data);
	}

	//-----------------------------------------------------------------------------
	void RegionNetPacketProcesser::onRecvTroopEnter( CClient *client, PT_REGION_M2C_ADD_TROOP_DATA* data )
	{
		for (Int i = 0; i < data->addTroopNum; i++)
		{
			if (client->getPlayerObj()->getAccountID() == data->addTroopInfo[i].playerId)
			{
				NetAddTroopInfo* addTroopInfo = &(data->addTroopInfo[i]);
				TroopData troopData;
				troopData.mId = data->addTroopInfo[i].troopId;
				troopData.mCharacterTemplateID = data->addTroopInfo[i].troopTemplateId;
				troopData.mPos = (NetVec2)data->addTroopInfo[i].pos;
				troopData.mHp = data->addTroopInfo[i].hp;
				troopData.mMp = data->addTroopInfo[i].mp;
				troopData.mDir = (NetVec2)data->addTroopInfo[i].dir;
				troopData.mSoldierNum = data->addTroopInfo[i].soldierNum;

				CCharacterSceneEntityDynamicData troopDynamicData;
				troopDynamicData.belongPlayerID = data->addTroopInfo[i].playerId;
				troopDynamicData.force		= (FORCE)data->addTroopInfo[i].force;
				troopDynamicData.hp			= data->addTroopInfo[i].hp;
				troopDynamicData.mp			= data->addTroopInfo[i].mp;
				troopDynamicData.hpmax		= data->addTroopInfo[i].maxHp;
				troopDynamicData.mpmax		= data->addTroopInfo[i].maxMp;
				troopDynamicData.moveSpeed  = data->addTroopInfo[i].moveSpeed;

				std::vector<Vec3> soldierPosList;

				//SLGCameraOpCtrl::getInstance().focusPos(soldierPosList[0]);

				CTroopObject* troopEntity =client->getPlayerObj()->getActiveClan()->getMainGenreal()->createTroopObject(&troopData,&troopDynamicData);
			}
			
		}

		////开始创建 军队实体z
		//for (Int i=0; i<data->addTroopNum; ++i)
		//{
		//	NetAddTroopInfo* addTroopInfo = &(data->addTroopInfo[i]);
		//	TroopData troopData;
		//	troopData.mId = data->addTroopInfo[i].troopId;
		//	troopData.mCharacterTemplateID = data->addTroopInfo[i].troopTemplateId;
		//	NetVec2 nvec2 = data->addTroopInfo[i].pos;
		//	troopData.mPos = nvec2;
		//	/*troopData.mPos.x = data->addTroopInfo[i].pos.x;
		//	troopData.mPos.z = data->addTroopInfo[i].pos.z;*/
		//	troopData.mHp = data->addTroopInfo[i].hp;
		//	troopData.mMp = data->addTroopInfo[i].mp;
		//	troopData.mDir.x = 1; //data->addTroopInfo[i].dir.x;
		//	troopData.mDir.z = 1;//data->addTroopInfo[i].dir.z;
		//	troopData.mSoldierNum = data->addTroopInfo[i].soldierNum;

		//	CCharacterSceneEntityDynamicData troopDynamicData;
		//	troopDynamicData.belongPlayerID = data->addTroopInfo[i].playerId;
		//	troopDynamicData.force		= (FORCE)data->addTroopInfo[i].force;
		//	troopDynamicData.hp			= data->addTroopInfo[i].hp;
		//	troopDynamicData.mp			= data->addTroopInfo[i].mp;
		//	troopDynamicData.hpmax		= data->addTroopInfo[i].maxHp;
		//	troopDynamicData.mpmax		= data->addTroopInfo[i].maxMp;

		//	Vec3 soldierPos;
		//	std::vector<Vec3> soldierPosList;

		//	for(UInt i = 0; i < addTroopInfo->soldierNum; ++i)
		//	{
		//		NetVec2 nvec2 = addTroopInfo->soldierPos[i];
		//		soldierPos = nvec2;
		//		soldierPosList.push_back(soldierPos);
		//	}

		//	//SLGCameraOpCtrl::getInstance().focusCamera(soldierPosList[0]);

		//	client->getPlayerObj()->getActiveClan()->getMainGenreal()->createTroopObject(&troopData, &troopDynamicData, soldierPosList);

		//	//Char16 szMessage[100] = { 0 };
		//	//MGStrOp::sprintf( szMessage, 100, L"onRecvTroopEnter mId[%d]", troopData.mId);

		//	//UIMessageBox::getInstance().showHint(szMessage);
		//}
	}

	//-----------------------------------------------------------------------------
	void RegionNetPacketProcesser::sendCreateTroopReturn(I32 frontServerNetId,PT_REGION_M2C_CREATE_TROOP_DATA* data)
	{
		//Vec3 centerPos = NetVec2(data->pos);
		//*centerPos.x = data->pos.x;
		//centerPos.z = data->pos.z;*/

		//Vec3 dir = Vec3(1/*data->dir.x*/, 0, NetVec2(data->dir).getY());//battleBuildingEntity->getDir();
		//std::vector<Vec3> soldierPosList;
		//UInt intervalRow = 3;
		//UInt intervalCol = 3;
		//UInt colNum = (sqrt((Flt)data->soldierNum / 2))* 2;
		//UInt rowNum = data->soldierNum / colNum;
		//if(colNum * rowNum < data->soldierNum)
		//{
		//	rowNum++;
		//}

		//Vec3 colDir = MGMath::rotateVector(dir, (Flt)90 * (MG_PI / 180));

		//Flt offsetRow = 0;
		//Flt offsetCol = 0;

		//if(colNum % 2 == 1)
		//{
		//	offsetCol = colNum / 2;
		//}
		//else
		//{
		//	offsetCol = (Flt)colNum / 2 - 0.5;
		//}

		//if(rowNum % 2 == 1)
		//{
		//	offsetRow = rowNum / 2;
		//}
		//else
		//{
		//	offsetRow = (Flt)rowNum / 2 - 0.5;
		//}

		//Vec3 startPoint = centerPos + dir * offsetRow * intervalRow + colDir * offsetCol * intervalCol;
		//startPoint.y = 0;
		//Vec3 elementPos = startPoint;

		//Flt col = 0;
		//Flt colGap = 0;
		//Flt rowGap = 0;
		//Vec3 tempPos;

		//for(UInt i = 0; i < data->soldierNum; ++i)
		//{
		//	elementPos = startPoint - colDir * col * intervalCol;
		//	elementPos.y = 0;
		//	soldierPosList.push_back(elementPos);

		//	col++;

		//	if(col == colNum)
		//	{
		//		startPoint = startPoint - dir * intervalRow;
		//		col = 0;
		//	}
		//}

		//// 获得一个发送【服务端】缓存
		//GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		//// 转换成标准包格式
		//GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		//if ( packet )
		//{
		//	// 设置标签
		//	packet->channel = GNPC_REGION;
		//	packet->type    = PT_REGION_C2F_CREATE_TROOP_RET;

		//	// 转换逻辑包
		//	PT_REGION_C2F_CREATE_TROOP_RET_DATA* sendData = (PT_REGION_C2F_CREATE_TROOP_RET_DATA*)(packet->data);
		//	if ( sendData )
		//	{
		//		// 填充逻辑包
		//		sendData->troopId	 = data->troopId;
		//		/*sendData->pos.x 	 = data->pos.x;
		//		sendData->pos.z 	 = data->pos.z;*/
		//		sendData->pos = (NetVec2(data->pos)).getData();
		//		sendData->regionId	 = data->regionId;
		//		sendData->regionType = data->regionType;
		//		sendData->instanceId = data->instanceId;
		//		sendData->soldierNum = soldierPosList.size();

		//		for(UInt i = 0; i < soldierPosList.size(); ++i)
		//		{
		//			/*sendData->soldierPos[i].x = soldierPosList[i].x;
		//			sendData->soldierPos[i].z = soldierPosList[i].z;*/
		//			NetVec2 nvec2 = soldierPosList[i];
		//			sendData->soldierPos[i] = nvec2.getData();
		//		}

		//		// 发送数据
		//		ClientNetApplyManager::getInstance().sendFrontServerPacket( frontServerNetId,dataPtr , 
		//			GameNetPacketData_INFO::headSize + PT_REGION_C2F_CREATE_TROOP_RET_DATA_INFO::dataSize(sendData) );
		//	}
		//}


		Vec3 centerPos;
		centerPos = NetVec2(data->pos);
		Vec3 dir = (NetVec2)data->dir;
		std::vector<Vec3> troopPosList;

		UInt colNum = (sqrt((Flt)data->troopNum / 2))* 2;
		UInt rowNum = data->troopNum / colNum;
		if(colNum * rowNum < data->troopNum)
		{
			rowNum++;
		}

		Flt patherRadius = 10;

		UInt intervalRow = patherRadius * 2 ;
		UInt intervalCol = intervalRow;


		Vec3 colDir = MGMath::rotateVector(dir, (Flt)90 * (MG_PI / 180));

		Flt offsetRow = 0;
		Flt offsetCol = 0;

		if(colNum % 2 == 1)
		{
			offsetCol = colNum / 2;
		}
		else
		{
			offsetCol = (Flt)colNum / 2 - 0.5;
		}

		if(rowNum % 2 == 1)
		{
			offsetRow = rowNum / 2;
		}
		else
		{
			offsetRow = (Flt)rowNum / 2 - 0.5;
		}

		Vec3 startPoint = centerPos + dir * offsetRow * intervalRow + colDir * offsetCol * intervalCol;
		startPoint.y = 0;
		Vec3 elementPos = startPoint;

		Flt col = 0;
		Flt colGap = 0;
		Flt rowGap = 0;
		Vec3 tempPos;

		for(UInt i = 0; i < data->troopNum; ++i)
		{
			elementPos = startPoint - colDir * col * intervalCol;
			elementPos.y = 0;
			troopPosList.push_back(elementPos);

			col++;

			if(col == colNum)
			{
				startPoint = startPoint - dir * intervalRow;
				col = 0;
			}
		}

		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_REGION;
			packet->type    = PT_REGION_C2F_CREATE_TROOP_RET;

			// 转换逻辑包
			PT_REGION_C2F_CREATE_TROOP_RET_DATA* sendData = (PT_REGION_C2F_CREATE_TROOP_RET_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->troopGroupId	 = data->troopGroupId;
				sendData->regionId	 = data->regionId;
				sendData->regionType = data->regionType;
				sendData->instanceId = data->instanceId;
				sendData->troopNum = troopPosList.size();

				for(UInt i = 0; i < troopPosList.size(); ++i)
				{
					sendData->troopPos[i] = ((NetVec2)troopPosList[i]).getData();
				}

				// 发送数据
				ClientNetApplyManager::getInstance().sendFrontServerPacket(frontServerNetId, dataPtr , 
					GameNetPacketData_INFO::headSize + PT_REGION_C2F_CREATE_TROOP_RET_INFO::dataSize(sendData) );
			}
		}
	
	}

	void RegionNetPacketProcesser::sendAddTroopTest( I32 frontServerId ,AccountIdType accountId)
	{
		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_REGION;
			packet->type    = PT_REGION_C2M_ADD_TROOP_TEST;

			// 转换逻辑包
			PT_REGION_C2M_ADD_TROOP_TEST_DATA* sendData = (PT_REGION_C2M_ADD_TROOP_TEST_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->accountId = accountId;

				// 发送数据
				ClientNetApplyManager::getInstance().sendFrontServerPacket(frontServerId, dataPtr , 
					GameNetPacketData_INFO::headSize + PT_REGION_C2M_ADD_TROOP_TEST_INFO::dataSize );
			}
		}
	}
}