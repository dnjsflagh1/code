//*****************************************************************************************************
#include "stdafx.h"
#include "UIItemTips.h"
#include "ItemTemplate.h"
#include "ItemEquipTemplate.h"
#include "ItemUseTemplate.h"
#include "ItemOtherTemplate.h"
#include "CGameMessageConfig.h"
#include "CharacterJudgeTemplate.h"
#include "ClientMain.h"
#include "PlayerItem.h"
#include "AttributeList.h"
#include "AttributeAppend.h"
#include "ItemClanListCsv.h"
//*****************************************************************************************************
namespace MG
{
    UIItemTips::UIItemTips()
        :mItemEquipInfo(NULL)
        ,mItemOtherInfo(NULL)
        ,mItemUseInfo(NULL)
        ,mItemRecord(NULL)
		,mItemClanInfo(NULL)
    {

    }
    //-----------------------------------------------------------------------------------------
    UIItemTips::~UIItemTips()
    {
        mItemEquipInfo	= NULL;
        mItemOtherInfo	= NULL;
        mItemUseInfo	= NULL;
        mItemRecord		= NULL;
		mItemClanInfo	= NULL;
    }
    //-----------------------------------------------------------------------------------------
    void UIItemTips::openItemTips( const PlayerItem* pItem, CoordI coord, ITEM_TIPS_TYPE showType)
    {
        DYNAMIC_ASSERT(pItem);

        const ItemInfo* tempItemInfo = pItem->getItemInfo();
        switch (tempItemInfo->ItemType)
        {
		case ITEM_TYPE_USE_CLAN:
			mItemClanInfo = ItemClanListCsv::getInstance().getInfoById(tempItemInfo->ItemListId);
			break;
        case ITEM_TYPE_EQUIP_GENERAL:
            mItemEquipInfo = ItemEquipTemplate::getInstance().getItemEquipInfo(tempItemInfo->ItemListId);
        	break;
		case ITEM_TYPE_USE_GENERAL:
			mItemUseInfo = ItemUseTemplate::getInstance().getItemUseInfo(tempItemInfo->ItemListId);
			break;
        case ITEM_TYPE_OTHER:
            mItemOtherInfo = ItemOtherTemplate::getInstance().getItemOtherInfo(tempItemInfo->ItemListId);
            break;
        default:
            DYNAMIC_ASSERT(0);
            break;
        }

        mItemRecord = pItem->getItemRecord();

        setItemTipsInfo(coord, showType);

        openGui();
    }
    //-----------------------------------------------------------------------------------------
    void UIItemTips::openItemTips( const ItemInfo* pItemInfo, CoordI coord, ITEM_TIPS_TYPE showType)
    {
        DYNAMIC_ASSERT(pItemInfo);

        switch (pItemInfo->ItemType)
        {
        case ITEM_TYPE_EQUIP_GENERAL:
            mItemEquipInfo = ItemEquipTemplate::getInstance().getItemEquipInfo(pItemInfo->ItemListId);
            break;
        case ITEM_TYPE_OTHER:
            mItemOtherInfo = ItemOtherTemplate::getInstance().getItemOtherInfo(pItemInfo->ItemListId);
            break;
        case ITEM_TYPE_USE_GENERAL:
            mItemUseInfo = ItemUseTemplate::getInstance().getItemUseInfo(pItemInfo->ItemListId);
            break;
		case ITEM_TYPE_USE_CLAN:
			mItemClanInfo = ItemClanListCsv::getInstance().getInfoById(pItemInfo->ItemListId);
			break;
        default:
            DYNAMIC_ASSERT(0);
            break;
        }

        setItemTipsInfo(coord, showType);

        openGui();
    }
    //-----------------------------------------------------------------------------------------
    void UIItemTips::openItemTips( const ItemRecord* pItemRecord, CoordI coord, ITEM_TIPS_TYPE showType)
    {
        DYNAMIC_ASSERT(pItemRecord);

        mItemRecord = pItemRecord;
        const ItemInfo* tempItemInfo = ItemTemplate::getInstance().getItemInfo(pItemRecord->itemTempID);
        switch (tempItemInfo->ItemType)
        {
        case ITEM_TYPE_EQUIP_GENERAL:
            mItemEquipInfo = ItemEquipTemplate::getInstance().getItemEquipInfo(tempItemInfo->ItemListId);
            break;
        case ITEM_TYPE_OTHER:
            mItemOtherInfo = ItemOtherTemplate::getInstance().getItemOtherInfo(tempItemInfo->ItemListId);
            break;
        case ITEM_TYPE_USE_GENERAL:
            mItemUseInfo = ItemUseTemplate::getInstance().getItemUseInfo(tempItemInfo->ItemListId);
            break;
		case ITEM_TYPE_USE_CLAN:
			mItemClanInfo = ItemClanListCsv::getInstance().getInfoById(tempItemInfo->ItemListId);
			break;
        default:
            DYNAMIC_ASSERT(0);
            break;
        }

        setItemTipsInfo(coord, showType);

        openGui();
    }
    //-----------------------------------------------------------------------------------------
    MG::Bool UIItemTips::closeGui()
    {
        mItemEquipInfo = NULL;
        mItemOtherInfo = NULL;
        mItemUseInfo = NULL;
        mItemRecord = NULL;

        return UIObject::closeGui();
    }
    //-----------------------------------------------------------------------------------------
	#define  item_tips_space 5
    //-----------------------------------------------------------------------------------------
    void UIItemTips::setItemTipsInfo(CoordI coord, ITEM_TIPS_TYPE showType)
    {
        U32 height = item_tips_space;
        //名字，品级
        setItemName(height);
        //武器，武器位置
        setItemEquipType(height);
        //简介
        setItemIntro(height);
        //耐久
        setItemDurable(height);
        //消失
        setItemDisappear(height);
        //限制
        setItemLimit(height);
        //属性加成
        setItemAttr(height);
        //套装
        setItemSuit(height);
        //支持类别
        setItemSupport(height);
        //堆叠数，卖出的游戏币
        setItemMoney(height, showType);
        //设置tips的位置
        setTipsCoord(height, coord);
    }
    //-----------------------------------------------------------------------------------------
    void UIItemTips::setItemName( U32& height )
    {
        Str16 tempName;
        U32 strengthenLvl = 0;
        U32 rank = 0;
        Color tempColor(1.f, 1.f, 1.f, 1.f);
        //获取属性
        if ( mItemEquipInfo )
        {
            tempName = mItemEquipInfo->Name;
            if ( mItemRecord )
                strengthenLvl = mItemRecord->curStrengthenLv;
            rank = mItemEquipInfo->Rank;
        }
        else if ( mItemUseInfo )
        {
            tempName = mItemUseInfo->Name;
            rank = mItemUseInfo->Rank;
        }
        else if ( mItemOtherInfo )
        {
            tempName = mItemOtherInfo->Name;
            rank = mItemOtherInfo->Rank;
        }
		else if(mItemClanInfo)
		{
			tempName = mItemClanInfo->Name;
			rank = mItemClanInfo->Rank;
		}
        else
            DYNAMIC_ASSERT(0);
        //根据评级获得颜色
        switch (rank)
        {
        case ITEM_RANK_WHITE:
            tempColor = /*Color(1.f, 0.f, 0.f,1.f);*/COLOR_WHITE;
        	break;
        case ITEM_RANK_GREEN:
            tempColor = /*Color(0.f, 1.f, 0.f, 1.f)*/COLOR_GREEN;
            break;
        case ITEM_RANK_BLUE:
            tempColor = /*Color(0.f, 0.f, 1.f, 0.f);*/COLOR_BLUE;
            break;
        case ITEM_RANK_PURPLE:
            tempColor = /*Color(175/255.f, 0.f, 1.f, 1.f);*/COLOR_PURPLE;
            break;
        default:
            DYNAMIC_ASSERT(0);
            break;
        }

		IText* preText = getLayout()->getText("itemname");
		preText->getWidget()->setCaption(L"");

		preText = getLayout()->getText("itemgrade");
		preText->getWidget()->setCaption(L"");

        //计算名字的长度
        U32 length = ClientMain::getInstance().getGui()->getLengthStr(tempName);
        U32 fontHeight = ClientMain::getInstance().getGui()->getHeightChar();
        //设置属性和控件的大小，位置
        IText* pText = getLayout()->getText("itemname");
        pText->getWidget()->setCaption(tempName);
        pText->setTextColour(tempColor);
        CoordI tempCoord = pText->getWidget()->getCoord();
        tempCoord.left = item_tips_space;
        tempCoord.top = height;
        tempCoord.width = length;
        tempCoord.height = fontHeight;
        pText->getWidget()->setCoord(tempCoord);
        //强化等级
        IText* pStrengthenText = getLayout()->getText("itemgrade");
        pStrengthenText->getWidget()->setCaption(L"");
        if ( strengthenLvl > 0 )
        {
            Str16 tempLvl = L"(";
            tempLvl += strengthenLvl;
            tempLvl += L")";

            length = ClientMain::getInstance().getGui()->getLengthStr(tempName);

            CoordI tempStrengthenCoord = pStrengthenText->getWidget()->getCoord();
            tempStrengthenCoord.left = tempCoord.left + tempCoord.width;
            tempStrengthenCoord.top = height;
            tempStrengthenCoord.width = length;
            tempStrengthenCoord.height = fontHeight;

            pStrengthenText->getWidget()->setCoord(tempStrengthenCoord);
            pStrengthenText->getWidget()->setCaption(tempLvl);
        }
        //更新高度
        height += tempCoord.height;
    }
    //-----------------------------------------------------------------------------------------
    void UIItemTips::setItemEquipType( U32& height )
    {
		/*
        IWidget* pWidget = getLayout()->getWidget("itemtype");
        pWidget->setCaption(L"");
        CoordI tempCoord = pWidget->getCoord();
        tempCoord.top = height;
        tempCoord.left = item_tips_space;

        IWidget* pPosWidget = getLayout()->getWidget("itempos");
        pPosWidget->setCaption(L"");
        
        //设置属性
        if ( mItemEquipInfo )
        {
            //类型
            Char16 msg[32] = L"";
            swprintf_s(msg, 32, L"equipclass%d", mItemEquipInfo->Class);
            pWidget->setCaption( CGameMessageConfig::getInstance().getStr(L"itemtemplate", msg, msg) ) ;
            pWidget->setCoord(tempCoord);
            //装备位
            swprintf_s( msg, 32, L"equipSlot%d", mItemEquipInfo->EquipSlotType);
            
            pPosWidget->setCaption( CGameMessageConfig::getInstance().getStr(L"itemtemplate", msg, msg) );
            CoordI tempSlotCoord = pPosWidget->getCoord();
            tempSlotCoord.top = tempCoord.top;
            pPosWidget->setCoord(tempSlotCoord);
        }
        else if ( mItemOtherInfo )
        {
            //类型
            Char16 msg[32] = L"";
            swprintf_s(msg, 32, L"otherclass%d", mItemOtherInfo->Class);
            pWidget->setCaption( CGameMessageConfig::getInstance().getStr(L"itemtemplate", msg, msg) ) ;
            pWidget->setCoord(tempCoord);
        }
        else if ( mItemUseInfo )
        {
            //类型
            Char16 msg[32] = L"";
            swprintf_s(msg, 32, L"useclass%d", mItemUseInfo->Class);
            pWidget->setCaption( CGameMessageConfig::getInstance().getStr(L"itemtemplate", msg, msg) ) ;
            pWidget->setCoord(tempCoord);
        }
		else if ( mItemClanInfo )
		{
			//类型
			Char16 msg[32] = L"";
			swprintf_s(msg, 32, L"useclass%d", mItemClanInfo->Class);
			pWidget->setCaption( CGameMessageConfig::getInstance().getStr(L"itemtemplate", msg, msg) ) ;
			pWidget->setCoord(tempCoord);
		}
		else
		{
			DYNAMIC_ASSERT(0);
		}

        //更新高度
        height += tempCoord.height;

		*/
    }
    //-----------------------------------------------------------------------------------------
    void UIItemTips::setItemIntro( U32& height )
    {
        //获取信息
        Str16 tempMsg;
        if ( mItemUseInfo )
        {
            tempMsg = mItemUseInfo->Text;
        }
        else if ( mItemEquipInfo )
        {
            tempMsg = mItemEquipInfo->Text;
        }
        else if ( mItemOtherInfo )
        {
            tempMsg = mItemOtherInfo->Text;
        }
		else if(mItemClanInfo)
		{
			tempMsg = mItemClanInfo->Text;
		}
        else
		{
            DYNAMIC_ASSERT(0);
		}
        //MyGui内部排版
        IWidget* pWidget = getLayout()->getWidget("itemintro");
        pWidget->setCaption(L"");
        CoordI tempCoord = pWidget->getCoord();
        tempCoord.left = item_tips_space;
        tempCoord.top = height;
        tempCoord.height = ClientMain::getInstance().getGui()->getHeightStrAddBreak(tempMsg, tempCoord.width);
        pWidget->setCoord(tempCoord);

        pWidget->setCaption(tempMsg);
        //更新高度
        height += tempCoord.height;
    }
    //-----------------------------------------------------------------------------------------
    void UIItemTips::setItemBind( U32& height )
    {
        IWidget* pWidget = getLayout()->getWidget("itembind");
        pWidget->setCaption(L"");
        /*U32 tempBind = 0;
        Str16 tempMsg;
        if ( mItemRecord->bindType )*/
    }
    //-----------------------------------------------------------------------------------------
    void UIItemTips::setItemDurable( U32& height )
    {
        Color tempColor;
		IWidget* pWidget = getLayout()->getWidget("itemdurable");
		pWidget->setCaption(L"");
        if ( mItemEquipInfo &&  mItemRecord )
        {
            if ( mItemRecord->curDurable*1.f / mItemEquipInfo->MaxEquipDurable > 0.4 )
                tempColor = Color(0.f, 1.f, 0.f, 1.f);
            else if ( mItemRecord->curDurable*1.f / mItemEquipInfo->MaxEquipDurable > 0.2 )
                tempColor = Color(1.f, 135.f/255.f, 0.f, 1.f);
            else
                tempColor = Color(1.f, 0.f, 0.f, 1.f);
			pWidget->getText()->setTextColour(tempColor);

            Char16 msg[32] = L"";
            swprintf_s(
                msg, 32,
                CGameMessageConfig::getInstance().getStr(L"itemtemplate", L"Itemdurable", L"Itemdurable").c_str(),
                mItemRecord->curDurable,
                mItemEquipInfo->MaxEquipDurable
                );
            pWidget->setCaption(msg);
            CoordI tempCoord = pWidget->getCoord();
            tempCoord.left = item_tips_space;
            tempCoord.top = height;
            tempCoord.height = ClientMain::getInstance().getGui()->getHeightChar();
            pWidget->setCoord(tempCoord);
            //更新高度
            height += tempCoord.height;
        }
        
    }
    //-----------------------------------------------------------------------------------------
    void UIItemTips::setItemDisappear( U32& height )
    {
        U32 tempDisapper = 0;
        if ( mItemUseInfo )
        {
            tempDisapper = mItemUseInfo->DisappearType;
        }
        else if ( mItemEquipInfo )
        {
            tempDisapper = mItemEquipInfo->DisappearType;
        }
        else if ( mItemOtherInfo )
        {
            tempDisapper = mItemOtherInfo->DisappearType;
        }
		else if ( mItemClanInfo )
		{
			tempDisapper = mItemClanInfo->DisappearType;
		}
        else
            DYNAMIC_ASSERT(0);

		IWidget* pWidget = getLayout()->getWidget("itemdisappear");
		pWidget->setCaption(L"");
		if(tempDisapper > 0)
		{
			Char16 msg[32] = L"";
			swprintf_s( msg, 32, L"itemdiappear%d", tempDisapper);
			pWidget->setCaption(CGameMessageConfig::getInstance().getStr(L"itemtemplate", msg, msg));   
			CoordI tempCoord = pWidget->getCoord();
			tempCoord.left = item_tips_space;
			tempCoord.top = height;
			tempCoord.height = ClientMain::getInstance().getGui()->getHeightChar();
			pWidget->setCoord(tempCoord);
			//更新高度
			height += tempCoord.height;
		}
    }
    //-----------------------------------------------------------------------------------------
    void UIItemTips::setItemLimit( U32& height )
    {
        IWidget* pWidget = getLayout()->getWidget("itemlimit");
        pWidget->setCaption(L"");
        //读表。
        if ( mItemEquipInfo  &&  mItemEquipInfo->CharacterJudgeid )
        {
            const CharacterJudgeInfo* tempInfo = CharacterJudgeTemplate::getInstance().getCharacterJudgeInfo(mItemEquipInfo->CharacterJudgeid);
            if ( tempInfo )
            {
                Str16 msg;  
                U32 ncount = 0;
                CGameMessageConfig::getInstance().setSection(L"CharacterJudgeTemplate");
                //性别限制
                if ( tempInfo->GenderType )
                {
                    ++ncount;
                    msg += CGameMessageConfig::getInstance().getStr(L"gendertype", L"gendertype");
                    if ( tempInfo->GenderType & 1 )
                    {    
                        msg += CGameMessageConfig::getInstance().getStr(L"gendertype1", L"gendertype1");
                        msg += L" ";
                    }
                    if ( tempInfo->GenderType & 2 )
                    {    
                        msg += CGameMessageConfig::getInstance().getStr(L"gendertype2", L"gendertype2");
                        msg += L" ";
                    }
                    if ( tempInfo->GenderType & 4 )
                    {    
                        msg += CGameMessageConfig::getInstance().getStr(L"gendertype3", L"gendertype3");
                        msg += L" "; 
                    }
                }
                //职业限制
                /*if (tempInfo->FormulaType)
                {
                    if ( ncount > 0 )
                        msg += L"\n";
                    ++ncount;
                    msg += CGameMessageConfig::getInstance().getStr(L"formulatype", L"formulatype");
                    if ( tempInfo->GenderType & 1 )
                    {    
                        msg += CGameMessageConfig::getInstance().getStr(L"formulatype1", L"formulatype1");
                        msg += L" ";
                    }
                    if ( tempInfo->GenderType & 2 )
                    {    
                        msg += CGameMessageConfig::getInstance().getStr(L"formulatype2", L"formulatype2");
                        msg += L" ";
                    }
                    if ( tempInfo->GenderType & 4 )
                    {    
                        msg += CGameMessageConfig::getInstance().getStr(L"formulatype3", L"formulatype3");
                        msg += L" "; 
                    }
                    if ( tempInfo->GenderType & 8 )
                    {    
                        msg += CGameMessageConfig::getInstance().getStr(L"formulatype4", L"formulatype4");
                        msg += L" "; 
                    }
                }*/
                //获得控件的高度
                U32 tempH = ncount * ClientMain::getInstance().getGui()->getHeightChar();
                //设置属性
                
                CoordI tempCoord = pWidget->getCoord();
                tempCoord.left = item_tips_space;
                tempCoord.top = height;
                tempCoord.height = tempH;
                pWidget->setCoord(tempCoord);
                pWidget->setCaption(msg); 
                //更新高度
                height += tempH;
            }
        }
    }
    //-----------------------------------------------------------------------------------------
    void UIItemTips::setItemAttr( U32& height )
    {
		//
		IText* pText = getLayout()->getText("itemattr");
		pText->getWidget()->setCaption(L"");

        Str16 tempMsg;
        std::map<U32, Flt> tempAttrMap;
        std::map<U32, Flt> tempAttrStrengthenMap;
        if ( mItemEquipInfo )
        {
            if ( mItemEquipInfo->AbilityAppendId1 )
            {
                //先找到基本属性。
                const AttributeAppendInfo* tempAppendAttr = AttributeAppend::getInstance().getAttributeAppendInfo(mItemEquipInfo->AbilityAppendId1);
                if ( tempAppendAttr )
                {
                    for (Int i=0; i<APPENDATTR_NUM; i++)
                    {
                        if ( tempAppendAttr->AppendAttrList[i].id )
						{   
							if ( tempAppendAttr->AppendType == APPEND_TYPE_REAL )
								tempAttrMap[tempAppendAttr->AppendAttrList[i].id] += tempAppendAttr->AppendAttrList[i].value;
							else
								tempAttrMap[tempAppendAttr->AppendAttrList[i].id] += 
								tempAppendAttr->AppendAttrList[i].value*mItemEquipInfo->Score*PERMILLAGE_VALUE;
						}
                        else
                            break;
                    }
                }
                //实例属性
                if (mItemRecord)
                {
                    //附加属性
                    if ( mItemRecord->randAppendID )
                    {
                        tempAppendAttr = AttributeAppend::getInstance().getAttributeAppendInfo(mItemRecord->randAppendID);
                        if ( tempAppendAttr )
                        {
                            for (Int i=0; i<APPENDATTR_NUM; i++)
                            {
								if ( tempAppendAttr->AppendAttrList[i].id )
								{   
									if ( tempAppendAttr->AppendType == APPEND_TYPE_REAL )
										tempAttrMap[tempAppendAttr->AppendAttrList[i].id] += tempAppendAttr->AppendAttrList[i].value;
									else
										tempAttrMap[tempAppendAttr->AppendAttrList[i].id] += 
										tempAppendAttr->AppendAttrList[i].value*mItemEquipInfo->Score*PERMILLAGE_VALUE;
								}
								else
									break;
                            }
                        }
                    }
                    //强化属性
                    if ( mItemRecord->curStrengthenLv )
                    {
                        if ( mItemEquipInfo->AbilityAppendId2 )
                        {
                            tempAppendAttr = AttributeAppend::getInstance().getAttributeAppendInfo(mItemEquipInfo->AbilityAppendId2);
                            if ( tempAppendAttr )
                            {
                                for (Int i=0; i<APPENDATTR_NUM; i++)
                                {
                                    if ( tempAppendAttr->AppendAttrList[i].id )
									{   
										if ( tempAppendAttr->AppendType == APPEND_TYPE_REAL )
											tempAttrStrengthenMap[tempAppendAttr->AppendAttrList[i].id] += tempAppendAttr->AppendAttrList[i].value;
										else
											tempAttrStrengthenMap[tempAppendAttr->AppendAttrList[i].id] += 
											tempAppendAttr->AppendAttrList[i].value*mItemRecord->curStrengthenLv*PERMILLAGE_VALUE;
									}
                                    else
                                        break;
                                }
                            }
                            //强化附加属性
                            if ( mItemRecord->strengthenAppendID )
                            {
                                tempAppendAttr = AttributeAppend::getInstance().getAttributeAppendInfo(mItemRecord->strengthenAppendID);
                                if ( tempAppendAttr )
                                {
                                    for (Int i=0; i<APPENDATTR_NUM; i++)
                                    {
										if ( tempAppendAttr->AppendAttrList[i].id )
										{   
											if ( tempAppendAttr->AppendType == APPEND_TYPE_REAL )
												tempAttrStrengthenMap[tempAppendAttr->AppendAttrList[i].id] += tempAppendAttr->AppendAttrList[i].value;
											else
												tempAttrStrengthenMap[tempAppendAttr->AppendAttrList[i].id] += 
												tempAppendAttr->AppendAttrList[i].value*mItemRecord->curStrengthenLv*PERMILLAGE_VALUE;
										}
										else
											break;
                                    }
                                }
                            }
                        }          
                    }
                }
            } 
            tempMsg = L"";
            //设置属性
            Str16 tempStr;
            std::map<U32, Flt>::iterator front1 = tempAttrMap.begin();
            std::map<U32, Flt>::iterator back1 = tempAttrMap.end();
            while (front1 != back1)
            {   
				Int val = (Int)(front1->second);
				if (val != 0)
				{
					MGStrOp::toString(val,tempStr);
					tempMsg += AttributeList::getInstance().getAttrInfo((ATTR_ID)front1->first)->attrChName;
					if (val > 0)
					{
						tempMsg += L" + ";
					}
					tempMsg += tempStr;
					tempMsg += L"\n";
				}
                ++front1;
            }
            std::map<U32, Flt>::iterator front2 = tempAttrStrengthenMap.begin();
            std::map<U32, Flt>::iterator back2 = tempAttrStrengthenMap.end();
            while (front2 != back2)
            {   MGStrOp::toString((Int)(front2->second),tempStr);
                tempMsg += L"\n";
                tempMsg += AttributeList::getInstance().getAttrInfo((ATTR_ID)front2->first)->attrChName;
                tempMsg += tempStr;
                ++front2;
            }  
            U32 tempH = (tempAttrMap.size() + tempAttrStrengthenMap.size() + 1) * pText->getFontHeight();
            CoordI tempCoord = pText->getWidget()->getCoord();
            tempCoord.left = item_tips_space;
            tempCoord.top = height;
            tempCoord.height = tempH;
            pText->getWidget()->setCoord(tempCoord);
            pText->getWidget()->setCaption(tempMsg); 
            //更新高度
            height += tempH;
        }
    }
    //-----------------------------------------------------------------------------------------
    void UIItemTips::setItemSuit( U32& height )
    {
        if ( mItemEquipInfo )
        {
            IWidget* pSuitWidget = getLayout()->getWidget("itemsuit");
            pSuitWidget->setCaption(L"");
        }
    }
    //-----------------------------------------------------------------------------------------
    void UIItemTips::setItemSupport( U32& height )
    {
        IText*  pText = getLayout()->getText("itemsupport");
        pText->getWidget()->setCaption(L"");
        U32 tempSupport = 0;
        Str16 tempMsg = L"";
        if ( mItemUseInfo )
        {
            tempSupport = mItemUseInfo->ForbidType;
        }
        else if ( mItemEquipInfo )
        {
            tempSupport = mItemEquipInfo->ForBidType;
        }
        else if ( mItemOtherInfo )
        {
            tempSupport = mItemOtherInfo->ForBidType;
        }
		else if ( mItemClanInfo )
		{
			tempSupport = mItemClanInfo->ForbidType;
		}
        else
            DYNAMIC_ASSERT(0);

        if ( tempSupport )
        {
            CGameMessageConfig::getInstance().setSection(L"itemtemplate");
            Int ncount = 0;
            if ( tempSupport & ITEM_FORBID_TYPE_GIVEUP )
            {
                ++ncount;
                tempMsg += CGameMessageConfig::getInstance().getStr(L"itemforbid1", L"itemforbid1");
                tempMsg += L"        ";
            }
            if ( tempSupport & ITEM_FORBID_TYPE_SHOP )
            {
                ++ncount;
                tempMsg += CGameMessageConfig::getInstance().getStr(L"itemforbid2", L"itemforbid2");
                tempMsg += L"        ";
            }
            if ( tempSupport & ITEM_FORBID_TYPE_REPAIR )
            {
                ++ncount;
                tempMsg += CGameMessageConfig::getInstance().getStr(L"itemforbid3", L"itemforbid3");
                if ( ncount % 3 == 0 )
                    tempMsg += L"\n";       
                else
                    tempMsg += L"        "; 
            }
            if ( tempSupport & ITEM_FORBID_TYPE_TRADE )
            {
                ++ncount;
                tempMsg += CGameMessageConfig::getInstance().getStr(L"itemforbid4", L"itemforbid4");
                if ( ncount % 3 == 0 )
                    tempMsg += L"\n";       
                else
                    tempMsg += L"        "; 
            }
            if ( tempSupport & ITEM_FORBID_TYPE_CIRCULATE )
            {
                ++ncount;
                tempMsg += CGameMessageConfig::getInstance().getStr(L"itemforbid5", L"itemforbid5");
                if ( ncount % 3 == 0 )  
                    tempMsg += L"\n";       
                else
                    tempMsg += L"        "; 
            }
            if ( tempSupport & ITEM_FORBID_TYPE_ARTIFICE )
            {
                ++ncount;
                tempMsg += CGameMessageConfig::getInstance().getStr(L"itemforbid6", L"itemforbid6");
            }
            
            U32 tempH = pText->getFontHeight();
            if ( ncount > 3 )
                tempH *= 2;
            CoordI tempCoord = pText->getWidget()->getCoord();
            tempCoord.left = item_tips_space;
            tempCoord.top = height;
            tempCoord.height = tempH;
            pText->getWidget()->setCoord(tempCoord);
            pText->getWidget()->setCaption(tempMsg); 
            //更新高度
            height += tempH;
        }
    }
    //-----------------------------------------------------------------------------------------
    void UIItemTips::setItemMoney( U32& height, ITEM_TIPS_TYPE showType)
    {
        IWidget* pPileWidget = getLayout()->getWidget("itempile");
        pPileWidget->setCaption(L"");
        U32 tempPrice = 0;
        CGameMessageConfig::getInstance().setSection(L"itemtemplate");
        if ( mItemUseInfo )
        {
            if (showType == ITEM_TIPS_TYPE_SHOP)
            {
				tempPrice = mItemUseInfo->BuyPrice;
            }
			else
			{
				tempPrice = mItemUseInfo->SellPrice;
			}
			
            if ( mItemRecord )
            {
                Char16 tempPile[32] = L"";
                swprintf_s(
                    tempPile, _countof(tempPile), 
                    CGameMessageConfig::getInstance().getStr(L"itempile", L"itempile").c_str(),
                    mItemRecord->curNum,
                    mItemUseInfo->MaxPlieNum
                    ) ;
                
                Vec2 tempPos = pPileWidget->getPosition();
                tempPos.y = (Flt)height;
                pPileWidget->setPosition(tempPos);
                pPileWidget->setCaption(tempPile);
            }
        }
        else if ( mItemEquipInfo )
        {
			if (showType == ITEM_TIPS_TYPE_SHOP)
			{
				tempPrice = mItemEquipInfo->BuyPrice;
			}
			else
			{
				tempPrice = mItemEquipInfo->SellPrice;
			}
        }
        else if ( mItemOtherInfo )
        {
			if (showType == ITEM_TIPS_TYPE_SHOP)
			{
				tempPrice = mItemOtherInfo->BuyPrice;
			}
			else
			{
				tempPrice = mItemOtherInfo->SellPrice;
			}
        }
		else if ( mItemClanInfo )
		{
			if (showType == ITEM_TIPS_TYPE_SHOP)
			{
				tempPrice = mItemClanInfo->BuyPrice;
			}
			else
			{
				tempPrice = mItemClanInfo->SellPrice;
			}
		}
        else
            DYNAMIC_ASSERT(0);

        Char16 strPrice[32] = L"";
		
        U32 tempStr = tempPrice/1000;
        U32 tempWrit = tempPrice-1000*tempStr;
		if (tempStr > 0 && tempWrit > 0)
		{
			swprintf_s(
				strPrice, _countof(strPrice), 
				CGameMessageConfig::getInstance().getStr(L"itemmoney1", L"itemmoney").c_str(),
				tempStr,
				tempWrit
				) ;
		}
		else if (tempWrit == 0)
		{
			swprintf_s(
				strPrice, _countof(strPrice), 
				CGameMessageConfig::getInstance().getStr(L"itemmoney2", L"itemmoney").c_str(),
				tempStr
				) ;
		}
		else if (tempStr == 0)
		{
			swprintf_s(
				strPrice, _countof(strPrice), 
				CGameMessageConfig::getInstance().getStr(L"itemmoney3", L"itemmoney").c_str(),
				tempWrit
				) ;
		}
		else
		{
			return;
		}
		Str16 priceTips = L"";
		
		if (showType == ITEM_TIPS_TYPE_SHOP)
		{
			priceTips +=L"购买单价：";
		}
		else
		{
			priceTips +=L"出售单价：";
		}
		priceTips += strPrice;
        IWidget* pMoneyWidget = getLayout()->getWidget("itemmoney");
        pMoneyWidget->setCaption(L"");
        CoordI tempCoord = pMoneyWidget->getCoord();
        tempCoord.top = height;
        pMoneyWidget->setCoord(tempCoord);
        pMoneyWidget->setCaption(priceTips);
        //更新高度
        height += tempCoord.height;
    }
    //-----------------------------------------------------------------------------------------
    void UIItemTips::setTipsCoord( U32 height, CoordI coord )
    {
        IWidget* pWidget = getLayout()->getWidget(MAIN_WIDGET);
        CoordI curCoord = pWidget->getCoord();
        curCoord.height = height + item_tips_space;

        U32 curScreenWidth =  ClientMain::getInstance().getEngine()->display()->getWidth();

        //默认位置为右上角
        if ( curCoord.width + coord.left + coord.width > curScreenWidth )
            curCoord.left = coord.left - curCoord.width;
        else
            curCoord.left = coord.left + coord.width;

        if ( coord.top - curCoord.height < 0 )
            curCoord.top = coord.top + coord.height;
        else
            curCoord.top = coord.top - curCoord.height;

        pWidget->setCoord(curCoord);
    }
    
}