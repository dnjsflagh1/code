/******************************************************************************/
#include "stdafx.h"
#include "ClientNetApplyManager.h"
#include "SkillNetPacketProcesser.h"
#include "CPlayer.h"
#include "NetPacketPackManager.h"
#include "SkillBaseInfo.h"
#include "CClientNew.h"
#include "CSkillOwnManager.h"
#include "MGRandom.h"
/******************************************************************************/
namespace MG
{
#define  SKILL_ID 1003000101
    //-----------------------------------------------------------------------------
    SkillNetPacketProcesser::SkillNetPacketProcesser()
    {

    }

    //-----------------------------------------------------------------------------
    SkillNetPacketProcesser::~SkillNetPacketProcesser()
    {

    }

    //-----------------------------------------------------------------------------
    Bool SkillNetPacketProcesser::processFrontServerPacket(CClient* client,NetEventRecv* packet)
    {
		if ( packet->getChannel() == GNPC_SKILL )
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_SKILL_M2C_PLAYERCHARACTER_CLANT:
				onRecvPlayCharacterClantSkillRequire( client,(PT_SKILL_M2C_PLAYERCHARACTER_CLANT_DATA*)data->data );
				break;
			case PT_SKILL_M2C_PLAYERCHARACTER_INJECT_EMITTER:
				onRecvPlayCharacterInjectEmitterSkillRequire( client,(PT_SKILL_M2C_PLAYERCHARACTER_INJECT_EMITTER_DATA*)data->data );
				break;
			case PT_SKILL_M2C_PLAYERCHARACTER_INJECT_POINT:
				onRecvPlayCharacterInjectPointSkillRequire( client,(PT_SKILL_M2C_PLAYERCHARACTER_INJECT_POINT_DATA*)data->data );
				break;
			case PT_SKILL_M2C_PLAYERCHARACTER_INJECT_OBJECT:
				onRecvPlayCharacterInjectObjectSkillRequire( client,(PT_SKILL_M2C_PLAYERCHARACTER_INJECT_OBJECT_DATA*)data->data );
				break;
			case PT_SKILL_M2C_TROOP_CLANT:
				onRecvTroopClantSkillRequire( client,(PT_SKILL_M2C_TROOP_CLANT_DATA*)data->data );
				break;
			case PT_SKILL_M2C_TROOP_INJECT_EMITTER:
				//onRecvTroopInjectEmitterSkillRequire( client,(PT_SKILL_M2C_TROOP_INJECT_EMITTER_DATA*)data->data );
				break;
			case PT_SKILL_M2C_TROOP_INJECT_POINT:
				//onRecvTroopInjectPointSkillRequire( client,(PT_SKILL_M2C_TROOP_INJECT_POINT_DATA*)data->data );
				break;
			case PT_SKILL_M2C_TROOP_INJECT_OBJECT:
				//onRecvTroopInjectObjectSkillRequire( client,(PT_SKILL_M2C_TROOP_INJECT_OBJECT_DATA*)data->data );
				break;
			case PT_SKILL_M2C_BUILDING_CLANT:
				onRecvBuildingClantSkillRequire( client,(PT_SKILL_M2C_BUILDING_CLANT_DATA*)data->data );
				break;
			case PT_SKILL_M2C_BUILDING_INJECT_EMITTER:
				onRecvBuildingInjectInstantSkillRequire( client,(PT_SKILL_M2C_BUILDING_INJECT_EMITTER_DATA*)data->data );
				break;
			case PT_SKILL_M2C_BUILDING_INJECT_POINT:
				onRecvBuildingInjectPointSkillRequire( client,(PT_SKILL_M2C_BUILDING_INJECT_POINT_DATA*)data->data );
				break;
			case PT_SKILL_M2C_BUILDING_INJECT_OBJECT:
				onRecvBuildingInjectObjectSkillRequire( client,(PT_SKILL_M2C_BUILDING_INJECT_OBJECT_DATA*)data->data );
				break;
			}
			return true;
		}

        return false;
    }

    //-----------------------------------------------------------------------------
    //void SkillNetPacketProcesser::sendLearnSkillRequestPacket(CSkillManagerForCharacter* skillMgr, IdType skillid)
    //{

    //}
	void SkillNetPacketProcesser::sendSkillPlayerCharacterCollisionAffectPlayerCharacterPacket(CClient* client)
	{
		// ×ª»»Âß¼­°ü
		PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA sendData;
		CPlayerCharacter* character = client->getPlayerObj()->getActiveClan()->getMainGenreal();
		// Ìî³äÂß¼­°ü
		sendData.injectCharacterId = character->getID();
		sendData.affectCharacterId = character->getID();
		sendData.affectTotal = 1;
		sendData.skillId = character->getCurrSkillId();

		client->getPackManager()->addPacketToBuff(PT_PLAYERCHARACTER_AFFECT_COLLISION_PLAYERCHARACTER, GOT_PLAYERCHARACTER, (Char8*)&sendData, character->getID());

	}
    //-----------------------------------------------------------------------------
    void SkillNetPacketProcesser::sendPlayCharacterClantSkillRequestPacket(CClient* client,CSkillObject* skillObject)
    {
        //Character* character = skillObject->getOwner();
        //if(character && character->getIsRecvSkill())
        //{
        //    // »ñµÃÒ»¸ö·¢ËÍ¡¾·þÎñ¶Ë¡¿»º´æ
        //    GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        //    // ×ª»»³É±ê×¼°ü¸ñÊ½
        //    GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        //    if ( packet )
        //    {
        //        // ÉèÖÃ±êÇ©
        //        packet->channel = GNPC_SKILL;
        //        packet->type    = PT_SKILL_C2F_PLAYERCHARACTER_CLANT;

        //        // ×ª»»Âß¼­°ü
        //        PT_SKILL_C2F_PLAYERCHARACTER_CLANT_DATA* sendData = (PT_SKILL_C2F_PLAYERCHARACTER_CLANT_DATA*)(packet->data);
        //        if ( sendData )
        //        {
        //            // Ìî³äÂß¼­°ü
        //            sendData->characterId = character->getID();
        //            sendData->skillId = skillObject->getBaseInfo()->id;
        //            sendData->characterPos.x = character->getPos().x;
        //            sendData->characterPos.z = character->getPos().z;
        //            sendData->characterDir.x = character->getDir().x;
        //            sendData->characterDir.z = character->getDir().z;

        //            // ·¢ËÍÊý¾Ý
        //            ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
        //                GameNetPacketData_INFO::headSize + PT_SKILL_C2F_PLAYERCHARACTER_CLANT_DATA_INFO::dataSize );
        //            
        //            character->setIsRecvSkill(false);
        //        }
        //    }

            
        //}

    }

	 //-----------------------------------------------------------------------------
	 void SkillNetPacketProcesser::sendPlayCharacterClantSkillRequestPacketToPackBuffer(CClient* client)
	 {
		/* CPlayerCharacter* character = client->getPlayerObj()->getActiveClan()->getMainGenreal();
		 if(character)
		 {         
			 CSkillOwnManager* skillOwer = character->getSkillOwnManager();
			 UInt skillId = SKILL_ID;
			 if (skillOwer)
			 {
				 if (skillOwer->getOwnSkillNum() == 0)
				 {
					 DYNAMIC_ASSERT(false);
					 return;
				 }
				 else if (skillOwer->getOwnSkillNum() == 1)
				 {

					 SkillData* skillData = skillOwer->getSkillDataByIndex(0);	
					 if (!skillData)
					 {
						 DYNAMIC_ASSERT(false);
						 return;
					 }
					 skillId = skillData->skillId;
				 }
				 else
				 {
					 UInt index = MGRandom::getInstance().rand_ab_One(0,skillOwer->getOwnSkillNum() - 1);
					 SkillData* skillData = skillOwer->getSkillDataByIndex(index);	
					 if (!skillData)
					 {
						 DYNAMIC_ASSERT(false);
						 return;
					 }
					 skillId = skillData->skillId;
				 }

				character->setCurrSkillId(skillId);

				 PT_SKILL_C2M_PLAYERCHARACTER_CLANT_DATA sendData;
				 // Ìî³äÂß¼­°ü
				 sendData.characterId = character->getID();
				 sendData.skillId = skillId;
				 sendData.characterPos.x = character->getCharacterData()->mPos.x;
				 sendData.characterPos.z = character->getCharacterData()->mPos.z;
				 sendData.characterDir.x = character->getCharacterData()->mDir.x;
				 sendData.characterDir.z = character->getCharacterData()->mDir.z;
				 sendData.targetType = character->getType();
				 sendData.targetId = character->getID();
				 sendData.targetIndex = character->getID();
				 sendData.targetPos.x =  character->getCharacterData()->mPos.x;
				 sendData.targetPos.z = character->getCharacterData()->mPos.z;

				client->getPackManager()->addPacketToBuff(PT_PLAYERCHARACTER_CLANT, GOT_PLAYERCHARACTER, (Char8*)&sendData, sendData.characterId);
			}
		 }
		 */
	 }
	 //-----------------------------------------------------------------------------
	 void SkillNetPacketProcesser::sendPlayCharacterInjectSkillRequestPacketToPackBuffer(CClient* client)
	 {
		 CPlayerCharacter* playerCharacter = client->getPlayerObj()->getActiveClan()->getMainGenreal();
		 if(!playerCharacter)
		 {
			return;
		 }

		PT_SKILL_C2M_PLAYERCHARACTER_INJECT_OBJECT_DATA sendData;

		sendData.skillId = playerCharacter->getCurrSkillId();
		sendData.characterId = client->getPlayerObj()->getActiveClan()->getMainGenreal()->getID();
		sendData.instanceUid = client->getPlayerObj()->getInstanceUid();
		sendData.objectIndex = 0;
		sendData.objectId = client->getPlayerObj()->getActiveClan()->getMainGenreal()->getID();
		sendData.objectType = client->getPlayerObj()->getActiveClan()->getMainGenreal()->getType();

		client->getPackManager()->addPacketToBuff(PT_PLAYERCHARACTER_INJECT_OBJECT, GOT_PLAYERCHARACTER, (Char8*)&sendData, client->getPlayerObj()->getActiveClan()->getMainGenreal()->getID());

	 }

    //-----------------------------------------------------------------------------
    void SkillNetPacketProcesser::sendPlayCharacterInjectSkillRequestPacket(CClient* client,CSkillObject* skillObject)
    {
		
    }

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendPlayCharacterEndInjectSkillPacket(CClient* client,CSkillObject* skillObject)
	{
		
	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendPlayCharacterEndInjectSkillPacketToPackBuffer(CClient* client)
	{
		PT_SKILL_C2M_PLAYERCHARACTER_END_INJECT_DATA sendData;
		// Ìî³äÂß¼­°ü
		CPlayerCharacter* character = client->getPlayerObj()->getActiveClan()->getMainGenreal();
		if (!character)
		{
			DYNAMIC_ASSERT(false);
			return;
		}
		sendData.characterId = character->getID();
		sendData.skillId = character->getCurrSkillId();

		client->getPackManager()->addPacketToBuff(PT_PLAYERCHARACTER_INJECT_END, GOT_PLAYERCHARACTER, (Char8*)&sendData, sendData.characterId);
	}

	//-----------------------------------------------------------------------------
//	void SkillNetPacketProcesser::sendMonsterClantSkillRequestPacketToPackBuffer(CSkillObject* skillObject)
//	{
// 		CMonsterEntity* monsterEntity = CSceneManager::getInstance().getMonsterEntity(skillObject->getOwnerID());
// 		if(!monsterEntity)
// 		{
// 			return;
// 		}
// 
// 		PT_SKILL_C2M_MONSTER_CLANT_DATA sendData;
// 		// Ìî³äÂß¼­°ü
// 		sendData.playerId = CPlayer::getInstance().getAccountID();
// 		sendData.monsterId = monsterEntity->getID();
// 		sendData.skillId = skillObject->getSkillInfo()->skillId;
// 		sendData.characterPos.x = monsterEntity->getPos().x;
// 		sendData.characterPos.z = monsterEntity->getPos().z;
// 		sendData.characterDir.x = monsterEntity->getDir().x;
// 		sendData.characterDir.z = monsterEntity->getDir().z;
// 		sendData.targetType = skillObject->getTargetObjectType();
// 		sendData.targetId = skillObject->getTargetObjectID();
// 		sendData.targetIndex = skillObject->getTargetObjectIndex();
// 		sendData.targetPos.x = skillObject->getTargetPosition().x;
// 		sendData.targetPos.z = skillObject->getTargetPosition().z;
// 
// 		NetPacketPackManager::getInstance().addPacketToBuff(PT_MONSTER_CLANT, GOT_MONSTER, (Char8*)&sendData, monsterEntity->getID());
//	}

	//-----------------------------------------------------------------------------
// 	void SkillNetPacketProcesser::sendMonsterInjectSkillRequestPacketToPackBuffer(CSkillObject* skillObject)
// 	{
// 		CMonsterEntity* monsterEntity = CSceneManager::getInstance().getMonsterEntity(skillObject->getOwnerID());
// 		if(!monsterEntity)
// 		{
// 			return;
// 		}
// 
// 		if(skillObject->getTargetObjectID() != 0)
// 		{
// 			CCharacterSceneEntity* targetCharacterEntity = CSceneManager::getInstance().getCharacterSceneEntity(skillObject->getTargetObjectType(), skillObject->getTargetObjectID(), skillObject->getTargetObjectIndex());
// 			if(!targetCharacterEntity)
// 			{
// 				return;
// 			}
// 		}
// 
// 
// 		switch(skillObject->getSkillInfo()->skillType)
// 		{
// 		case SKT_SHORTRANGEGENERAL:
// 		case SKT_LONGRANGEGENERAL:
// 			{
// 				PT_SKILL_C2M_MONSTER_INJECT_OBJECT_DATA sendData;
// 				sendData.skillId = skillObject->getSkillInfo()->skillId;
// 				sendData.playerId = CPlayer::getInstance().getAccountID();
// 				sendData.monsterId = monsterEntity->getID();
// 				sendData.regionId = CPlayer::getInstance().getActiveClan()->getData()->regionID;
// 				sendData.instanceUid = CPlayer::getInstance().getInstanceUid();
// 				sendData.objectIndex = skillObject->getTargetObjectIndex();
// 				sendData.objectId = skillObject->getTargetObjectID();
// 				sendData.objectType = skillObject->getTargetObjectType();
// 
// 				NetPacketPackManager::getInstance().addPacketToBuff(PT_MONSTER_INJECT_OBJECT, GOT_MONSTER, (Char8*)&sendData, monsterEntity->getID());
// 			}
// 			break;
// 		case SKT_SINGLEEMITTER:
// 			{
// 				Vec3 dir = skillObject->getTargetPosition() - monsterEntity->getPos();
// 				dir.y = 0;
// 				dir.normalise();
// 
// 				PT_SKILL_C2M_MONSTER_INJECT_EMITTER_DATA sendData;
// 				sendData.playerId = CPlayer::getInstance().getAccountID();
// 				sendData.skillId = skillObject->getSkillInfo()->skillId;
// 				sendData.monsterId = monsterEntity->getID();
// 				sendData.injectDir.x = dir.x; 
// 				sendData.injectDir.z = dir.z; 
// 
// 				NetPacketPackManager::getInstance().addPacketToBuff(PT_MONSTER_INJECT_EMITTER, GOT_MONSTER, (Char8*)&sendData, monsterEntity->getID());
// 			}
// 			break;
// 		case SKT_SELFAREA:
// 		case SKT_TARGETPOSAREA:
// 			{
// 				PT_SKILL_C2M_MONSTER_INJECT_POINT_DATA sendData;
// 				sendData.playerId = CPlayer::getInstance().getAccountID();
// 				sendData.skillId = skillObject->getSkillInfo()->skillId;
// 				sendData.monsterId = monsterEntity->getID();
// 				sendData.targetPos.x = skillObject->getTargetPosition().x;
// 				sendData.targetPos.z = skillObject->getTargetPosition().z;
// 
// 				NetPacketPackManager::getInstance().addPacketToBuff(PT_MONSTER_INJECT_POINT, GOT_MONSTER, (Char8*)&sendData, monsterEntity->getID());
// 			}
// 			break;
// 		}
// 
// 	}

	//-----------------------------------------------------------------------------
// 	void SkillNetPacketProcesser::sendMonsterEndInjectSkillPacketToPackBuffer(CSkillObject* skillObject)
// 	{
// 		CMonsterEntity* monsterEntity = CSceneManager::getInstance().getMonsterEntity(skillObject->getOwnerID());
// 		if(!monsterEntity)
// 		{         
// 			return;
// 		}
// 
// 		PT_SKILL_C2M_MONSTER_END_INJECT_DATA sendData;
// 		// Ìî³äÂß¼­°ü
// 		sendData.playerId = CPlayer::getInstance().getAccountID();
// 		sendData.monsterId = monsterEntity->getID();
// 		sendData.skillId = skillObject->getSkillInfo()->skillId;
// 
// 		NetPacketPackManager::getInstance().addPacketToBuff(PT_MONSTER_INJECT_END, GOT_MONSTER, (Char8*)&sendData, monsterEntity->getID());
// 	}
// 
// 	//-----------------------------------------------------------------------------
// 	void SkillNetPacketProcesser::sendSkillPlayerCharacterCollisionAffectPlayerCharacterPacket(IdType injectCharacterId, IdType affectCharacterId, UInt affectTotal, IdType skillId)
// 	{
//             // ×ª»»Âß¼­°ü
//             PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA sendData;
//             // Ìî³äÂß¼­°ü
//             sendData.injectCharacterId = injectCharacterId;
//             sendData.affectCharacterId = affectCharacterId;
//             sendData.affectTotal = affectTotal;
//             sendData.skillId= skillId;
// 
// 			NetPacketPackManager::getInstance().addPacketToBuff(PT_PLAYERCHARACTER_AFFECT_COLLISION_PLAYERCHARACTER, GOT_PLAYERCHARACTER, (Char8*)&sendData, injectCharacterId);
// 	
//     }

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendSkillPlayerCharacterCollisionAffectTroopPacket(CClient* client,IdType injectCharacterId, IdType affectTroopId, UInt affectSoldierIndex, UInt affectTotal, IdType skillId)
	{
//         // ×ª»»Âß¼­°ü
//         PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_TROOP_DATA sendData;
// 
//         // Ìî³äÂß¼­°ü
//         sendData.injectCharacterId = injectCharacterId;
//         sendData.affectTroopId = affectTroopId;
//         sendData.affectSoldierIndex = affectSoldierIndex;
//         sendData.affectTotal = affectTotal;
//         sendData.skillId= skillId;
// 		sendData.regionID = CPlayer::getInstance().getActiveClan()->getData()->regionID;
// 		sendData.instanceUid = CPlayer::getInstance().getInstanceUid();
// 
// 		NetPacketPackManager::getInstance().addPacketToBuff(PT_PLAYERCHARACTER_AFFECT_COLLISION_TROOP, GOT_PLAYERCHARACTER, (Char8*)&sendData, injectCharacterId);
// 	
    }

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendSkillPlayerCharacterCollisionAffectBuildingPacket(CClient* client,IdType injectCharacterId, IdType affectBuildingId, UInt affectTotal, IdType skillId, IdType mapId)
	{

//         // ×ª»»Âß¼­°ü
//         PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_BUILDING_DATA sendData;
//         // Ìî³äÂß¼­°ü
//         sendData.injectCharacterId = injectCharacterId;
//         sendData.affectBuildingId = affectBuildingId;
//         sendData.affectTotal = affectTotal;
//         sendData.skillId= skillId;
// 		sendData.regionID = CPlayer::getInstance().getActiveClan()->getData()->regionID;
// 		sendData.instanceUid = CPlayer::getInstance().getInstanceUid();
// 
// 		NetPacketPackManager::getInstance().addPacketToBuff(PT_PLAYERCHARACTER_AFFECT_COLLISION_BUILDING, GOT_PLAYERCHARACTER, (Char8*)&sendData, injectCharacterId);
    }

	//-----------------------------------------------------------------------------
// 	void SkillNetPacketProcesser::sendSkillPlayerCharacterCollisionAffectMonsterPacket(IdType injectCharacterId, IdType affectMonsterId, UInt affectTotal, IdType skillId)
// 	{
// 		// ×ª»»Âß¼­°ü
// 		PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_MONSTER_DATA sendData;
// 		// Ìî³äÂß¼­°ü
// 		sendData.injectCharacterId = injectCharacterId;
// 		sendData.affectMonsterId = affectMonsterId;
// 		sendData.affectTotal = affectTotal;
// 		sendData.skillId= skillId;
// 
// 		NetPacketPackManager::getInstance().addPacketToBuff(PT_PLAYERCHARACTER_AFFECT_COLLISION_MONSTER, GOT_PLAYERCHARACTER, (Char8*)&sendData, injectCharacterId);
// 	}


	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendSkillTroopCollisionAffectPlayerCharacterPacket(CClient* client,IdType injectTroopId, UInt injectSoldierIndex, IdType affectCharacterId, UInt affectTotal, IdType skillId)
	{
//         // ×ª»»Âß¼­°ü
//         PT_SKILL_C2M_TROOP_AFFECT_COLLISION_PLAYERCHARACTER_DATA sendData;
//         // Ìî³äÂß¼­°ü
//         sendData.injectTroopId = injectTroopId;
//         sendData.injectSoldierIndex = injectSoldierIndex;
//         sendData.affectCharacterId = affectCharacterId;
//         sendData.affectTotal = affectTotal;
//         sendData.skillId= skillId;
// 	
// 		NetPacketPackManager::getInstance().addPacketToBuff(PT_TROOP_AFFECT_COLLISION_PLAYERCHARACTER, GOT_TROOP, (Char8*)&sendData, injectTroopId);
    }

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendSkillTroopCollisionAffectTroopPacket(CClient* client,IdType injectTroopId, UInt injectSoldierIndex, IdType affectTroopId, UInt affectSoldierIndex, UInt affectTotal, IdType skillId)
	{
//         // ×ª»»Âß¼­°ü
//         PT_SKILL_C2M_TROOP_AFFECT_COLLISION_TROOP_DATA sendData;
//         // Ìî³äÂß¼­°ü
//         sendData.injectTroopId = injectTroopId;
//         sendData.injectSoldierIndex = injectSoldierIndex;
//         sendData.affectTroopId = affectTroopId;
//         sendData.affectSoldierIndex = affectSoldierIndex;
//         sendData.affectTotal = affectTotal;
//         sendData.skillId= skillId;
// 	
// 		NetPacketPackManager::getInstance().addPacketToBuff(PT_TROOP_AFFECT_COLLISION_TROOP, GOT_TROOP, (Char8*)&sendData, injectTroopId);
    }

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendSkillTroopCollisionAffectBuildingPacket(CClient* client,IdType injectTroopGroupId, UInt injectTroopId, IdType affectBuildingId, UInt affectTotal, IdType skillId, IdType mapId)
	{
        // ×ª»»Âß¼­°ü
//         PT_SKILL_C2M_TROOP_AFFECT_COLLISION_BUILDING_DATA sendData;
//         // Ìî³äÂß¼­°ü
//         sendData.injectTroopGroupId = injectTroopGroupId;
//         sendData.injectTroopId = injectTroopId;
//         sendData.affectBuildingId = affectBuildingId;
//         sendData.affectTotal = affectTotal;
//         sendData.skillId= skillId;
// 	
// 		NetPacketPackManager::getInstance().addPacketToBuff(PT_TROOP_AFFECT_COLLISION_BUILDING, GOT_TROOP, (Char8*)&sendData, injectTroopId);
    }

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendSkillTroopCollisionAffectMonsterPacket(CClient* client,IdType injectTroopGroupId, UInt injectTroopId, IdType affectMonsterId, UInt affectTotal, IdType skillId)
	{
		// ×ª»»Âß¼­°ü
		PT_SKILL_C2M_TROOP_AFFECT_COLLISION_MONSTER_DATA sendData;
		// Ìî³äÂß¼­°ü
		//sendData.injectTroopGroupId = injectTroopGroupId;
		sendData.injectTroopId = injectTroopId;
		sendData.affectMonsterId = affectMonsterId;
		sendData.affectTotal = affectTotal;
		sendData.skillId= skillId;

		client->getPackManager()->addPacketToBuff(PT_TROOP_AFFECT_COLLISION_MONSTER, GOT_TROOP, (Char8*)&sendData, injectTroopId);
	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendSkillBuildingCollisionAffectPlayerCharacterPacket(CClient* client,IdType injectBuildingId, IdType affectCharacterId, UInt affectTotal, IdType skillId)
	{
        // ×ª»»Âß¼­°ü
        PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_PLAYERCHARACTER_DATA sendData;
        // Ìî³äÂß¼­°ü
        sendData.injectBuildingId = injectBuildingId;
        sendData.affectCharacterId = affectCharacterId;
        sendData.affectTotal = affectTotal;
        sendData.skillId= skillId;
		client->getPackManager()->addPacketToBuff(PT_TROOP_AFFECT_COLLISION_MONSTER, GOT_TROOP, (Char8*)&sendData, injectBuildingId);
    }

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendSkillBuildingCollisionAffectTroopPacket(CClient* client,IdType injectBuildingId, IdType affectTroopGroupId, UInt affectTroopId, UInt affectTotal, IdType skillId)
	{
        // ×ª»»Âß¼­°ü
        PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_TROOP_DATA sendData;
        // Ìî³äÂß¼­°ü
        sendData.injectBuildingId = injectBuildingId;
        //sendData.affectTroopGroupId = affectTroopGroupId;
        sendData.affectTroopId = affectTroopId;
        sendData.affectTotal = affectTotal;
        sendData.skillId= skillId;

		client->getPackManager()->addPacketToBuff(PT_BUILDING_AFFECT_COLLISION_TROOP, GOT_TROOP, (Char8*)&sendData, injectBuildingId);
	
    }

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendSkillBuildingCollisionAffectBuildingPacket(CClient* client,IdType injectBuildingId, IdType affectBuildingId, UInt affectTotal, IdType skillId, IdType mapId)
	{
        // ×ª»»Âß¼­°ü
        PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_BUILDING_DATA sendData;
        // Ìî³äÂß¼­°ü
        sendData.injectBuildingId = injectBuildingId;
        sendData.affectBuildingId = affectBuildingId;
        sendData.affectTotal = affectTotal;
        sendData.skillId= skillId;

		client->getPackManager()->addPacketToBuff(PT_BUILDING_AFFECT_COLLISION_BUILDING, GOT_TROOP, (Char8*)&sendData, injectBuildingId);

    }

	void SkillNetPacketProcesser::sendSkillBuildingCollisionAffectMonsterPacket(CClient* client,IdType injectBuildingId, IdType affectMonsterId, UInt affectTotal, IdType skillId, IdType mapId)
	{
		// ×ª»»Âß¼­°ü
		PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_MONSTER_DATA sendData;
		// Ìî³äÂß¼­°ü
		sendData.injectBuildingId = injectBuildingId;
		sendData.affectMonsterId = affectMonsterId;
		sendData.affectTotal = affectTotal;
		sendData.skillId= skillId;

		client->getPackManager()->addPacketToBuff(PT_BUILDING_AFFECT_COLLISION_MONSTER, GOT_TROOP, (Char8*)&sendData, injectBuildingId);

	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendSkillMonsterCollisionAffectPlayerCharacterPacket(CClient* client,IdType injectMonsterId, IdType affectCharacterId, UInt affectTotal, IdType skillId)
	{
		// ×ª»»Âß¼­°ü
		PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA sendData;
		// Ìî³äÂß¼­°ü
		sendData.injectMonsterId = injectMonsterId;
		sendData.affectCharacterId = affectCharacterId;
		sendData.affectTotal = affectTotal;
		sendData.skillId= skillId;

		client->getPackManager()->addPacketToBuff(PT_MONSTER_AFFECT_COLLISION_PLAYERCHARACTER, GOT_TROOP, (Char8*)&sendData, injectMonsterId);

	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendSkillMonsterCollisionAffectTroopPacket(CClient* client,IdType injectMonsterId, IdType affectTroopId, UInt affectSoldierIndex, UInt affectTotal, IdType skillId)
	{

	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendSkillMonsterCollisionAffectBuildingPacket(CClient* client,IdType injectMonsterId, IdType affectBuildingId, UInt affectTotal, IdType skillId, IdType mapId)
	{

	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendSkillMonsterCollisionAffectMonsterPacket(CClient* client,IdType injectMonsterId, IdType affectMonsterId, UInt affectTotal, IdType skillId)
	{

	}




	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::onRecvLearnSkillResult(CClient* client, PT_SKILL_F2C_LEARN_RESULT_DATA* data )
	{

	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::onRecvPlayCharacterClantSkillRequire(CClient* client,  PT_SKILL_M2C_PLAYERCHARACTER_CLANT_DATA* data )
	{

	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::onRecvPlayCharacterInjectEmitterSkillRequire(CClient* client, PT_SKILL_M2C_PLAYERCHARACTER_INJECT_EMITTER_DATA* data )
	{


	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::onRecvPlayCharacterInjectPointSkillRequire(CClient* client, PT_SKILL_M2C_PLAYERCHARACTER_INJECT_POINT_DATA* data )
	{


	}
	
	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::onRecvPlayCharacterInjectObjectSkillRequire(CClient* client, PT_SKILL_M2C_PLAYERCHARACTER_INJECT_OBJECT_DATA* data )
	{

	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::onRecvPlayCharacterInjectEndSkillRequire(CClient* client,  PT_SKILL_M2C_PLAYERCHARACTER_END_INJECT_DATA* data )
	{

	}



	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::onRecvTroopClantSkillRequire( CClient* client,PT_SKILL_M2C_TROOP_CLANT_DATA* data )
	{
#if 0
		//FUNDETECTION(__MG_FUNC__);
		CTroopEntity* entity = CSceneManager::getInstance().getTroopEntity( data->troopGroupId, data->troopId );
		if ( entity )
		{
			//ÔÝÊ±²»¾«È·Î»ÖÃ
			CTroopGroupEntity* troopGroupEntity = (CTroopGroupEntity*)entity->getParent();
			//if(troopGroupEntity && troopGroupEntity->getAIManager()->getAIState() == move)
			//{
				//AI* ai = troopGroupEntity->getAIManager()->getCurrAI();
				//if(ai)
				//{
				//	ai->end();
				//	ai->destroy();
				//	troopGroupEntity->getAIManager()->setAIState(null);
				//}

			//}

			entity->stopMove();
			entity->setDir( Vec3( data->troopDir.x , 0 , data->troopDir.z) );
			//entity->setPos( Vec3( data->troopPos.x , 0 , data->troopPos.z) );
			entity->startClantSkill( data->skillId );
			if(CPlayer::getInstance().getActiveClan()->hasPlayerTroop(entity->getParent()->getID(), entity->getID()))
			{
				entity->setIsRecvSkill(true);
			}	
		}
#endif
	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendTroopInjectSkillRequestPacket(CClient* client,CSkillObject* skillObject)
	{
		
	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendTroopInjectSkillRequestPacketToPackBuffer(CClient* client,CSkillObject* skillObject)
	{

	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendTroopEndInjectSkillPacket(CClient* client,CSkillObject* skillObject)
	{


	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendTroopEndInjectSkillPacketToPackBuffer(CClient* client,CSkillObject* skillObject)
	{

	}


	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendBuildingClantSkillRequestPacket(CClient* client,CSkillObject* skillObject)
	{

	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendBuildingInjectSkillRequestPacket(CClient* client,CSkillObject* skillObject)
	{

	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendBuildingEndInjectSkillPacket(CClient* client,CSkillObject* skillObject)
	{


	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::onRecvBuildingClantSkillRequire( CClient* client, PT_SKILL_M2C_BUILDING_CLANT_DATA* data )
	{

	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::onRecvBuildingInjectInstantSkillRequire( CClient* client, PT_SKILL_M2C_BUILDING_INJECT_EMITTER_DATA* data )
	{
	
	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::onRecvBuildingInjectPointSkillRequire( CClient* client, PT_SKILL_M2C_BUILDING_INJECT_POINT_DATA* data )
	{
	
	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::onRecvBuildingInjectObjectSkillRequire( CClient* client, PT_SKILL_M2C_BUILDING_INJECT_OBJECT_DATA* data )
	{
	
	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendSkillSummonBuildingPacket(CClient* client,IdType characterId, IdType skillId, IdType mapId, Byte mapType, IdType templateId, NetVec2 pos)
	{
      	
    }




}