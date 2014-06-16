//**********************************************************************************************************
#ifndef _H_ITEXT_7589230_
#define _H_ITEXT_7589230_
//**********************************************************************************************************
#include "MGEngineInterfacePreqs.h"
#include "IWidget.h"
//**********************************************************************************************************
//¾²Ì¬ÎÄ×Ö½Ó¿Ú
namespace MG
{
    class IText
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
        virtual void setFontHeight(int _value) = 0;
        /** Get widget text font height */
        virtual int getFontHeight() = 0 ;
    protected:
    private:
    };
}
//**********************************************************************************************************
#endif
//**********************************************************************************************************