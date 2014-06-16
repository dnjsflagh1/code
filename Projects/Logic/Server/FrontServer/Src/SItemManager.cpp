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
        //此函数是一定是加到氏族仓库。
		Bool isNeedOverlay = getClanItems()->checkIsNeedOverlay(itemTempID);
		if (isNeedOverlay)
		{
			_handAddItemOverlay(itemTempID,num);
		}
		else
		{    //不需要判断叠加
             for (Int i = 0; i<num;i++)
             {  
				 _addItemToOneSlot(itemTempID,1);
             }
		}

		//判断是否是任务物品,以后如果有任务物品背包需独立出来
		SClanQuestManager*  questManager = getSClanQuestManager();
		for (Int i = 0;i <num; i++)
		{
			questManager->notifyGetOrDropItem(itemTempID,true);
		}

       
    }
    //----------------------------------------------------------------------------------------
    void SItemManager::handlAddItem( PlayerItem* pItem )
    {
        //放入格位中;
        ItemManager::addItem(pItem, ITEM_SITE_TYPE_CLAN, true, 0);
		updateClanItemToDB();
    }
    //----------------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------------
    itembag_del_res SItemManager::handlDelItem(IdType itemDBID, ITEM_SITE_TYPE type, PlayerCharacterIdType id)
    {
		if (type == ITEM_SITE_TYPE_CLAN)
		{
			//任务判断,只考虑背包
			PlayerItem* pItem = findItem(itemDBID,type,id);
			SClanQuestManager*  questManager = getSClanQuestManager();
			for (Int i = 0;i <pItem->getItemNum(); i++)
			{
				questManager->notifyGetOrDropItem(pItem->getItemTempID(),false);
			}
		}
		//不能删除只有三种可能
        //1，不存在，2，不能删除，3，界面不设删除功能
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
        //交换，可能是不同界面交换
        PlayerItem* pSendItem = findItem(sendIndex, sendtype, charId); 
        PlayerItem* pRecvItem = findItem(recvIndex, recvtype, charId);

		// 没有物品则退出
		if ( pSendItem == NULL )
			return item_changepos_res_Error_notchange;

        //如果有一个是装备栏
        if ( sendtype != recvtype  &&  ( sendtype == ITEM_SITE_TYPE_CHARACTER_EQUIP  ||  recvtype == ITEM_SITE_TYPE_CHARACTER_EQUIP  ) )
        {
            //交换位置
            if ( pRecvItem )
            {
                //如果不是装备
                if ( pSendItem->getItemType() != ITEM_TYPE_EQUIP_GENERAL  ||  pRecvItem->getItemType() != ITEM_TYPE_EQUIP_GENERAL )
                    return item_changepos_res_Error_notEquip;
                //如果位置不匹配;
                if ( pSendItem->getItemEquipSlotType() != pRecvItem->getItemEquipSlotType() )
                    return item_changepos_res_Error_Equip_pos;
			  
				//氏族&角色判定
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

                //交换playerItem;
				ItemManager::removeItem(sendIndex, sendtype, charId);
				ItemManager::removeItem(recvIndex, recvtype, charId);
               

                pRecvItem->setItemIndex(sendIndex);
                pSendItem->setItemIndex(recvIndex);
                ItemManager::addItem(pRecvItem, sendtype, true, charId);
                ItemManager::addItem(pSendItem, recvtype, true, charId);
                //通知DB                  
				if (sendtype == ITEM_SITE_TYPE_CLAN  ||  recvtype == ITEM_SITE_TYPE_CLAN)
				{   
					 updateClanItemToDB();
					 updatePlayerCharacterItemToDB(charId);
				}
				else
				{
					updatePlayerCharacterItemToDB(charId);
				}
				
                //通知MapSever
                if ( sendtype == ITEM_SITE_TYPE_CHARACTER_EQUIP )   
                    sendChangeEquipToMaqServer(charId, pRecvItem, sendIndex);
                else
                    sendChangeEquipToMaqServer(charId, pSendItem, recvIndex); 
				
				return item_changepos_res_Succeed;
            }
            else 
            {
                //从装备栏拿下来
                if ( sendtype == ITEM_SITE_TYPE_CHARACTER_EQUIP )
                {   
                    //交换playerItem;
                    ItemManager::removeItem(sendIndex, sendtype, charId);
                    pSendItem->setItemIndex(recvIndex);
                    ItemManager::addItem(pSendItem, recvtype, true, charId);
                    //通知DB                      ;
					if (sendtype == ITEM_SITE_TYPE_CLAN  ||  recvtype == ITEM_SITE_TYPE_CLAN)
					{   
						updateClanItemToDB();
						updatePlayerCharacterItemToDB(charId);
					}
					else
					{
						updatePlayerCharacterItemToDB(charId);
					}
                    //通知MapSever
                    sendChangeEquipToMaqServer(charId, NULL, sendIndex);

					return item_changepos_res_Succeed;
                }
                //穿装备
                else
                {
                    //如果不是装备
                    if ( pSendItem->getItemType() != ITEM_TYPE_EQUIP_GENERAL )
                        return item_changepos_res_Error_notEquip;
                    //如果位置不匹配;
                    if ( pSendItem->getItemEquipSlotType() != recvIndex )
                        return item_changepos_res_Error_Equip_pos;
                     
					//氏族&角色判定
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


                    //交换playerItem;
                   // ItemManager::removeItem(pSendItem->getItemDBID(), sendtype, charId);
                    ItemManager::removeItem(sendIndex, sendtype, charId);
                    pSendItem->setItemIndex(recvIndex);
                    ItemManager::addItem(pSendItem, recvtype, true, charId);
                    //通知DB                       
					if (sendtype == ITEM_SITE_TYPE_CLAN  ||  recvtype == ITEM_SITE_TYPE_CLAN)
					{   
						updateClanItemToDB();
						updatePlayerCharacterItemToDB(charId);
					}
					else
					{
						updatePlayerCharacterItemToDB(charId);
					}
                    //通知MapSever
                    sendChangeEquipToMaqServer(charId, pSendItem, recvIndex);

					return item_changepos_res_Succeed;
                }
            }
        }
        //如果没有装备栏
        else if ( sendtype != ITEM_SITE_TYPE_CHARACTER_EQUIP  &&  recvtype != ITEM_SITE_TYPE_CHARACTER_EQUIP )
        {
            //交换位置或交换
            if ( pRecvItem )
            {
                //是否可以叠加
                if ( pSendItem->getItemTempID()  ==  pRecvItem->getItemTempID()  &&  pSendItem->ifOverlying() )
                {
                    //判断是否超过最大值
                    U32 sendNum = pSendItem->getItemNum();
                    U32 recvNum = pRecvItem->getItemNum();
                    U32 maxNum = pSendItem->getItemPileMaxNum();
                    if ( sendNum + recvNum > maxNum )
                    {    
                        sendNum = (sendNum + recvNum) - maxNum;
                        recvNum = maxNum;
                        //索引值改变
                        pRecvItem->setItemNum(recvNum);
                        pSendItem->setItemNum(sendNum);
                        //通知DB                  
						updateClanItemToDB();
						updatePlayerCharacterItemToDB(charId);

						return item_changepos_res_Succeed;
                    }
                    else
                    {
                        recvNum += sendNum;
                        //索引值改变
                        pRecvItem->setItemNum(recvNum);
                        //删除pSendItem
                        handlDelItem(sendIndex, sendtype, charId);
                        //更新 pRecvItem 的num                     
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
                //交换位置
                else
                {
                    //交换playerItem;
					ItemManager::removeItem(sendIndex, sendtype, charId);
					ItemManager::removeItem(recvIndex, recvtype, charId);
                    pSendItem->setItemIndex(recvIndex);
                    pRecvItem->setItemIndex(sendIndex);
                    ItemManager::addItem(pSendItem, recvtype, true, charId); 
                    ItemManager::addItem(pRecvItem, sendtype, true, charId);
                    //通知DB                  ;
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
            //移动道具
            else 
            {
                //交换playerItem;
                ItemManager::removeItem(sendIndex, sendtype, charId);
                pSendItem->setItemIndex(recvIndex);
                ItemManager::addItem(pSendItem, recvtype, true, charId);
                //通知DB                       
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
        //其它情况，不能交换 
        return item_changepos_res_Error_notchange;
    }
    //----------------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------------
    void SItemManager::sendItemInfo()
    {
        std::vector<ItemRecord*> itemRecordList;

        //获取clanItem里的道具
        const std::map<IdType, PlayerItem*>* tempMapClanItem = getClanItems()->getPlayerItemMap();
        std::map<IdType, PlayerItem*>::const_iterator front = tempMapClanItem->begin();
        std::map<IdType, PlayerItem*>::const_iterator back = tempMapClanItem->end();
        while (front != back)
        {
            itemRecordList.push_back(front->second->getItemRecord());
            ++front;
        }

        //获取角色背包里的道具
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

		//角色装备信息
		std::map<PlayerCharacterIdType, GenrealEquip*>* tempGenrealEquipMap = getGenrealEquipMap();
		std::map<PlayerCharacterIdType, GenrealEquip*>::iterator frontGenrealEquip = tempGenrealEquipMap->begin();
		std::map<PlayerCharacterIdType, GenrealEquip*>::iterator backGenrealEquip = tempGenrealEquipMap->end();
		while (frontGenrealEquip != backGenrealEquip)
		{
			PlayerItem** genrealEquipArray = frontGenrealEquip->second->getEquipItemArray();
			//角色装备
			for (Int i=1; i<ITEM_EQUIP_SLOT_TYPE_MAX; i++)
			{
				if (genrealEquipArray[i] != NULL)
				{
					itemRecordList.push_back(genrealEquipArray[i]->getItemRecord());
				}
			}
           
           frontGenrealEquip++;
		}
		
		//获取回购栏里的数据
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
		//目标位置是否有道具
		PlayerItem* pTargetItem = findItem(selectIndex,splitType,id);
        if (pTargetItem == NULL)
        {
            pSelfItem->setItemNum(pSelfItem->getItemNum() - num);
			modifiedItem.push_back(pSelfItem);
			//获得ID。
			U32 tempID = tempID = getItemUserDefinedID();
			//创建PlayerItem。
			PlayerItem* tempItem = PlayerItemFactory::getInstance().addItem(tempID, pSelfItem->getItemTempID());
			//基本填充
			tempItem->setItemNum(num);
			tempItem->setItemPos(splitType);
			tempItem->setItemIndex(selectIndex);
            tempItem->setItemBelongID(ITEM_BELONG_TYPE_CLAN, mParent->getClanID());
			//放入格位中;
			ItemManager::addItem(tempItem, splitType, true, id);
			
			//更新数据库
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
			//通知客户端加一个物品
			ItemPacketProcesser::getInstance().sendAddItemToClient(mParent->getClientNetId(), tempItem);
			//通知客户端更改物品数量
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
		   //更新数据库
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
		   //通知客户端更改物品数量
		   ItemPacketProcesser::getInstance().sendItemUpdateNumListToClient(mParent->getClientNetId(),&modifiedItem);
		}
        return item_split_res_Succeed;
    }
    //----------------------------------------------------------------------------------------
	MG::item_use_res SItemManager::handlUseItemClient( U32 slotIndex,ITEM_SITE_TYPE type,PlayerCharacterIdType charid )
	{
		//检查是否能用道具
		PlayerItem* pItem = findItem(slotIndex, type, charid);
		if (pItem == NULL)
			return item_use_res_Error_None;

        

		//角色类使用物品
		if (pItem->getItemType() == ITEM_TYPE_USE_GENERAL)
		{
			if ( charid != mParent->getMainGenrealID() )
				return item_use_res_Error_None;
			//一，判断。
			//位置判断
			if (type !=  ITEM_SITE_TYPE_CHARACTER_BAG )
				return item_use_res_Error_Type;

			//角色是否存在。
			SPlayerCharacterPtr pSPlayerCharacter;
			mParent->getPlayerCharacter(pSPlayerCharacter,charid);
			//SPlayerCharacter* pSPlayerCharacter = mParent->getPlayerCharacterFromList(charid);
			//if ( pSPlayerCharacter == NULL )
			//	return item_use_res_Error_PC;
			
			//检查氏族 角色要求:
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
			//检查CD。并加CD, 加MapServer效果。
			sendItemUseToMapServer(pItem, charid);

		}

		//////////////////////////////////////////////////////////////////////////
		//氏族类使用物品
		else if (pItem->getItemType() == ITEM_TYPE_USE_CLAN)
		{
			//位置判断
			if (type !=  ITEM_SITE_TYPE_CLAN )
				return item_use_res_Error_Type;

			//检查氏族要求:
            if (GameJudge::getInstance().checkClanJudge(mParent,pItem->getItemInfo()->getItemBaseClanJudgeID())
				!= GAMEJUDGE_TYPE_SUCCESS)
            {
                return item_use_res_Error_Judge;
            }
            
			//氏族使用物品暂时直接在frontserver上处理
			U32 giveQuestId = pItem->getItemInfo()->getItemUseGiveQuestId();
			U32 itemGroupId =  pItem->getItemInfo()->getItemUseGiveItemGroupId();
			//开启任务id
			if ( giveQuestId )
			{
				;
			}	
			//开启道具分组 
			if ( itemGroupId )
			{
				if (handleCheckCanAddToClanBag(itemGroupId) == false)
				{
					return item_use_res_Error_ClanBag_Full;
				}
				else
				{   
					handAddItem(itemGroupId);
					//更新道具 OR 删除道具
					UInt num = pItem->getItemNum();
					if ( num > 1 )
					{
						pItem->setItemNum(num-1);
						updateClanItemToDB();
					}
					else  //删除道具
					{
						handlDelItem(pItem->getItemDBID(), type, charid);
					}
					
				}

			}
			//发送氏族使用物品送成功消息
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
		//角色使用道具
        if (pItem->getItemType() == ITEM_TYPE_USE_GENERAL)
        {
			//
			//
			//更新道具 OR 删除道具
			UInt num = pItem->getItemNum();
			if ( num > 1 )
			{
				pItem->setItemNum(num-1);
				updatePlayerCharacterItemToDB(charid);
			}
			else  //删除道具
			{
				handlDelItem(pItem->getItemDBID(), type, charid);
			}

        }
	    //氏族使用道具
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
        //重新计算武将的属性。
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
		//添加到回购栏
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

		//暂时在这处理:
		if (sendType == ITEM_SITE_TYPE_CLAN)
		{
			//任务判断,只考虑背包
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

		//分出道具和金钱。
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
		//处理金钱
		for (Int i=ITEM_MONEY_CLASS_NONE; i<ITEM_MONEY_CLASS_MAX; i++)
		{
			if (tempAddMoney[i])
			{	
				handlAddMoney(tempAddMoney[i], (ITEM_MONEY_CLASS)i);
			}
		}
		//处理经验
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

		////处理经验
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
		//修改内存
		addMoney(num, moneyClass);

		//存入DB。
		updateMoneyToDB(mParent->getClanID(), getMoney(moneyClass), moneyClass);

		//发送给客户端
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
		//修改内存
		LevelManager* pLevelManager = pSPlayerCharacter->getLevelManager(); 
		
		U32 tempLevel = 0;
		U32 tempCurExp = 0;

		pLevelManager->getLevelAndCurExp(pSPlayerCharacter, type, tempLevel, tempCurExp);
		const CharLvlInfo* pCharLvlInfo = CharacterLvlTemplate::getInstance().getCharLvlInfo((CHAR_LVL_USETYPE)type, tempLevel+1);
		if (NULL == pCharLvlInfo)
		{
			//满级了
			return;
		}

		if(false == pLevelManager->addExp(pSPlayerCharacter, type, num, isLevelUp))
		{
			//满级， 无法加经验
			//return;
		}

		//存入DB。
		updateExpToDB(pSPlayerCharacter, type);

		//发送给客户端
		ItemPacketProcesser::getInstance().sendAddExpToClient(
				mParent->getParentPlayer()->getClientNetID(),
				num,
				type,
				pSPlayerCharacter->getID(),
				pSPlayerCharacter->getType()
			);

		if ( isLevelUp )
		{
			//更新DB;
			updateLevelToDB(pSPlayerCharacter, type);
			//向MapSever发送同步消息。
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
		case CHAR_LVL_USETYPE_CHAR_LVL:		//～角色等级
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
		case CHAR_LVL_USETYPE_CHAR_LVL:		//～角色等级
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
		//氏族使用, 如宝箱，所以不考虑经验等信息...
		std::vector<ItemNum> tempItemVector;
		ItemGroupTemplate::getInstance().getItemGroupInfo(groupItemId, tempItemVector);
		const ItemInfo* pInfo = NULL;

		U32 tempAddMoney[ITEM_MONEY_CLASS_MAX] = { 0 };
		//U32 tempAddExp[CHAR_LVL_USETYPE_MAX] = { 0 };

		//分出道具和金钱。
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
		//处理金钱
		for (Int i=ITEM_MONEY_CLASS_NONE; i<ITEM_MONEY_CLASS_MAX; i++)
		{
			if (tempAddMoney[i])
			{	
				handlAddMoney(tempAddMoney[i], (ITEM_MONEY_CLASS)i);
			}
		}
		/*
		//处理经验
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
		//获得自定义ID。
		U32 tempID = getItemUserDefinedID();
		//创建PlayerItem。
		PlayerItem* pItem = PlayerItemFactory::getInstance().addItem(tempID, itemTempID);
		//基本填充
		pItem->setNewBase(ITEM_BELONG_TYPE_CLAN, mParent->getClanID(), slotIndex, num);

		//放入格位中;
		ItemManager::addItem(pItem, ITEM_SITE_TYPE_CLAN, true, 0);

		//更新数据库
		updateClanItemToDB();

		//给客服端发送消息
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

				//没有达到最大堆叠值将被修改
				if ( itemCurNum < maxOverlayNum )
				{
					modifiedPlayerItemList.push_back(pItem);
				}
				while ( itemCurNum < maxOverlayNum )
				{     
					num--;
					itemCurNum++;
					pItem->setItemNum(itemCurNum);

					//已经存放完毕
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
			//数量还有剩余寻找空闲格位添加
			_findFreeSlotAddItem(itemTempID,num,maxOverlayNum);
			
			//更新数据库
			//给客服端发送需要更改的物品数据
			updateClanItemToDB();
			ItemPacketProcesser::getInstance().sendItemUpdateNumListToClient(mParent->getClientNetId(),&modifiedPlayerItemList);
		}
		else
		{
            //当前仓库没有该物品，直接寻找空闲格位添加
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
		   //暂时不考虑经验和金钱的上线
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

		//分出道具和金钱。
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

		//以后还要添加检查金钱是否超过最大持有量。

		//判断背包是否已满。
		if (tempItemVector.size() >0 )
		{
			return checkCanAdd(tempItemVector);
		}
		return true;
		
	}
	//------------------------------------------------------------------------------------------
	MG::Bool SItemManager::handleCheckCanAddToClanBag( std::vector<ItemNum>& itemVector )
	{
		//分出道具和金钱。
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
		//以后还要添加检查金钱是否超过最大持有量。

		//判断背包是否已满。
		if (itemVector.size() >0 )
		{
			return checkCanAdd(itemVector);
		}
		return true;
	}
	//------------------------------------------------------------------------------------------
	void SItemManager::updateClanItemToDB()
	{
		//氏族背包
		std::vector<PlayerItem*> clanItemList;
        std::map<IdType, PlayerItem*>* clanItemMap = getClanItems()->getPlayerItemMap();
		std::map<IdType, PlayerItem*>::iterator front = clanItemMap->begin();
		std::map<IdType, PlayerItem*>::iterator back = clanItemMap->end();
		while (front != back)
		{
              clanItemList.push_back(front->second);
              front++;
		}
        
		//已经删除的数据
        clanItemMap = getDeletedItems()->getPlayerItemMap();
		front = clanItemMap->begin();
		back = clanItemMap->end();
		while (front != back)
		{
			clanItemList.push_back(front->second);
			front++;
		}
        
		//回购栏的数据
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
        //角色装备
		for (Int i=0; i<ITEM_EQUIP_SLOT_TYPE_MAX; i++)
		{
			if (genrealEquipArray[i] != NULL)
			{
                 characterItemList.push_back(genrealEquipArray[i]);
			}
		}
		//角色背包
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
		//暂时只在氏族背包中扣除
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
								//删除
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
				//没有足够的物品扣除
				if (deDuctCount != 0)
				{
					return;
				}
			}
			
			front++;
		}
		//
		//扣除金钱
		for (Int i=ITEM_MONEY_CLASS_NONE; i<ITEM_MONEY_CLASS_MAX; i++)
		{
			if (tempAddMoney[i])
			{	
				handlAddMoney(-tempAddMoney[i], (ITEM_MONEY_CLASS)i);
			}
		}
		updateClanItemToDB();
		//修改物品
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
					//金钱不够
                     flag = false; 
                     //front = tempItemVector.erase(front);
				}
				
			}
			else
			{
                 if (clanItem->checkItemExistInClanBag((*front).itemTemplate,(*front).num) == false)
                 {
					 //物品不够
					 flag = false; 
                 }
			}

			front++;
		}
         
		return flag;
        

	}
	//------------------------------------------------------------------------------------------
}