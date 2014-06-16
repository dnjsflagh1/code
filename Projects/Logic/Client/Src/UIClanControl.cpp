//*************************************************************************************

#include "stdafx.h"
#include "UIClanControl.h"
#include "LoginManager.h"
#include "CPlayer.h"
#include "ClientMain.h"
#include "UIMessageBox.h"
#include "UIYesNoMsgBox.h"
#include "CGameMessageConfig.h"
#include "GameMain.h"
#include "LoginScreen.h"
#include "UIAccountLogin.h"

//*************************************************************************************
namespace MG
{
    UIClanControl::UIClanControl() 
    {

    }
    //--------------------------------------------------------------------
    UIClanControl::~UIClanControl()
    {

    }
    //--------------------------------------------------------------------
    void UIClanControl::setEvent()
    {
        IButton* pButtonDelete = getLayout()->getButton("btn_delclan");
        assert(pButtonDelete);
        pButtonDelete->getWidget()->setMouseButtonClickEvent(onClickDeleteClan);

        IButton* pButtonjoin = getLayout()->getButton("btn_go");
        assert(pButtonjoin);
        pButtonjoin->getWidget()->setMouseButtonClickEvent(onClickReadyJoinGame);

        IButton* pButtonReturn = getLayout()->getButton("btn_return");
        assert(pButtonReturn);
        pButtonReturn->getWidget()->setMouseButtonClickEvent(onClickReLogin);
    }
    //--------------------------------------------------------------------
    void UIClanControl::onClickReadyJoinGame( void* widget )
    {
         assert(widget);
		 
		 Str16 tempTitle = CGameMessageConfig::getInstance().getStr(L"clanControl",L"loginToGameTitle",L"");
		 Str16 tempContent = CGameMessageConfig::getInstance().getStr(L"clanControl",L"loginToGametContent",L"");

		 UIYesNoMsgBox::getInstance().showHint(tempTitle,tempContent,(void*)(&UIClanControl::getInstance()), onReallyJoinGame, NULL, NULL);	
    }
	//--------------------------------------------------------------------
	void UIClanControl::onReallyJoinGame( void* arg )
	{
		 LoginScreen::getInstance().prepareJoiningGame();
	}
    //--------------------------------------------------------------------
    void UIClanControl::_joinGame()
    {
        closeGui();
        //GameMain::getInstance().enterGameScreen();

		LoginManager::getInstance().sendToFrontServerJoingame();
    }
    //--------------------------------------------------------------------
    Bool UIClanControl::openGui()
    {
		initInfo();
		
		LoginScreen::getInstance().loadSelectGeneralScene();

        return UIObject::openGui();
    }
    //--------------------------------------------------------------------
    void UIClanControl::initInfo()
    {
        CClan* pClan = CPlayer::getInstance().getActiveClan();
        assert(pClan);
        CPlayerCharacter* playerCharacter = pClan->getMainGenreal();
       
        Str16 tempName = pClan->getClanHomeLandName() + pClan->getName() + Str16(L"氏");
		Str16 tempZuZhang;
		if (playerCharacter)
		   tempZuZhang = playerCharacter->getNormalName();
		else
			tempZuZhang = L"无";
		
		//IText* textClanName = getLayout()->getText("text_clanname");
		//textClanName->getWidget()->setCaption(tempName);
        IText* textLClanName = getLayout()->getText("text_lclanname");
        textLClanName->getWidget()->setCaption(tempName);

		IText* textZuZhang = getLayout()->getText("text_zuzhang");
		textZuZhang->getWidget()->setCaption(tempZuZhang);
		
		IText* textJueWei = getLayout()->getText("text_juewei");
		textJueWei->getWidget()->setCaption(L"无"); 

		IText* textZhuDi = getLayout()->getText("text_zhudi");
		textZhuDi->getWidget()->setCaption(L"无");

		IText* textLevel = getLayout()->getText("text_level");
		textLevel->getWidget()->setCaption(L"1");



    }
    //--------------------------------------------------------------------
   /* void UIClanControl::_insertClanList()
    {
        IList* pList = getLayout()->getList("list_clan");
        assert( pList );
        pList->removeAllItems();
        CClan* pClan = NULL;

        std::map<U64, CClan*>* pClanList = CPlayer::getInstance().getClanList();
        if ( pClanList->size() <= 0 )
        {
            DYNAMIC_ASSERT(0);
            return;
        }

        std::map<U64, CClan*>::iterator beginIter = pClanList->begin();
        std::map<U64, CClan*>::iterator backIter = pClanList->end();
        while ( beginIter != backIter )
        {
            pClan = beginIter->second;
            Str16 tempName = pClan->getClanHomeLandName() + L"." + pClan->getName();
            pList->addItem( tempName, pClan->getClanID() );

            ++beginIter;
        }

        pClan = CPlayer::getInstance().getActiveClan();
        assert(pClan);
        mLastIndex = 0;
        mSelectIndex = 0;
        pList->setIndexSelected(mSelectIndex);
    }
	*/
    //--------------------------------------------------------------------

    //--------------------------------------------------------------------
    void UIClanControl::onClickDeleteClan( void* widget )
    {
        assert(widget);
        //UIClanControl::getInstance()._deleteClan();
		CClan* pClan = CPlayer::getInstance().getActiveClan();
		assert(pClan);
		Str16 tempName = pClan->getClanHomeLandName() + pClan->getName();

		Char16 realContent[1024] = {0};

		Str16 tempTitle = CGameMessageConfig::getInstance().getStr(L"clanControl",L"deleteclantitle",L"");
		Str16 tempContent = CGameMessageConfig::getInstance().getStr(L"clanControl",L"deleteclancontent",L"");
		swprintf_s(realContent,1024,tempContent.c_str(),tempName.c_str());



		UIYesNoMsgBox::getInstance().showHint(tempTitle,Str16(realContent),(void*)(&UIClanControl::getInstance()),onNotificateDeleteOk,(void*)(&UIClanControl::getInstance()),onNotificateDeleteCancle);
    }
    //--------------------------------------------------------------------
     void UIClanControl::selectClan()
    {
		
        IdType clanID =  CPlayer::getInstance().getActiveClan()->getClanID();
        assert( clanID );
        LoginManager::getInstance().sendToFrontServerSelectClan(clanID);
    }
    //--------------------------------------------------------------------
         /*void UIClanControl::_exitGame()
    {
        LoginManager::getInstance().sendToFrontServerExitgame();
    }*/
    //--------------------------------------------------------------------
    void UIClanControl::_deleteClan()
    {
		
		IdType clanID =  CPlayer::getInstance().getActiveClan()->getClanID();
		assert( clanID );
		//UIMessageBox::getInstance().showHint()
		LoginManager::getInstance().sendToFrontServerDeleteClan(clanID);

    }
    //--------------------------------------------------------------------
    void UIClanControl::update(Flt delta)
    {
        
    }
    //--------------------------------------------------------------------
   /* void UIClanControl::selectClan(Bool isSuc)
    {
        IList* pList = getLayout()->getList("list_clan");
        assert(pList);

        if ( isSuc )
        {
            mLastIndex = mSelectIndex;

            IAny* tempIAny = pList->getItemDataAt(mSelectIndex);
            assert(tempIAny);
            //如果是同一个，不作为。
            IdType* clanID = tempIAny->castType<IdType>();
            assert( clanID );

            IText* pText = getLayout()->getText("text_clanname");
            assert(pText);

            pText->getWidget()->setCaption(pList->getItemNameAt(mSelectIndex));

            //设置选择的clan为当前氏族。
            CPlayer::getInstance().setActive(*clanID);  

            //其它操作
            //？
        }
        else
        {
            mSelectIndex = mLastIndex;
            pList->setIndexSelected(mSelectIndex);
        }
    }
*/
	void UIClanControl::restore()
	{
		/*IText* textClanName = getLayout()->getText("text_clanname");
		textClanName->getWidget()->setCaption(L"");*/
		IText* textLClanName = getLayout()->getText("text_lclanname");
		textLClanName->getWidget()->setCaption(L"");
	}
	 //--------------------------------------------------------------------
	void UIClanControl::onClickReLogin( void* widget )
	{
		Str16 tempTitle = CGameMessageConfig::getInstance().getStr(L"clanControl",L"returnAccountTitle",L"");
		Str16 tempContent = CGameMessageConfig::getInstance().getStr(L"clanControl",L"returnAccountContent",L"");
		UIYesNoMsgBox::getInstance().showHint(tempTitle,tempContent, (void*)(&UIClanControl::getInstance()),onReturnAccount, NULL, NULL);
	}
	//--------------------------------------------------------------------
	void UIClanControl::onReturnAccount(void* arg)
	{
		
		UIClanControl::getInstance().closeGui();
		UIAccountLogin::getInstance().restore();
		UIAccountLogin::getInstance().openGui();
	}
	 //--------------------------------------------------------------------
	void UIClanControl::onNotificateDeleteOk( void* arg )
	{
      UIClanControl* clanControlInstance = (UIClanControl*)arg;
	  clanControlInstance->_deleteClan();
	 // UIYesNoMsgBox::getInstance().closeGui();


	}
	 //--------------------------------------------------------------------
	void UIClanControl::onNotificateDeleteCancle( void* arg )
	{
        UIYesNoMsgBox::getInstance().closeGui();
		return;
	}
	//--------------------------------------------------------------------
	void UIClanControl::refreshClanInfo( const Str16 zhuZhang,const Str16 jueWei,const Str16 zhuDi,const Str16 level )
	{
		if ( zhuZhang.length() >0 )
		{
			IText* textZuZhang = getLayout()->getText("text_zuzhang");
		    textZuZhang->getWidget()->setCaption(zhuZhang);

		}
		else
		{
			IText* textZuZhang = getLayout()->getText("text_zuzhang");
			textZuZhang->getWidget()->setCaption(L"无");
		}
		
		if ( jueWei.length() >0 )
		{
			IText* textJueWei = getLayout()->getText("text_juewei");
			textJueWei->getWidget()->setCaption(jueWei);

		}
		else
		{
			IText* textJueWei = getLayout()->getText("text_juewei");
			textJueWei->getWidget()->setCaption(L"无");
		}

		if ( zhuDi.length() >0 )
		{
			IText* textZhuDi = getLayout()->getText("text_zhudi");
			textZhuDi->getWidget()->setCaption(zhuDi);

		}
		else
		{
			IText* textZhuDi = getLayout()->getText("text_zhudi");
			textZhuDi->getWidget()->setCaption(L"无");
		}
		
		if ( zhuDi.length() >0 )
		{
			IText* textLevel = getLayout()->getText("text_level");
			textLevel->getWidget()->setCaption(level);

		}
		else
		{
			IText* textZhuDi = getLayout()->getText("text_level");
			textZhuDi->getWidget()->setCaption(L"1");
		}
		
	}

	//--------------------------------------------------------------------
	void UIClanControl::joinGame()
	{
		_joinGame();
	}
}