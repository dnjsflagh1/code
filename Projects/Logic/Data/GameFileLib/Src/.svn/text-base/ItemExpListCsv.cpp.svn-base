/******************************************************************************/

#include "stdafx.h"
#include "ItemExpListCsv.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	ItemExpListCsv::ItemExpListCsv()
	{

	}

	//--------------------------------------------------------------------------
	ItemExpListCsv::~ItemExpListCsv()
	{

	}

	//--------------------------------------------------------------------------
	Bool ItemExpListCsv::load(const Char16* FileName, IMGExternalPackManager* packManager/* = NULL*/)
	{
		CsvReader csvreader;
		if(!csvreader.create(FileName, packManager))
		{
			return false;
		}

		DYNAMIC_ASSERT(csvreader.getColumnSize() == ItemExpListCsvRow_Max);

		CsvData* csvdata = NULL;
		Int RowCount = csvreader.count();

		for(Int i = 0; i < RowCount; ++i)
		{
			csvdata = csvreader.findValue(i);
			if(!csvdata)
			{
				continue;
			}

			ItemIdType itemExpId = -1;
			MGStrOp::toU64(csvdata->mData[ItemExpListCsvRow_ItemExpId].c_str(), itemExpId);
			if (true == mItemExpList.hasData(itemExpId))
			{
				DYNAMIC_ASSERT(0);
				continue;
			}

			Int atrIconId = -1;
			MGStrOp::toI32(csvdata->mData[ItemExpListCsvRow_ArtIconId].c_str(), atrIconId);

			Int price = -1;
			MGStrOp::toI32(csvdata->mData[ItemExpListCsvRow_Price].c_str(), price);

			Int itemType = -1;
			MGStrOp::toI32(csvdata->mData[ItemExpListCsvRow_Class].c_str(), itemType);

			ItemExpListCsvInfo* newItemExpInfo = mItemExpList.createOrRetrieve(itemExpId, false);
			newItemExpInfo->itemExpId	= itemExpId;
			newItemExpInfo->name		= csvdata->mData[ItemExpListCsvRow_Name];
			newItemExpInfo->text		= csvdata->mData[ItemExpListCsvRow_Text];
			newItemExpInfo->atrIconId	= atrIconId;
			newItemExpInfo->price		= price;
			newItemExpInfo->itemType	= (ITEM_EXP_CLASS)itemType;
		}

		return true;
	}

	//--------------------------------------------------------------------------
	ItemExpListCsvInfo* ItemExpListCsv::getInfoById(ItemIdType id)
	{
		return mItemExpList.getData(id);
	}

	//--------------------------------------------------------------------------
	std::map<ItemIdType, ItemExpListCsvInfo*>* ItemExpListCsv::getList()
	{
		return mItemExpList.getDataSet();
	}

}