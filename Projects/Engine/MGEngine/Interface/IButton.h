//**********************************************************************************************************
#ifndef _H_IBUTTON_75843979_
#define _H_IBUTTON_75843979_
//**********************************************************************************************************

#include "MGEngineInterfacePreqs.h"
#include "IWidget.h"

//**********************************************************************************************************
//按钮接口
namespace MG
{
    class IButton
    {
    public:
        virtual IWidget*        getWidget() = 0;
        virtual void            setTextColour(const Color& value) = 0;
        virtual const Color     getTextColour() = 0;
        /** Set widget text align */
        virtual void            setTextAlign(MGAlign _value) = 0;
        /** Set widget text font */
        virtual void            setFontName(const std::string& _value) = 0;
        /** Get widget text font name */
        virtual const std::string& getFontName() = 0;
        /** Set widget text font height */
        virtual void            setFontHeight(int _value) = 0;
        /** Get widget text font height */
        virtual int             getFontHeight() = 0 ;
        //设置texture资源
        virtual void            setImageResource(const std::string& _name, const std::string& _group) = 0;
        //! Set button check state
        virtual void            setStateCheck(Bool _value) = 0;
        //! Get buton check
       virtual  Bool            getStateCheck() = 0;
    protected:
    private:
    };
}
//**********************************************************************************************************
#endif
//**********************************************************************************************************