/******************************************************************************/
#ifndef _ITERRAINWATEROPERATIONMANAGER_H_
#define _ITERRAINWATEROPERATIONMANAGER_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"
#include "IEditorOperation.h"
#include "ITerrain.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //游戏水显示
    /******************************************************************************/
    class ITerrainWaterShowOperationManager : public IEditorOperationManager
    {
    public:
        ///得到水组编号
        virtual U32     getWaterGroupID() = NULL;
        ///设置水组编号
        virtual void    setWaterGroupID(U32 id) = NULL;
    };
    
    /******************************************************************************/
    //游戏水隐藏
    /******************************************************************************/
    class ITerrainWaterHideOperationManager: public IEditorOperationManager
    {
    public:
    };

}

/******************************************************************************/
#endif
