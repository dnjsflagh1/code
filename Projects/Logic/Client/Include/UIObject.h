//*************************************************************************************
#ifndef _UIOBJECT_H_584jf_
#define _UIOBJECT_H_584jf_
//*************************************************************************************
#include "UICommon.h"
//*************************************************************************************
namespace MG
{
    class  UIObject
    {
    public:
        UIObject();
        virtual ~UIObject();
                  bool       initialize(const Str& filename, int level = 0);
                  bool       unInitialize();

    public:
        virtual    bool       loadLayout(Str fileName);
        virtual    void       setEvent(){}
        virtual    bool       isOpen();
        virtual    bool       openGui();
        virtual    bool       closeGui(Bool isForceClose = false);
        virtual    void       update(Flt delta){;}
        virtual    void       restore(){;}
    public:
                  ILayout*    getLayout(){ return mLayout; }

    protected:
        Str mLayoutName;
        //bool mbisOpen;
        ILayout* mLayout;
    };
}

#endif