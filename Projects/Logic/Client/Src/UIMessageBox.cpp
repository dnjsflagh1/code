//*************************************************************************************
#include "stdafx.h"
#include "UIMessageBox.h"
#include "CGameMessageConfig.h"
#include "IGui.h"
#include "ClientMain.h"
//*************************************************************************************
namespace MG
{
    UIMessageBox::UIMessageBox()
        :mpFuncConfirm(NULL)
        ,mpUserConfirm(NULL)
    {

    }
    //---------------------------------------------------------------------
    UIMessageBox::~UIMessageBox()
    {

    }
    //---------------------------------------------------------------------
    void UIMessageBox::showHint( std::wstring msgTtSec, std::wstring msgTtKey, std::wstring defaultTt, 
        std::wstring msgConSec, std::wstring msgConKey, std::wstring defaultCon,
        void* userConfirm /*= NULL*/, PVOID_CALLBACK funcConfirm /*= NULL*/
        )
    {
        //清空上一次的回调函数
        mpFuncConfirm = funcConfirm;
        mpUserConfirm = userConfirm;
        //设置msg信息
        std::wstring tempTtl =  CGameMessageConfig::getInstance().getStr( msgTtSec, msgTtKey, defaultTt );
        std::wstring tempCon =  CGameMessageConfig::getInstance().getStr( msgConSec, msgConKey, defaultCon );
        getLayout()->getWidget( "_Main" )->setCaption( tempTtl );

		IEdit* edt = getLayout()->getEdit("content");
		DYNAMIC_ASSERT(edt);
		edt->clearEditText(false);
		Int editWidth = getEditBoxWidth();
		IGui* igui = ClientMain::getInstance().getGui();
		DYNAMIC_ASSERT(igui);
		igui->getHeightStrAddBreak(tempCon,editWidth);
		edt->addText(tempCon);

        //打开自己
        openGui();
    }

	//---------------------------------------------------------------------
	void UIMessageBox::showHint( std::wstring msg )
	{
		showHint(L"", L"", msg,L"", L"", msg);
	}

    //---------------------------------------------------------------------
    void UIMessageBox::onclickConfirm( void* widget )
    {
        assert(widget);
        UIMessageBox::getInstance().callConfirm();
    }
    //---------------------------------------------------------------------
    void UIMessageBox::callConfirm()
    {
        if ( mpUserConfirm  &&  mpFuncConfirm )
            mpFuncConfirm( mpUserConfirm );
        closeGui();
    }
    //---------------------------------------------------------------------
    void UIMessageBox::setEvent()
    {
        IButton* pButton =  getLayout()->getButton( "confirm" );
        assert( pButton );
        pButton->getWidget()->setMouseButtonClickEvent( onclickConfirm );
    }
	//----------------------------------------------------------------------------------------
	Int UIMessageBox::getEditBoxWidth()
	{
		return (static_cast<Int>(getInstance().getLayout()->getEdit("content")->getWidget()->getSize().x) - 30);
	}
	//----------------------------------------------------------------------------------------
	Int UIMessageBox::getEditBoxHeight()
	{
		return (static_cast<Int>(getInstance().getLayout()->getEdit("content")->getWidget()->getSize().y) - 30);
	}
}
