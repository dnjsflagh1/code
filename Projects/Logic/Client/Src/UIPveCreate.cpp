//*************************************************************************************

#include "stdafx.h"
#include "UIPveCreate.h"
#include "CPlayer.h"
#include "CPveNetPacketProcesser.h"
#include "CRegionManager.h"
#include "UIMessageBox.h"
#include "ArtIconResCsv.h"
//*************************************************************************************

#define COMBO_TARGET_LIST "Combo_Target_List"

//*************************************************************************************
namespace MG
{
	//--------------------------------------------------------------------------------
	UIPveCreate::UIPveCreate()
	{
		//createTest();
		for (Int i=Pve_Position_1; i<Pve_Position_Max; ++i)
		{
			mPveMemberList.createOrRetrieve((Pve_Position)i);
		}
	}

	//--------------------------------------------------------------------------------
	UIPveCreate::~UIPveCreate()
	{
	}

	void UIPveCreate::setEvent()
	{
		//新建队伍
		{
			IButton* btnCreate = getLayout()->getButton("Btn_Create");
			DYNAMIC_ASSERT(btnCreate);
			btnCreate->getWidget()->setMouseButtonClickEvent(onClickButtonCreatePve);
		}

		//离开 按钮
		{
			IButton* btnLeave = getLayout()->getButton("Btn_Leave");
			DYNAMIC_ASSERT(btnLeave);
			btnLeave->getWidget()->setMouseButtonClickEvent(onClickLeaveRoom);
		}

		//开始 按钮
		{
			IButton* btnConfirm = getLayout()->getButton("Btn_Confirm");
			DYNAMIC_ASSERT(btnConfirm);
			btnConfirm->getWidget()->setMouseButtonClickEvent(onClickConfirm);
			btnConfirm->getWidget()->setVisible(true);
		}

		//踢 按钮
		{
			//踢 2
			{
				IButton* btnKick = getLayout()->getButton("Btn_Kick_2");
				DYNAMIC_ASSERT(btnKick);
				btnKick->getWidget()->setMouseButtonClickEvent(onClickKick2);
			}

			//踢 3
			{
				IButton* btnKick = getLayout()->getButton("Btn_Kick_3");
				DYNAMIC_ASSERT(btnKick);
				btnKick->getWidget()->setMouseButtonClickEvent(onClickKick3);
			}

			//踢 4
			{
				IButton* btnKick = getLayout()->getButton("Btn_Kick_4");
				DYNAMIC_ASSERT(btnKick);
				btnKick->getWidget()->setMouseButtonClickEvent(onClickKick4);
			}

			//踢 5
			{
				IButton* btnKick = getLayout()->getButton("Btn_Kick_5");
				DYNAMIC_ASSERT(btnKick);
				btnKick->getWidget()->setMouseButtonClickEvent(onClickKick5);
			}
			
		

			
		}
	}

	Bool UIPveCreate::openGui()
	{
		if (false == UIObject::isOpen())
		{
			CPveNetPacketProcesser::getInstance().sendPveRoomList();
			UIObject::openGui();
			return true;
		}
		else
		{
			IEdit* edit_PveName = UIPveCreate::getInstance().getLayout()->getEdit("EditBox_Name");
			edit_PveName->setCaption(L"");

			UIReFreshTargetRegionList();
			UIReFreshRoomList();
			
			if (true == mPveMemberList.getData(Pve_Position_1)->empty())
			{
				UIReFreshCreate();
			}
			else
			{
				UIReFreshMemberInfo();
			}
			
		}
		return false;
	}

	void UIPveCreate::restore()
	{
		mPveRoomList.clear();
		
		clearPveMember();
	}

	void UIPveCreate::onClickButtonCreatePve(void* widget)
	{
		//读取攻击目标名字
		IComboBox* comboTarget = UIPveCreate::getInstance().getLayout()->getComboBox(COMBO_TARGET_LIST);
		Int index = comboTarget->getIndexSelected();
		IAny* tempAny = comboTarget->getItemDataAt(index);
		if (NULL == tempAny)
		{
			return ;
		}

		InstanceIdType targetRegionId = *(tempAny->castType<InstanceIdType>());

		//读取战斗名字
		IEdit* edit_PveName = UIPveCreate::getInstance().getLayout()->getEdit("EditBox_Name");
		std::wstring pveNameStr = edit_PveName->getCaption();

		if (pveNameStr.empty())
		{
			//名字不能为空
			UIMessageBox::getInstance().showHint(L"战斗名字不能为空");
			return;
		}

		const AccountIdType accountId = CPlayer::getInstance().getAccountID();

		CPveNetPacketProcesser::getInstance().sendPveCreate(accountId, targetRegionId, pveNameStr.c_str());
	}

	void UIPveCreate::onClickLeaveRoom(void* widget)
	{
		const AccountIdType accountId = CPlayer::getInstance().getAccountID();
		CPveNetPacketProcesser::getInstance().sendPveLeaveRoom(accountId);
	}

	void UIPveCreate::onClickConfirm(void* widget)
	{
		const AccountIdType accountId = CPlayer::getInstance().getAccountID();
		CPveNetPacketProcesser::getInstance().sendPveStart(accountId);
	}

	void UIPveCreate::onClickKick2(void* widget)
	{
		UIPveMemberInfo* memberInfo = UIPveCreate::getInstance().getPveMemberByPosition(Pve_Position_2);
		DYNAMIC_ASSERT(NULL != memberInfo);

		const AccountIdType myAccountId = CPlayer::getInstance().getAccountID();
		CPveNetPacketProcesser::getInstance().sendPveKickMember(myAccountId, memberInfo->accountId);
	}

	void UIPveCreate::onClickKick3(void* widget)
	{
		UIPveMemberInfo* memberInfo = UIPveCreate::getInstance().getPveMemberByPosition(Pve_Position_3);
		DYNAMIC_ASSERT(NULL != memberInfo);

		const AccountIdType myAccountId = CPlayer::getInstance().getAccountID();
		CPveNetPacketProcesser::getInstance().sendPveKickMember(myAccountId, memberInfo->accountId);
	}

	void UIPveCreate::onClickKick4(void* widget)
	{
		UIPveMemberInfo* memberInfo = UIPveCreate::getInstance().getPveMemberByPosition(Pve_Position_4);
		DYNAMIC_ASSERT(NULL != memberInfo);

		const AccountIdType myAccountId = CPlayer::getInstance().getAccountID();
		CPveNetPacketProcesser::getInstance().sendPveKickMember(myAccountId, memberInfo->accountId);
	}

	void UIPveCreate::onClickKick5(void* widget)
	{
		UIPveMemberInfo* memberInfo = UIPveCreate::getInstance().getPveMemberByPosition(Pve_Position_5);
		DYNAMIC_ASSERT(NULL != memberInfo);

		const AccountIdType myAccountId = CPlayer::getInstance().getAccountID();
		CPveNetPacketProcesser::getInstance().sendPveKickMember(myAccountId, memberInfo->accountId);
	}

	//--------------------------------------------------------------------------------
	void UIPveCreate::onClickEnterRoom(void* widget, Int index)
	{
		IMixList* listMainZone = (IMixList*)widget;

		IMixListRow* row = listMainZone->getMixListRowByIndex(index);

		IAny* pAny = row->getWidget()->getUserData();
		UIPveRoomInfo* roomInfo = pAny->castType<UIPveRoomInfo>(pAny);
		DYNAMIC_ASSERT(NULL != roomInfo);
		CPveNetPacketProcesser::getInstance().sendPveEnterRoom(roomInfo->pveRoomId);
	}

	//--------------------------------------------------------------------------------
	void UIPveCreate::UIReFreshRoomList()
	{
		IMixList* listMainZone = getLayout()->getMixList("MixList_RoomList");
		DYNAMIC_ASSERT(listMainZone);

		listMainZone->setDoubleClickMixListRow(onClickEnterRoom);

		listMainZone->removeAllLine();
		char creatorName[32]	= "";

		for (Int i=0; i<mPveRoomList.size(); ++i)
		{
			listMainZone->addLine(0,L"");
			IMixListRow* row = listMainZone->getMixListRowByIndex(i);

			//一行数据
			UIPveRoomInfo* roomInfo = &(mPveRoomList.at(i));

			Color color = ColorSet::white();
			if (true == roomInfo->isMe)
			{
				color = ColorSet::yellow();
			}
			row->getChildWidget(1)->setCaption(roomInfo->strPveRoomId);
			row->getText(1)->setTextColour(color);
			row->getText(1)->setTextAlign(Center);
			
			row->getChildWidget(2)->setCaption(roomInfo->strTargetRegionName);
			row->getText(2)->setTextColour(color);
			row->getText(2)->setTextAlign(Center);
			
			row->getChildWidget(3)->setCaption(roomInfo->strPveRoomName);
			row->getText(3)->setTextColour(color);
			row->getText(3)->setTextAlign(Center);

			row->getChildWidget(4)->setCaption(roomInfo->strMemberNum);
			row->getText(4)->setTextColour(color);
			row->getText(4)->setTextAlign(Center);

			row->getWidget()->setUserData(*roomInfo);
		}
	}

	//--------------------------------------------------------------------------------
	void UIPveCreate::UIReFreshTargetRegionList()
	{
		//显示目标
		IComboBox* comboTarget = getLayout()->getComboBox(COMBO_TARGET_LIST);
		comboTarget->removeAllItems();

		//加载攻击目标内存
		std::map<InstanceIdType, CPveObject*>* pveList = CRegionManager::getInstance().getPveObjList();

		for(std::map<InstanceIdType, CPveObject*>::iterator iter = pveList->begin(); iter != pveList->end(); ++iter)
		{
			comboTarget->addItem(iter->second->getRegionNameStr16(), (iter->first));
		}
		comboTarget->setIndexSelected(0);
	}

	void UIPveCreate::UIReFreshCreate()
	{
		IWidget* createWidget = getLayout()->getWidget("Panel_Create");
		IWidget* roomWidget = getLayout()->getWidget("Panel_Room");
		
		roomWidget->setVisible(false);

		
		createWidget->setVisible(true);
	}

	void UIPveCreate::UIReFreshMemberByPos(Pve_Position pos, UIPveMemberInfo* memberInfo)
	{
		Bool leader = isLeader();

		IWidget* createWidget = getLayout()->getWidget("Panel_Create");
		IWidget* roomWidget = getLayout()->getWidget("Panel_Room");

		roomWidget->setVisible(true);
		createWidget->setCaption(L"");
		createWidget->setVisible(false);


		////关闭所有底图
		//for (Int i=0; i != 5; ++i)
		//{
		//	char imageBack[32] = "";
		//	sprintf(imageBack, "Panel_Back_%d", i + 1);
		//	IWidget* back_activeImage = getLayout()->getWidget(imageBack);
		//	back_activeImage->setVisible(false);
		//}

		if (true == memberInfo->empty())
		{
			//这个位置是空的

			char imageBack[32] = "";
			sprintf(imageBack, "Panel_Back_%d", pos + 1);
			IWidget* back_activeImage = getLayout()->getWidget(imageBack);
			back_activeImage->setVisible(true);
			return;
		}
		//填充UI信息
		//for (Int i = 0; i != mPveMemberList.size(); ++i)
		{
			//UIPveMemberInfo* memberInfo = (mPveMemberList.getData(pos));
			const ArtIconResCsvInfo* tempResInfo =ArtIconResCsv::getInstance().getIconArtResInfo(memberInfo->charArtIcon);
			DYNAMIC_ASSERT(NULL != tempResInfo);

			Int position = memberInfo->position + 1;

			////点亮底图
			//{
			//	char imageBack[32] = "";
			//	sprintf(imageBack, "Panel_Back_%d", position);
			//	IWidget* back_activeImage = getLayout()->getWidget(imageBack);
			//	back_activeImage->setVisible(true);
			//}

			Color color = ColorSet::white();
			if (true == memberInfo->isMe)
			{
				color = ColorSet::yellow();
			}


			//显示头像
			{
				char tempStr[32] = "";
				sprintf(tempStr, "Img_Head_%d", position);
				IImage* image_Head = getLayout()->getImage(tempStr);
				image_Head->setItemGroup(tempResInfo->SmallGroupName);
				image_Head->setItemResource(tempResInfo->SmallResName);
				image_Head->setItemName(tempResInfo->SmallItemName);
			}

			//等级
			{
				char tempStr[32] = "";
				sprintf(tempStr, "Text_Head_Level_%d", position);
				IText* text_Level = getLayout()->getText(tempStr);
				text_Level->getWidget()->setCaption(memberInfo->charLevel);
				text_Level->setTextColour(color);
			}

			//名字
			{
				char tempStr[32] = "";
				sprintf(tempStr, "Text_Name_%d", position);
				IText* text_Name = getLayout()->getText(tempStr);
				text_Name->getWidget()->setCaption(memberInfo->charName);
				text_Name->setTextColour(color);
			}

			//踢出 按钮
			{
				char tempStr[32] = "";
				sprintf(tempStr, "Btn_Kick_%d", position);
				IButton* btn_Kick = getLayout()->getButton(tempStr);
				btn_Kick->getWidget()->setCaption(L"踢");
				btn_Kick->getWidget()->setVisible(leader);

				//第一个不显示
				if (position == 1)
				{
					btn_Kick->getWidget()->setVisible(false);
				}
			}

			//开始 按钮
			{
				IButton* btn_Confirm = getLayout()->getButton("Btn_Confirm");
				btn_Confirm->getWidget()->setCaption(L"开始");
				btn_Confirm->getWidget()->setVisible(leader);
			}
		}
	}

	void UIPveCreate::UIReFreshMemberInfo()
	{
		Int nCount = mPveMemberList.getDataSet()->size();

		for (Int i=0; i<nCount; i++)
		{
			UIPveMemberInfo* memberInfo = mPveMemberList.getData((Pve_Position)i);
			UIReFreshMemberByPos((Pve_Position)i, memberInfo);
		}
		
	}

	void UIPveCreate::addPveRoom(Int addPveRoomNum, const NetPveRoomInfo* addPveRoomInfo)
	{
		const AccountIdType myAccountId = CPlayer::getInstance().getAccountID();

		DYNAMIC_ASSERT(addPveRoomNum >= 0);
		for (Int i=0; i<addPveRoomNum; ++i)
		{
			const NetPveRoomInfo* tempInfo = &(addPveRoomInfo[i]);
			CRegionObject* regionObj = CRegionManager::getInstance().getRegionObjectById(ROT_PVE, tempInfo->targetRegionId);
			DYNAMIC_ASSERT(NULL != regionObj);
		
			UIPveRoomInfo tempRoom;
			if(myAccountId == tempInfo->creatorAccountId)
			{
				//我自己创建的房间
				tempRoom.isMe = true;
			}
			else
			{
				tempRoom.isMe = false;
			}

			//人数
			wchar_t strMemberNum[32] = L"";
			swprintf( strMemberNum, L"%d", tempInfo->memberNum);
		
			//ID
			wchar_t strRoomId[32] = L"";
			swprintf( strRoomId, L"%d", tempInfo->pveRoomId);
			
			tempRoom.strTargetRegionName= regionObj->getRegionNameStr16();
			tempRoom.strPveRoomName	 	= tempInfo->pveRoomName;
			tempRoom.pveRoomId		 	= tempInfo->pveRoomId;
			tempRoom.strPveRoomId	 	= strRoomId;
			tempRoom.strMemberNum		= strMemberNum;
			mPveRoomList.push_back(tempRoom);
		}
	}

	void UIPveCreate::delPveRoom(Int roomId)
	{
		for (std::vector<UIPveRoomInfo>::iterator iter = mPveRoomList.begin(); iter != mPveRoomList.end(); ++iter)
		{
			if (iter->pveRoomId == roomId)
			{
				mPveRoomList.erase(iter);
				return;
			}
		}
	}

	void UIPveCreate::clearPveRoom()
	{
		mPveRoomList.clear();
	}

	void UIPveCreate::addPveMember(Int addPveMemberNum, const NetPveMemberInfo* addPveMemberInfo)
	{
		const AccountIdType myAccountId = CPlayer::getInstance().getAccountID();
		DYNAMIC_ASSERT(addPveMemberNum >= 0);
		for (Int i=0; i<addPveMemberNum; ++i)
		{
			const NetPveMemberInfo* tempInfo = &(addPveMemberInfo[i]);
			wchar_t outputStr[32] = L"";
			swprintf( outputStr, L"%d", tempInfo->charLevel);

			UIPveMemberInfo* newInfo = mPveMemberList.getData((Pve_Position)tempInfo->position);
			DYNAMIC_ASSERT(true == newInfo->empty());

			newInfo->accountId	= tempInfo->accountId;
			newInfo->charArtIcon= tempInfo->charArtIcon;
			newInfo->charName	= tempInfo->characterName;
			newInfo->charLevel	= outputStr;
			newInfo->position	= (Pve_Position)tempInfo->position;
			if (myAccountId == tempInfo->accountId)
			{
				newInfo->isMe = true;
			}
		}
	}

	void UIPveCreate::modifyMemberInfo(Pve_Position pos, UIPveMemberInfo* memberInfo)
	{
		UIPveMemberInfo* info = mPveMemberList.getData(pos);

		info->accountId		= memberInfo->accountId;
		info->charArtIcon	= memberInfo->charArtIcon;
		info->charName		= memberInfo->charName;
		info->charLevel		= memberInfo->charLevel;
		info->position		= memberInfo->position;
		info->isMe			= memberInfo->isMe;
		
	}

	void UIPveCreate::delPveMember(const AccountIdType accountId)
	{
		std::map<Pve_Position, UIPveMemberInfo*>* memberList = mPveMemberList.getDataSet();
		for (std::map<Pve_Position, UIPveMemberInfo*>::iterator iter = memberList->begin(); iter != memberList->end(); ++iter)
		{
			if (iter->second->accountId == accountId)
			{
				iter->second->clear();
				return;
			}
		}
	}

	void UIPveCreate::clearPveMember()
	{
		std::map<Pve_Position, UIPveMemberInfo*>* memberList = mPveMemberList.getDataSet();
		for (std::map<Pve_Position, UIPveMemberInfo*>::iterator iter = memberList->begin(); iter != memberList->end(); ++iter)
		{
			iter->second->clear();
		}
	}

	UIPveMemberInfo* UIPveCreate::getPveMemberByPosition(const Pve_Position position)
	{
		return mPveMemberList.getData(position);
	}

	void UIPveCreate::createTest()
	{
		//mPveMemberList.clear();

		//for (Int i=0; i<2; ++i)
		//{
		//	//const NetPveRoomInfo* tempInfo = &(addPveRoomInfo[i]);
		//	UIPveMemberInfo tempMember;
		//	tempMember.charArtIcon = 30011+ i;
		//	mPveMemberList.push_back(tempMember);
		//}
	}

	Bool UIPveCreate::isLeader()
	{

		if (true == mPveMemberList.empty())
		{
			return false;
		}

		std::map<Pve_Position, UIPveMemberInfo*>* memberList = mPveMemberList.getDataSet();
		std::map<Pve_Position, UIPveMemberInfo*>::iterator iter = memberList->find(Pve_Position_1);
		if (iter != memberList->end())
		{
			//找到房主
			UIPveMemberInfo* leaderInfo = iter->second;
			if (leaderInfo->accountId == CPlayer::getInstance().getAccountID())
			{
				//我是房主
				return true;
			}
		}

		

		return false;
	}
}