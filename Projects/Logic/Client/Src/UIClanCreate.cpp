//*************************************************************************************
#include "stdafx.h"
#include "UIClanCreate.h"
#include "CPlayer.h"
#include "LoginManager.h"
#include "CreateClanResConfig.h"
#include "LoginScreenOpCtrl.h"
#include "LoginScreen.h"
#include "ClientMain.h"
#include "BanKeyword.h"
#include "UIMessageBox.h"
#include "UIYesNoMsgBox.h"
#include "CGameMessageConfig.h"
#include "ArtIconResCsv.h"
//*************************************************************************************
namespace MG
{
	UIClanCreate::UIClanCreate()
		:mSelectXZ(1)
		,mSelectBackIndex(1)
		,mSelectFlagIndex(1)
		,mSelectBackColorIndex(1)
		,mSelectFlagColorIndex(1)
		,mJWNameList(NULL)
		,mClanNameList(NULL)
		,mSelectJWColumn(0)
		,mSelectJWRow(1)
		,mSelectClanRow(1)
		,mSelectClanColumn(0)
    {

    }
    //---------------------------------------------------------------------
    UIClanCreate::~UIClanCreate()
    {
		mBackArtResInfoList.clear();
		mFlagArtResInfoList.clear();
		mJWNameList->clear();
		mClanNameList->clear();
		mJWNameList = NULL;
		mClanNameList = NULL;
    }
    //---------------------------------------------------------------------
    void UIClanCreate::setEvent()
    {
        IButton* btnok = getLayout()->getButton("btn_ok");
		DYNAMIC_ASSERT(btnok);
        btnok->getWidget()->setMouseButtonClickEvent( onClickCreateClan );

		IButton* selectCLanImgBtn = getLayout()->getButton("select_btn");
		DYNAMIC_ASSERT(selectCLanImgBtn);
		selectCLanImgBtn->getWidget()->setMouseButtonClickEvent(onClickSelectBtn);

		IButton* btnrandom = getLayout()->getButton("btn_random");
		DYNAMIC_ASSERT(btnrandom);
		btnrandom->getWidget()->setMouseButtonClickEvent( onClickRandom );

		IButton* btn1 = getLayout()->getButton("xzLeft_btn");
		DYNAMIC_ASSERT(btn1);
		btn1->getWidget()->setMouseButtonClickEvent(OnLeftXZClick);

		IButton* btn2 = getLayout()->getButton("xzRight_btn");
		DYNAMIC_ASSERT(btn2);
		btn2->getWidget()->setMouseButtonClickEvent(OnRightXZClick);

		IButton* btn3 = getLayout()->getButton("backLeft_btn");
		DYNAMIC_ASSERT(btn3);
		btn1->getWidget()->setMouseButtonClickEvent(OnLeftBackClick);

		IButton* btn4 = getLayout()->getButton("backRight_btn");
		DYNAMIC_ASSERT(btn4);
		btn2->getWidget()->setMouseButtonClickEvent(OnRightBackClick);

		IButton* btn5 = getLayout()->getButton("flagLeft_btn");
		DYNAMIC_ASSERT(btn5);
		btn1->getWidget()->setMouseButtonClickEvent(OnLeftFlagClick);

		IButton* btn6 = getLayout()->getButton("flagRight_btn");
		DYNAMIC_ASSERT(btn6);
		btn2->getWidget()->setMouseButtonClickEvent(OnRightFlagClick);
		
		IEdit* edit1 =  getLayout()->getEdit("edt_clanjw");
		DYNAMIC_ASSERT(edit1);
		edit1->getWidget()->setMouseSetFocusEvent(OnOpenJWList);
		//edit1->getWidget()->setMouseLostFocusEvent(OnCloseJWList);

		IEdit* edit2 = getLayout()->getEdit("edt_clanname");
		DYNAMIC_ASSERT(edit2);
		edit2->getWidget()->setMouseSetFocusEvent(OnOpenClanNameList);
		//edit1->getWidget()->setMouseLostFocusEvent(OnCloseClanNameLsit);
		IImage* img = NULL;
		char temp[16] = "";
		for (int i = 1; i <= COLOR_COUNT; i++ )
		{
			Sprintf_s(temp,16,"fc_%d",i);
			img = getLayout()->getImage(temp);
			DYNAMIC_ASSERT(img);
			img->getWidget()->setMouseButtonClickEvent(OnClickFlagColor);
		}
		
		for (int i = 1; i <= COLOR_COUNT; i++ )
		{
			Sprintf_s(temp,16,"bc_%d",i);
			img = getLayout()->getImage(temp);
			DYNAMIC_ASSERT(img);
			img->getWidget()->setMouseButtonClickEvent(OnClickBackColor);
		}

		

    }
    //---------------------------------------------------------------------
    void UIClanCreate::onClickCreateClan( void* widget )
    {
        assert(widget);
		//郡望
		IEdit* edithomlandname = UIClanCreate::getInstance().getLayout()->getEdit("edt_clanjw");
		DYNAMIC_ASSERT(edithomlandname);
		Str16 temphomehandname = edithomlandname->getCaption();
		if ( temphomehandname.length() < 1 )
		{
			//提示错误并返回
			return;
		}
		if (BanKeyword<BanKeywordName>::getInstance().isBan(const_cast<Char16*>(temphomehandname.c_str())) || BanKeyword<BanKeywordEnter>::getInstance().isBan(const_cast<Char16*>(temphomehandname.c_str())) )
		{
			UIMessageBox::getInstance().showHint(L"名称中有非法字符!");
			return;
		}
		//名
		IEdit* editname = UIClanCreate::getInstance().getLayout()->getEdit("edt_clanname");
		DYNAMIC_ASSERT(editname);
		Str16 tempname = editname->getCaption();
		if ( tempname.length() < 1 )
		{
			//提示错误并返回
			return;
		}
		if (BanKeyword<BanKeywordName>::getInstance().isBan(const_cast<Char16*>(tempname.c_str())) || BanKeyword<BanKeywordEnter>::getInstance().isBan(const_cast<Char16*>(tempname.c_str())) )
		{
			UIMessageBox::getInstance().showHint(L"名称中有非法字符!");
			return;
		}
		

		Char16 realTitle[1024] = {0};
		Str16 tempClanName = temphomehandname + tempname;
		Str16 tempTitle = CGameMessageConfig::getInstance().getStr(L"createclanfail",L"createclantitle",L"");
		Str16 tempContent = CGameMessageConfig::getInstance().getStr(L"createclanfail",L"createclancontent",L"");
		swprintf_s(realTitle,1024,tempContent.c_str(),tempClanName.c_str());

		UIYesNoMsgBox::getInstance().showHint(tempTitle,Str16(realTitle),
			(void*)(&UIClanCreate::getInstance()),onNotificateOK,(void*)(&UIClanCreate::getInstance()),onNotificateCancle);
        //UIClanCreate::getInstance().createClan();
    }
    //---------------------------------------------------------------------
    void UIClanCreate::createClan()
    {
        //郡望
       IEdit* edithomlandname = getLayout()->getEdit("edt_clanjw");
        DYNAMIC_ASSERT(edithomlandname);
        Str16 temphomehandname = edithomlandname->getCaption();
        
        //名
        IEdit* editname = getLayout()->getEdit("edt_clanname");
        DYNAMIC_ASSERT(editname);
        Str16 tempname = editname->getCaption();
        
        CClan tempClan;
        tempClan.setClanHomeLandName( temphomehandname );
        tempClan.setName( tempname );
        
		//获取家族背景图标id,标志id,背景颜色id，标志颜色id
		U32 clanFlagId = mFlagArtResInfoList[mSelectFlagIndex]->ArtIconRes_Id;
		U32 clanBackId = mBackArtResInfoList[mSelectBackIndex]->ArtIconRes_Id;
		U32 clanFlagColorId = mFlagColorInfoList[mSelectFlagColorIndex]->ColorRes_Id;
		U32 clanBackColorId = mBackColorInfoList[mSelectBackColorIndex]->ColorRes_Id;
        LoginManager::getInstance().sendToFrontServerCreateClan( &tempClan );
    }
	//---------------------------------------------------------------------
	void UIClanCreate::onClickReset( void* widget )
	{
		if (widget)
		{
			//UIClanCreate::getInstance().restore();
			//显示星座
			UIClanCreate::getInstance().resetClanInfo();
			//UIClanCreate::getInstance().randomSetting();
			
		}
		   
	}
   //---------------------------------------------------------------------
	void UIClanCreate::onClickRandom( void* widget )
	{
		UIClanCreate::getInstance().randomSetting();
	}
	//---------------------------------------------------------------------
	void UIClanCreate::restore()
	{
		/*getLayout()->getEdit("edt_clanjw")->setCaption(L"");
		getLayout()->getEdit("edt_clanname")->setCaption(L"");
		getLayout()->getText("select_Index")->getWidget()->setCaption(L"1");
		getLayout()->getButton("xzLeft_btn")->getWidget()->setEnabled(false);
		getLayout()->getButton("xzRight_btn")->getWidget()->setEnabled(true);
		getLayout()->getWidget("_zuhui")->setVisible(false);*/
		mSelectXZ = 1;
		mSelectFlagIndex = 1;
		mSelectBackIndex = 1;
		mSelectJWRow = 1;
		mSelectJWColumn = 0;
		mSelectClanRow = 1;
		mSelectClanColumn = 0;
		//getLayout()->getText("text_clandetal")->getWidget()->setCaption(L"朱雀命格的氏族，门下武将对于计策及法术有更高的见解，氏族封地中将获取更多的神祗帮助。");

	}
	//---------------------------------------------------------------------
	void UIClanCreate::initFamily()
	{
		
		LoginScreen::getInstance().setAllEntitysVisible(true);

		for ( int i = 0; i < LoginScreen::FOCUS_ENTITY_MAX; i++ )
		{
			IEntity* entity = LoginScreen::getInstance().getEntity( i + LoginScreen::ENTITY_SUSAKU );
			if ( entity )
				entity->getSceneNode()->setVisible(false);
		}
		
		getLayout()->getWidget("_zuhui")->setVisible(false);

		IWidget* wd1 = getLayout()->getWidget("_junwang");
		DYNAMIC_ASSERT(wd1);
		wd1->setVisible(false);
		
		IWidget* wd2 = getLayout()->getWidget("_baijiaxing");
		DYNAMIC_ASSERT(wd2);
		wd2->setVisible(false);
	}
	void UIClanCreate::resetClanInfo()
	{
		
		//
		IEdit* edithomlandname = getLayout()->getEdit("edt_clanjw");
		DYNAMIC_ASSERT(edithomlandname);
		edithomlandname->setCaption(L"");

		//名
		IEdit* editname = getLayout()->getEdit("edt_clanname");
		DYNAMIC_ASSERT(editname);
		editname->setCaption(L"");

		mSelectBackIndex = 1;
		mSelectBackColorIndex = 1;
		mSelectFlagIndex = 1;
		mSelectFlagColorIndex = 1;
		mSelectXZ = 1;
		updateFlagPartUI(mSelectFlagIndex);
		updateSelectFlagColor();
		updateSelectBackColor();
		updateBackPartUI(mSelectFlagIndex);
		updateXZPartUI(mSelectXZ,true);
	}
	//---------------------------------------------------------------------
	void UIClanCreate::initBackArtResInfo()
	{
		if (mBackArtResInfoList.empty())
		{
			ArtIconResCsv::getInstance().getIconArtResInfo(ICON_ART_TYPE_CLAN_BACK,mBackArtResInfoList);
		}
	}
	//---------------------------------------------------------------------
	void UIClanCreate::initFlagArtResInfo()
	{
		if (mFlagArtResInfoList.empty())
		{
			ArtIconResCsv::getInstance().getIconArtResInfo(ICON_ART_TYPE_CLAN_FLAG,mFlagArtResInfoList);
		}
	}
	//---------------------------------------------------------------------
	void UIClanCreate::initJWList()
	{
		if (!mJWNameList || !mJWNameList->size())
		{
			mJWNameList = CharacterRandNameCsv::getInstance().getJunWangList();
			if (mJWNameList && mJWNameList->size() > 0)
			{
				////填充郡望列表
				IMixList* list = getLayout()->getMixList("jw_list");
				DYNAMIC_ASSERT(list);
				list->removeAllLine();


				Int i = 0;			//行数
				Int j = 0;			//列数

				for (std::vector<CharacterRandNameCsvInfo*>::iterator iter = mJWNameList->begin();iter != mJWNameList->end(); ++iter)
				{

					//一行数据 有5列
					if (j == COLUMN_COUNT || 0 == j)
					{
						j = 0;
						i++;
						list->addLine(i,L"");
					}

					IMixListRow* row = list->getMixListRow(i);
					DYNAMIC_ASSERT(row);
					CreateListRowBtnInfo btnInfo;
					btnInfo.row = i;
					btnInfo.column = j;
					btnInfo.text = (*iter)->Text;
					row->getChildWidget(j)->setCaption((*iter)->Text);
					row->getChildWidget(j)->setUserData(btnInfo);
					row->getChildWidget(j)->setMouseButtonClickEvent(OnSelectJWBtn);
					j++;
				}
				//将多余的子项没有数据设置为不可见
				while(j < COLUMN_COUNT)
				{

					IMixListRow* row = list->getMixListRow(i);
					DYNAMIC_ASSERT(row);

					row->getChildWidget(j)->setVisible(false);
					j++;
				}
			}
		}
	}
	//---------------------------------------------------------------------
	void UIClanCreate::initClanNameList()
	{
		if (!mClanNameList || !mClanNameList->size())
		{
			mClanNameList = CharacterRandNameCsv::getInstance().getCommonXingList();
			if (mClanNameList && mClanNameList->size()> 0)
			{
				//填充郡望列表
				IMixList* list = getLayout()->getMixList("bjx_list");
				DYNAMIC_ASSERT(list);
				list->removeAllLine();

				Int i = 0;			//行数
				Int j = 0;			//列数

				for (std::vector<CharacterRandNameCsvInfo*>::iterator iter = mClanNameList->begin();iter != mClanNameList->end(); ++iter)
				{

					//一行数据 有5列
					if (j == COLUMN_COUNT || 0 == j)
					{
						j = 0;
						i++;
						list->addLine(i,L"");
					}

					IMixListRow* row = list->getMixListRow(i);
					DYNAMIC_ASSERT(row);
					
					CreateListRowBtnInfo btnInfo;
					btnInfo.row = i;
					btnInfo.column = j;
					btnInfo.text = (*iter)->Text;
					row->getChildWidget(j)->setCaption((*iter)->Text);
					row->getChildWidget(j)->setUserData(btnInfo);
					row->getChildWidget(j)->setMouseButtonClickEvent(OnSelectClanNameBtn);
					j++;
				}
				while(j < COLUMN_COUNT)
				{

					IMixListRow* row = list->getMixListRow(i);
					DYNAMIC_ASSERT(row);

					row->getChildWidget(j)->setVisible(false);
					j++;
				}
			}
		}
	}
	//---------------------------------------------------------------------
	void UIClanCreate::initBackColorImgs()
	{
		if (mBackColorInfoList.empty())
		{
			ColorResConfig::getInstance().getColorResInfo(Color_Use_ClanBack,mBackColorInfoList);
			//进行数据处理
			if (!mBackColorInfoList.empty())
			{
				char temp[16]="";
				IImage* img = NULL;
				for (std::map<U32,  ColorResCsvInfo*>::iterator iter = mBackColorInfoList.begin();iter!= mBackColorInfoList.end();iter++)
				{
					Sprintf_s(temp, 32, "bc_%d", iter->first);
					img = getLayout()->getImage(temp);
					DYNAMIC_ASSERT(img);
					img->getWidget()->setColour(iter->second->ColorValue);
					img->getWidget()->setUserData(iter->first);
				}
			}		
		}	
	}
	//---------------------------------------------------------------------
	void UIClanCreate::initFlagColorImgs()
	{
		if (mFlagColorInfoList.empty())
		{
			ColorResConfig::getInstance().getColorResInfo(Color_Use_ClanFlag,mFlagColorInfoList);
			//进行数据处理
			if (!mFlagColorInfoList.empty())
			{
				char temp[16]="";
				IImage* img = NULL;
				for (std::map<U32,  ColorResCsvInfo*>::iterator iter = mFlagColorInfoList.begin();iter!= mFlagColorInfoList.end();iter++)
				{
					Sprintf_s(temp, 32, "fc_%d", iter->first);
					img = getLayout()->getImage(temp);
					DYNAMIC_ASSERT(img);
					img->getWidget()->setColour(iter->second->ColorValue);
					img->getWidget()->setUserData(iter->first);
				}
			}		
		}
	}
	//---------------------------------------------------------------------
	bool UIClanCreate::openGui()
	{
		initBackArtResInfo();
		initFlagArtResInfo();
		initJWList();
		initClanNameList();
		initBackColorImgs();
		initFlagColorImgs();
			
		if (UIObject::openGui())
		{
            //restore();
			initFamily();
			randomSetting();
			return true;
		}
		return false;

	}
	//---------------------------------------------------------------------
	void UIClanCreate::update(Flt delta)
	{
		if (this->isOpen())
		{
			//检查是否按了Tab
			if(ClientMain::getInstance().getEngine()->input()->isKeyReleased(KC_TAB))
			{
			
				IWidget* edit_clanname = getLayout()->getWidget("edt_clanname");
				DYNAMIC_ASSERT(edit_clanname);
				IWidget* edit_clanjw = getLayout()->getWidget("edt_clanjw");
				DYNAMIC_ASSERT(edit_clanjw);
				Bool   boolClanName = edit_clanname->isKeyFocus();
				Bool   boolClanJw =edit_clanjw->isKeyFocus();

				if ( boolClanName )
				{
					edit_clanjw->setKeyFocus(true); 
				}
				else
				{
				edit_clanname->setKeyFocus(true);
				}
			
			}
		}

	}
	//---------------------------------------------------------------------
	void UIClanCreate::onNotificateOK( void* arg )
	{
         UIClanCreate* pInstance = (UIClanCreate*)arg;
		 UIYesNoMsgBox::getInstance().closeGui();
		 pInstance->createClan();
		 

	}
	//-------------------------------------------------------------------------------
	void UIClanCreate::onNotificateCancle( void* arg )
	{

		UIYesNoMsgBox::getInstance().closeGui();
		return;

	}
	//-------------------------------------------------------------------------------
	void UIClanCreate::modifyXZIndex(U32 index )
	{
		if (mSelectXZ <= 0)
		{
			mSelectXZ = Max_XZ;
		}
		if (mSelectXZ > Max_XZ)
		{
			mSelectXZ = 1;
		}
	}
	//-------------------------------------------------------------------------------
	void UIClanCreate::modifyBackIndex(U32 index )
	{
		if (mSelectBackIndex <= 0)
		{
			mSelectBackIndex = mBackArtResInfoList.size();
		}
		if (mSelectBackIndex > mBackArtResInfoList.size())
		{
			mSelectBackIndex = 1;
		}
	}
	//-------------------------------------------------------------------------------
	void UIClanCreate::modifyFlagIndex(U32 index )
	{
		if (mSelectFlagIndex <= 0)
		{
			mSelectFlagIndex = mFlagArtResInfoList.size();
		}
		if (mSelectFlagIndex > mFlagArtResInfoList.size())
		{
			mSelectFlagIndex = 1;
		}
	}
	
	//-------------------------------------------------------------------------------
	void UIClanCreate::OnLeftXZClick( void* arg )
	{
		UIClanCreate::getInstance().mSelectXZ--;
		UIClanCreate::getInstance().modifyXZIndex(UIClanCreate::getInstance().mSelectXZ);	
		UIClanCreate::getInstance().updateXZPartUI(UIClanCreate::getInstance().mSelectXZ);
	}
	//-------------------------------------------------------------------------------
	void UIClanCreate::OnRightXZClick( void* arg )
	{

		UIClanCreate::getInstance().mSelectXZ++;
		UIClanCreate::getInstance().modifyXZIndex(UIClanCreate::getInstance().mSelectXZ);
		UIClanCreate::getInstance().updateXZPartUI(UIClanCreate::getInstance().mSelectXZ);
	}
	//-------------------------------------------------------------------------------
	void UIClanCreate::OnLeftBackClick( void* arg )
	{
		UIClanCreate::getInstance().mSelectBackIndex--;
		//修正index值，使其循环
		UIClanCreate::getInstance().modifyBackIndex(UIClanCreate::getInstance().mSelectBackIndex);
		//修正ui表现
		UIClanCreate::getInstance().updateBackPartUI(UIClanCreate::getInstance().mSelectBackIndex);
	}
	//-------------------------------------------------------------------------------
	void UIClanCreate::OnRightBackClick( void* arg )
	{
		UIClanCreate::getInstance().mSelectBackIndex++;
		//修正index值，使其循环
		UIClanCreate::getInstance().modifyBackIndex(UIClanCreate::getInstance().mSelectBackIndex);
		//修正ui表现
		UIClanCreate::getInstance().updateBackPartUI(UIClanCreate::getInstance().mSelectBackIndex);
	}
	//-------------------------------------------------------------------------------
	void UIClanCreate::OnLeftFlagClick( void* arg )
	{
		UIClanCreate::getInstance().mSelectFlagIndex--;
		//修正index值，使其循环
		UIClanCreate::getInstance().modifyFlagIndex(UIClanCreate::getInstance().mSelectFlagIndex);
		//修正ui表现
		UIClanCreate::getInstance().updateFlagPartUI(UIClanCreate::getInstance().mSelectFlagIndex);
	}
	//-------------------------------------------------------------------------------
	void UIClanCreate::OnRightFlagClick( void* arg )
	{
		UIClanCreate::getInstance().mSelectFlagIndex++;
		//修正index值，使其循环
		UIClanCreate::getInstance().modifyFlagIndex(UIClanCreate::getInstance().mSelectFlagIndex);
		//修正ui表现
		UIClanCreate::getInstance().updateFlagPartUI(UIClanCreate::getInstance().mSelectFlagIndex);
	}
	//-------------------------------------------------------------------------------
	void UIClanCreate::updateXZPartUI(U32 index, bool immdiately, Flt speed)
	{
		//设置当前选中星座数字
		Char16 temp[16] = L"";
		swprintf_s(temp, 16, L"%d", index);
		getLayout()->getText("select_Index")->getWidget()->setCaption(temp);
		//显示星座
		IEntity* entity = LoginScreen::getInstance().getEntity(index);
		if ( entity )
		{
			if (immdiately)
			{
				LoginScreenOpCtrl::getInstance().turnCameraImmediately( entity->getName() );
			}
			else
				LoginScreenOpCtrl::getInstance().turnCamera( entity->getName() );
			
		}

		if (index == 1)
		{
			getLayout()->getText("text_clandetal")->getWidget()->setCaption(L"朱雀命格的氏族，门下武将对于计策及法术有更高的见解，氏族封地中将获取更多的神祗帮助。");
		}
		else if	(index == 2)
		{
			getLayout()->getText("text_clandetal")->getWidget()->setCaption(L"白虎命格的氏族，门下武将在武艺上的造诣会强于其他人，氏族封地中的军事防御更为强大。");		
		}
		else if (index == 3)
		{
			getLayout()->getText("text_clandetal")->getWidget()->setCaption(L"玄武命格的氏族，门下武将多拥有较强的政务治理能力，氏族封地中会产生更多的生产交易资源。");
		}
		else
		{
			getLayout()->getText("text_clandetal")->getWidget()->setCaption(L"青龙命格的氏族，门下武将拥有强大的军事统帅能力，氏族封地中拥有更高的凝聚力。");
		}		
	}
	//-------------------------------------------------------------------------------
	void UIClanCreate::updateBackPartUI(U32 index)
	{
		IImage* img = NULL;
		img = getLayout()->getImage("mid_back");
		DYNAMIC_ASSERT(img);
		ArtIconResCsvInfo* mideRes = mBackArtResInfoList[index];
		DYNAMIC_ASSERT(mideRes);
		img->setTexture(mideRes->ResName,mideRes->GroupName,mideRes->ItemName);

		img = getLayout()->getImage("left_back");
		DYNAMIC_ASSERT(img);
		U32 leftIndex = index - 1;
		if (leftIndex <=0)
		{
			leftIndex = mBackArtResInfoList.size();
			
		}
		ArtIconResCsvInfo* leftRes = mBackArtResInfoList[leftIndex];
		DYNAMIC_ASSERT(leftRes);
		img->setTexture(leftRes->ResName,leftRes->GroupName,leftRes->ItemName);

		
		img = getLayout()->getImage("right_back");
		DYNAMIC_ASSERT(img);
		U32 rightIndex = index + 1;
		if (rightIndex > mBackArtResInfoList.size())
		{
			rightIndex = 1;	
		}

		ArtIconResCsvInfo* rightRes = mBackArtResInfoList[rightIndex];
		DYNAMIC_ASSERT(rightRes);
		img->setTexture(rightRes->ResName,rightRes->GroupName,rightRes->ItemName);
		//设置目标底图
		img= getLayout()->getImage("img_back");
		DYNAMIC_ASSERT(img);
		img->setTexture(mideRes->ResName,mideRes->GroupName,mideRes->ItemName);
	}
	//-------------------------------------------------------------------------------
	void UIClanCreate::updateFlagPartUI(U32 index)
	{
		IImage* img = NULL;
		img = getLayout()->getImage("mid_flag");
		DYNAMIC_ASSERT(img);
		ArtIconResCsvInfo* mideRes = mFlagArtResInfoList[index];
		DYNAMIC_ASSERT(mideRes);
		img->setTexture(mideRes->ResName,mideRes->GroupName,mideRes->ItemName);

		img = getLayout()->getImage("left_flag");
		DYNAMIC_ASSERT(img);
		U32 leftIndex = index - 1;
		if (leftIndex <= 0)
		{
			leftIndex = mFlagArtResInfoList.size();
		}
		ArtIconResCsvInfo* leftRes = mFlagArtResInfoList[leftIndex];
		DYNAMIC_ASSERT(leftRes);
		img->setTexture(leftRes->ResName,leftRes->GroupName,leftRes->ItemName);

		img = getLayout()->getImage("right_flag");
		DYNAMIC_ASSERT(img);
		U32 rightIndex = index + 1;
		if (rightIndex  > mFlagArtResInfoList.size())
		{
			rightIndex = 1;
		}
		
		ArtIconResCsvInfo* rightRes = mFlagArtResInfoList[rightIndex];
		DYNAMIC_ASSERT(rightRes);
		img->setTexture(rightRes->ResName,rightRes->GroupName,rightRes->ItemName);
		//设置目标背景图
		img= getLayout()->getImage("img_zuhui");
		DYNAMIC_ASSERT(img);
		img->setTexture(mideRes->ResName,mideRes->GroupName,mideRes->ItemName);
	}
	//---------------------------------------------------------------------
	void UIClanCreate::onClickSelectBtn( void* widget )
	{
		UIClanCreate::getInstance().setCLanImgSettingVisible();
	}
	//---------------------------------------------------------------------
	void UIClanCreate::setCLanImgSettingVisible()
	{
		bool visible = getLayout()->getWidget("_zuhui")->isVisible();
		getLayout()->getWidget("_zuhui")->setVisible(!visible);
	}
	//-------------------------------------------------------------------------------
	void UIClanCreate::OnOpenJWList(void* widget, void* newWidget)
	{
		UIClanCreate::getInstance().openJWList();
	}
	//-------------------------------------------------------------------------------
	void UIClanCreate::OnOpenClanNameList(void* widget, void* newWidget)
	{
		UIClanCreate::getInstance().openClanNameList();
	}
	//-------------------------------------------------------------------------------
	void UIClanCreate::updateJWBtnState(U32 row, U32 column)
	{
		IMixList* list = getLayout()->getMixList("jw_list");
		if (list)
		{
			IMixListRow* oldRow = list->getMixListRow(mSelectJWRow);
			if (!oldRow)
				return;
			oldRow->getChildWidget(mSelectJWColumn)->getButton()->setStateCheck(false);

			IMixListRow* newRow = list->getMixListRow(row);
			if (!newRow)
				return;
			newRow->getChildWidget(column)->getButton()->setStateCheck(true);

			mSelectJWRow = row;
			mSelectJWColumn = column;
		}
	}
	//-------------------------------------------------------------------------------
	void UIClanCreate::updateClanBtnState(U32 row, U32 column)
	{
		IMixList* list = getLayout()->getMixList("bjx_list");
		if (list)
		{
			IMixListRow* oldRow = list->getMixListRow(mSelectClanRow);
			if (!oldRow)
				return;
			oldRow->getChildWidget(mSelectClanColumn)->getButton()->setStateCheck(false);

			IMixListRow* newRow = list->getMixListRow(row);
			if (!newRow)
				return;
			newRow->getChildWidget(column)->getButton()->setStateCheck(true);

			mSelectClanRow = row;
			mSelectClanColumn = column;
		}
	}
	//-------------------------------------------------------------------------------
	void UIClanCreate::OnSelectJWBtn(void* widget)
	{
		IWidget* pwidget = (IWidget*)widget;
		DYNAMIC_ASSERT(pwidget);
		CreateListRowBtnInfo* info = pwidget->getUserData()->castType<CreateListRowBtnInfo>();
		DYNAMIC_ASSERT(info);
		if (info->column != UIClanCreate::getInstance().mSelectJWColumn || info->row !=  UIClanCreate::getInstance().mSelectJWRow)
		{
			UIClanCreate::getInstance().updateJWBtnState(info->row, info->column);
		}
		UIClanCreate::getInstance().setJWContent(info->text);
	}
	//-------------------------------------------------------------------------------
	void UIClanCreate::OnSelectClanNameBtn(void* widget)
	{
		IWidget* pwidget = (IWidget*)widget;
		DYNAMIC_ASSERT(pwidget);
		CreateListRowBtnInfo* info = pwidget->getUserData()->castType<CreateListRowBtnInfo>();
		DYNAMIC_ASSERT(info);
		if (info->column !=  UIClanCreate::getInstance().mSelectClanColumn || info->row !=  UIClanCreate::getInstance().mSelectClanRow)
		{
			UIClanCreate::getInstance().updateClanBtnState(info->row, info->column);
		}
		UIClanCreate::getInstance().setClanNameContent(info->text);
	}
	//-------------------------------------------------------------------------------
	void UIClanCreate::OnClickFlagColor(void* widget)
	{
		if (widget)
		{
			IWidget* pwidget = (IWidget*) widget;
			U32* index = pwidget->getUserData()->castType<U32>();
			if (*index > 0 && *index <= COLOR_COUNT )
			{
				UIClanCreate::getInstance().mSelectFlagColorIndex = *index;
				UIClanCreate::getInstance().updateSelectFlagColor();
			}
		}	
	}
	//-------------------------------------------------------------------------------
	void UIClanCreate::OnClickBackColor(void* widget)
	{
		if (widget)
		{
			IWidget* pwidget = (IWidget*) widget;
			U32* index = (U32*)pwidget->getUserData()->castType<U32>();
			if (*index > 0 && *index <= COLOR_COUNT )
			{
				UIClanCreate::getInstance().mSelectBackColorIndex = *index;
				UIClanCreate::getInstance().updateSelectBackColor();
			}
		}
	}
	//-------------------------------------------------------------------------------
	void UIClanCreate::updateSelectBackColor()
	{
		IImage* highlight = NULL;
		highlight = getLayout()->getImage("bhigh_light");
		DYNAMIC_ASSERT(highlight);
		char temp[16] = "";
		Sprintf_s(temp,16,"bc_%d",mSelectBackColorIndex);
		Vec2 pos = getLayout()->getWidget(temp)->getPosition();
		highlight->getWidget()->setPosition(pos);
		highlight->getWidget()->setVisible(true);

		//设置族徽背景颜色
		Color _value = mBackColorInfoList[mSelectBackColorIndex]->ColorValue;
		getLayout()->getImage("img_back")->getWidget()->setColour(_value);

	}
	//-------------------------------------------------------------------------------
	void UIClanCreate::updateSelectFlagColor()
	{
		IImage* highlight = NULL;
		highlight = getLayout()->getImage("fhigh_light");
		DYNAMIC_ASSERT(highlight);
		char temp[16] = "";
		Sprintf_s(temp,16,"fc_%d",mSelectFlagColorIndex);
		Vec2 pos = getLayout()->getWidget(temp)->getPosition();
		highlight->getWidget()->setPosition(pos);
		highlight->getWidget()->setVisible(true);

		//设置族徽背景颜色
		Color _value = mFlagColorInfoList[mSelectFlagColorIndex]->ColorValue;
		getLayout()->getImage("img_zuhui")->getWidget()->setColour(_value);

	}
	//-------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------
	void UIClanCreate::setClanNameContent(Str16 text)
	{
		IEdit* edt = getLayout()->getEdit("edt_clanname");
		DYNAMIC_ASSERT(edt);
		edt->setCaption(text);
	}
	//-------------------------------------------------------------------------------
	void UIClanCreate::setJWContent(Str16 text)
	{
		IEdit* edt = getLayout()->getEdit("edt_clanjw");
		DYNAMIC_ASSERT(edt);
		edt->setCaption(text);
	}
	//-------------------------------------------------------------------------------
	void UIClanCreate::openJWList()
	{
		getLayout()->getWidget("_junwang")->setVisible(true);
		getLayout()->getWidget("_baijiaxing")->setVisible(false);
	}
	//-------------------------------------------------------------------------------
	void UIClanCreate::openClanNameList()
	{
		getLayout()->getWidget("_baijiaxing")->setVisible(true);
		getLayout()->getWidget("_junwang")->setVisible(false);
	}
	//-------------------------------------------------------------------------------
	void UIClanCreate::OnCloseJWList(void* widget, void* newWidget)
	{
		UIClanCreate::getInstance().closeJWList();
	}
	//-------------------------------------------------------------------------------
	void UIClanCreate::OnCloseClanNameLsit(void* widget, void* newWidget)
	{
		UIClanCreate::getInstance().closeClanNameList();
	}
	//-------------------------------------------------------------------------------
	void UIClanCreate::closeJWList()
	{
		getLayout()->getWidget("_junwang")->setVisible(false);
	}
	//-------------------------------------------------------------------------------
	void UIClanCreate::closeClanNameList()
	{
		getLayout()->getWidget("_baijiaxing")->setVisible(false);
	}
	//-------------------------------------------------------------------------------
	void UIClanCreate::randomClan()
	{
		U32 randomLine;
		U32 randomColumn;
		U32	line = mClanNameList->size() / COLUMN_COUNT;
		//随机函数是[a, b) 
		randomLine = MGRandom::getInstance().rand_ab_One(1,line);
		////填充郡望列表
		IMixList* list = getLayout()->getMixList("bjx_list");
		DYNAMIC_ASSERT(list);

		IMixListRow* row = list->getMixListRowByIndex(randomLine);
		DYNAMIC_ASSERT(row);

		randomColumn = MGRandom::getInstance().rand_ab_One(0,COLUMN_COUNT);
		IWidget* randomWgt =NULL;
		randomWgt = row->getChildWidget(randomColumn);
		DYNAMIC_ASSERT(randomWgt);

		IAny* date = randomWgt->getUserData();
		//如果没有数据，默认取该行的第一列数据
		if (!date)
		{
			randomWgt = row->getChildWidget(0);
			randomColumn = 0;
		}
		if (randomColumn != mSelectClanColumn || randomLine != mSelectClanRow)
		{
			updateClanBtnState(randomLine, randomColumn);

			CreateListRowBtnInfo* info = randomWgt->getUserData()->castType<CreateListRowBtnInfo>();
			DYNAMIC_ASSERT(info);

			UIClanCreate::getInstance().setClanNameContent(info->text);
		}
	}
	//-------------------------------------------------------------------------------
	void UIClanCreate::randomJW()
	{
		U32 randomLine;
		U32 randomColumn;
		U32	line = mJWNameList->size() / COLUMN_COUNT;
		//随机函数是[a, b) 
		randomLine = MGRandom::getInstance().rand_ab_One(1,line);
		////填充郡望列表
		IMixList* list = getLayout()->getMixList("jw_list");
		DYNAMIC_ASSERT(list);

		IMixListRow* row = list->getMixListRowByIndex(randomLine);
		DYNAMIC_ASSERT(row);
		
		randomColumn = MGRandom::getInstance().rand_ab_One(0,COLUMN_COUNT);
		IWidget* randomWgt =NULL;
		randomWgt = row->getChildWidget(randomColumn);
		DYNAMIC_ASSERT(randomWgt);
		
		IAny* date = randomWgt->getUserData();
		//如果没有数据，默认取该行的第一列数据
		if (!date)
		{
			randomWgt = row->getChildWidget(0);
			randomColumn = 0;
		}

		randomWgt->getButton()->setStateCheck(true);
		if (mSelectJWColumn != randomColumn || mSelectJWRow != randomLine)
		{
			
			updateJWBtnState(randomLine, randomColumn);

			CreateListRowBtnInfo* info = randomWgt->getUserData()->castType<CreateListRowBtnInfo>();
			DYNAMIC_ASSERT(info);

			UIClanCreate::getInstance().setJWContent(info->text);
		}
	}
	//-------------------------------------------------------------------------------
	void UIClanCreate::randomSetting()
	{
		U32 random = MGRandom::getInstance().rand_ab_One(1,5);
		if (random != mSelectXZ )
		{
			mSelectXZ = random;
			updateXZPartUI(mSelectXZ, true);
		}

		U32 backIconSize =mBackArtResInfoList.size();
		random = MGRandom::getInstance().rand_ab_One(1,backIconSize);
		
		if (random != mSelectBackIndex)
		{
			mSelectBackIndex = random;
			updateBackPartUI(mSelectBackIndex); 
		}

		U32 flagIconSize =mFlagArtResInfoList.size();
		random = MGRandom::getInstance().rand_ab_One(1,flagIconSize);
		if (random != mSelectFlagIndex)
		{
			mSelectFlagIndex = random;
			updateFlagPartUI(mSelectFlagIndex);
		}
		//因为要出现随机的list子项，改变随机方式，随机出行列，取一个子项数据出来
		/*U32	jwSize = mJWNameList->size();
		random = MGRandom::getInstance().rand_ab_One(0,jwSize);
		Str16 text = mJWNameList->at(random)->Text;
		getLayout()->getEdit("edt_clanjw")->setCaption(text);


		U32	clanSize = mClanNameList->size();
		random = MGRandom::getInstance().rand_ab_One(1,clanSize);
		Str16  name = mClanNameList->at(random)->Text;
		getLayout()->getEdit("edt_clanname")->setCaption(name);*/
		
		randomClan();
		randomJW();

		U32 bColorSize = mBackColorInfoList.size();
		random = MGRandom::getInstance().rand_ab_One(1, bColorSize);
		if(random != mSelectBackColorIndex)
		{
			mSelectBackColorIndex = random;
			updateSelectBackColor();
		}

		U32 fColorSize = mFlagColorInfoList.size();
		random = MGRandom::getInstance().rand_ab_One(1, fColorSize);
		if(random != mSelectFlagColorIndex)
		{
			mSelectFlagColorIndex = random;
			updateSelectFlagColor();
		}
	}
}