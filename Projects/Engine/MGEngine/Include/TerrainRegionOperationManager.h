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
    //��Ϸ���������ϰ��ӿ�
    /******************************************************************************/
    class TerrainAddRegionOperationManager : public ITerrainAddRegionOperationManager
    {
    public:
        SINGLETON_INSTANCE(TerrainAddRegionOperationManager)
        TerrainAddRegionOperationManager();
        virtual ~TerrainAddRegionOperationManager();

        ///����һ������
        virtual IEditorOperation*       createOneOperation();

    protected:
    };

    /******************************************************************************/
    //��Ϸ�����Ƴ��ϰ��ӿ�
    /******************************************************************************/
    class TerrainRemoveRegionOperationManager : public ITerrainRemoveRegionOperationManager
    {
    public:
        SINGLETON_INSTANCE(TerrainRemoveRegionOperationManager)
        TerrainRemoveRegionOperationManager();
        virtual ~TerrainRemoveRegionOperationManager();

        ///����һ������
        virtual IEditorOperation*       createOneOperation( );

    protected:

    };

    
}

/******************************************************************************/

#endif

