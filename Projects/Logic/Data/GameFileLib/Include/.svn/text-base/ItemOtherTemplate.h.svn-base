//*****************************************************************************************************************
#ifndef _H_ITEM_OTHER_TEMPLATE_
#define _H_ITEM_OTHER_TEMPLATE_
//*****************************************************************************************************************
#include "GameFilePreqs.h"
//*****************************************************************************************************************
namespace MG
{

    //序号	    数据名称	                            中文名
    //1	        ItemUseId                               其他类物品id
    //3	        Name                                    其他类物品的名称，16个汉字内
    //4	        Text                                    "中文描述，64汉字内，支持转义，提供指定颜色、换行这样的功能。"
    //5	        ArtIconId                               其他类物品的icon，对应Icon表的Icon
    //6	        ArtMashId                               其他类物品掉落地面模型
    //7	        Price                                   其他类物品的基础价值
    //8	        BuyPrice                                其他类物品购买花费，消耗的是游戏币
    //9	        SellPrice                               其他类物品出售花费，消耗的是游戏币
    //11	    MaxPlieNum                              其他类物品的最大堆叠数量。
    //12	    Score                                   其他类物品的评分等级
    //13	    Rank                                    "其他类物品的品质类别，单选 1~白、2~绿、3~蓝、4~紫"
    //14	    Class                                   "其他类物品的类型，单选 具体分类待定"
    //16	    DisappearType                           "二进制位判定的消失方式，多选。不符合消失条件，物品不会自动消失"
    //17	    ForBidType                              "二进制位判定的支持功能，多选。符合位判定的，不支持相应功能"
    //18	    ExistenceTimeType                       "其他类物品的存在时间类型，单选 1~现实时间，2~游戏时间"
    //19	    ExistenceTime                           存在的秒数，时间到后物品消失或失效
    //20	    ClanJudgeid                             使用时对氏族的要求
    //21	    CharacterJudgeid                        使用时对角色的要求

    //-------------------------------------------------------------------------------
    struct ItemOtherInfo 
    {
        ItemIdType						ItemOtherId            	           ;
        Str16                           Name                               ;
        Str16                           Text                               ;
		Int								ArtIconId;
        U32                             ArtMeshId                          ;
        U64                             Price                              ;
        U64                             BuyPrice                           ;
        U64                             SellPrice                          ;
        U32                             MaxPileNum                         ;
        U64                             Score                              ;
        ITEM_RANK                       Rank                               ;
        ITEM_OTHER_CLASS                Class                              ;
        ITEM_BIND_TYPE                  BindType                           ;
        U32                             DisappearType                      ;
        U32                             ForBidType                         ;
        ITEM_EXISTENCE_TIME_TYPE        ExistenceTimeType                  ;
        U64                             ExistenceTime                      ;
		SkillIdType						SkillId								;

    };
    //-------------------------------------------------------------------------------
    class ItemOtherTemplate
    {
		enum ItemOtherCsvRow
		{
			ItemOtherCsvRow_ItemOtherId,
			ItemOtherCsvRow_ItemNotes,
			ItemOtherCsvRow_ItemName,
			ItemOtherCsvRow_ItemText,
			ItemOtherCsvRow_ArtIconId,
			ItemOtherCsvRow_ArtMeshId,
			ItemOtherCsvRow_Price,
			ItemOtherCsvRow_BuyPrice,
			ItemOtherCsvRow_SellPrice,
			ItemOtherCsvRow_MaxPileNum,
			ItemOtherCsvRow_Score,
			ItemOtherCsvRow_Rank,
			ItemOtherCsvRow_Class,
			ItemOtherCsvRow_BindType,
			ItemOtherCsvRow_DisappearType,
			ItemOtherCsvRow_ForbidType,
			ItemOtherCsvRow_ExistenceTimeType,
			ItemOtherCsvRow_ExistenceTime,
			ItemOtherCsvRow_SkillId,

			ItemOtherCsvRow_Max
		};
    public:
        ItemOtherTemplate(){;}
        ~ItemOtherTemplate();
        SINGLETON_INSTANCE(ItemOtherTemplate);

    public:
        Bool                    load(Str16 fileName, IMGExternalPackManager* packManager = NULL);
        const ItemOtherInfo*    getItemOtherInfo(ItemIdType tempID);



    private:
       SimpleMapDataSetManager<ItemIdType, ItemOtherInfo>        mItemOtherList;

    };

}
//*****************************************************************************************************************
#endif
//*****************************************************************************************************************