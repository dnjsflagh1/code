
/******************************************************************************/

#include "stdafx.h"
#include "ArtMapResCsv.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	ArtMapResCsv::ArtMapResCsv()
	{

	}

	//--------------------------------------------------------------------------
	ArtMapResCsv::~ArtMapResCsv()
	{

	}

	//--------------------------------------------------------------------------
	// MG_CN_MODIFY
	Bool ArtMapResCsv::load(const Char16* FileName, IMGExternalPackManager* packManager/* = NULL*/)
	{
		CsvReader csvreader;
		// MG_CN_MODIFY
		if(!csvreader.create(FileName, packManager))
		{
			return false;
		}

		DYNAMIC_ASSERT(csvreader.getColumnSize() == AMR_RPGRadarID + 1 || csvreader.getColumnSize() == AMR_Max);
		
		CsvData* csvdata = NULL;
		Int RowCount = csvreader.count();

		for(Int i = 0; i < RowCount; ++i)
		{
			csvdata = csvreader.findValue(i);
			if(!csvdata)
			{
				continue;
			}

			ArtMapResIdType artMapResId;
			MGStrOp::toI32(csvdata->mData[AMR_ArtMapResId].c_str(), artMapResId);
			if (true == mArtMapResList.hasData(artMapResId))
			{
				DYNAMIC_ASSERT(0);
				continue;
			}

			ArtMapResCsvInfo* newArtMapRes = mArtMapResList.createOrRetrieve(artMapResId, false);
			newArtMapRes->artMapResId	= artMapResId;
			newArtMapRes->name			= csvdata->mData[AMR_Name];
			newArtMapRes->BaseFilePath	= csvdata->mData[AMR_BaseFilePath];
			//newArtMapRes->cameraId		= csvdata->mData[AMR_CameraSetID];

			MGStrOp::toI32(csvdata->mData[AMR_UseType].c_str(), (I32&)newArtMapRes->mapType);
			MGStrOp::toU32(csvdata->mData[AMR_RPGCamSetID].c_str(), newArtMapRes->rpgCameraId);
			MGStrOp::toU32(csvdata->mData[AMR_RPGRadarID].c_str(), newArtMapRes->rpgRadarId);

			if ( csvdata->mData.size() > AMR_RPGRadarID + 1 )
			{
				MGStrOp::toU32(csvdata->mData[AMR_SLGCamSetID].c_str(), newArtMapRes->slgCameraId);
				MGStrOp::toU32(csvdata->mData[AMR_SLGRadarID].c_str(), newArtMapRes->slgRadarId);
			}
			else
			{
				newArtMapRes->slgCameraId = newArtMapRes->rpgCameraId;
				newArtMapRes->slgRadarId = newArtMapRes->rpgRadarId;
			}
		}

		return true;
	}

	//--------------------------------------------------------------------------
	ArtMapResCsvInfo* ArtMapResCsv::getArtMapResInfoById(ArtMapResIdType id)
	{
		return mArtMapResList.getData(id);
	}

	//--------------------------------------------------------------------------
	const ArtMapResCsvInfo* ArtMapResCsv::getArtMapResInfoByIndex(I32 order)
	{
		SimpleMapDataSetManager<ArtMapResIdType, ArtMapResCsvInfo>::DataSetMap* dataList = mArtMapResList.getDataSet();
		if ( !dataList || order >= (Int)dataList->size() )
		{
			return NULL;
		}

		SimpleMapDataSetManager<ArtMapResIdType, ArtMapResCsvInfo>::DataSetMapIter iter = dataList->begin();
		while( (order--) > 0 )
		{
			iter++;
		}
		return iter->second;
	}
}