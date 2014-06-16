//*************************************************************************************
#include "stdafx.h"
#include "UIYesNoMsgBox.h"
#include "CGameMessageConfig.h"
#include "HandleDropEvent.h"
#include "IGui.h"
#include "ClientMain.h"
//*************************************************************************************
namespace MG
{
	UIYesNoMsgBox::UIYesNoMsgBox()
		:mpFuncConfirm(NULL)
		,mpUserConfirm(NULL)
		,mpFuncCansel(NULL)
		,mpUserCansel(NULL)
	{

	}
	//------------------------------------------------------------------------
	void UIYesNoMsgBox::showHint( std::wstring msgTtSec, std::wstring msgTtKey, std::wstring defaultTt, std::wstring msgConSec, std::wstring msgConKey, std::wstring defaultCon, void* userConfirm /*= NULL*/, PVOID_CALLBACK funcConfirm /*= NULL*/, void* userCansel /*= NULL*/, PVOID_CALLBACK funcCansel /*= NULL */ )
	{
		//清空上一次的回调函数
		mpFuncConfirm = funcConfirm;
		mpUserConfirm = userConfirm;
		mpFuncCansel = funcCansel;
		mpUserCansel = userCansel;
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
	//------------------------------------------------------------------------
	void UIYesNoMsgBox::showHint( Str16 title,Str16 content,void* userConfirm /*= NULL*/, PVOID_CALLBACK funcConfirm /*= NULL*/,void* userCansel /*= NULL*/, PVOID_CALLBACK funcCansel /*= NULL */ )
	{
		//清空上一次的回调函数
		mpFuncConfirm = funcConfirm;
		mpUserConfirm = userConfirm;
		
		mpFuncCansel = funcCansel;
		mpUserCansel = userCansel;
		//设置msg信息
		getLayout()->getWidget( "_Main" )->setCaption( title );
		//getLayout()->getWidget( "content" )->setCaption( content );
		IEdit* edt = getLayout()->getEdit("content");
		DYNAMIC_ASSERT(edt);
		edt->clearEditText(false);
		Int editWidth = getEditBoxWidth();
		IGui* igui = ClientMain::getInstance().getGui();
		DYNAMIC_ASSERT(igui);
		igui->getHeightStrAddBreak(content,editWidth);
		edt->addText(content);
		//打开自己
		openGui();

	}
	//------------------------------------------------------------------------
	void UIYesNoMsgBox::setEvent()
	{
		IWidget* pIWidget =  getLayout()->getWidget( "confirm" );
		assert( pIWidget );
		pIWidget->setMouseButtonClickEvent( onclickConfirm );

		pIWidget = getLayout()->getWidget( "cansel" );
		assert( pIWidget );
		pIWidget->setMouseButtonClickEvent( onclickCansel );
	}
	//------------------------------------------------------------------------
	void UIYesNoMsgBox::onclickConfirm( void* widget )
	{
		assert(widget);
		UIYesNoMsgBox::getInstance().callConfirm();
	}
	//------------------------------------------------------------------------
	void UIYesNoMsgBox::onclickCansel( void* widget )
	{
		assert(widget);
		UIYesNoMsgBox::getInstance().callCansel();
	}
	//------------------------------------------------------------------------
	void UIYesNoMsgBox::callConfirm()
	{
		if ( mpUserConfirm  &&  mpFuncConfirm )
			mpFuncConfirm( mpUserConfirm );
		closeGui();
	}
	//------------------------------------------------------------------------
	void UIYesNoMsgBox::callCansel()
	{
		if ( mpUserCansel  &&  mpFuncCansel )
			mpFuncCansel( mpUserCansel );
		closeGui();
	}
	//----------------------------------------------------------------------------------------
	Int UIYesNoMsgBox::getEditBoxWidth()
	{
	
		return (static_cast<Int>(getInstance().getLayout()->getEdit("content")->getWidget()->getSize().x) - 30);
	}
	//----------------------------------------------------------------------------------------
	Int UIYesNoMsgBox::getEditBoxHeight()
	{
		return (static_cast<Int>(getInstance().getLayout()->getEdit("content")->getWidget()->getSize().y) - 30);
	}
}