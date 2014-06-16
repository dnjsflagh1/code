//******************************************************************************************
#include "stdafx.h"
#include "PointTemplate.h"
//******************************************************************************************
namespace MG
{
    PointTemplate::PointTemplate()
    {

    }
    //-----------------------------------------------------------------------------
    PointTemplate::~PointTemplate()
    {
        clear();
    }
    //-----------------------------------------------------------------------------
	// MG_CN_MODIFY
    Bool PointTemplate::load(Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/)
    {
		CsvReader csvreader;
		// MG_CN_MODIFY
		if(!csvreader.create(fileName, packManager))
		{
			Str16 error_msg = L"Load csv file ERROR: " + fileName;
			MG_MESSAGE(error_msg.c_str());
			DYNAMIC_ASSERT(false);
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

			PointTempInfo* pointInfo = new PointTempInfo;
			UInt nCol = 0;

			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), pointInfo->PointTemplateId);

			pointInfo->Note		 = csvdata->mData[nCol++].c_str();
			pointInfo->ListName	 = csvdata->mData[nCol++].c_str();
			pointInfo->Name      = csvdata->mData[nCol++].c_str();
			

			U32 result = 0;
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), result );
			pointInfo->UseType = (PointUseType)result;

			result = 0;
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), result );
			pointInfo->ShowType = (PointShowType)result;

			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), pointInfo->ArtMashId );

			mPointTempInfoMap[pointInfo->PointTemplateId] = pointInfo;
		}

		return true;
    }
    //-----------------------------------------------------------------------------
    const PointTempInfo* PointTemplate::getPointTempInfo( U32 Id )
    {
        return  mPointTempInfoMap[Id];
    }
	//-----------------------------------------------------------------------------
	const PointTempInfo* PointTemplate::getPointTempInfoByIndex( U32 index )
	{
		std::map<U32, PointTempInfo*>::iterator iter = mPointTempInfoMap.begin();
		while ( (index--) > 0 )
		{
			iter++;
		}
		return iter->second;
	}
    //-----------------------------------------------------------------------------
    void PointTemplate::clear()
    {
        std::map<U32, PointTempInfo*>::iterator pos = mPointTempInfoMap.begin();
        while ( pos != mPointTempInfoMap.end() )
        {
            delete pos->second;
            ++pos;
        }
        mPointTempInfoMap.clear();
    }
}
