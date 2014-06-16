//**********************************************************************************************************
#include "stdafx.h"
#include "DEViewScroll.h"
//**********************************************************************************************************
//**********************************************************************************************************
namespace MG
{ 
    DEViewScroll::DEViewScroll()
        :mpEGViewScroll(nullptr)
    {

    }
    //-----------------------------------------------------------------------------
    DEViewScroll::~DEViewScroll()
    {

    }
    //-----------------------------------------------------------------------------
    Bool DEViewScroll::setEGViewScroll( MyGUI::Widget* p )
    {
        assert(p);
        mpEGViewScroll = p->castType<MyGUI::ScrollView>();
        assert(mpEGViewScroll);
        setEGWidget(p);
        return true;
    }
    //-----------------------------------------------------------------------------
    IWidget* DEViewScroll::getWidget()
    {
        assert(mpEGViewScroll);
        setEGWidget(mpEGViewScroll);
        return this;
    }
    //-----------------------------------------------------------------------------
    int DEViewScroll::getChildNum()
    {
        assert(mpEGViewScroll);
        return mpEGViewScroll->getChildCount();
    }
    //-----------------------------------------------------------------------------
    void DEViewScroll::clear()
    {
        assert(mpEGViewScroll);
        Int nCount = mpEGViewScroll->getChildCount();
        for (Int i= 0; i<nCount; i++)
        {
            MyGUI::Widget* childWidget = mpEGViewScroll->getChildAt(0);
            MyGUI::WidgetManager::getInstance().destroyWidget(childWidget);
        }
    }
    //-----------------------------------------------------------------------------
    void DEViewScroll::setCanvasSize( const Vec2& _value )
    {
        assert(mpEGViewScroll);
        mpEGViewScroll->setCanvasSize(_value.x, _value.y);
    }
    //-----------------------------------------------------------------------------
    void DEViewScroll::setCanvasSize( Int _width, Int _height )
    {
        assert(mpEGViewScroll);
        mpEGViewScroll->setCanvasSize(_width, _height);
    }
    //-----------------------------------------------------------------------------
    VecI2 DEViewScroll::getCanvasSize()
    {
        assert(mpEGViewScroll);
        MyGUI::IntSize size = mpEGViewScroll->getCanvasSize();
        return VecI2(size.width, size.height); 
    }
	//-----------------------------------------------------------------------------
	void DEViewScroll::setVisibleVScroll( bool _value )
	{
		assert(mpEGViewScroll);

		mpEGViewScroll->setVisibleVScroll(_value);
	}
	//-----------------------------------------------------------------------------
	void DEViewScroll::setVisibleHScroll( bool _value )
	{
		assert(mpEGViewScroll);

		mpEGViewScroll->setVisibleHScroll(_value);
	}
}