//**********************************************************************************************************
#ifndef _H_UIITEMSHOP_
#define _H_UIITEMSHOP_
//**********************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//**********************************************************************************************************
namespace MG
{
    enum ITEM_SHOP_TYPE
    {
        ITEM_SHOP_TYPE_NULL,

        ITEM_SHOP_TYPE_SHOP,
        ITEM_SHOP_TYPE_CALLBACK,

        ITEM_SHOP_TYPE_MAX
    };

    class UIItemShop : public UIObject
    {
    public:
        UIItemShop();
        ~UIItemShop();
        SINGLETON_INSTANCE(UIItemShop);

    public:
        virtual void        setEvent();

    public://外部接口
        void                openShop(CItemShop* pShop);
		virtual void		restore();
        void                addCallBackItem(PlayerItem* pItem);
        void                deleteCallBackItem(PlayerItem* pItem, U32 index);
        //void                updateShopItem(U32 tempId, U32 num, U32 index);
        UInt                getShopId();
		void                sendSellItem(IconInfo* pSendInfo);
		void				updateMoney();

    private:
		//选择蒙板
        void                setSelectVisble(Int Index, Bool isVisble);
		void				setHighVisble(Int Index, Bool isVisble );
		//操作显示内容
		void                changeItemByItemShopType(ITEM_SHOP_TYPE type);
		void                clearItemList(ITEM_SHOP_TYPE type);
        void                addShopItemList();
        void                addShopItem(Int Index, ItemNum tempItem);
        void                addCallBackItemList();
        void                addCallBackItem(Int Index, PlayerItem* pItem);
		void				addItem(Int Index, ITEM_SHOP_TYPE type, const ItemInfo* iteminfo, U32 num = 1, IdType dbId = 0);
		//操作页面按钮
		void                initShopPage();
		void				initCallbackPage();
        void                changePage(Bool isAdd);
		 Bool                handlePageBnt(Bool isAdd);
		//卖或购买道具
		void                sendBuyItem();
		
		//修理按钮
		void				showRepairBnt();
		
		static void			onCancleBuyShopItem(void* arg);
		static void			onSureBuyShopItem(void* arg);

    private://事件函数
        static void         onSellItemEvent(void* widget);
        static void         onClickBntShopEvent(void* widget);
        static void         onClickBntCallBackEvent(void* widget);
        static void         onClickBntBuyItem(void* widget);
		static void         onRightClickImgBuyItem(void* widget);
        static void         onClickBntRepairItem(void* widget);
        static void         onClickImageItem(void* widget);
        static void         onClickBntLeft(void* widget);
        static void         onClickBntRight(void* widget);
		static void			onEventToolTips(void* pWidget, Bool isShow, Int left, Int top);
		static void			onSetMouseFocusEvent(void* pGetWidget, void* pLostWidget);
		static void			onLostMouseFocusEvent(void* pGetWidget, void* pLostWidget);

    private:
        Int                 mSelectIndex;
        U32                 mCurShopPage;
        U32                 mTotalShopPage;
        U32                 mCurCallBackPage;
        U32                 mTotalCallBackPage;
        ITEM_SHOP_TYPE      mItemShopType;

        CItemShop*          mCItemShop;

    };
}
//**********************************************************************************************************
#endif
//**********************************************************************************************************