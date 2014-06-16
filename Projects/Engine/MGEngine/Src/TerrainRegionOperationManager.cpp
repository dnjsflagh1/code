/******************************************************************************/
#include "stdafx.h"
#include "TerrainRegionOperationManager.h"
#include "TerrainRegionOperation.h"
/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //TerrainAddBlockOperationManager
    /******************************************************************************/
    TerrainAddRegionOperationManager::TerrainAddRegionOperationManager()
    {

    }
    //-----------------------------------------------------------------------
    TerrainAddRegionOperationManager::~TerrainAddRegionOperationManager()
    {

    }
    //-----------------------------------------------------------------------
    IEditorOperation* TerrainAddRegionOperationManager::createOneOperation()
    {
        TerrainAddRegionOperation* op = MG_NEW TerrainAddRegionOperation();

        return op;
    }

    /******************************************************************************/
    //TerrainRemoveRegionOperationManager
    /******************************************************************************/
    TerrainRemoveRegionOperationManager::TerrainRemoveRegionOperationManager()
    {

    }
    //-----------------------------------------------------------------------
    TerrainRemoveRegionOperationManager::~TerrainRemoveRegionOperationManager()
    {

    }
    //-----------------------------------------------------------------------
    IEditorOperation* TerrainRemoveRegionOperationManager::createOneOperation()
    {
        TerrainRemoveRegionOperation* op = MG_NEW TerrainRemoveRegionOperation();

        return op;
    }

   
}


