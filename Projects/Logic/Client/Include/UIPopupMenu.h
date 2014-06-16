//***********************************************************************************************************
#ifndef _H_UIPOPUPMENU_
#define _H_UIPOPUPMENU_
//***********************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//***********************************************************************************************************
namespace MG
{
    class UIPopupMenu : public UIObject
    {
    public:
        UIPopupMenu();
        ~UIPopupMenu();
        SINGLETON_INSTANCE(UIPopupMenu);

    public:
        virtual void    setEvent();
        virtual Bool    openGui();
        virtual Bool    closeGui();
        virtual void    update(Flt delta);

    private:
        static  void    onClickItem(void* widget);
        static  void    notifyKeyLostFocusEvent(void* widget, void* newWidget);
        static  void    notifyMouseSetFocusEvent(void* widget, void* newWidget);

    public://外部接口
        void            addItem(Str16 caption, UInt id);
        void            setSelectEvent(PopupMenuFunc func);
   
    private:
        void            handlEvent(UInt id);
        void            setHighLight(void* widget);

    private:
        PopupMenuFunc   mPopupMenuFunc;
        U32             mStartTime;
        U32             mSpaceTime;
        U32             mCurItemCount;

    };
       
}
//***********************************************************************************************************
#endif
//***********************************************************************************************************