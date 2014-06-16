//**********************************************************************************************************
#ifndef _H_DEFORM_575894327439_
#define _H_DEFORM_575894327439_
//**********************************************************************************************************
#include "IForm.h"
#include "DEWidget.h"
//**********************************************************************************************************
class  MyGUI::Widget;
class  MyGUI::Window;
//**********************************************************************************************************
namespace MG
{
    class DEForm : public IForm, public DEWidget  
    {
    public:
                                DEForm();
        virtual                 ~DEForm();

    public:
        virtual IWidget*        getWidget();

    public:
		virtual void			setItemTexture(const Str8& _resource, const Str8& _group, const Str8& _name);
        virtual void            setImageCoord(const CoordI& _coord);
        virtual void            setImageSize(const VecI2& _size);
        virtual void            setImagePosition(const VecI2& _point);

    protected:
        virtual void            setWindowButtonPressedEvent(PVOID_CALLBACK);
        virtual void            setWindowChangeCoordEvent(PVOID_CALLBACK);

    public:
        //引擎事件
                Bool            setEGForm(MyGUI::Widget* p);
                MyGUI::Widget*  getEGForm(){return mpEGForm;}

    protected:
        //引擎事件
                void            notifyWindowButtonPressed(MyGUI::Window* p, const std::string& name);
                void            notifyWindowChangeCoord(MyGUI::Window* p);

    protected:
        //记录引擎对象和对应的回调函数，当引擎的回调响应时可找到client的回调函数
        static std::map<MyGUI::Window*, PVOID_CALLBACK>             mMapWindowButtonPressedCallBack;
        static std::map<MyGUI::Window*, PVOID_CALLBACK>             mMapWindowChangeCoordCallBack;

    private:
        //引擎对象指针
        MyGUI::Window*                                          mpEGForm;

    };
}
//**********************************************************************************************************
#endif
//**********************************************************************************************************