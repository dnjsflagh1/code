//**********************************************************************************************************
#ifndef _H_DEVIEWSCROLL_77589437843_
#define _H_DEVIEWSCROLL_77589437843_
//**********************************************************************************************************
#include "IViewScroll.h"
#include "DEWidget.h"
#include <typeinfo.h>
//**********************************************************************************************************
class  MyGUI::Widget;
class  MyGUI::ScrollView;
//**********************************************************************************************************
namespace MG
{
    class DEViewScroll : public IViewScroll, public DEWidget  
    {
    public:
        DEViewScroll();
        virtual ~DEViewScroll();

    public:
        virtual IWidget*    getWidget();
        virtual int         getChildNum(); 
        virtual void        clear();
        virtual void        setCanvasSize(const Vec2& _value);
        virtual void        setCanvasSize(Int _width, Int _height);
        virtual VecI2       getCanvasSize();
		virtual void		setVisibleVScroll(bool _value);
		virtual void		setVisibleHScroll(bool _value);
       
    public:
        //引擎事件
        Bool                setEGViewScroll(MyGUI::Widget* p);
        MyGUI::Widget*      getEGViewScroll(){return mpEGViewScroll;}
    private:
        //引擎对象指针
        MyGUI::ScrollView* mpEGViewScroll;
    };
}
//**********************************************************************************************************
#endif
//**********************************************************************************************************