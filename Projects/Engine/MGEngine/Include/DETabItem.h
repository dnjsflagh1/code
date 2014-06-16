//**********************************************************************************************************
#ifndef _H_DETABITEM_
#define _H_DETABITEM_
//**********************************************************************************************************
#include "ITabItem.h"
#include "DEWidget.h"
//**********************************************************************************************************
class  MyGUI::Widget;
class  MyGUI::TabItem;
//**********************************************************************************************************
namespace MG
{
    class DETabItem : public ITabItem, public DEWidget  
    {
    public:
        DETabItem();
        virtual                 ~DETabItem();

    public:
        virtual IWidget*        getWidget();

    public:
        //引擎事件
        Bool            setEGTabItem(MyGUI::Widget* p);
        MyGUI::Widget*  getEGTabItem(){return mpEGTabItem;}

    private:
        //引擎对象指针
        MyGUI::TabItem*                                              mpEGTabItem;

    };
}
//**********************************************************************************************************
#endif
//**********************************************************************************************************