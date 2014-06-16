//**************************************************************************************************************
#include "stdafx.h"
#include "ItemPacketProcesser.h"
#include "GameNetPacket.h"
#include "ClientManager.h"
#include "ServerManager.h"
#include "FrontServerMain.h"
#include "SItemManager.h"
#include "SWorldManager.h"
#include "AttributePara.h"
//**************************************************************************************************************
namespace MG
{
    Bool ItemPacketProcesser::processMapServerPacket(I32 id, NetEventRecv* packet)
    {
        if ( packet->getChannel() == GNPC_ITEM )
        {
            //FUNDETECTION(__MG_FUNC__);
            GameNetPacketData* pData = (GameNetPacketData*)packet->getData();
            DYNAMIC_ASSERT( pData );

            switch (pData->type)
            {
            case PT_ITEM_M2F_PICK_ITEM:
                recvPickItemFromMapServer( id, (PT_ITEM_M2F_PICK_ITEM_DATA*)( pData->data ) );
                break;
			case PT_ITEM_M2F_USE_ITEM:
				recvItemUseFromMapServer( id, (PT_ITEM_M2F_USE_ITEM_DATA*)( pData->data ) );
				break;
			case PT_ITEM_M2F_ATFD_REWARD:
				recvRewardItemFromMapServer( id, (PT_ITEM_M2F_ATFD_REWARD_DATA*)( pData->data ));
				break;
			case PT_ITEM_M2F_DROP_ITEM_ADD_EXP:
				recvDropItemAddExpFromMapServer( id, (PT_ITEM_M2F_DROP_ITEM_ADD_EXP_DATA*)( pData->data ));
				break;
			default:
				DYNAMIC_ASSERT(0);
				break;
            }

            return true;
        }

        return false;
    }
    //---------------------------------------------------------------------------------------------
    MG::Bool ItemPacketProcesser::processClientPacket( I32 id, NetEventRecv* packet )
    {
        if ( packet->getChannel() == GNPC_ITEM )
        {
			//FUNDETECTION(__MG_FUNC__);
            GameNetPacketData* pData = (GameNetPacketData*)packet->getData();
            DYNAMIC_ASSERT( pData );

            switch (pData->type)
            {
            case PT_ITEM_C2S_DELETE:
                recvItemDel( id, (PT_ITEM_C2S_DELETE_DATA*)( pData->data ) );
                break;
           case PT_ITEM_C2S_CHANGEPOS:
                recvItemChangePos( id, (PT_ITEM_C2S_CHANGEPOS_DATA*)( pData->data ) );
                break;
           case PT_ITEM_C2S_SPLIT:
               recvItemSplit( id, (PT_ITEM_C2S_SPLIT_DATA*)( pData->data ) ) ;
               break;
           case PT_ITEM_C2F_PICK_ITEM:
               recvPickItemFromClient( id, (PT_ITEM_C2F_PICK_ITEM_DATA*)( pData->data ) );
               break;
           case PT_ITEM_C2F_USE_ITEM:
               recvItemUseFromClient(id, (PT_ITEM_C2F_USE_ITEM_DATA*)( pData->data ));
               break;
		   case PT_ITEM_C2M_ATFD_REWARD:
			   recvRewardItemFromClient(id, (PT_ITEM_C2M_ATFD_REWARD_DATA*)( pData->data ));
			   break;
		   case PT_ITEM_C2F_QUEST_REWARD:
			   recvRewardItemAssociateQuestFromClient(id, (PT_ITEM_C2F_QUEST_REWARD_DATA*)( pData->data ));
			   break;
		   default:
			   DYNAMIC_ASSERT(0);
			   break;
            }

            return true;
        }

        return false;
    }
    //---------------------------------------------------------------------------------------------
    void ItemPacketProcesser::recvItemDel( I32 id, PT_ITEM_C2S_DELETE_DATA* pData )
    {
		SPlayerPtr pPlayer;// = SWorldManager::getInstance().getGameObjectManager()->getPlayerByClientNetId(id);
        if (pPlayer.isNull())
        {
            DYNAMIC_ASSERT(0);
            return;
        }
        SClan* pClan;// = pPlayer->getMainClan();
        DYNAMIC_ASSERT(pClan);

        SItemManager* pItemManager = pClan->getItemManager();
        DYNAMIC_ASSERT(pItemManager);
       
         pItemManager->handlDelItem(pData->xItemDBID, (ITEM_SITE_TYPE)pData->type, pData->id);
       // sendItemDelToClient(id, (ITEM_SITE_TYPE)pData->type, pData->xItemDBID, pItemManager->handlDelItem(pData->xItemDBID, (ITEM_SITE_TYPE)pData->type, pData->id), pData->id);

    }
    //---------------------------------------------------------------------------------------------
    void ItemPacketProcesser::sendAddItemToClient(I32 id, PlayerItem* pItem)
    {

        ///////////////////////////////////////////////////////////////////////////

        // ���һ�����͡��ͻ��ˡ�����
        GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

        // ת���ɱ�׼����ʽ
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // ���ñ�ǩ
            packet->channel = GNPC_ITEM;
            packet->type    = PT_ITEM_S2C_ADD;

            // ת���߼���
            PT_ITEM_S2C_ADD_DATA* sendData = (PT_ITEM_S2C_ADD_DATA*)(packet->data);
            if ( sendData )
            {
                // ����߼���
                sendData->xItemRecord = *( pItem->getItemRecord());

                // ��������

				FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					GameNetPacketData_INFO::headSize + PT_ITEM_S2C_ADD_DATA_INFO::dataSize , 
					id);
            }
        }
    }

    //---------------------------------------------------------------------------------------------
    void ItemPacketProcesser::recvItemChangePos( I32 id, PT_ITEM_C2S_CHANGEPOS_DATA* pData )
    {
		SPlayerPtr pPlayer;// = SWorldManager::getInstance().getGameObjectManager()->getPlayerByClientNetId(id);
		if ( pPlayer.isNull() )
			return;

        SClan* pClan;// = pPlayer->getMainClan();
        DYNAMIC_ASSERT(pClan);

        SItemManager* pItemManager = pClan->getItemManager();
        DYNAMIC_ASSERT(pItemManager);
        
		item_changepos_res res = pItemManager->handlChangItem(pData->IndexSend, pData->IndexRecv, (ITEM_SITE_TYPE)pData->sendType,
			(ITEM_SITE_TYPE)pData->recvType, pData->id);
        //if ( pItemManager->handlChangItem(pData->IndexSend, pData->IndexRecv, (ITEM_SITE_TYPE)pData->sendType, (ITEM_SITE_TYPE)pData->recvType, pData->id) )
            sendItemChangePosToClient(id, (ITEM_SITE_TYPE)pData->sendType, (ITEM_SITE_TYPE)pData->recvType, pData->IndexSend, pData->IndexRecv,
				res, pData->id);
       // else
            //sendItemChangePosToClient(id, (ITEM_SITE_TYPE)pData->sendType, (ITEM_SITE_TYPE)pData->recvType, pData->IndexSend, pData->IndexRecv, item_changepos_res::item_changepos_res_Error_pos, pData->id);
    }
    //---------------------------------------------------------------------------------------------
    void ItemPacketProcesser::sendItemDelToClient(I32 id, ITEM_SITE_TYPE type, IdType itemDBID, itembag_del_res res, PlayerCharacterIdType charid)
    {
        // ���һ�����͡��ͻ��ˡ�����
        GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

        // ת���ɱ�׼����ʽ
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // ���ñ�ǩ
            packet->channel = GNPC_ITEM;
            packet->type    = PT_ITEM_S2C_DELETE;

            // ת���߼���
            PT_ITEM_S2C_DELETE_DATA* sendData = (PT_ITEM_S2C_DELETE_DATA*)(packet->data);
            if ( sendData )
            {
                // ����߼���
                sendData->type = type;
                sendData->xItemDBID = itemDBID;
                sendData->res = res;
                sendData->id = charid;

                // ��������
				FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					GameNetPacketData_INFO::headSize + PT_ITEM_S2C_DELETE_DATA_INFO::dataSize , 
					id );
            }
        }
    }

    //---------------------------------------------------------------------------------------------
    void ItemPacketProcesser::sendItemChangePosToClient(I32 id, ITEM_SITE_TYPE sendtype, ITEM_SITE_TYPE recvtype, U32 sendIndex, U32 recvIndex, item_changepos_res res, PlayerCharacterIdType charid )
    {
        // ���һ�����͡��ͻ��ˡ�����
        GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

        // ת���ɱ�׼����ʽ
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // ���ñ�ǩ
            packet->channel = GNPC_ITEM;
            packet->type    = PT_ITEM_S2C_CHANGEPOS;

            // ת���߼���
            PT_ITEM_S2C_CHANGEPOS_DATA* sendData = (PT_ITEM_S2C_CHANGEPOS_DATA*)(packet->data);
            if ( sendData )
            {
                // ����߼���
                sendData->sendType  = sendtype;
                sendData->recvType  = recvtype;  
                sendData->IndexRecv = recvIndex;
                sendData->IndexSend = sendIndex;
                sendData->res       = res;
                sendData->id        = charid;

                // ��������
				FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					GameNetPacketData_INFO::headSize + PT_ITEM_S2C_CHANGEPOS_DATA_INFO::dataSize , 
					id );
            }
        }
    }

    //---------------------------------------------------------------------------------------------
    void ItemPacketProcesser::sendAllClanItemInfoToClient(I32 id, SClanPtr& clanPtr )
    {
        std::vector<ItemRecord*> itemRecordList;

        //��ȡclanItem��ĵ���
        const std::map<IdType, PlayerItem*>* tempMapClanItem;// = getClanItems()->getPlayerItemMap();
        std::map<IdType, PlayerItem*>::const_iterator front = tempMapClanItem->begin();
        std::map<IdType, PlayerItem*>::const_iterator back = tempMapClanItem->end();
        while (front != back)
        {
            itemRecordList.push_back(front->second->getItemRecord());
            ++front;
        }

        //��ȡ��ɫ������ĵ���
        std::map<PlayerCharacterIdType, GenrealItem*>* tempGenrealItemMap;// = getGenrealItemMap();
        std::map<PlayerCharacterIdType, GenrealItem*>::iterator frontGenrealItem = tempGenrealItemMap->begin();
        std::map<PlayerCharacterIdType, GenrealItem*>::iterator backGenrealItem = tempGenrealItemMap->end();
        while ( frontGenrealItem != backGenrealItem )
        {
            //tempMapClanItem = frontGenrealItem->second->getPlayerItemMap();
            front = tempMapClanItem->begin();
            back = tempMapClanItem->end();
            while (front != back)
            {
                itemRecordList.push_back(front->second->getItemRecord());
                ++front;
            }
            ++frontGenrealItem;
        }

        //��ɫװ����Ϣ
        std::map<PlayerCharacterIdType, GenrealEquip*>* tempGenrealEquipMap;// = getGenrealEquipMap();
        std::map<PlayerCharacterIdType, GenrealEquip*>::iterator frontGenrealEquip = tempGenrealEquipMap->begin();
        std::map<PlayerCharacterIdType, GenrealEquip*>::iterator backGenrealEquip = tempGenrealEquipMap->end();
        while (frontGenrealEquip != backGenrealEquip)
        {
            PlayerItem** genrealEquipArray;// = frontGenrealEquip->second->getEquipItemArray();
            //��ɫװ��
            for (Int i=1; i<ITEM_EQUIP_SLOT_TYPE_MAX; i++)
            {
                if (genrealEquipArray[i] != NULL)
                {
                    itemRecordList.push_back(genrealEquipArray[i]->getItemRecord());
                }
            }

            frontGenrealEquip++;
        }

        //��ȡ�ع����������
        /*const std::map<IdType, PlayerItem*>* tempMapBuyBackItem = getClanItems()->getPlayerItemMap();
        std::map<IdType, PlayerItem*>::const_iterator front = tempMapBuyBackItem->begin();
        std::map<IdType, PlayerItem*>::const_iterator back = tempMapBuyBackItem->end();
        while (front != back)
        {
        itemRecordList.push_back(front->second->getItemRecord());
        ++front;
        }
        */

        //ItemPacketProcesser::getInstance().sendItemToClient(mParent->getClientNetId(), &itemRecordList);
    }

    //---------------------------------------------------------------------------------------------
    void ItemPacketProcesser::sendItemToClient(I32 id, std::vector<ItemRecord*>* ItemRecordList)
    {
        DYNAMIC_ASSERT(ItemRecordList);
        
        // �õ�һ�����ͷ��ͻ���
        GameNetSendDataBufferPtr dataPtr ;
        GameNetPacketData* packet       = NULL;
        PT_ITEM_S2C_ADDLIST_DATA* sendData = NULL;
        
        // ��ǰ��������ͷ��С
        I32 sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_ITEM_S2C_ADDLIST_DATA_INFO::headSize;
        // ��ǰ�������ݴ�С
        I32 sendDataSize        = sendDataHeadSize;
        // ׼���������ݴ�С
        I32 prepareSendDataSize = sendDataHeadSize;

        // ������Ʒ����
        std::vector<ItemRecord*>::iterator front     = ItemRecordList->begin();
        std::vector<ItemRecord*>::iterator back      = ItemRecordList->end();
        while (front != back)
        {

			//----------------------------------------------------------------------------------------------------

			if ( dataPtr.isNull() == false )
			{
				// ����һ����Ʒ���ݴ�С���������ݻ����С
				prepareSendDataSize = sendDataSize + PT_ITEM_S2C_ADDLIST_DATA_INFO::itemRecordSize;

				// ������ڻ�������С����
				if ( prepareSendDataSize >= dataPtr->getLogicDataMaxSize() )
				{
					FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,sendDataSize, id);
					dataPtr.setNull();
				}
			}

			//----------------------------------------------------------------------------------------------------

			if ( dataPtr.isNull() )
			{
				// �õ�һ�����ͷ��ͻ���
				FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );
				packet	= (GameNetPacketData*) dataPtr->getLogicData();
				if ( !packet )
					return;

				packet->channel = GNPC_ITEM;
				packet->type    = PT_ITEM_S2C_ADDLIST;
				sendData = (PT_ITEM_S2C_ADDLIST_DATA*)(packet->data);
				// ���
				sendData->num = 0;

				sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_ITEM_S2C_ADDLIST_DATA_INFO::headSize;
				sendDataSize        = sendDataHeadSize;
				prepareSendDataSize = sendDataHeadSize;
			}

			//----------------------------------------------------------------------------------------------------

            // ������Ʒ��¼
            sendData->xItemRecord[sendData->num] = *(*( front ));

            // ��������
            sendDataSize += PT_ITEM_S2C_ADDLIST_DATA_INFO::itemRecordSize;

            ++sendData->num;
            ++front;   
        }

		//----------------------------------------------------------------------------------------------------

        // �����ʣ������
        if ( dataPtr.isNull() == false )
        {
			FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,sendDataSize, id);
			dataPtr.setNull();
        }
    }

    //---------------------------------------------------------------------------------------------------------------
	void ItemPacketProcesser::sendItemSplitToClient( I32 id,UInt selfSlotIndex, ITEM_SITE_TYPE selfType, ITEM_SITE_TYPE splitType, UInt selectIndex, U32 num,
		item_split_res res, PlayerCharacterIdType charid)
    {
        // ���һ�����͡��ͻ��ˡ�����
        GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

        // ת���ɱ�׼����ʽ
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // ���ñ�ǩ
            packet->channel = GNPC_ITEM;
            packet->type    = PT_ITEM_S2C_SPLIT;

            // ת���߼���
            PT_ITEM_S2C_SPLIT_DATA* sendData = (PT_ITEM_S2C_SPLIT_DATA*)(packet->data);
            if ( sendData )
            {
                // ����߼���
				sendData->selfSlot = selfSlotIndex;
				sendData->selfType = selfType;
				sendData->splitType = splitType;
				//sendData->splitPos = pos;
				sendData->selectIndex = selectIndex;
				sendData->splitNum = num;
				sendData->characterId = id;
				sendData->res = res;

                // ��������
				FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					GameNetPacketData_INFO::headSize + PT_ITEM_S2C_SPLIT_DATA_INFO::dataSize , 
					id);
            }
        }
    }
	
    //---------------------------------------------------------------------------------------------------------------
    void ItemPacketProcesser::recvItemSplit( I32 id, PT_ITEM_C2S_SPLIT_DATA* pData )
    {
        SPlayerPtr pPlayer;// = SWorldManager::getInstance().getGameObjectManager()->getPlayerByClientNetId(id);
		if ( pPlayer.isNull() )
			return;

        SClan* pClan;// = pPlayer->getMainClan();
        DYNAMIC_ASSERT(pClan);

        SItemManager* pItemManager = pClan->getItemManager();
        DYNAMIC_ASSERT(pItemManager);

        item_split_res res = pItemManager->handlSplitItem(pData->selfSlot, (ITEM_SITE_TYPE)pData->selfType, (ITEM_SITE_TYPE)pData->splitType, 
			pData->selectIndex, pData->splitNum, pData->characterId);

		sendItemSplitToClient(id, pData->selfSlot, (ITEM_SITE_TYPE)pData->selfType, (ITEM_SITE_TYPE)pData->splitType, 
			pData->selectIndex, pData->splitNum, res, pData->characterId);
    }

    //---------------------------------------------------------------------------------------------------------------
    void ItemPacketProcesser::sendChangeEquipToMapServer( I32 id, PlayerCharacterIdType charid, PlayerItem* pItem, U32 pos )
    {
        // ���һ�����͡��ͻ��ˡ�����
        GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

        // ת���ɱ�׼����ʽ
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // ���ñ�ǩ
            packet->channel = GNPC_ITEM;
            packet->type    = PT_ITEM_F2M_CHANGE_EQUIP;

            // ת���߼���
            PT_ITEM_F2M_CHANGE_EQUIP_DATA* sendData = (PT_ITEM_F2M_CHANGE_EQUIP_DATA*)(packet->data);
            if ( sendData )
            {
                // ����߼���
                sendData->charid = charid;
				if ( pItem )
				{
					sendData->putonEquipAttr.equipId = pItem->getItemTempID();
					sendData->putonEquipAttr.curStrengthenLv = pItem->getItemRecord()->curStrengthenLv;
					sendData->putonEquipAttr.randAppendID = pItem->getItemRecord()->randAppendID;
					sendData->putonEquipAttr.strengthenAppendID = pItem->getItemRecord()->strengthenAppendID;
				}
                else
				{
					sendData->putonEquipAttr.equipId = 0;
					sendData->putonEquipAttr.curStrengthenLv = 0;
					sendData->putonEquipAttr.randAppendID = 0;
					sendData->putonEquipAttr.strengthenAppendID = 0;
				}
                sendData->pos = pos;

                // ��������
				FrontServerMain::getInstance().getServerLauncher()->sendServer(dataPtr,
					GameNetPacketData_INFO::headSize + PT_ITEM_F2M_CHANGE_EQUIP_DATA_INFO::dataSize ,
					id );
            }
        }
    }

    //---------------------------------------------------------------------------------------------------------------
    void ItemPacketProcesser::sendEquipListToMapServer( I32 id, SPlayerCharacter* pSPlayerCharacter )
    {
		PlayerCharacterIdType charid = pSPlayerCharacter->getID();

		SClan* pSClan;// = pSPlayerCharacter->getParentClan();
		DYNAMIC_ASSERT(pSClan);
		SItemManager* pSItemManager = pSClan->getItemManager();
		DYNAMIC_ASSERT(pSItemManager);
		PlayerItem** pItemArray = pSItemManager->getEquipArrayByPlayerCharacterId(charid);

        // ���һ�����͡��ͻ��ˡ�����
        GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

        // ת���ɱ�׼����ʽ
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // ���ñ�ǩ
            packet->channel = GNPC_ITEM;
            packet->type    = PT_ITEM_F2M_EQUIP_LIST;

            // ת���߼���
            PT_ITEM_F2M_EQUIP_LIST_DATA* sendData = (PT_ITEM_F2M_EQUIP_LIST_DATA*)(packet->data);
            if ( sendData )
            {
                // ����߼���
                sendData->charid = charid;
                for (Int i=1; i<ITEM_EQUIP_SLOT_TYPE_MAX; i++)
                {   
					if ( pItemArray[i] )
					{
						sendData->equipAttr[i].equipId = pItemArray[i]->getItemTempID();
						sendData->equipAttr[i].curStrengthenLv = pItemArray[i]->getItemRecord()->curStrengthenLv;
						sendData->equipAttr[i].randAppendID = pItemArray[i]->getItemRecord()->randAppendID;
						sendData->equipAttr[i].strengthenAppendID = pItemArray[i]->getItemRecord()->strengthenAppendID;
					}
					else
					{
						sendData->equipAttr[i].equipId = 0;
						sendData->equipAttr[i].curStrengthenLv = 0;
						sendData->equipAttr[i].randAppendID = 0;
						sendData->equipAttr[i].strengthenAppendID = 0;
					}	
				}		
						
                // ��������
				FrontServerMain::getInstance().getServerLauncher()->sendServer(dataPtr, 
					GameNetPacketData_INFO::headSize + PT_ITEM_F2M_EQUIP_LIST_DATA_INFO::dataSize , 
					id);
            }
        }
    }

	//--------------------------------------------------------------------------
	void ItemPacketProcesser::sendItemUseToClient( I32 id, PlayerCharacterIdType charid, U32 slotIndex,ITEM_SITE_TYPE type, item_use_res res )
	{ 
		// ���һ�����͡��ͻ��ˡ�����
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_ITEM;
			packet->type    = PT_ITEM_F2C_USE_ITEM;

			// ת���߼���
			PT_ITEM_F2C_USE_ITEM_DATA* sendData = (PT_ITEM_F2C_USE_ITEM_DATA*)(packet->data);
			if ( sendData )
			{
				// ����߼���
				sendData->charid = charid;
				sendData->slotIndex = slotIndex;
				sendData->itemType = type;
				sendData->res = res;

				// ��������
				FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					GameNetPacketData_INFO::headSize + PT_ITEM_F2C_USE_ITEM_DATA_INFO::dataSize ,
					id);
			}
		}
	}

	//---------------------------------------------------------------------------------------------------------------
    void ItemPacketProcesser::sendItemUseToMapServer( I32 id, PlayerCharacterIdType charid, U32 itemid, U32 slotIndex,ITEM_SITE_TYPE itemType )
    {
        // ���һ�����͡��ͻ��ˡ�����
        GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

        // ת���ɱ�׼����ʽ
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // ���ñ�ǩ
            packet->channel = GNPC_ITEM;
            packet->type    = PT_ITEM_F2M_USE_ITEM;

            // ת���߼���
            PT_ITEM_F2M_USE_ITEM_DATA* sendData = (PT_ITEM_F2M_USE_ITEM_DATA*)(packet->data);
            if ( sendData )
            {
                // ����߼���
                sendData->charid = charid;
                sendData->itemid = itemid;
			    //sendData->itemDBId = itemDBId;
				sendData->slotIndex = slotIndex;
				sendData->itemType = itemType;

                // ��������
				FrontServerMain::getInstance().getServerLauncher()->sendServer(dataPtr,
					GameNetPacketData_INFO::headSize + PT_ITEM_F2M_USE_ITEM_DATA_INFO::dataSize ,
					id);
            }
        }
    }

    //---------------------------------------------------------------------------------------------------------------
    void ItemPacketProcesser::recvItemUseFromClient( I32 id, PT_ITEM_C2F_USE_ITEM_DATA* pData )
    {
        SPlayerPtr pPlayer;// = SWorldManager::getInstance().getGameObjectManager()->getPlayerByClientNetId(id);
		if ( pPlayer.isNull() )
			return;

        SClan* pClan;// = pPlayer->getMainClan();
        DYNAMIC_ASSERT(pClan);

        SItemManager* pItemManager = pClan->getItemManager();
        DYNAMIC_ASSERT(pItemManager);

        item_use_res res = pItemManager->handlUseItemClient(pData->slotIndex,(ITEM_SITE_TYPE)pData->itemType,pData->charid);
		if ( res != item_use_res_Succeed ) 
			sendItemUseToClient(id, pData->charid, pData->slotIndex,(ITEM_SITE_TYPE)pData->itemType, res);
    }

	//--------------------------------------------------------------------------
	void ItemPacketProcesser::recvItemUseFromMapServer(I32 id, PT_ITEM_M2F_USE_ITEM_DATA* pData)
	{
		SPlayerPtr pSPlayerPtr;// = SWorldManager::getInstance().getGameObjectManager()->getPlayerByClientNetId(pData->netId);
		if ( pSPlayerPtr.isNull() )
			return;

		SClan* pSClan;// = pSPlayerPtr->getMainClan();
		DYNAMIC_ASSERT(pSClan);

		SItemManager* pItemManager = pSClan->getItemManager();
		DYNAMIC_ASSERT(pItemManager);

		item_use_res res = (item_use_res)pData->res;
		if ( res  ==  item_use_res_Succeed )
			res = pItemManager->handlUseItemMapServer(pData->slotIndex,(ITEM_SITE_TYPE)pData->itemType, pData->charid);

		sendItemUseToClient(pData->netId, pData->charid, pData->slotIndex,(ITEM_SITE_TYPE)pData->itemType, res);
	}

    //---------------------------------------------------------------------------------------------------------------
    void ItemPacketProcesser::sendPickItemToMapServer( I32 id, PlayerCharacterIdType charid, U32 itemindex )
    {
        // ���һ�����͡��ͻ��ˡ�����
        GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

        // ת���ɱ�׼����ʽ
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // ���ñ�ǩ
            packet->channel = GNPC_ITEM;
            packet->type    = PT_ITEM_F2M_PICK_ITEM;

            // ת���߼���
            PT_ITEM_F2M_PICK_ITEM_DATA* sendData = (PT_ITEM_F2M_PICK_ITEM_DATA*)(packet->data);
            if ( sendData )
            {
                // ����߼���
                sendData->charId = charid;
                sendData->itemIndex = itemindex;

                // ��������
				FrontServerMain::getInstance().getServerLauncher()->sendServer(dataPtr,
					GameNetPacketData_INFO::headSize + PT_ITEM_F2M_PICK_ITEM_DATA_INFO::dataSize ,
					id);
            }
        } 
    }

    //---------------------------------------------------------------------------------------------------------------
    void ItemPacketProcesser::recvPickItemFromClient( I32 id, PT_ITEM_C2F_PICK_ITEM_DATA* pData )
    {
		SPlayerPtr pPlayer;// = SWorldManager::getInstance().getPlayerByClientNetId(id);
		if ( pPlayer.isNull() )
			return;

		SClan* pSClan;// = pPlayer->getMainClan();
		DYNAMIC_ASSERT(pSClan);

		SItemManager* pSItemManager = pSClan->getItemManager();
		DYNAMIC_ASSERT(pSItemManager);

		//if ( pSItemManager->handlCheckPickItem(pData->itemTempId) )
			sendPickItemToMapServer(pPlayer->getMapServerNetID(), pData->charId, pData->itemIndex);
		//else
			//sendPickItemToClient(id);
    }

    //---------------------------------------------------------------------------------------------------------------
    void ItemPacketProcesser::recvPickItemFromMapServer( I32 id, PT_ITEM_M2F_PICK_ITEM_DATA* pData )
    {
		SPlayerPtr pSPlayerPtr;// = SWorldManager::getInstance().getGameObjectManager()->getPlayerByClientNetId(pData->netId);
		if ( pSPlayerPtr.isNull() )
			return;

		SClan* pSClan;// = pSPlayerPtr->getMainClan();
		DYNAMIC_ASSERT(pSClan);

		SItemManager* pSItemManager = pSClan->getItemManager();
		DYNAMIC_ASSERT(pSItemManager);


		if (pSItemManager->handleCheckCanAddToClanBag(pData->itemid, pData->num))
		{
             pSItemManager->handlPickItemMapServer(pData->charid, pData->itemid, pData->num);
		}
		else
		{
			//TODO:���屳������
			
		}
       
    }

	//---------------------------------------------------------------------------------------------------------------
	void ItemPacketProcesser::recvRewardItemFromMapServer( I32, PT_ITEM_M2F_ATFD_REWARD_DATA* pData )
	{
		SPlayerPtr pSPlayerPtr;// = SWorldManager::getInstance().getGameObjectManager()->getPlayerByClientNetId(pData->netId);
		if ( pSPlayerPtr.isNull() )
			return;

		SClan* pSClan;// = pSPlayerPtr->getMainClan();
		DYNAMIC_ASSERT(pSClan);

		SPlayerCharacter* pSPlayerCharacter;// = pSClan->getPlayerCharacterFromList(pData->playerCharId);
		DYNAMIC_ASSERT(pSPlayerCharacter);
		
		SItemManager* pItemManager = pSClan->getItemManager();
		DYNAMIC_ASSERT(pItemManager);
		
		pItemManager->handlRewardItemMapServer(pSPlayerCharacter, pData->groupItemId);
	}

	//--------------------------------------------------------------------------
	void ItemPacketProcesser::recvDropItemAddExpFromMapServer(I32, PT_ITEM_M2F_DROP_ITEM_ADD_EXP_DATA* pData)
	{
		SPlayerPtr pSPlayerPtr;// = SWorldManager::getInstance().getGameObjectManager()->getPlayerByAccountId(pData->accountId);
		if ( pSPlayerPtr.isNull() )
			return;

		SClan* pSClan;// = pSPlayerPtr->getMainClan();
		DYNAMIC_ASSERT(pSClan);

		SPlayerCharacter* pSPlayerCharacter;// = pSClan->getPlayerCharacterFromList(pData->charId);
		DYNAMIC_ASSERT(pSPlayerCharacter);

		SItemManager* pItemManager = pSClan->getItemManager();
		DYNAMIC_ASSERT(pItemManager);

		pItemManager->handleDropItemAddExp(pSPlayerCharacter, pData->itemId, pData->itemNum);
	}

	//---------------------------------------------------------------------------------------------------------------
	void ItemPacketProcesser::sendAddMoneyToClient( I32 id, Int num, Byte type )
	{
		// ���һ�����͡��ͻ��ˡ�����
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_ITEM;
			packet->type    = PT_ITEM_F2C_ADD_MONEY;

			// ת���߼���
			PT_ITEM_F2C_ADD_MONEY_DATA* sendData = (PT_ITEM_F2C_ADD_MONEY_DATA*)(packet->data);
			if ( sendData )
			{
				// ����߼���
				sendData->moneyNum = num;
				sendData->moneyType = type;

				// ��������
				FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					GameNetPacketData_INFO::headSize + PT_ITEM_F2C_ADD_MONEY_DATA_INFO::dataSize , 
					id);
			}
		}
	}

	//---------------------------------------------------------------------------------------------------------------
	void ItemPacketProcesser::sendAddExpToClient( I32 id, U32 num, Byte type, IdType charId, Byte charType )
	{
		// ���һ�����͡��ͻ��ˡ�����
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_ITEM;
			packet->type    = PT_ITEM_F2C_ADD_EXP;

			// ת���߼���
			PT_ITEM_F2C_ADD_EXP_DATA* sendData = (PT_ITEM_F2C_ADD_EXP_DATA*)(packet->data);
			if ( sendData )
			{
				// ����߼���
				sendData->charType	= type;
				sendData->expNum	= num;
				sendData->expType	= type;
				sendData->charId	= charId;

				// ��������
				FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					GameNetPacketData_INFO::headSize + PT_ITEM_F2C_ADD_EXP_DATA_INFO::dataSize ,
					id );
			}
		}
	}

	//---------------------------------------------------------------------------------------------------------------
	void ItemPacketProcesser::sendRewardItemToMapServer( I32 id, PlayerCharacterIdType charid, U32 groupItemId )
	{
		// ���һ�����͡��ͻ��ˡ�����
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_ITEM;
			packet->type    = PT_ITEM_C2M_ATFD_REWARD;

			// ת���߼���
			PT_ITEM_C2M_ATFD_REWARD_DATA* sendData = (PT_ITEM_C2M_ATFD_REWARD_DATA*)(packet->data);
			if ( sendData )
			{
				// ����߼���
				sendData->playerCharId = charid;
				sendData->groupItemId = groupItemId;

				// ��������
				FrontServerMain::getInstance().getServerLauncher()->sendServer(dataPtr,
					GameNetPacketData_INFO::headSize + PT_ITEM_C2M_ATFD_REWARD_DATA_INFO::dataSize ,
					id);
			}
		} 
	}

	//---------------------------------------------------------------------------------------------------------------
	void ItemPacketProcesser::sendRewardItemToClient( I32 id )
	{
		// ���һ�����͡��ͻ��ˡ�����
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_ITEM;
			packet->type    = PT_ITEM_F2C_ATFD_REWARD;

			// ת���߼���
			
			// ��������
			FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,GameNetPacketData_INFO::headSize, id);
		}
	}

	//----------------------------------------------------------------------------------------------------
	void	ItemPacketProcesser::sendPickItemToClient(I32 id)
	{
		// ���һ�����͡��ͻ��ˡ�����
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_ITEM;
			packet->type    = PT_ITEM_F2C_PICK_ITEM;

			// ת���߼���

			// ��������
			FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,GameNetPacketData_INFO::headSize, id);
		}
	}

	//---------------------------------------------------------------------------------------------------------------
	void ItemPacketProcesser::recvRewardItemFromClient( I32 id, PT_ITEM_C2M_ATFD_REWARD_DATA* pData )
	{
		SPlayerPtr pSPlayerPtr;// = SWorldManager::getInstance().getGameObjectManager()->getPlayerByClientNetId(id);
		if ( pSPlayerPtr.isNull() )
			return;
		
		SClan* pSClan;// = pSPlayerPtr->getMainClan();
		DYNAMIC_ASSERT(pSClan);

		SItemManager* pSItemManager = pSClan->getItemManager();
		DYNAMIC_ASSERT(pSItemManager);
		
		if ( pSItemManager->handleCheckCanAddToClanBag(pData->groupItemId) )
			sendRewardItemToMapServer(pSPlayerPtr->getMapServerNetID(), pData->playerCharId, pData->groupItemId);
		else
			sendRewardItemToClient(id);
	}

	//---------------------------------------------------------------------------------------------------------------
	void ItemPacketProcesser::recvRewardItemAssociateQuestFromClient( I32 id,PT_ITEM_C2F_QUEST_REWARD_DATA* pData )
	{
		SPlayerPtr pSPlayerPtr;// = SWorldManager::getInstance().getGameObjectManager()->getPlayerByClientNetId(id);
		if ( pSPlayerPtr.isNull() )
			return;
		
		SClan* pSClan;// = pSPlayerPtr->getMainClan();
		DYNAMIC_ASSERT(pSClan);

		SPlayerCharacter* pSPlayerCharacter;// = pSClan->getPlayerCharacterFromList(pData->playerCharId);
		DYNAMIC_ASSERT(pSPlayerCharacter);

		SItemManager* pItemManager = pSClan->getItemManager();
		DYNAMIC_ASSERT(pItemManager);
        
		//����ս�������Ľӿڣ���Ҫ�Ļ����Ժ󵥶�����
		pItemManager->handlRewardItemMapServer(pSPlayerCharacter, pData->groupItemId);

	}

	//---------------------------------------------------------------------------------------------------------------
	void ItemPacketProcesser::sendItemUpdateNumListToClient( I32 id,std::vector<PlayerItem*>* pItemList )
	{
		DYNAMIC_ASSERT(pItemList);

		// �õ�һ�����ͷ��ͻ���
		GameNetSendDataBufferPtr dataPtr;
		GameNetPacketData* packet       = NULL;
		PT_ITEM_S2C_UPDATE_NUM_lIST_DATA* sendData = NULL;

		// ��ǰ��������ͷ��С
		I32 sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_ITEM_S2C_UPDATE_NUM_lIST_DATA_INFO::headSize;
		// ��ǰ�������ݴ�С
		I32 sendDataSize        = sendDataHeadSize;
		// ׼���������ݴ�С
		I32 prepareSendDataSize = sendDataHeadSize;

		// �����������
		std::vector< PlayerItem*>::iterator front     = pItemList->begin();
		std::vector< PlayerItem*>::iterator back      = pItemList->end();
		while (front != back)
		{
			//----------------------------------------------------------------------------------------------------

			if ( dataPtr.isNull() == false )
			{
				// ����һ����Ʒ���ݴ�С���������ݻ����С
				prepareSendDataSize = sendDataSize + PT_ITEM_S2C_UPDATE_NUM_lIST_DATA_INFO::updateDataSize;

				// ������ڻ�������С����
				if ( prepareSendDataSize >= dataPtr->getLogicDataMaxSize() )
				{
					FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,sendDataSize, id);

					dataPtr.setNull();
				}
			}

			//----------------------------------------------------------------------------------------------------

			if ( dataPtr.isNull() )
			{
				// �õ�һ�����ͷ��ͻ���
				FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );
				packet       = (GameNetPacketData*) dataPtr->getLogicData();
				if ( !packet )
					return;
				
				packet->channel = GNPC_ITEM;
				packet->type    = PT_ITEM_S2C_UPDATE_NUM_LIST;
				sendData = (PT_ITEM_S2C_UPDATE_NUM_lIST_DATA*)(packet->data);
				// ���
				sendData->account = 0;

				// ��ǰ��������ͷ��С
				sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_ITEM_S2C_UPDATE_NUM_lIST_DATA_INFO::headSize;
				// ��ǰ�������ݴ�С
				sendDataSize        = sendDataHeadSize;
				// ׼���������ݴ�С
				prepareSendDataSize = sendDataHeadSize;
			}

			//----------------------------------------------------------------------------------------------------
			
			// ���������¼
			PT_ITEM_S2C_UPDATE_NUM_DATA& updateNumData = sendData->data[sendData->account];
			updateNumData.curNum = (*front)->getItemNum();
			updateNumData.slotIndex =  (*front)->getItemIndex();
            updateNumData.belongPos = (*front)->getItemSiteType();

			// ��������
			sendDataSize += PT_ITEM_S2C_UPDATE_NUM_lIST_DATA_INFO::updateDataSize;
			++sendData->account;
			++front;   
		}

		// �����ʣ������
		if ( dataPtr.isNull() == false )
		{
			FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,sendDataSize, id);
			dataPtr.setNull();
		}
	}
	//---------------------------------------------------------------------------------------------------------------
	void ItemPacketProcesser::sendBeginAddItemListToClient( I32 id )
	{
		// ���һ�����͡��ͻ��ˡ�����
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_ITEM;
			packet->type    = PT_ITEM_S2C_ADDLIST_BEGIN;

			// ת���߼���

			// ��������
			FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,GameNetPacketData_INFO::headSize, id);
		}
	}
}