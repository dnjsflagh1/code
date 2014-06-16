
/******************************************************************************/
#include "stdafx.h"
#include "ClientNetApplyManager.h"
#include "PlayerNetPacketProcesser.h"
#include "CSceneManager.h"
#include "LoginManager.h"
#include "CPlayer.h"
#include "UIArmyFunction.h"
#include "UIGenrealPicture.h"
#include "UIMessageBox.h"
#include "ClientMain.h"
#include "PlayerCharacterData.h"
#include "SLGCameraOpCtrl.h"
#include "UITiroChangeInstance.h"
#include "UIClanControl.h"
#include "CRegionObject.h"
#include "UISLGGeneralPic.h"
#include "UIClanInfo.h"
/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	Bool PlayerNetPacketProcesser::processFrontServerPacket(I32 id, NetEventRecv *packet)
	{
        if ( packet->getChannel() == GNPC_PLAYER )
        {
            GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

            switch (data->type)
            {
            case PT_PLAYER_F2C_PLAYERCHARACTER_INFO_LIST:
                onRecvClientGenrealInfoFromFrontServer( id, (PT_PLAYER_F2C_PLAYERCHARACTER_INFO_LIST_DATA*)data->data );
                break;
			case PT_PLAYER_F2C_MAIN_PLAYERCHARACTER_INFO:
				onRecvMainGenrealInfoFromFrontServer(id, (PT_PLAYER_F2C_MAIN_PLAYERCHARACTER_INFO_DATA*)data->data);
				break;
			case PT_PLAYER_F2C_JUMP_REGION:
				onRecvPlayerJumpMap( id, (PT_PLAYER_F2C_JUMP_REGION_DATA*)data->data );
				break;
			//case PT_PLAYER_F2C_JUMP_REGION_ERROR:
			//	onRecvPlayerJumpMapError(id, (PT_PLAYER_F2C_JUMP_REGION_ERROR_DATA*)data->data);
			//	break;
			case PT_PLAYER_M2C_REMAIN_PLAYERCHARACTER_LIST:
				onRecvRemainPlayerCharacterListFromMapServer( id, (PT_PLAYER_M2C_REMAIN_PLAYERCHARACTER_LIST_DATA*)data->data );
				break;
            case PT_PLAYER_F2C_TROOP_INFO_LIST:
                onRecvClientTroopListFromFrontServer(id, (PT_PLAYER_F2C_TROOP_INFO_LIST_DATA*)data->data);
                break;
			case PT_PLAYER_M2C_TIRO_LIST_BEGIN:
				onRecvTiroListFromMapServerBegin(id, (PT_PLAYER_M2C_TIRO_LIST_BEGIN_DATA*)data->data);
				break;
			case PT_PLAYER_M2C_TIRO_LIST:
				onRecvTiroListFromMapServer(id, (PT_PLAYER_M2C_TIRO_LIST_DATA*)data->data);
				break;
			case PT_PLAYER_M2C_TIRO_LIST_END:
				onRecvTiroListFromMapServerEnd(id, (PT_PLAYER_M2C_TIRO_LIST_END_DATA*)data->data);
				break;
			default:
				DYNAMIC_ASSERT(0);
				break;
            }
            return true;
        }
		return false;
	}
    //-----------------------------------------------------------------------------
	void PlayerNetPacketProcesser::onRecvRemainPlayerCharacterListFromMapServer( I32 id, PT_PLAYER_M2C_REMAIN_PLAYERCHARACTER_LIST_DATA* data )
	{
		//FUNDETECTION(__MG_FUNC__);
		int kk = 0;
	}
    
	//-----------------------------------------------------------------------------
	void PlayerNetPacketProcesser::onRecvMainGenrealInfoFromFrontServer( I32 id, PT_PLAYER_F2C_MAIN_PLAYERCHARACTER_INFO_DATA* data )
	{
		//FUNDETECTION(__MG_FUNC__);
		CClan* pClan = CPlayer::getInstance().getActiveClan();
		assert(pClan);
		//设置主武将ID
        pClan->setMainGenrealID(data->generalId);
	}
    //-----------------------------------------------------------------------------
    void PlayerNetPacketProcesser::onRecvClientGenrealInfoFromFrontServer( I32 id, PT_PLAYER_F2C_PLAYERCHARACTER_INFO_LIST_DATA* data )
    {
		//FUNDETECTION(__MG_FUNC__);
        CClan* pClan = CPlayer::getInstance().getActiveClan();
        assert(pClan);
        CPlayerCharacter* pCPlayerCharacter = NULL;
        Int nCount = data->remainPlayerCharacterNum;

        for (Int i=0; i<nCount; i++)
        {
            PlayerCharacterData playerCharacterData;
            playerCharacterData.mId                            = data->remainPlayerCharacter[i].Id                     ;
			playerCharacterData.charClanId                     = data->remainPlayerCharacter[i].charClanId                     ;
            playerCharacterData.mPos                           = (NetVec2)data->remainPlayerCharacter[i].genrealPos             ;
            playerCharacterData.mName                          = data->remainPlayerCharacter[i].name                   ;
            playerCharacterData.mRegionType                    = (REGION_OBJ_TYPE)data->remainPlayerCharacter[i].regionType	            ;
            playerCharacterData.mRegionID                      = data->remainPlayerCharacter[i].regionId		        ;
            playerCharacterData.mCharacterTemplateID           = data->remainPlayerCharacter[i].characterTemplateID    ;
            playerCharacterData.charCurAge                     = data->remainPlayerCharacter[i].charCurAge			    ;
			playerCharacterData.charLifeSpan				   = data->remainPlayerCharacter[i].charLifeSpan		;
            playerCharacterData.mLevel                         = data->remainPlayerCharacter[i].charLvl	            ;
            playerCharacterData.charExp1                       = data->remainPlayerCharacter[i].charExp1	            ;
            playerCharacterData.charExp2                       = data->remainPlayerCharacter[i].charExp2		        ;
            playerCharacterData.charExp3                       = data->remainPlayerCharacter[i].charExp3               ;
            playerCharacterData.mHp							   = data->remainPlayerCharacter[i].charHP			        ;
            playerCharacterData.mMp							   = data->remainPlayerCharacter[i].charMP	                ;
            playerCharacterData.mLineageNum                    = data->remainPlayerCharacter[i].charLineageNum	        ;
            playerCharacterData.charArtMashID1                 = data->remainPlayerCharacter[i].charArtMashID1		    ;
            playerCharacterData.charArtMashID2                 = data->remainPlayerCharacter[i].charArtMashID2         ;
            playerCharacterData.charArtIcon                    = data->remainPlayerCharacter[i].charArtIcon			;
            playerCharacterData.charInfluenceID                = data->remainPlayerCharacter[i].charInfluenceID		;
            playerCharacterData.charSkillPointAll              = data->remainPlayerCharacter[i].charSkillPointAll      ;
            playerCharacterData.charNoAssignSkillPoint         = data->remainPlayerCharacter[i].charNoAssignSkillPoint ;
            playerCharacterData.charState                      = (CHAR_STATE)data->remainPlayerCharacter[i].charState	            ;
            playerCharacterData.charLifeState                  = (CHAR_LIFE_STATE)data->remainPlayerCharacter[i].charLifeState	        ;
            playerCharacterData.mDir                           = (NetVec2)data->remainPlayerCharacter[i].charDir		        ;
            playerCharacterData.charSurName                    =  data->remainPlayerCharacter[i].surName;                 ;
			playerCharacterData.charAttrAppendId			   = data->remainPlayerCharacter[i].charAttrAppendId;
			playerCharacterData.charAttrAppendLvlAddId		   = data->remainPlayerCharacter[i].charAttrAppendLvlAddId;

            for (Int j=0; j<DB_RECORD_ATTR_NUM; j++)
            {
                playerCharacterData.charAttrRand[j] = data->remainPlayerCharacter[i].attrRand[j];
                playerCharacterData.charAttrRandAdd[j] = data->remainPlayerCharacter[i].attrRandAdd[j];
            }

			Bool isFirst = true;
            pCPlayerCharacter = pClan->addPlayerCharacter( &playerCharacterData, isFirst );
            assert(pCPlayerCharacter);
            
            //暂时写在这，
			if ( isFirst )
			{
				pCPlayerCharacter->init(&playerCharacterData);
				UIClanInfo::getInstance().addPlayerCharacter(pCPlayerCharacter);
			}

        }

		U64 mainGenrealID = pClan->getMainGenrealID();
		DYNAMIC_ASSERT_LOG(mainGenrealID > 0,"error: mainGenrealID == 0 !");
		if(mainGenrealID > 0)
		{  
            if (pClan->getMainGenreal() == NULL)   //排除招募等在游戏之中后新建的武将信息!~
            {
                 pClan->setMainPlayerCharacter(pClan->getPlayerCharacter(mainGenrealID));
            }
		}
		////更新氏族空置界面
		//Str16 zhuZhang = L"";
		//Str16 jueWei = L"";
		//Str16 zhuDi = L"";
		//Str16 level = L"";
  //      pCPlayerCharacter = pClan->getMainGenreal();
		//zhuZhang = pCPlayerCharacter->getName();
		//UIClanControl::getInstance().refreshClanInfo(zhuZhang,jueWei,zhuDi,level);
  //      //LoginManager::getInstance().handleGenrealInfo();
    }

	//-----------------------------------------------------------------------------
	void PlayerNetPacketProcesser::sendPrintTest()
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
			ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , GameNetPacketData_INFO::headSize);
				
		}
	}

	//-----------------------------------------------------------------------------
	void PlayerNetPacketProcesser::sendTiroList()
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
				//sendData->regionId	= regionId;
				//sendData->regionType = regionType;

				// 发送数据
				ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
					GameNetPacketData_INFO::headSize + PT_PLAYER_C2F_TIRO_LIST_INFO::dataSize );
			}
		}
	}

    //-----------------------------------------------------------------------------
	void PlayerNetPacketProcesser::sendPlayerEnterRegion(REGION_OBJ_TYPE regionType, RegionIdType regionId, InstanceUIdType instanceUid)
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
                sendData->regionId		= regionId;
				sendData->instanceUid	= instanceUid;
                sendData->regionType	= regionType;

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_PLAYER_C2F_JUMP_REGION_INFO::dataSize );
            }
        }
	
    }
	//-----------------------------------------------------------------------------
	void PlayerNetPacketProcesser::sendPlayerEnterRegionByCharId(AccountIdType accountId, PlayerCharacterIdType playerCharacterId)
	{
		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_PLAYER;
			packet->type    = PT_PLAYER_C2F_JUMP_REGION_BY_CHAR_ID;

			// 转换逻辑包
			PT_PLAYER_C2F_JUMP_REGION_BY_CHAR_ID_DATA* sendData = (PT_PLAYER_C2F_JUMP_REGION_BY_CHAR_ID_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->accountId				= accountId;
				sendData->playerCharacterId		= playerCharacterId;

				// 发送数据
				ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
					GameNetPacketData_INFO::headSize + PT_PLAYER_C2F_JUMP_REGION_BY_CHAR_ID_INFO::dataSize );
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
	void PlayerNetPacketProcesser::onRecvPlayerJumpMap(I32 id, PT_PLAYER_F2C_JUMP_REGION_DATA* data)
	{
		if (data->jumpResult != PlayerJump_Success)
		{
			wchar_t errorHint[32] = L"";
			swprintf( errorHint, L"摄像机跳转副本失败 regionType[%d],regionId[%I64i], instanceUid[%I64i]", 
				data->regionType,data->regionId,data->instanceUid);

			std::wstring str(errorHint);
			UIMessageBox::getInstance().showHint(str);
			return;
		}

		//--------------------------------------------------------------------------------------

		CSceneManager::getInstance().destroyRegionScene();
	
		//--------------------------------------------------------------------------------------

		//FUNDETECTION(__MG_FUNC__);
		//CClan* pClan = CPlayer::getInstance().getActiveClan();
		//assert(pClan);
		//ClanData* pData = pClan->getData();
		//assert(pData);
		//pData->regionID = data->regionId;
		//pData->regionType = (REGION_OBJ_TYPE)data->regionType;
		//pData->instanceUId = (REGION_OBJ_TYPE)data->instanceUid;

		CPlayer::getInstance().setInstanceUid(data->instanceUid);

		CPlayer::getInstance().setForce((FORCE)data->force);

		//--------------------------------------------------------------------------------------

		if ( CSceneManager::getInstance().loadRegionScene(data->regionId, (REGION_OBJ_TYPE)(data->regionType)) )	//yuanlinhu
		{	
			/*Vec2 worldPos = Vec2(NetVec2(data->pos));
			SLGCameraOpCtrl::getInstance().setFocusPos(worldPos);*/
		}

		//--------------------------------------------------------------------------------------
		Vec2 worldDir = Vec2(NetVec2(data->dir));
        Vec2 worldPos = Vec2(NetVec2(data->pos));
        SLGCameraOpCtrl::getInstance().syncFocusPosDirFromServer(worldPos, worldDir);

		//SLGCameraOpCtrl::getInstance().setFocusPos(worldPos);


		//关闭战斗相关界面
		//CClan* clan = CPlayer::getInstance().getActiveClan();
		//CPlayerCharacter* chara = clan->getMainGenreal();
        
		//UIArmyFunction::getInstance().closeGui();
		
   //     if ( chara )
   //     {  
			//CRegionObject* currRegion = CSceneManager::getInstance().getCurrRegion();
			//DYNAMIC_ASSERT(currRegion);
			//GameType currType = currRegion->getGameType();
			//if (currType == GameType_Slg)
			//{
			//	UISLGGeneralPic::getInstance().setCharacterId(chara->getID());
			//}
			//else if (currType == GameType_Max)
			//{
			//	UISLGGeneralPic::getInstance().setCharacterId(chara->getID());
			//}
			//else
		 //       UIGenrealPicture::getInstance().setCharacterId(chara->getID() );  
   //     }

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
    void PlayerNetPacketProcesser::onRecvClientTroopListFromFrontServer( I32 id, PT_PLAYER_F2C_TROOP_INFO_LIST_DATA* data )
    {
		//FUNDETECTION(__MG_FUNC__);
        CClan* pClan = CPlayer::getInstance().getActiveClan();
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


	void PlayerNetPacketProcesser::onRecvTiroListFromMapServerBegin( I32 id, PT_PLAYER_M2C_TIRO_LIST_BEGIN_DATA* data )
	{
		UITiroChangeInstance::getInstance().clearInstanceInfo(data->mapServerNetId);
	}

	void PlayerNetPacketProcesser::onRecvTiroListFromMapServerEnd( I32 id, PT_PLAYER_M2C_TIRO_LIST_END_DATA* data )
	{
		UITiroChangeInstance::getInstance().UIReFresh();
	}	

	//-----------------------------------------------------------------------------
	void PlayerNetPacketProcesser::onRecvTiroListFromMapServer( I32 id, PT_PLAYER_M2C_TIRO_LIST_DATA* data )
	{
		const InstanceUIdType myInstanceUId = CPlayer::getInstance().getInstanceUid();
		//DYNAMIC_ASSERT(myInstanceUId > 0);

		DYNAMIC_ASSERT(data->addTiroNum >= 0 && data->addTiroNum < 100);

		for (Int i=0; i<data->addTiroNum; ++i)
		{
			NetAddTiroInfo* addTiroInfo = &(data->addTiroInfo[i]);
			DYNAMIC_ASSERT(NULL != addTiroInfo);

			UIInstanceInfo instanceInfo;
			instanceInfo.mapServerNetId	= data->mapServerNetId;
			instanceInfo.regionId		= data->regionId;
			instanceInfo.regionType		= (REGION_OBJ_TYPE)data->regionType;

			instanceInfo.instanceUId	= addTiroInfo->instanceUId;
			instanceInfo.curPlayerNum	= addTiroInfo->curPlayerNum;
			instanceInfo.maxPlayerNum	= addTiroInfo->maxPlayerNum;
			if (myInstanceUId == addTiroInfo->instanceUId)
			{
				instanceInfo.instanceCurrent = true;
			}

			UITiroChangeInstance::getInstance().addInstanceInfo(data->mapServerNetId, &instanceInfo);
		}

		
	}

}