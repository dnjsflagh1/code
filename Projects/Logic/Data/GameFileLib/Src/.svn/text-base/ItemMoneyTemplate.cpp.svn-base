//*****************************************************************************************************************
#include "stdafx.h"
#include "ItemMoneyTemplate.h"
#include "ArtIconResCsv.h"
//*****************************************************************************************************************
namespace MG
{
    ItemMoneyTemplate::~ItemMoneyTemplate()
    {
    }
    //----------------------------------------------------------------------------------------------------
	MG::Bool ItemMoneyTemplate::load( Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/ )
    {
        CsvReader csvreader;
        if(!csvreader.create(fileName, packManager))
        {
            return false;
        }

		DYNAMIC_ASSERT(csvreader.getColumnSize() == ItemMoneyRow_Max);

        CsvData* csvdata = NULL;
        Int RowCount = csvreader.count();
        for(int i = 0; i < RowCount; ++i)
        {
            csvdata = csvreader.findValue(i);
            if(!csvdata)
            {
                continue;
            }

			ItemIdType ItemMoneyId = -1;
			MGStrOp::toU64(csvdata->mData[ItemMoneyRow_ItemMoneyId].c_str(), ItemMoneyId);
			if (true == mItemMoneyList.hasData(ItemMoneyId))
			{
				DYNAMIC_ASSERT(0);
				continue;
			}

			Int atrIconId = -1;
			MGStrOp::toI32(csvdata->mData[ItemMoneyRow_ArtIconId].c_str(), atrIconId);

			U32 ArtMeshId = -1;
			MGStrOp::toU32(csvdata->mData[ItemMoneyRow_ArtMeshId].c_str(), ArtMeshId);

			U32 Price = -1;
			MGStrOp::toU32(csvdata->mData[ItemMoneyRow_Price].c_str(), Price);

			Int Rank = -1;
			MGStrOp::toI32(csvdata->mData[ItemMoneyRow_Rank].c_str(), Rank);

			Int Class = -1;
			MGStrOp::toI32(csvdata->mData[ItemMoneyRow_Class].c_str(), Class);

			ItemMoneyInfo* newItemMoneyInfo = mItemMoneyList.createOrRetrieve(ItemMoneyId, false);
			newItemMoneyInfo->ItemMoneyId	= ItemMoneyId;
			newItemMoneyInfo->Name			= csvdata->mData[ItemMoneyRow_Name];
			newItemMoneyInfo->Text			= csvdata->mData[ItemMoneyRow_Text];
			newItemMoneyInfo->UnitName		= csvdata->mData[ItemMoneyRow_UnitName];
			newItemMoneyInfo->atrIconId		= atrIconId;
			newItemMoneyInfo->ArtMeshId		= ArtMeshId;
			newItemMoneyInfo->Price			= Price;
			newItemMoneyInfo->Rank			= (ITEM_RANK)Rank;
			newItemMoneyInfo->Class			= (ITEM_MONEY_CLASS)Class;
        }

        return true;
    }
    //----------------------------------------------------------------------------------------------------
	const ItemMoneyInfo* ItemMoneyTemplate::getItemMoneyInfo( ItemIdType tempID )
    {
        return mItemMoneyList.getData(tempID);
    }
    ////----------------------------------------------------------------------------------------------------
    //MG::Bool ItemMoneyTemplate::getItemMoneyInfo( U32 tempID, const ItemMoneyInfo*& info )
    //{
    //    std::map<U64, ItemMoneyInfo*>::iterator iter = mItemMoneyList.find(tempID);
    //    if ( iter != mItemMoneyList.end() )
    //    {   
    //        info = iter->second; 
    //        return true;
    //    }

    //    return false;
    //}
}