//*************************************************************************************

#include "stdafx.h"
#include "UICampaignInfoNew.h"
#include "CampaignNetPacketProcesser.h"
#include "CPlayer.h"
#include "ArtIconResCsv.h"
#include "CRegionManager.h"

//*************************************************************************************



//*************************************************************************************
namespace MG
{
	//------------------------------------------------------------------------
	UICampaignInfoNew::UICampaignInfoNew()
		:mTargetRegionId(0)
	{
		for (Int i=0; i<POSITION_MAX; ++i)
		{
			//UICampaignInfoNewSingle tempInfo;
			//mMemberList.push_back(tempInfo);
			mMemberList.createOrRetrieve(i);
		}

		mLearder.createOrRetrieve(0);

		//createMemberForTest();
	}

	//------------------------------------------------------------------------
	UICampaignInfoNew::~UICampaignInfoNew()
	{

	}

	//------------------------------------------------------------------------
	void UICampaignInfoNew::setEvent()
	{
		//��ȷ�ϰ�ť��
		{
			IButton* btnConfirm = getLayout()->getButton("Btn_Confirm");
			btnConfirm->getWidget()->setMouseButtonClickEvent(onEventConfirm);
		}

		//��ȡ����ť��
		{
			IButton* btnCancel = getLayout()->getButton("Btn_Cancel");
			btnCancel->getWidget()->setMouseButtonClickEvent(onEventCancel);
		}
	}

	//------------------------------------------------------------------------
	Bool UICampaignInfoNew::openGui()
	{
		if (  false == UIObject::isOpen() )
		{
			UIObject::openGui();
		}

		UIReFresh();
		return false;
	}

	//------------------------------------------------------------------------
	void UICampaignInfoNew::onEventConfirm(void* widget)
	{
		ClanIdType myClanId = CPlayer::getInstance().getActiveClan()->getClanID();
		SCampaign* myCampaign = CPlayer::getInstance().getMyCampaign();
		DYNAMIC_ASSERT(NULL != myCampaign);

		CampaignIdType myCampaignId = myCampaign->getCampaignId();

		Bool creatorIsMe = CPlayer::getInstance().campaignCreatorIsMe();
		if (false == creatorIsMe)
		{
			CampaignNetPacketProcesser::getInstance().sendCampaignReadyMySelf(myCampaignId, myClanId, 0);
			return;
		}
		else
		{
			CampaignNetPacketProcesser::getInstance().sendCampaignStart(myCampaignId, myClanId);
		}
		
	}

	//------------------------------------------------------------------------
	void UICampaignInfoNew::onEventCancel(void* widget)
	{
		ClanIdType myClanId = CPlayer::getInstance().getActiveClan()->getClanID();
		SCampaign* myCampaign = CPlayer::getInstance().getMyCampaign();
		DYNAMIC_ASSERT(NULL != myCampaign);

		CampaignIdType myCampaignId = myCampaign->getCampaignId();

		Bool creatorIsMe = CPlayer::getInstance().campaignCreatorIsMe();
		if (false == creatorIsMe)
		{
			CampaignNetPacketProcesser::getInstance().sendCampaignLeave(myCampaignId, myClanId);
			return;
		}
		else
		{
			CampaignNetPacketProcesser::getInstance().sendCampaignLeave(myCampaignId, myClanId);
			//return;
		}
	}

	//--------------------------------------------------------------------------------
	void UICampaignInfoNew::UIReFresh()
	{
		if (false == isOpen())
		{
			return;
		}

		Bool creatorIsMe = CPlayer::getInstance().campaignCreatorIsMe();
		
		//��ȷ�ϰ�ť��

		{
			IButton* btnConfirm = getLayout()->getButton("Btn_Confirm");

			if (true == creatorIsMe)
			{
				//���Ƿ���
				btnConfirm->getWidget()->setCaption(L"��ʼ");
			}
			else
			{
				//
				btnConfirm->getWidget()->setCaption(L"׼��");
			}
		}

		//ȡ����ť
		{
			IButton* btnCancel = getLayout()->getButton("Btn_Cancel");


			//if (true == creatorIsMe)
			{
				//���Ƿ���
				//btnCancel->getWidget()->setCaption(L"�߳�");
			}
			//else
			{
				//
				btnCancel->getWidget()->setCaption(L"�뿪����");
			}
		}

		//Ŀ����������
		{
			CRegionObject* regionObj = CRegionManager::getInstance().getRegionObjectById(ROT_PLACE, getTargetRegionId());
			IText* textTargetRegion = getLayout()->getText("TargetRegion");
			if (NULL != regionObj)
			{
				textTargetRegion->getWidget()->setCaption(regionObj->getRegionNameStr16());
			}

			//IText* textTargetRegionDes = getLayout()->getText("TargetRegionDes");
			//
			//if (NULL != regionObj)
			//{
			//	textTargetRegionDes->getWidget()->setCaption(regionObj->getRegionNameStr16());
			//}
		}

		//�ҵ� ��������
		{
			IText* textTargetRegion = getLayout()->getText("Attack_Region");
			const RegionIdType myRegionId = CPlayer::getInstance().getMainGenreal()->getRegionID();
			REGION_OBJ_TYPE myRegionType = CPlayer::getInstance().getMainGenreal()->getRegionType();
			CRegionObject* regionObj = CRegionManager::getInstance().getRegionObjectById(myRegionType,myRegionId);
			if (NULL != regionObj)
			{
				textTargetRegion->getWidget()->setCaption(regionObj->getRegionNameStr16());
			}

		}

		//��ʼ����ԱUI
		UIReFreshMemberList();
		UIReFreshHost();
	}

	//------------------------------------------------------------------------
	void UICampaignInfoNew::UIReFreshMemberList()
	{
		Int nCount = mMemberList.getDataSet()->size();

		for (Int i=0; i<nCount; i++)
		{
			UICampaignInfoNewSingle* memberInfo = mMemberList.getData(i);
			if (!memberInfo->empty())
			{
				UIReFreshMemberByIndex(i, memberInfo);
			}
		}
	}

	//------------------------------------------------------------------------
	void UICampaignInfoNew::UIReFreshMemberByIndex(Int index, UICampaignInfoNewSingle* memberInfo)
	{
		DYNAMIC_ASSERT(NULL != memberInfo && index >= 0 && index <= 9);

		Int imageIndex = index + 1;

		Color nameColor;
		if (memberInfo->isMe == true)
		{
			nameColor = Color(1,1,0,0);

			IButton* btnConfirm = getLayout()->getButton("Btn_Confirm");

			if (true == memberInfo->isReady)
			{
				btnConfirm->getWidget()->setCaption(L"ȡ��׼��");
			}
			else
			{
				btnConfirm->getWidget()->setCaption(L"׼��");
			}
		}
		else
		{
			nameColor = Color(1,1,1,0);
		}
		if (true == memberInfo->empty())
			return;

		////��׼��������
		//{
		//	char imageStr[32] = "";
		//	sprintf(imageStr, "Image_Other_Ready_%d", imageIndex);

		//	IImage* back_activeImage = getLayout()->getImage(imageStr);
		//	back_activeImage->getWidget()->setVisible(true);

		//	if (true == memberInfo->empty())
		//	{
		//		//���λ���ǿյ�
		//		back_activeImage->getWidget()->setVisible(false);
		//	}
		//}

		////����ͼƬ����
		//{
		//	char imageStr[32] = "";
		//	sprintf(imageStr, "other_back_active_%d", imageIndex);

		//	IImage* back_activeImage = getLayout()->getImage(imageStr);
		//	back_activeImage->getWidget()->setVisible(true);

		//	if (true == memberInfo->empty())
		//	{
		//		//���λ���ǿյ�
		//		back_activeImage->getWidget()->setVisible(false);
		//		return;
		//	}
		//}

		//ͷ�� ��С��
		{
			const ArtIconResCsvInfo* tempResInfo =ArtIconResCsv::getInstance().getIconArtResInfo(memberInfo->charArtIcon);
			DYNAMIC_ASSERT(NULL != tempResInfo);
			char imageStr[32] = "";
			sprintf( imageStr, "other_head_%d", imageIndex);
			IImage *headimg = getLayout()->getImage(imageStr);
			headimg->setItemGroup(tempResInfo->SmallGroupName);
			headimg->setItemResource(tempResInfo->SmallResName);
			headimg->setItemName(tempResInfo->SmallItemName);
		}

		//�ȼ�
		{
			char imageStr[32] = "";
			sprintf( imageStr, "other_lvtest_%d", imageIndex);

			IText* text_level = getLayout()->getText(imageStr);

			wchar_t outputStr[32] = L"";
			swprintf( outputStr, L"%d", memberInfo->level);
			text_level->getWidget()->setCaption(outputStr);
			text_level->setTextColour(nameColor);
		}

		//����
		{
			char imageStr[32] = "";
			sprintf( imageStr, "other_nametest_%d", imageIndex);

			IText* text_name = getLayout()->getText(imageStr);
			text_name->getWidget()->setCaption(memberInfo->clanName);
			text_name->setTextColour(nameColor);
		}
		
		//HP
		{
			char imageStr[32] = "";
			sprintf( imageStr, "other_HP_%d", imageIndex);

			IProgress* image_hp = getLayout()->getProgress(imageStr);
			if(memberInfo->maxHP <= 0)
			{
				memberInfo->maxHP = 1;
			}
			image_hp->setProgressPosition(memberInfo->curHP/memberInfo->maxHP);
		}

		//MP
		{
			char imageStr[32] = "";
			sprintf( imageStr, "other_MP_%d", imageIndex);

			IProgress* image_hp = getLayout()->getProgress(imageStr);
			if(memberInfo->maxMP <= 0)
			{
				memberInfo->maxMP = 1;
			}
			image_hp->setProgressPosition(memberInfo->curMP/memberInfo->maxMP);
		}
		
		//׼��
		{
			char imageStr[32] = "";
			sprintf( imageStr, "Image_Other_Ready_%d", imageIndex);

			IImage* image_Ready = getLayout()->getImage(imageStr);
			image_Ready->getWidget()->setVisible(memberInfo->isReady);
		}

	}

	//------------------------------------------------------------------------
	void UICampaignInfoNew::UIReFreshHost()
	{
		DYNAMIC_ASSERT(mLearder.getDataSet()->size() == 1);

		UICampaignInfoNewSingle* leaderInfo = mLearder.getDataSet()->begin()->second;

		
		Color nameColor;
		if (leaderInfo->isMe == true)
		{
			nameColor = Color(1,1,0,0);
		}
		else
		{
			nameColor = Color(1,1,1,0);
		}
		if (true == leaderInfo->empty())
			return;
		////����ͼƬ����
		//{
		//	IImage* back_activeImage = getLayout()->getImage("main_back_active");
		//	back_activeImage->getWidget()->setVisible(true);

		//	if (true == leaderInfo->empty())
		//	{
		//		//���λ���ǿյ�
		//		back_activeImage->getWidget()->setVisible(false);
		//		return;
		//	}
		//}

		//ͷ�� ����
		{
			const ArtIconResCsvInfo* tempResInfo =ArtIconResCsv::getInstance().getIconArtResInfo(leaderInfo->charArtIcon);
			DYNAMIC_ASSERT(NULL != tempResInfo);
			IImage *headimg = getLayout()->getImage("main_head");
			headimg->setItemGroup(tempResInfo->GroupName);
			headimg->setItemResource(tempResInfo->ResName);
			headimg->setItemName(tempResInfo->ItemName);
		}

		//�ȼ�
		{
			//�ȼ�
			{
				IText* text_level = getLayout()->getText("main_lvtest");

				wchar_t outputStr[32] = L"";
				swprintf( outputStr, L"%d", leaderInfo->level);
				text_level->getWidget()->setCaption(outputStr);
				text_level->setTextColour(nameColor);
			}
		}

		//����
		{
			IText* text_name = getLayout()->getText("main_nametest");
			text_name->getWidget()->setCaption(leaderInfo->clanName);
			text_name->setTextColour(nameColor);
		}


		//HP
		{

			IProgress* image_hp = getLayout()->getProgress("main_HP");
			if (leaderInfo->maxHP == 0)
			{
				leaderInfo->maxHP = 1;
			}
			image_hp->setProgressPosition(leaderInfo->curHP/leaderInfo->maxHP);
		}

		//MP
		{
			IProgress* image_mp = getLayout()->getProgress("main_MP");
			if (leaderInfo->maxMP == 0)
			{
				leaderInfo->maxMP = 1;
			}
			image_mp->setProgressPosition(leaderInfo->curMP/leaderInfo->maxMP);
		}
		IImage *readyImg = getLayout()->getImage("main_ready");
		readyImg->getWidget()->setVisible(true);

		//������־
		IImage *ledImg = getLayout()->getImage("main_leader");
		ledImg->getWidget()->setVisible(true);

	}

	//------------------------------------------------------------------------
	void UICampaignInfoNew::createMemberForTest()
	{
		for (Int i=POSITION_1; i<POSITION_MAX; ++i)
		{
			UICampaignInfoNewSingle tempInfo;
			tempInfo.charArtIcon = 30016;
			tempInfo.level = i;
			tempInfo.curHP = i*10;
			tempInfo.maxHP = 100;
			tempInfo.curMP = i*10 + 10;
			tempInfo.maxMP = 100;
			
			wchar_t clanName[32] = L"";
			swprintf( clanName, L"����%d", i);

			tempInfo.clanName.append(clanName);
			addMemberInfo(i, &tempInfo);
		}

		UICampaignInfoNewSingle tempInfo;
		tempInfo.charArtIcon = 30016;
		tempInfo.level = 10;
		tempInfo.curHP = 10*10;
		tempInfo.maxHP = 100;
		tempInfo.curMP = 10*10 + 10;
		tempInfo.maxMP = 100;

		wchar_t clanName[32] = L"";
		swprintf( clanName, L"����%d", 10);

		tempInfo.clanName.append(clanName);
		modifyLeaderInfo(&tempInfo);
	}

	//------------------------------------------------------------------------
	void UICampaignInfoNew::addMemberInfo(Int index, UICampaignInfoNewSingle* memberInfo)
	{
		UICampaignInfoNewSingle* info = mMemberList.getData(index);
		DYNAMIC_ASSERT(true == info->empty());
		modifyMemberInfo(index, memberInfo);
	}

	//------------------------------------------------------------------------
	void UICampaignInfoNew::modifyMemberInfo(Int index, UICampaignInfoNewSingle* memberInfo)
	{
		UICampaignInfoNewSingle* info = mMemberList.getData(index);
		
		info->charArtIcon	= memberInfo->charArtIcon;
		info->level		= memberInfo->level;
		info->clanName	= memberInfo->clanName;
		info->curHP		= memberInfo->curHP;
		info->maxHP		= memberInfo->maxHP;
		info->curMP		= memberInfo->curMP;
		info->maxMP		= memberInfo->maxMP;
		info->isMe		= memberInfo->isMe;
		info->isReady	= memberInfo->isReady;
	}

	//------------------------------------------------------------------------
	void UICampaignInfoNew::clearMemberInfo(Int index)
	{
		UICampaignInfoNewSingle* info = mMemberList.getData(index);
		info->clear();
	}

	//------------------------------------------------------------------------
	void UICampaignInfoNew::clearAllCampaignInfo()
	{
		//��� һ�����
		{
			std::map<Int, UICampaignInfoNewSingle*>* memberList = mMemberList.getDataSet();
			for (std::map<Int, UICampaignInfoNewSingle*>::iterator iter = memberList->begin(); iter != memberList->end(); ++iter)
			{
				iter->second->clear();
			}
		}
		
		//��շ���
		{
			std::map<Int, UICampaignInfoNewSingle*>* memberList = mLearder.getDataSet();
			for (std::map<Int, UICampaignInfoNewSingle*>::iterator iter = memberList->begin(); iter != memberList->end(); ++iter)
			{
				iter->second->clear();
			}
		}

	}

	//------------------------------------------------------------------------
	UICampaignInfoNewSingle* UICampaignInfoNew::getMemberInfoByPosition(Int position)
	{
		return mMemberList.getData(position);
	}	

	//------------------------------------------------------------------------
	void UICampaignInfoNew::modifyLeaderInfo(UICampaignInfoNewSingle* memberInfo)
	{
		UICampaignInfoNewSingle* info = mLearder.getDataSet()->begin()->second;
		DYNAMIC_ASSERT(true == info->empty());

		info->charArtIcon	= memberInfo->charArtIcon;
		info->level		= memberInfo->level;
		info->clanName	= memberInfo->clanName;
		info->curHP		= memberInfo->curHP;
		info->maxHP		= memberInfo->maxHP;
		info->curMP		= memberInfo->curMP;
		info->maxMP		= memberInfo->maxMP;
		info->isMe		= memberInfo->isMe;
	}
	//------------------------------------------------------------------------
	void  UICampaignInfoNew::restore()
	{
		/*UICampaignInfoNew::getInstance().clearAllCampaignInfo();
		UICampaignInfoNew::getInstance().UIClear();*/
		UIClear();
	}
	//------------------------------------------------------------------------
	void  UICampaignInfoNew::UIClear()
	{
		UIClearLeaderInfo();
		Int nCount = mMemberList.getDataSet()->size();
		for (Int i =0; i < nCount ; i++)
		{
			UIClearMemberInfoByIndex(i);
		}
	}
	//------------------------------------------------------------------------
	void  UICampaignInfoNew::UIClearLeaderInfo()
	{
		DYNAMIC_ASSERT(mLearder.getDataSet()->size() == 1);
		UICampaignInfoNewSingle* leaderInfo = mLearder.getDataSet()->begin()->second;
		if (true == leaderInfo->empty())
			return;
		//ͷ��
		IImage *headimg = getLayout()->getImage("main_head");
		headimg->setTexture("", "", "");
		//׼����־
		IImage *readyImg = getLayout()->getImage("main_ready");
		readyImg->getWidget()->setVisible(false);
		//������־
		IImage *ledImg = getLayout()->getImage("main_leader");
		ledImg->getWidget()->setVisible(false);
		//�ȼ�
		IText *lvText = getLayout()->getText("main_lvtest");
		lvText->getWidget()->setCaption(L"");
		//����
		IText *nameText = getLayout()->getText("main_nametest");
		nameText->getWidget()->setCaption(L"");
		//Ѫ��
		IProgress* image_hp = getLayout()->getProgress("main_HP");
		image_hp->setProgressPosition(0);
		//����
		IProgress* image_mp = getLayout()->getProgress("main_MP");
		image_mp->setProgressPosition(0);	
	}
	//------------------------------------------------------------------------
	void  UICampaignInfoNew::UIClearMemberInfoByIndex(Int index)
	{
		Int nIndex = index + 1;
		char tempStr[32] = "";
		//ͷ��
		sprintf( tempStr, "other_head_%d", nIndex);
		IImage *headimg = getLayout()->getImage(tempStr);
		headimg->setTexture("", "", "");
		//׼����־
		sprintf( tempStr, "Image_Other_Ready_%d", nIndex);
		IImage *readyImg = getLayout()->getImage(tempStr);
		readyImg->getWidget()->setVisible(false);
		//������־
		sprintf( tempStr, "other_leader_%d", nIndex);
		IImage *ledImg = getLayout()->getImage(tempStr);
		ledImg->getWidget()->setVisible(false);
		//�ȼ�
		sprintf( tempStr, "other_lvtest_%d", nIndex);
		IText *lvText = getLayout()->getText(tempStr);
		lvText->getWidget()->setCaption(L"");
		//����
		sprintf( tempStr, "other_nametest_%d", nIndex);
		IText *nameText = getLayout()->getText(tempStr);
		nameText->getWidget()->setCaption(L"");
		//Ѫ��
		sprintf( tempStr, "other_HP_%d", nIndex);
		IProgress* image_hp = getLayout()->getProgress(tempStr);
		image_hp->setProgressPosition(0);
		//����
		sprintf( tempStr, "other_MP_%d", nIndex);
		IProgress* image_mp = getLayout()->getProgress(tempStr);
		image_mp->setProgressPosition(0);	
	}
}