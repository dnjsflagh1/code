//**********************************************************************************************************
#include "stdafx.h"
#include "DEText.h"
//**********************************************************************************************************
//**********************************************************************************************************
namespace MG
{ 
    DEText::DEText()
        :mpEGText(nullptr)
    {

    }
    //-----------------------------------------------------------------------------
    DEText::~DEText()
    {

    }
    //-----------------------------------------------------------------------------
    Bool DEText::setEGText( MyGUI::Widget* p )
    {
        assert(p);
        mpEGText = p->castType<MyGUI::StaticText>();
        assert( mpEGText );
        setEGWidget(p);
        return true;
    }
    //-----------------------------------------------------------------------------
    IWidget* DEText::getWidget()
    {
        setEGWidget(mpEGText);
        return this;
    }
    //-----------------------------------------------------------------------------
    void DEText::setTextColour( const Color& value )
    {
        assert(mpEGText);
        mpEGText->setTextColour(MyGUI::Colour(value.r, value.g, value.b, value.a));
    }
    //-----------------------------------------------------------------------------
    const Color DEText::getTextColour()
    {
        assert(mpEGText);
        MyGUI::Colour tempcolour = mpEGText->getTextColour();
        return Color(tempcolour.red, tempcolour.green, tempcolour.blue, tempcolour.alpha);
    }
    //-----------------------------------------------------------------------------
    void DEText::setTextAlign( MGAlign _value )
    {
        assert(mpEGText);
        MyGUI::Align temp((MyGUI::Align::Enum)(int)_value);
        mpEGText->setTextAlign( temp );
    }
    //-----------------------------------------------------------------------------
    void DEText::setFontName( const std::string& _value )
    {
        assert(mpEGText);
        mpEGText->setFontName(_value);
    }
    //-----------------------------------------------------------------------------
    const std::string& DEText::getFontName()
    {
        assert(mpEGText);
        return mpEGText->getFontName();
    }
    //-----------------------------------------------------------------------------
    void DEText::setFontHeight( int _value )
    {
        assert(mpEGText);
        mpEGText->setFontHeight(_value);
    }
    //-----------------------------------------------------------------------------
    int DEText::getFontHeight()
    {
        assert(mpEGText);
        return mpEGText->getFontHeight();
    }
}