//********************************************************************************************************************
#include "stdafx.h"
#include "AccessListCsv.h"
//********************************************************************************************************************
namespace MG
{
    AccessListCsv::~AccessListCsv()
    {
        clear();
    }
    //-----------------------------------------------------------------------------------
	// MG_CN_MODIFY
    MG::Bool AccessListCsv::load( Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/ )
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

            AccessInfo* tempInfo = new AccessInfo;
            UInt nCol = 0;

            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->AccessId           );
            tempInfo->RoadName = csvdata->mData[nCol++];
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), (U32&)tempInfo->Type	        );
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->PlaceAId           );
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->PlaceBId           );
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->MapId	            );

            mMapAccessInfo[tempInfo->AccessId] = tempInfo;
        }

        return true;
    }
    //-----------------------------------------------------------------------------------
    const AccessInfo* AccessListCsv::getAccessInfo( U32 accessId )
    {
        std::map<U32, AccessInfo*>::iterator iter = mMapAccessInfo.find(accessId);
        if ( iter != mMapAccessInfo.end() )
        {
            return iter->second;
        }

        return NULL;
    }
    //-----------------------------------------------------------------------------------
    MG::Bool AccessListCsv::getAccessInfo( U32 accessId, const AccessInfo*& info )
    {
        std::map<U32, AccessInfo*>::iterator iter = mMapAccessInfo.find(accessId);
        if ( iter != mMapAccessInfo.end() )
        {
            info = iter->second;
            return true;
        }

        info = NULL;
        return false;
    }
    //-----------------------------------------------------------------------------------
    void AccessListCsv::clear()
    {
        std::map<U32, AccessInfo*>::iterator front = mMapAccessInfo.begin();
        std::map<U32, AccessInfo*>::iterator back = mMapAccessInfo.end();
        while (front != back)
        {
            MG_DELETE front->second;
            ++front;
        }

        mMapAccessInfo.clear();
    }
}