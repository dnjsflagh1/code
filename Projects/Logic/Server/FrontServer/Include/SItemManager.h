//**********************************************************************************************************
#ifndef _H_SITEMMANAGER_
#define _H_SITEMMANAGER_
//**********************************************************************************************************
#include "FrontServerPreqs.h"
#include "ItemManager.h"
#include "ItemNetPacket.h"
//**********************************************************************************************************
namespace MG
{
    class SItemManager : public ItemManager
    {
    public:

        SItemManager();
        virtual ~SItemManager();

    public:

        void                    setParent(SClan* clan){ mParent = clan ;}
 
		void                    loadClanItemDBData(std::vector<ItemRecord>& recordList);
		void                    loadPlayerCharacterDBdata(std::vector<ItemRecord>& recordList);
        void                    sendItemInfo();
        void                    setSize();
    public:
        //加DB
        void                    handlAddItem(U32 itemTempID, U32 num);
        void                    handAddItem(U32 groupItemId);


        itembag_del_res         handlDelItem(IdType itemDBID, ITEM_SITE_TYPE type, PlayerCharacterIdType id = 0);
		itembag_del_res         handlDelItem(U32 slotIndex, ITEM_SITE_TYPE type, PlayerCharacterIdType id = 0);
        void                    handlDelItem(IdType itemDBID, ITEM_SITE_TYPE type,Int num, PlayerCharacterIdType id = 0);
        item_changepos_res      handlChangItem(U32 sendIndex, U32 recvIndex, ITEM_SITE_TYPE sendtype, ITEM_SITE_TYPE recvtype, PlayerCharacterIdType charId);
        item_split_res          handlSplitItem(U32 slotIndex, ITEM_SITE_TYPE selfType, ITEM_SITE_TYPE splitType, U32 selectIndex, U32 num,
			PlayerCharacterIdType id = 0);
        
		item_use_res            handlUseItemClient(U32 slotIndex,ITEM_SITE_TYPE type,PlayerCharacterIdType charid);
		item_use_res            handlUseItemMapServer(U32 slotIndex,ITEM_SITE_TYPE type, PlayerCharacterIdType charid);

		//item_use_res            handlUseItemClient(IdType itemDBId, PlayerCharacterIdType charid);
		//item_use_res            handlUseItemMapServer(IdType itemDBId, PlayerCharacterIdType charid);



        void                    handlSellItemToShop(PlayerItem* pItem, ITEM_SITE_TYPE sendType, ITEM_SITE_TYPE recvType, PlayerCharacterIdType id = 0);
        void                    handlAddItem(PlayerItem* pItem);
		void					handlRewardItemMapServer(SPlayerCharacter* pSPlayerCharacter, U32 groupItemId);
		void					handlAddMoney(Int num, ITEM_MONEY_CLASS moneyClass);
		void					handlAddExp(U32 num, CHAR_LVL_USETYPE type, SPlayerCharacter* pSPlayerCharacter);
		void					handlPickItemMapServer(PlayerCharacterIdType charId, U32 itemTempId, U32 num);
        void                    handlDeductQuestItem(U32 groupItemId); //扣除任务物品
		//Bool                    handl
		//ylh 
		void					handleDropItemAddExp(SPlayerCharacter* pSPlayerCharacter, U32 itemTempId, Int num);
        
		//////////////////////////////////////////////////////////////////////////
		Bool                    handleCheckCanAddToClanBag(U32 itemTempId,U32 num);
        Bool                    handleCheckCanAddToClanBag(U32 groupItemId);
        Bool                    handleCheckCanAddToClanBag( std::vector<ItemNum>& itemVector);
        Bool                    handleCheckItemExistInClanBag(U32 groupItemId);
    private:
		////////////////////////////////////////////////////////////////////////////	
		void					updateMoneyToDB(ClanIdType clanid, U32 value, Byte type);
		void					updateExpToDB(SPlayerCharacter* pSPlayerCharacter, Byte type);
		void					updateLevelToDB(SPlayerCharacter* pSPlayerCharacter, Byte type);
        void                    updateClanItemToDB();
		void                    updatePlayerCharacterItemToDB(PlayerCharacterIdType charId);
		
		void                    _handAddItemOverlay(U32 itemTempID, U32 num);
		void                    _findFreeSlotAddItem(U32 itemTempID,U32 num,U32 maxOverlayNum);
		void                    _addItemToOneSlot(U32 itemTempID, U32 num);
        U32                     getItemUserDefinedID();
		void                    deleteDefinedID(IdType definedID);
    private:
        void                    sendChangeEquipToMaqServer(PlayerCharacterIdType id, PlayerItem* pItem, U32 pos);
        void                    sendItemUseToMapServer(PlayerItem* pItem, PlayerCharacterIdType charid);

    private:
		SClanQuestManager*      getSClanQuestManager();
        SClan*                  mParent;
		
		//自定义物品ID序列
		std::map<IdType,IdType>     mDefinedItemIdMap;
		
    };
}
//**********************************************************************************************************
#endif
//**********************************************************************************************************
