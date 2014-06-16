//**********************************************************************************************************
#ifndef _H_DEPROGRESS_675843975974_
#define _H_DEPROGRESS_675843975974_
//**********************************************************************************************************
#include "IProgress.h"
#include "DEWidget.h"
//**********************************************************************************************************
class  MyGUI::Widget;
class  MyGUI::ProgressEx;
//**********************************************************************************************************
namespace MG
{
    class DEProgress : public IProgress, public DEWidget  
    {
    public:
                                        DEProgress();
        virtual                         ~DEProgress();
    public:
        virtual IWidget*                getWidget();
        virtual void                    setProgressPosition(Flt _value);
        virtual Flt                     getProgressPosition();
        virtual void                    setTopTexture(const Str8 resName, const Str8 groupName, const Str8 itemName);
        virtual void                    setBottomTexture(const Str8 resName, const Str8 groupName, const Str8 itemName);
        virtual void                    setTexture(const Str8 resName, const Str8 groupName, const Str8 itemName);
    public:
        //引擎事件
                Bool                    setEGProgress(MyGUI::Widget* p);
                MyGUI::ProgressEx*      getEGProgress(){return mpEGProgress;}
    private:
        //引擎对象指针
        MyGUI::ProgressEx* mpEGProgress;
    };
}
//**********************************************************************************************************
#endif
//**********************************************************************************************************