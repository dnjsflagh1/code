/******************************************************************************/
#include "stdafx.h"
#include "TerrainHeightOperationManager.h"
#include "TerrainHeightOperation.h"
/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //TerrainRaiseHeightOperationManager
    /******************************************************************************/
    TerrainRaiseHeightOperationManager::TerrainRaiseHeightOperationManager()
        :mAmp(5)
		,mWaterAmp(5)
    {

    }
    //-----------------------------------------------------------------------
    TerrainRaiseHeightOperationManager::~TerrainRaiseHeightOperationManager()
    {
        
    }
    //-----------------------------------------------------------------------
    Flt TerrainRaiseHeightOperationManager::getAmplitude() 
    {
        return mAmp;
    }

    //-----------------------------------------------------------------------
    void TerrainRaiseHeightOperationManager::setAmplitude(Flt amp)
    {
        mAmp = amp;
    }
	//-----------------------------------------------------------------------
	Flt TerrainRaiseHeightOperationManager::getWaterAmplitude() 
	{
		return mWaterAmp;
	}

	//-----------------------------------------------------------------------
	void TerrainRaiseHeightOperationManager::setWaterAmplitude(Flt amp)
	{
		mWaterAmp = amp;
	}

    //-----------------------------------------------------------------------
    IEditorOperation* TerrainRaiseHeightOperationManager::createOneOperation()
    {
        TerrainRaiseHeightOperation* op = MG_NEW TerrainRaiseHeightOperation(mTerrainSurfaceType);

        return op;
    }
        
    /******************************************************************************/
    //TerrainLowerHeightOperationManager
    /******************************************************************************/
    TerrainLowerHeightOperationManager::TerrainLowerHeightOperationManager()
        :mAmp(5)
		,mWaterAmp(5)
    {

    }

    //-----------------------------------------------------------------------
    TerrainLowerHeightOperationManager::~TerrainLowerHeightOperationManager()
    {

    }

    //-----------------------------------------------------------------------
    Flt TerrainLowerHeightOperationManager::getAmplitude() 
    {
        return mAmp;
    }

    //-----------------------------------------------------------------------
    void TerrainLowerHeightOperationManager::setAmplitude(Flt amp)
    {
        mAmp = amp;
    }

	//-----------------------------------------------------------------------
	Flt TerrainLowerHeightOperationManager::getWaterAmplitude() 
	{
		return mWaterAmp;
	}

	//-----------------------------------------------------------------------
	void TerrainLowerHeightOperationManager::setWaterAmplitude(Flt amp)
	{
		mWaterAmp = amp;
	}

    //-----------------------------------------------------------------------
    IEditorOperation* TerrainLowerHeightOperationManager::createOneOperation()
    {
        TerrainLowerHeightOperation* op = MG_NEW TerrainLowerHeightOperation(mTerrainSurfaceType);

        return op;
    }

    /******************************************************************************/
    //TerrainUniformHeightOperationManager
    /******************************************************************************/
    TerrainUniformHeightOperationManager::TerrainUniformHeightOperationManager()
        :mAmp(5)
		,mLocked(false)
		,mWaterHeight(0.0f)
    {

    }

    //-----------------------------------------------------------------------
    TerrainUniformHeightOperationManager::~TerrainUniformHeightOperationManager()
    {

    }

    //-----------------------------------------------------------------------
    Flt TerrainUniformHeightOperationManager::getAmplitude() 
    {
        return mAmp;
    }

    //-----------------------------------------------------------------------
    void TerrainUniformHeightOperationManager::setAmplitude(Flt amp)
    {
        mAmp = amp;
    }

    //-----------------------------------------------------------------------
    IEditorOperation* TerrainUniformHeightOperationManager::createOneOperation()
    {
        TerrainUniformHeightOperation* op = MG_NEW TerrainUniformHeightOperation(mTerrainSurfaceType);

        return op;
    }

    /******************************************************************************/
    //TerrainNoiseHeightOperationManager
    /******************************************************************************/
    TerrainNoiseHeightOperationManager::TerrainNoiseHeightOperationManager()
        :mAmp(5)
    {

    }

    //-----------------------------------------------------------------------
    TerrainNoiseHeightOperationManager::~TerrainNoiseHeightOperationManager()
    {

    }

    //-----------------------------------------------------------------------
    Flt TerrainNoiseHeightOperationManager::getAmplitude() 
    {
        return mAmp;
    }

    //-----------------------------------------------------------------------
    void TerrainNoiseHeightOperationManager::setAmplitude(Flt amp)
    {
        mAmp = amp;
    }

    //-----------------------------------------------------------------------
    IEditorOperation* TerrainNoiseHeightOperationManager::createOneOperation()
    {
        TerrainNoiseHeightOperation* op = MG_NEW TerrainNoiseHeightOperation(mTerrainSurfaceType);

        return op;
    }

    /******************************************************************************/
    //TerrainSmoothHeightOperationManager
    /******************************************************************************/
    TerrainSmoothHeightOperationManager::TerrainSmoothHeightOperationManager()
        :mAmp(5)
    {

    }

    //-----------------------------------------------------------------------
    TerrainSmoothHeightOperationManager::~TerrainSmoothHeightOperationManager()
    {

    }

    //-----------------------------------------------------------------------
    Flt TerrainSmoothHeightOperationManager::getAmplitude() 
    {
        return mAmp;
    }

    //-----------------------------------------------------------------------
    void TerrainSmoothHeightOperationManager::setAmplitude(Flt amp)
    {
        mAmp = amp;
    }

    //-----------------------------------------------------------------------
    IEditorOperation* TerrainSmoothHeightOperationManager::createOneOperation()
    {
        TerrainSmoothHeightOperation* op = MG_NEW TerrainSmoothHeightOperation(mTerrainSurfaceType);
        return op;
    }


}


