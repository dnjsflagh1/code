/******************************************************************************/
#include "stdafx.h"
#include "TerrainWaterOperationManager.h"
#include "TerrainWaterOperation.h"
/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //TerrainWaterShowOperationManager
    /******************************************************************************/
    TerrainWaterShowOperationManager::TerrainWaterShowOperationManager()
        :mGroupID(0)
    {

    }
    //-----------------------------------------------------------------------
    TerrainWaterShowOperationManager::~TerrainWaterShowOperationManager()
    {

    }

    //-----------------------------------------------------------------------
    U32 TerrainWaterShowOperationManager::getWaterGroupID()
    {
        return mGroupID;
    }

    //-----------------------------------------------------------------------
    void TerrainWaterShowOperationManager::setWaterGroupID(U32 id) 
    {
        mGroupID = id;
    }

    //-----------------------------------------------------------------------
    IEditorOperation* TerrainWaterShowOperationManager::createOneOperation()
    {
        TerrainWaterShowOperation* op = MG_NEW TerrainWaterShowOperation();

        return op;
    }

   
    /******************************************************************************/
    //TerrainWaterHideOperationManager
    /******************************************************************************/
    TerrainWaterHideOperationManager::TerrainWaterHideOperationManager()
    {

    }
    //-----------------------------------------------------------------------
    TerrainWaterHideOperationManager::~TerrainWaterHideOperationManager()
    {

    }

    //-----------------------------------------------------------------------
    IEditorOperation* TerrainWaterHideOperationManager::createOneOperation()
    {
        TerrainWaterHideOperation* op = MG_NEW TerrainWaterHideOperation();

        return op;
    }

}


