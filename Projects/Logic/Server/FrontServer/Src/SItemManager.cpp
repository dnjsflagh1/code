//**********************************************************************************************************
#include "stdafx.h"
#include "SItemManager.h"
#include "PlayerItemFactory.h"
#include "ItemDBOp.h"
#include "FrontServerMain.h"
#include "SClan.h"
#include "ItemPacketProcesser.h"
#include "GenrealEquip.h"
#include "GenrealItem.h"
#include "SPlayer.h"
#include "GameJudge.h"
#include "SPlayerCharacter.h"
#include "ItemGroupTemplate.h"
#include "SAttributeNetPacketProcesser.h"
#include "PlayerCharacterDB.h"
#include "ClanDataBase.h"
#include "ItemMoneyTemplate.h"
#include "CharacterLvlTemplate.h"
#include "SClanQuestManager.h"
#include "ItemExpListCsv.h"
//**********************************************************************************************************
namespace MG
{
    SItemManager::SItemManager()
        :mParent(NULL)
    {
    }
    //----------------------------------------------------------------------------------------
    SItemManager::~SItemManager()
    {
    }
    //----------------------------------------------------------------------------------------
    void SItemManager::handlAddItem( U32 itemTempID, U32 num )
    {
        //�˺�����һ���Ǽӵ�����ֿ⡣
		Bool isNeedOverlay = getClanItems()->checkIsNeedOverlay(itemTempID);
		if (isNeedOverlay)
		{
			_handAddItemOverlay(itemTempID,num);
		}
		else
		{    //����Ҫ�жϵ���
             for (Int i = 0; i<num;i++)
             {  
				 _addItemToOneSlot(itemTempID,1);
             }
		}

		//�ж��Ƿ���������Ʒ,�Ժ������������Ʒ�������������
		SClanQuestManager*  questManager = getSClanQuestManager();
		for (Int i = 0;i <num; i++)
		{
			questManager->notifyGetOrDropItem(itemTempID,true);
		}

       
    }
    //----------------------------------------------------------------------------------------
    void SItemManager::handlAddItem( PlayerItem* pItem )
    {
        //�����λ��;
        ItemManager::addItem(pItem, ITEM_SITE_TYPE_CLAN, true, 0);
		updateClanItemToDB();
    }
    //----------------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------------
    itembag_del_res SItemManager::handlDelItem(IdType itemDBID, ITEM_SITE_TYPE type, PlayerCharacterIdType id)
    {
		if (type == ITEM_SITE_TYPE_CLAN)
		{
			//�����ж�,ֻ���Ǳ���
			PlayerItem* pItem = findItem(itemDBID,type,id);
			SClanQuestManager*  questManager = getSClanQuestManager();
			for (Int i = 0;i <pItem->getItemNum(); i++)
			{
				questManager->notifyGetOrDropItem(pItem->getItemTempID(),false);
			}
		}
		//����ɾ��ֻ�����ֿ���
        //1�������ڣ�2������ɾ����3�����治��ɾ������
        ITEM_DELETE_ERROR  errotType = ItemManager::deleteItem(itemDBID, type, id);
        if ( errotType == ITEM_DELETE_ERROR_SUCCEED )
		{
			if (type == ITEM_SITE_TYPE_CLAN)
			{
				updateClanItemToDB();
			}
			else if (type == ITEM_SITE_TYPE_CHARACTER_BAG || type == ITEM_SITE_TYPE_CHARACTER_EQUIP)
			{
				updatePlayerCharacterItemToDB(id);
			}
		}
		ItemPacketProcesser::getInstance().sendItemDelToClient(mParent->getParentPlayer()->getClientNetID(),type,itemDBID,(itembag_del_res)(Int)errotType,id);
        
		return (itembag_del_res)(Int)errotType;

    }
	
	//----------------------------------------------------------------------------------------
	MG::itembag_del_res SItemManager::handlDelItem( U32 slotIndex, ITEM_SITE_TYPE type, PlayerCharacterIdType id )
	{
		 
         ITEM_DELETE_ERROR  errotType = ItemManager::deleteItem(slotIndex, type, id);
		 if ( errotType == ITEM_DELETE_ERROR_SUCCEED )
		 {
			 if (type == ITEM_SITE_TYPE_CLAN)
			 {
				 updateClanItemToDB();
			 }
			 else if (type == ITEM_SITE_TYPE_CHARACTER_BAG || type == ITEM_SITE_TYPE_CHARACTER_EQUIP)
			 {
				 updatePlayerCharacterItemToDB(id);
			 }
		 }
		//ItemPacketProcesser::getInstance().sendItemDelToClient(mParent->getClientNetId(),type,(itembag_del_res)(Int)errotType,id);	 
		  return (itembag_del_res)(Int)errotType;
	}
//----------------------------------------------------------------------------------------
    MG::item_changepos_res SItemManager::handlChangItem( U32 sendIndex, U32 recvIndex, ITEM_SITE_TYPE sendtype, ITEM_SITE_TYPE recvtype, PlayerCharacterIdType charId )
    {
        //�����������ǲ�ͬ���潻��
        PlayerItem* pSendItem = findItem(sendIndex, sendtype, charId); 
        PlayerItem* pRecvItem = findItem(recvIndex, recvtype, charId);

		// û����Ʒ���˳�
		if ( pSendItem == NULL )
			return item_changepos_res_Error_notchange;

        //�����һ����װ����
        if ( sendtype != recvtype  &&  ( sendtype == ITEM_SITE_TYPE_CHARACTER_EQUIP  ||  recvtype == ITEM_SITE_TYPE_CHARACTER_EQUIP  ) )
        {
            //����λ��
            if ( pRecvItem )
            {
                //�������װ��
                if ( pSendItem->getItemType() != ITEM_TYPE_EQUIP_GENERAL  ||  pRecvItem->getItemType() != ITEM_TYPE_EQUIP_GENERAL )
                    return item_changepos_res_Error_notEquip;
                //���λ�ò�ƥ��;
                if ( pSendItem->getItemEquipSlotType() != pRecvItem->getItemEquipSlotType() )
                    return item_changepos_res_Error_Equip_pos;
			  
				//����&��ɫ�ж�
				SPlayerCharacterPtr pSPlayerCharacter;
				mParent->getPlayerCharacter(pSPlayerCharacter, charId);
				//SPlayerCharacter* pSPlayerCharacter = mParent->getPlayerCharacterFromList(charId);
				//if ( pSPlayerCharacter == NULL )
				//	return item_changepos_res_Error_unknown;

			  GAMEJUDGE_TYPE judgeType =  GameJudge::getInstance().checkGameJudge(
					mParent,
					pSPlayerCharacter.getPointer(),
					pSendItem->getItemInfo()->getItemBaseClanJudgeID(),
					pSendItem->getItemInfo()->getItemBaseCharacterJudgeID() 
					);
                if (judgeType != GAMEJUDGE_TYPE_SUCCESS)
                {
                    if (judgeType == GAMEJUDGE_TYPE_CHARACTER_LEVEL_ERROR)
                    {
						return item_changepos_res_Error_character_level;
                    }
                }

                //����playerItem;
				ItemManager::removeItem(sendIndex, sendtype, charId);
				ItemManager::removeItem(recvIndex, recvtype, charId);
               

                pRecvItem->setItemIndex(sendIndex);
                pSendItem->setItemIndex(recvIndex);
                ItemManager::addItem(pRecvItem, sendtype, true, charId);
                ItemManager::addItem(pSendItem, recvtype, true, charId);
                //֪ͨDB                  
				if (sendtype == ITEM_SITE_TYPE_CLAN  ||  recvtype == ITEM_SITE_TYPE_CLAN)
				{   
					 updateClanItemToDB();
					 updatePlayerCharacterItemToDB(charId);
				}
				else
				{
					updatePlayerCharacterItemToDB(charId);
				}
				
                //֪ͨMapSever
                if ( sendtype == ITEM_SITE_TYPE_CHARACTER_EQUIP )   
                    sendChangeEquipToMaqServer(charId, pRecvItem, sendIndex);
                else
                    sendChangeEquipToMaqServer(charId, pSendItem, recvIndex); 
				
				return item_changepos_res_Succeed;
            }
            else 
            {
                //��װ����������
                if ( sendtype == ITEM_SITE_TYPE_CHARACTER_EQUIP )
                {   
                    //����playerItem;
                    ItemManager::removeItem(sendIndex, sendtype, charId);
                    pSendItem->setItemIndex(recvIndex);
                    ItemManager::addItem(pSendItem, recvtype, true, charId);
                    //֪ͨDB                      ;
					if (sendtype == ITEM_SITE_TYPE_CLAN  ||  recvtype == ITEM_SITE_TYPE_CLAN)
					{   
						updateClanItemToDB();
						updatePlayerCharacterItemToDB(charId);
					}
					else
					{
						updatePlayerCharacterItemToDB(charId);
					}
                    //֪ͨMapSever
                    sendChangeEquipToMaqServer(charId, NULL, sendIndex);

					return item_changepos_res_Succeed;
                }
                //��װ��
                else
                {
                    //�������װ��
                    if ( pSendItem->getItemType() != ITEM_TYPE_EQUIP_GENERAL )
                        return item_changepos_res_Error_notEquip;
                    //���λ�ò�ƥ��;
                    if ( pSendItem->getItemEquipSlotType() != recvIndex )
                        return item_changepos_res_Error_Equip_pos;
                     
					//����&��ɫ�ж�
					SPlayerCharacterPtr pSPlayerCharacter;
					mParent->getPlayerCharacter(pSPlayerCharacter, charId);
					//SPlayerCharacter* pSPlayerCharacter = mParent->getPlayerCharacterFromList(charId);
					//if ( pSPlayerCharacter == NULL )
					//	return item_changepos_res_Error_unknown;

					GAMEJUDGE_TYPE judgeType =  GameJudge::getInstance().checkGameJudge(
						mParent,
						pSPlayerCharacter.getPointer(),
						pSendItem->getItemInfo()->getItemBaseClanJudgeID(),
						pSendItem->getItemInfo()->getItemBaseCharacterJudgeID() 
						);
					if (judgeType != GAMEJUDGE_TYPE_SUCCESS)
					{
						if (judgeType == GAMEJUDGE_TYPE_CHARACTER_LEVEL_ERROR)
						{
							return item_changepos_res_Error_character_level;
						}
					}


                    //����playerItem;
                   // ItemManager::removeItem(pSendItem->getItemDBID(), sendtype, charId);
                    ItemManager::removeItem(sendIndex, sendtype, charId);
                    pSendItem->setItemIndex(recvIndex);
                    ItemManager::addItem(pSendItem, recvtype, true, charId);
                    //֪ͨDB                       
					if (sendtype == ITEM_SITE_TYPE_CLAN  ||  recvtype == ITEM_SITE_TYPE_CLAN)
					{   
						updateClanItemToDB();
						updatePlayerCharacterItemToDB(charId);
					}
					else
					{
						updatePlayerCharacterItemToDB(charId);
					}
                    //֪ͨMapSever
                    sendChangeEquipToMaqServer(charId, pSendItem, recvIndex);

					return item_changepos_res_Succeed;
                }
            }
        }
        //���û��װ����
        else if ( sendtype != ITEM_SITE_TYPE_CHARACTER_EQUIP  &&  recvtype != ITEM_SITE_TYPE_CHARACTER_EQUIP )
        {
            //����λ�û򽻻�
            if ( pRecvItem )
            {
                //�Ƿ���Ե���
                if ( pSendItem->getItemTempID()  ==  pRecvItem->getItemTempID()  &&  pSendItem->ifOverlying() )
                {
                    //�ж��Ƿ񳬹����ֵ
                    U32 sendNum = pSendItem->getItemNum();
                    U32 recvNum = pRecvItem->getItemNum();
                    U32 maxNum = pSendItem->getItemPileMaxNum();
                    if ( sendNum + recvNum > maxNum )
                    {    
                        sendNum = (sendNum + recvNum) - maxNum;
                        recvNum = maxNum;
                        //����ֵ�ı�
                        pRecvItem->setItemNum(recvNum);
                        pSendItem->setItemNum(sendNum);
                        //֪ͨDB                  
						updateClanItemToDB();
						updatePlayerCharacterItemToDB(charId);

						return item_changepos_res_Succeed;
                    }
                    else
                    {
                        recvNum += sendNum;
                        //����ֵ�ı�
                        pRecvItem->setItemNum(recvNum);
                        //ɾ��pSendItem
                        handlDelItem(sendIndex, sendtype, charId);
                        //���� pRecvItem ��num                     
						if (sendtype == ITEM_SITE_TYPE_CLAN && recvtype == ITEM_SITE_TYPE_CLAN)
						{
							updateClanItemToDB();
						}
						else if (sendtype == ITEM_SITE_TYPE_CHARACTER_BAG && recvtype == ITEM_SITE_TYPE_CHARACTER_BAG)
						{
							updatePlayerCharacterItemToDB(charId);
						}
						else
						{
							updateClanItemToDB();
							updatePlayerCharacterItemToDB(charId);
						}


						return item_changepos_res_Succeed;

                    }
                }
                //����λ��
                else
                {
                    //����playerItem;
					ItemManager::removeItem(sendIndex, sendtype, charId);
					ItemManager::removeItem(recvIndex, recvtype, charId);
                    pSendItem->setItemIndex(recvIndex);
                    pRecvItem->setItemIndex(sendIndex);
                    ItemManager::addItem(pSendItem, recvtype, true, charId); 
                    ItemManager::addItem(pRecvItem, sendtype, true, charId);
                    //֪ͨDB                  ;
					if (sendtype == ITEM_SITE_TYPE_CLAN && recvtype == ITEM_SITE_TYPE_CLAN)
					{
						updateClanItemToDB();
					}
					else if (sendtype == ITEM_SITE_TYPE_CHARACTER_BAG && recvtype == ITEM_SITE_TYPE_CHARACTER_BAG)
					{
						updatePlayerCharacterItemToDB(charId);
					}
					else
					{
						updateClanItemToDB();
						updatePlayerCharacterItemToDB(charId);
					}
					return item_changepos_res_Succeed;

                }
            }
            //�ƶ�����
            else 
            {
                //����playerItem;
                ItemManager::removeItem(sendIndex, sendtype, charId);
                pSendItem->setItemIndex(recvIndex);
                ItemManager::addItem(pSendItem, recvtype, true, charId);
                //֪ͨDB                       
				if (sendtype == ITEM_SITE_TYPE_CLAN && recvtype == ITEM_SITE_TYPE_CLAN)
				{
					updateClanItemToDB();
				}
				else if (sendtype == ITEM_SITE_TYPE_CHARACTER_BAG && recvtype == ITEM_SITE_TYPE_CHARACTER_BAG)
				{
					updatePlayerCharacterItemToDB(charId);
				}
				else
				{
					updateClanItemToDB();
					updatePlayerCharacterItemToDB(charId);
				}
				return item_changepos_res_Succeed;
             }
        }
        //������������ܽ��� 
        return item_changepos_res_Error_notchange;
    }
    //----------------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------------
    void SItemManager::sendItemInfo()
    {
        std::vector<ItemRecord*> itemRecordList;

        //��ȡclanItem��ĵ���
        const std::map<IdType, PlayerItem*>* tempMapClanItem = getClanItems()->getPlayerItemMap();
        std::map<IdType, PlayerItem*>::const_iterator front = tempMapClanItem->begin();
        std::map<IdType, PlayerItem*>::const_iterator back = tempMapClanItem->end();
        while (front != back)
        {
            itemRecordList.push_back(front->second->getItemRecord());
            ++front;
        }

        //��ȡ��ɫ������ĵ���
        std::map<PlayerCharacterIdType, GenrealItem*>* tempGenrealItemMap = getGenrealItemMap();
        std::map<PlayerCharacterIdType, GenrealItem*>::iterator frontGenrealItem = tempGenrealItemMap->begin();
        std::map<PlayerCharacterIdType, GenrealItem*>::iterator backGenrealItem = tempGenrealItemMap->end();
        while ( frontGenrealItem != backGenrealItem )
        {
            tempMapClanItem = frontGenrealItem->second->getPlayerItemMap();
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
		std::map<PlayerCharacterIdType, GenrealEquip*>* tempGenrealEquipMap = getGenrealEquipMap();
		std::map<PlayerCharacterIdType, GenrealEquip*>::iterator frontGenrealEquip = tempGenrealEquipMap->begin();
		std::map<PlayerCharacterIdType, GenrealEquip*>::iterator backGenrealEquip = tempGenrealEquipMap->end();
		while (frontGenrealEquip != backGenrealEquip)
		{
			PlayerItem** genrealEquipArray = frontGenrealEquip->second->getEquipItemArray();
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

        ItemPacketProcesser::getInstance().sendItemToClient(mParent->getClientNetId(), &itemRecordList);
    }

    //----------------------------------------------------------------------------------------
    void SItemManager::setSize()
    {
        ClanData* pData = mParent->getData();
        getClanItems()->setSize(pData->clanbagSize);
    }
    //----------------------------------------------------------------------------------------
    MG::item_split_res SItemManager::handlSplitItem( U32 slotIndex, ITEM_SITE_TYPE selfType, ITEM_SITE_TYPE splitType, U32 selectIndex, U32 num, PlayerCharacterIdType id )
    {
        PlayerItem* pSelfItem = findItem(slotIndex, selfType, id); 
        if ( pSelfItem == NULL )
            return item_split_res_Error_cannot;

        if ( pSelfItem->ifOverlying() == false )
            return item_split_res_Error_cannot;

        if ( checkItemFull(splitType, id) )
            return item_split_res_Error_cannot;

        if ( pSelfItem->getItemNum() <= num )
            return item_split_res_Error_cannot;
       
		std::vector<PlayerItem*> modifiedItem;
		//Ŀ��λ���Ƿ��е���
		PlayerItem* pTargetItem = findItem(selectIndex,splitType,id);
        if (pTargetItem == NULL)
        {
            pSelfItem->setItemNum(pSelfItem->getItemNum() - num);
			modifiedItem.push_back(pSelfItem);
			//���ID��
			U32 tempID = tempID = getItemUserDefinedID();
			//����PlayerItem��
			PlayerItem* tempItem = PlayerItemFactory::getInstance().addItem(tempID, pSelfItem->getItemTempID());
			//�������
			tempItem->setItemNum(num);
			tempItem->setItemPos(splitType);
			tempItem->setItemIndex(selectIndex);
            tempItem->setItemBelongID(ITEM_BELONG_TYPE_CLAN, mParent->getClanID());
			//�����λ��;
			ItemManager::addItem(tempItem, splitType, true, id);
			
			//�������ݿ�
			if (splitType == ITEM_SITE_TYPE_CLAN && selfType == ITEM_SITE_TYPE_CLAN)
			{
				updateClanItemToDB();
			}
			else if (splitType == ITEM_SITE_TYPE_CHARACTER_BAG && selfType == ITEM_SITE_TYPE_CHARACTER_BAG)
			{
                updatePlayerCharacterItemToDB(id);
			}
			else
			{
                updateClanItemToDB();
				updatePlayerCharacterItemToDB(id);

			}
			//֪ͨ�ͻ��˼�һ����Ʒ
			ItemPacketProcesser::getInstance().sendAddItemToClient(mParent->getClientNetId(), tempItem);
			//֪ͨ�ͻ��˸�����Ʒ����
			ItemPacketProcesser::getInstance().sendItemUpdateNumListToClient(mParent->getClientNetId(),&modifiedItem);
        }
		else
		{
		   U32 selfItemNum  = pSelfItem->getItemNum();
           U32 existItemNum = pTargetItem->getItemNum();
		   U32 maxItemNum = pTargetItem->getItemPileMaxNum();
		   if ((existItemNum + num) > maxItemNum)
		   {
               pSelfItem->setItemNum(selfItemNum-(maxItemNum - existItemNum));
               pTargetItem->setItemNum(maxItemNum);
		   }
		   else
		   {
				pSelfItem->setItemNum(selfItemNum - num);
				pTargetItem->setItemNum(existItemNum + num);
		   }
           modifiedItem.push_back(pSelfItem);
           modifiedItem.push_back(pTargetItem);
		   //�������ݿ�
		   if (splitType == ITEM_SITE_TYPE_CLAN && selfType == ITEM_SITE_TYPE_CLAN)
		   {
			   updateClanItemToDB();
		   }
		   else if (splitType == ITEM_SITE_TYPE_CHARACTER_BAG && selfType == ITEM_SITE_TYPE_CHARACTER_BAG)
		   {
			   updatePlayerCharacterItemToDB(id);
		   }
		   else
		   {
			   updateClanItemToDB();
			   updatePlayerCharacterItemToDB(id);

		   }
		   //֪ͨ�ͻ��˸�����Ʒ����
		   ItemPacketProcesser::getInstance().sendItemUpdateNumListToClient(mParent->getClientNetId(),&modifiedItem);
		}
        return item_split_res_Succeed;
    }
    //----------------------------------------------------------------------------------------
	MG::item_use_res SItemManager::handlUseItemClient( U32 slotIndex,ITEM_SITE_TYPE type,PlayerCharacterIdType charid )
	{
		//����Ƿ����õ���
		PlayerItem* pItem = findItem(slotIndex, type, charid);
		if (pItem == NULL)
			return item_use_res_Error_None;

        

		//��ɫ��ʹ����Ʒ
		if (pItem->getItemType() == ITEM_TYPE_USE_GENERAL)
		{
			if ( charid != mParent->getMainGenrealID() )
				return item_use_res_Error_None;
			//һ���жϡ�
			//λ���ж�
			if (type !=  ITEM_SITE_TYPE_CHARACTER_BAG )
				return item_use_res_Error_Type;

			//��ɫ�Ƿ���ڡ�
			SPlayerCharacterPtr pSPlayerCharacter;
			mParent->getPlayerCharacter(pSPlayerCharacter,charid);
			//SPlayerCharacter* pSPlayerCharacter = mParent->getPlayerCharacterFromList(charid);
			//if ( pSPlayerCharacter == NULL )
			//	return item_use_res_Error_PC;
			
			//������� ��ɫҪ��:
			if ( GameJudge::getInstance().checkGameJudge(
				mParent,
				pSPlayerCharacter.getPointer(),
				pItem->getItemInfo()->getItemBaseClanJudgeID(),
				pItem->getItemInfo()->getItemBaseCharacterJudgeID() 
				)	!= GAMEJUDGE_TYPE_SUCCESS
				)
			{
				return item_use_res_Error_Judge;
			}
			//
			//���CD������CD, ��MapServerЧ����
			sendItemUseToMapServer(pItem, charid);

		}

		//////////////////////////////////////////////////////////////////////////
		//������ʹ����Ʒ
		else if (pItem->getItemType() == ITEM_TYPE_USE_CLAN)
		{
			//λ���ж�
			if (type !=  ITEM_SITE_TYPE_CLAN )
				return item_use_res_Error_Type;

			//�������Ҫ��:
            if (GameJudge::getInstance().checkClanJudge(mParent,pItem->getItemInfo()->getItemBaseClanJudgeID())
				!= GAMEJUDGE_TYPE_SUCCESS)
            {
                return item_use_res_Error_Judge;
            }
            
			//����ʹ����Ʒ��ʱֱ����frontserver�ϴ���
			U32 giveQuestId = pItem->getItemInfo()->getItemUseGiveQuestId();
			U32 itemGroupId =  pItem->getItemInfo()->getItemUseGiveItemGroupId();
			//��������id
			if ( giveQuestId )
			{
				;
			}	
			//�������߷��� 
			if ( itemGroupId )
			{
				if (handleCheckCanAddToClanBag(itemGroupId) == false)
				{
					return item_use_res_Error_ClanBag_Full;
				}
				else
				{   
					handAddItem(itemGroupId);
					//���µ��� OR ɾ������
					UInt num = pItem->getItemNum();
					if ( num > 1 )
					{
						pItem->setItemNum(num-1);
						updateClanItemToDB();
					}
					else  //ɾ������
					{
						handlDelItem(pItem->getItemDBID(), type, charid);
					}
					
				}

			}
			//��������ʹ����Ʒ�ͳɹ���Ϣ
			ItemPacketProcesser::getInstance().sendItemUseToClient(mParent->getClientNetId(),charid,slotIndex,type,item_use_res_Succeed);
		}
		else
		{
			return item_use_res_Error_Type;
		}
		return item_use_res_Succeed;

	}
	//----------------------------------------------------------------------------------------
	MG::item_use_res SItemManager::handlUseItemMapServer( U32 slotIndex,ITEM_SITE_TYPE type, PlayerCharacterIdType charid )
	{
		PlayerItem* pItem = findItem(slotIndex, type, charid);
		if (pItem == NULL)
			return item_use_res_Error_None;
		//��ɫʹ�õ���
        if (pItem->getItemType() == ITEM_TYPE_USE_GENERAL)
        {
			//
			//
			//���µ��� OR ɾ������
			UInt num = pItem->getItemNum();
			if ( num > 1 )
			{
				pItem->setItemNum(num-1);
				updatePlayerCharacterItemToDB(charid);
			}
			else  //ɾ������
			{
				handlDelItem(pItem->getItemDBID(), type, charid);
			}

        }
	    //����ʹ�õ���
		else if (pItem->getItemType() == ITEM_TYPE_USE_CLAN)
		{
			 return item_use_res_Error_Type;
		}
		else
		{
            return item_use_res_Error_Type;
		}
		//
        return item_use_res_Succeed;

	}

    //----------------------------------------------------------------------------------------
    void SItemManager::sendChangeEquipToMaqServer( PlayerCharacterIdType id, PlayerItem* pItem, U32 pos )
    {
        SPlayer* pPlayer = mParent->getParentPlayer();
        DYNAMIC_ASSERT(pPlayer);
        ItemPacketProcesser::getInstance().sendChangeEquipToMapServer(pPlayer->getMapServerNetID(), id, pItem, pos);
        //���¼����佫�����ԡ�
    }
    //----------------------------------------------------------------------------------------
    void SItemManager::sendItemUseToMapServer(PlayerItem* pItem, PlayerCharacterIdType charid)
    {
        SPlayer* pPlayer = mParent->getParentPlayer();
        DYNAMIC_ASSERT(pPlayer);
        ItemPacketProcesser::getInstance().sendItemUseToMapServer(pPlayer->getMapServerNetID(), charid, pItem->getItemTempID(),
			pItem->getItemIndex(),pItem->getItemSiteType());
		
    }
    //----------------------------------------------------------------------------------------
    void SItemManager::handlSellItemToShop( PlayerItem* pItem, ITEM_SITE_TYPE sendType, ITEM_SITE_TYPE recvType, PlayerCharacterIdType id /*= 0*/ )
    {
        ItemManager::removeItem(pItem->getItemDBID(), sendType, id);
		//��ӵ��ع���
        U32 slotIndex = getBuyBackItems()->getFreeIndex();
		pItem->setItemIndex(slotIndex);
		pItem->setItemPos(recvType);
		ItemManager::addItem(pItem,recvType,true,id);

		if (sendType == ITEM_SITE_TYPE_CLAN)
		{
			updateClanItemToDB();
		}
		if (sendType == ITEM_SITE_TYPE_CHARACTER_BAG)
		{
			updatePlayerCharacterItemToDB(id);
		}

		//��ʱ���⴦��:
		if (sendType == ITEM_SITE_TYPE_CLAN)
		{
			//�����ж�,ֻ���Ǳ���
			SClanQuestManager*  questManager = getSClanQuestManager();
			for (Int i = 0;i <pItem->getItemNum(); i++)
			{
				questManager->notifyGetOrDropItem(pItem->getItemTempID(),false);
			}
		}
		
    }
	//----------------------------------------------------------------------------------------
	void SItemManager::handlRewardItemMapServer( SPlayerCharacter* pSPlayerCharacter, U32 groupItemId )
	{
		std::vector<ItemNum> tempItemVector;
		ItemGroupTemplate::getInstance().getItemGroupInfo(groupItemId, tempItemVector);
		const ItemInfo* pInfo = NULL;
		
		U32 tempAddMoney[ITEM_MONEY_CLASS_MAX] = { 0 };
		U32 tempAddExp[CHAR_LVL_USETYPE_MAX] = { 0 };

		//�ֳ����ߺͽ�Ǯ��
		std::vector<ItemNum>::iterator front = tempItemVector.begin();
		std::vector<ItemNum>::iterator back = tempItemVector.end();
		while( front != back )
		{
			pInfo = ItemTemplate::getInstance().getItemInfo( (*front).itemTemplate );
			if ( pInfo->getItemBaseItemType() == ITEM_TYPE_EXP )
			{
				const ItemExpListCsvInfo* expInfo = ItemExpListCsv::getInstance().getInfoById(pInfo->ItemListId);
				tempAddExp[expInfo->itemType] += pInfo->getItemBasePrice()*((*front).num);
			}
			else if(pInfo->getItemBaseItemType() == ITEM_TYPE_MONEY)
			{
				const ItemMoneyInfo* moneyInfo = ItemMoneyTemplate::getInstance().getItemMoneyInfo(pInfo->ItemListId);
				tempAddMoney[moneyInfo->Class] += pInfo->getItemBasePrice()*((*front).num);
			}
			else
			{
				handlAddItem((*front).itemTemplate, (*front).num);
			}

			++front;
		}
		//�����Ǯ
		for (Int i=ITEM_MONEY_CLASS_NONE; i<ITEM_MONEY_CLASS_MAX; i++)
		{
			if (tempAddMoney[i])
			{	
				handlAddMoney(tempAddMoney[i], (ITEM_MONEY_CLASS)i);
			}
		}
		//������
		for (Int i=CHAR_LVL_USETYPE_NULL; i<CHAR_LVL_USETYPE_MAX; i++)
		{
			if ( tempAddExp[i] )
			{
				handlAddExp(tempAddExp[i], (CHAR_LVL_USETYPE)i, pSPlayerCharacter);
			}
		}
	}

	//------------------------------------------------------------------------------------------
	void SItemManager::handleDropItemAddExp(SPlayerCharacter* pSPlayerCharacter, U32 itemTempId, Int num)
	{
		if  ( pSPlayerCharacter->isDead() ) return;
		const ItemInfo* itemInfo = ItemTemplate::getInstance().getItemInfo(itemTempId);
		if (itemInfo->ItemType != ITEM_TYPE_EXP)
		{
			DYNAMIC_ASSERT(0);
			return;
		}
		const ItemExpListCsvInfo* expInfo = ItemExpListCsv::getInstance().getInfoById(itemInfo->ItemListId);
		
		handlAddExp(num*expInfo->price, CHAR_LVL_USETYPE_CHAR_LVL, pSPlayerCharacter);

		////������
		//for (Int i=1; i<CHAR_LVL_USETYPE_MAX; i++)
		//{
		//	if ( tempAddExp[i] )
		//	{
		//		handlAddExp(tempAddExp[i], (CHAR_LVL_USETYPE)i, pSPlayerCharacter);
		//	}
		//}
	}

	//------------------------------------------------------------------------------------------
	
	//------------------------------------------------------------------------------------------
	void SItemManager::handlAddMoney( Int num, ITEM_MONEY_CLASS moneyClass )
	{
		//�޸��ڴ�
		addMoney(num, moneyClass);

		//����DB��
		updateMoneyToDB(mParent->getClanID(), getMoney(moneyClass), moneyClass);

		//���͸��ͻ���
		ItemPacketProcesser::getInstance().sendAddMoneyToClient(
			mParent->getParentPlayer()->getClientNetID(),
			num,
			moneyClass
			);
	}
	//------------------------------------------------------------------------------------------
	void SItemManager::handlAddExp( U32 num, CHAR_LVL_USETYPE type, SPlayerCharacter* pSPlayerCharacter )
	{
		if ( pSPlayerCharacter->isDead() ) return;
		Bool isLevelUp = false;
		//�޸��ڴ�
		LevelManager* pLevelManager = pSPlayerCharacter->getLevelManager(); 
		
		U32 tempLevel = 0;
		U32 tempCurExp = 0;

		pLevelManager->getLevelAndCurExp(pSPlayerCharacter, type, tempLevel, tempCurExp);
		const CharLvlInfo* pCharLvlInfo = CharacterLvlTemplate::getInstance().getCharLvlInfo((CHAR_LVL_USETYPE)type, tempLevel+1);
		if (NULL == pCharLvlInfo)
		{
			//������
			return;
		}

		if(false == pLevelManager->addExp(pSPlayerCharacter, type, num, isLevelUp))
		{
			//������ �޷��Ӿ���
			//return;
		}

		//����DB��
		updateExpToDB(pSPlayerCharacter, type);

		//���͸��ͻ���
		ItemPacketProcesser::getInstance().sendAddExpToClient(
				mParent->getParentPlayer()->getClientNetID(),
				num,
				type,
				pSPlayerCharacter->getID(),
				pSPlayerCharacter->getType()
			);

		if ( isLevelUp )
		{
			//����DB;
			updateLevelToDB(pSPlayerCharacter, type);
			//��MapSever����ͬ����Ϣ��
			if ( CHAR_LVL_USETYPE_CHAR_LVL  ==  type||  CHAR_LVL_USETYPE_CHAR_TRUN  ==  type )
			{
				U32 level = 0;
				if ( CHAR_LVL_USETYPE_CHAR_LVL  ==  type )
					level = pSPlayerCharacter->getLevel();
				else
					level = pSPlayerCharacter->getData()->mLineageNum;

				SAttributeNetPacketProcesser::getInstance().sendUpLevel(
						mParent->getParentPlayer()->getMapServerNetID(),
						pSPlayerCharacter->getID(), 
						level,
						type
					);
			}
		}
	}
	//------------------------------------------------------------------------------------------
	void SItemManager::handlPickItemMapServer( PlayerCharacterIdType charId, U32 itemTempId, U32 num )
	{
		const ItemInfo* pInfo = ItemTemplate::getInstance().getItemInfo( itemTempId );
		if ( pInfo->getItemBaseItemType() == ITEM_TYPE_MONEY )
		{
			ITEM_MONEY_CLASS moneyType = pInfo->getItemMoneyClass();
			DYNAMIC_ASSERT(moneyType);
			if ( moneyType > ITEM_MONEY_CLASS_NONE /*ITEM_MONEY_CLASS_OTHER_SPARE_EXP4*/ )
				handlAddMoney(pInfo->getItemBasePrice()*num, moneyType);
	/*		else
			{	
				SPlayerCharacter* pSPlayerCharacter = mParent->getPlayerCharacterFromList(charId);
				DYNAMIC_ASSERT(pSPlayerCharacter);

				handlAddExp(pInfo->getItemBasePrice()*num, (CHAR_LVL_USETYPE)((Int)moneyType), pSPlayerCharacter);
			}*/
		}
		else if( pInfo->getItemBaseItemType() == ITEM_TYPE_EXP )
		{

		}
		else
		{
			handlAddItem(itemTempId, num);
			//ItemPacketProcesser::getInstance().sendAddItemToClient(mParent->getClientNetId(), pItem);
		}
	}
	//------------------------------------------------------------------------------------------
	void SItemManager::updateMoneyToDB( ClanIdType clanid, U32 value, Byte type )
	{
		switch (type)
		{
		case ITEM_MONEY_CLASS_MONEY_RMB_PRESENT:
			break;
		case ITEM_MONEY_CLASS_MONEY_GAME:
			ClanDataBaseDBOp::updateClanDataBaseMoney(
					*(FrontServerMain::getInstance().getDBDriver()),
					clanid,
					value
				);
			break;
		case ITEM_MONEY_CLASS_MONEY_FOOD:
			break;
		case ITEM_MONEY_CLASS_MONEY_MAN:
			break;
		case ITEM_MONEY_CLASS_RENOWN_SPARE1:
			break;
		case ITEM_MONEY_CLASS_RENOWN_SPARE2:
			break;
		case ITEM_MONEY_CLASS_RENOWN_SPARE3:
			break;
		case ITEM_MONEY_CLASS_RENOWN_SPARE4:
			break;
		}
	}
	//------------------------------------------------------------------------------------------
	void SItemManager::updateExpToDB( SPlayerCharacter* pSPlayerCharacter, Byte type )
	{
		switch (type)
		{
		case CHAR_LVL_USETYPE_CHAR_LVL:		//����ɫ�ȼ�
			{
				PlayerCharacterDBOp::updatePlayerCharacterExp(
						*(FrontServerMain::getInstance().getDBDriver()),
						pSPlayerCharacter->getID(),
						pSPlayerCharacter->getData()->charExp1
					);
			}
			break;
		case CHAR_LVL_USETYPE_CHAR_TRUN:	
			break;
		case CHAR_LVL_USETYPE_CHAR_SKILL:	
			break;
		case CHAR_LVL_USETYPE_CHAR_SPARE:	
			break;
		case CHAR_LVL_USETYPE_CLAN:	
			break;
		case CHAR_LVL_USETYPE_CLAN_POS:	
			break;
		case CHAR_LVL_USETYPE_CLAN_FEATS:	
			break;
		case CHAR_LVL_USETYPE_CLAN_SPARE:	
			break;	
		case CHAR_LVL_USETYPE_AYM_LVL:	
			break;
		case CHAR_LVL_USETYPE_AYM_SPARE:	
			break;		
		case CHAR_LVL_USETYPE_BUILD_LVL:	
			break;
		case CHAR_LVL_USETYPE_BUILD_SPARE:	
			break;
		case CHAR_LVL_USETYPE_OTHER_SPARE1:	
			break;
		case CHAR_LVL_USETYPE_OTHER_SPARE2:	
			break;
		case CHAR_LVL_USETYPE_OTHER_SPARE3:	
			break;
		case CHAR_LVL_USETYPE_OTHER_SPARE4:	
			break;	
		}
	}
	//------------------------------------------------------------------------------------------
	void SItemManager::updateLevelToDB( SPlayerCharacter* pSPlayerCharacter, Byte type )
	{
		switch (type)
		{
		case CHAR_LVL_USETYPE_CHAR_LVL:		//����ɫ�ȼ�
			{
				PlayerCharacterDBOp::updatePlayerCharacterLevel(
						*(FrontServerMain::getInstance().getDBDriver()),
						pSPlayerCharacter->getID(),
						pSPlayerCharacter->getLevel()
					);
			}
			break;
		case CHAR_LVL_USETYPE_CHAR_TRUN:	
			break;
		case CHAR_LVL_USETYPE_CHAR_SKILL:	
			break;
		case CHAR_LVL_USETYPE_CHAR_SPARE:	
			break;
		case CHAR_LVL_USETYPE_CLAN:	
			break;
		case CHAR_LVL_USETYPE_CLAN_POS:	
			break;
		case CHAR_LVL_USETYPE_CLAN_FEATS:	
			break;
		case CHAR_LVL_USETYPE_CLAN_SPARE:	
			break;	
		case CHAR_LVL_USETYPE_AYM_LVL:	
			break;
		case CHAR_LVL_USETYPE_AYM_SPARE:	
			break;		
		case CHAR_LVL_USETYPE_BUILD_LVL:	
			break;
		case CHAR_LVL_USETYPE_BUILD_SPARE:	
			break;
		case CHAR_LVL_USETYPE_OTHER_SPARE1:	
			break;
		case CHAR_LVL_USETYPE_OTHER_SPARE2:	
			break;
		case CHAR_LVL_USETYPE_OTHER_SPARE3:	
			break;
		case CHAR_LVL_USETYPE_OTHER_SPARE4:	
			break;	
		}
	}
	//------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------
	SClanQuestManager* SItemManager::getSClanQuestManager()
	{
		return mParent->getQuestManager();
    //      SClanQuestManager*  questManager = NULL;
		  //SPlayer* player = mParent->getParentPlayer();
		  //DYNAMIC_ASSERT(player);
		  //questManager = player->getClan()->getQuestManager();

		  //return questManager;
		  
	}
	//------------------------------------------------------------------------------------------
	void SItemManager::handAddItem( U32 groupItemId )
	{
		//����ʹ��, �籦�䣬���Բ����Ǿ������Ϣ...
		std::vector<ItemNum> tempItemVector;
		ItemGroupTemplate::getInstance().getItemGroupInfo(groupItemId, tempItemVector);
		const ItemInfo* pInfo = NULL;

		U32 tempAddMoney[ITEM_MONEY_CLASS_MAX] = { 0 };
		//U32 tempAddExp[CHAR_LVL_USETYPE_MAX] = { 0 };

		//�ֳ����ߺͽ�Ǯ��
		std::vector<ItemNum>::iterator front = tempItemVector.begin();
		std::vector<ItemNum>::iterator back = tempItemVector.end();
		while( front != back )
		{
			pInfo = ItemTemplate::getInstance().getItemInfo( (*front).itemTemplate );
			if ( pInfo->getItemBaseItemType() == ITEM_TYPE_EXP )
			{
				/*
				const ItemExpListCsvInfo* expInfo = ItemExpListCsv::getInstance().getInfoById(pInfo->ItemListId);
				tempAddExp[expInfo->itemType] += pInfo->getItemBasePrice()*((*front).num);
				*/
			}
			else if(pInfo->getItemBaseItemType() == ITEM_TYPE_MONEY)
			{
				const ItemMoneyInfo* moneyInfo = ItemMoneyTemplate::getInstance().getItemMoneyInfo(pInfo->ItemListId);
				tempAddMoney[moneyInfo->Class] += pInfo->getItemBasePrice()*((*front).num);
			}
			else
			{
				handlAddItem((*front).itemTemplate, (*front).num);
			}

			++front;
		}
		//�����Ǯ
		for (Int i=ITEM_MONEY_CLASS_NONE; i<ITEM_MONEY_CLASS_MAX; i++)
		{
			if (tempAddMoney[i])
			{	
				handlAddMoney(tempAddMoney[i], (ITEM_MONEY_CLASS)i);
			}
		}
		/*
		//������
		for (Int i=CHAR_LVL_USETYPE_NULL; i<CHAR_LVL_USETYPE_MAX; i++)
		{
			if ( tempAddExp[i] )
			{
				handlAddExp(tempAddExp[i], (CHAR_LVL_USETYPE)i, pSPlayerCharacter);
			}
		}
		*/
	}
	//------------------------------------------------------------------------------------------
	void SItemManager::_addItemToOneSlot( U32 itemTempID, U32 num )
	{
		UInt slotIndex = getClanItems()->getFreeIndex();
		if ( slotIndex == 0 )
			return;
		//����Զ���ID��
		U32 tempID = getItemUserDefinedID();
		//����PlayerItem��
		PlayerItem* pItem = PlayerItemFactory::getInstance().addItem(tempID, itemTempID);
		//�������
		pItem->setNewBase(ITEM_BELONG_TYPE_CLAN, mParent->getClanID(), slotIndex, num);

		//�����λ��;
		ItemManager::addItem(pItem, ITEM_SITE_TYPE_CLAN, true, 0);

		//�������ݿ�
		updateClanItemToDB();

		//���ͷ��˷�����Ϣ
        ItemPacketProcesser::getInstance().sendAddItemToClient(mParent->getClientNetId(), pItem);

	
	}
	//------------------------------------------------------------------------------------------
	void SItemManager::_handAddItemOverlay( U32 itemTempID, U32 num )
	{
		const ItemInfo* mItemInfo = ItemTemplate::getInstance().getItemInfo(itemTempID);
		U32 maxOverlayNum = mItemInfo->getItemBaseMaxPileNum();
		//
		std::vector<PlayerItem*>  existPlayerItemList;
		std::vector<PlayerItem*>  modifiedPlayerItemList;
		getClanItems()->findItemByTemplateId(itemTempID,existPlayerItemList);
		if (existPlayerItemList.size() >0)
		{
			PlayerItem* pItem = NULL;
			U32         itemCurNum;
			std::vector<PlayerItem*>::iterator front = existPlayerItemList.begin();
			std::vector<PlayerItem*>::iterator back = existPlayerItemList.end();
			while(front !=back )
			{
				pItem = (*front);
				itemCurNum = pItem->getItemNum();

				//û�дﵽ���ѵ�ֵ�����޸�
				if ( itemCurNum < maxOverlayNum )
				{
					modifiedPlayerItemList.push_back(pItem);
				}
				while ( itemCurNum < maxOverlayNum )
				{     
					num--;
					itemCurNum++;
					pItem->setItemNum(itemCurNum);

					//�Ѿ�������
					if (num == 0)
					{
						break;
					}
				}
				if (num == 0)
				{
					break;
				}
				else
				{
					front++;
				}

			}
			//��������ʣ��Ѱ�ҿ��и�λ���
			_findFreeSlotAddItem(itemTempID,num,maxOverlayNum);
			
			//�������ݿ�
			//���ͷ��˷�����Ҫ���ĵ���Ʒ����
			updateClanItemToDB();
			ItemPacketProcesser::getInstance().sendItemUpdateNumListToClient(mParent->getClientNetId(),&modifiedPlayerItemList);
		}
		else
		{
            //��ǰ�ֿ�û�и���Ʒ��ֱ��Ѱ�ҿ��и�λ���
			_findFreeSlotAddItem(itemTempID,num,maxOverlayNum);
		}

	}
	//------------------------------------------------------------------------------------------
	void SItemManager::_findFreeSlotAddItem(U32 itemTempID,U32 num,U32 maxOverlayNum)
	{

		while ( num !=0 )
		{
			if ( num < maxOverlayNum)
			{  
				_addItemToOneSlot(itemTempID,num);
				num = 0;
			}
			else if (num >= maxOverlayNum)
			{   
				_addItemToOneSlot(itemTempID,maxOverlayNum);
				num = num - maxOverlayNum;
			}
		} 	
	}
	//------------------------------------------------------------------------------------------
	MG::Bool SItemManager::handleCheckCanAddToClanBag( U32 itemTempId,U32 num )
	{
	   const ItemInfo* pInfo =  ItemTemplate::getInstance().getItemInfo( itemTempId );
	   if (!pInfo)
	   {   DYNAMIC_ASSERT_LOG("pInfo","error: pInfo == NULL!");
           return false;
	   }
	   if (pInfo->getItemBaseItemType() == ITEM_TYPE_MONEY || pInfo->getItemBaseItemType() == ITEM_TYPE_EXP)
	   {
		   //��ʱ�����Ǿ���ͽ�Ǯ������
		   return true;
	   }
	   else
	   {
		   return checkCanAdd(itemTempId,num);
	   }

	   return false;
	}
	//------------------------------------------------------------------------------------------
	MG::Bool SItemManager::handleCheckCanAddToClanBag( U32 groupItemId )
	{
		std::vector<ItemNum> tempItemVector;
		ItemGroupTemplate::getInstance().getItemGroupInfo(groupItemId, tempItemVector);
		const ItemInfo* pInfo = NULL;

		//�ֳ����ߺͽ�Ǯ��
		std::vector<ItemNum>::iterator front = tempItemVector.begin();
		while( front != tempItemVector.end())
		{
			pInfo = ItemTemplate::getInstance().getItemInfo( (*front).itemTemplate );
			if ( pInfo->getItemBaseItemType() == ITEM_TYPE_MONEY || pInfo->getItemBaseItemType() == ITEM_TYPE_EXP)
			{
				front = tempItemVector.erase(front);
			}
			else
			{
				++front;
			}
		}

		//�Ժ�Ҫ��Ӽ���Ǯ�Ƿ񳬹�����������

		//�жϱ����Ƿ�������
		if (tempItemVector.size() >0 )
		{
			return checkCanAdd(tempItemVector);
		}
		return true;
		
	}
	//------------------------------------------------------------------------------------------
	MG::Bool SItemManager::handleCheckCanAddToClanBag( std::vector<ItemNum>& itemVector )
	{
		//�ֳ����ߺͽ�Ǯ��
		const ItemInfo* pInfo = NULL;
		std::vector<ItemNum>::iterator front = itemVector.begin();
		while( front != itemVector.end())
		{
			pInfo = ItemTemplate::getInstance().getItemInfo( (*front).itemTemplate );
			if ( pInfo->getItemBaseItemType() == ITEM_TYPE_MONEY || pInfo->getItemBaseItemType() == ITEM_TYPE_EXP)
			{
				front = itemVector.erase(front);
			}
			else
			{
				++front;
			}
		}
		//�Ժ�Ҫ��Ӽ���Ǯ�Ƿ񳬹�����������

		//�жϱ����Ƿ�������
		if (itemVector.size() >0 )
		{
			return checkCanAdd(itemVector);
		}
		return true;
	}
	//------------------------------------------------------------------------------------------
	void SItemManager::updateClanItemToDB()
	{
		//���屳��
		std::vector<PlayerItem*> clanItemList;
        std::map<IdType, PlayerItem*>* clanItemMap = getClanItems()->getPlayerItemMap();
		std::map<IdType, PlayerItem*>::iterator front = clanItemMap->begin();
		std::map<IdType, PlayerItem*>::iterator back = clanItemMap->end();
		while (front != back)
		{
              clanItemList.push_back(front->second);
              front++;
		}
        
		//�Ѿ�ɾ��������
        clanItemMap = getDeletedItems()->getPlayerItemMap();
		front = clanItemMap->begin();
		back = clanItemMap->end();
		while (front != back)
		{
			clanItemList.push_back(front->second);
			front++;
		}
        
		//�ع���������
		clanItemMap = getBuyBackItems()->getPlayerItemMap();
		front = clanItemMap->begin();
		back = clanItemMap->end();
		while (front != back)
		{
			clanItemList.push_back(front->second);
			front++;
		}

		ClanDataBaseDBOp::updateClanItem(*( FrontServerMain::getInstance().getDBDriver() ),mParent->getClanID(),&clanItemList);
	}
	//------------------------------------------------------------------------------------------
	void SItemManager::updatePlayerCharacterItemToDB(PlayerCharacterIdType charId)
	{
		std::vector<PlayerItem*> characterItemList;
		std::map<IdType, PlayerItem*>* genrealItemMap = getGenrealItem(charId)->getPlayerItemMap();
		PlayerItem** genrealEquipArray = getGenrealEquip(charId)->getEquipItemArray();
        //��ɫװ��
		for (Int i=0; i<ITEM_EQUIP_SLOT_TYPE_MAX; i++)
		{
			if (genrealEquipArray[i] != NULL)
			{
                 characterItemList.push_back(genrealEquipArray[i]);
			}
		}
		//��ɫ����
		std::map<IdType, PlayerItem*>::iterator front = genrealItemMap->begin();
		std::map<IdType, PlayerItem*>::iterator back = genrealItemMap->end();
		while (front != back)
		{
             characterItemList.push_back(front->second);
			 front++;
		}
		PlayerCharacterDBOp::updatePlayerCharacterItem(*( FrontServerMain::getInstance().getDBDriver() ),charId,&characterItemList);

	}
	//------------------------------------------------------------------------------------------
	void SItemManager::loadClanItemDBData( std::vector<ItemRecord>& recordList )
	{
		//setSize();
        

		//playerItem
		U32 nCount = recordList.size();
		for (U32 i=0; i<nCount; i++)
		{
			ItemManager::addItem( &(recordList[i]), (ITEM_SITE_TYPE)(Int)recordList[i].belongPos, false, recordList[i].characterId );
			mDefinedItemIdMap[recordList[i].itemDBID] = recordList[i].itemDBID;
		}
		
		//money
		addMoney(mParent->getData()->clanGameMoney, ITEM_MONEY_CLASS_MONEY_GAME);
        
	}
    //------------------------------------------------------------------------------------------
	void SItemManager::loadPlayerCharacterDBdata( std::vector<ItemRecord>& recordList )
	{ 
		U32 nCount = recordList.size();
		for (U32 i=0; i<nCount; i++)
		{
			ItemManager::addItem( &(recordList[i]), (ITEM_SITE_TYPE)(Int)recordList[i].belongPos, false, recordList[i].characterId );
			mDefinedItemIdMap[recordList[i].itemDBID] = recordList[i].itemDBID;
		}
	}
	//------------------------------------------------------------------------------------------
	U32 SItemManager::getItemUserDefinedID()
	{ 
        IdType currentMaxId = 0;
		std::map<IdType,IdType>::iterator front = mDefinedItemIdMap.begin();
		std::map<IdType,IdType>::iterator back = mDefinedItemIdMap.end();
		while (front != back)
		{
			if (currentMaxId < (front->second))
			{
				currentMaxId = (front->second);
			}
			front++;
		}

		for (IdType i=1;i<=currentMaxId;i++)
		{
			std::map<IdType,IdType>::iterator It = mDefinedItemIdMap.find(i);
			if (It != mDefinedItemIdMap.end())
			{ 
				continue;
			}
			else
			{   
                mDefinedItemIdMap[i] = i;
                return i;
			}
		}
        currentMaxId++;
        mDefinedItemIdMap[currentMaxId] = currentMaxId;
		return currentMaxId;
	}

	void SItemManager::deleteDefinedID( IdType definedID )
	{
		std::map<IdType,IdType>::iterator It = mDefinedItemIdMap.find(definedID);
		if (It != mDefinedItemIdMap.end())
		{
              mDefinedItemIdMap.erase(It);
		}
	}
	//------------------------------------------------------------------------------------------
	void SItemManager::handlDeductQuestItem( U32 groupItemId )
	{  
		//��ʱֻ�����屳���п۳�
		std::vector<ItemNum> tempItemVector;
		ItemGroupTemplate::getInstance().getItemGroupInfo(groupItemId, tempItemVector);
		const ItemInfo* pInfo = NULL;
		
		U32 tempAddMoney[ITEM_MONEY_CLASS_MAX] = { 0 };
        std::vector<PlayerItem*> modifiedItem;
		std::vector<ItemNum>::iterator front = tempItemVector.begin();
		std::vector<ItemNum>::iterator back = tempItemVector.end();
		while( front != back )
		{
			pInfo = ItemTemplate::getInstance().getItemInfo( (*front).itemTemplate );
			
			if(pInfo->getItemBaseItemType() == ITEM_TYPE_MONEY)
			{
				const ItemMoneyInfo* moneyInfo = ItemMoneyTemplate::getInstance().getItemMoneyInfo(pInfo->ItemListId);
				tempAddMoney[moneyInfo->Class] -= pInfo->getItemBasePrice()*((*front).num);
			}
			else
			{
				std::vector<PlayerItem*> itemList;
				getClanItems()->findItemByTemplateId((*front).itemTemplate,itemList);
				U32 deDuctCount = (*front).num;
				if (itemList.size() >0 )
				{   
					std::vector<PlayerItem*>::iterator front = itemList.begin();
					std::vector<PlayerItem*>::iterator back = itemList.end();
					PlayerItem* pItem = NULL;
					U32 itemCurNum = 0;
					while (front != back)
					{  
						
						pItem = (*front);
						itemCurNum = pItem->getItemNum();
						modifiedItem.push_back(pItem);

                        while (itemCurNum != 0)
                        {
                            deDuctCount--;  
                            itemCurNum--;
                            pItem->setItemNum(itemCurNum);
							if (itemCurNum == 0)
							{
								//ɾ��
								modifiedItem.pop_back();
								handlDelItem(pItem->getItemDBID(),ITEM_SITE_TYPE_CLAN);
							}
							if (deDuctCount == 0)
							{
								break;
							}
                        }
                        if (deDuctCount == 0)
                        {
							break;
                        }

						front++;
					}

				}
				//û���㹻����Ʒ�۳�
				if (deDuctCount != 0)
				{
					return;
				}
			}
			
			front++;
		}
		//
		//�۳���Ǯ
		for (Int i=ITEM_MONEY_CLASS_NONE; i<ITEM_MONEY_CLASS_MAX; i++)
		{
			if (tempAddMoney[i])
			{	
				handlAddMoney(-tempAddMoney[i], (ITEM_MONEY_CLASS)i);
			}
		}
		updateClanItemToDB();
		//�޸���Ʒ
		ItemPacketProcesser::getInstance().sendItemUpdateNumListToClient(mParent->getClientNetId(),&modifiedItem);
	}
	//------------------------------------------------------------------------------------------
	void SItemManager::handlDelItem( IdType itemDBID, ITEM_SITE_TYPE type,Int num, PlayerCharacterIdType id /*= 0*/ )
	{

		  itembag_del_res    res = itembag_del_res_Succeed;
          PlayerItem* pItem = findItem(itemDBID,type,id);
		  std::vector<PlayerItem*> itemList;
		  if (NULL == pItem)
		  {
			  res = itembag_del_res_Error_ItemNone;
		  }
		  if (pItem->getItemNum() < num)
		  {
			  res = itembag_del_res_Error_Not_Enough_Num;
		  } 
		  pItem->setItemNum(pItem->getItemNum() - num);
		  itemList.push_back(pItem);
		  if (type == ITEM_SITE_TYPE_CLAN)
		  {
			  updateClanItemToDB();
		  }
		  else if (type == ITEM_SITE_TYPE_CHARACTER_BAG || type == ITEM_SITE_TYPE_CHARACTER_EQUIP)
		  {
			  updatePlayerCharacterItemToDB(id);
		  }
          ItemPacketProcesser::getInstance().sendItemUpdateNumListToClient(mParent->getClientNetId(),&itemList);
		  ItemPacketProcesser::getInstance().sendItemDelToClient(mParent->getClientNetId(),type,itemDBID,res,id);

	}
	
	//------------------------------------------------------------------------------------------
	MG::Bool SItemManager::handleCheckItemExistInClanBag( U32 groupItemId )
	{
		Bool flag = true;
		std::vector<ItemNum> tempItemVector;
		ItemGroupTemplate::getInstance().getItemGroupInfo(groupItemId, tempItemVector);
		const ItemInfo* pInfo = NULL;

		U32 tempAddMoney[ITEM_MONEY_CLASS_MAX] = { 0 };

		std::vector<ItemNum>::iterator front = tempItemVector.begin();
		//std::vector<ItemNum>::iterator back = tempItemVector.end();
		ClanItems* clanItem = getClanItems();
		while( front != tempItemVector.end() )
		{
			pInfo = ItemTemplate::getInstance().getItemInfo( (*front).itemTemplate );

			if(pInfo->getItemBaseItemType() == ITEM_TYPE_MONEY)
			{
				const ItemMoneyInfo* moneyInfo = ItemMoneyTemplate::getInstance().getItemMoneyInfo(pInfo->ItemListId);
				if (tempAddMoney[moneyInfo->Class] <=  pInfo->getItemBasePrice()*((*front).num))
				{
					//��Ǯ����
                     flag = false; 
                     //front = tempItemVector.erase(front);
				}
				
			}
			else
			{
                 if (clanItem->checkItemExistInClanBag((*front).itemTemplate,(*front).num) == false)
                 {
					 //��Ʒ����
					 flag = false; 
                 }
			}

			front++;
		}
         
		return flag;
        

	}
	//------------------------------------------------------------------------------------------
}