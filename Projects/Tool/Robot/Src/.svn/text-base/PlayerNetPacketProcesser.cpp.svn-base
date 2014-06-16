
/******************************************************************************/
#include "stdafx.h"
#include "ClientNetApplyManager.h"
#include "PlayerNetPacketProcesser.h"
//#include "CSceneManager.h"
//#include "LoginManager.h"
#include "CPlayer.h"
//#include "UIArmyFunction.h"
//#include "UIGenrealPicture.h"
//#include "UIMessageBox.h"

#include "PlayerCharacterData.h"

//#include "UITiroChangeInstance.h"
#include "CClientNew.h"
/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	Bool PlayerNetPacketProcesser::processFrontServerPacket(CClient* client, NetEventRecv *packet)
	{
        if ( packet->getChannel() == GNPC_PLAYER )
        {
            GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

            switch (data->type)
            {
            case PT_PLAYER_F2C_PLAYERCHARACTER_INFO_LIST:
                onRecvClientGenrealInfoFromFrontServer( client, (PT_PLAYER_F2C_PLAYERCHARACTER_INFO_LIST_DATA*)data->data );
                break;
			case PT_PLAYER_F2C_JUMP_REGION:
				onRecvPlayerJumpMap( client, (PT_PLAYER_F2C_JUMP_REGION_DATA*)data->data );
				break;
			//case PT_PLAYER_F2C_JUMP_REGION_ERROR:
			//	onRecvPlayerJumpMapError(id, (PT_PLAYER_F2C_JUMP_REGION_ERROR_DATA*)data->data);
			//	break;
			case PT_PLAYER_M2C_REMAIN_PLAYERCHARACTER_LIST:
				onRecvRemainPlayerCharacterListFromMapServer( client, (PT_PLAYER_M2C_REMAIN_PLAYERCHARACTER_LIST_DATA*)data->data );
				break;
            case PT_PLAYER_F2C_TROOP_INFO_LIST:
                onRecvClientTroopListFromFrontServer(client, (PT_PLAYER_F2C_TROOP_INFO_LIST_DATA*)data->data);
                break;
			case PT_PLAYER_M2C_TIRO_LIST:
				onRecvTiroListFromMapServer(client, (PT_PLAYER_M2C_TIRO_LIST_DATA*)data->data);
				break;
			//case PT_PLAYER_M2C_JUMP_REGION:
			//	onRecvPlayerJumpMapFromMapServer( id, (PT_PLAYER_M2C_JUMP_REGION_DATA*)data->data );
			//	break;
            }
            return true;
        }
		return false;
	}
    //-----------------------------------------------------------------------------
	void PlayerNetPacketProcesser::onRecvRemainPlayerCharacterListFromMapServer( CClient* client, PT_PLAYER_M2C_REMAIN_PLAYERCHARACTER_LIST_DATA* data )
	{
		//FUNDETECTION(__MG_FUNC__);
		int kk = 0;
	}
    //-----------------------------------------------------------------------------
    void PlayerNetPacketProcesser::onRecvClientGenrealInfoFromFrontServer( CClient* client, PT_PLAYER_F2C_PLAYERCHARACTER_INFO_LIST_DATA* data )
    {
		//FUNDETECTION(__MG_FUNC__);
        CClan* pClan = client->getPlayerObj()->getActiveClan();
        assert(pClan);
        CPlayerCharacter* pCPlayerCharacter = NULL;
        Int nCount = data->remainPlayerCharacterNum;

        for (Int i=0; i<nCount; i++)
        {
			PlayerCharacterData playerCharacterData;
			playerCharacterData.mId                 	= data->remainPlayerCharacter[i].Id                     ;
			playerCharacterData.charClanId          	= data->remainPlayerCharacter[i].charClanId             ;
			playerCharacterData.mPos                	= (NetVec2)data->remainPlayerCharacter[i].genrealPos    ;
			playerCharacterData.mName               	= data->remainPlayerCharacter[i].name                   ;
			playerCharacterData.mRegionType         	= (REGION_OBJ_TYPE)data->remainPlayerCharacter[i].regionType;
			playerCharacterData.mRegionID           	= data->remainPlayerCharacter[i].regionId		        ;
			playerCharacterData.mCharacterTemplateID	= data->remainPlayerCharacter[i].characterTemplateID	;
			playerCharacterData.charCurAge          	= data->remainPlayerCharacter[i].charCurAge			    ;
			playerCharacterData.mLevel              	= data->remainPlayerCharacter[i].charLvl				;
			playerCharacterData.charExp1            	= data->remainPlayerCharacter[i].charExp1	            ;
			playerCharacterData.charExp2            	= data->remainPlayerCharacter[i].charExp2		        ;
			playerCharacterData.charExp3            	= data->remainPlayerCharacter[i].charExp3				;
			playerCharacterData.mHp						= data->remainPlayerCharacter[i].charHP					;
			playerCharacterData.mMp						= data->remainPlayerCharacter[i].charMP					;
			playerCharacterData.mLineageNum				= data->remainPlayerCharacter[i].charLineageNum	        ;
			playerCharacterData.charArtMashID1			= data->remainPlayerCharacter[i].charArtMashID1		    ;
			playerCharacterData.charArtMashID2        	= data->remainPlayerCharacter[i].charArtMashID2			;
			playerCharacterData.charArtIcon           	= data->remainPlayerCharacter[i].charArtIcon			;
			playerCharacterData.charInfluenceID       	= data->remainPlayerCharacter[i].charInfluenceID		;
			playerCharacterData.charSkillPointAll     	= data->remainPlayerCharacter[i].charSkillPointAll		;
			playerCharacterData.charNoAssignSkillPoint	= data->remainPlayerCharacter[i].charNoAssignSkillPoint	;
			playerCharacterData.charState             	= (CHAR_STATE)data->remainPlayerCharacter[i].charState	;
			playerCharacterData.charLifeState         	= (CHAR_LIFE_STATE)data->remainPlayerCharacter[i].charLifeState;
			playerCharacterData.mDir                  	= (NetVec2)data->remainPlayerCharacter[i].charDir		;
			playerCharacterData.charSurName           	=  data->remainPlayerCharacter[i].surName;              ;

            for (Int j=0; j<DB_RECORD_ATTR_NUM; j++)
            {
                playerCharacterData.charAttrRand[j] = data->remainPlayerCharacter[i].attrRand[j];
                playerCharacterData.charAttrRandAdd[j] = data->remainPlayerCharacter[i].attrRandAdd[j];
            }

			Bool isFirst = true;
            pCPlayerCharacter = pClan->addPlayerCharacter( &playerCharacterData);
            assert(pCPlayerCharacter);
            
            //暂时写在这，
			if ( isFirst )
				pCPlayerCharacter->init(&playerCharacterData);
        }

        //LoginManager::getInstance().handleGenrealInfo();
    }

	//-----------------------------------------------------------------------------
	void PlayerNetPacketProcesser::sendPrintTest(I32 frontServerNetId)
	{
		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_PLAYER;
			packet->type    = PT_PLAYER_C2F_PRINT_TEST;

			// 发送数据
			ClientNetApplyManager::getInstance().sendFrontServerPacket( frontServerNetId,dataPtr , GameNetPacketData_INFO::headSize);
				
		}
	}

	//-----------------------------------------------------------------------------
	void PlayerNetPacketProcesser::sendTiroList(I32 frontServerNetId,RegionIdType regionId, REGION_OBJ_TYPE regionType)
	{
		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_PLAYER;
			packet->type    = PT_PLAYER_C2F_TIRO_LIST;

			// 转换逻辑包
			PT_PLAYER_C2F_TIRO_LIST_DATA* sendData = (PT_PLAYER_C2F_TIRO_LIST_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				/*sendData->regionId	= regionId;
				sendData->regionType = regionType;*/

				// 发送数据
				ClientNetApplyManager::getInstance().sendFrontServerPacket( frontServerNetId,dataPtr , 
					GameNetPacketData_INFO::headSize + PT_PLAYER_C2F_TIRO_LIST_INFO::dataSize );
			}
		}
	}

    //-----------------------------------------------------------------------------
	void PlayerNetPacketProcesser::sendPlayerEnterRegion(I32 frontServerNetId,RegionIdType regionId, REGION_OBJ_TYPE regionType)
	{
        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_PLAYER;
            packet->type    = PT_PLAYER_C2F_JUMP_REGION;

            // 转换逻辑包
            PT_PLAYER_C2F_JUMP_REGION_DATA* sendData = (PT_PLAYER_C2F_JUMP_REGION_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                sendData->regionId = regionId;
               // sendData->regionType = regionType;

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket( frontServerNetId,dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_PLAYER_C2F_JUMP_REGION_INFO::dataSize );
            }
        }
	
    }
    //-----------------------------------------------------------------------------
	//void PlayerNetPacketProcesser::OnRecvPlayerEnterMapScene()
	//{
	//	CSceneManager::getInstance().loadScene(0, smt_map);
	//	CWorldManager::getInstance().loadCurrMapObjData(0);
	//}
    //-----------------------------------------------------------------------------
	void PlayerNetPacketProcesser::onRecvPlayerJumpMap(CClient* client, PT_PLAYER_F2C_JUMP_REGION_DATA* data)
	{
		if (data->jumpResult != PlayerJump_Success)
		{
			/*wchar_t errorHint[32] = L"";
			swprintf( errorHint, L"摄像机跳转副本失败 regionType[%d],regionId[%I64i], instanceUid[%I64i]", 
				data->regionType,data->regionId,data->instanceUid);

			std::wstring str(errorHint);
			UIMessageBox::getInstance().showHint(str);*/
			return;
		}
		
		//FUNDETECTION(__MG_FUNC__);
        CClan* pClan = client->getPlayerObj()->getActiveClan();
		DYNAMIC_ASSERT(pClan);
		if (!pClan)
		{
			return;
		}
		ClanData* pData = pClan->getData();
		DYNAMIC_ASSERT(pData);
        pData->regionID = data->regionId;
        pData->regionType = (REGION_OBJ_TYPE)data->regionType;
		pData->instanceUId = (REGION_OBJ_TYPE)data->instanceUid;

		//CSceneManager::getInstance().loadRegionScene(pData->regionID, (REGION_OBJ_TYPE)(pData->regionType));	//yuanlinhu
		MG_LOG(out_error,"-----regionID = %d---type = %d----副本ID = %d---\n",pData->regionID,pData->regionType,pData->instanceUId);
		client->getPlayerObj()->setInstanceUid(data->instanceUid);

		//关闭战斗相关界面
		/*CClan* clan = client->getPlayerObj()->getActiveClan();
		CPlayerCharacter* chara = clan->getPlayerCharacterByIndex(0);
		DYNAMIC_ASSERT(chara);
		chara->getTroopList()->clear();*/
        
		//UIArmyFunction::getInstance().closeGui();
        //if ( chara )
        /*{  
			UIGenrealPicture::getInstance().openUIGenrealPicture( chara->getID() );  
        }*/

		//CWorldManager::getInstance().loadCurrPlaceObjData(0);

		//UIMessageBox::getInstance().showHint(L"[玩家]跳转地图成功");
	}

	////-----------------------------------------------------------------------------
	//void PlayerNetPacketProcesser::onRecvPlayerJumpMapError(I32 id, PT_PLAYER_F2C_JUMP_REGION_ERROR_DATA* data)
	//{
	//	switch(data->error)
	//	{
	//	case Player_Jump_server_crash:
	//		{
	//			UIMessageBox::getInstance().showHint(L"[玩家]跳转地图失败， MapServer当机");
	//		}
	//		break;
	//	}
	//}

    //-----------------------------------------------------------------------------
    void PlayerNetPacketProcesser::onRecvClientTroopListFromFrontServer( CClient* client, PT_PLAYER_F2C_TROOP_INFO_LIST_DATA* data )
    {
		//FUNDETECTION(__MG_FUNC__);
		CClan* pClan =client->getPlayerObj()->getActiveClan();
		assert(pClan);
        
       // CPlayerTroopGroup* tempTroopGroup = NULL;

        //for (Int i=0; i<data->troopNum; i++)
        //{
        //    TroopGroupData tempTroopGroupData;
        //    tempTroopGroupData.mID = data->troopInfo[i].Id;
        //    tempTroopGroupData.ArmyTemplateId = data->troopInfo[i].troopTemplateID;
        //    tempTroopGroupData.MasterId = data->troopInfo[i].charClanId;
        //    tempTroopGroupData.MasterType = TROOP_MASTER_TYPE_PLACEOBJ;
        //    tempTroopGroupData.mName = data->troopInfo[i].troopName;

        //    pClan->addPlayerTroopGroup(&tempTroopGroupData);
        //}
    }

	//-----------------------------------------------------------------------------
	//void PlayerNetPacketProcesser::onRecvPlayerJumpMapFromMapServer( I32 id, PT_PLAYER_M2C_JUMP_REGION_DATA* data )
	//{
	//	//FUNDETECTION(__MG_FUNC__);
	//	CClan* pClan = CPlayer::getInstance().getActiveClan();
	//	assert(pClan);
	//	ClanData* pData = pClan->getData();
	//	assert(pData);
	//	pData->regionID = data->regionId;
	//	pData->regionType = data->regionType;

	//	CSceneManager::getInstance().loadRegionScene(pData->regionID, (REGION_OBJ_TYPE)(pData->regionType));

	//	//关闭战斗相关界面
	//	CClan* clan = CPlayer::getInstance().getActiveClan();
	//	CPlayerCharacter* chara = clan->getPlayerCharacterByIndex(0);
	//	//UIArmyFunction::getInstance().closeGui();
    //  if ( chara )
	//	    UIGenrealPicture::getInstance().openUIGenrealPicture( chara->getID() );
	//}


	//-----------------------------------------------------------------------------
	void PlayerNetPacketProcesser::onRecvTiroListFromMapServer( CClient* client, PT_PLAYER_M2C_TIRO_LIST_DATA* data )
	{
		//const InstanceUIdType myInstanceUId = CPlayer::getInstance().getInstanceUid();
		//DYNAMIC_ASSERT(myInstanceUId > 0);

		//UITiroChangeInstance::getInstance().clearInstanceInfo();
		//for (Int i=0; i<data->addTiroNum; ++i)
		//{
		//	NetAddTiroInfo* addTiroInfo = &(data->addTiroInfo[i]);
			//DYNAMIC_ASSERT(NULL != addTiroInfo);

			//UIInstanceInfo instanceInfo;
// 			instanceInfo.regionId		= data->regionId;
// 			instanceInfo.regionType		= (REGION_OBJ_TYPE)data->regionType;
// 
// 			instanceInfo.instanceUId	= addTiroInfo->instanceUId;
// 			instanceInfo.curPlayerNum	= addTiroInfo->curPlayerNum;
// 			instanceInfo.maxPlayerNum	= addTiroInfo->maxPlayerNum;
// 			if (myInstanceUId == addTiroInfo->instanceUId)
// 			{
// 				instanceInfo.instanceCurrent = true;
// 			}

			//UITiroChangeInstance::getInstance().addInstanceInfo(&instanceInfo);
		//}

		//UITiroChangeInstance::getInstance().UIReFresh();
	}
}