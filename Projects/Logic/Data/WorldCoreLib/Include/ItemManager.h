//**********************************************************************************************************
#ifndef _H_ITEMMANAGER_
#define _H_ITEMMANAGER_
//**********************************************************************************************************
#include "WorldCorePreqs.h"
#include "ClanItems.h"
#include "BuyBackItem.h"
#include "DeletedItems.h"
//**********************************************************************************************************
namespace MG
{
    class ItemManager
    {
    public:

        ItemManager();
        virtual ~ItemManager();

    public:

        void            clear();
		void			clearAllItem();

    public:
        void            createItemBag(PlayerCharacterIdType charid); 
        void            eraseItemBag(PlayerCharacterIdType charid);

    public:
        //money;
        void            addMoney(Int num, ITEM_MONEY_CLASS type);
        Int             getMoney(ITEM_MONEY_CLASS type);
        //add
        void            addItem(PlayerItem* pItem, ITEM_SITE_TYPE type, Bool isServer, PlayerCharacterIdType id);
        PlayerItem*     addItem(ItemRecord* pRecord, ITEM_SITE_TYPE type, Bool isServer, PlayerCharacterIdType id);
		//find
      
		PlayerItem*   findItem(IdType itemDBID, ITEM_SITE_TYPE type, PlayerCharacterIdType id = 0);
        PlayerItem*   findItem(U32 slotIndex, ITEM_SITE_TYPE type, PlayerCharacterIdType id = 0);
        PlayerItem*   findItem(IdType itemDBID);
		//PlayerItem*   findItemByTemplateId(U32 itemplateId,ITEM_SITE_TYPE type, PlayerCharacterIdType id = 0);
		U32           findItemCountByTemplateId(U32 itemplateId,ITEM_SITE_TYPE type, PlayerCharacterIdType id = 0);

        //remove
        PlayerItem*     removeItem(IdType itemDBID, ITEM_SITE_TYPE type, PlayerCharacterIdType id = 0);
        PlayerItem*     removeItem(U32 index, ITEM_SITE_TYPE type, PlayerCharacterIdType id = 0);
        //delete
        ITEM_DELETE_ERROR            deleteItem(IdType itemDBID, ITEM_SITE_TYPE type, PlayerCharacterIdType id = 0);
        ITEM_DELETE_ERROR            deleteItem(U32 slotIndex, ITEM_SITE_TYPE type, PlayerCharacterIdType id = 0);      

    public:
        ClanItems*                                          getClanItems(){return &mClanItems;}
        GenrealItem*                                        getGenrealItem(PlayerCharacterIdType id);
        GenrealEquip*                                       getGenrealEquip(PlayerCharacterIdType id);
		PlayerItem**										getEquipArrayByPlayerCharacterId(PlayerCharacterIdType id);
        std::map<PlayerCharacterIdType, GenrealItem*>*      getGenrealItemMap();
        std::map<PlayerCharacterIdType, GenrealEquip*>*     getGenrealEquipMap();
		BuyBackItem*                                        getBuyBackItems(){return &mBuyBackItem;}
		DeletedItem*                                        getDeletedItems(){return &mDeletedItem;}

    public:
        U32                                         getItemNum(ITEM_SITE_TYPE type, PlayerCharacterIdType id = 0);
        Bool                                        checkItemFull(ITEM_SITE_TYPE type, PlayerCharacterIdType id = 0);
        
		
		//////////////////////////////////////////////////////////////////////////
		Bool                                        checkCanAdd( U32 itemTemplateId,U32 num );
		Bool                                        checkCanAdd(std::vector<ItemNum>& itemVector);
		Bool                                        checkIsNeedOverlay(U32 itemTemplateId);
        //Bool                                        checkCanAddMoney();
		//Bool                                        checkCanAddE
    private:
        BuyBackItem                                     mBuyBackItem;
		DeletedItem                                     mDeletedItem;
		ClanItems                                       mClanItems;
        std::map<PlayerCharacterIdType, GenrealItem*>   mGenrealItemMap;
        std::map<PlayerCharacterIdType, GenrealEquip*>  mGenrealEquipMap;
		
        UInt                                            mMoney[ITEM_MONEY_CLASS_MAX];

    };
}
//**********************************************************************************************************
#endif
//**********************************************************************************************************