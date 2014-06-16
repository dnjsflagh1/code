
//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: CharacterSkillTemplate.h
//        Author: xkc
//          Date: 2011-10-25
//          Time: 18:34
// Description: 
//			1.等级模板表。
//
// modify History:
//      <author>    <time>        <descript>
//         xkc      2011-10-25      add

//////////////////////////////////////////////////////////////
//******************************************************************************************
#ifndef _H_CHARACTERSKILLTEMPLATE_
#define _H_CHARACTERSKILLTEMPLATE_
//******************************************************************************************
#include "GameFilePreqs.h"
//******************************************************************************************
namespace MG
{
    enum CHAR_SKILL_TYPE
    {
        CHAR_SKILL_TYPE_NULL,

        CHAR_SKILL_TYPE_FIGHT,
        CHAR_SKILL_TYPE_BUSINESS,

        CHAR_SKILL_TYPE_MAX
    };
    //struct  skillinfo
    //{
    //    U32 id;
    //    U32 lv;
    //};
    //-------------------------------------------------------------------------------------------
    struct CharSkillInfo
    {
        U32                CharSkillID	                        ;                 //等级的序列id 
        U32                CharSkillGroupID                     ;
        CHAR_SKILL_TYPE    CharSkillType                        ;
        UInt			   CharSkillList[CHAR_SKILL_NUM]        ;
    };
    //-------------------------------------------------------------------------------------------
    class   CharacterSkillTemplate
    {
    public:
        CharacterSkillTemplate();
        ~CharacterSkillTemplate();
        SINGLETON_INSTANCE(CharacterSkillTemplate);

    public:
		// MG_CN_MODIFY
        //加载CharacterSkillTemplate。csv
        Bool load(Str16 fileName, IMGExternalPackManager* packManager = NULL);
        const CharSkillInfo* getCharSkillInfo(U32 id);
        Bool getCharSkillInfo(U32 id, const CharSkillInfo*& info);
        const CharSkillInfo* getRandCharSkillInfo(U32 groupid);
        Bool getRandCharSkillInfo(U32 groupid, const CharSkillInfo*& info);

    protected:
        void            clear();
        void            setSkillGroupMap(CharSkillInfo* info);

    private:
        std::map<U32, CharSkillInfo*> mMapCharSkillInfo;
        std::map<U32, std::vector<U32>*> mMapSkillGroup;
    };
}
//******************************************************************************************
#endif  // _H_CHARACTERLVLBTEMPLATE_
//******************************************************************************************