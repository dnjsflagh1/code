/******************************************************************************/

#include "stdafx.h"
#include "AreaListCsv.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	AreaListCsv::AreaListCsv()
	{

	}

	//--------------------------------------------------------------------------
	AreaListCsv::~AreaListCsv()
	{

	}

	//--------------------------------------------------------------------------
	// MG_CN_MODIFY
	bool AreaListCsv::load(const Char16* FileName, IMGExternalPackManager* packManager/* = NULL*/)
	{
		CsvReader csvreader;
		// MG_CN_MODIFY
		if(!csvreader.create(FileName, packManager))
		{
			return false;
		}

		CsvData* csvdata = NULL;
		Int RowCount = csvreader.count();

		for(Int i = 0; i < RowCount; ++i)
		{
			csvdata = csvreader.findValue(i);
			if(!csvdata)
			{
				continue;
			}

			AreaIdType areaId;
			MGStrOp::toU32(csvdata->mData[ALC_AreaId].c_str(), areaId);

			if (true == mAreaList.hasData(areaId))
			{
				DYNAMIC_ASSERT(0);
				continue;
			}

			I32 areaOpen;
			MGStrOp::toI32(csvdata->mData[ALC_OpenType].c_str(), areaOpen);
			DYNAMIC_ASSERT((AreaOpenType)areaOpen > AOT_Null && (AreaOpenType)areaOpen < AOT_Max);

			I32 areaType;
			MGStrOp::toI32(csvdata->mData[ALC_AreaType].c_str(), areaType);
			DYNAMIC_ASSERT((AreaType)areaOpen > AT_Null && (AreaType)areaOpen < AT_Max);


			AreaListCsvInfo* newArea = mAreaList.createOrRetrieve(areaId, false);
			newArea->areaId		= areaId;
			newArea->areaName	= csvdata->mData[ALC_Name];
			newArea->areaOpen	= (AreaOpenType)areaOpen;
			newArea->areaType	= (AreaType)areaType;

		}
		return true;
	}

	//--------------------------------------------------------------------------
	std::map<AreaIdType, AreaListCsvInfo*>* AreaListCsv::getList()
	{
		return mAreaList.getDataSet();
	}

	//--------------------------------------------------------------------------

}