/******************************************************************************/
#include "stdafx.h"
#include "ClientNetApplyManager.h"
#include "PlayerCharacterNetPacket.h"
#include "MonsterNetPacketProcesser.h"
//#include "CWorldManager.h"
#include "CMonsterEntity.h"
#include "CSceneManager.h"
#include "CPlayer.h"
#include "ClientMain.h"
#include "HeadDamageManage.h"
#include "UIMessageBox.h"

#include "MonsterData.h"

#include "NetPacketPackManager.h"
#include "PlayerNetPacketProcesser.h"
#include "SkillObject.h"
#include "CSkillOwnManager.h"
#include "UIMessageBox.h"
#include "MapListCsv.h"
#include "CRegionManager.h"
/******************************************************************************/
namespace MG
{
	//-----------------------------------------------------------------------
	Bool MonsterNetPacketProcesser::processFrontServerPacket(I32 id,NetEventRecv* packet)
	{
		if ( packet->getChannel() == GNPC_MONSTER )
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
				case PT_MONSTER_S2C_STOP_MOVE:
					onRecvMonsterStopMove(id, (PT_MONSTER_S2C_STOP_MOVE_DATA*)data->data);
					break;
				case PT_MONSTER_S2C_MOVE_POS:
					onRecvMonsterMove(id, (PT_MONSTER_S2C_MOVE_POS_DATA*)data->data);
					break;
				case PT_MONSTER_S2C_INSTANT_MOVE_POS:
					onRecvInstantMonsterMove(id, (PT_MONSTER_S2C_INSTANT_MOVE_POS_DATA*)data->data);
					break;
				case PT_MONSTER_S2C_ENTER_FIGHT:
					onRecvMonsterEnterFight(id, (PT_MONSTER_S2C_ENTER_FIGHT_DATA*)data->data);
					break;
				case PT_MONSTER_S2C_END_FIGHT:
					onRecvMonsterEndFight(id, (PT_MONSTER_S2C_END_FIGHT_DATA*)data->data);
					break;
			}
			return true;
		}

		return false;
	}

	//-----------------------------------------------------------------------
	void MonsterNetPacketProcesser::onRecvMonsterMove( I32 id, PT_MONSTER_S2C_MOVE_POS_DATA* data )
	{
		//FUNDETECTION(__MG_FUNC__);
		CMonsterEntity* monsterEntity = CSceneManager::getInstance().getMonsterEntity(data->monsterIndex);
		if (NULL != monsterEntity)
		{
			monsterEntity->doMoveToAction((NetVec2)data->startMovePos, (NetVec2)data->endMovePos, data->startMoveTime, false);
		}
	}

	//-----------------------------------------------------------------------
	void MonsterNetPacketProcesser::onRecvInstantMonsterMove( I32 id, PT_MONSTER_S2C_INSTANT_MOVE_POS_DATA* data )
	{
		CMonsterEntity* monsterEntity = CSceneManager::getInstance().getMonsterEntity(data->monsterIndex);
		if (NULL != monsterEntity)
		{
			monsterEntity->setPos((NetVec2)data->moveToPos);
			monsterEntity->getEntity()->getSceneNode()->stickTerrain();
		}
	}

	//-----------------------------------------------------------------------
	void MonsterNetPacketProcesser::onRecvMonsterStopMove( I32 id, PT_MONSTER_S2C_STOP_MOVE_DATA* data )
	{
		CMonsterEntity* monsterEntity = CSceneManager::getInstance().getMonsterEntity(data->monsterIndex);
		if (NULL != monsterEntity)
		{
			monsterEntity->stopMoveToAction();
			monsterEntity->setPos((NetVec2)data->pos);
			monsterEntity->getEntity()->getSceneNode()->stickTerrain();
		}
	}

	//-----------------------------------------------------------------------
	void MonsterNetPacketProcesser::onRecvMonsterEnterFight(I32 id, PT_MONSTER_S2C_ENTER_FIGHT_DATA* data)
	{
		CMonsterEntity* monsterEntity = CSceneManager::getInstance().getMonsterEntity(data->monsterIndex);
		if (NULL != monsterEntity)
		{
			monsterEntity->setBattleState(true);
			monsterEntity->getDynamicData()->moveSpeed = data->moveSpeed;
		}	
	}

	//-----------------------------------------------------------------------
	void MonsterNetPacketProcesser::onRecvMonsterEndFight(I32 id, PT_MONSTER_S2C_END_FIGHT_DATA* data)
	{
		CMonsterEntity* monsterEntity = CSceneManager::getInstance().getMonsterEntity(data->monsterIndex);
		if (NULL != monsterEntity)
		{
			monsterEntity->setBattleState(false);
			monsterEntity->getDynamicData()->moveSpeed = data->moveSpeed;
		}
	}

}