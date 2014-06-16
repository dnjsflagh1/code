//*******************************************************************************************************
#include "stdafx.h"
#include "SAttributeNetPacketProcesser.h"
#include "FrontServerMain.h"
#include "SCharacter.h"
#include "ServerManager.h"
#include "SPlayer.h"
#include "SWorldManager.h"
#include "SGameObjectManager.h"
#include "AttributePara.h"
//*******************************************************************************************************
namespace MG
{
    MG::Bool SAttributeNetPacketProcesser::processMapServerPacket( I32 id, NetEventRecv* packet )
    {
        if ( packet->getChannel() == GNPC_ATTRIBUTE )
        {   
            GameNetPacketData* data = (GameNetPacketData*)(packet->getData());
            switch (data->type)
            {
            case PT_ATTR_M2F_ATTR_HPMPSP:
                onRecvCharacterHpSpMp(id, (PT_ATTR_M2F_ATTR_HPMPSP_DATA*)data->data);
                break;
            }

            return true;
        }
        return false;
    }
    //------------------------------------------------------------------------------------------------
    void SAttributeNetPacketProcesser::onRecvCharacterHpSpMp( I32 id , PT_ATTR_M2F_ATTR_HPMPSP_DATA*data )
    {
		SPlayerPtr pSPlayerPtr;// = SWorldManager::getInstance().getGameObjectManager()->getPlayerByAccountId(data->accountId);
		if ( pSPlayerPtr.isNull() ) return;

		SClan* pSClan;// = pSPlayerPtr->getMainClan();
		if ( NULL == pSClan ) return;

        SCharacter* pCharacter;// = pSClan->getPlayerCharacterFromList(data->Id);
        if(pCharacter)
        {
            //如果角色受伤，恢复，或死亡会接到此消息。
            //发送给客户端
            sendCharacterHpSpMpToClient(
                pCharacter
                ,(DamageType)data->damageType
                ,data->value
                ,data->resultType
                );

            //判断是否死亡，并更新数据库hp， sp， mp。
            pCharacter->setHurtOrRecove((DamageType)data->damageType, (ATTACK_RESULT_TYPE)data->resultType, data->value);
        }
    }
    //------------------------------------------------------------------------------------------------
    void SAttributeNetPacketProcesser::sendCharacterHpSpMpToClient( SCharacter* pCharacter, DamageType reducetype, UInt val, Byte resType )
    {
        // 获得一个发送【客户端】缓存
        GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_ATTRIBUTE;
            packet->type    = PT_ATTR_F2C_ATTR_HPMPSP;

            // 转换逻辑包
            PT_ATTR_F2C_ATTR_HPMPSP_DATA* data = (PT_ATTR_F2C_ATTR_HPMPSP_DATA*)(packet->data);
            if ( data )
            {
                // 填充逻辑包
                data->damageType = reducetype;
                data->Id = pCharacter->getID();
                data->resultType = resType;
                data->val = val;

                // 发送数据
				FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					GameNetPacketData_INFO::headSize + PT_ATTR_F2C_ATTR_HPMPSP_DATA_INFO::dataSize, 
					/*pCharacter->getBelongPlayer()->getClientNetID()*/0 );

            }
        }
    }

	//------------------------------------------------------------------------------------------------
	void SAttributeNetPacketProcesser::sendUpLevel( I32 mapNetId, PlayerCharacterIdType charId, U32 level, Byte levelType )
	{
		// 获得一个发送【客户端】缓存
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_ATTRIBUTE;
			packet->type    = PT_ATTR_F2M_ATTR_LEVEL;

			// 转换逻辑包
			PT_ATTR_F2M_ATTR_LEVEL_DATA* data = (PT_ATTR_F2M_ATTR_LEVEL_DATA*)(packet->data);
			if ( data )
			{
				// 填充逻辑包
				data->charId = charId;
				data->level = level;
				data->levelType = levelType;

				// 发送数据
				FrontServerMain::getInstance().getServerLauncher()->sendServer(dataPtr,
					GameNetPacketData_INFO::headSize + PT_ATTR_F2M_ATTR_LEVEL_DATA_INFO::dataSize,
					mapNetId);
			}
		}
	}
	
}
