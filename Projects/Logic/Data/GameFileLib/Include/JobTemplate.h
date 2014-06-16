
//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: JobTemplate.h
//        Author: xkc
//          Date: 2011-10-25
//          Time: 18:34
// Description: 
//			1.职业模板表。
//
// modify History:
//      <author>    <time>        <descript>
//         xkc      2011-10-25      add

//////////////////////////////////////////////////////////////
//******************************************************************************************
#ifndef _H_JOBTEMPLATE_
#define _H_JOBTEMPLATE_
//******************************************************************************************
namespace MG
{

//        U32    JobId	              ;     //                 职业id
//#ifdef _CLIENT
//        Str16  Text		              ;     //                 职业文字介绍，128汉字内0。
//        U32    ArtIconId1	          ;     //                 职业的图标
//#endif    
//        U32    JobType		          ;     //                 职业类型
//        U32    AbilityId01	          ;     //                 徒步速度，十项系统属性之一，属性表获取id
//        U32    AbilityNum01	          ;     //                 徒步速度的值
//        U32    AbilityId02	          ;     //                 骑乘速度，id从属性表获取
//        U32    AbilityNum02	          ;     //                 骑乘速度的值
//        U32    AbilityId03	          ;     //                 转身速度，id从属性表获取
//        U32    AbilityNum03	          ;     //                 转身速度的值
//        U32    AbilityId04	          ;     //                 攻击速度，id从属性表获取
//        U32    AbilityNum04	          ;     //                 攻击速度的值
//        U32    AbilityId05	          ;     //                 攻击范围，id从属性表获取
//        U32    AbilityNum05	          ;     //                 攻击范围的值
//        U32    AbilityId06	          ;     //                 自身隐身等级，id从属性表获取
//        U32    AbilityNum06	          ;     //                 自身隐身等级的值
//        U32    AbilityId07	          ;     //                 隐身查看等级，id从属性表获取
//        U32    AbilityNum07	          ;     //                 隐身查看等级的值
//        U32    AbilityId08	          ;     //                 视野距离，id从属性表获取
//        U32    AbilityNum08	          ;     //                 视野距离的值
//        U32    AbilityId09	          ;     //                 被索敌距离，id从属性表获取
//        U32    AbilityNum09	          ;     //                 被索敌距离的值
//        U32    AbilityId10	          ;     //                 力初始值，id从属性表获取
//        U32    AbilityNum10	          ;     //                 力初始值
//        U32    AbilityId11	          ;     //                 敏初始值，id从属性表获取
//        U32    AbilityNum11	          ;     //                 敏初始值
//        U32    AbilityId12	          ;     //                 智初始值，id从属性表获取
//        U32    AbilityNum12	          ;     //                 智初始值
//        U32    AbilityId13	          ;     //                 神初始值，id从属性表获取
//        U32    AbilityNum13	          ;     //                 神初始值
//        U32    AbilityId14	          ;     //                 体初始值，id从属性表获取
//        U32    AbilityNum14	          ;     //                 体初始值
//        U32    AbilityId15	          ;     //                 魅初始值，id从属性表获取
//        U32    AbilityNum15	          ;     //                 魅初始值
//        U32    AbilityId16	          ;     //                 力升级加值，id从属性表获取
//        U32    AbilityNum16	          ;     //                 力升级加值
//        U32    AbilityId17	          ;     //                 敏升级加值，id从属性表获取
//        U32    AbilityNum17	          ;     //                 敏升级加值
//        U32    AbilityId18	          ;     //                 智升级加值，id从属性表获取
//        U32    AbilityNum18	          ;     //                 智升级加值
//        U32    AbilityId19	          ;     //                 神升级加值，id从属性表获取
//        U32    AbilityNum19	          ;     //                 神升级加值
//        U32    AbilityId20	          ;     //                 体升级加值，id从属性表获取
//        U32    AbilityNum20	          ;     //                 体升级加值
//        U32    AbilityId21	          ;     //                 魅升级加值，id从属性表获取
//        U32    AbilityNum21           ;     //                 魅升级加值
//        U32    AbilityAppendId		  ;     //                 从属性附加外表获得，额外的附加属性
//        U32    Skill01		          ;     //                 掌握的初始技能01
//        U32    Skill01_Lvl	          ;     //                 初始技能01的等级
//        U32    Skill02		          ;     //                 掌握的初始技能02
//        U32    Skill02_Lvl	          ;     //                 初始技能02的等级
//        U32    Skill03		          ;     //                 掌握的初始技能03
//        U32    Skill03_Lvl	          ;     //                 初始技能03的等级
//        U32    Skill04		          ;     //                 掌握的初始技能04
//        U32    Skill04_Lvl	          ;     //                 初始技能04的等级
//        U32    Skill05		          ;     //                 掌握的初始技能05
//        U32    Skill05_Lvl		      ;     //                 初始技能05的等级
//        U32    Skill06		          ;     //                 掌握的初始技能06
//        U32    Skill06_Lvl		      ;     //                 初始技能06的等级
    //-----------------------------------------------------------------------
    struct  JobAttr
    {
        U32 id;        //属性ID
        U32 value;     //属性初始值
    };
    //-----------------------------------------------------------------------
    struct  JobSkill
    {
        U32 id;         //技能ID
        U32 value;      //初始等级
    };
    enum  JOB_TYPE
    {
        JOB_TYPE_NULL,  

        JOB_TYPE_CIVIL,      //文
        JOB_TYPE_MILITARY,   //武

        JOB_TYPE_MAX
    };
    //-----------------------------------------------------------------------
    struct JobTemplateInfo
    {
        U32    JobId	              ;         //                 职业id
#ifdef _CLIENT
        Str16  Text		              ;         //                 职业文字介绍，128汉字内0。
        U32    ArtIconId1	          ;         //                 职业的图标
#endif    
        U32    JobType		          ;         //                 职业类型
        U32    AbilityAppendId		  ;         //                 从属性附加外表获得，额外的附加属性

        std::map<U32, JobAttr*> mJobAttrMap;    //                 属性初始值表 
        std::map<U32, JobSkill*> mJobSkillMap;  //                 技能初始值表

        ~JobTemplateInfo();

    public:
        //根据ID获得属性初始值
        Bool                            getAttrValue( U32 id, U32& value );
        U32                             getAttrValue( U32 id );
        //根据ID获得技能初始等级
        Bool                            getSkillValue( U32 id, U32& value );
        U32                             getSkillValue( U32 id );

    protected:
        void                            clear();

    };
    //-----------------------------------------------------------------------
    class JobTemplate                       
    {
    public:
        JobTemplate();
        ~JobTemplate();
        SINGLETON_INSTANCE(JobTemplate);

    public:
        //加载 JobTemplate.csv 
        Bool                            load();
        //根据ID获得  JobTemplateInfo
        Bool                            getJobTemplateInfo(U32 id, JobTemplateInfo*& info);
        //根据ID获得  JobTemplateInfo
        JobTemplateInfo*                getJobTemplateInfo(U32 id);

    protected:
        //释放内存
        void                            clear();

    private:
        std::map<U32, JobTemplateInfo*> mJobTemplateInfoMap;

    };
}
//******************************************************************************************
#endif  // _H_JOBTEMPLATE_
//******************************************************************************************