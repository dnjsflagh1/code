/******************************************************************************/
#include "stdafx.h"
#include "ClientNetApplyManager.h"
#include "RegionNetPacketProcesser.h"
#include "CSceneManager.h"
#include "LoginManager.h"
#include "CBuildingEntity.h"
#include "CPlayer.h"
#include "ClientMain.h"
#include "BuildingData.h"
#include "CTroopEntity.h"
#include "PlayerCharacterData.h"
#include "CPlayerCharacterEntity.h"
#include "IBlockManager.h"
#include "UIMessageBox.h"
#include "SLGCameraOpCtrl.h"
#include "MessageManager.h"
#include "ChannelInfo.h"
#include "MonsterData.h"
#include "CMonsterEntity.h"
#include "MessageManager.h"
#include "CharacterList.h"
#include "UIGenrealPicture.h"
#include "CharacterVisionEventList.h"
#include "CharacterVisionEvent.h"
#include "GameSoundManager.h"
#include "UIAliveRpg.h"
#include "UIAliveSlg.h"
#include "UICampaignCountDown.h"
#include "CRegionObject.h"
#include "UICampaignFight.h"
#include "UICampaignWar.h"
#include "GameSettingManager.h"

/******************************************************************************/
namespace MG
{
    //-----------------------------------------------------------------------------
	Bool RegionNetPacketProcesser::processFrontServerPacket(I32 id,NetEventRecv* packet)
	{
		if ( packet->getChannel() == GNPC_REGION )
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_REGION_M2C_ADD_PLAYER_CHARACTER:
				onRecvPlayerCharacterEnter( id, (PT_REGION_M2C_ADD_PLAYER_CHARACTER_DATA*)data->data );
				break;
			case PT_REGION_M2C_REMOVE_PLAYER_CHARACTER:
				onRecvPlayerCharacterLeave( id, (PT_REGION_M2C_REMOVE_PLAYER_CHARACTER_DATA*)data->data );
				break;
			case PT_REGION_M2C_CREATE_APPEAR_PLAYER_CHARACTER:
				onRecvPlayerCharacterCreateAndAppear(id, (PT_REGION_M2C_CREATE_APPEAR_PLAYER_CHARACTER_DATA*)data->data);
				break;
			case PT_REGION_M2C_DESTROY_DISAPPEAR_PLAYER_CHARACTER:
				onRecvPlayerCharacterDestroyAndDisappear(id, (PT_REGION_M2C_DESTROY_DISAPPEAR_PLAYER_CHARACTER_DATA*)data->data);
				break;
			case PT_REGION_M2C_ADD_BUILDING:
				onRecvBuildingEnter( id, (PT_REGION_M2C_ADD_BUILDING_DATA*)data->data );
				break;
			case PT_REGION_M2C_REMOVE_BUILDING:
				onRecvBuildingLeave( id, (PT_REGION_M2C_REMOVE_BUILDING_DATA*)data->data );
				break;
			//case PT_REGION_M2C_ADD_TRITH_PART_CHARACTER:
			//	onRecvThirdPartCharacterEnter( id, (PT_REGION_M2C_ADD_TRITH_PART_CHARACTER_DATA*)data->data );
			//	break;
			case PT_REGION_M2C_ADD_MONSTER:
				onRecvMonsterEnter( id, (PT_REGION_M2C_ADD_MONSTER_DATA*)data->data );
				break;
			case PT_REGION_M2C_MONSTER_ALIVE:
				onRecvMonsterAlive( id, (PT_REGION_M2C_MONSTER_ALIVE_DATA*)data->data );
				break;
			case PT_REGION_M2C_CREATE_APPEAR_MONSTER:
				onRecvMonsterCreateAndAppear(id, (PT_REGION_M2C_CREATE_APPEAR_MONSTER_DATA*)data->data);
				break;
			case PT_REGION_M2C_DESTROY_DISAPPEAR_MONSTER:
				onRecvMonsterDestroyAndDisappear(id,(PT_REGION_M2C_DESTROY_DISAPPEAR_MONSTER_DATA*)data->data);
				break;
			case PT_REGION_M2C_CREATE_TROOP:
				onRecvTroopCreate( id, (PT_REGION_M2C_CREATE_TROOP_DATA*)data->data );
				break;
			case PT_REGION_M2C_ADD_TROOP:
				onRecvTroopEnter( id, (PT_REGION_M2C_ADD_TROOP_DATA*)data->data );
				break;
			case PT_REGION_M2C_MONSTER_AI_CONTROL:
				onRecvMonsterAIControl( id, (PT_REGION_M2C_MONSTER_AI_CONTROL_DATA*)data->data );
				break;
			case PT_REGION_M2C_END_LOAD_SCENE:
				onRecvEndLoadScene( id, (PT_REGION_M2C_END_LOAD_SCENE_DATA*)data->data );
				break;
			case PT_REGION_M2C_PLAYER_CHARACTER_ALIVE:
				onRecvPlayerCharacterAliveFromMapServer( id, (PT_REGION_M2C_PLAYER_CHARACTER_ALIVE_DATA*)data->data );
				break;
			case PT_REGION_F2C_PLAYER_CHARACTER_ALIVE:
				onRecvPlayerCharacterAliveFromFrontServer( id, (PT_REGION_F2C_PLAYER_CHARACTER_ALIVE_DATA*)data->data );
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
	void RegionNetPacketProcesser::onRecvPlayerCharacterEnter( I32 id, PT_REGION_M2C_ADD_PLAYER_CHARACTER_DATA* data )
	{
		//CPlayer* myPlayer = &(CPlayer::getInstance());
		//Campaign* campaign = myPlayer->getCampaignSystem()->getMyCampaign();

        DYNAMIC_ASSERT_LOG( data->addPlayerNum < 1000, "onRecvPlayerCharacterEnter Too Much!" );
		for(Int i = 0; i < data->addPlayerNum; ++i)
		{
			NetAddPlayerCharacterInfo* playerCgaracterInfos = &(data->addPlayerInfo[i]);
            PlayerCharacterEntityData pcData;
            pcData.mId  = data->addPlayerInfo[i].character_id;
			pcData.mName = data->addPlayerInfo[i].name;
            pcData.surName = data->addPlayerInfo[i].surNmae;
            pcData.mCharacterTemplateID = data->addPlayerInfo[i].characterTemplateID;
            pcData.mDir = (NetVec2)data->addPlayerInfo[i].dir;
            pcData.hp = data->addPlayerInfo[i].hp;
            pcData.mp = data->addPlayerInfo[i].mp;
			pcData.mPos = (NetVec2)data->addPlayerInfo[i].pos;
			pcData.mBirthPos = (NetVec2)pcData.mPos;
            pcData.belongPlayerID	= data->addPlayerInfo[i].playerId;
			pcData.force			= (FORCE)data->addPlayerInfo[i].force;
			pcData.hpmax			= data->addPlayerInfo[i].hpmax;
			pcData.mpmax			= data->addPlayerInfo[i].mpmax;
			pcData.moveSpeed		= data->addPlayerInfo[i].moveSpeed;
			pcData.charArtIcon      = data->addPlayerInfo[i].artIconId;
			pcData.mLevel           = data->addPlayerInfo[i].level;

		    CPlayerCharacterEntity* entity = CSceneManager::getInstance().createPlayerCharacterEntity(&pcData);
            DYNAMIC_ASSERT(entity);

			//if(entity->getDynamicData()->belongPlayerID == CPlayer::getInstance().getAccountID())
			//{
				entity->setAIEnable(true);
			//}

			//设置势力
			FORCE force = FORCE_INIT;
#if 0
			if (NULL != campaign)
			{
				force = campaign->getPlayerCharacterForceByPlayerCharacterId(playerCgaracterInfos[i].character_id);
				if (force == FORCE_ATTACK || force == FORCE_DEFENSE)
				{
					entity->setCampaignForce(force);
				}
				//DYNAMIC_ASSERT(force == FORCE_ATTACK || force == FORCE_ATTACK || force == FORCE_DEFENSE);
				//DYNAMIC_ASSERT(force == FORCE_ATTACK || force == FORCE_DEFENSE);
				//troopGroupEntity->setCampaignForce(force);
			}
#endif

			//设置摄像机
			//CPlayer* myPlayer = &(CPlayer::getInstance());
			//CPlayerCharacter* playerCharacter = myPlayer->getActiveClan()->getMainGenreal();
   //         DYNAMIC_ASSERT(playerCharacter);
			//if( playerCharacter->getID() == pcData.mId)
			{
                Vec3 pos;
                entity->getEntity()->getSceneNode()->getPosition( pos );

				//我自己，需要移动摄像机
				//CSceneManager::getInstance().getEngineScene()->getActiveCamera()->focusPosition( pos );
				SLGCameraOpCtrl::getInstance().focusPos(pos);

				//选中英雄和军队
				//GameObjectOpCtrl::getInstance().addSelected((CCharacterSceneEntity*)entity);

				//myPlayer->setMyForce(force);
			}
			
			if(pcData.force == FORCE_ATTACK || pcData.force == FORCE_DEFENSE)
			{
				if(playerCgaracterInfos->isBattleLeader)
				{
					entity->createFlag(181004);
				}
				else
				{
					entity->createFlag(181003);
				}
				
			}

			LogSystem::getInstance().log(out_sys, "RegionNetPacketProcesser::onRecvPlayerCharacterEnter  playerId = [%I64d], character_id = [%I64d] \n",
				playerCgaracterInfos[i].playerId,playerCgaracterInfos[i].character_id);

        }

		//UIMessageBox::getInstance().showHint(L"新玩家 进来\n");
		
		//CSceneManager::getInstance().createTroopEntity(0, 50, "soldier_ng_z_3", "soldier_ng_z_3", FT_ROUND, Vec3(playerCgaracterInfos[0].pos.x, 0, playerCgaracterInfos[0].pos.z));
	}

    //-----------------------------------------------------------------------------
	void RegionNetPacketProcesser::onRecvPlayerCharacterLeave( I32 id, PT_REGION_M2C_REMOVE_PLAYER_CHARACTER_DATA* data )
	{
		//UIArmyFunction::getInstance().clearSelect();
		CSceneManager::getInstance().destroyPlayerCharacterEntity(data->character_id);

		//UIMessageBox::getInstance().showHint(L"新玩家 离开 ~!!!!\n");
	}

	//-----------------------------------------------------------------------------
	void RegionNetPacketProcesser::onRecvPlayerCharacterCreateAndAppear( I32 id, PT_REGION_M2C_CREATE_APPEAR_PLAYER_CHARACTER_DATA* data )
	{
		CPlayer* myPlayer = &(CPlayer::getInstance());
		//Campaign* campaign = myPlayer->getCampaignSystem()->getMyCampaign();

        DYNAMIC_ASSERT_LOG( data->addPlayerNum < 1000, "onRecvPlayerCharacterCreateAndAppear Too Much!" );
		for(Int i = 0; i < data->addPlayerNum; ++i)
		{
			NetAddPlayerCharacterInfo* playerCgaracterInfos = &(data->addPlayerInfo[i]);
			PlayerCharacterEntityData pcData;
			pcData.mId  = data->addPlayerInfo[i].character_id;
			pcData.mCharacterTemplateID = data->addPlayerInfo[i].characterTemplateID;
			pcData.mDir = (Vec3)((NetVec2)data->addPlayerInfo[i].dir);
			pcData.mName = data->addPlayerInfo[i].name;
			pcData.surName = data->addPlayerInfo[i].surNmae;
			pcData.mPos = (NetVec2)(data->addPlayerInfo[i].pos);
			pcData.mBirthPos = (NetVec2)pcData.mPos;
			pcData.belongPlayerID	= data->addPlayerInfo[i].playerId;
			pcData.force			= (FORCE)data->addPlayerInfo[i].force;
			pcData.hp				= data->addPlayerInfo[i].hp;
			pcData.mp				= data->addPlayerInfo[i].mp;
			pcData.hpmax			= data->addPlayerInfo[i].hpmax;
			pcData.mpmax			= data->addPlayerInfo[i].mpmax;
			pcData.moveSpeed		= data->addPlayerInfo[i].moveSpeed;
            pcData.charArtIcon      = data->addPlayerInfo[i].artIconId;
            pcData.mLevel           = data->addPlayerInfo[i].level;

			CPlayerCharacterEntity* entity = CSceneManager::getInstance().createPlayerCharacterEntity(&pcData);
			DYNAMIC_ASSERT(entity);

			//if(entity->getDynamicData()->belongPlayerID == CPlayer::getInstance().getAccountID())
			//{
				entity->setAIEnable(true);
			//}

			if (data->addPlayerInfo[i].force == FORCE_ATTACK || data->addPlayerInfo[i].force == FORCE_DEFENSE)
			{
				//战场里要播放音效
				GameSoundManager::getInstance().play(60013);
			}

			//设置势力
			FORCE force = FORCE_INIT;
#if 0
			if (NULL != campaign)
			{
				force = campaign->getPlayerCharacterForceByPlayerCharacterId(playerCgaracterInfos[i].character_id);
				if (force == FORCE_ATTACK || force == FORCE_DEFENSE)
				{
					entity->setCampaignForce(force);
				}
				//DYNAMIC_ASSERT(force == FORCE_ATTACK || force == FORCE_ATTACK || force == FORCE_DEFENSE);
				//DYNAMIC_ASSERT(force == FORCE_ATTACK || force == FORCE_DEFENSE);
				//troopGroupEntity->setCampaignForce(force);
			}
#endif

			//设置摄像机
			CPlayer* myPlayer = &(CPlayer::getInstance());
			CPlayerCharacter* playerCharacter = myPlayer->getActiveClan()->getMainGenreal();
			DYNAMIC_ASSERT(playerCharacter);
			if( playerCharacter->getID() == pcData.mId)
			{
				Vec3 pos;

                IEntity* entityInstance = entity->getEntity();
                DYNAMIC_ASSERT_LOG( entityInstance!=NULL, "IEntity null" );
                ISceneNode* sceneNode = entityInstance->getSceneNode();
                DYNAMIC_ASSERT_LOG( sceneNode!=NULL, "ISceneNode null" );
				sceneNode->getPosition( pos );

				//我自己，需要移动摄像机
				//CSceneManager::getInstance().getEngineScene()->getActiveCamera()->focusPosition( pos );
				SLGCameraOpCtrl::getInstance().focusPos(pos);

				//选中英雄和军队
				GameObjectOpCtrl::getInstance().addSelected((CCharacterSceneEntity*)entity);

				//myPlayer->setMyForce(force);
			}

			if(pcData.force == FORCE_ATTACK || pcData.force == FORCE_DEFENSE)
			{
				if(playerCgaracterInfos->isBattleLeader)
				{
					entity->createFlag(181004);
				}
				else
				{
					entity->createFlag(181003);
				}

			}

			Vec3 moveToPos = (NetVec2)(data->addPlayerInfo[i].moveToPos);
			if(moveToPos != Vec3(0,0,0))
			{
				Bool isBlockCheck = false;
				CRegionObject* currRegion = CSceneManager::getInstance().getCurrRegion();
				if(currRegion && currRegion->getGameType() == GameType_Slg)
				{
					isBlockCheck = true;
				}

				entity->doMoveToAction(moveToPos, 0 , isBlockCheck);
			}


			LogSystem::getInstance().log(out_sys, "RegionNetPacketProcesser::onRecvPlayerCharacterEnter  playerId = [%I64d], character_id = [%I64d] \n",
				playerCgaracterInfos[i].playerId,playerCgaracterInfos[i].character_id);

		}

	}

	 //-----------------------------------------------------------------------------
	void RegionNetPacketProcesser::onRecvPlayerCharacterDestroyAndDisappear( I32 id, PT_REGION_M2C_DESTROY_DISAPPEAR_PLAYER_CHARACTER_DATA* data )
	{
		CSceneManager::getInstance().destroyPlayerCharacterEntity(data->characterIndex);
	}

#if 0
	//-----------------------------------------------------------------------------
	void RegionNetPacketProcesser::onRecvTroopGroupEnter( I32 id, PT_REGION_M2C_ADD_TROOP_GROUP_DATA* data )
	{
		//CTroopGroupEntity* troopGroupEntity = NULL;
		//for(UInt i = 0; i < data->addTroopNum; ++i)
		//{
  //          TroopGroupData tgdata;
  //          tgdata.mDir = data->addTroopInfo[i].dir;
  //          tgdata.mName = data->addTroopInfo[i].name;
  //          tgdata.mPos.x = data->addTroopInfo[i].pos.x;
  //          tgdata.mPos.z = data->addTroopInfo[i].pos.z;
  //          tgdata.mID = data->addTroopInfo[i].troopId;
  //          tgdata.ArmyTemplateId = data->addTroopInfo[i].troopTemplateId;
  //          tgdata.ArmyNum = 1000;

		//	//从服务器发来【朝向】信息 需要客户端设置
		//	troopGroupEntity = CSceneManager::getInstance().createTroopGroupEntity( &tgdata, data->addTroopInfo[i].playerId );
		//	if(troopGroupEntity)
		//	{
		//		if(CPlayer::getInstance().getAccountID() == data->addTroopInfo[i].playerId)
		//		{
		//			CPlayer::getInstance().setSelectId(data->addTroopInfo[i].troopId);
		//		}
		//	}
		//}
	}

	//-----------------------------------------------------------------------------
	void RegionNetPacketProcesser::onRecvTroopGroupLeave( I32 id, PT_REGION_M2C_REMOVE_TROOP_GROUP_DATA* data )
	{
		UIArmyFunction::getInstance().clearSelect();
	}
#endif

	//-----------------------------------------------------------------------------
	void RegionNetPacketProcesser::onRecvBuildingEnter( I32 id, PT_REGION_M2C_ADD_BUILDING_DATA* data )
	{
        DYNAMIC_ASSERT_LOG( data->addBuildingNum < 1000, "onRecvBuildingEnter Too Much!" );

		CBuildingEntity* buildingEntity = NULL;
		for(UInt i = 0; i < data->addBuildingNum; ++i)
		{
            BuildingEntityData buildingData;
            buildingData.mId					= data->addBuildingInfo[i].uId;
            buildingData.mCharacterTemplateID	= data->addBuildingInfo[i].buildingTemplateId;
            buildingData.mPos					= (NetVec2)data->addBuildingInfo[i].pos;
			buildingData.mDir				= (NetVec2)data->addBuildingInfo[i].dir;
            //buildingData.mRegionID				= data->addBuildingInfo[i].regionId;
            buildingData.belongPlayerID = data->addBuildingInfo[i].belongAccountId;
			buildingData.force = (FORCE)data->addBuildingInfo[i].force;
			buildingData.hp = data->addBuildingInfo[i].hp;


            if ( GameSettingManager::getInstance().isDebugNoBuilding() == false )
            {
                buildingEntity = CSceneManager::getInstance().createBuildingEntity(&buildingData);
                if(NULL == buildingEntity)
                {
                    DYNAMIC_ASSERT(0);
                }
            }
		}
	}

	//-----------------------------------------------------------------------------
	void RegionNetPacketProcesser::onRecvBuildingLeave( I32 id, PT_REGION_M2C_REMOVE_BUILDING_DATA* data )
	{
        if ( GameSettingManager::getInstance().isDebugNoBuilding() == false )
        {
		    CSceneManager::getInstance().destroyBuildingEntity(data->buildingId);
        }
	}

	//-----------------------------------------------------------------------------
	void RegionNetPacketProcesser::onRecvMonsterEnter( I32 id, PT_REGION_M2C_ADD_MONSTER_DATA* data )
	{
        DYNAMIC_ASSERT_LOG( data->addNum < 100, "onRecvMonsterEnter Too Much!" );
		for(UInt i = 0; i < data->addNum; ++i)
		{
			NetAddMonsterInfo* addMonsterInfo = &(data->addInfo[i]);

			MonsterEntityData data;
			data.mId = addMonsterInfo->monsterId;
			data.mCharacterTemplateID = addMonsterInfo->charTemplateId;
			data.mPos = (NetVec2)addMonsterInfo->pos;
			data.mDir = (NetVec2)addMonsterInfo->dir;
			data.mBirthPos = data.mPos;
			data.force = FORCE_MONSTER;
			data.hp = addMonsterInfo->hp;
			data.hpmax = addMonsterInfo->maxHp;
			data.mp = addMonsterInfo->mp;
			data.mpmax = addMonsterInfo->maxMp;
			data.moveSpeed = addMonsterInfo->moveSpeed;
			//dynamicData.belongPlayerID = addMonsterInfo->controllerAccountId;

			CMonsterEntity* monsterEntity = CSceneManager::getInstance().createMonsterEntity(&data);
			if (monsterEntity)
			{
				monsterEntity->setAIEnable(true);
			}	
		}
	}

	//-----------------------------------------------------------------------------
	void RegionNetPacketProcesser::onRecvMonsterAlive( I32 id, PT_REGION_M2C_MONSTER_ALIVE_DATA* data )
	{
		MonsterEntityData monsterData;
		monsterData.mId = data->monsterInfo.monsterId;
		monsterData.mCharacterTemplateID = data->monsterInfo.charTemplateId;
		monsterData.mPos = (NetVec2)data->monsterInfo.pos;
		monsterData.mDir = (NetVec2)data->monsterInfo.dir;
		monsterData.mBirthPos = monsterData.mPos;
		monsterData.force = FORCE_MONSTER;
		monsterData.hp = data->monsterInfo.hp;
		monsterData.hpmax = data->monsterInfo.maxHp;
		monsterData.mp = data->monsterInfo.mp;
		monsterData.mpmax = data->monsterInfo.maxMp;
		monsterData.moveSpeed = data->monsterInfo.moveSpeed;

		CMonsterEntity* monsterEntity = CSceneManager::getInstance().createMonsterEntity(&monsterData);
		monsterEntity->setAIEnable(true);

		U32 characterVisionEventListId = monsterEntity->getCharacterTempInfo()->getCharacterVisionEventListId();
		const CharacterVisionEventListInfo* characterVisionEventListInfo = CharacterVisionEventList::getInstance().getCharacterVisionEventListInfo(characterVisionEventListId);
		if(!characterVisionEventListInfo)
		{
			return;
		}

		const CharacterVisionEventInfo* characterVisionEventInfo = CharacterVisionEvent::getInstance().getCharacterVisionEventInfo(characterVisionEventListInfo->rebirthId);
		if(!characterVisionEventInfo)
		{
			return;
		}

		Str actionName;
		MGStrOp::toString(characterVisionEventInfo->actionName.c_str(), actionName);
		monsterEntity->playAnimation(actionName);

		monsterEntity->addEffect(characterVisionEventInfo->effectResId);

		GameSoundManager::getInstance().play(characterVisionEventInfo->audioResId);
	}

	//-----------------------------------------------------------------------------
	void RegionNetPacketProcesser::onRecvMonsterCreateAndAppear( I32 id, PT_REGION_M2C_CREATE_APPEAR_MONSTER_DATA* data )
	{
        DYNAMIC_ASSERT_LOG( data->addNum < 100, "onRecvMonsterCreateAndAppear Too Much!" );
		for(UInt i = 0; i < data->addNum; ++i)
		{
			NetAddMonsterInfo* addMonsterInfo = &(data->addInfo[i]);

			MonsterEntityData monsterEntityDatata;
			monsterEntityDatata.mId = addMonsterInfo->monsterId;
			monsterEntityDatata.mCharacterTemplateID = addMonsterInfo->charTemplateId;
			monsterEntityDatata.mPos = (NetVec2)addMonsterInfo->pos;
			monsterEntityDatata.mDir = (NetVec2)addMonsterInfo->dir;
			monsterEntityDatata.mBirthPos = (NetVec2)addMonsterInfo->pos;
			monsterEntityDatata.force = FORCE_MONSTER;
			monsterEntityDatata.hp = addMonsterInfo->hp;
			monsterEntityDatata.hpmax = addMonsterInfo->maxHp;
			monsterEntityDatata.mp = addMonsterInfo->mp;
			monsterEntityDatata.mpmax = addMonsterInfo->maxMp;
			monsterEntityDatata.moveSpeed = addMonsterInfo->moveSpeed;

			CMonsterEntity* monsterEntity = CSceneManager::getInstance().createMonsterEntity(&monsterEntityDatata);
			if (monsterEntity)
			{
				monsterEntity->setAIEnable(true);

				Vec3 moveToPos = (NetVec2)(addMonsterInfo->moveToPos);
				if(moveToPos != Vec3(0,0,0))
				{
					Bool isBlockCheck = false;
					CRegionObject* currRegion = CSceneManager::getInstance().getCurrRegion();
					if(currRegion && currRegion->getGameType() == GameType_Slg)
					{
						isBlockCheck = true;
					}

					monsterEntity->doMoveToAction(moveToPos, 0 , isBlockCheck);
				}
			}

		}
	}

	//-----------------------------------------------------------------------------
	void RegionNetPacketProcesser::onRecvMonsterDestroyAndDisappear( I32 id, PT_REGION_M2C_DESTROY_DISAPPEAR_MONSTER_DATA* data )
	{
        DYNAMIC_ASSERT_LOG( data->num < 100, "onRecvMonsterDestroyAndDisappear Too Much!" );
		for(UInt i = 0; i < data->num; ++i)
		{
			//CSceneManager::getInstance().destroyMonsterEntity(data->monsterId[i]);	
		}
	}

	//-----------------------------------------------------------------------------
	void RegionNetPacketProcesser::onRecvPlayerCharacterAliveFromMapServer( I32 id, PT_REGION_M2C_PLAYER_CHARACTER_ALIVE_DATA* data )
	{
		//MessageManager::getInstance().addChatMsgForTest("武将实体复活 character_id[%d], x[%f], z[%f]\n", 
		//	data->playerInfo.character_id, ((NetVec2)data->playerInfo.pos).getX(), ((NetVec2)data->playerInfo.pos).getY());

		CPlayerCharacterEntity* playerCharacterEntity = CSceneManager::getInstance().getPlayerCharacterEntity(data->playerInfo.character_id);
		if(!playerCharacterEntity)
		{
			return;
		}

		playerCharacterEntity->getDynamicData()->mPos = (NetVec2)data->playerInfo.pos;

		playerCharacterEntity->getDynamicData()->mBirthPos = playerCharacterEntity->getDynamicData()->mPos;

		playerCharacterEntity->getDynamicData()->isDied = false;
		playerCharacterEntity->getDynamicData()->hp = data->playerInfo.hp;
		playerCharacterEntity->getDynamicData()->hpmax = data->playerInfo.hpmax;
		playerCharacterEntity->getDynamicData()->mp = data->playerInfo.mp;
		playerCharacterEntity->getDynamicData()->mpmax = data->playerInfo.mpmax;
		playerCharacterEntity->getActionStateManager().setIsPush(true);
		playerCharacterEntity->getAIStateManager().setIsPush(true);
		playerCharacterEntity->onRelive();
		playerCharacterEntity->setPos(playerCharacterEntity->getDynamicData()->mPos);
		playerCharacterEntity->getEntity()->getSceneNode()->stickTerrain();
		playerCharacterEntity->setBattleState(false, true);

		U32 characterVisionEventListId = playerCharacterEntity->getCharacterTempInfo()->getCharacterVisionEventListId();
		const CharacterVisionEventListInfo* characterVisionEventListInfo = CharacterVisionEventList::getInstance().getCharacterVisionEventListInfo(characterVisionEventListId);
		if(!characterVisionEventListInfo)
		{
			return;
		}

		const CharacterVisionEventInfo* characterVisionEventInfo = CharacterVisionEvent::getInstance().getCharacterVisionEventInfo(characterVisionEventListInfo->rebirthId);
		if(!characterVisionEventInfo)
		{
			return;
		}

		Str actionName;
		MGStrOp::toString(characterVisionEventInfo->actionName.c_str(), actionName);
		playerCharacterEntity->playAnimation(actionName);

		playerCharacterEntity->addEffect(characterVisionEventInfo->effectResId);

		GameSoundManager::getInstance().play(characterVisionEventInfo->audioResId);
	}

	void RegionNetPacketProcesser::onRecvPlayerCharacterAliveFromFrontServer( I32 id, PT_REGION_F2C_PLAYER_CHARACTER_ALIVE_DATA* data )
	{
		MessageManager::getInstance().addChatMsgForTest("将领复活");

		const PlayerCharacterIdType playerCharacterId = data->playerCharacterId;
		CPlayerCharacter* playerCharacter = CPlayer::getInstance().getPlayerCharacter(playerCharacterId);
		if (NULL != playerCharacter)
		{
			playerCharacter->setMax_HpSpMp();
			UIGenrealPicture::getInstance().setHp(playerCharacterId);
			UIGenrealPicture::getInstance().setMp(playerCharacterId);
			UIGenrealPicture::getInstance().setSp(playerCharacterId);
		}

		UIAliveRpg::getInstance().closeGui();
		UIAliveSlg::getInstance().closeGui();
	}
#if 0
	//-----------------------------------------------------------------------------
	void RegionNetPacketProcesser::onRecvCampEnter( I32 id, PT_REGION_M2C_ADD_CAMP_DATA* data )
	{
		for (Int i=0; i<data->addCampNum; ++i)
		{
			NetAddCampInfo* addCampInfo = &(data->addCampInfo[i]);

			BuildingData data;
			data.mId					= addCampInfo->campId;
			data.bbTempId				= addCampInfo->campTemplateId;
			data.mCharacterTemplateID	= addCampInfo->campTemplateId;
			data.hp						= addCampInfo->hp;
			data.mp						= addCampInfo->mp;
			data.buildingType			= BBTN_NORMAL_CAMP;
			data.mPos.x 				= addCampInfo->pos.x;
			data.mPos.z 				= addCampInfo->pos.z;

			CCharacterSceneEntityDynamicData dynamicData;
			dynamicData.belongPlayerID = addCampInfo->belongAccountId;
			dynamicData.force = (FORCE)addCampInfo->force;
			dynamicData.hp = addCampInfo->hp;
			dynamicData.mp = addCampInfo->mp;
	
			//dynamicData.belongPlayerID = 

			CBuildingEntity* battleBuildingEntity = CSceneManager::getInstance().createBuildingEntity(&data, &dynamicData);
			MessageManager::getInstance().addChatMsgForTest("创建军营 mId[%d]\n", data.mId);
		}
	}
#endif
	//-----------------------------------------------------------------------------
	void RegionNetPacketProcesser::onRecvTroopCreate( I32 id, PT_REGION_M2C_CREATE_TROOP_DATA* data )
	{
		//计算士兵的位子，并把结果反馈到服务器， 由服务器负责广播给其他客户端

		sendCreateTroopReturn(data);
	}

	//-----------------------------------------------------------------------------
	void RegionNetPacketProcesser::onRecvTroopEnter( I32 id, PT_REGION_M2C_ADD_TROOP_DATA* data )
	{
        DYNAMIC_ASSERT_LOG( data->addTroopNum < 100, "onRecvTroopEnter Too Much!" );
		//开始创建 军队实体z
		for (Int i=0; i<data->addTroopNum; ++i)
		{
			NetAddTroopInfo* addTroopInfo = &(data->addTroopInfo[i]);
			TroopEntityData troopData;
			troopData.mId = data->addTroopInfo[i].troopId;
			troopData.mCharacterTemplateID = data->addTroopInfo[i].troopTemplateId;
			troopData.mPos = (NetVec2)data->addTroopInfo[i].pos;
			troopData.mDir = (NetVec2)data->addTroopInfo[i].dir;
			troopData.mSoldierNum = data->addTroopInfo[i].soldierNum;
			troopData.belongPlayerID = data->addTroopInfo[i].playerId;
			troopData.force		= (FORCE)data->addTroopInfo[i].force;
			troopData.hp			= data->addTroopInfo[i].hp;
			troopData.mp			= data->addTroopInfo[i].mp;
			troopData.hpmax		= data->addTroopInfo[i].maxHp;
			troopData.mpmax		= data->addTroopInfo[i].maxMp;
			troopData.moveSpeed  = data->addTroopInfo[i].moveSpeed;

			std::vector<Vec3> soldierPosList;
			
			//SLGCameraOpCtrl::getInstance().focusPos(soldierPosList[0]);

			CTroopEntity* troopEntity = CSceneManager::getInstance().createTroopEntity(&troopData);

			if(troopData.belongPlayerID == CPlayer::getInstance().getAccountID())
			{
				troopEntity->setAIEnable(true);
				troopEntity->setAIController(true);
			}



			//MessageManager::getInstance().addChatMsgForTest("创建军队 mId[%d]\n", troopData.mId);
		}

	}

	//-----------------------------------------------------------------------------
	void RegionNetPacketProcesser::onRecvMonsterAIControl( I32 id, PT_REGION_M2C_MONSTER_AI_CONTROL_DATA* data )
	{
        DYNAMIC_ASSERT_LOG( data->addMonsterAINum < 100, "onRecvMonsterAIControl Too Much!" );
		//MonsterIdType saveMonsterAI[500] = { 0 };
		for (Int i=0; i<data->addMonsterAINum; ++i)
		{
			NetMonsterIdInfo* addMonsterAIInfo = &(data->addMonsterAIInfo[i]);
			CMonsterEntity* monsterEntity = CSceneManager::getInstance().getMonsterEntity(addMonsterAIInfo->monsterId);
			if(!monsterEntity)
			{
				return;
			}
			
			monsterEntity->getDynamicData()->belongPlayerID = data->controlerAccountId;
			//monsterEntity->setAIEnable(true);
		}
	}

	//-----------------------------------------------------------------------------
	void RegionNetPacketProcesser::onRecvEndLoadScene( I32 id, PT_REGION_M2C_END_LOAD_SCENE_DATA* data )
	{
        CSceneManager::getInstance().setLoadSceneEndDirty();

		UICampaignFight::getInstance().openGui();
		UICampaignWar::getInstance().openGui();
	}

	//-----------------------------------------------------------------------------
	void RegionNetPacketProcesser::sendAddBuildingByPlayer(U64 characterId, U64 regionId, Byte regionType, Int addBuildingNum, NetAddBuildingInfo* addBuildingInfo)
	{
#if 0
        // 得到一个大型发送缓存
        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( MG_GAME_NET_PACKET_BIG_MAX_SIZE );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            packet->channel = GNPC_REGION;
            packet->type    = PT_REGION_C2F_ADD_BUILDING;
            PT_REGION_C2F_ADD_BUILDING_DATA* sendData = (PT_REGION_C2F_ADD_BUILDING_DATA*)(packet->data);

            // 当前发送数据头大小
            I32 sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_REGION_C2F_ADD_BUILDING_DATA_INFO::headSize;
            // 准备发送数据大小
            I32 prepareSendDataSize = sendDataHeadSize;

            // 清空
            sendData->addBuildingNum = 0;
            sendData->characterId = characterId;
            sendData->regionId = regionId;
            sendData->regionType = regionType;

            // 遍历角色队列
            for (Int i=0 ; i != addBuildingNum; ++i)
            {
                NetAddBuildingInfoFront* building = &(addBuildingInfo[i]);

                //填充相应信息 Begin
                sendData->addBuildingInfo[i].templateId	= building->templateId;
                sendData->addBuildingInfo[i].pos.x		= building->pos.x;
                sendData->addBuildingInfo[i].pos.z		= building->pos.z;
                //填充相应信息 End

                sendData->addBuildingNum++;
                // 递增一个角色数据大小到发送数据缓存大小
                prepareSendDataSize += PT_REGION_C2F_ADD_BUILDING_DATA_INFO::elmsSize;

                // 如果大于缓存最大大小则发送
                if ( prepareSendDataSize+PT_REGION_C2F_ADD_BUILDING_DATA_INFO::elmsSize >= dataPtr->getDataMaxSize() )
                {
                    ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                        prepareSendDataSize );

                    // 清空
                    sendData->addBuildingNum   = 0;
                    prepareSendDataSize    = sendDataHeadSize;
                }
            }

            // 如果有剩余则发送
            if ( sendData->addBuildingNum > 0 )
            {
                ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                    prepareSendDataSize );
            }
        }
#endif
	}

	//-----------------------------------------------------------------------------
	void RegionNetPacketProcesser::sendRemoveBuildingByPlayer(U64  buildingId)
	{
        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_REGION;
            packet->type    = PT_REGION_C2F_REMOVE_BUILDING;

            // 转换逻辑包
            PT_REGION_C2F_REMOVE_BUILDING_DATA* sendData = (PT_REGION_C2F_REMOVE_BUILDING_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                sendData->buildingId = buildingId;

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_REGION_C2F_REMOVE_BUILDING_DATA_INFO::dataSize );
            }
        }

	}

	//-----------------------------------------------------------------------------
	void RegionNetPacketProcesser::sendCreateTroopReturn(PT_REGION_M2C_CREATE_TROOP_DATA* data)
	{
		Vec3 centerPos;
		centerPos = NetVec2(data->pos);
		Vec3 dir = (NetVec2)data->dir;

		std::vector<Vec3> troopPosList;
        const CharacterTempInfo* characterTempInfo = CharacterTemplate::getInstance().getCharacterTempInfo(data->troopTemplateId);
        if(!characterTempInfo)
        {
            return;
        }

        ModelDeclaration* modelDeclaration = ClientMain::getInstance().getEngine()->resourceMgr()->getModelDeclaration(characterTempInfo->getCharacterArtMashId(), false);
        if(!modelDeclaration)
        {
            return;
        }

		UInt colNum = characterTempInfo->getFormationListNum()/*(sqrt((Flt)data->troopNum / 2))* 2*/;
		UInt rowNum = data->troopNum / colNum;
		if(colNum * rowNum < data->troopNum)
		{
			rowNum++;
		}

		UInt armyListNum = characterTempInfo->getArmyListNum();
		UInt armyArmyX = characterTempInfo->getArmyArmyX();
		Flt troopRadius = armyListNum * (modelDeclaration->patherRadius * 2  + armyArmyX);

		IEntity* entity = NULL;

		UInt intervalRow = troopRadius;
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

        //-----------------------------------------------------------------------------

		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr ;
		// 转换成标准包格式
		GameNetPacketData* packet = NULL;
		// 转换逻辑包
		PT_REGION_C2F_CREATE_TROOP_RET_DATA* sendData = NULL;

        // 当前发送数据头大小
        I32 sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_REGION_C2F_CREATE_TROOP_RET_INFO::headSize;
        // 当前发送数据大小
        I32 sendDataSize        = sendDataHeadSize;
        // 准备发送数据大小
        I32 prepareSendDataSize = 0;

		for(UInt i = 0; i < troopPosList.size(); ++i)
		{
            //-----------------------------------------------------------------------------

            if ( dataPtr.isNull() == false )
            {
                // 递增一个角色数据大小到发送数据缓存大小
                prepareSendDataSize = sendDataSize + PT_REGION_C2F_CREATE_TROOP_RET_INFO::netAddTroopRetInfoSize;

                // 如果大于缓存最大大小则发送
                if ( prepareSendDataSize >= dataPtr->getLogicDataMaxSize() )
                {
                    ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                        GameNetPacketData_INFO::headSize + PT_REGION_C2F_CREATE_TROOP_RET_INFO::dataSize(sendData) );

                    dataPtr.setNull();
                }
            }

            //-----------------------------------------------------------------------------

            if ( dataPtr.isNull() )
            {
                // 获得一个发送【服务端】缓存
                dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

                // 转换成标准包格式
                packet = (GameNetPacketData*) dataPtr->getLogicData();
                if ( !packet )
                    return;

                // 设置标签
                packet->channel = GNPC_REGION;
                packet->type    = PT_REGION_C2F_CREATE_TROOP_RET;

                // 转换逻辑包
                sendData = (PT_REGION_C2F_CREATE_TROOP_RET_DATA*)(packet->data);

                // 填充逻辑包
                sendData->troopGroupId	 = data->troopGroupId;
                /*sendData->pos.x 	 = data->pos.x;
                sendData->pos.z 	 = data->pos.z;*/
                sendData->regionId	 = data->regionId;
                sendData->regionType = data->regionType;
                sendData->instanceId = data->instanceId;

		        sendData->troopNum  = 0;
            }

            //-----------------------------------------------------------------------------

			sendData->troopPos[sendData->troopNum] = ((NetVec2)troopPosList[i]).getData();
            sendData->troopNum++;
            sendDataSize += PT_REGION_C2F_CREATE_TROOP_RET_INFO::netAddTroopRetInfoSize;
		}

        //-----------------------------------------------------------------------------
        
        if ( dataPtr.isNull() == false )
        {
            ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                GameNetPacketData_INFO::headSize + PT_REGION_C2F_CREATE_TROOP_RET_INFO::dataSize(sendData) );
            dataPtr.setNull();
        }
	}

	//-----------------------------------------------------------------------------
	void RegionNetPacketProcesser::sendAddTroopTest()
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
				sendData->accountId = CPlayer::getInstance().getAccountID();

				// 发送数据
				ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
					GameNetPacketData_INFO::headSize + PT_REGION_C2M_ADD_TROOP_TEST_INFO::dataSize );
			}
		}
	}

	//-----------------------------------------------------------------------------
	void RegionNetPacketProcesser::sendTest1()
	{
		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_REGION;
			packet->type    = PT_REGION_C2M_TEST1;

			// 转换逻辑包
			PT_REGION_C2M_TEST_DATA* sendData = (PT_REGION_C2M_TEST_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->accountId = CPlayer::getInstance().getAccountID();

				// 发送数据
				ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
					GameNetPacketData_INFO::headSize + PT_REGION_C2M_TEST_INFO::dataSize );
			}
		}
	}

	//-----------------------------------------------------------------------------
	void RegionNetPacketProcesser::sendTest()
	{
		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_REGION;
			packet->type    = PT_REGION_C2M_TEST;

			// 转换逻辑包
			PT_REGION_C2M_TEST_DATA* sendData = (PT_REGION_C2M_TEST_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->accountId = CPlayer::getInstance().getAccountID();

				// 发送数据
				ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
					GameNetPacketData_INFO::headSize + PT_REGION_C2M_TEST_INFO::dataSize );
			}
		}
	}

	void RegionNetPacketProcesser::sendPlayerCharacterSetAlive(PlayerCharacterIdType playerCharacterId, AliveType aliveType)
	{
		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_REGION;
			packet->type    = PT_REGION_C2F_PLAYER_CHARACTER_ALIVE;

			// 转换逻辑包
			PT_REGION_C2F_PLAYER_CHARACTER_ALIVE_DATA* sendData = (PT_REGION_C2F_PLAYER_CHARACTER_ALIVE_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->accountId = CPlayer::getInstance().getAccountID();
				sendData->playerCharacterId = playerCharacterId;
				sendData->aliveType = aliveType;

				// 发送数据
				ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
					GameNetPacketData_INFO::headSize + PT_REGION_C2F_PLAYER_CHARACTER_ALIVE_INFO::dataSize );
			}
		}
	}

	//-----------------------------------------------------------------------------
}