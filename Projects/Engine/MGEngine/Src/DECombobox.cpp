//**********************************************************************************************************
#include "stdafx.h"
#include "DECombobox.h"
//**********************************************************************************************************
//**********************************************************************************************************
namespace MG
{ 
    std::map<MyGUI::ComboBox*, PVOIDINT_CALLBACK>                   DEComboBox::mMapComboAcceptCallBack;
    std::map<MyGUI::ComboBox*, PVOIDINT_CALLBACK>                   DEComboBox::mMapComboChangePositionCallBack;

    DEComboBox::DEComboBox()
        :mpEGComboBox(nullptr)
    {

    }
    //-----------------------------------------------------------------------------
    DEComboBox::~DEComboBox()
    {

    }

    IWidget* DEComboBox::getWidget()
    {
        assert(mpEGComboBox);
        return this;
    }

    void DEComboBox::setEditStatic( bool _value )
    {
        assert(mpEGComboBox);
        mpEGComboBox->setEditStatic(_value);
    }

    bool DEComboBox::getEditStatic()
    {
        assert(mpEGComboBox);
        return mpEGComboBox->getEditStatic();
    }

    size_t DEComboBox::getItemCount()
    {
         assert(mpEGComboBox);
         return mpEGComboBox->getItemCount();
    }

    void DEComboBox::insertItemAt( size_t _index, const std::wstring _name, IAny _data )
    {
         assert(mpEGComboBox);
         mpEGComboBox->insertItemAt(_index, _name, _data);
    }

    void DEComboBox::addItem( const std::wstring _name, IAny _data )
    {
         assert(mpEGComboBox);
         mpEGComboBox->addItem( _name, _data );
    }

    void DEComboBox::removeItemAt( size_t _index )
    {
         assert(mpEGComboBox);
         mpEGComboBox->removeItemAt( _index );
    }

    void DEComboBox::removeAllItems()
    {
         assert(mpEGComboBox);
         mpEGComboBox->removeAllItems();
    }

    size_t DEComboBox::findItemIndexWith( const std::wstring _name )
    {
         assert(mpEGComboBox);
         return mpEGComboBox->findItemIndexWith( _name );
    }

    size_t DEComboBox::getIndexSelected()
    {
         assert(mpEGComboBox);
         return mpEGComboBox->getIndexSelected();
    }

    void DEComboBox::setIndexSelected( size_t _index )
    {
         assert(mpEGComboBox);
         mpEGComboBox->setIndexSelected( _index );
    }

    void DEComboBox::clearIndexSelected()
    {
         assert(mpEGComboBox);
         mpEGComboBox->clearIndexSelected();
    }

    void DEComboBox::setItemNameAt( size_t _index, const std::wstring& _name )
    {
         assert(mpEGComboBox);
         mpEGComboBox->setItemNameAt( _index, _name );
    }

    const std::wstring& DEComboBox::getItemNameAt( size_t _index )
    {
         assert(mpEGComboBox);
         return mpEGComboBox->getItemNameAt( _index ).asWStr();
    }

    void DEComboBox::setComboAcceptEvent( PVOIDINT_CALLBACK func )
    {
         assert(mpEGComboBox);
         mMapComboAcceptCallBack[mpEGComboBox] = func;
         mpEGComboBox->eventComboAccept = MyGUI::newDelegate(this, &DEComboBox::notifyComboAccept);
    }

    void DEComboBox::setComboChangePositionEvent( PVOIDINT_CALLBACK func )
    {
        assert(mpEGComboBox);
        mMapComboChangePositionCallBack[mpEGComboBox] = func;
        mpEGComboBox->eventComboChangePosition = MyGUI::newDelegate(this, &DEComboBox::notifyComboChangePosition);
    }

    Bool DEComboBox::setEGComboBox( MyGUI::Widget* p )
    {
        assert(p);
        mpEGComboBox = p->castType<MyGUI::ComboBox>();
        assert(mpEGComboBox);
        setEGWidget(p);
        return true;
    }

    void DEComboBox::notifyComboAccept( MyGUI::ComboBox* p, size_t Index )
    {
        assert(p);
        mpEGComboBox = p;
        setEGWidget(p);
        (mMapComboAcceptCallBack[mpEGComboBox])(this, Index);
    }

    void DEComboBox::notifyComboChangePosition( MyGUI::ComboBox* p, size_t Index )
    {
        assert(p);
        mpEGComboBox = p;
        setEGWidget(p);
        (mMapComboChangePositionCallBack[mpEGComboBox])(this, Index);
    }

    void DEComboBox::setItemDataAt( size_t _index, IAny _data )
    {
        assert(mpEGComboBox); 

        mpEGComboBox->setItemDataAt(_index, _data);
    }

    void DEComboBox::clearItemDataAt( size_t _index )
    {
        assert(mpEGComboBox);

        mpEGComboBox->clearItemDataAt(_index);
    }

    IAny * DEComboBox::getItemDataAt( size_t _index )
    {
        assert(mpEGComboBox);

        return mpEGComboBox->getItemDataAt<IAny>(_index, true);
    }
}