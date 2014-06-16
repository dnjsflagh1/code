#include "stdafx.h"
#include "SPackNetPacketProcesser.h"
#include "SPlayerCharacterNetPacketProcesser.h"
#include "SSkillNetPacketProcesser.h"
#include "STroopNetPacketProcesser.h"
#include "SMonsterNetPacketProcesser.h"
/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	SPackNetPacketProcesser::SPackNetPacketProcesser()
	{

	}


	//--------------------------------------------------------------------------
	SPackNetPacketProcesser::~SPackNetPacketProcesser()
	{

	}

	//--------------------------------------------------------------------------
	Bool SPackNetPacketProcesser::processFrontServerPacket(I32 id, NetEventRecv* packet)
	{
		if ( packet->getChannel() == GNPC_PACK )
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_CHARACTER_C2S_PACK:
				onRecvCharacterPackFromFrontServer(id, (PT_PACK_C2S_CHARACTER_DATA*)data->data);
				break;
			}

			return true;
		}

		return false;
	}
	
	//--------------------------------------------------------------------------
	Bool SPackNetPacketProcesser::processMapServerPacket(I32 id, NetEventRecv* packet)
	{
		return false;
	}

	//--------------------------------------------------------------------------
	void SPackNetPacketProcesser::onRecvCharacterPackFromFrontServer(I32 id , PT_PACK_C2S_CHARACTER_DATA* data)
	{
		Char8* RecvData = data->data;

		Byte regionType = data->regionType; 
		U64 regionId = data->regionId; 
		I32 instanceId = data->instanceId;

		for(UINT i = 0; i  <  data->packetNum; ++i)
		{
			PackNetPacketType* paketType = (PackNetPacketType*)RecvData;
			if((*paketType) == PT_PLAYERCHARACTER_MOVE)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_PLAYERCHARACTER_C2S_MOVE_POS_DATA* moveData = (PT_PLAYERCHARACTER_C2S_MOVE_POS_DATA*)RecvData;
				SPlayerCharacterNetPacketProcesser::getInstance().onRecvPlayerCharacterMoveFromFrontServer(id, regionType, regionId, instanceId, moveData);

				RecvData += sizeof(PT_PLAYERCHARACTER_C2S_MOVE_POS_DATA);
			}
			else if((*paketType) == PT_PLAYERCHARACTER_STOP_MOVE)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_PLAYERCHARACTER_C2S_STOP_MOVE_DATA* moveData = (PT_PLAYERCHARACTER_C2S_STOP_MOVE_DATA*)RecvData;
				SPlayerCharacterNetPacketProcesser::getInstance().onRecvPlayerCharacterStopMoveFromFrontServer(id, regionType, regionId, instanceId, moveData);

				RecvData += sizeof(PT_PLAYERCHARACTER_C2S_STOP_MOVE_DATA);
			}
			else if((*paketType) == PT_PLAYERCHARACTER_CLANT)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_C2M_PLAYERCHARACTER_CLANT_DATA* clantData = (PT_SKILL_C2M_PLAYERCHARACTER_CLANT_DATA*)RecvData;
				SSkillNetPacketProcesser::getInstance().onRecvPlayCharacterClantSkillFromFrontServer(id, regionType, regionId, instanceId, clantData);

				RecvData += sizeof(PT_SKILL_C2M_PLAYERCHARACTER_CLANT_DATA);
			}
			else if((*paketType) == PT_PLAYERCHARACTER_INJECT_EMITTER)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_C2M_PLAYERCHARACTER_INJECT_EMITTER_DATA* injectData = (PT_SKILL_C2M_PLAYERCHARACTER_INJECT_EMITTER_DATA*)RecvData;
				SSkillNetPacketProcesser::getInstance().onRecvPlayCharacterInjectEmitterSkill(id, regionType, regionId, instanceId, injectData);

				RecvData += sizeof(PT_SKILL_C2M_PLAYERCHARACTER_INJECT_EMITTER_DATA);
			}
			else if((*paketType) == PT_PLAYERCHARACTER_INJECT_POINT)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_C2M_PLAYERCHARACTER_INJECT_POINT_DATA* injectData = (PT_SKILL_C2M_PLAYERCHARACTER_INJECT_POINT_DATA*)RecvData;
				SSkillNetPacketProcesser::getInstance().onRecvPlayCharacterInjectPointSkill(id, regionType, regionId, instanceId, injectData);

				RecvData += sizeof(PT_SKILL_C2M_PLAYERCHARACTER_INJECT_POINT_DATA);
			}
			else if((*paketType) == PT_PLAYERCHARACTER_INJECT_OBJECT)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_C2M_PLAYERCHARACTER_INJECT_OBJECT_DATA* injectData = (PT_SKILL_C2M_PLAYERCHARACTER_INJECT_OBJECT_DATA*)RecvData;
				SSkillNetPacketProcesser::getInstance().onRecvPlayCharacterInjectObjectSkill(id, regionType, regionId, instanceId, injectData);

				RecvData += sizeof(PT_SKILL_C2M_PLAYERCHARACTER_INJECT_OBJECT_DATA);
			}
			else if((*paketType) == PT_PLAYERCHARACTER_INJECT_END)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_C2M_PLAYERCHARACTER_END_INJECT_DATA* injectEndData = (PT_SKILL_C2M_PLAYERCHARACTER_END_INJECT_DATA*)RecvData;
				SSkillNetPacketProcesser::getInstance().onRecvPlayCharacterInjectEndSkill(id, regionType, regionId, instanceId, injectEndData);

				RecvData += sizeof(PT_SKILL_C2M_PLAYERCHARACTER_END_INJECT_DATA);
			}
			else if((*paketType) == PT_TROOP_MOVE)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_TROOP_C2S_MOVE_POS_DATA* moveData = (PT_TROOP_C2S_MOVE_POS_DATA*)RecvData;
				STroopNetPacketProcesser::getInstance().onRecvTroopMove(id, regionType, regionId, instanceId, moveData);

				RecvData += sizeof(PT_TROOP_C2S_MOVE_POS_DATA);
			}
			else if((*paketType) == PT_TROOP_STOP_MOVE)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_TROOP_C2S_STOP_MOVE_DATA* stopMoveData = (PT_TROOP_C2S_STOP_MOVE_DATA*)RecvData;
				STroopNetPacketProcesser::getInstance().onRecvTroopStopMove(id, regionType, regionId, instanceId, stopMoveData);
				//SPlayerCharacterNetPacketProcesser::getInstance().onRecvPlayerCharacterStopMoveFromFrontServer(id, moveData);

				RecvData += sizeof(PT_TROOP_C2S_STOP_MOVE_DATA);
			}
			else if((*paketType) == PT_TROOP_USE_SKILL)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_C2S_TROOP_USE_SKILL_DATA* useSkillData = (PT_SKILL_C2S_TROOP_USE_SKILL_DATA*)RecvData;
				//SPlayerCharacterNetPacketProcesser::getInstance().onRecvPlayerCharacterStopMoveFromFrontServer(id, moveData);
				SSkillNetPacketProcesser::getInstance().onRecvTroopUseSkill(id, regionType, regionId, instanceId, useSkillData);

				RecvData += sizeof(PT_SKILL_C2S_TROOP_USE_SKILL_DATA);
			}
			else if((*paketType) == PT_TROOP_SOLDIER_MOVE)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_TROOP_SOLDIER_C2S_MOVE_POS_DATA* moveData = (PT_TROOP_SOLDIER_C2S_MOVE_POS_DATA*)RecvData;
				STroopNetPacketProcesser::getInstance().onRecvTroopSoldierMove(id, regionType, regionId, instanceId, moveData);

				RecvData += sizeof(PT_TROOP_SOLDIER_C2S_MOVE_POS_DATA);
			}
			else if((*paketType) == PT_TROOP_SOLDIER_STOP_MOVE)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_TROOP_SOLDIER_C2S_STOP_MOVE_DATA* moveData = (PT_TROOP_SOLDIER_C2S_STOP_MOVE_DATA*)RecvData;
				STroopNetPacketProcesser::getInstance().onRecvTroopSoldierStopMove(id, regionType, regionId, instanceId, moveData);

				RecvData += sizeof(PT_TROOP_SOLDIER_C2S_STOP_MOVE_DATA);
			}
			else if((*paketType) == PT_TROOP_SOLDIER_CLANT)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_C2M_TROOP_CLANT_DATA* clantData = (PT_SKILL_C2M_TROOP_CLANT_DATA*)RecvData;
				SSkillNetPacketProcesser::getInstance().onRecvTroopClantSkillFromFrontServer(id, regionType, regionId, instanceId, clantData);

				RecvData += sizeof(PT_SKILL_C2M_TROOP_CLANT_DATA);
			}
			else if((*paketType) == PT_TROOP_SOLDIER_INJECT_END)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_C2M_TROOP_END_INJECT_DATA* endInjectData = (PT_SKILL_C2M_TROOP_END_INJECT_DATA*)RecvData;
				//SSkillNetPacketProcesser::getInstance().onRecvTroop
				RecvData += sizeof(PT_SKILL_C2M_TROOP_END_INJECT_DATA);
			}
			else if((*paketType) == PT_TROOP_SOLDIER_INJECT_OBJECT)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_C2M_TROOP_INJECT_OBJECT_DATA* injectData = (PT_SKILL_C2M_TROOP_INJECT_OBJECT_DATA*)RecvData;
				SSkillNetPacketProcesser::getInstance().onRecvTroopInjectObjectSkill(id, regionType, regionId, instanceId, injectData);

				RecvData += sizeof(PT_SKILL_C2M_TROOP_INJECT_OBJECT_DATA);
			}
			else if((*paketType) == PT_TROOP_SOLDIER_INJECT_EMITTER)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_C2M_TROOP_INJECT_EMITTER_DATA* injectData = (PT_SKILL_C2M_TROOP_INJECT_EMITTER_DATA*)RecvData;
				SSkillNetPacketProcesser::getInstance().onRecvTroopInjectEmitterSkill(id, regionType, regionId, instanceId, injectData);

				RecvData += sizeof(PT_SKILL_C2M_TROOP_INJECT_EMITTER_DATA);
			}
			else if((*paketType) == PT_TROOP_SOLDIER_INJECT_POINT)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_C2M_TROOP_INJECT_POINT_DATA* injectData = (PT_SKILL_C2M_TROOP_INJECT_POINT_DATA*)RecvData;
				SSkillNetPacketProcesser::getInstance().onRecvTroopInjectPointSkill(id, regionType, regionId, instanceId, injectData);

				RecvData += sizeof(PT_SKILL_C2M_TROOP_INJECT_POINT_DATA);
			}
			else if ((*paketType) == PT_PLAYERCHARACTER_AFFECT_COLLISION_PLAYERCHARACTER)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA* injectData = (PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA*)RecvData;
				SSkillNetPacketProcesser::getInstance().onRecvPlaycharacterAffectCollisonPlaycharacter(id, regionType, regionId, instanceId, injectData);

				RecvData += sizeof(PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA);
			}
			else if ((*paketType) == PT_PLAYERCHARACTER_AFFECT_COLLISION_TROOP)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_TROOP_DATA* injectData = (PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_TROOP_DATA*)RecvData;
				SSkillNetPacketProcesser::getInstance().onRecvPlaycharacterAffectCollisonTroop(id, regionType, regionId, instanceId, injectData);

				RecvData += sizeof(PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_TROOP_DATA);
			}
			else if ((*paketType) == PT_PLAYERCHARACTER_AFFECT_COLLISION_BUILDING)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_BUILDING_DATA* injectData = (PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_BUILDING_DATA*)RecvData;
				SSkillNetPacketProcesser::getInstance().onRecvPlaycharacterAffectCollisonBuilding(id, regionType, regionId, instanceId, injectData);

				RecvData += sizeof(PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_BUILDING_DATA);
			}
			else if ((*paketType) == PT_PLAYERCHARACTER_AFFECT_COLLISION_MONSTER)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_MONSTER_DATA* injectData = (PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_MONSTER_DATA*)RecvData;
				SSkillNetPacketProcesser::getInstance().onRecvPlaycharacterAffectCollisonMonster(id, regionType, regionId, instanceId, injectData);

				RecvData += sizeof(PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_MONSTER_DATA);
			}
			else if ((*paketType) == PT_TROOP_AFFECT_COLLISION_PLAYERCHARACTER)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_C2M_TROOP_AFFECT_COLLISION_PLAYERCHARACTER_DATA* injectData = (PT_SKILL_C2M_TROOP_AFFECT_COLLISION_PLAYERCHARACTER_DATA*)RecvData;
				SSkillNetPacketProcesser::getInstance().onRecvTroopAffectCollisonPlaycharacter(id, regionType, regionId, instanceId, injectData);

				RecvData += sizeof(PT_SKILL_C2M_TROOP_AFFECT_COLLISION_PLAYERCHARACTER_DATA);
			}
			else if ((*paketType) == PT_TROOP_AFFECT_COLLISION_TROOP)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_C2M_TROOP_AFFECT_COLLISION_TROOP_DATA* injectData = (PT_SKILL_C2M_TROOP_AFFECT_COLLISION_TROOP_DATA*)RecvData;
				SSkillNetPacketProcesser::getInstance().onRecvTroopAffectCollisonTroop(id, regionType, regionId, instanceId, injectData);

				RecvData += sizeof(PT_SKILL_C2M_TROOP_AFFECT_COLLISION_TROOP_DATA);
			}
			else if ((*paketType) == PT_TROOP_AFFECT_COLLISION_BUILDING)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_C2M_TROOP_AFFECT_COLLISION_BUILDING_DATA* injectData = (PT_SKILL_C2M_TROOP_AFFECT_COLLISION_BUILDING_DATA*)RecvData;
				SSkillNetPacketProcesser::getInstance().onRecvTroopAffectCollisonBuilding(id, regionType, regionId, instanceId, injectData);

				RecvData += sizeof(PT_SKILL_C2M_TROOP_AFFECT_COLLISION_BUILDING_DATA);
			}
			else if ((*paketType) == PT_TROOP_AFFECT_COLLISION_MONSTER)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_C2M_TROOP_AFFECT_COLLISION_MONSTER_DATA* injectData = (PT_SKILL_C2M_TROOP_AFFECT_COLLISION_MONSTER_DATA*)RecvData;
				SSkillNetPacketProcesser::getInstance().onRecvTroopAffectCollisonMonster(id, regionType, regionId, instanceId, injectData);

				RecvData += sizeof(PT_SKILL_C2M_TROOP_AFFECT_COLLISION_MONSTER_DATA);
			}
			else if ((*paketType) == PT_BUILDING_AFFECT_COLLISION_PLAYERCHARACTER)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_PLAYERCHARACTER_DATA* injectData = (PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_PLAYERCHARACTER_DATA*)RecvData;
				SSkillNetPacketProcesser::getInstance().onRecvBuildingAffectCollisonPlaycharacter(id, regionType, regionId, instanceId, injectData);

				RecvData += sizeof(PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_PLAYERCHARACTER_DATA);
			}
			else if ((*paketType) == PT_BUILDING_AFFECT_COLLISION_TROOP)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_TROOP_DATA* injectData = (PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_TROOP_DATA*)RecvData;
				SSkillNetPacketProcesser::getInstance().onRecvBuildingAffectCollisonTroop(id, regionType, regionId, instanceId, injectData);

				RecvData += sizeof(PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_TROOP_DATA);
			}
			else if ((*paketType) == PT_BUILDING_AFFECT_COLLISION_BUILDING)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_BUILDING_DATA* injectData = (PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_BUILDING_DATA*)RecvData;
				SSkillNetPacketProcesser::getInstance().onRecvBuildingAffectCollisonBuilding(id, regionType, regionId, instanceId, injectData);

				RecvData += sizeof(PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_BUILDING_DATA);
			}
			else if ((*paketType) == PT_BUILDING_AFFECT_COLLISION_MONSTER)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_MONSTER_DATA* injectData = (PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_MONSTER_DATA*)RecvData;
				SSkillNetPacketProcesser::getInstance().onRecvBuildingAffectCollisonMonster(id, regionType, regionId, instanceId, injectData);

				RecvData += sizeof(PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_MONSTER_DATA);
			}
			else if ((*paketType) == PT_MONSTER_AFFECT_COLLISION_PLAYERCHARACTER)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA* injectData = (PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA*)RecvData;
				SSkillNetPacketProcesser::getInstance().onRecvMonsterAffectCollisonPlaycharacter(id, regionType, regionId, instanceId, injectData);

				RecvData += sizeof(PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA);
			}
			else if ((*paketType) == PT_MONSTER_AFFECT_COLLISION_TROOP)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_TROOP_DATA* injectData = (PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_TROOP_DATA*)RecvData;
				SSkillNetPacketProcesser::getInstance().onRecvMonsterAffectCollisonTroop(id, regionType, regionId, instanceId, injectData);

				RecvData += sizeof(PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_TROOP_DATA);
			}
			else if ((*paketType) == PT_MONSTER_AFFECT_COLLISION_BUILDING)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_BUILDING_DATA* injectData = (PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_BUILDING_DATA*)RecvData;
				SSkillNetPacketProcesser::getInstance().onRecvMonsterAffectCollisonBuilding(id, regionType, regionId, instanceId, injectData);

				RecvData += sizeof(PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_BUILDING_DATA);
			}
			else if ((*paketType) == PT_MONSTER_AFFECT_COLLISION_MONSTER)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_MONSTER_DATA* injectData = (PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_MONSTER_DATA*)RecvData;
				SSkillNetPacketProcesser::getInstance().onRecvMonsterAffectCollisonMonster(id, regionType, regionId, instanceId, injectData);

				RecvData += sizeof(PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_MONSTER_DATA);
			}
		}
	}

}