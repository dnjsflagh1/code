//**********************************************************************************************************
#include "stdafx.h"
#include "UIItemShop.h"
#include "CItemShop.h"
#include "ShopPacketProcesser.h"
#include "ItemTemplate.h"
#include "CItemManager.h"
#include "UIMessageBox.h"
#include "ClientMain.h"
#include "PlayerItem.h"
#include "UIItemTips.h"
#include "UIYesNoMsgBox.h"
//**********************************************************************************************************
namespace MG
{
    UIItemShop::UIItemShop()
        :mSelectIndex(-1)
        ,mCItemShop(NULL)
        ,mCurShopPage(1)
        ,mTotalShopPage(1)
        ,mCurCallBackPage(1)
        ,mTotalCallBackPage(1)
        ,mItemShopType(ITEM_SHOP_TYPE_NULL)
    {

    }
    //--------------------------------------------------------------------------------------
    UIItemShop::~UIItemShop()
    {

    }
    //--------------------------------------------------------------------------------------
    void UIItemShop::setEvent()
    {
        Char8 temp[24] = "";
        IWidget* p = NULL;

        p = getLayout()->getWidget("btnshop");
        p->setMouseButtonClickEvent(onClickBntShopEvent);

        p = getLayout()->getWidget("btncallback");
        p->setMouseButtonClickEvent(onClickBntCallBackEvent);

        p = getLayout()->getWidget("goumai");
        p->setMouseButtonClickEvent(onClickBntBuyItem);

        p = getLayout()->getWidget("xiuli");
        p->setMouseButtonClickEvent(onClickBntRepairItem);

        p = getLayout()->getWidget("btnleft");
        p->setMouseButtonClickEvent(onClickBntLeft);

        p = getLayout()->getWidget("btnright");
        p->setMouseButtonClickEvent(onClickBntRight);

        for (Int i=1; i<=ITEM_SHOP_NUM; i++)
        {
            sprintf_s(temp, 24, "icon_item-%d", i);
            p = getLayout()->getWidget(temp);
            p->setMouseButtonClickEvent(onClickImageItem);
            p->setMouseButtonRightClickEvent(onRightClickImgBuyItem);
			p->setToolTipsEvent(onEventToolTips);
			p->setMouseSetFocusEvent(onSetMouseFocusEvent);
			p->setMouseLostFocusEvent(onLostMouseFocusEvent);
			p->setNeedToolTip(true);
			IconInfo info;
			info.group = ICON_GROUP_ITEMSHOP;
			info.type = ICON_TYPE_ITEM;
			info.index = i;
            p->setUserData(info);
        }
		//callback
		/*for (Int i=1; i<=ITEM_SHOP_NUM; i++)
		{
			sprintf_s(temp, 24, "h_icon_item-%d", i);
			p = getLayout()->getWidget(temp);
			p->setMouseButtonClickEvent(onClickImageItem);
			p->setMouseButtonReleasedEvent(onSellItemEvent);
			p->setToolTipsEvent(onEventToolTips);
			p->setMouseSetFocusEvent(onSetMouseFocusEvent);
			p->setMouseLostFocusEvent(onLostMouseFocusEvent);
			p->setNeedToolTip(true);
			IconInfo info;
			info.group = ICON_GROUP_ITEMSHOP;
			info.type = ICON_TYPE_ITEM;
			info.index = i;
			p->setUserData(info);

		}*/
		/*p = getLayout()->getWidget("callback_btn");
		p->setMouseButtonClickEvent(onClickBntBuyItem);*/

		p = getLayout()->getWidget("h_repair_btn");
		p->setMouseButtonClickEvent(onClickBntRepairItem);

		/*p = getLayout()->getWidget("h_pageup_btn");
		p->setMouseButtonClickEvent(onClickBntLeft);

		p = getLayout()->getWidget("h_pagedown_btn");
		p->setMouseButtonClickEvent(onClickBntRight);*/

    }
    //--------------------------------------------------------------------------------------
    void UIItemShop::openShop( CItemShop* pShop )
    {
        openGui();

        setSelectVisble(-1, false);
       /* if ( mCItemShop != pShop )
        {*/
            mCItemShop = pShop;
			clearItemList(ITEM_SHOP_TYPE_SHOP);
            initShopPage();
            addShopItemList();
			updateMoney();

			//是否显示修理按钮。

        //}
    }
	//--------------------------------------------------------------------------------------
	void UIItemShop::updateMoney()
	{
		//显示金钱
		if (isOpen())
		{
			CItemManager* pItemManager = &( CItemManager::getInstance() );

			IWidget* pWidget = NULL;
			Char8 temp[64] = "";
			Int money = pItemManager->getMoney(ITEM_MONEY_CLASS_MONEY_GAME);
			if (money > 0)
			{
				U32 guan = money/1000;
				U32 wen = money-1000*guan;
				if (guan > 0)
				{
					sprintf_s(temp, 64, "100000zong");
					Char16 guanStr[16] = L"";
					swprintf_s(guanStr, 16, L"%d", guan);
					pWidget = getLayout()->getWidget(temp);
					pWidget->setCaption(guanStr);
				}
				else
				{
					sprintf_s(temp, 64, "100000zong");
					pWidget = getLayout()->getWidget(temp);
					pWidget->setCaption(L"0");
				}
				sprintf_s(temp, 64, "100zong");
				Char16 wenStr[16] = L"";
				swprintf_s(wenStr, 16, L"%d", wen);
				pWidget = getLayout()->getWidget(temp);
				pWidget->setCaption(wenStr);
			}
			else
			{
				sprintf_s(temp, 64, "100000zong");
				pWidget = getLayout()->getWidget(temp);
				pWidget->setCaption(L"0");

				sprintf_s(temp, 64, "100zong");
				pWidget = getLayout()->getWidget(temp);
				pWidget->setCaption(L"0");
			}
		}
	}
    //--------------------------------------------------------------------------------------
    void UIItemShop::setSelectVisble( Int Index, Bool isVisble )
    {
        IWidget* pImage = getLayout()->getWidget("item-check1");
		DYNAMIC_ASSERT(pImage);

        if ( isVisble )
        {
            U32  mCurPage;
            switch ( mItemShopType )
            {
            case ITEM_SHOP_TYPE_SHOP:
                mCurPage = mCurShopPage;
                break;
            case ITEM_SHOP_TYPE_CALLBACK:
                mCurPage = mCurCallBackPage;
                break;
            }
           

			Char8 tempChar[32] = "";
			sprintf_s(tempChar, 32, "_Col%d", Index);
			IWidget* pWidget = getLayout()->getWidget(tempChar);
			DYNAMIC_ASSERT(pWidget);

			Char8 temp[32] = "";
			sprintf_s(temp, 32, "icon_item-%d", Index);
			IWidget* cWidget = getLayout()->getWidget(temp);
			DYNAMIC_ASSERT(cWidget);

			IAny* pAny = cWidget->getUserData();
			DYNAMIC_ASSERT(pAny);
			IconInfo* pInfo = pAny->castType<IconInfo>();
			DYNAMIC_ASSERT(pInfo);

			if ( pInfo->index )
			{
				pImage->setPosition( pWidget->getPosition());
				pImage->setVisible(true);
				mSelectIndex = Index + ITEM_SHOP_NUM*(mCurPage-1);
			}
        }
        else
        {
            mSelectIndex = -1;
            pImage->setVisible(false);
        }
    }
	void UIItemShop::setHighVisble(Int Index, Bool isVisble )
	{
		//IWidget* pImage = getLayout()->getWidget("iconhigh");
		IWidget* pImage = getLayout()->getWidget("item-highlight1");

		if ( isVisble )
		{
			Char8 tempChar[32] = "";
			sprintf_s(tempChar, 32, "_Col%d", Index);
			IWidget* pWidget = getLayout()->getWidget(tempChar);
			pImage->setPosition( pWidget->getPosition());
			pImage->setVisible(true);
		}
		else
		{
			pImage->setVisible(false);
		}
	}
    //--------------------------------------------------------------------------------------
    void UIItemShop::addShopItemList()
    {
        //clearItemList(ITEM_SHOP_TYPE_SHOP);

        U32 nStart = ITEM_SHOP_NUM*(mCurShopPage-1);
        U32 nEnd = ITEM_SHOP_NUM*mCurShopPage;
        U32 nCount = mCItemShop->getItemNumNumber();
        if ( nEnd < nCount )
            nCount = nEnd;

        for (U32 i=nStart; i<nCount; i++ )
        {
            ItemNum tempItemNum = mCItemShop->getItemNumByIndex(i);
            DYNAMIC_ASSERT(tempItemNum.itemTemplate);

            addShopItem(i-nStart+1, tempItemNum);
        }
    }
	void UIItemShop::addItem(Int Index, ITEM_SHOP_TYPE type, const ItemInfo* iteminfo, U32 num, IdType dbId)
	{
		IImage* pImage = NULL;
		IWidget* pWidget = NULL;
		Char8 temp[64] = "";

		
		if (type == ITEM_SHOP_TYPE_SHOP)
		{
			//图片
			sprintf_s(temp, 64, "icon_item-%d", Index);
			pImage = getLayout()->getImage(temp); 
			Str8 resName, groupName, itemName;
			iteminfo->getItemBaseIconResouce(resName, groupName, itemName);
			pImage->setTexture(resName, groupName, itemName);
			IconInfo* pInfo = pImage->getWidget()->getUserData()->castType<IconInfo>();
			DYNAMIC_ASSERT(pInfo);
			pInfo->tempID = iteminfo->getItemBaseTemplateID();
			pInfo->dbID = dbId;
			pInfo->index = Index;
			pImage->getWidget()->setUserData(*pInfo);
			//名字
			sprintf_s(temp, 64, "itemname-text-%d", Index);
			pWidget = getLayout()->getWidget(temp);
			pWidget->setCaption(iteminfo->getItemBaseItemName()) ;
			//数量
			sprintf_s(temp, 64, "text-%d", Index);
			pWidget = getLayout()->getWidget(temp);
			Char16 tempNumStr[16] = L"";
			swprintf_s(tempNumStr, 16, L"%d", num);
			pWidget->setCaption(tempNumStr) ;
			//钱
			U32 money = iteminfo->getItemBaseBuyPrice()*num;
			U32 guan = money/1000;
			U32 wen = money-1000*guan;
			Char16 tempMoneyStr[16] = L"";
			//小于1贯时隐藏"贯"图标

			//贯的图片
			
			if (guan == 0)
			{
				sprintf_s(temp, 64, "100000-%d", Index);
				pWidget = getLayout()->getWidget(temp);
				pWidget->setVisible(false);
				sprintf_s(temp, 64, "guan-%d", Index);
				pWidget = getLayout()->getWidget(temp);
				pWidget->setVisible(false);

			}
			else
			{
				sprintf_s(temp, 64, "100000-%d", Index);
				
				swprintf_s(tempMoneyStr, 16, L"%d", guan);
				pWidget = getLayout()->getWidget(temp);
				pWidget->setCaption(tempMoneyStr);
				sprintf_s(temp, 64, "guan-%d", Index);
				pWidget = getLayout()->getWidget(temp);
				pWidget->setVisible(true);
			}

			sprintf_s(temp, 64, "100-%d", Index);
			pWidget = getLayout()->getWidget(temp);
			swprintf_s(tempMoneyStr, 16, L"%d", wen);
			pWidget->setCaption(tempMoneyStr);

			//文的图片
			sprintf_s(temp, 64, "wen-%d", Index);
			pWidget = getLayout()->getWidget(temp);
			pWidget->setVisible(true);
		}
		else
		{
			//图片
			sprintf_s(temp, 64, "h_icon_item-%d", Index);
			pImage = getLayout()->getImage(temp); 
			Str8 resName, groupName, itemName;
			iteminfo->getItemBaseIconResouce(resName, groupName, itemName);
			pImage->setTexture(resName, groupName, itemName);
			IconInfo* pInfo = pImage->getWidget()->getUserData()->castType<IconInfo>();
			DYNAMIC_ASSERT(pInfo);
			pInfo->tempID = iteminfo->getItemBaseTemplateID();
			pInfo->dbID = dbId;
			pInfo->index = Index;
			pImage->getWidget()->setUserData(*pInfo);
			//名字
			sprintf_s(temp, 64, "h_itemname-text-%d", Index);
			pWidget = getLayout()->getWidget(temp);
			pWidget->setCaption(iteminfo->getItemBaseItemName()) ;
			//数量
			sprintf_s(temp, 64, "h_text-%d", Index);
			pWidget = getLayout()->getWidget(temp);
			Char16 tempNumStr[16] = L"";
			swprintf_s(tempNumStr, 16, L"%d", num);
			pWidget->setCaption(tempNumStr) ;
			//钱
			U32 money = iteminfo->getItemBaseBuyPrice()*num;
			U32 guan = money/1000;
			U32 wen = money-1000*guan;
			Char16 tempMoneyStr[16] = L"";
			//小于1贯时隐藏"贯"图标

			//贯的图片

			if (guan == 0)
			{
				sprintf_s(temp, 64, "h_100000-%d", Index);
				pWidget = getLayout()->getWidget(temp);
				pWidget->setVisible(false);
				sprintf_s(temp, 64, "h_guan-%d", Index);
				pWidget = getLayout()->getWidget(temp);
				pWidget->setVisible(false);

			}
			else
			{
				sprintf_s(temp, 64, "h_100000-%d", Index);

				swprintf_s(tempMoneyStr, 16, L"%d", guan);
				pWidget = getLayout()->getWidget(temp);
				pWidget->setCaption(tempMoneyStr);
				sprintf_s(temp, 64, "guan-%d", Index);
				pWidget = getLayout()->getWidget(temp);
				pWidget->setVisible(true);
			}

			sprintf_s(temp, 64, "h_100-%d", Index);
			pWidget = getLayout()->getWidget(temp);
			swprintf_s(tempMoneyStr, 16, L"%d", wen);
			pWidget->setCaption(tempMoneyStr);

			//文的图片
			sprintf_s(temp, 64, "h_wen-%d", Index);
			pWidget = getLayout()->getWidget(temp);
			pWidget->setVisible(true);
		}
		
	}
    //--------------------------------------------------------------------------------------
    void UIItemShop::addShopItem( Int Index, ItemNum tempItem )
    {
        const ItemInfo* iteminfo = ItemTemplate::getInstance().getItemInfo(tempItem.itemTemplate);
        DYNAMIC_ASSERT(iteminfo);

        addItem(Index, ITEM_SHOP_TYPE_SHOP, iteminfo,tempItem.num);
    }
    //--------------------------------------------------------------------------------------
	void UIItemShop::onSureBuyShopItem(void* arg)
	{
		UIItemShop* pInstance = (UIItemShop*)arg;
		
		ItemNum tempNum = pInstance->mCItemShop->getItemNumByIndex(pInstance->mSelectIndex-1);
		
		if ( tempNum.itemTemplate != 0 )
		{
			if ( CItemManager::getInstance().handleCheckCanAddToClanBag(tempNum.itemTemplate,tempNum.num) )
			{
				ShopPacketProcesser::getInstance().sendShopBuyItem(pInstance->mCItemShop->getShopInfo()->ItemShopID, tempNum.itemTemplate, tempNum.num);
			}
			else
				//提示：
				UIMessageBox::getInstance().showHint(L"itemshop", L"itemshopTitle", L"", L"itemshop", L"itemshoperror4", L"");
			
		}
	}
	//--------------------------------------------------------------------------------------
	void UIItemShop::onCancleBuyShopItem(void* arg)
	{
		UIYesNoMsgBox::getInstance().closeGui();
		return;
	}
	//--------------------------------------------------------------------------------------
    void UIItemShop::sendBuyItem()
    {
		//检查是否选择了物品
        if ( mSelectIndex > 0 )
        {
			//检查氏族背包是否已满
            if ( mItemShopType == ITEM_SHOP_TYPE_SHOP )
            {
				UIYesNoMsgBox::getInstance().showHint(L"购买物品确定",L"你确定要购买当前选中物品",
					(void*)(&UIItemShop::getInstance()),onSureBuyShopItem,(void*)(&UIItemShop::getInstance()),onCancleBuyShopItem);
            }
            else
            {
                PlayerItem* pItem = mCItemShop->getBuybackItemByIndex( mSelectIndex-1+ITEM_SHOP_NUM*(mCurCallBackPage-1) );
                ShopPacketProcesser::getInstance().sendShopBuybackItem(mCItemShop->getShopInfo()->ItemShopID, pItem->getItemDBID());
            }
        }
    }
    //--------------------------------------------------------------------------------------
    MG::UInt UIItemShop::getShopId()
    {
        if ( mCItemShop )
            return mCItemShop->getShopInfo()->ItemShopID;

        return 0;
    }
    //--------------------------------------------------------------------------------------
    void UIItemShop::onSellItemEvent(void* widget)
    {
		IWidget* p = (IWidget*)widget;
		if (p)
		{
			IconInfo* pInfo = p->getUserData()->castType<IconInfo>();
			DYNAMIC_ASSERT(pInfo);
			if (pInfo->tempID)
			{
				UIItemShop::getInstance().sendSellItem(pInfo);
			}
			IPointer* pPointer = ClientMain::getInstance().getPointer();
			if (pPointer)
			{
				pPointer->resetToDefaultPointer();
			}
		}
		//
  //      IAny* pSendAny = pPointer->getAnyData();
  //      //先检查是否是物品。
  //      if ( pSendAny )
  //      {
  //          IconInfo* pSendInfo = pSendAny->castType<IconInfo>();
  //          DYNAMIC_ASSERT(pSendInfo);

  //          UIItemShop::getInstance().sendSellItem(pSendInfo);

  //          pPointer->resetToDefaultPointer();
  //      }
    }
    //--------------------------------------------------------------------------------------
    void UIItemShop::onClickBntShopEvent( void* widget )
    {
        IWidget* p = (IWidget*)widget;
        p->getButton()->setStateCheck(true);

        //切换到商品界面
        UIItemShop::getInstance().changeItemByItemShopType(ITEM_SHOP_TYPE_SHOP);
		
    }
    //--------------------------------------------------------------------------------------
    void UIItemShop::onClickBntCallBackEvent( void* widget )
    {
        IWidget* p = (IWidget*)widget;
        p->getButton()->setStateCheck(true);
		
        //切换到回购界面
        UIItemShop::getInstance().changeItemByItemShopType(ITEM_SHOP_TYPE_CALLBACK);
		
    }
    //--------------------------------------------------------------------------------------
    void UIItemShop::onClickBntBuyItem( void* widget )
    {
        //购买商品。
        IWidget* p = (IWidget*)widget;
        if (p)
        {
            UIItemShop::getInstance().sendBuyItem();
        }
    }
	//--------------------------------------------------------------------------------------
	void UIItemShop::onRightClickImgBuyItem( void* widget )
	{
		//购买商品。
		IWidget* p = (IWidget*)widget;
		if (p)
		{
			IconInfo* pInfo = p->getUserData()->castType<IconInfo>();
			if (pInfo->tempID)
			{
				UIItemShop::getInstance().setSelectVisble( pInfo->index, true );
			}
			UIItemShop::getInstance().sendBuyItem();
		}
	}
    //--------------------------------------------------------------------------------------
    void UIItemShop::onClickBntRepairItem( void* widget )
    {
        //修理物品
    }
    //--------------------------------------------------------------------------------------
    void UIItemShop::onClickImageItem( void* widget )
    {
        //选中商品
        IWidget* p = (IWidget*)widget;
		IconInfo* pInfo = p->getUserData()->castType<IconInfo>();
        if (pInfo->index)
        {
            UIItemShop::getInstance().setSelectVisble( pInfo->index, true );
        }
    }
    //--------------------------------------------------------------------------------------
    void UIItemShop::onClickBntLeft( void* widget )
    {
        //切换页面。（减）
        UIItemShop::getInstance().changePage(false);
    }
    //--------------------------------------------------------------------------------------
    void UIItemShop::onClickBntRight( void* widget )
    {
        //切换页面。（加）
        UIItemShop::getInstance().changePage(true);
    }
    //--------------------------------------------------------------------------------------
    void UIItemShop::sendSellItem( IconInfo* pSendInfo )
    {
        //是否是背包的道具
        if ( pSendInfo->group == ICON_GROUP_CLAN_BAG || pSendInfo->group == ICON_GROUP_CHARACTER_BAG)
		{
			//是否是可买的
			DYNAMIC_ASSERT( pSendInfo->tempID );
			const ItemInfo* pItemInfo = ItemTemplate::getInstance().getItemInfo(pSendInfo->tempID);
			if ( pItemInfo->getItemBaseForbidType() & ITEM_FORBID_TYPE_SHOP )
			{
				//提示不可卖店。
				//？
				return;
			}
			//卖掉。
			DYNAMIC_ASSERT(pSendInfo->dbID);
		   ShopPacketProcesser::getInstance().sendShopSellItem(mCItemShop->getShopInfo()->ItemShopID, pSendInfo->dbID);
		}
    }
    //--------------------------------------------------------------------------------------
    void UIItemShop::changeItemByItemShopType( ITEM_SHOP_TYPE type )
    {
		//取消选择
		setSelectVisble(-1, false);

        if ( type == mItemShopType )
            return;

        mItemShopType = type;

        IButton* p = NULL;
		IWidget* pWidget = NULL;
		char msg[32] = "";
        switch (mItemShopType)
        {
        case ITEM_SHOP_TYPE_SHOP://商店
            {
                Sprintf_s(msg, 32, "callback_panel");
				pWidget = getLayout()->getWidget(msg);
				pWidget->setVisible(false);
				p = getLayout()->getButton("btncallback");
                p->setStateCheck(false);

				Sprintf_s(msg, 32, "shop_panel");
				pWidget = getLayout()->getWidget(msg);
				pWidget->setVisible(true);

				clearItemList(ITEM_SHOP_TYPE_CALLBACK);
                addShopItemList();   
            }
            break;
        case ITEM_SHOP_TYPE_CALLBACK://回购
            {
				Sprintf_s(msg, 32, "shop_panel");
				pWidget = getLayout()->getWidget(msg);
				pWidget->setVisible(false);
				p = getLayout()->getButton("btnshop");
                p->setStateCheck(false);

				Sprintf_s(msg, 32, "callback_panel");
				pWidget = getLayout()->getWidget(msg);
				pWidget->setVisible(true);
				//initCallbackPage();
				clearItemList(ITEM_SHOP_TYPE_SHOP);
                addCallBackItemList();    
            }
            break;
        default:
            DYNAMIC_ASSERT(0);
            break;
        }
    }
    //--------------------------------------------------------------------------------------
    void UIItemShop::changePage( Bool isAdd )
    {
        if ( handlePageBnt(isAdd)  ==  false )
            return;
        
        //取消选择。
        setSelectVisble(-1, false);
        //更新页面
        switch (mItemShopType)
        {
        case ITEM_SHOP_TYPE_SHOP:
			{
				clearItemList(ITEM_SHOP_TYPE_SHOP);
				addShopItemList();
			}
            break;
        case ITEM_SHOP_TYPE_CALLBACK:
			{
				clearItemList(ITEM_SHOP_TYPE_CALLBACK);
				addCallBackItemList();
			}
            break;
        default:
            DYNAMIC_ASSERT(0);
            break;
        }
    }
    //--------------------------------------------------------------------------------------
    void UIItemShop::clearItemList(ITEM_SHOP_TYPE type)
    {
        Char8 temp[64] = "";
        IWidget* pWidget = NULL;
		if (type == ITEM_SHOP_TYPE_SHOP)
		{
			for (Int Index=1; Index<=ITEM_SHOP_NUM; Index++)
			{    
				//图片
				sprintf_s(temp, 64, "icon_item-%d", Index);
				pWidget = getLayout()->getWidget(temp); 
				pWidget->getImage()->setTexture("", "", "");
				IconInfo nullInfo;
				pWidget->setUserData(nullInfo);
				//名字
				sprintf_s(temp, 64, "itemname-text-%d", Index);
				pWidget = getLayout()->getWidget(temp);
				pWidget->setCaption(L"") ;
				//钱。
				sprintf_s(temp, 64, "100000-%d", Index);
				pWidget = getLayout()->getWidget(temp);
				pWidget->setCaption(L"");

				sprintf_s(temp, 64, "100-%d", Index);
				pWidget = getLayout()->getWidget(temp);
				pWidget->setCaption(L"");

				sprintf_s(temp, 64, "text-%d", Index);
				pWidget = getLayout()->getWidget(temp);
				pWidget->setCaption(L"");

				//贯的图片
				sprintf_s(temp, 64, "guan-%d", Index);
				pWidget = getLayout()->getWidget(temp);
				pWidget->setVisible(false);

				//文的图片
				sprintf_s(temp, 64, "wen-%d", Index);
				pWidget = getLayout()->getWidget(temp);
				pWidget->setVisible(false);
			}
		}
		else
		{
			for (Int Index=1; Index<=ITEM_SHOP_NUM; Index++)
			{    
				//图片
				sprintf_s(temp, 64, "h_icon_item-%d", Index);
				pWidget = getLayout()->getWidget(temp); 
				pWidget->getImage()->setTexture("", "", "");
				//名字
				sprintf_s(temp, 64, "h_itemname-text-%d", Index);
				pWidget = getLayout()->getWidget(temp);
				pWidget->setCaption(L"") ;
				
				sprintf_s(temp, 64, "h_text-%d", Index);
				pWidget = getLayout()->getWidget(temp);
				pWidget->setCaption(L"");

			}
		}
       
    }
    //--------------------------------------------------------------------------------------
    void UIItemShop::addCallBackItemList()
    {
        std::vector<PlayerItem*>* pItemList = mCItemShop->getBuybackItemVector();

        U32 nStart = ITEM_SHOP_NUM*(mCurCallBackPage-1);
        U32 nEnd = ITEM_SHOP_NUM*mCurCallBackPage;
        U32 nCount = pItemList->size();
        if ( nEnd < nCount )
            nCount = nEnd;
		//设置页数
        PlayerItem* pItem = NULL;

        for (U32 i=nStart; i<nCount; i++ )
        {
            pItem = (*pItemList)[i];
            DYNAMIC_ASSERT(pItem);

            addCallBackItem(i-nStart+1, pItem);
        }
    }
    //--------------------------------------------------------------------------------------
    void UIItemShop::addCallBackItem( Int Index, PlayerItem* pItem )
    {
        const ItemInfo* iteminfo = pItem->getItemInfo();
        DYNAMIC_ASSERT(iteminfo);

        addItem(Index, ITEM_SHOP_TYPE_CALLBACK,iteminfo, 1, pItem->getItemDBID());
    }

    //--------------------------------------------------------------------------------------
    Bool UIItemShop::handlePageBnt( Bool isAdd )
    {
		//检查左右按钮是否需要disabled。
        Bool rel = true;
        //改变按钮状态
        IWidget* p = NULL;
        if ( mItemShopType == ITEM_SHOP_TYPE_SHOP )
        {
            if ( isAdd )
            {
                if ( mCurShopPage < mTotalShopPage )
                {    
                    ++mCurShopPage;  
                    if ( mCurShopPage == mTotalShopPage )
                    {
                        p = getLayout()->getWidget("btnright");
                        p->setEnabled(false);
                    }
                }
                else
                {
                    p = getLayout()->getWidget("btnright");
                    p->setEnabled(false);
                    rel = false;
                }

                p = getLayout()->getWidget("btnleft");
                p->setEnabled(true);
            }
            else
            {
                if ( mCurShopPage > 1 )
                {   
                    --mCurShopPage;  
                    if ( mCurShopPage == 1 )
                    {
                        p = getLayout()->getWidget("btnleft");
                        p->setEnabled(false);
                    }
                }
                else
                {
                    p = getLayout()->getWidget("btnleft");
                    p->setEnabled(false);

                    rel = false;
                }

                p = getLayout()->getWidget("btnright");
                p->setEnabled(true);
            }

            p = getLayout()->getWidget("currentPage_text");
            Char16 tempStr[32];
            swprintf_s(tempStr, 32, L"%d", mCurShopPage);
            p->setCaption(tempStr);

			p = getLayout()->getWidget("totalPage_text");
			Char16 totalStr[32];
			swprintf_s(totalStr, 32, L"%d", mTotalShopPage);
			p->setCaption(totalStr);
        }
        else
        {
            if ( isAdd )
            {
                if ( mCurCallBackPage < mTotalCallBackPage )
                {    
                    ++mCurCallBackPage;  
                    if ( mCurCallBackPage == mTotalCallBackPage )
                    {
                        p = getLayout()->getWidget("btnright");
                        p->setEnabled(false);
                    }
                }
                else
                {
                    p = getLayout()->getWidget("btnright");
                    p->setEnabled(false);
                    rel = false;
                }

                p = getLayout()->getWidget("btnleft");
                p->setEnabled(true);
            }
            else
            {
                if ( mCurCallBackPage > 1 )
                {   
                    --mCurCallBackPage;  
                    if ( mCurCallBackPage == 1 )
                    {
                        p = getLayout()->getWidget("btnleft");
                        p->setEnabled(false);
                    }
                }
                else
                {
                    p = getLayout()->getWidget("btnleft");
                    p->setEnabled(false);

                    rel = false;
                }

                p = getLayout()->getWidget("btnright");
                p->setEnabled(true);
            }
			p = getLayout()->getWidget("currentPage_text");
			Char16 tempStr[32];
			swprintf_s(tempStr, 32, L"%d", mCurCallBackPage);
			p->setCaption(tempStr);

			p = getLayout()->getWidget("totalPage_text");
			Char16 totalStr[32];
			swprintf_s(totalStr, 32, L"%d", mTotalCallBackPage);
			p->setCaption(totalStr);
        }
        
        return rel;
    }
    //--------------------------------------------------------------------------------------
    void UIItemShop::initShopPage()
    {
        mItemShopType = ITEM_SHOP_TYPE_SHOP;

        //初始化页数
        mCurShopPage = 1;
        mTotalShopPage = (mCItemShop->getItemNumNumber()) / ITEM_SHOP_NUM;
		Int mod = (mCItemShop->getItemNumNumber()) % ITEM_SHOP_NUM;
		if (mod > 0)
		{
			mTotalShopPage += 1;
		}
        if ( mTotalShopPage <= 0 )
            mTotalShopPage = 1;

        //显示商店当前页数
		IWidget* p = NULL;
		p = getLayout()->getWidget("currentPage_text");
		Char16 tempStr[32];
		swprintf_s(tempStr, 32, L"%d", mCurShopPage);
		p->setCaption(tempStr);

		p = getLayout()->getWidget("totalPage_text");
		Char16 totalStr[32];
		swprintf_s(totalStr, 32, L"%d", mTotalShopPage);
		p->setCaption(totalStr);

        //点亮商店按钮
        p = getLayout()->getWidget("btnshop");
        p->getButton()->setStateCheck(true);
		IWidget* pWidget = NULL;
		char msg[32] = "";
		Sprintf_s(msg, 32, "shop_panel");
		pWidget = getLayout()->getWidget(msg);
		pWidget->setVisible(true);

		if (mTotalShopPage == 1)
		{
			p = getLayout()->getWidget("btnright");
			p->setEnabled(false);
			p = getLayout()->getWidget("btnleft");
			p->setEnabled(false);
		}
		else
		{
			p = getLayout()->getWidget("btnright");
			p->setEnabled(true);
			p = getLayout()->getWidget("btnleft");
			p->setEnabled(false);
		}
    }

	void UIItemShop::initCallbackPage()
	{
		mItemShopType = ITEM_SHOP_TYPE_CALLBACK;

		//初始化页数

		mCurCallBackPage = 1;
		mTotalCallBackPage = mCItemShop->getBuybackItemNum() / ITEM_SHOP_NUM;
		if ( mTotalCallBackPage <= 0 )
			mTotalCallBackPage = 1;

		//显示商店当前页数
		IWidget* p = NULL;
		p = getLayout()->getWidget("h_currentPage");
		Char16 tempStr[32];
		swprintf_s(tempStr, 32, L"%d", mCurCallBackPage);
		p->setCaption(tempStr);

		p = getLayout()->getWidget("h_totalPage");
		Char16 totalStr[32];
		swprintf_s(totalStr, 32, L"%d", mTotalCallBackPage);
		p->setCaption(totalStr);

		//点亮回购按钮
		p = getLayout()->getWidget("btncallback");
		p->getButton()->setStateCheck(true);
	}
    //--------------------------------------------------------------------------------------
    void UIItemShop::addCallBackItem( PlayerItem* pItem )
    {
        if ( mItemShopType != ITEM_SHOP_TYPE_CALLBACK )
            return;
		
        U32 index = mCItemShop->getBuybackItemNum();
        index -= ( ITEM_SHOP_NUM*(mCurCallBackPage - 1) );

        DYNAMIC_ASSERT(index > 1  &&  index <= ITEM_SHOP_NUM);

        addCallBackItem(index, pItem);
    }
    //--------------------------------------------------------------------------------------
    void UIItemShop::deleteCallBackItem( PlayerItem* pItem, U32 index )
    {
        if ( mItemShopType != ITEM_SHOP_TYPE_CALLBACK )
            return;

        index -= ( ITEM_SHOP_NUM*(mCurCallBackPage - 1) );

        if (index > 1  &&  index <= ITEM_SHOP_NUM)
        {  
            addCallBackItemList();  
        }    
    }
	//--------------------------------------------------------------------------------------
	void UIItemShop::showRepairBnt()
	{
		IWidget* pWidget = getLayout()->getWidget("xiuli");
		if ( mCItemShop )
		{
			//检查是否包含修理功能
			if ( mCItemShop->getShopInfo()->Repair  &  ITEM_SHOP_FUNCTION_TYPE_REPAIR )
			{	
				pWidget->setVisible(true);
				return;
			}
		}

		pWidget->setVisible(false);
	}

	void UIItemShop::onEventToolTips( void* pWidget, Bool isShow, Int left, Int top )
	{
		DYNAMIC_ASSERT(pWidget);
		IWidget* pIcon = (IWidget*)pWidget;
		IAny* pAny = pIcon->getUserData();
		DYNAMIC_ASSERT(pAny);
		IconInfo* pInfo = pAny->castType<IconInfo>();
		DYNAMIC_ASSERT(pInfo);

		if ( pInfo->tempID )
		{
			if ( isShow == false )
			{
				UIItemTips::getInstance().closeGui();
			}
			else
			{
				if ( pInfo->dbID )
				{
					PlayerItem* pItem = CItemManager::getInstance().findItem(pInfo->dbID);
					DYNAMIC_ASSERT(pItem);
					UIItemTips::getInstance().openItemTips(pItem, pIcon->getAbsoluteCoord(),ITEM_TIPS_TYPE_SHOP);
				}
				else
				{
					const ItemInfo* pItemInfo = ItemTemplate::getInstance().getItemInfo(pInfo->tempID);
					UIItemTips::getInstance().openItemTips(pItemInfo, pIcon->getAbsoluteCoord(),ITEM_TIPS_TYPE_SHOP);
				}
			}
		}
	}
	//--------------------------------------------------------------------------------------
	void UIItemShop::onSetMouseFocusEvent( void* pGetWidget, void* pLostWidget )
	{
		IconInfo* pGetInfo = ((IWidget*)pGetWidget)->getUserData()->castType<IconInfo>();
		DYNAMIC_ASSERT(pGetInfo);
		if ( pGetInfo->index)
			UIItemShop::getInstance().setHighVisble(pGetInfo->index, true);
	}
	//--------------------------------------------------------------------------------------
	void UIItemShop::onLostMouseFocusEvent( void* pGetWidget, void* pLostWidget )
	{
		IconInfo* pGetInfo = ((IWidget*)pGetWidget)->getUserData()->castType<IconInfo>();
		DYNAMIC_ASSERT(pGetInfo);
		if ( pGetInfo->index )
			UIItemShop::getInstance().setHighVisble(pGetInfo->index, false);
	}
	//--------------------------------------------------------------------------------------
    void UIItemShop::restore()
    {
		mSelectIndex = -1;
		mCItemShop = NULL;
		mCurShopPage = 1;
		mTotalShopPage = 1;
		mCurCallBackPage = 1;
		mTotalCallBackPage = 1;
		mItemShopType = ITEM_SHOP_TYPE_NULL;
    }
}