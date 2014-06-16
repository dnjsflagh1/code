//**************************************************************************************************************
#include "stdafx.h"
#include "ItemPacketProcesser.h"
#include "ClientNetApplyManager.h"
#include "CItemManager.h"
#include "CSceneManager.h"
#include "CPlayerCharacterEntity.h"
#include "CPlayer.h"
#include "CClan.h"
#include "CCharacter.h"
#include "UIPveScore.h"
#include "MessageManager.h"
#include "ItemData.h"
#include "ISceneNodeAction.h"
#include "CItemEntity.h"
//**************************************************************************************************************
namespace MG
{
    MG::Bool ItemPacketProcesser::processFrontServerPacket( I32 id, NetEventRecv* packet )
    {
        if ( packet->getChannel() == GNPC_ITEM )
        {
            GameNetPacketData* pData = (GameNetPacketData*)packet->getData();
            DYNAMIC_ASSERT( pData );

            switch (pData->type)
            {
            case PT_ITEM_S2C_ADDLIST:
                recvItemList( id, (PT_ITEM_S2C_ADDLIST_DATA*)(pData->data) );
                break;
            case PT_ITEM_S2C_ADDLIST_BEGIN:
				recvBeginAddItemList();
                break;
            case PT_ITEM_S2C_ADD:
                recvAddItem( id, (PT_ITEM_S2C_ADD_DATA*)(pData->data) );
                break;
            case PT_ITEM_S2C_DELETE:
                recvDelItem( id, (PT_ITEM_S2C_DELETE_DATA*)(pData->data) );
                break;
            case PT_ITEM_S2C_CHANGEPOS:
                recvChangePos( id, (PT_ITEM_S2C_CHANGEPOS_DATA*)(pData->data) );
                break;
            case PT_ITEM_S2C_SPLIT:
                recvSplitItem(id, (PT_ITEM_S2C_SPLIT_DATA*)(pData->data));
                break;
            case PT_ITEM_F2C_USE_ITEM:
                recvUseItem(id, (PT_ITEM_F2C_USE_ITEM_DATA*)(pData->data));
                break;
            case PT_ITEM_M2C_EQUIP_LIST:
                recvEquipListFromMS(id, (PT_ITEM_M2C_EQUIP_LIST_DATA*)(pData->data));
                break;
            case PT_ITEM_M2C_CHANGE_EQUIP:
                recvChangeEquipFromMS(id, (PT_ITEM_M2C_CHANGE_EQUIP_DATA*)(pData->data));
                break;
            case PT_ITEM_M2C_PICK_ITEM:
                recvPickItemFromMS(id, (PT_ITEM_M2C_PICK_ITEM_DATA*)(pData->data));
                break;
			case PT_ITEM_F2C_ATFD_REWARD:
				recvRewardFromFS(id);
				break;
			case PT_ITEM_F2C_PICK_ITEM:
				recvPickItemFromFS(id);
				break;
			case PT_ITEM_M2C_ATFD_REWARD:
				recvRewardFromMS(id, (PT_ITEM_M2C_ATFD_REWARD_DATA*)(pData->data));
				break;
			case PT_ITEM_F2C_ADD_MONEY:
				recvAddMoney(id, (PT_ITEM_F2C_ADD_MONEY_DATA*)(pData->data));
				break;
			case PT_ITEM_F2C_ADD_EXP:
				recvAddExp(id, (PT_ITEM_F2C_ADD_EXP_DATA*)(pData->data));
				break;
			case PT_ITEM_M2C_DROP_ITEM_LIST:
				recvDropItemListFromMS(id, (PT_ITEM_M2C_DROP_ITEM_LIST_DATA*)(pData->data));
				break;
			case PT_ITEM_M2C_DROP_ITEM_DISAPPEAR:
				recvDropItemDisappear(id, (PT_ITEM_M2C_DROP_ITEM_DISAPPEAR_DATA*)(pData->data));
				break;
			case PT_ITEM_S2C_UPDATE_NUM_LIST:
				recvUpdateItemNum(id, (PT_ITEM_S2C_UPDATE_NUM_lIST_DATA*)(pData->data));
				break;
			default:
				{
					DYNAMIC_ASSERT(0);
				}
				break;
            }

            return true;
        }

        return false;
    }
    //-------------------------------------------------------------------------------------------------------
    void ItemPacketProcesser::recvItemList( I32 id, PT_ITEM_S2C_ADDLIST_DATA* pData )
    {
        for (U32 i=0; i<pData->num; i++)
        {
           // CItemManager::getInstance().addItem( &(pData->xItemRecord[i]), (ITEM_SITE_TYPE)(pData->xItemRecord[i].belongPos), false, pData->xItemRecord[i].characterId);
            CItemManager::getInstance().handlAddItem(&pData->xItemRecord[i]);
        }
    }
    //-------------------------------------------------------------------------------------------------------
    void ItemPacketProcesser::recvAddItem( I32 id, PT_ITEM_S2C_ADD_DATA* pData )
    {
		const ItemInfo* itemInfo = ItemTemplate::getInstance().getItemInfo(pData->xItemRecord.itemTempID);
        MessageManager::getInstance().addChatMsgForTest(L"��� %s ��Ʒ", itemInfo->getItemBaseItemName().c_str());
		CItemManager::getInstance().handlAddItem(&pData->xItemRecord);
    }
    //-------------------------------------------------------------------------------------------------------
    void ItemPacketProcesser::recvDelItem( I32 id, PT_ITEM_S2C_DELETE_DATA* pData )
    {
        if ( pData->res == itembag_del_res_Succeed )
        {
            CItemManager::getInstance().handlDelItem(pData->xItemDBID, (ITEM_SITE_TYPE)pData->type, pData->id);
        }
        else
        {
            //֪ͨϵͳ��Ϣ����
        }
    }
    //-------------------------------------------------------------------------------------------------------
    void ItemPacketProcesser::recvChangePos( I32 id, PT_ITEM_S2C_CHANGEPOS_DATA* pData )
    {
        
		if ( pData->res == item_changepos_res_Succeed )
        {
            CItemManager::getInstance().handlChangItem(pData->IndexSend, pData->IndexRecv, (ITEM_SITE_TYPE)pData->sendType, (ITEM_SITE_TYPE)pData->recvType, pData->id);
        }
        else if (pData->res == item_changepos_res_Error_character_level)
        {
			MessageManager::getInstance().addChatMsgForTest(L"�ȼ�����!");
        }
       
    }
    //---------------------------------------------------------------------------------------------
    void ItemPacketProcesser::sendDelItem( ITEM_SITE_TYPE type, IdType itemDBID, PlayerCharacterIdType charid /*= 0*/ )
    {
        // ���һ�����͡�����ˡ�����
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // ת���ɱ�׼����ʽ
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // ���ñ�ǩ
            packet->channel = GNPC_ITEM;
            packet->type    = PT_ITEM_C2S_DELETE;

            // ת���߼���
            PT_ITEM_C2S_DELETE_DATA* sendData = (PT_ITEM_C2S_DELETE_DATA*)(packet->data);
            if ( sendData )
            {
                // ����߼���
                sendData->type = type;
                sendData->xItemDBID = itemDBID;
                sendData->id = charid;

                // ��������
                ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_ITEM_C2S_DELETE_DATA_INFO::dataSize );
            }
        }
    }
    //---------------------------------------------------------------------------------------------
    void ItemPacketProcesser::sendChangePos( U32 sendIndex, U32 recvIndex, ITEM_SITE_TYPE sendtype, ITEM_SITE_TYPE recvtype, PlayerCharacterIdType charid )
    {
        // ���һ�����͡�����ˡ�����
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // ת���ɱ�׼����ʽ
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // ���ñ�ǩ
            packet->channel = GNPC_ITEM;
            packet->type    = PT_ITEM_C2S_CHANGEPOS;

            // ת���߼���
            PT_ITEM_C2S_CHANGEPOS_DATA* sendData = (PT_ITEM_C2S_CHANGEPOS_DATA*)(packet->data);
            if ( sendData )
            {
                // ����߼���
                sendData->IndexSend = sendIndex;
                sendData->IndexRecv = recvIndex;
                sendData->sendType = sendtype;
                sendData->recvType = recvtype;
                sendData->id = charid;

                // ��������
                ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_ITEM_C2S_CHANGEPOS_DATA_INFO::dataSize );
            }
        }
    }
    //---------------------------------------------------------------------------------------------
    void ItemPacketProcesser::sendSplitItem( IdType itemid, ITEM_SITE_TYPE selftype, ITEM_SITE_TYPE splittype, UInt splitpos, UInt splitnum, PlayerCharacterIdType charid )
    {
        // ���һ�����͡�����ˡ�����
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // ת���ɱ�׼����ʽ
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // ���ñ�ǩ
            packet->channel = GNPC_ITEM;
            packet->type    = PT_ITEM_C2S_SPLIT;

            // ת���߼���
            PT_ITEM_C2S_SPLIT_DATA* sendData = (PT_ITEM_C2S_SPLIT_DATA*)(packet->data);
            if ( sendData )
            {
                // ����߼���
               /* sendData->xItemDBID = itemid;
                sendData->selfType = selftype;
                sendData->splitType = splittype;
                sendData->splitPos = splitpos;
                sendData->splitNum = splitnum;
                sendData->id = charid;
				*/

                // ��������
                ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_ITEM_C2S_SPLIT_DATA_INFO::dataSize );
            }
        }
    }
	//---------------------------------------------------------------------------------------------
	void ItemPacketProcesser::sendSplitItem( U32 slotIndex, ITEM_SITE_TYPE selfType, ITEM_SITE_TYPE splitType, U32 selectSlot, U32 num, PlayerCharacterIdType id /*= 0*/ )
	{
		// ���һ�����͡�����ˡ�����
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_ITEM;
			packet->type    = PT_ITEM_C2S_SPLIT;

			// ת���߼���
			PT_ITEM_C2S_SPLIT_DATA* sendData = (PT_ITEM_C2S_SPLIT_DATA*)(packet->data);
			if ( sendData )
			{
				// ����߼���
				sendData->selfSlot = slotIndex;
				sendData->selfType = selfType;
				sendData->splitType = splitType;
				//sendData->splitPos = pos;
				sendData->selectIndex = selectSlot;
				sendData->splitNum = num;
				sendData->characterId = id;

				// ��������
				ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
					GameNetPacketData_INFO::headSize + PT_ITEM_C2S_SPLIT_DATA_INFO::dataSize );
			}
		}
	}
	//---------------------------------------------------------------------------------------------
    void ItemPacketProcesser::sendUseItem( IdType itemid, PlayerCharacterIdType charid )
    {
		/*
        // ���һ�����͡�����ˡ�����
        NetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // ת���ɱ�׼����ʽ
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getData();
        if ( packet )
        {
            // ���ñ�ǩ
            packet->channel = GNPC_ITEM;
            packet->type    = PT_ITEM_C2F_USE_ITEM;

            // ת���߼���
            PT_ITEM_C2F_USE_ITEM_DATA* sendData = (PT_ITEM_C2F_USE_ITEM_DATA*)(packet->data);
            if ( sendData )
            {
                // ����߼���
               // sendData->itemId = itemid;
                sendData->charid = charid;

                // ��������
                ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_ITEM_C2F_USE_ITEM_DATA_INFO::dataSize );
            }
        }
		*/
    }

	void ItemPacketProcesser::sendUseItem( U32 slotIndex,ITEM_SITE_TYPE itemType, PlayerCharacterIdType charid )
	{
		
		// ���һ�����͡�����ˡ�����
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_ITEM;
			packet->type    = PT_ITEM_C2F_USE_ITEM;

			// ת���߼���
			PT_ITEM_C2F_USE_ITEM_DATA* sendData = (PT_ITEM_C2F_USE_ITEM_DATA*)(packet->data);
			if ( sendData )
			{
				// ����߼���
				// sendData->itemId = itemid;
				sendData->charid = charid;
				sendData->itemType = itemType;
				sendData->slotIndex = slotIndex;

				// ��������
				ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
				GameNetPacketData_INFO::headSize + PT_ITEM_C2F_USE_ITEM_DATA_INFO::dataSize );
			}
		}
		
 
	}
	//---------------------------------------------------------------------------------------------
    void ItemPacketProcesser::recvSplitItem( I32 id, PT_ITEM_S2C_SPLIT_DATA* pData )
    {
        if ( pData->res == item_split_res_Succeed )
			CItemManager::getInstance().handlSplitItem( pData->selfSlot, (ITEM_SITE_TYPE)pData->selfType, (ITEM_SITE_TYPE)pData->splitType, 
			pData->selectIndex, pData->splitNum, pData->characterId);
        else
        {
            //֪ͨϵͳ��Ϣ����
        }
    }
    //---------------------------------------------------------------------------------------------
    void ItemPacketProcesser::recvUseItem( I32 id, PT_ITEM_F2C_USE_ITEM_DATA* pData )
    {
        if ( pData->res == item_use_res_Succeed )
		{    
			CItemManager::getInstance().handlUseItem(pData->slotIndex,(ITEM_SITE_TYPE)pData->itemType, pData->charid);
		}
        else if (pData->res == item_use_res_Error_ClanBag_Full)
        { 
			MessageManager::getInstance().addChatMsgForTest(L"��������,�޷������Ʒ!");
        }
        
    }
    //---------------------------------------------------------------------------------------------
    void ItemPacketProcesser::recvEquipListFromMS( I32 id, PT_ITEM_M2C_EQUIP_LIST_DATA* pData )
    {
        CPlayerCharacterEntity* pEntity = CSceneManager::getInstance().getPlayerCharacterEntity(pData->charid);
        //DYNAMIC_ASSERT(pEntity);

        if ( pEntity == NULL ) return;

        for (Int i=1; i<ITEM_EQUIP_SLOT_TYPE_MAX; i++)
        {
			pEntity->attachItem(pData->equipId[i], (ITEM_EQUIP_SLOT_TYPE)i);
        } 

		pEntity->applyActionGroup();
    }
    //---------------------------------------------------------------------------------------------
    void ItemPacketProcesser::recvChangeEquipFromMS( I32 id, PT_ITEM_M2C_CHANGE_EQUIP_DATA* pData )
    {
        CPlayerCharacterEntity* pEntity = CSceneManager::getInstance().getPlayerCharacterEntity(pData->charid);

        DYNAMIC_ASSERT_LOG( pEntity != NULL, "not find equip!");

        if ( pEntity == NULL ) return;

        if ( pData->putonEquipId )
		{
            pEntity->attachItem( pData->putonEquipId, (ITEM_EQUIP_SLOT_TYPE)(pData->pos) );
		}
        else
        {
            pEntity->detachItem( (ITEM_EQUIP_SLOT_TYPE)(pData->pos) );
        }

		pEntity->applyActionGroup();
    }
    //---------------------------------------------------------------------------------------------
    void ItemPacketProcesser::recvPickItemFromMS( I32 id, PT_ITEM_M2C_PICK_ITEM_DATA* pData )
    {
		CSceneManager::getInstance().destroyItemEntity(pData->index);
		
		//ȥ�������еĵ���ʵ��
		//?

        //��ʾxxx���xx��xx��
        //��
    }
    //---------------------------------------------------------------------------------------------
    void ItemPacketProcesser::sendPickItem( U32 itemIndex, PlayerCharacterIdType charId, Int itemTemplateId, Int itemNum)
    {
		//�ȼ�����屳���Ƿ�����
		if(!CItemManager::getInstance().handleCheckCanAddToClanBag(itemTemplateId,itemNum))
		{
			MessageManager::getInstance().addChatMsgForTest(L"��������������ʰȡ!");
			return;
		}
		// ���һ�����͡�����ˡ�����
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // ת���ɱ�׼����ʽ
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // ���ñ�ǩ
            packet->channel = GNPC_ITEM;
            packet->type    = PT_ITEM_C2F_PICK_ITEM;

            // ת���߼���
            PT_ITEM_C2F_PICK_ITEM_DATA* sendData = (PT_ITEM_C2F_PICK_ITEM_DATA*)(packet->data);
            if ( sendData )
            {
                // ����߼���
                sendData->itemIndex = itemIndex;
                sendData->charId = charId;
				sendData->itemTempId = itemTemplateId;

                // ��������
                ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_ITEM_C2F_PICK_ITEM_DATA_INFO::dataSize );
            }
        }
    }
	
	//---------------------------------------------------------------------------------------------
	void ItemPacketProcesser::sendRewardItem( U32 groupItemId, PlayerCharacterIdType playerCharId )
	{
		// ���һ�����͡�����ˡ�����
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

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
				sendData->groupItemId  = groupItemId;
				sendData->playerCharId = playerCharId;

				// ��������
				ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
					GameNetPacketData_INFO::headSize + PT_ITEM_C2M_ATFD_REWARD_DATA_INFO::dataSize );
			}
		}
	}
	//---------------------------------------------------------------------------------------------
	void ItemPacketProcesser::recvDropItemListFromMS( I32 id, PT_ITEM_M2C_DROP_ITEM_LIST_DATA* pData )
	{
		//�յ����������Ʒ�İ���
		//����Ӧ�ô�����Ʒentity
		//���뵽�����С�

        DYNAMIC_ASSERT_LOG( pData->nCount < 100, "recvDropItemListFromMS Too Much!" );

		for(UInt i = 0; i < pData->nCount; ++i)
		{
			netDropItemData* netDropItemInfo = &(pData->data[i]);

			Vec3 dir(1,0,0);
			Vec3 dropStartPos(netDropItemInfo->pos.x, 0, netDropItemInfo->pos.y);
			Int angle = MGRandom::getInstance().rand_ab_One(0, 360);
			dir = MGMath::rotateVector(dir, angle * (MG_PI / 180));
			Int dis = MGRandom::getInstance().rand_ab_One(1, 3);
			Vec3 dropEndPos = dropStartPos + dir * dis;

			ItemEntityData data;
			data.mId = netDropItemInfo->index;
			data.mItemNum = netDropItemInfo->num;
			data.mItemTemplateId = netDropItemInfo->itemTempId;
			data.mPos = dropEndPos;
			//data.mPos.x = netDropItemInfo->pos.x;
			//data.mPos.z = netDropItemInfo->pos.y;


			CItemEntity* itemEntity = CSceneManager::getInstance().createItemEntity(&data);
			if(!itemEntity)
			{
				return;
			}

			//itemEntity->parabolaDrop(data.mPos);
		}
	}
	//---------------------------------------------------------------------------------------------
	void ItemPacketProcesser::recvRewardFromMS( I32 id, PT_ITEM_M2C_ATFD_REWARD_DATA* pData )
	{
		//�յ���֮�󣬿��Ƿ���ʾ�������档
		if ( pData->isShow )
		{

			//��ʾ��������;
			UIPveScore::getInstance().openGui();
			
			//����UIPveCreate ��ʾʱ��
			UIPveScore::getInstance().setCloseTime();
			UIPveScore::getInstance().setGroupItemId(pData->groupItemId);
		}
		else
		{
			//��ʾ�Ƿ�������
		}
	}
	//---------------------------------------------------------------------------------------------
	void ItemPacketProcesser::recvAddMoney( I32 id, PT_ITEM_F2C_ADD_MONEY_DATA* pData )
	{
		CItemManager::getInstance().handlAddMoney(pData->moneyNum, pData->moneyType);
	}
	//---------------------------------------------------------------------------------------------
	void ItemPacketProcesser::recvAddExp( I32 id, PT_ITEM_F2C_ADD_EXP_DATA* pData )
	{
		CItemManager::getInstance().handlAddExp(pData->expNum, pData->expType, pData->charId, pData->charType);
	}
	//---------------------------------------------------------------------------------------------
	void ItemPacketProcesser::recvRewardFromFS( I32 id )
	{
		//��ʾ������������������
	}
	//---------------------------------------------------------------------------------------------
	void ItemPacketProcesser::recvPickItemFromFS( I32 id )
	{
		//��ʾ������������������
	}

    //---------------------------------------------------------------------------------------------
	void ItemPacketProcesser::recvDropItemDisappear(I32 id, PT_ITEM_M2C_DROP_ITEM_DISAPPEAR_DATA* pData)
	{
		CSceneManager::getInstance().destroyItemEntity(pData->index);
	}
	//---------------------------------------------------------------------------------------------
	void ItemPacketProcesser::sendRewardItemAssociateQuest( U32 groupItemId, PlayerCharacterIdType playerCharId )
	{
		// ���һ�����͡�����ˡ�����
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_ITEM;
			packet->type    = PT_ITEM_C2F_QUEST_REWARD;

			// ת���߼���
			PT_ITEM_C2F_QUEST_REWARD_DATA* sendData = (PT_ITEM_C2F_QUEST_REWARD_DATA*)(packet->data);
			if ( sendData )
			{
				// ����߼���
				sendData->groupItemId  = groupItemId;
				sendData->playerCharId = playerCharId;

				// ��������
				ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
					GameNetPacketData_INFO::headSize + PT_ITEM_C2F_QUEST_REWARD_DATA_INFO::dataSize );
			}
		}
	}
    //---------------------------------------------------------------------------------------------
	void ItemPacketProcesser::recvUpdateItemNum( I32 id,PT_ITEM_S2C_UPDATE_NUM_lIST_DATA* pData )
	{
         CItemManager::getInstance().handUpdateItemNum(pData->data,pData->account);
	}
	//---------------------------------------------------------------------------------------------
	void ItemPacketProcesser::recvBeginAddItemList()
	{
		CItemManager::getInstance().handleClearAllItem();
	}
	//---------------------------------------------------------------------------------------------

}