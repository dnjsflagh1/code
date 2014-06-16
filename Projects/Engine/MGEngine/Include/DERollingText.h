//**********************************************************************************************************
#ifndef _H_DEROLLINGTEXT_
#define _H_DEROLLINGTEXT_
//**********************************************************************************************************
#include "IRollingText.h"
#include "DEWidget.h"
//**********************************************************************************************************
namespace MG
{
    class DERollingText : public IRollingText, public DEWidget
    {
    public:
        DERollingText();
        virtual ~DERollingText();

    public:
        virtual IWidget*    getWidget();
        virtual void        addMsg(Str16 msg, U32 rollingTime, Byte priority);

    public: //事件
        //当所有信息都滚动完毕。
        virtual void        setEventRollingTextNone(PVOID_CALLBACK pFunc);

    public:
        //引擎事件
        Bool                setEGRollingText(MyGUI::Widget* p);
        MyGUI::Widget*      getEGRollingText(){return mpEGRollingText;}

    protected:
        //引擎事件
        void                notifyRollingTextNone( MyGUI::RollingText* p );

    protected:
        //记录引擎对象和对应的回调函数，当引擎的回调响应时可找到client的回调函数
        static std::map<MyGUI::RollingText*, PVOID_CALLBACK>                    mMapRollingTextNone;

    private:
        //引擎对象指针
        MyGUI::RollingText*                     mpEGRollingText;

    };
}
//**********************************************************************************************************
#endif
//**********************************************************************************************************