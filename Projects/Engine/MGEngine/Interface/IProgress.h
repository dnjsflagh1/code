//**********************************************************************************************************
#ifndef _H_IPROGRESS_758234954_
#define _H_IPROGRESS_758234954_
//**********************************************************************************************************
#include "MGEngineInterfacePreqs.h"
#include "IWidget.h"
//**********************************************************************************************************
//�������ӿ�
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
        //���ö�ͼ
        virtual void        setTopTexture(const Str8 resName, const Str8 groupName, const Str8 itemName) = 0;
        //���õ�ͼ
        virtual void        setBottomTexture(const Str8 resName, const Str8 groupName, const Str8 itemName) = 0;
        //���ý�����ͼ��
        virtual void        setTexture(const Str8 resName, const Str8 groupName, const Str8 itemName) = 0;

    
    };
}

//**********************************************************************************************************
#endif
//**********************************************************************************************************