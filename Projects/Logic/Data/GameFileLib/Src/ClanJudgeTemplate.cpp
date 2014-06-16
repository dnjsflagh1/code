//************************************************************************************************************
#include "stdafx.h"
#include "ClanJudgeTemplate.h"
//************************************************************************************************************
namespace MG
{
    ClanJudgeTemplate::~ClanJudgeTemplate()
    {
        clear();
    }
    //--------------------------------------------------------------------------------------
	// MG_CN_MODIFY
    MG::Bool ClanJudgeTemplate::load( Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/ )
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

            ClanJudgeInfo* tempInfo = new ClanJudgeInfo;
            UInt nCol = 0;

            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->ClanJudgeId                          );
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->Level								  );
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->NobilityLevel						  );
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->QuestId                              );
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->DeedId                               );  
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->ItemTemplateId                       );
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->ItemNum                              );
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->TimepieceId                          );
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->NeedStateId                          );
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->NoneStateId                          );
            tempInfo->Script = csvdata->mData[nCol++];

            mMapClanJudgeInfo[tempInfo->ClanJudgeId] = tempInfo;
        }

        return true;
    }
    //--------------------------------------------------------------------------------------
    const ClanJudgeInfo* ClanJudgeTemplate::getClanJudgeInfo( U32 ClanJudgeId )
    {
        std::map<U32, ClanJudgeInfo*>::iterator iter = mMapClanJudgeInfo.find(ClanJudgeId);
        if (iter != mMapClanJudgeInfo.end())
        {
            return iter->second;
        }

        return NULL;
    }
    //--------------------------------------------------------------------------------------
    void ClanJudgeTemplate::clear()
    {
        std::map<U32, ClanJudgeInfo*>::iterator front = mMapClanJudgeInfo.begin();
        std::map<U32, ClanJudgeInfo*>::iterator back = mMapClanJudgeInfo.end();
        while (front != back)
        {
            delete front->second;
            ++front;
        }

        mMapClanJudgeInfo.clear();
    }
}