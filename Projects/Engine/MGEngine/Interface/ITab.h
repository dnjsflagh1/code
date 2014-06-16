//**********************************************************************************************************
#ifndef _H_TAB_
#define _H_TAB_
//**********************************************************************************************************
#include "MGEngineInterfacePreqs.h"
#include "IWidget.h"
//**********************************************************************************************************
//��ǩ�ӿ�
namespace MG
{
    class ITab
    {
    public:
        virtual IWidget*    getWidget() = 0;
        
    public://�¼�
        /** Event : Active Tab sheet changed \n
        signature : void method(MyGUI::Tab* _sender, size_t _index)\n
        @param _sender widget that called this event
        @param _index Index of selected sheet
        */
        virtual void setEventTabChangeSelect(PVOIDINT_CALLBACK) = 0;

    protected:
    private:
    };
}

//**********************************************************************************************************
#endif
//**********************************************************************************************************