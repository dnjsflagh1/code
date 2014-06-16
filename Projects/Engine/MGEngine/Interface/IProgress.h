//**********************************************************************************************************
#ifndef _H_IPROGRESS_758234954_
#define _H_IPROGRESS_758234954_
//**********************************************************************************************************
#include "MGEngineInterfacePreqs.h"
#include "IWidget.h"
//**********************************************************************************************************
//进度条接口
namespace MG
{
    class IProgress
    {
    public:
        virtual IWidget*    getWidget() = 0;
        /** Set progress position */
        virtual void        setProgressPosition(Flt _value) = 0;
        /** Get progress position */
        virtual Flt         getProgressPosition() = 0;
        //设置顶图
        virtual void        setTopTexture(const Str8 resName, const Str8 groupName, const Str8 itemName) = 0;
        //设置底图
        virtual void        setBottomTexture(const Str8 resName, const Str8 groupName, const Str8 itemName) = 0;
        //设置进度条图。
        virtual void        setTexture(const Str8 resName, const Str8 groupName, const Str8 itemName) = 0;

    
    };
}

//**********************************************************************************************************
#endif
//**********************************************************************************************************