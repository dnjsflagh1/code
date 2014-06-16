//**********************************************************************************************************
#include "stdafx.h"
#include "DEList.h"
//**********************************************************************************************************
namespace  MG
{
    std::map<MyGUI::ListBox*, PVOIDINT_CALLBACK> DEList::mMapListSelectAccept;
    std::map<MyGUI::ListBox*, PVOIDINT_CALLBACK> DEList::mMapListChangePosition;
    std::map<MyGUI::ListBox*, PVOIDINT_CALLBACK> DEList::mMapListMouseItemActivate;
    std::map<MyGUI::ListBox*, PVOIDINT_CALLBACK> DEList::mMapListMouseItemFocus;
    std::map<MyGUI::ListBox*, PVOIDINT_CALLBACK> DEList::mMapListChangeScroll;

    DEList::DEList()
        :mpEGList(nullptr)
    {

    }
    //-----------------------------------------------------------------------------------
    DEList::~DEList()
    {

    }
    //-----------------------------------------------------------------------------------
    IWidget* DEList::getWidget()
    {
        setEGWidget(mpEGList);
        return this;
    }
    //-----------------------------------------------------------------------------------
    U32 DEList::getItemCount()
    {
        assert(mpEGList);
        return mpEGList->getItemCount();
    }
    //-----------------------------------------------------------------------------------
    void DEList::insertItemAt( U32 _index, const Str16& _name, IAny _data )
    {
        assert(mpEGList);
        mpEGList->insertItemAt(_index, _name, _data) ;
    }
    //-----------------------------------------------------------------------------------
    UInt DEList::addItem(const Str16& _name, IAny _data )
    {
        assert(mpEGList);

        mpEGList->addItem(_name, _data);

        return mpEGList->getItemCount() - 1;
    }
    //-----------------------------------------------------------------------------------
    void DEList::removeItemAt( U32 _index )
    {
        assert(mpEGList);
        mpEGList->removeItemAt(_index);
    }
    //-----------------------------------------------------------------------------------
    void DEList::removeAllItems()
    {
        assert(mpEGList);
        mpEGList->removeAllItems();
    }
    //-----------------------------------------------------------------------------------
    void DEList::swapItemsAt( U32 _index1, U32 _index2 )
    {
        assert(mpEGList);
        mpEGList->swapItemsAt(_index1, _index2);
    }
    //-----------------------------------------------------------------------------------
    U32 DEList::findItemIndexWith( const Str16& _name )
    {
        assert(mpEGList);
        return mpEGList->findItemIndexWith(_name);
    }
    //-----------------------------------------------------------------------------------
    U32 DEList::getIndexSelected()
    {
        assert(mpEGList);
        return mpEGList->getIndexSelected();
    }
    //-----------------------------------------------------------------------------------
    void DEList::setIndexSelected( U32 _index )
    {
        assert(mpEGList);
        mpEGList->setIndexSelected(_index);
    }
    //-----------------------------------------------------------------------------------
    void DEList::clearIndexSelected()
    {
        assert(mpEGList);
        mpEGList->clearIndexSelected();
    }
    //-----------------------------------------------------------------------------------
    void DEList::setEventListSelectAccept( PVOIDINT_CALLBACK pFunc )
    {
        assert(mpEGList);
        mMapListSelectAccept[mpEGList] = pFunc;
        mpEGList->eventListSelectAccept = MyGUI::newDelegate(this, &DEList::notifyListSelectAccept);
    }
    //-----------------------------------------------------------------------------------
    void DEList::setEeventListChangePosition( PVOIDINT_CALLBACK pFunc )
    {
        assert(mpEGList);
        mMapListChangePosition[mpEGList] = pFunc;
        mpEGList->eventListChangePosition = MyGUI::newDelegate(this, &DEList::notifyListChangePosition);
    }
    //-----------------------------------------------------------------------------------
    void DEList::setEventListMouseItemActivate( PVOIDINT_CALLBACK pFunc )
    {
        assert(mpEGList);
        mMapListMouseItemActivate[mpEGList] = pFunc;
        mpEGList->eventListMouseItemActivate = MyGUI::newDelegate(this, &DEList::notifyListMouseItemActivate);
    }
    //-----------------------------------------------------------------------------------
    void DEList::setEventListMouseItemFocus( PVOIDINT_CALLBACK pFunc )
    {
        assert(mpEGList);
        mMapListMouseItemFocus[mpEGList] = pFunc;
        mpEGList->eventListMouseItemFocus = MyGUI::newDelegate(this, &DEList::notifyListMouseItemFocus);
    }
    //-----------------------------------------------------------------------------------
    void DEList::setEventListChangeScroll( PVOIDINT_CALLBACK pFunc )
    {
        assert(mpEGList);
        mMapListChangeScroll[mpEGList] = pFunc;
        mpEGList->eventListChangeScroll = MyGUI::newDelegate(this, &DEList::notifyListChangeScroll);
    }
    //-----------------------------------------------------------------------------------
    Bool DEList::setEGList( MyGUI::Widget* p )
    {
        assert(p);
        mpEGList = p->castType<MyGUI::ListBox>();
        assert(mpEGList);
        setEGWidget(p);

        return true;
    }
    //-----------------------------------------------------------------------------------
    void DEList::notifyListSelectAccept( MyGUI::ListBox* p, U32 _index )
    {
        assert(p);
        mpEGList = p;
        setEGWidget(p);
        (mMapListSelectAccept[mpEGList])( this, _index );
    }
    //-----------------------------------------------------------------------------------
    void DEList::notifyListChangePosition( MyGUI::ListBox* p, U32 _index )
    {
        assert(p);
        mpEGList = p;
        setEGWidget(p);
        (mMapListChangePosition[mpEGList])(this, _index);
    }
    //-----------------------------------------------------------------------------------
    void DEList::notifyListMouseItemActivate( MyGUI::ListBox* p, U32 _index )
    {
        assert(p);
        mpEGList = p;
        setEGWidget(p);
        (mMapListMouseItemActivate[mpEGList])(this, _index);
    }
    //-----------------------------------------------------------------------------------
    void DEList::notifyListMouseItemFocus( MyGUI::ListBox* p, U32 _index )
    {
        assert(p);
        mpEGList = p;
        setEGWidget(p);
        (mMapListMouseItemFocus[mpEGList])(this, _index);
    }
    //-----------------------------------------------------------------------------------
    void DEList::notifyListChangeScroll( MyGUI::ListBox* p, U32 _index )
    {
        assert(p);
        mpEGList = p;
        setEGWidget(p);
        (mMapListChangeScroll[mpEGList])(this, _index);
    }
    //-----------------------------------------------------------------------------------
    MG::Str16 DEList::getItemNameAt( U32 _index )
    {
        assert(mpEGList);
        return mpEGList->getItemNameAt( _index );
    }
    //-----------------------------------------------------------------------------------
    IAny* DEList::getItemDataAt( U32 _index )
    {
        assert(mpEGList);
        return mpEGList->getItemDataAt<IAny>(_index);
    }
    //-----------------------------------------------------------------------------------
    void DEList::setItemDataAt( size_t _index, IAny _data )
    {
        assert(mpEGList);

        mpEGList->setItemDataAt(_index, _data);
    }
    //-----------------------------------------------------------------------------------
    void DEList::clearItemDataAt( size_t _index )
    {
        assert(mpEGList);

        mpEGList->clearItemDataAt(_index);
    }
    //-----------------------------------------------------------------------------------
    int DEList::getOptimalHeight()
    {
        assert(mpEGList);

        return mpEGList->getOptimalHeight();
    }
    //-----------------------------------------------------------------------------------
    void DEList::setScrollVisible( bool _visible )
    {
        assert(mpEGList);

        mpEGList->setScrollVisible(_visible);
    }
}
