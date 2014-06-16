//*************************************************************************************
#include "stdafx.h"
#include "UILoginLineUp.h"
#include "LoginManager.h"
#include "ClientMain.h"
#include "UISelectServer.h"
#include "CGameMessageConfig.h"
#include "ClientNetApplyManager.h"
//*************************************************************************************
namespace MG
{
    
    //--------------------------------------------------------------------------------
	void UILoginLineUp::setFullServerName()
	{
		Str16 tempFullName = UISelectServer::getInstance().getSelectMainZoneName() + L"-" + UISelectServer::getInstance().getSelectSubZoneName();
        IWidget* pWidget = getLayout()->getText("text_servername")->getWidget();
		DYNAMIC_ASSERT(pWidget);
		pWidget->setCaption(tempFullName);
	}
	 //--------------------------------------------------------------------------------
	void UILoginLineUp::setTextVisible( const Str8& name,Bool isVisible )
	{
         IWidget* pWidget = getLayout()->getText(name)->getWidget();
		 DYNAMIC_ASSERT(pWidget);
         pWidget->setVisible(isVisible);
   
	}

	//
	void UILoginLineUp::setEvent()
	{
		IButton* btnLogin = getLayout()->getButton("btn_cancle");
		btnLogin->getWidget()->setMouseButtonClickEvent(onClickCancle);
	}
	//--------------------------------------------------------------------------------
	void UILoginLineUp::adjustUI( LineUpType lineUpType )
 	{

       /*  setFullServerName();
		 //
		 Char16 tempState[50] = {0};
         swprintf_s(tempState,50,L"serverstate%d",lineUpType);
		 Str16 serverState = CGameMessageConfig::getInstance().getStr(L"loginlineup",Str16(tempState),L"");
         getLayout()->getText("text_serverstate")->getWidget()->setCaption(serverState);
		 //
         Char16 tempContent[50] = {0};
		 swprintf_s(tempContent,50,L"content%d",lineUpType);
		 Str16 serverContent = CGameMessageConfig::getInstance().getStr(L"loginlineup",Str16(tempContent),L"");
		 getLayout()->getText("text_content")->getWidget()->setCaption(serverContent);

		 // 
		 Char16 tempWaitContent[50] = {0};
		 swprintf_s(tempWaitContent,50,L"waitcontent%d",lineUpType);
		 Str16 serverWaitContent = CGameMessageConfig::getInstance().getStr(L"loginlineup",Str16(tempWaitContent),L"");
		 getLayout()->getText("text_wait")->getWidget()->setCaption(serverWaitContent);


         if ( lineUpType == LINE_UP_TYPE_BUSY)
         {     
               Str16 ranKed = CGameMessageConfig::getInstance().getStr(L"loginlineup",L"ranked",L"");
			   getLayout()->getText("text_ranked")->getWidget()->setCaption(ranKed);
               //
			   setTextVisible("text_ranked",true);
			   setTextVisible("text_number",true); 
         }
		 else if ( lineUpType == LINE_UP_TYPE_FULL)
		 {
             setTextVisible("text_ranked",false);
			 setTextVisible("text_number",false); 

		 }
		*/
	}
	//--------------------------------------------------------------------------------
	void UILoginLineUp::handleClickCancle()
	{
		//断开登入服务器
		ClientNetApplyManager::getInstance().disconnectLoginServer();
		this->closeGui();
	}
	//--------------------------------------------------------------------------------
	void UILoginLineUp::onClickCancle( void* widget )
	{
        if (widget)
        {
			UILoginLineUp::getInstance().handleClickCancle();
        }
	}
	//--------------------------------------------------------------------------------
	MG::Bool UILoginLineUp::openGui()
	{      
		return UIObject::openGui();
	}
	//--------------------------------------------------------------------------------
	void UILoginLineUp::restore()
	{

	}
	//--------------------------------------------------------------------------------
	void UILoginLineUp::update(Flt delta)
	{
	         //TODO
		     //增加自动更新  算时间差


	}
	//--------------------------------------------------------------------------------
	void UILoginLineUp::setRanKed( const Str16& ranKed )
	{
         if ( isTextVisible("text_ranked"))
         {
              IWidget* pWidget = NULL;
			  pWidget = getLayout()->getText("text_number")->getWidget();
			  DYNAMIC_ASSERT(pWidget);
		      pWidget->setCaption(ranKed);
         }
	}
	//--------------------------------------------------------------------------------
	Bool UILoginLineUp::isTextVisible( const Str8& name )
	{
          IWidget* pWidget = NULL;
		  pWidget = getLayout()->getText(name)->getWidget();
		  DYNAMIC_ASSERT(pWidget);
		  return pWidget->isVisible();
	}
	//--------------------------------------------------------------------------------
}