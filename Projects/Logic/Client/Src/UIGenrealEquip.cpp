//***************************************************************************************************
#include "stdafx.h"
#include "UIGenrealEquip.h"
#include "CPlayerCharacter.h"
#include "ClientMain.h"
#include "CItemManager.h"
#include "GenrealEquip.h"
#include "GenrealItem.h"
#include "PlayerItem.h"
#include "ItemPacketProcesser.h"
//***************************************************************************************************
namespace MG
{
    UIGenrealEquip::UIGenrealEquip()
        :mImage(NULL)
        ,mText(NULL)
        ,mCharid(0)
    {

    }
    //---------------------------------------------------------------------------------
    UIGenrealEquip::~UIGenrealEquip()
    {

    }
    //---------------------------------------------------------------------------------
    void UIGenrealEquip::setEvent()
    {
        IIcon* pIcon = NULL;
        Char8 tempStr[20] = "";
        for (Int i=1; i<=CHAR_EQUIP_NUM; i++)
        {
            sprintf_s(tempStr, sizeof(tempStr), "Icon_equip_%d", i);
            pIcon = getLayout()->getIcon(tempStr);
            assert(pIcon);
            pIcon->setEventStartDrag(onStartDrag);
            pIcon->setEventDropResult(onEndDrag);
            pIcon->setRequestDragWidgetInfo(onGetDragInfo);

            IconInfo info;
            info.group = ICON_GROUP_CHARACTER_EQUIP;
            info.type = ICON_TYPE_ITEM;
            info.index = i;
            pIcon->getWidget()->setUserData(info);
        }

        for (Int i=1; i<=CHAR_ITEM_NUM; i++)
        {
            sprintf_s(tempStr, sizeof(tempStr), "icon_item_%d", i);
            pIcon = getLayout()->getIcon(tempStr);
            assert(pIcon);
            pIcon->setEventStartDrag(onStartDrag);
            pIcon->setEventDropResult(onEndDrag); 
            pIcon->setRequestDragWidgetInfo(onGetDragInfo);

            IconInfo info;
            info.index = i;
            info.type = ICON_TYPE_ITEM;
            info.group = ICON_GROUP_CHARACTER_BAG;
            pIcon->getWidget()->setUserData(info);    
        }
    }
    //---------------------------------------------------------------------------------
    void UIGenrealEquip::onStartDrag( void* widget1, Bool& res )
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
    //---------------------------------------------------------------------------------
    void UIGenrealEquip::onEndDrag( void* widget1, void* widget2, Bool res )
    {
        //只写背包
        IIcon* pIconsend = (IIcon*)widget1; 
        IIcon* pIconrecv = (IIcon*)widget2;
        assert(pIconsend);

        IconInfo* pSendInfo = NULL;
        IconInfo* pRecvInfo = NULL;
        IAny* anyData = pIconsend->getWidget()->getUserData();
        pSendInfo =  anyData->castType<IconInfo>();
        if ( pIconrecv )
        {
            anyData = pIconrecv->getWidget()->getUserData();
            pRecvInfo =  anyData->castType<IconInfo>();
        }

        if ( pSendInfo->group == ICON_GROUP_CHARACTER_BAG )
        {
            //处理背包事件
            UIGenrealEquip::getInstance().onHandlBag(pSendInfo, pRecvInfo, res);
        }
        else
        {
            //处理装备事件
            UIGenrealEquip::getInstance().onHandlEquip(pSendInfo, pRecvInfo, res);
        }
    }
    //---------------------------------------------------------------------------------
    void UIGenrealEquip::addItemList()
    {
        GenrealItem* tempGenrealItem = CItemManager::getInstance().getGenrealItem(mCharid);
        PlayerItem* pItem = NULL;
        for (UInt i=1; i<=CHAR_ITEM_NUM; i++)
        {
            pItem = tempGenrealItem->findItem(i);
            if (pItem)
                addItem(pItem);
        }
    }
    //---------------------------------------------------------------------------------
    void UIGenrealEquip::addItem(PlayerItem* pItem)
    {
        Char8 temp[24] = "";
        U32 index = pItem->getItemIndex();
        sprintf_s(temp, 24, "icon_item_%d", index);
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

        ////text
        //if ( pItem->getItemNum() > 1 )
        //{
        //    sprintf_s(temp, 24, "text%d", index);
        //    IWidget* pWidget = getLayout()->getWidget(temp);
        //    DYNAMIC_ASSERT(pWidget);
        //    Str16 tempNum;
        //    tempNum +=  pItem->getItemNum();
        //    pWidget->setCaption(tempNum);
        //}
    }
    //---------------------------------------------------------------------------------
    void UIGenrealEquip::deleteItem(U32 index)
    {
        Char8 temp[24] = "";
        sprintf_s(temp, 24, "icon_item_%d", index);
        IIcon* pIcon = getLayout()->getIcon( temp );
        if (pIcon)
        {
            IconInfo*  pIconInfo = pIcon->getWidget()->getUserData()->castType<IconInfo>();
            pIcon->setTexture("", "", "");
            pIconInfo->clear();
            pIcon->getWidget()->setUserData(*pIconInfo);
        }
        /*sprintf_s(temp, 24, "text%d", index);
        IWidget* pWidget = getLayout()->getWidget( temp );
        if ( pWidget )
            pWidget->setCaption(L"");*/
    }
    //---------------------------------------------------------------------------------
    void UIGenrealEquip::updateItem(U32 index, U32 num)
    {
        //Char8 temp[24] = "";
        //sprintf_s(temp, 24, "text%d", index);
        //IWidget* pWidget = getLayout()->getWidget( temp );
        //if (pWidget)
        //{
        //    Str16 tempNum = L"";
        //    if ( num > 1 )
        //    {  
        //        tempNum += num;
        //        pWidget->setCaption(tempNum); 
        //    }
        //    else
        //        pWidget->setCaption(tempNum);
        //}
    }
    //---------------------------------------------------------------------------------
    void UIGenrealEquip::addEquipList()
    {
        GenrealEquip* tempGenrealEquip = CItemManager::getInstance().getGenrealEquip(mCharid);
        PlayerItem* pItem = NULL;
        for (UInt i=1; i<=CHAR_EQUIP_NUM; i++)
        {
            pItem = tempGenrealEquip->findItem((ITEM_EQUIP_SLOT_TYPE)i);
            if (pItem)
                addEquip(pItem);
        }
    }
    //---------------------------------------------------------------------------------
    void UIGenrealEquip::addEquip(PlayerItem* pItem)
    {
        Char8 temp[24] = "";
        U32 index = pItem->getItemIndex();
        sprintf_s(temp, 24, "Icon_equip_%d", index);
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
    }
    //---------------------------------------------------------------------------------
    void UIGenrealEquip::deleteEquip(U32 index)
    {
        Char8 temp[24] = "";
        sprintf_s(temp, 24, "Icon_equip_%d", index);
        IIcon* pIcon = getLayout()->getIcon( temp );
        if (pIcon)
        {
            IconInfo*  pIconInfo = pIcon->getWidget()->getUserData()->castType<IconInfo>();
            pIcon->setTexture("", "", "");
            pIconInfo->clear();
            pIcon->getWidget()->setUserData(*pIconInfo);
        }
    }
    //---------------------------------------------------------------------------------
    void UIGenrealEquip::onHandlBag( IconInfo* pSend, IconInfo* pRece, Bool ishave )
    {
        //扔道具
        if ( pRece == NULL )  
        {
            characterBagDropItem(pSend->dbID);  
            return;
        }
        if ( 
                pRece->group == ICON_GROUP_CHARACTER_BAG  ||
                pRece->group == ICON_GROUP_CHARACTER_EQUIP ||
                pRece->group == ICON_GROUP_CLAN_BAG
                )
        {
            characterBagChangePos(pSend, pRece);
        }
    }
    //---------------------------------------------------------------------------------
    void UIGenrealEquip::onHandlEquip( IconInfo* pSend, IconInfo* pRece, Bool ishave )
    {
        //扔道具
        if ( pRece == NULL )  
        {
            characterEquipDropItem(pSend->dbID);  
            return;
        }
        //交换
        if ( 
            pRece->group == ICON_GROUP_CHARACTER_BAG  ||
            pRece->group == ICON_GROUP_CLAN_BAG
            )
        {
            characterEquipChangePos(pSend, pRece);
        }
    }
    //---------------------------------------------------------------------------------
    void UIGenrealEquip::onGetDragInfo( void* widget1, void*& widget2, CoordI& rect, Byte& isImage )
    {
        assert(widget1);
        IIcon* pIcon = (IIcon*)(widget1);
        UIGenrealEquip::getInstance().getDragInfo(pIcon, widget2, rect, isImage);
    }
    //---------------------------------------------------------------------------------
    void UIGenrealEquip::getDragInfo( IIcon* pSend, void*& widget2, CoordI& rect, Byte& isImage )
    {
        IconInfo* pInfo = pSend->getWidget()->getUserData()->castType<IconInfo>();
        assert(pInfo);
        
        CoordI temp = pSend->getWidget()->getCoord();
        rect = temp;
        /*if (mImage != NULL)
            ;*/
        mImage = ClientMain::getInstance().getGui()->getImage(rect, pInfo->resouceName, pInfo->groupName, pInfo->itemName);
        widget2 = (void*)( mImage );

        isImage = ICON_DRAG_TYPE_IMAGE;
    }
    //----------------------------------------------------------------------------------
    void UIGenrealEquip::sendDropItem( IdType ID )
    {
        ItemPacketProcesser::getInstance().sendDelItem(ITEM_SITE_TYPE_CLAN, ID, 0);
    }
    //----------------------------------------------------------------------------------
    void UIGenrealEquip::sendBagChangePos( U32 sendIndex, U32 recvIndex,ITEM_SITE_TYPE sendType,ITEM_SITE_TYPE recvType, PlayerCharacterIdType charid )
    {
        ItemPacketProcesser::getInstance().sendChangePos(sendIndex, recvIndex, sendType, recvType, charid);
    }
    //----------------------------------------------------------------------------------
    void UIGenrealEquip::characterBagDropItem( IdType itemdbid )
    {
        sendDropItem(itemdbid);
    }
    //----------------------------------------------------------------------------------
    void UIGenrealEquip::characterEquipDropItem( IdType itemdbid )
    {
        sendDropItem(itemdbid);
    }
    //----------------------------------------------------------------------------------
    void UIGenrealEquip::characterBagChangePos( IconInfo* pSendInfo, IconInfo* pReceInfo )
    {
        U32 sendIndex = pSendInfo->index;
        U32 recvIndex = pReceInfo->index;
        //同界面移动位置
        if ( pReceInfo->group == ICON_GROUP_CHARACTER_BAG )
        {
            //相同位置
            if ( sendIndex == recvIndex )
                return;
            sendBagChangePos(sendIndex, recvIndex, ITEM_SITE_TYPE_CHARACTER_BAG, ITEM_SITE_TYPE_CHARACTER_BAG, mCharid);
        }
        //与氏族背包界面交互
        else if ( pReceInfo->group == ICON_GROUP_CLAN_BAG )
        {
            //拖到没有解封的位置
            if ( CItemManager::getInstance().getClanBagSize() < recvIndex )
                return;
            sendBagChangePos(sendIndex, recvIndex,ITEM_SITE_TYPE_CHARACTER_BAG, ITEM_SITE_TYPE_CLAN, mCharid);
            return;
        }
        //与装备界面交互
        else if ( pReceInfo->group == ICON_GROUP_CHARACTER_EQUIP )
        {
            PlayerItem* pItem = CItemManager::getInstance().findItem(pSendInfo->dbID, ITEM_SITE_TYPE_CHARACTER_BAG, mCharid);
            DYNAMIC_ASSERT(pItem);
            if (pItem->getItemType() != ITEM_TYPE_EQUIP)
                return;
            if ( pItem->getItemEquipSlotType() != pReceInfo->index )
                return;
            sendBagChangePos(sendIndex, recvIndex, ITEM_SITE_TYPE_CHARACTER_BAG, ITEM_SITE_TYPE_CHARACTER_EQUIP, mCharid);
        }
    }
    //----------------------------------------------------------------------------------
    void UIGenrealEquip::characterEquipChangePos( IconInfo* pSendInfo, IconInfo* pReceInfo )
    {
        U32 sendIndex = pSendInfo->index;
        U32 recvIndex = pReceInfo->index;

        if ( pReceInfo->group == ICON_GROUP_CHARACTER_BAG )
        {
            if ( pReceInfo->dbID )
            {
                PlayerItem* pItem = CItemManager::getInstance().findItem(pReceInfo->dbID, ITEM_SITE_TYPE_CHARACTER_BAG, mCharid);
                DYNAMIC_ASSERT(pItem);
                if (pItem->getItemType() != ITEM_TYPE_EQUIP)
                    return;
                if ( pItem->getItemEquipSlotType() != pSendInfo->index )
                    return;
            }
            sendBagChangePos(sendIndex, recvIndex, ITEM_SITE_TYPE_CHARACTER_EQUIP,ITEM_SITE_TYPE_CHARACTER_BAG, mCharid);
        }
        //与氏族背包界面交互
        else if ( pReceInfo->group == ICON_GROUP_CLAN_BAG )
        {
            if ( pReceInfo->dbID )
            {
                PlayerItem* pItem = CItemManager::getInstance().findItem(pReceInfo->dbID, ITEM_SITE_TYPE_CLAN, mCharid);
                DYNAMIC_ASSERT(pItem);
                if (pItem->getItemType() != ITEM_TYPE_EQUIP)
                    return;
                if ( pItem->getItemEquipSlotType() != pSendInfo->index )
                    return;
            }
            sendBagChangePos(sendIndex, recvIndex, ITEM_SITE_TYPE_CHARACTER_EQUIP,ITEM_SITE_TYPE_CLAN, mCharid);
        }
    }

}