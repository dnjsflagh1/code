//*********************************************************************************************

#include "stdafx.h"
#include "CRegionObject.h"

#include "RegionObjectData.h"
#include "ArtMapResCsv.h"

//*********************************************************************************************

namespace MG
{
	//--------------------------------------------------------------------------------------
	CRegionObject::CRegionObject(RegionObjectData* regionData)
		:mRegionData(regionData)
		,mHasCreated(false)
	{
	}

	//--------------------------------------------------------------------------------------
	CRegionObject::~CRegionObject()
	{

	}

	//--------------------------------------------------------------------------------------
	void CRegionObject::_create()
	{
		MGStrOp::toString(getData()->getMapListCsvInfo()->filePath.c_str(), mFilePath);
		MGStrOp::toString(getData()->getMapListCsvInfo()->fileName.c_str(), mFileName);
		MGStrOp::toString(getData()->getArtMapResCsvInfo()->BaseFilePath.c_str(), mBaseFilePath);
	}

	//--------------------------------------------------------------------------------------
	Str& CRegionObject::getFilePath()
	{
		if (false == mHasCreated)
		{
			_create();
			mHasCreated = true;
		}

		return mFilePath;
	}

	//--------------------------------------------------------------------------------------
	Str& CRegionObject::getFileName()
	{
		if (false == mHasCreated)
		{
			_create();
			mHasCreated = true;
		}
		return mFileName;
	}

	//--------------------------------------------------------------------------------------
	Str& CRegionObject::getBaseFilePath()
	{
		if (false == mHasCreated)
		{
			_create();
			mHasCreated = true;
		}

		return mBaseFilePath;
	}
	//--------------------------------------------------------------------------------------
	RegionObjectData* CRegionObject::getData()
	{
        return mRegionData;
	}

	//--------------------------------------------------------------------------------------
}