//***************************************************************************************
#include "stdafx.h"
#include "GameNetEvent.h"
#include "CBuffPacketProcesser.h"
#include "CSceneManager.h"
#include "CPlayerCharacterEntity.h"
#include "CBuffManager.h"
//***************************************************************************************
namespace MG
{
	MG::Bool CBuffPacketProcesser::processFrontServerPacket( I32 id, NetEventRecv* packet )
	{
		if ( packet->getChannel() == GNPC_BUFF )
		{
			GameNetPacketData* pGameNetPacketData = (GameNetPacketData*)(packet->getData());

			switch (pGameNetPacketData->type)
			{
			case PT_BUFF_M2C_PLAYERCHARACTER_BUFFDATA_LIST:
				recvPlayerCharacterBuffDataListFromMapServer(id, (PT_BUFF_M2C_PLAYERCHARACTER_BUFFDATA_LIST_Data*)pGameNetPacketData->data);
				break;
			case PT_BUFF_M2C_PLAYERCHARACTER_BUFFDATA:
				recvPlayerCharacterBuffDataFromMapServer(id, (PT_BUFF_M2C_PLAYERCHARACTER_BUFFDATA_Data*)pGameNetPacketData->data);
				break;
			}
			return true;
		}
		return false;
	}
	//-------------------------------------------------------------------------------
	void CBuffPacketProcesser::recvPlayerCharacterBuffDataListFromMapServer( I32 id, PT_BUFF_M2C_PLAYERCHARACTER_BUFFDATA_LIST_Data* pData )
	{
		CPlayerCharacterEntity* pCCharacterSceneEntity = CSceneManager::getInstance().getPlayerCharacterEntity(pData->dbId);
		DYNAMIC_ASSERT(pCCharacterSceneEntity);
		CBuffManager* pCBuffManager = pCCharacterSceneEntity->getCBuffManager();
		DYNAMIC_ASSERT(pCCharacterSceneEntity);

		//先清空所有的buff。
		pCBuffManager->clear();
		//在重新添加。
		netBuffData* pNetBuffData = NULL;
		for (Int i= 0; i<pData->ncount; i++)
		{
			pNetBuffData = &(pData->buffdatalist[i]);
			pCBuffManager->addOldBuff(pNetBuffData->buffId, pNetBuffData->timeUse, pNetBuffData->curAddNum);
		}
	}
	//-------------------------------------------------------------------------------
	void CBuffPacketProcesser::recvPlayerCharacterBuffDataFromMapServer( I32 id, PT_BUFF_M2C_PLAYERCHARACTER_BUFFDATA_Data* pData )
	{
		CPlayerCharacterEntity* pCCharacterSceneEntity = CSceneManager::getInstance().getPlayerCharacterEntity(pData->dbId);
		if ( pCCharacterSceneEntity == NULL ) return;

		CBuffManager* pCBuffManager = pCCharacterSceneEntity->getCBuffManager();
		DYNAMIC_ASSERT(pCCharacterSceneEntity);

		pCBuffManager->addOldBuff(pData->buffdatalist.buffId, pData->buffdatalist.timeUse, pData->buffdatalist.curAddNum);
	}
}