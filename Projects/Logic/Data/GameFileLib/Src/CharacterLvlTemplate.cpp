//******************************************************************************************
#include "stdafx.h"
#include "CharacterLvlTemplate.h"
//******************************************************************************************
namespace MG
{
    CharacterLvlTemplate::CharacterLvlTemplate()
    {

    }
    //-------------------------------------------------------------------------------------------
    CharacterLvlTemplate::~CharacterLvlTemplate()
    {
        clear();
    }
    //-------------------------------------------------------------------------------------------
    // MG_CN_MODIFY
	Bool CharacterLvlTemplate::load(Str16 filename, IMGExternalPackManager* packManager/* = NULL*/)
    {
        CsvReader csvreader;
		// MG_CN_MODIFY
        if(!csvreader.create(filename, packManager))
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

            CharLvlInfo* tempInfo = new CharLvlInfo;
            UInt nCol = 0;

            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->LevelId);
			++nCol;
            tempInfo->LevelName = csvdata->mData[nCol++].c_str();

            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), (U32&)tempInfo->UseType	);
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->UpToLvl	    );
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->SpendExp	    );
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->ClanJudgeid	    );
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->CharacterJudgeid      );

            mMapCharLvlInfo[tempInfo->LevelId] = tempInfo;

			setCharLvlInfo(tempInfo);
        }

        return true;
    }
	//-------------------------------------------------------------------------------------------
	const CharLvlInfo* CharacterLvlTemplate::getCharLvlInfo( CHAR_LVL_USETYPE type, U32 lvl )
	{
		std::map<U32, std::map<U32, CharLvlInfo*>>::iterator iter = mMapTypeLvlCharLvlInfo.find(type);
		if ( iter != mMapTypeLvlCharLvlInfo.end() )
		{
			std::map<U32, CharLvlInfo*>::iterator subIter = iter->second.find(lvl);
			if ( subIter != iter->second.end() )
				return subIter->second;
		}
		
		return NULL;
	}
	//-------------------------------------------------------------------------------------------
    void CharacterLvlTemplate::clear()
    {
        std::map<U32, CharLvlInfo*>::iterator iter = mMapCharLvlInfo.begin();
        while (mMapCharLvlInfo.end() != iter)
        {
            delete iter->second;
            ++iter;
        }
        mMapCharLvlInfo.clear();
    }
	//-------------------------------------------------------------------------------------------
	void CharacterLvlTemplate::setCharLvlInfo( CharLvlInfo* pInfo )
	{
		std::map<U32, CharLvlInfo*> mtempMap;
		std::map<U32, std::map<U32, CharLvlInfo*>>::iterator iter = mMapTypeLvlCharLvlInfo.find(pInfo->UseType);
		if ( iter != mMapTypeLvlCharLvlInfo.end() )
		{
			std::map<U32, CharLvlInfo*>::iterator subIter = iter->second.find(pInfo->UpToLvl);
			if ( subIter != iter->second.end() )
            {
				DYNAMIC_ASSERT(0);
            }
			else
			{
				(iter->second)[pInfo->UpToLvl] = pInfo;
			}
		}
		else
		{
			mtempMap[pInfo->UpToLvl] = pInfo;
			mMapTypeLvlCharLvlInfo[pInfo->UseType] = mtempMap;
		}
	}
}