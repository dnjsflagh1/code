//************************************************************************************************************
#include "stdafx.h"
#include "CharacterJudgeTemplate.h"
//************************************************************************************************************
namespace MG
{
    CharacterJudgeTemplate::~CharacterJudgeTemplate()
    {
        clear();
    }
    //--------------------------------------------------------------------------------------------------
    // MG_CN_MODIFY
	Bool CharacterJudgeTemplate::load( Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/ )
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

            CharacterJudgeInfo* tempInfo = new CharacterJudgeInfo;
            UInt nCol = 0;

			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->CharacterJudgeId                    );
            nCol++;
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->CharacterType                       );
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->Level			                     );
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->LineageLevel	                     );
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->AbilityAppendId                     );
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->GenderType                          );
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->PowerfulType                        );
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->ArmyType                            );
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->ItemClass                           );
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->InfluenceId                         );
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->TeamId                              );
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->InstanceID                          );
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->SkillId                             );
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->StateId			                 );
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->AddNum								 );
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->StateFlag			                 );
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->TimepieceId			             );
            tempInfo->Script = csvdata->mData[nCol++];                       
																	       
            mMapCharacterJudgeInfo[tempInfo->CharacterJudgeId] = tempInfo;
        }                                                                

        return true;
    }
    //--------------------------------------------------------------------------------------------------
    const CharacterJudgeInfo* CharacterJudgeTemplate::getCharacterJudgeInfo( U32 CharacterJudgeId )
    {
        std::map<U32, CharacterJudgeInfo*>::iterator iter = mMapCharacterJudgeInfo.find(CharacterJudgeId);
        if (iter != mMapCharacterJudgeInfo.end())
        {
            return iter->second;
        }

        return NULL;
    }
    //--------------------------------------------------------------------------------------------------
    void CharacterJudgeTemplate::clear()
    {
        std::map<U32, CharacterJudgeInfo*>::iterator front = mMapCharacterJudgeInfo.begin();
        std::map<U32, CharacterJudgeInfo*>::iterator back = mMapCharacterJudgeInfo.end();
        while (front != back)
        {
            delete front->second;
            ++front;
        }

        mMapCharacterJudgeInfo.clear();
    }
}