//**********************************************************************************************************
#ifndef _H_PLAYERITEM_
#define _H_PLAYERITEM_
//**********************************************************************************************************
#include "WorldCorePreqs.h"
#include "ItemTemplate.h"
//**********************************************************************************************************
namespace MG
{
    //----------------------------------------------------------------------------------------

        //数量	数据名称	类型	长度	应用	说明	
        //1	ItemDataBaseId	u int	32	    客/服	物品数据的变化记录id	
        //2	ItemTempLateId	u int	32	    客/服	此条变化记录是基于哪个物品模板id的
        //3		            u int	32	    客/服	物品属于氏族或据点
        //4		            u int	32	    客/服	物品属于类型id	
        //5		            u int	32	    客/服	物品当前所在格位	"0～无意义1～氏族仓库2～角色身上3～拍卖栏4～回购栏5～邮箱栏6～已销毁"  
        //6		            u int	32	    客/服	根据以上格位，物品所在的序列位置	
        //7		            u int	32	    客/服	物品绑定角色或氏族的id	
        //8		            Str16	32	    客/服	物品制造者id,合成物品才具备	
        //9		            u int	32	    客/服	物品当前堆叠数量	
        //10		        u int	32	    客/服	物品当前耐久	
        //11		        u int	32	    客/服	物品当前修理次数	
        //12		        u int	32	    客/服	物品当前强化次数	
        //13		        u int	32	    客/服	物品随机属性附加id	
        //14		        u int	32	    客/服	物品强化属性附加id	
        //15		        u int	32	    客/服	物品实例到期时间	
        //16		        u int	32	    客/服	物品实例诞生的时间，用于数据排查	
        //17		        u int	32	    客/服	物品实例被销毁的时间，用于数据排查	
        //18		        u int	32	    客/服	物品实例最近变更时间，用于数据排查	

    //----------------------------------------------------------------------------------------
    struct ItemRecord 
    {
        IdType              itemDBID            ; 
        U32                 itemTempID          ;
        ITEM_BELONG_TYPE    itemBelongType      ;
        IdType              itemBelongID        ;  //物品绑定角色或氏族的
        ITEM_SITE_TYPE      belongPos           ;      //物品当前所在格位
        ITEM_BIND_TYPE      bindType            ;
        U32                 slotIndex           ;
        Char16              fatherName[MAX_CHARACTER_NAME_LEN]          ;
        U32                 curNum              ;
        U32                 curDurable          ;
        U32                 curRepairNum        ;
        U32                 curStrengthenLv     ;
        U32                 randAppendID        ;
        U32                 strengthenAppendID  ;
        U64                 dueTime             ;
        U64                 bornTime            ;
        U64                 delTime             ;
        U64                 updateTime          ;
        PlayerCharacterIdType characterId       ;
        //---------------------------------------------------------------------------------------
        ItemRecord()
			:itemDBID(0),
			itemTempID(0)
            ,itemBelongType(ITEM_BELONG_TYPE_NULL)
            ,itemBelongID(0)
            ,belongPos(ITEM_SITE_TYPE_NULL)
            ,bindType(ITEM_BIND_TYPE_NULL)
            ,slotIndex(0)
            ,curNum(1)
            ,curDurable(0)
            ,curRepairNum(0)
            ,curStrengthenLv(0)
            ,randAppendID(0)
            ,strengthenAppendID(0)
            ,dueTime(0)
            ,bornTime(0)
            ,delTime(0)
            ,characterId(0)
        {
            fatherName[0] = L'0';
            fatherName[1] = L'\0';
        }
        //----------------------------------------------------------------------------------------
        ItemRecord& operator=(const ItemRecord& A)
        {
            itemDBID                                  = A.itemDBID                 ;
            itemTempID                                = A.itemTempID               ;
            itemBelongType                            = A.itemBelongType           ;
            itemBelongID                              = A.itemBelongID             ;
            belongPos                                 = A.belongPos                ;
            slotIndex                                 = A.slotIndex                    ;
            bindType                                  = A.bindType                 ;
            memcpy((void*)fatherName, (void*)A.fatherName, sizeof(fatherName))     ;
            curNum                                    = A.curNum                   ;
            curDurable                                = A.curDurable               ;
            curRepairNum                              = A.curRepairNum             ;
            curStrengthenLv                           = A.curStrengthenLv          ;
            randAppendID                              = A.randAppendID             ;
            strengthenAppendID                        = A.strengthenAppendID       ;
            dueTime                                   = A.dueTime                  ;
            bornTime                                  = A.bornTime                 ;
            delTime                                   = A.delTime                  ;
            updateTime                                = A.updateTime               ;
            characterId                               = A.characterId              ;
            
            return *this;
        }
        //----------------------------------------------------------------------------------------
        void clear()
        {
            itemDBID                                  = 0               ;
            itemTempID                                = 0               ;
            itemBelongType                            = ITEM_BELONG_TYPE_NULL               ;
            itemBelongID                              = 0               ;
            belongPos                                 = ITEM_SITE_TYPE_NULL                ;
            bindType                                  = ITEM_BIND_TYPE_NULL;
            slotIndex                                 = 0               ;
            fatherName[0] = L'0';
            fatherName[1] = L'\0';
            curNum                                    = 1               ;
            curDurable                                = 0               ;
            curRepairNum                              = 0               ;
            curStrengthenLv                           = 0               ;
            randAppendID                              = 0               ;
            strengthenAppendID                        = 0               ;
            dueTime                                   = 0               ;
            bornTime                                  = 0               ;
            delTime                                   = 0               ;
            updateTime                                = 0               ;
            characterId                               = 0               ;
        }
    };
    //----------------------------------------------------------------------------------------
    class PlayerItem
    {
    public:
        PlayerItem();
        ~PlayerItem();

    public:
        IdType                  getItemDBID()const{return mItemRecord->itemDBID;}
        U32                     getItemIndex()const{return mItemRecord->slotIndex;}
        U32                     getItemTempID()const{return mItemRecord->itemTempID;}
        Bool                    ifOverlying()const;
        ITEM_EQUIP_SLOT_TYPE    getItemEquipSlotType()const;
        ITEM_TYPE               getItemType()const{return mItemInfo->ItemType;}
        U32                     getItemNum()const{return mItemRecord->curNum;}
        U32                     getItemPileMaxNum()const;
        U32                     getItemRepairNum()const{return mItemRecord->curRepairNum;}
        ITEM_SITE_TYPE          getItemSiteType()const{return mItemRecord->belongPos;}
        U32                     getItemCurDur()const{return mItemRecord->curDurable;}

    public:
        void                    setCharacterID(PlayerCharacterIdType id){mItemRecord->characterId = id;}
        void                    setItemNum(U32 num);
        void                    setItemIndex(U32 index);
        void                    setItemPos(ITEM_SITE_TYPE type);
        void                    setBindType(ITEM_BIND_TYPE type){mItemRecord->bindType = type;}
        void                    setItemBelongID(ITEM_BELONG_TYPE type, IdType belongID){mItemRecord->itemBelongType = type; mItemRecord->itemBelongID = belongID;}
        void                    setItemDur(U32 dur){mItemRecord->curDurable = dur;}
        void                    setItemTempID(U32 tempID){mItemRecord->itemTempID = tempID;}
        void                    setItemFather(Str16 name){memcpy(mItemRecord->fatherName, name.c_str(), name.length()); mItemRecord->fatherName[name.length()] = L'\0';}
        void                    setItemRepairNum(Int num){ mItemRecord->curRepairNum = num;}

	public:
		void					setNewBase(ITEM_BELONG_TYPE type, IdType belongId, UInt slotIndex, UInt num);
		void					setNewEquip();

    public:
        void                    setItemRecord(ItemRecord* pRecord);
        ItemRecord*             getItemRecord()const{return mItemRecord;}
        const ItemInfo*         getItemInfo()const{return mItemInfo;}
        void                    reset(U32 itemTemplate, U32 itemID);
        void                    reset(U32 itemTemplate, ItemRecord* pRecord);

    private:
        void                    clear();
        void                    setItemTemplateInfo();

    protected:
    private:
        const ItemInfo*         mItemInfo;
        ItemRecord*             mItemRecord;

    };
}
//**********************************************************************************************************
#endif
//**********************************************************************************************************