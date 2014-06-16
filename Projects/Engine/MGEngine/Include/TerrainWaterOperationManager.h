/******************************************************************************/
#ifndef _TERRAINWATEROPERATIONMANAGER_H_
#define _TERRAINWATEROPERATIONMANAGER_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "ITerrainWaterOperationManager.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    //游戏水显示
    /******************************************************************************/
    class TerrainWaterShowOperationManager : public ITerrainWaterShowOperationManager
    {
    public:
        SINGLETON_INSTANCE(TerrainWaterShowOperationManager)
        TerrainWaterShowOperationManager();
        virtual ~TerrainWaterShowOperationManager();

        ///得到水组编号
        virtual U32     getWaterGroupID();
        ///设置水组编号
        virtual void    setWaterGroupID(U32 id) ;

        ///创建一个操作
        virtual IEditorOperation*       createOneOperation();

    protected:

        U32 mGroupID;

    };

    /******************************************************************************/
    //游戏水隐藏
    /******************************************************************************/
    class TerrainWaterHideOperationManager : public ITerrainWaterHideOperationManager
    {
    public:
        SINGLETON_INSTANCE(TerrainWaterHideOperationManager)
        TerrainWaterHideOperationManager();
        virtual ~TerrainWaterHideOperationManager();

        ///创建一个操作
        virtual IEditorOperation*       createOneOperation();

    protected:

    };

    
}

/******************************************************************************/

#endif

