//***************************************************************************************************
#include "stdafx.h"
#include "UIProgress.h"
//***************************************************************************************************
namespace MG
{
    UIProgress::UIProgress()
    {

    }
    //----------------------------------------------------------------------------------------
    UIProgress::~UIProgress()
    {

    }
    //----------------------------------------------------------------------------------------
    void UIProgress::setEvent()
    {
		//getLayout()->getProgress("progress_1")->setProgressPosition(0.f);
    }
	//----------------------------------------------------------------------------------------
	void UIProgress::setPosition( Int val )
	{
		if (val < 0 || val > 100)
		{
			val = 0;
		}
		//getLayout()->getProgress("progress_1")->setProgressPosition(val);
	}
	//----------------------------------------------------------------------------------------
	void UIProgress::setText( Char16* str )
	{
		getLayout()->getText("text_1")->getWidget()->setCaption(str);
	}

	void UIProgress::update()
	{
		static Int i = 0;
		i++;
		if (i > 100)
		{
			i = 0;
		}
		setPosition(i);
	}

	//----------------------------------------------------------------------------------------

	

}