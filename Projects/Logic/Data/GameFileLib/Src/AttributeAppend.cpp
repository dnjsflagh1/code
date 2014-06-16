//******************************************************************************************
#include "stdafx.h"
#include "AttributeAppend.h"
#include "AttributeList.h"
//******************************************************************************************
#define ATTRIBUTEAPPEND_COL_NUM	21
//******************************************************************************************
namespace MG
{
    //-----------------------------------------------------------------------------
    Bool AttributeGroupInfo::getRandAttributeAppendInfo( const AttributeAppendInfo*& info )
    {
        Int nCount = mAttrAppendInfoMap.size();
        if ( nCount <= 0 )
            return false;

        U32 randnum = MGRandom::getInstance().rand_ab_One(0, (U32)nCount);
        U32 index = 0;
        std::map<U32, AttributeAppendInfo*>::iterator pos = mAttrAppendInfoMap.begin();
        while ( pos != mAttrAppendInfoMap.end() )
        {
            if ( index++ == randnum )
            {
                info = pos->second;
                return true;
            }
            ++pos;
        }

        return false;
    }
    //-----------------------------------------------------------------------------
    const AttributeAppendInfo* AttributeGroupInfo::getRandAttributeAppendInfo( )
    {
        Int nCount = mAttrAppendInfoMap.size();
        if ( nCount <= 0 )
            return NULL;

        U32 randnum = MGRandom::getInstance().rand_ab_One(0, (U32)nCount);
        U32 index = 0;
        std::map<U32, AttributeAppendInfo*>::iterator pos = mAttrAppendInfoMap.begin();
        while ( pos != mAttrAppendInfoMap.end() )
        {
            if ( index++ == randnum )
            {
                return pos->second;  
            }
            ++pos;
        }

        return NULL;
    }
    //-----------------------------------------------------------------------------
    void AttributeGroupInfo::addAttributeAppendInfo( AttributeAppendInfo* info )
    {
        mAttrAppendInfoMap[info->AbilityAppendId] = info;
    }
    //-----------------------------------------------------------------------------
    AttributeAppend::AttributeAppend()
    {

    }
    //-----------------------------------------------------------------------------
    AttributeAppend::~AttributeAppend()
    {
        clear();
    }
    //-----------------------------------------------------------------------------
	// MG_CN_MODIFY
    Bool AttributeAppend::load(Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/)
    {
        CsvReader csvreader;
		// MG_CN_MODIFY
        if(!csvreader.create(fileName, packManager))
        {
            return false;
        }

		DYNAMIC_ASSERT(ATTRIBUTEAPPEND_COL_NUM == csvreader.getColumnSize());

        CsvData* csvdata = NULL;
        Int RowCount = csvreader.count();

        for(int i = 0; i < RowCount; ++i)
        {
            csvdata = csvreader.findValue(i);
            if(!csvdata)
            {
                continue;
            }

            AttributeAppendInfo* tempAttrInfo = new AttributeAppendInfo;
            UInt nCol = 0;

            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempAttrInfo->AbilityAppendId);
			nCol++;
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempAttrInfo->GroupAppendId);


            tempAttrInfo->GroupAppendName = csvdata->mData[nCol++].c_str();


            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), (U32&)tempAttrInfo->AppendType);

            for ( Int i=0; i<APPENDATTR_NUM; i++ )
            {
                MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempAttrInfo->AppendAttrList[i].id);
                MGStrOp::toFlt(csvdata->mData[nCol++].c_str(), tempAttrInfo->AppendAttrList[i].value);
            }

			setAttributeId(tempAttrInfo);

            mAttributeAppendInfoMap[tempAttrInfo->AbilityAppendId] = tempAttrInfo;

            addAttributeAppendInfoToGroup( tempAttrInfo );
        }

        return true;
    }
    //-----------------------------------------------------------------------------
    Bool AttributeAppend::getAttributeAppendInfo( U32 id, const AttributeAppendInfo*& info )
    {
        AttributeAppendInfo* pInfo = mAttributeAppendInfoMap[id];
        if ( pInfo )
        {
            info = pInfo;
            return true;
        }

        return false;
    }
    //-----------------------------------------------------------------------------
    const AttributeAppendInfo* AttributeAppend::getAttributeAppendInfo( U32 id )
    {
        return mAttributeAppendInfoMap[id];
    }
    //-----------------------------------------------------------------------------
    Bool AttributeAppend::getRandAttributeAppendInfo( U32 id, const AttributeAppendInfo*& info )
    {
        AttributeGroupInfo* pInfo = mAttributeGroupInfoMap[id];
        if ( pInfo )
        {
            return pInfo->getRandAttributeAppendInfo(info);
        }

        return false;
    }
    //-----------------------------------------------------------------------------
    const AttributeAppendInfo* AttributeAppend::getRandAttributeAppendInfo( U32 id )
    {
        AttributeGroupInfo* pInfo = mAttributeGroupInfoMap[id];
        if ( pInfo )
        {
            return pInfo->getRandAttributeAppendInfo();
        }

        return NULL;
    }
    //-----------------------------------------------------------------------------
    void AttributeAppend::clear()
    {
        AttributeGroupInfoMapIter iter1 = mAttributeGroupInfoMap.begin();
        while (iter1 != mAttributeGroupInfoMap.end())
        {
            delete iter1->second;
            ++iter1;
        }
        mAttributeGroupInfoMap.clear();

        AttributeAppendInfoMapIter iter2 = mAttributeAppendInfoMap.begin();
        while (iter2 != mAttributeAppendInfoMap.end())
        {
            delete iter2->second;
            ++iter2;
        }
        mAttributeAppendInfoMap.clear();
    }
    //-----------------------------------------------------------------------------
    void AttributeAppend::addAttributeAppendInfoToGroup( AttributeAppendInfo* info )
    {
        AttributeGroupInfoMapIter pos = mAttributeGroupInfoMap.find( info->GroupAppendId );
        if ( pos != mAttributeGroupInfoMap.end() )
        {    
            pos->second->addAttributeAppendInfo(info);
            return;
        }

        AttributeGroupInfo* pInfo = new AttributeGroupInfo;
        mAttributeGroupInfoMap[info->GroupAppendId] = pInfo;
        pInfo->addAttributeAppendInfo(info);
    }
	//-----------------------------------------------------------------------------
	void AttributeAppend::setAttributeId( AttributeAppendInfo* pAttributeAppendInfo )
	{
		for (Int i=0; i<APPENDATTR_NUM; i++)
		{
			if ( pAttributeAppendInfo->AppendAttrList[i].id == 0 )
				continue;
			const AttrInfo* pInfo = AttributeList::getInstance().getAttrInfoByAddId(pAttributeAppendInfo->AppendAttrList[i].id);
			DYNAMIC_ASSERT(pInfo);
			pAttributeAppendInfo->AppendAttrList[i].id = pInfo->attrId;
		}
	}
}