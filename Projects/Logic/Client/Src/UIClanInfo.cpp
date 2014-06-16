//***************************************************************************************************
#include "stdafx.h"
#include "UIClanInfo.h"
#include "ItemPacketProcesser.h"
#include "ClientMain.h"
#include "CItemManager.h"
#include "CPlayer.h"
#include "CClan.h"
#include "GenrealEquip.h"
#include "GenrealItem.h"
#include "UIItemTips.h"
#include "UIItemShop.h"
#include "ShopPacketProcesser.h"
#include "CGameMessageConfig.h"
#include "CharacterList.h"
#include "ArtIconResCsv.h"
#include "SkillInfoList.h"
#include "CSkillOwnManager.h"
#include "SkillObject.h"
#include "CCDManager.h"
#include "UIAnyIcon.h"
#include "UISkillTips.h"
#include "UISkillOperate.h"
#include "UISplitItem.h"
#include "UIMessageBox.h"
#include "CPlayerCharacterEntity.h"
#include "CSceneManager.h"
#include "UISLGSkillInfo.h"
#include "UIManage.h"
//***************************************************************************************************
#define  UI_GENREAL_SKILL_NUM 8
#define  UI_GENREAL_EQUIP_NUM 8
#define  UI_GENREAL_ITEM_NUM  4
#define  UI_CLAN_BAG_NUM      5
#define  UI_GOODS_ITEM_NUM    42
#define  UI_GENREAL_LIST_NUM  16
//***************************************************************************************************
namespace MG
{
    UIClanInfo::UIClanInfo()
        :mSelectClanInfoType(UI_CLAN_INFO_TYPE_NULL)
        ,mSelectGeneralId(0)
        ,mTotalGenralPage(1)
        ,mCurGenrealPage(1)
        ,mCurClanBagPage(1)
		,mSplitItemInfo(NULL)
		,mSplitCount(0)
		,mOnTipsItemDBId(0)
		,mOnHighSelectItemDBId(0)
		,mDragOperate(OPERATE_DRAG_NILL)
    {

    }
    //--------------------------------------------------------------------------------------
    UIClanInfo::~UIClanInfo()
    {

    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::setEvent()
    {
        IButton* pButton = NULL;
        IImage* pIcon = NULL;
        IMixList* pMixList = NULL;
        char tempStr[32] = "";

		//��ʱ��ӣ�û�д˹��ܡ�
		{
			getLayout()->getWidget("btnrelife")->setEnabled(false);
		}
		
        //�л����水ť
        for (Int i=1; i<UI_CLAN_INFO_TYPE_MAX; i++)
        {
            Sprintf_s(tempStr, 32, "button%d", i);
            pButton = getLayout()->getButton(tempStr);
			//��ʱ����ӣ���Ϊ����û�о���
			if ( UI_CLAN_INFO_TYPE_ARMY == i )
			{
				pButton->getWidget()->setEnabled(false);
				continue;
			}
			//end
            pButton->getWidget()->setMouseButtonClickEvent(onClickClanInfoBtn);
            pButton->getWidget()->setUserData(i);
        }

        //�佫����
        //pButton = getLayout()->getButton("grbtnleft");
        //pButton->getWidget()->setMouseButtonClickEvent(onClickGenrelLeftBtn);

        //pButton = getLayout()->getButton("grbtnright");
        //pButton->getWidget()->setMouseButtonClickEvent(onClickGenrelRightBtn);

        pMixList = getLayout()->getMixList("grMixlist");
		pMixList->setClickMixListRow(onClickGenrealList);
		pMixList->setDoubleClickMixListRow(onClickGenrealList);


        
        IconInfo tempInfo;
        //����
        for (Int i=1; i<=UI_GENREAL_SKILL_NUM; i++)
        {
            Sprintf_s(tempStr, 32, "skillIcon-%d", i);
            pIcon = getLayout()->getImage(tempStr);
            pIcon->getWidget()->setToolTipsEvent(onEventToolTips);
			pIcon->getWidget()->setMouseLostFocusEvent(onLostMouseFocusEvent);
			pIcon->getWidget()->setMouseSetFocusEvent(onGetMouseFocusEvent);
            //����icon��Ϣ
            tempInfo.group = ICON_GROUP_CHARACTER_SKILL;
            tempInfo.type = ICON_TYPE_SKILL;
            tempInfo.index = i;
            pIcon->getWidget()->setUserData(tempInfo);

            Sprintf_s(tempStr, 32, "passive_skillIcon-%d", i);
            pIcon = getLayout()->getImage(tempStr);
            pIcon->getWidget()->setToolTipsEvent(onEventToolTips);
			pIcon->getWidget()->setMouseLostFocusEvent(onLostMouseFocusEvent);
			pIcon->getWidget()->setMouseSetFocusEvent(onGetMouseFocusEvent);
            //����icon��Ϣ
            tempInfo.group = ICON_GROUP_CHARACTER_LIFESKILL;
            tempInfo.type = ICON_TYPE_SKILL;
            tempInfo.index = i;
            pIcon->getWidget()->setUserData(tempInfo);
        }
        //װ��
        for (Int i=1; i<UI_GENREAL_EQUIP_NUM; i++)
        {
            Sprintf_s(tempStr, 32, "grequip%d", i);
            pIcon = getLayout()->getImage(tempStr);
            pIcon->getWidget()->setToolTipsEvent(onEventToolTips);
            pIcon->getWidget()->setMouseDragEvent(onEventDrag);
            pIcon->getWidget()->setMouseButtonClickEvent(onClickItemIcon);
			pIcon->getWidget()->setMouseLostFocusEvent(onLostMouseFocusEvent);
			pIcon->getWidget()->setMouseSetFocusEvent(onGetMouseFocusEvent);
            //����icon��Ϣ
            tempInfo.group = ICON_GROUP_CHARACTER_EQUIP;
            tempInfo.type = ICON_TYPE_ITEM;
            tempInfo.index = i;
            pIcon->getWidget()->setUserData(tempInfo);
        }

        for (Int i=1; i<=UI_GENREAL_ITEM_NUM; i++)
        {
            Sprintf_s(tempStr, 32, "gritem_icon%d", i);
            pIcon = getLayout()->getImage(tempStr);
            pIcon->getWidget()->setToolTipsEvent(onEventToolTips);
            pIcon->getWidget()->setMouseDragEvent(onEventDrag);
            pIcon->getWidget()->setMouseButtonClickEvent(onClickItemIcon); 
			pIcon->getWidget()->setMouseButtonRightClickEvent(onRightClickImgItem);
            //pIcon->getWidget()->setMouseButtonDoubleClickEvent(onDoubleClickGenrealItem);
			pIcon->getWidget()->setMouseLostFocusEvent(onLostMouseFocusEvent);
			pIcon->getWidget()->setMouseSetFocusEvent(onGetMouseFocusEvent);
            //����icon��Ϣ
            tempInfo.group = ICON_GROUP_CHARACTER_BAG;
            tempInfo.type = ICON_TYPE_ITEM;
            tempInfo.index = i;
            pIcon->getWidget()->setUserData(tempInfo);
        }

        //���ʽ���,���ڲ���Ҫ����onClickClanBagBtn �¼�
        for (Int i=1; i<=UI_CLAN_BAG_NUM; i++)
        {
            Sprintf_s(tempStr, 32, "House-%d", i);
            pButton = getLayout()->getButton(tempStr);
            pButton->getWidget()->setMouseButtonClickEvent(onClickClanBagBtn);
            pButton->getWidget()->setUserData(i);
        }

        for (Int i=1; i<=UI_GOODS_ITEM_NUM; i++)
        {
            Sprintf_s(tempStr, 32, "gsicon%d", i);
            pIcon = getLayout()->getImage(tempStr);
			pIcon->getWidget()->setMouseButtonRightClickEvent(onRightClickImgItem);
            pIcon->getWidget()->setToolTipsEvent(onEventToolTips);
            pIcon->getWidget()->setMouseDragEvent(onEventDrag);
			pIcon->getWidget()->setMouseLostFocusEvent(onLostMouseFocusEvent);
			pIcon->getWidget()->setMouseSetFocusEvent(onGetMouseFocusEvent);
            //����icon��Ϣ
            tempInfo.group = ICON_GROUP_CLAN_BAG;
            tempInfo.type = ICON_TYPE_ITEM;
            tempInfo.index = i;
            pIcon->getWidget()->setUserData(tempInfo);
        }
    }
    //--------------------------------------------------------------------------------------
    MG::Bool UIClanInfo::openGui()
    {
		if ( mSelectClanInfoType == UI_CLAN_INFO_TYPE_NULL )
		{
			onHandleCutUI(UI_CLAN_INFO_TYPE_INFO);
		}

		if (mSelectClanInfoType == UI_CLAN_INFO_TYPE_GOODS)
		{
			updateMoney();
		}
	
        return UIObject::openGui();
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::onClickClanInfoBtn( void* pWidget )
    {
        DYNAMIC_ASSERT(pWidget);
        IWidget* pButton = (IWidget*)pWidget;
        IAny* pAny = pButton->getUserData();
        DYNAMIC_ASSERT(pAny);
        Int* pInt = pAny->castType<Int>();
        DYNAMIC_ASSERT(pInt);

        UIClanInfo::getInstance().onHandleCutUI(UI_CLAN_INFO_TYPE(*pInt));
    }
	//--------------------------------------------------------------------------------------
	void UIClanInfo::setSelectGeneralUI()
	{
		IMixListRow* pMixListRow = NULL;
		IMixList* pMixList = getLayout()->getMixList("grMixlist");
		DYNAMIC_ASSERT(pMixList);

		if ( mSelectGeneralId == 0 )
		{    
			DYNAMIC_ASSERT(0);
		}
		else
		{
			pMixListRow = pMixList->getMixListRow(mSelectGeneralId);
			DYNAMIC_ASSERT(pMixListRow);
			pMixList->setSelectIndex(pMixListRow->getIndex());
		}
	}
	//--------------------------------------------------------------------------------------
	void UIClanInfo::onSureSplitItem(void* arg,Int splitCount, Int maxCount)
	{
		//todo ��ֽӿ�
		if (splitCount > maxCount - 1)
		{
			UIMessageBox::getInstance().showHint(L"���ڵ�ǰ�����������,����������");
			//UIEditYesNoMsgBox::getInstance().closeGui();
			return;
		}
		//
		if (UIClanInfo::getInstance().mSplitItemInfo)
		{
			
			IconInfo tempInfo;
			tempInfo.copy(*UIClanInfo::getInstance().mSplitItemInfo);
			IPointer* pPointer = ClientMain::getInstance().getPointer();
			pPointer->setImage(UIClanInfo::getInstance().mSplitItemInfo->resouceName, UIClanInfo::getInstance().mSplitItemInfo->groupName, UIClanInfo::getInstance().mSplitItemInfo->itemName, tempInfo);
			UIClanInfo::getInstance().mDragOperate = OPERATE_ITEM_SPLIT;
			UIClanInfo::getInstance().mSplitCount = splitCount;
		}
	}
	//--------------------------------------------------------------------------------------
	void UIClanInfo::onCancelSplitItem(void* arg)
	{
		//UIEditYesNoMsgBox::getInstance().closeGui();
	}
	//--------------------------------------------------------------------------------------
	void UIClanInfo::onRightClickImgItem(void* pWidget)
	{
		IWidget* p = (IWidget*)pWidget;
		if (p)
		{
			//�Ҽ�������֮ǰ���϶�������ȡ���϶�������������ճȡ��Ʒ
			if (UIClanInfo::getInstance().mDragOperate != OPERATE_DRAG_NILL)
			{
				if (UIClanInfo::getInstance().mDragOperate == OPERATE_ITEM_SPLIT)
				{
					UIClanInfo::getInstance().mSplitItemInfo = NULL;
					UIClanInfo::getInstance().mSplitCount = 0;
				}
				UIClanInfo::getInstance().mDragOperate = OPERATE_DRAG_NILL;
				IPointer* pPointer = ClientMain::getInstance().getPointer();
				pPointer->resetToDefaultPointer();
				return;
			}	
			//֮ǰû�����϶�������Ҫô��shift��֣�Ҫô�̵�򿪳��ۣ�Ҫô��ʹ�������ʹ�õ���Ʒ
			IconInfo* pInfo = p->getUserData()->castType<IconInfo>();
			if (pInfo->dbID > 0)
			{
				//��⵽��shift�����µ�ͬʱ��Ϊ�����Ʒ��Ϊ
				if ( ClientMain::getInstance().getEngine()->input()->isShiftOn())
				{
					DYNAMIC_ASSERT( pInfo->tempID );
					const ItemInfo* pItemInfo = ItemTemplate::getInstance().getItemInfo(pInfo->tempID);
					//�ж���Ʒ�Ƿ�ɲ�֣����Բ�֣�������ֽ��棬��������ʾ���ܲ��
					ITEM_SITE_TYPE type = ITEM_SITE_TYPE_NULL;
					if (pInfo->group == ICON_GROUP_CLAN_BAG)
					{
						type = ITEM_SITE_TYPE_CLAN;
					}
					else if (pInfo->group == ICON_GROUP_CHARACTER_BAG)
					{
						type = ITEM_SITE_TYPE_CHARACTER_BAG;
					}
					PlayerItem* pItem = CItemManager::getInstance().findItem(pInfo->dbID, type, UIClanInfo::getInstance().mSelectGeneralId);
					if (pItem)
					{
						U32 itemCount = pItem->getItemNum();
						if (itemCount > 1)
						{
							if (1)
							{
								UIClanInfo::getInstance().mSplitItemInfo = pInfo;
								UISplitItem::getInstance().showHint(L"�����Ʒ",L"ȷ��Ҫ��ֵ�ǰ��Ʒ",itemCount,
									(void*)(&UIClanInfo::getInstance()),onSureSplitItem,(void*)(&UIClanInfo::getInstance()),onCancelSplitItem);
							}
						}
						//to do ���ܲ����ʾ
					}
				}
				else
				{
					//ֻ���Ҽ����³�����Ʒ
					//�̵����򿪲��ܳ���
					if(UIItemShop::getInstance().isOpen()  &&  pInfo->group == ICON_GROUP_CLAN_BAG)
					{
						UIItemShop::getInstance().sendSellItem(pInfo);
					}
					//ʹ����Ʒ,������ʹ����
					else   
					{
						PlayerItem* pItem = CItemManager::getInstance().findItem(pInfo->dbID);
						DYNAMIC_ASSERT_LOG(pItem,"pItem == NULL!");
						if(pItem == NULL)
						{
							return;
						}

						//����򿪵������屳������������ʹ������Ʒ
						if ( ICON_GROUP_CLAN_BAG == pInfo->group )
						{
							if ( pItem->getItemType() != ITEM_TYPE_USE_CLAN)
								return;
						}
						
						//����򿪵��ǽ�ɫ���������ǵ�ǰ��ͼ�м�����佫
						if ( ICON_GROUP_CHARACTER_BAG ==  pInfo->group )
						{
							if ( 0 == UIClanInfo::getInstance().getCurGenrealId() ) return;
							CPlayerCharacterEntity* pCPlayerCharacterEntity = CSceneManager::getInstance().getPlayerCharacterEntity(UIClanInfo::getInstance().getCurGenrealId());
							if (NULL == pCPlayerCharacterEntity) return;
						}
						
						ItemPacketProcesser::getInstance().sendUseItem(pItem->getItemIndex(), pItem->getItemSiteType(), UIClanInfo::getInstance().getCurGenrealId());
					}
				}
			}
		}
	}
 
    //--------------------------------------------------------------------------------------
    void UIClanInfo::onClickGenrealList( void* pWidget, Int index )
    {
        DYNAMIC_ASSERT(pWidget);
        IMixList* pMixList = (IMixList*)pWidget;
		IMixListRow* pIMixListRow = pMixList->getMixListRowByIndex(index);
		DYNAMIC_ASSERT(pIMixListRow);
        IAny* pAny = pIMixListRow->getWidget()->getUserData();
        DYNAMIC_ASSERT(pAny);
        PlayerCharacterIdType* pID = pAny->castType<PlayerCharacterIdType>();
        DYNAMIC_ASSERT(pID);

        UIClanInfo::getInstance().onHandleSelectGenreal(*pID);
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::onEventToolTips( void* pWidget, Bool isShow, Int left, Int top )
    {
        DYNAMIC_ASSERT(pWidget);
        IWidget* pIcon = (IWidget*)pWidget;
        IAny* pAny = pIcon->getUserData();
        DYNAMIC_ASSERT(pAny);
        IconInfo* pInfo = pAny->castType<IconInfo>();
        DYNAMIC_ASSERT(pInfo);

        if ( pInfo->tempID )
            UIClanInfo::getInstance().onHandleTips(isShow, pInfo, pIcon->getAbsoluteCoord());
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::onEventDrag( void* pWidget, int left, int top )
    {
        DYNAMIC_ASSERT(pWidget);
        IWidget* pImage = (IWidget*)pWidget;

		UIClanInfo::getInstance().onHandleDrag(pImage);
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::onClickItemIcon( void* pWidget )
    {
        DYNAMIC_ASSERT(pWidget);
        IWidget* pIcon = (IWidget*)pWidget;
        IAny* pAny = pIcon->getUserData();
        DYNAMIC_ASSERT(pAny);
        IconInfo* pInfo = pAny->castType<IconInfo>();
        DYNAMIC_ASSERT(pInfo);
		
		IPointer* pPointer = ClientMain::getInstance().getPointer();
		pPointer->resetToDefaultPointer();
		//�򿪵����滻����
		UIClanInfo::getInstance().onHandleClickGenrealItemIcon(pInfo, pIcon->getAbsoluteCoord());
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::onClickClanBagBtn( void* pWidget )
    {
        DYNAMIC_ASSERT(pWidget);
        IWidget* pButton = (IWidget*)pWidget;
        IAny* pAny = pButton->getUserData();
        DYNAMIC_ASSERT(pAny);
        Int* pInt = pAny->castType<Int>();
        DYNAMIC_ASSERT(pInt);

        UIClanInfo::getInstance().onHandleCutClanBag(*pInt);
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::onHandleCutUI( UI_CLAN_INFO_TYPE type )
    {
		//��ʱ����ӣ���Ϊ����û�о���
		if ( UI_CLAN_INFO_TYPE_ARMY == type )
			return;
		//end
		
        if ( type == mSelectClanInfoType )
            return;
        char msg[32] = "";
		IButton* pButton = NULL;
		IWidget* pWidget = NULL;

		if ( mSelectClanInfoType != UI_CLAN_INFO_TYPE_NULL )
		{
			Sprintf_s(msg, 32, "button%d", (Int)mSelectClanInfoType);
			pButton = getLayout()->getButton(msg);
			pButton->setStateCheck(false);
			//ԭ�������ص�

			Sprintf_s(msg, 32, "bg%d", (Int)mSelectClanInfoType);
			pWidget = getLayout()->getWidget(msg);
			pWidget->setVisible(false);
		}  

        mSelectClanInfoType = type;
        Sprintf_s(msg, 32, "button%d", (Int)mSelectClanInfoType);
        pButton = getLayout()->getButton(msg);
        pButton->setStateCheck(true);

        //ѡ�е�bg��ʾ��
        Sprintf_s(msg, 32, "bg%d", mSelectClanInfoType);
        pWidget = getLayout()->getWidget(msg);
        pWidget->setVisible(true);

        updateBgByClanInfoType(type);
    }
	//--------------------------------------------------------------------------------------
	void UIClanInfo::updateLevel()
	{
		if ( mSelectGeneralId == 0 )
			return;
		
		CPlayerCharacter* pChar = CPlayer::getInstance().getActiveClan()->getPlayerCharacter(mSelectGeneralId);
		DYNAMIC_ASSERT(pChar);
		//��ɫ�ȼ�
		Char16 tempMsg[32] = L"";
		IWidget* pWidget = NULL;
		pWidget = getLayout()->getWidget("lvtext");
		swprintf_s(tempMsg, 32, L"%d", pChar->getData()->mLevel);
		pWidget->setCaption( tempMsg );
	}
	//--------------------------------------------------------------------------------------
	void UIClanInfo::updateExp()
	{
		if ( mSelectGeneralId == 0 )
			return;
		CPlayerCharacter* pChar = CPlayer::getInstance().getActiveClan()->getPlayerCharacter(mSelectGeneralId);
		DYNAMIC_ASSERT(pChar);
		//��ɫ�ȼ�
		Char16 tempMsg[32] = L"";
		IWidget* pWidget = NULL;
		pWidget = getLayout()->getWidget("exp");
		if ( pChar->getData()->charExp1 >= 0 )
			swprintf_s(tempMsg, 32, L"%d", pChar->getData()->charExp1 );
		else	
			swprintf_s(tempMsg, 32, L"%d", 0 );
		pWidget->setCaption( tempMsg );
	}
    //--------------------------------------------------------------------------------------
    void UIClanInfo::onHandleSelectGenreal( PlayerCharacterIdType charid )
    {
        if (charid == mSelectGeneralId)
			return;

		mSelectGeneralId = charid;
		setSelectGeneralUI();

		clearCharItemList();
		clearCharEquipList();
		clearSkillList();

		//��Ʒ
		{
			GenrealItem* pGenrealItem = CItemManager::getInstance().getGenrealItem(mSelectGeneralId);
			if (pGenrealItem)
			{
				const std::map<IdType, PlayerItem*>* pMapGenrealItem = pGenrealItem->getPlayerItemMap();
				std::map<IdType, PlayerItem*>::const_iterator front = pMapGenrealItem->begin();
				std::map<IdType, PlayerItem*>::const_iterator back = pMapGenrealItem->end();

				while (front != back)
				{
					if (mSelectGeneralId == CPlayer::getInstance().getMainPlayerCharacterId())
						addItem(front->second,ITEM_SITE_TYPE_CHARACTER_BAG,true);
					else
						addItem(front->second,ITEM_SITE_TYPE_CHARACTER_BAG,false);

					++front;
				}
			}
		}

		//װ��
		{
			GenrealEquip* pGenrealEquip = CItemManager::getInstance().getGenrealEquip(mSelectGeneralId);
			if (pGenrealEquip)
			{
				PlayerItem**  pEquiplItemList = pGenrealEquip->getEquipItemArray();
				for (Int i=1; i<ITEM_EQUIP_SLOT_TYPE_MAX; i++)
				{
					if ( pEquiplItemList[i] )
						addCharEquip(pEquiplItemList[i]);
				}
			}
		}

		CPlayerCharacter* pChar = CPlayer::getInstance().getActiveClan()->getPlayerCharacter(mSelectGeneralId);
		DYNAMIC_ASSERT(pChar);

		//����
		addCharSkillList(pChar);

		{
			IImage* pImage = NULL;
			IWidget* pWidget = NULL;
			IProgress* pProgress = NULL;
			IButton* pButton = NULL;
			Str16 tempMsg;
			Char16 tempMsg2[32] = L"";

			//ͷ��
			pImage = getLayout()->getImage("head");
			const ArtIconResCsvInfo* tempIconResInfo = ArtIconResCsv::getInstance().getIconArtResInfo(pChar->getData()->charArtIcon);
			pImage->setTexture(tempIconResInfo->ResName, tempIconResInfo->GroupName, tempIconResInfo->ItemName);

			//��ɫ��
			pWidget = getLayout()->getWidget("nametext");
			pWidget->setCaption( pChar->getNormalName() );

			updateLevel();

			//��ɫѪ��
			/*pProgress = getLayout()->getProgress("HP");
			Flt temphp = pChar->getHp()/pChar->getMaxHp();
			pProgress->setProgressPosition(temphp);
			swprintf_s(tempMsg2, 32, L"%d/%d", pChar->getHp(), (Int)(pChar->getMaxHp()));
			pProgress->getWidget()->setCaption(tempMsg2);*/

			//��ɫħ��
			/*pProgress = getLayout()->getProgress("MP");
			Flt tempMp = pChar->getMp()/pChar->getMaxMp();
			pProgress->setProgressPosition(tempMp);
			swprintf_s(tempMsg2, 32, L"%d/%d", pChar->getMp(), (Int)(pChar->getMaxMp()));
			pProgress->getWidget()->setCaption(tempMsg2);*/

			//��ɫ����
			pWidget = getLayout()->getWidget("power");
			swprintf_s(tempMsg2, 32, L"%d", (int)(pChar->getAttributeSet()->getFanalValue(ATTR_ID_Talent1)) );
			pWidget->setCaption( tempMsg2 );

			//��ɫͳ˧
			pWidget = getLayout()->getWidget("technique");
			swprintf_s(tempMsg2, 32, L"%d", (int)(pChar->getAttributeSet()->getFanalValue(ATTR_ID_Talent2)) );
			pWidget->setCaption( tempMsg2 );

			//��ɫ��ı
			pWidget = getLayout()->getWidget("resourcefulness");
			swprintf_s(tempMsg2, 32, L"%d", (int)(pChar->getAttributeSet()->getFanalValue(ATTR_ID_Talent3)) );
			pWidget->setCaption( tempMsg2 );

			//��ɫ����
			pWidget = getLayout()->getWidget("affair");
			swprintf_s(tempMsg2, 32, L"%d", (int)(pChar->getAttributeSet()->getFanalValue(ATTR_ID_Talent4)) );
			pWidget->setCaption( tempMsg2 );

			//��ɫ�Ա�
			pWidget = getLayout()->getWidget("sex");
			GENDER_TYPE gender = pChar->getCharacterTempInfo()->getGenrealGenderType();
			if (gender == GENDER_TYPE_MAN)
			{
				swprintf_s(tempMsg2, 32, L"��");
			}
			else
				swprintf_s(tempMsg2, 32, L"Ů");	
			pWidget->setCaption( tempMsg2 );

			//��ɫ����
			pWidget = getLayout()->getWidget("age");
			swprintf_s(tempMsg2, 32, L"%d", pChar->getData()->charCurAge);
			pWidget->setCaption( tempMsg2 );

			//��ɫְҵ
			pWidget = getLayout()->getWidget("job");
			swprintf_s(tempMsg2, 32, L"formulatype%d", pChar->getCharacterTempInfo()->getCharacterFormulaType());
			pWidget->setCaption( CGameMessageConfig::getInstance().getStr(L"CharacterJudgeTemplate", tempMsg2, tempMsg2) );

			//��ɫ����
			pWidget = getLayout()->getWidget("lifespan");
			swprintf_s(tempMsg2, 32, L"%d", pChar->getData()->charLifeSpan );
			pWidget->setCaption( tempMsg2 );

			//��ɫת������
			pWidget = getLayout()->getWidget("reborn");
			if ( pChar->getData()->mLineageNum == 0 )
				pWidget->setCaption(CGameMessageConfig::getInstance().getStr(L"CharacterJudgeTemplate", L"metempsychosis0", L"metempsychosis0"));
			else
			{
				tempMsg = CGameMessageConfig::getInstance().getStr(L"CharacterJudgeTemplate", L"metempsychosis1", L"metempsychosis1");
				swprintf_s(tempMsg2, 32, tempMsg.c_str(), pChar->getData()->mLineageNum);
				pWidget->setCaption(tempMsg2);
			}

			//��ɫ����
			pWidget = getLayout()->getWidget("exp");
			if ( pChar->getData()->charExp1 >= 0 )
				swprintf_s(tempMsg2, 32, L"%d", pChar->getData()->charExp1 );
			else
				swprintf_s(tempMsg2, 32, L"%d", 0 );

			pWidget->setCaption( tempMsg2 );

			//��ɫ����
			pWidget = getLayout()->getWidget("score");
			if ( pChar->getData()->charExp3 >= 0 )
				swprintf_s(tempMsg2, 32, L"%d", pChar->getData()->charExp3);
			else
				swprintf_s(tempMsg2, 32, L"%d", 0 );
			pWidget->setCaption( tempMsg2 );

			//��ɫ״��
			pWidget = getLayout()->getWidget("lifestate");
			if ( pChar->getData()->charLifeState == CHAR_LIFE_STATE_Living )
			{
				swprintf_s(tempMsg2, 32, L"worktype%d", pChar->getData()->charState);
				pWidget->setCaption( CGameMessageConfig::getInstance().getStr(L"CharacterJudgeTemplate", tempMsg2, tempMsg2) );
				//���ظ��ť
				//getLayout()->getWidget("btnrelife")->setVisible(false);
			}
			else if ( pChar->getData()->charLifeState > CHAR_LIFE_STATE_Living )
			{
				swprintf_s(tempMsg2, 32, L"lifetype%d", pChar->getData()->charState);
				pWidget->setCaption( CGameMessageConfig::getInstance().getStr(L"CharacterJudgeTemplate", tempMsg2, tempMsg2) );
				//��ʾ���ť
				//getLayout()->getWidget("")->setVisible(true);
			}

			//��ɫ���
			/*pWidget = getLayout()->getWidget("tips");
			tempMsg = pChar->getCharacterTempInfo()->getCharacterTips();
			ClientMain::getInstance().getGui()->getHeightStrAddBreak(tempMsg, pWidget->getSize().x);
			pWidget->setCaption( tempMsg );*/
		}
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::onHandleTips( Bool isShow, IconInfo* pIconInfo, CoordI coord )
    {
        if ( isShow == false )
        {
            switch (pIconInfo->type)
            {
            case ICON_TYPE_ITEM:
                UIItemTips::getInstance().closeGui();
				mOnTipsItemDBId = 0;
                break;
			case ICON_TYPE_SKILL:
				UISkillTips::getInstance().closeGui();
				break;
			default:    
				break;
            }
        }
        else
        {
            switch (pIconInfo->type)
            {
            case ICON_TYPE_ITEM:
                {
                    PlayerItem* pItem = CItemManager::getInstance().findItem(pIconInfo->dbID);
                    DYNAMIC_ASSERT(pItem);
					mOnTipsItemDBId = pIconInfo->dbID;
                    UIItemTips::getInstance().openItemTips(pItem, coord);
                }
				break;
			case ICON_TYPE_SKILL:  
				{
					CPlayerCharacter* pCharacter = CPlayer::getInstance().getActiveClan()->getPlayerCharacter(mSelectGeneralId);
					DYNAMIC_ASSERT(pCharacter);
					UISkillTips::getInstance().openSkillTips(pIconInfo, coord, pCharacter);
				}
                break;
			default:    
				break;
            }
        }
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::onHandleGetIconInfo( IconInfo* pSendInfo, void*& widget2, CoordI rect )
    {
        if ( pSendInfo->type != ICON_TYPE_ITEM )
            return;

        //���ͼƬ����
        IImage* mImage = ClientMain::getInstance().getGui()->getImage(rect, pSendInfo->resouceName, pSendInfo->groupName, pSendInfo->itemName, true);
        widget2 = (void*)( mImage );
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::onHandleDrop( IconInfo* pSend, IconInfo* pRece )
    {
        if (mDragOperate == OPREATE__ITEM_CHANGEPOS)
        {
			switch (pSend->group)
			{
			case ICON_GROUP_CHARACTER_BAG:
				onHandleCharBag(pSend, pRece);
				break;
			case ICON_GROUP_CHARACTER_EQUIP:
				onHandleCharEquip(pSend, pRece);
				break;
			case ICON_GROUP_CLAN_BAG:
				onHandleClanBag(pSend, pRece);
				break;
			}
        }
		else if (mDragOperate == OPERATE_ITEM_SPLIT)
		{		
			if (pSend->group == ICON_GROUP_CHARACTER_BAG || pSend->group == ICON_GROUP_CLAN_BAG)
			{
				onSplitItem(pSend, pRece);
			}	
		}
		
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::onHandleClickGenrealItemIcon( IconInfo* pIconInfo, CoordI screenCoord )
    {
		ITEM_SITE_TYPE tempType;
		if ( pIconInfo->group == ICON_GROUP_CHARACTER_BAG )
			tempType = ITEM_SITE_TYPE_CHARACTER_BAG;
		else
			tempType = ITEM_SITE_TYPE_CHARACTER_EQUIP;

		Bool isUnintall = false;
		if ( pIconInfo->tempID )
			isUnintall = true;

		UIAnyIcon::getInstance().loadItem(tempType, pIconInfo->index, screenCoord, isUnintall);
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::onHandleCutClanBag( Int index )
    {
		if ( index == 0 )
		{
			DYNAMIC_ASSERT(0);
			return;
		}

        //�����ͬ��return
        if ( mCurClanBagPage == index )
            return;

		char msg[32] = "";
		IButton* pButton = NULL;
		if ( mCurClanBagPage != 0 )
		{
			
			Sprintf_s(msg, 32, "House-%d", mCurClanBagPage);
			pButton = getLayout()->getButton(msg);
			pButton->setStateCheck(false);
		}

        mCurClanBagPage = index;
        Sprintf_s(msg, 32, "House-%d", mCurClanBagPage);
        pButton = getLayout()->getButton(msg);
        pButton->setStateCheck(true);

        //��clear
        clearClanBagItemList();

        //һ��һ�����롣
        U32 nStart = UI_GOODS_ITEM_NUM*(mCurClanBagPage-1);
        U32 nEnd =  UI_GOODS_ITEM_NUM*mCurClanBagPage;
        ClanItems* pClanItems = CItemManager::getInstance().getClanItems();

        for (U32 i=nStart; i<nEnd; i++)
        {
            PlayerItem* pItem = pClanItems->findItem(i);
            if ( pItem )
                addClanBagItem(pItem);
        }
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::addClanBagItem( PlayerItem* pItem )
    {
        //����Ƿ���Ҫˢ�¡�
        //��
        //�����ݲ���顣
        Char8 temp[24] = "";
        U32 index = pItem->getItemIndex()-(mCurClanBagPage-1)*CLAN_ITEM_BAG_NUM;
		//U32 index = pItem->getItemIndex() + (mCurClanBagPage)*CLAN_ITEM_BAG_NUM;
        sprintf_s(temp, 24, "gsicon%d", index);
        IImage* pIcon = getLayout()->getImage( temp );

        IconInfo*  pIconInfo = pIcon->getWidget()->getUserData()->castType<IconInfo>();
        DYNAMIC_ASSERT(pIconInfo);

        const ItemInfo* iteminfo = pItem->getItemInfo();
        DYNAMIC_ASSERT(iteminfo);

		if (iteminfo->ItemType == ITEM_TYPE_EXP || iteminfo->ItemType == ITEM_TYPE_MONEY)
		{
			return;
		}

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
            sprintf_s(temp, 24, "gstext%d", index);
            IWidget* pWidget = getLayout()->getWidget(temp);
            DYNAMIC_ASSERT(pWidget);
            Char16 tempNum[16] = L"";
			swprintf_s(tempNum, 16, L"%d", pItem->getItemNum());
            pWidget->setCaption(tempNum);
        }
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::deleteClanBagItem( U32 index )
    {
        index -= (mCurClanBagPage-1)*CLAN_ITEM_BAG_NUM;
        Char8 temp[24] = "";
        sprintf_s(temp, 24, "gsicon%d", index);
        IImage* pIcon = getLayout()->getImage( temp );
        if (pIcon)
        {
            IconInfo*  pIconInfo = pIcon->getWidget()->getUserData()->castType<IconInfo>();
			DYNAMIC_ASSERT(pIconInfo);
			//�ص�ɾ����Ʒ��tips
			if (mOnTipsItemDBId > 0 && mOnTipsItemDBId == pIconInfo->dbID)
			{
				UIItemTips::getInstance().closeGui();
				mOnTipsItemDBId = 0;
			}
			//�ص�ɾ����Ʒ�ĸ���ѡ��״̬
			if (mOnHighSelectItemDBId > 0 && mOnHighSelectItemDBId == pIconInfo->dbID)
			{
				setHighVisble(ICON_GROUP_CLAN_BAG,1,false);
				mOnHighSelectItemDBId = 0;
			}
            pIcon->setTexture("", "", "");
            pIconInfo->clear();
            pIcon->getWidget()->setUserData(*pIconInfo);
        }
        sprintf_s(temp, 24, "gstext%d", index);
        IWidget* pWidget = getLayout()->getWidget( temp );
        if ( pWidget )
            pWidget->setCaption(L"");
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::updateClanBagItem( U32 index, U32 num )
    {
        index -= (mCurClanBagPage-1)*CLAN_ITEM_BAG_NUM;
        Char8 temp[24] = "";
        sprintf_s(temp, 24, "gstext%d", index);
        IWidget* pWidget = getLayout()->getWidget( temp );
        if (pWidget)
        {
            if ( num > 1 )
            {  
				Char16 numStr[16] = L"";
				swprintf_s(numStr, 16, L"%d", num);
                pWidget->setCaption(numStr); 
            }
            else
                pWidget->setCaption(L"");
        }
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::addUICharItem( PlayerItem* pItem )
    {
        Char8 temp[24] = "";
        U32 index = pItem->getItemIndex();
        sprintf_s(temp, 24, "gritem_icon%d", index);
        IImage* pIcon = getLayout()->getImage( temp );

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

		if (iteminfo->ItemType != ITEM_TYPE_USE_GENERAL)
		{
			return;
		}

		//CD
		sprintf_s(temp, 24, "grcd%d", index);
		IWidget* pChildWidget = pIcon->getWidget()->findWidget(temp);
		//���ҵ�CD��ʱ�䡣
		CDTimerData* pCDTimerData = CCDManager::getInstance().findCD(
				CD_MASTER_TYPE_CHARACTER, 
				mSelectGeneralId, 
				iteminfo->getItemUseOwnerTimepieceId()
			);
		if ( pCDTimerData == NULL )
		{
			pCDTimerData = CCDManager::getInstance().findCD(
				CD_MASTER_TYPE_CHARACTER, 
				mSelectGeneralId, 
				iteminfo->getItemUsePublicTimepieceId()
				);
		}
		//�ټ�CD
		if ( pCDTimerData )
		{
			Int tempLastTime = pCDTimerData->mLastTime + pCDTimerData->mStartTime - MGTimeOp::getCurrTick(); 
			if ( tempLastTime > 0 )
				pChildWidget->getImage()->setImageBroadcast(
					MGIMAGE_BROADCAST_TYPE_ONCE, 
					tempLastTime, 
					pCDTimerData->mTotalTime
				);
		}

        //text
        if ( pItem->getItemNum() > 1 )
        {
            sprintf_s(temp, 24, "grtext%d", index);
            IWidget* pWidget = getLayout()->getWidget(temp);
            DYNAMIC_ASSERT(pWidget);
			Char16 tempNum[16] = L"";
			swprintf_s( tempNum, 16, L"%d", pItem->getItemNum() );
			pWidget->setCaption(tempNum);
        }
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::deleteUICharItem( U32 index )
    {
		//���ͼƬ��
        Char8 temp[24] = "";
        sprintf_s(temp, 24, "gritem_icon%d", index);
        IImage* pIcon = getLayout()->getImage( temp );
        if (pIcon)
        {
            IconInfo*  pIconInfo = pIcon->getWidget()->getUserData()->castType<IconInfo>();
			//�ص�ɾ����Ʒ��tips
			if (mOnTipsItemDBId > 0 && mOnTipsItemDBId == pIconInfo->dbID)
			{
				UIItemTips::getInstance().closeGui();
				mOnTipsItemDBId = 0;
			}
			//�ص�ɾ����Ʒ�ĸ���ѡ��״̬
			if (mOnHighSelectItemDBId > 0 && mOnHighSelectItemDBId == pIconInfo->dbID)
			{
				setHighVisble(ICON_GROUP_CHARACTER_BAG,1,false);
				mOnHighSelectItemDBId = 0;
			}
			pIcon->setTexture("", "", "");
            pIconInfo->clear();
            pIcon->getWidget()->setUserData(*pIconInfo);
        }

		//�ص�CD
		sprintf_s(temp, 24, "grcd%d", index);
		IWidget* pChildWidget = pIcon->getWidget()->findWidget(temp);
		pChildWidget->getImage()->setImageBroadcast(MGIMAGE_BROADCAST_TYPE_NULL, 0, 0);

		//�������
        sprintf_s(temp, 24, "grtext%d", index);
        IWidget* pWidget = getLayout()->getWidget( temp );	
        if ( pWidget )
			pWidget->setCaption(L"");

    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::updateUICharItem( U32 index, U32 num )
    {
        Char8 temp[24] = "";
        sprintf_s(temp, 24, "grtext%d", index);
        IWidget* pWidget = getLayout()->getWidget( temp );
        if (pWidget)
        {
            Char16 tempWStr[24] = L"";
            if ( num > 1 )
            {  
				swprintf_s(tempWStr, 24, L"%d", num);
                pWidget->setCaption(tempWStr); 
            }
            else
                pWidget->setCaption(tempWStr);
        }
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::addCharEquip( PlayerItem* pItem )
    {
        Char8 temp[24] = "";
        U32 index = pItem->getItemIndex();
        sprintf_s(temp, 24, "grequip%d", index);
        IImage* pIcon = getLayout()->getImage( temp );

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
		updateBasicAttr();
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::deleteCharEquip( U32 index )
    {
        Char8 temp[24] = "";
        sprintf_s(temp, 24, "grequip%d", index);
        IImage* pIcon = getLayout()->getImage( temp );
        if (pIcon)
        {
            IconInfo*  pIconInfo = pIcon->getWidget()->getUserData()->castType<IconInfo>();
			//�ص�ɾ����Ʒ��tips
			if (mOnTipsItemDBId > 0 && mOnTipsItemDBId == pIconInfo->dbID)
			{
				UIItemTips::getInstance().closeGui();
				mOnTipsItemDBId = 0;
			}
			//�ص�ɾ����Ʒ�ĸ���ѡ��״̬
			if (mOnHighSelectItemDBId > 0 && mOnHighSelectItemDBId == pIconInfo->dbID)
			{
				setHighVisble(ICON_GROUP_CHARACTER_EQUIP,1,false);
				mOnHighSelectItemDBId = 0;
			}
            pIcon->setTexture("", "", "");
            pIconInfo->clear();
            pIcon->getWidget()->setUserData(*pIconInfo);
        }
		updateBasicAttr();
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::addItem( PlayerItem* pItem, ITEM_SITE_TYPE type, bool addKeyboard )
    {
        switch (type)
        {
        case ITEM_SITE_TYPE_CLAN:
            addClanBagItem(pItem);
            break;
        case ITEM_SITE_TYPE_CHARACTER_BAG:
			{
				if(addKeyboard)
				{
					if (UIManager::getInstance().getGameType() == GameType_Slg)
					{
						if (UISLGSkillInfo::getInstance().opreatorIsMe())
						{
							UISLGSkillInfo::getInstance().addItemIcon(pItem);
						}	
					}
					else if (UIManager::getInstance().getGameType() == GameType_Rpg)
					{
						UISkillOperate::getInstance().addCharItem(pItem);
					}

					if (mSelectGeneralId == CPlayer::getInstance().getMainPlayerCharacterId())
					{
						addUICharItem(pItem);
					}
				}
				else
					addUICharItem(pItem);
					
			}
			break;
        case ITEM_SITE_TYPE_CHARACTER_EQUIP:
            addCharEquip(pItem);
            break;
        default:
           // DYNAMIC_ASSERT(0);
            break;
        }
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::deleteItem( U32 index, ITEM_SITE_TYPE type,bool delKeyboard )
    {
        switch (type)
        {
        case ITEM_SITE_TYPE_CLAN:
            deleteClanBagItem(index);
            break;
        case ITEM_SITE_TYPE_CHARACTER_BAG:
			{
				if (delKeyboard)
				{
					//ɾ����ݼ�
					if (UIManager::getInstance().getGameType() == GameType_Slg)
					{
						if (UISLGSkillInfo::getInstance().opreatorIsMe())
						{
							UISLGSkillInfo::getInstance().deleteCharItem(index);
						}	
					}
					else if (UIManager::getInstance().getGameType() == GameType_Rpg)
					{
						UISkillOperate::getInstance().deleteCharItem(index);
					}
					//
					if (mSelectGeneralId == CPlayer::getInstance().getMainPlayerCharacterId())
					{
						//ѡ����Ǹ������е��佫һ������Ҫɾ�����屳������
						deleteUICharItem(index);
					}
				}
				else
					deleteUICharItem(index);
			}
			break;
        case ITEM_SITE_TYPE_CHARACTER_EQUIP:
            deleteCharEquip(index);
            break;
        default:
            DYNAMIC_ASSERT(0);
            break;
        }
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::updateItem( U32 index, U32 num, ITEM_SITE_TYPE type, bool updateKeyboard )
    {
        switch (type)
        {
        case ITEM_SITE_TYPE_CLAN:
            updateClanBagItem(index, num);
            break;
        case ITEM_SITE_TYPE_CHARACTER_BAG:
			{	
				//���¿�ݼ���ui
				if(updateKeyboard)
				{
					if (UIManager::getInstance().getGameType() == GameType_Slg)
					{
						if (UISLGSkillInfo::getInstance().opreatorIsMe())
						{
							UISLGSkillInfo::getInstance().updateCharItem(index,num);
						}	
					}
					else if (UIManager::getInstance().getGameType() == GameType_Rpg)
					{
						UISkillOperate::getInstance().updateCharItem(index,num);
					}

					if (mSelectGeneralId == CPlayer::getInstance().getMainPlayerCharacterId())
					{
						updateUICharItem(index, num);
					}
				}
				else
					updateUICharItem(index, num);
			}
			break;
        default:
            DYNAMIC_ASSERT(0);
            break;
        }
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::clearClanBagItemList()
    {
        Char8 temp[24] = "";
        for (Int i=1; i<=UI_GOODS_ITEM_NUM; i++)
        {
            sprintf_s(temp, 24, "gsicon%d", i);
            IImage* pIcon = getLayout()->getImage( temp );
            if ( pIcon )
            {
                IconInfo*  pIconInfo = pIcon->getWidget()->getUserData()->castType<IconInfo>();
                pIcon->setTexture("", "", "");
                pIconInfo->clear();
                pIcon->getWidget()->setUserData(*pIconInfo);
            }
            sprintf_s(temp, 24, "gstext%d", i);
            IWidget* pWidget = getLayout()->getWidget( temp );
            if ( pWidget )
                pWidget->setCaption(L"");
        } 
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::clearCharItemList()
    {
        Char8 temp[24] = "";
        for (Int i=1; i<=UI_GENREAL_ITEM_NUM; i++)
        {
            sprintf_s(temp, 24, "gritem_icon%d", i);
            IImage* pIcon = getLayout()->getImage( temp );
            if ( pIcon )
            {
                IconInfo*  pIconInfo = pIcon->getWidget()->getUserData()->castType<IconInfo>();
                pIcon->setTexture("", "", "");
                pIconInfo->clear();
                pIcon->getWidget()->setUserData(*pIconInfo);
            }
            sprintf_s(temp, 24, "grtext%d", i);
            IWidget* pWidget = getLayout()->getWidget( temp );
            if ( pWidget )
                pWidget->setCaption(L"");
        } 
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::clearCharEquipList()
    {
        Char8 temp[24] = "";
        for (Int i=1; i<UI_GENREAL_EQUIP_NUM; i++)
        {                       
            sprintf_s(temp, 24, "grequip%d", i);
            IImage* pIcon = getLayout()->getImage( temp );
            if ( pIcon )
            {
                IconInfo*  pIconInfo = pIcon->getWidget()->getUserData()->castType<IconInfo>();
                pIcon->setTexture("", "", "");
                pIconInfo->clear();
                pIcon->getWidget()->setUserData(*pIconInfo);
            }
        } 
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::clearSkillList()
    {
        Char8 temp[24] = "";
        for (Int i = 1; i <= UI_GENREAL_SKILL_NUM; i++)
        {
            sprintf_s(temp, 24, "skillIcon-%d", i);
            IImage* pIcon = getLayout()->getImage( temp );
            if ( pIcon )
            {
                IconInfo*  pIconInfo = pIcon->getWidget()->getUserData()->castType<IconInfo>();
                pIcon->setTexture("", "", "");
                pIconInfo->clear();
                pIcon->getWidget()->setUserData(*pIconInfo);
            }

            sprintf_s(temp, 24, "passive_skillIcon-%d", i);
            pIcon = getLayout()->getImage( temp );
            if ( pIcon )
            {
                IconInfo*  pIconInfo = pIcon->getWidget()->getUserData()->castType<IconInfo>();
                pIcon->setTexture("", "", "");
                pIconInfo->clear();
                pIcon->getWidget()->setUserData(*pIconInfo);
            }
        } 
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::onHandleClanBag( IconInfo* pSend, IconInfo* pRece )
    {
        ////����
        //if ( ishave == false )
        //{
        //    //��ʾ�Ƿ�ɾ��XXX����
        //    clanBagDropItem(pSend->dbID);
        //} 
        //else if ( pRece == NULL )
        //{    
        //    checkSpecialOperate(pSend);
        //}
        ////���屳�����԰���Ʒ�ŵ����屳������ɫ��������ɫװ�������������
        //else 
        if ( 
                ICON_GROUP_CLAN_BAG        == pRece->group     || 
                ICON_GROUP_CHARACTER_BAG   == pRece->group     ||
                ICON_GROUP_CHARACTER_EQUIP == pRece->group
                )
            {
                //����λ��
                clanBagChangePos(pSend, pRece);
            }
        else
        {
            checkSpecialOperate(pSend);
        }
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::onHandleCharBag( IconInfo* pSend, IconInfo* pRece )
    {
        ////�ӵ���
        //if ( ishave == false )  
        //{
        //    characterBagDropItem(pSend->dbID);  
        //    return;
        //}
        //else
        /*if ( pRece == NULL )
            return;
        else*/
        if ( 
            pRece->group == ICON_GROUP_CHARACTER_BAG  ||
            pRece->group == ICON_GROUP_CHARACTER_EQUIP ||
            pRece->group == ICON_GROUP_CLAN_BAG
            )
        {
            characterBagChangePos(pSend, pRece);
        }
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::onHandleCharEquip( IconInfo* pSend, IconInfo* pRece )
    {
        //�ӵ���
        //if ( ishave == false )  
        //{
        //    characterEquipDropItem(pSend->dbID);  
        //    return;
        //}
        //else if ( pRece == NULL )
        //    return;
        ////����
        //else 
        if ( 
            pRece->group == ICON_GROUP_CHARACTER_BAG  ||
            pRece->group == ICON_GROUP_CLAN_BAG
            )
        {
			characterEquipChangePos(pSend, pRece);
        }
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::clanBagDropItem( IdType itemdbid )
    {
        //��ʾ��Ϣ��
        sendDropItem(ITEM_SITE_TYPE_CLAN, itemdbid, 0);
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::clanBagChangePos( IconInfo* pSendInfo, IconInfo* pReceInfo )
    {
        U32 sendIndex = pSendInfo->index;
        U32 recvIndex = pReceInfo->index;
        
        //ͬ�����ƶ�λ��
        if ( pReceInfo->group == ICON_GROUP_CLAN_BAG )
        {
            //��ͬλ��
            if ( sendIndex == (recvIndex + CLAN_ITEM_BAG_NUM*(mCurClanBagPage-1)) )
                return;
            //�ϵ�û�н���λ��
            if ( CItemManager::getInstance().getClanBagSize() < recvIndex )
                return;
            sendBagChangePos(sendIndex, (recvIndex + CLAN_ITEM_BAG_NUM*(mCurClanBagPage-1)), ITEM_SITE_TYPE_CLAN, ITEM_SITE_TYPE_CLAN, mSelectGeneralId);
        }
        //���ɫ�������潻��
        else if ( pReceInfo->group == ICON_GROUP_CHARACTER_BAG )
        {
            sendBagChangePos(sendIndex, recvIndex, ITEM_SITE_TYPE_CLAN, ITEM_SITE_TYPE_CHARACTER_BAG, mSelectGeneralId);
        }
        //��װ�����潻��
        else if ( pReceInfo->group == ICON_GROUP_CHARACTER_EQUIP )
        {
            PlayerItem* pItem = CItemManager::getInstance().findItem(pSendInfo->dbID, ITEM_SITE_TYPE_CLAN, mSelectGeneralId);
            DYNAMIC_ASSERT(pItem);
            if (pItem->getItemType() != ITEM_TYPE_EQUIP_GENERAL)
                return;
            if ( pItem->getItemEquipSlotType() != pReceInfo->index )
                return;
            sendBagChangePos(sendIndex, recvIndex, ITEM_SITE_TYPE_CLAN, ITEM_SITE_TYPE_CHARACTER_EQUIP, mSelectGeneralId);
        }
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::sendDropItem( ITEM_SITE_TYPE type,IdType ID, PlayerCharacterIdType charid )
    {
        ItemPacketProcesser::getInstance().sendDelItem(type, ID, charid);
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::sendBagChangePos( U32 sendIndex, U32 recvIndex,ITEM_SITE_TYPE sendType,ITEM_SITE_TYPE recvType, PlayerCharacterIdType charid )
    {
        ItemPacketProcesser::getInstance().sendChangePos(sendIndex, recvIndex, sendType, recvType, charid);
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::characterBagDropItem( IdType itemdbid )
    {
        //��ʾ��Ϣ��
        sendDropItem(ITEM_SITE_TYPE_CHARACTER_BAG, itemdbid, mSelectGeneralId);
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::characterEquipDropItem( IdType itemdbid )
    {
        //��ʾ��Ϣ��
        sendDropItem(ITEM_SITE_TYPE_CHARACTER_EQUIP, itemdbid, mSelectGeneralId);
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::characterBagChangePos( IconInfo* pSendInfo, IconInfo* pReceInfo )
    {
        U32 sendIndex = pSendInfo->index;
        U32 recvIndex = pReceInfo->index;
        //ͬ�����ƶ�λ��
        if ( pReceInfo->group == ICON_GROUP_CHARACTER_BAG )
        {
            //��ͬλ��
            if ( sendIndex == recvIndex )
                return;
            sendBagChangePos(sendIndex, recvIndex, ITEM_SITE_TYPE_CHARACTER_BAG, ITEM_SITE_TYPE_CHARACTER_BAG, mSelectGeneralId);
        }
        //�����屳�����潻��
        else if ( pReceInfo->group == ICON_GROUP_CLAN_BAG )
        {
            //�ϵ�û�н���λ��
            if ( CItemManager::getInstance().getClanBagSize() < (recvIndex+(mCurClanBagPage-1)*UI_GOODS_ITEM_NUM) )
                return;
            sendBagChangePos(sendIndex, (recvIndex+(mCurClanBagPage-1)*UI_GOODS_ITEM_NUM),ITEM_SITE_TYPE_CHARACTER_BAG, ITEM_SITE_TYPE_CLAN, mSelectGeneralId);
            return;
        }
        //��װ�����潻��
        else if ( pReceInfo->group == ICON_GROUP_CHARACTER_EQUIP )
        {
            PlayerItem* pItem = CItemManager::getInstance().findItem(pSendInfo->dbID, ITEM_SITE_TYPE_CHARACTER_BAG, mSelectGeneralId);
            DYNAMIC_ASSERT(pItem);
            if (pItem->getItemType() != ITEM_TYPE_EQUIP_GENERAL)
                return;
            if ( pItem->getItemEquipSlotType() != pReceInfo->index )
                return;
            sendBagChangePos(sendIndex, recvIndex, ITEM_SITE_TYPE_CHARACTER_BAG, ITEM_SITE_TYPE_CHARACTER_EQUIP, mSelectGeneralId);
        }
    }
	//--------------------------------------------------------------------------------------
	void UIClanInfo::onSplitItem( IconInfo* pSendInfo, IconInfo* pReceInfo )
	{
		U32 sendIndex = pSendInfo->index;
		U32 recvIndex = pReceInfo->index;
		//�ӽ�ɫ�������
		if (pSendInfo->group == ICON_GROUP_CHARACTER_BAG)
		{
			//��ֵ���ɫ����
			if ( pReceInfo->group == ICON_GROUP_CHARACTER_BAG )
			{
				//��ͬλ��
				if ( sendIndex == recvIndex )
					return;
				ItemPacketProcesser::getInstance().sendSplitItem(sendIndex, ITEM_SITE_TYPE_CHARACTER_BAG, ITEM_SITE_TYPE_CHARACTER_BAG, recvIndex, mSplitCount, mSelectGeneralId);
			}
			//��ֵ����屳��
			else if ( pReceInfo->group == ICON_GROUP_CLAN_BAG )
			{
				//�ϵ�û�н���λ��
				if ( CItemManager::getInstance().getClanBagSize() < (recvIndex+(mCurClanBagPage-1)*UI_GOODS_ITEM_NUM) )
					return;
				ItemPacketProcesser::getInstance().sendSplitItem(sendIndex, ITEM_SITE_TYPE_CHARACTER_BAG, ITEM_SITE_TYPE_CLAN, (recvIndex+(mCurClanBagPage-1)*UI_GOODS_ITEM_NUM), mSplitCount, mSelectGeneralId);
			}
		}
		//�����屳�����
		else if (pSendInfo->group == ICON_GROUP_CLAN_BAG)
		{
			if ( pReceInfo->group == ICON_GROUP_CLAN_BAG )
			{
				//��ͬλ��
				if ( sendIndex == recvIndex )
					return;
				//�ϵ�û�н���λ��
				if ( CItemManager::getInstance().getClanBagSize() < (recvIndex+(mCurClanBagPage-1)*UI_GOODS_ITEM_NUM) )
					return;
				ItemPacketProcesser::getInstance().sendSplitItem(sendIndex, ITEM_SITE_TYPE_CLAN, ITEM_SITE_TYPE_CLAN, (recvIndex+(mCurClanBagPage-1)*UI_GOODS_ITEM_NUM), mSplitCount, mSelectGeneralId);
			}
			//��ֵ���ɫ����
			else if ( pReceInfo->group == ICON_GROUP_CHARACTER_BAG )
			{
				ItemPacketProcesser::getInstance().sendSplitItem(sendIndex, ITEM_SITE_TYPE_CLAN, ITEM_SITE_TYPE_CHARACTER_BAG, recvIndex, mSplitCount, mSelectGeneralId);
			}
		}
		mSplitCount = 0;
		mSplitItemInfo = NULL;
	}
    //--------------------------------------------------------------------------------------
    void UIClanInfo::characterEquipChangePos( IconInfo* pSendInfo, IconInfo* pReceInfo )
    {
        U32 sendIndex = pSendInfo->index;
        U32 recvIndex = pReceInfo->index;

        if ( pReceInfo->group == ICON_GROUP_CHARACTER_BAG )
        {
            if ( pReceInfo->dbID )
            {
                PlayerItem* pItem = CItemManager::getInstance().findItem(pReceInfo->dbID, ITEM_SITE_TYPE_CHARACTER_BAG, mSelectGeneralId);
                DYNAMIC_ASSERT(pItem);
                if (pItem->getItemType() != ITEM_TYPE_EQUIP_GENERAL)
                    return;
                if ( pItem->getItemEquipSlotType() != pSendInfo->index )
                    return;
            }
            sendBagChangePos(sendIndex, recvIndex, ITEM_SITE_TYPE_CHARACTER_EQUIP,ITEM_SITE_TYPE_CHARACTER_BAG, mSelectGeneralId);
        }
        //�����屳�����潻��
        else if ( pReceInfo->group == ICON_GROUP_CLAN_BAG )
        {
            if ( pReceInfo->dbID )
            {
                PlayerItem* pItem = CItemManager::getInstance().findItem(pReceInfo->dbID, ITEM_SITE_TYPE_CLAN, mSelectGeneralId);
                DYNAMIC_ASSERT(pItem);
                if (pItem->getItemType() != ITEM_TYPE_EQUIP_GENERAL)
                    return;
                if ( pItem->getItemEquipSlotType() != pSendInfo->index )
                    return;
            }
            sendBagChangePos(sendIndex, (recvIndex+(mCurClanBagPage-1)*UI_GOODS_ITEM_NUM), ITEM_SITE_TYPE_CHARACTER_EQUIP,ITEM_SITE_TYPE_CLAN, mSelectGeneralId);
        }
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::clearGenrealInfo()
    {
       clearSkillList();
       clearCharEquipList();
       clearCharItemList();
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::checkSpecialOperate( IconInfo* pSendInfo )
    {
        if ( UIItemShop::getInstance().getLayout()->isMouseInUI() )
        {
            UInt shopId =  UIItemShop::getInstance().getShopId();
            if ( shopId == 0 )
                return;

            ShopPacketProcesser::getInstance().sendShopSellItem(shopId, pSendInfo->dbID);
        }
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::clearClanInfo()
    {
        clearClanBagItemList();
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::restore()
    {
		Char8 msg[32] = "";
		IButton* pButton = NULL;
		IWidget* pWidget = NULL;
		for (Int i=1; i<UI_CLAN_INFO_TYPE_MAX-1; i++)
		{
			Sprintf_s(msg, 32, "button%d", i);
			pButton = getLayout()->getButton(msg);
			pButton->setStateCheck(false);

			//ѡ�е�bg��ʾ��
			Sprintf_s(msg, 32, "bg%d", i);
			pWidget = getLayout()->getWidget(msg);
			pWidget->setVisible(false);
		}

		for (Int i=1; i<UI_CLAN_BAG_NUM; i++)
		{
			Sprintf_s(msg, 32, "House-%d", i);
			pButton = getLayout()->getButton(msg);
			pButton->setStateCheck(false);
		}
		
		mTotalGenralPage = 1;
		mCurGenrealPage = 1;
		mCurClanBagPage = 1;
		mSelectClanInfoType = UI_CLAN_INFO_TYPE_NULL;
		mSelectGeneralId = 0;
		mSplitItemInfo = NULL;
		mSplitCount = 0;
		mOnTipsItemDBId = 0;
		mOnHighSelectItemDBId = 0;
		mDragOperate = OPERATE_DRAG_NILL;
        clearGenrealInfo();
        clearClanInfo();
		clearAllGenrealList();
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::addPlayerCharacter( CPlayerCharacter* pChar )
    {
		IMixListRow* pMixListRow = NULL;
		IMixList* pMixList = getLayout()->getMixList("grMixlist");
		DYNAMIC_ASSERT(pMixList);

        //pList->addItem(pChar->getNormalName(), pChar->getID());
		pMixListRow = pMixList->addLine(pChar->getID(), pChar->getNormalName());

		//��������
		pMixListRow->getChildWidget(1)->setCaption(pChar->getNormalName());
		pMixListRow->getWidget()->setUserData(pChar->getID());
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::delPlayerCharacter( CPlayerCharacter* pChar )
    {
        IList* pList = getLayout()->getList("grMixlist");
        DYNAMIC_ASSERT(pList);

        pList->removeItemAt( pList->findItemIndexWith(pChar->getNormalName()) );

        if ( pChar->getID() == mSelectGeneralId )
        {
            if ( pList->getItemCount() > 1 )
            {
                IAny* pAny = pList->getItemDataAt(0);
                IdType* id = pAny->castType<IdType>();

                mSelectGeneralId = *id;
            }
            else
                mSelectGeneralId = 0;

            //�����佫��Ϣ��
        }
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::updatePlayerCharacter( CPlayerCharacter* pChar )
    {
        if ( pChar->getID() == mSelectGeneralId )
        {
            //�����佫��Ϣ��
        }
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::initPlayerCharacterList()
    {
        CClan* pClan = CPlayer::getInstance().getActiveClan();
        DYNAMIC_ASSERT(pClan);

		IMixListRow* pMixListRow = NULL;
        IMixList* pMixList = getLayout()->getMixList("grMixlist");
        DYNAMIC_ASSERT(pMixList);

        std::map<IdType, CPlayerCharacter*>* pMapCPlayerCharacterList = pClan->getPlayerCharacterList();
        std::map<IdType, CPlayerCharacter*>::iterator front = pMapCPlayerCharacterList->begin();
        std::map<IdType, CPlayerCharacter*>::iterator back = pMapCPlayerCharacterList->end();
        while (front != back)
        {
			IMixListRow* pMixListRow = pMixList->addLine(front->second->getID(), front->second->getNormalName());

			//��������
			pMixListRow->getChildWidget(1)->setCaption(front->second->getNormalName());
			pMixListRow->getWidget()->setUserData(front->second->getID());

			//����״̬
			//����״̬����ͼƬ��

            if ( mSelectGeneralId == 0 )
			{    
				mSelectGeneralId = front->second->getID();
				pMixList->setSelectIndex(0);

			}

            ++front;
        }
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::updatePlayerCharacterInfo()
    {
        if ( mSelectGeneralId == 0 )
        {
            clearGenrealInfo();
        }
        else
        {
            ;
        }
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::updateBgByClanInfoType( UI_CLAN_INFO_TYPE type )
    {
        switch (type)
        {
        case UI_CLAN_INFO_TYPE_INFO:
            openClanInfoBg();
            break;
        case UI_CLAN_INFO_TYPE_GOODS:
            openClanGoodsBg();
            break;
        case UI_CLAN_INFO_TYPE_EQUIP:
            openClanEquipBg();
            break;
        case UI_CLAN_INFO_TYPE_ARMY:
            openClanArmyBg();
            break;
        default:
            DYNAMIC_ASSERT(0);
            break;
        }
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::openClanGoodsBg()
    {
		updateMoney();
		//if ( mCurClanBagPage == 0 )
		//{
		//	onHandleCutClanBag(1);
		//}   
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::openClanInfoBg()
    {
		IImage* pImage = NULL;
		IWidget* pWidget = NULL;
		CClan* pClan = CPlayer::getInstance().getActiveClan();
		Char16 tempMsg[32] = L"";

		//����
		pWidget = getLayout()->getWidget("region");
		pWidget->setCaption(pClan->getData()->clanHomeLandName);

		//������
		pWidget = getLayout()->getWidget("clanname");
		pWidget->setCaption(pClan->getData()->clanName);

		//�峤
		pWidget = getLayout()->getWidget("shaikh");
		pWidget->setCaption(pClan->getMainGenreal()->getNormalName());

		//��ʦ
		//pWidget = getLayout()->getWidget("advisor");
		//pWidget->setCaption(pClan->getData()->clanName);

		//��������
		pWidget = getLayout()->getWidget("genrealnum");
		swprintf_s(tempMsg, 32, L"%d", pClan->getPlayerCharacterNum());
		pWidget->setCaption(tempMsg);

		//���ڳ���
		//pWidget = getLayout()->getWidget("clancity");
		//pWidget->setCaption(pClan->getData()->clanName);

		//��������
		//pWidget = getLayout()->getWidget("claninfluence");
		//pWidget->setCaption(pClan->getData()->clanName);

		//�����λ
		//pWidget = getLayout()->getWidget("clanpeerage");
		//pWidget->setCaption(pClan->getData()->clanName);

		//���幦ѫ
		//pWidget = getLayout()->getWidget("clanexploit");
		//pWidget->setCaption(pClan->getData()->clanName);

		//����ȼ�
		//pWidget = getLayout()->getWidget("clanlevel");
		//pWidget->setCaption(pClan->getData()->clanName);

		//���徭��
		//pWidget = getLayout()->getWidget("clanexp");
		//pWidget->setCaption(pClan->getData()->clanName);

		//��������
		//pWidget = getLayout()->getWidget("clanprestige");
		//pWidget->setCaption(pClan->getData()->clanName);
		

    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::openClanEquipBg()
    {
		onHandleSelectGenreal(mSelectGeneralId);  
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::openClanArmyBg()
    {

    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::onDoubleClickGenrealItem( void* widget )
    {
        IWidget* pIWidget = (IWidget*)widget;
        IAny* pIAny = pIWidget->getUserData();
        IconInfo* pIconInfo = pIAny->castType<IconInfo>();
		DYNAMIC_ASSERT(pIconInfo);

		if ( pIconInfo->dbID )
		{	
			//���CDͼƬ�Ƿ���ת��
			Char8 tempChar[32] = "";
			Sprintf_s(tempChar, 32, "grcd%d", pIconInfo->index);
			IWidget* pCDWidget = pIWidget->findWidget(tempChar);
			if ( pCDWidget->getImage()->getImageBroadcast() != MGIMAGE_BROADCAST_TYPE_NULL )
				return;
			UIClanInfo::getInstance().onHandleDoubleClickGenrealItem(pIconInfo);
		}
    }
    //--------------------------------------------------------------------------------------
    void UIClanInfo::onHandleDoubleClickGenrealItem( IconInfo* pIconInfo )
    {
		//����ڴ�CD�Ƿ���ת��
		const ItemInfo* pInfo = ItemTemplate::getInstance().getItemInfo(pIconInfo->tempID);
		if ( CCDManager::getInstance().checkCD(CD_MASTER_TYPE_CHARACTER, mSelectGeneralId, pInfo->getItemUsePublicTimepieceId()) )
			return;
		if ( CCDManager::getInstance().checkCD(CD_MASTER_TYPE_CHARACTER, mSelectGeneralId, pInfo->getItemUseOwnerTimepieceId()) )
			return;
		//������Ϣ
		ItemPacketProcesser::getInstance().sendUseItem(pIconInfo->dbID, mSelectGeneralId);
		//addCD
		CCDManager::getInstance().addCD(
			CD_MASTER_TYPE_CHARACTER, 
			mSelectGeneralId, 
			pInfo->getItemUsePublicTimepieceId(),
			pInfo->getItemUsePublicTimepieceDelay(),
			pInfo->getItemUsePublicTimepieceDelay()
			);
    }
	//--------------------------------------------------------------------------------------
	void UIClanInfo::addCharSkill( const SkillInfo* skillinfo, Bool isInitiative, U32 num )
	{
		IImage* pImage = NULL;
		Char8 tempStr[32] = "";
		IconInfo* pIconInfo = NULL;
		const ArtIconResCsvInfo* pIconArtResInfo = NULL;

		if ( isInitiative )
		{
			Sprintf_s(tempStr, 32, "skillIcon-%d", num);
			pImage = getLayout()->getImage(tempStr);
			pIconInfo = pImage->getWidget()->getUserData()->castType<IconInfo>();
			DYNAMIC_ASSERT(pIconInfo);
			pIconArtResInfo = ArtIconResCsv::getInstance().getIconArtResInfo(skillinfo->skillInfo->artIconId);
			DYNAMIC_ASSERT(pIconArtResInfo);
			//�������
			pIconInfo->tempID = skillinfo->skillId;
			pIconInfo->resouceName = pIconArtResInfo->ResName;
			pIconInfo->groupName = pIconArtResInfo->GroupName;
			pIconInfo->itemName = pIconArtResInfo->ItemName;
			//������Ϣ����ͼƬ
			pImage->setTexture(pIconInfo->resouceName, pIconInfo->groupName, pIconInfo->itemName);
			pImage->getWidget()->setUserData(*pIconInfo);
		}
		else
		{
			Sprintf_s(tempStr, 32, "passive_skillIcon-%d", num);
			pImage = getLayout()->getImage(tempStr);
			pIconInfo = pImage->getWidget()->getUserData()->castType<IconInfo>();
			DYNAMIC_ASSERT(pIconInfo);
			pIconArtResInfo = ArtIconResCsv::getInstance().getIconArtResInfo(skillinfo->skillInfo->artIconId);
			DYNAMIC_ASSERT(pIconArtResInfo);
			//�������
			pIconInfo->tempID = skillinfo->skillId;
			pIconInfo->resouceName = pIconArtResInfo->ResName;
			pIconInfo->groupName = pIconArtResInfo->GroupName;
			pIconInfo->itemName = pIconArtResInfo->ItemName;
			//������Ϣ����ͼƬ
			pImage->setTexture(pIconInfo->resouceName, pIconInfo->groupName, pIconInfo->itemName);
			pImage->getWidget()->setUserData(*pIconInfo);
		}
	}
	//--------------------------------------------------------------------------------------
	void UIClanInfo::notifyUIAddCD( U32 cdId, U32 cdtime, U32 totalTime, PlayerCharacterIdType characterId /*= 0 */ )
	{
		if ( isOpen()  &&  characterId == mSelectGeneralId )
		{   
			Char8 tempStr[32] = "";
			IImage* pImage = NULL;
			IWidget* pWidget = NULL;
			IWidget* pChildWidget = NULL;
			IconInfo* pIconInfo = NULL;
			const SkillInfo* pSkillInfo = NULL;
			const ItemInfo* pItemInfo = NULL;
			//���ߡ�
			for (Int i=1; i<=UI_GENREAL_ITEM_NUM; i++)
			{
				Sprintf_s(tempStr, 32, "gritem_icon%d", i);
				pWidget = getLayout()->getWidget(tempStr);

				//���icon��Ϣ
				pIconInfo = pWidget->getUserData()->castType<IconInfo>();
				DYNAMIC_ASSERT(pIconInfo);
				if ( pIconInfo->tempID == 0 )
					continue;
				//��õ���id
				pItemInfo = ItemTemplate::getInstance().getItemInfo(pIconInfo->tempID);
				DYNAMIC_ASSERT(pItemInfo);
				if ( pItemInfo->getItemBaseItemType() == ITEM_TYPE_USE_GENERAL )
				{
					Sprintf_s(tempStr, 32, "grcd%d", i);
					pChildWidget = pWidget->findWidget(tempStr);
					if ( pItemInfo->getItemUseOwnerTimepieceId() == cdId )
					{	
						pChildWidget->getImage()->setImageBroadcast(MGIMAGE_BROADCAST_TYPE_ONCE, cdtime, totalTime);
					}
					if ( pItemInfo->getItemUsePublicTimepieceId() == cdId )
					{	
						if ( pChildWidget->getImage()->getImageBroadcast() == MGIMAGE_BROADCAST_TYPE_NULL )
							pChildWidget->getImage()->setImageBroadcast(MGIMAGE_BROADCAST_TYPE_ONCE, cdtime, totalTime);
					}
				}
			}
			//����
			//�߻����λΪ�ٺ���
			cdtime = cdtime;
			totalTime = totalTime;
			for (Int i=1; i<=UI_GENREAL_SKILL_NUM; i++)
			{
				Sprintf_s(tempStr, 32, "skillIcon-%d", i);
				pWidget = getLayout()->getWidget(tempStr);
				//���icon��Ϣ
				pIconInfo = pWidget->getUserData()->castType<IconInfo>();
				DYNAMIC_ASSERT(pIconInfo);
				if ( pIconInfo->tempID == 0 )
					continue;
				//��ü���xx
				pSkillInfo = SkillInfoList::getInstance().getSkillInfo(pIconInfo->tempID);
				DYNAMIC_ASSERT(pSkillInfo);
				InitiativeSkillBasicInfo* pInitiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)(pSkillInfo->skillInfo);
				Sprintf_s(tempStr, 32, "skillState-%d", i);
				pChildWidget = pWidget->findWidget(tempStr);
				//��CD
				
				if ( pInitiativeSkillBasicInfo->ownerTimepieceId == cdId )
				{	
					pChildWidget->getImage()->setImageBroadcast(MGIMAGE_BROADCAST_TYPE_ONCE, cdtime, totalTime);
				}
				if ( pInitiativeSkillBasicInfo->publicTimepieceId == cdId )
				{	
					if ( pChildWidget->getImage()->getImageBroadcast() == MGIMAGE_BROADCAST_TYPE_NULL )
						pChildWidget->getImage()->setImageBroadcast(MGIMAGE_BROADCAST_TYPE_ONCE, cdtime, totalTime);
				}
			}
		}
	}
	//--------------------------------------------------------------------------------------
	void UIClanInfo::notifyUIDeleteCD( U32 cdId, PlayerCharacterIdType characterId /*= 0 */ )
	{
		if ( isOpen()  &&  characterId == mSelectGeneralId )
		{
			Char8 tempStr[32] = "";
			IImage* pImage = NULL;
			IWidget* pWidget = NULL;
			IWidget* pChildWidget = NULL;
			IconInfo* pIconInfo = NULL;
			const SkillInfo* pSkillInfo = NULL;
			const ItemInfo* pItemInfo = NULL;
			//���ߡ�
			for (Int i=1; i<=UI_GENREAL_ITEM_NUM; i++)
			{
				Sprintf_s(tempStr, 32, "gritem_icon%d", i);
				pWidget = getLayout()->getWidget(tempStr);

				//���icon��Ϣ
				pIconInfo = pWidget->getUserData()->castType<IconInfo>();
				DYNAMIC_ASSERT(pIconInfo);
				//��õ���id
				pItemInfo = ItemTemplate::getInstance().getItemInfo(pIconInfo->tempID);
				DYNAMIC_ASSERT(pItemInfo);
				//ɾ��CD
				if ( pItemInfo->getItemBaseItemType() == ITEM_TYPE_USE_GENERAL )
				{
					Sprintf_s(tempStr, 32, "grcd%d", i);
					pChildWidget = pWidget->findWidget(tempStr);
					if ( pItemInfo->getItemUseOwnerTimepieceId() == cdId )
						pChildWidget->getImage()->setImageBroadcast(MGIMAGE_BROADCAST_TYPE_NULL, 0, 0);
				}
			}
			//����
			for (Int i=1; i<=UI_GENREAL_SKILL_NUM; i++)
			{
				Sprintf_s(tempStr, 32, "skillIcon-%d", i);
				pWidget = getLayout()->getWidget(tempStr);
				//���icon��Ϣ
				pIconInfo = pWidget->getUserData()->castType<IconInfo>();
				DYNAMIC_ASSERT(pIconInfo);
				//��ü���xx
				pSkillInfo = SkillInfoList::getInstance().getSkillInfo(pIconInfo->tempID);
				DYNAMIC_ASSERT(pSkillInfo);
				InitiativeSkillBasicInfo* pInitiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)(pSkillInfo->skillInfo);
				Sprintf_s(tempStr, 32, "skillState-%d", i);
				pChildWidget = pWidget->findWidget(tempStr);
				//ɾ��CD
				if ( pInitiativeSkillBasicInfo->ownerTimepieceId == cdId )
				{	
					pChildWidget->getImage()->setImageBroadcast(MGIMAGE_BROADCAST_TYPE_NULL, 0, 0);
				}
			}
		}
	}
	//--------------------------------------------------------------------------------------
	void UIClanInfo::updateItemCD()
	{
		if ( isOpen() == false )
			return;

		const CDTimer* pCDTimer = NULL;	

		//City
		pCDTimer = CCDManager::getInstance().getCityCDTimer();
		updateItemCDByCDTimer(pCDTimer);
		//Force
		pCDTimer = CCDManager::getInstance().getForceCDTimer();
		updateItemCDByCDTimer(pCDTimer);
		//Clan
		pCDTimer = CCDManager::getInstance().getClanCDTimer();
		updateItemCDByCDTimer(pCDTimer);
		//Genreal	
		pCDTimer = CCDManager::getInstance().getGenrealCDTimer(mSelectGeneralId);
		if ( pCDTimer )
			updateItemCDByCDTimer(pCDTimer);
	}
	//--------------------------------------------------------------------------------------	
	void UIClanInfo::updateItemCDByCDTimer( const CDTimer* pCDTimer )
	{
		const std::map<U32, CDTimerData*>* pMapCDTimerData = NULL;
		CDTimerData* pCDTimerData = NULL;

		pMapCDTimerData = pCDTimer->getAllCDTimeData();
		std::map<U32, CDTimerData*>::const_iterator front = pMapCDTimerData->begin();
		std::map<U32, CDTimerData*>::const_iterator back = pMapCDTimerData->end();
		while (front != back)
		{
			pCDTimerData = front->second;
			if ( pCDTimerData->mLastTime + pCDTimerData->mStartTime  >  MGTimeOp::getCurrTick() )
			{	
				notifyUIAddCD(
					pCDTimerData->mCdtempInfo->TimepieceId 
					,pCDTimerData->mLastTime + pCDTimerData->mStartTime - MGTimeOp::getCurrTick()
					,pCDTimerData->mTotalTime
					,mSelectGeneralId
					);
			}
			++front;
		}
	}
	//--------------------------------------------------------------------------------------
	void UIClanInfo::addCharSkillList( CPlayerCharacter* pCPlayerCharacter )
	{
		Int passivityNum = 1;		//����
		Int initiativeNum = 1;		//����
		if (pCPlayerCharacter == NULL)
		{
			pCPlayerCharacter = CPlayer::getInstance().getMainGenreal();
		}
		CSkillOwnManager* skillOwnManager = pCPlayerCharacter->getSkillOwnManager();
		if(!skillOwnManager)
		{
			return;
		}

		IdType skillId = 0;
		for(UInt i = 0; i < skillOwnManager->getOwnSkillNum(); ++i)
		{
			skillId = skillOwnManager->getOwnerSkillByIndex(i);
			if(skillId == 0)
			{	
				continue;
			}

			const SkillInfo* tempSkillInfo = SkillInfoList::getInstance().getSkillInfo(skillId);
			if ( tempSkillInfo->skillShowType == SKILL_SHOW_TYPE_ONE )
				addCharSkill(tempSkillInfo, true, passivityNum++);
			else
				addCharSkill(tempSkillInfo, false, initiativeNum++);
		}
	}
	//--------------------------------------------------------------------------------------
	void UIClanInfo::onHandleDrag( IWidget* pImage )
	{
		
		if( ClientMain::getInstance().getEngine()->input()->isMouseHolded(MB_Left))
		{
			IAny* pAny = pImage->getUserData();
			DYNAMIC_ASSERT(pAny);
			IconInfo* pInfo = pAny->castType<IconInfo>();
			DYNAMIC_ASSERT(pInfo);
			IPointer* pPointer = ClientMain::getInstance().getPointer();
			IAny* pSendAny = pPointer->getAnyData();

			if ( pSendAny )
			{
				IconInfo* pSendInfo = pSendAny->castType<IconInfo>();
				//�滻
				if ( pSendInfo->dbID != pInfo->dbID )
				{
					//ֻ�п�����Ʒ�����ܷŵ���ɫ������
					if (pInfo->group == ICON_GROUP_CHARACTER_BAG)
					{
						const ItemInfo* pItemInfo = ItemTemplate::getInstance().getItemInfo(pSendInfo->tempID);
						DYNAMIC_ASSERT(pItemInfo);
						if (pItemInfo->getItemUseInfo())
						{
							UIClanInfo::getInstance().onHandleDrop(pSendInfo, pInfo);
						}
					}
					else
						UIClanInfo::getInstance().onHandleDrop(pSendInfo, pInfo);
				}
				pPointer->resetToDefaultPointer();
				mDragOperate = OPERATE_DRAG_NILL;
				//pPointer->setImage("", "", "", NULL);
			}
			else if ( pInfo->tempID )
			{
				IconInfo tempInfo;
				tempInfo.copy(*pInfo);
				//����Ǳ�������indexҪ���¼���
				if ( tempInfo.group == ICON_GROUP_CLAN_BAG )
				{
					tempInfo.index += (mCurClanBagPage-1)*UI_GOODS_ITEM_NUM;
				}
				pPointer->setImage(pInfo->resouceName, pInfo->groupName, pInfo->itemName, tempInfo);
				mDragOperate = OPREATE__ITEM_CHANGEPOS;
			}
		}
	}
	//--------------------------------------------------------------------------------------
	void UIClanInfo::setHighVisble(  ICON_GROUP type, Int Index, Bool isVisble )
	{
		IWidget* pWidget = NULL;
		IWidget* pHighWidget = NULL;
		Char8 tempChar[32] = "";

		//�������ͻ�ÿؼ�
		switch ( type )
		{
		case ICON_GROUP_CLAN_BAG:
			{
				Sprintf_s(tempChar, 32, "gsiconbg%d", Index);
				pWidget = getLayout()->getWidget(tempChar);
				pHighWidget = getLayout()->getWidget("baghigh");
			}
			break;
		case ICON_GROUP_CHARACTER_BAG:
			{
				Sprintf_s(tempChar, 32, "gruse%d", Index);
				pWidget = getLayout()->getWidget(tempChar);
				pHighWidget = getLayout()->getWidget("charitemhigh");
			}
			break;
		case ICON_GROUP_CHARACTER_EQUIP:
			{
				Sprintf_s(tempChar, 32, "grequipbg%d", Index);
				pWidget = getLayout()->getWidget(tempChar);
				pHighWidget = getLayout()->getWidget("charitemhigh");
			}
			break;
		case ICON_GROUP_CHARACTER_SKILL:
			{
				Sprintf_s(tempChar, 32, "skill_bg-%d", Index);
				pWidget = getLayout()->getWidget(tempChar);
				pHighWidget = getLayout()->getWidget("skillhigh");
			}
			break;
		case ICON_GROUP_CHARACTER_LIFESKILL:
			{
				Sprintf_s(tempChar, 32, "passive_skill_bg%d", Index);
				pWidget = getLayout()->getWidget(tempChar);
				pHighWidget = getLayout()->getWidget("skillhigh");
			}
			break;
		default:
			DYNAMIC_ASSERT(0);
			break;
		}

		//���ø���
		if ( isVisble )
		{
			pHighWidget->setPosition( pWidget->getPosition());
			pHighWidget->setVisible(true);
		}
		else
		{
			pHighWidget->setVisible(false);
		}
	}
	//--------------------------------------------------------------------------------------
	void UIClanInfo::onGetMouseFocusEvent( void* pGetWidget, void* pLostWidget )
	{
		IconInfo* pGetInfo = ((IWidget*)pGetWidget)->getUserData()->castType<IconInfo>();
		DYNAMIC_ASSERT(pGetInfo);
		if ( pGetInfo->tempID )
		{
			UIClanInfo::getInstance().setHighVisble(pGetInfo->group, pGetInfo->index, true);
			UIClanInfo::getInstance().mOnHighSelectItemDBId = pGetInfo->dbID;
		}
	}
	//--------------------------------------------------------------------------------------
	void UIClanInfo::onLostMouseFocusEvent( void* pLostWidget, void* pGetWidget )
	{
		IconInfo* pLostInfo = ((IWidget*)pLostWidget)->getUserData()->castType<IconInfo>();
		DYNAMIC_ASSERT(pLostInfo);
		if ( pLostInfo->tempID )
		{
			UIClanInfo::getInstance().setHighVisble(pLostInfo->group, pLostInfo->index, false);
			UIClanInfo::getInstance().mOnHighSelectItemDBId = 0;
		}
	}
	//--------------------------------------------------------------------------------------
	void UIClanInfo::clearAllGenrealList()
	{
		IMixList* pMixList = getLayout()->getMixList("grMixlist");
		DYNAMIC_ASSERT(pMixList);
		pMixList->removeAllLine();
	}
	//--------------------------------------------------------------------------------------
	void UIClanInfo::updateBasicAttr()
	{
		if (isOpen() == false)
			return;
		CPlayerCharacter* pChar = CPlayer::getInstance().getActiveClan()->getPlayerCharacter(mSelectGeneralId);
		DYNAMIC_ASSERT(pChar);

		
		IWidget* pWidget = NULL;
		Char16 tempMsg2[32] = L"";
		//��ɫ����
		pWidget = getLayout()->getWidget("power");
		swprintf_s(tempMsg2, 32, L"%d", (int)(pChar->getAttributeSet()->getFanalValue(ATTR_ID_Talent1)) );
		pWidget->setCaption( tempMsg2 );

		//��ɫͳ˧
		pWidget = getLayout()->getWidget("technique");
		swprintf_s(tempMsg2, 32, L"%d", (int)(pChar->getAttributeSet()->getFanalValue(ATTR_ID_Talent2)) );
		pWidget->setCaption( tempMsg2 );

		//��ɫ��ı
		pWidget = getLayout()->getWidget("resourcefulness");
		swprintf_s(tempMsg2, 32, L"%d", (int)(pChar->getAttributeSet()->getFanalValue(ATTR_ID_Talent3)) );
		pWidget->setCaption( tempMsg2 );

		//��ɫ����
		pWidget = getLayout()->getWidget("affair");
		swprintf_s(tempMsg2, 32, L"%d", (int)(pChar->getAttributeSet()->getFanalValue(ATTR_ID_Talent4)) );
		pWidget->setCaption( tempMsg2 );

	}
	//--------------------------------------------------------------------------------------
	void UIClanInfo::updateMoney()
	{
		if (mSelectClanInfoType == UI_CLAN_INFO_TYPE_GOODS)
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
}