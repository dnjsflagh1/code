//**********************************************************************************************************
#ifndef _H_DETAB_
#define _H_DETAB_
//**********************************************************************************************************
#include "ITab.h"
#include "DEWidget.h"
//**********************************************************************************************************
class  MyGUI::Widget;
//**********************************************************************************************************
namespace MG
{
    class DETab : public ITab, public DEWidget  
    {
    public:
        DETab();
        virtual                 ~DETab();

    public:
        virtual IWidget*        getWidget();

    public://事件
        virtual void            setEventTabChangeSelect(PVOIDINT_CALLBACK);

    public:
        //引擎事件
        Bool                    setEGTab(MyGUI::Widget* p);
        MyGUI::Widget*          getEGTab(){return mpEGTab;}

    protected:
        //引擎事件
        void                    notifyTabChangeSelect(MyGUI::Tab* p, U32 Index);

    protected:
        //记录引擎对象和对应的回调函数，当引擎的回调响应时可找到client的回调函数
        static std::map<MyGUI::Tab*, PVOIDINT_CALLBACK>                 mMapTabChangeSelect;

    private:
        //引擎对象指针
        MyGUI::Tab*                                              mpEGTab;

    };
}
//**********************************************************************************************************
#endif
//**********************************************************************************************************