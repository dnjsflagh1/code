//******************************************************************************************
#include "stdafx.h"
#include "AttributePara.h"
//******************************************************************************************
namespace MG
{
    AttributePara::AttributePara()
    {

    }
    //--------------------------------------------------------------------------------------------------
    AttributePara::~AttributePara()
    {
        clear();
    }
    //--------------------------------------------------------------------------------------------------
	// MG_CN_MODIFY
    Bool AttributePara::load(Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/)
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

            AttrParaInfo* tempAttrInfo = new AttrParaInfo;
            UInt nCol = 0;

            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempAttrInfo->FormulaParameterId);
			nCol++;
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempAttrInfo->FormulaId);
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempAttrInfo->AbilityId);

            
            for ( Int i=0; i<ATTR_PARA_NUM; i++ )
            {
                MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempAttrInfo->attrID[i]); 
            }
            for ( Int i=0; i<ATTR_PARA_NUM; i++ )
            {
                MGStrOp::toFlt(csvdata->mData[nCol++].c_str(), tempAttrInfo->para[i]); 
            }
            
            mAttrParaInfoMap[tempAttrInfo->FormulaParameterId] = tempAttrInfo;

        }

        return true;
    }
    //--------------------------------------------------------------------------------------------------
    Bool AttributePara::getAttrParaInfo( U32 id, const AttrParaInfo*& info )
    {
       AttrParaInfo* pInfo = mAttrParaInfoMap[id];
       if (pInfo)
       {
           info = pInfo;
           return true;
       }

       return false;
    }
    //--------------------------------------------------------------------------------------------------
    const AttrParaInfo* AttributePara::getAttrParaInfo( U32 id )
    {
        AttrParaInfo* pInfo = mAttrParaInfoMap[id];
        if (pInfo)
        {
            return pInfo;
        }

        return NULL;
    }
    //--------------------------------------------------------------------------------------------------
    void AttributePara::clear()
    {
        AttrParaInfoMapIter pos = mAttrParaInfoMap.begin();
        while (pos != mAttrParaInfoMap.end())
        {
            delete pos->second;
            ++pos;
        }
        mAttrParaInfoMap.clear();
    }
    
}