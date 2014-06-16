//*****************************************************************************************************************
#include "stdafx.h"
#include "ItemSiteTemplate.h"
//*****************************************************************************************************************
namespace MG
{
    //------------------------------------------------------------------------------------------------
    // MG_CN_MODIFY
	Bool ItemSiteTemplate::load( Str16 fileName, IMGExternalPackManager* packManager/* = NULL */)
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

            ItemSiteInfo tempInfo;
            UInt nCol = 0;
            
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo.Id  );
            nCol++;
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), (U32&)tempInfo.SiteType  );
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), (U32&)tempInfo.ReplaceType  );
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo.MaxNum             );
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo.DefaultNum         );

            mItemSiteInfoMap[tempInfo.SiteType] = tempInfo;
        }

        return true;
    }
    //------------------------------------------------------------------------------------------------
    const ItemSiteInfo* ItemSiteTemplate::getItemSiteInfo( ITEM_SITE_TYPE siteID )
    {
        DYNAMIC_ASSERT( siteID > ITEM_SITE_TYPE_NULL );
        DYNAMIC_ASSERT( siteID < ITEM_SITE_TYPE_MAX);

        return &( mItemSiteInfoMap[siteID] );
    }
    //------------------------------------------------------------------------------------------------
    MG::Bool ItemSiteTemplate::getItemSiteInfo( ITEM_SITE_TYPE siteID, const ItemSiteInfo* info )
    {
        DYNAMIC_ASSERT( siteID > ITEM_SITE_TYPE_NULL );
        DYNAMIC_ASSERT( siteID < ITEM_SITE_TYPE_MAX);

        info = &( mItemSiteInfoMap[siteID] );

        return true;
    }

}