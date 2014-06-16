/******************************************************************************/

#include "stdafx.h"
#include "SRegionObjectBase.h"

/******************************************************************************/

namespace MG
{
	//-----------------------------------------------------------------------
	SRegionObjectBase::SRegionObjectBase(RegionObjectData* regionData)
		:mMapServerNetId(0)
		,mCampaignId(0)
		,mRegionData(regionData)
	{
		DYNAMIC_ASSERT(NULL != regionData);
	}

	//-----------------------------------------------------------------------
	SRegionObjectBase::~SRegionObjectBase()
	{
		MG_SAFE_DELETE(mRegionData);
	}

	//-----------------------------------------------------------------------
	void SRegionObjectBase::setMapServerNetId(NetIdType mapServerNetId)
	{
		mMapServerNetId = mapServerNetId;
	}

	//-----------------------------------------------------------------------
	NetIdType SRegionObjectBase::getMapServerNetId() const
	{
		return mMapServerNetId;
	}

	//-----------------------------------------------------------------------
	void SRegionObjectBase::setCampaignId(const CampaignIdType campaignId)
	{
		mCampaignId = campaignId;
	}

	//-----------------------------------------------------------------------
	CampaignIdType SRegionObjectBase::getCampaignId() const
	{
		return mCampaignId;
	}
	
	//-----------------------------------------------------------------------
	Bool SRegionObjectBase::isOpen()
	{
		return Bool(getMapServerNetId() > 0);
	}

	RegionObjectData* SRegionObjectBase::getRegionData()
	{
		return mRegionData;
	}
	//-----------------------------------------------------------------------
}