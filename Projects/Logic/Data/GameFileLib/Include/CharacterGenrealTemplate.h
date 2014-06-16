
//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: CharacterGenrealTemplate.h
//        Author: xkc
//          Date: 2011-10-25
//          Time: 18:34
// Description: 
//			1.武将模板表。
//
// modify History:
//      <author>    <time>        <descript>
//         xkc      2011-10-25      add

//////////////////////////////////////////////////////////////
//******************************************************************************************
#ifndef _H_CHARACTERGENREALTEMPLATE_
#define _H_CHARACTERGENREALTEMPLATE_
//******************************************************************************************
#include "GameFilePreqs.h"
//******************************************************************************************
namespace MG
{
        //数据名称	            类型	    长度	    应用	    说明
        //CharacterGeneralId	u int	    32	        客/服	    角色模板id
        //Notes	                string	    32	        None	    策划备注，16个汉字以内
        //SurName	            string	    8	        客	        将领角色的姓，4汉字内，为空将随机获得
        //Name	                string	    8	        客	        将领角色的名，4汉字内，为空将随机获得
        //ZhiName	            string	    8	        客	        角色的字，4汉字内，可为空
        //Age	                u int	    32	        客/服	    将领角色登场年龄，以游戏中的月为单位
        //LifeSpan	            u int	    32	        客/服	    将领角色的总寿命，以游戏中的月为单位
        //OfficialLevelId	    u int	    32	        客/服	    当前拥有的一个官位等级，外表Id
        //TitleId	            u int	    32	        客/服	    当前拥有的一个头衔，外表Id
        //JobType	            int	        4	        客/服	    角色的职业
        //AspirationType	    int	        4	        客/服	    志向类型，表示了角色的主要生活目标
        //Disposition01	        u int	    32	        客/服	    善良程度，越大表示越善良
        //Disposition02	        u int	    32	        客/服	    秩序程序，越大表示趋向于规律性解决问题
        //Disposition03	        u int	    32	        客/服	    野心，越大表示野心越大
        //Disposition04	        u int	    32	        客/服	    气量大小，越大表示气量越大
        //Disposition05	        u int	    32	        客/服	    胆量大小，越大表示胆量越大
        //Disposition06	        u int	    32	        客/服	    冷静程度，越大表示越冷静
        //Disposition07	        u int	    32	        客/服	    耐心程度，越大表示越耐心
        //Disposition08	        u int	    32	        客/服	    名声重视程度，越大表示越重视
        //Disposition09	        u int	    32	        客/服	    地位重视程度，越大表示越重视
        //Disposition10	        u int	    32	        客/服	    财富重视程度，越大表示越重视
        //Disposition11	        u int	    32	        客/服	    亲友重视程度，越大表示越重视
        //Disposition12	        u int	    32	        客/服	    人才的重视程度，越大表示越重视
        //Disposition13	        u int	    32	        客/服	    对酒的喜好程度，越大表示越喜欢
        //Disposition14	        u int	    32	        客/服	    对色的喜好程度，越大表示越喜欢
        //Disposition15	        u int	    32	        客/服	    对书籍的喜好程度，越大表示越喜欢
        //Disposition16	        u int	    32	        客/服	    对艺术的喜好程度，越大表示越喜欢
    //------------------------------------------------------------------------------------------------
    enum CHAR_GENR_JOBTYPE
    {
        CHAR_GENR_JOBTYPE_NULL,

        CHAR_GENR_JOBTYPE_BRAVE,                 //1～勇毅
        CHAR_GENR_JOBTYPE_COMMANDER,             //2～统帅
        CHAR_GENR_JOBTYPE_WIT,                   //3～智谋
        CHAR_GENR_JOBTYPE_POLITY,                //4～经略
        CHAR_GENR_JOBTYPE_SWORD,                 //5～任侠
        CHAR_GENR_JOBTYPE_UNUSUAL,               //6～异人

        CHAR_GENR_JOBTYPE_MAX      

    };
    //------------------------------------------------------------------------------------------------
    enum CHAR_GENR_AspType
    {
        CHAR_GENR_AspType_NULL,

        CHAR_GENR_AspType_Sky,                    //1～一统天下 
        CHAR_GENR_AspType_King,                   //2～群雄称霸
        CHAR_GENR_AspType_duke,                   //3～地方割据
        CHAR_GENR_AspType_teacher,                //4～君王辅佐
        CHAR_GENR_AspType_cynic,                  //5～发挥才能
        CHAR_GENR_AspType_swordsman,              //6～仗义任侠
        CHAR_GENR_AspType_freeman,                //7～唯我逍遥
        CHAR_GENR_AspType_money,                  //8～富贵荣华
        CHAR_GENR_AspType_life,                   //9～平平淡淡
        CHAR_GENR_AspType_recluse,                //10～遁世隐逸
        CHAR_GENR_AspType_goodman,                //11～兼济天下
        CHAR_GENR_AspType_safe,                   //12～安全第一

        CHAR_GENR_AspType_MAX
    };
    //------------------------------------------------------------------------------------------------
    struct CharGenrealInfo
    {
       U32                     CharacterGeneralId                 ;                             //角色模板id

       Str16                   SurName	                          ;                             //将领角色的姓，4汉字内，为空将随机获得
       Str16                   Name	                              ;                             //将领角色的名，4汉字内，为空将随机获得
       Str16                   ZhiName	                          ;                             //角色的字，4汉字内，可为空

       U32                     Age	                              ;                             //将领角色登场年龄，以游戏中的月为单位
       U32                     LifeSpan	                          ;                             //将领角色的总寿命，以游戏中的月为单位
       U32                     OfficialLevelId	                  ;                             //当前拥有的一个官位等级，外表Id
       U32                     TitleId	                          ;                             //当前拥有的一个头衔，外表Id
       CHAR_GENR_JOBTYPE       JobType	                          ;                             //角色的职业
       CHAR_GENR_AspType       AspirationType	                  ;                             //志向类型，表示了角色的主要生活目标
       U32                     Disposition[DISPOSITION_NUM]	      ;                             //善良程度，越大表示越善良
    };
    //-------------------------------------------------------------------------------------------
    class   CharacterGenrealTemplate
    {
    public:
        CharacterGenrealTemplate();
        ~CharacterGenrealTemplate();
        SINGLETON_INSTANCE(CharacterGenrealTemplate);

    public:
        //加载CharacterGenrealTemplate。csv
        Bool load(Str16 fileName);
        const CharGenrealInfo* getCharGenrealInfo(U32 id);
        Bool getCharGenrealInfo(U32 id, const CharGenrealInfo*& info);

    protected:
        void clear();

    private:
        std::map<U32, CharGenrealInfo*> mMapCharGenrealInfo;
    };
}
//******************************************************************************************
#endif  // _H_CHARACTERLVLBTEMPLATE_
//******************************************************************************************