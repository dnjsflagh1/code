//************************************************************************************************************
#ifndef _H_CHARACTER_TEMPLATE_JUDGE_
#define _H_CHARACTER_TEMPLATE_JUDGE_
//************************************************************************************************************
#include "GameFilePreqs.h"
//************************************************************************************************************
namespace MG
{
    //数据名称                               说明
    //CharacterJudgeId                       角色判定的调用Id
    //AbilityAppendId1                       角色属性下限判定，使用属性附加表id
    //AbilityAppendId2                       角色属性上限判定，使用属性附加表id
    //CharacterType                          "角色需要的类型，二进制多选选项类型同角色模板表中选项，但是本处为多选"
    //GenderType                             "角色需要的性别，二进制多选 选项类型同角色模板表中选项，但是本处为多选"
    //PowerfulType                           "角色需要的强度，二进制多选 选项类型同角色模板表中选项，但是本处为多选"
    //FormulaType                            "角色需要的职业，二进制多选 选项类型同角色模板表中选项，但是本处为多选"
    //RaceType                               "角色需要的种族，二进制多选 选项类型同角色模板表中选项，但是本处为多选"                                 
    //ItemClass                              "角色装备着的物品类别需求，多选 对应于可装备物品的class数据"
    //TeamId                                 角色要所处的队伍，外表id
    //MapId                                  角色所在当前地图，外表id
    //SkillId                                角色要掌握的技能，外表id
    //TimepieceId
    //NeedStateId
    //NoneStateId
    //StateFlag
    //Script                                 角色其他需求的外部脚本名

    struct CharacterJudgeInfo 
    {
        U32                     CharacterJudgeId    ;       
        U32                     CharacterType       ;
        U32						Level				;
		U32						LineageLevel		;
		U32                     AbilityAppendId		;
		U32                     GenderType          ;
        U32                     PowerfulType        ;
        U32                     ArmyType            ;
        U32                     ItemClass           ;
		U32                     InfluenceId         ;
        U32                     TeamId              ;
        U32                     InstanceID          ;
        U32                     SkillId             ;        
        U32                     StateId				;
        U32                     AddNum				;
        U32                     StateFlag           ;
		U32                     TimepieceId         ;
        Str16                   Script              ;
    };

    //--------------------------------------------------------------------------------
    class CharacterJudgeTemplate
    {
    public:
        CharacterJudgeTemplate(){;}
        ~CharacterJudgeTemplate();
        SINGLETON_INSTANCE(CharacterJudgeTemplate);

    public:
		// MG_CN_MODIFY
        Bool                                    load(Str16 fileName, IMGExternalPackManager* packManager = NULL);
        const CharacterJudgeInfo*               getCharacterJudgeInfo(U32 CharacterJudgeId);

    private:
        void                                    clear();

    private:
        std::map<U32, CharacterJudgeInfo*>       mMapCharacterJudgeInfo;

    };
}
//************************************************************************************************************
#endif
//************************************************************************************************************