/******************************************************************************/

#include "stdafx.h"
#include "VassalCsv.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	VassalCsv::VassalCsv()
	{

	}

	//--------------------------------------------------------------------------
	VassalCsv::~VassalCsv()
	{

	}

	//--------------------------------------------------------------------------
	// MG_CN_MODIFY
	bool VassalCsv::load(const Char16* FileName, IMGExternalPackManager* packManager/* = NULL*/)
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

			Int districtVassalid = -1;
			MGStrOp::toI32(csvdata->mData[Vassal_Row_DistrictVassalid].c_str(), districtVassalid);
			if (true == mVassalCsvList.hasData(districtVassalid))
			{
				DYNAMIC_ASSERT(0);
				continue;
			}

			I32 vassalType = -1;
			MGStrOp::toI32(csvdata->mData[Vassal_Row_Type].c_str(), vassalType);
			DYNAMIC_ASSERT((VassalType)vassalType > Vassal_Null && (VassalType)vassalType < Vassal_Max);

			I32 vassalId = -1;
			MGStrOp::toI32(csvdata->mData[Vassal_Row_VassalId].c_str(), vassalId);

			I32 districtId = -1;
			MGStrOp::toI32(csvdata->mData[Vassal_Row_DistrictId].c_str(), districtId);

			VassalCsvInfo* newVassalInfo = mVassalCsvList.createOrRetrieve(districtVassalid, false);
			newVassalInfo->districtVassalId	= districtVassalid;
			newVassalInfo->type				= (VassalType)vassalType;
			newVassalInfo->vassalId			= vassalId;
			newVassalInfo->districtId		= districtId;
		}

		return true;
	}

	std::map<Int, VassalCsvInfo*>* VassalCsv::getList()
	{
		return mVassalCsvList.getDataSet();
	}

	VassalCsvInfo* VassalCsv::getVassalCsvInfoByRegionId(const VassalType vassalType, const RegionIdType regionId)
	{
		VassalCsvInfo* retInfo = NULL;
		std::map<Int, VassalCsvInfo*>* vassalList = mVassalCsvList.getDataSet();
		for (std::map<Int, VassalCsvInfo*>::iterator iter = vassalList->begin(); iter != vassalList->end(); ++iter)
		{
			VassalCsvInfo* tempVassalCsv = iter->second;
			if (tempVassalCsv->type ==  vassalType && regionId == iter->second->vassalId)
			{
				DYNAMIC_ASSERT(NULL == retInfo);
				retInfo = iter->second;
			}
		}

		return retInfo;
	}

}