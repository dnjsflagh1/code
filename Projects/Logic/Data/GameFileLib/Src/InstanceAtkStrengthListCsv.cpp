/******************************************************************************/

#include "stdafx.h"
#include "InstanceAtkStrengthListCsv.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	InstanceAtkStrengthListCsv::InstanceAtkStrengthListCsv()
	{

	}

	//--------------------------------------------------------------------------
	InstanceAtkStrengthListCsv::~InstanceAtkStrengthListCsv()
	{

	}

	//--------------------------------------------------------------------------
	Bool InstanceAtkStrengthListCsv::load(const Char16* FileName, IMGExternalPackManager* packManager/* = NULL*/)
	{
		CsvReader csvreader;

		if(!csvreader.create(FileName, packManager))
		{
			return false;
		}

		DYNAMIC_ASSERT(csvreader.getColumnSize() == InstanceAtkStrengthListCsvRow_Max);

		CsvData* csvdata = NULL;
		Int RowCount = csvreader.count();

		for(Int i = 0; i < RowCount; ++i)
		{
			csvdata = csvreader.findValue(i);
			if(!csvdata)
			{
				continue;
			}

			CampIdType campId;
			MGStrOp::toU64(csvdata->mData[InstanceAtkStrengthListCsvRow_CampId].c_str(), campId);
			if (true == mInstanceAtkStrengthList.hasData(campId))
			{
				DYNAMIC_ASSERT(0);
				continue;
			}

			U32 buildTemplateId;
			MGStrOp::toU32(csvdata->mData[InstanceAtkStrengthListCsvRow_CharacterBuildId].c_str(), buildTemplateId);

			U32 campPoint;
			MGStrOp::toU32(csvdata->mData[InstanceAtkStrengthListCsvRow_CampPointId].c_str(), campPoint);

			U32 generalRefreshPoint;
			MGStrOp::toU32(csvdata->mData[InstanceAtkStrengthListCsvRow_GeneraRefreshpoint].c_str(), generalRefreshPoint);

			U32 generalAlivePoint;
			MGStrOp::toU32(csvdata->mData[InstanceAtkStrengthListCsvRow_GeneraSpawnPoint].c_str(), generalAlivePoint);

			U32 armyPoint01;
			MGStrOp::toU32(csvdata->mData[InstanceAtkStrengthListCsvRow_ArmyPlayedPoint01].c_str(), armyPoint01);

			U32 armyPoint02;
			MGStrOp::toU32(csvdata->mData[InstanceAtkStrengthListCsvRow_ArmyPlayedPoint02].c_str(), armyPoint02);

			U32 armyPoint03;
			MGStrOp::toU32(csvdata->mData[InstanceAtkStrengthListCsvRow_ArmyPlayedPoint03].c_str(), armyPoint03);

			U32 armyPoint04;
			MGStrOp::toU32(csvdata->mData[InstanceAtkStrengthListCsvRow_ArmyPlayedPoint04].c_str(), armyPoint04);

			U32 armyPoint05;
			MGStrOp::toU32(csvdata->mData[InstanceAtkStrengthListCsvRow_ArmyPlayedPoint05].c_str(), armyPoint05);

			InstanceAtkStrengthListCsvInfo* newInfo	= mInstanceAtkStrengthList.createOrRetrieve(campId, false);
			newInfo->campId					= campId;
			newInfo->buildTemplateId		= buildTemplateId;
			newInfo->campPoint				= campPoint;
			newInfo->generalRefreshPoint	= generalRefreshPoint;
			newInfo->generalAlivePoint		= generalAlivePoint;
			newInfo->armyPoint[0]			= armyPoint01;
			newInfo->armyPoint[1]			= armyPoint02;
			newInfo->armyPoint[2]			= armyPoint03;
			newInfo->armyPoint[3]			= armyPoint04;
			newInfo->armyPoint[4]			= armyPoint05;
		}

		return true;
	}

	//--------------------------------------------------------------------------
	InstanceAtkStrengthListCsvInfo* InstanceAtkStrengthListCsv::getInfoById(CampIdType campListId)
	{
		return mInstanceAtkStrengthList.getData(campListId);
	}

	//--------------------------------------------------------------------------
	std::map<CampIdType, InstanceAtkStrengthListCsvInfo*>* InstanceAtkStrengthListCsv::getList()
	{
		return mInstanceAtkStrengthList.getDataSet();
	}
}