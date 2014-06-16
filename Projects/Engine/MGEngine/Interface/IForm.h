//**********************************************************************************************************
#ifndef _H_IFORM_7584392759_
#define _H_IFORM_7584392759_
//**********************************************************************************************************
#include "MGEngineInterfacePreqs.h"
#include "IWidget.h"
//**********************************************************************************************************
//窗口接口
namespace MG
{
    class IForm
    {
    public:
        virtual IWidget* getWidget() = 0;
		virtual void setItemTexture(const Str8& _resource, const Str8& _group, const Str8& _name) = 0;
        virtual void setImageCoord(const CoordI& _coord) = 0;
        virtual void setImageSize(const VecI2& _size) = 0;
        virtual void setImagePosition(const VecI2& _point) = 0;

    public://事件
        virtual void     setWindowButtonPressedEvent(PVOID_CALLBACK) = 0;
        virtual void     setWindowChangeCoordEvent(PVOID_CALLBACK) = 0;
    protected:
    private:
    };
}

//**********************************************************************************************************
#endif
//**********************************************************************************************************