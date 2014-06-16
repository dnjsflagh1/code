/******************************************************************************/
#include "stdafx.h"
#include "TerrainTreeOperationManager.h"
#include "TerrainTreeOperation.h"
/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //TerrainDefineTreeOperationManager
    /******************************************************************************/
    TerrainTreeOperationManager::TerrainTreeOperationManager()
        :mOpModelID(0)
    {

    }
    //-----------------------------------------------------------------------
    TerrainTreeOperationManager::~TerrainTreeOperationManager()
    {

    }
    //-----------------------------------------------------------------------
    void TerrainTreeOperationManager::setOpModel( U32 modelID )
    {
        mOpModelID = modelID;
    }
    //-----------------------------------------------------------------------
    U32 TerrainTreeOperationManager::getOpModel()
    {
        return mOpModelID;
    }

	//-----------------------------------------------------------------------
	//设置Tree类型
	void TerrainTreeOperationManager::setTreeType(U32 tType)
	{
		mTreeType = tType;
	}

	//-----------------------------------------------------------------------
	//获取Tree类型
	U32 TerrainTreeOperationManager::getTreeType()
	{
		return mTreeType;
	}

    /******************************************************************************/
    //TerrainAddTreeOperationManager
    /******************************************************************************/
    TerrainAddTreeOperationManager::TerrainAddTreeOperationManager()
        :mDensity(0.5f)
        ,mScaleVariable(0.0f)
        ,mClumping(0.0f)
		,mAlign(true)
		,mPositionOffset(0.3f)
		,mGrassDistance(0.1f)
		,mTreeDistance(10.f)
		,mMinScale(0.1)
		,mMaxScale(1.0)
		,mDistributeType(1)
    {

    }
    //-----------------------------------------------------------------------
    TerrainAddTreeOperationManager::~TerrainAddTreeOperationManager()
    {

    }
    //-----------------------------------------------------------------------
    IEditorOperation* TerrainAddTreeOperationManager::createOneOperation()
    {
        TerrainAddTreeOperation* op = MG_NEW TerrainAddTreeOperation();

        return op;
    }
    //-----------------------------------------------------------------------
    Flt TerrainAddTreeOperationManager::getClumping()
    {
        return mClumping;
    }
    //-----------------------------------------------------------------------
    Flt	TerrainAddTreeOperationManager::getDensity()
    {
        return mDensity;
    }
    //-----------------------------------------------------------------------
    void TerrainAddTreeOperationManager::setClumping( Flt clumping )
    {
        mClumping = clumping;
    }
    //-----------------------------------------------------------------------
    void TerrainAddTreeOperationManager::setDensity(Flt density)
    {
        mDensity = density;
    }
    //-----------------------------------------------------------------------
    void TerrainAddTreeOperationManager::setScaleVariable( Flt variable )
    {
        mScaleVariable = variable;
    }
    //-----------------------------------------------------------------------
    Flt TerrainAddTreeOperationManager::getScaleVariable()
    {
        return mScaleVariable;
    }
    //-----------------------------------------------------------------------
    void TerrainAddTreeOperationManager::setScale( Flt scale )
    {
        mScale = scale;
    }
    //-----------------------------------------------------------------------
    Flt TerrainAddTreeOperationManager::getScale()
    {
        return mScale;
    }

	//-----------------------------------------------------------------------
	Flt TerrainAddTreeOperationManager::getGrassDistance()
	{
		return mGrassDistance;
	}
	//-----------------------------------------------------------------------
	void TerrainAddTreeOperationManager::setGrassDistance(Flt dis)
	{
		mGrassDistance = dis;
	}
	//-----------------------------------------------------------------------
	Flt TerrainAddTreeOperationManager::getTreeDistance()
	{
		return mTreeDistance;
	}
	//-----------------------------------------------------------------------
	void TerrainAddTreeOperationManager::setTreeDistance(Flt dis)
	{
		mTreeDistance = dis;
	}
	//-----------------------------------------------------------------------
	Flt TerrainAddTreeOperationManager::getMinScale()
	{
		return mMinScale;
	}
	//-----------------------------------------------------------------------
	void TerrainAddTreeOperationManager::setMinScale(Flt scale)
	{
		mMinScale = scale;
	}
	//-----------------------------------------------------------------------
	Flt TerrainAddTreeOperationManager::getMaxScale()
	{
		return mMaxScale;
	}
	//-----------------------------------------------------------------------
	void TerrainAddTreeOperationManager::setMaxScale(Flt scale)
	{
		mMaxScale = scale;
	}
	//-----------------------------------------------------------------------
	bool TerrainAddTreeOperationManager::getAlign()
	{
		return mAlign;
	}
	//-----------------------------------------------------------------------
	void TerrainAddTreeOperationManager::setAlign(bool align)
	{
		mAlign = align;
	}

	//-----------------------------------------------------------------------
	Flt TerrainAddTreeOperationManager::getPositionOffset()
	{
		return mPositionOffset;
	}
	//-----------------------------------------------------------------------
	void TerrainAddTreeOperationManager::setPositionOffset(Flt offset)
	{
		mPositionOffset = offset;
	}

	//-----------------------------------------------------------------------
	U32 TerrainAddTreeOperationManager::getDistribute()
	{
		return mDistributeType;
	}
	//-----------------------------------------------------------------------
	void TerrainAddTreeOperationManager::setDistribute(U32 disType)
	{
		mDistributeType = disType;
	}

    /*********************************************************************/
    //TerrainRemoveTreeOperationManager
    /******************************************************************************/
    TerrainRemoveTreeOperationManager::TerrainRemoveTreeOperationManager()
    {

    }
    //-----------------------------------------------------------------------
    TerrainRemoveTreeOperationManager::~TerrainRemoveTreeOperationManager()
    {

    }
    //-----------------------------------------------------------------------
    IEditorOperation* TerrainRemoveTreeOperationManager::createOneOperation()
    {
        TerrainRemoveTreeOperation* op = MG_NEW TerrainRemoveTreeOperation();

        return op;
    }

    /******************************************************************************/
    //TerrainAddTreeByNoiseOperationManager
    /******************************************************************************/
    TerrainDefineTreeOperationManager::TerrainDefineTreeOperationManager()
        :mDefineMode(DEFINE_BATCH_MODE_COMMON)
        ,mLocked(false)
    {
    }
    //-----------------------------------------------------------------------
    TerrainDefineTreeOperationManager::~TerrainDefineTreeOperationManager()
    {

    }
    //-----------------------------------------------------------------------
    IEditorOperation* TerrainDefineTreeOperationManager::createOneOperation()
    {
        TerrainDefineTreeOperation* op = MG_NEW TerrainDefineTreeOperation();
        return op;
    }
}


