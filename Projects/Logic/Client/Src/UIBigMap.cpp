//*************************************************************************************************************************
#include "stdafx.h"
#include "UIBigMap.h"
#include "CSceneManager.h"
#include "CMapDistribution.h"
#include "CRegionManager.h"
#include "CRegionObject.h"
#include "UIDistributionMap.h"
//*************************************************************************************************************************
namespace MG
{
	void UIBigMap::setEvent()
	{

	}	
	//-----------------------------------------------------------------------
	void UIBigMap::update( Flt delta )
	{
		if ( isOpen()  &&  mpCRegionObject )
		{
			if ( mpCRegionObject == CSceneManager::getInstance().getCurrRegion() )
			{
				;
			}
		}
	}
	//-----------------------------------------------------------------------
	void UIBigMap::onClickReturnDistributionMap( void* widget )
	{
		UIBigMap::getInstance().handleReturnDistributionMap();
	}
	//-----------------------------------------------------------------------
	void UIBigMap::handleReturnDistributionMap()
	{
		MapDistributionIdType id = 0;
		if ( mpCRegionObject->getRegionType() == ROT_MAP_DISTRIBUTION )
			id = mpCRegionObject->getRegionId();
		else
		{
			CMapDistribution* pCMapDistribution = ((CPlaceObject*)mpCRegionObject)->getRootMapDistributionObj();
			id = pCMapDistribution->getRegionId();
		}

		UIDistributionMap::getInstance().openGui(id);
	}
	//-----------------------------------------------------------------------
	MG::Bool UIBigMap::openBigMap( RegionIdType regionIdType, REGION_OBJ_TYPE regionObjType )
	{
		mpCRegionObject = CRegionManager::getInstance().getRegionObjectById(regionObjType, regionObjType);

		return UIObject::openGui();
	}
}