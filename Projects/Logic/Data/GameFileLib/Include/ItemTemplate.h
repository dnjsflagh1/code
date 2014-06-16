//*****************************************************************************************************************
#ifndef _H_ITEMTEMPLATE_
#define _H_ITEMTEMPLATE_
//*****************************************************************************************************************
#include "GameFilePreqs.h"
//*****************************************************************************************************************
namespace MG
{
		//cd时间单位，毫秒
		//逻辑层面cd时间单位以毫秒为准
		//配置文件CD单位。毫秒

		//----------------------------------------------------------------------
		//	"物品类型，单选
		//	1~通用经验类物品，2~通用货币类物品，3~氏族使用类物品
		//	4~将领装备类物品，5~将领使用类物品，6~其他一般类物品
		//	6以后陆续添加"

		enum ITEM_TYPE
		{
			ITEM_TYPE_NONE,

			ITEM_TYPE_EXP		= 1,					//1~通用经验类物品
			ITEM_TYPE_MONEY			,					//2~通用货币类物品
			ITEM_TYPE_USE_CLAN		,					//3~氏族使用类物品
			ITEM_TYPE_EQUIP_GENERAL	,					//4~将领装备类物品
			ITEM_TYPE_USE_GENERAL	,					//5~将领使用类物品
			ITEM_TYPE_OTHER			,					//6~其他一般类物品（材料，任务等）

			ITEM_TYPE_MAX
		};

        //-------------------------------------------------------------------------------
        struct ItemInfo 
        {
             ItemIdType		ItemId;
             ITEM_TYPE      ItemType;
             ItemIdType		ItemListId;

             const ItemUseInfo*     		mItemUseInfo;
             const ItemEquipInfo*   		mItemEquipInfo;
             const ItemOtherInfo*   		mItemOtherInfo;
             const ItemMoneyInfo*   		mItemMoneyInfo;
			 const ItemExpListCsvInfo*		mItemExpInfo;
			 const ItemClanListCsvInfo*		mItemClanInfo;

			 const ArtIconResCsvInfo*		mArtIconResCsv;
			 
             //--------------------------------------------------
             ItemInfo();
             Bool                   init();
             //--------------------------------------------------
             const ItemUseInfo*     		getItemUseInfo()const;
             const ItemEquipInfo*   		getItemEquipInfo()const;
             const ItemOtherInfo*   		getItemOtherInfo()const;
             const ItemMoneyInfo*   		getItemMoneyInfo()const;
			 const ItemExpListCsvInfo*		getItemExpInfo()const;
			 const ItemClanListCsvInfo*		getItemClanInfo()const;
             //--------------------------------------------------
             ItemIdType				getItemBaseTemplateID()const{return ItemId;}
             ITEM_TYPE              getItemBaseItemType()const{return ItemType;}
             Str16                  getItemBaseItemName()const;
             Str16                  getItemBaseItemText()const;
             void                   getItemBaseIconResouce(Str8& resName, Str8& groupName, Str8& itemName)const;
             U32                    getItemBaseDropMashID()const;
             U64                    getItemBasePrice()const;
             U64                    getItemBaseSellPrice()const;
             U64                    getItemBaseBuyPrice()const;
             U64                    getItemBaseMaxPileNum()const;
             U64                    getItemBaseScore()const;
             ITEM_RANK              getItemBaseRank()const;
             ITEM_BIND_TYPE         getItemBaseBindType()const;
             U32                    getItemBaseDisppearType()const;
             U32                    getItemBaseForbidType()const;
             ITEM_EXISTENCE_TIME_TYPE   getItemBaseExistenceTimeType()const;
             U64                    getItemBaseExistenceTime()const;
             U32                    getItemBaseClanJudgeID()const;
             U32                    getItemBaseCharacterJudgeID()const;
             //--------------------------------------------------
             //other
             ITEM_OTHER_CLASS       getItemOtherClass()const;
             //--------------------------------------------------
             //money
             //U32                    getItemMoneyBaseHoldNum()const;
             //U32                    getItemMoneyAddHoldNum()const;
			 ITEM_MONEY_CLASS       getItemMoneyClass()const;
             //--------------------------------------------------
             //use
             ITEM_USE_CLASS         getItemUseClass()const;
             U64                    getItemUseCaseTime()const;
             U32                    getItemUsePublicTimepieceId()const;
             U64                    getItemUsePublicTimepieceDelay()const;
             U32                    getItemUseOwnerTimepieceId()const;
             U64                    getItemUseOwnerTimepieceDelay()const;
             U32                    getItemUseResetTimepieceId()const;
             U32                    getItemUseResetTimepieceGroupId()const;
             U32                    getItemUseGiveQuestId()const;
             ItemIdType				getItemUseGiveItemGroupId()const;
             //U32                  getItemUseSkillId()const;
             U32                    getItemUseStateId()const;
             U64                    getItemUseStateNum()const;
             ITEM_USE_RESTORE_TYPE  getItemUseRestoreType()const;
             U32                    getItemUseRestoreParameter1()const;
			 U32                    getItemUseRestoreParameter2()const;
			 U32                    getItemUseRestoreParameter3()const;
             Str16                  getItemUseScript()const;
             //--------------------------------------------------
             //equipt
             ITEM_EQUIP_CLASS       getItemEquitClass()const;
             U32                    getItemEquitMaleMash()const;
             U32                    getItemEquitFemaleMash()const;
             U64                    getItemEquitRepairPrice()const;
             U64                    getItemEquitMaxUpGrade()const;
             U64                    getItemEquitMaxFixNum()const;
             U64                    getItemEquitMaxEquipDurable()const;
             ITEM_EQUIP_SLOT_TYPE   getItemEquitEquipSlotType()const;
             U32                    getItemEquitSuitId()const;
             U32                    getItemEquitAttrAppendId()const;
             U32                    getItemEquitRandAttrAppendId()const;
             U32                    getItemEquitStrenAttrAppendId()const;
             U32                    getItemEquitStrenRandAttrAppendId()const;
             U32                    getItemEquitSkillId()const;
             U32                    getItemEquitStateId()const;
             U64                    getItemEquitStateNum()const;
             U32                    getItemEquitWeaponActionId()const;
             Str16                  getItemEquitScript()const;
 
        };
        //-------------------------------------------------------------------------------
        class ItemTemplate
        {
			enum ItemTemplateRow
			{
				ItemTemplateRow_ItemId			= 0,
				ItemTemplateRow_Notes,
				ItemTemplateRow_ItemType,
				ItemTemplateRow_ItemListId,

				ItemTemplateRow_Max
			};

        public:
            ItemTemplate();
            ~ItemTemplate();
            SINGLETON_INSTANCE(ItemTemplate);

        public:
            Bool            load(Str16 fileName, IMGExternalPackManager* packManager = NULL);
            const ItemInfo* getItemInfo(ItemIdType tempID);

        private:
            SimpleMapDataSetManager<ItemIdType, ItemInfo>        mItemList;

        };

}
//*****************************************************************************************************************
#endif
//*****************************************************************************************************************