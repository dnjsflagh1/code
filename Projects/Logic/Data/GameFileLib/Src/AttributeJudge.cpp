//******************************************************************************************
#include "stdafx.h"
#include "AttributeJudge.h"
//******************************************************************************************
#define ATTRIBUTEJUDGE_COL_NUM 19
//******************************************************************************************
namespace MG
{
	MG::Bool AttributeJudge::load( Str16 fileName, IMGExternalPackManager* packManager /*= NULL*/ )
	{
		DYNAMIC_ASSERT( mMapAttributeJudgeInfo.size() == 0 );

		CsvReader csvreader;
		// MG_CN_MODIFY
		if(!csvreader.create(fileName, packManager))
		{
			return false;
		}

		DYNAMIC_ASSERT(csvreader.getColumnSize() == ATTRIBUTEJUDGE_COL_NUM);

		CsvData* csvdata = NULL;
		Int RowCount = csvreader.count();

		for(int i = 0; i < RowCount; ++i)
		{
			csvdata = csvreader.findValue(i);
			if(!csvdata)
			{
				continue;
			}

			AttributeJudgeInfo* tempAttrInfo = new AttributeJudgeInfo;
			UInt nCol = 0;

			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempAttrInfo->AbilityJudgeId);
			nCol++;
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), (U32&)tempAttrInfo->AbilityJudgeType);

			for ( Int i=0; i<APPENDATTR_NUM; i++ )
			{
				MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempAttrInfo->AppendAttrList[i].id);
				MGStrOp::toFlt(csvdata->mData[nCol++].c_str(), tempAttrInfo->AppendAttrList[i].value);
			}

			mMapAttributeJudgeInfo[tempAttrInfo->AbilityJudgeId] = tempAttrInfo;

		}

		return true;
	}
	//--------------------------------------------------------------------------------
	const AttributeJudgeInfo* AttributeJudge::getAttributeJudgeInfo( U32 id )
	{
		std::map<UInt, AttributeJudgeInfo*>::iterator iter = mMapAttributeJudgeInfo.find(id);
		if (mMapAttributeJudgeInfo.end() != iter)
		{
			return iter->second;
		}

		return NULL;
	}
	//--------------------------------------------------------------------------------
	void AttributeJudge::clear()
	{
		std::map<UInt, AttributeJudgeInfo*>::iterator frontIter = mMapAttributeJudgeInfo.begin();
		std::map<UInt, AttributeJudgeInfo*>::iterator endIter = mMapAttributeJudgeInfo.end();
		while (frontIter != endIter)
		{
			MG_SAFE_DELETE(frontIter->second);
			++frontIter;
		}

		mMapAttributeJudgeInfo.clear();
	}
	//--------------------------------------------------------------------------------
	AttributeJudge::~AttributeJudge()
	{
		clear();
	}
}