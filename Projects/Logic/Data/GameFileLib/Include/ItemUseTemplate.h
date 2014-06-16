//*****************************************************************************************************************
#ifndef _H_ITEM_USE_TEMPLATE_
#define _H_ITEM_USE_TEMPLATE_
//*****************************************************************************************************************
#include "GameFilePreqs.h"
//*****************************************************************************************************************
namespace MG
{
    //序号	    数据名称	                            中文名
    //1	        ItemUseId                               使用类物品id
    //3	        Name                                    使用类物品的名称，16个汉字内
    //4	        Text                                    "中文描述，64汉字内，支持转义，提供指定颜色、换行这样的功能。"
    //5	        ArtIconId                               使用类物品的icon，对应Icon表的Icon
    //6	        ArtMashId                               使用类物品掉落地面模型
    //7	        Price                                   使用类物品的基础价值
    //8	        BuyPrice                                使用类物品购买花费，消耗的是游戏币
    //9	        SellPrice                               使用类物品出售花费，消耗的是游戏币
    //11	    MaxPlieNum                              使用类物品的最大堆叠数量。
    //12	    Score                                   使用类物品的评分等级
    //13	    Rank                                    "使用类物品的品质类别，单选1~白、2~绿、3~蓝、4~紫"
    //14	    Class                                   "使用类物品的类型，单选具体分类待定"
    //16	    DisappearType                           "二进制位判定的消失方式，多选。不符合消失条件，物品不会自动消失"
    //17	    ForBidType                              "二进制位判定的支持功能，多选。符合位判定的，不支持相应功能"
    //18	    CastTime                                使用类物品的使用准备时长，毫秒为单位
    //19	    ExistenceTimeType                       "使用类物品的存在时间类型，单选1~现实时间，2~游戏时间"
    //20	    ExistenceTime                           存在的秒数，时间到后物品消失或失效
    //21	    PublicTimepieceId                       使用后会改变的公共计时器id
    //22	    PublicTimepieceDelay                    "使用后导致的以上计时器时长 此计时器id存在时间则物品无法被使用"
    //23	    OwnerTimepieceId                        使用后会改变的自身计时器id
    //24	    OwnerTimepieceDelay                     "使用后导致的以上计时器时长 此计时器id存在时间则物品无法被使用"
    //25	    ResetTimepieceId                        使用将对应的计时器时钟设置为0
    //26	    ResetTimepieceGroupId                   使用后将这一计时器分组的整组时钟置0
    //27	    ClanJudgeid                             使用时对氏族的要求
    //28	    CharacterJudgeid                        使用时对角色的要求
    //29	    GiveQuestId                             氏族使用可接的任务之id
    //30	    GiveItemGroupId                         氏族使用后开启的物品分组id
    //31	    SkillTemplateID                         角色使用后释放的技能id
    //32	    StateTemplateID                         角色使用后给状态的状态Id
    //33	    StateTemplateNum                        以上状态层数
    //34	    RestoreType                             "角色使用后回复目标的类型，单选:1,实际数值回复hp/mp/sp 2,最大hp/mp/sp值的千分数回复
    //35        RestoreParameter1                        HP参数
	//36        RestoreParameter2                        MP参数
	//37        RestoreParameter3                        SP参数
    //38	    UseSprit                                使用后的其他功能脚本
                       
	//enum RESTORE_TYPE	//将领使用后的回复类型
	//{
	//	RESTORE_TYPE_NULL,

	//	RESTORE_TYPE_HP = 1,		//1~回复Hp
	//	RESTORE_TYPE_MP,			//2~回复Mp
	//	RESTORE_TYPE_HP_MP,			//3~回复Hp和Mp
	//	RESTORE_TYPE_SP,			//4~回复Sp
	//	RESTORE_TYPE_HP_PERCENT,	//5~百分比回复Hp
	//	RESTORE_TYPE_MP_PERCENT,	//6~百分比回复Mp
	//	RESTORE_TYPE_HP_MP_PERCENT,	//7~百分比回复Hp和Mp
	//	RESTORE_TYPE_SP_PERCENT,	//8~百分比回复Sp

	//	RESTORE_TYPE_MAX
	//};

    //-------------------------------------------------------------------------------
    struct ItemUseInfo 
    {
		ItemIdType					ItemGeneralUseId;
		Str16						Name;
		Str16						Text;
		Int							ArtIconId;
		Int							ArtMeshId;
		U64							Price;
		U64							BuyPrice;
		U64							SellPrice;
		U64							MaxPlieNum;
		U64							Score;
		ITEM_RANK					Rank;
		ITEM_USE_CLASS				Class;
		ITEM_BIND_TYPE				BindType;
		U32							DisappearType;
		U32							ForbidType;
		U64	 						CastTime;
		ITEM_EXISTENCE_TIME_TYPE	ExistanceTimeType;
		U64	 						ExistanceTime;
		U32							PublicTimePieceId;
		U64							PublicTimePieceDelay;
		U32							OwnerTimePieceId;
		U64							OwnerTimePieceDelay;
		U32	 						ResetTimePieceId;
		U32	 						ResetTimePieceGroupId;
		U32	 						CharacterJudgeId;
		U32	 						StateId;
		U64							StateNum;
		ITEM_USE_RESTORE_TYPE	 	RestoreType;
		U32			 				RestoreParameter1;
		U32			 				RestoreParameter2;
		U32			 				RestoreParameter3;

		ItemUseInfo()
			:ItemGeneralUseId(0)
			,ArtIconId(0)
			,ArtMeshId(0)
			,Price(0)
			,BuyPrice(0)
			,SellPrice(0)
			,MaxPlieNum(0)
			,Score(0)
			,Rank(ITEM_RANK_NONE)
			,Class(ITEM_USE_CLASS_NONE)
			,BindType(ITEM_BIND_TYPE_NULL)
			,DisappearType(0)
			,ForbidType(0)
			,CastTime(0)
			,ExistanceTimeType(ITEM_EXISTENCE_TIME_TYPE_NULL)
			,ExistanceTime(0)
			,PublicTimePieceId(0)
			,PublicTimePieceDelay(0)
			,OwnerTimePieceId(0)
			,OwnerTimePieceDelay(0)
			,ResetTimePieceId(0)
			,ResetTimePieceGroupId(0)
			,CharacterJudgeId(0)
			,StateId(0)
			,StateNum(0)
			,RestoreType(ITEM_USE_RESTORE_TYPE_NULL)
			,RestoreParameter1(0)
			,RestoreParameter2(0)
			,RestoreParameter3(0)
		{
		}

    };
    //-------------------------------------------------------------------------------
    class ItemUseTemplate
    {
		enum ItemGeneralUseRow
		{
			ItemGeneralUseRow_ItemGeneralUseId,			
			ItemGeneralUseRow_Notes,
			ItemGeneralUseRow_Name,				
			ItemGeneralUseRow_Text,				
			ItemGeneralUseRow_ArtIconId,			
			ItemGeneralUseRow_ArtMeshId,			
			ItemGeneralUseRow_Price,				
			ItemGeneralUseRow_BuyPrice,			
			ItemGeneralUseRow_SellPrice,			
			ItemGeneralUseRow_MaxPlieNum,			
			ItemGeneralUseRow_Score,				
			ItemGeneralUseRow_Rank,				
			ItemGeneralUseRow_Class,				
			ItemGeneralUseRow_BindType,			
			ItemGeneralUseRow_DisapprearType,		
			ItemGeneralUseRow_ForbidType,			
			ItemGeneralUseRow_CastTime,			
			ItemGeneralUseRow_ExistanceTimeType,	
			ItemGeneralUseRow_ExistanceTime,		
			ItemGeneralUseRow_PublicTimePieceId,	
			ItemGeneralUseRow_PublicTimePieceDelay,
			ItemGeneralUseRow_OwnerTimePieceId,	
			ItemGeneralUseRow_OwnerTimePieceDelay,	
			ItemGeneralUseRow_ResetTimePieceId,	
			ItemGeneralUseRow_ResetTimePieceGroupId,
			ItemGeneralUseRow_CharacterJudgeId,			
			ItemGeneralUseRow_StateId,				
			ItemGeneralUseRow_StateNum,			
			ItemGeneralUseRow_RestoreType,			
			ItemGeneralUseRow_RestoreParameter1,
			ItemGeneralUseRow_RestoreParameter2,
			ItemGeneralUseRow_RestoreParameter3,
			ItemGeneralUseRow_Max
		};
    public:
        ItemUseTemplate(){;}
        ~ItemUseTemplate();
        SINGLETON_INSTANCE(ItemUseTemplate);

    public:
        Bool                    load(Str16 fileName, IMGExternalPackManager* packManager = NULL);
        const ItemUseInfo*      getItemUseInfo(ItemIdType tempID);

    private:
        SimpleMapDataSetManager<ItemIdType, ItemUseInfo>        mItemGeneralUseList;

    };

}
//*****************************************************************************************************************
#endif
//*****************************************************************************************************************