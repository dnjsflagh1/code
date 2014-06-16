//*************************************************************************************************************
#ifndef _H_DEHSCROLL_
#define _H_DEHSCROLL_
//*************************************************************************************************************
#include "IHScorll.h"
#include "DEWidget.h"
//*************************************************************************************************************
namespace MG
{
	class DEHScroll : public IHScroll, public DEWidget
	{
	public:
		DEHScroll();
		virtual ~DEHScroll(){;}

	public:
		Bool							setEGHScroll(MyGUI::Widget* p);
		MyGUI::Widget*					getEGHScroll(){return mEGHScroll;}

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
		static std::map<MyGUI::HScroll*, PVOIDINT_CALLBACK>		mMapScrollChangePosition;

	private:
		MyGUI::HScroll*					mEGHScroll;
	};
}
//*************************************************************************************************************
#endif
//*************************************************************************************************************