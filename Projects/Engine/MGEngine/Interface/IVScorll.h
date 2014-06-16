//*************************************************************************************************************
#ifndef _H_IVSCROLL_
#define _H_IVSCROLL_
//*************************************************************************************************************
#include "IWidget.h"
//*************************************************************************************************************
namespace MG
{
	class IVScroll
	{
	public:
		virtual IWidget*				getWidget() = 0;

		//设置滑动按钮可移动的范围（自己强加的意义）
		virtual void					setScrollRange(size_t _value) = 0;
		/** Get scroll range */
		virtual size_t					getScrollRange() = 0;

		/** 设置滑动按钮的位置 (value from 0 to range - 1) */
		virtual void					setScrollPosition(size_t _value) = 0;
		/** Get scroll position (value from 0 to range - 1) */
		virtual size_t					getScrollPosition()  = 0;

		/** Set scroll page
		@param _page Tracker step when buttons pressed
		*/
		virtual void					setScrollPage(size_t _value) = 0;
		/** Get scroll page */
		virtual size_t					getScrollPage()  = 0;

		/** Set scroll view page
		@param _viewPage Tracker step when pressed on scroll line
		*/
		virtual void					setScrollViewPage(size_t _value)  = 0;
		/** Get scroll view page */
		virtual size_t					getScrollViewPage()  = 0;

		/** Enable or disable move to click mode.\n
		Move to click mode: Tracker moves to cursor when pressed on scroll line.\n
		Disabled (false) by default.
		*/
		virtual void					setMoveToClick(bool _value)  = 0;
		/** Get move to click mode flag */
		virtual bool					getMoveToClick() = 0;

		//! @copydoc Widget::setPosition(const IntPoint& _value)
		virtual void					setPosition(const VecI2& _value) = 0;
		//! @copydoc Widget::setSize(const IntSize& _value)
		virtual void					setSize(const VecI2& _value) = 0;
		//! @copydoc Widget::setCoord(const IntCoord& _value)
		virtual void					setCoord(const CoordI& _value) = 0;

	public:
		virtual void					setScrollChangePositionEvent(PVOIDINT_CALLBACK func) = 0;

	};
}
//*************************************************************************************************************
#endif
//*************************************************************************************************************