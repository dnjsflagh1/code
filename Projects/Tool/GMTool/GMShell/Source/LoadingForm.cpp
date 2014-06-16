#include "StdAfx.h"
#include "LoadingForm.h"

namespace MG {

	//-----------------------------------------------------------------------------
	void LoadingForm::showMessage(String^msg)
	{
		BEGINDELEGATE(LoadingForm,showMessage)
			ADDDELEGATEPARAMETER msg
			ENDDELEGATE

			lbl_show_msg->Text = msg;

		this->Show();
		Refresh();
	}

	//-----------------------------------------------------------------------------
	void LoadingForm::loadGameTextConfig()
	{
		BEGINDELEGATE(LoadingForm,loadGameTextConfig)
			ENDDELEGATE
	}

}