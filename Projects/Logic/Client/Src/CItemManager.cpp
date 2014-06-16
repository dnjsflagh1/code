//**********************************************************************************************************
#include "stdafx.h"
#include "CItemManager.h"
#include "CPlayer.h"
#include "CClan.h"
#include "PlayerItem.h"
#include "UIClanInfo.h"
#include "UIItemShop.h"
#include "CCDManager.h"
#include "LevelManager.h"
#include "MessageManager.h"
#include "CBuffManager.h"
#include "CSceneManager.h"
#include "CPlayerCharacterEntity.h"
#include "AttributeAppend.h"
#include "CAttributeSystem.h"
#include "CharacterList.h"
#include "GenrealEquip.h"
#include "CGameMessageConfig.h"
//**********************************************************************************************************
namespace MG
{
    CItemManager::~CItemManager()
    {
       
    }
    //-------------------------------------------------------------------------------------------------
    void CItemManager::handlDelItem( IdType itemDBID, ITEM_SITE_TYPE type, PlayerCharacterIdType charid )
    {
		PlayerItem* pItem = findItem(itemDBID, type, charid);
		DYNAMIC_ASSERT(pItem);
        U32 index = pItem->getItemIndex();
		//֪ͨUI
		notifyUIDeleteItem(pItem, type, index);

        //�ڴ���ȥ��
        switch ( type )
        {   
        case ITEM_SITE_TYPE_CLAN:
            {   
                getClanItems()->deleteItem(itemDBID);
            }
            break;
        case ITEM_SITE_TYPE_CHARACTER_BAG:
            {
                deleteItem(itemDBID, type, charid);
            }
            break;
        case ITEM_SITE_TYPE_CHARACTER_EQUIP:
            {
				calAttr(charid, pItem, false);
                deleteItem(itemDBID, type, charid);
            }
            break;
        }
    }
    //-------------------------------------------------------------------------------------------------
    void CItemManager::handlChangItem( U32 sendIndex, U32 recvIndex, ITEM_SITE_TYPE sendtype, ITEM_SITE_TYPE recvtype, PlayerCharacterIdType charid )
    {
        //�����������ǲ�ͬ���潻��
        PlayerItem* pSendItem = findItem(sendIndex, sendtype, charid); 
        PlayerItem* pRecvItem = findItem(recvIndex, recvtype, charid);

        DYNAMIC_ASSERT(pSendItem);

        //�����һ����װ����
        if ( sendtype != recvtype  &&  ( sendtype == ITEM_SITE_TYPE_CHARACTER_EQUIP  ||  recvtype == ITEM_SITE_TYPE_CHARACTER_EQUIP  ) )
        {
            //����λ��
            if ( pRecvItem )
            {
                //�������װ��
                if ( pSendItem->getItemType() != ITEM_TYPE_EQUIP_GENERAL  ||  pRecvItem->getItemType() != ITEM_TYPE_EQUIP_GENERAL )
                    return ;
                //���λ�ò�ƥ��;
                if ( pSendItem->getItemEquipSlotType() != pRecvItem->getItemEquipSlotType() )
                    return ;

                //����playerItem;
                ItemManager::removeItem(pSendItem->getItemDBID(), sendtype, charid);
                ItemManager::removeItem(pRecvItem->getItemDBID(), recvtype, charid);
                pRecvItem->setItemIndex(sendIndex);
                pRecvItem->setCharacterID(charid);
                pRecvItem->setItemPos(sendtype);
                pSendItem->setItemIndex(recvIndex);
                pSendItem->setCharacterID(charid);
                pSendItem->setItemPos(recvtype);
                ItemManager::addItem(pRecvItem, sendtype, false, charid);
                ItemManager::addItem(pSendItem, recvtype, false, charid);

				//�������ԡ�
				if  (sendtype == ITEM_SITE_TYPE_CHARACTER_EQUIP)
				{
					calAttr(charid, pSendItem, false);
					calAttr(charid, pRecvItem, true);
				}
				else
				{
					calAttr(charid, pRecvItem, false);
					calAttr(charid, pSendItem, true);
				}
                //����ֵ�ı�
                
                //֪ͨUI
                notifyUIDeleteItem(pSendItem, sendtype, sendIndex);
                notifyUIDeleteItem(pRecvItem, recvtype, recvIndex);
                notifyUIAddItem(pSendItem);
                notifyUIAddItem(pRecvItem);
                
            }
            else 
            {
                //��װ����������
                if ( sendtype == ITEM_SITE_TYPE_CHARACTER_EQUIP )
                {   
                    //����playerItem;
                    ItemManager::removeItem(pSendItem->getItemDBID(), sendtype, charid);
                    pSendItem->setItemIndex(recvIndex);
                    pSendItem->setCharacterID(charid);
                    pSendItem->setItemPos(recvtype);
                    ItemManager::addItem(pSendItem, recvtype, false, charid);

					//�������ԡ�
					calAttr(charid, pSendItem, false);

                    //֪ͨUI
                    notifyUIDeleteItem(pSendItem, sendtype, sendIndex);
                    notifyUIAddItem(pSendItem);
                }
                //��װ��
                else
                {
                    //�������װ��
                    if ( pSendItem->getItemType() != ITEM_TYPE_EQUIP_GENERAL )
                        return ;
                    //���λ�ò�ƥ��;
                    if ( pSendItem->getItemEquipSlotType() != recvIndex )
                        return ;

                    //����playerItem;
                    ItemManager::removeItem(pSendItem->getItemDBID(), sendtype, charid);
                    pSendItem->setItemIndex(recvIndex);
                    pSendItem->setCharacterID(charid);
                    pSendItem->setItemPos(recvtype);
                    ItemManager::addItem(pSendItem, recvtype, false, charid);

					//�������ԡ�
					calAttr(charid, pSendItem, true);

                    //֪ͨUI
                    notifyUIDeleteItem(pSendItem,sendtype, sendIndex);
                    notifyUIAddItem(pSendItem);
                }
            }
        }
        //�������װ����
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
                        //֪ͨUI
                        notifyUIUpdateItem(pSendItem, sendtype, sendIndex, sendNum);
                        notifyUIUpdateItem(pRecvItem, recvtype, recvIndex, recvNum);
                    }
                    else
                    {
                        recvNum += sendNum;
                        //����ֵ�ı�
                        pRecvItem->setItemNum(recvNum);
                       
                        //֪ͨUI
                        notifyUIDeleteItem(pSendItem, sendtype, sendIndex);
                        notifyUIUpdateItem(pRecvItem, recvtype, recvIndex, recvNum);

						//ɾ��pSendItem
						ItemManager::deleteItem(pSendItem->getItemDBID(), sendtype, charid);
                    }
                }
                //����λ��
                else
                {
                    //����playerItem;
                    ItemManager::removeItem(pSendItem->getItemDBID(), sendtype, charid);
                    ItemManager::removeItem(pRecvItem->getItemDBID(), recvtype, charid);
                    pRecvItem->setItemIndex(sendIndex);
                    pRecvItem->setCharacterID(charid);
                    pRecvItem->setItemPos(recvtype);
                    pSendItem->setItemIndex(recvIndex);
                    pSendItem->setCharacterID(charid);
                    pSendItem->setItemPos(recvtype);
                    ItemManager::addItem(pRecvItem, sendtype, false, charid);
                    ItemManager::addItem(pSendItem, recvtype, false, charid);
                    //֪ͨUI
                    notifyUIDeleteItem(pSendItem, sendtype, sendIndex);
                    notifyUIDeleteItem(pRecvItem, recvtype, recvIndex);
                    notifyUIAddItem(pSendItem);
                    notifyUIAddItem(pRecvItem);
                }
            }
            //�ƶ�����
            else 
            {
                //����playerItem;
                ItemManager::removeItem(pSendItem->getItemDBID(), sendtype, charid);
                pSendItem->setItemIndex(recvIndex);
                pSendItem->setCharacterID(charid);
                pSendItem->setItemPos(recvtype);
				//֪ͨUI
				notifyUIDeleteItem(pSendItem, sendtype, sendIndex);
                ItemManager::addItem(pSendItem, recvtype, false, charid);
                notifyUIAddItem(pSendItem);
            }
        }
    }
    //-------------------------------------------------------------------------------------------------
    void CItemManager::setSize()
    {
        CClan* pClan = CPlayer::getInstance().getActiveClan();
        DYNAMIC_ASSERT(pClan);
        ClanData* pClanData = pClan->getData();
        DYNAMIC_ASSERT(pClanData);
        getClanItems()->setSize(pClanData->clanbagSize);
    }
    //-------------------------------------------------------------------------------------------------
    void CItemManager::handlAddItem( ItemRecord* pRecord )
    {
        //�ȼ��������
        PlayerItem* tempItem = ItemManager::addItem(pRecord, (ITEM_SITE_TYPE)pRecord->belongPos, false, pRecord->characterId);
		if ( ITEM_SITE_TYPE_CHARACTER_EQUIP == tempItem->getItemSiteType() )
			calAttr(pRecord->characterId, tempItem, true);

        //֪ͨUI
        notifyUIAddItem(tempItem);

		
    }
    //-------------------------------------------------------------------------------------------------
    void CItemManager::handlAddItem( PlayerItem* pItem )
    {
        //�����λ��;
        ItemManager::addItem(pItem, ITEM_SITE_TYPE_CLAN, false, 0);
        //֪ͨUI
        notifyUIAddItem(pItem);
    }
    //-------------------------------------------------------------------------------------------------
    void CItemManager::handlSplitItem( IdType itemDBId, ITEM_SITE_TYPE selfType, ITEM_SITE_TYPE splitType, U32 splitpos, U32 num, PlayerCharacterIdType id )
    {
        /*PlayerItem* pSelfItem = findItem(itemDBId, selfType, id); 
        if ( pSelfItem == NULL )
            return ;

        if ( pSelfItem->ifOverlying() == false )
            return ;

        if ( checkItemFull(splitType, id) )
            return ;

        U32 selfNum = pSelfItem->getItemNum();
        if ( selfNum <= num )
            return ;

        pSelfItem->setItemNum(selfNum - num);
        //֪ͨUI
        notifyUIUpdateItem(selfType, pSelfItem->getItemIndex(), selfNum - num);
		*/
    }
	
	//-------------------------------------------------------------------------------------------------
	void CItemManager::handlSplitItem( U32 slotIndex, ITEM_SITE_TYPE selfType, ITEM_SITE_TYPE splitType, U32 selectIndex, U32 num, PlayerCharacterIdType id /*= 0*/ )
	{
		PlayerItem* pSelfItem = findItem(slotIndex, selfType, id); 
		if ( pSelfItem == NULL )
			return;

		if ( pSelfItem->ifOverlying() == false )
			return;

		if ( checkItemFull(splitType, id) )
			return;

		if ( pSelfItem->getItemNum() <= num )
			return;
		//PlayerItem* pTargetItem = findItem(selectIndex,splitType,id);
		//notifyUIUpdateItem(selfType, pSelfItem->getItemIndex(), pSelfItem->getItemNum());
	//	notifyUIUpdateItem(splitType, pTargetItem->getItemIndex(), pTargetItem->getItemNum());
		//Ŀ��λ���Ƿ��е���
		/*PlayerItem* pTargetItem = findItem(selectIndex,splitType,id);
		if (pTargetItem == NULL)
		{
			pSelfItem->setItemNum(pSelfItem->getItemNum() - num);
			//֪ͨUI
			notifyUIUpdateItem(selfType, pSelfItem->getItemIndex(), pSelfItem->getItemNum());
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
				//֪ͨUI
				notifyUIUpdateItem(selfType, pSelfItem->getItemIndex(), pSelfItem->getItemNum());
				notifyUIUpdateItem(splitType, pTargetItem->getItemIndex(), pTargetItem->getItemNum());
			}
			else
			{
				pSelfItem->setItemNum(selfItemNum - num);
				pTargetItem->setItemNum(existItemNum + num);
				//֪ͨUI
				notifyUIUpdateItem(selfType, pSelfItem->getItemIndex(), pSelfItem->getItemNum());
				notifyUIUpdateItem(splitType, pTargetItem->getItemIndex(), pTargetItem->getItemNum());
			}
		}
		*/
	}
	//-------------------------------------------------------------------------------------------------
    void CItemManager::handlUseItem( IdType itemDBId, PlayerCharacterIdType charid )
    {
      /*  //����Ƿ����õ���
        PlayerItem* pItem = findItem(itemDBId, ITEM_SITE_TYPE_CHARACTER_BAG, charid);
        if (pItem == NULL)
            return ;
        if ( pItem->getItemType() != ITEM_TYPE_USE_GENERAL )
            return ;

        //���µ���
        UInt num = pItem->getItemNum();
        if ( num > 1 )
        {
            pItem->setItemNum(num-1);
            //֪ͨUI
            notifyUIUpdateItem(ITEM_SITE_TYPE_CHARACTER_BAG, pItem->getItemIndex(), num-1);
        }
        else  //ɾ������
        {
            //֪ͨUI
            notifyUIDeleteItem(ITEM_SITE_TYPE_CHARACTER_BAG, pItem->getItemIndex());
            //
            ItemManager::deleteItem(itemDBId, ITEM_SITE_TYPE_CHARACTER_BAG, charid);
        }
		//��CD
		CCDManager::getInstance().addCD(
			CD_MASTER_TYPE_CHARACTER,
			charid,
			pItem->getItemInfo()->getItemUseOwnerTimepieceId(),
			pItem->getItemInfo()->getItemUseOwnerTimepieceDelay(),
			pItem->getItemInfo()->getItemUseOwnerTimepieceDelay()
			);
			*/
    }

	void CItemManager::handlUseItem( U32 slotIndex, ITEM_SITE_TYPE itemType,PlayerCharacterIdType charid )
	{
		
		//����Ƿ����õ���
		PlayerItem* pItem = findItem(slotIndex, itemType, charid);
		if (pItem == NULL)
		return ;
		const ItemInfo* pItemInfo = pItem->getItemInfo();
		DYNAMIC_ASSERT(pItemInfo);

		if ( pItem->getItemType() != ITEM_TYPE_USE_GENERAL &&
			 pItem->getItemType() != ITEM_TYPE_USE_CLAN)
		{
			return ;
		}
	
		//���µ���
		UInt num = pItem->getItemNum();
		if ( num > 1 )
		{
			pItem->setItemNum(num-1);
			//֪ͨUI
			notifyUIUpdateItem(pItem, itemType, pItem->getItemIndex(), num-1);
		}
		else  //ɾ������
		{
			//֪ͨUI
			notifyUIDeleteItem(pItem, itemType, pItem->getItemIndex());
			//
			ItemManager::deleteItem(pItem->getItemDBID(), itemType, charid);
		}
		//��CD
		CCDManager::getInstance().addCD(
		CD_MASTER_TYPE_CHARACTER,
		charid,
		pItemInfo->getItemUseOwnerTimepieceId(),
		pItemInfo->getItemUseOwnerTimepieceDelay(),
		pItemInfo->getItemUseOwnerTimepieceDelay()
		);
		//��BUff
		/*CPlayerCharacterEntity* pCPlayerCharacterEntity = CSceneManager::getInstance().getPlayerCharacterEntity(charid);
		DYNAMIC_ASSERT(charid);
		pCPlayerCharacterEntity->getCBuffManager()->addNewBuff(
			pItemInfo->getItemUseStateId(),
			pItemInfo->getItemUseStateNum(),
			pCPlayerCharacterEntity->getDynamicData()->mLevel
			);*/
		//�Ӽ���
		//�ӽű���
		
	}
	//-------------------------------------------------------------------------------------------------
    void CItemManager::notifyUIAddItem( PlayerItem* pItem )
    {
		IdType selectGeneralId = UIClanInfo::getInstance().getCurGenrealId();
		if(pItem->getItemSiteType() == ITEM_SITE_TYPE_CHARACTER_BAG)
		{
			if (pItem->getItemRecord()->characterId == CPlayer::getInstance().getMainPlayerCharacterId())
				UIClanInfo::getInstance().addItem(pItem, pItem->getItemSiteType(),true);
			else
				UIClanInfo::getInstance().addItem(pItem, pItem->getItemSiteType(),false);
		}
		else
			UIClanInfo::getInstance().addItem(pItem, pItem->getItemSiteType(),false);
		
		
    }
    //-------------------------------------------------------------------------------------------------
    void CItemManager::notifyUIDeleteItem(PlayerItem* item,ITEM_SITE_TYPE type, U32 index )
    {
        if (item)
        {
			if(item->getItemRecord()->characterId == CPlayer::getInstance().getMainPlayerCharacterId())
				UIClanInfo::getInstance().deleteItem(index, type,true);
			else
				UIClanInfo::getInstance().deleteItem(index, type,false);

        }
		else
			UIClanInfo::getInstance().deleteItem(index, type,false);
		
    }
    //-------------------------------------------------------------------------------------------------
    void CItemManager::notifyUIUpdateItem(PlayerItem* item, ITEM_SITE_TYPE type, U32 index, U32 num )
    {
		if (item)
		{
			if(item->getItemRecord()->characterId == CPlayer::getInstance().getMainPlayerCharacterId())
				UIClanInfo::getInstance().updateItem(index, num, type,true);
			else
				UIClanInfo::getInstance().updateItem(index, num, type,false);

		}
		else
			UIClanInfo::getInstance().updateItem(index, num, type, false);
    }
    //-------------------------------------------------------------------------------------------------
    MG::U32 CItemManager::getClanBagSize()
    {
        return getClanItems()->getSize();
    }
    //-------------------------------------------------------------------------------------------------
    void CItemManager::handlRemoveItem( PlayerItem* pItem, ITEM_SITE_TYPE sendType, PlayerCharacterIdType id /*= 0*/ )
    {
        ItemManager::removeItem(pItem->getItemDBID(), sendType, id);
        notifyUIDeleteItem(pItem, sendType, pItem->getItemIndex());
    }
	//-------------------------------------------------------------------------------------------------
	void CItemManager::handlAddMoney( Int num, Byte type )
	{
		CItemManager::getInstance().addMoney(num, (ITEM_MONEY_CLASS)type);
		//֪ͨUI ��Ǯ����
        notifyUIUpdateMoney();
		Str16 tempStr;
		CGameMessageConfig::getInstance().getMoneyString(num,tempStr);
		if (num > 0)
		{
			MessageManager::getInstance().addChatMsgForTest(L"���%s��Ǯ", tempStr.c_str());
		}
		else
			MessageManager::getInstance().addChatMsgForTest(L"�۳�%s��Ǯ", tempStr.c_str());
		
		UIItemShop::getInstance().updateMoney();
		UIClanInfo::getInstance().updateMoney();

	}
	//-------------------------------------------------------------------------------------------------
	void CItemManager::handlAddExp( U32 num, Byte type, IdType objId, Byte objType )
	{
		CClan* pCClan = CPlayer::getInstance().getActiveClan();
		DYNAMIC_ASSERT(pCClan);
		CPlayerCharacter* pCCharacter = pCClan->getPlayerCharacter(objId);
		DYNAMIC_ASSERT(NULL != pCCharacter);


		LevelManager::getInstance().addExp(pCCharacter, type, num);

		//֪ͨUI�Ӿ��顣��
		MessageManager::getInstance().addChatMsgForTest("��� ����ֵ %d", num);
	}
	//-------------------------------------------------------------------------------------------------
	void CItemManager::handUpdateItemNum( PT_ITEM_S2C_UPDATE_NUM_DATA* data, Int account )
	{ 
         for (Int i = 0;i <account;i++)
         {
              PlayerItem* pItem = findItem(data->slotIndex,(ITEM_SITE_TYPE)data->belongPos);
			  DYNAMIC_ASSERT(pItem);
			  pItem->setItemNum(data->curNum);
			  notifyUIUpdateItem(pItem, (ITEM_SITE_TYPE)data->belongPos,data->slotIndex,data->curNum);
			  data++;
         }
		 
	}
   //-------------------------------------------------------------------------------------------------
	void CItemManager::notifyUIUpdateMoney()
	{
          UIClanInfo::getInstance().updateMoney();
	}
	//-------------------------------------------------------------------------------------------------
	MG::Bool CItemManager::handleCheckCanAddToClanBag( U32 itemTempId,U32 num )
	{
		const ItemInfo* pInfo =  ItemTemplate::getInstance().getItemInfo( itemTempId );
		if (pInfo->getItemBaseItemType() == ITEM_TYPE_MONEY || pInfo->getItemBaseItemType() == ITEM_TYPE_EXP)
		{
			//��ʱ�����Ǿ���ͽ�Ǯ������
			return true;
		}
		else
		{
			checkCanAdd(itemTempId,num);
		}
	}
	//-------------------------------------------------------------------------------------------------
	void CItemManager::calAttr( CCharacter* pSCharacter, PlayerItem* pPlayerItem, Bool isAdd )
	{
		CAttributeSystem* pSAttributeSystem = pSCharacter->getAttributeSystem();
		std::map<U32, Flt> tempAttrMap;	 
		getAttrMapBySlot(pPlayerItem, &tempAttrMap);

		std::map<U32, Flt>::iterator front = tempAttrMap.begin();
		std::map<U32, Flt>::iterator back = tempAttrMap.end();
		while (front != back)
		{
			if ( isAdd )
			{	
				pSAttributeSystem->calRelateAttr(
					front->first, front->second,
					pSCharacter->getCharacterTempInfo()->getCharacterFormulaType(),
					pSCharacter->getCharacterData()
					);
			}
			else
			{	
				pSAttributeSystem->calRelateAttr(
					front->first, -front->second,
					pSCharacter->getCharacterTempInfo()->getCharacterFormulaType(),
					pSCharacter->getCharacterData()
					);
			}

			++front;
		}
	}
	//-------------------------------------------------------------------------------------------------
	void CItemManager::calAttr( PlayerCharacterIdType id, PlayerItem* pPlayerItem, Bool isAdd )
	{
		CCharacter* pCCharacter = CPlayer::getInstance().getActiveClan()->getCharacter(id, GOT_PLAYERCHARACTER);
		if (NULL == pCCharacter)
			return;

		calAttr(pCCharacter, pPlayerItem, isAdd);
	}
	//-------------------------------------------------------------------------------------------------
	void CItemManager::calAttrAll( CCharacter* pSCharacter )
	{
		GenrealEquip* pGenrealEquip  = getGenrealEquip( pSCharacter->getID());
		DYNAMIC_ASSERT(pGenrealEquip);
		PlayerItem* pPlayerItem = NULL;
		for (Int i=1; i<ITEM_EQUIP_SLOT_TYPE_MAX; i++)
		{
			pPlayerItem = pGenrealEquip->findItem((ITEM_EQUIP_SLOT_TYPE)i);
			if ( NULL != pPlayerItem )
				calAttr(pSCharacter, pPlayerItem, true);
		}
	}
	//-------------------------------------------------------------------------------------------------
	void CItemManager::calAttrAllBase( CCharacter* pSCharacter )
	{
		GenrealEquip* pGenrealEquip  = getGenrealEquip( pSCharacter->getID());
		if (NULL == pGenrealEquip) return;
		PlayerItem* pPlayerItem = NULL;

		for (Int i=1; i<ITEM_EQUIP_SLOT_TYPE_MAX; i++)
		{
			pPlayerItem = pGenrealEquip->findItem((ITEM_EQUIP_SLOT_TYPE)i);
			if ( NULL != pPlayerItem )
			{
				CAttributeSystem* pSAttributeSystem = pSCharacter->getAttributeSystem();
				std::map<U32, Flt> tempAttrMap;	 
				getAttrMapBySlot(pPlayerItem, &tempAttrMap);

				std::map<U32, Flt>::iterator front = tempAttrMap.begin();
				std::map<U32, Flt>::iterator back = tempAttrMap.end();
				while (front != back)
				{
					pSAttributeSystem->addValue(
						front->first,
						front->second
						);

					++front;
				}
			}
		}
	}
	//-------------------------------------------------------------------------------------------------
	void CItemManager::getAttrMapBySlot( PlayerItem* pPlayerItem, std::map<U32, Flt>* pAttrMap )
	{
		if ( pPlayerItem )
		{
			//���ҵ��������ԡ�
			const AttributeAppendInfo* tempAppendAttr = AttributeAppend::getInstance().getAttributeAppendInfo(pPlayerItem->getItemInfo()->getItemEquitAttrAppendId());
			if ( tempAppendAttr )
			{
				for (Int i=0; i<APPENDATTR_NUM; i++)
				{
					if ( tempAppendAttr->AppendAttrList[i].id )
					{  
						if ( tempAppendAttr->AppendType == APPEND_TYPE_REAL )
							(*pAttrMap)[tempAppendAttr->AppendAttrList[i].id] += tempAppendAttr->AppendAttrList[i].value;
						else
							(*pAttrMap)[tempAppendAttr->AppendAttrList[i].id] += 
							tempAppendAttr->AppendAttrList[i].value*pPlayerItem->getItemInfo()->getItemBaseScore()*PERMILLAGE_VALUE;
					}
					else
						continue;
				}
			}
			//��������
			if ( pPlayerItem->getItemRecord()->randAppendID )
			{
				tempAppendAttr = AttributeAppend::getInstance().getAttributeAppendInfo(pPlayerItem->getItemRecord()->randAppendID);
				if ( tempAppendAttr )
				{
					for (Int i=0; i<APPENDATTR_NUM; i++)
					{
						if ( tempAppendAttr->AppendAttrList[i].id )
						{   
							if ( tempAppendAttr->AppendType == APPEND_TYPE_REAL )
								(*pAttrMap)[tempAppendAttr->AppendAttrList[i].id] += tempAppendAttr->AppendAttrList[i].value;
							else
								(*pAttrMap)[tempAppendAttr->AppendAttrList[i].id] += 
								tempAppendAttr->AppendAttrList[i].value*pPlayerItem->getItemInfo()->getItemBaseScore()*PERMILLAGE_VALUE;
						}
						else
							continue;
					}
				}
			}
			//ǿ������
			if ( pPlayerItem->getItemRecord()->curStrengthenLv )
			{
				if ( pPlayerItem->getItemInfo()->getItemEquitStrenRandAttrAppendId() )
				{
					tempAppendAttr = AttributeAppend::getInstance().getAttributeAppendInfo(pPlayerItem->getItemInfo()->getItemEquitStrenRandAttrAppendId());
					if ( tempAppendAttr )
					{
						for (Int i=0; i<APPENDATTR_NUM; i++)
						{
							if ( tempAppendAttr->AppendAttrList[i].id )
							{   
								if ( tempAppendAttr->AppendType == APPEND_TYPE_REAL )
									(*pAttrMap)[tempAppendAttr->AppendAttrList[i].id] += tempAppendAttr->AppendAttrList[i].value;
								else
									(*pAttrMap)[tempAppendAttr->AppendAttrList[i].id] += 
									tempAppendAttr->AppendAttrList[i].value*pPlayerItem->getItemRecord()->curStrengthenLv*PERMILLAGE_VALUE;
							}
							else
								break;
						}
					}
					//ǿ����������
					if ( pPlayerItem->getItemRecord()->strengthenAppendID )
					{
						tempAppendAttr = AttributeAppend::getInstance().getAttributeAppendInfo(pPlayerItem->getItemRecord()->strengthenAppendID);
						if ( tempAppendAttr )
						{
							for (Int i=0; i<APPENDATTR_NUM; i++)
							{
								if ( tempAppendAttr->AppendAttrList[i].id )
								{   
									if ( tempAppendAttr->AppendType == APPEND_TYPE_REAL)
										(*pAttrMap)[tempAppendAttr->AppendAttrList[i].id] += tempAppendAttr->AppendAttrList[i].value;
									else
										(*pAttrMap)[tempAppendAttr->AppendAttrList[i].id] += 
										tempAppendAttr->AppendAttrList[i].value*pPlayerItem->getItemRecord()->curStrengthenLv*PERMILLAGE_VALUE;
								}
								else
									break;
							}
						}
					}
				}          
			}
		}
	}
	//-------------------------------------------------------------------------------------------------
	void CItemManager::handleClearAllItem()
	{
		clearAllItem();
	}
	//-------------------------------------------------------------------------------------------------
	void CItemManager::addGameJudgeErrorMsgForClient( GAMEJUDGE_TYPE judgeType )
	{
		switch (judgeType)
		{
		case GAMEJUDGE_TYPE_CHARACTER_LEVEL_ERROR:
			{
				MessageManager::getInstance().addChatMsgForTest(L"��ɫ�ȼ�����!");
			}
			break;
		case GAMEJUDGE_TYPE_CHARACTER_TYPE_ERROR:
			{
                MessageManager::getInstance().addChatMsgForTest(L"��ɫ���Ͳ���!");
			}
			break;
		case GAMEJUDGE_TYPE_CHARACTER_GENDER_TYPE_ERROR:
			{
               MessageManager::getInstance().addChatMsgForTest(L"��ɫ�Ա𲻶�!");
			}
			break;
		case GAMEJUDGE_TYPE_CHARACTER_POWERFULL_TYPE_ERROR:
			{
               MessageManager::getInstance().addChatMsgForTest(L"��ɫְҵ����!");
			}
			break;

		}

	}
}