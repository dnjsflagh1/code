//**********************************************************************************************************
#ifndef _H_IVIEWSCROLL_758324915_
#define _H_IVIEWSCROLL_758324915_
//**********************************************************************************************************
#include "MGEngineInterfacePreqs.h"
#include "IWidget.h"
//**********************************************************************************************************
//带滚动条的区域接口
namespace MG
{
    class IViewScroll
    {
    public:
        virtual IWidget*    getWidget() = 0;
        virtual int         getChildNum() = 0;
        //清空所有子控件。
        virtual void        clear() = 0;
        /** Set canvas size */
        virtual void        setCanvasSize(const Vec2& _value) = 0;
        /** Set canvas size */
        virtual void        setCanvasSize(Int _width, Int _height) = 0;
        /** Get canvas size */
        virtual VecI2       getCanvasSize() = 0;
		/** Show VScroll when text size larger than Edit */
		virtual void		setVisibleVScroll(bool _value) = 0;
		/** Show HScroll when text size larger than Edit */
		virtual void		setVisibleHScroll(bool _value) = 0;
      
    protected:
    private:
    };
}
//**********************************************************************************************************
#endif
//**********************************************************************************************************