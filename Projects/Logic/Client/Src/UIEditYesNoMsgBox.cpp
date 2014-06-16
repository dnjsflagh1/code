//*************************************************************************************
#include "stdafx.h"
#include "UIEditYesNoMsgBox.h"
#include "CGameMessageConfig.h"
#include "UIMessageBox.h"
#include "ClientMain.h"
//*************************************************************************************
namespace MG
{
	UIEditYesNoMsgBox::UIEditYesNoMsgBox()
		:mpFuncConfirm(NULL)
		,mpUserConfirm(NULL)
		,mpFuncCancel(NULL)
		,mpUserCancel(NULL)
		,mInputCount(0)
		,mMaxCount(0)
	{

	}
	//------------------------------------------------------------------------
	void UIEditYesNoMsgBox::showHint( std::wstring msgTtSec, std::wstring msgTtKey, std::wstring defaultTt, std::wstring msgConSec, std::wstring msgConKey, std::wstring defaultCon, Int maxCount, void* userConfirm /*= NULL*/, PVOIDINTINT_CALLBACK funcConfirm /*= NULL*/, void* userCancel /*= NULL*/, PVOID_CALLBACK funcCancel /*= NULL */ )
	{
		//清空上一次的回调函数
		mpFuncConfirm = funcConfirm;
		mpUserConfirm = userConfirm;
		mpFuncCancel = funcCancel;
		mpUserCancel = userCancel;
		mInputCount = 0;
		mMaxCount = maxCount;
		//设置msg信息
		std::wstring tempTtl =  CGameMessageConfig::getInstance().getStr( msgTtSec, msgTtKey, defaultTt );
		std::wstring tempCon =  CGameMessageConfig::getInstance().getStr( msgConSec, msgConKey, defaultCon );
		getLayout()->getWidget( "_Main" )->setCaption( tempTtl );
		getLayout()->getWidget("count")->setCaption(L"");

		IEdit* edt = getLayout()->getEdit("content");
		DYNAMIC_ASSERT(edt);
		edt->clearEditText(false);
		Int editWidth =static_cast<Int>(getInstance().getLayout()->getEdit("content")->getWidget()->getSize().x) - 30;
		IGui* igui = ClientMain::getInstance().getGui();
		DYNAMIC_ASSERT(igui);
		igui->getHeightStrAddBreak(tempCon,editWidth);
		edt->addText(tempCon);

		
		//打开自己
		openGui();
	}
	//------------------------------------------------------------------------
	void UIEditYesNoMsgBox::showHint( Str16 title,Str16 content, Int maxCount, void* userConfirm /*= NULL*/, PVOIDINTINT_CALLBACK funcConfirm /*= NULL*/, void* userCancel /*= NULL*/, PVOID_CALLBACK funcCancel /*= NULL */ )
	{
		//清空上一次的回调函数
		mpFuncConfirm = funcConfirm;
		mpUserConfirm = userConfirm;
		mpFuncCancel = funcCancel;
		mpUserCancel = userCancel;
		mInputCount = 0;
		mMaxCount = maxCount;
		//设置msg信息
		getLayout()->getWidget( "_Main" )->setCaption( title );
		getLayout()->getWidget( "content" )->setCaption( content );
		getLayout()->getWidget("count")->setCaption(L"");

		IEdit* edt = getLayout()->getEdit("content");
		DYNAMIC_ASSERT(edt);
		edt->clearEditText(false);
		Int editWidth =static_cast<Int>(getInstance().getLayout()->getEdit("content")->getWidget()->getSize().x) - 30;
		IGui* igui = ClientMain::getInstance().getGui();
		DYNAMIC_ASSERT(igui);
		igui->getHeightStrAddBreak(content,editWidth);
		edt->addText(content);
		//打开自己
		openGui();

	}
	//------------------------------------------------------------------------
	void UIEditYesNoMsgBox::setEvent()
	{
		IWidget* pIWidget =  getLayout()->getWidget( "confirm" );
		assert( pIWidget );
		pIWidget->setMouseButtonClickEvent( onclickConfirm );

		pIWidget = getLayout()->getWidget( "cancel" );
		assert( pIWidget );
		pIWidget->setMouseButtonClickEvent( onclickCancel );
	}
	//------------------------------------------------------------------------
	void UIEditYesNoMsgBox::onclickConfirm( void* widget )
	{
		assert(widget);
		UIEditYesNoMsgBox::getInstance().callConfirm();
	}
	//------------------------------------------------------------------------
	void UIEditYesNoMsgBox::onclickCancel( void* widget )
	{
		assert(widget);
		UIEditYesNoMsgBox::getInstance().callCancel();
	}
	//------------------------------------------------------------------------
	void UIEditYesNoMsgBox::callConfirm()
	{
		if ( mpUserConfirm  &&  mpFuncConfirm )
		{
			IEdit* countEdt = getLayout()->getEdit("count");
			assert(countEdt);
			Str16 countStr = countEdt->getCaption();
			if (countStr.length() >= 1)
			{
				MGStrOp::toI32(countStr.c_str(),mInputCount);
			
				mpFuncConfirm( mpUserConfirm, mInputCount,mMaxCount);	
			}
			else
				UIMessageBox::getInstance().showHint(L"请输入数量");
		}
	}
	//------------------------------------------------------------------------
	void UIEditYesNoMsgBox::callCancel()
	{
		if ( mpUserCancel  &&  mpFuncCancel )
			mpFuncCancel( mpUserCancel );
		closeGui();
	}
}