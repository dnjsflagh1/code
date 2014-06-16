//******************************************************************************************
#include "stdafx.h"
#include "LineageTemplate.h"
//******************************************************************************************
namespace MG
{
    LineageTemplate::LineageTemplate()
    {

    }
    //-------------------------------------------------------------------------------
    LineageTemplate::~LineageTemplate()
    {
         clear();
    }
    //-------------------------------------------------------------------------------
	// MG_CN_MODIFY
    Bool LineageTemplate::load(Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/)
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

            LineageInfo* tempLineageInfo = new LineageInfo;
            UInt nCol = 0;

            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), (U32&)tempLineageInfo->lineageID);
            nCol++;

            tempLineageInfo->lineageName = csvdata->mData[nCol++].c_str();
            tempLineageInfo->lineageText = csvdata->mData[nCol++].c_str();
            MGStrOp::toString( csvdata->mData[nCol++].c_str(), tempLineageInfo->artIconRes);


            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempLineageInfo->abilityGroupAppendId);

            mLineageInfoMap[tempLineageInfo->lineageID] = tempLineageInfo;
        }

        return true;
    }
    //-------------------------------------------------------------------------------
    const LineageInfo* LineageTemplate::getLineageInfo( U32 lineageId )
    {
         return  mLineageInfoMap[lineageId];
    }
    //-------------------------------------------------------------------------------
    Bool LineageTemplate::getLineageInfo( U32 lineageId, const LineageInfo*& info )
    {
        LineageInfo* pInfo = mLineageInfoMap[lineageId];
        if ( pInfo )
        {
            info = pInfo;
            return true;
        }

        return false;
    }
    //-------------------------------------------------------------------------------
    void LineageTemplate::clear()
    {
        std::map<U32, LineageInfo*>::iterator pos = mLineageInfoMap.begin();
        while ( pos != mLineageInfoMap.end() )
        {
            delete pos->second;
            ++pos;
        }
        mLineageInfoMap.clear();
    }
}