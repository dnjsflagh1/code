//*************************************************************************************
#include "stdafx.h"
#include "UICreateCharacter.h"
#include "LoginManager.h"
#include "CPlayerCharacter.h"
#include "CPlayer.h"
#include "ClientMain.h"
#include "LoginScreen.h"
#include "PlayerCharacterData.h"
#include "SimplePlayerCharacter.h"
#include "CharacterList.h"
#include "CharacterResourceConfig.h"
#include "ArtIconResCsv.h"
#include "BanKeyword.h"
#include "UIMessageBox.h"
#include "UIYesNoMsgBox.h"
#include "CGameMessageConfig.h"
#include "CharacterRandNameCsv.h"
//*************************************************************************************
namespace MG
{

	UICreateCharacter::~UICreateCharacter()
	{  
	}

    void UICreateCharacter::setEvent()
    {
         IButton* buttonconfirm = getLayout()->getButton("btn_ok");
         assert(buttonconfirm);
         buttonconfirm->getWidget()->setMouseButtonClickEvent( OnClickConfirm );

         IButton* buttonreset = getLayout()->getButton("btn_reset");
		 assert(buttonreset);
		 buttonreset->getWidget()->setMouseButtonClickEvent(OnRest);

         IButton* buttonrandom = getLayout()->getButton("btn_random");
		 assert(buttonrandom);
		 buttonrandom->getWidget()->setMouseButtonClickEvent(OnRandom);

		 IButton* buttonleft = getLayout()->getButton("btn_left");
		 assert(buttonleft);
		 buttonleft->getWidget()->setMouseButtonClickEvent( OnClickLeft );

		 IButton* buttonright = getLayout()->getButton("btn_right");
		 assert(buttonright);
		 buttonright->getWidget()->setMouseButtonClickEvent( OnClickRight );
    }
    //-------------------------------------------------------------------
    void UICreateCharacter::OnClickConfirm( void* widget )
    {
         assert(widget);
		
		 IEdit* editname = UICreateCharacter::getInstance().getLayout()->getEdit("edt_name");
		 assert(editname);
		 Str16 tempEditname = editname->getCaption();
		 if ( tempEditname.length() < 1 )
		 {
			 //错误提示
			 UIMessageBox::getInstance().showHint(L"请输入角色名!");
			 return;
		 }
		 if (BanKeyword<BanKeywordName>::getInstance().isBan(const_cast<Char16*>(tempEditname.c_str())) || BanKeyword<BanKeywordEnter>::getInstance().isBan(const_cast<Char16*>(tempEditname.c_str())) )
		 {
			 UIMessageBox::getInstance().showHint(L"名称中有非法字符!");
			 return;
		 }

		 if ( LoginScreen::getInstance().getSelectCharIndex() == -1 )
		 {
			 UIMessageBox::getInstance().showHint(L"请选择一名角色!");
			 return;
		 }
		 CClan* pClan = CPlayer::getInstance().getActiveClan();
		 assert(pClan);
		 Str16 jwName= pClan->getClanHomeLandName();
		 Str16 clanName = pClan->getName();
		 
		 Char16 realContent[1024] = {0};
		 
		 Str16 tempTitle = CGameMessageConfig::getInstance().getStr(L"createcharacter",L"createcharactertitle",L"");
		 Str16 tempContent = CGameMessageConfig::getInstance().getStr(L"createcharacter",L"createcharactercontent",L"");
		 swprintf_s(realContent,1024,tempContent.c_str(),clanName.c_str(), tempEditname.c_str(),jwName.c_str(),clanName.c_str());

		 UIYesNoMsgBox::getInstance().showHint(tempTitle,Str16(realContent),
			 (void*)(&UICreateCharacter::getInstance()),onNotificateOK,(void*)(&UICreateCharacter::getInstance()),onNotificateCancle);

    }
    //-------------------------------------------------------------------
    void UICreateCharacter::sendCharacterData()
    {
		SimpleCharacterResInfo* simpleData = NULL;
		
		if ( mSelectCharResourceID >= 0 && mSelectCharResourceID < mCharTemplates.size() )
		{
			simpleData = &mCharTemplates[mSelectCharResourceID];
		}

		if ( simpleData )
		{
			IEdit* editname = getLayout()->getEdit("edt_name");
			assert(editname);
			Str16 tempEditname = editname->getCaption();

			PlayerCharacterData characterData;
			characterData.mName = tempEditname;
			characterData.charArtIcon = simpleData->articonid;

			characterData.charSurName = CPlayer::getInstance().getActiveClan()->getName();
			characterData.charArtIcon = simpleData->articonid;
			LoginManager::getInstance().sendToFrontServerCreateGenreal(simpleData->id, &characterData);

			closeGui();
		}
    }
	//-------------------------------------------------------------------
	void UICreateCharacter::restore()
	{
       //getLayout()->getEdit("edt_name")->getWidget()->setCaption(L"");
	   getLayout()->getEdit("edt_name")->clearEditText(false);
	   getLayout()->getText("test_power")->getWidget()->setCaption(L"");
	   getLayout()->getText("test_agile")->getWidget()->setCaption(L"");
	   getLayout()->getText("test_intellect")->getWidget()->setCaption(L"");
	   getLayout()->getText("test_spirt")->getWidget()->setCaption(L"");
	   getLayout()->getText("test_ps")->getWidget()->setCaption(L"");
	   getLayout()->getText("test_eg")->getWidget()->setCaption(L"");
	}
	//-------------------------------------------------------------------
	void UICreateCharacter::OnRest( void* widget )
	{
		UICreateCharacter::getInstance().restore();
	}
	//-------------------------------------------------------------------
	void UICreateCharacter::OnRandom( void* widget )
	{
		U32 randomId;
		if ( UICreateCharacter::getInstance().mCharTemplates.size() > 1 )
			randomId = MGRandom::getInstance().rand_ab_One(1,UICreateCharacter::getInstance().mCharTemplates.size());
		if (randomId != UICreateCharacter::getInstance().mSelectCharResourceID)
		{
			//mSelectCharResourceID 与loginScreen中的mSelectedGeneralIndex是相等的
			UICreateCharacter::getInstance().checkCharacter(randomId);
			LoginScreen::getInstance().randomGeneralbyId(randomId);
			
			Str16 randomName;
			if (UICreateCharacter::getInstance().mCheckSex == GENDER_TYPE_MAN)
			{
				randomName = CharacterRandNameCsv::getInstance().getRandMaleMing();
			}
			else
				randomName = CharacterRandNameCsv::getInstance().getRandFeMaleMing();

			IEdit* editname = UICreateCharacter::getInstance().getLayout()->getEdit("edt_name");
			assert(editname);
			editname->clearEditText(false);
			editname->setCaption(randomName);
		}
	}
	//-------------------------------------------------------------------
	void UICreateCharacter::initCharacter()
	{
		if ( mCharTemplates.empty() )
		{
			std::map<U32,CharacterResInfo*> tempResInfoList = CharacterResourceConfig::getInstance().getCharacterResourceInfoList();
			if (tempResInfoList.empty())
				return;

			U32 templateid[10];
			ZeroMemory(templateid, sizeof(templateid)); 

			for ( std::map<U32, CharacterResInfo*>::iterator iter = tempResInfoList.begin(); iter != tempResInfoList.end(); iter++ )
			{
				CharacterResInfo* characterResInfo = iter->second;

				SimpleCharacterResInfo	res_info;
				res_info.id				= characterResInfo->id;
				res_info.name			= characterResInfo->name;
				res_info.templateid		= characterResInfo->templateid;
				res_info.sex			= CharacterTemplate::getInstance().getCharacterTempInfo(res_info.templateid)->getGenrealGenderType();
				res_info.maplistip		= (RegionIdType)(characterResInfo->maplistid);
				res_info.pointresid		= characterResInfo->pointresid;
				res_info.maplisttype	= (MapType)characterResInfo->maplisttype;

				mCharTemplates.push_back(res_info);

				//数组从0开始
				templateid[res_info.id-1] = res_info.templateid;
			}

			//初始化所有角色属性
			SimplePlayerCharacter::getInstance().init(templateid);
            
			//设置选择的角色属性
			//setAttribute();
			//设置角色头像资源
			/*if (mSelectResIno->sex == GENDER_TYPE_MAN)
			mIconArtType = IOCN_ART_TYPE_MALEHEAD_LARGE;
			if (mSelectResIno->sex == GENDER_TYPE_WOMAN)
			mIconArtType = IOCN_ART_TYPE_FEMALEHEAD_LARGE;
			setHeadPicList();*/
		}

		mSelectCharResourceID = -1;
	}
	//-------------------------------------------------------------------
	bool UICreateCharacter::openGui()
	{
		restore();
		initCharacter();
		LoginScreen::getInstance().loadCreateGeneralScene();
		UIObject::openGui();
		return true;
	}
	//-------------------------------------------------------------------
	void UICreateCharacter::OnClickCharacter(CCharacterSceneEntity* entity)
	{
		U32 id = LoginScreen::getInstance().getTempCharIndex(entity);
		checkCharacter(id);
	}
	//-------------------------------------------------------------------
	void UICreateCharacter::OnMouseOverCharacter(CCharacterSceneEntity* entity)
	{
		
	}
	//-------------------------------------------------------------------
	void UICreateCharacter::checkCharacter(I32 id)
	{
		//角色状态
		if ( id >= 0 && id < mCharTemplates.size() )
		{
			SimpleCharacterResInfo& simpleInfo = mCharTemplates[id];
			{
				//更新头像资源
				if (simpleInfo.sex == GENDER_TYPE_MAN)
					mIconArtType = IOCN_ART_TYPE_MALEHEAD_LARGE;
				if (simpleInfo.sex == GENDER_TYPE_WOMAN)
					mIconArtType = IOCN_ART_TYPE_FEMALEHEAD_LARGE;

				mSelectCharResourceID = id;
				mCheckSex = simpleInfo.sex;
				//显示角色的初始属性
				setAttribute();
				setHeadPicList();
			}
		}	
	}
	//-------------------------------------------------------------------
	void UICreateCharacter::setAttribute()
	{
		if ( mSelectCharResourceID >= 0 && mSelectCharResourceID < mCharTemplates.size() )
		{
			Str16 strPower = L"";
			Str16 strAgile = L"";
			Str16 strIntellect = L"";
			Str16 strSpirt = L"";
			Str16 strPs = L"";
			Str16 strEnergy = L"";

			U32 id = mSelectCharResourceID;

			MGStrOp::toString((Int)SimplePlayerCharacter::getInstance().mPlayerCharacterData[id].mPower,strPower);
			MGStrOp::toString((Int)SimplePlayerCharacter::getInstance().mPlayerCharacterData[id].mAgile,strAgile);
			MGStrOp::toString((Int)SimplePlayerCharacter::getInstance().mPlayerCharacterData[id].mIntellect,strIntellect);
			MGStrOp::toString((Int)SimplePlayerCharacter::getInstance().mPlayerCharacterData[id].mSpirt,strSpirt);
			MGStrOp::toString((Int)SimplePlayerCharacter::getInstance().mPlayerCharacterData[id].mPhysicalStrength,strPs);
			MGStrOp::toString((Int)SimplePlayerCharacter::getInstance().mPlayerCharacterData[id].mEnergy,strEnergy);

			getLayout()->getText("test_power")->getWidget()->setCaption(strPower);
			getLayout()->getText("test_agile")->getWidget()->setCaption(strAgile);
			getLayout()->getText("test_intellect")->getWidget()->setCaption(strIntellect);
			getLayout()->getText("test_spirt")->getWidget()->setCaption(strSpirt);
			getLayout()->getText("test_ps")->getWidget()->setCaption(strPs);
			getLayout()->getText("test_eg")->getWidget()->setCaption(strEnergy);
		}
	}
	//-------------------------------------------------------------------
	void UICreateCharacter::setHeadPicList( )
	{
		ArtIconResCsv::getInstance().getIconArtResInfo(mIconArtType,mIconResInfoList);
		if (mIconResInfoList.empty())
			return;
      
		//重新设置资源时 随机选择一个头像
		mMaxPicCount = mIconResInfoList.size();
		mCurPicCount = MGRandom::getInstance().rand_ab_One(1,mMaxPicCount);
		Str16 tempLeft(L"");
		Str16 tempRight(L"");
		MGStrOp::toString(mCurPicCount,tempLeft);
        MGStrOp::toString(mMaxPicCount,tempRight);
		getLayout()->getText("text_left")->getWidget()->setCaption(tempLeft);
        getLayout()->getText("text_right")->getWidget()->setCaption(tempRight);
		
		//显示随机的头像
       IImage* headimg = getLayout()->getImage("img_headpic");
       headimg->setItemResource(mIconResInfoList[mCurPicCount]->ResName);
	   headimg->setItemGroup(mIconResInfoList[mCurPicCount]->GroupName);
	   headimg->setItemName(mIconResInfoList[mCurPicCount]->ItemName);

	   if ( mSelectCharResourceID >= 0 && mSelectCharResourceID < mCharTemplates.size() )
	   {
		   mCharTemplates[mSelectCharResourceID].articonid = mIconResInfoList[mCurPicCount]->ArtIconRes_Id;
	   }
	}
	//-------------------------------------------------------------------
	void UICreateCharacter::changeHeadPic( Direction dir )
	{		    
        if ( dir == DIR_LEFT)
        {
			if (mCurPicCount == 1)
			   mCurPicCount = mMaxPicCount;
			else
				mCurPicCount -= 1;
            IImage* headimg = getLayout()->getImage("img_headpic");

			headimg->setItemResource(mIconResInfoList[mCurPicCount]->ResName);
			headimg->setItemGroup(mIconResInfoList[mCurPicCount]->GroupName);
			headimg->setItemName(mIconResInfoList[mCurPicCount]->ItemName);

			if ( mSelectCharResourceID >= 0 && mSelectCharResourceID < mCharTemplates.size() )
			{
				mCharTemplates[mSelectCharResourceID].articonid = mIconResInfoList[mCurPicCount]->ArtIconRes_Id;
			}

			Str16 tempLeft(L"");
			MGStrOp::toString(mCurPicCount,tempLeft);
            getLayout()->getText("text_left")->getWidget()->setCaption(tempLeft);

        }

		if (dir == DIR_RIGHT)
		{
			if (mCurPicCount == mMaxPicCount)
			  mCurPicCount = 1;
			else
				mCurPicCount += 1;

			IImage* headimg = getLayout()->getImage("img_headpic");
		
			headimg->setItemResource(mIconResInfoList[mCurPicCount]->ResName);
			headimg->setItemGroup(mIconResInfoList[mCurPicCount]->GroupName);
			headimg->setItemName(mIconResInfoList[mCurPicCount]->ItemName);

			if ( mSelectCharResourceID >= 0 && mSelectCharResourceID < mCharTemplates.size() )
			{
				mCharTemplates[mSelectCharResourceID].articonid = mIconResInfoList[mCurPicCount]->ArtIconRes_Id;
			}

			Str16 tempLeft(L"");
			MGStrOp::toString(mCurPicCount,tempLeft);
			getLayout()->getText("text_left")->getWidget()->setCaption(tempLeft);

		}

	}
	//-------------------------------------------------------------------
	void UICreateCharacter::OnClickLeft( void* widget )
	{
		if (widget)
		{
			UICreateCharacter::getInstance().changeHeadPic(DIR_LEFT);
		}

	}
	//-------------------------------------------------------------------
	void UICreateCharacter::OnClickRight( void* widget )
	{
		if (widget)
		{
           UICreateCharacter::getInstance().changeHeadPic(DIR_RIGHT);
		}

	}
	//-------------------------------------------------------------------
	void UICreateCharacter::update(Flt delta)
	{
		
		/*if (this->isOpen())
		{
          

			if(ClientMain::getInstance().getEngine()->input()->isKeyReleased(KC_TAB))
			{
				IWidget* edit_name = getLayout()->getWidget("edt_name");
				//IWidget* edit_biaozi = getLayout()->getWidget("edt_biaozi");
				Bool   boolName = edit_name->isKeyFocus();
				//Bool   boolbiaozi =edit_biaozi->isKeyFocus();

				if ( boolName )
				{
					//edit_biaozi->setKeyFocus(true); 
				}
				else
				{
					edit_name->setKeyFocus(true);
				}

			}
		}
		*/
		

	}
	//-------------------------------------------------------------------
	void UICreateCharacter::onNotificateOK( void* arg )
	{
		UIYesNoMsgBox::getInstance().closeGui();
		LoginScreen::getInstance().prepareCreateGeneral();
	}
	//-------------------------------------------------------------------
	void UICreateCharacter::onNotificateCancle( void* arg )
	{
		UIYesNoMsgBox::getInstance().closeGui();
		return;
	}
}