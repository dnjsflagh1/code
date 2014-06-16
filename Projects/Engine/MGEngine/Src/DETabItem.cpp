//**********************************************************************************************************
#include "stdafx.h"
#include "DETabItem.h"
//**********************************************************************************************************
namespace MG
{
    DETabItem::DETabItem()
        :mpEGTabItem(nullptr)
    {

    }
    //----------------------------------------------------------------------------------
    DETabItem::~DETabItem()
    {

    }
    //----------------------------------------------------------------------------------
    IWidget* DETabItem::getWidget()
    {
        setEGWidget(mpEGTabItem);
        return this;
    }
    //----------------------------------------------------------------------------------
    Bool DETabItem::setEGTabItem( MyGUI::Widget* p )
    {
        assert(p);
        mpEGTabItem = p->castType<MyGUI::TabItem>();
        assert( mpEGTabItem );
        setEGWidget(p);
        
        return true;
    }
}