//*************************************************************************************************************
#include "stdafx.h"
#include "BigMapResCsv.h"
//*************************************************************************************************************
namespace MG
{
    BigMapResCsv::~BigMapResCsv()
    {

    }
    //--------------------------------------------------------------------------------------------
	// MG_CN_MODIFY
    MG::Bool BigMapResCsv::load( Str16 fileName, IMGExternalPackManager* packManager/* = NULL */)
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

            UInt nCol = 3;

            std::string widgetName;
            MGStrOp::toString(csvdata->mData[nCol++].c_str(), widgetName);
            UInt placeid = 0;
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), placeid );


            mMapWidgetNamePlaceId[widgetName] = placeid;
        }

        return true;
    }
    //--------------------------------------------------------------------------------------------
    U32 BigMapResCsv::getPlaceId( std::string widgetName )
    {
        std::map<std::string, U32>::iterator iter = mMapWidgetNamePlaceId.find(widgetName);
        if ( iter != mMapWidgetNamePlaceId.end() )
        {    
            return iter->second;
        }

        return 0;
    }
    //--------------------------------------------------------------------------------------------
    void BigMapResCsv::clear()
    {
        mMapWidgetNamePlaceId.clear();
    }
}