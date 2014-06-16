/******************************************************************************/
#include "stdafx.h"
#include "ClientNetApplyManager.h"
#include "PackNetPacketProcesser.h"
#include "PlayCharacterNetPacketProcesser.h"
#include "SkillNetPacketProcesser.h"
#include "TroopNetPacketProcesser.h"
/******************************************************************************/

namespace MG
{
	//--------------------------	------------------------------------------------
	Bool PackNetPacketProcesser::processFrontServerPacket(CClient* client, NetEventRecv *packet)
	{
		if ( packet->getChannel() == GNPC_PACK )
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
				case PT_CHARACTER_S2C_PACK:
					onRecvCharacterPackFromFrontServer(client, (PT_PACK_S2C_CHARACTER_DATA*)data->data);
					break;
			}
			return true;
		}
		return false;
	}

	//-----------------------------------------------------------------------------
	void PackNetPacketProcesser::onRecvCharacterPackFromFrontServer(CClient* client, PT_PACK_S2C_CHARACTER_DATA* data)
	{
		Char8* RecvData = data->data;

		for(UINT i = 0; i  <  data->packetNum; ++i)
		{
			PackNetPacketType* paketType = (PackNetPacketType*)RecvData;
			if((*paketType) == PT_PLAYERCHARACTER_MOVE)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_PLAYERCHARACTER_S2C_MOVE_POS_DATA* moveData = (PT_PLAYERCHARACTER_S2C_MOVE_POS_DATA*)RecvData;
				PlayCharacterNetPacketProcesser::getInstance().onRecvPlayerCharacterMove(client, moveData);

				RecvData += sizeof(PT_PLAYERCHARACTER_S2C_MOVE_POS_DATA);
			}
			else if((*paketType) == PT_PLAYERCHARACTER_CLANT)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_M2C_PLAYERCHARACTER_CLANT_DATA* clantData = (PT_SKILL_M2C_PLAYERCHARACTER_CLANT_DATA*)RecvData;
				SkillNetPacketProcesser::getInstance().onRecvPlayCharacterClantSkillRequire(client,clantData);

				RecvData += sizeof(PT_SKILL_M2C_PLAYERCHARACTER_CLANT_DATA);
			}
			else if((*paketType) == PT_PLAYERCHARACTER_INJECT_EMITTER)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_M2C_PLAYERCHARACTER_INJECT_EMITTER_DATA* injectData = (PT_SKILL_M2C_PLAYERCHARACTER_INJECT_EMITTER_DATA*)RecvData;
				SkillNetPacketProcesser::getInstance().onRecvPlayCharacterInjectEmitterSkillRequire(client,injectData);

				RecvData += sizeof(PT_SKILL_M2C_PLAYERCHARACTER_INJECT_EMITTER_DATA);
			}
			else if((*paketType) == PT_PLAYERCHARACTER_INJECT_POINT)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_M2C_PLAYERCHARACTER_INJECT_POINT_DATA* injectData = (PT_SKILL_M2C_PLAYERCHARACTER_INJECT_POINT_DATA*)RecvData;
				SkillNetPacketProcesser::getInstance().onRecvPlayCharacterInjectPointSkillRequire(client,injectData);

				RecvData += sizeof(PT_SKILL_M2C_PLAYERCHARACTER_INJECT_POINT_DATA);
			}
			else if((*paketType) == PT_PLAYERCHARACTER_INJECT_OBJECT)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_M2C_PLAYERCHARACTER_INJECT_OBJECT_DATA* injectData = (PT_SKILL_M2C_PLAYERCHARACTER_INJECT_OBJECT_DATA*)RecvData;
				SkillNetPacketProcesser::getInstance().onRecvPlayCharacterInjectObjectSkillRequire(client,injectData);

				RecvData += sizeof(PT_SKILL_M2C_PLAYERCHARACTER_INJECT_OBJECT_DATA);
			}
			else if((*paketType) == PT_PLAYERCHARACTER_INJECT_END)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_SKILL_M2C_PLAYERCHARACTER_END_INJECT_DATA* injectEndData = (PT_SKILL_M2C_PLAYERCHARACTER_END_INJECT_DATA*)RecvData;
				SkillNetPacketProcesser::getInstance().onRecvPlayCharacterInjectEndSkillRequire(client,injectEndData);

				RecvData += sizeof(PT_SKILL_M2C_PLAYERCHARACTER_END_INJECT_DATA);
			}
			else if((*paketType) == PT_TROOP_SOLDIER_MOVE)
			{
				RecvData += sizeof(PackNetPacketType);
				PT_TROOP_SOLDIER_S2C_MOVE_POS_DATA* moveData = (PT_TROOP_SOLDIER_S2C_MOVE_POS_DATA*)RecvData;
				TroopNetPacketProcesser::getInstance().onRecvTroopSoldierMove(client, moveData);

				RecvData += sizeof(PT_TROOP_SOLDIER_S2C_MOVE_POS_DATA);
			}
		}
	
	}

}