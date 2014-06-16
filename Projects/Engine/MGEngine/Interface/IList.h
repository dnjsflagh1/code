//**********************************************************************************************************
#ifndef _H_LIST_
#define _H_LIST_
//**********************************************************************************************************
#include "MGEngineInterfacePreqs.h"
#include "IWidget.h"
#include "IAny.h"
//**********************************************************************************************************
//竖型列表接口
namespace MG
{
    class IList
    {
    public:
        virtual IWidget*    getWidget() = 0;

    public:
        //! Get number of items
        virtual  U32 getItemCount() = 0;

        //! Insert an item into a array at a specified position
        virtual  void insertItemAt(U32 _index, const Str16& _name, IAny _data = NULL) = 0;

        //! Add an item to the end of a array
        virtual  UInt addItem(const Str16& _name, IAny _data = NULL) = 0;

        //! Remove item at a specified position
        virtual  void removeItemAt(U32 _index) = 0;

        //! Remove all items
        virtual  void removeAllItems() = 0;

        //! Swap items at a specified positions
        virtual  void swapItemsAt(U32 _index1, U32 _index2) = 0;


        //! Search item, returns the position of the first occurrence in array or ITEM_NONE if item not found
        virtual  U32 findItemIndexWith(const Str16& _name) = 0;


        /** Get index of selected item (ITEM_NONE if none selected) */
        virtual  U32 getIndexSelected()  = 0;

        /** Select specified _index */
        virtual  void setIndexSelected(U32 _index) = 0;

        /** Clear item selection */
        virtual  void clearIndexSelected()  = 0;

        //! Get item name from specified position
        virtual  Str16 getItemNameAt(U32 _index) = 0;

        //! Get item data from specified position
        virtual  IAny* getItemDataAt( U32 _index ) = 0;

        //! Replace an item data at a specified position
        virtual  void setItemDataAt(size_t _index, IAny _data) = 0;

        //! Clear an item data at a specified position
        virtual  void clearItemDataAt(size_t _index) = 0;

        //! Return optimal height to fit all items in List
        virtual  int getOptimalHeight() = 0;

        //! Set scroll visible when it needed
        virtual  void setScrollVisible(bool _visible) = 0;

    public://事件
        /*event:*/
        /** Event : Enter pressed or double click.\n
        signature : void method(MyGUI::List* _sender, size_t _index)\n
        @param _sender widget that called this event
        @param _index of selected item
        */
        virtual  void setEventListSelectAccept(PVOIDINT_CALLBACK) = 0;

        /** Event : Selected item position changed.\n
        signature : void method(MyGUI::List* _sender, size_t _index)\n
        @param _sender widget that called this event
        @param _index of new item
        */
        virtual  void setEeventListChangePosition(PVOIDINT_CALLBACK) = 0;

        /** Event : Item was selected by mouse.\n
        signature : void method(MyGUI::List* _sender, size_t _index)\n
        @param _sender widget that called this event
        @param _index of selected item
        */
        virtual  void setEventListMouseItemActivate(PVOIDINT_CALLBACK) = 0;

        /** Event : Mouse is over item.\n
        signature : void method(MyGUI::List* _sender, size_t _index)\n
        @param _sender widget that called this event
        @param _index of focused item
        */
        virtual  void setEventListMouseItemFocus(PVOIDINT_CALLBACK) = 0;

        /** Event : Position of scroll changed.\n
        signature : void method(MyGUI::List* _sender, size_t _position)\n
        @param _sender widget that called this event
        @param _position of scroll
        */
        virtual  void setEventListChangeScroll(PVOIDINT_CALLBACK) = 0;

    protected:
    private:
    };
}

//**********************************************************************************************************
#endif
//**********************************************************************************************************