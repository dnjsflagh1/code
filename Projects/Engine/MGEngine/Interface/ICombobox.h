//**********************************************************************************************************
#ifndef _H_ICOMBOBOX_758439875043_
#define _H_ICOMBOBOX_758439875043_
//**********************************************************************************************************
#include "MGEngineInterfacePreqs.h"
#include "IWidget.h"
//**********************************************************************************************************
//按钮接口
namespace MG
{
    class IComboBox
    {
    public:
        virtual IWidget*                getWidget() = 0;  
        //设置为静态模式，相当于Text，但是可以多行显示。
        virtual void                    setEditStatic(bool _value) = 0;
        //获得是否为静态模式。
        virtual bool                    getEditStatic() = 0;
        //! Get number of items
        virtual size_t                  getItemCount() = 0;
        //! Insert an item into a array at a specified position
        virtual void                    insertItemAt(size_t _index, const std::wstring _name, IAny _data = NULL) = 0;
        //! Add an item to the end of a array
        virtual void                    addItem(const std::wstring _name, IAny _data = NULL) = 0;
        //! Remove item at a specified position
        virtual void                    removeItemAt(size_t _index) = 0;
        //! Remove all items
        virtual void                    removeAllItems() = 0;
        //! Search item, returns the position of the first occurrence in array or ITEM_NONE if item not found
        virtual size_t                  findItemIndexWith(const std::wstring _name) = 0;
        //! Get index of selected item (ITEM_NONE if none selected)
        virtual size_t                  getIndexSelected() = 0;
        //! Select specified _index
        virtual void                    setIndexSelected(size_t _index) = 0;
        //! Clear item selection
        virtual void                    clearIndexSelected() = 0;
        //! RePlaceEntity an item name at a specified position
        virtual void                    setItemNameAt(size_t _index, const std::wstring & _name) = 0;
        //! Get item name from specified position
        virtual const std::wstring &    getItemNameAt(size_t _index) = 0;
        //! Replace an item data at a specified position
        virtual void                    setItemDataAt(size_t _index, IAny _data) = 0;
        //! Clear an item data at a specified position
        virtual void                    clearItemDataAt(size_t _index) = 0;
        //! Get item data from specified position
        virtual IAny *                  getItemDataAt(size_t _index) = 0;
    public://事件
        virtual void                    setComboAcceptEvent(PVOIDINT_CALLBACK func) = 0;

        virtual void                    setComboChangePositionEvent(PVOIDINT_CALLBACK func) = 0;
    };
}
//**********************************************************************************************************
#endif
//**********************************************************************************************************