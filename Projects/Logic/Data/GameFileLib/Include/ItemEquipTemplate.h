//*****************************************************************************************************************
#ifndef _H_ITEM_EQUIP_TEMPLATE_
#define _H_ITEM_EQUIP_TEMPLATE_
//*****************************************************************************************************************
#include "GameFilePreqs.h"
//*****************************************************************************************************************
namespace MG
{
    //序号	    数据名称	                            中文名
    //1	        ItemEquipId                          装备类物品id
    //2	        Name                                 装备名称，16个汉字内
    //3	        Text                                 "中文描述，64汉字内，支持转义，
    //4	        ArtIconId                            提供指定颜色、换行这样的功能。"
    //5	        ArtMashId1                           装备的icon，对应Icon表的Icon
    //6	        ArtMashId2                           装备后显示的模型id,这里是男性时的模型
    //7	        ArtMashId3                           装备后显示的模型id,这里是女性时的模型装备掉落地面模型
    //8	        Price                                装备的基础价值
    //9	        BuyPrice                             装备购买花费，消耗的是游戏币
    //10	    SellPrice                            装备出售花费，消耗的是游戏币
    //11	    RepairPrice                          装备修理花费，消耗的是游戏币，100%损坏的费用
    //13	    MaxUpGrade                           装备的最大强化次数，0表示不可强化
    //14	    MaxFixNum                            装备的最大修理次数
    //15	    MaxEquipDurable                      装备的最大耐久，0表示无耐久
    //16	    Score                                装备评分等级
    //17	    Rank                                 "装备的品质类别，单选1~白、2~绿、3~蓝、4~紫"
    //18	    Class                                "装备的类型，单选具体分类待定"
    //19	    EquipSlotType                        "装备对应的的格位，单选，暂定为1~主武器，2~副武器，3~法宝，4~饰物5~头部，6~身体，7~足部，8~备用"
    //20	    SuitId                               可装备物品隶属于哪一套套装，套装外表获得
    //22	    DisappearType                        "二进制位判定的消失方式，多选。不符合消失条件，物品不会自动消失"
    //23	    ForBidType                           "二进制位判定的支持功能，多选。符合位判定的，不支持相应功能"
    //24	    ExistenceTimeType                    "物品存在的时间类型，单选1~现实时间，2~游戏时间"
    //25	    ExistenceTime                        存在的秒数，时间到后装备消失或失效
    //26	    ClanJudgeid                          装备时对氏族的要求
    //27	    CharacterJudgeid                     装备时对角色的要求
    //28	    AbilityAppendId1                     装备后基本的属性附加id
    //29	    AbilityAppendGroupId1                装备产生时，随机的属性附加id
    //30	    AbilityAppendId2                     装备强化的属性附加id
    //31	    AbilityAppendGroupId2                装备随机强化的属性附加id
    //32	    SkillTemplateID                      装备后给予的技能id
    //33	    StateTemplateID                      装备后给予的状态id
    //34	    StateTemplateNum                     给予的状态层数
    //35	    WeaponActionId                       装备后导致的攻击动作改变
    //36	    EquipSprit                           装备后的其他功能脚本
                                            
    //-------------------------------------------------------------------------------
    struct ItemEquipInfo                  
    {                                
        ItemIdType						ItemEquipId               	            ;                            
        Str16                           Name                                    ;
        Str16                           Text                                    ;
		Int								ArtIconId								;
        U32                             ArtMashId1                              ;
        U32                             ArtMashId2                              ;
        U32                             ArtMashId3                              ;
        U64                             Price                                   ;
        U64                             BuyPrice                                ;
        U64                             SellPrice                               ;
        U64                             RepairPrice                             ;
        U64                             MaxUpGrade                              ;
        U64                             MaxFixNum                               ;
        U64                             MaxEquipDurable                         ;
        U64                             Score                                   ;
        ITEM_RANK                       Rank                                    ;
        ITEM_EQUIP_CLASS                Class                                   ;
        ITEM_EQUIP_SLOT_TYPE            EquipSlotType                           ;
        U32                             SuitId                                  ;
        ITEM_BIND_TYPE                  BindType                                ;
        U32                             DisappearType                           ;
        U32                             ForBidType                              ;
        ITEM_EXISTENCE_TIME_TYPE        ExistenceTimeType                       ;
        U32                             ExistenceTime                           ;
        U32                             ClanJudgeid                             ;
        U32                             CharacterJudgeid                        ;
        U32                             AbilityAppendId1                        ;
        U32                             AbilityAppendGroupId1                   ;  
        U32                             AbilityAppendId2                        ;
        U32                             AbilityAppendGroupId2                   ;
        U32                             SkillTemplateID                         ;  
        U32                             StateTemplateID                         ;
        U64                             StateTemplateNum                        ;
        U32                             WeaponActionId                          ;
        Str16                           EquipSprit                              ;
    };
    //-------------------------------------------------------------------------------
    class ItemEquipTemplate
    {
		enum ItemEquipCsvRow
		{
			ItemEquipCsvRow_ItemEquipId               	,
			ItemEquipCsvRow_Notes						,
			ItemEquipCsvRow_Name                        ,
			ItemEquipCsvRow_Text                        ,
			ItemEquipCsvRow_ArtIconId					,
			ItemEquipCsvRow_ArtMashId1					,                 
			ItemEquipCsvRow_ArtMashId2					,                
			ItemEquipCsvRow_ArtMashId3					,               
			ItemEquipCsvRow_Price						,              
			ItemEquipCsvRow_BuyPrice					,             
			ItemEquipCsvRow_SellPrice					,            
			ItemEquipCsvRow_RepairPrice					,           
			ItemEquipCsvRow_MaxUpGrade					,          
			ItemEquipCsvRow_MaxFixNum					,         
			ItemEquipCsvRow_MaxEquipDurable				,        
			ItemEquipCsvRow_Score						,       
			ItemEquipCsvRow_Rank						,      
			ItemEquipCsvRow_Class						,     
			ItemEquipCsvRow_EquipSlotType				,    
			ItemEquipCsvRow_SuitId						,   
			ItemEquipCsvRow_BindType					,  
			ItemEquipCsvRow_DisappearType				, 
			ItemEquipCsvRow_ForBidType                  ,
			ItemEquipCsvRow_ExistenceTimeType           ,
			ItemEquipCsvRow_ExistenceTime               ,
			ItemEquipCsvRow_ClanJudgeid                 ,
			ItemEquipCsvRow_CharacterJudgeid            ,
			ItemEquipCsvRow_AbilityAppendId1            ,
			ItemEquipCsvRow_AbilityAppendGroupId1       ,
			ItemEquipCsvRow_AbilityAppendId2            ,
			ItemEquipCsvRow_AbilityAppendGroupId2       ,
			ItemEquipCsvRow_SkillTemplateID             ,
			ItemEquipCsvRow_StateTemplateID             ,
			ItemEquipCsvRow_StateTemplateNum            ,
			ItemEquipCsvRow_WeaponActionId              ,
			ItemEquipCsvRow_EquipSprit                  ,
			
			ItemEquipCsvRow_Max
		};
    public:
        ItemEquipTemplate(){;}
        ~ItemEquipTemplate();
        SINGLETON_INSTANCE(ItemEquipTemplate);

    public:
        Bool                    load(Str16 fileName, IMGExternalPackManager* packManager = NULL);
        const ItemEquipInfo*    getItemEquipInfo(ItemIdType tempID);

    private:
        SimpleMapDataSetManager<ItemIdType, ItemEquipInfo>        mItemEquipList;

    };

}
//*****************************************************************************************************************
#endif
//*****************************************************************************************************************