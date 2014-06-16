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
        //���֣�Ʒ��
        void    setItemName(U32& height);
        //����������λ��
        void    setItemEquipType(U32& height);
        //���
        void    setItemIntro(U32& height);
        //��
        void    setItemBind(U32& height);
        //�;�
        void    setItemDurable(U32& height);
        //��ʧ
        void    setItemDisappear(U32& height);
        //����
        void    setItemLimit(U32& height);
        //���Լӳ�
        void    setItemAttr(U32& height);
        //��װ
        void    setItemSuit(U32& height);
        //֧�����
        void    setItemSupport(U32& height);
        //�ѵ�������������Ϸ��
        void    setItemMoney(U32& height, ITEM_TIPS_TYPE showType);
        //����tips��λ��
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