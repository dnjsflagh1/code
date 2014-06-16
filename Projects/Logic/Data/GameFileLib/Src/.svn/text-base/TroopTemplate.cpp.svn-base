//******************************************************************************************
#include "stdafx.h"
#include "TroopTemplate.h"
//******************************************************************************************
namespace MG
{
    TroopTemplate::TroopTemplate()
    {

    }
    //--------------------------------------------------------------------------------
    TroopTemplate::~TroopTemplate()
    {
       clear();
    }
    //--------------------------------------------------------------------------------
    Bool TroopTemplate::load(Str16 fileName)
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

            TroopTemplateInfo* tempInfo = new TroopTemplateInfo;
            UInt nCol = 0;

            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->ArmyTemplateId);
            nCol++;

            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->CharacterTemplateId);
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), (U32&)(tempInfo->ArmyType)	);
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->OfficialLevel	    );
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->ArmyLevel	        );
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->ArmyNumMax	        );
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->ArmyObjNum         );
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->ArmyCharacterNum	);
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->ArmyX	            );
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->ArmyY	            );
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->ListNum	        );
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->ArmyLoyal	        );
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->ArmyWeapon	        );

            for ( Int i=0; i<TROOPTEMPLATE_STATE_MAX; i++ )
            {
                MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->StateArray[i]	 );
            }

            mTroopTemplateInfoMap[tempInfo->ArmyTemplateId] = tempInfo;
        }

        return true;
    }
    //--------------------------------------------------------------------------------
    Bool TroopTemplate::getTroopTemplateInfo( U32 id, const TroopTemplateInfo*& info )
    {
        TroopTemplateInfo* pInfo = mTroopTemplateInfoMap[id];
        if ( pInfo )
        {    
            info = pInfo;
            return true;
        }

        return false;
    }
    //--------------------------------------------------------------------------------
    const TroopTemplateInfo* TroopTemplate::getTroopTemplateInfo( U32 id )
    {
        return mTroopTemplateInfoMap[id];
    }
	//--------------------------------------------------------------------------------
	const TroopTemplateInfo* TroopTemplate::getTroopTemplateInfoByIndex(Int index)
	{
		TroopTemplateInfoMapIter iter = mTroopTemplateInfoMap.begin();
		while( (index--) > 0 )
		{
			iter++;
		}
		return iter->second;
	}
    //--------------------------------------------------------------------------------
    void TroopTemplate::clear()
    {
        TroopTemplateInfoMapIter pos = mTroopTemplateInfoMap.begin();
        while ( pos != mTroopTemplateInfoMap.end() )
        {
            delete pos->second;
            ++pos;
        }
        mTroopTemplateInfoMap.clear();
    }
}