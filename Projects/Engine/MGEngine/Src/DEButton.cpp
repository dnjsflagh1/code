//**********************************************************************************************************
#include "stdafx.h"
#include "DEButton.h"
//**********************************************************************************************************
//**********************************************************************************************************
namespace MG
{ 
    DEButton::DEButton()
        :mpEGButon(nullptr)
    {

    }
    //-----------------------------------------------------------------------------
    DEButton::~DEButton()
    {

    }
    //-----------------------------------------------------------------------------
    Bool DEButton::setEGButton( MyGUI::Widget* p )
    {
        assert( p );
       mpEGButon = p->castType<MyGUI::Button>();
       assert ( mpEGButon );
       setEGWidget(p);
       return true;
    }
    //-----------------------------------------------------------------------------
    IWidget* DEButton::getWidget()
    {
        assert( mpEGButon );
        setEGWidget(mpEGButon);
        return this;
    }
    //-----------------------------------------------------------------------------
    void DEButton::setTextColour( const Color& value )
    {
        assert(mpEGButon);
        mpEGButon->setTextColour(MyGUI::Colour(value.r, value.g, value.b, value.a));
    }
    //-----------------------------------------------------------------------------
    const Color DEButton::getTextColour()
    {
        assert(mpEGButon);
        MyGUI::Colour tempcolour = mpEGButon->getTextColour();
        return Color(tempcolour.red, tempcolour.green, tempcolour.blue, tempcolour.alpha);
    }
    //-----------------------------------------------------------------------------
    void DEButton::setImageResource( const std::string& _name, const std::string& _group )
    {
        assert(mpEGButon);
        MyGUI::ImageBox* tempImage = mpEGButon->getStaticImage();
        if ( tempImage )
        {    
            tempImage->setItemResource( _name ); 
            tempImage->setItemGroup( _group );
        }
    }
    //-----------------------------------------------------------------------------
    void DEButton::setTextAlign( MGAlign _value )
    {
        assert(mpEGButon);
        MyGUI::Align temp((MyGUI::Align::Enum)(int)_value);
        mpEGButon->setTextAlign(temp);
    }
    //-----------------------------------------------------------------------------
    void DEButton::setFontName( const std::string& _value )
    {
        assert(mpEGButon);
        mpEGButon->setFontName(_value);
    }
    //-----------------------------------------------------------------------------
    const std::string& DEButton::getFontName()
    {
        assert(mpEGButon);
        return mpEGButon->getFontName();
    }
    //-----------------------------------------------------------------------------
    void DEButton::setFontHeight( int _value )
    {
        assert(mpEGButon);
        mpEGButon->setFontHeight(_value);
    }
    //-----------------------------------------------------------------------------
    int DEButton::getFontHeight()
    {
        assert(mpEGButon);
        return mpEGButon->getFontHeight();
    }
    //-----------------------------------------------------------------------------
    void DEButton::setStateCheck( Bool _value )
    {
        assert(mpEGButon);
        mpEGButon->setStateCheck(_value);
    }
    //-----------------------------------------------------------------------------
    MG::Bool DEButton::getStateCheck()
    {
        assert(mpEGButon);
        return mpEGButon->getStateCheck();
    }
}