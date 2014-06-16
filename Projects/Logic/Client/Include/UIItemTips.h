//*****************************************************************************************************
#ifndef _H_UIITEMTIPS_
#define _H_UIITEMTIPS_
//*****************************************************************************************************
#include "UIObject.h"
//*****************************************************************************************************
namespace MG
{
    class UIItemTips : public UIObject
    {
    public:
        UIItemTips();
        virtual ~UIItemTips();
        SINGLETON_INSTANCE(UIItemTips);
    public:
        void    openItemTips(const PlayerItem* pItem, CoordI coord, ITEM_TIPS_TYPE showType = ITEM_TIPS_TYPE_GENERAL);
        void    openItemTips(const ItemInfo* pItemInfo, CoordI coord, ITEM_TIPS_TYPE showType = ITEM_TIPS_TYPE_GENERAL);
        void    openItemTips(const ItemRecord* pItemRecord, CoordI coord, ITEM_TIPS_TYPE showType = ITEM_TIPS_TYPE_GENERAL);

        virtual Bool    closeGui();
    private:
        void    setItemTipsInfo(CoordI coord, ITEM_TIPS_TYPE showType);
        //名字，品级
        void    setItemName(U32& height);
        //武器，武器位置
        void    setItemEquipType(U32& height);
        //简介
        void    setItemIntro(U32& height);
        //绑定
        void    setItemBind(U32& height);
        //耐久
        void    setItemDurable(U32& height);
        //消失
        void    setItemDisappear(U32& height);
        //限制
        void    setItemLimit(U32& height);
        //属性加成
        void    setItemAttr(U32& height);
        //套装
        void    setItemSuit(U32& height);
        //支持类别
        void    setItemSupport(U32& height);
        //堆叠数，卖出的游戏币
        void    setItemMoney(U32& height, ITEM_TIPS_TYPE showType);
        //设置tips的位置
        void    setTipsCoord(U32 height, CoordI coord);
       
    private:
        const ItemRecord*    	 	mItemRecord;
        const ItemEquipInfo* 	 	mItemEquipInfo;
        const ItemUseInfo*   	 	mItemUseInfo;
        const ItemOtherInfo* 	 	mItemOtherInfo;
		const ItemClanListCsvInfo*  mItemClanInfo;
    };
}
//*****************************************************************************************************
#endif
//*****************************************************************************************************