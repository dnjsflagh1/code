//********************************************************************************************************
#include "stdafx.h"
#include "TestUI.h"
#include "ClientMain.h"
#include "CSceneManager.h"
//#include "UICampaignList.h"
#include "UISelectPlace.h"
//#include "UICampaignInfo.h"
#include "CampaignNetPacketProcesser.h"
#include "UIClanRoleControl.h"
#include "UIChatMenu.h"
//#include "UICampaignInfo.h"
#include "TroopNetPacketProcesser.h"
#include "CPlayer.h"
#include "PlayCharacterNetPacketProcesser.h"
//#include "CWorldManager.h"
#include "PlayerNetPacketProcesser.h"
#include "RegionNetPacketProcesser.h"
#include "UIArmyFunction.h"
#include "UIGenrealPicture.h"
#include "ClientMain.h"
#include "GameSoundManager.h"
#include "ShopPacketProcesser.h"
#include "TestPopupMenu.h"
#include "UINpc.h"
#include "CPlayer.h"
#include "UITiroChangeInstance.h"
#include "UICampaignListNew.h"
#include "CPlayer.h"
#include "UIQuestManager.h"
#include "TemplateUI.h"
#include "UIClanInfo.h"
#include "UICampaignInfoNew.h"
#include "UICampaignSystemNew.h"
#include "UICampaignBarrack.h"
#include "UIBattleScore.h"
#include "UIPveCreate.h"
#include "UICampaignCountDown.h"
#include "UICampaignWinLoseMsg.h"
#include "UICampaignFight.h"
#include "UICampaignWar.h"
#include "CGeneralRecruitNetPacketProcessor.h"
#include "UICampaignCountDown.h"
#include "UIRecruitGeneral.h"
#include "UIChangeRecruit.h"
//********************************************************************************************************
namespace MG
{
    TestUI::TestUI()
    {

    }
    //--------------------------------------------------------------------
    TestUI::~TestUI()
    {

    }
    //--------------------------------------------------------------------
    Bool TestUI::init()
    {
       // UITestPopupMenu::getInstance().initialize("TestPopupMenuUI.layout");
        
        return true;
    }
    //--------------------------------------------------------------------
    Bool TestUI::update()
    {
		
		if(ClientMain::getInstance().getEngine()->input()->isCtrlOn() == false)
		{
			return true;
		}

		U64 clanId = 0;
		PlayerCharacterIdType playerCharacterId = 0;
		Clan* clan = CPlayer::getInstance().getActiveClan();
		if (NULL != clan)
		{
			clanId = clan->getClanID();
			if (CPlayer::getInstance().getMainGenreal() != NULL)
			{
				playerCharacterId =  CPlayer::getInstance().getMainGenreal()->getID();
			}
		}

		if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_Q ))
		{
			UIChangeRecruit::getInstance().openGui();
			//TemplateUI::getInstance().openGui();
			//RegionNetPacketProcesser::getInstance().sendTest();
			//PlayCharacterNetPacketProcesser::getInstance().jumpMapForUI(playerCharacterId, JMT_Distribution, 1, 0);
			//PlayCharacterNetPacketProcesser::getInstance().sendPlayerCharacterJumpRegion(playerCharacterId, ROT_TIRO, 4, 4001);
			return true;
		}
		if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_W ))
		{
			UIPveCreate::getInstance().openGui();
			//RegionNetPacketProcesser::getInstance().sendTest1();
			//PlayCharacterNetPacketProcesser::getInstance().jumpMapForUI(playerCharacterId, JMT_Distribution, 1, 0);
			//PlayCharacterNetPacketProcesser::getInstance().sendPlayerCharacterJumpRegion(playerCharacterId, ROT_TIRO, 4, 4001);
			return true;
		}
		if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_R ))
		{
			UITiroChangeInstance::getInstance().openGui();
			//CGeneralRecruitNetPacketProcessor::getInstance().sendGetRandomGeneralList(1);
			//UIPveCreate::getInstance().openGui();
			//CGeneralRecruitNetPacketProcessor::getInstance().sendGeneralRecruit();
			return true;
		}
		if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_P ))
		{
			//UICampaignListNew::getInstance().openGui();
			UIRecruitGeneral::getInstance().setGeneralRecruitId(1);
			//CGeneralRecruitNetPacketProcessor::getInstance().sendGetRandomGeneralList(1);
			//UIPveCreate::getInstance().openGui();
			//CGeneralRecruitNetPacketProcessor::getInstance().sendGeneralRecruit();
			return true;
		}
		if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_O ))
		{
			UIRecruitGeneral::getInstance().setGeneralRecruitId(2);
			
			//CGeneralRecruitNetPacketProcessor::getInstance().sendGetRandomGeneralList(2);
			//UIPveCreate::getInstance().openGui();
			//CGeneralRecruitNetPacketProcessor::getInstance().sendGeneralRecruit();
			return true;
		}
//
		if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_Y))
		{
			CGeneralRecruitNetPacketProcessor::getInstance().sendChangeGeneral(2);
			return true;
			//CGeneralRecruitNetPacketProcessor::getInstance().sendGeneralRecruit();
			//UICampaignFight::getInstance().openGui();
			//GameSoundManager::getInstance().stopAll();
#if 0
			PlayCharacterNetPacketProcesser::getInstance().sendPlayerCharacterJumpRegion(playerCharacterId, ROT_PLACE, 16385, 0);
			CPlayerCharacter * playerCharacter = CPlayer::getInstance().getMainGenreal();
			PlayerNetPacketProcesser::getInstance().sendPlayerEnterRegionByCharId(CPlayer::getInstance().getAccountID(), playerCharacterId);
#endif
			//playerCharacter->getAttributeSystem()->print();
			//UITiroChangeInstance::getInstance().openGui();
			//UICampaignBarrack::getInstance().openGui();
			//CampaignNetPacketProcesser::getInstance().sendCampaignEndManual(CPlayer::getInstance().getMyCampaignId());

			//RegionNetPacketProcesser::getInstance().sendTest();
			//UICampaignBarrack::getInstance().openGui();
			//RegionNetPacketProcesser::getInstance().sendAddTroopTest();
			//UICampaignInfoNew::getInstance().openGui();
			//CampaignNetPacketProcesser::getInstance().sendCampaignStart(1, clanId);
			return true;
		}
		
		

		if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_G ))
		{
			Vec3 pos(103.09, 0.04, -68.59);
			Vec3 dir(0,0,0);

			PT_REGION_M2C_ADD_PLAYER_CHARACTER_DATA data;
			data.addPlayerNum = 1;
			data.addPlayerInfo->playerId = 1;
			data.addPlayerInfo->character_id = 4001;
			data.addPlayerInfo->characterTemplateID = 4001;
			data.addPlayerInfo->mp = 1;
			data.addPlayerInfo->hp = 1;
			data.addPlayerInfo->mpmax = 1;
			data.addPlayerInfo->hpmax = 1;

			data.addPlayerInfo->pos			= ((NetVec2)pos).getData();
			data.addPlayerInfo->dir			= ((NetVec2)dir).getData();

			RegionNetPacketProcesser::getInstance().onRecvPlayerCharacterEnter(1, &data );
			//CGeneralRecruitNetPacketProcessor::getInstance().sendGetRecruitList(1);
			//UIRecruitGeneral::getInstance().openGui();
			//PlayCharacterNetPacketProcesser::getInstance().jumpMapForUI(playerCharacterId, JMT_Distribution, 1, 0);
			//PlayCharacterNetPacketProcesser::getInstance().sendPlayerCharacterJumpRegion(playerCharacterId, ROT_TIRO, 4, 4001);
			return true;
		}
		if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_H ))
		{

			Vec3 pos(103.09, 0.04, -68.59);
			Vec3 dir(0,0,0);
			PT_PLAYER_F2C_JUMP_REGION_DATA jump_data;
			jump_data.regionType	= ROT_MAP_DISTRIBUTION;
			jump_data.regionId		= 1;
			jump_data.instanceUid	= 0;
			jump_data.jumpResult	= PlayerJump_Success;
			jump_data.force			= 0;
			jump_data.pos			= ((NetVec2)pos).getData();
			jump_data.dir			= ((NetVec2)dir).getData();
			
			PlayerNetPacketProcesser::getInstance().onRecvPlayerJumpMap(0, &jump_data);

			PT_REGION_M2C_END_LOAD_SCENE_DATA end_data;
			RegionNetPacketProcesser::getInstance().onRecvEndLoadScene(0, &end_data );
			//U64 accountID = CPlayer::getInstance().getAccountID();
			//PlayCharacterNetPacketProcesser::getInstance().sendPlayerCharacterJumpRegion(playerCharacterId, ROT_PLACE, 1010001, 0);
			//PlayerNetPacketProcesser::getInstance().sendPlayerEnterRegionByCharId(accountID, playerCharacterId);
			//PlayCharacterNetPacketProcesser::getInstance().sendPlayerCharacterJumpRegion(playerCharacterId, ROT_TIRO, 4, 4001);
			return true;
		}

		//地图跳转 Begin
		if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_J ))
		{
			//U64 accountID = CPlayer::getInstance().getAccountID();
			PlayCharacterNetPacketProcesser::getInstance().sendPlayerCharacterJumpRegion(playerCharacterId, ROT_PVE, 40001, 0);
			//PlayerNetPacketProcesser::getInstance().sendPlayerEnterRegionByCharId(accountID, playerCharacterId);
			return true;
		}
//
//
		if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_K ))
		{
			U64 accountID = CPlayer::getInstance().getAccountID();
			PlayCharacterNetPacketProcesser::getInstance().sendPlayerCharacterJumpRegion(playerCharacterId, ROT_TIRO, 20001, 0);
			//PlayerNetPacketProcesser::getInstance().sendPlayerEnterRegionByCharId(accountID, playerCharacterId);
			return true;
		}
		if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_L ))
		{
			CPlayer* player = &(CPlayer::getInstance());
			U64 accountID = CPlayer::getInstance().getAccountID();
			//PlayCharacterNetPacketProcesser::getInstance().sendPlayerCharacterJumpRegion(playerCharacterId, ROT_TIRO, 20001, 0);
			//PlayerNetPacketProcesser::getInstance().sendPlayerEnterRegionByCharId(accountID, playerCharacterId);
			return true;
		}
		if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_V ))
		{
			U64 accountID = CPlayer::getInstance().getAccountID();
			PlayCharacterNetPacketProcesser::getInstance().sendPlayerCharacterJumpRegion(playerCharacterId, ROT_HOME, 5, 0);
			//PlayerNetPacketProcesser::getInstance().sendPlayerEnterRegionByCharId(accountID, playerCharacterId);
			return true;
		}
		if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_B ))
		{
			//RegionNetPacketProcesser::getInstance().sendPlayerCharacterSetAlive(playerCharacterId);
			return true;
		}
//
		if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_N ))
		{
			//CPlayer* myPlayer = &(CPlayer::getInstance());
			//AccountIdType myAccountId = myPlayer->getAccountID();
			//CampaignIdType myCampaignId = myPlayer->getMyCampaignId();
			//CampIdType myCampId = 1;
			//CampaignNetPacketProcesser::getInstance().sendCampaignChangeCampControl(myCampaignId, myAccountId, myCampId, myAccountId);
			//PlayerNetPacketProcesser::getInstance().sendPlayerEnterRegion(10001, ROT_AREA);
			//U64 clanId = CPlayer::getInstance().getActiveClan()->getClanID();

			//CampaignNetPacketProcesser::getInstance().sendCampaignReady(274, 1, clanId, ARMY_READY_CONFIRM);
			RegionNetPacketProcesser::getInstance().sendTest();
			return true;
		}

		if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_M ))
		{
			RegionNetPacketProcesser::getInstance().sendTest1();
			//PlayerNetPacketProcesser::getInstance().sendPlayerEnterRegion(ROT_MAP_DISTRIBUTION, 1, 0);
			//U64 clanId = CPlayer::getInstance().getActiveClan()->getClanID();

			//CampaignNetPacketProcesser::getInstance().sendCampaignEnter(274, clanId, 1);
			return true;

			//PlayCharacterNetPacketProcesser::getInstance().sendPlayerCharacterMove(clanId, Vec3(0,0,0));
			//TroopNetPacketProcesser::getInstance().sendTroopGroupMove(clanId, Vec3(0,0,0));
		}
//	//地图跳转 End
//
//		if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_C ))
//		{
//			//CampaignNetPacketProcesser::getInstance().sendCampaignCreate(clanId, 274, L"战斗1");
//			//UICampaignCreate::getInstance().openGui();
//			//UICampaignList::getInstance().openGui();
//			return true;
//
//			//PlayCharacterNetPacketProcesser::getInstance().sendPlayerCharacterMove(clanId, Vec3(0,0,0));
//			//TroopNetPacketProcesser::getInstance().sendTroopGroupMove(clanId, Vec3(0,0,0));
//		}
//
//
//		
//		if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_P ))
//		{
//
//			PlayerNetPacketProcesser::getInstance().sendPrintTest();
//			return true;
//
//			//PlayCharacterNetPacketProcesser::getInstance().sendPlayerCharacterMove(clanId, Vec3(0,0,0));
//			//TroopNetPacketProcesser::getInstance().sendTroopGroupMove(clanId, Vec3(0,0,0));
//		}
//
//		if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_A))
//		{
//			//CSceneManager::getInstance().loadRegionScene(273, ROT_AREA);
//			return true;
//		}
//
//		
//
//		if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_D))
//		{
//
//			//CSceneManager::getInstance().loadRegionScene(375, ROT_PLACE);
//			return true;
//		}
//
//
//		if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_G ))
//		{
//			ClientMain::getInstance().getEngine()->display()->setTerrainRegionDisplayEnabled(true);
//
//			//ITerrainManager* terrainManager = ClientMain::getInstance().getScene()->getTerrainManager();
//			//for(UInt i = 0; i < terrainManager->getTerrainChunkCount(); ++i)
//			//{
//			//	terrainManager.getTerrainChunkByIndex(i)->getTerrainRegion()->setBlockRegionVisible();
//			//}
//			//ClientMain::getInstance().getScene()->getTerrainManager()->getTerrainRegionManager()->setBlockRegionVisible(true);
//			//ClientMain::getInstance().getEngine()->display()->apply();
//
//           // ShopPacketProcesser::getInstance().sendOpenShopToFS(1);
//			//CClan* clan = CPlayer::getInstance().getActiveClan();
//			//CPlayerCharacter* chara = clan->getPlayerCharacterByIndex(0);
//
//			//Vec3 pos;
//			//for (Int i = 0; i<1000; ++i)
//			//{
//			//	pos.x = i;
//			//	pos.z = -i;
//			//	PlayCharacterNetPacketProcesser::getInstance().sendPlayerCharacterMove(chara->getID(), pos);
//			//	//Sleep(100);
//
//			//}
//
//			//GameSoundManager::getInstance().play("4");
//
//			//ClientMain::getInstance().getEngine()->soundMgr()->stopAll();
//			//ClientMain::getInstance().getEngine()->soundMgr()->createOrRetriveSound("test","Normal.ogg",true)->play();
//
//			//CClan* clan = CPlayer::getInstance().getActiveClan();
//			//CPlayerCharacter* chara = clan->getPlayerCharacterByIndex(0);
//
//			//UIArmyFunction::getInstance().openGui();
//			//UIGenrealPicture::getInstance().closeGui();
//			/*		Clan* clan = CPlayer::getInstance().getActiveClan();
//
//			Bool bRet = QuestSystem::getInstance().IsQuestAccepted(clan, 1);
//			Bool bRet2 = QuestSystem::getInstance().IsQuestFinishedByClan(clan, 1);
//			Bool bRet3 = QuestSystem::getInstance().IsQuestSubmitedByClan(clan, 1);
//
//			UIQuestSubmit::getInstance().openByQuestId(1);
//
//			Bool bRet4 = QuestSystem::getInstance().IsQuestAccepted(clan, 1);
//			Bool bRet5 = QuestSystem::getInstance().IsQuestFinishedByClan(clan, 1);
//			Bool bRet6 = QuestSystem::getInstance().IsQuestSubmitedByClan(clan, 1);*/
//			return false;
//			//UIQuestAccept::getInstance().openGui();
//			////CSceneManager::getInstance().createPlayerCharacterEntity(1, 1, "fsgkjfgs", "hero1", Vec3(-1174.94, 655.58, -192.34));
//			////UICampaignCreate::getInstance().openGui();
//			//return false;
//		}
//
//#if 0
//
//		if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_H ))
//		{
//
//			GameSoundManager::getInstance().play(3);
//			//ClientMain::getInstance().getEngine()->soundMgr()->stopAll();
//			//ISound* sound = ClientMain::getInstance().getEngine()->soundMgr()->createOrRetriveSound("test1","Battle.ogg",true);
//			//sound->setPriority(SP_LOW);
//			//sound->play();
//			//CClan* clan = CPlayer::getInstance().getActiveClan();
//			//CPlayerCharacter* chara = clan->getPlayerCharacterByIndex(0);
//
//			//UIArmyFunction::getInstance().closeGui();
//			//UIGenrealPicture::getInstance().openUIGenrealPicture( chara->getID() );
//			//Bool bRet = QuestSystem::getInstance().AcceptQuest(clan->getQuestManager()->getQuestPlayerCharacter(), 1);
//			//Bool bRet1 = QuestSystem::getInstance().AcceptQuest(clan->getQuestManager()->getQuestPlayerCharacter(), 1);
//
//			//Bool bRet2 = QuestSystem::getInstance().submitQuest(clan->getQuestManager()->getQuestPlayerCharacter(), 1);
//			//Bool bRet3 = QuestSystem::getInstance().submitQuest(clan->getQuestManager()->getQuestPlayerCharacter(), 1);
//
//			//Bool bRet1 = QuestSystem::getInstance().IsQuestAccepted(clan, 1);
//			//Bool bRet2 = QuestSystem::getInstance().IsQuestFinishedByClan(clan, 1);
//			//Bool bRet3 = QuestSystem::getInstance().IsQuestSubmitedByClan(clan, 1);
//
//			//UIQuestAccept::getInstance().openByQuestId(1);
//			return false;
//			//CSceneManager::getInstance().createTroopGroupEntity(1, 1, "fsgkjfgs", "hero1", Vec3(-1174.94, 655.58, -192.34));
//			//UICampaignCreate::getInstance().openGui();
//			//return false;
//		}
//		if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_J ))
//		{
//			//ClientMain::getInstance().getEngine()->soundMgr()->stopAll();
//			//U64 clanId = CPlayer::getInstance().getActiveClan()->getMainGenrealID();
//
//			////PlayCharacterNetPacketProcesser::getInstance().sendPlayerCharacterJumpRegion(clanId, 273, ROT_MAP);
//
//			//TroopNetPacketProcesser::getInstance().sendTroopGroupJumpRegion(clanId, 273, ROT_MAP);
//			CPlayerTroopGroup* group = CPlayer::getInstance().getActiveClan()->getPlayerTroopGroupByIndex(0);
//			CPlayerCharacter* character = CPlayer::getInstance().getActiveClan()->getPlayerCharacterByIndex(0);
//
//			//TroopNetPacketProcesser::getInstance().sendTroopGroupJumpRegion(group->getID(), character->getRegionID(), ROT_MAP);
//			return false;
//		}
//		
//
//		if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_H ))
//		{
//			UIQuestSubmit::getInstance().openGui();
//			//CSceneManager::getInstance().createPlayerCharacterEntity(1, 1, "fsgkjfgs", "hero1", Vec3(-1174.94, 655.58, -192.34));
//			//UICampaignCreate::getInstance().openGui();
//			return false;
//		}
//
//		if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_I ))
//		{
//			if (false == UICampaignCreate::getInstance().isOpen())
//			{
//				UICampaignCreate::getInstance().openGui();
//			}
//			else
//			{
//				UICampaignCreate::getInstance().closeGui();
//			}
//			
//		}
//
//		if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_L ))
//		{
//			if (false == UICampaignList::getInstance().isOpen())
//			{
//				UICampaignList::getInstance().openGui();
//				U64 regionId = 273;
//				CampaignNetPacketProcesser::getInstance().sendCampaignList(regionId);
//			}
//			else
//			{
//				UICampaignList::getInstance().closeGui();
//			}
//			
//		}
//		if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_O ))
//		{
//			//if (false == UICampaignInfo::getInstance().isOpen())
//			//{
//			//	UICampaignInfo::getInstance().openGui();
//			//}
//			//else
//			//{
//			//	UICampaignInfo::getInstance().closeGui();
//			//}
//			
//		}
//		
//
//
//		//if (ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_V ))
//		//{
//		//	U64 clanId = CPlayer::getInstance().getActiveClan()->getClanID();
//
//		//	Vec3 pos;
//		//	ClientMain::getInstance().getScene()->getTerrainManager()->getMouseRayIntersection(pos,true);
//
//		//	NetAddBuildingInfoFront info ;
//		//	info.templateId = 1;
//		//	info.pos.x = pos.x;
//		//	info.pos.z = pos.z;
//
//		//	//RegionNetPacketProcesser::getInstance().sendAddBattleBuildingByPlayer(1,273,(Byte)ROT_PLACE,1,&info);
//		//	//TroopNetPacketProcesser::getInstance().sendTroopMove(clanId,1, Vec3(0,0,0));
//		//	TroopNetPacketProcesser::getInstance().sendTroopGroupJumpRegion(clanId,273, ROT_PLACE); 
//		//}
//
//		if (ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_C ))
//		{
//			//Vec3 pos;
//			//ClientMain::getInstance().getScene()->getTerrainManager()->getMouseRayIntersection(pos,true);
//
//			//NetAddBuildingInfoFront info ;
//			//info.templateId = 1;
//			//
//			//info.pos.x = pos.x;
//			//info.pos.z = pos.z;
//
//			//RegionNetPacketProcesser::getInstance().sendAddBattleBuildingByPlayer(1,273,(Byte)ROT_MAP,1,&info);
//		}
//
//#endif
//		//if(ClientMain::getInstance().getEngine()->input()->isKeyPressed( KC_LCONTROL))
//		//{
//
//		//	UINpc::getInstance().openNpcTalkDialog(101,CPlayer::getInstance().getActiveClan()->getPlayerCharacterByIndex(0)->getID());
//		//	return true;
//		//}
//		if (ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_F5 ))
//		{
//			UINpc::getInstance().openNpcTalkDialog(20001,CPlayer::getInstance().getActiveClan()->getMainGenrealID());
//		}
//		if (ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_F6 ))
//		{
//			UIQuestManager::getInstance().openGui();
//		}
		
        return true;
    }
}