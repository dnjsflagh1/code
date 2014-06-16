//**********************************************************************************************************
#include "stdafx.h"
#include "DETimeText.h"
//**********************************************************************************************************
namespace MG
{
	std::map<MyGUI::TimeText*, PVOIDINT_CALLBACK> DETimeText::mMapTimeTextTimeOut;

	DETimeText::DETimeText()
		:mpEGTimeText(NULL)
	{

	}
	//------------------------------------------------------------------------------------------------------
	IWidget* DETimeText::getWidget()
	{
		DYNAMIC_ASSERT(mpEGTimeText);
		setEGWidget(mpEGTimeText);

		return this;
	}
	//------------------------------------------------------------------------------------------------------
	void DETimeText::setCoolDownTime( U32 totalTime, MGTIMETEXT_SHOW_TYPE showtype /*= MGTIMETEXT_SHOW_TYPE_GAME*/, MGTIMETEXT_UNIT_TYPE unittype /*= MGTIMETEXT_UNIT_TYPE_SECOND */ )
	{
		DYNAMIC_ASSERT(mpEGTimeText);

		mpEGTimeText->setCoolDownTime(totalTime, (MyGUI::TIMETEXT_SHOW_TYPE)((int)showtype), (MyGUI::TIMETEXT_UNIT_TYPE)((int)unittype));
	}
	//------------------------------------------------------------------------------------------------------
	void DETimeText::setEventTimeOut( PVOIDINT_CALLBACK func, UInt timeoutTime, UInt spaceTime )
	{
		DYNAMIC_ASSERT(mpEGTimeText);

		mMapTimeTextTimeOut[mpEGTimeText] = func;
		mpEGTimeText->mTimeTextTimeoutEvent = MyGUI::newDelegate(this, &DETimeText::notifyTimeTextTimeOut);

		mpEGTimeText->setTimeoutTime(timeoutTime);
		mpEGTimeText->setSpaceTime(spaceTime);
	}
	//------------------------------------------------------------------------------------------------------
	MG::Bool DETimeText::setEGTimeText( MyGUI::Widget* p )
	{
		DYNAMIC_ASSERT(p);

		mpEGTimeText = p->castType<MyGUI::TimeText>();

		DYNAMIC_ASSERT(mpEGTimeText);

		setEGWidget(p);

		return true;
	}
	//------------------------------------------------------------------------------------------------------
	void DETimeText::notifyTimeTextTimeOut( MyGUI::TimeText* p, int timeoutTime )
	{
		DYNAMIC_ASSERT(p);

		mpEGTimeText = p;
		(*mMapTimeTextTimeOut[mpEGTimeText])(this, timeoutTime);
	}
}