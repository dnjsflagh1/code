/******************************************************************************/

#include "stdafx.h"
#include "PlaceListCsv.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	PlaceListCsv::PlaceListCsv()
	{

	}

	//--------------------------------------------------------------------------
	PlaceListCsv::~PlaceListCsv()
	{

	}

	//--------------------------------------------------------------------------
	// MG_CN_MODIFY
	bool PlaceListCsv::load(const Char16* FileName, IMGExternalPackManager* packManager/* = NULL*/)
	{
		CsvReader csvreader;
		// MG_CN_MODIFY
		if(!csvreader.create(FileName, packManager))
		{
			return false;
		}

		CsvData* csvdata = NULL;
		Int RowCount = csvreader.count();

		DYNAMIC_ASSERT(csvreader.getColumnSize() == PLC_Max);

		for(Int i = 0; i < RowCount; ++i)
		{
			csvdata = csvreader.findValue(i);
			if(!csvdata)
			{
				continue;
			}

			I32 placeOpen = -1;
			MGStrOp::toI32(csvdata->mData[PLC_OpenType].c_str(), placeOpen);
			DYNAMIC_ASSERT((PlaceOpenType)placeOpen > POT_Null && (PlaceOpenType)placeOpen < POT_Max);
			if (POT_Open != (PlaceOpenType)placeOpen)
			{
				continue;
			}

			PlaceIdType placeId;
			MGStrOp::toU32(csvdata->mData[PLC_PlaceId].c_str(), placeId);
			if (true == mPlaceList.hasData(placeId))
			{
				DYNAMIC_ASSERT(0);
				continue;
			}

			
			I32 placeRank = -1;
			MGStrOp::toI32(csvdata->mData[PLC_PlaceRank].c_str(), placeRank);
			DYNAMIC_ASSERT((PlaceRankType)placeRank > PlaceRankType_Null && (PlaceRankType)placeRank < PlaceRankType_Max);

			I32 placeType = -1;
			MGStrOp::toI32(csvdata->mData[PLC_PlaceType].c_str(), placeType);
			DYNAMIC_ASSERT((PlaceType)placeType > PlaceType_Null && (PlaceType)placeType < PlaceType_Max);

			MapIdType mapListId = 0;
			MGStrOp::toU32(csvdata->mData[PLC_MapListId].c_str(), mapListId);

			InstanceIdType instanceId = 0;
			MGStrOp::toU32(csvdata->mData[PLC_InstanceId].c_str(), instanceId);

			U32 ArtIconResId = 0;
			MGStrOp::toU32(csvdata->mData[PLC_ArtIconResId].c_str(), ArtIconResId);

			U32 ArtMashResId = 0;
			MGStrOp::toU32(csvdata->mData[PLC_ArtMashResId].c_str(), ArtMashResId);

			MapDistributionIdType mapDistrListId = 0;
			MGStrOp::toU32(csvdata->mData[PLC_MapDistrListId].c_str(), mapDistrListId);

			ArtPointResId artPointResId = 0;
			MGStrOp::toI32(csvdata->mData[PLC_ArtPointResId].c_str(), artPointResId);


			PlaceListCsvInfo* newPlace = mPlaceList.createOrRetrieve(placeId, false);
			newPlace->placeId		= placeId;
			newPlace->placeNote		= csvdata->mData[PLC_Note];
			newPlace->placeName		= csvdata->mData[PLC_Name];
			newPlace->placeListName = csvdata->mData[PLC_ListName];
			newPlace->placeText		= csvdata->mData[PLC_Text];
			newPlace->placeTitle	= csvdata->mData[PLC_Title];
			newPlace->placeOpen		= (PlaceOpenType)placeOpen;
			newPlace->placeRank		= (PlaceRankType)placeRank;
			newPlace->placeType		= (PlaceType)placeType;
			newPlace->mapListId		= mapListId;
			newPlace->instanceId	= instanceId;
			newPlace->artIconResId	= ArtIconResId;
			newPlace->artMashResId	= ArtMashResId;
			newPlace->mapDistrListId= mapDistrListId;
			newPlace->artPointResId	= artPointResId;
		}

		return true;
	}

	//--------------------------------------------------------------------------
	PlaceListCsvInfo* PlaceListCsv::getPlaceListInfo(const PlaceIdType id )
	{
		return mPlaceList.getData( id );
	}

	//--------------------------------------------------------------------------
	std::map<PlaceIdType, PlaceListCsvInfo*>* PlaceListCsv::getList()
	{
		return mPlaceList.getDataSet();
	}

}