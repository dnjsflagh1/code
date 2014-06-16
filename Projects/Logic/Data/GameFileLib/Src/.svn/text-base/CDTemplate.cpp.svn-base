//****************************************************************************************************
#include "stdafx.h"
#include "CDTemplate.h"
//****************************************************************************************************
namespace MG
{
    CDTemplate::~CDTemplate()
    {
        clear();
    }
    //-------------------------------------------------------------------------------
	// MG_CN_MODIFY
    MG::Bool CDTemplate::load( Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/)
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

            CDTempInfo* tempInfo = new CDTempInfo;
            UInt nCol = 0;

            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->TimepieceId            );
			nCol++;
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->TimepieceGroupId       );
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), (U32&)tempInfo->UseType	        );
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), (U32&)tempInfo->TimeType	        );
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), (U32&)tempInfo->SaveType	        );
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), (U32&)tempInfo->SaveEntityType   );

            mCDTempInfoMap[tempInfo->TimepieceId] = tempInfo;
        }

        return true;
    }
    //-------------------------------------------------------------------------------
    const CDTempInfo* CDTemplate::getCDTempInfo( U32 cdTempId )
    {
        return mCDTempInfoMap[cdTempId];
    }
    //-------------------------------------------------------------------------------
    MG::Bool CDTemplate::getCDTempInfo( U32 cdTempId, const CDTempInfo*& info )
    {
        CDTempInfo* pInfo = mCDTempInfoMap[cdTempId];
        if ( pInfo )
        {
            info = pInfo;
            return true;
        }
        return false;
    }
    //-------------------------------------------------------------------------------
    void CDTemplate::clear()
    {
        std::map<U32, CDTempInfo*>::iterator front = mCDTempInfoMap.begin();
        std::map<U32, CDTempInfo*>::iterator back = mCDTempInfoMap.end();
        while (front != back)
        {
            delete front->second;
            ++front;
        }
        mCDTempInfoMap.clear();
    }
}