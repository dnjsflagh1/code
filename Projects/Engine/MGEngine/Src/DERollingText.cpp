//**********************************************************************************************************
#include "stdafx.h"
#include "DERollingText.h"
//**********************************************************************************************************
namespace MG
{
    std::map<MyGUI::RollingText*, PVOID_CALLBACK>                    DERollingText::mMapRollingTextNone;

    DERollingText::DERollingText()
        :mpEGRollingText(NULL)
    {

    }
	//-------------------------------------------------------------------------------------------
    DERollingText::~DERollingText()
    {

    }
    //-------------------------------------------------------------------------------------------
    IWidget* DERollingText::getWidget()
    {
        setEGWidget(mpEGRollingText);

        return this;
    }
    //-------------------------------------------------------------------------------------------
    void DERollingText::addMsg( Str16 msg, U32 rollingTime, Byte priority )
    {
        assert ( mpEGRollingText ); 

        mpEGRollingText->addMsg(msg, rollingTime, priority);
    }
    //-------------------------------------------------------------------------------------------
    void DERollingText::setEventRollingTextNone( PVOID_CALLBACK pFunc )
    {
        assert ( mpEGRollingText );

        mMapRollingTextNone[mpEGRollingText] = pFunc;
        mpEGRollingText->mEventRollingTextNone = MyGUI::newDelegate(this, &DERollingText::notifyRollingTextNone);
    }
    //-------------------------------------------------------------------------------------------
    MG::Bool DERollingText::setEGRollingText( MyGUI::Widget* p )
    {
        assert(p);
        mpEGRollingText = p->castType<MyGUI::RollingText>();
        assert(mpEGRollingText);
        setEGWidget(p);

        return true;
    }
    //-------------------------------------------------------------------------------------------
    void DERollingText::notifyRollingTextNone( MyGUI::RollingText* p )
    {
        assert ( p );

        mpEGRollingText = p;
        mMapRollingTextNone[mpEGRollingText](this);
    }
}