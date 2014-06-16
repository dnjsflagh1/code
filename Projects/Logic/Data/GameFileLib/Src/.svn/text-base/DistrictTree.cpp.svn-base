

/******************************************************************************/

#include "stdafx.h"
#include "DistrictTree.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	DistrictTreeCsv::DistrictTreeCsv()
	{

	}

	//--------------------------------------------------------------------------
	DistrictTreeCsv::~DistrictTreeCsv()
	{

	}

	//--------------------------------------------------------------------------
	// MG_CN_MODIFY
	Bool DistrictTreeCsv::loadCsv(const Char16* FileName, IMGExternalPackManager* packManager/* = NULL*/)
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

			DistrictTreeIdType treeId;
			MGStrOp::toI32(csvdata->mData[DistrictTreeRow::districtTreeId].c_str(), treeId);

			if (true == mDistrictTree.hasData(treeId))
			{
				DYNAMIC_ASSERT(0);
				continue;
			}

			DistrictTreeInfo* newDistrictInfo = mDistrictTree.createOrRetrieve(treeId, false);
			newDistrictInfo->districtTreeId = treeId;
			I32 rootType = -1;
			MGStrOp::toI32(csvdata->mData[DistrictTreeRow::root_type].c_str(), rootType);
			newDistrictInfo->rootType = (RootType)rootType;
			MGStrOp::toI32(csvdata->mData[DistrictTreeRow::master_districtId].c_str(), newDistrictInfo->masterDistrictId);
			MGStrOp::toI32(csvdata->mData[DistrictTreeRow::slaver_districtId].c_str(), newDistrictInfo->slaveDistrictId);
		}

		return true;
	}

	//--------------------------------------------------------------------------
	std::map<DistrictTreeIdType, DistrictTreeInfo*>* DistrictTreeCsv::getDistrictTreeList()
	{
		return mDistrictTree.getDataSet();
	}

	//--------------------------------------------------------------------------
}


