//*****************************************************************************************************************
#include "stdafx.h"
#include "BaseAITemplate.h"
//*****************************************************************************************************************
namespace MG
{
	enum
	{	
		AIBASEID,
		NOTES,
		AIBASETYPE,
		PARAM1,
		PARAM2,
		PARAM3,
		PARAM4,
		PARAM5,
		PARAM6,
		PARAM7,
		PARAM8,
	};

	BaseAITemplate::BaseAITemplate()
	{

	}
	//-------------------------------------------------------------------------------------------------

	BaseAITemplate::~BaseAITemplate()
	{
		clear();
	}

	//-------------------------------------------------------------------------------------------------
	// MG_CN_MODIFY
	Bool BaseAITemplate::load( Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/ )
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

			BaseAIInfo* tempInfo = new BaseAIInfo;

			MGStrOp::toU32(csvdata->mData[AIBASEID].c_str(), tempInfo->aiBaseId);

			UInt tempAIBaseType = 0;
			MGStrOp::toU32(csvdata->mData[AIBASETYPE].c_str(), tempAIBaseType);
			tempInfo->aiBaseType = (BaseAIType)tempAIBaseType;
			
			Flt tempParam = 0;

			for(UInt i = 0; i < 8; ++i)
			{
				MGStrOp::toFlt(csvdata->mData[PARAM1 + i].c_str(), tempParam);

				switch(tempInfo->aiBaseType)
				{
				case BAT_REBIRTH:
				case BAT_DISAPPEAR:
				case BAT_RANDOMMOVE:
				case BAT_ESCAPE:
				case BAT_PURSUE:
						tempParam /= 10;
					break;
				case BAT_GUARD:
					if(i == 0 || i == 1 || i == 2)
					{
						tempParam /= 10;
					}
					break;
				case BAT_KEEPDISTANCE:
					if(i == 0 || i == 2)
					{
						tempParam /= 10;
					}
					break;
				}

				tempInfo->paramList.push_back(tempParam);
			}


			mBaseAIInfoList[tempInfo->aiBaseId] = tempInfo;
		}

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	const BaseAIInfo* BaseAITemplate::getBaseAIInfo( U32 id )
	{
		std::map<UInt, BaseAIInfo*>::iterator it = mBaseAIInfoList.find(id);
		if(it == mBaseAIInfoList.end())
		{
			return NULL;
		}

		return it->second;
	}

	//-------------------------------------------------------------------------------------------------
	void BaseAITemplate::clear()
	{
		for(std::map<UInt, BaseAIInfo*>::iterator it = mBaseAIInfoList.begin(); it != mBaseAIInfoList.end(); ++it)
		{
			MG_SAFE_DELETE(it->second);
		}

		mBaseAIInfoList.clear();
	}


	//*********************************************************************************************************

}