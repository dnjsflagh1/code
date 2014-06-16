//**********************************************************************************************************
#ifndef _H_DETEXT_7290875084093_
#define _H_DETEXT_7290875084093_
//**********************************************************************************************************
#include "IText.h"
#include "DEWidget.h"
//**********************************************************************************************************
class  MyGUI::Widget;
//**********************************************************************************************************
namespace MG
{
    class DEText : public IText, public DEWidget  
    {
    public:
                                DEText();
        virtual                 ~DEText();

    public:
        virtual IWidget*        getWidget();
        virtual void            setTextColour(const Color& value);
        virtual const Color     getTextColour();
        virtual void            setTextAlign(MGAlign _value);
        virtual void            setFontName(const std::string& _value);
        virtual const std::string& getFontName();
        virtual void            setFontHeight(int _value);
        virtual int             getFontHeight();

    public:
        //引擎事件
                Bool            setEGText(MyGUI::Widget* p);
                MyGUI::Widget*  getEGText(){return mpEGText;}

    private:
        //引擎对象指针
        MyGUI::StaticText*                                              mpEGText;

    };
}
//**********************************************************************************************************
#endif
//**********************************************************************************************************