//******************************************************************************************
#include "stdafx.h"
#include "JobTemplate.h"
//******************************************************************************************
namespace MG
{
    JobTemplate::JobTemplate()
    {

    }
    //-----------------------------------------------------------------------
    JobTemplate::~JobTemplate()
    {
        clear();
    }
    //-----------------------------------------------------------------------
    Bool JobTemplate::load()
    {
        CsvReader csvreader;

        if(!csvreader.create(L"JobTemplate.csv"))
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

            JobTemplateInfo* tempInfo = new JobTemplateInfo;
            UInt nCol = 0;

            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->JobId);
            nCol++;
#ifdef _CLIENT
            tempInfo->Text = csvdata->mData[nCol++].c_str();
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->ArtIconId1);
#endif // _CLIENT

            //职业类型
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), (U32)tempInfo->JobType);

            //Attr
#define  ATTR_NUM 21
            for ( Int i=0; i<ATTR_NUM; i++ )
            {
                JobAttr* tempAttr = new JobAttr;
                MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempAttr->id);
                MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempAttr->value);
                tempInfo->mJobAttrMap[tempAttr->id] = tempAttr;
            }
#undef ATTR_NUM

            //附加属性ID
            MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempInfo->AbilityAppendId);

            //Skill
#define  SKILL_NUM 6
            for ( Int i=0; i<SKILL_NUM; i++ )
            {
                JobSkill* tempSkill = new JobSkill;
                MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempSkill->id);
                MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempSkill->value);
                tempInfo->mJobSkillMap[tempSkill->id] = tempSkill;
            }
#undef SKILL_NUM

            mJobTemplateInfoMap[tempInfo->JobId] = tempInfo;
        }

        return true;
    }
    //-----------------------------------------------------------------------
    Bool JobTemplate::getJobTemplateInfo( U32 id, JobTemplateInfo*& info )
    {
        JobTemplateInfo* pInfo = mJobTemplateInfoMap[id] ;
        if ( pInfo )
        {
            info = pInfo;
            return true;
        }

        return false;
    }
    //-----------------------------------------------------------------------
    JobTemplateInfo* JobTemplate::getJobTemplateInfo( U32 id )
    {
        return mJobTemplateInfoMap[id];
    }
    //-----------------------------------------------------------------------
    void JobTemplate::clear()
    {
        std::map<U32, JobTemplateInfo*>::iterator pos = mJobTemplateInfoMap.begin();
        while (pos != mJobTemplateInfoMap.end())
        {
            delete pos->second;
            ++pos;
        }
        mJobTemplateInfoMap.clear();
    }
    //-----------------------------------------------------------------------
    Bool JobTemplateInfo::getAttrValue( U32 id, U32& value )
    {
        JobAttr* pInfo = mJobAttrMap[id];
        if (pInfo)
        {
            value = pInfo->value;
            return true;
        }

        return false;
    }
    //-----------------------------------------------------------------------
    U32 JobTemplateInfo::getAttrValue( U32 id )
    {
        JobAttr* pInfo = mJobAttrMap[id];
        if (pInfo)
            return pInfo->value;

        return 0; 
    }
    //-----------------------------------------------------------------------
    Bool JobTemplateInfo::getSkillValue( U32 id, U32& value )
    {
        JobSkill* pInfo = mJobSkillMap[id];
        if (pInfo)
        {
            value = pInfo->value;
            return true;
        }

        return false;
    }
    //-----------------------------------------------------------------------
    U32 JobTemplateInfo::getSkillValue( U32 id )
    {
        JobSkill* pInfo = mJobSkillMap[id];
        if (pInfo)
            return pInfo->value;

        return 0;
    }
    //-----------------------------------------------------------------------
    JobTemplateInfo::~JobTemplateInfo()
    {
        clear();
    }
    //-----------------------------------------------------------------------
    void JobTemplateInfo::clear()
    {
        std::map<U32, JobAttr*>::iterator iter1 = mJobAttrMap.begin();
        while ( iter1 != mJobAttrMap.end() )
        {
            delete iter1->second;
            ++iter1;
        }
        mJobAttrMap.clear();

        std::map<U32, JobSkill*>::iterator iter2 = mJobSkillMap.begin();
        while ( iter2 != mJobSkillMap.end() )
        {
            delete iter2->second;
            ++iter2;
        }
        mJobSkillMap.clear();
    }
}