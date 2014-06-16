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
    //��Ϸˮ��ʾ
    /******************************************************************************/
    class ITerrainWaterShowOperationManager : public IEditorOperationManager
    {
    public:
        ///�õ�ˮ����
        virtual U32     getWaterGroupID() = NULL;
        ///����ˮ����
        virtual void    setWaterGroupID(U32 id) = NULL;
    };
    
    /******************************************************************************/
    //��Ϸˮ����
    /******************************************************************************/
    class ITerrainWaterHideOperationManager: public IEditorOperationManager
    {
    public:
    };

}

/******************************************************************************/
#endif
