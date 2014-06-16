//*************************************************************************************************************************
#include "stdafx.h"
#include "UIDistributionMap.h"
#include "UIBigMap.h"
#include "UIWorldMap.h"
//*************************************************************************************************************************
namespace MG
{
	void CDistributionMap::setEvent()
	{

	}
	//------------------------------------------------------------------------------------------
	void CDistributionMap::init( const Str& filename )
	{

	}
	//------------------------------------------------------------------------------------------
	void CDistributionMap::onClickEnterPlaceMap( void* widget )
	{

	}
	//------------------------------------------------------------------------------------------
	void CDistributionMap::onClickReturnWorldMap( void* widget )
	{

	}
	//------------------------------------------------------------------------------------------
	void CDistributionMap::handleEnterPlaceMap( PlaceIdType id )
	{
		UIBigMap::getInstance().openBigMap(id, ROT_PLACE);
	}
	//------------------------------------------------------------------------------------------
	void CDistributionMap::handleReturnWorldMap( RegionIdType id )
	{
		UIWorldMap::getInstance().openGui(id);
	}
	//------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------

	UIDistributionMap::UIDistributionMap()
		:mCurOpenCDistributionMap(NULL)
	{

	}
	//------------------------------------------------------------------------------------------
	MG::Bool UIDistributionMap::initialize()
	{
		return true;
	}
	//------------------------------------------------------------------------------------------
	void UIDistributionMap::unInitialize()
	{
		std::map<MapDistributionIdType, CDistributionMap*>::iterator beginIter = mMapCDistributionMap.begin();
		std::map<MapDistributionIdType, CDistributionMap*>::iterator endIter = mMapCDistributionMap.end();
		while (beginIter != endIter)
		{
			delete beginIter->second;

			++beginIter;
		}

		mMapCDistributionMap.clear();
	}
	//------------------------------------------------------------------------------------------
	void UIDistributionMap::openGui( MapDistributionIdType mapIdType )
	{
		std::map<MapDistributionIdType, CDistributionMap*>::iterator iter = mMapCDistributionMap.find(mapIdType);
		if ( iter != mMapCDistributionMap.end() )
		{
			if ( mCurOpenCDistributionMap )
			{
				mCurOpenCDistributionMap->closeGui();
			}
			mCurOpenCDistributionMap = iter->second;
			mCurOpenCDistributionMap->openGui();

			return;
		}

		char msg[64] = "";
		Sprintf_s(msg, 64, "%d政区地图不存在", mapIdType);
		DYNAMIC_ASSERT_LOG(0, msg);
	}
	//------------------------------------------------------------------------------------------
	void UIDistributionMap::closeGui()
	{
		mCurOpenCDistributionMap->closeGui();
		mCurOpenCDistributionMap = NULL;
	}

	
}