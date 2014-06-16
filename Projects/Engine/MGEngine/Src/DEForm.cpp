//**********************************************************************************************************
#include "stdafx.h"
#include "DEForm.h"
//**********************************************************************************************************
//**********************************************************************************************************
namespace MG
{ 
    std::map<MyGUI::Window*, PVOID_CALLBACK>             DEForm::mMapWindowButtonPressedCallBack;
    std::map<MyGUI::Window*, PVOID_CALLBACK>             DEForm::mMapWindowChangeCoordCallBack;

    DEForm::DEForm()
        :mpEGForm(nullptr)
    {

    }
    //-----------------------------------------------------------------------------
    DEForm::~DEForm()
    {

    }
    //-----------------------------------------------------------------------------
    Bool DEForm::setEGForm( MyGUI::Widget* p )
    {
        assert( p );
        mpEGForm = p->castType<MyGUI::Window>();
        assert( mpEGForm );
        setEGWidget(p);
        return true;
    }
    //-----------------------------------------------------------------------------
    IWidget* DEForm::getWidget()
    {
        setEGWidget(mpEGForm);
        return this;
    }
    //-----------------------------------------------------------------------------
    void DEForm::setWindowButtonPressedEvent( PVOID_CALLBACK pfunc )
    {
        assert ( mpEGForm );  
        mMapWindowButtonPressedCallBack[mpEGForm] = pfunc;
        mpEGForm->eventWindowButtonPressed = MyGUI::newDelegate(this, &DEForm::notifyWindowButtonPressed);
    }
    //-----------------------------------------------------------------------------
    void DEForm::setWindowChangeCoordEvent( PVOID_CALLBACK pfunc )
    {
        assert ( mpEGForm );  
        mMapWindowChangeCoordCallBack[mpEGForm] = pfunc;
        mpEGForm->eventWindowChangeCoord = MyGUI::newDelegate(this, &DEForm::notifyWindowChangeCoord);
    }
    //-----------------------------------------------------------------------------
    void DEForm::notifyWindowButtonPressed( MyGUI::Window* p, const std::string& name )
    {
        mpEGForm = p;
        assert (mpEGForm);
        setEGWidget(p);
        if ( name == "close" )
            (mMapWindowButtonPressedCallBack[mpEGForm])(this);
    }
    //-----------------------------------------------------------------------------
    void DEForm::notifyWindowChangeCoord( MyGUI::Window* p )
    {
        mpEGForm = p;
        assert (mpEGForm);
        setEGWidget(p);
        (mMapWindowChangeCoordCallBack[mpEGForm])(this);
    }
    //-----------------------------------------------------------------------------
    void DEForm::setImageCoord( const CoordI& _coord )
    {
        assert (mpEGForm);

        MyGUI::IntCoord tempCoord(_coord.left,_coord.top, _coord.width, _coord.height);

        mpEGForm->setImageCoord(tempCoord);
    }
    //-----------------------------------------------------------------------------
    void DEForm::setImageSize( const VecI2& _size )
    {
        assert (mpEGForm);

        MyGUI::IntSize tempSize(_size.x, _size.y);
        mpEGForm->setImageSize(tempSize);
    }
    //-----------------------------------------------------------------------------
    void DEForm::setImagePosition( const VecI2& _point )
    {
        assert (mpEGForm);

        MyGUI::IntPoint tempPoint(_point.x, _point.y);
        mpEGForm->setImagePosition(tempPoint);
    }
	//-----------------------------------------------------------------------------
	void DEForm::setItemTexture( const Str8& _resource, const Str8& _group, const Str8& _name )
	{
		assert (mpEGForm);

		mpEGForm->setItemResource(_resource);
		mpEGForm->setItemGroup(_group);
		mpEGForm->setItemName(_name);
	}
}