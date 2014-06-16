/******************************************************************************/
#include "stdafx.h"
#include "ClientNetApplyManager.h"
#include "SkillNetPacketProcesser.h"
#include "CSceneManager.h"
#include "CBuildingEntity.h"
#include "CPlayer.h"
#include "CPlayerCharacterEntity.h"
#include "NetPacketPackManager.h"
#include "SkillBaseInfo.h"
#include "CCDManager.h"
#include "CTroopSoldierEntity.h"
#include "CTroopEntity.h"
#include "SkillInfoList.h"
#include "CMonsterEntity.h"
#include "CGoUpAndDownSkillEffect.h"
#include "CharacterSceneEntityAction.h"
#include "CActionManager.h"
/******************************************************************************/
namespace MG
{

    //-----------------------------------------------------------------------------
    SkillNetPacketProcesser::SkillNetPacketProcesser()
    {

    }

    //-----------------------------------------------------------------------------
    SkillNetPacketProcesser::~SkillNetPacketProcesser()
    {

    }

    //-----------------------------------------------------------------------------
    Bool SkillNetPacketProcesser::processFrontServerPacket(I32 id,NetEventRecv* packet)
    {
		if ( packet->getChannel() == GNPC_SKILL )
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_SKILL_M2C_PLAYERCHARACTER_CLANT:
				onRecvPlayCharacterClantSkillRequire( (PT_SKILL_M2C_PLAYERCHARACTER_CLANT_DATA*)data->data );
				break;
			case PT_SKILL_M2C_PLAYERCHARACTER_INJECT_EMITTER:
				onRecvPlayCharacterInjectEmitterSkillRequire( (PT_SKILL_M2C_PLAYERCHARACTER_INJECT_EMITTER_DATA*)data->data );
				break;
			case PT_SKILL_M2C_PLAYERCHARACTER_INJECT_POINT:
				onRecvPlayCharacterInjectPointSkillRequire( (PT_SKILL_M2C_PLAYERCHARACTER_INJECT_POINT_DATA*)data->data );
				break;
			case PT_SKILL_M2C_PLAYERCHARACTER_INJECT_OBJECT:
				onRecvPlayCharacterInjectObjectSkillRequire( (PT_SKILL_M2C_PLAYERCHARACTER_INJECT_OBJECT_DATA*)data->data );
				break;
			case PT_SKILL_M2C_PLAYERCHARACTER_END_INJECT:
				onRecvPlayCharacterInjectEndSkillRequire( (PT_SKILL_M2C_PLAYERCHARACTER_END_INJECT_DATA*)data->data );
				break;
			case PT_SKILL_M2C_TROOP_CLANT:
				onRecvTroopClantSkillRequire( (PT_SKILL_M2C_TROOP_CLANT_DATA*)data->data );
				break;
			case PT_SKILL_M2C_TROOP_INJECT_EMITTER:
				onRecvTroopInjectEmitterSkillRequire( (PT_SKILL_M2C_TROOP_INJECT_EMITTER_DATA*)data->data );
				break;
			case PT_SKILL_M2C_TROOP_INJECT_POINT:
				onRecvTroopInjectPointSkillRequire( (PT_SKILL_M2C_TROOP_INJECT_POINT_DATA*)data->data );
				break;
			case PT_SKILL_M2C_TROOP_INJECT_OBJECT:
				onRecvTroopInjectObjectSkillRequire( (PT_SKILL_M2C_TROOP_INJECT_OBJECT_DATA*)data->data );
				break;
			case PT_SKILL_S2C_TROOP_USE_SKILL:
				onRecvTroopUseSkillRequire( (PT_SKILL_S2C_TROOP_USE_SKILL_DATA*)data->data );
				break;
			case PT_SKILL_M2C_BUILDING_CLANT:
				onRecvBuildingClantSkillRequire( (PT_SKILL_M2C_BUILDING_CLANT_DATA*)data->data );
				break;
			case PT_SKILL_M2C_BUILDING_INJECT_EMITTER:
				onRecvBuildingInjectInstantSkillRequire( (PT_SKILL_M2C_BUILDING_INJECT_EMITTER_DATA*)data->data );
				break;
			case PT_SKILL_M2C_BUILDING_INJECT_POINT:
				onRecvBuildingInjectPointSkillRequire( (PT_SKILL_M2C_BUILDING_INJECT_POINT_DATA*)data->data );
				break;
			case PT_SKILL_M2C_BUILDING_INJECT_OBJECT:
				onRecvBuildingInjectObjectSkillRequire( (PT_SKILL_M2C_BUILDING_INJECT_OBJECT_DATA*)data->data );
				break;
			case PT_SKILL_M2C_MONSTER_INJECT_OBJECT:
				onRecvMonsterInjectObjectSkillRequire( (PT_SKILL_M2C_MONSTER_INJECT_OBJECT_DATA*)data->data );
				break;
			case PT_SKILL_M2C_MONSTER_INJECT_POINT:
				onRecvMonsterInjectPointSkillRequire( (PT_SKILL_M2C_MONSTER_INJECT_POINT_DATA*)data->data );
				break;
			case PT_SKILL_M2C_MONSTER_END_INJECT:
				onRecvMonsterInjectEndSkillRequire( (PT_SKILL_M2C_MONSTER_END_INJECT_DATA*)data->data );
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

    //-----------------------------------------------------------------------------
    void SkillNetPacketProcesser::sendPlayCharacterClantSkillRequestPacket(CSkillObject* skillObject)
    {
        //Character* character = skillObject->getOwner();
        //if(character && character->getIsRecvSkill())
        //{
        //    // 获得一个发送【服务端】缓存
        //    GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        //    // 转换成标准包格式
        //    GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        //    if ( packet )
        //    {
        //        // 设置标签
        //        packet->channel = GNPC_SKILL;
        //        packet->type    = PT_SKILL_C2F_PLAYERCHARACTER_CLANT;

        //        // 转换逻辑包
        //        PT_SKILL_C2F_PLAYERCHARACTER_CLANT_DATA* sendData = (PT_SKILL_C2F_PLAYERCHARACTER_CLANT_DATA*)(packet->data);
        //        if ( sendData )
        //        {
        //            // 填充逻辑包
        //            sendData->characterId = character->getID();
        //            sendData->skillId = skillObject->getBaseInfo()->id;
        //            sendData->characterPos.x = character->getPos().x;
        //            sendData->characterPos.z = character->getPos().z;
        //            sendData->characterDir.x = character->getDir().x;
        //            sendData->characterDir.z = character->getDir().z;

        //            // 发送数据
        //            ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
        //                GameNetPacketData_INFO::headSize + PT_SKILL_C2F_PLAYERCHARACTER_CLANT_DATA_INFO::dataSize );
        //            
        //            character->setIsRecvSkill(false);
        //        }
        //    }

            
        //}

    }


	//-----------------------------------------------------------------------------
	 void SkillNetPacketProcesser::sendCharacterUseSkillPacketToPackBuffer(CSkillObject* skillObject)
	 {
		 SkillInfo* skillInfo = skillObject->getSkillInfo();

		 GAMEOBJ_TYPE gameObjType = skillObject->getOwnerType();

		 if( skillInfo->skillType != SKT_PARABOLAAREA 
			 && skillInfo->skillType != SKT_GOUPANDDOWN 
			 && skillInfo->skillType != SKT_SHORTRANGEGENERAL 
			 && skillInfo->skillType != SKT_LONGRANGEGENERAL 
			 && skillInfo->skillType != SKT_SELFAREA 
			 && skillInfo->skillType != SKT_TARGETPOSAREA 
			 && skillInfo->skillType != SKT_SINGLEEMITTER )
		 {
			 if(gameObjType == GOT_PLAYERCHARACTER)
			 {
				 sendPlayCharacterClantSkillRequestPacketToPackBuffer(skillObject);
			 }
			 else if(gameObjType == GOT_SOLDIER)
			 {
				 //CAITroopObjectSendSkillPacket* aiTroopObjectSendSkillPacket = (CAITroopObjectSendSkillPacket*)((CTroopSoldierEntity*)mOwner)->getTroopEntity()->getAIStateManager().getState("CAITroopObjectSendSkillPacket", false);
				 //if(!aiTroopObjectSendSkillPacket)
				 //{
					// return;
				 //}

				 sendTroopClantSkillRequestPacketToPackBuffer(skillObject);
			 }
			 else if(gameObjType == GOT_MONSTER)
			 {
				 //sendMonsterClantSkillRequestPacketToPackBuffer(skillObject);
			 }
		 }
		 else
		 {
			 if(gameObjType == GOT_PLAYERCHARACTER)
			 {
				 sendPlayCharacterInjectSkillRequestPacketToPackBuffer(skillObject);
			 }
			 else if(gameObjType == GOT_SOLDIER)
			 {
				 //CAITroopObjectSendSkillPacket* aiTroopObjectSendSkillPacket = (CAITroopObjectSendSkillPacket*)((CTroopSoldierEntity*)mOwner)->getTroopEntity()->getAIStateManager().getState("CAITroopObjectSendSkillPacket", false);
				 //if(!aiTroopObjectSendSkillPacket)
				 //{
					// return;
				 //}

				 sendTroopInjectSkillRequestPacketToPackBuffer(skillObject);
			 }
			 else if(gameObjType == GOT_MONSTER)
			 {
				 //sendMonsterInjectSkillRequestPacketToPackBuffer(skillObject);
			 }
			 else if(gameObjType == GOT_TROOP)
			 {
				 sendTroopUseSkillRequestPacketToPackBuffer(skillObject);
			 }
		 }
	 }

	 //-----------------------------------------------------------------------------
	 void SkillNetPacketProcesser::sendPlayCharacterClantSkillRequestPacketToPackBuffer(CSkillObject* skillObject)
	 {
		 CPlayerCharacterEntity* playerCharacterEntity = CSceneManager::getInstance().getPlayerCharacterEntity(skillObject->getOwnerID());
		 if(!playerCharacterEntity)
		 {
			return;
		 }

		 PT_SKILL_C2M_PLAYERCHARACTER_CLANT_DATA sendData;
		 // 填充逻辑包
		 sendData.characterIndex = playerCharacterEntity->getID();
		 sendData.skillId = skillObject->getSkillInfo()->skillId;

		 /*sendData.characterPos.x = playerCharacterEntity->getPos().x;
		 sendData.characterPos.z = playerCharacterEntity->getPos().z;
		 sendData.characterDir.x = playerCharacterEntity->getDir().x;
		 sendData.characterDir.z = playerCharacterEntity->getDir().z;*/
		 sendData.characterPos = ((NetVec2)playerCharacterEntity->getPos()).getData();
		 sendData.characterDir = ((NetVec2)playerCharacterEntity->getDir()).getData();

		 sendData.targetType = skillObject->getTargetObjectType();
		 sendData.targetId = skillObject->getTargetObjectID();
		 sendData.targetIndex = skillObject->getTargetObjectIndex();

		 /*sendData.targetPos.x = skillObject->getTargetPosition().x;
		 sendData.targetPos.z = skillObject->getTargetPosition().z;*/
		 sendData.targetPos = ((NetVec2)skillObject->getTargetPosition()).getData();

		 NetPacketPackManager::getInstance().addPacketToBuff(PT_PLAYERCHARACTER_CLANT, GOT_PLAYERCHARACTER, (Char8*)&sendData, playerCharacterEntity->getID());
	 }

	 //-----------------------------------------------------------------------------
	 void SkillNetPacketProcesser::sendPlayCharacterInjectSkillRequestPacketToPackBuffer(CSkillObject* skillObject)
	 {
		 CPlayerCharacterEntity* playerCharacterEntity = CSceneManager::getInstance().getPlayerCharacterEntity(skillObject->getOwnerID());
		 if(!playerCharacterEntity)
		 {
			return;
		 }

		 if(skillObject->getTargetObjectID() != 0)
		 {
			CCharacterSceneEntity* targetCharacterEntity = CSceneManager::getInstance().getCharacterSceneEntity(skillObject->getTargetObjectType(), skillObject->getTargetObjectID(), skillObject->getTargetObjectIndex());
			if(!targetCharacterEntity)
			{
				return;
			}
		 }
		 

		 switch(skillObject->getSkillInfo()->skillType)
		 {
		 case SKT_SHORTRANGEGENERAL:
		 case SKT_LONGRANGEGENERAL:
		 case SKT_SINGLETARGET:
		 case SKT_LONGRANGEAUXILIARY:
			 {
				PT_SKILL_C2M_PLAYERCHARACTER_INJECT_OBJECT_DATA sendData;
				sendData.skillId = skillObject->getSkillInfo()->skillId;
				sendData.characterIndex = playerCharacterEntity->getID();
				sendData.objectIndex = skillObject->getTargetObjectIndex();
				sendData.objectId = skillObject->getTargetObjectID();
				sendData.objectType = skillObject->getTargetObjectType();

				NetPacketPackManager::getInstance().addPacketToBuff(PT_PLAYERCHARACTER_INJECT_OBJECT, GOT_PLAYERCHARACTER, (Char8*)&sendData, playerCharacterEntity->getID());
			 }
			 break;
		 case SKT_SINGLEEMITTER:
			 {
				 Vec3 dir = skillObject->getTargetPosition() - playerCharacterEntity->getPos();
				 dir.y = 0;
				 dir.normalise();

				 PT_SKILL_C2M_PLAYERCHARACTER_INJECT_EMITTER_DATA sendData;
				 sendData.skillId = skillObject->getSkillInfo()->skillId;
				 sendData.characterIndex = playerCharacterEntity->getID();
				 /*sendData.injectDir.x = dir.x; 
				 sendData.injectDir.z = dir.z; */
				 sendData.injectDir = ((NetVec2)dir).getData();

				 NetPacketPackManager::getInstance().addPacketToBuff(PT_PLAYERCHARACTER_INJECT_EMITTER, GOT_PLAYERCHARACTER, (Char8*)&sendData, playerCharacterEntity->getID());
			 }
			 break;
		 case SKT_SELFAREA:
			 {
				 PT_SKILL_C2M_PLAYERCHARACTER_INJECT_POINT_DATA sendData;
				 sendData.skillId = skillObject->getSkillInfo()->skillId;
				 sendData.characterIndex = playerCharacterEntity->getID();
				 /*sendData.targetPos.x = skillObject->getTargetPosition().x;
				 sendData.targetPos.z = skillObject->getTargetPosition().z;
				 sendData.dir.x = playerCharacterEntity->getDir().x;
				 sendData.dir.z = playerCharacterEntity->getDir().z;*/
				 sendData.targetPos = ((NetVec2)skillObject->getTargetPosition()).getData();
				 sendData.dir = ((NetVec2)playerCharacterEntity->getDir()).getData();

				 NetPacketPackManager::getInstance().addPacketToBuff(PT_PLAYERCHARACTER_INJECT_POINT, GOT_PLAYERCHARACTER, (Char8*)&sendData, playerCharacterEntity->getID());
			 }
			 break;
		 case SKT_TARGETPOSAREA:
			 {
				 PT_SKILL_C2M_PLAYERCHARACTER_INJECT_POINT_DATA sendData;
				 sendData.skillId = skillObject->getSkillInfo()->skillId;
				 sendData.characterIndex = playerCharacterEntity->getID();
				 /*sendData.targetPos.x = skillObject->getTargetPosition().x;
				 sendData.targetPos.z = skillObject->getTargetPosition().z;
				 sendData.dir.x = 0;
				 sendData.dir.z = 0;*/
				 sendData.targetPos = ((NetVec2)skillObject->getTargetPosition()).getData();

				 NetPacketPackManager::getInstance().addPacketToBuff(PT_PLAYERCHARACTER_INJECT_POINT, GOT_PLAYERCHARACTER, (Char8*)&sendData, playerCharacterEntity->getID());
			 }
			 break;
		 }


		 //
		 //skillObject->getOwner();

		 // 获得一个发送【服务端】缓存
		 //  GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		 //  // 转换成标准包格式
		 //  GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		 //  if ( packet )
		 //  {
		 //      // 设置标签
		 //      packet->channel = GNPC_SKILL;

		 //      SkillOpType opType = skillObject->getListInfo()->skillType;
		 //      switch(opType)
		 //      {
		 //      case SKILLOPTYPE_EMITTER:
		 //          {
		 //              packet->type    = PT_SKILL_C2F_PLAYERCHARACTER_INJECT_EMITTER;

		 //              // 转换逻辑包
		 //              PT_SKILL_C2F_PLAYERCHARACTER_INJECT_EMITTER_DATA* sendData = (PT_SKILL_C2F_PLAYERCHARACTER_INJECT_EMITTER_DATA*)(packet->data);
		 //              if ( sendData )
		 //              {
		 //                  // 填充逻辑包
		 //CSceneEntity* gameObject = CSceneManager::getInstance().getSceneEntity( skillObject->getOwnerID(), skillObject->getOwnerType() );
		 //if(!gameObject)
		 //{
		 //	return;
		 //}

		 //                  sendData->characterId = gameObject->getID();
		 //                  sendData->skillId = skillObject->getBaseInfo()->id;

		 //                  // 发送数据
		 //                  ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
		 //                      GameNetPacketData_INFO::headSize + PT_SKILL_C2F_PLAYERCHARACTER_INJECT_EMITTER_DATA_INFO::dataSize );

		 //              }
		 //          }
		 //          break;

		 //      case SKILLOPTYPE_POINT:
		 //          {
		 //              packet->type    = PT_SKILL_C2F_PLAYERCHARACTER_INJECT_POINT;

		 //              // 转换逻辑包
		 //              PT_SKILL_C2F_PLAYERCHARACTER_INJECT_POINT_DATA* sendData = (PT_SKILL_C2F_PLAYERCHARACTER_INJECT_POINT_DATA*)(packet->data);
		 //              if ( sendData )
		 //              {
		 //                  // 填充逻辑包
		 //                  CSceneEntity* gameObject = CSceneManager::getInstance().getSceneEntity( skillObject->getOwnerID(), skillObject->getOwnerType() );
		 //                  if(!gameObject)
		 //                  {
		 //                      return;
		 //                  }

		 //                  sendData->characterId = gameObject->getID();
		 //                  sendData->skillId = skillObject->getBaseInfo()->id;
		 //                  sendData->targetPos.x = skillObject->getTargetPosition().x;
		 //                  sendData->targetPos.z = skillObject->getTargetPosition().z;

		 //                  // 发送数据
		 //                  ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
		 //                      GameNetPacketData_INFO::headSize +PT_SKILL_C2F_PLAYERCHARACTER_INJECT_POINT_DATA_INFO::dataSize );

		 //              }

		 //          }
		 //          break;

		 //      case SKILLOPTYPE_OBJECT:
		 //          {
		 //              packet->type    = PT_SKILL_C2F_PLAYERCHARACTER_INJECT_OBJECT;

		 //              // 转换逻辑包
		 //              PT_SKILL_C2F_PLAYERCHARACTER_INJECT_OBJECT_DATA* sendData = (PT_SKILL_C2F_PLAYERCHARACTER_INJECT_OBJECT_DATA*)(packet->data);
		 //              if ( sendData )
		 //              {
		 //                  // 填充逻辑包
		 //                  CSceneEntity* gameObject = CSceneManager::getInstance().getSceneEntity( skillObject->getOwnerID(), skillObject->getOwnerType() );
		 //                  if(!gameObject)
		 //                  {
		 //                      return;
		 //                  }

		 //                  sendData->characterId = gameObject->getID();
		 //                  sendData->skillId = skillObject->getBaseInfo()->id;
		 //                  sendData->objectId = skillObject->getTargetObjectID();
		 //                  sendData->objectIndex = skillObject->getTargetObjectIndex();
		 //                  sendData->objectType = skillObject->getTargetObjectType();

		 //                  // 发送数据
		 //                  ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
		 //                      GameNetPacketData_INFO::headSize +PT_SKILL_C2F_PLAYERCHARACTER_INJECT_OBJECT_DATA_INFO::dataSize );

		 //              }                 
		 //          }
		 //          break;

		 //      }

		 //  }


	 }

    //-----------------------------------------------------------------------------
    void SkillNetPacketProcesser::sendPlayCharacterInjectSkillRequestPacket(CSkillObject* skillObject)
    {
		//
		//skillObject->getOwner();

        // 获得一个发送【服务端】缓存
      //  GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

      //  // 转换成标准包格式
      //  GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
      //  if ( packet )
      //  {
      //      // 设置标签
      //      packet->channel = GNPC_SKILL;

      //      SkillOpType opType = skillObject->getListInfo()->skillType;
      //      switch(opType)
      //      {
      //      case SKILLOPTYPE_EMITTER:
      //          {
      //              packet->type    = PT_SKILL_C2F_PLAYERCHARACTER_INJECT_EMITTER;

      //              // 转换逻辑包
      //              PT_SKILL_C2F_PLAYERCHARACTER_INJECT_EMITTER_DATA* sendData = (PT_SKILL_C2F_PLAYERCHARACTER_INJECT_EMITTER_DATA*)(packet->data);
      //              if ( sendData )
      //              {
      //                  // 填充逻辑包
						//CSceneEntity* gameObject = CSceneManager::getInstance().getSceneEntity( skillObject->getOwnerID(), skillObject->getOwnerType() );
						//if(!gameObject)
						//{
						//	return;
						//}

      //                  sendData->characterId = gameObject->getID();
      //                  sendData->skillId = skillObject->getBaseInfo()->id;

      //                  // 发送数据
      //                  ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
      //                      GameNetPacketData_INFO::headSize + PT_SKILL_C2F_PLAYERCHARACTER_INJECT_EMITTER_DATA_INFO::dataSize );

      //              }
      //          }
      //          break;

      //      case SKILLOPTYPE_POINT:
      //          {
      //              packet->type    = PT_SKILL_C2F_PLAYERCHARACTER_INJECT_POINT;

      //              // 转换逻辑包
      //              PT_SKILL_C2F_PLAYERCHARACTER_INJECT_POINT_DATA* sendData = (PT_SKILL_C2F_PLAYERCHARACTER_INJECT_POINT_DATA*)(packet->data);
      //              if ( sendData )
      //              {
      //                  // 填充逻辑包
      //                  CSceneEntity* gameObject = CSceneManager::getInstance().getSceneEntity( skillObject->getOwnerID(), skillObject->getOwnerType() );
      //                  if(!gameObject)
      //                  {
      //                      return;
      //                  }

      //                  sendData->characterId = gameObject->getID();
      //                  sendData->skillId = skillObject->getBaseInfo()->id;
      //                  sendData->targetPos.x = skillObject->getTargetPosition().x;
      //                  sendData->targetPos.z = skillObject->getTargetPosition().z;

      //                  // 发送数据
      //                  ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
      //                      GameNetPacketData_INFO::headSize +PT_SKILL_C2F_PLAYERCHARACTER_INJECT_POINT_DATA_INFO::dataSize );

      //              }

      //          }
      //          break;

      //      case SKILLOPTYPE_OBJECT:
      //          {
      //              packet->type    = PT_SKILL_C2F_PLAYERCHARACTER_INJECT_OBJECT;

      //              // 转换逻辑包
      //              PT_SKILL_C2F_PLAYERCHARACTER_INJECT_OBJECT_DATA* sendData = (PT_SKILL_C2F_PLAYERCHARACTER_INJECT_OBJECT_DATA*)(packet->data);
      //              if ( sendData )
      //              {
      //                  // 填充逻辑包
      //                  CSceneEntity* gameObject = CSceneManager::getInstance().getSceneEntity( skillObject->getOwnerID(), skillObject->getOwnerType() );
      //                  if(!gameObject)
      //                  {
      //                      return;
      //                  }

      //                  sendData->characterId = gameObject->getID();
      //                  sendData->skillId = skillObject->getBaseInfo()->id;
      //                  sendData->objectId = skillObject->getTargetObjectID();
      //                  sendData->objectIndex = skillObject->getTargetObjectIndex();
      //                  sendData->objectType = skillObject->getTargetObjectType();

      //                  // 发送数据
      //                  ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
      //                      GameNetPacketData_INFO::headSize +PT_SKILL_C2F_PLAYERCHARACTER_INJECT_OBJECT_DATA_INFO::dataSize );

      //              }                 
      //          }
      //          break;

      //      }

      //  }

		
    }

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendPlayCharacterEndInjectSkillPacket(CSkillObject* skillObject)
	{
		if(skillObject)
		{
            CSceneEntity* gameObject = CSceneManager::getInstance().getSceneEntity( skillObject->getOwnerID(), skillObject->getOwnerType() );
            if(!gameObject)
            {
                return;
            }

            CCharacterSceneEntity* character = (CCharacterSceneEntity*)gameObject;

            if(false)
            //if(character && character->getIsRecvSkill())
            {
                // 获得一个发送【服务端】缓存
                GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

                // 转换成标准包格式
                GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
                if ( packet )
                {
                    // 设置标签
                    packet->channel = GNPC_SKILL;
                    packet->type    = PT_SKILL_C2M_PLAYERCHARACTER_END_INJECT;

                    // 转换逻辑包
                    PT_SKILL_C2M_PLAYERCHARACTER_END_INJECT_DATA* sendData = (PT_SKILL_C2M_PLAYERCHARACTER_END_INJECT_DATA*)(packet->data);
                    if ( sendData )
                    {
                        // 填充逻辑包
                        sendData->characterIndex = gameObject->getID();
                        sendData->skillId = skillObject->getSkillInfo()->skillId;

                        // 发送数据
                        ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                            GameNetPacketData_INFO::headSize + PT_SKILL_C2M_PLAYERCHARACTER_END_INJECT_DATA_INFO::dataSize );
                    }
                }
            }

		}
		
	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendPlayCharacterEndInjectSkillPacketToPackBuffer(CSkillObject* skillObject)
	{
		CPlayerCharacterEntity* playerCharacterEntity = CSceneManager::getInstance().getPlayerCharacterEntity(skillObject->getOwnerID());
		if(!playerCharacterEntity)
		{         
			return;
		}

		PT_SKILL_C2M_PLAYERCHARACTER_END_INJECT_DATA sendData;
		// 填充逻辑包
		sendData.characterIndex = playerCharacterEntity->getID();
		sendData.skillId = skillObject->getSkillInfo()->skillId;

		NetPacketPackManager::getInstance().addPacketToBuff(PT_PLAYERCHARACTER_INJECT_END, GOT_PLAYERCHARACTER, (Char8*)&sendData, playerCharacterEntity->getID());
	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendSkillPlayerCharacterCollisionAffectPlayerCharacterPacket(GameObjectIndexIdInSceneType injectCharacterIndex, GameObjectIndexIdInSceneType affectCharacterIndex, UInt affectTotal, IdType skillId)
	{
            // 转换逻辑包
            PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA sendData;
            // 填充逻辑包
            sendData.injectCharacterIndex = injectCharacterIndex;
            sendData.affectCharacterIndex = affectCharacterIndex;
            sendData.affectTotal = affectTotal;
            sendData.skillId= skillId;

			NetPacketPackManager::getInstance().addPacketToBuff(PT_PLAYERCHARACTER_AFFECT_COLLISION_PLAYERCHARACTER, GOT_PLAYERCHARACTER, (Char8*)&sendData, affectCharacterIndex);
	
    }

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendSkillPlayerCharacterCollisionAffectTroopPacket(GameObjectIndexIdInSceneType injectCharacterIndex, GameObjectIndexIdInSceneType affectTroopIndex, UInt affectSoldierIndex, UInt affectTotal, IdType skillId)
	{
        // 转换逻辑包
        PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_TROOP_DATA sendData;

        // 填充逻辑包
        sendData.injectCharacterIndex = injectCharacterIndex;
        sendData.affectTroopIndex = affectTroopIndex;
        sendData.affectSoldierIndex = affectSoldierIndex;
        sendData.affectTotal = affectTotal;
        sendData.skillId= skillId;

		NetPacketPackManager::getInstance().addPacketToBuff(PT_PLAYERCHARACTER_AFFECT_COLLISION_TROOP, GOT_PLAYERCHARACTER, (Char8*)&sendData, affectTroopIndex);
	
    }

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendSkillPlayerCharacterCollisionAffectBuildingPacket(GameObjectIndexIdInSceneType injectCharacterIndex, GameObjectIndexIdInSceneType affectBuildingIndex, UInt affectTotal, IdType skillId, IdType mapId)
	{

        // 转换逻辑包
        PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_BUILDING_DATA sendData;
        // 填充逻辑包
        sendData.injectCharacterIndex = injectCharacterIndex;
        sendData.affectBuildingIndex = affectBuildingIndex;
        sendData.affectTotal = affectTotal;
        sendData.skillId= skillId;

		NetPacketPackManager::getInstance().addPacketToBuff(PT_PLAYERCHARACTER_AFFECT_COLLISION_BUILDING, GOT_PLAYERCHARACTER, (Char8*)&sendData, affectBuildingIndex);
    }

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendSkillPlayerCharacterCollisionAffectMonsterPacket(GameObjectIndexIdInSceneType injectCharacterIndex, GameObjectIndexIdInSceneType affectMonsterIndex, UInt affectTotal, IdType skillId, Vec3 affectPos)
	{
		// 转换逻辑包
		PT_SKILL_C2M_PLAYERCHARACTER_AFFECT_COLLISION_MONSTER_DATA sendData;
		// 填充逻辑包
		sendData.injectCharacterIndex = injectCharacterIndex;
		sendData.affectMonsterIndex = affectMonsterIndex;
		sendData.affectTotal = affectTotal;
		sendData.skillId= skillId;
		sendData.affectPos = ((NetVec2)affectPos).getData();

		NetPacketPackManager::getInstance().addPacketToBuff(PT_PLAYERCHARACTER_AFFECT_COLLISION_MONSTER, GOT_PLAYERCHARACTER, (Char8*)&sendData, affectMonsterIndex);
	}


	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendSkillTroopCollisionAffectPlayerCharacterPacket(GameObjectIndexIdInSceneType injectTroopIndex, UInt injectSoldierIndex, GameObjectIndexIdInSceneType affectCharacterIndex, UInt affectTotal, IdType skillId)
	{
        // 转换逻辑包
        PT_SKILL_C2M_TROOP_AFFECT_COLLISION_PLAYERCHARACTER_DATA sendData;
        // 填充逻辑包
        sendData.injectTroopIndex = injectTroopIndex;
        sendData.affectCharacterIndex = affectCharacterIndex;
        sendData.affectTotal = affectTotal;
        sendData.skillId= skillId;
	
		NetPacketPackManager::getInstance().addPacketToBuff(PT_TROOP_AFFECT_COLLISION_PLAYERCHARACTER, GOT_TROOP, (Char8*)&sendData, affectCharacterIndex);
    }

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendSkillTroopCollisionAffectTroopPacket(GameObjectIndexIdInSceneType injectTroopIndex, UInt injectSoldierIndex, GameObjectIndexIdInSceneType affectTroopIndex, UInt affectSoldierIndex, UInt affectTotal, IdType skillId)
	{
        // 转换逻辑包
        PT_SKILL_C2M_TROOP_AFFECT_COLLISION_TROOP_DATA sendData;
        // 填充逻辑包
        sendData.injectTroopIndex = injectTroopIndex;
        sendData.affectTroopIndex = affectTroopIndex;
        sendData.affectTotal = affectTotal;
        sendData.skillId= skillId;
	
		NetPacketPackManager::getInstance().addPacketToBuff(PT_TROOP_AFFECT_COLLISION_TROOP, GOT_TROOP, (Char8*)&sendData, affectTroopIndex);
    }

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendSkillTroopCollisionAffectBuildingPacket(GameObjectIndexIdInSceneType injectTroopIndex, UInt injectSoldierIndex, GameObjectIndexIdInSceneType affectBuildingIndex, UInt affectTotal, IdType skillId, IdType mapId)
	{
        // 转换逻辑包
        PT_SKILL_C2M_TROOP_AFFECT_COLLISION_BUILDING_DATA sendData;
        // 填充逻辑包
        sendData.injectTroopIndex = injectTroopIndex;
        sendData.affectBuildingIndex = affectBuildingIndex;
        sendData.affectTotal = affectTotal;
        sendData.skillId= skillId;
	
		NetPacketPackManager::getInstance().addPacketToBuff(PT_TROOP_AFFECT_COLLISION_BUILDING, GOT_TROOP, (Char8*)&sendData, affectBuildingIndex);
    }

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendSkillTroopCollisionAffectMonsterPacket(GameObjectIndexIdInSceneType injectTroopIndex, UInt injectSoldierIndex, IdType affectMonsterIndex, UInt affectTotal, IdType skillId)
	{
		// 转换逻辑包
		PT_SKILL_C2M_TROOP_AFFECT_COLLISION_MONSTER_DATA sendData;
		// 填充逻辑包
		sendData.injectTroopIndex = injectTroopIndex;
		sendData.affectMonsterIndex = affectMonsterIndex;
		sendData.affectTotal = affectTotal;
		sendData.skillId= skillId;

		NetPacketPackManager::getInstance().addPacketToBuff(PT_TROOP_AFFECT_COLLISION_MONSTER, GOT_TROOP, (Char8*)&sendData, affectMonsterIndex);
	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendSkillBuildingCollisionAffectPlayerCharacterPacket(GameObjectIndexIdInSceneType injectBuildingIndex, GameObjectIndexIdInSceneType affectCharacterIndex, UInt affectTotal, IdType skillId)
	{
        // 转换逻辑包
        PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_PLAYERCHARACTER_DATA sendData;
        // 填充逻辑包
        sendData.injectBuildingIndex = injectBuildingIndex;
        sendData.affectCharacterIndex = affectCharacterIndex;
        sendData.affectTotal = affectTotal;
        sendData.skillId= skillId;

		NetPacketPackManager::getInstance().addPacketToBuff(PT_TROOP_AFFECT_COLLISION_MONSTER, GOT_TROOP, (Char8*)&sendData, affectCharacterIndex);
    }

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendSkillBuildingCollisionAffectTroopPacket(GameObjectIndexIdInSceneType injectBuildingIndex, GameObjectIndexIdInSceneType affectTroopIndex, UInt affectSoldierIndex, UInt affectTotal, IdType skillId)
	{
        // 转换逻辑包
        PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_TROOP_DATA sendData;
        // 填充逻辑包
        sendData.injectBuildingIndex = injectBuildingIndex;
        sendData.affectTroopIndex = affectTroopIndex;
        sendData.affectTotal = affectTotal;
        sendData.skillId= skillId;

		NetPacketPackManager::getInstance().addPacketToBuff(PT_BUILDING_AFFECT_COLLISION_TROOP, GOT_TROOP, (Char8*)&sendData, affectTroopIndex);
	
    }

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendSkillBuildingCollisionAffectBuildingPacket(GameObjectIndexIdInSceneType injectBuildingIndex, GameObjectIndexIdInSceneType affectBuildingIndex, UInt affectTotal, IdType skillId, IdType mapId)
	{
        // 转换逻辑包
        PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_BUILDING_DATA sendData;
        // 填充逻辑包
        sendData.injectBuildingIndex = injectBuildingIndex;
        sendData.affectBuildingIndex = affectBuildingIndex;
        sendData.affectTotal = affectTotal;
        sendData.skillId= skillId;

		NetPacketPackManager::getInstance().addPacketToBuff(PT_BUILDING_AFFECT_COLLISION_BUILDING, GOT_TROOP, (Char8*)&sendData, affectBuildingIndex);

    }

	void SkillNetPacketProcesser::sendSkillBuildingCollisionAffectMonsterPacket(GameObjectIndexIdInSceneType injectBuildingIndex, GameObjectIndexIdInSceneType affectMonsterIndex, UInt affectTotal, IdType skillId, IdType mapId)
	{
		// 转换逻辑包
		PT_SKILL_C2M_BUILDING_AFFECT_COLLISION_MONSTER_DATA sendData;
		// 填充逻辑包
		sendData.injectBuildingIndex = injectBuildingIndex;
		sendData.affectMonsterIndex = affectMonsterIndex;
		sendData.affectTotal = affectTotal;
		sendData.skillId= skillId;

		NetPacketPackManager::getInstance().addPacketToBuff(PT_BUILDING_AFFECT_COLLISION_MONSTER, GOT_TROOP, (Char8*)&sendData, affectMonsterIndex);

	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendSkillMonsterCollisionAffectPlayerCharacterPacket(GameObjectIndexIdInSceneType injectMonsterIndex, GameObjectIndexIdInSceneType affectCharacterIndex, UInt affectTotal, IdType skillId)
	{
		// 转换逻辑包
		PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_PLAYERCHARACTER_DATA sendData;
		// 填充逻辑包
		sendData.injectMonsterIndex = injectMonsterIndex;
		sendData.affectCharacterIndex = affectCharacterIndex;
		sendData.affectTotal = affectTotal;
		sendData.skillId= skillId;

		NetPacketPackManager::getInstance().addPacketToBuff(PT_MONSTER_AFFECT_COLLISION_PLAYERCHARACTER, GOT_MONSTER, (Char8*)&sendData, injectMonsterIndex);

	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendSkillMonsterCollisionAffectTroopPacket(GameObjectIndexIdInSceneType injectMonsterIndex, GameObjectIndexIdInSceneType affectTroopIndex, UInt affectSoldierIndex, UInt affectTotal, IdType skillId)
	{
		// 转换逻辑包
		PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_TROOP_DATA sendData;
		// 填充逻辑包
		sendData.injectMonsterIndex = injectMonsterIndex;
		sendData.affectTroopIndex = affectTroopIndex;
		sendData.affectTotal = affectTotal;
		sendData.skillId= skillId;

		NetPacketPackManager::getInstance().addPacketToBuff(PT_MONSTER_AFFECT_COLLISION_TROOP, GOT_MONSTER, (Char8*)&sendData, affectTroopIndex);

	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendSkillMonsterCollisionAffectBuildingPacket(GameObjectIndexIdInSceneType injectMonsterIndex, GameObjectIndexIdInSceneType affectBuildingIndex, UInt affectTotal, IdType skillId, IdType mapId)
	{
		// 转换逻辑包
		PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_BUILDING_DATA sendData;
		// 填充逻辑包
		sendData.injectMonsterIndex = injectMonsterIndex;
		sendData.affectBuildingIndex = affectBuildingIndex;
		sendData.affectTotal = affectTotal;
		sendData.skillId= skillId;

		NetPacketPackManager::getInstance().addPacketToBuff(PT_MONSTER_AFFECT_COLLISION_BUILDING, GOT_MONSTER, (Char8*)&sendData, affectBuildingIndex);

	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendSkillMonsterCollisionAffectMonsterPacket(GameObjectIndexIdInSceneType injectMonsterIndex, GameObjectIndexIdInSceneType affectMonsterIndex, UInt affectTotal, IdType skillId)
	{
		// 转换逻辑包
		PT_SKILL_C2M_MONSTER_AFFECT_COLLISION_MONSTER_DATA sendData;
		// 填充逻辑包
		sendData.injectMonsterIndex = injectMonsterIndex;
		sendData.affectMonsterIndex = affectMonsterIndex;
		sendData.affectTotal = affectTotal;
		sendData.skillId= skillId;

		NetPacketPackManager::getInstance().addPacketToBuff(PT_MONSTER_AFFECT_COLLISION_MONSTER, GOT_MONSTER, (Char8*)&sendData, affectMonsterIndex);

	}


	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendSkillCharacterCollisionAffectCharacter(GAMEOBJ_TYPE injectCharacterType, CCharacterSceneEntity* injectCharacter, GAMEOBJ_TYPE affectCharacterType, CCharacterSceneEntity* affectCharacter, UInt affectTotal, IdType skillId, IdType mapId, Vec3 affectPos)
	{
		if(affectCharacterType == GOT_PLAYERCHARACTER)
		{

			if(injectCharacterType == GOT_PLAYERCHARACTER)
			{
				SkillNetPacketProcesser::getInstance().sendSkillPlayerCharacterCollisionAffectPlayerCharacterPacket( injectCharacter->getID(), affectCharacter->getID(), 1, skillId );
			}
			else if(injectCharacterType == GOT_SOLDIER)
			{
				CTroopSoldierEntity* troopSoldierEntity = (CTroopSoldierEntity*)injectCharacter;
				SkillNetPacketProcesser::getInstance().sendSkillTroopCollisionAffectPlayerCharacterPacket( troopSoldierEntity->getTroopEntity()->getID(), injectCharacter->getID(), affectCharacter->getID(), 1, skillId );
			}
			else if(injectCharacterType == GOT_MONSTER)
			{
				SkillNetPacketProcesser::getInstance().sendSkillMonsterCollisionAffectPlayerCharacterPacket( injectCharacter->getID(), affectCharacter->getID(), 1, skillId );
			}
			else if(injectCharacterType == GOT_BUILDING)
			{
				SkillNetPacketProcesser::getInstance().sendSkillBuildingCollisionAffectPlayerCharacterPacket( injectCharacter->getID(), affectCharacter->getID(), 1, skillId );
			}
		}
		else if(affectCharacterType == GOT_MONSTER)
		{

			if(injectCharacterType == GOT_PLAYERCHARACTER)
			{
				SkillNetPacketProcesser::getInstance().sendSkillPlayerCharacterCollisionAffectMonsterPacket( injectCharacter->getID(), affectCharacter->getID(), 1, skillId, affectPos );
			}
			else if(injectCharacterType == GOT_SOLDIER)
			{
				CTroopSoldierEntity* troopSoldierEntity = (CTroopSoldierEntity*)injectCharacter;
				SkillNetPacketProcesser::getInstance().sendSkillTroopCollisionAffectMonsterPacket( troopSoldierEntity->getTroopEntity()->getID(), injectCharacter->getID(), affectCharacter->getID(), 1, skillId );
			}
			else if(injectCharacterType == GOT_MONSTER)
			{
				SkillNetPacketProcesser::getInstance().sendSkillMonsterCollisionAffectMonsterPacket( injectCharacter->getID(), affectCharacter->getID(), 1, skillId );
			}
			else if(injectCharacterType == GOT_BUILDING)
			{
				SkillNetPacketProcesser::getInstance().sendSkillBuildingCollisionAffectPlayerCharacterPacket( injectCharacter->getID(), affectCharacter->getID(), 1, skillId );
			}
		}
		else if(affectCharacterType == GOT_SOLDIER)
		{
			CTroopSoldierEntity* affectTroopSoldierEntity = (CTroopSoldierEntity*)affectCharacter;
			if(injectCharacterType == GOT_PLAYERCHARACTER)
			{
				SkillNetPacketProcesser::getInstance().sendSkillPlayerCharacterCollisionAffectTroopPacket( injectCharacter->getID(), affectTroopSoldierEntity->getTroopEntity()->getID(), affectCharacter->getID(), 1, skillId );
			}
			else if(injectCharacterType == GOT_SOLDIER)
			{
				CTroopSoldierEntity* injectTroopSoldierEntity = (CTroopSoldierEntity*)injectCharacter;
				SkillNetPacketProcesser::getInstance().sendSkillTroopCollisionAffectTroopPacket( injectTroopSoldierEntity->getTroopEntity()->getID(), injectCharacter->getID(), affectTroopSoldierEntity->getTroopEntity()->getID(), affectCharacter->getID(), 1, skillId );
			}
			else if(injectCharacterType == GOT_MONSTER)
			{
				SkillNetPacketProcesser::getInstance().sendSkillMonsterCollisionAffectTroopPacket( injectCharacter->getID(), affectTroopSoldierEntity->getTroopEntity()->getID(), affectCharacter->getID(), 1, skillId );
			}
			else if(injectCharacterType == GOT_BUILDING)
			{
				SkillNetPacketProcesser::getInstance().sendSkillBuildingCollisionAffectTroopPacket( injectCharacter->getID(), affectTroopSoldierEntity->getTroopEntity()->getID(), affectCharacter->getID(), 1, skillId );
			}
		}
		else if(affectCharacterType == GOT_TROOP)
		{
			CTroopEntity* affectTroopEntity = (CTroopEntity*)affectCharacter;
			if(injectCharacterType == GOT_PLAYERCHARACTER)
			{
				SkillNetPacketProcesser::getInstance().sendSkillPlayerCharacterCollisionAffectTroopPacket( injectCharacter->getID(), affectTroopEntity->getID(), 0, 1, skillId );
			}
			else if(injectCharacterType == GOT_TROOP)
			{
				CTroopEntity* injectTroopEntity = (CTroopEntity*)injectCharacter;
				SkillNetPacketProcesser::getInstance().sendSkillTroopCollisionAffectTroopPacket( injectTroopEntity->getID(), 0, affectTroopEntity->getID(), 0, 1, skillId );
			}
			else if(injectCharacterType == GOT_MONSTER)
			{
				SkillNetPacketProcesser::getInstance().sendSkillMonsterCollisionAffectTroopPacket( injectCharacter->getID(), affectTroopEntity->getID(), 0, 1, skillId );
			}
			else if(injectCharacterType == GOT_BUILDING)
			{
				SkillNetPacketProcesser::getInstance().sendSkillBuildingCollisionAffectTroopPacket( injectCharacter->getID(), affectTroopEntity->getID(), 0, 1, skillId );
			}
		}
		else if(affectCharacterType == GOT_BUILDING)
		{
			if(injectCharacterType == GOT_PLAYERCHARACTER)
			{
				SkillNetPacketProcesser::getInstance().sendSkillPlayerCharacterCollisionAffectBuildingPacket( injectCharacter->getID(), affectCharacter->getID(), 1, skillId ,mapId );
			}
			else if(injectCharacterType == GOT_SOLDIER)
			{
				CTroopSoldierEntity* injectTroopSoldierEntity = (CTroopSoldierEntity*)injectCharacter;
				SkillNetPacketProcesser::getInstance().sendSkillTroopCollisionAffectBuildingPacket(injectTroopSoldierEntity->getTroopEntity()->getID(), injectCharacter->getID(), affectCharacter->getID(), 1, skillId, mapId );
			}
			else if(injectCharacterType == GOT_BUILDING)
			{
				SkillNetPacketProcesser::getInstance().sendSkillBuildingCollisionAffectBuildingPacket( injectCharacter->getID(), affectCharacter->getID(), 1, skillId, mapId );
			}

		}
	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::onRecvLearnSkillResult( PT_SKILL_F2C_LEARN_RESULT_DATA* data )
	{
		//TODO:
		//通过本家族找到PlayerCharacter并赋值
		//CClan::getPlayerCharacter()
		//getSkillManager()->addSkill(id)

		//不要赋值给Scene中的PlayerCharacterEntity
	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::onRecvPlayCharacterClantSkillRequire( PT_SKILL_M2C_PLAYERCHARACTER_CLANT_DATA* data )
	{
		//FUNDETECTION(__MG_FUNC__);
		CPlayerCharacterEntity* playerCharacterEntity = CSceneManager::getInstance().getPlayerCharacterEntity( data->characterIndex );
		if ( playerCharacterEntity )
		{
			playerCharacterEntity->stopMoveToAction();

            SkillInfo* skillInfo  = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(data->skillId);
			if(!skillInfo)
			{
				return;
			}

			CSkillObject* skillObject = (CSkillObject*)playerCharacterEntity->getSkillUseManager()->prepareUseSkill(data->skillId);
			if(!skillObject)
			{	
				return;
			}
			
			Flt y = playerCharacterEntity->getPos(false).y;
			/*playerCharacterEntity->setPos( Vec3( data->characterPos.x , y , data->characterPos.z) );
			playerCharacterEntity->setDir( Vec3( data->characterDir.x , 0 , data->characterDir.z) );*/
			playerCharacterEntity->setPos( (NetVec2)data->characterPos );
			playerCharacterEntity->getEntity()->getSceneNode()->stickTerrain();
			playerCharacterEntity->setDir( (NetVec2)data->characterDir );

			CCSEntityClantSkillAcion* clantSkillAcion = CActionManager::getInstance().createCCSEntityClantSkillAcion(skillObject);
			playerCharacterEntity->getActionStateManager().push(clantSkillAcion);
		}
	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::onRecvPlayCharacterInjectEmitterSkillRequire( PT_SKILL_M2C_PLAYERCHARACTER_INJECT_EMITTER_DATA* data )
	{
		//FUNDETECTION(__MG_FUNC__);
		CPlayerCharacterEntity* playerCharacterEntity = CSceneManager::getInstance().getPlayerCharacterEntity( data->characterIndex );
		if(!playerCharacterEntity)
		{
			return;
		}

		SkillInfo* skillInfo  = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(data->skillId);
		if(!skillInfo)
		{
			return;
		}

		CSkillObject* skillObject = (CSkillObject*)playerCharacterEntity->getSkillUseManager()->prepareUseSkill(data->skillId);
		if(!skillObject)
		{
			return;
		}

		InitiativeSkillBasicInfo* initiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)skillObject->getSkillInfo()->skillInfo;
		if(!initiativeSkillBasicInfo)
		{
			return;
		}

		if(playerCharacterEntity->getDynamicData()->belongPlayerID == CPlayer::getInstance().getAccountID())
		{
			playerCharacterEntity->getSkillUseManager()->addCD(skillInfo, CSkillUseManager::AACSCT_OWNER);
		}

		playerCharacterEntity->stopMoveToAction();
		//playerCharacterEntity->setDir(Vec3(data->injectDir.x,0,data->injectDir.z));
		playerCharacterEntity->setDir((NetVec2)data->injectDir);

		CCSEntityInjectSkillAcion* injectSkillAcion = CActionManager::getInstance().createCCSEntityInjectSkillAcion(skillObject);
		playerCharacterEntity->getActionStateManager().push(injectSkillAcion);
	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::onRecvPlayCharacterInjectPointSkillRequire( PT_SKILL_M2C_PLAYERCHARACTER_INJECT_POINT_DATA* data )
	{
		//FUNDETECTION(__MG_FUNC__);
		CPlayerCharacterEntity* playerCharacterEntity = CSceneManager::getInstance().getPlayerCharacterEntity( data->characterIndex );
		if(!playerCharacterEntity)
		{
			return;
		}

		SkillInfo* skillInfo  = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(data->skillId);
		if(!skillInfo)
		{
			return;
		}

		CSkillObject* skillObject = (CSkillObject*)playerCharacterEntity->getSkillUseManager()->prepareUseSkill(data->skillId);
		if(!skillObject)
		{
			return;
		}

		//skillObject->setTargetPosition(Vec3(data->targetPos.x, 0, data->targetPos.z));
		skillObject->setTargetPosition( (NetVec2)data->targetPos);
		InitiativeSkillBasicInfo* initiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)skillObject->getSkillInfo()->skillInfo;
		if(!initiativeSkillBasicInfo)
		{
			return;
		}

		if(playerCharacterEntity->getDynamicData()->belongPlayerID == CPlayer::getInstance().getAccountID())
		{
			playerCharacterEntity->getSkillUseManager()->addCD(skillInfo, CSkillUseManager::AACSCT_OWNER);
		}

		/*Vec3 dir = Vec3(data->dir.x, 0, data->dir.z);*/
		Vec3 dir = (NetVec2)data->dir;
		
		if(COMPARE_FLOAT(dir.x,0.0f) && COMPARE_FLOAT(dir.z,0.0f))
		{
			//dir = Vec3(data->targetPos.getX(), 0, data->targetPos.z) - playerCharacterEntity->getPos();
			dir = (Vec3)((NetVec2)data->targetPos) - playerCharacterEntity->getPos();
			dir.normalise();
		}

		playerCharacterEntity->stopMoveToAction();
		playerCharacterEntity->setDir(dir);
		//skillObject->setTargetPosition(Vec3(data->targetPos.x, 0, data->targetPos.z));
		skillObject->setTargetPosition((NetVec2)data->targetPos);

		CCSEntityInjectSkillAcion* injectSkillAcion = CActionManager::getInstance().createCCSEntityInjectSkillAcion(skillObject);
		playerCharacterEntity->getActionStateManager().push(injectSkillAcion);
	}
	
	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::onRecvPlayCharacterInjectObjectSkillRequire( PT_SKILL_M2C_PLAYERCHARACTER_INJECT_OBJECT_DATA* data )
	{
		//FUNDETECTION(__MG_FUNC__);
		CPlayerCharacterEntity* playerCharacterEntity = CSceneManager::getInstance().getPlayerCharacterEntity( data->characterIndex );
		if(!playerCharacterEntity)
		{
			return;
		}

		CCharacterSceneEntity* targetCharacter = CSceneManager::getInstance().getCharacterSceneEntity((GAMEOBJ_TYPE)data->objectType, data->objectId, data->objectIndex);
		if(!targetCharacter)
		{
			return;
		}

        SkillInfo* skillInfo  = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(data->skillId);
		if(!skillInfo)
		{
			return;
		}

        CSkillObject* skillObject = (CSkillObject*)playerCharacterEntity->getSkillUseManager()->prepareUseSkill(data->skillId);
        if(!skillObject)
        {
            return;
        }

        skillObject->setTargetObject((GAMEOBJ_TYPE)data->objectType, data->objectId, data->objectIndex);

		InitiativeSkillBasicInfo* initiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)skillObject->getSkillInfo()->skillInfo;
		if(!initiativeSkillBasicInfo)
		{
			return;
		}

		if(playerCharacterEntity->getDynamicData()->belongPlayerID == CPlayer::getInstance().getAccountID())
		{
			playerCharacterEntity->getSkillUseManager()->addCD(skillInfo, CSkillUseManager::AACSCT_OWNER);
		}

		Vec3 dir = targetCharacter->getPos() - playerCharacterEntity->getPos();
		dir.normalise();
		playerCharacterEntity->setDir(dir);
		playerCharacterEntity->stopMoveToAction();

		skillObject->setTargetObject((GAMEOBJ_TYPE)data->objectType, data->objectId, data->objectIndex );

		CCSEntityInjectSkillAcion* injectSkillAcion = CActionManager::getInstance().createCCSEntityInjectSkillAcion(skillObject);
		playerCharacterEntity->getActionStateManager().push(injectSkillAcion);
	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::onRecvPlayCharacterInjectEndSkillRequire( PT_SKILL_M2C_PLAYERCHARACTER_END_INJECT_DATA* data )
	{
		CPlayerCharacterEntity* entity = CSceneManager::getInstance().getPlayerCharacterEntity( data->characterIndex );
		CSkillObject* skillObject = (CSkillObject*)entity->getSkillUseManager()->getPreparedUseSkill();
		if(!skillObject || skillObject->getSkillInfo()->skillId != data->skillId)
		{
			return;
		}

		skillObject->stopUse();
	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::onRecvMonsterClantSkillRequire( PT_SKILL_M2C_MONSTER_CLANT_DATA* data )
	{
		//FUNDETECTION(__MG_FUNC__);
		CMonsterEntity* monsterEntity = CSceneManager::getInstance().getMonsterEntity( data->monsterIndex );
		if(!monsterEntity)
		{
			return;
		}

		monsterEntity->stopMoveToAction();

		SkillInfo* skillInfo  = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(data->skillId);
		if(!skillInfo)
		{
			return;
		}

		CSkillObject* skillObject = (CSkillObject*)monsterEntity->getSkillUseManager()->prepareUseSkill(data->skillId);
		if(!skillObject)
		{
			return;
		}

		/*monsterEntity->setPos( Vec3( data->characterPos.x , 0 , data->characterPos.z) );
		monsterEntity->setDir( Vec3( data->characterDir.x , 0 , data->characterDir.z) );*/
		monsterEntity->setPos( (NetVec2)data->characterPos );
		monsterEntity->setDir( (NetVec2)data->characterDir );

		CCSEntityClantSkillAcion* clantSkillAcion = CActionManager::getInstance().createCCSEntityClantSkillAcion(skillObject);
		monsterEntity->getActionStateManager().push(clantSkillAcion);
	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::onRecvMonsterInjectEmitterSkillRequire( PT_SKILL_M2C_MONSTER_INJECT_EMITTER_DATA* data )
	{
		CMonsterEntity* monsterEntity = CSceneManager::getInstance().getMonsterEntity( data->monsterIndex );
		if(!monsterEntity)
		{
			return;
		}

		SkillInfo* skillInfo  = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(data->skillId);
		if(!skillInfo)
		{
			return;
		}

		CSkillObject* skillObject = (CSkillObject*)monsterEntity->getSkillUseManager()->prepareUseSkill(data->skillId);
		if(!skillObject)
		{
			return;
		}

		InitiativeSkillBasicInfo* initiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)skillObject->getSkillInfo()->skillInfo;
		if(!initiativeSkillBasicInfo)
		{
			return;
		}

		//if(monsterEntity->getDynamicData()->belongPlayerID == CPlayer::getInstance().getAccountID())
		//{
		//	CCDManager::getInstance().addCD(CD_MASTER_TYPE_CHARACTER, data->monsterId, initiativeSkillBasicInfo->ownerTimepieceId, initiativeSkillBasicInfo->ownerTimepieceDelay);
		//}

		monsterEntity->stopMoveToAction();
		/*monsterEntity->setDir(Vec3(data->injectDir.x,0,data->injectDir.z));*/
		monsterEntity->setDir((NetVec2)data->injectDir);

		CCSEntityInjectSkillAcion* injectSkillAcion = CActionManager::getInstance().createCCSEntityInjectSkillAcion(skillObject);
		monsterEntity->getActionStateManager().push(injectSkillAcion);
	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::onRecvMonsterInjectPointSkillRequire( PT_SKILL_M2C_MONSTER_INJECT_POINT_DATA* data )
	{
		CMonsterEntity* monsterEntity = CSceneManager::getInstance().getMonsterEntity( data->monsterIndex );
		if(!monsterEntity)
		{
			return;
		}

		SkillInfo* skillInfo  = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(data->skillId);
		if(!skillInfo)
		{
			return;
		}

		CSkillObject* skillObject = (CSkillObject*)monsterEntity->getSkillUseManager()->prepareUseSkill(data->skillId);
		if(!skillObject)
		{
			return;
		}

		/*skillObject->setTargetPosition(Vec3(data->targetPos.x, 0, data->targetPos.z));*/
		skillObject->setTargetPosition((NetVec2)data->targetPos);

		InitiativeSkillBasicInfo* initiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)skillObject->getSkillInfo()->skillInfo;
		if(!initiativeSkillBasicInfo)
		{
			return;
		}

		//if(monsterEntity->getDynamicData()->belongPlayerID == CPlayer::getInstance().getAccountID())
		//{
		//	CCDManager::getInstance().addCD(CD_MASTER_TYPE_CHARACTER, data->characterId, initiativeSkillBasicInfo->ownerTimepieceId, initiativeSkillBasicInfo->ownerTimepieceDelay);
		//}

		monsterEntity->stopMoveToAction();
		/*skillObject->setTargetPosition(Vec3(data->targetPos.x, 0, data->targetPos.z));*/
		skillObject->setTargetPosition((NetVec2)data->targetPos);

		CCSEntityInjectSkillAcion* injectSkillAcion = CActionManager::getInstance().createCCSEntityInjectSkillAcion(skillObject);
		monsterEntity->getActionStateManager().push(injectSkillAcion);
	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::onRecvMonsterInjectObjectSkillRequire( PT_SKILL_M2C_MONSTER_INJECT_OBJECT_DATA* data )
	{
		//FUNDETECTION(__MG_FUNC__);
		CMonsterEntity* monsterEntity = CSceneManager::getInstance().getMonsterEntity( data->monsterIndex );
		if(!monsterEntity)
		{
			return;
		}

		CCharacterSceneEntity* targetCharacter = CSceneManager::getInstance().getCharacterSceneEntity((GAMEOBJ_TYPE)data->objectType, data->objectId, data->objectIndex);
		if(!targetCharacter)
		{
			return;
		}

		SkillInfo* skillInfo  = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(data->skillId);
		if(!skillInfo)
		{
			return;
		}

		CSkillObject* skillObject = (CSkillObject*)monsterEntity->getSkillUseManager()->prepareUseSkill(data->skillId);
		if(!skillObject)
		{
			return;
		}

		skillObject->setTargetObject((GAMEOBJ_TYPE)data->objectType, data->objectId, data->objectIndex);

		InitiativeSkillBasicInfo* initiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)skillObject->getSkillInfo()->skillInfo;
		if(!initiativeSkillBasicInfo)
		{
			return;
		}

	/*	if(monsterEntity->getDynamicData()->belongPlayerID == CPlayer::getInstance().getAccountID())
		{
			CCDManager::getInstance().addCD(CD_MASTER_TYPE_CHARACTER, data->characterId, initiativeSkillBasicInfo->ownerTimepieceId, initiativeSkillBasicInfo->ownerTimepieceDelay);
		}*/

		Vec3 dir = targetCharacter->getPos() - monsterEntity->getPos();
		dir.normalise();
		monsterEntity->setDir(dir);
		monsterEntity->stopMoveToAction();
		skillObject->setTargetObject((GAMEOBJ_TYPE)data->objectType, data->objectId, data->objectIndex );

		CCSEntityInjectSkillAcion* injectSkillAcion = CActionManager::getInstance().createCCSEntityInjectSkillAcion(skillObject);
		monsterEntity->getActionStateManager().push(injectSkillAcion);
	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::onRecvMonsterInjectEndSkillRequire( PT_SKILL_M2C_MONSTER_END_INJECT_DATA* data )
	{
		CMonsterEntity* entity = CSceneManager::getInstance().getMonsterEntity( data->monsterIndex );
		CSkillObject* skillObject = (CSkillObject*)entity->getSkillUseManager()->getPreparedUseSkill();
		if(!skillObject || skillObject->getSkillInfo()->skillId != data->skillId)
		{
			return;
		}

		skillObject->stopUse();
	}




	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::onRecvTroopClantSkillRequire( PT_SKILL_M2C_TROOP_CLANT_DATA* data )
	{
#if 0
		//FUNDETECTION(__MG_FUNC__);
		CTroopEntity* entity = CSceneManager::getInstance().getTroopEntity( data->troopGroupId, data->troopId );
		if ( entity )
		{
			//暂时不精确位置
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
	void SkillNetPacketProcesser::onRecvTroopInjectEmitterSkillRequire( PT_SKILL_M2C_TROOP_INJECT_EMITTER_DATA* data )
	{
		//FUNDETECTION(__MG_FUNC__);
		CTroopSoldierEntity* troopSoldier = CSceneManager::getInstance().getTroopSoldierEntity(data->troopIndex, data->soldierIndex);
		if(!troopSoldier)
		{
			return;
		}

		SkillInfo* skillInfo  = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(data->skillId);
		if(!skillInfo)
		{
			return;
		}

		CSkillObject* skillObject = (CSkillObject*)troopSoldier->getSkillUseManager()->prepareUseSkill(data->skillId);
		if(!skillObject)
		{
			return;
		}

		troopSoldier->stopMoveToAction();
		/*troopSoldier->setDir(Vec3(data->injectDir.x,0,data->injectDir.z));*/
		troopSoldier->setDir((NetVec2)data->injectDir);

		CCSEntityInjectSkillAcion* injectSkillAcion = CActionManager::getInstance().createCCSEntityInjectSkillAcion(skillObject);
		troopSoldier->getActionStateManager().push(injectSkillAcion);
	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::onRecvTroopInjectPointSkillRequire( PT_SKILL_M2C_TROOP_INJECT_POINT_DATA* data )
	{
		//FUNDETECTION(__MG_FUNC__);
		CTroopSoldierEntity* troopSoldier = CSceneManager::getInstance().getTroopSoldierEntity(data->troopIndex, data->soldierIndex);
		if(!troopSoldier)
		{
			return;
		}

		SkillInfo* skillInfo  = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(data->skillId);
		if(!skillInfo)
		{
			return;
		}

		CSkillObject* skillObject = (CSkillObject*)troopSoldier->getSkillUseManager()->prepareUseSkill(data->skillId);
		if(!skillObject)
		{
			return;
		}

		troopSoldier->stopMoveToAction();

		Vec3 tempVec3TargetPos;
		NetVec2 netVec2Pos(data->targetPos);
		tempVec3TargetPos = netVec2Pos;
		skillObject->setTargetPosition(tempVec3TargetPos);

		Vec3 tempVec3Dir;
		NetVec2 netVec2Dir(data->dir);
		tempVec3Dir = netVec2Dir;
		//skillObject->setTargetPosition(tempVec3TargetPos);

		/*if(data->dir.x != 0 || data->dir.z != 0)
		{
			troopSoldier->setDir(Vec3(data->dir.x, 0, data->dir.z));
		}*/
		if(COMPARE_FLOAT(tempVec3Dir.x,0.0f) || COMPARE_FLOAT(tempVec3Dir.z,0.0f) ) 
		{
			troopSoldier->setDir(tempVec3Dir);
		}
		else
		{
			Vec3 dir = tempVec3TargetPos - troopSoldier->getPos();
			dir.y = 0;
			dir.normalise();
			troopSoldier->setDir(dir);
		}

		CCSEntityInjectSkillAcion* injectSkillAcion = CActionManager::getInstance().createCCSEntityInjectSkillAcion(skillObject);
		troopSoldier->getActionStateManager().push(injectSkillAcion);	
	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::onRecvTroopInjectObjectSkillRequire( PT_SKILL_M2C_TROOP_INJECT_OBJECT_DATA* data )
	{
		//FUNDETECTION(__MG_FUNC__);
		CTroopSoldierEntity* troopSoldier = CSceneManager::getInstance().getTroopSoldierEntity(data->troopIndex, data->soldierIndex);
		if(!troopSoldier)
		{
			return;
		}

		CCharacterSceneEntity* targetCharacter = CSceneManager::getInstance().getCharacterSceneEntity((GAMEOBJ_TYPE)data->objectType, data->objectId, data->objectIndex);
		if(!targetCharacter)
		{
			return;
		}

		SkillInfo* skillInfo  = (SkillInfo*)SkillInfoList::getInstance().getSkillInfo(data->skillId);
		if(!skillInfo)
		{
			return;
		}

		CSkillObject* skillObject = (CSkillObject*)troopSoldier->getSkillUseManager()->prepareUseSkill(data->skillId);
		if(!skillObject)
		{
			return;
		}

		Vec3 dir = targetCharacter->getPos() - troopSoldier->getPos();
		dir.normalise();
		troopSoldier->stopMoveToAction();
		troopSoldier->setDir(dir);
		skillObject->setTargetObject((GAMEOBJ_TYPE)data->objectType, data->objectId, data->objectIndex );

		CCSEntityInjectSkillAcion* injectSkillAcion = CActionManager::getInstance().createCCSEntityInjectSkillAcion(skillObject);
		troopSoldier->getActionStateManager().push(injectSkillAcion);
	}

	void SkillNetPacketProcesser::onRecvTroopUseSkillRequire( PT_SKILL_S2C_TROOP_USE_SKILL_DATA* data )
	{
		CTroopEntity* troopEntity = CSceneManager::getInstance().getTroopEntity(data->troopIndex);
		if(!troopEntity)
		{
			return;
		}

		troopEntity->useSkill(data->skillId, data->targetType, data->targetId, (NetVec2)data->targetPos);
	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendTroopClantSkillRequestPacket(CSkillObject* skillObject)
	{
#if 0
		//
		//skillObject->getOwner();
        CCharacterSceneEntity* character = (CCharacterSceneEntity*)skillObject->getOwner();
        CTroopEntity* troopEntity = (CTroopEntity*)character;
        if(character && character->getIsRecvSkill())
        {
            // 获得一个发送【服务端】缓存
            GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

            // 转换成标准包格式
            GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getData();
            if ( packet )
            {
                // 设置标签
                packet->channel = GNPC_SKILL;
                packet->type    = PT_SKILL_C2F_TROOP_CLANT;

                // 转换逻辑包
                PT_SKILL_C2F_TROOP_CLANT_DATA* sendData = (PT_SKILL_C2F_TROOP_CLANT_DATA*)(packet->data);
                if ( sendData )
                {
                    // 填充逻辑包
                    sendData->troopGroupId = troopEntity->getParent()->getID();
                    sendData->troopId = character->getID();
                    sendData->skillId = skillObject->getBaseInfo()->id;
                    sendData->troopPos.x = character->getPos().x;
                    sendData->troopPos.z = character->getPos().z;
                    sendData->troopDir.x = character->getDir().x;
                    sendData->troopDir.z = character->getDir().z;

                    // 发送数据
                    ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                        GameNetPacketData_INFO::headSize + PT_SKILL_C2F_TROOP_CLANT_DATA_INFO::dataSize );

                    character->setIsRecvSkill(false);
                }
            }
        }
#endif
	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendTroopUseSkillRequestPacketToPackBuffer(CSkillObject* skillObject)
	{
		CTroopEntity* troopEntity = CSceneManager::getInstance().getTroopEntity(skillObject->getOwnerID());
		if(!troopEntity)
		{
			return;
		}

		PT_SKILL_C2S_TROOP_USE_SKILL_DATA sendData;
		sendData.troopIndex = troopEntity->getID();
		sendData.skillId = skillObject->getSkillInfo()->skillId;
		/*sendData.troopPos.x = troopSoldierEntity->getPos().x;
		sendData.troopPos.z = troopSoldierEntity->getPos().z;
		sendData.troopDir.x = troopSoldierEntity->getDir().x;
		sendData.troopDir.z = troopSoldierEntity->getDir().z;*/

		sendData.targetType = skillObject->getTargetObjectType();
		sendData.targetIndex = skillObject->getTargetObjectID();
		/*sendData.targetPos.x = skillObject->getTargetPosition().x;
		sendData.targetPos.z = skillObject->getTargetPosition().z;*/
		sendData.targetPos = ((NetVec2)skillObject->getTargetPosition()).getData();

		NetPacketPackManager::getInstance().addPacketToBuff(PT_TROOP_USE_SKILL, GOT_TROOP, (Char8*)&sendData, troopEntity->getID());
	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendTroopClantSkillRequestPacketToPackBuffer(CSkillObject* skillObject)
	{
		CTroopSoldierEntity* troopSoldierEntity = CSceneManager::getInstance().getTroopSoldierEntity(skillObject->getOwnerID(), skillObject->getTargetObjectIndex());
		if(!troopSoldierEntity)
		{
			return;
		}

		PT_SKILL_C2M_TROOP_CLANT_DATA sendData;
		sendData.troopIndex = troopSoldierEntity->getTroopEntity()->getID();
		sendData.soldierIndex = troopSoldierEntity->getID();
		sendData.skillId = skillObject->getSkillInfo()->skillId;
		/*sendData.troopPos.x = troopSoldierEntity->getPos().x;
		sendData.troopPos.z = troopSoldierEntity->getPos().z;
		sendData.troopDir.x = troopSoldierEntity->getDir().x;
		sendData.troopDir.z = troopSoldierEntity->getDir().z;*/
		sendData.troopPos = ((NetVec2)troopSoldierEntity->getPos()).getData();
		sendData.troopDir = ((NetVec2)troopSoldierEntity->getDir()).getData();

		sendData.targetType = skillObject->getTargetObjectType();
		sendData.targetId = skillObject->getTargetObjectID();
		sendData.targetIndex = skillObject->getTargetObjectIndex();
		/*sendData.targetPos.x = skillObject->getTargetPosition().x;
		sendData.targetPos.z = skillObject->getTargetPosition().z;*/
		sendData.targetPos = ((NetVec2)skillObject->getTargetPosition()).getData();
		
		 NetPacketPackManager::getInstance().addPacketToBuff(PT_TROOP_SOLDIER_CLANT, GOT_SOLDIER, (Char8*)&sendData, troopSoldierEntity->getTroopEntity()->getID(), troopSoldierEntity->getID());
	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendTroopInjectSkillRequestPacket(CSkillObject* skillObject)
	{
		//
		//skillObject->getOwner();
		//SkillOpType opType = skillObject->getBaseInfo()->opType;
		//Character* character = skillObject->getOwner();
		//CTroopEntity* troopEntity = (CTroopEntity*)character;

		//if(!character)
		//{
		//	return;
		//}

  //      // 获得一个发送【服务端】缓存
  //      GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

  //      // 转换成标准包格式
  //      GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getData();
  //      if ( packet )
  //      {
  //          // 设置标签
  //          packet->channel = GNPC_SKILL;

  //          SkillOpType opType = skillObject->getBaseInfo()->opType;
  //          switch(opType)
  //          {
  //          case SKILLOPTYPE_EMITTER:
  //              {
  //                  packet->type    = PT_SKILL_C2F_TROOP_INJECT_EMITTER;

  //                  // 转换逻辑包
  //                  PT_SKILL_C2F_TROOP_INJECT_EMITTER_DATA* sendData = (PT_SKILL_C2F_TROOP_INJECT_EMITTER_DATA*)(packet->data);
  //                  if ( sendData )
  //                  {
  //                      // 填充逻辑包
  //                      sendData->troopGroupId = troopEntity->getParent()->getID();
  //                      sendData->troopId = character->getID();
  //                      sendData->skillId = skillObject->getBaseInfo()->id;

  //                      // 发送数据
  //                      ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
  //                          GameNetPacketData_INFO::headSize + PT_SKILL_C2F_TROOP_INJECT_EMITTER_DATA_INFO::dataSize );

  //                  }
  //                  
  //              }
  //              break;

  //          case SKILLOPTYPE_POINT:
  //              {
  //                  packet->type    = PT_SKILL_C2F_TROOP_INJECT_POINT;

  //                  // 转换逻辑包
  //                  PT_SKILL_C2F_TROOP_INJECT_POINT_DATA* sendData = (PT_SKILL_C2F_TROOP_INJECT_POINT_DATA*)(packet->data);
  //                  if ( sendData )
  //                  {
  //                      // 填充逻辑包
  //                      sendData->troopGroupId = troopEntity->getParent()->getID();
  //                      sendData->troopId = character->getID();
  //                      sendData->skillId = skillObject->getBaseInfo()->id;
  //                      sendData->targetPos.x = skillObject->getTargetPosition().x;
  //                      sendData->targetPos.z = skillObject->getTargetPosition().z;

  //                      // 发送数据
  //                      ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
  //                          GameNetPacketData_INFO::headSize +PT_SKILL_C2F_TROOP_INJECT_POINT_DATA_INFO::dataSize );

  //                  }
  //                  
  //              }
  //              break;

  //          case SKILLOPTYPE_OBJECT:
  //              {
  //                  packet->type    = PT_SKILL_C2F_TROOP_INJECT_OBJECT;

  //                  // 转换逻辑包
  //                  PT_SKILL_C2F_TROOP_INJECT_OBJECT_DATA* sendData = (PT_SKILL_C2F_TROOP_INJECT_OBJECT_DATA*)(packet->data);
  //                  if ( sendData )
  //                  {
  //                      // 填充逻辑包
  //                      sendData->troopGroupId = troopEntity->getParent()->getID();
  //                      sendData->troopId = character->getID();
  //                      sendData->skillId = skillObject->getBaseInfo()->id;
  //                      sendData->objectId = skillObject->getTargetObjectID();
  //                      sendData->objectIndex = skillObject->getTargetObjectIndex();
  //                      sendData->objectType = skillObject->getTargetObjectType();

  //                      // 发送数据
  //                      ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
  //                          GameNetPacketData_INFO::headSize +PT_SKILL_C2F_TROOP_INJECT_OBJECT_DATA_INFO::dataSize );

  //                  } 
  //              }
  //              break;

  //          }

  //      }

	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendTroopInjectSkillRequestPacketToPackBuffer(CSkillObject* skillObject)
	{
		CTroopSoldierEntity* troopSoldierEntity = CSceneManager::getInstance().getTroopSoldierEntity(skillObject->getOwnerID(), skillObject->getOwnerIndex());
		if(!troopSoldierEntity)
		{
			return;
		}

		if(skillObject->getTargetObjectID() != 0)
		{
			CCharacterSceneEntity* targetCharacterEntity = CSceneManager::getInstance().getCharacterSceneEntity(skillObject->getTargetObjectType(), skillObject->getTargetObjectID(), skillObject->getTargetObjectIndex());
			if(!targetCharacterEntity)
			{
				return;
			}
		}

		switch(skillObject->getSkillInfo()->skillType)
		{
		case SKT_SHORTRANGEGENERAL:
		case SKT_LONGRANGEGENERAL:
		case SKT_LONGRANGEAUXILIARY:
			{
				PT_SKILL_C2M_TROOP_INJECT_OBJECT_DATA sendData;
				sendData.skillId = skillObject->getSkillInfo()->skillId;
				sendData.troopIndex = troopSoldierEntity->getTroopEntity()->getID();
				sendData.soldierId = troopSoldierEntity->getID();
				sendData.objectIndex = skillObject->getTargetObjectIndex();
				sendData.objectId = skillObject->getTargetObjectID();
				sendData.objectType = skillObject->getTargetObjectType();

				NetPacketPackManager::getInstance().addPacketToBuff(PT_TROOP_SOLDIER_INJECT_OBJECT, GOT_SOLDIER, (Char8*)&sendData, troopSoldierEntity->getTroopEntity()->getID(), troopSoldierEntity->getID());
			}
			break;
		case SKT_SINGLEEMITTER:
			{
				Vec3 dir = skillObject->getTargetPosition() - troopSoldierEntity->getPos();
				dir.normalise();

				PT_SKILL_C2M_TROOP_INJECT_EMITTER_DATA sendData;
				sendData.skillId = skillObject->getSkillInfo()->skillId;
				sendData.troopIndex = troopSoldierEntity->getTroopEntity()->getID();
				sendData.soldierIndex = troopSoldierEntity->getID();
				/*sendData.injectDir.x = dir.x;
				sendData.injectDir.z = dir.z;*/
				sendData.injectDir = ((NetVec2)dir).getData();

				NetPacketPackManager::getInstance().addPacketToBuff(PT_TROOP_SOLDIER_INJECT_EMITTER, GOT_SOLDIER, (Char8*)&sendData, troopSoldierEntity->getTroopEntity()->getID(), troopSoldierEntity->getID());
			}
			break;
		case SKT_PARABOLAAREA:
			{
				PT_SKILL_C2M_TROOP_INJECT_POINT_DATA sendData;
				sendData.skillId = skillObject->getSkillInfo()->skillId;
				sendData.troopIndex = troopSoldierEntity->getTroopEntity()->getID();
				sendData.soldierIndex = troopSoldierEntity->getID();
				//sendData.dir.x = 0/*troopSoldierEntity->getDir().x*/;
				//sendData.dir.z = 0/*troopSoldierEntity->getDir().z*/;
				sendData.targetPos = ((NetVec2)skillObject->getTargetPosition()).getData();

				NetPacketPackManager::getInstance().addPacketToBuff(PT_TROOP_SOLDIER_INJECT_POINT, GOT_SOLDIER, (Char8*)&sendData, troopSoldierEntity->getTroopEntity()->getID(), troopSoldierEntity->getID());
			}
			break;
		case SKT_GOUPANDDOWN:
			{
				PT_SKILL_C2M_TROOP_INJECT_POINT_DATA sendData;
				sendData.skillId = skillObject->getSkillInfo()->skillId;
				sendData.troopIndex = troopSoldierEntity->getTroopEntity()->getID();
				sendData.soldierIndex = troopSoldierEntity->getID();
				Flt dirX = troopSoldierEntity->getDir().x;
				Flt dirZ = troopSoldierEntity->getDir().z;
				Flt absDirX = abs(dirX);
				Flt absDirZ = abs(dirZ);
				if(absDirX > absDirZ)
				{
					if(dirX < 0)
					{
						/*sendData.dir.x = -1;
						sendData.dir.z = 0;*/
						sendData.dir = (NetVec2(-1.0f,0.0f)).getData();
					}
					else
					{
						/*sendData.dir.x = 1;
						sendData.dir.z = 0;*/
						sendData.dir = (NetVec2(1.0f,0.0f)).getData();
					}
				}
				else
				{
					if(dirZ < 0)
					{
						/*sendData.dir.x = 0;
						sendData.dir.z = -1;*/
						sendData.dir = (NetVec2(0.0f,-1.0f)).getData();
					}
					else
					{
						/*sendData.dir.x = 0;
						sendData.dir.z = 1;*/
						sendData.dir = (NetVec2(0.0f,1.0f)).getData();
					}
				}
				//sendData.dir.x = troopSoldierEntity->getDir().x;
				//sendData.dir.z = troopSoldierEntity->getDir().z;
				sendData.targetPos = ((NetVec2)skillObject->getTargetPosition()).getData();

				NetPacketPackManager::getInstance().addPacketToBuff(PT_TROOP_SOLDIER_INJECT_POINT, GOT_SOLDIER, (Char8*)&sendData, troopSoldierEntity->getTroopEntity()->getID(), troopSoldierEntity->getID());
			}
			break;
		}
	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendTroopEndInjectSkillPacket(CSkillObject* skillObject)
	{
		if(skillObject)
		{
			//Character* character = skillObject->getOwner();
			//CTroopEntity* troopEntity = (CTroopEntity*)character;
			//if(!character)
			//{
			//	return;
			//}

   //         // 获得一个发送【服务端】缓存
   //         GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

   //         // 转换成标准包格式
   //         GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getData();
   //         if ( packet )
   //         {
   //             // 设置标签
   //             packet->channel = GNPC_SKILL;
   //             packet->type    = PT_SKILL_C2F_TROOP_END_INJECT;

   //             // 转换逻辑包
   //             PT_SKILL_C2F_TROOP_END_INJECT_DATA* sendData = (PT_SKILL_C2F_TROOP_END_INJECT_DATA*)(packet->data);
   //             if ( sendData )
   //             {
   //                 // 填充逻辑包
   //                 sendData->troopGroupId = troopEntity->getParent()->getID();
   //                 sendData->troopId = character->getID();
   //                 sendData->skillId = skillObject->getBaseInfo()->id;

   //                 // 发送数据
   //                 ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
   //                     GameNetPacketData_INFO::headSize + PT_SKILL_C2F_TROOP_END_INJECT_DATA_INFO::dataSize );
   //             }
   //         }

		}

	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendTroopEndInjectSkillPacketToPackBuffer(CSkillObject* skillObject)
	{
		CTroopSoldierEntity* troopSoldierEntity = CSceneManager::getInstance().getTroopSoldierEntity(skillObject->getOwnerID(), skillObject->getOwnerIndex());
		if(troopSoldierEntity)
		{         
			PT_SKILL_C2M_TROOP_END_INJECT_DATA sendData;
			// 填充逻辑包
			sendData.troopIndex = troopSoldierEntity->getTroopEntity()->getID();
			sendData.soldierIndex = troopSoldierEntity->getID();
			sendData.skillId = skillObject->getSkillInfo()->skillId;

			NetPacketPackManager::getInstance().addPacketToBuff(PT_TROOP_SOLDIER_INJECT_END, GOT_SOLDIER, (Char8*)&sendData, troopSoldierEntity->getTroopEntity()->getID(), troopSoldierEntity->getID());
		}
	}


	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendBuildingClantSkillRequestPacket(CSkillObject* skillObject)
	{
		//
		//skillObject->getOwner();
		//GameObject* gameObject = CSceneManager::getInstance().getGameObject(skillObject->getOwnerType(), skillObject->getOwnerID());
		//if(!gameObject)
		//{
		//	return;
		//}

		//CCharacterSceneEntity* character = (CCharacterSceneEntity*)gameObject;
		//if(character && character->getIsRecvSkill())
		//{
  //          // 获得一个发送【服务端】缓存
  //          GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

  //          // 转换成标准包格式
  //          GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getData();
  //          if ( packet )
  //          {
  //              // 设置标签
  //              packet->channel = GNPC_SKILL;
  //              packet->type    = PT_SKILL_C2F_BUILDING_CLANT;

  //              // 转换逻辑包
  //              PT_SKILL_C2F_BUILDING_CLANT_DATA* sendData = (PT_SKILL_C2F_BUILDING_CLANT_DATA*)(packet->data);
  //              if ( sendData )
  //              {
  //                  // 填充逻辑包
  //                  sendData->buildingId = character->getID();
  //                  sendData->skillId = skillObject->getBaseInfo()->id;
  //                  sendData->mapId = character->getRegionID();

  //                  // 发送数据
  //                  ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
  //                      GameNetPacketData_INFO::headSize + PT_SKILL_C2F_TROOP_END_INJECT_DATA_INFO::dataSize );
  //              }
  //          }

		//    character->setIsRecvSkill(false);
		//}

	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendBuildingInjectSkillRequestPacket(CSkillObject* skillObject)
	{
		//
		//skillObject->getOwner();
		

        // 获得一个发送【服务端】缓存
      //  GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

      //  // 转换成标准包格式
      //  GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getData();
      //  if ( packet )
      //  {
      //      // 设置标签
      //      packet->channel = GNPC_SKILL;

      //      SkillOpType opType = skillObject->getBaseInfo()->opType;
      //      switch(opType)
      //      {
      //      case SKILLOPTYPE_EMITTER:
      //          {
      //              packet->type    = PT_SKILL_C2F_BUILDING_INJECT_EMITTER;

      //              // 转换逻辑包
      //              PT_SKILL_C2F_BUILDING_INJECT_EMITTER_DATA* sendData = (PT_SKILL_C2F_BUILDING_INJECT_EMITTER_DATA*)(packet->data);
      //              if ( sendData )
      //              {
      //                  // 填充逻辑包
						//GameObject* gameObject = CSceneManager::getInstance().getGameObject(skillObject->getOwnerType(), skillObject->getOwnerID());
						//if(!gameObject)
						//{
						//	return;
						//}

      //                  sendData->buildingId = gameObject->getID();
      //                  sendData->skillId = skillObject->getBaseInfo()->id;
      //                  sendData->mapId = CSceneManager::getInstance().getRegionId();

      //                  // 发送数据
      //                  ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
      //                      GameNetPacketData_INFO::headSize + PT_SKILL_C2F_BUILDING_INJECT_EMITTER_DATA_INFO::dataSize );

      //              }
      //              
      //          }
      //          break;

      //      case SKILLOPTYPE_POINT:
      //          {
      //              packet->type    = PT_SKILL_C2F_BUILDING_INJECT_POINT;

      //              // 转换逻辑包
      //              PT_SKILL_C2F_BUILDING_INJECT_POINT_DATA* sendData = (PT_SKILL_C2F_BUILDING_INJECT_POINT_DATA*)(packet->data);
      //              if ( sendData )
      //              {
      //                  // 填充逻辑包
						//GameObject* gameObject = CSceneManager::getInstance().getGameObject(skillObject->getOwnerType(), skillObject->getOwnerID());
						//if(!gameObject)
						//{
						//	return;
						//}
      //                  sendData->buildingId = gameObject->getID();
      //                  sendData->skillId = skillObject->getBaseInfo()->id;
      //                  sendData->targetPos.x = skillObject->getTargetPosition().x;
      //                  sendData->targetPos.z = skillObject->getTargetPosition().z;
      //                  sendData->mapId = CSceneManager::getInstance().getRegionId();

      //                  // 发送数据
      //                  ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
      //                      GameNetPacketData_INFO::headSize +PT_SKILL_C2F_BUILDING_INJECT_POINT_DATA_INFO::dataSize );

      //              }
      //              
      //          }
      //          break;

      //      case SKILLOPTYPE_OBJECT:
      //          {
      //              packet->type    = PT_SKILL_C2F_BUILDING_INJECT_OBJECT;

      //              // 转换逻辑包
      //              PT_SKILL_C2F_BUILDING_INJECT_OBJECT_DATA* sendData = (PT_SKILL_C2F_BUILDING_INJECT_OBJECT_DATA*)(packet->data);
      //              if ( sendData )
      //              {
      //                  // 填充逻辑包
						//GameObject* gameObject = CSceneManager::getInstance().getGameObject(skillObject->getOwnerType(), skillObject->getOwnerID());
						//if(!gameObject)
						//{
						//	return;
						//}

      //                  sendData->buildingId = gameObject->getID();
      //                  sendData->skillId = skillObject->getBaseInfo()->id;
      //                  sendData->objectId = skillObject->getTargetObjectID();
      //                  sendData->objectIndex = skillObject->getTargetObjectIndex();
      //                  sendData->objectType = skillObject->getTargetObjectType();
      //                  sendData->mapId = CSceneManager::getInstance().getRegionId();

      //                  // 发送数据
      //                  ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
      //                      GameNetPacketData_INFO::headSize +PT_SKILL_C2F_BUILDING_INJECT_OBJECT_DATA_INFO::dataSize );

      //              } 
      //              
      //          }
      //          break;

      //      }

      //  }

	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendBuildingEndInjectSkillPacket(CSkillObject* skillObject)
	{
		//if(skillObject)
		//{
  //          // 获得一个发送【服务端】缓存
  //          GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

  //          // 转换成标准包格式
  //          GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getData();
  //          if ( packet )
  //          {
  //              // 设置标签
  //              packet->channel = GNPC_SKILL;
  //              packet->type    = PT_SKILL_C2F_BUILDING_END_INJECT;

  //              // 转换逻辑包
  //              PT_SKILL_C2F_BUILDING_END_INJECT_DATA* sendData = (PT_SKILL_C2F_BUILDING_END_INJECT_DATA*)(packet->data);
  //              if ( sendData )
  //              {
  //                  // 填充逻辑包
		//			GameObject* gameObject = CSceneManager::getInstance().getGameObject(skillObject->getOwnerType(), skillObject->getOwnerID());
		//			if(!gameObject)
		//			{
		//				return;
		//			}

  //                  sendData->buildingId = gameObject->getID();
  //                  sendData->skillId = skillObject->getBaseInfo()->id;

  //                  // 发送数据
  //                  ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
  //                      GameNetPacketData_INFO::headSize + PT_SKILL_C2F_BUILDING_END_INJECT_DATA_INFO::dataSize );
  //              }
  //          }
	
  //      }

	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::onRecvBuildingClantSkillRequire( PT_SKILL_M2C_BUILDING_CLANT_DATA* data )
	{
		//FUNDETECTION(__MG_FUNC__);
		//CBattleBuildingEntity* entity = CSceneManager::getInstance().getBuildingEntity( data->buildingId );
		//if ( entity )
		//{
		//	//暂时不精确位置
		//	//entity->setPos( Vec3( data->buildingPos.x , 0 , data->buildingPos.z) );
		//	//entity->setDir( Vec3( data->buildingDir.x , 0 , data->buildingDir.z) );
		//	entity->startClantSkill( data->skillId );
		//	//entity->setIsRecv(true);
		//}
	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::onRecvBuildingInjectInstantSkillRequire( PT_SKILL_M2C_BUILDING_INJECT_EMITTER_DATA* data )
	{
		//FUNDETECTION(__MG_FUNC__);
		/*CBattleBuildingEntity* entity = CSceneManager::getInstance().getBuildingEntity( data->buildingId );
		if ( entity )
		{
			entity->startInjectSkill(data->skillId);
		}*/
	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::onRecvBuildingInjectPointSkillRequire( PT_SKILL_M2C_BUILDING_INJECT_POINT_DATA* data )
	{
		//FUNDETECTION(__MG_FUNC__);
		//CBattleBuildingEntity* entity = CSceneManager::getInstance().getBuildingEntity( data->buildingId );
		//if ( entity )
		//{
		//	entity->startInjectSkill(data->skillId, Vec3(data->targetPos.x, 0, data->targetPos.z));
		//}
	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::onRecvBuildingInjectObjectSkillRequire( PT_SKILL_M2C_BUILDING_INJECT_OBJECT_DATA* data )
	{
		//FUNDETECTION(__MG_FUNC__);
		//CBattleBuildingEntity* entity = CSceneManager::getInstance().getBuildingEntity( data->buildingId );
		//if ( entity )
		//{
		//	entity->startInjectSkill(data->skillId, (GAMEOBJ_TYPE)data->objectType, data->objectId, data->objectIndex);
		//}
	}

	//-----------------------------------------------------------------------------
	void SkillNetPacketProcesser::sendSkillSummonBuildingPacket(IdType characterId, IdType skillId, IdType mapId, Byte mapType, IdType templateId, NetVec2 pos)
	{
        // 获得一个发送【服务端】缓存
        //GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        //// 转换成标准包格式
        //GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getData();
        //if ( packet )
        //{
        //    // 设置标签
        //    packet->channel = GNPC_SKILL;
        //    packet->type    = PT_SKILL_C2F_SUMMON_BUILDING;

        //    // 转换逻辑包
        //    PT_SKILL_C2F_SUMMON_BUILDING_DATA* sendData = (PT_SKILL_C2F_SUMMON_BUILDING_DATA*)(packet->data);
        //    if ( sendData )
        //    {
        //        // 填充逻辑包
        //        sendData->characterId = characterId;
        //        sendData->mapId = mapId;
        //        sendData->skillId = skillId;
        //        sendData->tamplateId = templateId;
        //        sendData->pos.x = pos.x;
        //        sendData->pos.z = pos.z;
        //        sendData->mapType = mapType;

        //        // 发送数据
        //        ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
        //            GameNetPacketData_INFO::headSize + PT_SKILL_C2F_SUMMON_BUILDING_DATA_INFO::dataSize );
        //    }
        //}

        	
    }




}