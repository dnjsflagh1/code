//*************************************************************************************
#ifndef _h_Test_PopupMenu_
#define _h_Test_PopupMenu_
//*************************************************************************************
#include "UIObject.h"
//*************************************************************************************
namespace MG
{
    class  UITestPopupMenu : public UIObject
    {
    public:
        UITestPopupMenu(){}
        virtual ~UITestPopupMenu(){;}
        SINGLETON_INSTANCE(UITestPopupMenu);
    public:
        virtual void setEvent();
        void            addMsg(Str16 msg, U32 showTime, Byte priority);

    private:
        static void onClickButton(void* widget);

    private:
        void        handEvent(Int id);
    };

    class  UITestRollingText : public UIObject
    {
    public:
        UITestRollingText(){}
        virtual ~UITestRollingText(){;}
        SINGLETON_INSTANCE(UITestRollingText);
    public:
        virtual void    setEvent();

    private:
        static void     onRollingTextNone(void* widget); 

    public:
        void            addMsg(Str16 msg, U32 showTime, Byte priority);

    };
}
//*************************************************************************************
#endif
//*************************************************************************************