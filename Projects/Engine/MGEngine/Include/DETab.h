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

    public://�¼�
        virtual void            setEventTabChangeSelect(PVOIDINT_CALLBACK);

    public:
        //�����¼�
        Bool                    setEGTab(MyGUI::Widget* p);
        MyGUI::Widget*          getEGTab(){return mpEGTab;}

    protected:
        //�����¼�
        void                    notifyTabChangeSelect(MyGUI::Tab* p, U32 Index);

    protected:
        //��¼�������Ͷ�Ӧ�Ļص�������������Ļص���Ӧʱ���ҵ�client�Ļص�����
        static std::map<MyGUI::Tab*, PVOIDINT_CALLBACK>                 mMapTabChangeSelect;

    private:
        //�������ָ��
        MyGUI::Tab*                                              mpEGTab;

    };
}
//**********************************************************************************************************
#endif
//**********************************************************************************************************