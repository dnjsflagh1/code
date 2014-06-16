/******************************************************************************/
#include "stdafx.h"
#include "TerrainTextureOperationManager.h"
#include "TerrainTextureOperation.h"
/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //TerrainAddTextureOperationManager
    /******************************************************************************/
    TerrainAddTextureOperationManager::TerrainAddTextureOperationManager()
        :mAmp(0.3)
    {

    }

    //-----------------------------------------------------------------------
    TerrainAddTextureOperationManager::~TerrainAddTextureOperationManager()
    {

    }

    //-----------------------------------------------------------------------
    Flt TerrainAddTextureOperationManager::getAmplitude() 
    {
        return mAmp;
    }

    //-----------------------------------------------------------------------
    void TerrainAddTextureOperationManager::setAmplitude(Flt amp)
    {
        mAmp = amp;
    }

    //-----------------------------------------------------------------------
    IEditorOperation* TerrainAddTextureOperationManager::createOneOperation()
    {
        TerrainAddTextureOperation* op = MG_NEW TerrainAddTextureOperation();

        return op;
    }

    /******************************************************************************/
    //TerrainRemoveTextureOperationManager
    /******************************************************************************/
    TerrainRemoveTextureOperationManager::TerrainRemoveTextureOperationManager()
        :mAmp(0.3)
    {

    }

    //-----------------------------------------------------------------------
    TerrainRemoveTextureOperationManager::~TerrainRemoveTextureOperationManager()
    {

    }

    //-----------------------------------------------------------------------
    Flt TerrainRemoveTextureOperationManager::getAmplitude() 
    {
        return mAmp;
    }

    //-----------------------------------------------------------------------
    void TerrainRemoveTextureOperationManager::setAmplitude(Flt amp)
    {
        mAmp = amp;
    }

    //-----------------------------------------------------------------------
    IEditorOperation* TerrainRemoveTextureOperationManager::createOneOperation()
    {
        TerrainRemoveTextureOperation* op = MG_NEW TerrainRemoveTextureOperation();

        return op;
    }

    /******************************************************************************/
    //TerrainUniformTextureOperationManager
    /******************************************************************************/
    TerrainUniformTextureOperationManager::TerrainUniformTextureOperationManager()
        :mAmp(0.3)
    {

    }

    //-----------------------------------------------------------------------
    TerrainUniformTextureOperationManager::~TerrainUniformTextureOperationManager()
    {

    }

    //-----------------------------------------------------------------------
    Flt TerrainUniformTextureOperationManager::getAmplitude() 
    {
        return mAmp;
    }

    //-----------------------------------------------------------------------
    void TerrainUniformTextureOperationManager::setAmplitude(Flt amp)
    {
        mAmp = amp;
    }

    //-----------------------------------------------------------------------
    IEditorOperation* TerrainUniformTextureOperationManager::createOneOperation()
    {
        TerrainUniformTextureOperation* op = MG_NEW TerrainUniformTextureOperation();

        return op;
    }

    /******************************************************************************/
    //TerrainMopTextureOperationManager
    /******************************************************************************/
    TerrainMopTextureOperationManager::TerrainMopTextureOperationManager()
        :mAmp(0.3)
    {

    }

    //-----------------------------------------------------------------------
    TerrainMopTextureOperationManager::~TerrainMopTextureOperationManager()
    {

    }

    //-----------------------------------------------------------------------
    Flt TerrainMopTextureOperationManager::getAmplitude() 
    {
        return mAmp;
    }

    //-----------------------------------------------------------------------
    void TerrainMopTextureOperationManager::setAmplitude(Flt amp)
    {
        mAmp = amp;
    }

    //-----------------------------------------------------------------------
    IEditorOperation* TerrainMopTextureOperationManager::createOneOperation()
    {
        TerrainMopTextureOperation* op = MG_NEW TerrainMopTextureOperation();

        return op;
    }

    /******************************************************************************/
    //TerrainBlurTextureOperationManager
    /******************************************************************************/
    TerrainBlurTextureOperationManager::TerrainBlurTextureOperationManager()
        :mAmp(0.3)
    {

    }

    //-----------------------------------------------------------------------
    TerrainBlurTextureOperationManager::~TerrainBlurTextureOperationManager()
    {

    }

    //-----------------------------------------------------------------------
    Flt TerrainBlurTextureOperationManager::getAmplitude() 
    {
        return mAmp;
    }

    //-----------------------------------------------------------------------
    void TerrainBlurTextureOperationManager::setAmplitude(Flt amp)
    {
        mAmp = amp;
    }

    //-----------------------------------------------------------------------
    IEditorOperation* TerrainBlurTextureOperationManager::createOneOperation()
    {
        TerrainBlurTextureOperation* op = MG_NEW TerrainBlurTextureOperation();

        return op;
    }
}


