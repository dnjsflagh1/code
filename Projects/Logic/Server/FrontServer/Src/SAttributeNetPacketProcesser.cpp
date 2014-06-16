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
            //�����ɫ���ˣ��ָ�����������ӵ�����Ϣ��
            //���͸��ͻ���
            sendCharacterHpSpMpToClient(
                pCharacter
                ,(DamageType)data->damageType
                ,data->value
                ,data->resultType
                );

            //�ж��Ƿ����������������ݿ�hp�� sp�� mp��
            pCharacter->setHurtOrRecove((DamageType)data->damageType, (ATTACK_RESULT_TYPE)data->resultType, data->value);
        }
    }
    //------------------------------------------------------------------------------------------------
    void SAttributeNetPacketProcesser::sendCharacterHpSpMpToClient( SCharacter* pCharacter, DamageType reducetype, UInt val, Byte resType )
    {
        // ���һ�����͡��ͻ��ˡ�����
        GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

        // ת���ɱ�׼����ʽ
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // ���ñ�ǩ
            packet->channel = GNPC_ATTRIBUTE;
            packet->type    = PT_ATTR_F2C_ATTR_HPMPSP;

            // ת���߼���
            PT_ATTR_F2C_ATTR_HPMPSP_DATA* data = (PT_ATTR_F2C_ATTR_HPMPSP_DATA*)(packet->data);
            if ( data )
            {
                // ����߼���
                data->damageType = reducetype;
                data->Id = pCharacter->getID();
                data->resultType = resType;
                data->val = val;

                // ��������
				FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					GameNetPacketData_INFO::headSize + PT_ATTR_F2C_ATTR_HPMPSP_DATA_INFO::dataSize, 
					/*pCharacter->getBelongPlayer()->getClientNetID()*/0 );

            }
        }
    }

	//------------------------------------------------------------------------------------------------
	void SAttributeNetPacketProcesser::sendUpLevel( I32 mapNetId, PlayerCharacterIdType charId, U32 level, Byte levelType )
	{
		// ���һ�����͡��ͻ��ˡ�����
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_ATTRIBUTE;
			packet->type    = PT_ATTR_F2M_ATTR_LEVEL;

			// ת���߼���
			PT_ATTR_F2M_ATTR_LEVEL_DATA* data = (PT_ATTR_F2M_ATTR_LEVEL_DATA*)(packet->data);
			if ( data )
			{
				// ����߼���
				data->charId = charId;
				data->level = level;
				data->levelType = levelType;

				// ��������
				FrontServerMain::getInstance().getServerLauncher()->sendServer(dataPtr,
					GameNetPacketData_INFO::headSize + PT_ATTR_F2M_ATTR_LEVEL_DATA_INFO::dataSize,
					mapNetId);
			}
		}
	}
	
}
