//******************************************************************************************
#include "stdafx.h"
#include "AttributeList.h"
//******************************************************************************************
namespace MG
{
    AttributeList::~AttributeList()
    {
        clear();
    }
    //----------------------------------------------------------------------
	// MG_CN_MODIFY
    Bool AttributeList::load(Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/)
    {
		DYNAMIC_ASSERT(mMapAttrInfo.size() == 0);

        CsvReader csvreader;
		// MG_CN_MODIFY
        if(!csvreader.create(fileName, packManager))
        {
            return false;
        }

        CsvData* csvdata = NULL;
        Int RowCount = csvreader.count();

		DYNAMIC_ASSERT(RowCount == ATTR_ID_MAX-1);

        for(int i = 0; i < RowCount; ++i)
        {
            csvdata = csvreader.findValue(i);
            if(!csvdata)
            {
                continue;
            }

            AttrInfo* tempAttrInfo = new AttrInfo;
            UInt nCol = 0;

            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), (U32&)tempAttrInfo->attrId);
			nCol++;

			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempAttrInfo->attrInitId);
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempAttrInfo->attrAddId);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempAttrInfo->groupId);
            tempAttrInfo->attrChName = csvdata->mData[nCol++].c_str();

            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), (U32&)tempAttrInfo->useType);

            MGStrOp::toI32(csvdata->mData[nCol++].c_str(), tempAttrInfo->defaultValue);
            MGStrOp::toI32(csvdata->mData[nCol++].c_str(), tempAttrInfo->minValue);
            MGStrOp::toI32(csvdata->mData[nCol++].c_str(), tempAttrInfo->maxValue);

            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempAttrInfo->formulaParaID[1]);
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempAttrInfo->formulaParaID[2]);
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempAttrInfo->formulaParaID[3]);
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempAttrInfo->formulaParaID[4]);

            mMapAttrInfo[tempAttrInfo->attrId] = tempAttrInfo;

			setGroupIdAttrInfo(tempAttrInfo);
			setUseTypeAttrInfo(tempAttrInfo);
			setInitAttrInfo(tempAttrInfo);
			setAddAttrInfo(tempAttrInfo);
        }

        return true;
    }
    //----------------------------------------------------------------------
    void AttributeList::clear()
    {
		std::map<UInt, std::vector<AttrInfo*>*>::iterator frontgroup = mMapGroupAttrInfo.begin();
		std::map<UInt, std::vector<AttrInfo*>*>::iterator backgroup = mMapGroupAttrInfo.end();
		while (frontgroup != backgroup)
		{
			frontgroup->second->clear();
			delete frontgroup->second;
			++frontgroup;
		}
		mMapGroupAttrInfo.clear();
		//----------------------------------------------------------------------------
		std::map<ATTR_USE_TYPE, std::vector<AttrInfo*>*>::iterator frontUse = mMapUseTypeAttrInfo.begin();
		std::map<ATTR_USE_TYPE, std::vector<AttrInfo*>*>::iterator backUse = mMapUseTypeAttrInfo.end();
		while (frontUse != backUse)
		{
			frontUse->second->clear();
			delete frontUse->second;
			++frontUse;
		}
		mMapUseTypeAttrInfo.clear();
		//----------------------------------------------------------------------------
        std::map<ATTR_ID, AttrInfo*>::iterator pos = mMapAttrInfo.begin();
		std::map<ATTR_ID, AttrInfo*>::iterator back = mMapAttrInfo.end();
        while ( pos != back )
        {
            delete pos->second;

            ++pos;
        }

        mMapAttrInfo.clear();
		mMapInitAttrInfo.clear();
		mMapAddAttrInfo.clear();
    }
    //----------------------------------------------------------------------
    const AttrInfo* AttributeList::getAttrInfo( ATTR_ID id )
    {
        return mMapAttrInfo[id];
    }
    //----------------------------------------------------------------------
    Bool AttributeList::getAttrInfo( ATTR_ID id, const AttrInfo* info )
    {
        AttrInfo* pInfo = mMapAttrInfo[id];
        if (pInfo)
        {
            info = pInfo;
            return true;
        }

        return false;
    }
	//----------------------------------------------------------------------
	void AttributeList::setUseTypeAttrInfo( AttrInfo* info )
	{
		std::map<ATTR_USE_TYPE, std::vector<AttrInfo*>*>::iterator iter = mMapUseTypeAttrInfo.find(info->useType);
		if ( iter != mMapUseTypeAttrInfo.end() )
		{
			iter->second->push_back(info);
		}
		else
		{
			std::vector<AttrInfo*>* tempVectorAttrInfo = new std::vector<AttrInfo*>;
			tempVectorAttrInfo->push_back(info);
			mMapUseTypeAttrInfo[info->useType] = tempVectorAttrInfo;
		}
	}
	//----------------------------------------------------------------------
	std::vector<AttrInfo*>* AttributeList::getVectorAttrInfoByUseType( ATTR_USE_TYPE useType )
	{
		std::map<ATTR_USE_TYPE, std::vector<AttrInfo*>*>::iterator iter = mMapUseTypeAttrInfo.find(useType);
		if ( iter != mMapUseTypeAttrInfo.end() )
			return iter->second;

		return NULL;
	}
	//----------------------------------------------------------------------
	const AttrInfo* AttributeList::getAttrInfoByInitId( UInt initId )
	{
		std::map<UInt, AttrInfo*>::iterator iter = mMapInitAttrInfo.find(initId);
		if ( iter != mMapInitAttrInfo.end() )
			return iter->second;

		return NULL;
	}
	//----------------------------------------------------------------------
	const AttrInfo* AttributeList::getAttrInfoByAddId( UInt addId )
	{
		std::map<UInt, AttrInfo*>::iterator iter = mMapAddAttrInfo.find(addId);
		if ( iter != mMapAddAttrInfo.end() )
			return iter->second;

		return NULL;
	}
	//----------------------------------------------------------------------
	void AttributeList::setInitAttrInfo( AttrInfo* info )
	{
		if ( info->attrInitId == 0 )	return;
		std::map<UInt, AttrInfo*>::iterator iter = mMapInitAttrInfo.find(info->attrInitId);
		if ( iter != mMapInitAttrInfo.end() )
		{	
			DYNAMIC_ASSERT(0);
		}
		else
			mMapInitAttrInfo[info->attrInitId] = info;

	}
	//----------------------------------------------------------------------
	void AttributeList::setAddAttrInfo( AttrInfo* info )
	{
		if ( info->attrAddId == 0 )	return;
		std::map<UInt, AttrInfo*>::iterator iter = mMapAddAttrInfo.find(info->attrAddId);
		if ( iter != mMapAddAttrInfo.end() )
		{	
			DYNAMIC_ASSERT(0);
		}
		else
			mMapAddAttrInfo[info->attrAddId] = info;

	}
	//----------------------------------------------------------------------
	std::vector<AttrInfo*>* AttributeList::getVectorAttrInfoByGroupId( UInt groupId )
	{
		std::map<UInt, std::vector<AttrInfo*>*>::iterator iter = mMapGroupAttrInfo.find(groupId);
		if ( mMapGroupAttrInfo.end() != iter )
			return iter->second;

		return NULL;
	}
	//----------------------------------------------------------------------
	void AttributeList::setGroupIdAttrInfo( AttrInfo* info )
	{
		std::map<UInt, std::vector<AttrInfo*>*>::iterator iter = mMapGroupAttrInfo.find(info->groupId);
		if ( iter != mMapGroupAttrInfo.end() )
		{
			iter->second->push_back(info);
		}
		else
		{
			std::vector<AttrInfo*>* tempVectorAttrInfo = new std::vector<AttrInfo*>;
			tempVectorAttrInfo->push_back(info);
			mMapGroupAttrInfo[info->groupId] = tempVectorAttrInfo;
		}
	}
}