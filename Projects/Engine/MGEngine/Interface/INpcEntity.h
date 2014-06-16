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
    //游戏NpcEntity接口
    /******************************************************************************/
    class INpcEntity : public IEntity
    {
    public:

        ///得到模板编号
        virtual const Int           getTemplateID(){return mTemplateID;};
        ///设置模板编号
        virtual void                setTemplateID( Int id ){mTemplateID=id;};
        
        ///得到功能编号
        virtual const Int           getFunctionID(){return mFunctionID;};
        ///设置功能编号
        virtual void                setFunctionID( Int id ){mFunctionID=id;};
        
    protected:

        Int mTemplateID;
        Int mFunctionID;
    };

}

/******************************************************************************/
#endif
