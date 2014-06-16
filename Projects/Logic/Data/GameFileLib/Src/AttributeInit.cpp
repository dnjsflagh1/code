//******************************************************************************************
#include "stdafx.h"
#include "AttributeInit.h"
#include "AttributeList.h"
//******************************************************************************************
#define  ATTRIBUTEINIT_COL_NUM 18
//******************************************************************************************
namespace MG
{
	MG::Bool AttributeInit::load( Str16 fileName, IMGExternalPackManager* packManager /*= NULL*/ )
	{
		DYNAMIC_ASSERT( mMapAttributeInitInfo.size() == 0 );

		CsvReader csvreader;
		// MG_CN_MODIFY
		if(!csvreader.create(fileName, packManager))
		{
			return false;
		}

		DYNAMIC_ASSERT(csvreader.getColumnSize() == ATTRIBUTEINIT_COL_NUM);

		CsvData* csvdata = NULL;
		Int RowCount = csvreader.count();

		for(int i = 0; i < RowCount; ++i)
		{
			csvdata = csvreader.findValue(i);
			if(!csvdata)
			{
				continue;
			}

			AttributeInitInfo* tempAttrInfo = new AttributeInitInfo;
			UInt nCol = 0;

			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempAttrInfo->AbilityInitId);
			nCol++;

			for ( Int i=0; i<APPENDATTR_NUM; i++ )
			{
				MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempAttrInfo->AppendAttrList[i].id);
				MGStrOp::toFlt(csvdata->mData[nCol++].c_str(), tempAttrInfo->AppendAttrList[i].value);
			}

			setAttributeId(tempAttrInfo);

			mMapAttributeInitInfo[tempAttrInfo->AbilityInitId] = tempAttrInfo;

		}

		return true;
	}
	//--------------------------------------------------------------------------
	const AttributeInitInfo* AttributeInit::getAttributeInitInfo( U32 id )
	{
		std::map<UInt, AttributeInitInfo*>::iterator iter = mMapAttributeInitInfo.find(id);
		if ( iter != mMapAttributeInitInfo.end() )
			return iter->second;

		return NULL;
	}
	//--------------------------------------------------------------------------
	void AttributeInit::clear()
	{
		std::map<UInt, AttributeInitInfo*>::iterator frontIter = mMapAttributeInitInfo.begin();
		std::map<UInt, AttributeInitInfo*>::iterator endIter = mMapAttributeInitInfo.end();
		while ( frontIter != endIter)
		{
			MG_SAFE_DELETE(frontIter->second);
			++frontIter;
		}

		mMapAttributeInitInfo.clear();
	}
	//--------------------------------------------------------------------------
	AttributeInit::~AttributeInit()
	{
		clear();
	}
	//--------------------------------------------------------------------------
	void AttributeInit::setAttributeId( AttributeInitInfo* pAttributeInitInfo )
	{
		for (Int i=0; i<APPENDATTR_NUM; i++)
		{
			if ( pAttributeInitInfo->AppendAttrList[i].id == 0 )
				continue;
			const AttrInfo* pInfo = AttributeList::getInstance().getAttrInfoByInitId(pAttributeInitInfo->AppendAttrList[i].id);
			DYNAMIC_ASSERT(pInfo);
			pAttributeInitInfo->AppendAttrList[i].id = pInfo->attrId;
		}
	}
}