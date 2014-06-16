//*****************************************************************************************************************
#include "stdafx.h"
#include "DEMixListRow.h"
#include "GuiDelegateElementPool.h"
//*****************************************************************************************************************
namespace MG
{
    DEMixListRow::DEMixListRow()
        :mpEGMixListRow(NULL)
    {

    }
    //----------------------------------------------------------------------------------
    IWidget* DEMixListRow::getWidget()
    {
        DYNAMIC_ASSERT(mpEGMixListRow);
        setEGWidget(mpEGMixListRow);

        return this;
    }
    //----------------------------------------------------------------------------------
    void DEMixListRow::setId( Int id )
    {
        DYNAMIC_ASSERT(mpEGMixListRow);
        mpEGMixListRow->setId(id);
    }
    //----------------------------------------------------------------------------------
    void DEMixListRow::setMixListRowName( Str16 name )
    {
        DYNAMIC_ASSERT(mpEGMixListRow);
        mpEGMixListRow->setName(name);
    }
    //----------------------------------------------------------------------------------
    MG::Int DEMixListRow::getId()
    {
        DYNAMIC_ASSERT(mpEGMixListRow);
        return mpEGMixListRow->getId();
    }
    //----------------------------------------------------------------------------------
    MG::Str16 DEMixListRow::getMixListRowName()
    {
        DYNAMIC_ASSERT(mpEGMixListRow);
        return mpEGMixListRow->getName();
    }
    //----------------------------------------------------------------------------------
    IButton* DEMixListRow::getButton( Int index )
    {
        DYNAMIC_ASSERT(mpEGMixListRow);
        MyGUI::Widget* tempWidget = mpEGMixListRow->getChildAt(index);
        DYNAMIC_ASSERT(tempWidget);

        return GuiDgElmPool::getInstance().getDEButton(tempWidget);
    }
	//----------------------------------------------------------------------------------
	Int  DEMixListRow::getIndex()
	{
		return mpEGMixListRow->getIndex();
	}
    //----------------------------------------------------------------------------------
    IImage* DEMixListRow::getImage( Int index )
    {
        DYNAMIC_ASSERT(mpEGMixListRow);
        MyGUI::Widget* tempWidget = mpEGMixListRow->getChildAt(index);
        DYNAMIC_ASSERT(tempWidget);

        return GuiDgElmPool::getInstance().getDEImage(tempWidget);
    }
    //----------------------------------------------------------------------------------
    IText* DEMixListRow::getText( Int index )
    {
        DYNAMIC_ASSERT(mpEGMixListRow);
        MyGUI::Widget* tempWidget = mpEGMixListRow->getChildAt(index);
        DYNAMIC_ASSERT(tempWidget);

        return GuiDgElmPool::getInstance().getDEText(tempWidget);
    }
    //----------------------------------------------------------------------------------
    MG::Bool DEMixListRow::setEGMixListRow( MyGUI::Widget* p )
    {
        DYNAMIC_ASSERT(p);
        mpEGMixListRow = p->castType<MyGUI::MixListRow>();
        DYNAMIC_ASSERT(mpEGMixListRow);

        return true;
    }
    //----------------------------------------------------------------------------------
    IWidget* DEMixListRow::getChildWidget( Int index )
    {
        DYNAMIC_ASSERT(mpEGMixListRow);
        MyGUI::Widget* tempWidget = mpEGMixListRow->getChildAt(index);
        DYNAMIC_ASSERT(tempWidget);

        return GuiDgElmPool::getInstance().getDEWidget(tempWidget);
    }
}