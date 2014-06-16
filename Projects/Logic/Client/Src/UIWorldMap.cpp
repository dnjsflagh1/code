//*************************************************************************************************************************
#include "stdafx.h"
#include "UIWorldMap.h"
#include "UIDistributionMap.h"
//*************************************************************************************************************************
namespace MG
{
	void CWorldMap::setEvent()
	{

	}
	//------------------------------------------------------------------------------------------
	void CWorldMap::init( const Str& filename )
	{

	}
	//------------------------------------------------------------------------------------------
	void CWorldMap::onClickEnterDistribution( void* widget )
	{

	}
	//------------------------------------------------------------------------------------------
	void CWorldMap::handleEnterDistribution( MapDistributionIdType id )
	{
		UIDistributionMap::getInstance().openGui(id);
	}
	//------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------
	UIWorldMap::UIWorldMap()
		:mCurOpenCWorldMap(NULL)
	{

	}
	//------------------------------------------------------------------------------------------
	MG::Bool UIWorldMap::initialize()
	{
		return true;
	}
	//------------------------------------------------------------------------------------------
	void UIWorldMap::unInitialize()
	{
		std::map<MapIdType, CWorldMap*>::iterator beginIter = mMapCWorldMap.begin();
		std::map<MapIdType, CWorldMap*>::iterator endIter = mMapCWorldMap.end();
		while (beginIter != endIter)
		{
			delete beginIter->second;

			++beginIter;
		}

		mMapCWorldMap.clear();
	}
	//------------------------------------------------------------------------------------------
	void UIWorldMap::openGui( MapIdType mapIdType )
	{
		std::map<MapIdType, CWorldMap*>::iterator iter = mMapCWorldMap.find(mapIdType);
		if ( iter != mMapCWorldMap.end() )
		{
			if ( mCurOpenCWorldMap )
				mCurOpenCWorldMap->closeGui();
			mCurOpenCWorldMap = iter->second;
			mCurOpenCWorldMap->openGui();
		}
	}
	//------------------------------------------------------------------------------------------
	void UIWorldMap::closeGui()
	{
		mCurOpenCWorldMap->closeGui();
		mCurOpenCWorldMap = NULL;
	}

	
}