//***************************************************************************************************
#include "stdafx.h"
#include "UINpc.h"
#include "NpcFuctionInfo.h"
#include "CPlayer.h"
#include "CharacterList.h"
#include "NpcFuctionInfo.h"
#include "ArtIconResCsv.h"
#include "Dialog.h"
#include "QuestNetPacketProcesser.h"
#include "QuestList.h"
#include "CClanQuestManager.h"
#include "QuestNormalList.h"
#include "QuestText.h"
#include "NpcFunctionObject.h"
#include "NpcClanQuestFunctionObject.h"
#include "NpcItemShopFunctionObject.h"
#include "NpcTalkFunctionObject.h"
#include "NpcGeneralRecruitFunctionObject.h"
#include "NpcChangeFightedGerneralFunctionObject.h"
#include "NpcPveDuplicateFunctionObject.h"
#include "NpcPvpBattleFuctionObject.h"
#include "PlayCharacterNetPacketProcesser.h"
#include "DialogueVassal.h"
#include "NpcJumpMapFunctionObject.h"
#include "ItemGroupTemplate.h"
#include "UIItemTips.h"
#include "ItemTemplate.h"
#include "ItemMoneyTemplate.h"
#include "ItemExpListCsv.h"
#include "ClientMain.h"
//***************************************************************************************************
namespace MG
{
	UINpc::UINpc()
	{
		mFunctionObjs.reserve(UINPC_FUNCTION_MAX_COUNT);
		mRewardItems.reserve(UINPC_ITEM_MAX_COUNT);
		mType = NPC_DIALOG_TYPE_NULL;
		mCurrSelectFunObjIndex = -1;
		mPlaceId = 0;
		mCharacterId = 0;
		mNpcCharTempId = 0;
		mQuestId = 0;
		mQuestState = NPC_QUEST_STATE_NULL;
	}
    //----------------------------------------------------------------------------------------
	UINpc::~UINpc()
    {
		clearGeneralTalkData();
    }
    //----------------------------------------------------------------------------------------
    void UINpc::setEvent()
    {
		// �رհ�ť
		IForm* mainForm = getLayout()->getForm("_Main");
		mainForm->setWindowButtonPressedEvent(onClickCloseBtn);
		
		// �����¼���ť
		Char temp[64] = {0};
		Int i = 0;
		for (; i < UINPC_FUNCTION_MAX_COUNT; i++)
		{
			MG::MGStrOp::sprintf(temp,64,"btn_fun%d",i+1);
			IButton* btn = getLayout()->getButton(temp);
			btn->getWidget()->setUserData(i);
			btn->getWidget()->setMouseButtonClickEvent(onClickFunBtn);
		}
		
		// �������ť
		IButton* btn = getLayout()->getButton("btn_mission_accept");
		DYNAMIC_ASSERT(btn);
		btn->getWidget()->setMouseButtonClickEvent(onClickQuestCmdBtn);

		btn = getLayout()->getButton("btn_mission_finish");
		DYNAMIC_ASSERT(btn);
		btn->getWidget()->setMouseButtonClickEvent(onClickQuestCmdBtn);
		
		// ����ȡ����ť
		btn =  getLayout()->getButton("btn_accept_back");
		DYNAMIC_ASSERT(btn);
		if (btn)
		{
			btn->getWidget()->setMouseButtonClickEvent(onClickQuestBackBtn);
		}	
		
		btn =  getLayout()->getButton("btn_finish_back");
		DYNAMIC_ASSERT(btn);
		if (btn)
		{
			btn->getWidget()->setMouseButtonClickEvent(onClickQuestBackBtn);
		}	
		//�򵥶Ի�����
		btn = getLayout()->getButton("btn_chat_ok");
		DYNAMIC_ASSERT(btn);
		btn->getWidget()->setMouseButtonClickEvent(onClickQuestCmdBtn);

		btn = getLayout()->getButton("btn_chat_next");
		DYNAMIC_ASSERT(btn);
		btn->getWidget()->setMouseButtonClickEvent(onClickQuestBackBtn);

		
		// �ݵ�����
		btn =  getLayout()->getButton("btn_place_jump");
		DYNAMIC_ASSERT(btn);
		if (btn)
		{
			btn->getWidget()->setMouseButtonClickEvent(onClickPlaceEneter);
		}
    }
	//----------------------------------------------------------------------------------------
	MG::Bool UINpc::openGui()
	{
		if (getLayout()->isVisible() == false )
		{   
			UIObject::openGui();
			getLayout()->getWidget(MAIN_WIDGET)->setAction(WIDGET_ACTION_CENTER_TO_EDGE, 0.25, false);
		}
		return true;
	}
	//----------------------------------------------------------------------------------------
	Bool UINpc::closeGui(Bool isForceClose)
	{
		if ( isForceClose )
			return UIObject::closeGui(isForceClose);
		
		if (getLayout()->isVisible() == true)
		    getLayout()->getWidget(MAIN_WIDGET)->setAction(WIDGET_ACTION_EDGE_TO_CENTER, 0.25, true);

		return true;
	}
	//----------------------------------------------------------------------------------------
	void UINpc::clearGeneralTalkData()
	{
		std::vector<NpcFuctionObject*>::iterator it = mFunctionObjs.begin();
		for (; it != mFunctionObjs.end(); it++)
		{
			MG_SAFE_DELETE(*it);
		}
		mFunctionObjs.clear();

		mNpcCharTempId = 0;
		mCharacterId = 0;
		mCurrSelectFunObjIndex = -1;
	}
	//----------------------------------------------------------------------------------------
	void UINpc::clearQuestData()
	{
		mRewardItems.clear();
		mType = NPC_DIALOG_TYPE_NULL;
		IWidget* pWidget = NULL;
		char msg[32] = "";
		for (int i = 1; i <= 4; i++)
		{
			Sprintf_s(msg, 32, "func_%d", i);
			pWidget = getLayout()->getWidget(msg);
			pWidget->setVisible(false);
		}
		mQuestState = NPC_QUEST_STATE_NULL;
		mCurrSelectFunObjIndex = -1;
	}
	//----------------------------------------------------------------------------------------
	void UINpc::clearPlaceData()
	{
		mCharacterId = 0;
		mPlaceId = 0;
	}
	//----------------------------------------------------------------------------------------
	void UINpc::onClickCloseBtn( void* widget )
	{
		DYNAMIC_ASSERT(widget);
		UINpc::getInstance().clearGeneralTalkData();
		UINpc::getInstance().clearQuestData();
		UINpc::getInstance().closeGui(false);
	}
	//----------------------------------------------------------------------------------------
	void UINpc::onClickFunBtn( void* widget )
	{
		DYNAMIC_ASSERT(widget);
		IWidget* iWidget = (IWidget*)widget;
		IAny* anyData = iWidget->getUserData();
		Int* funIndex = anyData->castType<Int>();
		NpcFuctionObject* funObj = UINpc::getInstance()._getFunctionObj((UInt)(*funIndex));
		if(!funObj)
			return;
		if(funObj->execute() && funObj->mNpcFunctionInfo->type == NPC_FUCTION_TYPE_CLAN_QUEST)
		{
			UINpc::getInstance()._setCurrSelectFunctionObj(*funIndex);
		}
	}
	//----------------------------------------------------------------------------------------
	void UINpc::onClickQuestCmdBtn( void* widget )
	{
		UINpc::getInstance()._handleQuestBtnCmd();
		//����������ɹ�
		//UINpc::getInstance().destoryFunctionObj();
		//UINpc::getInstance()._setFunctionIocn();
	}
	
	//----------------------------------------------------------------------------------------
	void UINpc::onClickQuestBackBtn( void* widget )
	{
		UINpc::getInstance()._adjustGeneralTalkUi();
	}
	//----------------------------------------------------------------------------------------
	void UINpc::_addFunction( NpcFunctionInfo* funInfo )
	{
		DYNAMIC_ASSERT(funInfo);
		DYNAMIC_ASSERT(mFunctionObjs.size() < UINPC_FUNCTION_MAX_COUNT);
		DYNAMIC_ASSERT(mCharacterId != 0);
		if (mFunctionObjs.size() >= UINPC_FUNCTION_MAX_COUNT)
		{
			return;
		}
		if (mCharacterId == 0)
		{
			return;
		}
		switch (funInfo->type)
		{
		case NPC_FUCTION_TYPE_CLAN_QUEST:
			{
				NpcFuctionObject* funObj = NpcClanQuestFunctionObject::create(funInfo,mNpcCharTempId,mCharacterId);
				if (funObj)
				{
					mFunctionObjs.push_back(funObj);
				}
			}
			break;
		case NPC_FUCTION_TYPE_ITEMSHOP:
			{
				NpcFuctionObject* funObj = NpcItemShopFunctionObject::create(funInfo,mNpcCharTempId,mCharacterId);
				if (funObj)
				{
					mFunctionObjs.push_back(funObj);
				}
			}
			break;
		case NPC_FUCTION_TYPE_JUMPMAP:
			{
				NpcFuctionObject* funObj =	NpcJumpMapFunctionObject::create(funInfo,mNpcCharTempId,mCharacterId);
				if (funObj)
				{
					mFunctionObjs.push_back(funObj);
				}
			}
			break;
		case NPC_FUCTION_TYPE_CLAN_STORAGE:
			{
               
			}
			break;
		case NPC_FUCTION_TYPE_GENERAL_RECRUIRED:
			{
                NpcFuctionObject* funObj =	NpcGeneralRecruitFunctionObject::create(funInfo,mNpcCharTempId,mCharacterId);
				if (funObj)
				{
					mFunctionObjs.push_back(funObj);
				}
			}
			break;
		case NPC_FUCTION_TYPE_CHANGE_FIGHTED_GENERAL:
			{
				NpcFuctionObject* funObj =	NpcChangeFightedGeneralFuctionObject::create(funInfo,mNpcCharTempId,mCharacterId);
				if (funObj)
				{
					mFunctionObjs.push_back(funObj);
				}
			}
			break;
		case NPC_FUCTION_TYPE_PVP_BATTLE:
			{
				NpcFuctionObject* funObj =	NpcPvpBattleFunctionObject::create(funInfo,mNpcCharTempId,mCharacterId);
				if (funObj)
				{
					mFunctionObjs.push_back(funObj);
				}
			}
			break;
		case NPC_FUCTION_TYPE_PVE_BATTLE:
			{
				NpcFuctionObject* funObj =	NpcPveDuplicteFunctionObject::create(funInfo,mNpcCharTempId,mCharacterId);
				if (funObj)
				{
					mFunctionObjs.push_back(funObj);
				}
			}
			break;
		}
		
	}
	//----------------------------------------------------------------------------------------
	void UINpc::_openFunctionGui(NPC_DIALOG_TYPE dialogType)
	{
		if (dialogType == NPC_DIALOG_TYPE_NULL)
		{
			return;
		}
		char msg[32] = "";
		IWidget* pWidget = NULL;
		if (mType != dialogType ) 
		{
			if(mType != NPC_DIALOG_TYPE_NULL)
			{
				Sprintf_s(msg, 32, "func_%d", (Int)mType);
				pWidget = getLayout()->getWidget(msg);
				pWidget->setVisible(false);
			}
			mType = dialogType;
		}
		Sprintf_s(msg, 32, "func_%d", (Int)mType);
		pWidget = getLayout()->getWidget(msg);
		pWidget->setVisible(true);
		

		IViewScroll* viewScroll = getLayout()->getViewScroll("scroll_function");
		DYNAMIC_ASSERT(viewScroll);
		if (viewScroll)
		{
			if (mType == NPC_DIALOG_TYPE_GENERAL)
			{
				viewScroll->getWidget()->setVisible(true);
			}
			else
			{
				viewScroll->getWidget()->setVisible(false);
			}
		}
		
	}
	//----------------------------------------------------------------------------------------
	Bool UINpc::_adjustGeneralTalkUi()
	{
		

		Char temp[64] = {0};
		Int i = 0;
		/// ��书�ܰ�ť, ͼ��
		for (i = 0; i < UINPC_FUNCTION_MAX_COUNT; i++)
		{
			MG::MGStrOp::sprintf(temp,64,"btn_fun%d",i+1);
			IButton* btn = getLayout()->getButton(temp);
			btn->getWidget()->setVisible(false);
		}
		for (i = 0; i < UINPC_FUNCTION_MAX_COUNT; i++)
		{
			MG::MGStrOp::sprintf(temp,64,"img_fun%d",i+1);
			IImage* img = getLayout()->getImage(temp);
			img->getWidget()->setVisible(false);
		}
		for (i = 0; i < mFunctionObjs.size() && i < UINPC_FUNCTION_MAX_COUNT; i++)
		{
			MG::MGStrOp::sprintf(temp,64,"btn_fun%d",i+1);
			IButton* btn = getLayout()->getButton(temp);
			btn->getWidget()->setVisible(true);
			btn->getWidget()->setCaption(_getFunctionObj(i)->mNpcFunctionInfo->desc);
		}
		for (i = 0; i < mFunctionObjs.size() && i < UINPC_FUNCTION_MAX_COUNT; i++)
		{
			MG::MGStrOp::sprintf(temp,64,"img_fun%d",i+1);
			IImage* img = getLayout()->getImage(temp);
			img->getWidget()->setVisible(true);
			_setFunctionIocn(i,_getFunctionObj(i)->mNpcFunctionInfo->artIocnResId);
		}

		/// ���ù��ܰ�ť�ͻ�����С
		getLayout()->getViewScroll("scroll_function")->setCanvasSize(366,24 * Int((i + 1.5f) / 2));	
		_openFunctionGui(NPC_DIALOG_TYPE_GENERAL);
		/// ���������Ϣ
		const CharacterTempInfo* tempInfo = CharacterTemplate::getInstance().getCharacterTempInfo(mNpcCharTempId);
		if (!tempInfo || tempInfo->getCharacterType() != CHARACTER_TYPE_NPC )
		{
			return false;
		}

		/// ���ñ���
		//_setTitle(L"NPC�Ի�");
		
		/// ����NPC����
		MG::Str16 npcInfo = tempInfo->getCharacterSurName() + tempInfo->getNpcName();
		_setName((MG::Char16 *)npcInfo.c_str());

		/// ����npcͼ��	
		_setNpcIocn(tempInfo->getCharacterArtIconId());
		
		/// ���öԻ�����
		//_setDescTitle(L"");

		/// ���öԻ���Ϣ
		//
		if (tempInfo->getNpcCharacterDialogId() != 0)
		{
			DialogInfo* dialogInfo = DialogInfos::getInstance().getDialogInfo(tempInfo->getNpcCharacterDialogId());
			DYNAMIC_ASSERT_LOG(dialogInfo,"CharacterNpcList.csv��CharacterDialogId�ֶ�,��dialog.csv��û�ҵ���Ӧֵ!");
			if (dialogInfo)
			{
				IEdit* edt = getLayout()->getEdit("content_1");
				DYNAMIC_ASSERT(edt);
				edt->clearEditText(false);
				Int editWidth = getEditBoxWidth(1);
				Str16 temp;
		
				U32 randNum;
				randNum = MGRandom::getInstance().rand_ab_One(0,2);
				if (randNum)
				{
					temp = dialogInfo->normalContent2;
				}
				else
				{
					temp = dialogInfo->normalContent1;
				}
				getWidthStrAddBreak(temp,editWidth);
				
				edt->addText(temp);
			}
		}
		
		return true;
		
	}
	//----------------------------------------------------------------------------------------
	Bool UINpc::_adjustQuestUi()
	{
		/// ���������Ϣ
		const CharacterTempInfo* tempInfo = CharacterTemplate::getInstance().getCharacterTempInfo(mNpcCharTempId);
		DYNAMIC_ASSERT(tempInfo);
		if (!tempInfo)
		{
			return false;
		}

		ClanQuestInfo* questInfo =ClanQuestInfos::getInstance().getQuestInfo(mQuestId);
		
		if (!questInfo && !questInfo->questInfo)
		{
			DYNAMIC_ASSERT(false);
			return false;
		}
		
		QuestTextInfo* textInfo = questInfo->questInfo->getTextInfo();
		if (!textInfo)
		{
			DYNAMIC_ASSERT(false);
			return false;
		}
		//�򵥵ĶԻ�������������
		if (mQuestState == NPC_QUEST_STATE_TALK)
		{
			_openFunctionGui(NPC_DIALOG_TYPE_TALK);
			///����������������
			if (!textInfo->nameAdd.empty())
			{
				_setTaskDescTitle((Char16*)textInfo->name.c_str(),NPC_DIALOG_TYPE_TALK);
			}
			else
			{
				Str16 tempText = textInfo->name + L"(" + textInfo->nameAdd + L")";
				_setTaskDescTitle((Char16*)tempText.c_str(),NPC_DIALOG_TYPE_TALK);
			}
			//todo ��ť�ǳ���next,ok?
			IButton* btn = getLayout()->getButton("btn_chat_ok");
			DYNAMIC_ASSERT(btn);
			btn->getWidget()->setVisible(true);
			//��������
			//content_4
			IEdit* edt = getLayout()->getEdit("content_4");
			edt->clearEditText(false);
			DYNAMIC_ASSERT(edt);
			Int editWidth = getEditBoxWidth(4);
			Str16 temp = textInfo->destNpcText;
			getWidthStrAddBreak(temp,editWidth);
			
			edt->addText(temp);
		}
		else
		{
			_openFunctionGui(NPC_DIALOG_TYPE_QUEST);
			char msg[32] = "";
			IWidget* pWidget = NULL;
			///����������������
			if (!textInfo->nameAdd.empty())
			{
				_setTaskDescTitle((Char16*)textInfo->name.c_str(),NPC_DIALOG_TYPE_QUEST);
			}
			else
			{
				Str16 tempText = textInfo->name + L"(" + textInfo->nameAdd + L")";
				_setTaskDescTitle((Char16*)tempText.c_str(),NPC_DIALOG_TYPE_QUEST);
			}

			switch(mQuestState)
			{
			case NPC_QUEST_STATE_ACCEPT:
				{
					Sprintf_s(msg, 32, "accept_task");
					pWidget = getLayout()->getWidget(msg);
					pWidget->setVisible(true);

					Sprintf_s(msg, 32, "commit_task");
					pWidget = getLayout()->getWidget(msg);
					pWidget->setVisible(false);
					//��������
					IEdit* edt = getLayout()->getEdit("content_2");
					DYNAMIC_ASSERT(edt);
					edt->clearEditText(false);
					Int editWidth = getEditBoxWidth(2);
					Str16 temp  = textInfo->acceptText;
					getWidthStrAddBreak(temp,editWidth);
					
					edt->addText(temp);
				}
				break;
			case NPC_QUEST_STATE_COMMIT:
				{
					Sprintf_s(msg, 32, "accept_task");
					pWidget = getLayout()->getWidget(msg);
					pWidget->setVisible(false);

					Sprintf_s(msg, 32, "commit_task");
					pWidget = getLayout()->getWidget(msg);
					pWidget->setVisible(true);
					IButton* btn = getLayout()->getButton("btn_mission_finish");
					DYNAMIC_ASSERT(btn);
					btn->getWidget()->setEnabled(true);
					//��������
					IEdit* edt = getLayout()->getEdit("content_2");
					DYNAMIC_ASSERT(edt);
					edt->clearEditText(false);
					Int editWidth = getEditBoxWidth(2);
					Str16 temp = textInfo->submitText;
					getWidthStrAddBreak(temp,editWidth);
					
					edt->addText(temp);
				}
				break;
			case NPC_QUEST_STATE_UNCOMMIT:
				{
					Sprintf_s(msg, 32, "accept_task");
					pWidget = getLayout()->getWidget(msg);
					pWidget->setVisible(false);

					Sprintf_s(msg, 32, "commit_task");
					pWidget = getLayout()->getWidget(msg);
					pWidget->setVisible(true);
					IButton* btn = getLayout()->getButton("btn_mission_finish");
					DYNAMIC_ASSERT(btn);
					btn->getWidget()->setEnabled(false);
					//��������
					IEdit* edt = getLayout()->getEdit("content_2");
					DYNAMIC_ASSERT(edt);
					edt->clearEditText(false);
					Int editWidth = getEditBoxWidth(2);
					Str16 temp = textInfo->submitTextUnFinish;
					getWidthStrAddBreak(temp,editWidth);
					edt->addText(temp);	
				}
				break;
			}
			/// TODO:
			/// ���ý�����Ϣ 
			
			_addRewardItem();
		}
		
		//-----------------------------------------------------
		/// ���ñ���
		//_setTitle(L"����Ի�");

		/// ����NPC����
		MG::Str16 npcInfo = tempInfo->getCharacterSurName() + tempInfo->getNpcName();
		_setName((MG::Char16 *)npcInfo.c_str());
		
		/// ����npcͼ��	
		_setNpcIocn(tempInfo->getCharacterArtIconId());
		//-----------------------------------------------------
		
		
		return true;
	}
	//----------------------------------------------------------------------------------------
	void UINpc::_setName( Char16* name )
	{
		IText* text = getLayout()->getText("text_npc_name");
		if (!text)
		{
			return;
		}
		text->getWidget()->setCaption(name);
	}
	//----------------------------------------------------------------------------------------
	void UINpc::_setTitle( Char16* title )
	{
		IForm * mainForm = getLayout()->getForm("_Main");
		DYNAMIC_ASSERT(mainForm);
		if (!mainForm)
		{
			return;
		}
		mainForm->getWidget()->setCaption(title);
	}
	//----------------------------------------------------------------------------------------
	void UINpc::_setTaskDescTitle( Char16* title, NPC_DIALOG_TYPE type)
	{
		if (type == NPC_DIALOG_TYPE_QUEST)
		{
			IText* text = getLayout()->getText("task_title");
			if (!text)
			{
				return;
			}
			text->getWidget()->setCaption(title);
		}
		else
		{
			IText* text = getLayout()->getText("chat_title");
			if (!text)
			{
				return;
			}
			text->getWidget()->setCaption(title);
		}
		
	}
	//----------------------------------------------------------------------------------------
	NpcFuctionObject* UINpc::_getFunctionObj( Int index )
	{
		if(index == -1)
		{
			index = mCurrSelectFunObjIndex;
		}
		if (mFunctionObjs.size() <= index)
		{
			return NULL;
		}
		return mFunctionObjs[index];
	}

	//----------------------------------------------------------------------------------------
	void UINpc::destoryFunctionObj( Int index )
	{
		if (index == -1)
		{
			index = mCurrSelectFunObjIndex;
		}
		if ( mFunctionObjs.size() <= index)
		{
			return;
		}	
		std::vector<NpcFuctionObject*>::iterator it = mFunctionObjs.begin();
		Int count = 0;
		for (; it != mFunctionObjs.end(); it++,count++)
		{
			if (count == index)
			{
				MG_SAFE_DELETE(*it);
				mFunctionObjs.erase(it);
				return;
			}
		}
	}
	//----------------------------------------------------------------------------------------
	void UINpc::_setNpcIocn( UInt id )
	{
		const ArtIconResCsvInfo* iconInfo = ArtIconResCsv::getInstance().getIconArtResInfo(id);
		if (iconInfo)
		{

			IImage* npcImage = getLayout()->getImage("npc_head");
			if (!npcImage)
			{
				return;
			}
			npcImage->setTexture(iconInfo->ResName, iconInfo->GroupName, iconInfo->ItemName);
		}	
	}
	//----------------------------------------------------------------------------------------
	void UINpc::_setFunctionIocn(Int index, Int id )
	{
		Char temp[64] = {0};
		if ( id == -1)
		{
			if (index == -1)
			{
				index = mCurrSelectFunObjIndex;
				
			}
			if (index < 0 || index >= UINPC_FUNCTION_MAX_COUNT)
			{
				return;
			}
			MGStrOp::sprintf(temp,64,"img_fun%d",index + 1);
			IImage* img = getLayout()->getImage(temp);
			DYNAMIC_ASSERT(img);
			img->getWidget()->setVisible(false);
		}
		else
		{
			const ArtIconResCsvInfo* iconInfo = ArtIconResCsv::getInstance().getIconArtResInfo(id);
			if (iconInfo)
			{
				MGStrOp::sprintf(temp,64,"img_fun%d",index + 1);
				IImage* img = getLayout()->getImage(temp);
				DYNAMIC_ASSERT(img);
				img->getWidget()->setVisible(true);
				if (img)
				{
					img->setItemGroup(iconInfo->GroupName);
					img->setItemName(iconInfo->ItemName);
					img->setItemResource(iconInfo->ResName);
				}
			}
		}
		
	}
	//
	void UINpc::returnTalkDialog()
	{
		clearQuestData();
		_adjustGeneralTalkUi();
	}
	//----------------------------------------------------------------------------------------
	void UINpc::openGeneralTalkDialog(U32 npcCharTempId,PlayerCharacterIdType characterId)
	{
		//������½��������ȹر�UI
		if (this->isOpen())
		{
			if (npcCharTempId != mNpcCharTempId && characterId != mCharacterId)
			{
				closeGui(true);
			}
			else
			{
				return;
			}
		}
		
		/// ���ԭ������
		clearPlaceData();
		clearGeneralTalkData();
		clearQuestData();

		/// ���������
		mNpcCharTempId = npcCharTempId;
		mCharacterId = characterId;


		//NPC
		/*Str16				getNpcName()const;
		Str16				getNpcZhiName()const;
		GENDER_TYPE			getNpcGenderType()const;
		U32					getNpcCharacterAppellationId()const;
		U32					getNpcCharacterDialogId()const;
		U32					getNpcArtEffectId()const;
		U32					getNpcAudioResId()const;
		U32					getNpcFunctionListId(int index)const;*/

		/// NPCģ���������
		const CharacterTempInfo* characterTempInfo = CharacterTemplate::getInstance().getCharacterTempInfo(npcCharTempId);
		if (!characterTempInfo)
		{
			DYNAMIC_ASSERT(false);
			return;
		}
		if (characterTempInfo->getCharacterType() != CHARACTER_TYPE_NPC)
		{
			DYNAMIC_ASSERT(false);
			return;
		}

		/// ����npcģ��ID��ӹ���
		/*NpcFuncionDialogInfo* npcDialogInfoNpc = NpcFuncionDialogInfos::getInstance().getNpcFucionDialogInfobyCharacterTempId(npcCharTempId);
		if (!npcDialogInfoNpc)
		{
			return;
		}*/
		NpcFunctionInfo* funInfo = NULL;
		for(Int i = 0; i < NPC_DIALOG_FUNCTION_ID_COUNT; i++)
		{
			funInfo = NpcFunctionInfos::getInstance().getNpcFuctionInfo(characterTempInfo->getNpcFunctionListId(i));
			if (funInfo)
			{
 				UINpc::getInstance()._addFunction(funInfo);
			}
		}
		
		///���µ���UI
		if(!_adjustGeneralTalkUi())
		{
			closeGui(true);
			return;
		}

		///�򿪽���
		openGui();
	}
	//----------------------------------------------------------------------------------------
	void UINpc::openNpcQuestDialog( QuestIdType npcQuestId, NPC_QUEST_STATE state)
	{
		clearQuestData();

		///���������
		//mType = NPC_DIALOG_TYPE_QUEST;

		mQuestId = npcQuestId;
		mQuestState = state;

		/// ����npcģ��ID��ӹ���
		ClanQuestInfo* missionInfo = ClanQuestInfos::getInstance().getQuestInfo(mQuestId);
		DYNAMIC_ASSERT(missionInfo);
		if (!missionInfo)
		{
			return;
		}
		
		//�����Ʒ
		ItemGroupTemplate::getInstance().getItemGroupInfo(missionInfo->questInfo->getItemGroupId(),mRewardItems);

		///���µ���UI
		if(!_adjustQuestUi())
		{
			closeGui(true);
			return;
		}

		///�򿪽���
		openGui();
	}
	//----------------------------------------------------------------------------------------
	void UINpc::_setType( NPC_DIALOG_TYPE type )
	{
		mType = type;
	}
	//----------------------------------------------------------------------------------------
	void UINpc::_setCurrSelectFunctionObj( Int index )
	{
		if (index < UINPC_FUNCTION_MAX_COUNT && index > -2)
		{
			mCurrSelectFunObjIndex  = index;
		}
	}
	//----------------------------------------------------------------------------------------
	void UINpc::_handleQuestBtnCmd()
	{
		//IButton* btn = getLayout()->getButton("btn_mission_cmd");
		//DYNAMIC_ASSERT(btn);
		//btn->getWidget()->setEnabled(false);
		//destoryFunctionObj();
		_setFunctionIocn();
		switch(mQuestState)
		{
		case NPC_QUEST_STATE_ACCEPT:
			//��������
			{
				//IButton* btn = getLayout()->getButton("btn_mission_accept");
				//DYNAMIC_ASSERT(btn);
				//btn->getWidget()->setEnabled(false);
				CClanQuestManager::getInstance().acceptClanQuest(_getFunctionObj()->mNpcFunctionInfo->param1,mCharacterId);
			}	
			break;
		case NPC_QUEST_STATE_COMMIT:
			{
				//IButton* btn = getLayout()->getButton("btn_mission_finish");
				//DYNAMIC_ASSERT(btn);
				//btn->getWidget()->setEnabled(false);
				CClanQuestManager::getInstance().submitClanQuest(_getFunctionObj()->mNpcFunctionInfo->param1);
			}
			break;
		case NPC_QUEST_STATE_UNCOMMIT:
			CClanQuestManager::getInstance().giveupClanQuest(_getFunctionObj()->mNpcFunctionInfo->param1);
			break;
		case NPC_QUEST_STATE_TALK:
			{
				QuestNetPacketProcesser::getInstance().sendTalkToNpc(_getFunctionObj()->mNpcFunctionInfo->param1,_getFunctionObj()->mNpcCharTempId);
				destoryFunctionObj();
				returnTalkDialog();
			}
			break;

		}
	}

	void UINpc::openNpcPlaceDialog( PlaceIdType placeId,PlayerCharacterIdType characterId )
	{
		clearPlaceData();
		clearGeneralTalkData();
		clearQuestData();

		/// ���ý�������
		mType = NPC_DIALOG_TYPE_PLACE;

		/// ���������
		mPlaceId = placeId;
		mCharacterId = characterId;

		/// ���µ���UI
		if(!_adjustPlaceUi())
		{
			closeGui(true);
			return;
		}

		///�򿪽���
		openGui();
	}
	//----------------------------------------------------------------------------------------
	MG::Bool UINpc::_adjustPlaceUi()
	{
		///TODO:
		/// ���ݵ�������Ϣ
		///const PlaceInfo* tempInfo;
		/// DYNAMIC_ASSERT(tempInfo);
		/// if (!tempInfo)
		/// {
		/// 	return false;
		/// }
	
		/// ���ñ���
		_setTitle(L"�ݵ�Ի�");

		/// ���þݵ�����
		///_setName((MG::Char16 *)tempInfo->Name.c_str());

		/// ���þݵ�ͼ��	
		///_setNpcIocn(tempInfo->ArtIconId);

		/// ���þݵ�Ի�����
		///_setDescTitle((Char16*)missionInfo->name.c_str());

		/// ���þݵ�Ի���Ϣ
		///_setDescContent((Char16*)dialogInfo->normalContent2.c_str());
		///missionInfo->

		/// ����npc���ĶԻ��йؿؼ�
		IViewScroll* viewScroll = getLayout()->getViewScroll("scroll_function");
		DYNAMIC_ASSERT(viewScroll);
		if (viewScroll)
		{
			viewScroll->getWidget()->setVisible(false);
		}

		/// ��������Ի��йؿؼ�
		IImage* img = getLayout()->getImage("img_misson");
		DYNAMIC_ASSERT(img);
		if (img)
		{
			img->getWidget()->setVisible(false);
		}
		
		/// ���þݵ��йؿؼ�
		IImage* imgPlace = getLayout()->getImage("img_place_jump");
		DYNAMIC_ASSERT(imgPlace);
		imgPlace->getWidget()->setVisible(true);
		
		return true;
	}

	//----------------------------------------------------------------------------------------
	void UINpc::onClickPlaceEneter( void* widget )
	{
		CPlayerCharacter* myCharacter = CPlayer::getInstance().getMainGenreal();
		RegionIdType placeId = UINpc::getInstance().getPlaceId();
		DYNAMIC_ASSERT(placeId > 0);
		PlayCharacterNetPacketProcesser::getInstance().sendPlayerCharacterJumpRegion(myCharacter->getID(),ROT_PLACE, placeId, 0);
		//NpcFuctionObject* selectedFuncObject = _getFunctionObj(_ge)
		//PlayCharacterNetPacketProcesser::getInstance().jumpMapForUI(myCharacter->getID(),)
	}

	//----------------------------------------------------------------------------------------
	PlaceIdType UINpc::getPlaceId() const 
	{ 
		return mPlaceId; 
	}
	//----------------------------------------------------------------------------------------
	void UINpc::_addRewardItem()
	{
		restoreRewardItemUi();
		if (mRewardItems.size() > 0)
		{   
             Int index = 1;
			 IconInfo tempInfo;
			 Char8 temStr[32] = {0};
			 IImage* pIcon = NULL;
			 IText*  pText = NULL;
			 wstring itemSizeStr = L"";
			 std::vector<ItemNum>::iterator itemIt = mRewardItems.begin();
			 for (;itemIt != mRewardItems.end(); itemIt++)
			 {   
				 ItemNum& tempItemNum= (*itemIt); 
				 const ItemInfo* pInfo = ItemTemplate::getInstance().getItemInfo(tempItemNum.itemTemplate); 
				
				 //money exp û��ͼƬ,Ҳ����ҪTips
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
	//----------------------------------------------------------------------------------------
	void UINpc::onEventToolTips( void* pWidget, Bool isShow, Int left, Int top )
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

		UINpc::getInstance().onHandleTips(isShow,pInfo,pIcon->getAbsoluteCoord()); 
	}
	//----------------------------------------------------------------------------------------
	void UINpc::onHandleTips( Bool isShow, IconInfo* pIconInfo, CoordI coord )
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
	void UINpc::restoreRewardItemUi()
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
        for (Int index = 1; index <= UINPC_ITEM_MAX_COUNT;index++)
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
	//----------------------------------------------------------------------------------------
	MG::U32 UINpc::getWidthStrAddBreak( Str16& src, Int width, Str8 fontName )
	{
		IGui* igui = ClientMain::getInstance().getGui();
		return igui->getHeightStrAddBreak(src,width,fontName);

	}
	//----------------------------------------------------------------------------------------
	MG::Int UINpc::getEditBoxWidth( Int index )
	{
		Char8 tempName[16] = "";
		sprintf_s(tempName,16,"content_%d",index);
		
		return (static_cast<Int>(getInstance().getLayout()->getEdit(tempName)->getWidget()->getSize().x) - 30);
	}
	//----------------------------------------------------------------------------------------
	MG::Int UINpc::getEditBoxHeight( Int index)
	{
		Char8 tempName[16] = "";
		sprintf_s(tempName,16,"content_%d",index);

		return (static_cast<Int>(getInstance().getLayout()->getEdit(tempName)->getWidget()->getSize().y) - 30);
	}
	//----------------------------------------------------------------------------------------
}