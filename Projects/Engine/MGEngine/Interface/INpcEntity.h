/******************************************************************************/
#ifndef _INpcEntity_H_
#define _INpcEntity_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"
#include "IEntity.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //��ϷNpcEntity�ӿ�
    /******************************************************************************/
    class INpcEntity : public IEntity
    {
    public:

        ///�õ�ģ����
        virtual const Int           getTemplateID(){return mTemplateID;};
        ///����ģ����
        virtual void                setTemplateID( Int id ){mTemplateID=id;};
        
        ///�õ����ܱ��
        virtual const Int           getFunctionID(){return mFunctionID;};
        ///���ù��ܱ��
        virtual void                setFunctionID( Int id ){mFunctionID=id;};
        
    protected:

        Int mTemplateID;
        Int mFunctionID;
    };

}

/******************************************************************************/
#endif
