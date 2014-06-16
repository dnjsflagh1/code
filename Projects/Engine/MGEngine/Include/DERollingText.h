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

    public: //�¼�
        //��������Ϣ��������ϡ�
        virtual void        setEventRollingTextNone(PVOID_CALLBACK pFunc);

    public:
        //�����¼�
        Bool                setEGRollingText(MyGUI::Widget* p);
        MyGUI::Widget*      getEGRollingText(){return mpEGRollingText;}

    protected:
        //�����¼�
        void                notifyRollingTextNone( MyGUI::RollingText* p );

    protected:
        //��¼�������Ͷ�Ӧ�Ļص�������������Ļص���Ӧʱ���ҵ�client�Ļص�����
        static std::map<MyGUI::RollingText*, PVOID_CALLBACK>                    mMapRollingTextNone;

    private:
        //�������ָ��
        MyGUI::RollingText*                     mpEGRollingText;

    };
}
//**********************************************************************************************************
#endif
//**********************************************************************************************************