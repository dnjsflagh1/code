//******************************************************************************************
#include "stdafx.h"
#include "ResPackConfig.h"
//******************************************************************************************
namespace MG
{
	ResPackConfig::~ResPackConfig()
	{
		clear();
	}
	//-----------------------------------------------------------------------------------
	MG::Bool ResPackConfig::load( Str16 fileName )
	{
		CsvReader csvreader;

		if(!csvreader.create(fileName))
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

			ResPackInfo* resPackInfo = new ResPackInfo;
			UInt nCol = 0;

			MGStrOp::toU32(csvdata->mData[nCol++].c_str(),      resPackInfo->ResPackId     );
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(),      (U32&)resPackInfo->ResPackType  );
			MGStrOp::toString(csvdata->mData[nCol++].c_str(),   resPackInfo->ResPackDescription	        );
			MGStrOp::toString(csvdata->mData[nCol++].c_str(),   resPackInfo->ResPackName	        );
			MGStrOp::toString(csvdata->mData[nCol++].c_str(),   resPackInfo->ResPackPath	        );

			mResPackInfoList[resPackInfo->ResPackId] = resPackInfo;
		}

		return true;
	}
	//-----------------------------------------------------------------------------------
	const ResPackInfo* ResPackConfig::getResPackInfo( U32 id )
	{
		std::map<U32, ResPackInfo*>::iterator it = mResPackInfoList.find(id);
		if (it != mResPackInfoList.end())
		{
			return it->second;
		}
		return NULL;
	}
	//-----------------------------------------------------------------------------------
	void ResPackConfig::clear()
	{
		std::map<U32, ResPackInfo*>::iterator front = mResPackInfoList.begin();
		std::map<U32, ResPackInfo*>::iterator back = mResPackInfoList.end();
		while (front != back)
		{
			delete front->second;
			++front;
		}

		mResPackInfoList.clear();
	}
}