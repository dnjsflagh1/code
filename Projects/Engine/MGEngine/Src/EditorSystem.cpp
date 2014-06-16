/******************************************************************************/
#include "stdafx.h"
#include "EditorSystem.h"
#include "BrushSystem.h"
#include "TerrainHeightOperationManager.h"
#include "TerrainTextureOperationManager.h"
#include "TerrainTreeOperationManager.h"
#include "TerrainRegionOperationManager.h"
#include "TerrainWaterOperationManager.h"
/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------
    EditorSystem::EditorSystem()
        :mMaxOperationMemeryCount(10)
    {
    
    }

    //-----------------------------------------------------------------------
    EditorSystem::~EditorSystem()
    {
        clearOperationList();
    }

    //-----------------------------------------------------------------------
    void EditorSystem::push( IEditorOperation* op )
    {
        if ( mEditorOperationList.size() > mMaxOperationMemeryCount )
        {
            IEditorOperation* oldOp = mEditorOperationList.front();
            mEditorOperationList.pop_front();
            MG_SAFE_DELETE( oldOp );
        }

        op->execute();
        mEditorOperationList.push_back( op );
    }

    //-----------------------------------------------------------------------
    void EditorSystem::pop() 
    {
        if ( mEditorOperationList.size() > 0 )
        {
            IEditorOperation* oldOp = mEditorOperationList.back();
            mEditorOperationList.pop_back();
            oldOp->rollback();
            MG_SAFE_DELETE( oldOp );
        }
    }

    //-----------------------------------------------------------------------
    void EditorSystem::clearOperationList()
    {
        UInt size = mEditorOperationList.size();

        for( UInt i=0; i<size ; i++ )
        {
            IEditorOperation* oldOp = mEditorOperationList.front();
            mEditorOperationList.pop_front();
            MG_SAFE_DELETE( oldOp );
        }
    }

    //-----------------------------------------------------------------------
    IBrushSystem* EditorSystem::getBrushSystem()
    {
        return &BrushSystem::getInstance();
    }

    //-----------------------------------------------------------------------
    ITerrainRaiseHeightOperationManager* EditorSystem::getTerrainRaiseHeightOperationManager()
    {
        return &TerrainRaiseHeightOperationManager::getInstance();
    }

    //-----------------------------------------------------------------------
    ITerrainLowerHeightOperationManager* EditorSystem::getTerrainLowerHeightOperationManager()
    {
        return &TerrainLowerHeightOperationManager::getInstance();
    }
    //-----------------------------------------------------------------------
    ITerrainUniformHeightOperationManager* EditorSystem::getTerrainUniformHeightOperationManager()
    {
        return &TerrainUniformHeightOperationManager::getInstance();
    }
    //-----------------------------------------------------------------------
    ITerrainNoiseHeightOperationManager* EditorSystem::getTerrainNoiseHeightOperationManager()
    {
        return &TerrainNoiseHeightOperationManager::getInstance();
    }
    //-----------------------------------------------------------------------
    ITerrainSmoothHeightOperationManager* EditorSystem::getTerrainSmoothHeightOperationManager()
    {
        return &TerrainSmoothHeightOperationManager::getInstance();
    }
    //-----------------------------------------------------------------------
    ITerrainAddTextureOperationManager* EditorSystem::getTerrainAddTextureOperationManager()
    {
         return &TerrainAddTextureOperationManager::getInstance();
    }
    //-----------------------------------------------------------------------
    ITerrainRemoveTextureOperationManager* EditorSystem::getTerrainRemoveTextureOperationManager()
    {
        return &TerrainRemoveTextureOperationManager::getInstance();
    }
    //-----------------------------------------------------------------------
    ITerrainUniformTextureOperationManager* EditorSystem::getTerrainUniformTextureOOperationManager()
    {
        return &TerrainUniformTextureOperationManager::getInstance();
    }
    //-----------------------------------------------------------------------
    ITerrainMopTextureOperationManager* EditorSystem::getTerrainMopTextureOperationManager()
    {
        return &TerrainMopTextureOperationManager::getInstance();
    }
    //-----------------------------------------------------------------------
    ITerrainBlurTextureOperationManager* EditorSystem::getTerrainBlurTextureOperationManager()
    {
         return &TerrainBlurTextureOperationManager::getInstance();
    }
    //-----------------------------------------------------------------------
    ITerrainTreeOperationManager* EditorSystem::getTerrainTreeOperationManager()
    {
		return &TerrainTreeOperationManager::getInstance();
    }
    //-----------------------------------------------------------------------
    ITerrainAddTreeOperationManager* EditorSystem::getTerrainAddTreeOperationManager()
    {
         return &TerrainAddTreeOperationManager::getInstance();
    }
    //-----------------------------------------------------------------------
    ITerrainRemoveTreeOperationManager* EditorSystem::getTerrainRemoveTreeOperationManager()
    {
         return &TerrainRemoveTreeOperationManager::getInstance();
    }
    //-----------------------------------------------------------------------
    ITerrainDefineTreeOperationManager* EditorSystem::getTerrainDefineTreeOperationManager()
    {
		return &TerrainDefineTreeOperationManager::getInstance();
    }
    //-----------------------------------------------------------------------
    ITerrainAddRegionOperationManager* EditorSystem::getTerrainAddRegionOperationManager()
    {
         return &TerrainAddRegionOperationManager::getInstance();
    }

    //-----------------------------------------------------------------------
    ITerrainRemoveRegionOperationManager* EditorSystem::getTerrainRemoveRegionOperationManager()
    {
         return &TerrainRemoveRegionOperationManager::getInstance();
    }

    //-----------------------------------------------------------------------
    ITerrainWaterShowOperationManager* EditorSystem::getTerrainWaterShowOperationManager()
    {
        return &TerrainWaterShowOperationManager::getInstance();
    }

    //-----------------------------------------------------------------------
    ITerrainWaterHideOperationManager* EditorSystem::getTerrainWaterHideOperationManager()
    {
        return &TerrainWaterHideOperationManager::getInstance();
    }


}


