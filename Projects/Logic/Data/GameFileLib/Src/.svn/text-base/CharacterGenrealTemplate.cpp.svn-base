//******************************************************************************************
#include "stdafx.h"
#include "CharacterGenrealTemplate.h"
//******************************************************************************************
namespace     MG
{
    CharacterGenrealTemplate::CharacterGenrealTemplate()
    {

    }
    //-------------------------------------------------------------------------------------------
    CharacterGenrealTemplate::~CharacterGenrealTemplate()
    {
        clear();
    }
    //-------------------------------------------------------------------------------------------
    Bool CharacterGenrealTemplate::load(Str16 fileName)
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

            CharGenrealInfo* tempInfo = new CharGenrealInfo;
            UInt nCol = 0;

            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->CharacterGeneralId);
            nCol++;


            tempInfo->SurName = csvdata->mData[nCol++].c_str();
            tempInfo->Name = csvdata->mData[nCol++].c_str();
            tempInfo->ZhiName = csvdata->mData[nCol++].c_str();


            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->Age	                                       );
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->LifeSpan	                                   );
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->OfficialLevelId	                           );
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->TitleId	                                   );
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), (U32&)tempInfo->JobType	                                   );
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), (U32&)tempInfo->AspirationType	                               );

            for (Int i=0; i<DISPOSITION_NUM; i++)
            {
                MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->Disposition[i]                           );
            }          

            mMapCharGenrealInfo[tempInfo->CharacterGeneralId] = tempInfo;
        }

        return true;
    }
    //-------------------------------------------------------------------------------------------
    const CharGenrealInfo* CharacterGenrealTemplate::getCharGenrealInfo( U32 id )
    {
        return mMapCharGenrealInfo[id];
    }
    //-------------------------------------------------------------------------------------------
    Bool CharacterGenrealTemplate::getCharGenrealInfo( U32 id, const CharGenrealInfo*& info )
    {
        CharGenrealInfo* pInfo = mMapCharGenrealInfo[id];
        if (pInfo)
        {
            info = pInfo;
            return true;
        }

        return false;
    }
    //-------------------------------------------------------------------------------------------
    void CharacterGenrealTemplate::clear()
    {
        std::map<U32, CharGenrealInfo*>::iterator iter = mMapCharGenrealInfo.begin();
        while (mMapCharGenrealInfo.end() != iter)
        {
            delete iter->second;
            ++iter;
        }
        mMapCharGenrealInfo.clear();
    }
}