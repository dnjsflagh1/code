//***************************************************************************************************
#include "stdafx.h"
#include "UIRecruitGeneral.h"
#include "UIMessageBox.h"
#include "ArtIconResCsv.h"
#include "CGameMessageConfig.h"
#include "CPlayerCharacter.h"
#include "CGeneralRecruitNetPacketProcessor.h"
#include "CharacterList.h"
#include "CalendarInfo.h"
#include "UIYesNoMsgBox.h"
//***************************************************************************************************
namespace MG
{
	UIRecruitGeneral::UIRecruitGeneral()
		:mUpdateTime(0)
		,mGeneralRecruitId(0)
		,mWantRecruitIndex(-1)
	{
		//test();
	}

	//----------------------------------------------------------------------------------------
	UIRecruitGeneral::~UIRecruitGeneral()
	{

	}

	//----------------------------------------------------------------------------------------
	void UIRecruitGeneral::test()
	{
		for (Int i=0; i<5; ++i)
		{
			NetRandomGeneralInfo data;
			data.charTemplateId = 10002 + i;
			//data.artIconId = 30009 + i;
			//data.age = 1 + i;
			//data.job = 1 + i;
			//data.str = 1 + i;
			//data.gym = 1 + i;
			//data.wit = 1 + i;
			//data.affair = 1 + i;

			loadGeneralInfos(&data);
		}
	}

	//----------------------------------------------------------------------------------------
	void UIRecruitGeneral::setEvent()
	{
		IButton* pButton = NULL;
		IImage* pIcon = NULL;
		char tempStr[32] = "";

		IButton* btnUpdate = getLayout()->getButton("update_btn");
		DYNAMIC_ASSERT(btnUpdate);
		btnUpdate->getWidget()->setMouseButtonClickEvent(onEventUpdateBtn);

		for(int i = 1; i <= 5; i++)
		{
			Sprintf_s(tempStr, 32, "btn_%d", i);
			pButton = getLayout()->getButton(tempStr);
			DYNAMIC_ASSERT(pButton);
			pButton->getWidget()->setMouseButtonClickEvent(onEventRecruitBtn);
		}
	}
	//--------------------------------------------------------------------------------------
	void UIRecruitGeneral::update(Flt delta)
	{
		IText* txt = getLayout()->getText("update_time_txt");
		DYNAMIC_ASSERT(txt);
		//�ӷ�����ȡˢ��ʱ��
		txt->getWidget()->setCaption(L"");
	}
	//--------------------------------------------------------------------------------------
	void UIRecruitGeneral::restore()
	{
		mWantRecruitIndex = -1;
	}
	//--------------------------------------------------------------------------------------
	bool UIRecruitGeneral::openGui()
	{
		if (false == UIObject::isOpen())
		{
			UIObject::openGui();
			UIFresh();
		}
		else
		{
			UIObject::closeGui();
		}

		return false;
	}
	//--------------------------------------------------------------------------------------
	void UIRecruitGeneral::onEventUpdateBtn(void* widget)
	{
		U32 generalRecruitId = UIRecruitGeneral::getInstance().getGeneralRecruitId();
		CGeneralRecruitNetPacketProcessor::getInstance().sendFreshRandomGeneral(generalRecruitId);
		//CGeneralRecruitNetPacketProcessor::getInstance().sendFreshRandomGeneral();
#if 0
		//ʣ��ˢ��ʱ��Ϊ0��ˢ�³�Ա�б�
		if(UIRecruitGeneral::getInstance().mUpdateTime == 0)
		{
			//UIRecruitGeneral::getInstance().loadGeneralInfos();
		}
		else
		{
			//���򵯳�ˢ��ʱ��û�е�����ʾ����ˢ��ui�б�
			UIMessageBox::getInstance().showHint(L"ˢ��ʱ��δ��������ˢ�£�");
		}
#endif
	}
	//--------------------------------------------------------------------------------------
	void UIRecruitGeneral::onEventRecruitBtn(void* widget)
	{
		if (true == UIRecruitGeneral::getInstance().getGeneralList()->empty())
		{
			UIMessageBox::getInstance().showHint(L"��ˢ�º���ļ�佫");
			return;
		}

		IWidget* pwidget = (IWidget*)widget;
		DYNAMIC_ASSERT(pwidget != NULL);

		IAny* anyData = pwidget->getUserData();
		DYNAMIC_ASSERT(anyData);
		RecruitGeneralInfo* generalInfo = anyData->castType<RecruitGeneralInfo>();
		DYNAMIC_ASSERT(NULL != generalInfo);

		if (generalInfo->hasRecruit == true)
		{
			UIMessageBox::getInstance().showHint(L"������ļ�����佫");
			return;
		}
		
		UIRecruitGeneral::getInstance().mWantRecruitIndex = generalInfo->index;
		Char16 realContent[1024] = {0};

		Str16 tempTitle = CGameMessageConfig::getInstance().getStr(L"recruitgeneral",L"recruitgeneralTitle1",L"");
		Str16 tempContent = CGameMessageConfig::getInstance().getStr(L"recruitgeneral",L"recruitgeneral1",L"");
		swprintf_s(realContent,1024,tempContent.c_str(),generalInfo->name.c_str());
		UIYesNoMsgBox::getInstance().showHint(tempTitle,realContent, (void*)(&UIRecruitGeneral::getInstance()),OnSendGeneralRecruit, NULL, NULL);
	}
	//----------------------------------------------------------------------------------------------------------
	void UIRecruitGeneral::OnSendGeneralRecruit(void* arg)
	{
		//������������ļ���佫id
		if (UIRecruitGeneral::getInstance().mWantRecruitIndex >= 0)
		{
			CGeneralRecruitNetPacketProcessor::getInstance().sendGeneralRecruit((RECRUIT_POSITION)UIRecruitGeneral::getInstance().mWantRecruitIndex);
		}
	}
	//---------------------------------------------------------------------------------------------------------
	void UIRecruitGeneral::UIClear()
	{
		char tempStr[32] = "";
		Char16 tempMsg[32] = L"";
		IButton* btn = NULL;
		IImage* img = NULL;
		IText*	txt = NULL;

		for (Int i=1; i<=5; ++i)
		{
			//ͷ��
			Sprintf_s(tempStr, 32, "img_%d", i);
			img = getLayout()->getImage(tempStr);
			DYNAMIC_ASSERT(img);
			img->setTexture("", "", "");

			//����
			Sprintf_s(tempStr, 32, "name_%d", i);
			txt = getLayout()->getText(tempStr);
			DYNAMIC_ASSERT(txt);
			//���ֲ��ָ���Ʒ����ʾ��ͬ����ɫ
			txt->getWidget()->setCaption(L"");
			//����
			swprintf_s(tempMsg, 32, L"%d",0 );
			Sprintf_s(tempStr, 32, "age_%d", i);
			txt = getLayout()->getText(tempStr);
			DYNAMIC_ASSERT(txt);
			txt->getWidget()->setCaption(L"");
			//�Ա�
			Sprintf_s(tempStr, 32, "class_%d", i);
			txt = getLayout()->getText(tempStr);
			DYNAMIC_ASSERT(txt);
			txt->getWidget()->setCaption(L"");
			//����
			Sprintf_s(tempStr, 32, "str_%d", i);
			txt = getLayout()->getText(tempStr);
			DYNAMIC_ASSERT(txt);
			txt->getWidget()->setCaption(L"");
			//����
			Sprintf_s(tempStr, 32, "gym_%d", i);
			txt = getLayout()->getText(tempStr);
			DYNAMIC_ASSERT(txt);
			txt->getWidget()->setCaption(L"");
			//��ı
			Sprintf_s(tempStr, 32, "wit_%d", i);
			txt = getLayout()->getText(tempStr);
			DYNAMIC_ASSERT(txt);
			txt->getWidget()->setCaption(L"");
			//����
			Sprintf_s(tempStr, 32, "affair_%d", i);
			txt = getLayout()->getText(tempStr);
			DYNAMIC_ASSERT(txt);
			txt->getWidget()->setCaption(L"");

			Sprintf_s(tempStr, 32, "btn_%d", i);
			btn = getLayout()->getButton(tempStr);
			DYNAMIC_ASSERT(btn);

			btn->getWidget()->setUserData(0);
		}
	}

	void UIRecruitGeneral::UIFresh()
	{
		if (isOpen() == false)
		{
			return;
		}

		UIClear();
		Int i = 0;
		char tempStr[32] = "";
		Char16 tempMsg[32] = L"";
		IButton* btn = NULL;
		IImage* img = NULL;
		IText*	txt = NULL;

		std::map<Int, RecruitGeneralInfo>::iterator iter;
		for (iter = mRecruitGeneralList.begin(); iter != mRecruitGeneralList.end(); ++iter)
		{
			RecruitGeneralInfo* temp = &(iter->second);
			
			i++;

			Sprintf_s(tempStr, 32, "btn_%d", i);
			btn = getLayout()->getButton(tempStr);
			DYNAMIC_ASSERT(btn);

			btn->getWidget()->setUserData(*temp);
			if (temp->hasRecruit == true)
			{
				//��ļ�����佫�� ֱ������ ����
				continue;
			}

			
			Sprintf_s(tempStr, 32, "btn_%d", i);
			btn = getLayout()->getButton(tempStr);
			DYNAMIC_ASSERT(btn);

			//ͷ��
			Sprintf_s(tempStr, 32, "img_%d", i);
			img = getLayout()->getImage(tempStr);
			DYNAMIC_ASSERT(img);
			const ArtIconResCsvInfo* tempIconResInfo = ArtIconResCsv::getInstance().getIconArtResInfo(temp->artIconId);
			img->setTexture(tempIconResInfo->ResName, tempIconResInfo->GroupName, tempIconResInfo->ItemName);

			//����
			Sprintf_s(tempStr, 32, "name_%d", i);
			txt = getLayout()->getText(tempStr);
			DYNAMIC_ASSERT(txt);
			//���ֲ��ָ���Ʒ����ʾ��ͬ����ɫ
			txt->setTextColour(temp->nameColor);
			txt->getWidget()->setCaption(temp->name);

			txt->setTextColour(ColorSet::white());
			//����
			swprintf_s(tempMsg, 32, L"%d/%d",temp->age, temp->lifeSpan);
			Sprintf_s(tempStr, 32, "age_%d", i);
			txt = getLayout()->getText(tempStr);
			DYNAMIC_ASSERT(txt);
			txt->getWidget()->setCaption(tempMsg);
			//�Ա�
			Sprintf_s(tempStr, 32, "class_%d", i);
			txt = getLayout()->getText(tempStr);
			DYNAMIC_ASSERT(txt);
			txt->getWidget()->setCaption(temp->sex);
			//����
			swprintf_s(tempMsg, 32, L"%d",temp->str );
			Sprintf_s(tempStr, 32, "str_%d", i);
			txt = getLayout()->getText(tempStr);
			DYNAMIC_ASSERT(txt);
			txt->getWidget()->setCaption(tempMsg);
			//����
			swprintf_s(tempMsg, 32, L"%d",temp->gym );
			Sprintf_s(tempStr, 32, "gym_%d", i);
			txt = getLayout()->getText(tempStr);
			DYNAMIC_ASSERT(txt);
			txt->getWidget()->setCaption(tempMsg);
			//��ı
			swprintf_s(tempMsg, 32, L"%d",temp->wit );
			Sprintf_s(tempStr, 32, "wit_%d", i);
			txt = getLayout()->getText(tempStr);
			DYNAMIC_ASSERT(txt);
			txt->getWidget()->setCaption(tempMsg);
			//����
			swprintf_s(tempMsg, 32, L"%d",temp->affair );
			Sprintf_s(tempStr, 32, "affair_%d", i);
			txt = getLayout()->getText(tempStr);
			DYNAMIC_ASSERT(txt);
			txt->getWidget()->setCaption(tempMsg);

			
		}
	}

	void UIRecruitGeneral::clearRecruitGeneralList()
	{
		mRecruitGeneralList.clear();

		UIRecruitGeneral::getInstance().resetRandPosition();
	}

	//--------------------------------------------------------------------------------------
	bool UIRecruitGeneral::loadGeneralInfos(NetRandomGeneralInfo* data)
	{
		Int position = getRandPosition();
		const CharacterTempInfo* charTempInfo = CharacterTemplate::getInstance().getCharacterTempInfo(data->charTemplateId);
		DYNAMIC_ASSERT(NULL != charTempInfo);
		Str16 sex;
		if (GENDER_TYPE_MAN == charTempInfo->getGenrealGenderType())
		{
			sex = L"��";
		}
		else if(GENDER_TYPE_WOMAN == charTempInfo->getGenrealGenderType())
		{
			sex = L"Ů";
		}
		else if(GENDER_TYPE_NONE_SEX == charTempInfo->getGenrealGenderType())
		{
			DYNAMIC_ASSERT(0);
			sex = L"���Ա�";
		}
		else
		{
			DYNAMIC_ASSERT(0);
		}

		Color nameColor = ColorSet::red();
		const POWERFUL_TYPE powerfulType= charTempInfo->getGenrealPowerfulType();
		if (POWERFUL_TYPE_FIRST == powerfulType)
		{
			nameColor = ColorSet::purple();
		}
		else if (POWERFUL_TYPE_SECOND == powerfulType)
		{
			nameColor = ColorSet::purple();
		}
		else if (POWERFUL_TYPE_THIRD == powerfulType)
		{
			nameColor = ColorSet::green();
		}
		else if (POWERFUL_TYPE_NORMAL == powerfulType)
		{
			nameColor = ColorSet::white();
		}
		else
		{
			DYNAMIC_ASSERT(0);
		}


		CPlayerCharacter playerCharacter;
		PlayerCharacterData tempData;

		tempData.mCharacterTemplateID = data->charTemplateId;
		for (Int i=0; i<DB_RECORD_ATTR_NUM; ++i)
		{
			tempData.charAttrRand[i] = data->charAttrRand[i];
			tempData.charAttrRandAdd[i] = data->charAttrRandAdd[i];
		}
		tempData.charAttrAppendId = data->charAttrAppendId;
		tempData.charAttrAppendLvlAddId = data->charAttrAppendLvlId;

		playerCharacter.init(&tempData);


		RecruitGeneralInfo generalInfo;
		generalInfo.charTemplateId 	= data->charTemplateId;
		generalInfo.artIconId 	= charTempInfo->getCharacterArtIconId();
		generalInfo.name		= data->name;
		generalInfo.nameColor	= nameColor;
		generalInfo.age 		= data->age;
		generalInfo.lifeSpan 	= data->lifeSpan;
		generalInfo.sex			= sex;
		generalInfo.str 		= playerCharacter.getAttributeSystem()->getFanalValue(ATTR_ID_Talent1);
		generalInfo.gym 		= playerCharacter.getAttributeSystem()->getFanalValue(ATTR_ID_Talent2);
		generalInfo.wit 		= playerCharacter.getAttributeSystem()->getFanalValue(ATTR_ID_Talent3);
		generalInfo.affair		= playerCharacter.getAttributeSystem()->getFanalValue(ATTR_ID_Talent4);
		generalInfo.index		= data->index;

		//mRecruitGeneralList.push_back(generalInfo);
		std::map<Int, RecruitGeneralInfo>::iterator iter = mRecruitGeneralList.find(position);
		if (iter != mRecruitGeneralList.end())
		{
			//�ظ�
			DYNAMIC_ASSERT(0);
		}
		mRecruitGeneralList[position] = generalInfo;

#if 0
		//�ӷ�����ǻ�ȡһ�����ݣ�ˢ��ui
		std::vector<RecruitGeneralInfo> tempInfoList; //�ӷ�������ȡ���з�װ
		DYNAMIC_ASSERT(tempInfoList.size() == 5);
		std::vector<RecruitGeneralInfo>::iterator iter;
		Int i = 1;
		char tempStr[32] = "";
		Char16 tempMsg[32] = L"";
		IButton* btn = NULL;
		IImage* img = NULL;
		IText*	txt = NULL;
		for (iter = tempInfoList.begin(); iter != tempInfoList.end(); ++iter)
		{
			RecruitGeneralInfo temp = *iter;
			//ͷ��
			Sprintf_s(tempStr, 32, "img_%d", i);
			img = getLayout()->getImage(tempStr);
			DYNAMIC_ASSERT(img);
			const ArtIconResCsvInfo* tempIconResInfo = ArtIconResCsv::getInstance().getIconArtResInfo(temp.imgIconId);
			img->setTexture(tempIconResInfo->ResName, tempIconResInfo->GroupName, tempIconResInfo->ItemName);
			
			//����
			Sprintf_s(tempStr, 32, "name_%d", i);
			txt = getLayout()->getText(tempStr);
			DYNAMIC_ASSERT(txt);
			//���ֲ��ָ���Ʒ����ʾ��ͬ����ɫ
			txt->getWidget()->setCaption(temp.name);
			//����
			swprintf_s(tempMsg, 32, L"%d",temp.age );
			Sprintf_s(tempStr, 32, "age_%d", i);
			txt = getLayout()->getText(tempStr);
			DYNAMIC_ASSERT(txt);
			txt->getWidget()->setCaption(tempMsg);
			//ְҵ
			swprintf_s(tempMsg, 32, L"formulatype%d", temp.job);
			Sprintf_s(tempStr, 32, "class_%d", i);
			txt = getLayout()->getText(tempStr);
			DYNAMIC_ASSERT(txt);
			txt->getWidget()->setCaption( CGameMessageConfig::getInstance().getStr(L"CharacterJudgeTemplate", tempMsg, tempMsg) );;
			//����
			swprintf_s(tempMsg, 32, L"%d",temp.str );
			Sprintf_s(tempStr, 32, "str_%d", i);
			txt = getLayout()->getText(tempStr);
			DYNAMIC_ASSERT(txt);
			txt->getWidget()->setCaption(tempMsg);
			//����
			swprintf_s(tempMsg, 32, L"%d",temp.gym );
			Sprintf_s(tempStr, 32, "gym_%d", i);
			txt = getLayout()->getText(tempStr);
			DYNAMIC_ASSERT(txt);
			txt->getWidget()->setCaption(tempMsg);
			//��ı
			swprintf_s(tempMsg, 32, L"%d",temp.wit );
			Sprintf_s(tempStr, 32, "wit_%d", i);
			txt = getLayout()->getText(tempStr);
			DYNAMIC_ASSERT(txt);
			txt->getWidget()->setCaption(tempMsg);
			//����
			swprintf_s(tempMsg, 32, L"%d",temp.affair );
			Sprintf_s(tempStr, 32, "affair_%d", i);
			txt = getLayout()->getText(tempStr);
			DYNAMIC_ASSERT(txt);
			txt->getWidget()->setCaption(tempMsg);

			Sprintf_s(tempStr, 32, "btn_%d", i);
			btn = getLayout()->getButton(tempStr);
			DYNAMIC_ASSERT(btn);
			btn->getWidget()->setUserData(temp.generalId);

			i++;

			if (i == 5)
			{
				break;
			}
		}
#endif
		return true;
	}

	void UIRecruitGeneral::setGeneralRecruitId(U32 generalRecruitId)
	{ 
		if (mGeneralRecruitId != generalRecruitId)
		{
			clearRecruitGeneralList();
		}

		mGeneralRecruitId = generalRecruitId; 
		if (false == isOpen())
		{
			openGui();
			UIFresh();
		}
	}

	U32 UIRecruitGeneral::getGeneralRecruitId() const
	{
		return mGeneralRecruitId;
	}

	RecruitGeneralInfo*	UIRecruitGeneral::getGeneralInfoByIndex(U32 index)
	{
		std::map<Int, RecruitGeneralInfo>::iterator iter= mRecruitGeneralList.begin();
		for (; iter != mRecruitGeneralList.end(); ++iter)
		{
			if (iter->second.index == index)
			{
				return &(iter->second);
			}
		}
		
		return NULL;
	}

	std::map<Int, RecruitGeneralInfo>* UIRecruitGeneral::getGeneralList()
	{
		return &mRecruitGeneralList;
	}

	Int UIRecruitGeneral::getRandPosition()
	{
		Int result = -1;
		Int num = mPositionList.size();
		if (0 == num)
		{
			DYNAMIC_ASSERT(0);
		}
		else if(1 == num)
		{
			result = mPositionList.at(0);
		}
		else
		{
			U32 randNum = MGRandom::getInstance().rand_ab_One(0, num);

			result = mPositionList.at(randNum);
			for (std::vector<Int>::iterator iter = mPositionList.begin(); iter != mPositionList.end(); ++iter)
			{
				if (*iter == result)
				{
					mPositionList.erase(iter);
					break;
				}
			}
		}

		DYNAMIC_ASSERT(result >= 0 && result < 5);
		return result;
	}

	void UIRecruitGeneral::resetRandPosition()
	{
		mPositionList.clear();
		for (Int i=0; i<5; ++i)
		{
			mPositionList.push_back(i);
		}
	}

}