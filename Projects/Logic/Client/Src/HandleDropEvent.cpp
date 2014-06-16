//********************************************************************************************************************
#include "stdafx.h"
#include "HandleDropEvent.h"
#include "ClientMain.h"
#include "UIClanInfo.h"
#include "ItemPacketProcesser.h"
#include "CItemManager.h"
#include "UIYesNoMsgBox.h"
//********************************************************************************************************************
namespace MG
{
    void HandleDropEvent::setEvent()
    {
        ClientMain::getInstance().getPointer()->setDropEvent(handleDropEvent);   
    }
	//------------------------------------------------------------------------------------------------
	void HandleDropEvent::onDropItem(void* arg)
	{
		
		IconInfo& info = ((HandleDropEvent*)arg)->mDropItemInfo;
		if(info.dbID > 0)
		{
			IdType charid = UIClanInfo::getInstance().getCurGenrealId();
			
			switch (info.group)
			{
			case ICON_GROUP_CHARACTER_BAG:
				ItemPacketProcesser::getInstance().sendDelItem(ITEM_SITE_TYPE_CHARACTER_BAG, info.dbID, charid);
				break;
			case ICON_GROUP_CHARACTER_EQUIP:
				ItemPacketProcesser::getInstance().sendDelItem(ITEM_SITE_TYPE_CHARACTER_EQUIP,info.dbID, charid);
				break;
			case ICON_GROUP_CLAN_BAG:
				ItemPacketProcesser::getInstance().sendDelItem(ITEM_SITE_TYPE_CLAN, info.dbID, 0);
				break;
			}
			info.clear();
		}
		
	}
	//------------------------------------------------------------------------------------------------
	void HandleDropEvent::onCancelDropItem(void* arg)
	{
		HandleDropEvent::getInstance().mDropItemInfo.clear();
	}

    //------------------------------------------------------------------------------------------------
    void HandleDropEvent::handleDropEvent( void* pointer )
    {
        IPointer* pPointer = (IPointer*)pointer;
        IAny* pAny = pPointer->getAnyData();
        DYNAMIC_ASSERT(pAny);
        IconInfo* pIconInfo = pAny->castType<IconInfo>();
        DYNAMIC_ASSERT(pIconInfo);
		// ��ֵ���캯��ֻ��ֵ�˲���
		HandleDropEvent::getInstance().mDropItemInfo = (*pIconInfo);
		HandleDropEvent::getInstance().mDropItemInfo.type = pIconInfo->type;
		HandleDropEvent::getInstance().mDropItemInfo.group = pIconInfo->group;
		HandleDropEvent::getInstance().mDropItemInfo.index = pIconInfo->index;
		//IconInfo *temp = HandleDropEvent::getInstance().mDropItemInfo;

		//��ɫ���ϵ�Ʒ�ʣ�����ʱ���赯��ȷ�Ͻ���
		PlayerItem* pItem = CItemManager::getInstance().findItem(pIconInfo->dbID);
		DYNAMIC_ASSERT(pItem);
		const ItemInfo* iteminfo = pItem->getItemInfo();
		DYNAMIC_ASSERT(iteminfo);
		ITEM_RANK rank = iteminfo->getItemBaseRank();
		if (rank >= ITEM_RANK_GREEN )
		{
			UIYesNoMsgBox::getInstance().showHint(L"������Ʒ",L"ȷ��Ҫ������ǰ��Ʒ",(void*)(&HandleDropEvent::getInstance()),onDropItem,(void*)(&HandleDropEvent::getInstance()),onCancelDropItem);
		}
		else
			HandleDropEvent::getInstance().onDropItem((void*)(&HandleDropEvent::getInstance()));

    }
}