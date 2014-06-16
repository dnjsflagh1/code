//********************************************************************************************************
#include "stdafx.h"
#include "TestScene.h"
#include "GameMain.h"
#include "ClientMain.h"
#include "LuaSkillSystem.h"
#include "CPlayerCharacterEntity.h"
#include "CPlayer.h"
#include "GameNetPacket.h"
#include "SkillNetPacketProcesser.h"
#include "ClientNetApplyManager.h"
#include "CSceneManager.h"
#include "UIManage.h"
#include "SLGCameraOpCtrl.h"
#include "ISceneNodeAction.h"
#include "IActionManager.h"
#include "UIMiniMap.h"
#include "UISystemSetting.h"
#include "UISelectServer.h"
#include "PlayCharacterNetPacketProcesser.h"
#include "CTroopEntity.h"
//********************************************************************************************************
namespace MG
{

	//--------------------------------------------------------------------
	TestScene::TestScene()
	{
        mHighConfig = false;
        mEntity = NULL;
		lastTime = 0;
		currTime = 0;
	}

	//--------------------------------------------------------------------
	TestScene::~TestScene()
	{

	}

	//--------------------------------------------------------------------
	Bool TestScene::init()
	{
		return true;
	}

	//--------------------------------------------------------------------
	Bool TestScene::update()
	{

		std::vector<IEffectComponent*>::iterator iter = mEffectComponentList.begin();
		for ( ; iter != mEffectComponentList.end(); iter++)
		{
			Vec3 pos;
			(*iter)->getSceneNode()->getPosition(pos);
			(*iter)->getSceneNode()->setPosition(Vec3(pos.x, pos.y, pos.z-1));
		}

        if( ClientMain::getInstance().getEngine()->input()->isCtrlOn() == false )
        {
            return true;
        }

		currTime = MGTimeOp::getCurrTick();
		if((currTime - lastTime) > 2000)
		{
			IEntity* tempEntity = NULL;
			Vec3 currPos;
			Vec3 dir(1,0,0);
			Int angle;
			Int dis;
			for(UInt i = 0; i < mEntityList.size(); ++i)
			{
				tempEntity = mEntityList[i];
				tempEntity->getSceneNode()->getPosition(currPos);
				angle = MGRandom::getInstance().rand_ab_One(0, 360);
				dis = MGRandom::getInstance().rand_ab_One(1, 20);
				dir = MGMath::rotateVector(dir, angle);
				currPos = currPos + dir * dis;

				if(currPos.x < 0 || currPos.z > 0 || currPos.x > 1024 || currPos.z < -1024 )
				{
					continue;
				}
				//if(currPos.x <= -128.f || currPos.x >= 128.f || currPos.z <= -128.f || currPos.z >= 128.f)
				//{
				//	continue;
				//}

				/*tempEntity->getSceneNode()->moveToByPathFinder(currPos, true);*/
				//tempEntity->getSceneNode()->moveToByPathFinder(currPos, true);
			}
			
			lastTime = currTime;
		}
		
        if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_F3 ))
        {
            ClientMain::getInstance().setConsole(true);
            DetectionMgr::getInstance().setPrint( true );

            // if ( CSceneManager::getInstance().loadRegionScene("Media\\Scene\\Test\\Test_Battle_Map", "Config\\Scene\\Test\\Test_Battle_Map\\Scene.xml"))
            //if ( CSceneManager::getInstance().loadRegionScene("Media\\Scene\\Map\\World_yuanzhou", "Config\\Scene\\Map\\World_yuanzhou\\Scene.xml"))
            //if ( CSceneManager::getInstance().loadRegionScene("Media\\Scene\\Map\\Place_Xian_0001", "Config\\Scene\\Place\\Place_Xian_0001\\Scene.xml"))
            if ( CSceneManager::getInstance().loadRegionScene(20001, ROT_TIRO))
            {
                CSceneManager::getInstance().onLoadSceneEnd();

 /*               GameMain::getInstance().clearOperatorCtrls();*/
            

                GameMain::getInstance().addOperatorCtrls( &GameObjectOpCtrl::getInstance() );
                // 设置摄像机
                ICamera* camera = ClientMain::getInstance().getScene()->getActiveCamera();
                if ( camera )
                {
                    camera->setNearClipDistance(2);
                    camera->setFarClipDistance(2000);
                    camera->setFov(45);

                    SLGCameraOpCtrl::getInstance().setCamera( camera );
                    GameMain::getInstance().addOperatorCtrls( &SLGCameraOpCtrl::getInstance() );
                }

               // GameMain::getInstance().enterGameScreen();

                CPlayer::getInstance().setAccountID(1);

                ClanData clanData;
                clanData.clanId            = 101;
                CPlayer::getInstance().deleteAllClan();
                CPlayer::getInstance().addClan(&clanData);
                CPlayer::getInstance().setActive(clanData.clanId);

				ClientMain::getInstance().getEngine()->unLockTreeManager();
                //SLGCameraOpCtrl::getInstance().revertCamera();

                //Vec3 pos(250, 0, -100);

                //PlayerCharacterEntityData playerCharacterData;
                //playerCharacterData.mId = 1;
                ////playerCharacterData.charClanId = 101;
                //playerCharacterData.charArtIcon = 40001;
                //playerCharacterData.mCharacterTemplateID = 1;
                //playerCharacterData.mPos = pos;
                //playerCharacterData.belongPlayerID = 1;
                //playerCharacterData.moveSpeed = 3;
                //playerCharacterData.yawSpeed = 1;

                ////Vec3 pos(639.423, 0, -621.859);



                //CPlayerCharacterEntity* playerCharacter = CSceneManager::getInstance().createPlayerCharacterEntity(&playerCharacterData);
                ////playerCharacter->setPos(pos);

                //playerCharacter->setAIEnable( true );

                ///////////////////////////////////////////////////////////////////////////////////////////////////

                ////开始创建 军队实体
                //TroopEntityData troopData;
                //troopData.mId = 1;
                //troopData.mCharacterTemplateID = 108;
                //troopData.mPos.x = 260;
                //troopData.mPos.z = -90;
                //troopData.hp = 100;
                //troopData.mp = 100;
                //troopData.mDir.x = 1;
                //troopData.mDir.z = 0;
                //troopData.mSoldierNum = 6;
                //troopData.belongPlayerID = 1;

                //SLGCameraOpCtrl::getInstance().focusPos(pos);



                //CTroopEntity* troopEntity = CSceneManager::getInstance().createTroopEntity(&troopData);
                //troopEntity->setAIEnable( true );
                //troopEntity->setPos( Vec3(270, 0, -100) );

            }
        }

		//if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_F6 ))
		if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_F4 ))
		{
			IScene* scene = ClientMain::getInstance().getScene();
			ITerrainManager* terrain = scene->getTerrainManager();

			Vec3 intersect_pos;
			terrain->getMouseRayIntersection(intersect_pos);
			if (scene)
			{
				IDecalSet* decalset = scene->getDecalSet("TestDecal");
				if (!decalset)
				{
					decalset = scene->createDecalSet("TestDecal", 1, "SelectedCircle.png", DT_HIGHLEVEL);
				}
				else
				{
					IDecal* decal = decalset->getDecal(0);
					decalset->setSize(10);
					if (decal)
					{
						decal->setPosition(intersect_pos);
					}
				}
			}
		}

		if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_F5 ))
		{
			//CPlayerCharacter* pc = CPlayer::getInstance().getActiveClan()->getMainGenreal();
			//PlayCharacterNetPacketProcesser::getInstance().sendPlayerCharacterJumpRegion(pc->getID(), ROT_PLACE, 147457, 0);

			IScene* scene = ClientMain::getInstance().getScene();
			ITerrainManager* terrain = scene->getTerrainManager();

			Vec3 intersect_pos;
			terrain->getMouseRayIntersection(intersect_pos);
			if ( scene )
			{
				IEntity* entity = scene->createEntity(11001);
				if (entity)
				{
					entity->getSceneNode()->setPosition(intersect_pos);
				}
			}
			//IScene* scene = ClientMain::getInstance().getScene();
			//if ( scene )
			//{
			//	IEffectEntity* effectEntity = scene->getEffectComponent("testEffect");
			//	if ( !effectEntity )
			//	{
			//		effectEntity = scene->createEffectEntity("testEffect", 3, false);
			//		mEffectEntityList.push_back(effectEntity);

			//		IEntity* entity = scene->getEntity( "kuma_0" );
			//		if ( entity )
			//		{
			//			effectEntity->bind(entity, true);
			//		}
			//		entity = scene->getEntity( "kuma_1" );
			//		if ( entity )
			//		{
			//			effectEntity->bind(entity, true);
			//		}	
			//	}
			//}
		}

		if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_F6 ))
		{
			//UISelectServer::getInstance().closeGui();
			//UISystemSetting::getInstance().openGui();
			IScene* scene = ClientMain::getInstance().getScene();
			ITerrainManager* terrain = scene->getTerrainManager();

			Vec3 intersect_pos;
			terrain->getMouseRayIntersection(intersect_pos);
			if (scene)
			{

				IEffectComponent* component = scene->createEffectComponent(10003, true, true);
				mEffectComponentList.push_back(component);

				if (component)
				{
					component->getSceneNode()->setPosition(Vec3(intersect_pos.x, intersect_pos.y, intersect_pos.z));
					component->getSceneNode()->setVisible(true);
					//component->getSceneNode()->setDirection(Vec3(1, 0, 0));
				}
			}
		}

		if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_F7 ))
		{
			IScene* scene = ClientMain::getInstance().getScene();
			ITerrainManager* terrain = scene->getTerrainManager();

			Vec3 intersect_pos;
			terrain->getMouseRayIntersection(intersect_pos);

			CPlayerCharacter* playerCharacter = CPlayer::getInstance().getActiveClan()->getMainGenreal();
			if(!playerCharacter)
			{
				return true;
			}

			CPlayerCharacterEntity* playerCharacterEntity = CSceneManager::getInstance().getPlayerCharacterEntity(playerCharacter->getID());
			if(!playerCharacterEntity)
			{
				return true;
			}
	
			playerCharacterEntity->setPos(intersect_pos);
			playerCharacterEntity->getEntity()->getSceneNode()->stickTerrain();


			//Vec3 startPos = intersect_pos;
			////entity->getSceneNode()->getPosition(startPos);
			//startPos.y += 1.0f;


			//PlayerCharacterData pcData;
			//pcData.mId  = 0;
			//pcData.mCharacterTemplateID = 1;
			//pcData.mDir = Vec3(0,0,-1.0f);
			//pcData.charHP = 100;
			//pcData.charMP = 100;
			//pcData.mName = L"test";
			//pcData.mPos.x = startPos.x;
			//pcData.mPos.z = startPos.z;

			//CCharacterSceneEntityDynamicData dynamicData;
			//dynamicData.belongPlayerID = 1;

			//CPlayerCharacterEntity* entity = CSceneManager::getInstance().createPlayerCharacterEntity(&pcData, &dynamicData);
			//entity->attachEntityAccessory( "weapon", 10009, ATTACH_POINT_LEFT_HAND );
			//entity->attachEntityAccessory( "horse", 10002, ATTACH_POINT_RIDE );
			//entity->playAnimation("normal_run001", true);
			//entity->attachItem(20035);
			//entity->doMoveToAction(Vec3(0,0,0), 0);

			//entity->doMoveToAction(Vec3(0,0,-30.0), 0, false);

		}

		if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_F8 ) )
		{
			IScene* scene = ClientMain::getInstance().getScene();
			if ( scene )
			{
				ITerrainManager* terrain = scene->getTerrainManager();

				Vec3 intersect_pos;
				terrain->getMouseRayIntersection(intersect_pos);

				Vec3 startPos = intersect_pos;

				//int count = mEntityList.size();
				//char name[16];
				//sprintf_s( name, 16, "kuma_%d", count);

				IEntity* entity = scene->getEntity("Kuma");
				if (!entity)
				{
					entity = scene->createEntity("Kuma", 46035);
				}
				if (entity)
				{
					entity->getSceneNode()->setPosition(startPos);
					entity->getSceneNode()->stickTerrain();

					mEntityList.push_back(entity);
				}

			}
		}

		if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_F9 ) )
		{
			//IScene* scene = ClientMain::getInstance().getScene();
			//if ( scene )
			//{
			//	IEntity* entity = scene->getEntity("Kuma");
			//	if ( entity )
			//	{
			//		entity->getAnimationController()->play("none_none_attack1");

			//		IEffectComponent* effectEntity = scene->getEffectComponent("testEffect");
			//		if ( !effectEntity )
			//		{
			//			effectEntity = scene->createEffectComponent("testEffect", 20, false);
			//			
			//			effectEntity->bind(entity, true);
			//		}
			//	}
			//}	
		}

		return true;
	}
}
