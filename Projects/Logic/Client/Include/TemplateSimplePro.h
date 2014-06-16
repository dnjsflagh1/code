//*************************************************************************************
#ifndef _TemplateSIMPLEPRO_H_584jf_
#define _TemplateSIMPLEPRO_H_584jf_
//*************************************************************************************
#include "UIObject.h"
//*************************************************************************************
namespace MG
{
    class  TemplateSimplePro:public UIObject
    {
    public:
        TemplateSimplePro(){}
        virtual ~TemplateSimplePro(){;}
        SINGLETON_INSTANCE(TemplateSimplePro);
    public:
        virtual void setEvent();
    public:
        static void onMouseReleaseImagehead(void* widget, Int x, Int y, MouseCode mouseId);
        static void onTooltipsImagehead(void* widget, Bool isShow, Int x, Int y);
        static void onMouseClickImagehead(void* widget);
    protected:
        void setClick();
        void setHp();
        void setMp();
        void setLv();
        void setName();
    };
}

#endif