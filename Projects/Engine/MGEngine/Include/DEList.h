//**********************************************************************************************************
#ifndef _H_DELIST_
#define _H_DELIST_
//**********************************************************************************************************
#include "IList.h"
#include "DEWidget.h"
//**********************************************************************************************************
class MyGUI::Widget;
//**********************************************************************************************************
namespace MG
{
    class DEList : public IList, public DEWidget
    {
    public:
        DEList();
        virtual ~DEList();

    public:
        virtual IWidget*    getWidget();

    public:
        virtual  U32    getItemCount();
        virtual  void   insertItemAt(U32 _index, const Str16& _name, IAny _data = NULL);
        virtual  UInt   addItem(const Str16& _name, IAny _data = NULL);
        virtual  void   removeItemAt(U32 _index);
        virtual  void   removeAllItems();
        virtual  void   swapItemsAt(U32 _index1, U32 _index2);
        virtual  U32    findItemIndexWith(const Str16& _name);
        virtual  U32    getIndexSelected();
        virtual  void   setIndexSelected(U32 _index);
        virtual  void   clearIndexSelected();
        virtual  Str16  getItemNameAt(U32 _index);
        virtual  IAny*  getItemDataAt( U32 _index );
        virtual  void   setItemDataAt(size_t _index, IAny _data);
        virtual  void   clearItemDataAt(size_t _index);
        virtual  int    getOptimalHeight();
        virtual  void   setScrollVisible(bool _visible);

    public://事件
        virtual  void setEventListSelectAccept(PVOIDINT_CALLBACK pFunc);
        virtual  void setEeventListChangePosition(PVOIDINT_CALLBACK pFunc);
        virtual  void setEventListMouseItemActivate(PVOIDINT_CALLBACK pFunc);
        virtual  void setEventListMouseItemFocus(PVOIDINT_CALLBACK pFunc);
        virtual  void setEventListChangeScroll(PVOIDINT_CALLBACK pFunc);

    public:
        //引擎事件
        Bool            setEGList(MyGUI::Widget* p);
        MyGUI::Widget*  getEGList(){return mpEGList;}

    protected:
        //引擎事件
        void notifyListSelectAccept(MyGUI::ListBox* p, U32 _index);
        void notifyListChangePosition(MyGUI::ListBox* p, U32 _index);
        void notifyListMouseItemActivate(MyGUI::ListBox* p, U32 _index);
        void notifyListMouseItemFocus(MyGUI::ListBox* p, U32 _index);
        void notifyListChangeScroll(MyGUI::ListBox* p, U32 _index);

    protected:
        //记录引擎对象和对应的回调函数，当引擎的回调响应时可找到client的回调函数
        static std::map<MyGUI::ListBox*, PVOIDINT_CALLBACK> mMapListSelectAccept;
        static std::map<MyGUI::ListBox*, PVOIDINT_CALLBACK> mMapListChangePosition;
        static std::map<MyGUI::ListBox*, PVOIDINT_CALLBACK> mMapListMouseItemActivate;
        static std::map<MyGUI::ListBox*, PVOIDINT_CALLBACK> mMapListMouseItemFocus;
        static std::map<MyGUI::ListBox*, PVOIDINT_CALLBACK> mMapListChangeScroll;

    private:
        //引擎对象指针
        MyGUI::ListBox* mpEGList;
    };
}

//**********************************************************************************************************
#endif
//**********************************************************************************************************