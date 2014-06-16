//**********************************************************************************************************
#ifndef _H_DEComboBox_57589342087539_
#define _H_DEComboBox_57589342087539_
//**********************************************************************************************************
#include "ICombobox.h"
#include "DEWidget.h"
//**********************************************************************************************************
class  MyGUI::Widget;
class  MyGUI::ComboBox;
//**********************************************************************************************************
namespace MG
{
    class DEComboBox : public IComboBox, public DEWidget  
    {
    public:
                                        DEComboBox();
        virtual                         ~DEComboBox();

    public:
        virtual IWidget*                getWidget();  
        virtual void                    setEditStatic(bool _value);
        virtual bool                    getEditStatic();
        virtual size_t                  getItemCount();
        virtual void                    insertItemAt(size_t _index, const std::wstring _name, IAny _data = NULL);
        virtual void                    addItem(const std::wstring _name, IAny _data = NULL);
        virtual void                    removeItemAt(size_t _index);
        virtual void                    removeAllItems();
        virtual size_t                  findItemIndexWith(const std::wstring _name);
        virtual size_t                  getIndexSelected();
        virtual void                    setIndexSelected(size_t _index);
        virtual void                    clearIndexSelected();
        virtual void                    setItemNameAt(size_t _index, const std::wstring& _name);
        virtual const std::wstring&     getItemNameAt(size_t _index);
        virtual void                    setItemDataAt(size_t _index, IAny _data);
        virtual void                    clearItemDataAt(size_t _index);
        virtual IAny *                  getItemDataAt(size_t _index);
    public://事件
        virtual void                    setComboAcceptEvent(PVOIDINT_CALLBACK func);
        virtual void                    setComboChangePositionEvent(PVOIDINT_CALLBACK func);

    public: 
        //引擎事件
                Bool                    setEGComboBox(MyGUI::Widget* p);
                MyGUI::Widget*          getEGComboBox(){return mpEGComboBox;}

    protected:
        //引擎事件
                void                    notifyComboAccept(MyGUI::ComboBox* p, size_t Index);
                void                    notifyComboChangePosition(MyGUI::ComboBox* p, size_t Index);

    protected:
        //记录引擎对象和对应的回调函数，当引擎的回调响应时可找到client的回调函数
        static std::map<MyGUI::ComboBox*, PVOIDINT_CALLBACK>                   mMapComboAcceptCallBack;
        static std::map<MyGUI::ComboBox*, PVOIDINT_CALLBACK>                   mMapComboChangePositionCallBack;

    private:
        //引擎对象指针
        MyGUI::ComboBox*                                                mpEGComboBox;
    };
}
//**********************************************************************************************************
#endif
//**********************************************************************************************************