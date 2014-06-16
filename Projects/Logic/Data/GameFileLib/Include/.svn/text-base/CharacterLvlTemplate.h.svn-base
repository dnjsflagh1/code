
//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: CharacterLvlTemplate.h
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
#ifndef _H_CHARACTERLVLBTEMPLATE_
#define _H_CHARACTERLVLBTEMPLATE_
//******************************************************************************************
#include "GameFilePreqs.h"
//******************************************************************************************
namespace MG
{
        //数据名称	        类型	    长度	应用	 说明
        //LevelId	        u int	    32	    客/服	等级的序列id
        //LevelName	        string	    32	    客	    等级中文名，16汉字内，用于官位等
        //UseType	        u int	    32	    客/服	"等级的作用分类，统一分类表示属于一个升级经验"
        //UpToLvl	        u int	    32	    客/服	要升到的等级
        //SpendExp	        u int	    32	    客/服	升级到以上等级需要花费的经验
        //OpenType	        int	        4	    客/服	升级以上等级是否开放
        //NeedLevel	        u int	    32	    客/服	升级到以上等级需要的目标等级
        //QuestId	        u int	    32	    客/服	升级到此等级完成的任务Id
        //ExploitId	        u int	    32	    客/服	升级到此等级需要达成的成就Id
    
    //-------------------------------------------------------------------------------------------
    struct CharLvlInfo
    {
        U32                LevelId			;                 //等级的序列id

        Str16              LevelName		;                 //等级中文名，16汉字内，用于官位等

        CHAR_LVL_USETYPE   UseType			;                 //"等级的作用分类，统一分类表示属于一个升级经验"
        U32                UpToLvl			;                 //要升到的等级
        U32                SpendExp			;                 //升级到以上等级需要花费的经验
        U32                ClanJudgeid	    ;                 //升级到此等级完成的任务Id
        U32                CharacterJudgeid	;                 //升级到此等级需要达成的成就Id
    };
    //-------------------------------------------------------------------------------------------
    class   CharacterLvlTemplate
    {
    public:
        CharacterLvlTemplate();
        ~CharacterLvlTemplate();
        SINGLETON_INSTANCE(CharacterLvlTemplate);

    public:
		// MG_CN_MODIFY
        //加载CharacterLvlTemplate。csv
        Bool load(Str16 filename, IMGExternalPackManager* packManager = NULL);
        
		const CharLvlInfo* getCharLvlInfo(CHAR_LVL_USETYPE type,  U32 lvl);

    private:
        void clear();
		void setCharLvlInfo(CharLvlInfo* pInfo);
		

    private:
        std::map<U32, CharLvlInfo*> mMapCharLvlInfo;
		std::map<U32, std::map<U32, CharLvlInfo*>> mMapTypeLvlCharLvlInfo;
    };
}
//******************************************************************************************
#endif  // _H_CHARACTERLVLBTEMPLATE_
//******************************************************************************************