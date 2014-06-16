//*************************************************************************************************************
#include "stdafx.h"
#include "DEVScroll.h"
//*************************************************************************************************************
namespace MG
{
	std::map<MyGUI::VScroll*, PVOIDINT_CALLBACK>		DEVScroll::mMapScrollChangePosition;
	//------------------------------------------------------------------------------------------------
	DEVScroll::DEVScroll()
		:mEGVScroll(NULL)
	{

	}
	//------------------------------------------------------------------------------------------------
	MG::Bool DEVScroll::setEGVScroll( MyGUI::Widget* p )
	{
		DYNAMIC_ASSERT(p);
		mEGVScroll = p->castType<MyGUI::VScroll>();
		DYNAMIC_ASSERT(mEGVScroll);
		setEGWidget(p);

		return true;
	}
	//------------------------------------------------------------------------------------------------
	IWidget* DEVScroll::getWidget()
	{
		DYNAMIC_ASSERT(mEGVScroll);
		setEGWidget(mEGVScroll);

		return this;
	}
	//------------------------------------------------------------------------------------------------
	void DEVScroll::setScrollRange( size_t _value )
	{
		DYNAMIC_ASSERT(mEGVScroll);

		mEGVScroll->setScrollPage(_value);
	}
	//------------------------------------------------------------------------------------------------
	size_t DEVScroll::getScrollRange()
	{
		DYNAMIC_ASSERT(mEGVScroll);

		return mEGVScroll->getScrollRange();
	}
	//------------------------------------------------------------------------------------------------
	void DEVScroll::setScrollPosition( size_t _value )
	{
		DYNAMIC_ASSERT(mEGVScroll);

		mEGVScroll->setScrollPosition(_value);
	}
	//------------------------------------------------------------------------------------------------
	size_t DEVScroll::getScrollPosition()
	{
		DYNAMIC_ASSERT(mEGVScroll);

		return mEGVScroll->getScrollPosition();
	}
	//------------------------------------------------------------------------------------------------
	void DEVScroll::setScrollPage( size_t _value )
	{
		DYNAMIC_ASSERT(mEGVScroll);

		mEGVScroll->setScrollPage(_value);
	}
	//------------------------------------------------------------------------------------------------
	size_t DEVScroll::getScrollPage()
	{
		DYNAMIC_ASSERT(mEGVScroll);

		return mEGVScroll->getScrollPage();
	}
	//------------------------------------------------------------------------------------------------
	void DEVScroll::setScrollViewPage( size_t _value )
	{
		DYNAMIC_ASSERT(mEGVScroll);

		mEGVScroll->setScrollViewPage(_value);
	}
	//------------------------------------------------------------------------------------------------
	size_t DEVScroll::getScrollViewPage()
	{
		DYNAMIC_ASSERT(mEGVScroll);

		return mEGVScroll->getScrollViewPage();
	}
	//------------------------------------------------------------------------------------------------
	void DEVScroll::setMoveToClick( bool _value )
	{
		DYNAMIC_ASSERT(mEGVScroll);

		mEGVScroll->setMoveToClick(_value);
	}
	//------------------------------------------------------------------------------------------------
	bool DEVScroll::getMoveToClick()
	{
		DYNAMIC_ASSERT(mEGVScroll);

		return mEGVScroll->getMoveToClick();
	}
	//------------------------------------------------------------------------------------------------
	void DEVScroll::setPosition( const VecI2& _value )
	{
		DYNAMIC_ASSERT(mEGVScroll);

		MyGUI::IntPoint tempPos;
		tempPos.left = _value.x;
		tempPos.top = _value.y;
		mEGVScroll->setPosition(tempPos);
	}
	//------------------------------------------------------------------------------------------------
	void DEVScroll::setSize( const VecI2& _value )
	{
		DYNAMIC_ASSERT(mEGVScroll);

		MyGUI::IntSize tempSize;
		tempSize.width = _value.x;
		tempSize.height = _value.y;
		mEGVScroll->setSize(tempSize);
	}
	//------------------------------------------------------------------------------------------------
	void DEVScroll::setCoord( const CoordI& _value )
	{
		DYNAMIC_ASSERT(mEGVScroll);

		MyGUI::IntCoord tempCoord;
		tempCoord.left = _value.left;
		tempCoord.top = _value.top;
		tempCoord.width = _value.width;
		tempCoord.height = _value.height;
		mEGVScroll->setCoord(tempCoord);
	}
	//------------------------------------------------------------------------------------------------
	void DEVScroll::setScrollChangePositionEvent( PVOIDINT_CALLBACK func )
	{
		mMapScrollChangePosition[mEGVScroll] = func;

		mEGVScroll->eventScrollChangePosition = MyGUI::newDelegate(this, &DEVScroll::notifyScrollChangePositionEvent);
	}
	//------------------------------------------------------------------------------------------------
	void DEVScroll::notifyScrollChangePositionEvent( MyGUI::VScroll* scorll, size_t pos )
	{
		DYNAMIC_ASSERT(scorll);
		mEGVScroll = scorll;

		mMapScrollChangePosition[scorll](this, pos);
	}
}