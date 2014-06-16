//********************************************************************************************************
#include "stdafx.h"
#include "TestSkill.h"
#include "ClientMain.h"
#include "LuaSkillSystem.h"
#include "CPlayerCharacterEntity.h"
#include "CPlayer.h"
#include "GameNetPacket.h"
#include "SkillNetPacketProcesser.h"
#include "ClientNetApplyManager.h"
#include "CSceneManager.h"
#include "UIManage.h"
#include "ISceneNode.h"
#include "IEffectEntity.h"
//********************************************************************************************************
namespace MG
{

	//--------------------------------------------------------------------
	TestSkill::TestSkill()
	{
		mEntity = NULL;
		mEntityCampare = NULL;
	}

	//--------------------------------------------------------------------
	TestSkill::~TestSkill()
	{
		MG_SAFE_DELETE( mEntity );
		MG_SAFE_DELETE( mEntityCampare );
	}

	//--------------------------------------------------------------------
	Bool TestSkill::init()
	{
		return true;
	}

	//--------------------------------------------------------------------
	Bool TestSkill::update()
	{
		//static int num_water_fall = 0;
		//static int num_smoke_red = 0;
		//static int num_smoke_blue = 0;
		//static int ani_num = 0;
		//static Vec3 effect_pos = Vec3(0.0, 2.0, 0.0);

		//if(ClientMain::getInstance().getEngine()->input()->isAltOn())
		//{
		//	if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_Q ))
		//	{

		//		///* mEntity->startClantSkill( 1 );*/
		//		//PT_SKILL_C2F_TROOP_CLANT_DATA data;
		//		//data.troopId = 2;
		//		//data.skillId = 1;
		//		//ClientNetApplyManager::getInstance().sendFrontServerPacket(GNPC_SKILL, PT_SKILL_C2F_TROOP_CLANT, (CChar*)&data, sizeof(PT_SKILL_C2F_TROOP_CLANT_DATA));
		//	}

		//	if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_E ))
		//	{
		//		char effect_name[16];
		//		sprintf_s( effect_name, _countof(effect_name) - 1, "waterfall%d", num_water_fall );

		//		IEffectEntity* effect = CSceneManager::getInstance().getEngineScene()->createEffectEntity(effect_name, "jjj_fire", true);
		//		ISceneNode* sceneNode = effect->getSceneNode();

		//		if ( !sceneNode )
		//			return true;

		//		if ( num_water_fall == 0 )
		//		{
		//			sceneNode->setPosition(Vec3(0,10,-30));
		//			sceneNode->setScale(Vec3(100,100,100));
		//			num_water_fall++;
		//		}
		//		else
		//		{
		//			Vec3 final_pos = Vec3(0,10,-30);
		//			int round_num = (( num_water_fall - 1 ) / 2 + 1);

		//			if ( ( num_water_fall & 0x01 ) == 0 )
		//				final_pos.x -= ( 2.0 * round_num );
		//			else if ( ( num_water_fall & 0x01 ) == 1 )
		//				final_pos.x += ( 2.0 * round_num );

		//			sceneNode->setPosition(final_pos);
		//			num_water_fall++;
		//		}
		//	}

			/*if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_R ))
			{
			char effect_name[16];
			sprintf_s( effect_name, _countof(effect_name) - 1, "waterfall%d", num_water_fall );
			CSceneManager::getInstance().getEngineScene()->destroyEffectComponent(effect_name);

			if ( num_water_fall > 0 )
			num_water_fall--;
			}

			if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_D ))
			{
			char effect_name[16];
			sprintf_s( effect_name, _countof(effect_name) - 1, "smoke_100_%d", num_smoke_red );

			IEffectEntity* effect = CSceneManager::getInstance().getEngineScene()->createEffectEntity(effect_name, "Hit_Big", true);
			ISceneNode* sceneNode = effect->getSceneNode();

			if ( !sceneNode )
			return true;

			if ( num_smoke_red == 0 )
			{
			sceneNode->setPosition(Vec3(0,10,0));
			num_smoke_red++;
			}
			else
			{
			Vec3 final_pos = Vec3(0,10,0);
			int round_num = (( num_smoke_red - 1 ) / 2 + 1);

			if ( ( num_smoke_red & 0x01 ) == 0 )
			final_pos.x -= ( 5.0 * round_num );
			else if ( ( num_smoke_red & 0x01 ) == 1 )
			final_pos.x += ( 5.0 * round_num );

			sceneNode->setPosition(final_pos);
			num_smoke_red++;
			}
			}

			if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_F ))
			{
			char effect_name[16];
			sprintf_s( effect_name, _countof(effect_name) - 1, "smoke_100_%d", num_smoke_red );
			CSceneManager::getInstance().getEngineScene()->destroyEffectComponent(effect_name);

			if ( num_smoke_red > 0 )
			num_smoke_red--;
			}

			if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_C ))
			{
			char effect_name[16];
			sprintf_s( effect_name, _countof(effect_name) - 1, "smoke_50_%d", num_smoke_blue );

			IEffectEntity* effect = CSceneManager::getInstance().getEngineScene()->createEffectEntity(effect_name, "Walk_Smoke_Big", true);
			ISceneNode* sceneNode = effect->getSceneNode();

			if ( !sceneNode )
			return true;

			if ( num_smoke_blue == 0 )
			{
			sceneNode->setPosition(Vec3(0,10,20));
			num_smoke_blue++;
			}
			else
			{
			Vec3 final_pos = Vec3(0,10,20);
			int round_num = (( num_smoke_blue - 1 ) / 2 + 1);

			if ( ( num_smoke_blue & 0x01 ) == 0 )
			final_pos.x -= ( 5.0 * round_num );
			else if ( ( num_smoke_blue & 0x01 ) == 1 )
			final_pos.x += ( 5.0 * round_num );

			sceneNode->setPosition(final_pos);
			num_smoke_blue++;
			}
			}

			if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_V ))
			{
			char effect_name[16];
			sprintf_s( effect_name, _countof(effect_name) - 1, "smoke_50_%d", num_smoke_blue );
			CSceneManager::getInstance().getEngineScene()->destroyEffectComponent(effect_name);d

			if ( num_smoke_blue > 0 )
			num_smoke_blue--;
			}*/

			//if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_C ))
			//{

			//	PlayerCharacterData data;
			//	ZeroMemory(&data, sizeof(data));
			//	data.characterTemplateID = 3;
			//	data.charID = 0;
			//	data.charPos = Vec3(0,0,0);

			//	mEntity = CSceneManager::getInstance().createPlayerCharacterEntity(&data, 0);
			//	if( mEntity )
			//	{
			//		IEntity* entity = mEntity->getEntity();
			//		if ( entity && entity->getSceneNode() )
			//			entity->getSceneNode()->setPosition(Vec3(0,10,0));
			//		//mEntity->getEntity()->getAnimationController()->play("idle");
			//	}
			//	

				/*if ( !mEntity )
				{
				mEntity = CSceneManager::getInstance().createPlayerCharacterEntity(0,0,"entity1","general",Vec3(0,0,0));
				CPlayer::getInstance().getActiveClan()->addPlayerCharacter( 0 );
				mEntity->createEntity("soldier", Vec3(0,0,0));
				mEntityCampare->createEntity("TestEntity2", "horse2", Vec3(200.0,0.0,0.0));

				mEntity->setDirection(Vec3(0.0f, 0.0f, 1   .0f), MG::ISceneNode::TS_LOCAL);
				mEntity->setScale(Vec3(10.0f,10.0f,10.0f));
				mEntityCampare->setScale(Vec3(100.0f,100.0f,100.0f));
				mEntity->setDirection(Vec3(0.0f, 0.0f, 1.0f),  MG::ISceneNode::TS_WORLD);
				mEntityCampare->setDirection(Vec3(0.0f, 0.0f, 1.0f), MG::ISceneNode::TS_WORLD);

				mEntity->getEntity()->getAnimationController()->play("idle");
				mEntity->setMoveSpeed(7.0f);

				/*mEntityCampare = CSceneManager::getInstance().createPlayerCharacterEntity(0,1,"entity2","foot_soldier",Vec3(0,0,2));
				CPlayer::getInstance().getActiveClan()->addPlayerCharacter( 1 );
				mEntityCampare->setDirection(Vec3(0.0f, 0.0f, 1.0f),  MG::ISceneNode::TS_WORLD);				
				mEntityCampare->getEntity()->getModelObject()->getAnimationController()->play("idle");

				mEntityCampare->setMoveSpeed(1.0f);

				CSceneManager::getInstance().getEngineScene()->getActiveCamera()->focusPosition(Vec3(0,0,0));
				}
				else
				{
				if ( mEntity )
				{
				CSceneManager::getInstance().getEngineScene()->destroyEffectComponent("warmup");

				IEffectEntity* effect_entity = CSceneManager::getInstance().getEngineScene()->createEffectEntity("warmup", "BloodsStrike_01", true);
				if ( effect_entity && effect_entity->getSceneNode() )
				{
				if ( mEntity )
				effect_entity->getSceneNode()->setPosition(mEntity->getPos() + Vec3(0, 1.0, 0));
				}
				}

				}*/

				//IEntityGroup* effectEntity1 = CSceneManager::getInstance().getEngineScene()->createEntityGroup("arrow",4);
				//IEntity* effectEntity = effectEntity1->getEntity(0);
				//if ( effectEntity && effectEntity->getSceneNode() )
				//	effectEntity->getSceneNode()->setPosition(Vec3(0,20,0));
			//}

			/*if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_Y ))
			{
				mEngineEntity = ClientMain::getInstance().getScene()->createEntity(7);
				if ( mEngineEntity )
				{
					if ( mEngineEntity->getSceneNode() )
						mEngineEntity->getSceneNode()->setPosition(Vec3(0,10,0));
					mEngineEntity->getAnimationController()->play("gather");
				}*/
				//mEntityGroup = CSceneManager::getInstance().createTroopGroupEntity(1,1,5,1,Vec3(0,0,0));
				/*if ( mEntity )*/
				/*{
				CSceneManager::getInstance().getEngineScene()->destroyEffectComponent("Walk_Smoke_Big");

				IEffectEntity* effect_entity = CSceneManager::getInstance().getEngineScene()->createEffectEntity("charge", "Walk_Smoke_Big", true);
				if ( effect_entity && effect_entity->getSceneNode() )
				{
				if ( mEntity )
				effect_entity->getSceneNode()->setPosition(mEntity->getPos() + Vec3(0, 1.0, 0));
				}

				effect_pos
				}*/

				//if ( mEntity )
				/*{
				IEffectEntity* effect_entity = CSceneManager::getInstance().getEngineScene()->getEffectComponent("charge");

				if ( !effect_entity  )
				{
				IEffectEntity* effect_entity = CSceneManager::getInstance().getEngineScene()->createEffectEntity("charge", "Arrow", true);
				}

				if ( effect_entity && effect_entity->getSceneNode() )
				{
				if ( mEntity )
				effect_entity->getSceneNode()->setPosition(Vec3(0,0,0));
				}
				}*/
				/*IEntity* effectEntity = CSceneManager::getInstance().getEngineScene()->createEntity( "flag2" );
				if ( effectEntity && effectEntity->getSceneNode() )
				{
					effectEntity->getSceneNode()->setPosition(Vec3(0,10,0));
					effectEntity->getAnimationController()->play("flutter");
				}*/
			//}

			//if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_A ))
			//{
			//	if ( mEntity )
			//	{
			//		if ( ani_num == 0 )
			//		{
			//			mEntity->getEntity()->getAnimationController()->play("atk1");
			//		}
			//		else if ( ani_num == 1 )
			//		{
			//			mEntity->getEntity()->getAnimationController()->play("atk2");
			//		}
			//		else if ( ani_num == 2 )
			//		{
			//			mEntity->getEntity()->getAnimationController()->play("atk3");
			//		}
			//		else if ( ani_num == 3 )
			//		{
			//			mEntity->getEntity()->getAnimationController()->play("die");
			//		}
			//		else if ( ani_num == 4 )
			//		{
			//			mEntity->getEntity()->getAnimationController()->play("run");
			//		}
			//		else if ( ani_num == 5 )
			//		{
			//			mEntity->getEntity()->getAnimationController()->play("run1");
			//		}
			//		else if ( ani_num == 6 )
			//		{
			//			mEntity->getEntity()->getAnimationController()->play("walk");
			//		}
			//		else if ( ani_num == 7 )
			//		{
			//			mEntity->getEntity()->getAnimationController()->play("skill1");
			//		}
			//		else if ( ani_num == 8 )
			//		{
			//			mEntity->getEntity()->getAnimationController()->play("skill2");
			//		}
			//		else if ( ani_num == 9 )
			//		{
			//			mEntity->getEntity()->getAnimationController()->play("idle");
			//		}
			//		else if ( ani_num == 10 )
			//		{
			//			if ( mEntityGroup )
			//			{
			//				//mEntityGroup->startInjectSkill(data->skillId, (GAMEOBJ_TYPE)data->objectType, data->objectId, data->objectIndex);
			//			}
			//		}
			//		
			//		ani_num++;
			//		if ( ani_num > 10 )
			//			ani_num = 0;

			//	}
			//}

			//if ( ClientMain::getInstance().getEngine()->input()->isMousePressed(MB_Left) )
			//{
			//	if ( mEntity )
			//	{            // 分配处理鼠标左健地面事件
			//		Vec3 pos;
			//		if ( ClientMain::getInstance().getScene()->getTerrainManager()->getMouseRayIntersection(pos) )
			//			mEntity->moveTo( pos );
			//	}
			//}

			//if ( ClientMain::getInstance().getEngine()->input()->isKeyPressed(KC_X) )
			//{
			//	if ( mEntity )
			//	{            // 分配处理鼠标左健地面事件
			//		//mEntity->getEntity()->getModelObject()->getAnimationController()->stopAll();
			//	}
			//}

			//if ( ClientMain::getInstance().getEngine()->input()->isKeyPressed(KC_J) )
			//{
			//	if ( mEntity )
			//	{            // 分配处理鼠标左健地面事件
			//		mEntity->startInjectSkill(1, Vec3(0,0,1));
			//	}

			//}

			/*if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_Z ))
			{


			}*/

			/*if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_Z ))
			{
			if ( mEntity->isEntityCreated() )
			mEntity->moveTo(Vec3(0.0f,0.0f,200.0f));
			}

			if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_X ))
			{
			if ( mEntity->isEntityCreated() )
			mEntity->moveTo(Vec3(200.0f, 0.0f, 0.0f));
			}

			if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_Y ))
			{
			if ( mEntity->isEntityCreated() )
			mEntity->moveTo(Vec3(0.0f,200.0f,0.0f));
			}*/


		//}
		return true;
	}
}
