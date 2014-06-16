//*************************************************************************************
#include "stdafx.h"
#include "UISplitItem.h"
#include "CGameMessageConfig.h"
#include "UIMessageBox.h"
//*************************************************************************************
namespace MG
{
	UISplitItem::UISplitItem()
		:mpFuncConfirm(NULL)
		,mpUserConfirm(NULL)
		,mpFuncCancel(NULL)
		,mpUserCancel(NULL)
		,mInputSplitCount(0)
		,mMaxCount(0)
	{

	}
	//------------------------------------------------------------------------
	void UISplitItem::showHint( std::wstring msgTtSec, std::wstring msgTtKey, std::wstring defaultTt, std::wstring msgConSec, std::wstring msgConKey, std::wstring defaultCon, Int maxCount, void* userConfirm /*= NULL*/, PVOIDINTINT_CALLBACK funcConfirm /*= NULL*/, void* userCancel /*= NULL*/, PVOID_CALLBACK funcCancel /*= NULL */ )
	{
		//清空上一次的回调函数
		mInputSplitCount = 1;
		mpFuncConfirm = funcConfirm;
		mpUserConfirm = userConfirm;
		mpFuncCancel = funcCancel;
		mpUserCancel = userCancel;
		mMaxCount = maxCount;
		//设置msg信息
		std::wstring tempTtl =  CGameMessageConfig::getInstance().getStr( msgTtSec, msgTtKey, defaultTt );
		std::wstring tempCon =  CGameMessageConfig::getInstance().getStr( msgConSec, msgConKey, defaultCon );
		getLayout()->getWidget( "_Main" )->setCaption( tempTtl );
		getLayout()->getWidget( "content" )->setCaption( tempCon );
		getLayout()->getWidget("countTxt")->setCaption(L"1");
		setAutoNumberEnabled(0,false);
		setAutoNumberEnabled(1,true);
		
		//打开自己
		openGui();
	}
	//------------------------------------------------------------------------
	void UISplitItem::showHint( Str16 title,Str16 content, Int maxCount, void* userConfirm /*= NULL*/, PVOIDINTINT_CALLBACK funcConfirm /*= NULL*/, void* userCancel /*= NULL*/, PVOID_CALLBACK funcCancel /*= NULL */ )
	{
		//清空上一次的回调函数
		//打开默认输入为1
		mInputSplitCount = 1;
		mpFuncConfirm = funcConfirm;
		mpUserConfirm = userConfirm;
		mpFuncCancel = funcCancel;
		mpUserCancel = userCancel;
		
		mMaxCount = maxCount;
		//设置msg信息
		getLayout()->getWidget( "_Main" )->setCaption( title );
		getLayout()->getWidget( "content" )->setCaption( content );
		getLayout()->getWidget("countTxt")->setCaption(L"1");
		setAutoNumberEnabled(0,false);
		setAutoNumberEnabled(1,true);
		//打开自己
		openGui();

	}
	//------------------------------------------------------------------------
	void UISplitItem::init()
	{
		IEdit *edt = getLayout()->getEdit("countTxt");
		assert(edt);
		edt->setCaption(L"");
		edt->setTextChangeEvent(onInputSplitTextChange);
	}
	//------------------------------------------------------------------------
	void UISplitItem::setEvent()
	{
		init();
		IWidget* pIWidget =  getLayout()->getWidget( "confirm" );
		assert( pIWidget );
		pIWidget->setMouseButtonClickEvent( onclickConfirm );

		pIWidget = getLayout()->getWidget( "cancel" );
		assert( pIWidget );
		pIWidget->setMouseButtonClickEvent( onclickCancel );

		pIWidget = getLayout()->getWidget( "decBtn" );
		assert( pIWidget );
		pIWidget->setMouseButtonClickEvent(onClickBtnLeft);

		pIWidget = getLayout()->getWidget("addBtn");
		assert( pIWidget );
		pIWidget->setMouseButtonClickEvent(onClickBtnRight);
	}
	//------------------------------------------------------------------------
	void UISplitItem::onInputSplitTextChange( void* widget )
	{
		assert(widget);
		IEdit* countEdt = (IEdit*)widget;
		assert(countEdt);
		Str16 countStr = countEdt->getCaption();
		if (countStr.length() >= 1)
		{
			Int tempCount;
			MGStrOp::toI32(countStr.c_str(),tempCount);

			if(tempCount >= UISplitItem::getInstance().mMaxCount)
			{
				UISplitItem::getInstance().mInputSplitCount = UISplitItem::getInstance().mMaxCount - 1;
				UISplitItem::getInstance().setAutoNumberEnabled(1,false);
				UISplitItem::getInstance().setAutoNumberEnabled(0,true);
				UISplitItem::getInstance().setEditCountValue();
				return;
			}
			if (tempCount <= 1)
			{
				UISplitItem::getInstance().mInputSplitCount = 1;
				UISplitItem::getInstance().setAutoNumberEnabled(0,false);
				UISplitItem::getInstance().setAutoNumberEnabled(1,true);
				UISplitItem::getInstance().setEditCountValue();
				return;
			}
			UISplitItem::getInstance().mInputSplitCount = tempCount;
			UISplitItem::getInstance().setAutoNumberEnabled(0,true);
			UISplitItem::getInstance().setAutoNumberEnabled(1,true);
		}
	}
	//------------------------------------------------------------------------
	void UISplitItem::onclickConfirm( void* widget )
	{
		assert(widget);
		UISplitItem::getInstance().callConfirm();
	}
	//------------------------------------------------------------------------
	void UISplitItem::onclickCancel( void* widget )
	{
		assert(widget);
		UISplitItem::getInstance().callCancel();
	}
	//------------------------------------------------------------------------
	void UISplitItem::setAutoNumberEnabled(U32 index, bool enable)
	{
		//0左边自减，1右边自增
		if (index == 0)
		{
			IButton* lbtn = getLayout()->getButton("decBtn");
			assert(lbtn);
			lbtn->getWidget()->setEnabled(enable);
		}
		else
		{
			IButton* rbtn = getLayout()->getButton("addBtn");
			assert(rbtn);
			rbtn->getWidget()->setEnabled(enable);
		}
	}
	//------------------------------------------------------------------------
	void UISplitItem::setEditCountValue()
	{
		IEdit* countEdt = getLayout()->getEdit("countTxt");
		assert(countEdt);
		Char16 tempchar[16] = L"";
		swprintf_s(tempchar, 16, L"%d", mInputSplitCount);
		countEdt->setCaption(tempchar);
	}
	//------------------------------------------------------------------------
	void UISplitItem::onClickBtnRight( void* widget )
	{
		assert(widget);
		assert(UISplitItem::getInstance().mMaxCount);
		IWidget* pwidget = (IWidget*) widget;
		UISplitItem::getInstance().setAutoNumberEnabled(0,true);

		if(UISplitItem::getInstance().mInputSplitCount < UISplitItem::getInstance().mMaxCount - 1)
		{
			UISplitItem::getInstance().mInputSplitCount += 1;
		}
		else
		{
			UISplitItem::getInstance().mInputSplitCount = UISplitItem::getInstance().mMaxCount - 1;
		}

		UISplitItem::getInstance().setEditCountValue();

		if (UISplitItem::getInstance().mInputSplitCount == UISplitItem::getInstance().mMaxCount - 1)
		{
			pwidget->setEnabled(false);
		}
	}
	//------------------------------------------------------------------------
	void UISplitItem::onClickBtnLeft( void* widget )
	{
		assert(widget);
		assert(UISplitItem::getInstance().mMaxCount);
		IWidget* pwidget = (IWidget*) widget;
		UISplitItem::getInstance().setAutoNumberEnabled(1,true);

		if(UISplitItem::getInstance().mInputSplitCount > 1)
		{
			UISplitItem::getInstance().mInputSplitCount -= 1;
		}
		else
		{
			UISplitItem::getInstance().mInputSplitCount = 1;
		}

		UISplitItem::getInstance().setEditCountValue();

		if (UISplitItem::getInstance().mInputSplitCount == 1)
		{
			pwidget->setEnabled(false);
		}
	}
	//------------------------------------------------------------------------
	void UISplitItem::callConfirm()
	{
		if ( mpUserConfirm  &&  mpFuncConfirm )
		{
			if (mInputSplitCount > 0 && mInputSplitCount < mMaxCount)
			{
				mpFuncConfirm( mpUserConfirm, mInputSplitCount, mMaxCount);	
			}
			else
				UIMessageBox::getInstance().showHint(L"请输入正确的拆分数量");
			closeGui();
		}
	}
	//------------------------------------------------------------------------
	void UISplitItem::callCancel()
	{
		if ( mpUserCancel  &&  mpFuncCancel )
			mpFuncCancel( mpUserCancel );
		closeGui();
	}
}