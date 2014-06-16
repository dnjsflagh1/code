/******************************************************************************/
#include "stdafx.h"
#include "SSkillNetPacketProcesser.h"
#include "SPlayerCharacter.h"
#include "SWorldManager.h"
#include "NetTranspondPacketProcesser.h"
#include "LuaManager.h"
#include "SLuaSkillSystem.h"
#include "SkillObject.h"
#include "SWorldManager.h"
#include "AttributePara.h"
#include "AttributeFormula.h"
#include "SkillInfoList.h"
#include "SSkillOwnManager.h"
#include "SSkillUseManager.h"
#include "SCDManager.h"
#include "SMonster.h"
#include "SSkillObject.h"
#include "SSceneGridManager.h"
#include "SelfAreaSkillTemplate.h"
#include "TargetPosAreaSkillTemplate.h"
#include "STroop.h"
/******************************************************************************/

namespace MG
{
    //-----------------------------------------------------------------------
	SSkillNetPacketProcesser::SSkillNetPacketProcesser()
	{

	}

    //-----------------------------------------------------------------------
	SSkillNetPacketProcesser::~SSkillNetPacketProcesser()
	{

	}

    //----------------------------------------------------------------------------------------------------------------------------------------
	Bool SSkillNetPacketProcesser::processFrontServerPacket(I32 id, NetEventRecv *packet)
	{
		if(packet->getChannel() == GNPC_SKILL)
		{
#if 0
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());
			switch(data->type)
			{
			case PT_SKILL_C2M_PLAYERCHARACTER_CLANT:
				onRecvPlayCharacterClantSkillFromFrontServer(id, (PT_SKILL_C2M_PLAYERCHARACTER_CLANT_DATA*)data->data);
				break;
			case PT_SKILL_C2M_PLAYERCHARACTER_INJECT_EMITTER:
				onRecvPlayCharacterInjectEmitterSkill(id, (PT_SKILL_C2M_PLAYERCHARACTER_INJECT_EMITTER_DATA*)data->data);
				break;
			case PT_SKILL_C2M_PLAYERCHARACTER_INJECT_POINT:
				onRecvPlayCharacterInjectPointSkill(id, (PT_SKILL_C2M_PLAYERCHARACTER_INJECT_POINT_DATA*)data->data);
				break;
			case PT_SKILL_C2M_PLAYERCHARACTER_INJECT_OBJECT:
				onRecvPlayCharacterInjectObjectSkill(id, (PT_SKILL_C2M_PLAYERCHARACTER_INJECT_OBJECT_DATA*)data->data);
				break;
			case PT_SKILL_C2M_TROOP_CLANT:
				onRecvTroopClantSkillFromFrontServer(id, (PT_SKILL_C2M_TROOP_CLANT_DATA*)data->data);
				break;
			case PT_SKILL_C2M_TROOP_INJECT_EMITTER:
				onRecvTroopInjectEmitterSkill(id, (PT_SKILL_C2M_TROOP_INJECT_EMITTER_DATA*)data->data);
				break;
			case PT_SKILL_C2M_TROOP_INJECT_POINT:
				onRecvTroopInjectPointSkill(id, (PT_SKILL_C2M_TROOP_INJECT_POINT_DATA*)data->data);
				break;
			case PT_SKILL_C2M_TROOP_INJECT_OBJECT:
				onRecvTroopInjectObjectSkill(id, (PT_SKILL_C2M_TROOP_INJECT_OBJECT_DATA*)data->data);
				break;
			case PT_SKILL_C2M_BUILDING_CLANT:
				onRecvBuildingClantSkillFromFrontServer(id, (PT_SKILL_C2M_BUILDING_CLANT_DATA*)data->data);
				break;
			case PT_SKILL_C2M_BUILDING_INJECT_EMITTER:
				onRecvBuildingInjectEmitterSkill(id, (PT_SKILL_C2M_BUILDING_INJECT_EMITTER_DATA*)data->data);
				break;
			case PT_SKILL_C2M_BUILDING_INJECT_POINT:
				onRecvBuildingInjectPointSkill(id, (PT_SKILL_C2M_BUILDING_INJECT_POINT_DATA*)data->data);
				break;
			case PT_SKILL_C2M_BUILDING_INJECT_OBJECT:
				onRecvBuildingInjectObjectSkill(id, (PT_SKILL_C2M_BUILDING_INJECT_OBJECT_DATA*)data->data);
				break;
			case PT_SKILL_F2M_LEARN:
				onRecvPlayerCharacterLearnSkill(id, (PT_SKILL_F2M_LEARN_DATA*)data->data);
				break;
			/*case  PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_PLAYERCHARACTER:
				onRecvPlaycharacterAffectCollisonPlaycharacter(id, (PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA*)data->data);
				break;
			case  PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_TROOP:
				onRecvPlaycharacterAffectCollisonTroop(id, (PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_TROOP_DATA*)data->data);
				break;
			case  PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_BUILDING:
				onRecvPlaycharacterAffectCollisonBuilding(id, (PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_BUILDING_DATA*)data->data);
				break;
			case  PT_SKILL_C2M_TROOP_AFFECT_COLLISION_TROOP:
				onRecvTroopAffectCollisonTroop(id, (PT_SKILL_C2M_TROOP_AFFECT_COLLISION_TROOP_DATA*)data->data);
				break;
			case  PT_SKILL_C2M_TROOP_AFFECT_COLLISION_PLAYERCHARACTER:
				onRecvTroopAffectCollisonPlaycharacter(id, (PT_SKILL_C2M_TROOP_AFFECT_COLLISION_PLAYERCHARACTER_DATA*)data->data);
				break;
			case  PT_SKILL_C2M_TROOP_AFFECT_COLLISION_BUILDING:
				onRecvTroopAffectCollisonBuilding(id, (PT_SKILL_C2M_TROOP_AFFECT_COLLISION_BUILDING_DATA*)data->data);
				break;
			case  PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_TROOP:
				onRecvBuildingAffectCollisonTroop(id, (PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_TROOP_DATA*)data->data);
				break;
			case  PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_PLAYERCHARACTER:
				onRecvBuildingAffectCollisonPlaycharacter(id, (PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_PLAYERCHARACTER_DATA*)data->data);
				break;
			case  PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_BUILDING:
				onRecvBuildingAffectCollisonBuilding(id, (PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_BUILDING_DATA*)data->data);
				break;*/
			default:
				return false;
			}

			return true;
#endif
		}

		return false;
	}

    //-----------------------------------------------------------------------
    void SSkillNetPacketProcesser::onRecvPlayCharacterClantSkillFromFrontServer(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_PLAYERCHARACTER_CLANT_DATA* data)
    {
#if 0
		SPlayerPtr player = SWorldManager::getInstance().getPlayerByClientNetId(id);
		if(player.isNull())
		{
			return;
		}

		SSceneObject* sceneObject = SWorldManager::getInstance.getSceneObject((REGION_OBJ_TYPE)regionType, regionId, instanceId);
		if(!sceneObject)
		{
			return;
		}

		SPlayerCharacterPtr playerCharacter;
		if(sceneObject->getPlayerCharacter(sceneObject, data->characterIndex) == false)
			return;

		if(playerCharacter.isNull() || playerCharacter->isDead())
			return;

		SPlayerPtr ownerPlayer;
		playerCharacter->getPlayer(ownerPlayer);
		if(ownerPlayer.isNull())
		{
			return;
		}

		if(player->getAccountId() != ownerPlayer->getAccountId())
		{
			return;
		}

		SkillInfo* skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(data->skillId);
		if(!skillInfo)
		{
			return;	
		}

		InitiativeSkillBasicInfo* initiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)skillInfo->skillInfo;
		if(!initiativeSkillBasicInfo)
		{
			return;
		}

		if(playerCharacter->getMp() <= 0 && skillInfo->skillType != SKT_SHORTRANGEGENERAL
			&& skillInfo->skillType != SKT_LONGRANGEGENERAL && skillInfo->skillType != SKT_GOUPANDDOWN)
		{
			return;
		}

		/*if(playerCharacter->mCDTimer.ifGoing(initiativeSkillBasicInfo->ownerTimepieceId))
		{
		return;
		}*/

		判定释放技能的角色是否符合释放条件 未添加


		判定点击的目标是否为可作用 未添加

		SSkillOwnManager* skillOwnManager = playerCharacter->getSkillOwnManager();
		if(!skillOwnManager->isOwnSkill(data->skillId))
		{
			return;
		}

		SSkillUseManager* skillUseManager = playerCharacter->getSkillUseManager();
		SSkillObject* skillObject = (SSkillObject*)skillUseManager->prepareUseSkill(data->skillId);
		if(data->targetId != 0)
		{
			skillObject->setTargetObject((GAMEOBJ_TYPE)data->targetType, data->targetId, data->targetIndex);
		}
		else
		{
			skillObject->setTargetPosition(NetVec2(data->targetPos));
		}
		skillObject->startClant(true);


		SRegionObjectBase* regionObject = playerCharacter->getCurrentRegionObject();
		if(regionObject && regionObject->isOpen())
		{
			NetTranspondSendDataBufferPtr dataPtr ;
            NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );
			GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
			if ( packet )
			{
				packet->channel = GNPC_SKILL;
				packet->type    = PT_SKILL_M2C_PLAYERCHARACTER_CLANT;
				PT_SKILL_M2C_PLAYERCHARACTER_CLANT_DATA* sendData = (PT_SKILL_M2C_PLAYERCHARACTER_CLANT_DATA*)(packet->data);
				if(sendData)
				{
					sendData->characterIndex    = data->characterIndex;
					sendData->skillId        = data->skillId;
					sendData->characterPos  = data->characterPos;
					sendData->characterDir = data->characterDir;

					SRegionObjectBase* regionObjectBase = playerCharacter->getCurrentRegionObject();
					if(regionObjectBase)
					{
						NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(dataPtr, GameNetPacketData_INFO::headSize+PT_SKILL_M2C_PLAYERCHARACTER_CLANT_DATA_INFO::dataSize, 
							playerCharacter->getSceneObjectInSceneGridsManager()->currSceneGrid, NULL, regionObjectBase, 0);
					}
				}
			}
		}
#endif
    }
	//-----------------------------------------------------------------------
	void SSkillNetPacketProcesser::onRecvPlayCharacterInjectEmitterSkill(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_PLAYERCHARACTER_INJECT_EMITTER_DATA* data)
	{
#if 0
		SPlayerPtr player = SWorldManager::getInstance().getPlayerByClientNetId(id);
		if(player.isNull())
		{
			return;
		}

		SSceneObject* sceneObject = SWorldManager::getInstance.getSceneObject((REGION_OBJ_TYPE)regionType, regionId, instanceId);
		if(!sceneObject)
		{
			return;
		}

		SPlayerCharacterPtr playerCharacter;
		if(sceneObject->getPlayerCharacter(sceneObject, data->characterIndex) == false)
			return;

		if(playerCharacter.isNull() || playerCharacter->isDead())
			return;
		
		SPlayerPtr ownerPlayer;
		playerCharacter->getPlayer(ownerPlayer);
		if(ownerPlayer.isNull())
		{
			return;
		}

		if(player->getAccountID() != ownerPlayer->getAccountID())
		{
			return;
		}

		if(!playerCharacter->getSkillOwnManager()->isOwnSkill( data->skillId ))
		{
			return;
		}

		SkillInfo* skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(data->skillId);
		if(!skillInfo)
		{
			return;
		}

		if(!playerCharacter->getSkillUseManager()->isCanUseSkill( skillInfo ))
		{
			return;
		}

		InitiativeSkillBasicInfo* initiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)(SkillInfoList::getInstance().getSkillInfo(data->skillId)->skillInfo);
		if(!initiativeSkillBasicInfo)
		{
			return;
		}

		if(playerCharacter->getSCDManager()->checkCD(CD_MASTER_TYPE_CHARACTER, initiativeSkillBasicInfo->ownerTimepieceId))
		{
			return;
		}

		if(playerCharacter->getMp() <= 0 && skillInfo->skillType != SKT_SHORTRANGEGENERAL
			&& skillInfo->skillType != SKT_LONGRANGEGENERAL && skillInfo->skillType != SKT_GOUPANDDOWN)
		{
			return;
		}

		const AttrParaInfo* attrParaInfo;
		if(initiativeSkillBasicInfo->formulaParameterId2 != 0)
		{
			attrParaInfo = AttributePara::getInstance().getAttrParaInfo(initiativeSkillBasicInfo->formulaParameterId2);
			if(!attrParaInfo)
			{
				return;
			}

			Int val = AttributeFormula::getInstance().calValue(playerCharacter->getAttributeSet(), playerCharacter->getCharacterData(), attrParaInfo->para, attrParaInfo->attrID, attrParaInfo->FormulaId);

			switch(initiativeSkillBasicInfo->spendType)
			{
			case ST_HP:
				playerCharacter->syncAddOrReduceHp(-val);
				break;
			case ST_MP:
				playerCharacter->syncAddOrReduceMp(-val);
				break;
			case ST_HPMP:
				playerCharacter->syncAddOrReduceHp(-val);
				playerCharacter->syncAddOrReduceMp(-val);
				break;
			case ST_SP:
				playerCharacter->syncAddOrReduceSp(-val);
				break;
			case ST_PROMILLE_HP:

				playerCharacter->syncAddOrReduceHp(-(playerCharacter->getMaxHp() * val * 0.001));
				break;
			case ST_PROMILLE_MP:
				playerCharacter->syncAddOrReduceMp(-(playerCharacter->getMaxMp() * val * 0.001));
				break;
			case ST_PROMILLE_HPMP:
				playerCharacter->syncAddOrReduceHp(-(playerCharacter->getMaxHp() * val * 0.001));
				playerCharacter->syncAddOrReduceMp(-(playerCharacter->getMaxMp() * val * 0.001));
				break;
			case ST_PROMILLE_SP:
				playerCharacter->syncAddOrReduceSp(-(playerCharacter->getMaxSp() * val * 0.001));
				break;
			}

		}

		playerCharacter->getSCDManager()->addCD(
			CD_MASTER_TYPE_CHARACTER, 
			initiativeSkillBasicInfo->ownerTimepieceId, 
			initiativeSkillBasicInfo->ownerTimepieceDelay,
			initiativeSkillBasicInfo->ownerTimepieceDelay
			);

		 广播区域所有玩家
		SRegionObjectBase* regionObject = playerCharacter->getCurrentRegionObject();
		if(regionObject && regionObject->isOpen())
		{
			NetTranspondSendDataBufferPtr dataPtr  ;
            NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

			GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
			if ( packet )
			{
				packet->channel = GNPC_SKILL;
				packet->type    = PT_SKILL_M2C_PLAYERCHARACTER_INJECT_EMITTER;
				PT_SKILL_M2C_PLAYERCHARACTER_INJECT_EMITTER_DATA* sendData = (PT_SKILL_M2C_PLAYERCHARACTER_INJECT_EMITTER_DATA*)(packet->data);
				if(sendData)
				{
					sendData->characterIndex    = data->characterIndex;
					sendData->skillId        = data->skillId;
					sendData->injectDir		 = data->injectDir;

					SRegionObjectBase* regionObjectBase = playerCharacter->getCurrentRegionObject();
					if(regionObjectBase)
					{
						NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(dataPtr, GameNetPacketData_INFO::headSize+PT_SKILL_M2C_PLAYERCHARACTER_INJECT_EMITTER_DATA_INFO::dataSize, 
							playerCharacter->getSceneObjectInSceneGridsManager()->currSceneGrid, NULL, regionObjectBase, 0);
					}
				}
			}
		}
#endif
	}

	////-----------------------------------------------------------------------
	void SSkillNetPacketProcesser::onRecvPlayCharacterInjectObjectSkill(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_PLAYERCHARACTER_INJECT_OBJECT_DATA* data)
	{
#if 0
		SPlayerPtr player = SWorldManager::getInstance().getPlayerByClientNetId(id);
		if(player.isNull())
		{
			return;
		}

		SSceneObject* sceneObject = SWorldManager::getInstance.getSceneObject((REGION_OBJ_TYPE)regionType, regionId, instanceId);
		if(!sceneObject)
		{
			return;
		}

		SPlayerCharacterPtr playerCharacter;
		if(sceneObject->getPlayerCharacter(sceneObject, data->characterIndex) == false)
			return;

		if(playerCharacter.isNull() || playerCharacter->isDead())
			return;

		SPlayerPtr ownerPlayer;
		playerCharacter->getPlayer(ownerPlayer);
		if(ownerPlayer.isNull())
		{
			return;
		}

		if(player->getAccountID() != ownerPlayer->getAccountID())
		{
			return;
		}

		if(!playerCharacter->getSkillOwnManager()->isOwnSkill( data->skillId ))
		{
			return;
		}

		SCharacter* objectCharacter = NULL;
		if(data->objectType == GOT_PLAYERCHARACTER)
		{
			SPlayerCharacterPtr objectPlayerCharacter;
			if(sceneObject->getPlayerCharacter(objectPlayerCharacter, data->objectId) == false)
			{
				return;
			}

			objectCharacter = objectPlayerCharacter.getPointer();
		}
		else if(data->objectType == GOT_SOLDIER)
		{
			STroopNew* troop = SWorldManager::getInstance().getTroopFromMemory((REGION_OBJ_TYPE)data->regionType, (RegionIdType)regionId, data->instanceUid, data->objectId);
			if(!troop)
			{
				return;
			}

			objectCharacter = troop->getTroopSoldier(data->objectIndex);
			if(!objectCharacter)
			{
				return;
			}

			taregtRegionId = troop->getRegionID();

			objectCharacter = troopGroup->getTroop(data->objectIndex);
		}
		else if(data->objectType == GOT_TROOP)
		{
			STroopPtr objectTroop;
			if(sceneObject->getTroop(objectTroop, data->objectId) == false)
			{
				return;
			}

			objectCharacter = objectTroop.getPointer();
		}
		else if(data->objectType == GOT_BUILDING)
		{
			SBuildingPtr objectBuilding;
			if(sceneObject->getBuilding(objectBuilding, data->objectId) == false)
			{
				return;
			}

			objectCharacter = objectBuilding.getPointer();
		}
		else if(data->objectType == GOT_MONSTER)
		{
			SMonsterPtr objectMonster;
			if(sceneObject->getMonster(objectMonster, data->objectId) == false)
			{
				return;
			}

			objectCharacter = objectMonster.getPointer();
		}

		if(!objectCharacter || objectCharacter->isDead())
		{
			return;
		}

		SkillInfo* skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(data->skillId);
		if(!skillInfo)
		{
			return;
		}

		if(!playerCharacter->getSkillUseManager()->isCanUseSkill(skillInfo, objectCharacter))
		{
			return;
		}

		InitiativeSkillBasicInfo* initiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)(SkillInfoList::getInstance().getSkillInfo(data->skillId)->skillInfo);
		if(!initiativeSkillBasicInfo)
		{
			return;
		}

		if(playerCharacter->getSCDManager()->checkCD(CD_MASTER_TYPE_CHARACTER, initiativeSkillBasicInfo->ownerTimepieceId))
		{
			return;
		}

		if(playerCharacter->getMp() <= 0 && skillInfo->skillType != SKT_SHORTRANGEGENERAL
			&& skillInfo->skillType != SKT_LONGRANGEGENERAL && skillInfo->skillType != SKT_GOUPANDDOWN)
		{
			return;
		}

		const AttrParaInfo* attrParaInfo;
		if(initiativeSkillBasicInfo->formulaParameterId2 != 0)
		{
			attrParaInfo = AttributePara::getInstance().getAttrParaInfo(initiativeSkillBasicInfo->formulaParameterId2);
			if(!attrParaInfo)
			{
				return;
			}

			Int val = AttributeFormula::getInstance().calValue(playerCharacter->getAttributeSet(), playerCharacter->getCharacterData(), attrParaInfo->para, attrParaInfo->attrID, attrParaInfo->FormulaId);

			switch(initiativeSkillBasicInfo->spendType)
			{
			case ST_HP:
				playerCharacter->syncAddOrReduceHp(-val);
				break;
			case ST_MP:
				playerCharacter->syncAddOrReduceMp(-val);
				break;
			case ST_HPMP:
				playerCharacter->syncAddOrReduceHp(-val);
				playerCharacter->syncAddOrReduceMp(-val);
				break;
			case ST_SP:
				playerCharacter->syncAddOrReduceSp(-val);
				break;
			case ST_PROMILLE_HP:
				
				playerCharacter->syncAddOrReduceHp(-(playerCharacter->getMaxHp() * val * 0.001));
				break;
			case ST_PROMILLE_MP:
				playerCharacter->syncAddOrReduceMp(-(playerCharacter->getMaxMp() * val * 0.001));
				break;
			case ST_PROMILLE_HPMP:
				playerCharacter->syncAddOrReduceHp(-(playerCharacter->getMaxHp() * val * 0.001));
				playerCharacter->syncAddOrReduceMp(-(playerCharacter->getMaxMp() * val * 0.001));
				break;
			case ST_PROMILLE_SP:
				playerCharacter->syncAddOrReduceSp(-(playerCharacter->getMaxSp() * val * 0.001));
				break;
			}

		}

		playerCharacter->getSCDManager()->addCD(
			CD_MASTER_TYPE_CHARACTER, 
			initiativeSkillBasicInfo->ownerTimepieceId, 
			initiativeSkillBasicInfo->ownerTimepieceDelay,
			initiativeSkillBasicInfo->ownerTimepieceDelay
			);

		 
			 广播区域所有玩家
		SRegionObjectBase* regionObject = playerCharacter->getCurrentRegionObject();
		if(regionObject && regionObject->isOpen())
		{
			NetTranspondSendDataBufferPtr dataPtr ;
            NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

			GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
			if ( packet )
			{
				packet->channel = GNPC_SKILL;
				packet->type    = PT_SKILL_M2C_PLAYERCHARACTER_INJECT_OBJECT;
				PT_SKILL_M2C_PLAYERCHARACTER_INJECT_OBJECT_DATA* sendData = (PT_SKILL_M2C_PLAYERCHARACTER_INJECT_OBJECT_DATA*)(packet->data);
				if(sendData)
				{
					sendData->characterIndex    = data->characterIndex;
					sendData->skillId        = data->skillId;
					sendData->objectId		= data->objectId;
					sendData->objectType		= data->objectType;
					sendData->objectIndex	= data->objectIndex;

					SRegionObjectBase* regionObjectBase = playerCharacter->getCurrentRegionObject();
					if(regionObjectBase)
					{
						NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(dataPtr, GameNetPacketData_INFO::headSize+PT_SKILL_M2C_PLAYERCHARACTER_INJECT_OBJECT_DATA_INFO::dataSize, 
							playerCharacter->getSceneObjectInSceneGridsManager()->currSceneGrid, NULL, regionObjectBase, 0);
					}
				}
			}
		}
#endif
	}
	
	//-----------------------------------------------------------------------
	void SSkillNetPacketProcesser::onRecvPlayCharacterInjectEndSkill(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_PLAYERCHARACTER_END_INJECT_DATA* data)
	{
#if 0
		SPlayerPtr player = SWorldManager::getInstance().getPlayerByClientNetId(id);
		if(player.isNull())
		{
			return;
		}

		SSceneObject* sceneObject = SWorldManager::getInstance.getSceneObject((REGION_OBJ_TYPE)regionType, regionId, instanceId);
		if(!sceneObject)
		{
			return;
		}

		SPlayerCharacterPtr playerCharacter;
		if(sceneObject->getPlayerCharacter(sceneObject, data->characterIndex) == false)
			return;

		if(playerCharacter.isNull() || playerCharacter->isDead())
			return;

		SPlayerPtr ownerPlayer;
		playerCharacter->getPlayer(ownerPlayer);
		if(ownerPlayer.isNull())
		{
			return;
		}

		if(player->getAccountID() != ownerPlayer->getAccountID())
		{
			return;
		}

		SSkillObject* skillObject = (SSkillObject*)playerCharacter->getSkillUseManager()->getPreparedUseSkill();
		if(	!skillObject || skillObject->getSkillInfo()->skillId != data->skillId )
		{
			return;
		}

		skillObject->stopUse();

		 广播区域所有玩家
		SRegionObjectBase* regionObject = playerCharacter->getCurrentRegionObject();
		if(!regionObject || !regionObject->isOpen())
		{
			return;
		}

		NetTranspondSendDataBufferPtr dataPtr ;
        NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if ( packet )
		{
			packet->channel = GNPC_SKILL;
			packet->type    = PT_SKILL_M2C_PLAYERCHARACTER_END_INJECT;
			PT_SKILL_M2C_PLAYERCHARACTER_END_INJECT_DATA* sendData = (PT_SKILL_M2C_PLAYERCHARACTER_END_INJECT_DATA*)(packet->data);
			if(sendData)
			{
				sendData->characterIndex    = data->characterIndex;
				sendData->skillId        = data->skillId;

				SRegionObjectBase* regionObjectBase = playerCharacter->getCurrentRegionObject();
				if(regionObjectBase)
				{
					NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(dataPtr, GameNetPacketData_INFO::headSize+PT_SKILL_M2C_PLAYERCHARACTER_END_INJECT_DATA_INFO::dataSize, 
						playerCharacter->getSceneObjectInSceneGridsManager()->currSceneGrid, NULL, regionObjectBase, 0);
				}
			}
		}
#endif
	}

	//-----------------------------------------------------------------------
	void SSkillNetPacketProcesser::onRecvPlayCharacterInjectPointSkill(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_PLAYERCHARACTER_INJECT_POINT_DATA* data)
	{
#if 0
		SPlayerPtr player = SWorldManager::getInstance().getPlayerByClientNetId(id);
		if(player.isNull())
		{
			return;
		}

		SSceneObject* sceneObject = SWorldManager::getInstance.getSceneObject((REGION_OBJ_TYPE)regionType, regionId, instanceId);
		if(!sceneObject)
		{
			return;
		}

		SPlayerCharacterPtr playerCharacter;
		if(sceneObject->getPlayerCharacter(sceneObject, data->characterIndex) == false)
			return;

		if(playerCharacter.isNull() || playerCharacter->isDead())
			return;

		SPlayerPtr ownerPlayer;
		playerCharacter->getPlayer(ownerPlayer);
		if(ownerPlayer.isNull())
		{
			return;
		}

		if(player->getAccountID() != ownerPlayer->getAccountID())
		{
			return;
		}

		if(!playerCharacter->getSkillOwnManager()->isOwnSkill( data->skillId ))
		{
			return;
		}

		SkillInfo* skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(data->skillId);
		if(!skillInfo)
		{
			return;
		}

		if(!playerCharacter->getSkillUseManager()->isCanUseSkill( skillInfo ))
		{
			return;
		}

		InitiativeSkillBasicInfo* initiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)(SkillInfoList::getInstance().getSkillInfo(data->skillId)->skillInfo);
		if(!initiativeSkillBasicInfo)
		{
			return;
		}

		if(playerCharacter->getSCDManager()->checkCD(CD_MASTER_TYPE_CHARACTER, initiativeSkillBasicInfo->ownerTimepieceId))
		{
			return;
		}

		if(playerCharacter->getMp() <= 0 && skillInfo->skillType != SKT_SHORTRANGEGENERAL
			&& skillInfo->skillType != SKT_LONGRANGEGENERAL && skillInfo->skillType != SKT_GOUPANDDOWN)
		{
			return;
		}

		const AttrParaInfo* attrParaInfo;
		if(initiativeSkillBasicInfo->formulaParameterId2 != 0)
		{
			attrParaInfo = AttributePara::getInstance().getAttrParaInfo(initiativeSkillBasicInfo->formulaParameterId2);
			if(!attrParaInfo)
			{
				return;
			}

			Int val = AttributeFormula::getInstance().calValue(playerCharacter->getAttributeSet(), playerCharacter->getCharacterData(), attrParaInfo->para, attrParaInfo->attrID, attrParaInfo->FormulaId);

			switch(initiativeSkillBasicInfo->spendType)
			{
			case ST_HP:
				playerCharacter->syncAddOrReduceHp(-val);
				break;
			case ST_MP:
				playerCharacter->syncAddOrReduceMp(-val);
				break;
			case ST_HPMP:
				playerCharacter->syncAddOrReduceHp(-val);
				playerCharacter->syncAddOrReduceMp(-val);
				break;
			case ST_SP:
				playerCharacter->syncAddOrReduceSp(-val);
				break;
			case ST_PROMILLE_HP:

				playerCharacter->syncAddOrReduceHp(-(playerCharacter->getMaxHp() * val * 0.001));
				break;
			case ST_PROMILLE_MP:
				playerCharacter->syncAddOrReduceMp(-(playerCharacter->getMaxMp() * val * 0.001));
				break;
			case ST_PROMILLE_HPMP:
				playerCharacter->syncAddOrReduceHp(-(playerCharacter->getMaxHp() * val * 0.001));
				playerCharacter->syncAddOrReduceMp(-(playerCharacter->getMaxMp() * val * 0.001));
				break;
			case ST_PROMILLE_SP:
				playerCharacter->syncAddOrReduceSp(-(playerCharacter->getMaxSp() * val * 0.001));
				break;
			}

		}

		playerCharacter->getSCDManager()->addCD(
			CD_MASTER_TYPE_CHARACTER, 
			initiativeSkillBasicInfo->ownerTimepieceId, 
			initiativeSkillBasicInfo->ownerTimepieceDelay,
			initiativeSkillBasicInfo->ownerTimepieceDelay
			);

		 广播区域所有玩家
		SRegionObjectBase* regionObject = playerCharacter->getCurrentRegionObject();
		if(regionObject && regionObject->isOpen())
		{
			NetTranspondSendDataBufferPtr dataPtr ;
            NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

			GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
			if ( packet )
			{
				packet->channel = GNPC_SKILL;
				packet->type    = PT_SKILL_M2C_PLAYERCHARACTER_INJECT_POINT;
				PT_SKILL_M2C_PLAYERCHARACTER_INJECT_POINT_DATA* sendData = (PT_SKILL_M2C_PLAYERCHARACTER_INJECT_POINT_DATA*)(packet->data);
				if(sendData)
				{
					sendData->characterIndex    = data->characterIndex;
					sendData->skillId        = data->skillId;
					sendData->targetPos      = data->targetPos;
					sendData->dir			 = data->dir;

					SRegionObjectBase* regionObjectBase = playerCharacter->getCurrentRegionObject();
					if(regionObjectBase)
					{
						NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(dataPtr, GameNetPacketData_INFO::headSize+PT_SKILL_M2C_PLAYERCHARACTER_INJECT_POINT_DATA_INFO::dataSize, 
							playerCharacter->getSceneObjectInSceneGridsManager()->currSceneGrid, NULL, regionObjectBase, 0);
					}
				}
			}
		}
#endif
	}

	//-----------------------------------------------------------------------
	void SSkillNetPacketProcesser::sendMonsterInjectSkillToClient( SMonster* monster, SSkillObject* skillObject )
	{
#if 0
		if(!monster)
		{
			return;
		}
		
		SRegionObjectBase* regionObject = monster->getCurrentRegionObject();
		if(!regionObject || !regionObject->isOpen())
		{
			return;
		}

		NetTranspondSendDataBufferPtr dataPtr ;
        NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if ( packet )
		{
			packet->channel = GNPC_SKILL;
			packet->type    = PT_SKILL_M2C_PLAYERCHARACTER_INJECT_POINT;
		}

		switch(skillObject->getSkillInfo()->skillType)
		{
		case SKT_SHORTRANGEGENERAL:
		case SKT_LONGRANGEGENERAL:
			{
				packet->type    = PT_SKILL_M2C_MONSTER_INJECT_OBJECT;
				PT_SKILL_M2C_MONSTER_INJECT_OBJECT_DATA* sendData = (PT_SKILL_M2C_MONSTER_INJECT_OBJECT_DATA*)(packet->data);
				sendData->monsterIndex    = monster->getID();
				sendData->skillId      = skillObject->getSkillInfo()->skillId;
				sendData->objectId	   = skillObject->getTargetObjectID();
				sendData->objectType   = skillObject->getTargetObjectType();
				sendData->objectIndex  = skillObject->getTargetObjectIndex();

				SRegionObjectBase* regionObjectBase = monster->getCurrentRegionObject();
				if(regionObjectBase)
				{
					NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(dataPtr, GameNetPacketData_INFO::headSize+PT_SKILL_M2C_MONSTER_INJECT_OBJECT_DATA_INFO::dataSize, 
						monster->getSceneObjectInSceneGridsManager()->currSceneGrid, NULL, regionObjectBase, 0);
				}
			}
			break;
		case SKT_SINGLEEMITTER:
			{
				packet->type    = PT_SKILL_M2C_MONSTER_INJECT_EMITTER;
				PT_SKILL_M2C_MONSTER_INJECT_EMITTER_DATA* sendData = (PT_SKILL_M2C_MONSTER_INJECT_EMITTER_DATA*)(packet->data);

				Vec3 dir = skillObject->getTargetPosition() - monster->getPos();
				dir.y = 0;
				dir.normalise();

				sendData->monsterIndex    = monster->getID();
				sendData->skillId      = skillObject->getSkillInfo()->skillId;
				/*sendData->injectDir.x  = dir.x;
				sendData->injectDir.z  = dir.z;*/
				sendData->injectDir		= ((NetVec2)dir).getData();

				SRegionObjectBase* regionObjectBase = monster->getCurrentRegionObject();
				if(regionObjectBase)
				{
					NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(dataPtr, GameNetPacketData_INFO::headSize+PT_SKILL_M2C_MONSTER_INJECT_EMITTER_DATA_INFO::dataSize, 
						monster->getSceneObjectInSceneGridsManager()->currSceneGrid, NULL, regionObjectBase, 0);
				}
			}
			break;
		case SKT_SELFAREA:
		case SKT_TARGETPOSAREA:
			{
				packet->type    = PT_SKILL_M2C_MONSTER_INJECT_POINT;
				PT_SKILL_M2C_MONSTER_INJECT_POINT_DATA* sendData = (PT_SKILL_M2C_MONSTER_INJECT_POINT_DATA*)(packet->data);

				sendData->monsterIndex    = monster->getID();
				sendData->skillId      = skillObject->getSkillInfo()->skillId;
				/*sendData->targetPos.x   = skillObject->getTargetPosition().x;
				sendData->targetPos.z   = skillObject->getTargetPosition().z;*/
				sendData->targetPos	   = ((NetVec2)skillObject->getTargetPosition()).getData();

				SRegionObjectBase* regionObjectBase = monster->getCurrentRegionObject();
				if(regionObjectBase)
				{
					NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(dataPtr, GameNetPacketData_INFO::headSize+PT_SKILL_M2C_MONSTER_INJECT_POINT_DATA_INFO::dataSize, 
						monster->getSceneObjectInSceneGridsManager()->currSceneGrid, NULL, regionObjectBase, 0);
				}
			}
			break;
		}
#endif
	}

	//-----------------------------------------------------------------------
	void SSkillNetPacketProcesser::onRecvTroopUseSkill(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2S_TROOP_USE_SKILL_DATA* data)
	{
#if 0
		SPlayerPtr player = SWorldManager::getInstance().getPlayerByClientNetId(id);
		if(player.isNull())
		{
			return;
		}

		SSceneObject* sceneObject = SWorldManager::getInstance.getSceneObject((REGION_OBJ_TYPE)regionType, regionId, instanceId);
		if(!sceneObject)
		{
			return;
		}

		STroopPtr troop;
		if(sceneObject->getTroop(sceneObject, data->troopIndex) == false)
			return;

		if(troop.isNull() || troop->isDead())
			return;

		SPlayerPtr ownerPlayer;
		troop->getPlayer(ownerPlayer);
		if(ownerPlayer.isNull())
		{
			return;
		}

		if(player->getAccountID() != ownerPlayer->getAccountID())
		{
			return;
		}

		SkillInfo* skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(data->skillId);
		if(!skillInfo)
		{
			return;	
		}

		InitiativeSkillBasicInfo* initiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)skillInfo->skillInfo;
		if(!initiativeSkillBasicInfo)
		{
			return;
		}

		if(cdManager->checkCD(CD_MASTER_TYPE_TROOP, data->troopId, initiativeSkillBasicInfo->ownerTimepieceId))
		{
			return;
		}

		SSkillUseManager* skillUseManager = troopSoldier->getSkillUseManager();
		SSkillObject* skillObject = (SSkillObject*)skillUseManager->prepareUseSkill(data->skillId);
		if(data->targetId != 0)
		{
			skillObject->setTargetObject((GAMEOBJ_TYPE)data->targetType, data->targetId, data->targetIndex);
		}
		else
		{
			skillObject->setTargetPosition(NetVec2(data->targetPos));
		}

		skillObject->startClant(true);


		 广播区域所有玩家
		SRegionObjectBase* regionObject = troop->getCurrentRegionObject();
		if(regionObject && regionObject->isOpen())
		{
			NetTranspondSendDataBufferPtr dataPtr  ;
            NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

			GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
			if ( packet )
			{
				packet->channel = GNPC_SKILL;
				packet->type    = PT_SKILL_S2C_TROOP_USE_SKILL;
				PT_SKILL_S2C_TROOP_USE_SKILL_DATA* sendData = (PT_SKILL_S2C_TROOP_USE_SKILL_DATA*)(packet->data);
				if(sendData)
				{
					sendData->troopIndex = data->troopIndex;
					sendData->skillId = data->skillId;
					sendData->targetType = data->targetType;
					sendData->targetId = data->targetIndex;
					sendData->targetPos = data->targetPos;
					NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(dataPtr, GameNetPacketData_INFO::headSize+PT_SKILL_S2C_TROOP_USE_SKILL_DATA_INFO::dataSize,regionObject);
				}
			}
		}
#endif
	}

	////-----------------------------------------------------------------------
	void SSkillNetPacketProcesser::onRecvTroopClantSkillFromFrontServer(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_TROOP_CLANT_DATA* data)
	{
#if 0
		SPlayerPtr player = SWorldManager::getInstance().getPlayerByClientNetId(id);
		if(player.isNull())
		{
			return;
		}

		SSceneObject* sceneObject = SWorldManager::getInstance.getSceneObject((REGION_OBJ_TYPE)regionType, regionId, instanceId);
		if(!sceneObject)
		{
			return;
		}

		STroopPtr troop;
		if(sceneObject->getTroop(sceneObject, data->troopIndex) == false)
			return;

		if(troop.isNull() || troop->isDead())
			return;

		SPlayerPtr ownerPlayer;
		troop->getPlayer(ownerPlayer);
		if(ownerPlayer.isNull())
		{
			return;
		}

		if(player->getAccountID() != ownerPlayer->getAccountID())
		{
			return;
		}

		STroopSoldier* troopSoldier = troop->getTroopSoldier(data->soldierIndex);
		if(!troopSoldier)
		{
			return;
		}


		SkillInfo* skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(data->skillId);
		if(!skillInfo)
		{
			return;	
		}

		InitiativeSkillBasicInfo* initiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)skillInfo->skillInfo;
		if(!initiativeSkillBasicInfo)
		{
			return;
		}

		if(cdManager->checkCD(CD_MASTER_TYPE_TROOP, data->troopId, initiativeSkillBasicInfo->ownerTimepieceId))
		{
			return;
		}

		SSkillUseManager* skillUseManager = troopSoldier->getSkillUseManager();
		SSkillObject* skillObject = (SSkillObject*)skillUseManager->prepareUseSkill(data->skillId);
		if(data->targetId != 0)
		{
			skillObject->setTargetObject((GAMEOBJ_TYPE)data->targetType, data->targetId, data->targetIndex);
		}
		else
		{
			skillObject->setTargetPosition(NetVec2(data->targetPos));
		}

		skillObject->startClant(true);
		
		 广播区域所有玩家
		SRegionObjectBase* regionObject = troop->getCurrentRegionObject();
		if(regionObject && regionObject->isOpen())
		{
			NetTranspondSendDataBufferPtr dataPtr ;
            NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

			GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
			if ( packet )
			{
				packet->channel = GNPC_SKILL;
				packet->type    = PT_SKILL_M2C_TROOP_CLANT;
				PT_SKILL_M2C_TROOP_CLANT_DATA* sendData = (PT_SKILL_M2C_TROOP_CLANT_DATA*)(packet->data);
				if(sendData)
				{
					sendData->troopIndex = data->troopIndex;
					sendData->soldierIndex = data->soldierIndex;
					sendData->skillId = data->skillId;
					sendData->troopPos = data->troopPos;
					sendData->troopDir = data->troopDir;
					NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(dataPtr, GameNetPacketData_INFO::headSize+PT_SKILL_M2C_TROOP_CLANT_DATA_INFO::dataSize,regionObject);
				}
			}
		}
#endif
	}

	////-----------------------------------------------------------------------
	void SSkillNetPacketProcesser::onRecvTroopInjectEmitterSkill(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_TROOP_INJECT_EMITTER_DATA* data)
	{
#if 0
		SPlayerPtr player = SWorldManager::getInstance().getPlayerByClientNetId(id);
		if(player.isNull())
		{
			return;
		}

		SSceneObject* sceneObject = SWorldManager::getInstance.getSceneObject((REGION_OBJ_TYPE)regionType, regionId, instanceId);
		if(!sceneObject)
		{
			return;
		}

		STroopPtr troop;
		if(sceneObject->getTroop(sceneObject, data->troopIndex) == false)
			return;

		if(troop.isNull() || troop->isDead())
			return;

		SPlayerPtr ownerPlayer;
		troop->getPlayer(ownerPlayer);
		if(ownerPlayer.isNull())
		{
			return;
		}

		if(player->getAccountID() != ownerPlayer->getAccountID())
		{
			return;
		}

		STroopSoldier* troopSoldier = troop->getTroopSoldier(data->soldierIndex);
		if(!troopSoldier)
		{
			return;
		}

		SkillInfo* skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(data->skillId);
		if(!skillInfo)
		{
			return;
		}

		if(!troop->getSkillUseManager()->isCanUseSkill( skillInfo ))
		{
			return;
		}

		 广播区域所有玩家
		SRegionObjectBase* regionObject = troop->getCurrentRegionObject();
		if(regionObject && regionObject->isOpen())
		{
			NetTranspondSendDataBufferPtr dataPtr  ;
            NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

			GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
			if ( packet )
			{
				packet->channel = GNPC_SKILL;
				packet->type    = PT_SKILL_M2C_TROOP_INJECT_EMITTER;
				PT_SKILL_M2C_TROOP_INJECT_EMITTER_DATA* sendData = (PT_SKILL_M2C_TROOP_INJECT_EMITTER_DATA*)(packet->data);
				if(sendData)
				{
					sendData->troopIndex = data->troopIndex;
					sendData->soldierIndex = data->soldierIndex;
					sendData->skillId = data->skillId;
					sendData->injectDir = data->injectDir;
	
					NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(dataPtr, GameNetPacketData_INFO::headSize+PT_SKILL_M2C_TROOP_INJECT_EMITTER_DATA_INFO::dataSize,regionObject);
				}
			}
		}
#endif
	}

	//-----------------------------------------------------------------------
	void SSkillNetPacketProcesser::onRecvTroopInjectObjectSkill(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_TROOP_INJECT_OBJECT_DATA* data)
	{
#if 0
		SPlayerPtr player = SWorldManager::getInstance().getPlayerByClientNetId(id);
		if(player.isNull())
		{
			return;
		}

		SSceneObject* sceneObject = SWorldManager::getInstance.getSceneObject((REGION_OBJ_TYPE)regionType, regionId, instanceId);
		if(!sceneObject)
		{
			return;
		}

		STroopPtr troop;
		if(sceneObject->getTroop(sceneObject, data->troopIndex) == false)
			return;

		if(troop.isNull() || troop->isDead())
			return;

		SPlayerPtr ownerPlayer;
		troop->getPlayer(ownerPlayer);
		if(ownerPlayer.isNull())
		{
			return;
		}

		if(player->getAccountID() != ownerPlayer->getAccountID())
		{
			return;
		}

		STroopSoldier* troopSoldier = troop->getTroopSoldier(data->soldierId);
		if(!troopSoldier)
		{
			return;
		}


		SkillInfo* skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(data->skillId);
		if(!skillInfo)
		{
			return;
		}

		SCharacter* objectCharacter = NULL;
		if(data->objectType == GOT_PLAYERCHARACTER)
		{
			SPlayerCharacterPtr objectPlayerCharacter;
			if(sceneObject->getPlayerCharacter(objectPlayerCharacter, data->objectId) == false)
			{
				return;
			}

			objectCharacter = objectPlayerCharacter.getPointer();
		}
		else if(data->objectType == GOT_SOLDIER)
		{
			STroopNew* troop = SWorldManager::getInstance().getTroopFromMemory((REGION_OBJ_TYPE)data->regionType, (RegionIdType)regionId, data->instanceUid, data->objectId);
			if(!troop)
			{
				return;
			}

			objectCharacter = troop->getTroopSoldier(data->objectIndex);
			if(!objectCharacter)
			{
				return;
			}

			taregtRegionId = troop->getRegionID();

			objectCharacter = troopGroup->getTroop(data->objectIndex);
		}
		else if(data->objectType == GOT_TROOP)
		{
			STroopPtr objectTroop;
			if(sceneObject->getTroop(objectTroop, data->objectId) == false)
			{
				return;
			}

			objectCharacter = objectTroop.getPointer();
		}
		else if(data->objectType == GOT_BUILDING)
		{
			SBuildingPtr objectBuilding;
			if(sceneObject->getBuilding(objectBuilding, data->objectId) == false)
			{
				return;
			}

			objectCharacter = objectBuilding.getPointer();
		}
		else if(data->objectType == GOT_MONSTER)
		{
			SMonsterPtr objectMonster;
			if(sceneObject->getMonster(objectMonster, data->objectId) == false)
			{
				return;
			}

			objectCharacter = objectMonster.getPointer();
		}

		if(!objectCharacter || objectCharacter->isDead())
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		if(!troop->getSkillUseManager()->isCanUseSkill( skillInfo, objectCharacter ))
		{
			return;
		}

		 广播区域所有玩家
		SRegionObjectBase* regionObject = troop->getCurrentRegionObject();
		if(regionObject && regionObject->isOpen())
		{
			NetTranspondSendDataBufferPtr dataPtr ;
            NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

			GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
			if ( packet )
			{
				packet->channel = GNPC_SKILL;
				packet->type    = PT_SKILL_M2C_TROOP_INJECT_OBJECT;
				PT_SKILL_M2C_TROOP_INJECT_OBJECT_DATA* sendData = (PT_SKILL_M2C_TROOP_INJECT_OBJECT_DATA*)(packet->data);
				if(sendData)
				{
					sendData->troopIndex = data->troopIndex;
					sendData->soldierIndex = data->soldierId;
					sendData->skillId = data->skillId;
					sendData->objectId = data->objectId;
					sendData->objectIndex = data->objectIndex;
					sendData->objectType = data->objectType;
					NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(dataPtr, GameNetPacketData_INFO::headSize+PT_SKILL_M2C_TROOP_INJECT_OBJECT_DATA_INFO::dataSize,regionObject);
				}
			}
		}
#endif
	}

	//-----------------------------------------------------------------------
	void SSkillNetPacketProcesser::onRecvTroopInjectPointSkill(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_TROOP_INJECT_POINT_DATA* data)
	{
#if 0
		SPlayerPtr player = SWorldManager::getInstance().getPlayerByClientNetId(id);
		if(player.isNull())
		{
			return;
		}

		SSceneObject* sceneObject = SWorldManager::getInstance.getSceneObject((REGION_OBJ_TYPE)regionType, regionId, instanceId);
		if(!sceneObject)
		{
			return;
		}

		STroopPtr troop;
		if(sceneObject->getTroop(sceneObject, data->troopIndex) == false)
			return;

		if(troop.isNull() || troop->isDead())
			return;

		SPlayerPtr ownerPlayer;
		troop->getPlayer(ownerPlayer);
		if(ownerPlayer.isNull())
		{
			return;
		}

		if(player->getAccountID() != ownerPlayer->getAccountID())
		{
			return;
		}

		STroopSoldier* troopSoldier = troop->getTroopSoldier(data->soldierIndex);
		if(!troopSoldier)
		{
			return;
		}

		SkillInfo* skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(data->skillId);
		if(!skillInfo)
		{
			return;
		}

		if(!troop->getSkillUseManager()->isCanUseSkill( skillInfo ))
		{
			return;
		}

		 广播区域所有玩家
		SRegionObjectBase* regionObject = troop->getCurrentRegionObject();
		if(regionObject && regionObject->isOpen())
		{
			NetTranspondSendDataBufferPtr dataPtr ;
            NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

			GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
			if ( packet )
			{
				packet->channel = GNPC_SKILL;
				packet->type    = PT_SKILL_M2C_TROOP_INJECT_POINT;
				PT_SKILL_M2C_TROOP_INJECT_POINT_DATA* sendData = (PT_SKILL_M2C_TROOP_INJECT_POINT_DATA*)(packet->data);
				if(sendData)
				{
					sendData->troopIndex = data->troopIndex;
					sendData->soldierIndex   = data->soldierIndex;
					sendData->skillId        = data->skillId;
					sendData->targetPos      = ((NetVec2)data->targetPos).getData();
					sendData->dir            = ((NetVec2)data->dir).getData();
					NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(dataPtr, GameNetPacketData_INFO::headSize+PT_SKILL_M2C_TROOP_INJECT_POINT_DATA_INFO::dataSize,regionObject);
				}
			}
		}
#endif
	}

	//-----------------------------------------------------------------------
	void SSkillNetPacketProcesser::onRecvBuildingClantSkillFromFrontServer(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_BUILDING_CLANT_DATA* data)
	{
#if 0
		SPlayerPtr player = SWorldManager::getInstance().getPlayerByClientNetId(id);
		if(player.isNull())
		{
			return;
		}

		SSceneObject* sceneObject = SWorldManager::getInstance.getSceneObject((REGION_OBJ_TYPE)regionType, regionId, instanceId);
		if(!sceneObject)
		{
			return;
		}

		SBuildingPtr building;
		if(sceneObject->getBuilding(sceneObject, data->buildingIndex) == false)
			return;

		if(building.isNull() || building->isDead())
			return;

		SPlayerPtr ownerPlayer;
		building->getPlayer(ownerPlayer);
		if(ownerPlayer.isNull())
		{
			return;
		}

		if(player->getAccountID() != ownerPlayer->getAccountID())
		{
			return;
		}

			if(player && player->getAccountId() == data->playerId && troop->getRegionID() == objectCharacter->getRegionID())
			 广播区域所有玩家
			SRegionObjectBase* regionObject = building->getCurrentRegionObject();
			if(regionObject && regionObject->isOpen())
			{
				NetTranspondSendDataBufferPtr dataPtr ;
                NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

				GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
				if ( packet )
				{
					packet->channel = GNPC_SKILL;
					packet->type    = PT_SKILL_M2C_BUILDING_CLANT;
					PT_SKILL_M2C_BUILDING_CLANT_DATA* sendData = (PT_SKILL_M2C_BUILDING_CLANT_DATA*)(packet->data);
					if(sendData)
					{
						sendData->buildingIndex = data->buildingIndex;
						sendData->skillId = data->skillId;
						NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(dataPtr, GameNetPacketData_INFO::headSize+PT_SKILL_M2C_BUILDING_CLANT_DATA_INFO::dataSize,regionObject);
					}
				}
			}
		}
#endif
	}

	//-----------------------------------------------------------------------
	void SSkillNetPacketProcesser::onRecvBuildingInjectEmitterSkill(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_BUILDING_INJECT_EMITTER_DATA* data)
	{
#if 0
		SPlayerPtr player = SWorldManager::getInstance().getPlayerByClientNetId(id);
		if(player.isNull())
		{
			return;
		}

		SSceneObject* sceneObject = SWorldManager::getInstance.getSceneObject((REGION_OBJ_TYPE)regionType, regionId, instanceId);
		if(!sceneObject)
		{
			return;
		}

		SBuildingPtr building;
		if(sceneObject->getBuilding(sceneObject, data->buildingIndex) == false)
			return;

		if(building.isNull() || building->isDead())
			return;

		SPlayerPtr ownerPlayer;
		building->getPlayer(ownerPlayer);
		if(ownerPlayer.isNull())
		{
			return;
		}

<<<<<<< .mine		if(player && player->getAccountId() == data->playerId)
=======		//if(player->getAccountID() != ownerPlayer->getAccountID())
		{
			return;
		}
		if( building)
>>>>>>> .theirs		{
			 广播区域所有玩家
			SRegionObjectBase* regionObject = building->getCurrentRegionObject();
			if(regionObject && regionObject->isOpen())
			{
				NetTranspondSendDataBufferPtr dataPtr ;
                NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

				GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
				if ( packet )
				{
					packet->channel = GNPC_SKILL;
					packet->type    = PT_SKILL_M2C_BUILDING_INJECT_EMITTER;
					PT_SKILL_M2C_BUILDING_INJECT_EMITTER_DATA* sendData = (PT_SKILL_M2C_BUILDING_INJECT_EMITTER_DATA*)(packet->data);
					if(sendData)
					{
						sendData->buildingId = data->buildingIndex;
						sendData->skillId = data->skillId;
						NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(dataPtr, GameNetPacketData_INFO::headSize+PT_SKILL_M2C_BUILDING_INJECT_EMITTER_DATA_INFO::dataSize,regionObject);
					}
				}
			}
		}
#endif
	}

	////-----------------------------------------------------------------------
	void SSkillNetPacketProcesser::onRecvBuildingInjectObjectSkill(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_BUILDING_INJECT_OBJECT_DATA* data)
	{
#if 0
		SPlayerPtr player = SWorldManager::getInstance().getPlayerByClientNetId(id);
		if(player.isNull())
		{
			return;
		}

		SSceneObject* sceneObject = SWorldManager::getInstance.getSceneObject((REGION_OBJ_TYPE)regionType, regionId, instanceId);
		if(!sceneObject)
		{
			return;
		}

		SBuildingPtr building;
		if(sceneObject->getBuilding(sceneObject, data->buildingIndex) == false)
			return;

		if(building.isNull() || building->isDead())
			return;

		SPlayerPtr ownerPlayer;
		building->getPlayer(ownerPlayer);
		if(ownerPlayer.isNull())
		{
			return;
		}

		if(player->getAccountID() != ownerPlayer->getAccountID())
		{
			return;
		}

		SCharacter* objectCharacter = NULL;

		if(data->objectType == GOT_PLAYERCHARACTER)
		{
			SPlayerCharacterPtr objectPlayerCharacter;
			if(sceneObject->getPlayerCharacter(objectPlayerCharacter, data->objectId) == false)
			{
				return;
			}

			objectCharacter = objectPlayerCharacter.getPointer();
		}
		else if(data->objectType == GOT_SOLDIER)
		{
			STroopNew* troop = SWorldManager::getInstance().getTroopFromMemory((REGION_OBJ_TYPE)data->regionType, (RegionIdType)regionId, data->instanceUid, data->objectId);
			if(!troop)
			{
				return;
			}

			objectCharacter = troop->getTroopSoldier(data->objectIndex);
			if(!objectCharacter)
			{
				return;
			}

			taregtRegionId = troop->getRegionID();

			objectCharacter = troopGroup->getTroop(data->objectIndex);
		}
		else if(data->objectType == GOT_TROOP)
		{
			STroopPtr objectTroop;
			if(sceneObject->getTroop(objectTroop, data->objectId) == false)
			{
				return;
			}

			objectCharacter = objectTroop.getPointer();
		}
		else if(data->objectType == GOT_BUILDING)
		{
			SBuildingPtr objectBuilding;
			if(sceneObject->getBuilding(objectBuilding, data->objectId) == false)
			{
				return;
			}

			objectCharacter = objectBuilding.getPointer();
		}
		else if(data->objectType == GOT_MONSTER)
		{
			SMonsterPtr objectMonster;
			if(sceneObject->getMonster(objectMonster, data->objectId) == false)
			{
				return;
			}

			objectCharacter = objectMonster.getPointer();
		}

		if(!objectCharacter || objectCharacter->isDead())
		{
			return;
		}

		 广播区域所有玩家
		SRegionObjectBase* regionObject = building->getCurrentRegionObject();
		if(regionObject && regionObject->isOpen())
		{

			NetTranspondSendDataBufferPtr dataPtr ;
            NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

			GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
			if ( packet )
			{
				packet->channel = GNPC_SKILL;
				packet->type    = PT_SKILL_M2C_BUILDING_INJECT_OBJECT;
				PT_SKILL_M2C_BUILDING_INJECT_OBJECT_DATA* sendData = (PT_SKILL_M2C_BUILDING_INJECT_OBJECT_DATA*)(packet->data);
				if(sendData)
				{
					sendData->buildingIndex	= data->buildingId;
					sendData->skillId       = data->skillId;
					sendData->objectId		= data->objectId;
					sendData->objectType	= data->objectType;
					sendData->objectIndex	= data->objectIndex;

					NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(dataPtr, GameNetPacketData_INFO::headSize+PT_SKILL_M2C_BUILDING_INJECT_OBJECT_DATA_INFO::dataSize,regionObject);
				}
			}
		}
#endif
	}

	//-----------------------------------------------------------------------
	void SSkillNetPacketProcesser::onRecvBuildingInjectPointSkill(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_BUILDING_INJECT_POINT_DATA* data)
	{
#if 0
		SPlayerPtr player = SWorldManager::getInstance().getPlayerByClientNetId(id);
		if(player.isNull())
		{
			return;
		}

		SSceneObject* sceneObject = SWorldManager::getInstance.getSceneObject((REGION_OBJ_TYPE)regionType, regionId, instanceId);
		if(!sceneObject)
		{
			return;
		}

		SBuildingPtr building;
		if(sceneObject->getBuilding(building, data->buildingIndex) == false)
			return;

		if(building.isNull() || building->isDead())
			return;

		SPlayerPtr ownerPlayer;
		building->getPlayer(ownerPlayer);
		if(ownerPlayer.isNull())
		{
			return;
		}

		if(player->getAccountID() != ownerPlayer->getAccountID())
		{
			return;
		}

		if(building)
		{
			 广播区域所有玩家
			SRegionObjectBase* regionObject = building->getCurrentRegionObject();
			if(regionObject && regionObject->isOpen())
			{
				NetTranspondSendDataBufferPtr dataPtr ;
                NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );

				GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
				if ( packet )
				{
					packet->channel = GNPC_SKILL;
					packet->type    = PT_SKILL_M2C_BUILDING_INJECT_POINT;
					PT_SKILL_M2C_BUILDING_INJECT_POINT_DATA* sendData = (PT_SKILL_M2C_BUILDING_INJECT_POINT_DATA*)(packet->data);
					if(sendData)
					{
						sendData->buildingIndex    = data->buildingIndex;
						sendData->skillId        = data->skillId;
						sendData->targetPos      = data->targetPos;

						NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(dataPtr, GameNetPacketData_INFO::headSize+PT_SKILL_M2C_BUILDING_INJECT_POINT_DATA_INFO::dataSize,regionObject);
					}
				}
			}
		}
#endif
	}

//	-----------------------------------------------------------------------
	void SSkillNetPacketProcesser::onRecvPlaycharacterAffectCollisonPlaycharacter(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA* data)
	{
#if 0
		if(data)
		{
			SSceneObject* sceneObject = SWorldManager::getInstance.getSceneObject((REGION_OBJ_TYPE)regionType, regionId, instanceId);
			if(!sceneObject)
			{
				return;
			}

			SPlayerCharacterPtr injectCharacter;
			if(sceneObject->getPlayerCharacter(injectCharacter, data->injectCharacterIndex) == false)
				return;

			if(injectCharacter.isNull())
				return;

			SPlayerCharacterPtr affectCharacter;
			if(sceneObject->getPlayerCharacter(affectCharacter, data->affectCharacterIndex) == false)
				return;

			if(affectCharacter.isNull() || affectCharacter->isDead())
				return;


			SkillInfo* skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(data->skillId);
			if(!skillInfo)
			{
				return;
			}

			InitiativeSkillBasicInfo* initiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)skillInfo->skillInfo;
			if(!initiativeSkillBasicInfo)
			{
				return;
			}

			if(skillInfo->skillType == SKT_LONGRANGEAUXILIARY)
			{
				Int hate = 0;
				affectCharacter->skillTreat((SCharacter*)affectCharacter, (SCharacter*)injectCharacter, initiativeSkillBasicInfo->damageType, initiativeSkillBasicInfo->formulaParameterId, hate, initiativeSkillBasicInfo->stateId, initiativeSkillBasicInfo->stateNum, initiativeSkillBasicInfo->randomState);
			}
			else
			{
				affectCharacter->obtainDamage((SCharacter*)injectCharacter, initiativeSkillBasicInfo->attackType, initiativeSkillBasicInfo->damageType, (ATTACK_POS)1, initiativeSkillBasicInfo->formulaParameterId, 0, initiativeSkillBasicInfo->stateId, initiativeSkillBasicInfo->stateNum, initiativeSkillBasicInfo->randomState);
			}
		}
#endif
	}

	//-----------------------------------------------------------------------
	void SSkillNetPacketProcesser::onRecvPlaycharacterAffectCollisonTroop(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_TROOP_DATA* data)
	{
#if 0
		if(data)
		{
			SSceneObject* sceneObject = SWorldManager::getInstance.getSceneObject((REGION_OBJ_TYPE)regionType, regionId, instanceId);
			if(!sceneObject)
			{
				return;
			}

			SPlayerCharacterPtr injectCharacter;
			if(sceneObject->getPlayerCharacter(injectCharacter, data->injectCharacterIndex) == false)
				return;

			if(injectCharacter.isNull())
				return;

			STroopPtr affectTroop;
			if(sceneObject->getTroop(affectTroop, data->affectTroopIndex) == false)
				return;

			if(affectTroop.isNull() || affectTroop->isDead())
				return;

			SkillInfo* skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(data->skillId);
			if(!skillInfo)
			{
				return;
			}

			InitiativeSkillBasicInfo* initiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)skillInfo->skillInfo;
			if(!initiativeSkillBasicInfo)
			{
				return;
			}

			affectTroop->obtainDamage((SCharacter*)injectCharacter, initiativeSkillBasicInfo->attackType, initiativeSkillBasicInfo->damageType, (ATTACK_POS)1, initiativeSkillBasicInfo->formulaParameterId);
		}
#endif
	}

//	-----------------------------------------------------------------------
	void SSkillNetPacketProcesser::onRecvPlaycharacterAffectCollisonBuilding(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_BUILDING_DATA* data)
	{
#if 0
		if(data)
		{
			SSceneObject* sceneObject = SWorldManager::getInstance.getSceneObject((REGION_OBJ_TYPE)regionType, regionId, instanceId);
			if(!sceneObject)
			{
				return;
			}

			SPlayerCharacterPtr injectCharacter;
			if(sceneObject->getPlayerCharacter(injectCharacter, data->injectCharacterIndex) == false)
				return;

			if(injectCharacter.isNull())
				return;

			SBuildingPtr affectBuilding;
			if(sceneObject->getBuilding(affectBuilding, data->affectBuildingIndex) == false)
				return;

			if(affectBuilding.isNull() || affectBuilding->isDead())
				return;


			SkillInfo* skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(data->skillId);
			if(!skillInfo)
			{
				return;
			}

			InitiativeSkillBasicInfo* initiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)skillInfo->skillInfo;
			if(!initiativeSkillBasicInfo)
			{
				return;
			}

			affectBuilding->obtainDamage((SCharacter*)injectCharacter, initiativeSkillBasicInfo->attackType, initiativeSkillBasicInfo->damageType, (ATTACK_POS)1, initiativeSkillBasicInfo->formulaParameterId);
		}
#endif
	}

	//-----------------------------------------------------------------------
	void SSkillNetPacketProcesser::onRecvPlaycharacterAffectCollisonMonster(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_MONSTER_DATA* data)
	{
#if 0
		if(data)
		{
			SSceneObject* sceneObject = SWorldManager::getInstance.getSceneObject((REGION_OBJ_TYPE)regionType, regionId, instanceId);
			if(!sceneObject)
			{
				return;
			}

			SPlayerCharacterPtr injectCharacter;
			if(sceneObject->getPlayerCharacter(injectCharacter, data->injectCharacterIndex) == false)
				return;

			if(injectCharacter.isNull())
				return;

			SMonsterPtr affectMonster;
			if(sceneObject->getMonster(affectMonster, data->affectMonsterIndex) == false)
				return;

			if(affectMonster.isNull() || affectMonster->isDead())
				return;


			SkillInfo* skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(data->skillId);
			if(!skillInfo)
			{
				return;
			}

			InitiativeSkillBasicInfo* initiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)skillInfo->skillInfo;
			if(!initiativeSkillBasicInfo)
			{
				return;
			}

		/*	Vec3 dis;
			Flt disLenght = 0;

			if(skillInfo->skillType == SKT_SELFAREA || skillInfo->skillType == SKT_TARGETPOSAREA)
			{
				Vec3 affectPos = (NetVec2)data->affectPos;
				dis = affectPos - injectCharacter->getPos();
				dis.y = 0;
				disLenght = dis.length();

				Flt skillRadius = 0;
				if(skillInfo->skillType == SKT_SELFAREA)
				{
					skillRadius = ((SelfAreaSkillInfo*)initiativeSkillBasicInfo)->skillRadius;
				}
				else
				{
					skillRadius = ((TargetPosAreaSkillInfo*)initiativeSkillBasicInfo)->skillRadius;
				}

				if(skillRadius < disLenght)
				{
					return;
				}
			}
			else
			{
				dis = affectMonster->getPos() - injectCharacter->getPos();
				dis.y = 0;
				disLenght = dis.length();

				if(initiativeSkillBasicInfo->range < disLenght)
				{
					return;
				}
			}*/

			affectMonster->obtainDamage((SCharacter*)injectCharacter, initiativeSkillBasicInfo->attackType, initiativeSkillBasicInfo->damageType, (ATTACK_POS)1, initiativeSkillBasicInfo->formulaParameterId);
		}
#endif
	}

//	-----------------------------------------------------------------------
	void SSkillNetPacketProcesser::onRecvTroopAffectCollisonTroop(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_TROOP_AFFECT_COLLISION_TROOP_DATA* data)
	{
		if(data)
		{
			SSceneObject* sceneObject;// = SWorldManager::getInstance.getSceneObject((REGION_OBJ_TYPE)regionType, regionId, instanceId);
			if(!sceneObject)
			{
				return;
			}

			STroopPtr injectTroop;
			//if(sceneObject->getTroop(injectTroop, data->injectTroopIndex) == false)
			//	return;

			if(injectTroop.isNull())
				return;

			STroopPtr affectTroop;
			//if(sceneObject->getTroop(affectTroop, data->affectTroopIndex) == false)
			//	return;

			if(affectTroop.isNull() || affectTroop->isDead())
				return;
			
			SkillInfo* skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(data->skillId);
			if(!skillInfo)
			{
				return;
			}

			InitiativeSkillBasicInfo* initiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)skillInfo->skillInfo;
			if(!initiativeSkillBasicInfo)
			{
				return;
			}

			affectTroop->obtainDamage((SCharacter*)injectTroop.getPointer(), initiativeSkillBasicInfo->attackType, initiativeSkillBasicInfo->damageType, (ATTACK_POS)1, initiativeSkillBasicInfo->formulaParameterId);
		}
	}

	//-----------------------------------------------------------------------
	void SSkillNetPacketProcesser::onRecvTroopAffectCollisonPlaycharacter(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_TROOP_AFFECT_COLLISION_PLAYERCHARACTER_DATA* data)
	{
		if(data)
		{
			SSceneObject* sceneObject;// = SWorldManager::getInstance.getSceneObject((REGION_OBJ_TYPE)regionType, regionId, instanceId);
			if(!sceneObject)
			{
				return;
			}

			STroopPtr injectTroop;
			//if(sceneObject->getTroop(injectTroop, data->injectTroopIndex) == false)
			//	return;

			if(injectTroop.isNull())
				return;

			SPlayerCharacterPtr affectCharacter;
			//if(sceneObject->getPlayerCharacter(affectCharacter, data->affectCharacterIndex) == false)
			//	return;

			if(affectCharacter.isNull() || affectCharacter->isDead())
				return;

			SkillInfo* skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(data->skillId);
			if(!skillInfo)
			{
				return;
			}

			InitiativeSkillBasicInfo* initiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)skillInfo->skillInfo;
			if(!initiativeSkillBasicInfo)
			{
				return;
			}

			affectCharacter->obtainDamage((SCharacter*)injectTroop.getPointer(), initiativeSkillBasicInfo->attackType, initiativeSkillBasicInfo->damageType, (ATTACK_POS)1, initiativeSkillBasicInfo->formulaParameterId);//xukaichao
		}
	}

//	-----------------------------------------------------------------------
	void SSkillNetPacketProcesser::onRecvTroopAffectCollisonBuilding(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_TROOP_AFFECT_COLLISION_BUILDING_DATA* data)
	{
		if(data)
		{
			SSceneObject* sceneObject;// = SWorldManager::getInstance.getSceneObject((REGION_OBJ_TYPE)regionType, regionId, instanceId);
			if(!sceneObject)
			{
				return;
			}

			STroopPtr injectTroop;
			//if(sceneObject->getTroop(injectTroop, data->injectTroopIndex) == false)
			//	return;

			if(injectTroop.isNull())
				return;

			SBuildingPtr affectBuilding;
			//if(sceneObject->getBuilding(affectBuilding, data->affectBuildingIndex) == false)
			//	return;

			//if(affectBuilding.isNull() || affectBuilding->isDead())
			//	return;
			
			SkillInfo* skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(data->skillId);
			if(!skillInfo)
			{
				return;
			}

			InitiativeSkillBasicInfo* initiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)skillInfo->skillInfo;
			if(!initiativeSkillBasicInfo)
			{
				return;
			}

			affectBuilding->obtainDamage((SCharacter*)injectTroop.getPointer(), initiativeSkillBasicInfo->attackType, initiativeSkillBasicInfo->damageType, (ATTACK_POS)1, initiativeSkillBasicInfo->formulaParameterId);//xukaichao
		}
	}

//	-----------------------------------------------------------------------
	void SSkillNetPacketProcesser::onRecvTroopAffectCollisonMonster(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_TROOP_AFFECT_COLLISION_MONSTER_DATA* data)
	{
		if(data)
		{
			SSceneObject* sceneObject;// = SWorldManager::getInstance.getSceneObject((REGION_OBJ_TYPE)regionType, regionId, instanceId);
			if(!sceneObject)
			{
				return;
			}

			STroopPtr injectTroop;
			//if(sceneObject->getTroop(injectTroop, data->injectTroopIndex) == false)
			//	return;

			if(injectTroop.isNull())
				return;

			SMonsterPtr affectMonster;
			//if(sceneObject->getMonster(affectMonster, data->affectMonsterIndex) == false)
			//	return;

			if(affectMonster.isNull() || affectMonster->isDead())
				return;

			SkillInfo* skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(data->skillId);
			if(!skillInfo)
			{
				return;
			}

			InitiativeSkillBasicInfo* initiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)skillInfo->skillInfo;
			if(!initiativeSkillBasicInfo)
			{
				return;
			}

			affectMonster->obtainDamage((SCharacter*)injectTroop.getPointer(), initiativeSkillBasicInfo->attackType, initiativeSkillBasicInfo->damageType, (ATTACK_POS)1, initiativeSkillBasicInfo->formulaParameterId);//xukaichao
		}
	}

//	-----------------------------------------------------------------------
	void SSkillNetPacketProcesser::onRecvBuildingAffectCollisonTroop(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_TROOP_DATA* data)
	{
		if(data)
		{
			SSceneObject* sceneObject;// = SWorldManager::getInstance.getSceneObject((REGION_OBJ_TYPE)regionType, regionId, instanceId);
			if(!sceneObject)
			{
				return;
			}

			SBuildingPtr injectBuilding;
			//if(sceneObject->getBuilding(injectBuilding, data->injectBuildingIndex) == false)
			//	return;

			if(injectBuilding.isNull())
				return;

			STroopPtr affectTroop;
			//if(sceneObject->getMonster(affectTroop, data->affectTroopIndex) == false)
			//	return;

			if(affectTroop.isNull() || affectTroop->isDead())
				return;
			
			SkillInfo* skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(data->skillId);
			if(!skillInfo)
			{
				return;
			}

			InitiativeSkillBasicInfo* initiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)skillInfo->skillInfo;
			if(!initiativeSkillBasicInfo)
			{
				return;
			}

			affectTroop->obtainDamage((SCharacter*)injectBuilding.getPointer(), initiativeSkillBasicInfo->attackType, initiativeSkillBasicInfo->damageType, (ATTACK_POS)1, initiativeSkillBasicInfo->formulaParameterId);//xukaichao	
		}
	}

	//-----------------------------------------------------------------------
	void SSkillNetPacketProcesser::onRecvBuildingAffectCollisonPlaycharacter(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_PLAYERCHARACTER_DATA* data)
	{
		if(data)
		{
			SSceneObject* sceneObject;// = SWorldManager::getInstance.getSceneObject((REGION_OBJ_TYPE)regionType, regionId, instanceId);
			if(!sceneObject)
			{
				return;
			}

			SBuildingPtr injectBuilding;
			//if(sceneObject->getBuilding(injectBuilding, data->injectBuildingIndex) == false)
			//	return;

			//if(injectBuilding.isNull())
			//	return;

			SPlayerCharacterPtr affectCharacter;
			//if(sceneObject->getPlayerCharacter(affectCharacter, data->affectCharacterIndex) == false)
			//	return;

			if(affectCharacter.isNull() || affectCharacter->isDead())
				return;

			SkillInfo* skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(data->skillId);
			if(!skillInfo)
			{
				return;
			}

			InitiativeSkillBasicInfo* initiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)skillInfo->skillInfo;
			if(!initiativeSkillBasicInfo)
			{
				return;
			}

			affectCharacter->obtainDamage((SCharacter*)injectBuilding.getPointer(), initiativeSkillBasicInfo->attackType, initiativeSkillBasicInfo->damageType, (ATTACK_POS)1, initiativeSkillBasicInfo->formulaParameterId);//xukaichao	
		}

	}

	//-----------------------------------------------------------------------
	void SSkillNetPacketProcesser::onRecvBuildingAffectCollisonBuilding(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_BUILDING_DATA* data)
	{
		if(data)
		{
			SSceneObject* sceneObject;// = SWorldManager::getInstance.getSceneObject((REGION_OBJ_TYPE)regionType, regionId, instanceId);
			if(!sceneObject)
			{
				return;
			}

			SBuildingPtr injectBuilding;
			//if(sceneObject->getBuilding(injectBuilding, data->injectBuildingIndex) == false)
				//return;

			if(injectBuilding.isNull())
				return;

			//SBuildingPtr affectBuilding;
			//if(sceneObject->getBuilding(affectBuilding, data->affectBuildingIndex) == false)
			//	return;

			//if(affectBuilding.isNull() || affectBuilding->isDead())
			//	return;

			SkillInfo* skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(data->skillId);
			if(!skillInfo)
			{
				return;
			}

			InitiativeSkillBasicInfo* initiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)skillInfo->skillInfo;
			if(!initiativeSkillBasicInfo)
			{
				return;
			}

			//affectBuilding->obtainDamage((SCharacter*)injectBuilding, initiativeSkillBasicInfo->attackType, initiativeSkillBasicInfo->damageType, (ATTACK_POS)1, initiativeSkillBasicInfo->formulaParameterId);//xukaichao	
		}
	}

	//-----------------------------------------------------------------------
	void SSkillNetPacketProcesser::onRecvBuildingAffectCollisonMonster(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_MONSTER_DATA* data)
	{
		if(data)
		{
			SSceneObject* sceneObject;// = SWorldManager::getInstance.getSceneObject((REGION_OBJ_TYPE)regionType, regionId, instanceId);
			if(!sceneObject)
			{
				return;
			}

			SBuildingPtr injectBuilding;
			//if(sceneObject->getBuilding(injectBuilding, data->injectBuildingIndex) == false)
			//	return;

			if(injectBuilding.isNull())
				return;

			SMonsterPtr affectMonster;
			//if(sceneObject->getMonster(affectMonster, data->affectMonsterIndex) == false)
			//	return;

			if(affectMonster.isNull() || affectMonster->isDead())
				return;

			SkillInfo* skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(data->skillId);
			if(!skillInfo)
			{
				return;
			}

			InitiativeSkillBasicInfo* initiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)skillInfo->skillInfo;
			if(!initiativeSkillBasicInfo)
			{
				return;
			}

			affectMonster->obtainDamage((SCharacter*)injectBuilding.getPointer(), initiativeSkillBasicInfo->attackType, initiativeSkillBasicInfo->damageType, (ATTACK_POS)1, initiativeSkillBasicInfo->formulaParameterId);//xukaichao	
		}
	}

	////-----------------------------------------------------------------------
	void SSkillNetPacketProcesser::onRecvMonsterAffectCollisonTroop(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_TROOP_DATA* data)
	{
		if(data)
		{
			SSceneObject* sceneObject;// = SWorldManager::getInstance.getSceneObject((REGION_OBJ_TYPE)regionType, regionId, instanceId);
			if(!sceneObject)
			{
				return;
			}

			SMonsterPtr injectMonster;
			//if(sceneObject->getMonster(injectMonster, data->injectMonsterIndex) == false)
			//	return;

			if(injectMonster.isNull())
				return;

			STroopPtr affectTroop;
			//if(sceneObject->getTroop(affectTroop, data->affectTroopIndex) == false)
			//	return;

			if(affectTroop.isNull() || affectTroop->isDead())
				return;

			SkillInfo* skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(data->skillId);
			if(!skillInfo)
			{
				return;
			}

			InitiativeSkillBasicInfo* initiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)skillInfo->skillInfo;
			if(!initiativeSkillBasicInfo)
			{
				return;
			}

			affectTroop->obtainDamage((SCharacter*)injectMonster.getPointer(), initiativeSkillBasicInfo->attackType, initiativeSkillBasicInfo->damageType, (ATTACK_POS)1, initiativeSkillBasicInfo->formulaParameterId);//xukaichao	
		}
	}

	////-----------------------------------------------------------------------
	void SSkillNetPacketProcesser::onRecvMonsterAffectCollisonPlaycharacter(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA* data)
	{
		if(data)
		{
			SSceneObject* sceneObject;// = SWorldManager::getInstance.getSceneObject((REGION_OBJ_TYPE)regionType, regionId, instanceId);
			if(!sceneObject)
			{
				return;
			}

			SMonsterPtr injectMonster;
			//if(sceneObject->getMonster(injectMonster, data->injectMonsterIndex) == false)
			//	return;

			if(injectMonster.isNull())
				return;

			SPlayerCharacterPtr affectCharacter;
			//if(sceneObject->getPlayerCharacter(affectCharacter, data->affectCharacterIndex) == false)
			//	return;

			if(affectCharacter.isNull() || affectCharacter->isDead())
				return;

			SkillInfo* skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(data->skillId);
			if(!skillInfo)
			{
				return;
			}

			InitiativeSkillBasicInfo* initiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)skillInfo->skillInfo;
			if(!initiativeSkillBasicInfo)
			{
				return;
			}

			affectCharacter->obtainDamage((SCharacter*)injectMonster.getPointer(), initiativeSkillBasicInfo->attackType, initiativeSkillBasicInfo->damageType, (ATTACK_POS)1, initiativeSkillBasicInfo->formulaParameterId);//xukaichao	
		}

	}

	//-----------------------------------------------------------------------
	void SSkillNetPacketProcesser::onRecvMonsterAffectCollisonBuilding(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_BUILDING_DATA* data)
	{
		if(data)
		{
			SSceneObject* sceneObject;// = SWorldManager::getInstance.getSceneObject((REGION_OBJ_TYPE)regionType, regionId, instanceId);
			if(!sceneObject)
			{
				return;
			}

			SMonsterPtr injectMonster;
			//if(sceneObject->getMonster(injectMonster, data->injectMonsterIndex) == false)
			//	return;

			if(injectMonster.isNull())
				return;

			SBuildingPtr affectBuilding;
			//if(sceneObject->getBuilding(affectBuilding, data->affectBuildingIndex) == false)
			//	return;

			if(affectBuilding.isNull() || affectBuilding->isDead())
				return;

			SkillInfo* skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(data->skillId);
			if(!skillInfo)
			{
				return;
			}

			InitiativeSkillBasicInfo* initiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)skillInfo->skillInfo;
			if(!initiativeSkillBasicInfo)
			{
				return;
			}

			affectBuilding->obtainDamage((SCharacter*)injectMonster.getPointer(), initiativeSkillBasicInfo->attackType, initiativeSkillBasicInfo->damageType, (ATTACK_POS)1, initiativeSkillBasicInfo->formulaParameterId);//xukaichao	
		}
	}

	//-----------------------------------------------------------------------
	void SSkillNetPacketProcesser::onRecvMonsterAffectCollisonMonster(I32 id, Byte regionType, U64 regionId, I32 instanceId, PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_MONSTER_DATA* data)
	{
		if(data)
		{
			SSceneObject* sceneObject;// = SWorldManager::getInstance.getSceneObject((REGION_OBJ_TYPE)regionType, regionId, instanceId);
			if(!sceneObject)
			{
				return;
			}

			SMonsterPtr injectMonster;
			//if(sceneObject->getMonster(injectMonster, data->injectMonsterIndex) == false)
			//	return;

			if(injectMonster.isNull())
				return;

			SMonsterPtr affectMonster;
			//if(sceneObject->getMonster(affectMonster, data->affectMonsterIndex) == false)
			//	return;

			if(affectMonster.isNull() || affectMonster->isDead())
				return;


			SkillInfo* skillInfo = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(data->skillId);
			if(!skillInfo)
			{
				return;
			}

			InitiativeSkillBasicInfo* initiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)skillInfo->skillInfo;
			if(!initiativeSkillBasicInfo)
			{
				return;
			}

			affectMonster->obtainDamage((SCharacter*)injectMonster.getPointer(), initiativeSkillBasicInfo->attackType, initiativeSkillBasicInfo->damageType, (ATTACK_POS)1, initiativeSkillBasicInfo->formulaParameterId);//xukaichao	
		}
	}

	//-----------------------------------------------------------------------
	void SSkillNetPacketProcesser::onRecvSkillSummonBuilding(I32 id, PT_SKILL_C2M_SUMMON_BUILDING_DATA* data)
	{

	}
	//-----------------------------------------------------------------------
	void SSkillNetPacketProcesser::onRecvPlayerCharacterLearnSkill( I32 id, PT_SKILL_F2M_LEARN_DATA* data )
	{
		//SPlayerCharacter* playerCharacter = SWorldManager::getInstance().getPlayerCharacterFromMemory(data->characterId);
		//if(playerCharacter)
		//{
		//	playerCharacter->getSkillOwnManager()->learnSkill(data->skillId);		
		//}
	}

}
