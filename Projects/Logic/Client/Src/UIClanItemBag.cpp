//**********************************************************************************************************
#include "stdafx.h"
#include "UIClanItemBag.h"
#include "ItemPacketProcesser.h"
#include "ClientMain.h"
#include "CItemManager.h"
#include "CPlayer.h"
#include "CClan.h"
//**********************************************************************************************************
namespace MG
{
    UIClanItemBag::UIClanItemBag()
        :mCurPage(1)
        ,mTotalPage(1)
        ,mSelectIndex(-1)
    {

    }
    //----------------------------------------------------------------------------------
    UIClanItemBag::~UIClanItemBag()
    {

    }
    //----------------------------------------------------------------------------------
    void UIClanItemBag::setEvent()
    {
        Char8 temp[24] = "";
        Char8 tempStr[24] = "";
        IIcon* pIcon = NULL;
        IText* pText = NULL;

        for (Int i=1; i<=CLAN_ITEM_BAG_NUM; i++)
        {
            sprintf_s(temp, 24, "icon%d", i);
            pIcon = getLayout()->getIcon( temp );
            pIcon->setEventStartDrag(onStartDrag);
            pIcon->setEventDropResult(onEndDrag);
            pIcon->setRequestDragWidgetInfo(onGetDragInfo);
            IconInfo info;
            info.index = i;
            info.type = ICON_TYPE_ITEM;
            info.group = ICON_GROUP_CLAN_BAG;

            pIcon->getWidget()->setUserData(info); 

            sprintf_s(temp, 24, "text%d", i);
            pText = getLayout()->getText(temp);
            pText->getWidget()->setCaption(L"");
        }
    }
    //----------------------------------------------------------------------------------
    void UIClanItemBag::onStartDrag( void* widget1, Bool& res )
    {
        IIcon* pIconsend = (IIcon*)widget1; 
        assert(pIconsend);
        IAny* anyData = pIconsend->getWidget()->getUserData();
        IconInfo* objData =  anyData->castType<IconInfo>();
        if ( !objData  || objData->tempID == 0  )
            res = false;
        else
            res = true;
    }
    //----------------------------------------------------------------------------------
    void UIClanItemBag::onEndDrag( void* widget1, void* widget2, Bool res )
    {
        //只写背包
        IIcon* pIconsend = (IIcon*)widget1; 
        IIcon* pIconrece = (IIcon*)widget2;
        assert(pIconsend);

        IAny* anyData = pIconsend->getWidget()->getUserData();
        IconInfo* objData =  anyData->castType<IconInfo>();
        if ( objData->group == ICON_GROUP_CLAN_BAG )
        {
            //处理背包事件
            UIClanItemBag::getInstance().onHandlBag(pIconsend, pIconrece, res);
        }
    }
    //----------------------------------------------------------------------------------
    void UIClanItemBag::onGetDragInfo( void* widget1, void*& widget2, CoordI& rect, Byte& isImage )
    {
        assert(widget1);
        IIcon* pIcon = (IIcon*)(widget1);
        UIClanItemBag::getInstance().getDragInfo(pIcon, widget2, rect, isImage);
    }
    //----------------------------------------------------------------------------------
    void UIClanItemBag::getDragInfo( IIcon* pSend, void*& widget2, CoordI& rect, Byte& isImage )
    {
        IconInfo* pInfo = pSend->getWidget()->getUserData()->castType<IconInfo>();
        assert(pInfo);
        if ( pInfo->tempID == 0 )
            return;

        CoordI temp = pSend->getWidget()->getCoord();
        rect = temp;
        
        mImage = ClientMain::getInstance().getGui()->getImage(rect, pInfo->resouceName, pInfo->groupName, pInfo->itemName, true);
        widget2 = (void*)( mImage );

        isImage = ICON_DRAG_TYPE_IMAGE;
    }
    //----------------------------------------------------------------------------------
    void UIClanItemBag::onHandlBag( IIcon* pSend, IIcon* pRece, Bool ishave  )
    {
        IconInfo* pSendInfo = pSend->getWidget()->getUserData()->castType<IconInfo>();
        assert(pSendInfo);

        //丢掉
        if ( ishave == false )
        {
            //提示是否删除XXX道具
            clanBagDropItem(pSendInfo->dbID);
        } 
        else 
        {
            if ( pRece == NULL )
                return;

            IconInfo* pReceInfo = pRece->getWidget()->getUserData()->castType<IconInfo>();
            assert(pReceInfo);

            //氏族背包可以把物品放到氏族背包，角色背包，角色装备栏，快捷栏。
            if ( 
                 ICON_GROUP_CLAN_BAG        == pReceInfo->group     || 
                 ICON_GROUP_CHARACTER_BAG   == pReceInfo->group     ||
                 ICON_GROUP_CHARACTER_EQUIP == pReceInfo->group
                )
            {
                //交换位置
                clanBagChangePos(pSendInfo, pReceInfo);
            }
        }
    }
    //----------------------------------------------------------------------------------
    void UIClanItemBag::sendDropItem( IdType ID )
    {
        ItemPacketProcesser::getInstance().sendDelItem(ITEM_SITE_TYPE_CLAN, ID, 0);
    }
    //----------------------------------------------------------------------------------
    void UIClanItemBag::sendBagChangePos( U32 sendIndex, U32 recvIndex,ITEM_SITE_TYPE recvType, PlayerCharacterIdType charid )
    {
        ItemPacketProcesser::getInstance().sendChangePos(sendIndex, recvIndex, ITEM_SITE_TYPE_CLAN, recvType, charid);
    }
    //----------------------------------------------------------------------------------
    void UIClanItemBag::addItem( PlayerItem* pItem )
    {
        //检查是否需要刷新。
        //？
        //现在暂不检查。
        Char8 temp[24] = "";
        U32 index = pItem->getItemIndex()-(mCurPage-1)*CLAN_ITEM_BAG_NUM+1;
        sprintf_s(temp, 24, "icon%d", index);
        IIcon* pIcon = getLayout()->getIcon( temp );

        IconInfo*  pIconInfo = pIcon->getWidget()->getUserData()->castType<IconInfo>();
        DYNAMIC_ASSERT(pIconInfo);

        const ItemInfo* iteminfo = pItem->getItemInfo();
        DYNAMIC_ASSERT(iteminfo);

        if (pIcon)
        {
            pIconInfo->clear();
            pIconInfo->dbID = pItem->getItemDBID();
            pIconInfo->tempID = pItem->getItemTempID();
            iteminfo->getItemBaseIconResouce(pIconInfo->resouceName, pIconInfo->groupName, pIconInfo->itemName);
            pIcon->setTexture(pIconInfo->resouceName, pIconInfo->groupName, pIconInfo->itemName);
            pIcon->getWidget()->setUserData(*pIconInfo);
        }

        //text
        if ( pItem->getItemNum() > 1 )
        {
            sprintf_s(temp, 24, "text%d", index);
            IWidget* pWidget = getLayout()->getWidget(temp);
            DYNAMIC_ASSERT(pWidget);
            Str16 tempNum;
            tempNum +=  pItem->getItemNum();
            pWidget->setCaption(tempNum);
        }
    }
    //----------------------------------------------------------------------------------
    void UIClanItemBag::deleteItem( U32 index )
    {
        index -= (mCurPage-1)*CLAN_ITEM_BAG_NUM;
        Char8 temp[24] = "";
        sprintf_s(temp, 24, "icon%d", index);
        IIcon* pIcon = getLayout()->getIcon( temp );
        if (pIcon)
        {
            IconInfo*  pIconInfo = pIcon->getWidget()->getUserData()->castType<IconInfo>();
            pIcon->setTexture("", "", "");
            pIconInfo->clear();
            pIcon->getWidget()->setUserData(*pIconInfo);
        }
        sprintf_s(temp, 24, "text%d", index);
        IWidget* pWidget = getLayout()->getWidget( temp );
        if ( pWidget )
            pWidget->setCaption(L"");
    }
    //----------------------------------------------------------------------------------
    void UIClanItemBag::clearItem()
    {
        Char8 temp[24] = "";
        for (Int i=0; i<CLAN_ITEM_BAG_NUM; i++)
        {
            sprintf_s(temp, 24, "icon%d", i+1);
            IIcon* pIcon = getLayout()->getIcon( temp );
            if ( pIcon )
            {
                IconInfo*  pIconInfo = pIcon->getWidget()->getUserData()->castType<IconInfo>();
                pIcon->setTexture("", "", "");
                pIconInfo->clear();
                pIcon->getWidget()->setUserData(*pIconInfo);
            }
            sprintf_s(temp, 24, "text%d", i+1);
            IWidget* pWidget = getLayout()->getWidget( temp );
            if ( pWidget )
                pWidget->setCaption(L"");
        } 
    }
    //----------------------------------------------------------------------------------
    void UIClanItemBag::addItemList()
    {
        U32 nStart = CLAN_ITEM_BAG_NUM*(mCurPage-1);
        U32 nEnd =  CLAN_ITEM_BAG_NUM*mCurPage;
        ClanItems* pClanItems = CItemManager::getInstance().getClanItems();

        for (U32 i=nStart; i<nEnd; i++)
        {
            PlayerItem* pItem = pClanItems->findItem(i);
            if ( pItem )
                addItem(pItem);
        }
    }
    //----------------------------------------------------------------------------------
    void UIClanItemBag::updateItem( U32 index, U32 num )
    {
        Char8 temp[24] = "";
        sprintf_s(temp, 24, "text%d", index);
        IWidget* pWidget = getLayout()->getWidget( temp );
        if (pWidget)
        {
            Str16 tempNum = L"";
            if ( num > 1 )
            {  
                tempNum += num;
                pWidget->setCaption(tempNum); 
            }
            else
                pWidget->setCaption(tempNum);
        }
    }
    //----------------------------------------------------------------------------------
    void UIClanItemBag::clanBagDropItem( IdType itemdbid )
    {
        //提示信息。
        sendDropItem(itemdbid);
    }
    //----------------------------------------------------------------------------------
    void UIClanItemBag::clanBagChangePos( IconInfo* pSendInfo, IconInfo* pReceInfo )
    {
        U32 sendIndex = pSendInfo->index + CLAN_ITEM_BAG_NUM*(mCurPage-1);
        U32 recvIndex = pReceInfo->index + CLAN_ITEM_BAG_NUM*(mCurPage-1);
        PlayerCharacterIdType charid = CPlayer::getInstance().getActiveClan()->getMainGenrealID();
        //同界面移动位置
        if ( pReceInfo->group == ICON_GROUP_CLAN_BAG )
        {
            //相同位置
            if ( sendIndex == recvIndex )
                return;
            //拖到没有解封的位置
            if ( CItemManager::getInstance().getClanBagSize() < recvIndex )
                return;
            sendBagChangePos(sendIndex, recvIndex, ITEM_SITE_TYPE_CLAN, charid);
        }
        //与角色背包界面交互
        else if ( pReceInfo->group == ICON_GROUP_CHARACTER_BAG )
        {
            sendBagChangePos(sendIndex, recvIndex, ITEM_SITE_TYPE_CHARACTER_BAG, charid);
        }
        //与装备界面交互
        else if ( pReceInfo->group == ICON_GROUP_CHARACTER_EQUIP )
        {
            PlayerItem* pItem = CItemManager::getInstance().findItem(pSendInfo->dbID, ITEM_SITE_TYPE_CLAN, charid);
            DYNAMIC_ASSERT(pItem);
            if (pItem->getItemType() != ITEM_TYPE_EQUIP)
                return;
            if ( pItem->getItemEquipSlotType() != pReceInfo->index )
                return;
            sendBagChangePos(sendIndex, recvIndex, ITEM_SITE_TYPE_CHARACTER_EQUIP, charid);
        }
    }
}