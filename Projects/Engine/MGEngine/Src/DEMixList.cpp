//*****************************************************************************************************************
#include "stdafx.h"
#include "DEMixList.h"
#include "GuiDelegateElementPool.h"
#include "DEMixListRow.h"
//*****************************************************************************************************************
namespace MG
{
    std::map<MyGUI::MixList*, PVOIDINT_CALLBACK>                      DEMixList::mMapClickCallBack;
    std::map<MyGUI::MixList*, PVOIDINT_CALLBACK>                      DEMixList::mMapDoubleClickCallBack;

    DEMixList::DEMixList()
        :mpEGMixList(NULL)
    {

    }
    //----------------------------------------------------------------------------------
    IWidget* DEMixList::getWidget()
    {
        DYNAMIC_ASSERT(mpEGMixList);
        setEGWidget(mpEGMixList);

        return this;
    }
    //----------------------------------------------------------------------------------
    IMixListRow* DEMixList::getMixListRow( int _id )
    {
        DYNAMIC_ASSERT(mpEGMixList);
        MyGUI::MixListRow* tempRow = mpEGMixList->getMixListRow(_id);
        if ( tempRow )
            return GuiDgElmPool::getInstance().getDEMixListRow(tempRow);

        return NULL;
    }
    //----------------------------------------------------------------------------------
    IMixListRow* DEMixList::getMixListRow( std::wstring _name )
    {
        DYNAMIC_ASSERT(mpEGMixList);
        MyGUI::MixListRow* tempRow = mpEGMixList->getMixListRow(_name);
        if ( tempRow )
            return GuiDgElmPool::getInstance().getDEMixListRow(tempRow);

        return NULL;
    }
    //----------------------------------------------------------------------------------
    IMixListRow* DEMixList::getMixListRow( int _id, std::wstring _name )
    {
        DYNAMIC_ASSERT(mpEGMixList);
        MyGUI::MixListRow* tempRow = mpEGMixList->getMixListRow(_id, _name);
        if ( tempRow )
            return GuiDgElmPool::getInstance().getDEMixListRow(tempRow);

        return NULL;
    }
    //----------------------------------------------------------------------------------
    IMixListRow* DEMixList::addLine( int _id, std::wstring _name )
    {
        DYNAMIC_ASSERT(mpEGMixList);
        MyGUI::MixListRow* tempRow = mpEGMixList->addLine(_id, _name);
        if ( tempRow )
            return GuiDgElmPool::getInstance().getDEMixListRow(tempRow);
        return NULL;
    }
    //----------------------------------------------------------------------------------
    void DEMixList::removeLine( int _id )
    {
        DYNAMIC_ASSERT(mpEGMixList);
        mpEGMixList->removeLine(_id);
    }
    //----------------------------------------------------------------------------------
    void DEMixList::removeLine( std::wstring _name )
    {
        DYNAMIC_ASSERT(mpEGMixList);
        mpEGMixList->removeLine(_name);
    }
    //----------------------------------------------------------------------------------
    void DEMixList::removeAllLine()
    {
        DYNAMIC_ASSERT(mpEGMixList);
        mpEGMixList->removeAllLine();
    }
    //----------------------------------------------------------------------------------
    MG::Bool DEMixList::setEGMixList( MyGUI::Widget* p )
    {
        DYNAMIC_ASSERT(p);
        mpEGMixList = p->castType<MyGUI::MixList>();
        DYNAMIC_ASSERT(mpEGMixList);
        setEGWidget(p);

        return false;
    }
    //----------------------------------------------------------------------------------
    void DEMixList::setClickMixListRow( PVOIDINT_CALLBACK func )
    {
        DYNAMIC_ASSERT(mpEGMixList);
        mMapClickCallBack[mpEGMixList] = func;

        mpEGMixList->mClickMixListRowNode = MyGUI::newDelegate(this, &DEMixList::notifyMouseButtonClick);
    }
    //----------------------------------------------------------------------------------
    void DEMixList::notifyMouseButtonClick( MyGUI::MixList* p, int Index )
    {
        DYNAMIC_ASSERT(p);
        mpEGMixList = p ;

        mMapClickCallBack[mpEGMixList](this, Index);
    }
    //----------------------------------------------------------------------------------
    IMixListRow* DEMixList::getMixListRowByIndex( int _index )
    {
        DYNAMIC_ASSERT(mpEGMixList);
        MyGUI::MixListRow* tempRow = mpEGMixList->getMixListRowByIndex(_index);
        if ( tempRow )
            return GuiDgElmPool::getInstance().getDEMixListRow(tempRow);

        return NULL;
    }
    //----------------------------------------------------------------------------------
    MG::Int DEMixList::getMixLixRowCount()
    {
        DYNAMIC_ASSERT(mpEGMixList);

        return mpEGMixList->getMixLixRowCount();
    }
    //----------------------------------------------------------------------------------
    void DEMixList::setDoubleClickMixListRow( PVOIDINT_CALLBACK func )
    {
        DYNAMIC_ASSERT(mpEGMixList);
        mMapDoubleClickCallBack[mpEGMixList] = func;

        mpEGMixList->mDoubleClickMixListRowNode = MyGUI::newDelegate(this, &DEMixList::notifyMouseButtonDoubleClick);
    }
    //----------------------------------------------------------------------------------
    void DEMixList::notifyMouseButtonDoubleClick( MyGUI::MixList* p, int index )
    {
        DYNAMIC_ASSERT(p);
        mpEGMixList = p ;

        mMapDoubleClickCallBack[mpEGMixList](this, index);
    }
	//----------------------------------------------------------------------------------
	void DEMixList::setSelectIndex( int index )
	{
		DYNAMIC_ASSERT(mpEGMixList);

		mpEGMixList->setSelectIndex(index);
	}
	//----------------------------------------------------------------------------------
	MG::Int DEMixList::getSelectIndex()
	{
		DYNAMIC_ASSERT(mpEGMixList);

		return mpEGMixList->getSelectIndex();
	}
}