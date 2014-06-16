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
        //�����¼�
                Bool            setEGForm(MyGUI::Widget* p);
                MyGUI::Widget*  getEGForm(){return mpEGForm;}

    protected:
        //�����¼�
                void            notifyWindowButtonPressed(MyGUI::Window* p, const std::string& name);
                void            notifyWindowChangeCoord(MyGUI::Window* p);

    protected:
        //��¼�������Ͷ�Ӧ�Ļص�������������Ļص���Ӧʱ���ҵ�client�Ļص�����
        static std::map<MyGUI::Window*, PVOID_CALLBACK>             mMapWindowButtonPressedCallBack;
        static std::map<MyGUI::Window*, PVOID_CALLBACK>             mMapWindowChangeCoordCallBack;

    private:
        //�������ָ��
        MyGUI::Window*                                          mpEGForm;

    };
}
//**********************************************************************************************************
#endif
//**********************************************************************************************************