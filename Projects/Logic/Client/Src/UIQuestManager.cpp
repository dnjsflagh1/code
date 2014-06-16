//***************************************************************************************************
#include "stdafx.h"
#include "UIQuestManager.h"
#include "CClanQuestManager.h"
#include "QuestList.h"
#include "QuestText.h"
#include "ClanQuestInfoBase.h"
#include "IMixList.h"
#include "IMixListRow.h"
#include "ItemTemplate.h"
#include "ItemGroupTemplate.h"
#include "ItemMoneyTemplate.h"
#include "UIItemTips.h"
#include "ItemExpListCsv.h"
#include "UIYesNoMsgBox.h"
#include "UIMessageBox.h"
#include "ClientMain.h"
//***************************************************************************************************
namespace MG
{
    UIQuestManager::UIQuestManager()
    {
		mSelectQuestInfoId = -1;
    }
    //----------------------------------------------------------------------------------------
    UIQuestManager::~UIQuestManager()
    {

    }
	//----------------------------------------------------------------------------------------
	Bool UIQuestManager::openGui()
	{
		if (  false == UIObject::isOpen() )
		{
			UIObject::openGui();

			InitUI();

			return true;
		}
		return false;
	}
	//----------------------------------------------------------------------------------------
	void UIQuestManager::InitUI()
	{
		IWidget* pWidget = NULL;
		pWidget = getLayout()->getWidget("quest_info");
		DYNAMIC_ASSERT(pWidget);

		IMixList* iMixList = getLayout()->getMixList("list_quests");
		DYNAMIC_ASSERT(iMixList);
		
		Int listCount = iMixList->getMixLixRowCount();
		if (listCount > 0)
		{
			//没有选择显示哪个，默认显示第一个任务
			pWidget->setVisible(true);	
			if (mSelectQuestInfoId != -1)
			{
				_setQuestInfo(mSelectQuestInfoId);
			}
			else
			{
				IMixListRow* mixRow = NULL;
				mixRow = iMixList->getMixListRowByIndex(0);
				if (mixRow)
				{
					Int showQuestId = mixRow->getId();
					if (showQuestId != -1)
					{
						_setQuestInfo(showQuestId);
						iMixList->setSelectIndex(0);
					}
				}
			}
		}
		else
		{
			//任务列表没有任何任务，隐藏任务信息界面
			pWidget->setVisible(false);	
		}
	}
    //----------------------------------------------------------------------------------------
    void UIQuestManager::setEvent()
    {
		IForm* mainForm = getLayout()->getForm("_Main");
		mainForm->setWindowButtonPressedEvent(onClickCloseBtn);

		IMixList* iMixList = getLayout()->getMixList("list_quests");
		iMixList->setClickMixListRow(onSelectRow);

		IButton* btn = getLayout()->getButton("drop_btn");
		DYNAMIC_ASSERT(btn);
		btn->getWidget()->setMouseButtonClickEvent(onClickGiveUpBtn);
    }
	//----------------------------------------------------------------------------------------
	void UIQuestManager::onClickCloseBtn(void* widget)
	{
		UIQuestManager::getInstance().closeGui();
	}
	//----------------------------------------------------------------------------------------
	void UIQuestManager::onClickGiveUpBtn(void* widget)
	{
		if (UIQuestManager::getInstance().mSelectQuestInfoId != -1)
		{
			//确定放弃任务提示
			Str16 hintStr; 
			 CClanQuestManager::getInstance().showQuestHintStr(UIQuestManager::getInstance().mSelectQuestInfoId, hintStr);
			static Char16 str[64] = {0};

			MGStrOp::sprintf(str,64,L"确定要放弃【%s】任务",hintStr.c_str());
			UIYesNoMsgBox::getInstance().showHint(L"放弃任务提示",str,
				(void*)(&UIQuestManager::getInstance()),onSureGiveupQuest,NULL, NULL);
			
		}
		else
		{
			UIMessageBox::getInstance().showHint(L"没有选中的任务，请先选择一个任务！");
		}
	}
	//----------------------------------------------------------------------------------------
	void UIQuestManager::onSureGiveupQuest(void* arg)
	{
		CClanQuestManager::getInstance().giveupClanQuest(UIQuestManager::getInstance().mSelectQuestInfoId);
	}
	//----------------------------------------------------------------------------------------
	void UIQuestManager::onClickCheckBtn( void* widget)
	{
		DYNAMIC_ASSERT(widget);
		IWidget* iWidget = (IWidget*)widget;
		IAny* anyData = iWidget->getUserData();
		Int* index = anyData->castType<Int>();
		IButton* checkBox = iWidget->getButton();
		Bool check = checkBox->getStateCheck();
		checkBox->setStateCheck(!check);
	}
	void UIQuestManager::onSelectRow( void* widget,Int index  )
	{
		DYNAMIC_ASSERT(widget);
		IMixList* mixList = (IMixList*)widget;
		IMixListRow* row = mixList->getMixListRowByIndex(index);
		U32 questInfoId = row->getId();
		if (questInfoId != -1)
		{
			UIQuestManager::getInstance()._setQuestInfo(questInfoId);
		}
	}

	void UIQuestManager::addQuest( ClanQuestObject* questObj )
	{
		DYNAMIC_ASSERT(questObj);
		IMixList* iMixList = getLayout()->getMixList("list_quests");
		QuestTextInfo* textInfo = questObj->mInfo->questInfo->getTextInfo();
		DYNAMIC_ASSERT(textInfo);
		Str16 temp;
		

		IMixListRow* mixRow = NULL;
		Bool isNewLine = false;
		if (textInfo->nameAdd == L"" || textInfo->nameAdd.empty() || textInfo->nameAdd.compare(L"0") == 0)
		{
			temp = textInfo->name;
		}
		else
		{
			temp = textInfo->name + L"("+ textInfo->nameAdd +L")";
		}

		mixRow = iMixList->getMixListRow(temp);
		if (!mixRow)
		{
			//添加一条任务新记录
			mixRow = iMixList->addLine(questObj->mInfo->id,temp);
			mixRow->getChildWidget(1)->setCaption(temp);
			isNewLine = true;
		}
	
		DYNAMIC_ASSERT(mixRow);
		if (isNewLine)
		{
			//添加一条任务新记录 
			IButton* checkBox = mixRow->getButton(0);
			DYNAMIC_ASSERT(checkBox);
			checkBox->getWidget()->setUserData(questObj->mInfo->id);
			checkBox->getWidget()->setMouseButtonClickEvent(onClickCheckBtn);
			mixRow->getWidget()->setUserData(questObj->mInfo->id);
			//IImage* img = mixRow->getImage(2);
			//DYNAMIC_ASSERT(img);
		}
		else
		{
			//如果任务列表选中的跟要增加的同个任务，刷新下任务进度
			Char16 tempBuf[64] = {0};
			IText *text;

			Int needValue0 = 0;
			needValue0 = questObj->mInfo->questInfo->getValue(true,0);
			if (needValue0 > 0)
			{
				MGStrOp::sprintf(tempBuf,64,L"%d",questObj->mRecord.value[0]);
				text = getLayout()->getText("recordCnt_1");
				DYNAMIC_ASSERT(text);
				text->getWidget()->setCaption(tempBuf);
			}

			Int needValue1 = 0;
			needValue1 = questObj->mInfo->questInfo->getValue(true,1);
			if (needValue1 > 0)
			{
				MGStrOp::sprintf(tempBuf,64,L"%d",questObj->mRecord.value[1]);
				text = getLayout()->getText("recordCnt_2");
				DYNAMIC_ASSERT(text);
				text->getWidget()->setCaption(tempBuf);
			}

			Int needValue2 = 0;
			needValue2 = questObj->mInfo->questInfo->getValue(true,2);
			if (needValue2 > 0)
			{
				MGStrOp::sprintf(tempBuf,64,L"%d",questObj->mRecord.value[2]);
				text = getLayout()->getText("recordCnt_3");
				DYNAMIC_ASSERT(text);
				text->getWidget()->setCaption(tempBuf);
			}

			Int needValue3 = 0;
			needValue3 = questObj->mInfo->questInfo->getValue(true,3);
			if (needValue3 > 0)
			{
				MGStrOp::sprintf(tempBuf,64,L"%d",questObj->mRecord.value[3]);
				text = getLayout()->getText("recordCnt_4");
				DYNAMIC_ASSERT(text);
				text->getWidget()->setCaption(tempBuf);
			}
		}
		//设置任务状态图标
		IImage* img = mixRow->getImage(2);
		DYNAMIC_ASSERT(img);
		if (questObj->mRecord.state == QUEST_COMPLETE_STATE_ACCEPTED)
		{
			//img->setItemGroup();
			//img->setItemGroup();
			//img->setItemGroup();
		}
		else if (questObj->mRecord.state == QUEST_COMPLETE_STATE_FINISHED)
		{

		}
		else if (questObj->mRecord.state == QUEST_COMPLETE_STATE_FAILED)
		{
			img->setTexture("Main_State_Task","shibai","2");
		}
		else if (questObj->mRecord.state == QUEST_COMPLETE_STATE_SUBMITED)
		{
			img->setTexture("Main_State_Task","yiwancheng","1");
		}
		
	}

	void UIQuestManager::_setQuestInfo( U32 questInfoId )
	{
	
		ClanQuestObject* questObj = CClanQuestManager::getInstance().getQuest(questInfoId);
		DYNAMIC_ASSERT(questObj);
		
		if (questInfoId != mSelectQuestInfoId)
		{
			_clearQuestInfo();
			_setAwardItemsUi(questObj);
			mSelectQuestInfoId = questInfoId;
		}
		else
			return;

		QuestTextInfo* textInfo = questObj->mInfo->questInfo->getTextInfo();
		IEdit* edit = getLayout()->getEdit("edit_quest_desc");
		DYNAMIC_ASSERT(edit);
		edit->clearEditText(false);
		Int width =  (static_cast<Int>(edit->getWidget()->getSize().x) - 30);
		Str16 temp= textInfo->desc;
		IGui* igui = ClientMain::getInstance().getGui();
		igui->getHeightStrAddBreak(temp,width);
		edit->addText(temp);
		
		IText* text = NULL;
		Int needValue0 = 0;
		needValue0 = questObj->mInfo->questInfo->getValue(true,0);
		if (needValue0 > 0)
		{
			text = getLayout()->getText("text_quest_situation1");
			DYNAMIC_ASSERT(text);
			text->getWidget()->setCaption(textInfo->valueText1);

			Char16 tempBuf[64] = {0};
			MGStrOp::sprintf(tempBuf,64,L"%d",questObj->mRecord.value[0]);
			text = getLayout()->getText("recordCnt_1");
			DYNAMIC_ASSERT(text);
			text->getWidget()->setCaption(tempBuf);

			MGStrOp::sprintf(tempBuf,64,L"%d",needValue0);
			text = getLayout()->getText("needCnt_1");
			DYNAMIC_ASSERT(text);
			text->getWidget()->setCaption(tempBuf);

			text = getLayout()->getText("s1");
			DYNAMIC_ASSERT(text);
			text->getWidget()->setVisible(true);
		}
		
		Int needValue1 = 0;
		needValue1 = questObj->mInfo->questInfo->getValue(true,1);
		if (needValue1 > 0)
		{
			text = getLayout()->getText("text_quest_situation2");
			DYNAMIC_ASSERT(text);
			text->getWidget()->setCaption(textInfo->valueText2);

			Char16 tempBuf[64] = {0};
			MGStrOp::sprintf(tempBuf,64,L"%d",questObj->mRecord.value[1]);
			text = getLayout()->getText("recordCnt_2");
			DYNAMIC_ASSERT(text);
			text->getWidget()->setCaption(tempBuf);

			MGStrOp::sprintf(tempBuf,64,L"%d",needValue1);
			text = getLayout()->getText("needCnt_2");
			DYNAMIC_ASSERT(text);
			text->getWidget()->setCaption(tempBuf);

			text = getLayout()->getText("s2");
			DYNAMIC_ASSERT(text);
			text->getWidget()->setVisible(true);
		}
	
		Int needValue2 = 0;
		needValue2 = questObj->mInfo->questInfo->getValue(true,2);
		if (needValue2 > 0)
		{
			text = getLayout()->getText("text_quest_situation3");
			DYNAMIC_ASSERT(text);
			text->getWidget()->setCaption(textInfo->valueText3);

			Char16 tempBuf[64] = {0};
			MGStrOp::sprintf(tempBuf,64,L"%d",questObj->mRecord.value[2]);
			text = getLayout()->getText("recordCnt_3");
			DYNAMIC_ASSERT(text);
			text->getWidget()->setCaption(tempBuf);

			MGStrOp::sprintf(tempBuf,64,L"%d",needValue2);
			text = getLayout()->getText("needCnt_3");
			DYNAMIC_ASSERT(text);
			text->getWidget()->setCaption(tempBuf);

			text = getLayout()->getText("s3");
			DYNAMIC_ASSERT(text);
			text->getWidget()->setVisible(true);
		}
		
		Int needValue3 = 0;
		needValue3 = questObj->mInfo->questInfo->getValue(true,3);
		if (needValue3 > 0)
		{
			text = getLayout()->getText("text_quest_situation4");
			DYNAMIC_ASSERT(text);
			text->getWidget()->setCaption(textInfo->valueText4);

			Char16 tempBuf[64] = {0};
			MGStrOp::sprintf(tempBuf,64,L"%d",questObj->mRecord.value[3]);
			text = getLayout()->getText("recordCnt_4");
			DYNAMIC_ASSERT(text);
			text->getWidget()->setCaption(tempBuf);

			MGStrOp::sprintf(tempBuf,64,L"%d",needValue3);
			text = getLayout()->getText("needCnt_4");
			DYNAMIC_ASSERT(text);
			text->getWidget()->setCaption(tempBuf);

			text = getLayout()->getText("s4");
			DYNAMIC_ASSERT(text);
			text->getWidget()->setVisible(true);
		}
	}
	//-------------------------------------------------------------------------------------------------------------
	void UIQuestManager::_clearAwardItemsUi()
	{
		IImage* pIcon = NULL;
		IText* pText = NULL;
		pText = getLayout()->getText("text_money_guan");
		DYNAMIC_ASSERT(pText);
		pText->getWidget()->setCaption(L"0");

		pText = getLayout()->getText("text_money_wen");
		DYNAMIC_ASSERT(pText);
		pText->getWidget()->setCaption(L"0");

		pText = getLayout()->getText("text_exp");
		DYNAMIC_ASSERT(pText);
		pText->getWidget()->setCaption(L"0");

        Char8 temStr[32] = {0};
        for (Int index = 1; index <= UIREWARD_ITEM_MAX_COUNT;index++)
        {
			/*SprintF(temStr,"gruse%d",index);
			pIcon =  getLayout()->getImage(temStr);
			DYNAMIC_ASSERT(pIcon);
			*/
			SprintF(temStr,"grtext%d",index);
			pText = getLayout()->getText(temStr);
			DYNAMIC_ASSERT(pText);
			pText->getWidget()->setCaption(L"");
        }
	}
	//-------------------------------------------------------------------------------------------------------------
	void UIQuestManager::_setAwardItemsUi(ClanQuestObject* questObj)
	{
		// 奖励信息
		std::vector<ItemNum>  rewardItems;
		ItemGroupTemplate::getInstance().getItemGroupInfo(questObj->mInfo->questInfo->getItemGroupId(),rewardItems);
		if (rewardItems.size() > 0)
		{   
			Int index = 1;
			IconInfo tempInfo;
			Char8 temStr[32] = {0};
			IImage* pIcon = NULL;
			IText*  pText = NULL;
			wstring itemSizeStr = L"";
			std::vector<ItemNum>::iterator itemIt = rewardItems.begin();
			for (;itemIt != rewardItems.end(); itemIt++)
			{   
				ItemNum& tempItemNum= (*itemIt); 
				const ItemInfo* pInfo = ItemTemplate::getInstance().getItemInfo(tempItemNum.itemTemplate); 
				if (pInfo)
				{
					if (pInfo->ItemType == ITEM_TYPE_MONEY)
					{
					 const ItemMoneyInfo* pItemMoneyInfo = pInfo->getItemMoneyInfo();
						 if (!pItemMoneyInfo)
						 {
							 continue;
						 }
						 if(pItemMoneyInfo->Class == ITEM_MONEY_CLASS_MONEY_GAME)
						 {
							 Int money_guan = (Int)(pItemMoneyInfo->Price/1000)*(tempItemNum.num);
							 Int money_wen =  (pItemMoneyInfo->Price%1000)*(tempItemNum.num);
							 wstring money_guan_str;
							 wstring money_wen_str;
							 MGStrOp::toString(money_guan,money_guan_str);
							 MGStrOp::toString(money_wen,money_wen_str);
							 IText* pText = NULL;
							 pText = getLayout()->getText("text_money_guan");
							 DYNAMIC_ASSERT(pText);
							 pText->getWidget()->setCaption(money_guan_str);

							 pText = getLayout()->getText("text_money_wen");
							 DYNAMIC_ASSERT(pText);
							 pText->getWidget()->setCaption(money_wen_str);

							 continue;

						 }
					}
					else if(pInfo->ItemType == ITEM_TYPE_EXP)
					{
						 const ItemExpListCsvInfo* pItemExpInfo = pInfo->getItemExpInfo();
						 if (NULL == pItemExpInfo)
						 {
							 continue;
						 }

						 Int exp = (pItemExpInfo->price)*(tempItemNum.num);
						 wstring exp_str;
						 MGStrOp::toString(exp,exp_str);
						 IText* pText = NULL;
						 pText = getLayout()->getText("text_exp");
						 DYNAMIC_ASSERT(pText);
						 pText->getWidget()->setCaption(exp_str);

						 continue;
					}

					//picon
					Str8 itemGroup;
					Str8 itemResource;
					Str8 itemName;
					pInfo->getItemBaseIconResouce(itemResource,itemGroup,itemName);
					tempInfo.group = ICON_GROUP_SHORTCUT_ITEM;
					tempInfo.type = ICON_TYPE_ITEM;
					tempInfo.index = index;
					tempInfo.tempID = tempItemNum.itemTemplate;
					SprintF(temStr,"gruse%d",index);
					pIcon =  getLayout()->getImage(temStr);
					DYNAMIC_ASSERT(pIcon);
					pIcon->setItemGroup(itemGroup);
					pIcon->setItemResource(itemResource);
					pIcon->setItemName(itemName);
					pIcon->getWidget()->setUserData(tempInfo);
					pIcon->getWidget()->setToolTipsEvent(onEventToolTips);

					MGStrOp::toString(tempItemNum.num,itemSizeStr);
					SprintF(temStr,"grtext%d",index);
					pText = getLayout()->getText(temStr);
					DYNAMIC_ASSERT(pText);
					pText->getWidget()->setCaption(itemSizeStr);

					index++;
				}
			}

		}
	}
	//-------------------------------------------------------------------------------------------------------------
	void UIQuestManager::removeQuest( U32 clanQuestInfoId )
	{
		IMixList* iMixList = getLayout()->getMixList("list_quests");
		DYNAMIC_ASSERT(iMixList);
		IMixListRow* mixRow = NULL;
		
		mixRow = iMixList->getMixListRow(clanQuestInfoId);
		if (mixRow)
		{
			iMixList->removeLine(clanQuestInfoId);
		}

		//移除当前选中项，默认显示第一个任务
		if (mSelectQuestInfoId == clanQuestInfoId)
		{
			mSelectQuestInfoId = -1;
			InitUI();
		}
		
	}
	//-------------------------------------------------------------------------------------------------------------
	void UIQuestManager::_clearQuestInfo()
	{ 
		IText* text = getLayout()->getText("edit_quest_desc");
		DYNAMIC_ASSERT(text);
		text->getWidget()->setCaption(L"");

		text = getLayout()->getText("text_quest_situation1");
		DYNAMIC_ASSERT(text);
		text->getWidget()->setCaption(L"");

		text = getLayout()->getText("text_quest_situation2");
		DYNAMIC_ASSERT(text);
		text->getWidget()->setCaption(L"");

		text = getLayout()->getText("text_quest_situation3");
		DYNAMIC_ASSERT(text);
		text->getWidget()->setCaption(L"");

		text = getLayout()->getText("text_quest_situation4");
		DYNAMIC_ASSERT(text);
		text->getWidget()->setCaption(L"");

		
		text = getLayout()->getText("recordCnt_1");
		DYNAMIC_ASSERT(text);
		text->getWidget()->setCaption(L"");
		
		text = getLayout()->getText("needCnt_1");
		DYNAMIC_ASSERT(text);
		text->getWidget()->setCaption(L"");

		text = getLayout()->getText("recordCnt_2");
		DYNAMIC_ASSERT(text);
		text->getWidget()->setCaption(L"");

		text = getLayout()->getText("needCnt_2");
		DYNAMIC_ASSERT(text);
		text->getWidget()->setCaption(L"");

		text = getLayout()->getText("recordCnt_3");
		DYNAMIC_ASSERT(text);
		text->getWidget()->setCaption(L"");

		text = getLayout()->getText("needCnt_3");
		DYNAMIC_ASSERT(text);
		text->getWidget()->setCaption(L"");

		text = getLayout()->getText("recordCnt_4");
		DYNAMIC_ASSERT(text);
		text->getWidget()->setCaption(L"");

		text = getLayout()->getText("needCnt_4");
		DYNAMIC_ASSERT(text);
		text->getWidget()->setCaption(L"");

		text = getLayout()->getText("s1");
		DYNAMIC_ASSERT(text);
		text->getWidget()->setVisible(false);

		text = getLayout()->getText("s2");
		DYNAMIC_ASSERT(text);
		text->getWidget()->setVisible(false);

		text = getLayout()->getText("s3");
		DYNAMIC_ASSERT(text);
		text->getWidget()->setVisible(false);

		text = getLayout()->getText("s4");
		DYNAMIC_ASSERT(text);
		text->getWidget()->setVisible(false);

		_clearAwardItemsUi();
	}

	//----------------------------------------------------------------------------------------
	void UIQuestManager::onEventToolTips( void* pWidget, Bool isShow, Int left, Int top )
	{
		DYNAMIC_ASSERT(pWidget);
		IWidget* pIcon = (IWidget*)pWidget;
		IAny* pAny = pIcon->getUserData();
		DYNAMIC_ASSERT(pAny);
		IconInfo* pInfo = pAny->castType<IconInfo>();
		DYNAMIC_ASSERT(pInfo);



		if(pInfo->tempID == 0)
		{
			return;
		}

		UIQuestManager::getInstance().onHandleTips(isShow,pInfo,pIcon->getAbsoluteCoord()); 
	}
	//----------------------------------------------------------------------------------------
	void UIQuestManager::onHandleTips( Bool isShow, IconInfo* pIconInfo, CoordI coord )
	{
		if ( isShow == false )
		{
			switch (pIconInfo->type)
			{
			case ICON_TYPE_ITEM:
				UIItemTips::getInstance().closeGui();
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
					const ItemInfo* pInfo = ItemTemplate::getInstance().getItemInfo(pIconInfo->tempID);
					DYNAMIC_ASSERT(pInfo);
					UIItemTips::getInstance().openItemTips(pInfo, coord);
				}
				break;
			default:    
				break;
			}
		}

	}
	//----------------------------------------------------------------------------------------
	void UIQuestManager::restore()
	{
		IMixList* iMixList = getLayout()->getMixList("list_quests");
		DYNAMIC_ASSERT(iMixList);
		iMixList->removeAllLine();
		_clearQuestInfo();
	}
}