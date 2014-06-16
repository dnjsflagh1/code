//*************************************************************************************************************
#include "stdafx.h"
#include "DEHScroll.h"
//*************************************************************************************************************
namespace MG
{
	std::map<MyGUI::HScroll*, PVOIDINT_CALLBACK>		DEHScroll::mMapScrollChangePosition;
	//------------------------------------------------------------------------------------------------
	DEHScroll::DEHScroll()
		:mEGHScroll(NULL)
	{

	}
	//------------------------------------------------------------------------------------------------
	MG::Bool DEHScroll::setEGHScroll( MyGUI::Widget* p )
	{
		DYNAMIC_ASSERT(p);
		mEGHScroll = p->castType<MyGUI::HScroll>();
		DYNAMIC_ASSERT(mEGHScroll);
		setEGWidget(p);

		return true;
	}
	//------------------------------------------------------------------------------------------------
	IWidget* DEHScroll::getWidget()
	{
		DYNAMIC_ASSERT(mEGHScroll);
		setEGWidget(mEGHScroll);

		return this;
	}
	//------------------------------------------------------------------------------------------------
	void DEHScroll::setScrollRange( size_t _value )
	{
		DYNAMIC_ASSERT(mEGHScroll);

		mEGHScroll->setScrollPage(_value);
	}
	//------------------------------------------------------------------------------------------------
	size_t DEHScroll::getScrollRange()
	{
		DYNAMIC_ASSERT(mEGHScroll);

		return mEGHScroll->getScrollRange();
	}
	//------------------------------------------------------------------------------------------------
	void DEHScroll::setScrollPosition( size_t _value )
	{
		DYNAMIC_ASSERT(mEGHScroll);

		mEGHScroll->setScrollPosition(_value);
	}
	//------------------------------------------------------------------------------------------------
	size_t DEHScroll::getScrollPosition()
	{
		DYNAMIC_ASSERT(mEGHScroll);

		return mEGHScroll->getScrollPosition();
	}
	//------------------------------------------------------------------------------------------------
	void DEHScroll::setScrollPage( size_t _value )
	{
		DYNAMIC_ASSERT(mEGHScroll);

		mEGHScroll->setScrollPage(_value);
	}
	//------------------------------------------------------------------------------------------------
	size_t DEHScroll::getScrollPage()
	{
		DYNAMIC_ASSERT(mEGHScroll);

		return mEGHScroll->getScrollPage();
	}
	//------------------------------------------------------------------------------------------------
	void DEHScroll::setScrollViewPage( size_t _value )
	{
		DYNAMIC_ASSERT(mEGHScroll);

		mEGHScroll->setScrollViewPage(_value);
	}
	//------------------------------------------------------------------------------------------------
	size_t DEHScroll::getScrollViewPage()
	{
		DYNAMIC_ASSERT(mEGHScroll);

		return mEGHScroll->getScrollViewPage();
	}
	//------------------------------------------------------------------------------------------------
	void DEHScroll::setMoveToClick( bool _value )
	{
		DYNAMIC_ASSERT(mEGHScroll);

		mEGHScroll->setMoveToClick(_value);
	}
	//------------------------------------------------------------------------------------------------
	bool DEHScroll::getMoveToClick()
	{
		DYNAMIC_ASSERT(mEGHScroll);

		return mEGHScroll->getMoveToClick();
	}
	//------------------------------------------------------------------------------------------------
	void DEHScroll::setPosition( const VecI2& _value )
	{
		DYNAMIC_ASSERT(mEGHScroll);

		MyGUI::IntPoint tempPos;
		tempPos.left = _value.x;
		tempPos.top = _value.y;
		mEGHScroll->setPosition(tempPos);
	}
	//------------------------------------------------------------------------------------------------
	void DEHScroll::setSize( const VecI2& _value )
	{
		DYNAMIC_ASSERT(mEGHScroll);

		MyGUI::IntSize tempSize;
		tempSize.width = _value.x;
		tempSize.height = _value.y;
		mEGHScroll->setSize(tempSize);
	}
	//------------------------------------------------------------------------------------------------
	void DEHScroll::setCoord( const CoordI& _value )
	{
		DYNAMIC_ASSERT(mEGHScroll);

		MyGUI::IntCoord tempCoord;
		tempCoord.left = _value.left;
		tempCoord.top = _value.top;
		tempCoord.width = _value.width;
		tempCoord.height = _value.height;
		mEGHScroll->setCoord(tempCoord);
	}
	//------------------------------------------------------------------------------------------------
	void DEHScroll::setScrollChangePositionEvent( PVOIDINT_CALLBACK func )
	{
		mMapScrollChangePosition[mEGHScroll] = func;

		mEGHScroll->eventScrollChangePosition = MyGUI::newDelegate(this, &DEHScroll::notifyScrollChangePositionEvent);
	}
	//------------------------------------------------------------------------------------------------
	void DEHScroll::notifyScrollChangePositionEvent( MyGUI::VScroll* scorll, size_t pos )
	{
		DYNAMIC_ASSERT(scorll);
		mEGHScroll = scorll->castType<MyGUI::HScroll>();

		mMapScrollChangePosition[mEGHScroll](this, pos);
	}
}