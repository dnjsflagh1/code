//**********************************************************************************************************
#ifndef _H_DEBUTTON_7584397589_
#define _H_DEBUTTON_7584397589_
//**********************************************************************************************************
#include "IButton.h"
#include "DEWidget.h"
//**********************************************************************************************************
class  MyGUI::Widget;
class  MyGUI::Button;
struct MyGUI::MouseButton;
//**********************************************************************************************************
namespace MG
{
    class DEButton : public IButton, public DEWidget  
    {
    public:
                                DEButton();
        virtual                 ~DEButton();
    public:
        virtual IWidget*        getWidget();
        virtual void            setTextColour(const Color& value);
        virtual const Color     getTextColour();
        virtual void            setImageResource(const std::string& _name, const std::string& _group);
        virtual void            setTextAlign(MGAlign _value);
        virtual void            setFontName(const std::string& _value);
        virtual const std::string& getFontName();
        virtual void            setFontHeight(int _value);
        virtual int             getFontHeight();
        virtual void            setStateCheck(Bool _value);
        virtual Bool            getStateCheck();
          
    public:
                Bool            setEGButton(MyGUI::Widget* p);
                MyGUI::Widget*  getEGButton(){return mpEGButon;}
        
    private:
        //引擎对象指针
        MyGUI::Button*                                          mpEGButon;
       
    };
}
//**********************************************************************************************************
#endif
//**********************************************************************************************************