//*************************************************************************************************************
#ifndef _H_DEVSCROLL_
#define _H_DEVSCROLL_
//*************************************************************************************************************
#include "IVScorll.h"
#include "DEWidget.h"
//*************************************************************************************************************
namespace MG
{
	class DEVScroll : public IVScroll, public DEWidget
	{
	public:
		DEVScroll();
		virtual ~DEVScroll(){;}

	public:
		Bool							setEGVScroll(MyGUI::Widget* p);
		MyGUI::Widget*					getEGVScroll(){return mEGVScroll;}

	public:
		virtual IWidget*				getWidget();
		virtual void					setScrollRange(size_t _value);
		virtual size_t					getScrollRange();
		virtual void					setScrollPosition(size_t _value);
		virtual size_t					getScrollPosition();
		virtual void					setScrollPage(size_t _value);
		virtual size_t					getScrollPage();
		virtual void					setScrollViewPage(size_t _value);
		virtual size_t					getScrollViewPage();
		virtual void					setMoveToClick(bool _value);
		virtual bool					getMoveToClick();
		virtual void					setPosition(const VecI2& _value);
		virtual void					setSize(const VecI2& _value);
		virtual void					setCoord(const CoordI& _value);

	public:
		virtual void					setScrollChangePositionEvent(PVOIDINT_CALLBACK func);

	private:
		void							notifyScrollChangePositionEvent(MyGUI::VScroll* scorll, size_t pos);

	private:
		static std::map<MyGUI::VScroll*, PVOIDINT_CALLBACK>		mMapScrollChangePosition;

	private:
		MyGUI::VScroll*					mEGVScroll;
	};
}
//*************************************************************************************************************
#endif
//*************************************************************************************************************