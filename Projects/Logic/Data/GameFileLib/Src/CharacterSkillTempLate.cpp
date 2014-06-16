//******************************************************************************************
#include "stdafx.h"
#include "CharacterSkillTemplate.h"
//******************************************************************************************
namespace MG
{
    CharacterSkillTemplate::CharacterSkillTemplate()
    {

    }
    //-------------------------------------------------------------------------------------------
    CharacterSkillTemplate::~CharacterSkillTemplate()
    {
        clear();
    }
    //-------------------------------------------------------------------------------------------
    // MG_CN_MODIFY
	Bool CharacterSkillTemplate::load(Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/)
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

            CharSkillInfo* tempInfo = new CharSkillInfo;
            UInt nCol = 0;

            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->CharSkillID                );
			nCol++;
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->CharSkillGroupID           );
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), (U32&)tempInfo->CharSkillType	    );
            for (Int j=0; j<CHAR_SKILL_NUM; j++)
            {
                MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->CharSkillList[j]	);
                //MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->CharSkillList[j].lv	);
            }

            mMapCharSkillInfo[tempInfo->CharSkillID] = tempInfo;
            if ( tempInfo->CharSkillGroupID )
                setSkillGroupMap(tempInfo);
        }

        return true;
    }
    //-------------------------------------------------------------------------------------------
    const CharSkillInfo* CharacterSkillTemplate::getCharSkillInfo( U32 id )
    {
        return mMapCharSkillInfo[id];
    }
    //-------------------------------------------------------------------------------------------
    Bool CharacterSkillTemplate::getCharSkillInfo( U32 id, const CharSkillInfo*& info )
    {
        CharSkillInfo* pInfo = mMapCharSkillInfo[id];
        if (pInfo)
        {
            info = pInfo;
            return true;
        }

        return false;
    }
    //-------------------------------------------------------------------------------------------
    void CharacterSkillTemplate::clear()
    {
        std::map<U32, CharSkillInfo*>::iterator front = mMapCharSkillInfo.begin();
        std::map<U32, CharSkillInfo*>::iterator back = mMapCharSkillInfo.end();
        while (back != front)
        {
            delete front->second;
            ++front;
        }
        mMapCharSkillInfo.clear();

        std::map<U32, std::vector<U32>*>::iterator frontg = mMapSkillGroup.begin();
        std::map<U32, std::vector<U32>*>::iterator backg = mMapSkillGroup.end();
        while (backg != frontg)
        {
            delete frontg->second;
            ++frontg;
        }
        mMapSkillGroup.clear();
    }
    //-------------------------------------------------------------------------------------------
    void CharacterSkillTemplate::setSkillGroupMap( CharSkillInfo* info )
    {
        std::map<U32, std::vector<U32>*>::iterator iter = mMapSkillGroup.find(info->CharSkillGroupID);
        if (iter != mMapSkillGroup.end())
        {
            iter->second->push_back(info->CharSkillID);
        }
        else
        {
            std::vector<U32>* tempV = new std::vector<U32>;
            mMapSkillGroup[info->CharSkillGroupID] = tempV;
            tempV->push_back(info->CharSkillID);
        }
    }
    //-------------------------------------------------------------------------------------------
    const CharSkillInfo* CharacterSkillTemplate::getRandCharSkillInfo( U32 groupid )
    {
        std::map<U32, std::vector<U32>*>::iterator iter = mMapSkillGroup.find(groupid);
        if (iter != mMapSkillGroup.end())
        {
            std::vector<U32>* tempV = iter->second;
            U32 groupSize = tempV->size();
            groupSize = MGRandom::getInstance().rand_ab_One(0, groupSize-1);

            return getCharSkillInfo( (*tempV)[groupSize] );
        }

        return NULL;
    }
    //-------------------------------------------------------------------------------------------
    MG::Bool CharacterSkillTemplate::getRandCharSkillInfo( U32 groupid, const CharSkillInfo*& info )
    {
        std::map<U32, std::vector<U32>*>::iterator iter = mMapSkillGroup.find(groupid);
        if (iter != mMapSkillGroup.end())
        {
            std::vector<U32>* tempV = iter->second;
            U32 groupSize = tempV->size();
            groupSize = MGRandom::getInstance().rand_ab_One(0, groupSize-1);

            getCharSkillInfo( (*tempV)[groupSize], info );

            return true;
        }

        return false;
    }
}