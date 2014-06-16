/******************************************************************************/
#ifndef _TERRAINREGIONOPERATIONMANAGER_H_
#define _TERRAINREGIONOPERATIONMANAGER_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "ITerrainRegionOperationManager.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    //游戏地形增加障碍接口
    /******************************************************************************/
    class TerrainAddRegionOperationManager : public ITerrainAddRegionOperationManager
    {
    public:
        SINGLETON_INSTANCE(TerrainAddRegionOperationManager)
        TerrainAddRegionOperationManager();
        virtual ~TerrainAddRegionOperationManager();

        ///创建一个操作
        virtual IEditorOperation*       createOneOperation();

    protected:
    };

    /******************************************************************************/
    //游戏地形移除障碍接口
    /******************************************************************************/
    class TerrainRemoveRegionOperationManager : public ITerrainRemoveRegionOperationManager
    {
    public:
        SINGLETON_INSTANCE(TerrainRemoveRegionOperationManager)
        TerrainRemoveRegionOperationManager();
        virtual ~TerrainRemoveRegionOperationManager();

        ///创建一个操作
        virtual IEditorOperation*       createOneOperation( );

    protected:

    };

    
}

/******************************************************************************/

#endif

