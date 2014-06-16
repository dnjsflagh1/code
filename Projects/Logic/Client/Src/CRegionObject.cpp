//*********************************************************************************************

#include "stdafx.h"
#include "CRegionObject.h"

#include "RegionObjectData.h"
#include "ArtMapResCsv.h"
#include "InstanceType2GameType.h"
#include "CPlayer.h"

//*********************************************************************************************

namespace MG
{
	//--------------------------------------------------------------------------------------
	CRegionObject::CRegionObject(RegionObjectData* regionData)
		:mRegionData(regionData)
		,mStartCampaignTime(0)
	{
		MGStrOp::toString(getData()->getMapListCsvInfo()->filePath.c_str(), mFilePath);
		MGStrOp::toString(getData()->getMapListCsvInfo()->fileName.c_str(), mFileName);
		MGStrOp::toString(getData()->getArtMapResCsvInfo()->BaseFilePath.c_str(), mBaseFilePath);
		MGStrOp::toString(getRegionNameStr16().c_str(), mRegionName);
	}

	//--------------------------------------------------------------------------------------
	CRegionObject::~CRegionObject()
	{

	}

	//--------------------------------------------------------------------------------------
	GameType CRegionObject::getGameType()
	{
		if (ROT_PLACE	== getRegionType())
		{
			InstanceUIdType uid = CPlayer::getInstance().getInstanceUid();
			if (uid > 0)
				return GameType_Slg;
			else
				return GameType_Rpg;
		}
		else
			return InstanceType2GameType::InstanceTypeChangeGameType(getRegionType());
	}

	//--------------------------------------------------------------------------------------
	RegionObjectData* CRegionObject::getData()
	{
		return mRegionData;
	}

	//--------------------------------------------------------------------------------------
	Str& CRegionObject::getFilePath()
	{
		return mFilePath;
	}

	//--------------------------------------------------------------------------------------
	Str& CRegionObject::getFileName()
	{
		return mFileName;
	}

	//--------------------------------------------------------------------------------------
	Str& CRegionObject::getBaseFilePath()
	{
		return mBaseFilePath;
	}

	//--------------------------------------------------------------------------------------
	Str16& CRegionObject::getRegionNameStr16()
	{
		return getData()->getMapListCsvInfo()->mapName;
	}

	Str& CRegionObject::getRegionNameStr8()
	{
		return mRegionName;
	}

	//--------------------------------------------------------------------------------------
	MapType CRegionObject::getMapType()
	{
		return getData()->getMapListCsvInfo()->mapType; 
	}

	void CRegionObject::setStartCampaignTime(U32 prepareTimeSecond)
	{
		mStartCampaignTime = prepareTimeSecond;
	}

	U64 CRegionObject::getStartCampaignTime() const
	{
		return mStartCampaignTime;
	}
	//--------------------------------------------------------------------------------------
}