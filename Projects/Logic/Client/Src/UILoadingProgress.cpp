//***************************************************************************************************
#include "stdafx.h"
#include "UILoadingProgress.h"
//***************************************************************************************************
namespace MG
{
	UILoadingProgress::UILoadingProgress()
		:mProgress(0.0f)
	{

	}
	//----------------------------------------------------------------------------------------
	UILoadingProgress::~UILoadingProgress()
	{

	}
	//----------------------------------------------------------------------------------------
	bool UILoadingProgress::openGui()
	{
		setValue(0.0f);
		return UIObject::openGui();

	}
	//----------------------------------------------------------------------------------------
	bool UILoadingProgress::closeGui()
	{
		return UIObject::closeGui();
	}
	//----------------------------------------------------------------------------------------
	void UILoadingProgress::setEvent()
	{
	}
	//----------------------------------------------------------------------------------------
	void UILoadingProgress::setPosition( Int val )
	{
		
	}
	//----------------------------------------------------------------------------------------
	void UILoadingProgress::setText( Char16* str )
	{
	}

	//----------------------------------------------------------------------------------------
	void UILoadingProgress::update(Flt delta)
	{
	}

	//----------------------------------------------------------------------------------------

	void UILoadingProgress::setValue(Flt val)
	{
		val = max(val, 0.0f);
		val = min(1.0f, val);

		mProgress = val;
		val *= 100.0f;

		Str16 caption;
		MGStrOp::toString((Int)val, caption);
		caption += L"%";


		IProgress* progress = getLayout()->getProgress("Progress_Loading");

		if ( progress )
		{	
			progress->setProgressPosition( mProgress );
			progress->getWidget()->setCaption(caption);
		}

	}

	//----------------------------------------------------------------------------------------
	Flt UILoadingProgress::getValue()
	{
		return mProgress;
	}
}