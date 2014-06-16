/******************************************************************************/
#include "stdafx.h"
#include "ClientNetApplyManager.h"
#include "PackNetPacketProcesser.h"
#include "PlayCharacterNetPacketProcesser.h"
#include "SkillNetPacketProcesser.h"
#include "TroopNetPacketProcesser.h"
#include "MonsterNetPacketProcesser.h"
/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	Bool PackNetPacketProcesser::processFrontServerPacket(I32 id, NetEventRecv *packet)
	{
		if ( packet->getChannel() == GNPC_PACK )
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
				case PT_CHARACTER_S2C_PACK:
					onRecvCharacterPackFromFrontServer(id, (PT_PACK_S2C_CHARACTER_DATA*)data->data);
					break;
			}
			return true;
		}
		return false;
	}

	//-----------------------------------------------------------------------------
	void PackNetPacketProcesser::onRecvCharacterPackFromFrontServer(I32 id, PT_PACK_S2C_CHARACTER_DATA* data)
	{
		Char8* RecvData = data->data;

		for(UINT i = 0; i  <  data->packetNum; ++i)
		{
			PackNetPacketType* paketType = (PackNetPacketType*)RecvData;
			if((*paketType) == PT_PLAYERCHARACTER_MOVE)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_PLAYERCHARACTER_S2C_MOVE_POS_DATA* moveData = (PT_PLAYERCHARACTER_S2C_MOVE_POS_DATA*)RecvData;
				PlayCharacterNetPacketProcesser::getInstance().onRecvPlayerCharacterMove(id, moveData);

				RecvData += sizeof(PT_PLAYERCHARACTER_S2C_MOVE_POS_DATA);
			}
			else if((*paketType) == PT_PLAYERCHARACTER_STOP_MOVE)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_PLAYERCHARACTER_S2C_STOP_MOVE_DATA* stopMoveData = (PT_PLAYERCHARACTER_S2C_STOP_MOVE_DATA*)RecvData;
				PlayCharacterNetPacketProcesser::getInstance().onRecvPlayerCharacterStopMove(id, stopMoveData);

				RecvData += sizeof(PT_PLAYERCHARACTER_S2C_STOP_MOVE_DATA);
			}
			else if((*paketType) == PT_PLAYERCHARACTER_CLANT)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_M2C_PLAYERCHARACTER_CLANT_DATA* clantData = (PT_SKILL_M2C_PLAYERCHARACTER_CLANT_DATA*)RecvData;
				SkillNetPacketProcesser::getInstance().onRecvPlayCharacterClantSkillRequire(clantData);

				RecvData += sizeof(PT_SKILL_M2C_PLAYERCHARACTER_CLANT_DATA);
			}
			else if((*paketType) == PT_PLAYERCHARACTER_INJECT_EMITTER)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_M2C_PLAYERCHARACTER_INJECT_EMITTER_DATA* injectData = (PT_SKILL_M2C_PLAYERCHARACTER_INJECT_EMITTER_DATA*)RecvData;
				SkillNetPacketProcesser::getInstance().onRecvPlayCharacterInjectEmitterSkillRequire(injectData);

				RecvData += sizeof(PT_SKILL_M2C_PLAYERCHARACTER_INJECT_EMITTER_DATA);
			}
			else if((*paketType) == PT_PLAYERCHARACTER_INJECT_POINT)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_M2C_PLAYERCHARACTER_INJECT_POINT_DATA* injectData = (PT_SKILL_M2C_PLAYERCHARACTER_INJECT_POINT_DATA*)RecvData;
				SkillNetPacketProcesser::getInstance().onRecvPlayCharacterInjectPointSkillRequire(injectData);

				RecvData += sizeof(PT_SKILL_M2C_PLAYERCHARACTER_INJECT_POINT_DATA);
			}
			else if((*paketType) == PT_PLAYERCHARACTER_INJECT_OBJECT)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_M2C_PLAYERCHARACTER_INJECT_OBJECT_DATA* injectData = (PT_SKILL_M2C_PLAYERCHARACTER_INJECT_OBJECT_DATA*)RecvData;
				SkillNetPacketProcesser::getInstance().onRecvPlayCharacterInjectObjectSkillRequire(injectData);

				RecvData += sizeof(PT_SKILL_M2C_PLAYERCHARACTER_INJECT_OBJECT_DATA);
			}
			else if((*paketType) == PT_PLAYERCHARACTER_INJECT_END)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_M2C_PLAYERCHARACTER_END_INJECT_DATA* injectEndData = (PT_SKILL_M2C_PLAYERCHARACTER_END_INJECT_DATA*)RecvData;
				SkillNetPacketProcesser::getInstance().onRecvPlayCharacterInjectEndSkillRequire(injectEndData);

				RecvData += sizeof(PT_SKILL_M2C_PLAYERCHARACTER_END_INJECT_DATA);
			}
			else if((*paketType) == PT_MONSTER_MOVE)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_MONSTER_S2C_MOVE_POS_DATA* moveData = (PT_MONSTER_S2C_MOVE_POS_DATA*)RecvData;
				MonsterNetPacketProcesser::getInstance().onRecvMonsterMove(id, moveData);

				RecvData += sizeof(PT_MONSTER_S2C_MOVE_POS_DATA);
			}
			else if((*paketType) == PT_MONSTER_S2C_INSTANT_MOVE_POS)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_MONSTER_S2C_INSTANT_MOVE_POS_DATA* moveData = (PT_MONSTER_S2C_INSTANT_MOVE_POS_DATA*)RecvData;
				MonsterNetPacketProcesser::getInstance().onRecvInstantMonsterMove(id, moveData);

				RecvData += sizeof(PT_MONSTER_S2C_INSTANT_MOVE_POS_DATA);
			}
			else if((*paketType) == PT_MONSTER_STOP_MOVE)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_MONSTER_S2C_STOP_MOVE_DATA* stopMoveData = (PT_MONSTER_S2C_STOP_MOVE_DATA*)RecvData;
				MonsterNetPacketProcesser::getInstance().onRecvMonsterStopMove(id, stopMoveData);

				RecvData += sizeof(PT_MONSTER_S2C_STOP_MOVE_DATA);
			}
			else if((*paketType) == PT_MONSTER_CLANT)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_M2C_MONSTER_CLANT_DATA* clantData = (PT_SKILL_M2C_MONSTER_CLANT_DATA*)RecvData;
				SkillNetPacketProcesser::getInstance().onRecvMonsterClantSkillRequire(clantData);

				RecvData += sizeof(PT_SKILL_M2C_MONSTER_CLANT_DATA);
			}
			else if((*paketType) == PT_MONSTER_INJECT_EMITTER)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_M2C_MONSTER_INJECT_EMITTER_DATA* injectData = (PT_SKILL_M2C_MONSTER_INJECT_EMITTER_DATA*)RecvData;
				SkillNetPacketProcesser::getInstance().onRecvMonsterInjectEmitterSkillRequire(injectData);

				RecvData += sizeof(PT_SKILL_M2C_MONSTER_INJECT_EMITTER_DATA);
			}
			else if((*paketType) == PT_MONSTER_INJECT_POINT)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_M2C_MONSTER_INJECT_POINT_DATA* injectData = (PT_SKILL_M2C_MONSTER_INJECT_POINT_DATA*)RecvData;
				SkillNetPacketProcesser::getInstance().onRecvMonsterInjectPointSkillRequire(injectData);

				RecvData += sizeof(PT_SKILL_M2C_MONSTER_INJECT_POINT_DATA);
			}
			else if((*paketType) == PT_MONSTER_INJECT_OBJECT)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_M2C_MONSTER_INJECT_OBJECT_DATA* injectData = (PT_SKILL_M2C_MONSTER_INJECT_OBJECT_DATA*)RecvData;
				SkillNetPacketProcesser::getInstance().onRecvMonsterInjectObjectSkillRequire(injectData);

				RecvData += sizeof(PT_SKILL_M2C_MONSTER_INJECT_OBJECT_DATA);
			}
			else if((*paketType) == PT_MONSTER_INJECT_END)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_M2C_MONSTER_END_INJECT_DATA* injectEndData = (PT_SKILL_M2C_MONSTER_END_INJECT_DATA*)RecvData;
				SkillNetPacketProcesser::getInstance().onRecvMonsterInjectEndSkillRequire(injectEndData);

				RecvData += sizeof(PT_SKILL_M2C_MONSTER_END_INJECT_DATA);
			}
			else if((*paketType) == PT_TROOP_MOVE)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_TROOP_S2C_MOVE_POS_DATA* moveData = (PT_TROOP_S2C_MOVE_POS_DATA*)RecvData;
				TroopNetPacketProcesser::getInstance().onRecvTroopEntityMove(id, moveData);

				RecvData += sizeof(PT_TROOP_S2C_MOVE_POS_DATA);
			}
			else if((*paketType) == PT_TROOP_STOP_MOVE)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_TROOP_S2C_STOP_MOVE_DATA* stopMoveData = (PT_TROOP_S2C_STOP_MOVE_DATA*)RecvData;
				TroopNetPacketProcesser::getInstance().onRecvTroopEntityStopMove(id, stopMoveData);

				RecvData += sizeof(PT_TROOP_S2C_STOP_MOVE_DATA);
			}
			else if((*paketType) == PT_TROOP_USE_SKILL)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_S2C_TROOP_USE_SKILL_DATA* useSkillData = (PT_SKILL_S2C_TROOP_USE_SKILL_DATA*)RecvData;
				SkillNetPacketProcesser::getInstance().onRecvTroopUseSkillRequire(useSkillData);

				RecvData += sizeof(PT_SKILL_S2C_TROOP_USE_SKILL_DATA);
			}
			else if((*paketType) == PT_TROOP_SOLDIER_MOVE)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_TROOP_SOLDIER_S2C_MOVE_POS_DATA* moveData = (PT_TROOP_SOLDIER_S2C_MOVE_POS_DATA*)RecvData;
				TroopNetPacketProcesser::getInstance().onRecvTroopSoldierMove(id, moveData);

				RecvData += sizeof(PT_TROOP_SOLDIER_S2C_MOVE_POS_DATA);
			}
			else if((*paketType) == PT_TROOP_SOLDIER_STOP_MOVE)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_TROOP_SOLDIER_S2C_STOP_MOVE_DATA* stopMoveData = (PT_TROOP_SOLDIER_S2C_STOP_MOVE_DATA*)RecvData;
				TroopNetPacketProcesser::getInstance().onRecvTroopSoldierStopMove(id, stopMoveData);

				RecvData += sizeof(PT_TROOP_SOLDIER_S2C_STOP_MOVE_DATA);
			}
			else if((*paketType) == PT_TROOP_SOLDIER_INJECT_OBJECT)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_M2C_TROOP_INJECT_OBJECT_DATA* injectData = (PT_SKILL_M2C_TROOP_INJECT_OBJECT_DATA*)RecvData;
				SkillNetPacketProcesser::getInstance().onRecvTroopInjectObjectSkillRequire(injectData);

				RecvData += sizeof(PT_SKILL_M2C_TROOP_INJECT_OBJECT_DATA);
			}
			else if((*paketType) == PT_TROOP_SOLDIER_INJECT_EMITTER)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_M2C_TROOP_INJECT_EMITTER_DATA* injectData = (PT_SKILL_M2C_TROOP_INJECT_EMITTER_DATA*)RecvData;
				SkillNetPacketProcesser::getInstance().onRecvTroopInjectEmitterSkillRequire(injectData);

				RecvData += sizeof(PT_SKILL_M2C_TROOP_INJECT_EMITTER_DATA);
			}
			else if((*paketType) == PT_TROOP_SOLDIER_INJECT_POINT)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_M2C_TROOP_INJECT_POINT_DATA* injectData = (PT_SKILL_M2C_TROOP_INJECT_POINT_DATA*)RecvData;
				SkillNetPacketProcesser::getInstance().onRecvTroopInjectPointSkillRequire(injectData);

				RecvData += sizeof(PT_SKILL_M2C_TROOP_INJECT_POINT_DATA);
			}
		}
	
	}

}