//*****************************************************************************************************
#include "stdafx.h"
#include "CAttributeNetPacketProcesser.h"
#include "CCharacter.h"
#include "CCharacterSceneEntity.h"
#include "CPlayer.h"
#include "CClan.h"
#include "CSceneManager.h"
#include "HeadDamageManage.h"
#include "CTroopEntity.h"
#include "CTroopSoldierEntity.h"
#include "FightManager.h"
#include "CFightMainManager.h"
#include "MessageManager.h"
#include "UIGenrealPicture.h"
#include "CPlayerCharacterEntity.h"
#include "CharacterList.h"
#include "CharacterVisionEventList.h"
#include "CharacterVisionEvent.h"
#include "GameSoundManager.h"
//***************************************************************************************************** 
namespace MG
{
    MG::Bool CAttributeNetPacketProcesser::processFrontServerPacket( I32 id,NetEventRecv* packet )
    {
        if ( packet->getChannel() == GNPC_ATTRIBUTE )
        {
            GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

            switch (data->type)
            {
            case PT_ATTR_S2C_ATTR_HPMPSP:
                onRecvSyncCharacterDamage( id, (PT_ATTR_S2C_ATTR_HPMPSP_DATA*)data->data );
                break;
            case PT_ATTR_F2C_ATTR_HPMPSP:
                onRecvCharacterDamage( id, (PT_ATTR_F2C_ATTR_HPMPSP_DATA*)data->data );
                break;
			case PT_ATTR_M2C_ATTR_LEVEL:
				onRecvUpLevel( id, (PT_ATTR_M2C_ATTR_LEVEL_DATA*)data->data );
				break;
            }
            return true;
        }
        return false;
    }
    //-----------------------------------------------------------------------------------------
    void CAttributeNetPacketProcesser::onRecvSyncCharacterDamage( I32 id, PT_ATTR_S2C_ATTR_HPMPSP_DATA* data )
    {

       /* Char8 tempMsg[128]  = "";

        Sprintf_s(tempMsg, 128, "伤害值 = %d， 最终的结果 = %d， 伤害对象 = %d\n", data->val, data->resultType, data->objType);
        MG_LOG(out_sys, tempMsg);*/

		if(data->objType == GOT_TROOP)
		{
			CTroopEntity* troop = CSceneManager::getInstance().getTroopEntity(data->Id);
			if(!troop)
			{
				return;
			}

			Vec3 pos = troop->getTroopCenterPos();
			float height = troop->getSoldierEntitysByIndex(0)->getEntity()->getModelObject()->getHeight();
			//无效
			if ( data->resultType == ATTACK_RESULT_TYPE_INVALID )
				HeadDamageManage::getInstance().addMiss( pos, height );
			//躲避
			else if ( data->resultType == ATTACK_RESULT_TYPE_DODGE )
				HeadDamageManage::getInstance().addMiss( pos, height );
			//吸收
			else if ( data->resultType == ATTACK_RESULT_TYPE_ABSORB )
				HeadDamageManage::getInstance().addMiss( pos, height );
			//治疗无效
			else if ( data->resultType == ATTACK_RESULT_TYPE_RECOVER_INVALID )
				HeadDamageManage::getInstance().addMiss( pos, height );
			//死亡
			else if ( data->resultType == ATTACK_RESULT_TYPE_DEAD )
			{
				troop->setHp(0);
				CTroopSoldierEntity* troopSoldierEntity = NULL;
				for(UInt i = 0; i < troop->getSoldierEntitysNum(); ++i)
				{	
					troopSoldierEntity = troop->getSoldierEntitysByIndex(i);
					if(!troopSoldierEntity)
					{
						continue;
					}

					troopSoldierEntity->die();
				}	
			}
			//恢复
			else if ( data->resultType == ATTACK_RESULT_TYPE_RECOVER )
			{   
				if ( data->damageType & DT_HP )
				{
					HeadDamageManage::getInstance().addNum( pos, height, DT_HP, data->val, true );
					troop->setHp(troop->getHp() + data->val);
				}
				if ( data->damageType & DT_MP )
				{
					HeadDamageManage::getInstance().addNum( pos, height, DT_MP, data->val, true );
					troop->setMp(troop->getMp() + data->val);
				}
				if ( data->damageType & DT_SP )
				{
					HeadDamageManage::getInstance().addNum( pos, height, DT_SP, data->val, true );
					troop->setSp(troop->getSp() + data->val);
				}

				//CFightMainManager::getInstance().addAndUpdateFightOnUseAuxiliarySkill((GAMEOBJ_TYPE)data->objType, data->Id, (GAMEOBJ_TYPE)data->masterType, data->masterId, data->hateVal);

			}
			//恢复
			else if ( data->resultType == ATTACK_RESULT_TYPE_HURT_CHANGE_RECOVER )
			{   
				if ( data->damageType & DT_HP )
				{
					HeadDamageManage::getInstance().addNum( pos, height, DT_HP, data->val, true );
					troop->setHp(troop->getHp() + data->val);
				}
				if ( data->damageType & DT_MP )
				{
					HeadDamageManage::getInstance().addNum( pos, height, DT_MP, data->val, true );
					troop->setMp(troop->getMp() + data->val);
				}
				if ( data->damageType & DT_SP )
				{
					HeadDamageManage::getInstance().addNum( pos, height, DT_SP, data->val, true );
					troop->setSp(troop->getSp() + data->val);
				}

			}
			//伤害
			else if ( data->resultType == ATTACK_RESULT_TYPE_HURT )
			{   
				if ( data->damageType & DT_HP )
				{
					HeadDamageManage::getInstance().addNum( pos, height, DT_HP, data->val, false );
					troop->setHp(troop->getHp() - data->val);
				}
				if ( data->damageType & DT_MP )
				{
					HeadDamageManage::getInstance().addNum( pos, height, DT_MP, data->val, false );
					troop->setMp(troop->getMp() - data->val);
				}
				if ( data->damageType & DT_SP )
				{
					HeadDamageManage::getInstance().addNum( pos, height, DT_SP, data->val, false );
					troop->setSp(troop->getSp() - data->val);
				}
			}

			//死亡
			if(data->resultType == ATTACK_RESULT_TYPE_DEAD)
			{
				MessageManager::getInstance().addChatMsgForTest("武将死亡 character_id[%d], objType[%d]\n", 
					data->Id, data->objType);
				return;
			}

			//if(data->resultType != ATTACK_RESULT_TYPE_RECOVER)
			//{
			//	//CFightMainManager::getInstance().addAndUpdateFightOnUseAttackSkill((GAMEOBJ_TYPE)data->objType, data->Id, (GAMEOBJ_TYPE)data->masterType, data->masterId, 0, data->Id, data->hateVal);
			//}

			return;
		}

        CCharacterSceneEntity* entity = CSceneManager::getInstance().getCharacterSceneEntity( (GAMEOBJ_TYPE)data->objType, data->Id  );
        if(entity)
        {
            Vec3 pos;
            entity->getEntity()->getSceneNode()->getPosition(pos);
			float height = entity->getEntity()->getModelObject()->getHeight();


            //无效
            if ( data->resultType == ATTACK_RESULT_TYPE_INVALID )
                HeadDamageManage::getInstance().addMiss( pos, height );
			//治疗无效
			else if ( data->resultType == ATTACK_RESULT_TYPE_RECOVER_INVALID )
				HeadDamageManage::getInstance().addMiss( pos, height );
            //躲避
            else if ( data->resultType == ATTACK_RESULT_TYPE_DODGE )
                HeadDamageManage::getInstance().addMiss( pos, height );
            //吸收
            else if ( data->resultType == ATTACK_RESULT_TYPE_ABSORB )
                HeadDamageManage::getInstance().addMiss( pos, height );
            //死亡
            else if ( data->resultType == ATTACK_RESULT_TYPE_DEAD )
			{
				HeadDamageManage::getInstance().addNum( pos, height, DT_HP, data->val, false );
				entity->setHp(0);
                entity->die();
			}
            //恢复
            else if ( data->resultType == ATTACK_RESULT_TYPE_RECOVER )
            {   
                if ( data->damageType & DT_HP )
                {
                    HeadDamageManage::getInstance().addNum( pos, height, DT_HP, data->val, true );
                    entity->setHp(entity->getHp() + data->val);
                }
                if ( data->damageType & DT_MP )
                {
                    HeadDamageManage::getInstance().addNum( pos, height, DT_MP, data->val, true );
                    entity->setMp(entity->getMp() + data->val);
                }
                if ( data->damageType & DT_SP )
                {
                    HeadDamageManage::getInstance().addNum( pos, height, DT_SP, data->val, true );
                    entity->setSp(entity->getSp() + data->val);
                }

				//CFightMainManager::getInstance().addAndUpdateFightOnUseAuxiliarySkill((GAMEOBJ_TYPE)data->objType, data->Id, (GAMEOBJ_TYPE)data->masterType, data->masterId, data->hateVal);
                
            }
			//伤害转治疗
			else if ( data->resultType == ATTACK_RESULT_TYPE_HURT_CHANGE_RECOVER )
			{   
				if ( data->damageType & DT_HP )
				{
					HeadDamageManage::getInstance().addNum( pos, height, DT_HP, data->val, true );
					entity->setHp(entity->getHp() + data->val);
				}
				if ( data->damageType & DT_MP )
				{
					HeadDamageManage::getInstance().addNum( pos, height, DT_MP, data->val, true );
					entity->setMp(entity->getMp() + data->val);
				}
				if ( data->damageType & DT_SP )
				{
					HeadDamageManage::getInstance().addNum( pos, height, DT_SP, data->val, true );
					entity->setSp(entity->getSp() + data->val);
				}

			}
            //伤害
            else if ( data->resultType == ATTACK_RESULT_TYPE_HURT )
            {   
                if ( data->damageType & DT_HP )
                {
                    HeadDamageManage::getInstance().addNum( pos, height, DT_HP, data->val, false );
                    entity->setHp(entity->getHp() - data->val);
                }
                if ( data->damageType & DT_MP )
                {
                    HeadDamageManage::getInstance().addNum( pos, height, DT_MP, data->val, false );
                    entity->setMp(entity->getMp() - data->val);
                }
                if ( data->damageType & DT_SP )
                {
                    HeadDamageManage::getInstance().addNum( pos, height, DT_SP, data->val, false );
                    entity->setSp(entity->getSp() - data->val);
                }
            }

			//if(data->resultType != ATTACK_RESULT_TYPE_RECOVER)
			//{
			//	CFightMainManager::getInstance().addAndUpdateFightOnUseAttackSkill((GAMEOBJ_TYPE)data->objType, data->Id, (GAMEOBJ_TYPE)data->masterType, data->masterId, 0, data->Id, data->hateVal);
			//}
        }
    }
    //-----------------------------------------------------------------------------------------
    void CAttributeNetPacketProcesser::onRecvCharacterDamage( I32 id, PT_ATTR_F2C_ATTR_HPMPSP_DATA* data )
    {
        CCharacter* pCharacter = CPlayer::getInstance().getActiveClan()->getPlayerCharacter(data->Id);
        if(pCharacter)
        {
            pCharacter->setHpMpSp(data->val, (DamageType)data->damageType, (ATTACK_RESULT_TYPE)data->resultType);
        }
    }
	//-----------------------------------------------------------------------------------------
	void CAttributeNetPacketProcesser::onRecvUpLevel( I32 id, PT_ATTR_M2C_ATTR_LEVEL_DATA* data )
	{
		const AccountIdType myAccountId = CPlayer::getInstance().getAccountID();
		CPlayerCharacterEntity* entity = CSceneManager::getInstance().getPlayerCharacterEntity(data->charId);
		if(entity)
		{
			//改变血量
			entity->setHpMax(data->hpMax);
			entity->setHp(data->hp);			
			entity->setMpMax(data->mpMax);
			entity->setMp(data->mp);
			
			//改变实体的等级。
			//播放升级特效;

			U32 characterVisionEventListId = entity->getCharacterTempInfo()->getCharacterVisionEventListId();
			const CharacterVisionEventListInfo* characterVisionEventListInfo = CharacterVisionEventList::getInstance().getCharacterVisionEventListInfo(characterVisionEventListId);
			if(!characterVisionEventListInfo)
			{
				return;
			}

			const CharacterVisionEventInfo* characterVisionEventInfo = CharacterVisionEvent::getInstance().getCharacterVisionEventInfo(characterVisionEventListInfo->upgradeId);
			if(!characterVisionEventInfo)
			{
				return;
			}

			Str actionName;
			MGStrOp::toString(characterVisionEventInfo->actionName.c_str(), actionName);
			entity->playAnimation(actionName);

			entity->addEffect(characterVisionEventInfo->effectResId);

			GameSoundManager::getInstance().play(characterVisionEventInfo->audioResId);
		}
	}
}