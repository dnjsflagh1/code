#include "stdafx.h"
#include "BlockObject.h"

namespace MG
{
	/**********************************************************************************************/

	BlockObject::BlockObject()
	{

	}

	//------------------------------------------------------------------------------------------

	BlockObject::~BlockObject()
	{
		mCurrRegionGridList.clear();
	}

	//------------------------------------------------------------------------------------------
	void BlockObject::setBlockPosRect( RectF blockPosRect )
	{
		mBlockPosRect = blockPosRect;
	}

	//------------------------------------------------------------------------------------------
	void BlockObject::setCurrRegionGrid( std::map<UInt, BlockObjectSceneManager::RegionGrid*>& currRegionGridList )
	{
		removeCurrRegionGrid();
		addCurrRegionGrid(currRegionGridList);
	}

	//------------------------------------------------------------------------------------------
	void BlockObject::addCurrRegionGrid( std::map<UInt, BlockObjectSceneManager::RegionGrid*>& currRegionGridList )
	{
		for(std::map<UInt, BlockObjectSceneManager::RegionGrid*>::iterator it = currRegionGridList.begin(); it != currRegionGridList.end(); ++it)
		{
			mCurrRegionGridList[it->first] = it->second;
		}
	}

	//------------------------------------------------------------------------------------------
	void BlockObject::removeCurrRegionGrid()
	{
		mCurrRegionGridList.clear();
	}

	//------------------------------------------------------------------------------------------
	RectF BlockObject::getBlockPosRect()
	{
		return mBlockPosRect;
	}

	//------------------------------------------------------------------------------------------
	std::map<UInt, BlockObjectSceneManager::RegionGrid*>* BlockObject::getCurrRegionGrid()
	{
		return &mCurrRegionGridList;
	}

}