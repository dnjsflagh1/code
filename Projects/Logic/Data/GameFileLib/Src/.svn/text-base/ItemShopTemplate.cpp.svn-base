//*****************************************************************************************************
#include "stdafx.h"
#include "ItemShopTemplate.h"
//*****************************************************************************************************
namespace MG
{
    ItemShopTemplate::~ItemShopTemplate()
    {
        clear();
    }
    //----------------------------------------------------------------------------------------
	// MG_CN_MODIFY
    MG::Bool ItemShopTemplate::load( Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/ )
    {
        CsvReader csvreader;
		// MG_CN_MODIFY
        if(!csvreader.create(fileName, packManager))
        {
            return false;
        }

        CsvData* csvdata = NULL;
        Int RowCount = csvreader.count();

        for(int i = 0; i < RowCount; ++i)
        {
            csvdata = csvreader.findValue(i);
            if(!csvdata)
            {
                continue;
            }

            ItemShopInfo* tempInfo = new ItemShopInfo;
            UInt nCol = 0;

            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->ItemShopID         );
			nCol++;
            wcscpy_s(tempInfo->ShopName, NAME_LENGTH, csvdata->mData[nCol++].c_str());

            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->Repair                     );
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->MoneyId                    );
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->GroupID                    );

            mItemShopInfoMap[tempInfo->ItemShopID] = tempInfo;
        }

        return true;
    }
    //----------------------------------------------------------------------------------------
    const ItemShopInfo* ItemShopTemplate::getItemShopInfo( U32 shopId )
    {
        return mItemShopInfoMap[shopId];
    }
    //----------------------------------------------------------------------------------------
    MG::Bool ItemShopTemplate::getItemShopInfo( U32 shopId, const ItemShopInfo*& info )
    {
        ItemShopInfo* pInfo = mItemShopInfoMap[shopId];
        if (pInfo)
        {
            info = pInfo;
            return true;
        }

        return false;
    }
    //----------------------------------------------------------------------------------------
    void ItemShopTemplate::clear()
    {
        std::map<U32, ItemShopInfo*>::iterator front = mItemShopInfoMap.begin();
        std::map<U32, ItemShopInfo*>::iterator back  = mItemShopInfoMap.end();
        while (front != back)
        {
            delete front->second;
            ++front;
        }

        mItemShopInfoMap.clear();
    }
}