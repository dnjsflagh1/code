//**********************************************************************************************************
#include "stdafx.h"
#include "DETab.h"
//**********************************************************************************************************
namespace MG
{
    std::map<MyGUI::Tab*, PVOIDINT_CALLBACK>                 DETab::mMapTabChangeSelect;

    DETab::DETab()
        :mpEGTab(nullptr)
    {

    }
    //------------------------------------------------------------------------------------------
    DETab::~DETab()
    {

    }
    //------------------------------------------------------------------------------------------
    IWidget* DETab::getWidget()
    {
        setEGWidget(mpEGTab);
        return this;
    }
    //------------------------------------------------------------------------------------------
    void DETab::setEventTabChangeSelect( PVOIDINT_CALLBACK pfunc )
    {
        assert(mpEGTab);
        mMapTabChangeSelect[mpEGTab] = pfunc;
        mpEGTab->eventTabChangeSelect = MyGUI::newDelegate(this, &DETab::notifyTabChangeSelect);
    }
    //------------------------------------------------------------------------------------------
    Bool DETab::setEGTab( MyGUI::Widget* p )
    {
        assert(p);
        mpEGTab = p->castType<MyGUI::Tab>();
        assert(mpEGTab);
        setEGWidget(p);

        return true;
    }
    //------------------------------------------------------------------------------------------
    void DETab::notifyTabChangeSelect( MyGUI::Tab* p, U32 Index )
    {
        assert(p);
        mpEGTab = p;
        setEGWidget(p);
        (mMapTabChangeSelect[mpEGTab])(this, Index);
    }
}